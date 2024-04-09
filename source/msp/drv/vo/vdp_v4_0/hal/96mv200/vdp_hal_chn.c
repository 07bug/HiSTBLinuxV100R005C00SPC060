#include "vdp_define.h"
#include "vdp_ip_define.h"
#include "vdp_hal_comm.h"
#include "vdp_hal_chn.h"

#if EDA_TEST
#include "vdp_env_def.h"
#endif
#if VDP_CBB_FPGA
#include "vdp_fpga_define.h"
//#include "sv_unf_osal.h"
#if FPGA_AUTORUN
#include "vdp_util.h"
#endif
//#include <linux/fcntl.h>
#endif

//#include "vdp_drv_func.h"


extern S_VDP_REGS_TYPE *pVdpReg;

extern char cOfName[256];
extern char cIfName[256];
extern char cIfNamehdr[256];
extern struct file *fpCfgHdrOut;

#if VDP_CBB_FPGA
extern HI_U32 gu32SumOut[MAX_SUM][256];
//extern HI_U32 gu32_ret[MAX_CHK_CHN][MAX_CHK_FRM];
#endif
extern HI_U32  *gu32_ret;

HI_VOID VDP_DISP_SetDispMode  (HI_U32 u32hd_id, HI_U32 u32DispMode)
{
    U_DHD0_CTRL DHD0_CTRL;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetFramePackingEn Select Wrong CHANNEL ID\n");
        return ;
    }

    DHD0_CTRL.u32 = VDP_RegRead((HI_ULONG)(&(pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET));
    DHD0_CTRL.bits.disp_mode = u32DispMode;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET), DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_SetHdmiMode  (HI_U32 u32hd_id, HI_U32 u32hdmi_md)
{
    U_DHD0_CTRL DHD0_CTRL;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetHdmiMode Select Wrong CHANNEL ID\n");
        return ;
    }

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET));
    DHD0_CTRL.bits.hdmi_mode = u32hdmi_md;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET), DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_SetRegUp (HI_U32 u32hd_id)
{
    U_DHD0_CTRL DHD0_CTRL;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetIntfEnable Select Wrong CHANNEL ID\n");
        return ;
    }

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET));
    DHD0_CTRL.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET), DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_SetIntfEnable(HI_U32 u32hd_id, HI_U32 bTrue)
{
    U_DHD0_CTRL DHD0_CTRL;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetIntfEnable Select Wrong CHANNEL ID\n");
        return ;
    }

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET));
    DHD0_CTRL.bits.intf_en = bTrue;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET), DHD0_CTRL.u32);

    VDP_DISP_SetRegUp(u32hd_id);
}

HI_VOID VDP_DISP_SetIntMask  (HI_U32 u32masktypeen)
{
    U_VOINTMSK VOINTMSK;

    /* Dispaly interrupt mask enable */
    VOINTMSK.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOINTMSK.u32)));
    VOINTMSK.u32 = VOINTMSK.u32 | u32masktypeen;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOINTMSK.u32)), VOINTMSK.u32);

    return ;
}

HI_VOID  VDP_DISP_SetIntDisable(HI_U32 u32masktypeen)
{
    U_VOINTMSK VOINTMSK;

    /* Dispaly interrupt mask enable */
    VOINTMSK.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOINTMSK.u32)));
    VOINTMSK.u32 = VOINTMSK.u32 & (~u32masktypeen);
    VDP_RegWrite((HI_ULONG) & (pVdpReg->VOINTMSK.u32), VOINTMSK.u32);

    return ;
}

HI_U32 VDP_DISP_GetDispMode(HI_U32 u32hd_id)
{
    U_DHD0_CTRL DHD0_CTRL;
    DHD0_CTRL.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET);
    return DHD0_CTRL.bits.iop;
}

HI_VOID  VDP_DISP_OpenIntf(HI_U32 u32hd_id, VDP_DISP_SYNCINFO_S stSyncInfo)
{
    U_DHD0_CTRL DHD0_CTRL;
    U_DHD0_VSYNC DHD0_VSYNC;
    U_DHD0_VPLUS DHD0_VPLUS;
    U_DHD0_PWR DHD0_PWR;
    U_DHD0_HSYNC1 DHD0_HSYNC1;
    U_DHD0_HSYNC2 DHD0_HSYNC2;

    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_OpenIntf Select Wrong CHANNEL ID\n");
        return ;
    }


    /*
    //VOU VHD CHANNEL enable
    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET));
    DHD0_CTRL.bits.iop   = stSyncInfo.bIop;//
    //DHD0_CTRL.bits.intfb = //stSyncInfo.u32Intfb; in intf
    //DHD0_CTRL.bits.synm  = //stSyncInfo.bSynm;
    DHD0_CTRL.bits.idv   = stSyncInfo.bIdv;//DATA INV
    DHD0_CTRL.bits.ihs   = stSyncInfo.bIhs;// H PULSE INV
    DHD0_CTRL.bits.ivs   = stSyncInfo.bIvs;//V PULSE INV
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD0_CTRL.u32)+u32hd_id*CHN_OFFSET),DHD0_CTRL.u32);
     */
    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET));
    DHD0_CTRL.bits.iop   = stSyncInfo.bIop;//
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET), DHD0_CTRL.u32);


    DHD0_HSYNC1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSYNC1.u32) + u32hd_id * CHN_OFFSET));
    DHD0_HSYNC2.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSYNC2.u32) + u32hd_id * CHN_OFFSET));
    DHD0_HSYNC1.bits.hact = stSyncInfo.u32Hact - 1;
    DHD0_HSYNC1.bits.hbb  = stSyncInfo.u32Hbb - 1;
    DHD0_HSYNC2.bits.hfb  = stSyncInfo.u32Hfb - 1;
    DHD0_HSYNC2.bits.hmid = (stSyncInfo.u32Hmid == 0) ? 0 : stSyncInfo.u32Hmid - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSYNC1.u32) + u32hd_id * CHN_OFFSET), DHD0_HSYNC1.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSYNC2.u32) + u32hd_id * CHN_OFFSET), DHD0_HSYNC2.u32);

    //Config VHD interface veritical timming
    DHD0_VSYNC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VSYNC.u32) + u32hd_id * CHN_OFFSET));
    DHD0_VSYNC.bits.vact = stSyncInfo.u32Vact  - 1;
    DHD0_VSYNC.bits.vbb = stSyncInfo.u32Vbb - 1;
    DHD0_VSYNC.bits.vfb =  stSyncInfo.u32Vfb - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VSYNC.u32) + u32hd_id * CHN_OFFSET), DHD0_VSYNC.u32);

    //Config VHD interface veritical bottom timming,no use in progressive mode
    DHD0_VPLUS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VPLUS.u32) + u32hd_id * CHN_OFFSET));
    DHD0_VPLUS.bits.bvact = stSyncInfo.u32Bvact - 1;
    DHD0_VPLUS.bits.bvbb =  stSyncInfo.u32Bvbb - 1;
    DHD0_VPLUS.bits.bvfb =  stSyncInfo.u32Bvfb - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VPLUS.u32) + u32hd_id * CHN_OFFSET), DHD0_VPLUS.u32);

    //Config VHD interface veritical bottom timming,
    DHD0_PWR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_PWR.u32) + u32hd_id * CHN_OFFSET));
    DHD0_PWR.bits.hpw = stSyncInfo.u32Hpw - 1;
    DHD0_PWR.bits.vpw = stSyncInfo.u32Vpw - 1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_PWR.u32) + u32hd_id * CHN_OFFSET), DHD0_PWR.u32);
}

#if 0
//mod me
HI_VOID VDP_DISP_SetVSync(HI_U32 u32hd_id, HI_U32 u32vfb, HI_U32 u32vbb, HI_U32 u32vact)
{
    U_DHD0_VSYNC DHD0_VSYNC;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetVSync Select Wrong CHANNEL ID\n");
        return ;
    }
    //Config VHD interface veritical timming
    DHD0_VSYNC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VSYNC.u32) + u32hd_id * CHN_OFFSET));
    DHD0_VSYNC.bits.vact = u32vact;
    DHD0_VSYNC.bits.vbb = u32vbb;
    DHD0_VSYNC.bits.vfb = u32vfb;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VSYNC.u32) + u32hd_id * CHN_OFFSET), DHD0_VSYNC.u32);
}

HI_VOID VDP_DISP_SetVSyncPlus(HI_U32 u32hd_id, HI_U32 u32bvfb, HI_U32 u32bvbb, HI_U32 u32vact)
{

    U_DHD0_VPLUS DHD0_VPLUS;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetVSyncPlus Select Wrong CHANNEL ID\n");
        return ;
    }

    //Config VHD interface veritical bottom timming,no use in progressive mode
    DHD0_VPLUS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VPLUS.u32) + u32hd_id * CHN_OFFSET));
    DHD0_VPLUS.bits.bvact = u32vact;
    DHD0_VPLUS.bits.bvbb = u32bvbb;
    DHD0_VPLUS.bits.bvfb = u32bvfb;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VPLUS.u32) + u32hd_id * CHN_OFFSET), DHD0_VPLUS.u32);


}

