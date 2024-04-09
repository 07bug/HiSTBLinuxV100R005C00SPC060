#include "vdp_hal_comm.h"
#include "vdp_hal_wbc.h"
#include "vdp_hal_gfx.h"

#include "vdp_drv_func.h"

extern S_VDP_REGS_TYPE *pVdpReg;


HI_VOID VDP_WBC_SetTunlCellAddr(VDP_LAYER_WBC_E enLayer,  HI_U32 u32Addr)
{
    U_WBC_DHD0_TUNLADDR     WBC_DHD0_TUNLADDR;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 )
    {
        WBC_DHD0_TUNLADDR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_TUNLADDR.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_TUNLADDR.bits.tunl_cell_addr =  u32Addr;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_TUNLADDR.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_TUNLADDR.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetTunlCellAddr() select wrong layer id\n");
    }

}

HI_VOID VDP_WBC_ConfigSmmuBypass(VDP_LAYER_WBC_E enLayer,  HI_BOOL bBypass)
{
    U_WBC_DHD0_SMMU_BYPASS    WBC_DHD0_SMMU_BYPASS;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 )
    {
        WBC_DHD0_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_SMMU_BYPASS.bits.l_bypass =  bBypass;
        WBC_DHD0_SMMU_BYPASS.bits.c_bypass =  bBypass;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_SMMU_BYPASS.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetTunlCellAddr() select wrong layer id\n");
    }

}

HI_VOID VDP_WBC_SetLowdlyEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_LOWDLYCTRL    WBC_DHD0_LOWDLYCTRL;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_LOWDLYCTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_LOWDLYCTRL.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_LOWDLYCTRL.bits.lowdly_en =  u32Enable;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_LOWDLYCTRL.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_LOWDLYCTRL.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetLowdlyEnable() select wrong layer id\n");
    }

}


HI_VOID VDP_WBC_SetWbPerLineNum(VDP_LAYER_WBC_E enLayer,  HI_U32 u32Num)
{
    U_WBC_DHD0_LOWDLYCTRL    WBC_DHD0_LOWDLYCTRL;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_LOWDLYCTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_LOWDLYCTRL.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_LOWDLYCTRL.bits.wb_per_line_num =  u32Num - 1;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_LOWDLYCTRL.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_LOWDLYCTRL.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetWbPerLineNum() select wrong layer id\n");
    }

}

HI_VOID VDP_WBC_SetPartfnsLineNum(VDP_LAYER_WBC_E enLayer, HI_U32 u32Num)
{
    U_WBC_DHD0_LOWDLYCTRL    WBC_DHD0_LOWDLYCTRL;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_LOWDLYCTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_LOWDLYCTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_LOWDLYCTRL.bits.partfns_line_num = u32Num - 1;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_LOWDLYCTRL.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_LOWDLYCTRL.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetPartfnsLineNum() select wrong layer id\n");
    }

}


//Hi3798CV200 add  p2i
HI_VOID VDP_WBC_SetProToInterEnable  (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_CTRL    WBC_DHD0_CTRL;
    if ((enLayer != VDP_LAYER_WBC_HD0) && (enLayer != VDP_LAYER_WBC_VP0))
    {
        VDP_PRINT("Error, VDP_WBC_SetProToInterEnable() select wrong dhd layer id\n");
        return ;

    }

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 )
    {
        WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_CTRL.bits.wbc_p2i_en =  u32Enable;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET)), WBC_DHD0_CTRL.u32);
    }
}

//-----Hi3798CV200 add poitsel---------------------------------------
HI_VOID VDP_WBC_SetWbcVpConnection  (HI_U32 enLayer, VDP_LAYER_CONN_E WbcVpConnect)
{
    U_WBC_DHD0_CTRL  WBC_DHD0_CTRL;

    if (enLayer != VDP_LAYER_WBC_VP0)
    {
        VDP_PRINT("Error, VDP_WBC_SetWbcVpConnection() select wrong dhd layer id\n");
        return ;

    }

    WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_CTRL.bits.wbc_point_sel = WbcVpConnect;
    VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET)), WBC_DHD0_CTRL.u32);
}
//----------------------------------------------

HI_VOID VDP_WBC_SetCropPos (VDP_LAYER_WBC_E enLayer, VDP_RECT_S stRect)
{
    U_WBC_DHD0_FCROP WBC_DHD0_FCROP;
    U_WBC_DHD0_LCROP WBC_DHD0_LCROP;

    if (enLayer == VDP_LAYER_WBC_HD0
        || enLayer == VDP_LAYER_WBC_GP0
        || enLayer == VDP_LAYER_WBC_G0
        || enLayer == VDP_LAYER_WBC_G4
        || enLayer == VDP_LAYER_WBC_VP0
       )
    {
        WBC_DHD0_FCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_FCROP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_FCROP.bits.wfcrop = stRect.u32X;
        WBC_DHD0_FCROP.bits.hfcrop = stRect.u32Y;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_FCROP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_FCROP.u32);

        WBC_DHD0_LCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_LCROP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_LCROP.bits.wlcrop = stRect.u32Wth - 1;
        WBC_DHD0_LCROP.bits.hlcrop = stRect.u32Hgt - 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_LCROP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_LCROP.u32);

    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetCropPos() select wrong layer id\n");
    }
    return ;
}

