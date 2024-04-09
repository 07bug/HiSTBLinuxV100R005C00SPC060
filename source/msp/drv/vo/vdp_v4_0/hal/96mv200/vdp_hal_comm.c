#include "vdp_define.h"
#include "vdp_hal_comm.h"
#include "vdp_dm_typefxp.h"
#if VDP_CBB_FPGA
#include "vdp_fpga_define.h"
#endif
#if ESL_TEST
#define SYS_TEST       1
#else
#define SYS_TEST       0
#endif

#if EDA_TEST
#define CPP_MODE 1
#else
#define CPP_MODE 0
#endif

#if EDA_TEST
#include "vdp_fun.h"
S_VDP_REGS_TYPE *pVdpReg = new S_VDP_REGS_TYPE;
extern Driver *u_drv;
#if (!BT_TEST & !FPGA_TEST)
extern ahb_bus_sys *u_ahb_drv;
#endif

#else//FPGA_TEST

S_VDP_REGS_TYPE *pVdpReg;
#if VDP_CBB_FPGA
//  #include "vdp_util.h"
extern char cOfName[256];
extern char cIfName[256];
//extern  volatile HI_U32 g_pOptmRegVirAddrTnrSnrDbm ;
extern  volatile HI_U32 g_pOptmRegVirAddrDci ;

extern  HI_VOID reg2txt_zjy(HI_U32 *a, HI_U32 b, HI_UCHAR *Filename);
#endif

#endif//EDA_TEST


//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
#if  0
HI_U32 VDP_RegRead(volatile HI_U32 *a)
{

#if EDA_TEST
    HI_U32 offset = (HI_U64)a - (HI_U64)pVdpReg;

#if SYS_TEST
    cout << hex << "cpu_read(0x" << setw(8) << setfill('0') << offset << ");" << endl;
#endif
    return u_drv->apb_read(VDP_BASE_ADDR + offset);
#elif VDP_CBB_FPGA
    //for VPSS reg access
    //if((offset>= 0xd800) && (offset < 0xf000))
    {
        //return *(g_pOptmRegVirAddrTnrSnrDbm +(offset-0xd800)) ;
    }
    // else
    {
        return (*(a));
    }
#else
    return (*(a));
#endif

}
#endif

HI_U32 VDP_RegRead(HI_ULONG a)
{
    return (*((volatile HI_U32 *)a));
}
#if  0
HI_VOID VDP_RegWrite(volatile HI_U32 *a, HI_U32 b)
{

    //  HI_U32 offset = (HI_U64)a - (HI_U64)pVdpReg;
    HI_U32 *pu32Src;
    HI_U64 offset ;
    pu32Src = (HI_U32 *)pVdpReg;
    offset = (HI_U64)(a - pu32Src);
    offset = offset * 4;
#if EDA_TEST
    u_drv->apb_write(VDP_BASE_ADDR + offset, b); // DUT cfg
#endif

#if VDP_CBB_FPGA
    //for VPSS reg access
    if ((offset >= 0xd800) && (offset < 0xf000))
    {
        //*(g_pOptmRegVirAddrTnrSnrDbm +(offset-0xd800))  = b;
    }
    else
    {
        *a = b;
    }
#else
    *a = b;       // ENV cfg
#endif

#if REG_LOG_ZJY
    reg2txt_zjy((HI_U32 *) ((HI_U32)a & 0xffff), b, "reg_vdp_g0_bbc");
#endif


    /*
    #if REG_LOG
        reg2txt((HI_U32 *) ((HI_U32)a&0xffff), b, "Tc002_ar_p_v0_sdk_test_01_2.regcfg");
    #endif
    */

#if SYS_TEST
    cout << hex << "cpu_write( 0x" << setw(8) << setfill('0') << offset << ", 0x" << b << ");" << endl;
#endif
    return ;
}
#endif
HI_VOID VDP_RegWrite(HI_ULONG  a, HI_U32 b)
{
    *((volatile HI_U32 *)a) = b;
    return ;
}

#if FPGA_TEST
extern HI_VOID reg2txt(HI_U32 *a, HI_U32 b, HI_UCHAR *Filename);
#endif