HI_VOID VDP_DISP_SetHSync(HI_U32 u32hd_id, HI_U32 u32hfb, HI_U32 u32hbb, HI_U32 u32hact)
{


    U_DHD0_HSYNC1 DHD0_HSYNC1;
    U_DHD0_HSYNC2 DHD0_HSYNC2;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetHSync Select Wrong CHANNEL ID\n");
        return ;
    }

    //Config VHD interface horizontal timming
    DHD0_HSYNC1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSYNC1.u32) + u32hd_id * CHN_OFFSET));
    DHD0_HSYNC2.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSYNC2.u32) + u32hd_id * CHN_OFFSET));
    DHD0_HSYNC1.bits.hact = u32hact;
    DHD0_HSYNC1.bits.hbb = u32hbb;
    DHD0_HSYNC2.bits.hfb = u32hfb;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSYNC1.u32) + u32hd_id * CHN_OFFSET), DHD0_HSYNC1.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSYNC2.u32) + u32hd_id * CHN_OFFSET), DHD0_HSYNC2.u32);

}

HI_VOID  VDP_DISP_SetPlusWidth(HI_U32 u32hd_id, HI_U32 u32hpw, HI_U32 u32vpw)
{
    U_DHD0_PWR DHD0_PWR;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetPlusWidth Select Wrong CHANNEL ID\n");
        return ;
    }
    DHD0_PWR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_PWR.u32) + u32hd_id * CHN_OFFSET));
    DHD0_PWR.bits.hpw = u32hpw;
    DHD0_PWR.bits.vpw = u32vpw;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_PWR.u32) + u32hd_id * CHN_OFFSET), DHD0_PWR.u32);
}

HI_VOID VDP_DISP_SetPlusPhase(HI_U32 u32hd_id, HI_U32 u32ihs, HI_U32 u32ivs, HI_U32 u32idv)
{
    U_DHD0_CTRL DHD0_CTRL;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetPlusPhase Select Wrong CHANNEL ID\n");
        return ;
    }
    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET));
    DHD0_CTRL.bits.ihs = u32ihs;
    DHD0_CTRL.bits.ivs = u32ivs;
    DHD0_CTRL.bits.idv = u32idv;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET), DHD0_CTRL.u32);
}
#endif

#if 1
HI_VOID VDP_DISP_SetSyncInv(HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, VDP_DISP_SYNCINV_S enInv)
{
    U_DHD0_SYNC_INV DHD0_SYNC_INV;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetSync_INV Select Wrong CHANNEL ID\n");
        return ;
    }

    switch (enIntf)
    {
            //case VDP_DISP_INTF_DATE:
        case VDP_DISP_INTF_HDDATE:
        case VDP_DISP_INTF_SDDATE:
        {
            DHD0_SYNC_INV.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_SYNC_INV.u32) + u32hd_id * CHN_OFFSET));
            DHD0_SYNC_INV.bits.date_f_inv  = enInv.u32FdInv;
            DHD0_SYNC_INV.bits.date_vs_inv = enInv.u32VsInv;
            DHD0_SYNC_INV.bits.date_hs_inv = enInv.u32HsInv;
            DHD0_SYNC_INV.bits.date_dv_inv = enInv.u32DvInv;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_SYNC_INV.u32) + u32hd_id * CHN_OFFSET), DHD0_SYNC_INV.u32);

            break;
        }
        case VDP_DISP_INTF_HDMI:
        {
            DHD0_SYNC_INV.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_SYNC_INV.u32) + u32hd_id * CHN_OFFSET));
            DHD0_SYNC_INV.bits.hdmi_f_inv  = enInv.u32FdInv;
            DHD0_SYNC_INV.bits.hdmi_vs_inv = enInv.u32VsInv;
            DHD0_SYNC_INV.bits.hdmi_hs_inv = enInv.u32HsInv;
            DHD0_SYNC_INV.bits.hdmi_dv_inv = enInv.u32DvInv;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_SYNC_INV.u32) + u32hd_id * CHN_OFFSET), DHD0_SYNC_INV.u32);

            break;
        }
        case VDP_DISP_INTF_VGA:
        {
            DHD0_SYNC_INV.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_SYNC_INV.u32) + u32hd_id * CHN_OFFSET));
            DHD0_SYNC_INV.bits.vga_vs_inv = enInv.u32VsInv;
            DHD0_SYNC_INV.bits.vga_hs_inv = enInv.u32HsInv;
            DHD0_SYNC_INV.bits.vga_dv_inv = enInv.u32DvInv;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_SYNC_INV.u32) + u32hd_id * CHN_OFFSET), DHD0_SYNC_INV.u32);

            break;
        }
        case VDP_DISP_INTF_LCD:
        {
            DHD0_SYNC_INV.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_SYNC_INV.u32) + u32hd_id * CHN_OFFSET));
            DHD0_SYNC_INV.bits.lcd_vs_inv = enInv.u32VsInv;
            DHD0_SYNC_INV.bits.lcd_hs_inv = enInv.u32HsInv;
            DHD0_SYNC_INV.bits.lcd_dv_inv = enInv.u32DvInv;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_SYNC_INV.u32) + u32hd_id * CHN_OFFSET), DHD0_SYNC_INV.u32);

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
#endif


HI_VOID  VDP_DISP_SetIntfMuxSel(HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf)
{
    U_VO_MUX VO_MUX;

    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetIntfMuxSel Select Wrong CHANNEL ID\n");
        return ;
    }

    switch (enIntf)
    {
#if INTF_EN
        case VDP_DISP_INTF_LCD:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.digital_sel = 2;
            VO_MUX.bits.lcd_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG) & (pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        case VDP_DISP_INTF_BT1120:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.bt1120_sel = u32hd_id;
            VO_MUX.bits.digital_sel = 0;
            VDP_RegWrite((HI_ULONG) & (pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
#else
        case VDP_DISP_INTF_LCD:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.digital_sel = u32hd_id * 2;
            VDP_RegWrite((HI_ULONG) & (pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        case VDP_DISP_INTF_BT1120:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.digital_sel = 1 + u32hd_id * 2;
            VDP_RegWrite((HI_ULONG) & (pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
#endif
        case VDP_DISP_INTF_HDMI:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.hdmi_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG) & (pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        case VDP_DISP_INTF_VGA:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.vga_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG) & (pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        case VDP_DISP_INTF_HDDATE:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.hddate_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG) & (pVdpReg->VO_MUX.u32), VO_MUX.u32);

            break;
        }
        case VDP_DISP_INTF_SDDATE:
        {
            VO_MUX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VO_MUX.u32)));
            VO_MUX.bits.sddate_sel = u32hd_id;
            VDP_RegWrite((HI_ULONG) & (pVdpReg->VO_MUX.u32), VO_MUX.u32);

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
    VOINTSTA.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOINTSTA.u32)));

    return (VOINTSTA.u32 & u32intmask);
}

#if    1

//--------------FPGA DEBUG------------//

HI_VOID  VDP_DISP_ClearIntSta(HI_U32 u32intmask )
{
    //volatile U_VOMSKINTSTA VOMSKINTSTA;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->VOMSKINTSTA.u32), u32intmask);
}
#endif

HI_VOID VDP_DISP_SetVtThdMode(HI_U32 u32hd_id, HI_U32 u32uthdnum, HI_U32 u32mode)
{
    U_DHD0_VTTHD3 DHD0_VTTHD3;
    U_DHD0_VTTHD  DHD0_VTTHD;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetVtThdMode Select Wrong CHANNEL ID\n");
        return ;
    }

    if (u32uthdnum == 1) //threshold 1 int mode
    {
        DHD0_VTTHD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VTTHD.u32) + u32hd_id * CHN_OFFSET));
        DHD0_VTTHD.bits.thd1_mode = u32mode;// frame or field
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VTTHD.u32) + u32hd_id * CHN_OFFSET), DHD0_VTTHD.u32);
    }
    else if (u32uthdnum == 2) //threshold 2 int mode
    {
        DHD0_VTTHD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VTTHD.u32) + u32hd_id * CHN_OFFSET));
        DHD0_VTTHD.bits.thd2_mode = u32mode;// frame or field
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VTTHD.u32) + u32hd_id * CHN_OFFSET), DHD0_VTTHD.u32);
    }
    else if (u32uthdnum == 3) //threshold 3 int mode
    {
        DHD0_VTTHD3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VTTHD3.u32) + u32hd_id * CHN_OFFSET));
        DHD0_VTTHD3.bits.thd3_mode = u32mode;// frame or field
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VTTHD3.u32) + u32hd_id * CHN_OFFSET), DHD0_VTTHD3.u32);

    }
}

HI_VOID VDP_DISP_SetVtThd(HI_U32 u32hd_id, HI_U32 u32uthdnum, HI_U32 u32vtthd)
{

    U_DHD0_VTTHD DHD0_VTTHD;
    U_DHD0_VTTHD3 DHD0_VTTHD3;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetVtThd Select Wrong CHANNEL ID\n");
        return ;
    }

    if (u32uthdnum == 1)
    {
        DHD0_VTTHD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VTTHD.u32) + u32hd_id * CHN_OFFSET));
        DHD0_VTTHD.bits.vtmgthd1 = u32vtthd;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VTTHD.u32) + u32hd_id * CHN_OFFSET), DHD0_VTTHD.u32);
    }
    else if (u32uthdnum == 2)
    {
        DHD0_VTTHD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VTTHD.u32) + u32hd_id * CHN_OFFSET));
        DHD0_VTTHD.bits.vtmgthd2 = u32vtthd;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VTTHD.u32) + u32hd_id * CHN_OFFSET), DHD0_VTTHD.u32);
    }
    else if (u32uthdnum == 3)
    {
        DHD0_VTTHD3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VTTHD3.u32) + u32hd_id * CHN_OFFSET));
        DHD0_VTTHD3.bits.vtmgthd3 = u32vtthd;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VTTHD3.u32) + u32hd_id * CHN_OFFSET), DHD0_VTTHD3.u32);
    }
    else if (u32uthdnum == 4)
    {
        DHD0_VTTHD3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_VTTHD3.u32) + u32hd_id * CHN_OFFSET));
        DHD0_VTTHD3.bits.vtmgthd4 = u32vtthd;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_VTTHD3.u32) + u32hd_id * CHN_OFFSET), DHD0_VTTHD3.u32);
    }
}

