
#include "vdp_hal_ip_para.h"
#include "vdp_hal_comm.h"
extern volatile volatile S_VDP_REGS_TYPE* pVdpReg;

HI_VOID VDP_PARA_SetParaAddrVhdChn00( HI_U32 para_addr_vhd_chn00)
{
	U_PARA_ADDR_VHD_CHN00 PARA_ADDR_VHD_CHN00;

	PARA_ADDR_VHD_CHN00.bits.para_addr_vhd_chn00 = para_addr_vhd_chn00;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN00.u32),PARA_ADDR_VHD_CHN00.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn01( HI_U32 para_addr_vhd_chn01)
{
	U_PARA_ADDR_VHD_CHN01 PARA_ADDR_VHD_CHN01;

	PARA_ADDR_VHD_CHN01.bits.para_addr_vhd_chn01 = para_addr_vhd_chn01;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN01.u32),PARA_ADDR_VHD_CHN01.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn02( HI_U32 para_addr_vhd_chn02)
{
	U_PARA_ADDR_VHD_CHN02 PARA_ADDR_VHD_CHN02;

	PARA_ADDR_VHD_CHN02.bits.para_addr_vhd_chn02 = para_addr_vhd_chn02;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN02.u32),PARA_ADDR_VHD_CHN02.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn03( HI_U32 para_addr_vhd_chn03)
{
	U_PARA_ADDR_VHD_CHN03 PARA_ADDR_VHD_CHN03;

	PARA_ADDR_VHD_CHN03.bits.para_addr_vhd_chn03 = para_addr_vhd_chn03;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN03.u32),PARA_ADDR_VHD_CHN03.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn04( HI_U32 para_addr_vhd_chn04)
{
	U_PARA_ADDR_VHD_CHN04 PARA_ADDR_VHD_CHN04;

	PARA_ADDR_VHD_CHN04.bits.para_addr_vhd_chn04 = para_addr_vhd_chn04;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN04.u32),PARA_ADDR_VHD_CHN04.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn05( HI_U32 para_addr_vhd_chn05)
{
	U_PARA_ADDR_VHD_CHN05 PARA_ADDR_VHD_CHN05;

	PARA_ADDR_VHD_CHN05.bits.para_addr_vhd_chn05 = para_addr_vhd_chn05;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN05.u32),PARA_ADDR_VHD_CHN05.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn06( HI_U32 para_addr_vhd_chn06)
{
	U_PARA_ADDR_VHD_CHN06 PARA_ADDR_VHD_CHN06;

	PARA_ADDR_VHD_CHN06.bits.para_addr_vhd_chn06 = para_addr_vhd_chn06;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN06.u32),PARA_ADDR_VHD_CHN06.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn07( HI_U32 para_addr_vhd_chn07)
{
	U_PARA_ADDR_VHD_CHN07 PARA_ADDR_VHD_CHN07;

	PARA_ADDR_VHD_CHN07.bits.para_addr_vhd_chn07 = para_addr_vhd_chn07;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN07.u32),PARA_ADDR_VHD_CHN07.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn08( HI_U32 para_addr_vhd_chn08)
{
	U_PARA_ADDR_VHD_CHN08 PARA_ADDR_VHD_CHN08;

	PARA_ADDR_VHD_CHN08.bits.para_addr_vhd_chn08 = para_addr_vhd_chn08;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN08.u32),PARA_ADDR_VHD_CHN08.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn09( HI_U32 para_addr_vhd_chn09)
{
	U_PARA_ADDR_VHD_CHN09 PARA_ADDR_VHD_CHN09;

	PARA_ADDR_VHD_CHN09.bits.para_addr_vhd_chn09 = para_addr_vhd_chn09;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN09.u32),PARA_ADDR_VHD_CHN09.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn10( HI_U32 para_addr_vhd_chn10)
{
	U_PARA_ADDR_VHD_CHN10 PARA_ADDR_VHD_CHN10;

	PARA_ADDR_VHD_CHN10.bits.para_addr_vhd_chn10 = para_addr_vhd_chn10;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN10.u32),PARA_ADDR_VHD_CHN10.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn11( HI_U32 para_addr_vhd_chn11)
{
	U_PARA_ADDR_VHD_CHN11 PARA_ADDR_VHD_CHN11;

	PARA_ADDR_VHD_CHN11.bits.para_addr_vhd_chn11 = para_addr_vhd_chn11;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN11.u32),PARA_ADDR_VHD_CHN11.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn12( HI_U32 para_addr_vhd_chn12)
{
	U_PARA_ADDR_VHD_CHN12 PARA_ADDR_VHD_CHN12;

	PARA_ADDR_VHD_CHN12.bits.para_addr_vhd_chn12 = para_addr_vhd_chn12;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN12.u32),PARA_ADDR_VHD_CHN12.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn13( HI_U32 para_addr_vhd_chn13)
{
	U_PARA_ADDR_VHD_CHN13 PARA_ADDR_VHD_CHN13;

	PARA_ADDR_VHD_CHN13.bits.para_addr_vhd_chn13 = para_addr_vhd_chn13;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN13.u32),PARA_ADDR_VHD_CHN13.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn14( HI_U32 para_addr_vhd_chn14)
{
	U_PARA_ADDR_VHD_CHN14 PARA_ADDR_VHD_CHN14;

	PARA_ADDR_VHD_CHN14.bits.para_addr_vhd_chn14 = para_addr_vhd_chn14;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN14.u32),PARA_ADDR_VHD_CHN14.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn15( HI_U32 para_addr_vhd_chn15)
{
	U_PARA_ADDR_VHD_CHN15 PARA_ADDR_VHD_CHN15;

	PARA_ADDR_VHD_CHN15.bits.para_addr_vhd_chn15 = para_addr_vhd_chn15;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN15.u32),PARA_ADDR_VHD_CHN15.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn16( HI_U32 para_addr_vhd_chn16)
{
	U_PARA_ADDR_VHD_CHN16 PARA_ADDR_VHD_CHN16;

	PARA_ADDR_VHD_CHN16.bits.para_addr_vhd_chn16 = para_addr_vhd_chn16;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN16.u32),PARA_ADDR_VHD_CHN16.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn17( HI_U32 para_addr_vhd_chn17)
{
	U_PARA_ADDR_VHD_CHN17 PARA_ADDR_VHD_CHN17;

	PARA_ADDR_VHD_CHN17.bits.para_addr_vhd_chn17 = para_addr_vhd_chn17;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN17.u32),PARA_ADDR_VHD_CHN17.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn18( HI_U32 para_addr_vhd_chn18)
{
	U_PARA_ADDR_VHD_CHN18 PARA_ADDR_VHD_CHN18;

	PARA_ADDR_VHD_CHN18.bits.para_addr_vhd_chn18 = para_addr_vhd_chn18;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN18.u32),PARA_ADDR_VHD_CHN18.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn19( HI_U32 para_addr_vhd_chn19)
{
	U_PARA_ADDR_VHD_CHN19 PARA_ADDR_VHD_CHN19;

	PARA_ADDR_VHD_CHN19.bits.para_addr_vhd_chn19 = para_addr_vhd_chn19;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN19.u32),PARA_ADDR_VHD_CHN19.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn20( HI_U32 para_addr_vhd_chn20)
{
	U_PARA_ADDR_VHD_CHN20 PARA_ADDR_VHD_CHN20;

	PARA_ADDR_VHD_CHN20.bits.para_addr_vhd_chn20 = para_addr_vhd_chn20;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN20.u32),PARA_ADDR_VHD_CHN20.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn21( HI_U32 para_addr_vhd_chn21)
{
	U_PARA_ADDR_VHD_CHN21 PARA_ADDR_VHD_CHN21;

	PARA_ADDR_VHD_CHN21.bits.para_addr_vhd_chn21 = para_addr_vhd_chn21;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN21.u32),PARA_ADDR_VHD_CHN21.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn22( HI_U32 para_addr_vhd_chn22)
{
	U_PARA_ADDR_VHD_CHN22 PARA_ADDR_VHD_CHN22;

	PARA_ADDR_VHD_CHN22.bits.para_addr_vhd_chn22 = para_addr_vhd_chn22;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN22.u32),PARA_ADDR_VHD_CHN22.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn23( HI_U32 para_addr_vhd_chn23)
{
	U_PARA_ADDR_VHD_CHN23 PARA_ADDR_VHD_CHN23;

	PARA_ADDR_VHD_CHN23.bits.para_addr_vhd_chn23 = para_addr_vhd_chn23;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN23.u32),PARA_ADDR_VHD_CHN23.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn24( HI_U32 para_addr_vhd_chn24)
{
	U_PARA_ADDR_VHD_CHN24 PARA_ADDR_VHD_CHN24;

	PARA_ADDR_VHD_CHN24.bits.para_addr_vhd_chn24 = para_addr_vhd_chn24;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN24.u32),PARA_ADDR_VHD_CHN24.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn25( HI_U32 para_addr_vhd_chn25)
{
	U_PARA_ADDR_VHD_CHN25 PARA_ADDR_VHD_CHN25;

	PARA_ADDR_VHD_CHN25.bits.para_addr_vhd_chn25 = para_addr_vhd_chn25;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN25.u32),PARA_ADDR_VHD_CHN25.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn26( HI_U32 para_addr_vhd_chn26)
{
	U_PARA_ADDR_VHD_CHN26 PARA_ADDR_VHD_CHN26;

	PARA_ADDR_VHD_CHN26.bits.para_addr_vhd_chn26 = para_addr_vhd_chn26;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN26.u32),PARA_ADDR_VHD_CHN26.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn27( HI_U32 para_addr_vhd_chn27)
{
	U_PARA_ADDR_VHD_CHN27 PARA_ADDR_VHD_CHN27;

	PARA_ADDR_VHD_CHN27.bits.para_addr_vhd_chn27 = para_addr_vhd_chn27;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN27.u32),PARA_ADDR_VHD_CHN27.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn28( HI_U32 para_addr_vhd_chn28)
{
	U_PARA_ADDR_VHD_CHN28 PARA_ADDR_VHD_CHN28;

	PARA_ADDR_VHD_CHN28.bits.para_addr_vhd_chn28 = para_addr_vhd_chn28;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN28.u32),PARA_ADDR_VHD_CHN28.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn29( HI_U32 para_addr_vhd_chn29)
{
	U_PARA_ADDR_VHD_CHN29 PARA_ADDR_VHD_CHN29;

	PARA_ADDR_VHD_CHN29.bits.para_addr_vhd_chn29 = para_addr_vhd_chn29;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN29.u32),PARA_ADDR_VHD_CHN29.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn30( HI_U32 para_addr_vhd_chn30)
{
	U_PARA_ADDR_VHD_CHN30 PARA_ADDR_VHD_CHN30;

	PARA_ADDR_VHD_CHN30.bits.para_addr_vhd_chn30 = para_addr_vhd_chn30;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN30.u32),PARA_ADDR_VHD_CHN30.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaAddrVhdChn31( HI_U32 para_addr_vhd_chn31)
{
	U_PARA_ADDR_VHD_CHN31 PARA_ADDR_VHD_CHN31;

	PARA_ADDR_VHD_CHN31.bits.para_addr_vhd_chn31 = para_addr_vhd_chn31;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN31.u32),PARA_ADDR_VHD_CHN31.u32);

	return ;
}


HI_VOID VDP_PARA_SetParaUpVhdChn( HI_U32 u32ChnNum)
{
	U_PARA_UP_VHD PARA_UP_VHD;
	if(u32ChnNum <=31)
	{
		PARA_UP_VHD.u32 = (1 << u32ChnNum);
		VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);
	}
	return ;
}

HI_VOID VDP_PARA_SetParaUpVhdChnAll(HI_VOID)
{
	U_PARA_UP_VHD PARA_UP_VHD;

	PARA_UP_VHD.u32  = 0xffffffff;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);

	return ;
}