HI_VOID  VDP_WBC_SetOutReso (VDP_LAYER_WBC_E enLayer, VDP_RECT_S stRect)
{
    U_WBC_DHD0_ORESO WBC_DHD0_ORESO;
#ifdef VDP_HI3798MV200
    if (enLayer == VDP_LAYER_WBC_VP0)
    {
        U_WBC_DHD0_VFPOS WBC_DHD0_VFPOS;
        U_WBC_DHD0_VLPOS WBC_DHD0_VLPOS;
        U_WBC_DHD0_DFPOS WBC_DHD0_DFPOS;
        U_WBC_DHD0_DLPOS WBC_DHD0_DLPOS;

        /*video position */
        WBC_DHD0_VFPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_VFPOS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_VFPOS.bits.video_xfpos = 0;
        WBC_DHD0_VFPOS.bits.video_yfpos = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_VFPOS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_VFPOS.u32);

        WBC_DHD0_VLPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_VLPOS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_VLPOS.bits.video_xlpos = stRect.u32Wth - 1;
        WBC_DHD0_VLPOS.bits.video_ylpos = stRect.u32Hgt - 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_VLPOS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_VLPOS.u32);


        /*video position */
        WBC_DHD0_DFPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_DFPOS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_DFPOS.bits.disp_xfpos = 0;
        WBC_DHD0_DFPOS.bits.disp_yfpos = 0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_DFPOS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_DFPOS.u32);

        WBC_DHD0_DLPOS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_DLPOS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_DLPOS.bits.disp_xlpos = stRect.u32Wth - 1;
        WBC_DHD0_DLPOS.bits.disp_ylpos = stRect.u32Hgt - 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_DLPOS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_DLPOS.u32);
    }
#endif

    WBC_DHD0_ORESO.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ORESO.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_ORESO.bits.ow = stRect.u32Wth - 1;
    WBC_DHD0_ORESO.bits.oh = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ORESO.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ORESO.u32);

    return ;
}

HI_VOID VDP_WBC_SetEnable( VDP_LAYER_WBC_E enLayer, HI_U32 bEnable)
{

    U_WBC_DHD0_CTRL WBC_DHD0_CTRL;

    WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_CTRL.bits.wbc_en = bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET), WBC_DHD0_CTRL.u32);
}

HI_VOID VDP_WBC_SetOutIntf (VDP_LAYER_WBC_E enLayer, VDP_DATA_RMODE_E u32RdMode)
{
    U_WBC_DHD0_CTRL WBC_DHD0_CTRL;

    if (enLayer == VDP_LAYER_WBC_HD0
        || enLayer == VDP_LAYER_WBC_GP0
        || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_CTRL.bits.mode_out = u32RdMode;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET), WBC_DHD0_CTRL.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetOutIntf() select wrong layer id\n");
    }
}

HI_VOID VDP_WBC_SetOutFmt(VDP_LAYER_WBC_E enLayer, VDP_WBC_OFMT_E stIntfFmt)

{
    U_WBC_DHD0_CTRL WBC_DHD0_CTRL;

    WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_CTRL.bits.format_out = stIntfFmt;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET), WBC_DHD0_CTRL.u32);

}


HI_VOID  VDP_WBC_SetLayerAddr   (VDP_LAYER_WBC_E enLayer, HI_U32 u32LAddr, HI_U32 u32CAddr, HI_U32 u32LStr, HI_U32 u32CStr)
{
    U_WBC_DHD0_STRIDE WBC_DHD0_STRIDE;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_YADDR.u32) + enLayer * WBC_OFFSET), u32LAddr);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_CADDR.u32) + enLayer * WBC_OFFSET), u32CAddr);
    WBC_DHD0_STRIDE.bits.wbclstride = u32LStr;
    WBC_DHD0_STRIDE.bits.wbccstride = u32CStr;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_STRIDE.u32) + enLayer * WBC_OFFSET), WBC_DHD0_STRIDE.u32);

    return ;
}

HI_VOID  VDP_WBC_SetLayerReso     (VDP_LAYER_WBC_E enLayer, VDP_DISP_RECT_S  stRect)
{
    U_WBC_DHD0_ORESO WBC_DHD0_ORESO;

    WBC_DHD0_ORESO.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ORESO.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_ORESO.bits.ow = stRect.u32OWth - 1;
    WBC_DHD0_ORESO.bits.oh = stRect.u32OHgt - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ORESO.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ORESO.u32);

}

HI_VOID VDP_WBC_SetDitherEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)

{
    U_WBC_DHD0_DITHER_CTRL WBC_DHD0_DITHER_CTRL;
    U_WBC_GP0_DITHER_CTRL  WBC_GP0_DITHER_CTRL;
    U_WBC_ME_DITHER_CTRL   WBC_ME_DITHER_CTRL;


    if (enLayer ==  VDP_LAYER_WBC_HD0 || enLayer ==  VDP_LAYER_WBC_VP0)
    {
        //DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET  ));
        WBC_DHD0_DITHER_CTRL.bits.dither_en = u32Enable;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_DITHER_CTRL.u32) ) + enLayer * WBC_OFFSET), WBC_DHD0_DITHER_CTRL.u32);
    }
    else  if (enLayer ==  VDP_LAYER_WBC_GP0)
    {
        WBC_GP0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_GP0_DITHER_CTRL.u32)  ));
        WBC_GP0_DITHER_CTRL.bits.dither_en = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_GP0_DITHER_CTRL.u32) ), WBC_GP0_DITHER_CTRL.u32);
    }
    else  if (enLayer ==  VDP_LAYER_WBC_ME)
    {
        WBC_ME_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_ME_DITHER_CTRL.u32)  ));
        WBC_ME_DITHER_CTRL.bits.dither_en = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_ME_DITHER_CTRL.u32) ), WBC_ME_DITHER_CTRL.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetDitherEnable() select wrong layer id\n");
    }


}
HI_VOID VDP_WBC_SetDitherRoundEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)

