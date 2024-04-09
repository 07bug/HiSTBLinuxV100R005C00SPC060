//**********************************************************************
// File Name   : vdp_hal_chn.c
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
#include "vdp_hal_chn.h"


extern volatile S_VDP_REGS_TYPE* pVdpReg;


HI_VOID VDP_DISP_SetUfOffineEn  (HI_U32 u32hd_id, HI_U32 u32UfOfflineEn)
{
    U_DHD0_CTRL DHD0_CTRL;

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.uf_offline_en = u32UfOfflineEn;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_SetDispMode  (HI_U32 u32hd_id, HI_U32 u32DispMode)
{
    U_DHD0_CTRL DHD0_CTRL;

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.disp_mode = u32DispMode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_SetHdmiMode  (HI_U32 u32hd_id, HI_U32 u32hdmi_md)
{
    U_INTF_HDMI_CTRL INTF_HDMI_CTRL;

    INTF_HDMI_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->INTF_HDMI_CTRL.u32)+u32hd_id*CHN_OFFSET));
    INTF_HDMI_CTRL.bits.rgb_mode = (u32hdmi_md != 0) ? 0 : 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->INTF_HDMI_CTRL.u32)+u32hd_id*CHN_OFFSET),INTF_HDMI_CTRL.u32);
}


HI_VOID VDP_DISP_SetHdmi420Enable  (HI_U32 u32hd_id, HI_U32 u32Enable)
{
#if 0
    U_DHD0_CTRL DHD0_CTRL;

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.hdmi420_en = u32Enable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);
#endif
}

HI_VOID VDP_DISP_SetHdmi420CSel  (HI_U32 u32hd_id, HI_U32 u32Csel)
{
#if 0
    U_DHD0_CTRL DHD0_CTRL;

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.hdmi420c_sel = u32Csel;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);
#endif
}

HI_VOID VDP_DISP_SetRegUp (HI_U32 u32hd_id)
{
    U_DHD0_CTRL DHD0_CTRL;

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_SetIntfEnable(HI_U32 u32hd_id, HI_U32 bTrue)
{
    U_DHD0_CTRL DHD0_CTRL;

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    if(u32hd_id == VDP_CHN_DHD1)
        DHD0_CTRL.bits.intf_en = 0;
    else
        DHD0_CTRL.bits.intf_en = bTrue;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);

    VDP_DISP_SetRegUp(u32hd_id);
}

HI_VOID VDP_DISP_SetSplitMode  (HI_U32 u32hd_id, HI_U32 u32SplitMode)
{
	U_DHD0_CTRL1	 DHD0_CTRL1;

	DHD0_CTRL1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL1.u32)));

	if(u32SplitMode == VDP_SPLIT_MODE_4P_1SPLIT)
	{
		DHD0_CTRL1.bits.multichn_en		   = 2;
		DHD0_CTRL1.bits.multichn_split_mode  = 2;
	}
	else if(u32SplitMode == VDP_SPLIT_MODE_4P_4SPLIT)
	{
		DHD0_CTRL1.bits.multichn_en		   = 2;
		DHD0_CTRL1.bits.multichn_split_mode  = 3;
	}
	else if(u32SplitMode == VDP_SPLIT_MODE_4P_2SPLIT)
	{
		DHD0_CTRL1.bits.multichn_en		   = 2;
		DHD0_CTRL1.bits.multichn_split_mode  = 1;
	}
	else if(u32SplitMode == VDP_SPLIT_MODE_2P_1SPLIT)
	{
		DHD0_CTRL1.bits.multichn_en		   = 1;
		DHD0_CTRL1.bits.multichn_split_mode  = 0;
	}
	else if(u32SplitMode == VDP_SPLIT_MODE_2P_2SPLIT)
	{
		DHD0_CTRL1.bits.multichn_en		   = 1;
		DHD0_CTRL1.bits.multichn_split_mode  = 1;
	}
	else if(u32SplitMode == VDP_SPLIT_MODE_2P_ODDEVEN)
	{
		DHD0_CTRL1.bits.multichn_en		   = 1;
		DHD0_CTRL1.bits.multichn_split_mode  = 0;
	}
	else if(u32SplitMode == VDP_SPLIT_MODE_1P_1SPLIT)
	{
		DHD0_CTRL1.bits.multichn_en		   = 0;
		DHD0_CTRL1.bits.multichn_split_mode  = 4;
	}
	if(u32SplitMode == VDP_SPLIT_MODE_4P_2SPLIT)
	{
		DHD0_CTRL1.bits.multichn_en		   = 2;
		DHD0_CTRL1.bits.multichn_split_mode  = 1;
	}

	VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL1.u32)), DHD0_CTRL1.u32);

}

HI_VOID VDP_DISP_SetIntMask  (HI_U32 u32masktypeen)
{
    U_VOINTMSK VOINTMSK;

    /* Dispaly interrupt mask enable */
    VOINTMSK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VOINTMSK.u32)));
    VOINTMSK.u32 = VOINTMSK.u32 | u32masktypeen;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VOINTMSK.u32)), VOINTMSK.u32);

    return ;
}

HI_VOID VDP_DISP_ClearIntMask  (HI_U32 u32masktypeen)
{
    U_VOINTMSK  VOINTMSK;

    /* Dispaly interrupt mask enable */
    VOINTMSK.u32 = u32masktypeen;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VOINTMSK.u32)), VOINTMSK.u32);
    return ;
}

HI_VOID  VDP_DISP_SetIntDisable(HI_U32 u32masktypeen)
{
    U_VOINTMSK VOINTMSK;

    /* Dispaly interrupt mask enable */
    VOINTMSK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VOINTMSK.u32)));
    VOINTMSK.u32 = VOINTMSK.u32 & (~u32masktypeen);
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VOINTMSK.u32), VOINTMSK.u32);

    return ;
}

HI_VOID VDP_DISP_SetOflIntMask  (HI_U32 u32masktypeen)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_DISP_SetOflIntDisable(HI_U32 u32masktypeen)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_DISP_BfmClkSel(HI_U32 u32Num)
{
    U_VODEBUG  VODEBUG ;
    /* Dispaly interrupt mask enable */
    VODEBUG.u32        = VDP_RegRead(((HI_ULONG)&(pVdpReg->VODEBUG.u32)));
    VODEBUG.bits.bfm_clk_sel = u32Num;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VODEBUG.u32), VODEBUG.u32);
    return ;
}

