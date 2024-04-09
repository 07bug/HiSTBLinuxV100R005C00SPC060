//**********************************************************************
// File Name   : vdp_hal_wbc.cpp
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
#include "vdp_hal_wbc.h"
#include "vdp_hal_gfx.h"
#include "vdp_hal_ip_cap.h"

extern volatile S_VDP_REGS_TYPE* pVdpReg;



HI_VOID VDP_WBC_SetCmpEnable( VDP_LAYER_WBC_E enLayer, HI_U32 bEnable)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetCmpDrr( VDP_LAYER_WBC_E enLayer, HI_U32 u32CmpDrr)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetLossy( VDP_LAYER_WBC_E enLayer, HI_U32 bEnable)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetOffSet( VDP_LAYER_WBC_E enLayer, HI_U32 u32Offset)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetTunlCellAddr(VDP_LAYER_WBC_E enLayer,  HI_U32 u32Addr)
{
    VDP_CAP_SetWbcTunladdrL       (  enLayer * WBC_FDR_OFFSET, u32Addr);
    return;
}

HI_VOID VDP_WBC_SetLowdlyEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    VDP_CAP_SetLowdlyEn       (  enLayer * WBC_FDR_OFFSET, u32Enable);
    return;
}

HI_VOID VDP_WBC_SetLowdlyTestEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    VDP_CAP_SetLowdlyTest       (  enLayer * WBC_FDR_OFFSET, u32Enable);
    return;
}

HI_VOID VDP_WBC_SetWbPerLineNum(VDP_LAYER_WBC_E enLayer,  HI_U32 u32Num)
{
    VDP_CAP_SetWbPerLineNum       (  enLayer * WBC_FDR_OFFSET, u32Num);
    return;

}

HI_VOID VDP_WBC_SetPartfnsLineNum(VDP_LAYER_WBC_E enLayer,HI_U32 u32Num)
{
    VDP_CAP_SetPartfnsLineNum       (  enLayer * WBC_FDR_OFFSET, u32Num);
    return;

}

HI_VOID VDP_WBC_HistogramEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_VtthdMode(VDP_LAYER_WBC_E enLayer, HI_U32 u32wbc_vtthd_mode)
{
    U_WBC_DHD0_CTRL    WBC_DHD0_CTRL;
    if(enLayer == VDP_LAYER_WBC_HD0|| enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32)+ enLayer * WBC_OFFSET));
        WBC_DHD0_CTRL.bits.wbc_vtthd_mode =  u32wbc_vtthd_mode;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_CTRL.u32);
    }
}

HI_VOID VDP_WBC_SetOflEnable(HI_U32 bEnable)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetOflPro(HI_U32 u32Data)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetOflDispMode(HI_U32 u32Data)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetOflMixerReso(VDP_RECT_S stRect)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetOflStart(HI_VOID)
{
    DISP_INFO("98mv310 Nousing!\n");
}

//Hi3798CV200 add  p2i
HI_VOID VDP_WBC_SetProToInterEnable  (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_CTRL    WBC_DHD0_CTRL;

    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 )
    {
        WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_CTRL.bits.wbc_p2i_en =  u32Enable;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET)), WBC_DHD0_CTRL.u32);
    }
}

//-----Hi3798CV200 add poitsel---------------------------------------
HI_VOID VDP_WBC_SetWbcVpConnection  (HI_U32 enLayer, VDP_LAYER_CONN_E WbcVpConnect)
{
    U_WBC_DHD0_CTRL  WBC_DHD0_CTRL;

    WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_CTRL.bits.wbc_point_sel = WbcVpConnect;
    VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET)), WBC_DHD0_CTRL.u32);
}
//----------------------------------------------

HI_VOID VDP_WBC_SetHzmeCkGtEn (VDP_LAYER_WBC_E enLayer, HI_U32 u32CkGtEn)
{
    U_WBC_DHD0_ZME_HINFO WBC_DHD0_ZME_HINFO;

    if(enLayer == VDP_LAYER_WBC_HD0)
    {
        WBC_DHD0_ZME_HINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_HINFO.bits.ck_gt_en = u32CkGtEn;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HINFO.u32);
    }
}

HI_VOID VDP_WBC_SetVzmeCkGtEn (VDP_LAYER_WBC_E enLayer, HI_U32 u32CkGtEn)
{
    U_WBC_DHD0_ZME_VINFO WBC_DHD0_ZME_VINFO;

    if(enLayer == VDP_LAYER_WBC_HD0)
    {
        WBC_DHD0_ZME_VINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_VINFO.bits.ck_gt_en = u32CkGtEn;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VINFO.u32);
    }
}

HI_VOID VDP_WBC_SetCropPos (VDP_LAYER_WBC_E enLayer, VDP_RECT_S stRect)
{
	U_WBC_DHD0_FCROP WBC_DHD0_FCROP;
	U_WBC_DHD0_LCROP WBC_DHD0_LCROP;

    if(enLayer == VDP_LAYER_WBC_HD0
	|| enLayer == VDP_LAYER_WBC_GP0
	|| enLayer == VDP_LAYER_WBC_G0
	|| enLayer == VDP_LAYER_WBC_G4
	|| enLayer == VDP_LAYER_WBC_VP0
	)
    {
        WBC_DHD0_FCROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_FCROP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_FCROP.bits.wfcrop = stRect.u32X;
        WBC_DHD0_FCROP.bits.hfcrop = stRect.u32Y;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_FCROP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_FCROP.u32);

        WBC_DHD0_LCROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_LCROP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_LCROP.bits.wlcrop = stRect.u32Wth-1;
        WBC_DHD0_LCROP.bits.hlcrop = stRect.u32Hgt-1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_LCROP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_LCROP.u32);

    }
}