{
    U_WBC_DHD0_DITHER_CTRL WBC_DHD0_DITHER_CTRL;
    U_WBC_GP0_DITHER_CTRL  WBC_GP0_DITHER_CTRL;
    U_WBC_ME_DITHER_CTRL   WBC_ME_DITHER_CTRL;

    if (enLayer ==  VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        //DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET  ));
        WBC_DHD0_DITHER_CTRL.bits.dither_round = u32Enable;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_DITHER_CTRL.u32) ) + enLayer * WBC_OFFSET), WBC_DHD0_DITHER_CTRL.u32);
    }
    else  if (enLayer ==  VDP_LAYER_WBC_GP0)
    {
        WBC_GP0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_GP0_DITHER_CTRL.u32)  ));
        WBC_GP0_DITHER_CTRL.bits.dither_round = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_GP0_DITHER_CTRL.u32) ), WBC_GP0_DITHER_CTRL.u32);
    }
    else  if (enLayer ==  VDP_LAYER_WBC_ME)
    {
        WBC_ME_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_ME_DITHER_CTRL.u32)  ));
        WBC_ME_DITHER_CTRL.bits.dither_round = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_ME_DITHER_CTRL.u32) ), WBC_ME_DITHER_CTRL.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetDitherRoundEnable() select wrong layer id\n");
    }


}


HI_VOID VDP_WBC_SetDitherMode  (VDP_LAYER_WBC_E enLayer, VDP_DITHER_E enDitherMode)
{
    U_WBC_DHD0_DITHER_CTRL WBC_DHD0_DITHER_CTRL;
    U_WBC_GP0_DITHER_CTRL  WBC_GP0_DITHER_CTRL;
    U_WBC_ME_DITHER_CTRL   WBC_ME_DITHER_CTRL;

    if (enDitherMode == VDP_DITHER_ROUND_8 )
    {
        enDitherMode = VDP_DITHER_DROP_10;
    }
    else  if (enDitherMode == VDP_DITHER_ROUND_10)
    {
        enDitherMode = VDP_DITHER_TMP_10;
    }
    else
    {
        ;// VDP_PRINT("Error,VDP_WBC_SetDitherMode() select wrong Mode!!!!  \n");
    }

    if (enLayer ==  VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET));
        //WBC_DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32)  ));
        WBC_DHD0_DITHER_CTRL.bits.dither_mode = enDitherMode;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_DITHER_CTRL.u32) ) + enLayer * WBC_OFFSET), WBC_DHD0_DITHER_CTRL.u32);
    }
    else  if (enLayer ==  VDP_LAYER_WBC_GP0)
    {
        WBC_GP0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_GP0_DITHER_CTRL.u32)  ));
        WBC_GP0_DITHER_CTRL.bits.dither_mode = enDitherMode;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_GP0_DITHER_CTRL.u32) ), WBC_GP0_DITHER_CTRL.u32);
    }
    else  if (enLayer ==  VDP_LAYER_WBC_ME)
    {
        WBC_ME_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_ME_DITHER_CTRL.u32)  ));
        WBC_ME_DITHER_CTRL.bits.dither_mode = enDitherMode;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_ME_DITHER_CTRL.u32) ), WBC_ME_DITHER_CTRL.u32);
    }
    else
    {
        ;//  VDP_PRINT("Error,VDP_WBC_SetDitherMode() select wrong layer id\n");
    }


    // U_WBC_DHD0_DITHER_CTRL WBC_DHD0_DITHER_CTRL;

    // if(enLayer == VDP_LAYER_WBC_HD0
    // || enLayer == VDP_LAYER_WBC_GP0
    // || enLayer == VDP_LAYER_WBC_ME
    // )
    // {
    //     WBC_DHD0_DITHER_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET));
    //     WBC_DHD0_DITHER_CTRL.bits.dither_md = enDitherMode;
    //     VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_DITHER_CTRL.u32) + enLayer * WBC_OFFSET), WBC_DHD0_DITHER_CTRL.u32);

    // }

}

HI_VOID  VDP_WBC_SetCropReso (VDP_LAYER_WBC_E enLayer, VDP_DISP_RECT_S stRect)
{
    U_WBC_DHD0_FCROP WBC_DHD0_FCROP;
    U_WBC_DHD0_LCROP WBC_DHD0_LCROP;

    U_WBC_GP0_FCROP WBC_GP0_FCROP;
    U_WBC_GP0_LCROP WBC_GP0_LCROP;

    U_WBC_G0_FCROP WBC_G0_FCROP;
    U_WBC_G0_LCROP WBC_G0_LCROP;


    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_FCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_FCROP.u32) + enLayer * WBC_OFFSET ));
        WBC_DHD0_FCROP.bits.wfcrop = stRect.u32DXS;
        WBC_DHD0_FCROP.bits.hfcrop = stRect.u32DYS;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_FCROP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_FCROP.u32);

        WBC_DHD0_LCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_LCROP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_LCROP.bits.wlcrop = stRect.u32DXL - 1;
        WBC_DHD0_LCROP.bits.hlcrop = stRect.u32DYL - 1;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_LCROP.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_LCROP.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        WBC_GP0_FCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_GP0_FCROP.u32)));
        WBC_GP0_FCROP.bits.wfcrop = stRect.u32DXS;
        WBC_GP0_FCROP.bits.hfcrop = stRect.u32DYS;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_GP0_FCROP.u32)), WBC_GP0_FCROP.u32);

        WBC_GP0_LCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_GP0_LCROP.u32)));
        WBC_GP0_LCROP.bits.wlcrop = stRect.u32DXL - 1;
        WBC_GP0_LCROP.bits.hlcrop = stRect.u32DYL - 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_GP0_LCROP.u32)), WBC_GP0_LCROP.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_G0)
    {
        WBC_G0_FCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_G0_FCROP.u32)));
        WBC_G0_FCROP.bits.wfcrop = stRect.u32DXS;
        WBC_G0_FCROP.bits.hfcrop = stRect.u32DYS;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_G0_FCROP.u32)), WBC_G0_FCROP.u32);

        WBC_G0_LCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_G0_LCROP.u32)));
        WBC_G0_LCROP.bits.wlcrop = stRect.u32DXL - 1;
        WBC_G0_LCROP.bits.hlcrop = stRect.u32DYL - 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_G0_LCROP.u32)), WBC_G0_LCROP.u32);


    }
    else if (enLayer == VDP_LAYER_WBC_G4)
    {
        WBC_G0_FCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_G0_FCROP.u32) + WBC_OFFSET));
        WBC_G0_FCROP.bits.wfcrop = stRect.u32DXS;
        WBC_G0_FCROP.bits.hfcrop = stRect.u32DYS;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_G0_FCROP.u32) + WBC_OFFSET), WBC_G0_FCROP.u32);

        WBC_G0_LCROP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_G0_LCROP.u32) + WBC_OFFSET));
        WBC_G0_LCROP.bits.wlcrop = stRect.u32DXL - 1;
        WBC_G0_LCROP.bits.hlcrop = stRect.u32DYL - 1;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_G0_LCROP.u32) + WBC_OFFSET), WBC_G0_LCROP.u32);
    }

    //if(enLayer == VDP_LAYER_WBC_HD0
    //|| enLayer == VDP_LAYER_WBC_GP0
    //|| enLayer == VDP_LAYER_WBC_G0
    //|| enLayer == VDP_LAYER_WBC_G4
    //)
    //{
    //    WBC_DHD0_FCROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_FCROP.u32) + enLayer * WBC_OFFSET));
    //    WBC_DHD0_FCROP.bits.wfcrop = stRect.u32DXS;
    //    WBC_DHD0_FCROP.bits.hfcrop = stRect.u32DYS;
    //    VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_FCROP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_FCROP.u32);

    //    WBC_DHD0_LCROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_LCROP.u32) + enLayer * WBC_OFFSET));
    //    WBC_DHD0_LCROP.bits.wlcrop = stRect.u32DXL-1;
    //    WBC_DHD0_LCROP.bits.hlcrop = stRect.u32DYL-1;
    //    VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_LCROP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_LCROP.u32);

    //}
    return ;
}
#if 0
HI_VOID VDP_WBC_SetSmmuLBypass(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_SMMU_BYPASS  WBC_DHD0_SMMU_BYPASS ;

    WBC_DHD0_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_SMMU_BYPASS.bits.l_bypass = u32Enable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_SMMU_BYPASS.u32);
}