//--------------FPGA DEBUG------------//

#if 0//FPGA_DEBUG_STEP
HI_VOID VDP_SetVdpFpgaDebugWrite(HI_U32 u32Data)
{
    U_VOFPGATEST  VOFPGATEST;

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOFPGATEST.u32)), u32Data);
}
HI_S32 VDP_SetVdpFpgaDebugRead(HI_VOID)
{
    U_VOFPGATEST  VOFPGATEST;

    return VDP_RegRead(((HI_ULONG) & (pVdpReg->VOFPGATEST.u32)));
}
#endif

//--------------------------------------------------------------------
// AXI BUS BEING
//--------------------------------------------------------------------

HI_VOID VDP_SetVDPMemLowPower(HI_VOID)
{
    U_VOLOWPOWER_CTRL VOLOWPOWER_CTRL;

    VOLOWPOWER_CTRL.u32 = 0x00005b2b;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOLOWPOWER_CTRL.u32)), VOLOWPOWER_CTRL.u32);
}

HI_VOID VDP_SetClkGateEn(HI_U32 u32Data)
{
    U_VOCTRL VOCTRL;

    VOCTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOCTRL.u32)));
    VOCTRL.bits.vo_ck_gt_en = u32Data;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOCTRL.u32)), VOCTRL.u32);
}

HI_VOID VDP_SetWrOutStd(HI_U32 u32Data, HI_U32 u32BusId, HI_U32 u32OutStd)
{
    U_VOAXICTRL  VOAXICTRL;
    U_VOAXICTRL1 VOAXICTRL1;

    if (u32Data == VDP_MASTER0)
    {
        if (u32BusId == 0)
        {
            VOAXICTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)));
            VOAXICTRL.bits.m0_wr_ostd = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)), VOAXICTRL.u32);
        }
        else
        {
            VDP_PRINT("Error,VDP_SetWrOutStd() Select Wrong Bus Id,Wr Support one id!\n");
        }
    }
    else if (u32Data == VDP_MASTER1)
    {
        if (u32BusId == 0)
        {
            VOAXICTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)));
            VOAXICTRL.bits.m1_wr_ostd = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)), VOAXICTRL.u32);
        }
        else
        {
            VDP_PRINT("Error,VDP_SetWrOutStd() Select Wrong Bus Id,Wr Support one id!\n");
        }
    }
    else if (u32Data == VDP_MASTER2)
    {
        if (u32BusId == 0)
        {
            VOAXICTRL1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)));
            VOAXICTRL1.bits.m2_wr_ostd = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)), VOAXICTRL1.u32);
        }
        else
        {
            VDP_PRINT("Error,VDP_SetWrOutStd() Select Wrong Bus Id,Wr Support one id!\n");
        }
    }
    else if (u32Data == VDP_MASTER3)
    {
        if (u32BusId == 0)
        {
            VOAXICTRL1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)));
            VOAXICTRL1.bits.m3_wr_ostd = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)), VOAXICTRL1.u32);
        }
        else
        {
            VDP_PRINT("Error,VDP_SetWrOutStd() Select Wrong Bus Id,Wr Support one id!\n");
        }
    }
    else
    {
        VDP_PRINT("Error,VDP_SetWrOutStd() Select Wrong Master!\n");
    }

    return ;
}