HI_VOID  VDP_DISP_SetClipCoef (HI_U32 u32hd_id, VDP_DISP_INTF_E clipsel, VDP_DISP_CLIP_S stClipData)
{

    U_DHD0_CLIP0_L       DHD0_CLIP0_L;
    U_DHD0_CLIP0_H       DHD0_CLIP0_H;
    U_DHD0_CLIP1_L       DHD0_CLIP1_L;
    U_DHD0_CLIP1_H       DHD0_CLIP1_H;
    U_DHD0_CLIP2_L       DHD0_CLIP2_L;
    U_DHD0_CLIP2_H       DHD0_CLIP2_H;
    U_DHD0_CLIP3_L       DHD0_CLIP3_L;
    U_DHD0_CLIP3_H       DHD0_CLIP3_H;
    U_DHD0_CLIP4_L       DHD0_CLIP4_L;
    U_DHD0_CLIP4_H       DHD0_CLIP4_H;

    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetClipVtt Select Wrong CHANNEL ID\n");
        return ;
    }

    //BT1120
    if (clipsel == VDP_DISP_INTF_BT1120)
    {
        DHD0_CLIP0_L.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP0_L.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP0_L.bits.clip_cl2 = stClipData.u32ClipLow_y;
        DHD0_CLIP0_L.bits.clip_cl1 = stClipData.u32ClipLow_cb;
        DHD0_CLIP0_L.bits.clip_cl0 = stClipData.u32ClipLow_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP0_L.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP0_L.u32);

        DHD0_CLIP0_H.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP0_H.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP0_H.bits.clip_ch2 = stClipData.u32ClipHigh_y;
        DHD0_CLIP0_H.bits.clip_ch1 = stClipData.u32ClipHigh_cb;
        DHD0_CLIP0_H.bits.clip_ch0 = stClipData.u32ClipHigh_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP0_H.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP0_H.u32);
    }

    //DATE
    else if (clipsel == VDP_DISP_INTF_SDDATE)
    {

        DHD0_CLIP1_L.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP1_L.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP1_L.bits.clip_cl2 = stClipData.u32ClipLow_y;
        DHD0_CLIP1_L.bits.clip_cl1 = stClipData.u32ClipLow_cb;
        DHD0_CLIP1_L.bits.clip_cl0 = stClipData.u32ClipLow_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP1_L.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP1_L.u32);

        DHD0_CLIP1_H.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP1_H.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP1_H.bits.clip_ch2 = stClipData.u32ClipHigh_y;
        DHD0_CLIP1_H.bits.clip_ch1 = stClipData.u32ClipHigh_cb;
        DHD0_CLIP1_H.bits.clip_ch0 = stClipData.u32ClipHigh_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP1_H.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP1_H.u32);
    }

    //HDMI
    else if (clipsel == VDP_DISP_INTF_HDMI)
    {

        DHD0_CLIP2_L.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP2_L.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP2_L.bits.clip_cl2 = stClipData.u32ClipLow_y;
        DHD0_CLIP2_L.bits.clip_cl1 = stClipData.u32ClipLow_cb;
        DHD0_CLIP2_L.bits.clip_cl0 = stClipData.u32ClipLow_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP2_L.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP2_L.u32);

        DHD0_CLIP2_H.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP2_H.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP2_H.bits.clip_ch2 = stClipData.u32ClipHigh_y;
        DHD0_CLIP2_H.bits.clip_ch1 = stClipData.u32ClipHigh_cb;
        DHD0_CLIP2_H.bits.clip_ch0 = stClipData.u32ClipHigh_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP2_H.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP2_H.u32);
    }

    //VGA
    else if (clipsel == VDP_DISP_INTF_VGA)
    {

        DHD0_CLIP3_L.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP3_L.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP3_L.bits.clip_cl2 = stClipData.u32ClipLow_y;
        DHD0_CLIP3_L.bits.clip_cl1 = stClipData.u32ClipLow_cb;
        DHD0_CLIP3_L.bits.clip_cl0 = stClipData.u32ClipLow_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP3_L.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP3_L.u32);

        DHD0_CLIP3_H.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP3_H.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP3_H.bits.clip_ch2 = stClipData.u32ClipHigh_y;
        DHD0_CLIP3_H.bits.clip_ch1 = stClipData.u32ClipHigh_cb;
        DHD0_CLIP3_H.bits.clip_ch0 = stClipData.u32ClipHigh_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP3_H.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP3_H.u32);
    }

    //LCD
    else if (clipsel == VDP_DISP_INTF_LCD)
    {

        DHD0_CLIP4_L.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP4_L.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP4_L.bits.clip_cl2 = stClipData.u32ClipLow_y;
        DHD0_CLIP4_L.bits.clip_cl1 = stClipData.u32ClipLow_cb;
        DHD0_CLIP4_L.bits.clip_cl0 = stClipData.u32ClipLow_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP4_L.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP4_L.u32);

        DHD0_CLIP4_H.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CLIP4_H.u32) + u32hd_id * CHN_OFFSET));
        DHD0_CLIP4_H.bits.clip_ch2 = stClipData.u32ClipHigh_y;
        DHD0_CLIP4_H.bits.clip_ch1 = stClipData.u32ClipHigh_cb;
        DHD0_CLIP4_H.bits.clip_ch0 = stClipData.u32ClipHigh_cr;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CLIP4_H.u32) + u32hd_id * CHN_OFFSET), DHD0_CLIP4_H.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_DISP_SetClipVtt Select Wrong Interface Mode\n");
    }
}

HI_VOID  VDP_DISP_SetCscEnable  (HI_U32 u32hd_id, HI_U32 enCSC)
{
    U_DHD0_CSC_IDC DHD0_CSC_IDC;

    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetCscEnable Select Wrong CHANNEL ID\n");
        return ;
    }
    DHD0_CSC_IDC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CSC_IDC.u32) + u32hd_id * CHN_OFFSET));
    DHD0_CSC_IDC.bits.csc_en = enCSC;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CSC_IDC.u32) + u32hd_id * CHN_OFFSET), DHD0_CSC_IDC.u32);

}


//mod me
HI_VOID VDP_DISP_SetProToInterEnable   (HI_U32 u32hd_id, HI_U32 u32Enable)
{
    U_DHD0_CTRL DHD0_CTRL;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetProToInterEnable Select Wrong CHANNEL ID\n");
        return ;
    }

    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET));
    DHD0_CTRL.bits.p2i_en = u32Enable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET), DHD0_CTRL.u32);
}


#if 0
HI_VOID VDP_INTF_SetDitherMode  (HI_U32 u32Data, VDP_DITHER_E enDitherMode)

{
    U_INTF_DITHER0_CTRL INTF_DITHER0_CTRL;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetDitherMode Select Wrong INTF ID\n");
        return ;
    }


    INTF_DITHER0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_DITHER0_CTRL.u32) + u32Data * INTF_OFFSET));
    INTF_DITHER0_CTRL.bits.dither_md = enDitherMode;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_DITHER0_CTRL.u32) + u32Data * INTF_OFFSET), INTF_DITHER0_CTRL.u32);
}

HI_VOID VDP_INTF_SetDitherCoef  (HI_U32 u32Data,  VDP_DITHER_COEF_S dither_coef)

{
    U_INTF_DITHER0_COEF0 INTF_DITHER0_COEF0;
    U_INTF_DITHER0_COEF1 INTF_DITHER0_COEF1;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetDitherCoef Select Wrong CHANNEL ID\n");
        return ;
    }

    INTF_DITHER0_COEF0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_DITHER0_COEF0.u32) + u32Data * INTF_OFFSET));
    INTF_DITHER0_COEF0.bits.dither_coef0 = dither_coef.dither_coef0 ;
    INTF_DITHER0_COEF0.bits.dither_coef1 = dither_coef.dither_coef1 ;
    INTF_DITHER0_COEF0.bits.dither_coef2 = dither_coef.dither_coef2 ;
    INTF_DITHER0_COEF0.bits.dither_coef3 = dither_coef.dither_coef3 ;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_DITHER0_COEF0.u32) + u32Data * INTF_OFFSET), INTF_DITHER0_COEF0.u32);

    INTF_DITHER0_COEF1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_DITHER0_COEF1.u32) + u32Data * INTF_OFFSET));
    INTF_DITHER0_COEF1.bits.dither_coef4 = dither_coef.dither_coef4 ;
    INTF_DITHER0_COEF1.bits.dither_coef5 = dither_coef.dither_coef5 ;
    INTF_DITHER0_COEF1.bits.dither_coef6 = dither_coef.dither_coef6 ;
    INTF_DITHER0_COEF1.bits.dither_coef7 = dither_coef.dither_coef7 ;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_DITHER0_COEF1.u32) + u32Data * INTF_OFFSET), INTF_DITHER0_COEF1.u32);
}