HI_VOID VDP_WBC_SetSmmuCBypass(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_SMMU_BYPASS  WBC_DHD0_SMMU_BYPASS ;

    WBC_DHD0_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32) + enLayer * WBC_OFFSET));
    WBC_DHD0_SMMU_BYPASS.bits.c_bypass = u32Enable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_SMMU_BYPASS.u32);
}
#endif

HI_VOID  VDP_WBC_SetRegUp (VDP_LAYER_WBC_E enLayer)
{
    U_WBC_DHD0_UPD WBC_DHD0_UPD;
    WBC_DHD0_UPD.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_UPD.u32) + enLayer * WBC_OFFSET), WBC_DHD0_UPD.u32);

    return ;
}

HI_VOID VDP_WBC_SetZmeCoefAddr(VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E u32Mode, HI_U32 u32Addr)
{
    U_WBC_DHD0_HLCOEFAD WBC_DHD0_HLCOEFAD;
    U_WBC_DHD0_HCCOEFAD WBC_DHD0_HCCOEFAD;
    U_WBC_DHD0_VLCOEFAD WBC_DHD0_VLCOEFAD;
    U_WBC_DHD0_VCCOEFAD WBC_DHD0_VCCOEFAD;

    HI_U32 ADDR_OFFSET = 0x100 ;
#if WBC_GP0_EN
    U_GP0_HCOEFAD      GP0_HCOEFAD;
    U_GP0_VCOEFAD      GP0_VCOEFAD;
#endif

    if ( enLayer == VDP_LAYER_WBC_HD0 ||  enLayer == VDP_LAYER_WBC_ME || enLayer == VDP_LAYER_WBC_VP0 )
    {
        if (u32Mode == VDP_WBC_PARA_ZME_HOR)
        {
            WBC_DHD0_HLCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HLCOEFAD.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_HLCOEFAD.bits.coef_addr = u32Addr;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HLCOEFAD.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HLCOEFAD.u32);

            WBC_DHD0_HCCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCCOEFAD.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_HCCOEFAD.bits.coef_addr = (u32Addr + ADDR_OFFSET) & 0xfffffff0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCCOEFAD.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCCOEFAD.u32);

        }
        else if (u32Mode == VDP_WBC_PARA_ZME_VER)
        {
            WBC_DHD0_VLCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_VLCOEFAD.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_VLCOEFAD.bits.coef_addr = u32Addr;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_VLCOEFAD.u32) + enLayer * WBC_OFFSET), WBC_DHD0_VLCOEFAD.u32);

            WBC_DHD0_VCCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_VCCOEFAD.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_VCCOEFAD.bits.coef_addr = (u32Addr + ADDR_OFFSET) & 0xfffffff0;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_VCCOEFAD.u32) + enLayer * WBC_OFFSET), WBC_DHD0_VCCOEFAD.u32);

        }
        else
        {
            VDP_PRINT("Error,VDP_WBC_SetZmeCoefAddr() Select a Wrong Mode!\n");
        }

    }



#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        if (u32Mode == VDP_WBC_PARA_ZME_HOR)
        {
            GP0_HCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_HCOEFAD.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_HCOEFAD.bits.coef_addr = u32Addr;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_HCOEFAD.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_HCOEFAD.u32);
        }
        else if (u32Mode == VDP_WBC_PARA_ZME_VER)
        {
            GP0_VCOEFAD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_VCOEFAD.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_VCOEFAD.bits.coef_addr = u32Addr;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_VCOEFAD.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_VCOEFAD.u32);
        }
        else
        {
            VDP_PRINT("Error,VDP_GP_SetZmeCoefAddr() Select a Wrong Mode!\n");
        }
    }
#endif
    return ;

}

HI_VOID  VDP_WBC_SetParaUpd (VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E enMode)
{
    U_WBC_DHD0_PARAUP WBC_DHD0_PARAUP;
    U_WBC_ME_PARAUP WBC_ME_PARAUP;
#if WBC_GP0_EN
    U_GP0_PARAUP GP0_PARAUP;
    GP0_PARAUP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_PARAUP.u32) + WBC_GP0_SEL * GP_OFFSET));