HI_VOID VDP_SetRdOutStd(HI_U32 u32Data, HI_U32 u32BusId, HI_U32 u32OutStd)
{
    U_VOAXICTRL  VOAXICTRL;
    U_VOAXICTRL1 VOAXICTRL1;

    if (u32Data == VDP_MASTER0)
    {
        if (u32BusId == 0)
        {
            VOAXICTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)));
            VOAXICTRL.bits.m0_outstd_rid0 = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)), VOAXICTRL.u32);
        }
        else if (u32BusId == 1)
        {
            VOAXICTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)));
            VOAXICTRL.bits.m0_outstd_rid1 = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)), VOAXICTRL.u32);
        }
        else
        {
            VDP_PRINT("Error,VDP_SetRdOutStd() Select Wrong Bus Id,Rd Support two id!\n");
        }
    }
    else if (u32Data == VDP_MASTER1)
    {
        if (u32BusId == 0)
        {
            VOAXICTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)));
            VOAXICTRL.bits.m1_outstd_rid0 = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)), VOAXICTRL.u32);
        }
        else if (u32BusId == 1)
        {
            VOAXICTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)));
            VOAXICTRL.bits.m1_outstd_rid1 = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)), VOAXICTRL.u32);
        }
        else
        {
            VDP_PRINT("Error,VDP_SetRdOutStd() Select Wrong Bus Id,Rd Support two id!\n");
        }
    }
    else if (u32Data == VDP_MASTER2)
    {
        if (u32BusId == 0)
        {
            VOAXICTRL1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)));
            VOAXICTRL1.bits.m2_outstd_rid0 = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)), VOAXICTRL1.u32);
        }
        else if (u32BusId == 1)
        {
            VOAXICTRL1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)));
            VOAXICTRL1.bits.m2_outstd_rid1 = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)), VOAXICTRL1.u32);
        }
        else
        {
            VDP_PRINT("Error,VDP_SetRdOutStd() Select Wrong Bus Id,Rd Support two id!\n");
        }
    }
    else if (u32Data == VDP_MASTER3)
    {
        if (u32BusId == 0)
        {
            VOAXICTRL1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)));
            VOAXICTRL1.bits.m3_outstd_rid0 = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)), VOAXICTRL1.u32);
        }
        else if (u32BusId == 1)
        {
            VOAXICTRL1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)));
            VOAXICTRL1.bits.m3_outstd_rid1 = u32OutStd;
            VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL1.u32)), VOAXICTRL1.u32);
        }
        else
        {
            VDP_PRINT("Error,VDP_SetRdOutStd() Select Wrong Bus Id,Rd Support two id!\n");
        }
    }
    else
    {
        VDP_PRINT("Error,VDP_SetWrOutStd() Select Wrong Master!\n");
    }

    return ;
}

HI_VOID VDP_SetRdMultiIdEnable(HI_U32 u32Data, HI_U32 u32Enable)
{
    U_VOAXICTRL  VOAXICTRL;

    if (u32Data == VDP_MASTER0)
    {
        VOAXICTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)));
        VOAXICTRL.bits.m0_mutli_id_o = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)), VOAXICTRL.u32);
    }
    else if (u32Data == VDP_MASTER1)
    {
        VOAXICTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)));
        VOAXICTRL.bits.m1_mutli_id_o = u32Enable;
        VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOAXICTRL.u32)), VOAXICTRL.u32);
    }
    else
    {
        VDP_PRINT("Error,VDP_SetRdMultiIdEnable() Select Wrong Master!\n");
    }

    return ;
}

HI_VOID VDP_SetAxiMidEnable  (HI_U32 u32Enable)
{
    U_VOMIDORDER    VOMIDORDER;

    VOMIDORDER.u32  = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOMIDORDER.u32)));
    VOMIDORDER.bits.mid_enable = u32Enable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOMIDORDER.u32)), VOMIDORDER.u32);

    return ;
}

HI_VOID VDP_VID_SetReqCtrl(HI_U32 u32Data, HI_U32 u32ReqCtrl)
{
    U_V0_CTRL V0_CTRL;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetReqCtrl() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.req_ctrl = u32ReqCtrl;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}
HI_VOID VDP_GFX_SetReqCtrl(HI_U32 u32Data, HI_U32 u32ReqCtrl)
{
    U_G0_CTRL G0_CTRL;

    if (u32Data >= GFX_MAX)
    {
        VDP_PRINT("Error,VDP_GFX_SetReqCtrl() Select Wrong Video Layer ID\n");
        return ;
    }

    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.req_ctrl = u32ReqCtrl;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);

    return ;
}
//--------------------------------------------------------------------
// AXI BUS END
//--------------------------------------------------------------------

#if 0