HI_VOID  VDP_INTF_SetClipEnable  (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf)
{
    VDP_PRINT("Error,This Driver has been deleted ...\n");
}



HI_VOID  VDP_INTF_SetCscEnable  (HI_U32 u32Data, HI_U32 enCSC)
{
    U_INTF_CSC_IDC INTF_CSC_IDC;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetCscEnable Select Wrong CHANNEL ID\n");
        return ;
    }
    INTF_CSC_IDC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CSC_IDC.u32) + u32Data * INTF_OFFSET));
    INTF_CSC_IDC.bits.csc_en = enCSC;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CSC_IDC.u32) + u32Data * INTF_OFFSET), INTF_CSC_IDC.u32);

}

HI_VOID   VDP_INTF_SetCscDcCoef(HI_U32 u32Data, VDP_CSC_DC_COEF_S stCscCoef)
{
    U_INTF_CSC_IDC  INTF_CSC_IDC;
    U_INTF_CSC_ODC  INTF_CSC_ODC;
    U_INTF_CSC_IODC INTF_CSC_IODC;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetCscDcCoef Select Wrong CHANNEL ID\n");
        return ;
    }

    INTF_CSC_IDC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CSC_IDC.u32) + u32Data * INTF_OFFSET));
    INTF_CSC_IDC.bits.cscidc1 = stCscCoef.csc_in_dc1;
    INTF_CSC_IDC.bits.cscidc0 = stCscCoef.csc_in_dc0;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CSC_IDC.u32) + u32Data * INTF_OFFSET), INTF_CSC_IDC.u32);

    INTF_CSC_ODC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CSC_ODC.u32) + u32Data * INTF_OFFSET));
    INTF_CSC_ODC.bits.cscodc1 = stCscCoef.csc_out_dc1;
    INTF_CSC_ODC.bits.cscodc0 = stCscCoef.csc_out_dc0;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CSC_ODC.u32) + u32Data * INTF_OFFSET), INTF_CSC_ODC.u32);

    INTF_CSC_IODC.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CSC_IODC.u32) + u32Data * INTF_OFFSET));
    INTF_CSC_IODC.bits.cscidc2 = stCscCoef.csc_in_dc2;
    INTF_CSC_IODC.bits.cscodc2 = stCscCoef.csc_out_dc2;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CSC_IODC.u32) + u32Data * INTF_OFFSET), INTF_CSC_IODC.u32);

}

HI_VOID   VDP_INTF_SetCscCoef(HI_U32 u32Data, VDP_CSC_COEF_S stCscCoef)
{
    U_INTF_CSC_P0        INTF_CSC_P0;
    U_INTF_CSC_P1        INTF_CSC_P1;
    U_INTF_CSC_P2        INTF_CSC_P2;
    U_INTF_CSC_P3        INTF_CSC_P3;
    U_INTF_CSC_P4        INTF_CSC_P4;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetCscCoef Select Wrong INTF ID\n");
        return ;
    }

    INTF_CSC_P0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CSC_P0.u32) + u32Data * INTF_OFFSET));
    INTF_CSC_P0.bits.cscp00 = stCscCoef.csc_coef00;
    INTF_CSC_P0.bits.cscp01 = stCscCoef.csc_coef01;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CSC_P0.u32) + u32Data * INTF_OFFSET), INTF_CSC_P0.u32);

    INTF_CSC_P1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CSC_P1.u32) + u32Data * INTF_OFFSET));
    INTF_CSC_P1.bits.cscp02 = stCscCoef.csc_coef02;
    INTF_CSC_P1.bits.cscp10 = stCscCoef.csc_coef10;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CSC_P1.u32) + u32Data * INTF_OFFSET), INTF_CSC_P1.u32);

    INTF_CSC_P2.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CSC_P2.u32) + u32Data * INTF_OFFSET));
    INTF_CSC_P2.bits.cscp11 = stCscCoef.csc_coef11;
    INTF_CSC_P2.bits.cscp12 = stCscCoef.csc_coef12;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CSC_P2.u32) + u32Data * INTF_OFFSET), INTF_CSC_P2.u32);

    INTF_CSC_P3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CSC_P3.u32) + u32Data * INTF_OFFSET));
    INTF_CSC_P3.bits.cscp20 = stCscCoef.csc_coef20;
    INTF_CSC_P3.bits.cscp21 = stCscCoef.csc_coef21;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CSC_P3.u32) + u32Data * INTF_OFFSET), INTF_CSC_P3.u32);

    INTF_CSC_P4.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CSC_P4.u32) + u32Data * INTF_OFFSET));
    INTF_CSC_P4.bits.cscp22 = stCscCoef.csc_coef22;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CSC_P4.u32) + u32Data * INTF_OFFSET), INTF_CSC_P4.u32);

}

HI_VOID VDP_INTF_SetCscMode(HI_U32 u32Data, VDP_CSC_MODE_E enCscMode)

{
    VDP_CSC_COEF_S    st_csc_coef;
    VDP_CSC_DC_COEF_S st_csc_dc_coef;

    HI_U32 u32Pre   = 1 << 10;
    HI_U32 u32DcPre = 4;//1:8bit; 4:10bit

    if (enCscMode == VDP_CSC_RGB2YUV_601)
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
    else if (enCscMode == VDP_CSC_YUV2RGB_601)
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
    else if (enCscMode == VDP_CSC_RGB2YUV_709)
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
    else if (enCscMode == VDP_CSC_YUV2RGB_709)
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
    else if (enCscMode == VDP_CSC_YUV2YUV_709_601)
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
    else if (enCscMode == VDP_CSC_YUV2YUV_601_709)
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
        st_csc_coef.csc_coef00     = 1 * u32Pre;
        st_csc_coef.csc_coef01     = 0 * u32Pre;
        st_csc_coef.csc_coef02     = 0 * u32Pre;

        st_csc_coef.csc_coef10     = 0 * u32Pre;
        st_csc_coef.csc_coef11     = 1 * u32Pre;
        st_csc_coef.csc_coef12     = 0 * u32Pre;

        st_csc_coef.csc_coef20     = 0 * u32Pre;
        st_csc_coef.csc_coef21     = 0 * u32Pre;
        st_csc_coef.csc_coef22     = 1 * u32Pre;

        st_csc_dc_coef.csc_in_dc0  = -16  * u32DcPre;
        st_csc_dc_coef.csc_in_dc1  = -128 * u32DcPre;
        st_csc_dc_coef.csc_in_dc2  = -128 * u32DcPre;

        st_csc_dc_coef.csc_out_dc0 =  16 * u32DcPre;
        st_csc_dc_coef.csc_out_dc1 = 128 * u32DcPre;
        st_csc_dc_coef.csc_out_dc2 = 128 * u32DcPre;
    }

    VDP_INTF_SetCscCoef  (u32Data, st_csc_coef);
    VDP_INTF_SetCscDcCoef(u32Data, st_csc_dc_coef);

    return ;
}


HI_VOID  VDP_INTF_SetClipCoef (HI_U32 u32Data, VDP_DISP_CLIP_S stClipData)
{

    U_INTF_CLIP0_L       INTF_CLIP0_L;
    U_INTF_CLIP0_H       INTF_CLIP0_H;
    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetClipVtt Select Wrong INTF ID\n");
        return ;
    }

    INTF_CLIP0_L.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CLIP0_L.u32) + u32Data * INTF_OFFSET));
    INTF_CLIP0_L.bits.clip_cl2 = stClipData.u32ClipLow_y;
    INTF_CLIP0_L.bits.clip_cl1 = stClipData.u32ClipLow_cb;
    INTF_CLIP0_L.bits.clip_cl0 = stClipData.u32ClipLow_cr;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CLIP0_L.u32) + u32Data * INTF_OFFSET), INTF_CLIP0_L.u32);

    INTF_CLIP0_H.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CLIP0_H.u32) + u32Data * INTF_OFFSET));
    INTF_CLIP0_H.bits.clip_ch2 = stClipData.u32ClipHigh_y;
    INTF_CLIP0_H.bits.clip_ch1 = stClipData.u32ClipHigh_cb;
    INTF_CLIP0_H.bits.clip_ch0 = stClipData.u32ClipHigh_cr;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CLIP0_H.u32) + u32Data * INTF_OFFSET), INTF_CLIP0_H.u32);
}

HI_VOID VDP_INTF_SetHShrpEnable   (HI_U32 u32Data, HI_BOOL hsp_en)
{
    U_INTF_HSPCFG1 INTF_HSPCFG1;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error, VDP_INTF_SetHShrpEnable() select wrong intf ID\n");
        return;
    }

    INTF_HSPCFG1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG1.u32) + u32Data * INTF_OFFSET));

    INTF_HSPCFG1.bits.hsp_en = hsp_en;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG1.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG1.u32);
}