HI_VOID  VDP_DISP_OpenIntf(HI_U32 u32hd_id,VDP_DISP_SYNCINFO_S stSyncInfo)
{
    U_DHD0_CTRL DHD0_CTRL;
    U_DHD0_VSYNC DHD0_VSYNC;
    U_DHD0_VSYNC2 DHD0_VSYNC2;
    U_DHD0_VPLUS DHD0_VPLUS;
    U_DHD0_VPLUS2 DHD0_VPLUS2;
    U_DHD0_PWR DHD0_PWR;
    U_DHD0_HSYNC1 DHD0_HSYNC1;
    U_DHD0_HSYNC2 DHD0_HSYNC2;

    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_OpenIntf Select Wrong CHANNEL ID\n");
        return ;
    }

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.iop   = stSyncInfo.bIop;//
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);


    DHD0_HSYNC1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_HSYNC1.u32)+u32hd_id*CHN_OFFSET));
    DHD0_HSYNC2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_HSYNC2.u32)+u32hd_id*CHN_OFFSET));
    DHD0_HSYNC1.bits.hact = stSyncInfo.u32Hact -1;
    DHD0_HSYNC1.bits.hbb  = stSyncInfo.u32Hbb -1;
    DHD0_HSYNC2.bits.hfb  = stSyncInfo.u32Hfb -1;
    DHD0_HSYNC2.bits.hmid = (stSyncInfo.u32Hmid == 0) ? 0 : stSyncInfo.u32Hmid -1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_HSYNC1.u32)+u32hd_id*CHN_OFFSET), DHD0_HSYNC1.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_HSYNC2.u32)+u32hd_id*CHN_OFFSET), DHD0_HSYNC2.u32);

    //Config VHD interface veritical timming
    DHD0_VSYNC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VSYNC.u32)+u32hd_id*CHN_OFFSET));
    DHD0_VSYNC.bits.vact = stSyncInfo.u32Vact  -1;
    DHD0_VSYNC.bits.vbb = stSyncInfo.u32Vbb - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VSYNC.u32)+u32hd_id*CHN_OFFSET), DHD0_VSYNC.u32);

    DHD0_VSYNC2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VSYNC2.u32)+u32hd_id*CHN_OFFSET));
    DHD0_VSYNC2.bits.vfb =  stSyncInfo.u32Vfb - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VSYNC2.u32)+u32hd_id*CHN_OFFSET), DHD0_VSYNC2.u32);

    //Config VHD interface veritical bottom timming,no use in progressive mode
    DHD0_VPLUS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VPLUS.u32)+u32hd_id*CHN_OFFSET));
    DHD0_VPLUS.bits.bvact = stSyncInfo.u32Bvact - 1;
    DHD0_VPLUS.bits.bvbb =  stSyncInfo.u32Bvbb - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VPLUS.u32)+u32hd_id*CHN_OFFSET), DHD0_VPLUS.u32);

    DHD0_VPLUS2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VPLUS2.u32)+u32hd_id*CHN_OFFSET));
    DHD0_VPLUS2.bits.bvfb =  stSyncInfo.u32Bvfb - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VPLUS2.u32)+u32hd_id*CHN_OFFSET), DHD0_VPLUS2.u32);

    //Config VHD interface veritical bottom timming,
    DHD0_PWR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_PWR.u32)+u32hd_id*CHN_OFFSET));
    DHD0_PWR.bits.hpw = stSyncInfo.u32Hpw - 1;
    DHD0_PWR.bits.vpw = stSyncInfo.u32Vpw - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_PWR.u32)+u32hd_id*CHN_OFFSET), DHD0_PWR.u32);
}