HI_VOID  VDP_WBC_SetOutReso (VDP_LAYER_WBC_E enLayer, VDP_RECT_S stRect)
{
    U_WBC_DHD0_ZME_HINFO WBC_DHD0_ZME_HINFO;
    U_WBC_DHD0_ZME_VINFO WBC_DHD0_ZME_VINFO;

    WBC_DHD0_ZME_HINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_ZME_HINFO.bits.out_width = stRect.u32Wth - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HINFO.u32);

    WBC_DHD0_ZME_VINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_ZME_VINFO.bits.out_height = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VINFO.u32);
    return ;
}

#if 1
HI_VOID  VDP_WBC_SetVideoPos     ( VDP_LAYER_WBC_E enLayer, VDP_RECT_S  stRect)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_WBC_SetDispPos     ( VDP_LAYER_WBC_E enLayer, VDP_RECT_S  stRect)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_WBC_SetVideoBkg ( VDP_LAYER_WBC_E enLayer, VDP_BKG_S stBkg)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_WBC_SetMixvBkg ( VDP_LAYER_WBC_E enLayer, VDP_BKG_S stBkg)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_WBC_SetMuteEnable     ( VDP_LAYER_WBC_E enLayer, HI_U32 bEnable)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_WBC_SetMuteBkg         ( VDP_LAYER_WBC_E enLayer, VDP_MUTE_BK_S stMuteBkg)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}
#endif

HI_VOID VDP_WBC_SetEnable( VDP_LAYER_WBC_E enLayer, HI_U32 bEnable)
{

	U_WBC_DHD0_CTRL WBC_DHD0_CTRL;

	WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
    if((enLayer == VDP_LAYER_WBC_VP0) || (enLayer == VDP_LAYER_WBC_GP0))
        WBC_DHD0_CTRL.bits.wbc_en = 0;
    else
        WBC_DHD0_CTRL.bits.wbc_en = bEnable;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET), WBC_DHD0_CTRL.u32);
}

HI_VOID VDP_WBC_SetDataWidth( VDP_LAYER_WBC_E enLayer, HI_U32 u32DataWidth)
{
    VDP_CAP_SetDataWidth      (  enLayer * WBC_FDR_OFFSET,  u32DataWidth);
}

HI_VOID  VDP_WBC_SetUpdMode (HI_U32 u32Data, HI_U32 u32UpdMode )
{
    U_WBC_DHD0_CTRL WBC_DHD0_CTRL;

    WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + u32Data * WBC_OFFSET));
    WBC_DHD0_CTRL.bits.rgup_mode =  u32UpdMode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + u32Data * WBC_OFFSET), WBC_DHD0_CTRL.u32);

    return ;
}

HI_VOID VDP_WBC_SetOutIntf (VDP_LAYER_WBC_E enLayer, VDP_DATA_RMODE_E u32RdMode)
{
    U_WBC_DHD0_CTRL WBC_DHD0_CTRL;

    if(enLayer == VDP_LAYER_WBC_HD0
	|| enLayer == VDP_LAYER_WBC_GP0
    || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_CTRL.bits.mode_out = u32RdMode;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET), WBC_DHD0_CTRL.u32);
    }
}

HI_VOID VDP_WBC_SetOutFmt(VDP_LAYER_WBC_E enLayer, VDP_WBC_OFMT_E stIntfFmt)

{
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;

    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
        if(stIntfFmt == VDP_WBC_OFMT_SP420)
        {
            WBC_DHD0_ZME_VSP.bits.zme_out_fmt = 1;
        }
        else if(stIntfFmt == VDP_WBC_OFMT_SP422)
        {
            WBC_DHD0_ZME_VSP.bits.zme_out_fmt = 0;
        }

        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
    }

}

HI_VOID VDP_WBC_SetSpd(VDP_LAYER_WBC_E enLayer, HI_U32 u32ReqSpd)
{
    VDP_CAP_SetReqInterval    (  enLayer * WBC_FDR_OFFSET , u32ReqSpd);
}

HI_VOID VDP_WBC_SetWlen(VDP_LAYER_WBC_E enLayer, VDP_WBC_WLEN_E stWlen)
{
    VDP_CAP_SetWbcLen         (  enLayer * WBC_FDR_OFFSET , stWlen);
}

HI_VOID  VDP_WBC_SetLayerAddr   (VDP_LAYER_WBC_E enLayer, HI_U32 u32LAddr,HI_U32 u32CAddr,HI_U32 u32LStr, HI_U32 u32CStr)
{
    VDP_CAP_SetWbcYaddrL      (  enLayer * WBC_FDR_OFFSET,  u32LAddr);
    VDP_CAP_SetWbcCaddrL      (  enLayer * WBC_FDR_OFFSET,  u32CAddr);
    VDP_CAP_SetWbcYstride     (  enLayer * WBC_FDR_OFFSET,  u32LStr );
    VDP_CAP_SetWbcCstride     (  enLayer * WBC_FDR_OFFSET,  u32CStr );
}

HI_VOID  VDP_WBC_SetLayerReso     (VDP_LAYER_WBC_E enLayer, VDP_DISP_RECT_S  stRect)
{
    U_WBC_DHD0_ZME_HINFO WBC_DHD0_ZME_HINFO;
    U_WBC_DHD0_ZME_VINFO WBC_DHD0_ZME_VINFO;

    WBC_DHD0_ZME_HINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_ZME_HINFO.bits.out_width = stRect.u32OWth - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HINFO.u32);

    WBC_DHD0_ZME_VINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_ZME_VINFO.bits.out_height = stRect.u32OHgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VINFO.u32);
}

HI_VOID VDP_WBC_SetBmp_Thd( VDP_LAYER_WBC_E enLayer, HI_U32 u32wbc_bmp_thd)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetDitherEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_DITHER_CTRL WBC_DHD0_DITHER_CTRL;


    if(enLayer ==  VDP_LAYER_WBC_HD0 || enLayer ==  VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32)+ enLayer * WBC_OFFSET  ));
        WBC_DHD0_DITHER_CTRL.bits.dither_en = u32Enable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) ), WBC_DHD0_DITHER_CTRL.u32);
    }
}
HI_VOID VDP_WBC_SetDitherRoundEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)