HI_VOID VDP_HDATE_SetVdacDetEnable(HI_U32 u32Data)
{
    U_HDATE_DACDET2 HDATE_DACDET2 ;

    HDATE_DACDET2.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->HDATE_DACDET2.u32));
    HDATE_DACDET2.bits.vdac_det_en = u32Data;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->HDATE_DACDET2.u32), HDATE_DACDET2.u32);

    return ;
}

HI_VOID VDP_HDATE_SetVdacDetLine(HI_U32 u32Data)
{
    U_HDATE_DACDET1 HDATE_DACDET1 ;

    HDATE_DACDET1.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->HDATE_DACDET1.u32));
    HDATE_DACDET1.bits.det_line = u32Data;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->HDATE_DACDET1.u32), HDATE_DACDET1.u32);

    return ;
}

HI_VOID VDP_HDATE_SetVdacDetHigh(HI_U32 u32Data)
{
    U_HDATE_DACDET1 HDATE_DACDET1 ;

    HDATE_DACDET1.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->HDATE_DACDET1.u32));
    HDATE_DACDET1.bits.vdac_det_high = u32Data;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->HDATE_DACDET1.u32), HDATE_DACDET1.u32);

    return ;
}

HI_VOID VDP_HDATE_SetVdacDetWidth(HI_U32 u32Data)
{
    U_HDATE_DACDET2 HDATE_DACDET2 ;

    HDATE_DACDET2.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->HDATE_DACDET2.u32));
    HDATE_DACDET2.bits.det_pixel_wid = u32Data;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->HDATE_DACDET2.u32), HDATE_DACDET2.u32);

    return ;
}

HI_VOID VDP_HDATE_SetVdacDetStart(HI_U32 u32Data)
{
    U_HDATE_DACDET2 HDATE_DACDET2 ;

    HDATE_DACDET2.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->HDATE_DACDET2.u32));
    HDATE_DACDET2.bits.det_pixel_sta = u32Data;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->HDATE_DACDET2.u32), HDATE_DACDET2.u32);

    return ;
}
#endif

#if 0
HI_VOID VDP_SDATE_SetVdacDetLine(HI_U32 u32Data)
{
    U_DATE_DACDET1 DATE_DACDET1 ;

    DATE_DACDET1.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->DATE_DACDET1.u32));
    DATE_DACDET1.bits.det_line = u32Data;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->DATE_DACDET1.u32), DATE_DACDET1.u32);

    return ;
}

HI_VOID VDP_SDATE_SetVdacDetHigh(HI_U32 u32Data)
{
    U_DATE_DACDET1 DATE_DACDET1 ;

    DATE_DACDET1.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->DATE_DACDET1.u32));
    DATE_DACDET1.bits.vdac_det_high = u32Data;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->DATE_DACDET1.u32), DATE_DACDET1.u32);

    return ;
}

HI_VOID VDP_SDATE_SetVdacDetWidth(HI_U32 u32Data)
{
    U_DATE_DACDET2 DATE_DACDET2 ;

    DATE_DACDET2.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->DATE_DACDET2.u32));
    DATE_DACDET2.bits.det_pixel_wid = u32Data;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->DATE_DACDET2.u32), DATE_DACDET2.u32);

    return ;
}

HI_VOID VDP_SDATE_SetVdacDetStart(HI_U32 u32Data)
{
    U_DATE_DACDET2 DATE_DACDET2 ;

    DATE_DACDET2.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->DATE_DACDET2.u32));
    DATE_DACDET2.bits.det_pixel_sta = u32Data;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->DATE_DACDET2.u32), DATE_DACDET2.u32);

    return ;
}

#endif