HI_VOID  VDP_DISP_OpenTypIntf(HI_U32 u32hd_id, VDP_DISP_DIGFMT_E enDigFmt)
{
    VDP_DISP_SYNCINFO_S  stSyncInfo;


    switch(enDigFmt)
    {
        case VDP_DISP_DIGFMT_PAL:
        {

            stSyncInfo.bIop     = 0;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 288;
            stSyncInfo.u32Vfb   = 2;
            stSyncInfo.u32Vbb   = 22;

            stSyncInfo.u32Hact  = 720;
            stSyncInfo.u32Hfb   = 12;
            stSyncInfo.u32Hbb   = 132;

            stSyncInfo.u32Bvact = 288;
            stSyncInfo.u32Bvfb  = 2;
#if EDA_TEST
            stSyncInfo.u32Bvbb  = 22;
#else
            stSyncInfo.u32Bvbb  = 23;
#endif

            stSyncInfo.u32Hpw   = 63;
            stSyncInfo.u32Vpw   = 3;

            stSyncInfo.u32Hmid  = 300;//YPbPr可能要求为0;

            break;

        }
        case VDP_DISP_DIGFMT_NTSC:
        {

            stSyncInfo.bIop     = 0;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 240;
            stSyncInfo.u32Vfb   = 4;
            stSyncInfo.u32Vbb   = 18;

            stSyncInfo.u32Hact  = 720;
            stSyncInfo.u32Hfb   = 18;
            stSyncInfo.u32Hbb   = 120;

            stSyncInfo.u32Bvact = 240;
            stSyncInfo.u32Bvfb  = 4;
#if EDA_TEST
            stSyncInfo.u32Bvbb  = 18;
#else
            stSyncInfo.u32Bvbb  = 19;
#endif

            stSyncInfo.u32Hpw   = 62;
            stSyncInfo.u32Vpw   = 3;

            stSyncInfo.u32Hmid  = 310;//YPbPr可能要求为0;

            break;

        }
        case VDP_DISP_DIGFMT_1080P50:
        {
            //1080p@25Hz SMPTE 274M
            //1080p@50Hz SMPTE 274M
#if 1
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 1080;//H_1080P;
            stSyncInfo.u32Vfb   = 4;
            stSyncInfo.u32Vbb   = 41;

            stSyncInfo.u32Hact  = 1920;//W_1080P;
            stSyncInfo.u32Hfb   = 528;
            stSyncInfo.u32Hbb   = 192;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 5;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Hmid  = 0;
#else

            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = H_1080P;
            stSyncInfo.u32Vfb   = 10;
            stSyncInfo.u32Vbb   = 160;

            stSyncInfo.u32Hact  = W_1080P;
            stSyncInfo.u32Hfb   = 147;
            stSyncInfo.u32Hbb   = 309;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 5;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Hmid  = 0;

#endif
            break;


        }

        case VDP_DISP_DIGFMT_1080P_24_FP:
        {
            //1080p@25Hz SMPTE 274M
            //1080p@50Hz SMPTE 274M

            stSyncInfo.bIop = 1;
            //stSyncInfo.u32Intfb = 1;
            //stSyncInfo.bSynm = 0;

            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Vact = 1080;
            stSyncInfo.u32Vfb  = 4;
            stSyncInfo.u32Vbb  = 41;

            stSyncInfo.u32Hact = 1920;
            stSyncInfo.u32Hfb  = 638;
            stSyncInfo.u32Hbb  = 192;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw = 44;
            stSyncInfo.u32Vpw = 5;

            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Hmid = 1;
            //stIntfFmt = VDP_DISP_INTFDATAFMT_YCBCR422;

            //Vou_SetIntfDigSel(VDP_DIGSEL_YCMUX_EMB);

            break;

        }
        case VDP_DISP_DIGFMT_1080P60:
        {
            //1080p@25Hz SMPTE 274M
            //1080p@50Hz SMPTE 274M

            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 1080;//H_1080P;
            stSyncInfo.u32Vfb   = 4;
            stSyncInfo.u32Vbb   = 41;

            stSyncInfo.u32Hact  = 1920;//W_1080P;
            stSyncInfo.u32Hfb   = 88;
            stSyncInfo.u32Hbb   = 192;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 5;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        case VDP_DISP_DIGFMT_1080P30:
        {
            //1080p@25Hz SMPTE 274M
            //1080p@50Hz SMPTE 274M

            stSyncInfo.bIop = 1;

            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Vact = 1080;
            stSyncInfo.u32Vfb  = 4;
            stSyncInfo.u32Vbb  = 41;

            stSyncInfo.u32Hact = 1920;
            stSyncInfo.u32Hfb  = 88;
            stSyncInfo.u32Hbb  = 192;
            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw = 0x0;
            stSyncInfo.u32Vpw = 0x0;
            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Hmid = 0x0;
            break;
        }

        case VDP_DISP_DIGFMT_1080P_25:
        {
            /* |--INTFACE---||-----TOP-----||----HORIZON--------||----BOTTOM-----||-PULSE-||-INVERSE-| */
            /* Synm Iop Itf Vact Vbb Vfb Hact Hbb Hfb Bvact Bvbb Bvfb Hpw Vpw Hmid bIdv bIhs bIvs */
            // 3 HI_UNF_ENC_FMT_1080P_25,
            //{1, 1, 2, 1080, 41, 4, 1920, 192, 528, /*1,*/ 1, 1, 1, 44, 5, 0, 0, 0}, /* 1080P@25Hz */
            printk("@@@@@@@@@ VDP_DISP_DIGFMT_1080P_25 !!\n");
            //1080p@25Hz SMPTE 274M
            //1080p@50Hz SMPTE 274M
            stSyncInfo.bIop = 1;
            stSyncInfo.u32Intfb = 2;
            stSyncInfo.bSynm = 1;

            stSyncInfo.u32Vact = 1080;
            stSyncInfo.u32Vfb = 4;
            stSyncInfo.u32Vbb = 41;

            stSyncInfo.u32Hact = 1920;
            stSyncInfo.u32Hfb = 528;
            stSyncInfo.u32Hbb = 192;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb = 0;
            stSyncInfo.u32Bvbb = 0;

            stSyncInfo.u32Hpw = 44;
            stSyncInfo.u32Vpw = 5;

            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Hmid = 0;

            break;

        }

        case VDP_DISP_DIGFMT_1080P_24:
        {

            /* |--INTFACE---||-----TOP-----||----HORIZON--------||----BOTTOM-----||-PULSE-||-INVERSE-| */
            /* Synm Iop  Itf  Vact Vbb Vfb	 Hact  Hbb Hfb		Bvact Bvbb Bvfb  Hpw Vpw Hmid bIdv bIhs bIvs */
            //{ {1,	1,	 2,  1080,	41,  4,  1920, 192, 638,	   1,	1,	1,	  44, 5, 1, 0,	0,	0}, /* 1080P@24Hz */
            printk("@@@@@@@@@  VDP_DISP_DIGFMT_1080P_24 !!\n");
            //1080p@25Hz SMPTE 274M
            //1080p@50Hz SMPTE 274M
            stSyncInfo.bIop = 1;
            stSyncInfo.u32Intfb = 2;
            stSyncInfo.bSynm = 1;

            stSyncInfo.u32Vact = 1080;
            stSyncInfo.u32Vfb  = 4;
            stSyncInfo.u32Vbb  = 41;

            stSyncInfo.u32Hact = 1920;
            stSyncInfo.u32Hfb  = 638;
            stSyncInfo.u32Hbb  = 192;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb	= 0;
            stSyncInfo.u32Bvbb	= 0;

            stSyncInfo.u32Hpw = 44;
            stSyncInfo.u32Vpw = 5;

            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Hmid = 0;

            break;

        }

        case VDP_DISP_DIGFMT_1080I50:
        {

            stSyncInfo.bIop     = 0;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 1080 / 2;
            stSyncInfo.u32Vfb   = 2;
            stSyncInfo.u32Vbb   = 20;

            stSyncInfo.u32Hact  = 1920;
            stSyncInfo.u32Hfb   = 528;
            stSyncInfo.u32Hbb   = 192;

            stSyncInfo.u32Bvact = 1080 / 2;
            stSyncInfo.u32Bvfb  = 2;
#if EDA_TEST
            stSyncInfo.u32Bvbb  = 20;
#else
            stSyncInfo.u32Bvbb  = 21;
#endif

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 5;

            stSyncInfo.u32Hmid  = 1128;

            break;

        }
        case VDP_DISP_DIGFMT_1080I60:
        {

            stSyncInfo.bIop     = 0;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 540;//H_1080P/2;
            stSyncInfo.u32Vfb   = 2;
            stSyncInfo.u32Vbb   = 20;

            stSyncInfo.u32Hact  = 1920;//W_1080P;
            stSyncInfo.u32Hfb   = 88;
            stSyncInfo.u32Hbb   = 192;

            stSyncInfo.u32Bvact = 540;//H_1080P/2;
            stSyncInfo.u32Bvfb  = 2;
            stSyncInfo.u32Bvbb  = 20;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 5;

            stSyncInfo.u32Hmid  = 908;

            break;

        }
        case VDP_DISP_DIGFMT_720P50:
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 720;//H_720P;
            stSyncInfo.u32Vfb   = 5;
            stSyncInfo.u32Vbb   = 25;

            stSyncInfo.u32Hact  = 1280;//W_720P;
            stSyncInfo.u32Hfb   = 440;
            stSyncInfo.u32Hbb   = 260;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 40;
            stSyncInfo.u32Vpw   = 5;

            stSyncInfo.u32Hmid  = 0;

            break;
        }
         case VDP_DISP_DIGFMT_720P60:
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 720;//H_720P;
            stSyncInfo.u32Vfb   = 5;
            stSyncInfo.u32Vbb   = 25;

            stSyncInfo.u32Hact  = 1280;//W_720P;
            stSyncInfo.u32Hfb   = 110;
            stSyncInfo.u32Hbb   = 260;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 40;
            stSyncInfo.u32Vpw   = 5;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        case VDP_DISP_DIGFMT_800x600:
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 600;
            stSyncInfo.u32Vfb   = 1;
            stSyncInfo.u32Vbb   = 27;

            stSyncInfo.u32Hact  = 800;
            stSyncInfo.u32Hfb   = 40;
            stSyncInfo.u32Hbb   = 216;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 0x0;
            stSyncInfo.u32Vpw   = 0x0;

            stSyncInfo.u32Hmid  = 0x0;

            break;

        }
        case VDP_DISP_DIGFMT_576P:
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 576;
            stSyncInfo.u32Vfb   = 5;
            stSyncInfo.u32Vbb   = 44;

            stSyncInfo.u32Hact  = 720;
            stSyncInfo.u32Hfb   = 12;
            stSyncInfo.u32Hbb   = 132;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 64;
            stSyncInfo.u32Vpw   = 5;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        case VDP_DISP_DIGFMT_576I:
        {

            stSyncInfo.bIop     = 0;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 288;//H_576P/2;
            stSyncInfo.u32Vfb   = 2;
            stSyncInfo.u32Vbb   = 22;

            stSyncInfo.u32Hact  = 720;//W_576P;
            stSyncInfo.u32Hfb   = 12;
            stSyncInfo.u32Hbb   = 132;

            stSyncInfo.u32Bvact = 288;//H_576P/2;
            stSyncInfo.u32Bvfb  = 2;
#if EDA_TEST
            stSyncInfo.u32Bvbb  = 22;
#else
            stSyncInfo.u32Bvbb  = 23;
#endif

            stSyncInfo.u32Hpw   = 63;
            stSyncInfo.u32Vpw   = 3;

            stSyncInfo.u32Hmid  = 600;

            break;

        }
        case VDP_DISP_DIGFMT_480P://@60
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 480;
            stSyncInfo.u32Vfb   = 9;
            stSyncInfo.u32Vbb   = 36;

            stSyncInfo.u32Hact  = 720;
            stSyncInfo.u32Hfb   = 16;
            stSyncInfo.u32Hbb   = 122;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 62;
            stSyncInfo.u32Vpw   = 6;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        case VDP_DISP_DIGFMT_480I:
        {

            stSyncInfo.bIop     = 0;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 240;//H_D1/2;
            stSyncInfo.u32Vfb   = 4;
            stSyncInfo.u32Vbb   = 18;

            stSyncInfo.u32Hact  = 720;//W_D1;
            stSyncInfo.u32Hfb   = 20;
            stSyncInfo.u32Hbb   = 118;

            stSyncInfo.u32Bvact = 240;//H_D1/2;
            stSyncInfo.u32Bvfb  = 4;
#if EDA_TEST
            stSyncInfo.u32Bvbb  = 18;
#else
            stSyncInfo.u32Bvbb  = 19;
#endif

            stSyncInfo.u32Hpw   = 62;
            stSyncInfo.u32Vpw   = 3;

            stSyncInfo.u32Hmid  = 620;

            break;

        }
        case VDP_DISP_DIGFMT_1600P60:
        {
            stSyncInfo.bSynm    = 1;
            stSyncInfo.bIop     = 1;
            stSyncInfo.u32Intfb = 2;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 1600;//H_1600P;
            stSyncInfo.u32Vfb   = 3;
            stSyncInfo.u32Vbb   = 37;

            stSyncInfo.u32Hact  = 2560;//W_1600P;
            stSyncInfo.u32Hfb   = 80;
            stSyncInfo.u32Hbb   = 48;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 32;
            stSyncInfo.u32Vpw   = 6;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        case VDP_DISP_DIGFMT_2160P60:
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 2160;//H_2160P;
            stSyncInfo.u32Vfb   = 4 * 2;
            stSyncInfo.u32Vbb   = 41 * 2;

            stSyncInfo.u32Hact  = 3840;//W_2160P;
            stSyncInfo.u32Hfb   = 88 * 2;
            stSyncInfo.u32Hbb   = 192 * 2;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 8;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        case VDP_DISP_DIGFMT_2160P50:
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 2160;//H_2160P;
            stSyncInfo.u32Vfb   = 4 * 2;
            stSyncInfo.u32Vbb   = 41 * 2;

            stSyncInfo.u32Hact  = 3840;//W_2160P;
            stSyncInfo.u32Hfb   = 88 * 2 * 6;
            stSyncInfo.u32Hbb   = 192 * 2;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 8;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        case VDP_DISP_DIGFMT_2160P30:
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 2160;//H_2160P;
            stSyncInfo.u32Vfb   = 4 * 2;
            stSyncInfo.u32Vbb   = 41 * 2;

            stSyncInfo.u32Hact  = 3840;//W_2160P;
            stSyncInfo.u32Hfb   = 88 * 2;
            stSyncInfo.u32Hbb   = 192 * 2;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 8;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Hmid  = 0;

            break;

        }

        case VDP_DISP_DIGFMT_4096x2160P24:
        {
            stSyncInfo.bIop 	= 1;
            stSyncInfo.bIdv 	= 0;
            stSyncInfo.bIhs 	= 0;
            stSyncInfo.bIvs 	= 0;
            stSyncInfo.u32Vact	= 2160;
            stSyncInfo.u32Vfb	= 4 * 2;
            stSyncInfo.u32Vbb	= 82;//还有问题，需要确认?????
            stSyncInfo.u32Hact	= 4096;
            stSyncInfo.u32Hfb	= 1020;//对这个参数很敏感
            stSyncInfo.u32Hbb	= 384;//还有问题，需要确认??????
            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb	= 0;
            stSyncInfo.u32Bvbb	= 0;
            stSyncInfo.u32Hpw	= 88;
            stSyncInfo.u32Vpw	= 10;
            stSyncInfo.bIdv 	= 0;
            stSyncInfo.bIhs 	= 0;
            stSyncInfo.bIvs 	= 0;
            stSyncInfo.u32Hmid	= 0;
            break;
        }

        case VDP_DISP_DIGFMT_4096x2160P30:
        case VDP_DISP_DIGFMT_4096x2160_30HZ :
        {
            stSyncInfo.bIop     = 1;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;
            stSyncInfo.u32Vact  = 2160;
            stSyncInfo.u32Vfb   = 4 * 2;
            stSyncInfo.u32Vbb   = 56;//41*2;
            stSyncInfo.u32Hact  = 4096;
            stSyncInfo.u32Hfb   = 176;//对这个参数很敏感
            stSyncInfo.u32Hbb   = 180;//如果有问题就是这个参数不对
            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;
            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 8;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;
            stSyncInfo.u32Hmid  = 0;
            break;
        }
        case VDP_DISP_DIGFMT_4096x2160_50HZ :
        {
            stSyncInfo.bIop     = 1;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;
            stSyncInfo.u32Vact  = 2160;
            stSyncInfo.u32Vfb   = 8;
            stSyncInfo.u32Vbb   = 82;//41*2;
            stSyncInfo.u32Hact  = 4096;
            stSyncInfo.u32Hfb   = 968;//对这个参数很敏感
            stSyncInfo.u32Hbb   = 216;//如果有问题就是这个参数不对
            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;
            stSyncInfo.u32Hpw   = 88;
            stSyncInfo.u32Vpw   = 10;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;
            stSyncInfo.u32Hmid  = 1;
            break;
        }

        case VDP_DISP_DIGFMT_4096x2160P60:
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 2160;//H_2160P;
            stSyncInfo.u32Vfb   = 4 * 2;
            stSyncInfo.u32Vbb   = 41 * 2;

            stSyncInfo.u32Hact  = 4096;//W_4096;
            stSyncInfo.u32Hfb   = 100;
            stSyncInfo.u32Hbb   = 204;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 8;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        case VDP_DISP_DIGFMT_2160P120:
        {
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 1080;//H_2160P/2;
            stSyncInfo.u32Vfb   = 4;
            stSyncInfo.u32Vbb   = 41;

            stSyncInfo.u32Hact  = 3840;//W_2160P;
            stSyncInfo.u32Hfb   = 88 * 2;
            stSyncInfo.u32Hbb   = 192 * 2;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 8;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        case VDP_DISP_DIGFMT_TESTI:
        {
            VDP_PRINT("Now is TestMode I\n");

            stSyncInfo.bIop = 0;
            //stSyncInfo.u32Intfb = 1;
            //stSyncInfo.bSynm = 0;

            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Vact = 64;
            stSyncInfo.u32Vfb  = 6;
            stSyncInfo.u32Vbb  = 5;

            stSyncInfo.u32Hact = 720;
            stSyncInfo.u32Hfb  = 20;
            stSyncInfo.u32Hbb  = 10;

            stSyncInfo.u32Bvact = 64;
            stSyncInfo.u32Bvfb  = 6;
            stSyncInfo.u32Bvbb  = 5;

            stSyncInfo.u32Hpw = 0x0;
            stSyncInfo.u32Vpw = 0x0;

            stSyncInfo.u32Hmid = 0x0;
            //stIntfFmt = VDP_DISP_INTFDATAFMT_YCBCR422;

            //Vou_SetIntfDigSel(VDP_DIGSEL_YCMUX_EMB);

            break;

        }
        case VDP_DISP_DIGFMT_TESTP:
        {
            VDP_PRINT("Now is TestMode P\n");

            stSyncInfo.bIop = 1;
            //1stSyncInfo.u32Intfb = 2;
            //1stSyncInfo.bSynm = 0;

            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Vact = 128;
            stSyncInfo.u32Vfb  = 10;
            stSyncInfo.u32Vbb  = 10;

            stSyncInfo.u32Hact = 720;
            stSyncInfo.u32Hfb  = 16;
            stSyncInfo.u32Hbb  = 16;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw = 0x0;
            stSyncInfo.u32Vpw = 0x0;

            stSyncInfo.u32Hmid = 0x0;
            //stIntfFmt = VDP_DISP_INTFDATAFMT_YCBCR444;

            //Vou_SetIntfDigSel(VDP_DIGSEL_YCBCR_EMB);

            break;

        }
        case VDP_DISP_DIGFMT_TESTS:
        {
            VDP_PRINT("Now is TestMode S\n");

            stSyncInfo.bIop = 0;

            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Vact = 64;
            stSyncInfo.u32Vfb  = 6;
            stSyncInfo.u32Vbb  = 2;

            stSyncInfo.u32Hact = 720;
            stSyncInfo.u32Hfb  = 20;
            stSyncInfo.u32Hbb  = 10;

            stSyncInfo.u32Bvact = 64;
            stSyncInfo.u32Bvfb  = 6;
            stSyncInfo.u32Bvbb  = 2;

            stSyncInfo.u32Hpw = 0x0;
            stSyncInfo.u32Vpw = 0x0;

            stSyncInfo.u32Hmid = 0x0;

            break;

        }
        case VDP_DISP_DIGFMT_TESTUT:
        {
            VDP_PRINT("Now is TestMode UT\n");

            stSyncInfo.bIop = 1;

            stSyncInfo.bIdv = 0;
            stSyncInfo.bIhs = 0;
            stSyncInfo.bIvs = 0;

            stSyncInfo.u32Vact = 2048;
            stSyncInfo.u32Vfb  = 1;
            stSyncInfo.u32Vbb  = 1;

            stSyncInfo.u32Hact = 64;
            stSyncInfo.u32Hfb  = 8;
            stSyncInfo.u32Hbb  = 8;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw = 0x0;
            stSyncInfo.u32Vpw = 0x0;

            stSyncInfo.u32Hmid = 0x0;

            break;

        }
        case VDP_DISP_DIGFMT_2160P60_HBI:
        {
            VDP_PRINT("VDP_DISP_DIGFMT_2160P60_HBI\n");
            stSyncInfo.bIop     = 1;

            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Vact  = 2160;//H_2160P;
            stSyncInfo.u32Vfb   = 4 * 2;
            stSyncInfo.u32Vbb   = 41 * 2;

            stSyncInfo.u32Hact  = 3840;//W_2160P;
            stSyncInfo.u32Hfb   = 260 * 2;
            stSyncInfo.u32Hbb   = 40 * 2;

            stSyncInfo.u32Bvact = 0;
            stSyncInfo.u32Bvfb  = 0;
            stSyncInfo.u32Bvbb  = 0;

            stSyncInfo.u32Hpw   = 44;
            stSyncInfo.u32Vpw   = 8;
            stSyncInfo.bIdv     = 0;
            stSyncInfo.bIhs     = 0;
            stSyncInfo.bIvs     = 0;

            stSyncInfo.u32Hmid  = 0;

            break;

        }
        default:
        {
            VDP_PRINT("Error,VDP_DISP_OpenIntf() Wrong Default DIG FMT mode\n");
            return ;
        }
    }

    if(stSyncInfo.u32Hact <= 0)
    {
        stSyncInfo.u32Hact = 1;
    }
    if(stSyncInfo.u32Hbb <=0)
    {
        stSyncInfo.u32Hbb = 1;
    }
    if(stSyncInfo.u32Hfb <=0)
    {
        stSyncInfo.u32Hfb = 1;
    }

    if(stSyncInfo.u32Vact <= 0)
    {
        stSyncInfo.u32Vact = 1;
    }
    if(stSyncInfo.u32Vbb <=0)
    {
        stSyncInfo.u32Vbb = 1;
    }
    if(stSyncInfo.u32Vfb <=0)
    {
        stSyncInfo.u32Vfb = 1;
    }

    if(stSyncInfo.u32Bvact <= 0)
    {
        stSyncInfo.u32Bvact = 1;
    }
    if(stSyncInfo.u32Bvbb <=0)
    {
        stSyncInfo.u32Bvbb = 1;
    }
    if(stSyncInfo.u32Bvfb <=0)
    {
        stSyncInfo.u32Bvfb = 1;
    }

    if(stSyncInfo.u32Hpw <=0)
    {
        stSyncInfo.u32Hpw = 1;
    }
    if(stSyncInfo.u32Vpw <=0)
    {
        stSyncInfo.u32Vpw = 1;
    }

    // VDP_DISP_SetVSync(enChan,stSyncInfo);
    // VDP_DISP_SetHSync(enChan,stSyncInfo);
    // VDP_DISP_SetPlusWidth(enChan,stSyncInfo);
    // VDP_DISP_SetPlusPhase(enChan,stSyncInfo);
    // VDP_DISP_SetOutFmt(enChan,stIntfFmt);
    // VDP_DISP_SetVTThdMode(enChan, bool(!(stSyncInfo.bIop)));
    // VDP_DISP_SetIntfMode(enChan,stSyncInfo);
    VDP_DISP_OpenIntf(u32hd_id,stSyncInfo);

    return ;

}

