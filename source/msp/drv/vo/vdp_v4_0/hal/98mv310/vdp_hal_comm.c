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
// $Log: vdp_driver.cpp,v $
//
//
//
//
//**********************************************************************
#include "vdp_hal_comm.h"

volatile S_VDP_REGS_TYPE* pVdpReg;
extern volatile HI_U32 g_pOptmRegVirAddrDci ;
//extern MMZ_BUFFER_S  gstVdpRegMem[XDP_REGMEM_ID_BUTT];
extern HI_U32 VDP_FhdShpVirAddr;
extern HI_U32 VDP_MrgVirAddr;


//----------------------------------------------------------------------
//REG WR RD
//----------------------------------------------------------------------
HI_U32 VDP_RegRead(HI_ULONG a)
{
	HI_ULONG addr = VDP_BASE_ADDR + a - ((HI_ULONG)&(pVdpReg->VOCTRL.u32));
	if ((addr >= 0xf8cca000) && (addr <= 0xf8cca0c0))
	{
    	addr = (addr - 0xf8cca000 +  (HI_ULONG)VDP_MrgVirAddr);
        return (*((volatile HI_U32 *)addr));
	}
    else
    {
	    return (*((volatile HI_U32 *)a));
    }
}

HI_VOID VDP_RegWrite(HI_ULONG  a, HI_U32 b)
{
	HI_ULONG addr = VDP_BASE_ADDR + a - ((HI_ULONG)&(pVdpReg->VOCTRL.u32));
    *((volatile HI_U32 *)a) = b;

	if ((addr >= 0xf8cca000) && (addr <= 0xf8cca0c0))
	{
    	addr = (addr - 0xf8cca000 + (HI_ULONG)VDP_MrgVirAddr );
    	//printk("addr = %x\n",(int)addr);
        *((volatile HI_U32 *)addr) = b;
    	//printk("addr = %p  ,  b = %x \n",paddr,b);
	}
    return ;
}

#if 0
HI_U32 VDP_RegRead(volatile HI_U32* a)
{
	HI_U32 addr = VDP_BASE_ADDR + (HI_U32)a - (HI_U32)((HI_ULONG)&(pVdpReg->VOCTRL.u32));
	if ((addr >= 0xf8cc7004) && (addr <= 0xf8cc704c))
	{
    	addr = (addr - 0xf8cc7004 +  VDP_FhdShpVirAddr);
    	//printk("addr = %x\n",addr);
    	a = (HI_U32*)addr;
	}
	if ((addr >= 0xf8cca000) && (addr <= 0xf8cca0c0))
	{
    	addr = (addr - 0xf8cca000 +  VDP_MrgVirAddr);
    	//printk("addr = %x\n",addr);
    	a = (HI_U32*)addr;
	}
    return (*(a));
}

HI_VOID VDP_RegWrite(volatile HI_U32* a, HI_U32 b)
{
    //HI_U32 *pu32RegBegin;
    //HI_U32 u64Regoffset ;
	HI_U32 *paddr;
	HI_U32 addr = VDP_BASE_ADDR + (HI_U32)a - (HI_U32)((HI_ULONG)&(pVdpReg->VOCTRL.u32));
    *a = b;

	if ((addr >= 0xf8cc7004) && (addr <= 0xf8cc704c))
	{
    	addr = (addr - 0xf8cc7004 + VDP_FhdShpVirAddr );
    	//printk("addr = %x\n",addr);
    	paddr = (HI_U32*)addr;
    	*paddr = b;
    	//printk("addr = %p  ,  b = %x \n",paddr,b);
	}
	if ((addr >= 0xf8cca000) && (addr <= 0xf8cca0c0))
	{
    	addr = (addr - 0xf8cca000 + VDP_MrgVirAddr );
    	//printk("addr = %x\n",addr);
    	paddr = (HI_U32*)addr;
    	*paddr = b;
    	//printk("addr = %p  ,  b = %x \n",paddr,b);
	}

#if 0
    pu32RegBegin = (HI_U32 *)pVdpReg ;
    u64Regoffset = (HI_U32)((HI_U32 *)a - pu32RegBegin);
    u64Regoffset = u64Regoffset * 4;

    *(HI_U32 *)(gstVdpRegMem[XDP_REGMEM_ID0].pu8StartVirAddr + u64Regoffset) = b;
#endif
    return ;
}
#endif

HI_U32 VDP_DdrRead(volatile HI_U32* a)
{
//	HI_U32 *pu32RegBegin;
//	HI_U32 u64Regoffset ;
//
//	pu32RegBegin = (HI_U32 *)pVdpReg ;
//	u64Regoffset = (HI_U32)((HI_U32 *)a - pu32RegBegin);
//	u64Regoffset = u64Regoffset * 4;
//	return (*(HI_U32 *)(gstVdpRegMem[XDP_REGMEM_ID0].pu8StartVirAddr + u64Regoffset));
return HI_SUCCESS;

}