{
    U_WBC_DHD0_DITHER_CTRL WBC_DHD0_DITHER_CTRL;

    if(enLayer ==  VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        //DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET  ));
        WBC_DHD0_DITHER_CTRL.bits.dither_round= u32Enable;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) )+ enLayer * WBC_OFFSET), WBC_DHD0_DITHER_CTRL.u32);
    }
}


HI_VOID VDP_WBC_SetDitherMode  (VDP_LAYER_WBC_E enLayer, VDP_DITHER_E enDitherMode)
{
    U_WBC_DHD0_DITHER_CTRL WBC_DHD0_DITHER_CTRL;
    if(enDitherMode == VDP_DITHER_ROUND_8 )
    {
        enDitherMode =VDP_DITHER_DROP_10;
    }
    else  if(enDitherMode == VDP_DITHER_ROUND_10)
    {
        enDitherMode =VDP_DITHER_TMP_10;
    }
    if(enLayer ==  VDP_LAYER_WBC_HD0|| enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_DITHER_CTRL.bits.dither_mode= enDitherMode;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) )+ enLayer * WBC_OFFSET), WBC_DHD0_DITHER_CTRL.u32);
    }
}

HI_VOID VDP_WBC_SetDitherCoef  (VDP_LAYER_WBC_E enLayer, VDP_DITHER_COEF_S dither_coef)

{

    U_WBC_DHD0_DITHER_COEF0 WBC_DHD0_DITHER_COEF0;
    U_WBC_DHD0_DITHER_COEF1 WBC_DHD0_DITHER_COEF1;

    if(enLayer == VDP_LAYER_WBC_HD0
	|| enLayer == VDP_LAYER_WBC_GP0
	|| enLayer == VDP_LAYER_WBC_ME
    || enLayer == VDP_LAYER_WBC_VP0
	)
	{
        WBC_DHD0_DITHER_COEF0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_COEF0.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_DITHER_COEF0.bits.dither_coef0 = dither_coef.dither_coef0 ;
        WBC_DHD0_DITHER_COEF0.bits.dither_coef1 = dither_coef.dither_coef1 ;
        WBC_DHD0_DITHER_COEF0.bits.dither_coef2 = dither_coef.dither_coef2 ;
        WBC_DHD0_DITHER_COEF0.bits.dither_coef3 = dither_coef.dither_coef3 ;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_COEF0.u32) + enLayer * WBC_OFFSET), WBC_DHD0_DITHER_COEF0.u32);

        WBC_DHD0_DITHER_COEF1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_COEF1.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_DITHER_COEF1.bits.dither_coef4 = dither_coef.dither_coef4 ;
        WBC_DHD0_DITHER_COEF1.bits.dither_coef5 = dither_coef.dither_coef5 ;
        WBC_DHD0_DITHER_COEF1.bits.dither_coef6 = dither_coef.dither_coef6 ;
        WBC_DHD0_DITHER_COEF1.bits.dither_coef7 = dither_coef.dither_coef7 ;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_COEF1.u32) + enLayer * WBC_OFFSET), WBC_DHD0_DITHER_COEF1.u32);
    }
}

HI_VOID  VDP_WBC_SetCropReso (VDP_LAYER_WBC_E enLayer, VDP_DISP_RECT_S stRect)
{
	U_WBC_DHD0_FCROP WBC_DHD0_FCROP;
	U_WBC_DHD0_LCROP WBC_DHD0_LCROP;


    if(enLayer == VDP_LAYER_WBC_HD0|| enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_FCROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_FCROP.u32)+ enLayer * WBC_OFFSET ));
        WBC_DHD0_FCROP.bits.wfcrop = stRect.u32DXS;
        WBC_DHD0_FCROP.bits.hfcrop = stRect.u32DYS;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_FCROP.u32)+ enLayer * WBC_OFFSET), WBC_DHD0_FCROP.u32);

        WBC_DHD0_LCROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_LCROP.u32)+ enLayer * WBC_OFFSET));
        WBC_DHD0_LCROP.bits.wlcrop = stRect.u32DXL-1;
        WBC_DHD0_LCROP.bits.hlcrop = stRect.u32DYL-1;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_LCROP.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_LCROP.u32);
    }
}

HI_VOID  VDP_WBC_SetRegUp (VDP_LAYER_WBC_E enLayer)
{
	U_WBC_DHD0_UPD WBC_DHD0_UPD;
	WBC_DHD0_UPD.bits.regup = 0x1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_UPD.u32) + enLayer * WBC_OFFSET), WBC_DHD0_UPD.u32);

	return ;
}
HI_VOID VDP_WBC_SetHVZmeCoefAddr(VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E u32Mode, HI_U32 u32Addr)
{
    U_PARA_ADDR_VHD_CHN11 PARA_ADDR_VHD_CHN11;
    U_PARA_ADDR_VHD_CHN12 PARA_ADDR_VHD_CHN12;

    if(u32Mode == VDP_WBC_PARA_ZME_HOR)
    {
        PARA_ADDR_VHD_CHN11.bits.para_addr_vhd_chn11 = u32Addr;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN11.u32),PARA_ADDR_VHD_CHN11.u32);
    }
    else if(u32Mode == VDP_WBC_PARA_ZME_VER)
    {
        PARA_ADDR_VHD_CHN12.bits.para_addr_vhd_chn12 = u32Addr;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN12.u32),PARA_ADDR_VHD_CHN12.u32);
    }
    else
    {

    }

    return ;
}

HI_VOID VDP_WBC_SetZmeCoefAddr(VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E u32Mode, HI_U32 u32Addr)
{
    return ;
}