HI_VOID VDP_DISP_SetSyncInv(HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, VDP_DISP_SYNCINV_S enInv)
{
    U_INTF_HDMI_SYNC_INV INTF_HDMI_SYNC_INV;
    U_INTF_DATE_SYNC_INV INTF_DATE_SYNC_INV;

    switch(enIntf)
    {
        case VDP_DISP_INTF_HDDATE:
        case VDP_DISP_INTF_SDDATE:
        {
            INTF_DATE_SYNC_INV.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->INTF_DATE_SYNC_INV.u32)+0*CHN_OFFSET));
            INTF_DATE_SYNC_INV.bits.f_inv  = enInv.u32FdInv;
            INTF_DATE_SYNC_INV.bits.vs_inv = enInv.u32VsInv;
            INTF_DATE_SYNC_INV.bits.hs_inv = enInv.u32HsInv;
            INTF_DATE_SYNC_INV.bits.dv_inv = enInv.u32DvInv;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->INTF_DATE_SYNC_INV.u32)+0*CHN_OFFSET),INTF_DATE_SYNC_INV.u32);

            break;
        }
        case VDP_DISP_INTF_HDMI:
        {
            INTF_HDMI_SYNC_INV.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->INTF_HDMI_SYNC_INV.u32)+0*CHN_OFFSET));
            INTF_HDMI_SYNC_INV.bits.vs_inv = enInv.u32VsInv;
            INTF_HDMI_SYNC_INV.bits.hs_inv = enInv.u32HsInv;
            INTF_HDMI_SYNC_INV.bits.dv_inv = enInv.u32DvInv;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->INTF_HDMI_SYNC_INV.u32)+0*CHN_OFFSET),INTF_HDMI_SYNC_INV.u32);

            break;
        }
        case VDP_DISP_INTF_VGA:
        {
            DISP_INFO("98mv310 Nousing!\n");
            break;
        }
        case VDP_DISP_INTF_LCD:
        {
            DISP_INFO("98mv310 Nousing!\n");
            break;
        }
        default:
        {
            VDP_PRINT("Error! DP_DISP_SetSyncInv Wrong Select\n");
            return ;
        }
    }
    return ;
}