#endif


    if ( enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {

        WBC_DHD0_PARAUP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_PARAUP.u32)) + enLayer * WBC_OFFSET);
        if (enMode == VDP_WBC_PARA_ZME_HOR)
        {
            WBC_DHD0_PARAUP.bits.wbc_hlcoef_upd = 0x1;
            WBC_DHD0_PARAUP.bits.wbc_hccoef_upd = 0x1;
        }
        else if (enMode == VDP_WBC_PARA_ZME_VER)
        {
            WBC_DHD0_PARAUP.bits.wbc_vlcoef_upd = 0x1;
            WBC_DHD0_PARAUP.bits.wbc_vccoef_upd = 0x1;
        }
        else
        {
            VDP_PRINT("error,VDP_WBC_DHD0_SetParaUpd() select wrong mode!\n");
        }

        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_PARAUP.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_PARAUP.u32);
        return ;
    }
#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {

        if (enMode == VDP_WBC_PARA_ZME_HOR)
        {
            GP0_PARAUP.bits.gp0_hcoef_upd = 0x1;
        }
        else if (enMode == VDP_WBC_PARA_ZME_VER)
        {
            GP0_PARAUP.bits.gp0_vcoef_upd = 0x1;
        }
        else
        {
            VDP_PRINT("error,VDP_GP_SetParaUpd() select wrong mode!\n");
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_PARAUP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_PARAUP.u32);
        return ;
    }
#endif
    else if ( enLayer == VDP_LAYER_WBC_ME)
    {

        WBC_ME_PARAUP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_ME_PARAUP.u32)));
        if (enMode == VDP_WBC_PARA_ZME_HOR)
        {
            WBC_ME_PARAUP.bits.wbc_hlcoef_upd = 0x1;
            WBC_ME_PARAUP.bits.wbc_hccoef_upd = 0x1;
        }
        else if (enMode == VDP_WBC_PARA_ZME_VER)
        {
            WBC_ME_PARAUP.bits.wbc_vlcoef_upd = 0x1;
            WBC_ME_PARAUP.bits.wbc_vccoef_upd = 0x1;
        }
        else
        {
            VDP_PRINT("error,VDP_WBC_DHD0_SetParaUpd() select wrong mode!\n");
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_ME_PARAUP.u32)), WBC_ME_PARAUP.u32);
        return ;
    }
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
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_ME)
    {
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlmsc_en = u32bEnable;
            WBC_DHD0_ZME_HSP.bits.hlfir_en = 1;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchmsc_en = u32bEnable;
            WBC_DHD0_ZME_HSP.bits.hchfir_en = 1;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        //if((enMode == VDP_ZME_MODE_NONL)||(enMode == VDP_ZME_MODE_ALL))
        //{
        //    WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)));
        //    WBC_DHD0_ZME_HSP.bits.non_lnr_en = u32bEnable;
        //    VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)), WBC_DHD0_ZME_HSP.u32);
        //}


        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlmsc_en = u32bEnable;
            WBC_DHD0_ZME_VSP.bits.vlfir_en = 1;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchmsc_en = u32bEnable;
            WBC_DHD0_ZME_VSP.bits.vchfir_en = 1;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

    }
#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        if ((enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hsc_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vsc_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }

        return ;
    }
#endif
    return ;

}

HI_VOID  VDP_WBC_SetMidEnable(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 bEnable)
{

    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
#if WBC_GP0_EN
    U_GP0_ZME_HSP      GP0_ZME_HSP;
    U_GP0_ZME_VSP      GP0_ZME_VSP;
#endif
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_ME)
    {
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);

        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }
    }
#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        if ((enMode == VDP_ZME_MODE_ALPHA) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hamid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hlmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hchmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_ALPHAV) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vamid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }
        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vlmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vchmid_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
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
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_ME)
    {
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);

        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }
    }
#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {

        if ((enMode == VDP_ZME_MODE_ALPHA) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hafir_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HSP.bits.hfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_ALPHAV) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vafir_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VSP.bits.vfir_en = bEnable;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_VSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSP.u32);
        }
    }
#endif

    return ;

}

#if 0
HI_VOID VDP_WBC_SetZmeVerTap(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 u32VerTap)
{
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
    if (enLayer == VDP_LAYER_WBC_HD0 )
    {
        /*
           if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
           {
           WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32)));
           WBC_DHD0_ZME_VSP.bits.vsc_luma_tap = u32VerTap;
           VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32)), WBC_DHD0_ZME_VSP.u32);
           }
         */


        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32)));
            WBC_DHD0_ZME_VSP.bits.vsc_chroma_tap = u32VerTap;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32)), WBC_DHD0_ZME_VSP.u32);
        }
    }

}
#endif

HI_VOID VDP_WBC_SetZmeHfirOrder(VDP_LAYER_WBC_E enLayer, HI_U32 u32HfirOrder)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
#if WBC_GP0_EN
    U_GP0_ZME_HSP      GP0_ZME_HSP;
#endif
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_ME)
    {

        WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_HSP.bits.hfir_order = u32HfirOrder;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
    }
#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_ZME_HSP.bits.hfir_order = u32HfirOrder;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
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
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_HSP.bits.hratio = u32Ratio;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
    }
#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_ZME_HSP.bits.hratio = u32Ratio;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HSP.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HSP.u32);
    }
#endif
    return ;
}

HI_VOID  VDP_WBC_SetZmeInFmt(VDP_LAYER_WBC_E enLayer, VDP_PROC_FMT_E u32Fmt)
{
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_VSP.bits.zme_in_fmt = u32Fmt;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
    }

    return ;
}

HI_VOID  VDP_WBC_SetZmeOutFmt(VDP_LAYER_WBC_E enLayer, VDP_PROC_FMT_E u32Fmt)
{
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_VSP.bits.zme_out_fmt = u32Fmt;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSP.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
    }

    return ;
}