HI_VOID VDP_INTF_SetHShrpF0coef(HI_U32 u32Data, HI_S16 tmp0, HI_S16 tmp1, HI_S16 tmp2, HI_S16 tmp3)
{
    U_INTF_HSPCFG0 INTF_HSPCFG0;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error, VDP_INTF_SetHShrpF0coef() select wrong intf ID\n");
        return;
    }

    INTF_HSPCFG0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG0.u32) + u32Data * INTF_OFFSET));
    INTF_HSPCFG0.bits.hsp_hf0_tmp3 = tmp3;
    INTF_HSPCFG0.bits.hsp_hf0_tmp2 = tmp2;
    INTF_HSPCFG0.bits.hsp_hf0_tmp1 = tmp1;
    INTF_HSPCFG0.bits.hsp_hf0_tmp0 = tmp0;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG0.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG0.u32);
}

HI_VOID VDP_INTF_SetHShrpF1coef(HI_U32 u32Data, HI_S16 tmp0, HI_S16 tmp1, HI_S16 tmp2, HI_S16 tmp3)
{
    U_INTF_HSPCFG7 INTF_HSPCFG7;
    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error, VDP_INTF_SetHShrpF1coef() select wrong intf ID\n");
        return;
    }

    INTF_HSPCFG7.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG7.u32) + u32Data * INTF_OFFSET));
    INTF_HSPCFG7.bits.hsp_hf1_tmp3 = tmp3;
    INTF_HSPCFG7.bits.hsp_hf1_tmp2 = tmp2;
    INTF_HSPCFG7.bits.hsp_hf1_tmp1 = tmp1;
    INTF_HSPCFG7.bits.hsp_hf1_tmp0 = tmp0;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG7.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG7.u32);
}

HI_VOID VDP_INTF_SetHShrpCoring(HI_U32 u32Data, HI_U8 hf0_coring, HI_U8 hf1_coring)
{
    U_INTF_HSPCFG1 INTF_HSPCFG1;
    U_INTF_HSPCFG8 INTF_HSPCFG8;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error, VDP_INTF_SetHShrpCoring() select wrong intf ID\n");
        return;
    }

    INTF_HSPCFG1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG1.u32) + u32Data * INTF_OFFSET));
    INTF_HSPCFG8.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG8.u32) + u32Data * INTF_OFFSET));

    INTF_HSPCFG1.bits.hsp_hf0_coring = hf0_coring;
    INTF_HSPCFG8.bits.hsp_hf1_coring = hf1_coring;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG1.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG1.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG8.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG8.u32);
}

HI_VOID VDP_INTF_SetHShrpGain(HI_U32 u32Data, HI_S16 hf0_gainneg, HI_S16 hf0_gainpos, HI_S16 hf1_gainneg, HI_S16 hf1_gainpos)
{
    U_INTF_HSPCFG5  INTF_HSPCFG5;
    U_INTF_HSPCFG12 INTF_HSPCFG12;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error, VDP_INTF_SetHShrpGain() select wrong intf ID\n");
        return;
    }
    INTF_HSPCFG5.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG5.u32) + u32Data * INTF_OFFSET));
    INTF_HSPCFG12.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG12.u32) + u32Data * INTF_OFFSET));

    INTF_HSPCFG5.bits.hsp_hf0_gainneg  = hf0_gainneg;
    INTF_HSPCFG5.bits.hsp_hf0_gainpos  = hf0_gainpos;
    INTF_HSPCFG12.bits.hsp_hf1_gainneg = hf1_gainneg;
    INTF_HSPCFG12.bits.hsp_hf1_gainpos = hf1_gainpos;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG5.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG5.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG12.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG12.u32);
}

HI_VOID VDP_INTF_SetHShrpAdpEn(HI_U32 u32Data, HI_BOOL hf0_adpshooten, HI_BOOL hf1_adpshooten)
{
    U_INTF_HSPCFG6 INTF_HSPCFG6;
    U_INTF_HSPCFG13 INTF_HSPCFG13;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error, VDP_INTF_SetHShrpAdpEn() select wrong intf ID\n");
        return;
    }
    INTF_HSPCFG6.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG6.u32) + u32Data * INTF_OFFSET));
    INTF_HSPCFG13.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG13.u32) + u32Data * INTF_OFFSET));

    INTF_HSPCFG6.bits.hsp_hf0_adpshoot_en  = hf0_adpshooten;
    INTF_HSPCFG13.bits.hsp_hf1_adpshoot_en = hf1_adpshooten;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG6.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG6.u32);
}

HI_VOID VDP_INTF_SetHShrpWsize(HI_U32 u32Data, HI_U8 hf0_winsize, HI_U8 hf1_winsize)
{
    U_INTF_HSPCFG6 INTF_HSPCFG6;
    U_INTF_HSPCFG13 INTF_HSPCFG13;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error, VDP_INTF_SetHShrpWsize() select wrong intf ID\n");
        return;
    }
    INTF_HSPCFG6.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG6.u32) + u32Data * INTF_OFFSET));
    INTF_HSPCFG13.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG13.u32) + u32Data * INTF_OFFSET));

    INTF_HSPCFG6.bits.hsp_hf0_winsize     = hf0_winsize;
    INTF_HSPCFG13.bits.hsp_hf1_winsize    = hf1_winsize;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG6.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG6.u32);
}

HI_VOID VDP_INTF_SetHShrpThrd(HI_U32 u32Data, HI_U8 hf0_underth, HI_U8 hf0_overth, HI_U8 hf1_underth, HI_U8 hf1_overth)
{
    U_INTF_HSPCFG6 INTF_HSPCFG6;
    U_INTF_HSPCFG13 INTF_HSPCFG13;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error, VDP_INTF_SetHShrpThrd() select wrong intf ID\n");
        return;
    }
    INTF_HSPCFG6.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG6.u32) + u32Data * INTF_OFFSET));
    INTF_HSPCFG13.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG13.u32) + u32Data * INTF_OFFSET));

    INTF_HSPCFG6.bits.hsp_hf0_underth = hf0_underth;
    INTF_HSPCFG6.bits.hsp_hf0_overth  = hf0_overth;
    INTF_HSPCFG13.bits.hsp_hf1_underth = hf1_underth;
    INTF_HSPCFG13.bits.hsp_hf1_overth  = hf1_overth;


    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG6.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG6.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG13.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG13.u32);
}

HI_VOID VDP_INTF_SetHShrpMixratio(HI_U32 u32Data, HI_U8 hf0_mixratio, HI_U8 hf1_mixratio)
{
    U_INTF_HSPCFG6 INTF_HSPCFG6;
    U_INTF_HSPCFG13 INTF_HSPCFG13;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error, VDP_INTF_SetHShrpMixratio() select wrong intf ID\n");
        return;
    }
    INTF_HSPCFG6.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG6.u32) + u32Data * INTF_OFFSET));
    INTF_HSPCFG13.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG13.u32) + u32Data * INTF_OFFSET));

    INTF_HSPCFG6.bits.hsp_hf0_mixratio    = hf0_mixratio;
    INTF_HSPCFG13.bits.hsp_hf1_mixratio    = hf1_mixratio;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG6.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG6.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG13.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG13.u32);
}

HI_VOID VDP_INTF_SetHShrpEn(HI_U32 u32Data, HI_BOOL h1_en, HI_BOOL h2_en, HI_BOOL ltih_en, HI_BOOL ctih_en)
{
    U_INTF_HSPCFG14 INTF_HSPCFG14;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetHShrpEn() select wrong intf ID\n");
        return;
    }
    INTF_HSPCFG14.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG14.u32) + u32Data * INTF_OFFSET));
    INTF_HSPCFG14.bits.hsp_h0_en = h1_en;
    INTF_HSPCFG14.bits.hsp_h1_en = h2_en;
    INTF_HSPCFG14.bits.hsp_ltih_en = ltih_en;
    INTF_HSPCFG14.bits.hsp_ctih_en = ctih_en;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG14.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG14.u32);
}

HI_VOID VDP_INTF_SetHShrpXti(HI_U32 u32Data, HI_U8 hf_shootdiv, HI_U8 lti_ratio, HI_U8 ldti_gain, HI_U8 cdti_gain)
{
    U_INTF_HSPCFG14 INTF_HSPCFG14;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetHShrpXti() select wrong intf ID\n");
        return;
    }
    INTF_HSPCFG14.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG14.u32) + u32Data * INTF_OFFSET));

    INTF_HSPCFG14.bits.hsp_hf_shootdiv = hf_shootdiv;
    INTF_HSPCFG14.bits.hsp_lti_ratio = lti_ratio;
    INTF_HSPCFG14.bits.hsp_ldti_gain = ldti_gain;
    INTF_HSPCFG14.bits.hsp_cdti_gain = cdti_gain;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG14.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG14.u32);
}

HI_VOID VDP_INTF_SetHShrpGlbpara(HI_U32 u32Data, HI_U8 peak_ratio, HI_U16 glb_overth, HI_U16 glb_underth)
{
    U_INTF_HSPCFG15 INTF_HSPCFG15;

    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetHShrpXti() select wrong intf ID\n");
        return;
    }
    INTF_HSPCFG15.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_HSPCFG15.u32) + u32Data * INTF_OFFSET));

    INTF_HSPCFG15.bits.hsp_peak_ratio = peak_ratio;
    INTF_HSPCFG15.bits.hsp_glb_overth = glb_overth;
    INTF_HSPCFG15.bits.hsp_glb_underth = glb_underth;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_HSPCFG15.u32) + u32Data * INTF_OFFSET), INTF_HSPCFG15.u32);
}