HI_VOID  VDP_WBC_SetParaUpd (VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E enMode)
{
    U_PARA_UP_VHD PARA_UP_VHD;

    PARA_UP_VHD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32));
    if(enMode == VDP_WBC_PARA_ZME_HOR)
    {
        PARA_UP_VHD.bits.para_up_vhd_chn11 = 1;
    }
    else if(enMode == VDP_WBC_PARA_ZME_VER)
    {
        PARA_UP_VHD.bits.para_up_vhd_chn12 = 1;
    }
    else
    {

    }
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);
    return;
}


HI_VOID VDP_WBC_SetZmeEnable  (VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;

#if WBC_GP0_EN
	U_GP0_ZME_HSP      GP0_ZME_HSP;
	U_GP0_ZME_VSP      GP0_ZME_VSP;
#endif

    /*WBC zoom enable */
    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {
        if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlmsc_en = u32bEnable;
            WBC_DHD0_ZME_HSP.bits.hlfir_en = 1;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchmsc_en = u32bEnable;
            WBC_DHD0_ZME_HSP.bits.hchfir_en = 1;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }
        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlmsc_en = u32bEnable;
            WBC_DHD0_ZME_VSP.bits.vlfir_en = 1;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchmsc_en = u32bEnable;
            WBC_DHD0_ZME_VSP.bits.vchfir_en = 1;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

    }
#if WBC_GP0_EN
    else if(enLayer == VDP_LAYER_WBC_GP0)
    {
        if((enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hsc_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vsc_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }
    }
#endif
    return ;

}

HI_VOID  VDP_WBC_SetMidEnable(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode,HI_U32 bEnable)
{

    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
#if WBC_GP0_EN
	U_GP0_ZME_HSP      GP0_ZME_HSP;
	U_GP0_ZME_VSP      GP0_ZME_VSP;
#endif
    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {
        if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);

        }

        if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }
    }
#if WBC_GP0_EN
    else if(enLayer == VDP_LAYER_WBC_GP0)
    {
        if((enMode == VDP_ZME_MODE_ALPHA)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hamid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }
        if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hlmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hchmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_ALPHAV)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vamid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }
        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vlmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vchmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }
    }
#endif
    return;

}

HI_VOID VDP_WBC_SetFirEnable(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 bEnable)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
#if WBC_GP0_EN
	U_GP0_ZME_HSP      GP0_ZME_HSP;
	U_GP0_ZME_VSP      GP0_ZME_VSP;
#endif
    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {
        if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);

        }

        if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }
    }
#if WBC_GP0_EN
    else if(enLayer == VDP_LAYER_WBC_GP0)
    {

        if((enMode == VDP_ZME_MODE_ALPHA)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hafir_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_ALPHAV)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vafir_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }
    }
#endif

    return ;

}

HI_VOID VDP_WBC_SetZmeHfirOrder(VDP_LAYER_WBC_E enLayer, HI_U32 u32HfirOrder)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
#if WBC_GP0_EN
        U_GP0_ZME_HSP      GP0_ZME_HSP;
#endif
    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {

        WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_HSP.bits.hfir_order = u32HfirOrder;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
    }
#if WBC_GP0_EN
    else if(enLayer == VDP_LAYER_WBC_GP0)
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_ZME_HSP.bits.hfir_order = u32HfirOrder;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
    }
#endif
    return ;
}

HI_VOID VDP_WBC_SetZmeHorRatio(VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
#if WBC_GP0_EN
	U_GP0_ZME_HSP      GP0_ZME_HSP;
#endif
    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_HSP.bits.hratio = u32Ratio;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
    }
#if WBC_GP0_EN
    else if(enLayer == VDP_LAYER_WBC_GP0)
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_ZME_HSP.bits.hratio = u32Ratio;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
    }
#endif
    return ;
}

HI_VOID  VDP_WBC_SetZmeInFmt(VDP_LAYER_WBC_E enLayer, VDP_PROC_FMT_E u32Fmt)
{
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;

    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_VSP.bits.zme_in_fmt = u32Fmt;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
    }

    return ;
}

HI_VOID  VDP_WBC_SetZmeOutFmt(VDP_LAYER_WBC_E enLayer, VDP_PROC_FMT_E u32Fmt)
{
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;

    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_VSP.bits.zme_out_fmt = u32Fmt;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
    }

    return ;
}

HI_VOID  VDP_WBC_SetZmeVerRatio(VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio)
{
    U_WBC_DHD0_ZME_VSR WBC_DHD0_ZME_VSR;
#if WBC_GP0_EN
	U_GP0_ZME_VSR        GP0_ZME_VSR;
#endif

    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSR.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_VSR.bits.vratio = u32Ratio;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSR.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSR.u32);
    }
#if WBC_GP0_EN
    else if(enLayer == VDP_LAYER_WBC_GP0)
    {
        GP0_ZME_VSR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSR.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_ZME_VSR.bits.vratio = u32Ratio;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSR.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSR.u32);
    }
#endif
    return ;
}

HI_VOID  VDP_WBC_SetZmePhase    (VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode,HI_S32 s32Phase)
{
    U_WBC_DHD0_ZME_HLOFFSET   WBC_DHD0_ZME_HLOFFSET;
    U_WBC_DHD0_ZME_HCOFFSET   WBC_DHD0_ZME_HCOFFSET;
    U_WBC_DHD0_ZME_VOFFSET   WBC_DHD0_ZME_VOFFSET;
    U_WBC_DHD0_ZME_VBOFFSET  WBC_DHD0_ZME_VBOFFSET;
#if WBC_GP0_EN
    U_GP0_ZME_HLOFFSET  GP0_ZME_HLOFFSET;
    U_GP0_ZME_HCOFFSET  GP0_ZME_HCOFFSET;
	U_GP0_ZME_VOFFSET        GP0_ZME_VOFFSET;
#endif

    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_ME)
    {

        if((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32) +  enLayer* WBC_OFFSET));
            WBC_DHD0_ZME_HLOFFSET.bits.hor_loffset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32) +  enLayer* WBC_OFFSET), WBC_DHD0_ZME_HLOFFSET.u32);
        }

        if((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HCOFFSET.bits.hor_coffset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32) +  enLayer* WBC_OFFSET), WBC_DHD0_ZME_HCOFFSET.u32);
        }

        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VOFFSET.bits.vluma_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VOFFSET.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VOFFSET.bits.vchroma_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VOFFSET.u32);
        }

        if((enMode == VDP_ZME_MODE_VERB)||(enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VBOFFSET.bits.vbluma_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VBOFFSET.u32);
        }

        if((enMode == VDP_ZME_MODE_VERB)||(enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VBOFFSET.bits.vbchroma_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VBOFFSET.u32);
        }
    }