HI_VOID  VDP_WBC_SetZmeVerRatio(VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio)
{
    U_WBC_DHD0_ZME_VSR WBC_DHD0_ZME_VSR;
#if WBC_GP0_EN
    U_GP0_ZME_VSR        GP0_ZME_VSR;
#endif

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSR.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_ZME_VSR.bits.vratio = u32Ratio;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VSR.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VSR.u32);
    }
#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        GP0_ZME_VSR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_VSR.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_ZME_VSR.bits.vratio = u32Ratio;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_VSR.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VSR.u32);
    }
#endif
    return ;
}

HI_VOID  VDP_WBC_SetZmePhase    (VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_S32 s32Phase)
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

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_ME)
    {

        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32) +  enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HLOFFSET.bits.hor_loffset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32) +  enLayer * WBC_OFFSET), WBC_DHD0_ZME_HLOFFSET.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_HCOFFSET.bits.hor_coffset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32) +  enLayer * WBC_OFFSET), WBC_DHD0_ZME_HCOFFSET.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VOFFSET.bits.vluma_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VOFFSET.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VOFFSET.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VOFFSET.bits.vchroma_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VOFFSET.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VOFFSET.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERBL) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VBOFFSET.bits.vbluma_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VBOFFSET.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERBC) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32) + enLayer * WBC_OFFSET));
            WBC_DHD0_ZME_VBOFFSET.bits.vbchroma_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32) + enLayer * WBC_OFFSET), WBC_DHD0_ZME_VBOFFSET.u32);
        }
    }
#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HLOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HLOFFSET.bits.hor_loffset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HLOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HLOFFSET.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_HCOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_HCOFFSET.bits.hor_coffset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_HCOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_HCOFFSET.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_VOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VOFFSET.bits.vbtm_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_VOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VOFFSET.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            GP0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_ZME_VOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET));
            GP0_ZME_VOFFSET.bits.vtp_offset = s32Phase;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_ZME_VOFFSET.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_ZME_VOFFSET.u32);
        }
    }
#endif

    return ;
}

HI_VOID  VDP_WBC_SetCscEnable  (VDP_LAYER_WBC_E enLayer, HI_U32 enCSC)
{
    U_WBC_DHD0_CSCIDC WBC_DHD0_CSCIDC;
#if WBC_GP0_EN
    U_GP0_CSC_IDC     GP0_CSC_IDC;
#endif

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {

        WBC_DHD0_CSCIDC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCIDC.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_CSCIDC.bits.csc_en = enCSC;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCIDC.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_CSCIDC.u32);
    }
#if WBC_GP0_EN
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        GP0_CSC_IDC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CSC_IDC.u32) + WBC_GP0_SEL * GP_OFFSET));
#ifdef VDP_HI3798MV200
        GP0_CSC_IDC.bits.csc_en = 0;
#else
        GP0_CSC_IDC.bits.csc_en = enCSC;
#endif
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CSC_IDC.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_CSC_IDC.u32);

    }
#endif
    return ;
}

HI_VOID VDP_WBC_SetCscDcCoef(VDP_LAYER_WBC_E enLayer, VDP_CSC_DC_COEF_S stCscCoef)
{
    U_WBC_DHD0_CSCIDC WBC_DHD0_CSCIDC;
    U_WBC_DHD0_CSCODC WBC_DHD0_CSCODC;
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_FI)
    {
        WBC_DHD0_CSCIDC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCIDC.u32)) + enLayer * WBC_OFFSET);

        WBC_DHD0_CSCIDC.bits.cscidc2 = stCscCoef.csc_in_dc2;
        WBC_DHD0_CSCIDC.bits.cscidc1 = stCscCoef.csc_in_dc1;
        WBC_DHD0_CSCIDC.bits.cscidc0 = stCscCoef.csc_in_dc0;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCIDC.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_CSCIDC.u32);

        WBC_DHD0_CSCODC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCODC.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_CSCODC.bits.cscodc2 = stCscCoef.csc_out_dc2;
        WBC_DHD0_CSCODC.bits.cscodc1 = stCscCoef.csc_out_dc1;
        WBC_DHD0_CSCODC.bits.cscodc0 = stCscCoef.csc_out_dc0;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCODC.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_CSCODC.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        U_GP0_CSC_IDC  GP0_CSC_IDC;
        U_GP0_CSC_ODC  GP0_CSC_ODC;
        U_GP0_CSC_IODC GP0_CSC_IODC;
        GP0_CSC_IDC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CSC_IDC.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_CSC_IDC.bits.cscidc1  = stCscCoef.csc_in_dc1;
        GP0_CSC_IDC.bits.cscidc0  = stCscCoef.csc_in_dc0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CSC_IDC.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_CSC_IDC.u32);

        GP0_CSC_ODC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CSC_ODC.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_CSC_ODC.bits.cscodc1 = stCscCoef.csc_out_dc1;
        GP0_CSC_ODC.bits.cscodc0 = stCscCoef.csc_out_dc0;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CSC_ODC.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_CSC_ODC.u32);

        GP0_CSC_IODC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CSC_IODC.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_CSC_IODC.bits.cscodc2 = stCscCoef.csc_out_dc2;
        GP0_CSC_IODC.bits.cscidc2 = stCscCoef.csc_in_dc2;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CSC_IODC.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_CSC_IODC.u32);
    }
    return ;
}