HI_VOID VDP_INTF_SetRegUp (HI_U32 u32Data)
{
    U_INTF_UPD INTF_UPD;
    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetIntfEnable Select Wrong interface ID\n");
        return ;
    }

    INTF_UPD.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_UPD.u32) + u32Data * INTF_OFFSET));
    INTF_UPD.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_UPD.u32) + u32Data * INTF_OFFSET), INTF_UPD.u32);
}

HI_VOID VDP_INTF_SetHdmiMode  (HI_U32 u32Data, HI_U32 u32hdmi_md)
{
    U_INTF_CTRL INTF_CTRL;
    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetHdmiMode Select Wrong CHANNEL ID\n");
        return ;
    }

    INTF_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_CTRL.u32) + u32Data * INTF_OFFSET));
    INTF_CTRL.bits.hdmi_mode = u32hdmi_md;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_CTRL.u32) + u32Data * INTF_OFFSET), INTF_CTRL.u32);
}

HI_VOID VDP_INTF_SetSyncInv(HI_U32 u32Data, VDP_DISP_SYNCINV_S enInv)
{
    U_INTF_SYNC_INV INTF_SYNC_INV;
    if (u32Data >= INTF_MAX)
    {
        VDP_PRINT("Error,VDP_INTF_SetSync_INV Select Wrong INTF ID\n");
        return ;
    }

    INTF_SYNC_INV.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->INTF_SYNC_INV.u32) + u32Data * INTF_OFFSET));
    INTF_SYNC_INV.bits.f_inv  = enInv.u32FdInv;
    INTF_SYNC_INV.bits.vs_inv = enInv.u32VsInv;
    INTF_SYNC_INV.bits.hs_inv = enInv.u32HsInv;
    INTF_SYNC_INV.bits.dv_inv = enInv.u32DvInv;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->INTF_SYNC_INV.u32) + u32Data * INTF_OFFSET), INTF_SYNC_INV.u32);
}

HI_VOID VDP_DISP_SetHShrpEnable   (VDP_CHN_E enLayer, HI_BOOL hsp_en)
{
    U_DHD0_HSPCFG1 DHD0_HSPCFG1;

    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG1.u32) + CHN_OFFSET));

        DHD0_HSPCFG1.bits.hsp_en = hsp_en;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG1.u32) + CHN_OFFSET), DHD0_HSPCFG1.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpEnable() select wrong layer ID\n");
    }

}

HI_VOID VDP_DISP_SetHShrpF0coef(VDP_CHN_E enLayer, HI_S16 tmp0, HI_S16 tmp1, HI_S16 tmp2, HI_S16 tmp3)
{
    U_DHD0_HSPCFG0 DHD0_HSPCFG0;


    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG0.u32) + CHN_OFFSET));

        DHD0_HSPCFG0.bits.hsp_hf0_tmp3 = tmp3;
        DHD0_HSPCFG0.bits.hsp_hf0_tmp2 = tmp2;
        DHD0_HSPCFG0.bits.hsp_hf0_tmp1 = tmp1;
        DHD0_HSPCFG0.bits.hsp_hf0_tmp0 = tmp0;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG0.u32) + CHN_OFFSET), DHD0_HSPCFG0.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpF0coef() select wrong layer ID\n");
    }
}

HI_VOID VDP_DISP_SetHShrpF1coef(VDP_CHN_E enLayer, HI_S16 tmp0, HI_S16 tmp1, HI_S16 tmp2, HI_S16 tmp3)
{
    U_DHD0_HSPCFG7 DHD0_HSPCFG7;

    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG7.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG7.u32) + CHN_OFFSET));

        DHD0_HSPCFG7.bits.hsp_hf1_tmp3 = tmp3;
        DHD0_HSPCFG7.bits.hsp_hf1_tmp2 = tmp2;
        DHD0_HSPCFG7.bits.hsp_hf1_tmp1 = tmp1;
        DHD0_HSPCFG7.bits.hsp_hf1_tmp0 = tmp0;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG7.u32) + CHN_OFFSET), DHD0_HSPCFG7.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpF1coef() select wrong layer ID\n");
    }
}

HI_VOID VDP_DISP_SetHShrpCoring(VDP_CHN_E enLayer, HI_U8 hf0_coring, HI_U8 hf1_coring)
{
    U_DHD0_HSPCFG1 DHD0_HSPCFG1;
    U_DHD0_HSPCFG8 DHD0_HSPCFG8;
    if (enLayer ==  VDP_CHN_DHD1)
    {
        DHD0_HSPCFG1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG1.u32) + CHN_OFFSET));
        DHD0_HSPCFG8.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG8.u32) + CHN_OFFSET));

        DHD0_HSPCFG1.bits.hsp_hf0_coring = hf0_coring;
        DHD0_HSPCFG8.bits.hsp_hf1_coring = hf1_coring;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG1.u32) + CHN_OFFSET), DHD0_HSPCFG1.u32);
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG8.u32) + CHN_OFFSET), DHD0_HSPCFG8.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpCoring() select wrong layer ID\n");
    }

}

HI_VOID VDP_DISP_SetHShrpGain(VDP_CHN_E enLayer, HI_S16 hf0_gainneg, HI_S16 hf0_gainpos, HI_S16 hf1_gainneg, HI_S16 hf1_gainpos)
{
    U_DHD0_HSPCFG5 DHD0_HSPCFG5;
    U_DHD0_HSPCFG12 DHD0_HSPCFG12;

    if (enLayer == VDP_CHN_DHD1)
    {

        DHD0_HSPCFG5.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG5.u32) + CHN_OFFSET));
        DHD0_HSPCFG12.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG12.u32) + CHN_OFFSET));

        DHD0_HSPCFG5.bits.hsp_hf0_gainneg  = hf0_gainneg;
        DHD0_HSPCFG5.bits.hsp_hf0_gainpos  = hf0_gainpos;
        DHD0_HSPCFG12.bits.hsp_hf1_gainneg = hf1_gainneg;
        DHD0_HSPCFG12.bits.hsp_hf1_gainpos = hf1_gainpos;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG5.u32) + CHN_OFFSET), DHD0_HSPCFG5.u32);
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG12.u32) + CHN_OFFSET), DHD0_HSPCFG12.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpGain() select wrong layer ID\n");
    }
}

HI_VOID VDP_DISP_SetHShrpAdpEn(VDP_CHN_E enLayer, HI_BOOL hf0_adpshooten, HI_BOOL hf1_adpshooten)
{
    U_DHD0_HSPCFG6 DHD0_HSPCFG6;
    U_DHD0_HSPCFG13 DHD0_HSPCFG13;

    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG6.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG6.u32) + CHN_OFFSET));
        DHD0_HSPCFG13.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG13.u32) + CHN_OFFSET));

        DHD0_HSPCFG6.bits.hsp_hf0_adpshoot_en  = hf0_adpshooten;
        DHD0_HSPCFG13.bits.hsp_hf1_adpshoot_en = hf1_adpshooten;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG6.u32) + CHN_OFFSET), DHD0_HSPCFG6.u32);
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG13.u32) + CHN_OFFSET), DHD0_HSPCFG13.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpAdpEn() select wrong layer ID\n");
    }
}

HI_VOID VDP_DISP_SetHShrpWsize(VDP_CHN_E enLayer, HI_U8 hf0_winsize, HI_U8 hf1_winsize)
{
    U_DHD0_HSPCFG6 DHD0_HSPCFG6;
    U_DHD0_HSPCFG13 DHD0_HSPCFG13;

    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG6.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG6.u32) + CHN_OFFSET));
        DHD0_HSPCFG13.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG13.u32) + CHN_OFFSET));

        DHD0_HSPCFG6.bits.hsp_hf0_winsize     = hf0_winsize;
        DHD0_HSPCFG13.bits.hsp_hf1_winsize    = hf1_winsize;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG6.u32) + CHN_OFFSET), DHD0_HSPCFG6.u32);
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG13.u32) + CHN_OFFSET), DHD0_HSPCFG13.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpWsize() select wrong layer ID\n");
    }

}

HI_VOID VDP_DISP_SetHShrpThrd(VDP_CHN_E enLayer, HI_U8 hf0_underth, HI_U8 hf0_overth, HI_U8 hf1_underth, HI_U8 hf1_overth)
{
    U_DHD0_HSPCFG6 DHD0_HSPCFG6;
    U_DHD0_HSPCFG13 DHD0_HSPCFG13;

    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG6.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG6.u32) + CHN_OFFSET));
        DHD0_HSPCFG13.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG13.u32) + CHN_OFFSET));

        DHD0_HSPCFG6.bits.hsp_hf0_underth = hf0_underth;
        DHD0_HSPCFG6.bits.hsp_hf0_overth  = hf0_overth;
        DHD0_HSPCFG13.bits.hsp_hf1_underth = hf1_underth;
        DHD0_HSPCFG13.bits.hsp_hf1_overth  = hf1_overth;


        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG6.u32) + CHN_OFFSET), DHD0_HSPCFG6.u32);
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG13.u32) + CHN_OFFSET), DHD0_HSPCFG13.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpThrd() select wrong layer ID\n");
    }
}