#if WBC_GP0_EN
    else if(enLayer == VDP_LAYER_WBC_GP0)
    {
        if((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HLOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HLOFFSET.bits.hor_loffset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HLOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HLOFFSET.u32);
        }

        if((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HCOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HCOFFSET.bits.hor_coffset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HCOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HCOFFSET.u32);
        }

        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VOFFSET.bits.vbtm_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VOFFSET.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VOFFSET.bits.vtp_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VOFFSET.u32);
        }
    }
#endif

    return ;
}

HI_VOID  VDP_WBC_SetCscEnable  (VDP_LAYER_WBC_E enLayer, HI_U32 enCSC)
{
    U_WBC_DHD0_CSCIDC WBC_DHD0_CSCIDC;
    if(enLayer == VDP_LAYER_WBC_HD0|| enLayer == VDP_LAYER_WBC_VP0)
    {

        WBC_DHD0_CSCIDC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCIDC.u32))+ enLayer * WBC_OFFSET);
        WBC_DHD0_CSCIDC.bits.csc_en = enCSC;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCIDC.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_CSCIDC.u32);
    }
    return ;
}

HI_VOID VDP_WBC_SetCscDcCoef(VDP_LAYER_WBC_E enLayer,VDP_CSC_DC_COEF_S stCscCoef)
{
    U_WBC_DHD0_CSCIDC WBC_DHD0_CSCIDC;
    U_WBC_DHD0_CSCODC WBC_DHD0_CSCODC;
    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_FI)
    {
        WBC_DHD0_CSCIDC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCIDC.u32))+ enLayer * WBC_OFFSET);

        WBC_DHD0_CSCIDC.bits.cscidc2 = stCscCoef.csc_in_dc2;
        WBC_DHD0_CSCIDC.bits.cscidc1 = stCscCoef.csc_in_dc1;
        WBC_DHD0_CSCIDC.bits.cscidc0 = stCscCoef.csc_in_dc0;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCIDC.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_CSCIDC.u32);

        WBC_DHD0_CSCODC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCODC.u32))+ enLayer * WBC_OFFSET);
        WBC_DHD0_CSCODC.bits.cscodc2 = stCscCoef.csc_out_dc2;
        WBC_DHD0_CSCODC.bits.cscodc1 = stCscCoef.csc_out_dc1;
        WBC_DHD0_CSCODC.bits.cscodc0 = stCscCoef.csc_out_dc0;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCODC.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_CSCODC.u32);
    }
    return ;
}

HI_VOID VDP_WBC_SetCscCoef(VDP_LAYER_WBC_E enLayer,VDP_CSC_COEF_S stCscCoef)
{
    U_WBC_DHD0_CSCP0        WBC_DHD0_CSCP0;
    U_WBC_DHD0_CSCP1        WBC_DHD0_CSCP1;
    U_WBC_DHD0_CSCP2        WBC_DHD0_CSCP2;
    U_WBC_DHD0_CSCP3        WBC_DHD0_CSCP3;
    U_WBC_DHD0_CSCP4        WBC_DHD0_CSCP4;
    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_FI)
    {
        WBC_DHD0_CSCP0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP0.u32))+ enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP0.bits.cscp00 = stCscCoef.csc_coef00;
        WBC_DHD0_CSCP0.bits.cscp01 = stCscCoef.csc_coef01;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP0.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_CSCP0.u32);

        WBC_DHD0_CSCP1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP1.u32))+ enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP1.bits.cscp02 = stCscCoef.csc_coef02;
        WBC_DHD0_CSCP1.bits.cscp10 = stCscCoef.csc_coef10;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP1.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_CSCP1.u32);

        WBC_DHD0_CSCP2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP2.u32))+ enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP2.bits.cscp11 = stCscCoef.csc_coef11;
        WBC_DHD0_CSCP2.bits.cscp12 = stCscCoef.csc_coef12;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP2.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_CSCP2.u32);

        WBC_DHD0_CSCP3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP3.u32))+ enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP3.bits.cscp20 = stCscCoef.csc_coef20;
        WBC_DHD0_CSCP3.bits.cscp21 = stCscCoef.csc_coef21;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP3.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_CSCP3.u32);

        WBC_DHD0_CSCP4.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP4.u32))+ enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP4.bits.cscp22 = stCscCoef.csc_coef22;
        VDP_RegWrite((((HI_ULONG)&(pVdpReg->WBC_DHD0_CSCP4.u32))+ enLayer * WBC_OFFSET), WBC_DHD0_CSCP4.u32);
    }
}

