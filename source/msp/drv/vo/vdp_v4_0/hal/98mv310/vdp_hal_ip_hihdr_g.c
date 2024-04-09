
#include "vdp_hal_ip_hihdr_g.h"
#include "vdp_hal_comm.h"
extern volatile S_VDP_REGS_TYPE *pVdpReg;

HI_VOID VDP_HIHDR_G_SetTmpCoefAddr  (HI_U32 u32Addr)
{

    U_PARA_ADDR_VHD_CHN14 PARA_ADDR_VHD_CHN14;

    PARA_ADDR_VHD_CHN14.bits.para_addr_vhd_chn14 = u32Addr;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN14.u32),PARA_ADDR_VHD_CHN14.u32);

    return ;
}

HI_VOID VDP_HIHDR_G_SetGmmCoefAddr  (HI_U32 u32Addr)
{

    U_PARA_ADDR_VHD_CHN15 PARA_ADDR_VHD_CHN15;

    PARA_ADDR_VHD_CHN15.bits.para_addr_vhd_chn15 = u32Addr;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN15.u32),PARA_ADDR_VHD_CHN15.u32);

    return ;
}

HI_VOID  VDP_HIHDR_G_SetTmpParaUpd (HI_U32 regup)
{
    U_PARA_UP_VHD PARA_UP_VHD;

    PARA_UP_VHD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32));
    PARA_UP_VHD.bits.para_up_vhd_chn14 = regup;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);
    return ;
}