HI_VOID VDP_DISP_SetHShrpMixratio(VDP_CHN_E enLayer, HI_U8 hf0_mixratio, HI_U8 hf1_mixratio)
{
    U_DHD0_HSPCFG6 DHD0_HSPCFG6;
    U_DHD0_HSPCFG13 DHD0_HSPCFG13;

    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG6.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG6.u32) + CHN_OFFSET));
        DHD0_HSPCFG13.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG13.u32) + CHN_OFFSET));

        DHD0_HSPCFG6.bits.hsp_hf0_mixratio    = hf0_mixratio;
        DHD0_HSPCFG13.bits.hsp_hf1_mixratio    = hf1_mixratio;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG6.u32) + CHN_OFFSET), DHD0_HSPCFG6.u32);
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG13.u32) + CHN_OFFSET), DHD0_HSPCFG13.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpParam() select wrong layer ID\n");
    }

}

HI_VOID VDP_DISP_SetHShrpEn(VDP_CHN_E enLayer, HI_BOOL h1_en, HI_BOOL h2_en, HI_BOOL ltih_en, HI_BOOL ctih_en)
{
    U_DHD0_HSPCFG14 DHD0_HSPCFG14;

    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG14.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG14.u32) + CHN_OFFSET));

        DHD0_HSPCFG14.bits.hsp_h0_en = h1_en;
        DHD0_HSPCFG14.bits.hsp_h1_en = h2_en;
        DHD0_HSPCFG14.bits.hsp_ltih_en = ltih_en;
        DHD0_HSPCFG14.bits.hsp_ctih_en = ctih_en;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG14.u32) + CHN_OFFSET), DHD0_HSPCFG14.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpEn() select wrong layer ID\n");
    }

}

HI_VOID VDP_DISP_SetHShrpXti(VDP_CHN_E enLayer, HI_U8 hf_shootdiv, HI_U8 lti_ratio, HI_U8 ldti_gain, HI_U8 cdti_gain)
{
    U_DHD0_HSPCFG14 DHD0_HSPCFG14;

    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG14.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG14.u32) + CHN_OFFSET));

        DHD0_HSPCFG14.bits.hsp_hf_shootdiv = hf_shootdiv;
        DHD0_HSPCFG14.bits.hsp_lti_ratio = lti_ratio;
        DHD0_HSPCFG14.bits.hsp_ldti_gain = ldti_gain;
        DHD0_HSPCFG14.bits.hsp_cdti_gain = cdti_gain;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG14.u32) + CHN_OFFSET), DHD0_HSPCFG14.u32);

    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpXti() select wrong layer ID\n");
    }

}

HI_VOID VDP_DISP_SetHShrpGlbpara(VDP_CHN_E enLayer, HI_U8 peak_ratio, HI_U16 glb_overth, HI_U16 glb_underth)
{
    U_DHD0_HSPCFG15 DHD0_HSPCFG15;

    if (enLayer == VDP_CHN_DHD1)
    {
        DHD0_HSPCFG15.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG15.u32) + CHN_OFFSET));

        DHD0_HSPCFG15.bits.hsp_peak_ratio = peak_ratio;
        DHD0_HSPCFG15.bits.hsp_glb_overth = glb_overth;
        DHD0_HSPCFG15.bits.hsp_glb_underth = glb_underth;

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_HSPCFG15.u32) + CHN_OFFSET), DHD0_HSPCFG15.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_DISP_SetHShrpReg15() select wrong layer ID\n");
    }
}

HI_VOID VDP_DISP_SetOneSyncTwoEnable   (HI_U32 u32Enable)
{
    U_VOCTRL VOCTRL;

    VOCTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOCTRL.u32)));
    VOCTRL.bits.one_sync2_en = u32Enable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOCTRL.u32)), VOCTRL.u32);
}

HI_VOID VDP_DISP_SetDhd1Select         (HI_U32 u32Data)
{
    U_VOCTRL VOCTRL;

    VOCTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOCTRL.u32)));
    VOCTRL.bits.chn2_select = u32Data;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOCTRL.u32)), VOCTRL.u32);
}
#endif

#if SR_EN
#if 0
HI_VOID VDP_DISP_SetSrMux (HI_U32 u32Data, VDP_SR_MUX_E SrMux)
{
    U_SR_CTRL  SR_CTRL;

    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetSrMux() Select Wrong Video Layer ID\n");
        return ;
    }

    SR_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_CTRL.u32) + u32Data * CHN_OFFSET));
    SR_CTRL.bits.sr_zme_en = SrMux;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_CTRL.u32) + u32Data * CHN_OFFSET), SR_CTRL.u32);
}

HI_VOID VDP_DISP_SetSrDemoCtrl (HI_U32 u32Data, VDP_SR_DEMO_E DemoCtrl)
{
    U_SR_CTRL  SR_CTRL;

    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetSrMux() Select Wrong Video Layer ID\n");
        return ;
    }

    SR_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_CTRL.u32) + u32Data * CHN_OFFSET));
    SR_CTRL.bits.demo_ctrl = DemoCtrl;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_CTRL.u32) + u32Data * CHN_OFFSET), SR_CTRL.u32);
}

HI_VOID VDP_DISP_SetSrServeMode (HI_U32 u32Data, VDP_SR_SERVE_MODE_E Mode)
{
    U_SR_CTRL  SR_CTRL;

    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetSrServeMode() Select Wrong Video Layer ID\n");
        return ;
    }

    SR_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_CTRL.u32) + u32Data * CHN_OFFSET));
    SR_CTRL.bits.serve_mode = Mode;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_CTRL.u32) + u32Data * CHN_OFFSET), SR_CTRL.u32);
}
#endif
#if 0

HI_VOID VDP_DISP_SetSrSharpenMode (HI_U32 u32Data, VDP_SR_SHARP_MODE_E Mode)
{
    U_SR_SHARP_EN  SR_SHARP_EN;

    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetSrSharpenMode() Select Wrong Video Layer ID\n");
        return ;
    }

    SR_SHARP_EN.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_SHARP_EN.u32) + u32Data * CHN_OFFSET));
    SR_SHARP_EN.bits.hsh_nodir = Mode;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_SHARP_EN.u32) + u32Data * CHN_OFFSET), SR_SHARP_EN.u32);
}

HI_VOID VDP_DISP_SetSrEiscDetailGain (HI_U32 u32Data, HI_U32 u32DetaiGain)
{
    U_SR_SHARP_EN  SR_SHARP_EN;

    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetSrEiscDetailGain() Select Wrong Video Layer ID\n");
        return ;
    }

    SR_SHARP_EN.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_SHARP_EN.u32) + u32Data * CHN_OFFSET));
    SR_SHARP_EN.bits.ensc_detail_gain = u32DetaiGain;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_SHARP_EN.u32) + u32Data * CHN_OFFSET), SR_SHARP_EN.u32);
}
#endif