HI_VOID VDP_WBC_SetCscMode( VDP_LAYER_WBC_E enLayer, VDP_CSC_MODE_E enCscMode)
{
    VDP_CSC_COEF_S    st_csc_coef = {0};
    VDP_CSC_DC_COEF_S st_csc_dc_coef = {0};

    HI_S32 u32Pre   ;//= 1 << 10;
    HI_S32 u32DcPre ;//= 4;//1:8bit; 4:10bit

    if(enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0|| enLayer == VDP_LAYER_WBC_FI)
    {
        u32Pre   = 1 << 10;
        u32DcPre = 1;//1:8bit; 4:10bit
        if(enCscMode == VDP_CSC_RGB2YUV_601)
        {
            st_csc_coef.csc_coef00     = (HI_S32)(0.299  * u32Pre);
            st_csc_coef.csc_coef01     = (HI_S32)(0.587  * u32Pre);
            st_csc_coef.csc_coef02     = (HI_S32)(0.114  * u32Pre);

            st_csc_coef.csc_coef10     = (HI_S32)(-0.172 * u32Pre);
            st_csc_coef.csc_coef11     = (HI_S32)(-0.339 * u32Pre);
            st_csc_coef.csc_coef12     = (HI_S32)(0.511  * u32Pre);

            st_csc_coef.csc_coef20     = (HI_S32)(0.511  * u32Pre);
            st_csc_coef.csc_coef21     = (HI_S32)(-0.428 * u32Pre);
            st_csc_coef.csc_coef22     = (HI_S32)(-0.083 * u32Pre);

            st_csc_dc_coef.csc_in_dc0  = 0 * u32DcPre;
            st_csc_dc_coef.csc_in_dc1  = 0 * u32DcPre;
            st_csc_dc_coef.csc_in_dc2  = 0 * u32DcPre;

            st_csc_dc_coef.csc_out_dc0 =  16 * u32DcPre;
            st_csc_dc_coef.csc_out_dc1 = 128 * u32DcPre;
            st_csc_dc_coef.csc_out_dc2 = 128 * u32DcPre;
        }
        else if(enCscMode == VDP_CSC_YUV2RGB_601)
        {
            st_csc_coef.csc_coef00     = (HI_S32)(    1  * u32Pre);
            st_csc_coef.csc_coef01     = (HI_S32)(    0  * u32Pre);
            st_csc_coef.csc_coef02     = (HI_S32)(1.371  * u32Pre);

            st_csc_coef.csc_coef10     = (HI_S32)(     1 * u32Pre);
            st_csc_coef.csc_coef11     = (HI_S32)(-0.698 * u32Pre);
            st_csc_coef.csc_coef12     = (HI_S32)(-0.336 * u32Pre);

            st_csc_coef.csc_coef20     = (HI_S32)(    1  * u32Pre);
            st_csc_coef.csc_coef21     = (HI_S32)(1.732  * u32Pre);
            st_csc_coef.csc_coef22     = (HI_S32)(    0  * u32Pre);

            st_csc_dc_coef.csc_in_dc0  = -16  * u32DcPre;
            st_csc_dc_coef.csc_in_dc1  = -128 * u32DcPre;
            st_csc_dc_coef.csc_in_dc2  = -128 * u32DcPre;

            st_csc_dc_coef.csc_out_dc0 =  0 * u32DcPre;
            st_csc_dc_coef.csc_out_dc1 =  0 * u32DcPre;
            st_csc_dc_coef.csc_out_dc2 =  0 * u32DcPre;
        }
        else if(enCscMode == VDP_CSC_RGB2YUV_709)
        {
            st_csc_coef.csc_coef00     = (HI_S32)(0.213  * u32Pre);
            st_csc_coef.csc_coef01     = (HI_S32)(0.715  * u32Pre);
            st_csc_coef.csc_coef02     = (HI_S32)(0.072  * u32Pre);

            st_csc_coef.csc_coef10     = (HI_S32)(-0.117 * u32Pre);
            st_csc_coef.csc_coef11     = (HI_S32)(-0.394 * u32Pre);
            st_csc_coef.csc_coef12     = (HI_S32)( 0.511 * u32Pre);

            st_csc_coef.csc_coef20     = (HI_S32)( 0.511 * u32Pre);
            st_csc_coef.csc_coef21     = (HI_S32)(-0.464 * u32Pre);
            st_csc_coef.csc_coef22     = (HI_S32)(-0.047 * u32Pre);

            st_csc_dc_coef.csc_in_dc0  = 0 * u32DcPre;
            st_csc_dc_coef.csc_in_dc1  = 0 * u32DcPre;
            st_csc_dc_coef.csc_in_dc2  = 0 * u32DcPre;

            st_csc_dc_coef.csc_out_dc0 = 16  * u32DcPre;
            st_csc_dc_coef.csc_out_dc1 = 128 * u32DcPre;
            st_csc_dc_coef.csc_out_dc2 = 128 * u32DcPre;
        }
        else if(enCscMode == VDP_CSC_YUV2RGB_709)
        {
            st_csc_coef.csc_coef00     = (HI_S32)(    1  * u32Pre);
            st_csc_coef.csc_coef01     = (HI_S32)(    0  * u32Pre);
            st_csc_coef.csc_coef02     = (HI_S32)(1.540  * u32Pre);

            st_csc_coef.csc_coef10     = (HI_S32)(     1 * u32Pre);
            st_csc_coef.csc_coef11     = (HI_S32)(-0.183 * u32Pre);
            st_csc_coef.csc_coef12     = (HI_S32)(-0.459 * u32Pre);

            st_csc_coef.csc_coef20     = (HI_S32)(    1  * u32Pre);
            st_csc_coef.csc_coef21     = (HI_S32)(1.816  * u32Pre);
            st_csc_coef.csc_coef22     = (HI_S32)(    0  * u32Pre);

            st_csc_dc_coef.csc_in_dc0  = -16  * u32DcPre;
            st_csc_dc_coef.csc_in_dc1  = -128 * u32DcPre;
            st_csc_dc_coef.csc_in_dc2  = -128 * u32DcPre;

            st_csc_dc_coef.csc_out_dc0 = 0 * u32DcPre;
            st_csc_dc_coef.csc_out_dc1 = 0 * u32DcPre;
            st_csc_dc_coef.csc_out_dc2 = 0 * u32DcPre;
        }
        else if(enCscMode == VDP_CSC_YUV2YUV_709_601)
        {
            st_csc_coef.csc_coef00     = (HI_S32)(     1 * u32Pre);
            st_csc_coef.csc_coef01     = (HI_S32)(-0.116 * u32Pre);
            st_csc_coef.csc_coef02     = (HI_S32)( 0.208 * u32Pre);

            st_csc_coef.csc_coef10     = (HI_S32)(     0 * u32Pre);
            st_csc_coef.csc_coef11     = (HI_S32)( 1.017 * u32Pre);
            st_csc_coef.csc_coef12     = (HI_S32)( 0.114 * u32Pre);

            st_csc_coef.csc_coef20     = (HI_S32)(     0 * u32Pre);
            st_csc_coef.csc_coef21     = (HI_S32)( 0.075 * u32Pre);
            st_csc_coef.csc_coef22     = (HI_S32)( 1.025 * u32Pre);

            st_csc_dc_coef.csc_in_dc0  = -16  * u32DcPre;
            st_csc_dc_coef.csc_in_dc1  = -128 * u32DcPre;
            st_csc_dc_coef.csc_in_dc2  = -128 * u32DcPre;

            st_csc_dc_coef.csc_out_dc0 =   16 * u32DcPre;
            st_csc_dc_coef.csc_out_dc1 =  128 * u32DcPre;
            st_csc_dc_coef.csc_out_dc2 =  128 * u32DcPre;
        }
        else if(enCscMode == VDP_CSC_YUV2YUV_601_709)
        {
            st_csc_coef.csc_coef00     = (HI_S32)(     1 * u32Pre);
            st_csc_coef.csc_coef01     = (HI_S32)(-0.116 * u32Pre);
            st_csc_coef.csc_coef02     = (HI_S32)( 0.208 * u32Pre);

            st_csc_coef.csc_coef10     = (HI_S32)(     0 * u32Pre);
            st_csc_coef.csc_coef11     = (HI_S32)( 1.017 * u32Pre);
            st_csc_coef.csc_coef12     = (HI_S32)( 0.114 * u32Pre);

            st_csc_coef.csc_coef20     = (HI_S32)(     0 * u32Pre);
            st_csc_coef.csc_coef21     = (HI_S32)( 0.075 * u32Pre);
            st_csc_coef.csc_coef22     = (HI_S32)( 1.025 * u32Pre);

            st_csc_dc_coef.csc_in_dc0  = -16  * u32DcPre;
            st_csc_dc_coef.csc_in_dc1  = -128 * u32DcPre;
            st_csc_dc_coef.csc_in_dc2  = -128 * u32DcPre;

            st_csc_dc_coef.csc_out_dc0 =   16 * u32DcPre;
            st_csc_dc_coef.csc_out_dc1 =  128 * u32DcPre;
            st_csc_dc_coef.csc_out_dc2 =  128 * u32DcPre;
        }
        else
        {
            st_csc_coef.csc_coef00     = (HI_S32)1 * u32Pre;
            st_csc_coef.csc_coef01     = (HI_S32)0 * u32Pre;
            st_csc_coef.csc_coef02     = (HI_S32)0 * u32Pre;

            st_csc_coef.csc_coef10     = (HI_S32)0 * u32Pre;
            st_csc_coef.csc_coef11     = (HI_S32)1 * u32Pre;
            st_csc_coef.csc_coef12     = (HI_S32)0 * u32Pre;

            st_csc_coef.csc_coef20     = (HI_S32)0 * u32Pre;
            st_csc_coef.csc_coef21     = (HI_S32)0 * u32Pre;
            st_csc_coef.csc_coef22     = (HI_S32)1 * u32Pre;

            st_csc_dc_coef.csc_in_dc0  = -16  * u32DcPre;
            st_csc_dc_coef.csc_in_dc1  = -128 * u32DcPre;
            st_csc_dc_coef.csc_in_dc2  = -128 * u32DcPre;

            st_csc_dc_coef.csc_out_dc0 =  16 * u32DcPre;
            st_csc_dc_coef.csc_out_dc1 = 128 * u32DcPre;
            st_csc_dc_coef.csc_out_dc2 = 128 * u32DcPre;
        }

        VDP_WBC_SetCscCoef  ( enLayer,st_csc_coef);
        VDP_WBC_SetCscDcCoef( enLayer,st_csc_dc_coef);
    }
    return ;
}