HI_VOID  VDP_DISP_SetIntfMuxSel(HI_U32 u32hd_id,VDP_DISP_INTF_E enIntf)
{
    U_VO_MUX VO_MUX;


    switch(enIntf)
    {
#if INTF_EN
        case VDP_DISP_INTF_LCD:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.digital_sel = 2;
            VO_MUX.bits.lcd_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG)&(pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        case VDP_DISP_INTF_BT1120:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.bt1120_sel = u32hd_id;
            VO_MUX.bits.digital_sel = 0;
            VDP_RegWrite((HI_ULONG)&(pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
#else
        case VDP_DISP_INTF_LCD:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.digital_sel = u32hd_id*2;
            VDP_RegWrite((HI_ULONG)&(pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        case VDP_DISP_INTF_BT1120:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.digital_sel = 1+u32hd_id*2;
            VDP_RegWrite((HI_ULONG)&(pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
#endif
        case VDP_DISP_INTF_HDMI:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.hdmi_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG)&(pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        case VDP_DISP_INTF_VGA:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.vga_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG)&(pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        case VDP_DISP_INTF_HDDATE:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.hddate_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG)&(pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
		case VDP_DISP_INTF_SDDATE:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.sddate_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG)&(pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        default:
        {
            VDP_PRINT("Error! VDP_DISP_SetIntfMuxSel Wrong Select\n");
            return ;
        }
    }
    return ;
}

HI_U32 VDP_DISP_GetIntSta(HI_U32 u32intmask)
{
    U_VOINTSTA VOINTSTA;

    /* read interrupt status */
    VOINTSTA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VOINTSTA.u32)));

    return (VOINTSTA.u32 & u32intmask);
}



HI_VOID  VDP_DISP_ClearIntSta(HI_U32 u32intmask )
{
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VOMSKINTSTA.u32), u32intmask);
}

HI_U32 VDP_DISP_GetOflIntSta(HI_U32 u32intmask)
{
    DISP_INFO("98mv310 Nousing!\n");
    return HI_SUCCESS;
}

HI_VOID VDP_DISP_SetVtThdMode(HI_U32 u32hd_id, HI_U32 u32uthdnum, HI_U32 u32mode)
{
    U_DHD0_VTTHD3 DHD0_VTTHD3;
    U_DHD0_VTTHD  DHD0_VTTHD;
    U_DHD0_VTTHD5 DHD0_VTTHD5;

    if(u32uthdnum == 1)//threshold 1 int mode
    {
        DHD0_VTTHD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD.bits.thd1_mode = u32mode;// frame or field
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD.u32);
    }
    else if(u32uthdnum == 2)//threshold 2 int mode
    {
        DHD0_VTTHD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD.bits.thd2_mode = u32mode;// frame or field
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD.u32);
    }
    else if(u32uthdnum == 3)//threshold 3 int mode
    {
        DHD0_VTTHD3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD3.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD3.bits.thd3_mode = u32mode;// frame or field
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD3.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD3.u32);
    }
    else if(u32uthdnum == 4)//threshold 3 int mode
    {
        DHD0_VTTHD3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD3.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD3.bits.thd4_mode = u32mode;// frame or field
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD3.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD3.u32);
    }
    else if(u32uthdnum == 5)//threshold 3 int mode
    {
        DHD0_VTTHD5.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD5.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD5.bits.thd5_mode = u32mode;// frame or field
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD5.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD5.u32);
    }
    else if(u32uthdnum == 6)//threshold 3 int mode
    {
        DHD0_VTTHD5.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD5.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD5.bits.thd6_mode = u32mode;// frame or field
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD5.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD5.u32);
    }
}