HI_VOID VDP_CBM_SetMixerBkg(VDP_CBM_MIX_E u32mixer_id, VDP_BKG_S stBkg)
{
    U_CBM_BKG1 CBM_BKG1;
    U_CBM_BKG2 CBM_BKG2;
    U_CBM_BKG3 CBM_BKG3;

    if (u32mixer_id == VDP_CBM_MIX0)
    {
        /* DHD0  mixer link */
        CBM_BKG1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_BKG1.u32)));
        CBM_BKG1.bits.cbm_bkgy1  = stBkg.u32BkgY;
        CBM_BKG1.bits.cbm_bkgcb1 = stBkg.u32BkgU;
        CBM_BKG1.bits.cbm_bkgcr1 = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG) & (pVdpReg->CBM_BKG1.u32), CBM_BKG1.u32);
    }
    else if (u32mixer_id == VDP_CBM_MIX1)
    {
        CBM_BKG2.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_BKG2.u32)));
        CBM_BKG2.bits.cbm_bkgy2  = stBkg.u32BkgY;
        CBM_BKG2.bits.cbm_bkgcb2 = stBkg.u32BkgU;
        CBM_BKG2.bits.cbm_bkgcr2 = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG) & (pVdpReg->CBM_BKG2.u32), CBM_BKG2.u32);
    }
    else if (u32mixer_id == VDP_CBM_MIX2)
    {
        /* DHD1 mixer link */
        CBM_BKG3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_BKG3.u32)));
        CBM_BKG3.bits.cbm_bkgy3  = stBkg.u32BkgY;
        CBM_BKG3.bits.cbm_bkgcb3 = stBkg.u32BkgU;
        CBM_BKG3.bits.cbm_bkgcr3 = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG) & (pVdpReg->CBM_BKG3.u32), CBM_BKG3.u32);
    }
#if SD0_EN
    else if (u32mixer_id == VDP_CBM_MIX2)
    {
        U_MIXDSD_BKG MIXDSD_BKG;
        /* DSD mixer link */
        MIXDSD_BKG.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXDSD_BKG.u32)));
        MIXDSD_BKG.bits.mixer_bkgy  = stBkg.u32BkgY;
        MIXDSD_BKG.bits.mixer_bkgcb = stBkg.u32BkgU;
        MIXDSD_BKG.bits.mixer_bkgcr = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG) & (pVdpReg->MIXDSD_BKG.u32), MIXDSD_BKG.u32);


    }
#endif

#if MIXG_EN
    else if (u32mixer_id == VDP_CBM_MIXG0)
    {
        U_MIXG0_BKG MIXG0_BKG;
        U_MIXG0_BKALPHA MIXG0_BKALPHA;
        /* G0 mixer link */
        MIXG0_BKG.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXG0_BKG.u32)));
        MIXG0_BKG.bits.mixer_bkgy  = stBkg.u32BkgY;
        MIXG0_BKG.bits.mixer_bkgcb = stBkg.u32BkgU;
        MIXG0_BKG.bits.mixer_bkgcr = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG) & (pVdpReg->MIXG0_BKG.u32), MIXG0_BKG.u32);

        MIXG0_BKALPHA.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXG0_BKALPHA.u32)));
        MIXG0_BKALPHA.bits.mixer_alpha  = stBkg.u32BkgA;
        VDP_RegWrite((HI_ULONG) & (pVdpReg->MIXG0_BKALPHA.u32), MIXG0_BKALPHA.u32);
    }
    else if (u32mixer_id == VDP_CBM_MIXV0)
    {
        U_MIXV0_BKG MIXV0_BKG;
        MIXV0_BKG.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXV0_BKG.u32)));
        MIXV0_BKG.bits.mixer_bkgy  = stBkg.u32BkgY;
        MIXV0_BKG.bits.mixer_bkgcb = stBkg.u32BkgU;
        MIXV0_BKG.bits.mixer_bkgcr = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG) & (pVdpReg->MIXV0_BKG.u32), MIXV0_BKG.u32);
    }
#endif
    else
    {
        VDP_PRINT("Error! VDP_CBM_SetMixerBkg() Select Wrong mixer ID\n");
    }

    return ;
}

HI_VOID VDP_CBM_Clear_MixvPrio(HI_U32 u32layer_id)
{
    U_MIXV0_MIX MIXV0_MIX;
    MIXV0_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXV0_MIX.u32)));

    if (MIXV0_MIX.bits.mixer_prio0 == (u32layer_id + 1))
    {
        MIXV0_MIX.bits.mixer_prio0 = 0;
    }

    if (MIXV0_MIX.bits.mixer_prio1 == (u32layer_id + 1))
    {
        MIXV0_MIX.bits.mixer_prio1 = 0;
    }

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXV0_MIX.u32)), MIXV0_MIX.u32);

    return;
}