HI_VOID VDP_WBC_SetAutoSt( VDP_LAYER_WBC_E enLayer, HI_U32 bEnable)
{
	U_WBC_DHD0_CTRL  WBC_DHD0_CTRL;

	WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
	WBC_DHD0_CTRL.bits.auto_stop_en=  bEnable;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET), WBC_DHD0_CTRL.u32);
}

HI_VOID VDP_WBC_SetThreeMd( VDP_LAYER_WBC_E enLayer, HI_U32 bMode)
{
    U_WBC_DHD0_CTRL    WBC_DHD0_CTRL;

    if(enLayer == VDP_LAYER_WBC_HD0
	|| enLayer == VDP_LAYER_WBC_GP0
    || enLayer == VDP_LAYER_WBC_VP0
	)
    {
        WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_CTRL.bits.three_d_mode =  bMode;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET), WBC_DHD0_CTRL.u32);
    }
}

#if CDS_EN
HI_VOID VDP_WBC_SetCdsEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_HCDS WBC_DHD0_HCDS;
    if(enLayer == VDP_LAYER_WBC_HD0
	|| enLayer == VDP_LAYER_WBC_FI
    || enLayer == VDP_LAYER_WBC_VP0
	)
    {
        WBC_DHD0_HCDS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS.bits.hcds_en = u32Enable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS.u32);
    }
}

HI_VOID VDP_WBC_SetCdsFirEnable        (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_HCDS WBC_DHD0_HCDS;
    if(enLayer == VDP_LAYER_WBC_HD0
    || enLayer == VDP_LAYER_WBC_VP0
	|| enLayer == VDP_LAYER_WBC_FI
	)
    {
        WBC_DHD0_HCDS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS.bits.hchfir_en = u32Enable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS.u32);
    }
}