HI_VOID VDP_WBC_SetCscCoef(VDP_LAYER_WBC_E enLayer, VDP_CSC_COEF_S stCscCoef)
{
    U_WBC_DHD0_CSCP0        WBC_DHD0_CSCP0;
    U_WBC_DHD0_CSCP1        WBC_DHD0_CSCP1;
    U_WBC_DHD0_CSCP2        WBC_DHD0_CSCP2;
    U_WBC_DHD0_CSCP3        WBC_DHD0_CSCP3;
    U_WBC_DHD0_CSCP4        WBC_DHD0_CSCP4;
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0 || enLayer == VDP_LAYER_WBC_FI)
    {
        WBC_DHD0_CSCP0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP0.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP0.bits.cscp00 = stCscCoef.csc_coef00;
        WBC_DHD0_CSCP0.bits.cscp01 = stCscCoef.csc_coef01;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP0.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_CSCP0.u32);

        WBC_DHD0_CSCP1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP1.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP1.bits.cscp02 = stCscCoef.csc_coef02;
        WBC_DHD0_CSCP1.bits.cscp10 = stCscCoef.csc_coef10;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP1.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_CSCP1.u32);

        WBC_DHD0_CSCP2.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP2.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP2.bits.cscp11 = stCscCoef.csc_coef11;
        WBC_DHD0_CSCP2.bits.cscp12 = stCscCoef.csc_coef12;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP2.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_CSCP2.u32);

        WBC_DHD0_CSCP3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP3.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP3.bits.cscp20 = stCscCoef.csc_coef20;
        WBC_DHD0_CSCP3.bits.cscp21 = stCscCoef.csc_coef21;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP3.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_CSCP3.u32);

        WBC_DHD0_CSCP4.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP4.u32)) + enLayer * WBC_OFFSET);
        WBC_DHD0_CSCP4.bits.cscp22 = stCscCoef.csc_coef22;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_CSCP4.u32)) + enLayer * WBC_OFFSET), WBC_DHD0_CSCP4.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        U_GP0_CSC_P0            GP0_CSC_P0;
        U_GP0_CSC_P1            GP0_CSC_P1;
        U_GP0_CSC_P2            GP0_CSC_P2;
        U_GP0_CSC_P3            GP0_CSC_P3;
        U_GP0_CSC_P4            GP0_CSC_P4;

        GP0_CSC_P0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CSC_P0.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_CSC_P0.bits.cscp00 = stCscCoef.csc_coef00;
        GP0_CSC_P0.bits.cscp01 = stCscCoef.csc_coef01;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CSC_P0.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_CSC_P0.u32);

        GP0_CSC_P1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CSC_P1.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_CSC_P1.bits.cscp02 = stCscCoef.csc_coef02;
        GP0_CSC_P1.bits.cscp10 = stCscCoef.csc_coef10;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CSC_P1.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_CSC_P1.u32);

        GP0_CSC_P2.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CSC_P2.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_CSC_P2.bits.cscp11 = stCscCoef.csc_coef11;
        GP0_CSC_P2.bits.cscp12 = stCscCoef.csc_coef12;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CSC_P2.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_CSC_P2.u32);

        GP0_CSC_P3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CSC_P3.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_CSC_P3.bits.cscp20 = stCscCoef.csc_coef20;
        GP0_CSC_P3.bits.cscp21 = stCscCoef.csc_coef21;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CSC_P3.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_CSC_P3.u32);

        GP0_CSC_P4.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CSC_P4.u32) + WBC_GP0_SEL * GP_OFFSET));
        GP0_CSC_P4.bits.cscp22 = stCscCoef.csc_coef22;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CSC_P4.u32) + WBC_GP0_SEL * GP_OFFSET), GP0_CSC_P4.u32);
    }

}

HI_VOID VDP_WBC_SetThreeMd( VDP_LAYER_WBC_E enLayer, HI_U32 bMode)
{
    U_WBC_DHD0_CTRL    WBC_DHD0_CTRL;

    if (enLayer == VDP_LAYER_WBC_HD0
        || enLayer == VDP_LAYER_WBC_GP0
        || enLayer == VDP_LAYER_WBC_VP0
       )
    {
        WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_CTRL.bits.three_d_mode =  bMode;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + enLayer * WBC_OFFSET), WBC_DHD0_CTRL.u32);
    }
}

#if CDS_EN
HI_VOID VDP_WBC_SetCdsEnable(VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_HCDS WBC_DHD0_HCDS;
    if (enLayer == VDP_LAYER_WBC_HD0
        || enLayer == VDP_LAYER_WBC_FI
        || enLayer == VDP_LAYER_WBC_VP0
       )
    {
        WBC_DHD0_HCDS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS.bits.hcds_en = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetCdsEnable() Select a Wrong layer!\n");
    }
}

HI_VOID VDP_WBC_SetCdsFirEnable        (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_HCDS WBC_DHD0_HCDS;
    if (enLayer == VDP_LAYER_WBC_HD0
        || enLayer == VDP_LAYER_WBC_VP0
        || enLayer == VDP_LAYER_WBC_FI
       )
    {
        WBC_DHD0_HCDS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS.bits.hchfir_en = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetCdsFirEnable() Select a Wrong layer!\n");
    }
}

HI_VOID VDP_WBC_SetCdsMidEnable        (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_HCDS WBC_DHD0_HCDS;
    if (enLayer == VDP_LAYER_WBC_HD0
        || enLayer == VDP_LAYER_WBC_VP0
        || enLayer == VDP_LAYER_WBC_FI
       )
    {
        WBC_DHD0_HCDS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS.bits.hchmid_en = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetCdsMidEnable() Select a Wrong layer!\n");
    }
}

HI_VOID VDP_WBC_SetCdsCoef             (VDP_LAYER_WBC_E enLayer, HI_S32 *s32Coef)
{
    U_WBC_DHD0_HCDS_COEF0 WBC_DHD0_HCDS_COEF0;
    U_WBC_DHD0_HCDS_COEF1 WBC_DHD0_HCDS_COEF1;

    if (enLayer == VDP_LAYER_WBC_HD0
        || enLayer == VDP_LAYER_WBC_VP0
        || enLayer == VDP_LAYER_WBC_FI
       )
    {
        WBC_DHD0_HCDS_COEF0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS_COEF0.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS_COEF0.bits.coef0 = s32Coef[0];
        WBC_DHD0_HCDS_COEF0.bits.coef1 = s32Coef[1];
        WBC_DHD0_HCDS_COEF0.bits.coef2 = s32Coef[2];
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS_COEF0.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS_COEF0.u32);

        WBC_DHD0_HCDS_COEF1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS_COEF1.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HCDS_COEF1.bits.coef3 = s32Coef[3];
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HCDS_COEF1.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HCDS_COEF1.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetCdsCoef() Select a Wrong layer!\n");
    }
}
#endif