HI_VOID VDP_DISP_SetVtThd(HI_U32 u32hd_id, HI_U32 u32uthdnum, HI_U32 u32vtthd)
{

    U_DHD0_VTTHD DHD0_VTTHD;
    U_DHD0_VTTHD3 DHD0_VTTHD3;
    U_DHD0_VTTHD5 DHD0_VTTHD5;

    if(u32uthdnum == 1)
    {
        DHD0_VTTHD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD.bits.vtmgthd1 = u32vtthd;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD.u32);
    }
    else if(u32uthdnum == 2)
    {
        DHD0_VTTHD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD.bits.vtmgthd2 = u32vtthd;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD.u32);
    }
    else if(u32uthdnum== 3)
    {
        DHD0_VTTHD3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD3.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD3.bits.vtmgthd3 = u32vtthd;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD3.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD3.u32);
    }
    else if(u32uthdnum== 4)
    {
        DHD0_VTTHD3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD3.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD3.bits.vtmgthd4 = u32vtthd;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD3.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD3.u32);
    }
    else if(u32uthdnum== 5)
    {
        DHD0_VTTHD5.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD5.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD5.bits.vtmgthd5 = u32vtthd;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD5.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD5.u32);
    }
    else if(u32uthdnum== 6)
    {
        DHD0_VTTHD5.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_VTTHD5.u32)+u32hd_id*CHN_OFFSET));
        DHD0_VTTHD5.bits.vtmgthd6 = u32vtthd;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_VTTHD5.u32)+u32hd_id*CHN_OFFSET), DHD0_VTTHD5.u32);
    }
}