HI_U32 VDP_RegReadEx(HI_U32 a)
{
    return HI_SUCCESS;
}


HI_VOID VDP_RegWriteEx(HI_U32 a, HI_U32 b)
{

}

#ifndef __DISP_PLATFORM_BOOT__
HI_S32 XDP_CalcRunTime(HI_VOID)
{
    HI_ULONG ulTimeusec;
    struct timeval stTime;
    do_gettimeofday(&stTime);
    ulTimeusec = stTime.tv_usec;
    return ulTimeusec;
}
#endif

//--------------------------------------------------------------------
// FPGA DEBUG
//--------------------------------------------------------------------
HI_VOID VDP_SetVdpFpgaDebugWrite(HI_U32 u32Data)
{
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VOFPGATEST.u32)), u32Data);
}

HI_S32 VDP_SetVdpFpgaDebugRead(HI_VOID)
{
    return VDP_RegRead(((HI_ULONG)&(pVdpReg->VOFPGATEST.u32)));
}


//--------------------------------------------------------------------
// AXI BUS BEING
//--------------------------------------------------------------------
HI_VOID VDP_SetVDPMemLowPower(HI_VOID)
{
    /*U_VOLOWPOWER_CTRL VOLOWPOWER_CTRL;

    VOLOWPOWER_CTRL.u32 = 0x00005b2b;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VOLOWPOWER_CTRL.u32)), VOLOWPOWER_CTRL.u32);*/
}

HI_VOID VDP_SetClkGateEn(HI_U32 u32Data)
{
    U_VOCTRL VOCTRL;

    VOCTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VOCTRL.u32)));
    VOCTRL.bits.vo_ck_gt_en = u32Data;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VOCTRL.u32)), VOCTRL.u32);
}

HI_VOID VDP_SetWrOutStd(HI_U32 u32Data, HI_U32 u32BusId, HI_U32 u32OutStd)
{
    VDP_MASTER_SetMstr0Woutstanding (  u32OutStd);
    return ;
}

HI_VOID VDP_SetRdOutStd(HI_U32 u32Data, HI_U32 u32BusId, HI_U32 u32OutStd)
{
    VDP_MASTER_SetMstr0Routstanding (  u32OutStd);
    return ;
}


HI_VOID VDP_SetArbMode(HI_U32 u32Data, HI_U32 u32bMode)
{
    HI_U32 u32ArbMode = !(u32bMode & 0x2 >> 1);
    VDP_MASTER_SetArbMode           (  u32ArbMode);
    return ;
}

HI_VOID VDP_SetRdMultiIdEnable(HI_U32 u32Data, HI_U32 u32Enable)
{
    VDP_MASTER_SetMidEnable         (  u32Enable);
    return ;
}

HI_VOID VDP_SetParaMasterSel  (HI_U32 u32MasterNum)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_SetAxiMidEnable  (HI_U32 u32Enable)
{
    VDP_MASTER_SetMidEnable         (  u32Enable);
    return ;
}

HI_VOID VDP_SetAxiEdgeMode  (VDP_AXI_EDGE_MODE_E EdgeMode)
{
    HI_U32 u32SplitMode = (EdgeMode == VDP_AXI_EDGE_MODE_4096) ? 4 : 1;
    VDP_MASTER_SetSplitMode         (  u32SplitMode);
    return ;
}

HI_VOID VDP_CBM_SetMixerBkg(VDP_CBM_MIX_E u32mixer_id, VDP_BKG_S stBkg)
{
    U_CBM_BKG1 CBM_BKG1;

    if (u32mixer_id == VDP_CBM_MIX0)
    {
        /* DHD0  mixer link */
        CBM_BKG1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->CBM_BKG1.u32)));
        CBM_BKG1.bits.cbm_bkgy1  = stBkg.u32BkgY;
        CBM_BKG1.bits.cbm_bkgcb1 = stBkg.u32BkgU;
        CBM_BKG1.bits.cbm_bkgcr1 = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->CBM_BKG1.u32), CBM_BKG1.u32);
    }