HI_VOID  VDP_HIHDR_G_SetGmmParaUpd (HI_U32 regup)
{
    U_PARA_UP_VHD PARA_UP_VHD;

    PARA_UP_VHD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32));
    PARA_UP_VHD.bits.para_up_vhd_chn15 = regup;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);
    return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDemoPos(HI_U32 ghdr_demo_pos)
{
	U_GHDR_CTRL GHDR_CTRL;

	GHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32));
	GHDR_CTRL.bits.ghdr_demo_pos = ghdr_demo_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32),GHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDemoMode(HI_U32 ghdr_demo_mode)
{
	U_GHDR_CTRL GHDR_CTRL;

	GHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32));
	GHDR_CTRL.bits.ghdr_demo_mode = ghdr_demo_mode;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32),GHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDemoEn(HI_U32 ghdr_demo_en)
{
	U_GHDR_CTRL GHDR_CTRL;

	GHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32));
	GHDR_CTRL.bits.ghdr_demo_en = ghdr_demo_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32),GHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrCkGtEn(HI_U32 ghdr_ck_gt_en)
{
	U_GHDR_CTRL GHDR_CTRL;

	GHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32));
	GHDR_CTRL.bits.ghdr_ck_gt_en = ghdr_ck_gt_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32),GHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDegmmEn(HI_U32 ghdr_degmm_en)
{
	U_GHDR_CTRL GHDR_CTRL;

	GHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32));
	GHDR_CTRL.bits.ghdr_degmm_en = ghdr_degmm_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32),GHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrEn(HI_U32 ghdr_en)
{
	U_GHDR_CTRL GHDR_CTRL;

	GHDR_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32));
	GHDR_CTRL.bits.ghdr_en = ghdr_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_CTRL.u32),GHDR_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutEn(HI_U32 ghdr_gamut_en)
{
	U_GHDR_GAMUT_CTRL GHDR_GAMUT_CTRL;

	GHDR_GAMUT_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_CTRL.u32));
	GHDR_GAMUT_CTRL.bits.ghdr_gamut_en = ghdr_gamut_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_CTRL.u32),GHDR_GAMUT_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutCoef00(HI_U32 ghdr_gamut_coef00)
{
	U_GHDR_GAMUT_COEF00 GHDR_GAMUT_COEF00;

	GHDR_GAMUT_COEF00.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF00.u32));
	GHDR_GAMUT_COEF00.bits.ghdr_gamut_coef00 = ghdr_gamut_coef00;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF00.u32),GHDR_GAMUT_COEF00.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutCoef01(HI_U32 ghdr_gamut_coef01)
{
	U_GHDR_GAMUT_COEF01 GHDR_GAMUT_COEF01;

	GHDR_GAMUT_COEF01.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF01.u32));
	GHDR_GAMUT_COEF01.bits.ghdr_gamut_coef01 = ghdr_gamut_coef01;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF01.u32),GHDR_GAMUT_COEF01.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutCoef02(HI_U32 ghdr_gamut_coef02)
{
	U_GHDR_GAMUT_COEF02 GHDR_GAMUT_COEF02;

	GHDR_GAMUT_COEF02.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF02.u32));
	GHDR_GAMUT_COEF02.bits.ghdr_gamut_coef02 = ghdr_gamut_coef02;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF02.u32),GHDR_GAMUT_COEF02.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutCoef10(HI_U32 ghdr_gamut_coef10)
{
	U_GHDR_GAMUT_COEF10 GHDR_GAMUT_COEF10;

	GHDR_GAMUT_COEF10.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF10.u32));
	GHDR_GAMUT_COEF10.bits.ghdr_gamut_coef10 = ghdr_gamut_coef10;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF10.u32),GHDR_GAMUT_COEF10.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutCoef11(HI_U32 ghdr_gamut_coef11)
{
	U_GHDR_GAMUT_COEF11 GHDR_GAMUT_COEF11;

	GHDR_GAMUT_COEF11.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF11.u32));
	GHDR_GAMUT_COEF11.bits.ghdr_gamut_coef11 = ghdr_gamut_coef11;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF11.u32),GHDR_GAMUT_COEF11.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutCoef12(HI_U32 ghdr_gamut_coef12)
{
	U_GHDR_GAMUT_COEF12 GHDR_GAMUT_COEF12;

	GHDR_GAMUT_COEF12.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF12.u32));
	GHDR_GAMUT_COEF12.bits.ghdr_gamut_coef12 = ghdr_gamut_coef12;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF12.u32),GHDR_GAMUT_COEF12.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutCoef20(HI_U32 ghdr_gamut_coef20)
{
	U_GHDR_GAMUT_COEF20 GHDR_GAMUT_COEF20;

	GHDR_GAMUT_COEF20.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF20.u32));
	GHDR_GAMUT_COEF20.bits.ghdr_gamut_coef20 = ghdr_gamut_coef20;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF20.u32),GHDR_GAMUT_COEF20.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutCoef21(HI_U32 ghdr_gamut_coef21)
{
	U_GHDR_GAMUT_COEF21 GHDR_GAMUT_COEF21;

	GHDR_GAMUT_COEF21.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF21.u32));
	GHDR_GAMUT_COEF21.bits.ghdr_gamut_coef21 = ghdr_gamut_coef21;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF21.u32),GHDR_GAMUT_COEF21.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutCoef22(HI_U32 ghdr_gamut_coef22)
{
	U_GHDR_GAMUT_COEF22 GHDR_GAMUT_COEF22;

	GHDR_GAMUT_COEF22.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF22.u32));
	GHDR_GAMUT_COEF22.bits.ghdr_gamut_coef22 = ghdr_gamut_coef22;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_COEF22.u32),GHDR_GAMUT_COEF22.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutScale(HI_U32 ghdr_gamut_scale)
{
	U_GHDR_GAMUT_SCALE GHDR_GAMUT_SCALE;

	GHDR_GAMUT_SCALE.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_SCALE.u32));
	GHDR_GAMUT_SCALE.bits.ghdr_gamut_scale = ghdr_gamut_scale;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_SCALE.u32),GHDR_GAMUT_SCALE.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutClipMin(HI_U32 ghdr_gamut_clip_min)
{
	U_GHDR_GAMUT_CLIP_MIN GHDR_GAMUT_CLIP_MIN;

	GHDR_GAMUT_CLIP_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_CLIP_MIN.u32));
	GHDR_GAMUT_CLIP_MIN.bits.ghdr_gamut_clip_min = ghdr_gamut_clip_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_CLIP_MIN.u32),GHDR_GAMUT_CLIP_MIN.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGamutClipMax(HI_U32 ghdr_gamut_clip_max)
{
	U_GHDR_GAMUT_CLIP_MAX GHDR_GAMUT_CLIP_MAX;

	GHDR_GAMUT_CLIP_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMUT_CLIP_MAX.u32));
	GHDR_GAMUT_CLIP_MAX.bits.ghdr_gamut_clip_max = ghdr_gamut_clip_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMUT_CLIP_MAX.u32),GHDR_GAMUT_CLIP_MAX.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapEn(HI_U32 ghdr_tmap_en)
{
	U_GHDR_TONEMAP_CTRL GHDR_TONEMAP_CTRL;

	GHDR_TONEMAP_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_CTRL.u32));
	GHDR_TONEMAP_CTRL.bits.ghdr_tmap_en = ghdr_tmap_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_CTRL.u32),GHDR_TONEMAP_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapRdEn(HI_U32 ghdr_tmap_rd_en)
{
	U_GHDR_TONEMAP_REN GHDR_TONEMAP_REN;

	GHDR_TONEMAP_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_REN.u32));
	GHDR_TONEMAP_REN.bits.ghdr_tmap_rd_en = ghdr_tmap_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_REN.u32),GHDR_TONEMAP_REN.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapParaData(HI_U32 ghdr_tmap_para_data)
{
	U_GHDR_TONEMAP_DATA GHDR_TONEMAP_DATA;

	GHDR_TONEMAP_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_DATA.u32));
	GHDR_TONEMAP_DATA.bits.ghdr_tmap_para_data = ghdr_tmap_para_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_DATA.u32),GHDR_TONEMAP_DATA.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX4Step(HI_U32 g_tmap_x4_step)
{
	U_GHDR_TONEMAP_STEP GHDR_TONEMAP_STEP;

	GHDR_TONEMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_STEP.u32));
	GHDR_TONEMAP_STEP.bits.g_tmap_x4_step = g_tmap_x4_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_STEP.u32),GHDR_TONEMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX3Step(HI_U32 g_tmap_x3_step)
{
	U_GHDR_TONEMAP_STEP GHDR_TONEMAP_STEP;

	GHDR_TONEMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_STEP.u32));
	GHDR_TONEMAP_STEP.bits.g_tmap_x3_step = g_tmap_x3_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_STEP.u32),GHDR_TONEMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX2Step(HI_U32 g_tmap_x2_step)
{
	U_GHDR_TONEMAP_STEP GHDR_TONEMAP_STEP;

	GHDR_TONEMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_STEP.u32));
	GHDR_TONEMAP_STEP.bits.g_tmap_x2_step = g_tmap_x2_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_STEP.u32),GHDR_TONEMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX1Step(HI_U32 g_tmap_x1_step)
{
	U_GHDR_TONEMAP_STEP GHDR_TONEMAP_STEP;

	GHDR_TONEMAP_STEP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_STEP.u32));
	GHDR_TONEMAP_STEP.bits.g_tmap_x1_step = g_tmap_x1_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_STEP.u32),GHDR_TONEMAP_STEP.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX1Pos(HI_U32 g_tmap_x1_pos)
{
	U_GHDR_TONEMAP_POS1 GHDR_TONEMAP_POS1;

	GHDR_TONEMAP_POS1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_POS1.u32));
	GHDR_TONEMAP_POS1.bits.g_tmap_x1_pos = g_tmap_x1_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_POS1.u32),GHDR_TONEMAP_POS1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX2Pos(HI_U32 g_tmap_x2_pos)
{
	U_GHDR_TONEMAP_POS2 GHDR_TONEMAP_POS2;

	GHDR_TONEMAP_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_POS2.u32));
	GHDR_TONEMAP_POS2.bits.g_tmap_x2_pos = g_tmap_x2_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_POS2.u32),GHDR_TONEMAP_POS2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX3Pos(HI_U32 g_tmap_x3_pos)
{
	U_GHDR_TONEMAP_POS3 GHDR_TONEMAP_POS3;

	GHDR_TONEMAP_POS3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_POS3.u32));
	GHDR_TONEMAP_POS3.bits.g_tmap_x3_pos = g_tmap_x3_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_POS3.u32),GHDR_TONEMAP_POS3.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX4Pos(HI_U32 g_tmap_x4_pos)
{
	U_GHDR_TONEMAP_POS4 GHDR_TONEMAP_POS4;

	GHDR_TONEMAP_POS4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_POS4.u32));
	GHDR_TONEMAP_POS4.bits.g_tmap_x4_pos = g_tmap_x4_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_POS4.u32),GHDR_TONEMAP_POS4.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX4Num(HI_U32 g_tmap_x4_num)
{
	U_GHDR_TONEMAP_NUM GHDR_TONEMAP_NUM;

	GHDR_TONEMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_NUM.u32));
	GHDR_TONEMAP_NUM.bits.g_tmap_x4_num = g_tmap_x4_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_NUM.u32),GHDR_TONEMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX3Num(HI_U32 g_tmap_x3_num)
{
	U_GHDR_TONEMAP_NUM GHDR_TONEMAP_NUM;

	GHDR_TONEMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_NUM.u32));
	GHDR_TONEMAP_NUM.bits.g_tmap_x3_num = g_tmap_x3_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_NUM.u32),GHDR_TONEMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX2Num(HI_U32 g_tmap_x2_num)
{
	U_GHDR_TONEMAP_NUM GHDR_TONEMAP_NUM;

	GHDR_TONEMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_NUM.u32));
	GHDR_TONEMAP_NUM.bits.g_tmap_x2_num = g_tmap_x2_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_NUM.u32),GHDR_TONEMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGTmapX1Num(HI_U32 g_tmap_x1_num)
{
	U_GHDR_TONEMAP_NUM GHDR_TONEMAP_NUM;

	GHDR_TONEMAP_NUM.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_NUM.u32));
	GHDR_TONEMAP_NUM.bits.g_tmap_x1_num = g_tmap_x1_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_NUM.u32),GHDR_TONEMAP_NUM.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapLumaCoef0(HI_U32 ghdr_tmap_luma_coef0)
{
	U_GHDR_TONEMAP_LUMA_COEF0 GHDR_TONEMAP_LUMA_COEF0;

	GHDR_TONEMAP_LUMA_COEF0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_LUMA_COEF0.u32));
	GHDR_TONEMAP_LUMA_COEF0.bits.ghdr_tmap_luma_coef0 = ghdr_tmap_luma_coef0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_LUMA_COEF0.u32),GHDR_TONEMAP_LUMA_COEF0.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapLumaCoef1(HI_U32 ghdr_tmap_luma_coef1)
{
	U_GHDR_TONEMAP_LUMA_COEF1 GHDR_TONEMAP_LUMA_COEF1;

	GHDR_TONEMAP_LUMA_COEF1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_LUMA_COEF1.u32));
	GHDR_TONEMAP_LUMA_COEF1.bits.ghdr_tmap_luma_coef1 = ghdr_tmap_luma_coef1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_LUMA_COEF1.u32),GHDR_TONEMAP_LUMA_COEF1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapLumaCoef2(HI_U32 ghdr_tmap_luma_coef2)
{
	U_GHDR_TONEMAP_LUMA_COEF2 GHDR_TONEMAP_LUMA_COEF2;

	GHDR_TONEMAP_LUMA_COEF2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_LUMA_COEF2.u32));
	GHDR_TONEMAP_LUMA_COEF2.bits.ghdr_tmap_luma_coef2 = ghdr_tmap_luma_coef2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_LUMA_COEF2.u32),GHDR_TONEMAP_LUMA_COEF2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapLumaScale(HI_U32 ghdr_tmap_luma_scale)
{
	U_GHDR_TONEMAP_LUMA_SCALE GHDR_TONEMAP_LUMA_SCALE;

	GHDR_TONEMAP_LUMA_SCALE.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_LUMA_SCALE.u32));
	GHDR_TONEMAP_LUMA_SCALE.bits.ghdr_tmap_luma_scale = ghdr_tmap_luma_scale;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_LUMA_SCALE.u32),GHDR_TONEMAP_LUMA_SCALE.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapCoefScale(HI_U32 ghdr_tmap_coef_scale)
{
	U_GHDR_TONEMAP_COEF_SCALE GHDR_TONEMAP_COEF_SCALE;

	GHDR_TONEMAP_COEF_SCALE.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_COEF_SCALE.u32));
	GHDR_TONEMAP_COEF_SCALE.bits.ghdr_tmap_coef_scale = ghdr_tmap_coef_scale;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_COEF_SCALE.u32),GHDR_TONEMAP_COEF_SCALE.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapOutClipMin(HI_U32 ghdr_tmap_out_clip_min)
{
	U_GHDR_TONEMAP_OUT_CLIP_MIN GHDR_TONEMAP_OUT_CLIP_MIN;

	GHDR_TONEMAP_OUT_CLIP_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_OUT_CLIP_MIN.u32));
	GHDR_TONEMAP_OUT_CLIP_MIN.bits.ghdr_tmap_out_clip_min = ghdr_tmap_out_clip_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_OUT_CLIP_MIN.u32),GHDR_TONEMAP_OUT_CLIP_MIN.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrTmapOutClipMax(HI_U32 ghdr_tmap_out_clip_max)
{
	U_GHDR_TONEMAP_OUT_CLIP_MAX GHDR_TONEMAP_OUT_CLIP_MAX;

	GHDR_TONEMAP_OUT_CLIP_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_OUT_CLIP_MAX.u32));
	GHDR_TONEMAP_OUT_CLIP_MAX.bits.ghdr_tmap_out_clip_max = ghdr_tmap_out_clip_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_TONEMAP_OUT_CLIP_MAX.u32),GHDR_TONEMAP_OUT_CLIP_MAX.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGmmEn(HI_U32 ghdr_gmm_en)
{
	U_GHDR_GAMMA_CTRL GHDR_GAMMA_CTRL;

	GHDR_GAMMA_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_CTRL.u32));
	GHDR_GAMMA_CTRL.bits.ghdr_gmm_en = ghdr_gmm_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_CTRL.u32),GHDR_GAMMA_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGammaRdEn(HI_U32 ghdr_gamma_rd_en)
{
	U_GHDR_GAMMA_REN GHDR_GAMMA_REN;

	GHDR_GAMMA_REN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_REN.u32));
	GHDR_GAMMA_REN.bits.ghdr_gamma_rd_en = ghdr_gamma_rd_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_REN.u32),GHDR_GAMMA_REN.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrGammaParaData(HI_U32 ghdr_gamma_para_data)
{
	U_GHDR_GAMMMA_DATA GHDR_GAMMMA_DATA;

	GHDR_GAMMMA_DATA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMMA_DATA.u32));
	GHDR_GAMMMA_DATA.bits.ghdr_gamma_para_data = ghdr_gamma_para_data;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMMA_DATA.u32),GHDR_GAMMMA_DATA.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX4Step(HI_U32 g_gmm_x4_step)
{
	U_GHDR_GAMMA_STEP1 GHDR_GAMMA_STEP1;

	GHDR_GAMMA_STEP1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP1.u32));
	GHDR_GAMMA_STEP1.bits.g_gmm_x4_step = g_gmm_x4_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP1.u32),GHDR_GAMMA_STEP1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX3Step(HI_U32 g_gmm_x3_step)
{
	U_GHDR_GAMMA_STEP1 GHDR_GAMMA_STEP1;

	GHDR_GAMMA_STEP1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP1.u32));
	GHDR_GAMMA_STEP1.bits.g_gmm_x3_step = g_gmm_x3_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP1.u32),GHDR_GAMMA_STEP1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX2Step(HI_U32 g_gmm_x2_step)
{
	U_GHDR_GAMMA_STEP1 GHDR_GAMMA_STEP1;

	GHDR_GAMMA_STEP1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP1.u32));
	GHDR_GAMMA_STEP1.bits.g_gmm_x2_step = g_gmm_x2_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP1.u32),GHDR_GAMMA_STEP1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX1Step(HI_U32 g_gmm_x1_step)
{
	U_GHDR_GAMMA_STEP1 GHDR_GAMMA_STEP1;

	GHDR_GAMMA_STEP1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP1.u32));
	GHDR_GAMMA_STEP1.bits.g_gmm_x1_step = g_gmm_x1_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP1.u32),GHDR_GAMMA_STEP1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX8Step(HI_U32 g_gmm_x8_step)
{
	U_GHDR_GAMMA_STEP2 GHDR_GAMMA_STEP2;

	GHDR_GAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP2.u32));
	GHDR_GAMMA_STEP2.bits.g_gmm_x8_step = g_gmm_x8_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP2.u32),GHDR_GAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX7Step(HI_U32 g_gmm_x7_step)
{
	U_GHDR_GAMMA_STEP2 GHDR_GAMMA_STEP2;

	GHDR_GAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP2.u32));
	GHDR_GAMMA_STEP2.bits.g_gmm_x7_step = g_gmm_x7_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP2.u32),GHDR_GAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX6Step(HI_U32 g_gmm_x6_step)
{
	U_GHDR_GAMMA_STEP2 GHDR_GAMMA_STEP2;

	GHDR_GAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP2.u32));
	GHDR_GAMMA_STEP2.bits.g_gmm_x6_step = g_gmm_x6_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP2.u32),GHDR_GAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX5Step(HI_U32 g_gmm_x5_step)
{
	U_GHDR_GAMMA_STEP2 GHDR_GAMMA_STEP2;

	GHDR_GAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP2.u32));
	GHDR_GAMMA_STEP2.bits.g_gmm_x5_step = g_gmm_x5_step;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_STEP2.u32),GHDR_GAMMA_STEP2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX2Pos(HI_U32 g_gmm_x2_pos)
{
	U_GHDR_GAMMA_POS1 GHDR_GAMMA_POS1;

	GHDR_GAMMA_POS1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS1.u32));
	GHDR_GAMMA_POS1.bits.g_gmm_x2_pos = g_gmm_x2_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS1.u32),GHDR_GAMMA_POS1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX1Pos(HI_U32 g_gmm_x1_pos)
{
	U_GHDR_GAMMA_POS1 GHDR_GAMMA_POS1;

	GHDR_GAMMA_POS1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS1.u32));
	GHDR_GAMMA_POS1.bits.g_gmm_x1_pos = g_gmm_x1_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS1.u32),GHDR_GAMMA_POS1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX4Pos(HI_U32 g_gmm_x4_pos)
{
	U_GHDR_GAMMA_POS2 GHDR_GAMMA_POS2;

	GHDR_GAMMA_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS2.u32));
	GHDR_GAMMA_POS2.bits.g_gmm_x4_pos = g_gmm_x4_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS2.u32),GHDR_GAMMA_POS2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX3Pos(HI_U32 g_gmm_x3_pos)
{
	U_GHDR_GAMMA_POS2 GHDR_GAMMA_POS2;

	GHDR_GAMMA_POS2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS2.u32));
	GHDR_GAMMA_POS2.bits.g_gmm_x3_pos = g_gmm_x3_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS2.u32),GHDR_GAMMA_POS2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX6Pos(HI_U32 g_gmm_x6_pos)
{
	U_GHDR_GAMMA_POS3 GHDR_GAMMA_POS3;

	GHDR_GAMMA_POS3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS3.u32));
	GHDR_GAMMA_POS3.bits.g_gmm_x6_pos = g_gmm_x6_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS3.u32),GHDR_GAMMA_POS3.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX5Pos(HI_U32 g_gmm_x5_pos)
{
	U_GHDR_GAMMA_POS3 GHDR_GAMMA_POS3;

	GHDR_GAMMA_POS3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS3.u32));
	GHDR_GAMMA_POS3.bits.g_gmm_x5_pos = g_gmm_x5_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS3.u32),GHDR_GAMMA_POS3.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX8Pos(HI_U32 g_gmm_x8_pos)
{
	U_GHDR_GAMMA_POS4 GHDR_GAMMA_POS4;

	GHDR_GAMMA_POS4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS4.u32));
	GHDR_GAMMA_POS4.bits.g_gmm_x8_pos = g_gmm_x8_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS4.u32),GHDR_GAMMA_POS4.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX7Pos(HI_U32 g_gmm_x7_pos)
{
	U_GHDR_GAMMA_POS4 GHDR_GAMMA_POS4;

	GHDR_GAMMA_POS4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS4.u32));
	GHDR_GAMMA_POS4.bits.g_gmm_x7_pos = g_gmm_x7_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_POS4.u32),GHDR_GAMMA_POS4.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX4Num(HI_U32 g_gmm_x4_num)
{
	U_GHDR_GAMMA_NUM1 GHDR_GAMMA_NUM1;

	GHDR_GAMMA_NUM1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM1.u32));
	GHDR_GAMMA_NUM1.bits.g_gmm_x4_num = g_gmm_x4_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM1.u32),GHDR_GAMMA_NUM1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX3Num(HI_U32 g_gmm_x3_num)
{
	U_GHDR_GAMMA_NUM1 GHDR_GAMMA_NUM1;

	GHDR_GAMMA_NUM1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM1.u32));
	GHDR_GAMMA_NUM1.bits.g_gmm_x3_num = g_gmm_x3_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM1.u32),GHDR_GAMMA_NUM1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX2Num(HI_U32 g_gmm_x2_num)
{
	U_GHDR_GAMMA_NUM1 GHDR_GAMMA_NUM1;

	GHDR_GAMMA_NUM1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM1.u32));
	GHDR_GAMMA_NUM1.bits.g_gmm_x2_num = g_gmm_x2_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM1.u32),GHDR_GAMMA_NUM1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX1Num(HI_U32 g_gmm_x1_num)
{
	U_GHDR_GAMMA_NUM1 GHDR_GAMMA_NUM1;

	GHDR_GAMMA_NUM1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM1.u32));
	GHDR_GAMMA_NUM1.bits.g_gmm_x1_num = g_gmm_x1_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM1.u32),GHDR_GAMMA_NUM1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX8Num(HI_U32 g_gmm_x8_num)
{
	U_GHDR_GAMMA_NUM2 GHDR_GAMMA_NUM2;

	GHDR_GAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM2.u32));
	GHDR_GAMMA_NUM2.bits.g_gmm_x8_num = g_gmm_x8_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM2.u32),GHDR_GAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX7Num(HI_U32 g_gmm_x7_num)
{
	U_GHDR_GAMMA_NUM2 GHDR_GAMMA_NUM2;

	GHDR_GAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM2.u32));
	GHDR_GAMMA_NUM2.bits.g_gmm_x7_num = g_gmm_x7_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM2.u32),GHDR_GAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX6Num(HI_U32 g_gmm_x6_num)
{
	U_GHDR_GAMMA_NUM2 GHDR_GAMMA_NUM2;

	GHDR_GAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM2.u32));
	GHDR_GAMMA_NUM2.bits.g_gmm_x6_num = g_gmm_x6_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM2.u32),GHDR_GAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGGmmX5Num(HI_U32 g_gmm_x5_num)
{
	U_GHDR_GAMMA_NUM2 GHDR_GAMMA_NUM2;

	GHDR_GAMMA_NUM2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM2.u32));
	GHDR_GAMMA_NUM2.bits.g_gmm_x5_num = g_gmm_x5_num;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_GAMMA_NUM2.u32),GHDR_GAMMA_NUM2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherRoundUnlim(HI_U32 ghdr_dither_round_unlim)
{
	U_GHDR_DITHER_CTRL GHDR_DITHER_CTRL;

	GHDR_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32));
	GHDR_DITHER_CTRL.bits.ghdr_dither_round_unlim = ghdr_dither_round_unlim;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32),GHDR_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherEn(HI_U32 ghdr_dither_en)
{
	U_GHDR_DITHER_CTRL GHDR_DITHER_CTRL;

	GHDR_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32));
	GHDR_DITHER_CTRL.bits.ghdr_dither_en = ghdr_dither_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32),GHDR_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherMode(HI_U32 ghdr_dither_mode)
{
	U_GHDR_DITHER_CTRL GHDR_DITHER_CTRL;

	GHDR_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32));
	GHDR_DITHER_CTRL.bits.ghdr_dither_mode = ghdr_dither_mode;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32),GHDR_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherRound(HI_U32 ghdr_dither_round)
{
	U_GHDR_DITHER_CTRL GHDR_DITHER_CTRL;

	GHDR_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32));
	GHDR_DITHER_CTRL.bits.ghdr_dither_round = ghdr_dither_round;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32),GHDR_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherDomainMode(HI_U32 ghdr_dither_domain_mode)
{
	U_GHDR_DITHER_CTRL GHDR_DITHER_CTRL;

	GHDR_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32));
	GHDR_DITHER_CTRL.bits.ghdr_dither_domain_mode = ghdr_dither_domain_mode;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32),GHDR_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherTapMode(HI_U32 ghdr_dither_tap_mode)
{
	U_GHDR_DITHER_CTRL GHDR_DITHER_CTRL;

	GHDR_DITHER_CTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32));
	GHDR_DITHER_CTRL.bits.ghdr_dither_tap_mode = ghdr_dither_tap_mode;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_CTRL.u32),GHDR_DITHER_CTRL.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherThrMax(HI_U32 ghdr_dither_thr_max)
{
	U_GHDR_DITHER_THR GHDR_DITHER_THR;

	GHDR_DITHER_THR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_THR.u32));
	GHDR_DITHER_THR.bits.ghdr_dither_thr_max = ghdr_dither_thr_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_THR.u32),GHDR_DITHER_THR.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherThrMin(HI_U32 ghdr_dither_thr_min)
{
	U_GHDR_DITHER_THR GHDR_DITHER_THR;

	GHDR_DITHER_THR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_THR.u32));
	GHDR_DITHER_THR.bits.ghdr_dither_thr_min = ghdr_dither_thr_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_THR.u32),GHDR_DITHER_THR.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherSedY0(HI_U32 ghdr_dither_sed_y0)
{
	U_GHDR_DITHER_SED_Y0 GHDR_DITHER_SED_Y0;

	GHDR_DITHER_SED_Y0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_Y0.u32));
	GHDR_DITHER_SED_Y0.bits.ghdr_dither_sed_y0 = ghdr_dither_sed_y0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_Y0.u32),GHDR_DITHER_SED_Y0.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherSedU0(HI_U32 ghdr_dither_sed_u0)
{
	U_GHDR_DITHER_SED_U0 GHDR_DITHER_SED_U0;

	GHDR_DITHER_SED_U0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_U0.u32));
	GHDR_DITHER_SED_U0.bits.ghdr_dither_sed_u0 = ghdr_dither_sed_u0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_U0.u32),GHDR_DITHER_SED_U0.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherSedV0(HI_U32 ghdr_dither_sed_v0)
{
	U_GHDR_DITHER_SED_V0 GHDR_DITHER_SED_V0;

	GHDR_DITHER_SED_V0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_V0.u32));
	GHDR_DITHER_SED_V0.bits.ghdr_dither_sed_v0 = ghdr_dither_sed_v0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_V0.u32),GHDR_DITHER_SED_V0.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherSedW0(HI_U32 ghdr_dither_sed_w0)
{
	U_GHDR_DITHER_SED_W0 GHDR_DITHER_SED_W0;

	GHDR_DITHER_SED_W0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_W0.u32));
	GHDR_DITHER_SED_W0.bits.ghdr_dither_sed_w0 = ghdr_dither_sed_w0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_W0.u32),GHDR_DITHER_SED_W0.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherSedY1(HI_U32 ghdr_dither_sed_y1)
{
	U_GHDR_DITHER_SED_Y1 GHDR_DITHER_SED_Y1;

	GHDR_DITHER_SED_Y1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_Y1.u32));
	GHDR_DITHER_SED_Y1.bits.ghdr_dither_sed_y1 = ghdr_dither_sed_y1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_Y1.u32),GHDR_DITHER_SED_Y1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherSedU1(HI_U32 ghdr_dither_sed_u1)
{
	U_GHDR_DITHER_SED_U1 GHDR_DITHER_SED_U1;

	GHDR_DITHER_SED_U1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_U1.u32));
	GHDR_DITHER_SED_U1.bits.ghdr_dither_sed_u1 = ghdr_dither_sed_u1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_U1.u32),GHDR_DITHER_SED_U1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherSedV1(HI_U32 ghdr_dither_sed_v1)
{
	U_GHDR_DITHER_SED_V1 GHDR_DITHER_SED_V1;

	GHDR_DITHER_SED_V1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_V1.u32));
	GHDR_DITHER_SED_V1.bits.ghdr_dither_sed_v1 = ghdr_dither_sed_v1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_V1.u32),GHDR_DITHER_SED_V1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetGhdrDitherSedW1(HI_U32 ghdr_dither_sed_w1)
{
	U_GHDR_DITHER_SED_W1 GHDR_DITHER_SED_W1;

	GHDR_DITHER_SED_W1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_W1.u32));
	GHDR_DITHER_SED_W1.bits.ghdr_dither_sed_w1 = ghdr_dither_sed_w1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GHDR_DITHER_SED_W1.u32),GHDR_DITHER_SED_W1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yEn(HI_U32 hihdr_r2y_en)
{
    U_HIHDR_G_RGB2YUV_CTRL HIHDR_G_RGB2YUV_CTRL;

    HIHDR_G_RGB2YUV_CTRL.u32 = VDP_RegRead((HI_ULONG) & (pVdpReg->HIHDR_G_RGB2YUV_CTRL.u32));
    HIHDR_G_RGB2YUV_CTRL.bits.hihdr_r2y_en = hihdr_r2y_en;
    VDP_RegWrite((HI_ULONG) & (pVdpReg->HIHDR_G_RGB2YUV_CTRL.u32), HIHDR_G_RGB2YUV_CTRL.u32);

    return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yCoef00(HI_U32 hihdr_r2y_coef00)
{
	U_HIHDR_G_RGB2YUV_COEF0 HIHDR_G_RGB2YUV_COEF0;

	HIHDR_G_RGB2YUV_COEF0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF0.u32));
	HIHDR_G_RGB2YUV_COEF0.bits.hihdr_r2y_coef00 = hihdr_r2y_coef00;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF0.u32),HIHDR_G_RGB2YUV_COEF0.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yCoef01(HI_U32 hihdr_r2y_coef01)
{
	U_HIHDR_G_RGB2YUV_COEF1 HIHDR_G_RGB2YUV_COEF1;

	HIHDR_G_RGB2YUV_COEF1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF1.u32));
	HIHDR_G_RGB2YUV_COEF1.bits.hihdr_r2y_coef01 = hihdr_r2y_coef01;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF1.u32),HIHDR_G_RGB2YUV_COEF1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yCoef02(HI_U32 hihdr_r2y_coef02)
{
	U_HIHDR_G_RGB2YUV_COEF2 HIHDR_G_RGB2YUV_COEF2;

	HIHDR_G_RGB2YUV_COEF2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF2.u32));
	HIHDR_G_RGB2YUV_COEF2.bits.hihdr_r2y_coef02 = hihdr_r2y_coef02;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF2.u32),HIHDR_G_RGB2YUV_COEF2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yCoef10(HI_U32 hihdr_r2y_coef10)
{
	U_HIHDR_G_RGB2YUV_COEF3 HIHDR_G_RGB2YUV_COEF3;

	HIHDR_G_RGB2YUV_COEF3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF3.u32));
	HIHDR_G_RGB2YUV_COEF3.bits.hihdr_r2y_coef10 = hihdr_r2y_coef10;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF3.u32),HIHDR_G_RGB2YUV_COEF3.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yCoef11(HI_U32 hihdr_r2y_coef11)
{
	U_HIHDR_G_RGB2YUV_COEF4 HIHDR_G_RGB2YUV_COEF4;

	HIHDR_G_RGB2YUV_COEF4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF4.u32));
	HIHDR_G_RGB2YUV_COEF4.bits.hihdr_r2y_coef11 = hihdr_r2y_coef11;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF4.u32),HIHDR_G_RGB2YUV_COEF4.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yCoef12(HI_U32 hihdr_r2y_coef12)
{
	U_HIHDR_G_RGB2YUV_COEF5 HIHDR_G_RGB2YUV_COEF5;

	HIHDR_G_RGB2YUV_COEF5.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF5.u32));
	HIHDR_G_RGB2YUV_COEF5.bits.hihdr_r2y_coef12 = hihdr_r2y_coef12;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF5.u32),HIHDR_G_RGB2YUV_COEF5.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yCoef20(HI_U32 hihdr_r2y_coef20)
{
	U_HIHDR_G_RGB2YUV_COEF6 HIHDR_G_RGB2YUV_COEF6;

	HIHDR_G_RGB2YUV_COEF6.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF6.u32));
	HIHDR_G_RGB2YUV_COEF6.bits.hihdr_r2y_coef20 = hihdr_r2y_coef20;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF6.u32),HIHDR_G_RGB2YUV_COEF6.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yCoef21(HI_U32 hihdr_r2y_coef21)
{
	U_HIHDR_G_RGB2YUV_COEF7 HIHDR_G_RGB2YUV_COEF7;

	HIHDR_G_RGB2YUV_COEF7.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF7.u32));
	HIHDR_G_RGB2YUV_COEF7.bits.hihdr_r2y_coef21 = hihdr_r2y_coef21;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF7.u32),HIHDR_G_RGB2YUV_COEF7.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yCoef22(HI_U32 hihdr_r2y_coef22)
{
	U_HIHDR_G_RGB2YUV_COEF8 HIHDR_G_RGB2YUV_COEF8;

	HIHDR_G_RGB2YUV_COEF8.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF8.u32));
	HIHDR_G_RGB2YUV_COEF8.bits.hihdr_r2y_coef22 = hihdr_r2y_coef22;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_COEF8.u32),HIHDR_G_RGB2YUV_COEF8.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yScale2p(HI_U32 hihdr_r2y_scale2p)
{
	U_HIHDR_G_RGB2YUV_SCALE2P HIHDR_G_RGB2YUV_SCALE2P;

	HIHDR_G_RGB2YUV_SCALE2P.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_SCALE2P.u32));
	HIHDR_G_RGB2YUV_SCALE2P.bits.hihdr_r2y_scale2p = hihdr_r2y_scale2p;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_SCALE2P.u32),HIHDR_G_RGB2YUV_SCALE2P.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yIdc0(HI_U32 hihdr_r2y_idc0)
{
	U_HIHDR_G_RGB2YUV_IDC0 HIHDR_G_RGB2YUV_IDC0;

	HIHDR_G_RGB2YUV_IDC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_IDC0.u32));
	HIHDR_G_RGB2YUV_IDC0.bits.hihdr_r2y_idc0 = hihdr_r2y_idc0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_IDC0.u32),HIHDR_G_RGB2YUV_IDC0.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yIdc1(HI_U32 hihdr_r2y_idc1)
{
	U_HIHDR_G_RGB2YUV_IDC1 HIHDR_G_RGB2YUV_IDC1;

	HIHDR_G_RGB2YUV_IDC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_IDC1.u32));
	HIHDR_G_RGB2YUV_IDC1.bits.hihdr_r2y_idc1 = hihdr_r2y_idc1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_IDC1.u32),HIHDR_G_RGB2YUV_IDC1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yIdc2(HI_U32 hihdr_r2y_idc2)
{
	U_HIHDR_G_RGB2YUV_IDC2 HIHDR_G_RGB2YUV_IDC2;

	HIHDR_G_RGB2YUV_IDC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_IDC2.u32));
	HIHDR_G_RGB2YUV_IDC2.bits.hihdr_r2y_idc2 = hihdr_r2y_idc2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_IDC2.u32),HIHDR_G_RGB2YUV_IDC2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yOdc0(HI_U32 hihdr_r2y_odc0)
{
	U_HIHDR_G_RGB2YUV_ODC0 HIHDR_G_RGB2YUV_ODC0;

	HIHDR_G_RGB2YUV_ODC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_ODC0.u32));
	HIHDR_G_RGB2YUV_ODC0.bits.hihdr_r2y_odc0 = hihdr_r2y_odc0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_ODC0.u32),HIHDR_G_RGB2YUV_ODC0.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yOdc1(HI_U32 hihdr_r2y_odc1)
{
	U_HIHDR_G_RGB2YUV_ODC1 HIHDR_G_RGB2YUV_ODC1;

	HIHDR_G_RGB2YUV_ODC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_ODC1.u32));
	HIHDR_G_RGB2YUV_ODC1.bits.hihdr_r2y_odc1 = hihdr_r2y_odc1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_ODC1.u32),HIHDR_G_RGB2YUV_ODC1.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yOdc2(HI_U32 hihdr_r2y_odc2)
{
	U_HIHDR_G_RGB2YUV_ODC2 HIHDR_G_RGB2YUV_ODC2;

	HIHDR_G_RGB2YUV_ODC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_ODC2.u32));
	HIHDR_G_RGB2YUV_ODC2.bits.hihdr_r2y_odc2 = hihdr_r2y_odc2;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_ODC2.u32),HIHDR_G_RGB2YUV_ODC2.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yClipMin(HI_U32 hihdr_r2y_clip_min)
{
	U_HIHDR_G_RGB2YUV_MIN HIHDR_G_RGB2YUV_MIN;

	HIHDR_G_RGB2YUV_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_MIN.u32));
	HIHDR_G_RGB2YUV_MIN.bits.hihdr_r2y_clip_min = hihdr_r2y_clip_min;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_MIN.u32),HIHDR_G_RGB2YUV_MIN.u32);

	return ;
}


HI_VOID VDP_HIHDR_G_SetHihdrR2yClipMax(HI_U32 hihdr_r2y_clip_max)
{
	U_HIHDR_G_RGB2YUV_MAX HIHDR_G_RGB2YUV_MAX;

	HIHDR_G_RGB2YUV_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_MAX.u32));
	HIHDR_G_RGB2YUV_MAX.bits.hihdr_r2y_clip_max = hihdr_r2y_clip_max;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_G_RGB2YUV_MAX.u32),HIHDR_G_RGB2YUV_MAX.u32);

	return ;
}

//layer_name  : VDP
//module_name : HIHDR_G