HI_VOID VDP_CBM_SetMixerPrio(VDP_CBM_MIX_E u32mixer_id, HI_U32 u32layer_id, HI_U32 u32prio)
{
    U_CBM_MIX1 CBM_MIX1;
    //U_CBM_MIX2 CBM_MIX2;
    U_CBM_MIX3 CBM_MIX3;
    //HI_U32     u32Layer;


    if (u32mixer_id == VDP_CBM_MIX0) //DHD0
    {
        switch (u32prio)
        {
            case 0:
            {
                CBM_MIX1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX1.u32)));
                CBM_MIX1.bits.mixer_prio0 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX1.u32)), CBM_MIX1.u32);
                break;
            }
            case 1:
            {
                CBM_MIX1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX1.u32)));
                CBM_MIX1.bits.mixer_prio1 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX1.u32)), CBM_MIX1.u32);
                break;
            }
#if 0
            //only 2 layers in mixer when vp & gp is enabled
            case 2:
            {
                CBM_MIX1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX1.u32)));
                CBM_MIX1.bits.mixer_prio2 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX1.u32)), CBM_MIX1.u32);
                break;
            }
            case 3:
            {
                CBM_MIX1.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX1.u32)));
                CBM_MIX1.bits.mixer_prio3 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX1.u32)), CBM_MIX1.u32);
                break;
            }
#endif
            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }

        }
    }
#if MIXG_EN
    else if (u32mixer_id == VDP_CBM_MIXG0)
    {
        U_MIXG0_MIX MIXG0_MIX;
        switch (u32prio)
        {
            case 0:
            {
                MIXG0_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio0 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }
            case 1:
            {
                MIXG0_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio1 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }
            case 2:
            {
                MIXG0_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio2 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }
            case 3:
            {
                MIXG0_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio3 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }
            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }

        }
    }
    else if (u32mixer_id == VDP_CBM_MIXG1)
        ;
    else if (u32mixer_id == VDP_CBM_MIXV0)
    {
        U_MIXV0_MIX MIXV0_MIX;
        switch (u32prio)
        {
            case 0:
            {
                MIXV0_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXV0_MIX.u32)));
                MIXV0_MIX.bits.mixer_prio0 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXV0_MIX.u32)), MIXV0_MIX.u32);
                break;
            }
            case 1:
            {
                MIXV0_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXV0_MIX.u32)));
                MIXV0_MIX.bits.mixer_prio1 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXV0_MIX.u32)), MIXV0_MIX.u32);
                break;
            }
            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }

        }
    }
    else if (u32mixer_id == VDP_CBM_MIXV1)
        ;
#endif
#if 0//for STB/BVT
    else if (u32mixer_id == VDP_CBM_MIX1) //DHD1
    {
        switch (u32prio)
        {
            case 0:
            {
                CBM_MIX2.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX2.u32)));
                CBM_MIX2.bits.mixer_prio0 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX2.u32)), CBM_MIX2.u32);
                break;
            }
            case 1:
            {
                CBM_MIX2.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX2.u32)));
                CBM_MIX2.bits.mixer_prio1 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX2.u32)), CBM_MIX2.u32);
                break;
            }
            //mask by hyx
            //case 2:
            //{
            //  CBM_MIX2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->CBM_MIX2.u32)));
            //  CBM_MIX2.bits.mixer_prio2 = u32layer_id;
            //  VDP_RegWrite(((HI_ULONG)&(pVdpReg->CBM_MIX2.u32)), CBM_MIX2.u32);
            //  break;
            //}
            //case 3:
            //{
            //  CBM_MIX2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->CBM_MIX2.u32)));
            //  CBM_MIX2.bits.mixer_prio3 = u32layer_id;
            //  VDP_RegWrite(((HI_ULONG)&(pVdpReg->CBM_MIX2.u32)), CBM_MIX2.u32);
            //  break;
            //}
            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }


        }
    }