#if 0
HI_VOID VDP_DISP_SetSrSharpenThrsh (HI_U32 u32Data, HI_U32 u32HighThr, HI_U32 u32LowThr)
{
    U_SR_SHARP_THR  SR_SHARP_THR;

    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetSrSharpenGain() Select Wrong Video Layer ID\n");
        return ;
    }

    SR_SHARP_THR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_SHARP_THR.u32) + u32Data * CHN_OFFSET));
    SR_SHARP_THR.bits.over_thrsh = u32HighThr;
    SR_SHARP_THR.bits.under_thrsh = u32LowThr;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_SHARP_THR.u32) + u32Data * CHN_OFFSET), SR_SHARP_THR.u32);
}
#endif
#if 0
HI_VOID VDP_DISP_SetSrHorCoef (HI_U32 u32Data, VDP_SR_HORCOEF_S stSrHorCoef)
{
    U_SR_HCOEF0    SR_HCOEF0;
    U_SR_HCOEF1    SR_HCOEF1;
    U_SR_HCOEF2    SR_HCOEF2;
    U_SR_HCOEF3    SR_HCOEF3;
    U_SR_HCOEF4    SR_HCOEF4;
    U_SR_HCOEF5    SR_HCOEF5;
    U_SR_HCOEF6    SR_HCOEF6;
    U_SR_HCOEF7    SR_HCOEF7;
    U_SR_HCOEF8    SR_HCOEF8;
    U_SR_HCOEF9    SR_HCOEF9;
    U_SR_HCOEF10   SR_HCOEF10;

    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetSrHorCoef() Select Wrong Video Layer ID\n");
        return ;
    }

    SR_HCOEF0.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF0.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF1.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF1.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF2.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF2.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF3.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF3.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF4.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF4.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF5.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF5.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF6.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF6.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF7.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF7.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF8.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF8.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF9.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF9.u32)  + u32Data * CHN_OFFSET));
    SR_HCOEF10.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_HCOEF10.u32) + u32Data * CHN_OFFSET));

    SR_HCOEF0.bits.hlcoef00 = stSrHorCoef.sr_hlcoef00;
    SR_HCOEF0.bits.hlcoef01 = stSrHorCoef.sr_hlcoef01;
    SR_HCOEF0.bits.hlcoef02 = stSrHorCoef.sr_hlcoef02;

    SR_HCOEF1.bits.hlcoef03 = stSrHorCoef.sr_hlcoef03;
    SR_HCOEF1.bits.hlcoef04 = stSrHorCoef.sr_hlcoef04;
    SR_HCOEF1.bits.hlcoef05 = stSrHorCoef.sr_hlcoef05;

    SR_HCOEF2.bits.hlcoef06 = stSrHorCoef.sr_hlcoef06;
    SR_HCOEF2.bits.hlcoef07 = stSrHorCoef.sr_hlcoef07;
    SR_HCOEF2.bits.hlcoef10 = stSrHorCoef.sr_hlcoef10;

    SR_HCOEF3.bits.hlcoef11 = stSrHorCoef.sr_hlcoef11;
    SR_HCOEF3.bits.hlcoef12 = stSrHorCoef.sr_hlcoef12;
    SR_HCOEF3.bits.hlcoef13 = stSrHorCoef.sr_hlcoef13;

    SR_HCOEF4.bits.hlcoef14 = stSrHorCoef.sr_hlcoef14;
    SR_HCOEF4.bits.hlcoef15 = stSrHorCoef.sr_hlcoef15;
    SR_HCOEF4.bits.hlcoef16 = stSrHorCoef.sr_hlcoef16;

    SR_HCOEF5.bits.hlcoef17 = stSrHorCoef.sr_hlcoef17;
    SR_HCOEF5.bits.hccoef00 = stSrHorCoef.sr_hccoef00;
    SR_HCOEF5.bits.hccoef01 = stSrHorCoef.sr_hccoef01;

    SR_HCOEF6.bits.hccoef02 = stSrHorCoef.sr_hccoef02;
    SR_HCOEF6.bits.hccoef03 = stSrHorCoef.sr_hccoef03;
    SR_HCOEF6.bits.hccoef04 = stSrHorCoef.sr_hccoef04;

    SR_HCOEF7.bits.hccoef05 = stSrHorCoef.sr_hccoef05;
    SR_HCOEF7.bits.hccoef06 = stSrHorCoef.sr_hccoef06;
    SR_HCOEF7.bits.hccoef07 = stSrHorCoef.sr_hccoef07;

    SR_HCOEF8.bits.hccoef10 = stSrHorCoef.sr_hccoef10;
    SR_HCOEF8.bits.hccoef11 = stSrHorCoef.sr_hccoef11;
    SR_HCOEF8.bits.hccoef12 = stSrHorCoef.sr_hccoef12;

    SR_HCOEF9.bits.hccoef13 = stSrHorCoef.sr_hccoef13;
    SR_HCOEF9.bits.hccoef14 = stSrHorCoef.sr_hccoef14;
    SR_HCOEF9.bits.hccoef15 = stSrHorCoef.sr_hccoef15;

    SR_HCOEF10.bits.hccoef16 = stSrHorCoef.sr_hccoef16;
    SR_HCOEF10.bits.hccoef17 = stSrHorCoef.sr_hccoef17;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF0.u32)  + u32Data * CHN_OFFSET), SR_HCOEF0.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF1.u32)  + u32Data * CHN_OFFSET), SR_HCOEF1.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF2.u32)  + u32Data * CHN_OFFSET), SR_HCOEF2.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF3.u32)  + u32Data * CHN_OFFSET), SR_HCOEF3.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF4.u32)  + u32Data * CHN_OFFSET), SR_HCOEF4.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF5.u32)  + u32Data * CHN_OFFSET), SR_HCOEF5.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF6.u32)  + u32Data * CHN_OFFSET), SR_HCOEF6.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF7.u32)  + u32Data * CHN_OFFSET), SR_HCOEF7.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF8.u32)  + u32Data * CHN_OFFSET), SR_HCOEF8.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF9.u32)  + u32Data * CHN_OFFSET), SR_HCOEF9.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_HCOEF10.u32) + u32Data * CHN_OFFSET), SR_HCOEF10.u32);

    return ;
}

HI_VOID VDP_DISP_SetSrVerCoef (HI_U32 u32Data, VDP_SR_VERCOEF_S  stSrVerCoef)
{
    U_SR_VCOEF0   SR_VCOEF0;
    U_SR_VCOEF1   SR_VCOEF1;
    U_SR_VCOEF2   SR_VCOEF2;
    U_SR_VCOEF3   SR_VCOEF3;
    U_SR_VCOEF4   SR_VCOEF4;
    U_SR_VCOEF5   SR_VCOEF5;
    U_SR_VCOEF6   SR_VCOEF6;
    U_SR_VCOEF7   SR_VCOEF7;

    if (u32Data >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetSrVerCoef() Select Wrong Video Layer ID\n");
        return ;
    }

    SR_VCOEF0.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_VCOEF0.u32)  + u32Data * CHN_OFFSET));
    SR_VCOEF1.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_VCOEF1.u32)  + u32Data * CHN_OFFSET));
    SR_VCOEF2.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_VCOEF2.u32)  + u32Data * CHN_OFFSET));
    SR_VCOEF3.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_VCOEF3.u32)  + u32Data * CHN_OFFSET));
    SR_VCOEF4.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_VCOEF4.u32)  + u32Data * CHN_OFFSET));
    SR_VCOEF5.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_VCOEF5.u32)  + u32Data * CHN_OFFSET));
    SR_VCOEF6.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_VCOEF6.u32)  + u32Data * CHN_OFFSET));
    SR_VCOEF7.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->SR_VCOEF7.u32)  + u32Data * CHN_OFFSET));

    SR_VCOEF0.bits.vlcoef00 = stSrVerCoef.sr_vlcoef00;
    SR_VCOEF0.bits.vlcoef01 = stSrVerCoef.sr_vlcoef01;
    SR_VCOEF0.bits.vlcoef02 = stSrVerCoef.sr_vlcoef02;

    SR_VCOEF1.bits.vlcoef03 = stSrVerCoef.sr_vlcoef03;
    SR_VCOEF1.bits.vlcoef04 = stSrVerCoef.sr_vlcoef04;
    SR_VCOEF1.bits.vlcoef05 = stSrVerCoef.sr_vlcoef05;

    SR_VCOEF2.bits.vlcoef10 = stSrVerCoef.sr_vlcoef10;
    SR_VCOEF2.bits.vlcoef11 = stSrVerCoef.sr_vlcoef11;
    SR_VCOEF2.bits.vlcoef12 = stSrVerCoef.sr_vlcoef12;

    SR_VCOEF3.bits.vlcoef13 = stSrVerCoef.sr_vlcoef13;
    SR_VCOEF3.bits.vlcoef14 = stSrVerCoef.sr_vlcoef14;
    SR_VCOEF3.bits.vlcoef15 = stSrVerCoef.sr_vlcoef15;

    SR_VCOEF4.bits.vccoef00 = stSrVerCoef.sr_vccoef00;
    SR_VCOEF4.bits.vccoef01 = stSrVerCoef.sr_vccoef01;
    SR_VCOEF4.bits.vccoef02 = stSrVerCoef.sr_vccoef02;

    SR_VCOEF5.bits.vccoef03 = stSrVerCoef.sr_vccoef03;
    SR_VCOEF5.bits.vccoef04 = stSrVerCoef.sr_vccoef04;
    SR_VCOEF5.bits.vccoef05 = stSrVerCoef.sr_vccoef05;

    SR_VCOEF6.bits.vccoef10 = stSrVerCoef.sr_vccoef10;
    SR_VCOEF6.bits.vccoef11 = stSrVerCoef.sr_vccoef11;
    SR_VCOEF6.bits.vccoef12 = stSrVerCoef.sr_vccoef12;

    SR_VCOEF7.bits.vccoef13 = stSrVerCoef.sr_vccoef13;
    SR_VCOEF7.bits.vccoef14 = stSrVerCoef.sr_vccoef14;
    SR_VCOEF7.bits.vccoef15 = stSrVerCoef.sr_vccoef15;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_VCOEF0.u32)  + u32Data * CHN_OFFSET), SR_VCOEF0.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_VCOEF1.u32)  + u32Data * CHN_OFFSET), SR_VCOEF1.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_VCOEF2.u32)  + u32Data * CHN_OFFSET), SR_VCOEF2.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_VCOEF3.u32)  + u32Data * CHN_OFFSET), SR_VCOEF3.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_VCOEF4.u32)  + u32Data * CHN_OFFSET), SR_VCOEF4.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_VCOEF5.u32)  + u32Data * CHN_OFFSET), SR_VCOEF5.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_VCOEF6.u32)  + u32Data * CHN_OFFSET), SR_VCOEF6.u32);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SR_VCOEF7.u32)  + u32Data * CHN_OFFSET), SR_VCOEF7.u32);

    return ;
}
#endif
#endif

HI_VOID VDP_DISP_SetNxgDataSwapEnable(HI_U32 u32hd_id, HI_U32 enable)
{
    U_DHD0_CTRL DHD0_CTRL;
    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_SetPlusPhase Select Wrong CHANNEL ID\n");
        return ;
    }
    DHD0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET));
    DHD0_CTRL.bits.fpga_lmt_en = enable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->DHD0_CTRL.u32) + u32hd_id * CHN_OFFSET), DHD0_CTRL.u32);
}

HI_VOID VDP_DISP_GetVactState(HI_U32 u32hd_id, HI_BOOL *pbBtm, HI_U32 *pu32Vcnt)
{
    U_DHD0_STATE DHD0_STATE;

    if (u32hd_id >= CHN_MAX)
    {
        VDP_PRINT("Error,VDP_DISP_GetVactState Select Wrong CHANNEL ID\n");
        return ;
    }

    //Set Vou Dhd Channel Gamma Correct Enable
    DHD0_STATE.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->DHD0_STATE.u32) + u32hd_id * CHN_OFFSET));
    *pbBtm   = DHD0_STATE.bits.bottom_field;
    *pu32Vcnt = DHD0_STATE.bits.vcnt;

    return;
}