#if 0
//mod me
HI_VOID VDP_WBC_SetDhdLocate(HI_U32 u32Id, VDP_WBC_LOCATE_E   u32Data)

{
    if (u32Id >= CHN_MAX)
    {
        VDP_PRINT("error,VDP_WBC_SetDhdLocate() select wrong layer id\n");
        return ;
    }

    U_WBC_DHD_LOCATE  WBC_DHD_LOCATE;

    WBC_DHD_LOCATE.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD_LOCATE.u32)));
    WBC_DHD_LOCATE.bits.wbc_dhd_locate = (HI_U32) u32Data;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD_LOCATE.u32)), WBC_DHD_LOCATE.u32);
}


HI_VOID VDP_WBC_SetDhdOflEn(HI_U32 u32Id, HI_U32  u32Data)
{
    if (u32Id >= CHN_MAX)
    {
        VDP_PRINT("error,VDP_WBC_SetDhdLocate() select wrong layer id\n");
        return ;
    }

    U_WBC_OFL_EN  WBC_OFL_EN;

    WBC_OFL_EN.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)));
    WBC_OFL_EN.bits.wbc_ofl_en = u32Data;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)), WBC_OFL_EN.u32);
}
#endif

#if 0
//new_add wbc_dhd
HI_VOID VDP_WBC_SetDhdOflEn(VDP_LAYER_WBC_E enLayer, HI_U32 u32Data)
{
    U_WBC_OFL_EN WBC_OFL_EN;
    if (enLayer == VDP_LAYER_WBC_HD0)
    {

        WBC_OFL_EN.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)));
        WBC_OFL_EN.bits.wbc0_ofl_en = u32Data;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)), WBC_OFL_EN.u32);

    }
    else if (enLayer == VDP_LAYER_WBC_HD1)
    {

        WBC_OFL_EN.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)));
        WBC_OFL_EN.bits.wbc1_ofl_en = u32Data;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)), WBC_OFL_EN.u32);

    }
    else if (enLayer == VDP_LAYER_WBC_DSD)
    {

        WBC_OFL_EN.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)));
        WBC_OFL_EN.bits.wbc2_ofl_en = u32Data;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)), WBC_OFL_EN.u32);

    }


}
#endif

#if 0
//mod me
HI_VOID VDP_WBC_SetDhdOflMode(VDP_LAYER_WBC_E enLayer, HI_U32 u32Data)
{
    U_WBC_OFL_EN WBC_OFL_EN;
    if (enLayer == VDP_LAYER_WBC_HD0)
    {

        WBC_OFL_EN.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)));
        WBC_OFL_EN.bits.wbc0_ofl_pro = u32Data;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_OFL_EN.u32)), WBC_OFL_EN.u32);

    }

}

#endif

//wbc flip
HI_VOID VDP_WBC_SetUVOrder(HI_U32 u32LayerId, HI_U32 u32Enable)
{
    U_WBC_DHD0_CTRL  WBC_DHD0_CTRL;
    if (u32LayerId == VDP_LAYER_WBC_HD0 || u32LayerId == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + u32LayerId * WBC_OFFSET));
        WBC_DHD0_CTRL.bits.uv_order = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_CTRL.u32) + u32LayerId * WBC_OFFSET), WBC_DHD0_CTRL.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_WBC_SetUVOrder() Select a Wrong layer!\n");
    }

    return ;

}

HI_VOID VDP_WBC_SetHorZmeEnable        (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_HPZME  WBC_DHD0_HPZME;
    U_WBC_GP0_HPZME   WBC_GP0_HPZME;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_HPZME.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HPZME.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HPZME.bits.hpzme_en = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HPZME.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HPZME.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        WBC_GP0_HPZME.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_GP0_HPZME.u32)));
        WBC_GP0_HPZME.bits.hpzme_en = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_GP0_HPZME.u32)), WBC_GP0_HPZME.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_WBC_SetHorZmeEnable() select wrong dhd layer id\n");
        return ;
    }

}

HI_VOID VDP_WBC_SetHorZmeMidEnable     (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_HPZME  WBC_DHD0_HPZME;
    U_WBC_GP0_HPZME   WBC_GP0_HPZME;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_HPZME.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HPZME.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HPZME.bits.hpzme_mid_en = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HPZME.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HPZME.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        WBC_GP0_HPZME.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_GP0_HPZME.u32)));
        WBC_GP0_HPZME.bits.hpzme_mid_en = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_GP0_HPZME.u32)), WBC_GP0_HPZME.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_WBC_SetHorZmeMidEnable() select wrong dhd layer id\n");
        return ;
    }
}

HI_VOID VDP_WBC_SetHorZmeFirEnable     (VDP_LAYER_WBC_E enLayer, HI_U32 u32Enable)
{
    U_WBC_DHD0_HPZME  WBC_DHD0_HPZME;
    U_WBC_GP0_HPZME   WBC_GP0_HPZME;

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_HPZME.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_DHD0_HPZME.u32) + enLayer * WBC_OFFSET));
        WBC_DHD0_HPZME.bits.hpzme_mode = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_DHD0_HPZME.u32) + enLayer * WBC_OFFSET), WBC_DHD0_HPZME.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {
        WBC_GP0_HPZME.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->WBC_GP0_HPZME.u32)));
        WBC_GP0_HPZME.bits.hpzme_mode = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->WBC_GP0_HPZME.u32)), WBC_GP0_HPZME.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_WBC_SetHorZmeFirEnable() select wrong dhd layer id\n");
        return ;
    }
}