HI_VOID VDP_DISP_SetCbarEnable(HI_U32 u32hd_id,HI_U32 bTrue)
{
    U_DHD0_CTRL DHD0_CTRL;

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.cbar_en = bTrue;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_SetCbarSel(HI_U32 u32hd_id,HI_U32 u32_cbar_sel)
{
    U_DHD0_CTRL DHD0_CTRL;

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.cbar_sel = u32_cbar_sel;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_SetDitherEnable(HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, HI_U32 u32Enable)
{
    DISP_INFO("98mv310 Nousing!\n");
}


HI_VOID VDP_DISP_SetDitherRoundEnable(HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, HI_U32 u32Enable)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_DISP_SetDitherMode  (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, VDP_DITHER_E enDitherMode)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_DISP_SetDitherCoef  (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, VDP_DITHER_COEF_S dither_coef)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID  VDP_DISP_SetClipEnable  (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf)
{
    VDP_PRINT("98mv310 Nousing!\n");
}

HI_VOID  VDP_DISP_SetClipCoef (HI_U32 u32hd_id, VDP_DISP_INTF_E clipsel, VDP_DISP_CLIP_S stClipData)
{
#if 1
    U_INTF_HDMI_CLIP_L     INTF_HDMI_CLIP_L ;
    U_INTF_HDMI_CLIP_H     INTF_HDMI_CLIP_H ;
    U_DATE_CLIP0_L         DATE_CLIP0_L     ;
    U_DATE_CLIP0_H         DATE_CLIP0_H     ;

    if(clipsel == VDP_DISP_INTF_HDMI)
    {
        INTF_HDMI_CLIP_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->INTF_HDMI_CLIP_L.u32)+u32hd_id*CHN_OFFSET));
        INTF_HDMI_CLIP_L.bits.hdmi_clip_en  = stClipData.bClipEn;
        INTF_HDMI_CLIP_L.bits.hdmi_cl2 = stClipData.u32ClipLow_y;
        INTF_HDMI_CLIP_L.bits.hdmi_cl1 = stClipData.u32ClipLow_cb;
        INTF_HDMI_CLIP_L.bits.hdmi_cl0 = stClipData.u32ClipLow_cr;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->INTF_HDMI_CLIP_L.u32)+u32hd_id*CHN_OFFSET), INTF_HDMI_CLIP_L.u32);

        INTF_HDMI_CLIP_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->INTF_HDMI_CLIP_H.u32)+u32hd_id*CHN_OFFSET));
        INTF_HDMI_CLIP_H.bits.hdmi_ch2 = stClipData.u32ClipHigh_y;
        INTF_HDMI_CLIP_H.bits.hdmi_ch1 = stClipData.u32ClipHigh_cb;
        INTF_HDMI_CLIP_H.bits.hdmi_ch0 = stClipData.u32ClipHigh_cr;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->INTF_HDMI_CLIP_H.u32)+u32hd_id*CHN_OFFSET), INTF_HDMI_CLIP_H.u32);
    }

    //DATE
    else if(clipsel == VDP_DISP_INTF_SDDATE)
    {

        DATE_CLIP0_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DATE_CLIP0_L.u32)+u32hd_id*CHN_OFFSET));
        DATE_CLIP0_L.bits.clip_en  = stClipData.bClipEn;
        DATE_CLIP0_L.bits.clip_cl2 = stClipData.u32ClipLow_y;
        DATE_CLIP0_L.bits.clip_cl1 = stClipData.u32ClipLow_cb;
        DATE_CLIP0_L.bits.clip_cl0 = stClipData.u32ClipLow_cr;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DATE_CLIP0_L.u32)+u32hd_id*CHN_OFFSET), DATE_CLIP0_L.u32);

        DATE_CLIP0_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DATE_CLIP0_H.u32)+u32hd_id*CHN_OFFSET));
        DATE_CLIP0_H.bits.clip_ch2 = stClipData.u32ClipHigh_y;
        DATE_CLIP0_H.bits.clip_ch1 = stClipData.u32ClipHigh_cb;
        DATE_CLIP0_H.bits.clip_ch0 = stClipData.u32ClipHigh_cr;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->DATE_CLIP0_H.u32)+u32hd_id*CHN_OFFSET), DATE_CLIP0_H.u32);
    }