#if MIXG_EN
    else if (u32mixer_id == VDP_CBM_MIXG0)
    {
        U_MIXG0_BKG MIXG0_BKG;
        U_MIXG0_BKALPHA MIXG0_BKALPHA;
        /* G0 mixer link */
        MIXG0_BKG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXG0_BKG.u32)));
        MIXG0_BKG.bits.mixer_bkgy  = stBkg.u32BkgY;
        MIXG0_BKG.bits.mixer_bkgcb = stBkg.u32BkgU;
        MIXG0_BKG.bits.mixer_bkgcr = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->MIXG0_BKG.u32), MIXG0_BKG.u32);

        MIXG0_BKALPHA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXG0_BKALPHA.u32)));
        MIXG0_BKALPHA.bits.mixer_alpha  = stBkg.u32BkgA;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->MIXG0_BKALPHA.u32), MIXG0_BKALPHA.u32);
    }
    else if (u32mixer_id == VDP_CBM_MIXV0)
    {
        U_MIXV0_BKG MIXV0_BKG;
        MIXV0_BKG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXV0_BKG.u32)));
        MIXV0_BKG.bits.mixer_bkgy  = stBkg.u32BkgY;
        MIXV0_BKG.bits.mixer_bkgcb = stBkg.u32BkgU;
        MIXV0_BKG.bits.mixer_bkgcr = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->MIXV0_BKG.u32), MIXV0_BKG.u32);
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
    MIXV0_MIX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXV0_MIX.u32)));

    if (MIXV0_MIX.bits.mixer_prio0 == (u32layer_id + 1))
    {
        MIXV0_MIX.bits.mixer_prio0 = 0;
    }

    if (MIXV0_MIX.bits.mixer_prio1 == (u32layer_id + 1))
    {
        MIXV0_MIX.bits.mixer_prio1 = 0;
    }

    VDP_RegWrite(((HI_ULONG)&(pVdpReg->MIXV0_MIX.u32)), MIXV0_MIX.u32);

    return;
}

HI_VOID VDP_CBM_SetMixerPrio(VDP_CBM_MIX_E u32mixer_id, HI_U32 u32layer_id, HI_U32 u32prio)
{
    U_CBM_MIX1  CBM_MIX1;
    U_MIXG0_MIX MIXG0_MIX;
    U_MIXV0_MIX MIXV0_MIX;

    if (u32mixer_id == VDP_CBM_MIX0) //DHD0
    {
        switch (u32prio)
        {
            case 0:
            {
                CBM_MIX1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->CBM_MIX1.u32)));
                CBM_MIX1.bits.mixer_prio0 = u32layer_id;
                VDP_RegWrite(((HI_ULONG)&(pVdpReg->CBM_MIX1.u32)), CBM_MIX1.u32);
                break;
            }

            case 1:
            {
                CBM_MIX1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->CBM_MIX1.u32)));
                CBM_MIX1.bits.mixer_prio1 = u32layer_id;
                VDP_RegWrite(((HI_ULONG)&(pVdpReg->CBM_MIX1.u32)), CBM_MIX1.u32);
                break;
            }

            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }

        }
    }
    else if (u32mixer_id == VDP_CBM_MIXG0)
    {
        switch (u32prio)
        {
            case 0:
            {
                MIXG0_MIX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio0 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG)&(pVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }

            case 1:
            {
                MIXG0_MIX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio1 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG)&(pVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }

            case 2:
            {
                MIXG0_MIX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio2 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG)&(pVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }

            case 3:
            {
                MIXG0_MIX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio3 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG)&(pVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }

            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }

        }
    }
    else if (u32mixer_id == VDP_CBM_MIXV0)
    {
        switch (u32prio)
        {
            case 0:
            {
                MIXV0_MIX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXV0_MIX.u32)));
                MIXV0_MIX.bits.mixer_prio0 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG)&(pVdpReg->MIXV0_MIX.u32)), MIXV0_MIX.u32);
                break;
            }

            case 1:
            {
                MIXV0_MIX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MIXV0_MIX.u32)));
                MIXV0_MIX.bits.mixer_prio1 = u32layer_id + 1;
                VDP_RegWrite(((HI_ULONG)&(pVdpReg->MIXV0_MIX.u32)), MIXV0_MIX.u32);
                break;
            }

            default:
            {
                VDP_PRINT("Error, Vou_SetCbmMixerPrio() Set mixer  select wrong layer ID\n");
                return ;
            }

        }
    }
}

HI_VOID VDP_CBM_ResetMixerPrio(VDP_CBM_MIX_E u32mixer_id)
{

    if (u32mixer_id == VDP_CBM_MIX0) //DHD0
    {
        U_CBM_MIX1 CBM_MIX1;
        CBM_MIX1.u32 = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->CBM_MIX1.u32)), CBM_MIX1.u32);
    }
    else if (u32mixer_id == VDP_CBM_MIXG0)
    {
        U_MIXG0_MIX MIXG0_MIX;
        MIXG0_MIX.u32 = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
    }
    else if (u32mixer_id == VDP_CBM_MIXV0)
    {
        U_MIXV0_MIX MIXV0_MIX;
        MIXV0_MIX.u32 = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->MIXV0_MIX.u32)), MIXV0_MIX.u32);
    }
    else
    {
        VDP_PRINT("Error, VDP_CBM_ResetMixerPrio() Set mixer  select wrong layer ID\n");
    }

    return ;
}

HI_VOID VDP_SetCheckSumEnable(HI_U32  bEnable)
{
    U_DHD_TOP_CTRL  DHD_TOP_CTRL;

    DHD_TOP_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DHD_TOP_CTRL.u32)));
    DHD_TOP_CTRL.bits.chk_sum_en = bEnable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->DHD_TOP_CTRL.u32)), DHD_TOP_CTRL.u32);
}