#endif
    else if (u32mixer_id == VDP_CBM_MIX2) //DHD1
    {
        switch (u32prio)
        {
            case 0:
            {
                CBM_MIX3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX3.u32)));
                CBM_MIX3.bits.mixer_prio0 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX3.u32)), CBM_MIX3.u32);
                break;
            }
            case 1:
            {
                CBM_MIX3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX3.u32)));
                CBM_MIX3.bits.mixer_prio1 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX3.u32)), CBM_MIX3.u32);
                break;
            }
            //case 2:
            //{
            //  CBM_MIX3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->CBM_MIX3.u32)));
            //  CBM_MIX3.bits.mixer_prio2 = u32layer_id;
            //  VDP_RegWrite(((HI_ULONG)&(pVdpReg->CBM_MIX3.u32)), CBM_MIX3.u32);
            //  break;
            //}
            //case 3:
            //{
            //  CBM_MIX3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->CBM_MIX3.u32)));
            //  CBM_MIX3.bits.mixer_prio3 = u32layer_id;
            //  VDP_RegWrite(((HI_ULONG)&(pVdpReg->CBM_MIX3.u32)), CBM_MIX3.u32);
            //  break;
            //}
            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }


        }
    }
#if SD0_EN
    else if (u32mixer_id == VDP_CBM_MIX2) //DSD
    {
        U_MIXDSD_MIX MIXDSD_MIX;
        switch (u32prio)
        {
            case 0:
            {
                MIXDSD_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXDSD_MIX.u32)));
                MIXDSD_MIX.bits.mixer_prio0 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXDSD_MIX.u32)), MIXDSD_MIX.u32);
                break;
            }
            case 1:
            {
                MIXDSD_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXDSD_MIX.u32)));
                MIXDSD_MIX.bits.mixer_prio1 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXDSD_MIX.u32)), MIXDSD_MIX.u32);
                break;
            }
            case 2:
            {
                MIXDSD_MIX.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXDSD_MIX.u32)));
                MIXDSD_MIX.bits.mixer_prio2 = u32layer_id;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXDSD_MIX.u32)), MIXDSD_MIX.u32);
                break;
            }
            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }
        }


    }
#endif
#if 0
    else if (u32mixer_id == VDP_CBM_MIX2) //MIX_4K
    {
        if (u32layer_id == VDP_CBM_CBM)
        {
            u32Layer = 1;
        }
        else if (u32layer_id == VDP_CBM_GFX3) //hc
        {
            u32Layer = 2;
        }
        else
        {
            u32Layer = 0;
        }

        switch (u32prio)
        {
            case 0:
            {
                CBM_MIX3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX3.u32)));
                CBM_MIX3.bits.mixer_prio0 = u32Layer;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX3.u32)), CBM_MIX3.u32);
                break;
            }
            case 1:
            {
                CBM_MIX3.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->CBM_MIX3.u32)));
                CBM_MIX3.bits.mixer_prio1 = u32Layer;
                VDP_RegWrite(((HI_ULONG) & (pVdpReg->CBM_MIX3.u32)), CBM_MIX3.u32);
                break;
            }
            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }


        }
    }
#endif


}

HI_VOID VDP_SetCheckSumEnable(HI_U32  bEnable)
{
    U_VOCTRL  VOCTRL;

    VOCTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOCTRL.u32)));
    VOCTRL.bits.chk_sum_en = bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOCTRL.u32)), VOCTRL.u32);
}

HI_VOID VDP_SetTwoChnEnable(HI_U32 bEnable)
{
    U_VOCTRL  VOCTRL;

    VOCTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOCTRL.u32)));
    VOCTRL.bits.twochn_en = bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOCTRL.u32)), VOCTRL.u32);
}

HI_VOID VDP_SetTwoChnMode(HI_U32 u32Data)
{
    U_VOCTRL  VOCTRL;

    VOCTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->VOCTRL.u32)));
    VOCTRL.bits.twochn_mode = u32Data;//in HiFoneB02 twochn_mode = 1 only
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->VOCTRL.u32)), VOCTRL.u32);

}