#endif
}

HI_VOID  VDP_DISP_SetCscEnable  (HI_U32 u32hd_id, HI_U32 enCSC)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID   VDP_DISP_SetCscDcCoef(HI_U32 u32hd_id,VDP_CSC_DC_COEF_S stCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID   VDP_DISP_SetCscCoef(HI_U32 u32hd_id,VDP_CSC_COEF_S stCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");

}

HI_VOID VDP_DISP_SetCscMode(HI_U32 u32hd_id, VDP_CSC_MODE_E enCscMode)
{
    DISP_INFO("98mv310 Nousing!\n");

    return ;
}

HI_VOID VDP_DISP_SetGammaEnable(HI_U32 u32hd_id, HI_U32 u32GmmEn)
{
    U_DHD0_CTRL DHD0_CTRL;

    //Set Vou Dhd Channel Gamma Correct Enable
    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.gmm_en = u32GmmEn;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET), DHD0_CTRL.u32);
}
HI_VOID VDP_DISP_SetMirrorEnable(HI_U32 u32hd_id, HI_U32 u32MirrEn)
{
    U_DHD0_CTRL DHD0_CTRL;

    //Set Vou Dhd Channel Gamma Correct Enable
    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.mirror_en = 0;//u32MirrEn;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET), DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_SetGammaAddr(HI_U32 u32hd_id, HI_U32 uGmmAddr)
{
    DISP_INFO("98mv310 Nousing!\n");

}

HI_VOID  VDP_DISP_SetParaUpd (HI_U32 u32Data, VDP_DISP_PARA_E enMode)
{
    DISP_INFO("98mv310 Nousing!\n");

    return ;
}


//mod me
HI_VOID VDP_DISP_SetProToInterEnable   (HI_U32 u32hd_id, HI_U32 u32Enable)
{
    U_DHD0_CTRL DHD0_CTRL;

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.p2i_en = 0;//u32Enable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);
}



HI_VOID VDP_DISP_SetPauseMode(HI_U32 u32hd_id, HI_U32 enable)
{
    U_DHD0_PAUSE DHD0_PAUSE;
    DHD0_PAUSE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_PAUSE.u32)+u32hd_id*CHN_OFFSET));
    DHD0_PAUSE.bits.pause_mode = enable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_PAUSE.u32)+u32hd_id*CHN_OFFSET), DHD0_PAUSE.u32);
}

HI_VOID VDP_DISP_SetPreStartPos(HI_U32 pre_start_pos)
{
	U_DHD0_START_POS2 DHD0_START_POS2;

	DHD0_START_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->DHD0_START_POS2.u32));
	DHD0_START_POS2.bits.pre_start_pos = pre_start_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->DHD0_START_POS2.u32),DHD0_START_POS2.u32);

	return ;
}

HI_VOID VDP_DISP_SetPreStartLinePos(HI_U32 pre_start_line_pos)
{
	U_DHD0_START_POS2 DHD0_START_POS2;

	DHD0_START_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->DHD0_START_POS2.u32));
	DHD0_START_POS2.bits.pre_start_line_pos = pre_start_line_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->DHD0_START_POS2.u32),DHD0_START_POS2.u32);

	return ;
}

HI_VOID VDP_DISP_SetStartPos (HI_U32 u32Data, HI_U32 u32StartPos)
{
    U_DHD0_START_POS   DHD0_START_POS;


    DHD0_START_POS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_START_POS.u32)+u32Data*CHN_OFFSET));
    DHD0_START_POS.bits.start_pos = u32StartPos;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_START_POS.u32)+u32Data*CHN_OFFSET),DHD0_START_POS.u32);
}

HI_VOID VDP_DISP_SetParaLoadPos (HI_U32 u32Data, HI_U32 u32StartPos)
{
    U_DHD0_PARATHD   DHD0_PARATHD;


    DHD0_PARATHD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_PARATHD.u32)+u32Data*CHN_OFFSET));
    DHD0_PARATHD.bits.para_thd = u32StartPos;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_PARATHD.u32)+u32Data*CHN_OFFSET),DHD0_PARATHD.u32);
}

HI_VOID VDP_DISP_SetIntfRgbModeEn(HI_U32 u32En)
{
	U_INTF_HDMI_CTRL INTF_HDMI_CTRL;

	INTF_HDMI_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->INTF_HDMI_CTRL.u32));
	INTF_HDMI_CTRL.bits.rgb_mode = ~u32En;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->INTF_HDMI_CTRL.u32),INTF_HDMI_CTRL.u32);

	return ;
}

HI_VOID VDP_DISP_GetDHD0VblankState(HI_BOOL *pbVblank)
{
    U_DHD0_STATE           DHD0_STATE;
    DHD0_STATE.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->DHD0_STATE.u32));
    *pbVblank = DHD0_STATE.bits.vblank;
    return;
}

HI_VOID VDP_DISP_GetVactState(HI_U32 u32hd_id, HI_BOOL *pbBtm, HI_U32 *pu32Vcnt)
{
    U_DHD0_STATE DHD0_STATE;


    //Set Vou Dhd Channel Gamma Correct Enable
    DHD0_STATE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_STATE.u32)+u32hd_id*CHN_OFFSET));
    *pbBtm   = DHD0_STATE.bits.bottom_field;
    *pu32Vcnt = DHD0_STATE.bits.count_vcnt;

    return;
}

HI_U32 VDP_DISP_GetDispMode(HI_U32 u32hd_id)
{
    U_DHD0_CTRL DHD0_CTRL;
    DHD0_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32) + u32hd_id*CHN_OFFSET);

    return DHD0_CTRL.bits.iop;
}


HI_VOID VDP_DISP_SetNxgDataSwapEnable(HI_U32 u32hd_id, HI_U32 enable)
{
    DISP_INFO("98mv310 Nousing!\n");
}