HI_VOID VDP_WBC_SetCdsMidEnable        (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_HCDS WBC_DHD0_HCDS;
    if(enLayer == VDP_LAYER_WBC_HD0
    || enLayer == VDP_LAYER_WBC_VP0
	|| enLayer == VDP_LAYER_WBC_FI
	)
    {
        WBC_DHD0_HCDS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS.bits.hchmid_en = u32Enable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS.u32);
    }
}

HI_VOID VDP_WBC_SetCdsCoef             (VDP_LAYER_WBC_E enLayer, HI_S32 * s32Coef)
{
    U_WBC_DHD0_HCDS_COEF0 WBC_DHD0_HCDS_COEF0;
    U_WBC_DHD0_HCDS_COEF1 WBC_DHD0_HCDS_COEF1;

    if(enLayer == VDP_LAYER_WBC_HD0
    || enLayer == VDP_LAYER_WBC_VP0
	|| enLayer == VDP_LAYER_WBC_FI
	)
    {
        WBC_DHD0_HCDS_COEF0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS_COEF0.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS_COEF0.bits.coef0 = s32Coef[0];
        WBC_DHD0_HCDS_COEF0.bits.coef1 = s32Coef[1];
        WBC_DHD0_HCDS_COEF0.bits.coef2 = s32Coef[2];
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS_COEF0.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS_COEF0.u32);

        WBC_DHD0_HCDS_COEF1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS_COEF1.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS_COEF1.bits.coef3 = s32Coef[3];
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_HCDS_COEF1.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS_COEF1.u32);
    }
}
#endif


HI_VOID VDP_WBC_SetConnection(HI_U32 u32LayerId, HI_U32 u32Data )
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetCoefReadEnable(HI_U32 u32Id, HI_U32 u32Para)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetCoefReadDisable(HI_U32 u32Id, HI_U32 u32Para)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetCmpMb(VDP_LAYER_WBC_E enLayer, HI_U32 u32MbBits)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetCmpMaxMin(VDP_LAYER_WBC_E enLayer, HI_U32 u32MinBitsCnt, HI_U32 u32MaxBitsCnt)
{
    DISP_INFO("98mv310 Nousing!\n");
}
HI_VOID VDP_WBC_SetCmpAdjThr(VDP_LAYER_WBC_E enLayer, HI_U32 u32AdjSadThr, HI_U32 u32AdjSadBitThr,HI_U32 u32AdjSpecBitThr)
{
    DISP_INFO("98mv310 Nousing!\n");
}
HI_VOID VDP_WBC_SetCmpBigGrad(VDP_LAYER_WBC_E enLayer, HI_U32 u32BigGradThr, HI_U32 u32BigGradNumThr)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetCmpBlk(VDP_LAYER_WBC_E enLayer, HI_U32 u32SmthThr, HI_U32 u32BlkCompThr)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetCmpGraphic(VDP_LAYER_WBC_E enLayer, HI_U32 u32GrcEn, HI_U32 u32VideoSadThr)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetCmpRateCtrl(VDP_LAYER_WBC_E enLayer, HI_U32 u32MaxTrow, HI_U32 u32SmthGain, HI_U32 u32SadBitNgain)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetCmpFrameSize(VDP_LAYER_WBC_E enLayer, HI_U32 u32FrameSize)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetMasterSel  (HI_U32 u32Data, HI_U32 u32MasterNum)
{
    DISP_INFO("98mv310 Nousing!\n");
}


//wbc flip
HI_VOID VDP_WBC_SetFlipEnable(HI_U32 u32LayerId, HI_U32 u32Enable)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetUVOrder(HI_U32 u32LayerId, HI_U32 u32Enable)
{
  VDP_CAP_SetUvOrder    (  u32LayerId * WBC_FDR_OFFSET,  u32Enable    );
}

HI_VOID VDP_WBC_SetDhdFlip(HI_U32 u32LayerId, HI_U32 u32Data )
{
    DISP_INFO("98mv310 Nousing!\n");
}
HI_VOID VDP_WBC_SetGpFlip(HI_U32 u32LayerId, HI_U32 u32Data )
{
    DISP_INFO("98mv310 Nousing!\n");
}


HI_VOID VDP_WBC_SetHorZmeEnable        (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    DISP_INFO("98mv310 Nousing!\n");

}

HI_VOID VDP_WBC_SetHorZmeMidEnable     (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetHorZmeFirEnable     (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_SetBtDebug     (VDP_LAYER_WBC_E enLayer, HI_U32 u32FmtSel)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_WBC_ConfigSmmuBypass(VDP_LAYER_WBC_E enLayer, HI_BOOL bBypass)
{
    VDP_CAP_SetMmu3dBypass (enLayer, bBypass );
    VDP_CAP_SetMmu2dBypass (enLayer, bBypass );
}

HI_VOID VDP_WBC_GetWbcDHD0StateLineNum(HI_U32 *pu32WbcLineNum)
{
    U_WBC_LINE_NUM         WBC_LINE_NUM;
    WBC_LINE_NUM.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->WBC_LINE_NUM.u32));
    *pu32WbcLineNum = WBC_LINE_NUM.bits.wbc_l_linenum;
    return;
}

HI_VOID VDP_WBC_GetWbcDHD0PartFnsLineNum(HI_U32 *pu32PartFnsLineNum)
{
    U_WBC_WORK_LOWDLYCTRL   WBC_WORK_LOWDLYCTRL;
    WBC_WORK_LOWDLYCTRL.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->WBC_WORK_LOWDLYCTRL.u32));
    *pu32PartFnsLineNum = ((WBC_WORK_LOWDLYCTRL.u32)& 0xfff000) >> 12;
    return;
}

