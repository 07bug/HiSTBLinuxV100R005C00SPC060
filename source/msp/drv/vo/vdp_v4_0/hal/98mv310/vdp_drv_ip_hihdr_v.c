#include "vdp_drv_ip_hihdr_v.h"


//------------------------------------
//  Register Getting & Setting function
//------------------------------------
extern volatile S_VDP_REGS_TYPE *pVdpReg;


HI_VOID VDP_HIHDR_V_SetVDegmm(VDP_HIHDR_V_PQ_CFG_S *stHiHdrPqCfg)
{
    U_VHDR_DEGAMMA_STEP1   VHDR_DEGAMMA_STEP1                ; /* 0xb20c */
    U_VHDR_DEGAMMA_STEP2   VHDR_DEGAMMA_STEP2                ; /* 0xb210 */
    U_VHDR_DEGAMMA_POS1    VHDR_DEGAMMA_POS1                 ; /* 0xb214 */
    U_VHDR_DEGAMMA_POS2    VHDR_DEGAMMA_POS2                 ; /* 0xb218 */
    U_VHDR_DEGAMMA_POS3    VHDR_DEGAMMA_POS3                 ; /* 0xb21c */
    U_VHDR_DEGAMMA_POS4    VHDR_DEGAMMA_POS4                 ; /* 0xb220 */
    U_VHDR_DEGAMMA_NUM1    VHDR_DEGAMMA_NUM1                 ; /* 0xb224 */
    U_VHDR_DEGAMMA_NUM2    VHDR_DEGAMMA_NUM2                 ; /* 0xb228 */

	VHDR_DEGAMMA_STEP1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_STEP1.u32));
	VHDR_DEGAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_STEP2.u32));
	VHDR_DEGAMMA_POS1 .u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_POS1 .u32));
	VHDR_DEGAMMA_POS2 .u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_POS2 .u32));
	VHDR_DEGAMMA_POS3 .u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_POS3 .u32));
	VHDR_DEGAMMA_POS4 .u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_POS4 .u32));
	VHDR_DEGAMMA_NUM1 .u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_NUM1 .u32));
	VHDR_DEGAMMA_NUM2 .u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_NUM2 .u32));

	VHDR_DEGAMMA_STEP1.bits.v_degmm_x1_step = stHiHdrPqCfg->v_degmm_x1_step;
	VHDR_DEGAMMA_STEP1.bits.v_degmm_x2_step = stHiHdrPqCfg->v_degmm_x2_step;
	VHDR_DEGAMMA_STEP1.bits.v_degmm_x3_step = stHiHdrPqCfg->v_degmm_x3_step;
	VHDR_DEGAMMA_STEP1.bits.v_degmm_x4_step = stHiHdrPqCfg->v_degmm_x4_step;
	VHDR_DEGAMMA_STEP2.bits.v_degmm_x5_step = stHiHdrPqCfg->v_degmm_x5_step;
	VHDR_DEGAMMA_STEP2.bits.v_degmm_x6_step = stHiHdrPqCfg->v_degmm_x6_step;
	VHDR_DEGAMMA_STEP2.bits.v_degmm_x7_step = stHiHdrPqCfg->v_degmm_x7_step;
	VHDR_DEGAMMA_STEP2.bits.v_degmm_x8_step = stHiHdrPqCfg->v_degmm_x8_step;

	VHDR_DEGAMMA_POS1.bits.v_degmm_x1_pos = stHiHdrPqCfg->v_degmm_x1_pos;
	VHDR_DEGAMMA_POS1.bits.v_degmm_x2_pos = stHiHdrPqCfg->v_degmm_x2_pos;
	VHDR_DEGAMMA_POS2.bits.v_degmm_x3_pos = stHiHdrPqCfg->v_degmm_x3_pos;
	VHDR_DEGAMMA_POS2.bits.v_degmm_x4_pos = stHiHdrPqCfg->v_degmm_x4_pos;
	VHDR_DEGAMMA_POS3.bits.v_degmm_x5_pos = stHiHdrPqCfg->v_degmm_x5_pos;
	VHDR_DEGAMMA_POS3.bits.v_degmm_x6_pos = stHiHdrPqCfg->v_degmm_x6_pos;
	VHDR_DEGAMMA_POS4.bits.v_degmm_x7_pos = stHiHdrPqCfg->v_degmm_x7_pos;
	VHDR_DEGAMMA_POS4.bits.v_degmm_x8_pos = stHiHdrPqCfg->v_degmm_x8_pos;

	VHDR_DEGAMMA_NUM1.bits.v_degmm_x1_num = stHiHdrPqCfg->v_degmm_x1_num;
	VHDR_DEGAMMA_NUM1.bits.v_degmm_x2_num = stHiHdrPqCfg->v_degmm_x2_num;
	VHDR_DEGAMMA_NUM1.bits.v_degmm_x3_num = stHiHdrPqCfg->v_degmm_x3_num;
	VHDR_DEGAMMA_NUM1.bits.v_degmm_x4_num = stHiHdrPqCfg->v_degmm_x4_num;
	VHDR_DEGAMMA_NUM2.bits.v_degmm_x5_num = stHiHdrPqCfg->v_degmm_x5_num;
	VHDR_DEGAMMA_NUM2.bits.v_degmm_x6_num = stHiHdrPqCfg->v_degmm_x6_num;
	VHDR_DEGAMMA_NUM2.bits.v_degmm_x7_num = stHiHdrPqCfg->v_degmm_x7_num;
	VHDR_DEGAMMA_NUM2.bits.v_degmm_x8_num = stHiHdrPqCfg->v_degmm_x8_num;

	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_STEP1.u32),VHDR_DEGAMMA_STEP1.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_STEP2.u32),VHDR_DEGAMMA_STEP2.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_POS1 .u32),VHDR_DEGAMMA_POS1 .u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_POS2 .u32),VHDR_DEGAMMA_POS2 .u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_POS3 .u32),VHDR_DEGAMMA_POS3 .u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_POS4 .u32),VHDR_DEGAMMA_POS4 .u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_NUM1 .u32),VHDR_DEGAMMA_NUM1 .u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DEGAMMA_NUM2 .u32),VHDR_DEGAMMA_NUM2 .u32);

	return ;
}

HI_VOID VDP_HIHDR_V_SetVTmap(VDP_HIHDR_V_PQ_CFG_S *stHiHdrPqCfg)
{
    U_VHDR_TONEMAP_STEP1   VHDR_TONEMAP_STEP1                ; /* 0xb410 */
    U_VHDR_TONEMAP_STEP2   VHDR_TONEMAP_STEP2                ; /* 0xb414 */
    U_VHDR_TONEMAP_POS1    VHDR_TONEMAP_POS1                 ; /* 0xb418 */
    U_VHDR_TONEMAP_POS2    VHDR_TONEMAP_POS2                 ; /* 0xb41c */
    U_VHDR_TONEMAP_POS3    VHDR_TONEMAP_POS3                 ; /* 0xb420 */
    U_VHDR_TONEMAP_POS4    VHDR_TONEMAP_POS4                 ; /* 0xb424 */
    U_VHDR_TONEMAP_POS5    VHDR_TONEMAP_POS5                 ; /* 0xb428 */
    U_VHDR_TONEMAP_POS6    VHDR_TONEMAP_POS6                 ; /* 0xb42c */
    U_VHDR_TONEMAP_POS7    VHDR_TONEMAP_POS7                 ; /* 0xb430 */
    U_VHDR_TONEMAP_POS8    VHDR_TONEMAP_POS8                 ; /* 0xb434 */
    U_VHDR_TONEMAP_NUM1    VHDR_TONEMAP_NUM1                 ; /* 0xb438 */
    U_VHDR_TONEMAP_NUM2    VHDR_TONEMAP_NUM2                 ; /* 0xb43c */

    U_VHDR_TONEMAP_LUMA_COEF0   VHDR_TONEMAP_LUMA_COEF0      ; /* 0xb470 */
    U_VHDR_TONEMAP_LUMA_COEF1   VHDR_TONEMAP_LUMA_COEF1      ; /* 0xb474 */
    U_VHDR_TONEMAP_LUMA_COEF2   VHDR_TONEMAP_LUMA_COEF2      ; /* 0xb478 */
    U_VHDR_TONEMAP_LUMA_SCALE   VHDR_TONEMAP_LUMA_SCALE      ; /* 0xb47c */
    U_VHDR_TONEMAP_COEF_SCALE   VHDR_TONEMAP_COEF_SCALE      ; /* 0xb480 */
    U_VHDR_TONEMAP_OUT_CLIP_MIN   VHDR_TONEMAP_OUT_CLIP_MIN  ; /* 0xb484 */
    U_VHDR_TONEMAP_OUT_CLIP_MAX   VHDR_TONEMAP_OUT_CLIP_MAX  ; /* 0xb488 */
    U_VHDR_TONEMAP_OUT_DC0   VHDR_TONEMAP_OUT_DC0            ; /* 0xb48c */
    U_VHDR_TONEMAP_OUT_DC1   VHDR_TONEMAP_OUT_DC1            ; /* 0xb490 */
    U_VHDR_TONEMAP_OUT_DC2   VHDR_TONEMAP_OUT_DC2            ; /* 0xb494 */
    U_VHDR_TONEMAP_ALPHA   VHDR_TONEMAP_ALPHA                ; /* 0xb498 */

	VHDR_TONEMAP_STEP1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_STEP1.u32));
	VHDR_TONEMAP_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_STEP2.u32));
	VHDR_TONEMAP_POS1.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS1.u32));
	VHDR_TONEMAP_POS2.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS2.u32));
	VHDR_TONEMAP_POS3.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS3.u32));
	VHDR_TONEMAP_POS4.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS4.u32));
	VHDR_TONEMAP_POS5.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS5.u32));
	VHDR_TONEMAP_POS6.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS6.u32));
	VHDR_TONEMAP_POS7.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS7.u32));
	VHDR_TONEMAP_POS8.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS8.u32));
	VHDR_TONEMAP_NUM1.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_NUM1.u32));
	VHDR_TONEMAP_NUM2.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_NUM2.u32));

	VHDR_TONEMAP_LUMA_COEF0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_LUMA_COEF0));
	VHDR_TONEMAP_LUMA_COEF1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_LUMA_COEF1));
	VHDR_TONEMAP_LUMA_COEF2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_LUMA_COEF2));
	VHDR_TONEMAP_LUMA_SCALE.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_LUMA_SCALE));
	VHDR_TONEMAP_COEF_SCALE.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_COEF_SCALE));
	VHDR_TONEMAP_OUT_DC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_DC0.u32));
	VHDR_TONEMAP_OUT_DC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_DC1.u32));
	VHDR_TONEMAP_OUT_DC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_DC2.u32));
	VHDR_TONEMAP_OUT_CLIP_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_CLIP_MIN.u32));
	VHDR_TONEMAP_OUT_CLIP_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_CLIP_MAX.u32));
	VHDR_TONEMAP_ALPHA.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_ALPHA.u32));

	VHDR_TONEMAP_STEP1.bits.v_tmap_x1_step = stHiHdrPqCfg->v_tmap_x1_step;
	VHDR_TONEMAP_STEP1.bits.v_tmap_x2_step = stHiHdrPqCfg->v_tmap_x2_step;
	VHDR_TONEMAP_STEP1.bits.v_tmap_x3_step = stHiHdrPqCfg->v_tmap_x3_step;
	VHDR_TONEMAP_STEP1.bits.v_tmap_x4_step = stHiHdrPqCfg->v_tmap_x4_step;
	VHDR_TONEMAP_STEP2.bits.v_tmap_x5_step = stHiHdrPqCfg->v_tmap_x5_step;
	VHDR_TONEMAP_STEP2.bits.v_tmap_x6_step = stHiHdrPqCfg->v_tmap_x6_step;
	VHDR_TONEMAP_STEP2.bits.v_tmap_x7_step = stHiHdrPqCfg->v_tmap_x7_step;
	VHDR_TONEMAP_STEP2.bits.v_tmap_x8_step = stHiHdrPqCfg->v_tmap_x8_step;

	VHDR_TONEMAP_POS1.bits.v_tmap_x1_pos = stHiHdrPqCfg->v_tmap_x1_pos;
	VHDR_TONEMAP_POS2.bits.v_tmap_x2_pos = stHiHdrPqCfg->v_tmap_x2_pos;
	VHDR_TONEMAP_POS3.bits.v_tmap_x3_pos = stHiHdrPqCfg->v_tmap_x3_pos;
	VHDR_TONEMAP_POS4.bits.v_tmap_x4_pos = stHiHdrPqCfg->v_tmap_x4_pos;
	VHDR_TONEMAP_POS5.bits.v_tmap_x5_pos = stHiHdrPqCfg->v_tmap_x5_pos;
	VHDR_TONEMAP_POS6.bits.v_tmap_x6_pos = stHiHdrPqCfg->v_tmap_x6_pos;
	VHDR_TONEMAP_POS7.bits.v_tmap_x7_pos = stHiHdrPqCfg->v_tmap_x7_pos;
	VHDR_TONEMAP_POS8.bits.v_tmap_x8_pos = stHiHdrPqCfg->v_tmap_x8_pos;

	VHDR_TONEMAP_NUM1.bits.v_tmap_x4_num = stHiHdrPqCfg->v_tmap_x4_num;
	VHDR_TONEMAP_NUM1.bits.v_tmap_x3_num = stHiHdrPqCfg->v_tmap_x3_num;
	VHDR_TONEMAP_NUM1.bits.v_tmap_x2_num = stHiHdrPqCfg->v_tmap_x2_num;
	VHDR_TONEMAP_NUM1.bits.v_tmap_x1_num = stHiHdrPqCfg->v_tmap_x1_num;
	VHDR_TONEMAP_NUM2.bits.v_tmap_x8_num = stHiHdrPqCfg->v_tmap_x8_num;
	VHDR_TONEMAP_NUM2.bits.v_tmap_x7_num = stHiHdrPqCfg->v_tmap_x7_num;
	VHDR_TONEMAP_NUM2.bits.v_tmap_x6_num = stHiHdrPqCfg->v_tmap_x6_num;
	VHDR_TONEMAP_NUM2.bits.v_tmap_x5_num = stHiHdrPqCfg->v_tmap_x5_num;

	VHDR_TONEMAP_LUMA_COEF0.bits.vhdr_tmap_luma_coef0 = stHiHdrPqCfg->vhdr_tmap_luma_coef0;
	VHDR_TONEMAP_LUMA_COEF1.bits.vhdr_tmap_luma_coef1 = stHiHdrPqCfg->vhdr_tmap_luma_coef1;
	VHDR_TONEMAP_LUMA_COEF2.bits.vhdr_tmap_luma_coef2 = stHiHdrPqCfg->vhdr_tmap_luma_coef2;
	VHDR_TONEMAP_LUMA_SCALE.bits.vhdr_tmap_luma_scale = stHiHdrPqCfg->vhdr_tmap_luma_scale;
	VHDR_TONEMAP_COEF_SCALE.bits.vhdr_tmap_coef_scale = stHiHdrPqCfg->vhdr_tmap_coef_scale;
	VHDR_TONEMAP_OUT_DC0.bits.vhdr_tmap_out_dc0 = stHiHdrPqCfg->vhdr_tmap_out_dc0;
	VHDR_TONEMAP_OUT_DC1.bits.vhdr_tmap_out_dc1 = stHiHdrPqCfg->vhdr_tmap_out_dc1;
	VHDR_TONEMAP_OUT_DC2.bits.vhdr_tmap_out_dc2 = stHiHdrPqCfg->vhdr_tmap_out_dc2;
	VHDR_TONEMAP_OUT_CLIP_MIN.bits.vhdr_tmap_out_clip_min = stHiHdrPqCfg->vhdr_tmap_out_clip_min;
	VHDR_TONEMAP_OUT_CLIP_MAX.bits.vhdr_tmap_out_clip_max = stHiHdrPqCfg->vhdr_tmap_out_clip_max;
	VHDR_TONEMAP_ALPHA.bits.vhdr_tmap_scale_mix_alpha = stHiHdrPqCfg->vhdr_tmap_scale_mix_alpha;
	VHDR_TONEMAP_ALPHA.bits.vhdr_tmap_mix_alpha = stHiHdrPqCfg->vhdr_tmap_mix_alpha;

	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_STEP1.u32),VHDR_TONEMAP_STEP1.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_STEP2.u32),VHDR_TONEMAP_STEP2.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS1.u32 ),VHDR_TONEMAP_POS1.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS2.u32 ),VHDR_TONEMAP_POS2.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS3.u32 ),VHDR_TONEMAP_POS3.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS4.u32 ),VHDR_TONEMAP_POS4.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS5.u32 ),VHDR_TONEMAP_POS5.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS6.u32 ),VHDR_TONEMAP_POS6.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS7.u32 ),VHDR_TONEMAP_POS7.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_POS8.u32 ),VHDR_TONEMAP_POS8.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_NUM1.u32 ),VHDR_TONEMAP_NUM1.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_NUM2.u32 ),VHDR_TONEMAP_NUM2.u32 );

	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_LUMA_COEF0.u32),VHDR_TONEMAP_LUMA_COEF0.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_LUMA_COEF1.u32),VHDR_TONEMAP_LUMA_COEF1.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_LUMA_COEF2.u32),VHDR_TONEMAP_LUMA_COEF2.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_LUMA_SCALE.u32),VHDR_TONEMAP_LUMA_SCALE.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_COEF_SCALE.u32),VHDR_TONEMAP_COEF_SCALE.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_DC0.u32),VHDR_TONEMAP_OUT_DC0.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_DC1.u32),VHDR_TONEMAP_OUT_DC1.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_DC2.u32),VHDR_TONEMAP_OUT_DC2.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_CLIP_MIN.u32),VHDR_TONEMAP_OUT_CLIP_MIN.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_OUT_CLIP_MAX.u32),VHDR_TONEMAP_OUT_CLIP_MAX.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_ALPHA.u32),VHDR_TONEMAP_ALPHA.u32);
	return ;
}

HI_VOID VDP_HIHDR_V_SetVSmap(VDP_HIHDR_V_PQ_CFG_S *stHiHdrPqCfg)
{
    U_VHDR_TONEMAP_SM_STEP1  VHDR_TONEMAP_SM_STEP1          ; /* 0xb440 */
    U_VHDR_TONEMAP_SM_STEP2  VHDR_TONEMAP_SM_STEP2          ; /* 0xb444 */
    U_VHDR_TONEMAP_SM_POS1   VHDR_TONEMAP_SM_POS1            ; /* 0xb448 */
    U_VHDR_TONEMAP_SM_POS2   VHDR_TONEMAP_SM_POS2            ; /* 0xb44c */
    U_VHDR_TONEMAP_SM_POS3   VHDR_TONEMAP_SM_POS3            ; /* 0xb450 */
    U_VHDR_TONEMAP_SM_POS4   VHDR_TONEMAP_SM_POS4            ; /* 0xb454 */
    U_VHDR_TONEMAP_SM_POS5   VHDR_TONEMAP_SM_POS5            ; /* 0xb458 */
    U_VHDR_TONEMAP_SM_POS6   VHDR_TONEMAP_SM_POS6            ; /* 0xb45c */
    U_VHDR_TONEMAP_SM_POS7   VHDR_TONEMAP_SM_POS7            ; /* 0xb460 */
    U_VHDR_TONEMAP_SM_POS8   VHDR_TONEMAP_SM_POS8            ; /* 0xb464 */
    U_VHDR_TONEMAP_SM_NUM1   VHDR_TONEMAP_SM_NUM1            ; /* 0xb468 */
    U_VHDR_TONEMAP_SM_NUM2   VHDR_TONEMAP_SM_NUM2            ; /* 0xb46c */

    VHDR_TONEMAP_SM_STEP1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_STEP1.u32));
    VHDR_TONEMAP_SM_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_STEP2.u32));
    VHDR_TONEMAP_SM_POS1.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS1.u32 ));
    VHDR_TONEMAP_SM_POS2.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS2.u32 ));
    VHDR_TONEMAP_SM_POS3.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS3.u32 ));
    VHDR_TONEMAP_SM_POS4.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS4.u32 ));
    VHDR_TONEMAP_SM_POS5.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS5.u32 ));
    VHDR_TONEMAP_SM_POS6.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS6.u32 ));
    VHDR_TONEMAP_SM_POS7.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS7.u32 ));
    VHDR_TONEMAP_SM_POS8.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS8.u32 ));
    VHDR_TONEMAP_SM_NUM1.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_NUM1.u32 ));
    VHDR_TONEMAP_SM_NUM2.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_NUM2.u32 ));

    VHDR_TONEMAP_SM_STEP1.bits.v_smap_x1_step = stHiHdrPqCfg->v_smap_x1_step;
    VHDR_TONEMAP_SM_STEP1.bits.v_smap_x2_step = stHiHdrPqCfg->v_smap_x2_step;
    VHDR_TONEMAP_SM_STEP1.bits.v_smap_x3_step = stHiHdrPqCfg->v_smap_x3_step;
    VHDR_TONEMAP_SM_STEP1.bits.v_smap_x4_step = stHiHdrPqCfg->v_smap_x4_step;
    VHDR_TONEMAP_SM_STEP2.bits.v_smap_x5_step = stHiHdrPqCfg->v_smap_x5_step;
    VHDR_TONEMAP_SM_STEP2.bits.v_smap_x6_step = stHiHdrPqCfg->v_smap_x6_step;
    VHDR_TONEMAP_SM_STEP2.bits.v_smap_x7_step = stHiHdrPqCfg->v_smap_x7_step;
    VHDR_TONEMAP_SM_STEP2.bits.v_smap_x8_step = stHiHdrPqCfg->v_smap_x8_step;

    VHDR_TONEMAP_SM_POS1.bits.v_smap_x1_pos  = stHiHdrPqCfg->v_smap_x1_pos;
    VHDR_TONEMAP_SM_POS2.bits.v_smap_x2_pos  = stHiHdrPqCfg->v_smap_x2_pos;
    VHDR_TONEMAP_SM_POS3.bits.v_smap_x3_pos  = stHiHdrPqCfg->v_smap_x3_pos;
    VHDR_TONEMAP_SM_POS4.bits.v_smap_x4_pos  = stHiHdrPqCfg->v_smap_x4_pos;
    VHDR_TONEMAP_SM_POS5.bits.v_smap_x5_pos  = stHiHdrPqCfg->v_smap_x5_pos;
    VHDR_TONEMAP_SM_POS6.bits.v_smap_x6_pos  = stHiHdrPqCfg->v_smap_x6_pos;
    VHDR_TONEMAP_SM_POS7.bits.v_smap_x7_pos  = stHiHdrPqCfg->v_smap_x7_pos;
    VHDR_TONEMAP_SM_POS8.bits.v_smap_x8_pos  = stHiHdrPqCfg->v_smap_x8_pos;

    VHDR_TONEMAP_SM_NUM1.bits.v_smap_x1_num  = stHiHdrPqCfg->v_smap_x1_num;
    VHDR_TONEMAP_SM_NUM1.bits.v_smap_x2_num  = stHiHdrPqCfg->v_smap_x2_num;
    VHDR_TONEMAP_SM_NUM1.bits.v_smap_x3_num  = stHiHdrPqCfg->v_smap_x3_num;
    VHDR_TONEMAP_SM_NUM1.bits.v_smap_x4_num  = stHiHdrPqCfg->v_smap_x4_num;
    VHDR_TONEMAP_SM_NUM2.bits.v_smap_x5_num  = stHiHdrPqCfg->v_smap_x5_num;
    VHDR_TONEMAP_SM_NUM2.bits.v_smap_x6_num  = stHiHdrPqCfg->v_smap_x6_num;
    VHDR_TONEMAP_SM_NUM2.bits.v_smap_x7_num  = stHiHdrPqCfg->v_smap_x7_num;
    VHDR_TONEMAP_SM_NUM2.bits.v_smap_x8_num  = stHiHdrPqCfg->v_smap_x8_num;


    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_STEP1.u32),VHDR_TONEMAP_SM_STEP1.u32);
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_STEP2.u32),VHDR_TONEMAP_SM_STEP2.u32);
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS1.u32 ),VHDR_TONEMAP_SM_POS1.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS2.u32 ),VHDR_TONEMAP_SM_POS2.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS3.u32 ),VHDR_TONEMAP_SM_POS3.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS4.u32 ),VHDR_TONEMAP_SM_POS4.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS5.u32 ),VHDR_TONEMAP_SM_POS5.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS6.u32 ),VHDR_TONEMAP_SM_POS6.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS7.u32 ),VHDR_TONEMAP_SM_POS7.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_POS8.u32 ),VHDR_TONEMAP_SM_POS8.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_NUM1.u32 ),VHDR_TONEMAP_SM_NUM1.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_TONEMAP_SM_NUM2.u32 ),VHDR_TONEMAP_SM_NUM2.u32 );
    return ;
}

HI_VOID VDP_HIHDR_V_SetVGmm(VDP_HIHDR_V_PQ_CFG_S *stHiHdrPqCfg)
{
    U_VHDR_GAMMA_STEP1     VHDR_GAMMA_STEP1                  ; /* 0xb50c */
    U_VHDR_GAMMA_STEP2     VHDR_GAMMA_STEP2                  ; /* 0xb510 */
    U_VHDR_GAMMA_POS1      VHDR_GAMMA_POS1                   ; /* 0xb514 */
    U_VHDR_GAMMA_POS2      VHDR_GAMMA_POS2                   ; /* 0xb518 */
    U_VHDR_GAMMA_POS3      VHDR_GAMMA_POS3                   ; /* 0xb51c */
    U_VHDR_GAMMA_POS4      VHDR_GAMMA_POS4                   ; /* 0xb520 */
    U_VHDR_GAMMA_POS5      VHDR_GAMMA_POS5                   ; /* 0xb524 */
    U_VHDR_GAMMA_POS6      VHDR_GAMMA_POS6                   ; /* 0xb528 */
    U_VHDR_GAMMA_POS7      VHDR_GAMMA_POS7                   ; /* 0xb52c */
    U_VHDR_GAMMA_POS8      VHDR_GAMMA_POS8                   ; /* 0xb530 */
    U_VHDR_GAMMA_NUM1      VHDR_GAMMA_NUM1                   ; /* 0xb534 */
    U_VHDR_GAMMA_NUM2      VHDR_GAMMA_NUM2                   ; /* 0xb538 */

    VHDR_GAMMA_STEP1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_STEP1.u32));
    VHDR_GAMMA_STEP2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_STEP2.u32));
    VHDR_GAMMA_POS1.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS1.u32 ));
    VHDR_GAMMA_POS2.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS2.u32 ));
    VHDR_GAMMA_POS3.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS3.u32 ));
    VHDR_GAMMA_POS4.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS4.u32 ));
    VHDR_GAMMA_POS5.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS5.u32 ));
    VHDR_GAMMA_POS6.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS6.u32 ));
    VHDR_GAMMA_POS7.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS7.u32 ));
    VHDR_GAMMA_POS8.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS8.u32 ));
    VHDR_GAMMA_NUM1.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_NUM1.u32 ));
    VHDR_GAMMA_NUM2.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMMA_NUM2.u32 ));

    VHDR_GAMMA_STEP1.bits.v_gmm_x1_step = stHiHdrPqCfg->v_gmm_x1_step;
    VHDR_GAMMA_STEP1.bits.v_gmm_x2_step = stHiHdrPqCfg->v_gmm_x2_step;
    VHDR_GAMMA_STEP1.bits.v_gmm_x3_step = stHiHdrPqCfg->v_gmm_x3_step;
    VHDR_GAMMA_STEP1.bits.v_gmm_x4_step = stHiHdrPqCfg->v_gmm_x4_step;
    VHDR_GAMMA_STEP2.bits.v_gmm_x5_step = stHiHdrPqCfg->v_gmm_x5_step;
    VHDR_GAMMA_STEP2.bits.v_gmm_x6_step = stHiHdrPqCfg->v_gmm_x6_step;
    VHDR_GAMMA_STEP2.bits.v_gmm_x7_step = stHiHdrPqCfg->v_gmm_x7_step;
    VHDR_GAMMA_STEP2.bits.v_gmm_x8_step = stHiHdrPqCfg->v_gmm_x8_step;

    VHDR_GAMMA_POS1.bits.v_gmm_x1_pos  = stHiHdrPqCfg->v_gmm_x1_pos;
    VHDR_GAMMA_POS2.bits.v_gmm_x2_pos  = stHiHdrPqCfg->v_gmm_x2_pos;
    VHDR_GAMMA_POS3.bits.v_gmm_x3_pos  = stHiHdrPqCfg->v_gmm_x3_pos;
    VHDR_GAMMA_POS4.bits.v_gmm_x4_pos  = stHiHdrPqCfg->v_gmm_x4_pos;
    VHDR_GAMMA_POS5.bits.v_gmm_x5_pos  = stHiHdrPqCfg->v_gmm_x5_pos;
    VHDR_GAMMA_POS6.bits.v_gmm_x6_pos  = stHiHdrPqCfg->v_gmm_x6_pos;
    VHDR_GAMMA_POS7.bits.v_gmm_x7_pos  = stHiHdrPqCfg->v_gmm_x7_pos;
    VHDR_GAMMA_POS8.bits.v_gmm_x8_pos  = stHiHdrPqCfg->v_gmm_x8_pos;

    VHDR_GAMMA_NUM1.bits.v_gmm_x1_num  = stHiHdrPqCfg->v_gmm_x1_num;
    VHDR_GAMMA_NUM1.bits.v_gmm_x2_num  = stHiHdrPqCfg->v_gmm_x2_num;
    VHDR_GAMMA_NUM1.bits.v_gmm_x3_num  = stHiHdrPqCfg->v_gmm_x3_num;
    VHDR_GAMMA_NUM1.bits.v_gmm_x4_num  = stHiHdrPqCfg->v_gmm_x4_num;
    VHDR_GAMMA_NUM2.bits.v_gmm_x5_num  = stHiHdrPqCfg->v_gmm_x5_num;
    VHDR_GAMMA_NUM2.bits.v_gmm_x6_num  = stHiHdrPqCfg->v_gmm_x6_num;
    VHDR_GAMMA_NUM2.bits.v_gmm_x7_num  = stHiHdrPqCfg->v_gmm_x7_num;
    VHDR_GAMMA_NUM2.bits.v_gmm_x8_num  = stHiHdrPqCfg->v_gmm_x8_num;

    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_STEP1.u32),VHDR_GAMMA_STEP1.u32);
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_STEP2.u32),VHDR_GAMMA_STEP2.u32);
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS1.u32 ),VHDR_GAMMA_POS1.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS2.u32 ),VHDR_GAMMA_POS2.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS3.u32 ),VHDR_GAMMA_POS3.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS4.u32 ),VHDR_GAMMA_POS4.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS5.u32 ),VHDR_GAMMA_POS5.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS6.u32 ),VHDR_GAMMA_POS6.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS7.u32 ),VHDR_GAMMA_POS7.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_POS8.u32 ),VHDR_GAMMA_POS8.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_NUM1.u32 ),VHDR_GAMMA_NUM1.u32 );
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMMA_NUM2.u32 ),VHDR_GAMMA_NUM2.u32 );
    return ;
}


HI_VOID VDP_HIHDR_V_SetVhdrR2y(VDP_HIHDR_V_PQ_CFG_S *stHiHdrPqCfg)
{
    U_VHDR_RGB2YUV_COEF0   VHDR_RGB2YUV_COEF0                ; /* 0xb704 */
    U_VHDR_RGB2YUV_COEF1   VHDR_RGB2YUV_COEF1                ; /* 0xb708 */
    U_VHDR_RGB2YUV_COEF2   VHDR_RGB2YUV_COEF2                ; /* 0xb70c */
    U_VHDR_RGB2YUV_COEF3   VHDR_RGB2YUV_COEF3                ; /* 0xb710 */
    U_VHDR_RGB2YUV_COEF4   VHDR_RGB2YUV_COEF4                ; /* 0xb714 */
    U_VHDR_RGB2YUV_COEF5   VHDR_RGB2YUV_COEF5                ; /* 0xb718 */
    U_VHDR_RGB2YUV_COEF6   VHDR_RGB2YUV_COEF6                ; /* 0xb71c */
    U_VHDR_RGB2YUV_COEF7   VHDR_RGB2YUV_COEF7                ; /* 0xb720 */
    U_VHDR_RGB2YUV_COEF8   VHDR_RGB2YUV_COEF8                ; /* 0xb724 */
    U_VHDR_RGB2YUV_IDC0    VHDR_RGB2YUV_IDC0                 ; /* 0xb72c */
    U_VHDR_RGB2YUV_IDC1    VHDR_RGB2YUV_IDC1                 ; /* 0xb730 */
    U_VHDR_RGB2YUV_IDC2    VHDR_RGB2YUV_IDC2                 ; /* 0xb734 */
    U_VHDR_RGB2YUV_ODC0    VHDR_RGB2YUV_ODC0                 ; /* 0xb738 */
    U_VHDR_RGB2YUV_ODC1    VHDR_RGB2YUV_ODC1                 ; /* 0xb73c */
    U_VHDR_RGB2YUV_ODC2    VHDR_RGB2YUV_ODC2                 ; /* 0xb740 */
    U_VHDR_RGB2YUV_MIN     VHDR_RGB2YUV_MIN                  ; /* 0xb744 */
    U_VHDR_RGB2YUV_MAX     VHDR_RGB2YUV_MAX                  ; /* 0xb748 */
    U_VHDR_RGB2YUV_SCALE2P VHDR_RGB2YUV_SCALE2P              ; /* 0xb728 */

	VHDR_RGB2YUV_COEF0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF0.u32));
	VHDR_RGB2YUV_COEF1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF1.u32));
	VHDR_RGB2YUV_COEF2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF2.u32));
	VHDR_RGB2YUV_COEF3.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF3.u32));
	VHDR_RGB2YUV_COEF4.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF4.u32));
	VHDR_RGB2YUV_COEF5.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF5.u32));
	VHDR_RGB2YUV_COEF6.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF6.u32));
	VHDR_RGB2YUV_COEF7.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF7.u32));
	VHDR_RGB2YUV_COEF8.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF8.u32));
	VHDR_RGB2YUV_IDC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_IDC0.u32));
	VHDR_RGB2YUV_IDC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_IDC1.u32));
	VHDR_RGB2YUV_IDC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_IDC2.u32));
	VHDR_RGB2YUV_ODC0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_ODC0.u32));
	VHDR_RGB2YUV_ODC1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_ODC1.u32));
	VHDR_RGB2YUV_ODC2.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_ODC2.u32));

    VHDR_RGB2YUV_SCALE2P.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_SCALE2P.u32));
    VHDR_RGB2YUV_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_MIN.u32));
	VHDR_RGB2YUV_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_MAX.u32));

	VHDR_RGB2YUV_COEF0.bits.vhdr_r2y_coef00 = stHiHdrPqCfg->vhdr_r2y_coef00;
	VHDR_RGB2YUV_COEF1.bits.vhdr_r2y_coef01 = stHiHdrPqCfg->vhdr_r2y_coef01;
	VHDR_RGB2YUV_COEF2.bits.vhdr_r2y_coef02 = stHiHdrPqCfg->vhdr_r2y_coef02;
	VHDR_RGB2YUV_COEF3.bits.vhdr_r2y_coef10 = stHiHdrPqCfg->vhdr_r2y_coef10;
	VHDR_RGB2YUV_COEF4.bits.vhdr_r2y_coef11 = stHiHdrPqCfg->vhdr_r2y_coef11;
	VHDR_RGB2YUV_COEF5.bits.vhdr_r2y_coef12 = stHiHdrPqCfg->vhdr_r2y_coef12;
	VHDR_RGB2YUV_COEF6.bits.vhdr_r2y_coef20 = stHiHdrPqCfg->vhdr_r2y_coef20;
	VHDR_RGB2YUV_COEF7.bits.vhdr_r2y_coef21 = stHiHdrPqCfg->vhdr_r2y_coef21;
	VHDR_RGB2YUV_COEF8.bits.vhdr_r2y_coef22 = stHiHdrPqCfg->vhdr_r2y_coef22;

	VHDR_RGB2YUV_IDC0.bits.vhdr_r2y_idc0 = stHiHdrPqCfg->vhdr_r2y_idc0;
	VHDR_RGB2YUV_IDC1.bits.vhdr_r2y_idc1 = stHiHdrPqCfg->vhdr_r2y_idc1;
	VHDR_RGB2YUV_IDC2.bits.vhdr_r2y_idc2 = stHiHdrPqCfg->vhdr_r2y_idc2;
	VHDR_RGB2YUV_ODC0.bits.vhdr_r2y_odc0 = stHiHdrPqCfg->vhdr_r2y_odc0;
	VHDR_RGB2YUV_ODC1.bits.vhdr_r2y_odc1 = stHiHdrPqCfg->vhdr_r2y_odc1;
	VHDR_RGB2YUV_ODC2.bits.vhdr_r2y_odc2 = stHiHdrPqCfg->vhdr_r2y_odc2;

	VHDR_RGB2YUV_MIN.bits.vhdr_r2y_clip_c_min  = stHiHdrPqCfg->vhdr_r2y_clip_c_min;
	VHDR_RGB2YUV_MIN.bits.vhdr_r2y_clip_y_min  = stHiHdrPqCfg->vhdr_r2y_clip_y_min;
	VHDR_RGB2YUV_MAX.bits.vhdr_r2y_clip_c_max  = stHiHdrPqCfg->vhdr_r2y_clip_c_max;
	VHDR_RGB2YUV_MAX.bits.vhdr_r2y_clip_y_max  = stHiHdrPqCfg->vhdr_r2y_clip_y_max;
	VHDR_RGB2YUV_SCALE2P.bits.vhdr_r2y_scale2p = stHiHdrPqCfg->vhdr_r2y_scale2p;
    VHDR_RGB2YUV_SCALE2P.bits.vhdr_cadj_scale2p= stHiHdrPqCfg->vhdr_cadj_scale2p;

	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF0.u32),VHDR_RGB2YUV_COEF0.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF1.u32),VHDR_RGB2YUV_COEF1.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF2.u32),VHDR_RGB2YUV_COEF2.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF3.u32),VHDR_RGB2YUV_COEF3.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF4.u32),VHDR_RGB2YUV_COEF4.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF5.u32),VHDR_RGB2YUV_COEF5.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF6.u32),VHDR_RGB2YUV_COEF6.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF7.u32),VHDR_RGB2YUV_COEF7.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_COEF8.u32),VHDR_RGB2YUV_COEF8.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_IDC0.u32 ),VHDR_RGB2YUV_IDC0.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_IDC1.u32 ),VHDR_RGB2YUV_IDC1.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_IDC2.u32 ),VHDR_RGB2YUV_IDC2.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_ODC0.u32 ),VHDR_RGB2YUV_ODC0.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_ODC1.u32 ),VHDR_RGB2YUV_ODC1.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_ODC2.u32 ),VHDR_RGB2YUV_ODC2.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_MIN.u32  ),VHDR_RGB2YUV_MIN.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_MAX.u32  ),VHDR_RGB2YUV_MAX.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_RGB2YUV_SCALE2P.u32 ),VHDR_RGB2YUV_SCALE2P.u32 );

	return ;
}


HI_VOID VDP_HIHDR_V_SetVhdrGamut(VDP_HIHDR_V_PQ_CFG_S *stHiHdrPqCfg)
{
    U_VHDR_GAMUT_COEF00    VHDR_GAMUT_COEF00                 ; /* 0xb304 */
    U_VHDR_GAMUT_COEF01    VHDR_GAMUT_COEF01                 ; /* 0xb308 */
    U_VHDR_GAMUT_COEF02    VHDR_GAMUT_COEF02                 ; /* 0xb30c */
    U_VHDR_GAMUT_COEF10    VHDR_GAMUT_COEF10                 ; /* 0xb310 */
    U_VHDR_GAMUT_COEF11    VHDR_GAMUT_COEF11                 ; /* 0xb314 */
    U_VHDR_GAMUT_COEF12    VHDR_GAMUT_COEF12                 ; /* 0xb318 */
    U_VHDR_GAMUT_COEF20    VHDR_GAMUT_COEF20                 ; /* 0xb31c */
    U_VHDR_GAMUT_COEF21    VHDR_GAMUT_COEF21                 ; /* 0xb320 */
    U_VHDR_GAMUT_COEF22    VHDR_GAMUT_COEF22                 ; /* 0xb324 */
    U_VHDR_GAMUT_SCALE     VHDR_GAMUT_SCALE                  ; /* 0xb328 */
    U_VHDR_GAMUT_IDC0      VHDR_GAMUT_IDC0                   ; /* 0xb32c */
    U_VHDR_GAMUT_IDC1      VHDR_GAMUT_IDC1                   ; /* 0xb330 */
    U_VHDR_GAMUT_IDC2      VHDR_GAMUT_IDC2                   ; /* 0xb334 */
    U_VHDR_GAMUT_ODC0      VHDR_GAMUT_ODC0                   ; /* 0xb338 */
    U_VHDR_GAMUT_ODC1      VHDR_GAMUT_ODC1                   ; /* 0xb33c */
    U_VHDR_GAMUT_ODC2      VHDR_GAMUT_ODC2                   ; /* 0xb340 */
    U_VHDR_GAMUT_CLIP_MIN   VHDR_GAMUT_CLIP_MIN              ; /* 0xb344 */
    U_VHDR_GAMUT_CLIP_MAX   VHDR_GAMUT_CLIP_MAX              ; /* 0xb348 */

	VHDR_GAMUT_COEF00.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF00.u32));
	VHDR_GAMUT_COEF01.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF01.u32));
	VHDR_GAMUT_COEF02.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF02.u32));
	VHDR_GAMUT_COEF10.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF10.u32));
	VHDR_GAMUT_COEF11.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF11.u32));
	VHDR_GAMUT_COEF12.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF12.u32));
	VHDR_GAMUT_COEF20.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF20.u32));
	VHDR_GAMUT_COEF21.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF21.u32));
	VHDR_GAMUT_COEF22.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF22.u32));
	VHDR_GAMUT_IDC0.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_IDC0.u32));
	VHDR_GAMUT_IDC1.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_IDC1.u32));
	VHDR_GAMUT_IDC2.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_IDC2.u32));
	VHDR_GAMUT_ODC0.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_ODC0.u32));
	VHDR_GAMUT_ODC1.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_ODC1.u32));
	VHDR_GAMUT_ODC2.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_ODC2.u32));

	VHDR_GAMUT_SCALE.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_SCALE.u32));
    VHDR_GAMUT_CLIP_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_CLIP_MIN.u32));
    VHDR_GAMUT_CLIP_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_GAMUT_CLIP_MAX.u32));

	VHDR_GAMUT_COEF00.bits.vhdr_gamut_coef00 = stHiHdrPqCfg->vhdr_gamut_coef00;
	VHDR_GAMUT_COEF01.bits.vhdr_gamut_coef01 = stHiHdrPqCfg->vhdr_gamut_coef01;
	VHDR_GAMUT_COEF02.bits.vhdr_gamut_coef02 = stHiHdrPqCfg->vhdr_gamut_coef02;
	VHDR_GAMUT_COEF10.bits.vhdr_gamut_coef10 = stHiHdrPqCfg->vhdr_gamut_coef10;
	VHDR_GAMUT_COEF11.bits.vhdr_gamut_coef11 = stHiHdrPqCfg->vhdr_gamut_coef11;
	VHDR_GAMUT_COEF12.bits.vhdr_gamut_coef12 = stHiHdrPqCfg->vhdr_gamut_coef12;
	VHDR_GAMUT_COEF20.bits.vhdr_gamut_coef20 = stHiHdrPqCfg->vhdr_gamut_coef20;
	VHDR_GAMUT_COEF21.bits.vhdr_gamut_coef21 = stHiHdrPqCfg->vhdr_gamut_coef21;
	VHDR_GAMUT_COEF22.bits.vhdr_gamut_coef22 = stHiHdrPqCfg->vhdr_gamut_coef22;
	VHDR_GAMUT_IDC0.bits.vhdr_gamut_idc0 = stHiHdrPqCfg->vhdr_gamut_idc0;
	VHDR_GAMUT_IDC1.bits.vhdr_gamut_idc1 = stHiHdrPqCfg->vhdr_gamut_idc1;
	VHDR_GAMUT_IDC2.bits.vhdr_gamut_idc2 = stHiHdrPqCfg->vhdr_gamut_idc2;
	VHDR_GAMUT_ODC0.bits.vhdr_gamut_odc0 = stHiHdrPqCfg->vhdr_gamut_odc0;
	VHDR_GAMUT_ODC1.bits.vhdr_gamut_odc1 = stHiHdrPqCfg->vhdr_gamut_odc1;
	VHDR_GAMUT_ODC2.bits.vhdr_gamut_odc2 = stHiHdrPqCfg->vhdr_gamut_odc2;
	VHDR_GAMUT_SCALE.bits.vhdr_gamut_scale    = stHiHdrPqCfg->vhdr_gamut_scale   ;
	VHDR_GAMUT_CLIP_MIN.bits.vhdr_gamut_clip_min = stHiHdrPqCfg->vhdr_gamut_clip_min;
	VHDR_GAMUT_CLIP_MAX.bits.vhdr_gamut_clip_max = stHiHdrPqCfg->vhdr_gamut_clip_max;

	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF00.u32),VHDR_GAMUT_COEF00.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF01.u32),VHDR_GAMUT_COEF01.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF02.u32),VHDR_GAMUT_COEF02.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF10.u32),VHDR_GAMUT_COEF10.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF11.u32),VHDR_GAMUT_COEF11.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF12.u32),VHDR_GAMUT_COEF12.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF20.u32),VHDR_GAMUT_COEF20.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF21.u32),VHDR_GAMUT_COEF21.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_COEF22.u32),VHDR_GAMUT_COEF22.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_IDC0.u32  ),VHDR_GAMUT_IDC0.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_IDC1.u32  ),VHDR_GAMUT_IDC1.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_IDC2.u32  ),VHDR_GAMUT_IDC2.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_ODC0.u32  ),VHDR_GAMUT_ODC0.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_ODC1.u32  ),VHDR_GAMUT_ODC1.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_ODC2.u32  ),VHDR_GAMUT_ODC2.u32  );

	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_SCALE.u32  ),VHDR_GAMUT_SCALE.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_CLIP_MIN.u32  ),VHDR_GAMUT_CLIP_MIN.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_GAMUT_CLIP_MAX.u32  ),VHDR_GAMUT_CLIP_MAX.u32  );

	return ;
}

HI_VOID VDP_HIHDR_V_SetHihdrY2r1(VDP_HIHDR_V_Y2R_CFG_S *stHiHdrPqCfg)
{
    U_HIHDR_V_YUV2RGB_COEF00     HIHDR_V_YUV2RGB_COEF00        ; /* 0xb004 */
    U_HIHDR_V_YUV2RGB_COEF01     HIHDR_V_YUV2RGB_COEF01        ; /* 0xb008 */
    U_HIHDR_V_YUV2RGB_COEF02     HIHDR_V_YUV2RGB_COEF02        ; /* 0xb00c */
    U_HIHDR_V_YUV2RGB_COEF03     HIHDR_V_YUV2RGB_COEF03        ; /* 0xb010 */
    U_HIHDR_V_YUV2RGB_COEF04     HIHDR_V_YUV2RGB_COEF04        ; /* 0xb014 */
    U_HIHDR_V_YUV2RGB_COEF05     HIHDR_V_YUV2RGB_COEF05        ; /* 0xb018 */
    U_HIHDR_V_YUV2RGB_COEF06     HIHDR_V_YUV2RGB_COEF06        ; /* 0xb01c */
    U_HIHDR_V_YUV2RGB_COEF07     HIHDR_V_YUV2RGB_COEF07        ; /* 0xb020 */
    U_HIHDR_V_YUV2RGB_COEF08     HIHDR_V_YUV2RGB_COEF08        ; /* 0xb024 */
    U_HIHDR_V_YUV2RGB_IN_DC00    HIHDR_V_YUV2RGB_IN_DC00      ; /* 0xb050 */
    U_HIHDR_V_YUV2RGB_IN_DC01    HIHDR_V_YUV2RGB_IN_DC01      ; /* 0xb054 */
    U_HIHDR_V_YUV2RGB_IN_DC02    HIHDR_V_YUV2RGB_IN_DC02      ; /* 0xb058 */
    U_HIHDR_V_YUV2RGB_OUT_DC00   HIHDR_V_YUV2RGB_OUT_DC00    ; /* 0xb05c */
    U_HIHDR_V_YUV2RGB_OUT_DC01   HIHDR_V_YUV2RGB_OUT_DC01    ; /* 0xb060 */
    U_HIHDR_V_YUV2RGB_OUT_DC02   HIHDR_V_YUV2RGB_OUT_DC02    ; /* 0xb064 */
    U_HIHDR_V_YUV2RGB_MIN        HIHDR_V_YUV2RGB_MIN         ; /* 0xb080 */
    U_HIHDR_V_YUV2RGB_MAX        HIHDR_V_YUV2RGB_MAX         ; /* 0xb084 */
	U_HIHDR_V_YUV2RGB_SCALE2P    HIHDR_V_YUV2RGB_SCALE2P;

	HIHDR_V_YUV2RGB_COEF00.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF00.u32  ));
	HIHDR_V_YUV2RGB_COEF01.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF01.u32  ));
	HIHDR_V_YUV2RGB_COEF02.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF02.u32  ));
	HIHDR_V_YUV2RGB_COEF03.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF03.u32  ));
	HIHDR_V_YUV2RGB_COEF04.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF04.u32  ));
	HIHDR_V_YUV2RGB_COEF05.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF05.u32  ));
	HIHDR_V_YUV2RGB_COEF06.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF06.u32  ));
	HIHDR_V_YUV2RGB_COEF07.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF07.u32  ));
	HIHDR_V_YUV2RGB_COEF08.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF08.u32  ));
	HIHDR_V_YUV2RGB_IN_DC00.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC00.u32 ));
	HIHDR_V_YUV2RGB_IN_DC01.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC01.u32 ));
	HIHDR_V_YUV2RGB_IN_DC02.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC02.u32 ));
	HIHDR_V_YUV2RGB_OUT_DC00.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC00.u32));
	HIHDR_V_YUV2RGB_OUT_DC01.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC01.u32));
	HIHDR_V_YUV2RGB_OUT_DC02.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC02.u32));

	HIHDR_V_YUV2RGB_SCALE2P.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_SCALE2P.u32));
	HIHDR_V_YUV2RGB_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_MIN.u32));
	HIHDR_V_YUV2RGB_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_MAX.u32));

    HIHDR_V_YUV2RGB_COEF00.bits.hihdr_y2r_coef00 = stHiHdrPqCfg->hihdr_y2r_coef00;
    HIHDR_V_YUV2RGB_COEF01.bits.hihdr_y2r_coef01 = stHiHdrPqCfg->hihdr_y2r_coef01;
    HIHDR_V_YUV2RGB_COEF02.bits.hihdr_y2r_coef02 = stHiHdrPqCfg->hihdr_y2r_coef02;
    HIHDR_V_YUV2RGB_COEF03.bits.hihdr_y2r_coef03 = stHiHdrPqCfg->hihdr_y2r_coef03;
    HIHDR_V_YUV2RGB_COEF04.bits.hihdr_y2r_coef04 = stHiHdrPqCfg->hihdr_y2r_coef04;
    HIHDR_V_YUV2RGB_COEF05.bits.hihdr_y2r_coef05 = stHiHdrPqCfg->hihdr_y2r_coef05;
    HIHDR_V_YUV2RGB_COEF06.bits.hihdr_y2r_coef06 = stHiHdrPqCfg->hihdr_y2r_coef06;
    HIHDR_V_YUV2RGB_COEF07.bits.hihdr_y2r_coef07 = stHiHdrPqCfg->hihdr_y2r_coef07;
    HIHDR_V_YUV2RGB_COEF08.bits.hihdr_y2r_coef08 = stHiHdrPqCfg->hihdr_y2r_coef08;

    HIHDR_V_YUV2RGB_IN_DC00.bits.hihdr_y2r_idc00 = stHiHdrPqCfg->hihdr_y2r_idc00;
    HIHDR_V_YUV2RGB_IN_DC01.bits.hihdr_y2r_idc01 = stHiHdrPqCfg->hihdr_y2r_idc01;
    HIHDR_V_YUV2RGB_IN_DC02.bits.hihdr_y2r_idc02 = stHiHdrPqCfg->hihdr_y2r_idc02;

    HIHDR_V_YUV2RGB_OUT_DC00.bits.hihdr_y2r_odc00 = stHiHdrPqCfg->hihdr_y2r_odc00;
    HIHDR_V_YUV2RGB_OUT_DC01.bits.hihdr_y2r_odc01 = stHiHdrPqCfg->hihdr_y2r_odc01;
    HIHDR_V_YUV2RGB_OUT_DC02.bits.hihdr_y2r_odc02 = stHiHdrPqCfg->hihdr_y2r_odc02;

	HIHDR_V_YUV2RGB_SCALE2P.bits.hihdr_y2r_v0_scale2p = stHiHdrPqCfg->hihdr_y2r_v0_scale2p;
	HIHDR_V_YUV2RGB_MIN.bits.hihdr_y2r_v0_clip_min = stHiHdrPqCfg->hihdr_y2r_v0_clip_min;
	HIHDR_V_YUV2RGB_MAX.bits.hihdr_y2r_v0_clip_max = stHiHdrPqCfg->hihdr_y2r_v0_clip_max;


	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF00.u32  ),HIHDR_V_YUV2RGB_COEF00.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF01.u32  ),HIHDR_V_YUV2RGB_COEF01.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF02.u32  ),HIHDR_V_YUV2RGB_COEF02.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF03.u32  ),HIHDR_V_YUV2RGB_COEF03.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF04.u32  ),HIHDR_V_YUV2RGB_COEF04.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF05.u32  ),HIHDR_V_YUV2RGB_COEF05.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF06.u32  ),HIHDR_V_YUV2RGB_COEF06.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF07.u32  ),HIHDR_V_YUV2RGB_COEF07.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF08.u32  ),HIHDR_V_YUV2RGB_COEF08.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC00.u32 ),HIHDR_V_YUV2RGB_IN_DC00.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC01.u32 ),HIHDR_V_YUV2RGB_IN_DC01.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC02.u32 ),HIHDR_V_YUV2RGB_IN_DC02.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC00.u32),HIHDR_V_YUV2RGB_OUT_DC00.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC01.u32),HIHDR_V_YUV2RGB_OUT_DC01.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC02.u32),HIHDR_V_YUV2RGB_OUT_DC02.u32);


	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_SCALE2P.u32),HIHDR_V_YUV2RGB_SCALE2P.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_MIN.u32),HIHDR_V_YUV2RGB_MIN.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_MAX.u32),HIHDR_V_YUV2RGB_MAX.u32);
    return ;
}

HI_VOID VDP_HIHDR_V_SetHihdrY2r2(VDP_HIHDR_V_Y2R_CFG_S *stHiHdrPqCfg)
{
    U_HIHDR_V_YUV2RGB_COEF10     HIHDR_V_YUV2RGB_COEF10        ; /* 0xb004 */
    U_HIHDR_V_YUV2RGB_COEF11     HIHDR_V_YUV2RGB_COEF11        ; /* 0xb008 */
    U_HIHDR_V_YUV2RGB_COEF12     HIHDR_V_YUV2RGB_COEF12        ; /* 0xb00c */
    U_HIHDR_V_YUV2RGB_COEF13     HIHDR_V_YUV2RGB_COEF13        ; /* 0xb010 */
    U_HIHDR_V_YUV2RGB_COEF14     HIHDR_V_YUV2RGB_COEF14        ; /* 0xb014 */
    U_HIHDR_V_YUV2RGB_COEF15     HIHDR_V_YUV2RGB_COEF15        ; /* 0xb018 */
    U_HIHDR_V_YUV2RGB_COEF16     HIHDR_V_YUV2RGB_COEF16        ; /* 0xb01c */
    U_HIHDR_V_YUV2RGB_COEF17     HIHDR_V_YUV2RGB_COEF17        ; /* 0xb020 */
    U_HIHDR_V_YUV2RGB_COEF18     HIHDR_V_YUV2RGB_COEF18        ; /* 0xb024 */
    U_HIHDR_V_YUV2RGB_IN_DC10    HIHDR_V_YUV2RGB_IN_DC10      ; /* 0xb050 */
    U_HIHDR_V_YUV2RGB_IN_DC11    HIHDR_V_YUV2RGB_IN_DC11      ; /* 0xb054 */
    U_HIHDR_V_YUV2RGB_IN_DC12    HIHDR_V_YUV2RGB_IN_DC12      ; /* 0xb058 */
    U_HIHDR_V_YUV2RGB_OUT_DC10   HIHDR_V_YUV2RGB_OUT_DC10    ; /* 0xb05c */
    U_HIHDR_V_YUV2RGB_OUT_DC11   HIHDR_V_YUV2RGB_OUT_DC11    ; /* 0xb060 */
    U_HIHDR_V_YUV2RGB_OUT_DC12   HIHDR_V_YUV2RGB_OUT_DC12    ; /* 0xb064 */
    U_HIHDR_V_YUV2RGB_MIN        HIHDR_V_YUV2RGB_MIN         ; /* 0xb080 */
    U_HIHDR_V_YUV2RGB_MAX        HIHDR_V_YUV2RGB_MAX         ; /* 0xb084 */
	U_HIHDR_V_YUV2RGB_SCALE2P    HIHDR_V_YUV2RGB_SCALE2P;

	HIHDR_V_YUV2RGB_COEF10.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF10.u32  ));
	HIHDR_V_YUV2RGB_COEF11.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF11.u32  ));
	HIHDR_V_YUV2RGB_COEF12.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF12.u32  ));
	HIHDR_V_YUV2RGB_COEF13.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF13.u32  ));
	HIHDR_V_YUV2RGB_COEF14.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF14.u32  ));
	HIHDR_V_YUV2RGB_COEF15.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF15.u32  ));
	HIHDR_V_YUV2RGB_COEF16.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF16.u32  ));
	HIHDR_V_YUV2RGB_COEF17.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF17.u32  ));
	HIHDR_V_YUV2RGB_COEF18.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF18.u32  ));
	HIHDR_V_YUV2RGB_IN_DC10.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC10.u32 ));
	HIHDR_V_YUV2RGB_IN_DC11.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC11.u32 ));
	HIHDR_V_YUV2RGB_IN_DC12.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC12.u32 ));
	HIHDR_V_YUV2RGB_OUT_DC10.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC10.u32));
	HIHDR_V_YUV2RGB_OUT_DC11.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC11.u32));
	HIHDR_V_YUV2RGB_OUT_DC12.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC12.u32));

	HIHDR_V_YUV2RGB_SCALE2P.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_SCALE2P.u32));
	HIHDR_V_YUV2RGB_MIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_MIN.u32));
	HIHDR_V_YUV2RGB_MAX.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_MAX.u32));

    HIHDR_V_YUV2RGB_COEF10.bits.hihdr_y2r_coef10 = stHiHdrPqCfg->hihdr_y2r_coef10;
    HIHDR_V_YUV2RGB_COEF11.bits.hihdr_y2r_coef11 = stHiHdrPqCfg->hihdr_y2r_coef11;
    HIHDR_V_YUV2RGB_COEF12.bits.hihdr_y2r_coef12 = stHiHdrPqCfg->hihdr_y2r_coef12;
    HIHDR_V_YUV2RGB_COEF13.bits.hihdr_y2r_coef13 = stHiHdrPqCfg->hihdr_y2r_coef13;
    HIHDR_V_YUV2RGB_COEF14.bits.hihdr_y2r_coef14 = stHiHdrPqCfg->hihdr_y2r_coef14;
    HIHDR_V_YUV2RGB_COEF15.bits.hihdr_y2r_coef15 = stHiHdrPqCfg->hihdr_y2r_coef15;
    HIHDR_V_YUV2RGB_COEF16.bits.hihdr_y2r_coef16 = stHiHdrPqCfg->hihdr_y2r_coef16;
    HIHDR_V_YUV2RGB_COEF17.bits.hihdr_y2r_coef17 = stHiHdrPqCfg->hihdr_y2r_coef17;
    HIHDR_V_YUV2RGB_COEF18.bits.hihdr_y2r_coef18 = stHiHdrPqCfg->hihdr_y2r_coef18;

    HIHDR_V_YUV2RGB_IN_DC10.bits.hihdr_y2r_idc10 = stHiHdrPqCfg->hihdr_y2r_idc10;
    HIHDR_V_YUV2RGB_IN_DC11.bits.hihdr_y2r_idc11 = stHiHdrPqCfg->hihdr_y2r_idc11;
    HIHDR_V_YUV2RGB_IN_DC12.bits.hihdr_y2r_idc12 = stHiHdrPqCfg->hihdr_y2r_idc12;

    HIHDR_V_YUV2RGB_OUT_DC10.bits.hihdr_y2r_odc10 = stHiHdrPqCfg->hihdr_y2r_odc10;
    HIHDR_V_YUV2RGB_OUT_DC11.bits.hihdr_y2r_odc11 = stHiHdrPqCfg->hihdr_y2r_odc11;
    HIHDR_V_YUV2RGB_OUT_DC12.bits.hihdr_y2r_odc12 = stHiHdrPqCfg->hihdr_y2r_odc12;

	HIHDR_V_YUV2RGB_SCALE2P.bits.hihdr_y2r_v1_scale2p = stHiHdrPqCfg->hihdr_y2r_v1_scale2p;
	HIHDR_V_YUV2RGB_MIN.bits.hihdr_y2r_v1_clip_min = stHiHdrPqCfg->hihdr_y2r_v1_clip_min;
	HIHDR_V_YUV2RGB_MAX.bits.hihdr_y2r_v1_clip_max = stHiHdrPqCfg->hihdr_y2r_v1_clip_max;


	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF10.u32  ),HIHDR_V_YUV2RGB_COEF10.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF11.u32  ),HIHDR_V_YUV2RGB_COEF11.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF12.u32  ),HIHDR_V_YUV2RGB_COEF12.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF13.u32  ),HIHDR_V_YUV2RGB_COEF13.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF14.u32  ),HIHDR_V_YUV2RGB_COEF14.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF15.u32  ),HIHDR_V_YUV2RGB_COEF15.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF16.u32  ),HIHDR_V_YUV2RGB_COEF16.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF17.u32  ),HIHDR_V_YUV2RGB_COEF17.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF18.u32  ),HIHDR_V_YUV2RGB_COEF18.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC10.u32 ),HIHDR_V_YUV2RGB_IN_DC10.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC11.u32 ),HIHDR_V_YUV2RGB_IN_DC11.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC12.u32 ),HIHDR_V_YUV2RGB_IN_DC12.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC10.u32),HIHDR_V_YUV2RGB_OUT_DC10.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC11.u32),HIHDR_V_YUV2RGB_OUT_DC11.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC12.u32),HIHDR_V_YUV2RGB_OUT_DC12.u32);


	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_SCALE2P.u32),HIHDR_V_YUV2RGB_SCALE2P.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_MIN.u32),HIHDR_V_YUV2RGB_MIN.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_MAX.u32),HIHDR_V_YUV2RGB_MAX.u32);
    return ;
}

HI_VOID VDP_HIHDR_V_SetVhdrDitherCtrl(VDP_HIHDR_V_CFG_S *pstHiHdrCfg)
{
	U_VHDR_DITHER_CTRL     VHDR_DITHER_CTRL;
    U_VHDR_DITHER_THR      VHDR_DITHER_THR                   ; /* 0xb604 */
    U_VHDR_DITHER_SED_Y0   VHDR_DITHER_SED_Y0                ; /* 0xb608 */
    U_VHDR_DITHER_SED_U0   VHDR_DITHER_SED_U0                ; /* 0xb60c */
    U_VHDR_DITHER_SED_V0   VHDR_DITHER_SED_V0                ; /* 0xb610 */
    U_VHDR_DITHER_SED_W0   VHDR_DITHER_SED_W0                ; /* 0xb614 */
    U_VHDR_DITHER_SED_Y1   VHDR_DITHER_SED_Y1                ; /* 0xb618 */
    U_VHDR_DITHER_SED_U1   VHDR_DITHER_SED_U1                ; /* 0xb61c */
    U_VHDR_DITHER_SED_V1   VHDR_DITHER_SED_V1                ; /* 0xb620 */
    U_VHDR_DITHER_SED_W1   VHDR_DITHER_SED_W1                ; /* 0xb624 */

	VHDR_DITHER_CTRL.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_CTRL.u32));
	VHDR_DITHER_SED_Y0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_Y0.u32));
	VHDR_DITHER_SED_U0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_U0.u32));
	VHDR_DITHER_SED_V0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_V0.u32));
	VHDR_DITHER_SED_W0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_W0.u32));
	VHDR_DITHER_SED_Y1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_Y1.u32));
	VHDR_DITHER_SED_U1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_U1.u32));
	VHDR_DITHER_SED_V1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_V1.u32));
	VHDR_DITHER_SED_W1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_W1.u32));
	VHDR_DITHER_THR.u32    = VDP_RegRead((HI_ULONG)&(pVdpReg->VHDR_DITHER_THR.u32));

	VHDR_DITHER_CTRL.bits.vhdr_dither_en          = pstHiHdrCfg->vhdr_dither_en;
	VHDR_DITHER_CTRL.bits.vhdr_dither_round_unlim = pstHiHdrCfg->vhdr_dither_round_unlim;
	VHDR_DITHER_CTRL.bits.vhdr_dither_mode        = pstHiHdrCfg->vhdr_dither_mode;
	VHDR_DITHER_CTRL.bits.vhdr_dither_tap_mode    = pstHiHdrCfg->vhdr_dither_tap_mode;
	VHDR_DITHER_CTRL.bits.vhdr_dither_tap_mode    = pstHiHdrCfg->vhdr_dither_tap_mode;
	VHDR_DITHER_CTRL.bits.vhdr_dither_round       = pstHiHdrCfg->vhdr_dither_round;
	VHDR_DITHER_CTRL.bits.vhdr_dither_domain_mode = pstHiHdrCfg->vhdr_dither_domain_mode;

	VHDR_DITHER_SED_Y0.bits.vhdr_dither_sed_y0 = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0;
	VHDR_DITHER_SED_U0.bits.vhdr_dither_sed_u0 = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0;
	VHDR_DITHER_SED_V0.bits.vhdr_dither_sed_v0 = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0;
	VHDR_DITHER_SED_W0.bits.vhdr_dither_sed_w0 = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0;
	VHDR_DITHER_SED_Y1.bits.vhdr_dither_sed_y1 = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1;
	VHDR_DITHER_SED_U1.bits.vhdr_dither_sed_u1 = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1;
	VHDR_DITHER_SED_V1.bits.vhdr_dither_sed_v1 = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1;
	VHDR_DITHER_SED_W1.bits.vhdr_dither_sed_w1 = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1;
	VHDR_DITHER_THR.bits.vhdr_dither_thr_max   = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max;
	VHDR_DITHER_THR.bits.vhdr_dither_thr_min   = pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min;

	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_CTRL.u32),VHDR_DITHER_CTRL.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_Y0.u32),VHDR_DITHER_SED_Y0.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_U0.u32),VHDR_DITHER_SED_U0.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_V0.u32),VHDR_DITHER_SED_V0.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_W0.u32),VHDR_DITHER_SED_W0.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_Y1.u32),VHDR_DITHER_SED_Y1.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_U1.u32),VHDR_DITHER_SED_U1.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_V1.u32),VHDR_DITHER_SED_V1.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_SED_W1.u32),VHDR_DITHER_SED_W1.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->VHDR_DITHER_THR.u32),VHDR_DITHER_THR.u32);

    return ;
}

//#define SLOW
HI_S32 VDP_DRV_SetHiHdrCfg(HI_U32 u32LayerId, VDP_HIHDR_V_CFG_S *pstHiHdrCfg)
{
	VDP_HIHDR_V_SetVhdrCkGtEn          (pstHiHdrCfg->vhdr_ck_gt_en);
	VDP_HIHDR_V_SetVhdrGamutBind       (pstHiHdrCfg->vhdr_gamut_bind);
	VDP_HIHDR_V_SetVhdrEn              (pstHiHdrCfg->vhdr_en);
	VDP_HIHDR_V_SetVhdrTmapEn          (pstHiHdrCfg->vhdr_tmap_en);
	VDP_HIHDR_V_SetVhdrDegmmEn         (pstHiHdrCfg->vhdr_degmm_en);
	VDP_HIHDR_V_SetVhdrGmmEn           (pstHiHdrCfg->vhdr_gmm_en);
    VDP_HIHDR_V_SetVhdrCadjEn          (pstHiHdrCfg->vhdr_cadj_en);
	VDP_HIHDR_V_SetVhdrGamutEn         (pstHiHdrCfg->vhdr_gamut_en);
	VDP_HIHDR_V_SetVhdrR2yEn           (pstHiHdrCfg->vhdr_r2y_en);


    if (pstHiHdrCfg->vhdr_degmm_en)
    {
        VDP_HIHDR_V_SetVDegmm          (&pstHiHdrCfg->stHiHdrPqCfg);
    }



    if (pstHiHdrCfg->vhdr_gamut_en)
    {
        VDP_HIHDR_V_SetVhdrGamut       (&pstHiHdrCfg->stHiHdrPqCfg);
    }



    if (pstHiHdrCfg->vhdr_tmap_en)
    {
        VDP_HIHDR_V_SetVTmap           (&pstHiHdrCfg->stHiHdrPqCfg);
    }



    if (pstHiHdrCfg->vhdr_tmap_en)
    {
        VDP_HIHDR_V_SetVSmap           (&pstHiHdrCfg->stHiHdrPqCfg);
    }




    if(pstHiHdrCfg->vhdr_gmm_en)
    {
        VDP_HIHDR_V_SetVGmm            (&pstHiHdrCfg->stHiHdrPqCfg);
    }



	if(pstHiHdrCfg->vhdr_dither_en)
	{
        VDP_HIHDR_V_SetVhdrDitherCtrl  (pstHiHdrCfg);
	}



    if(pstHiHdrCfg->vhdr_r2y_en)
    {
        VDP_HIHDR_V_SetVhdrR2y         (&pstHiHdrCfg->stHiHdrPqCfg);
    }


    /*Y2R*/
	VDP_HIHDR_V_SetHihdrVDemoPos       (pstHiHdrCfg->hihdr_v_demo_pos);
	VDP_HIHDR_V_SetHihdrVDemoMode      (pstHiHdrCfg->hihdr_v_demo_mode);
	VDP_HIHDR_V_SetHihdrVDemoEn        (pstHiHdrCfg->hihdr_v_demo_en);
	VDP_HIHDR_V_SetHihdrY2rCkGtEn      (pstHiHdrCfg->hihdr_y2r_ck_gt_en);
	VDP_HIHDR_V_SetHihdrY2rEn          (pstHiHdrCfg->hihdr_y2r_en);

    if(pstHiHdrCfg->hihdr_y2r_en)
    {
        if (u32LayerId == VDP_LAYER_VID0)
        {
            VDP_HIHDR_V_SetHihdrV0VhdrEn       (pstHiHdrCfg->hihdr_v0_vhdr_en);
            VDP_HIHDR_V_SetHihdrV0ClEn         (pstHiHdrCfg->hihdr_v0_cl_en);
            VDP_HIHDR_V_SetHihdrV0Y2rEn        (pstHiHdrCfg->hihdr_v0_y2r_en);

            VDP_HIHDR_V_SetHihdrY2r1(&pstHiHdrCfg->stHiHdrY2RCfg);

        }
        else
        {
            VDP_HIHDR_V_SetHihdrV1VhdrEn       (pstHiHdrCfg->hihdr_v1_vhdr_en);
            VDP_HIHDR_V_SetHihdrV1ClEn         (pstHiHdrCfg->hihdr_v1_cl_en);
            VDP_HIHDR_V_SetHihdrV1Y2rEn        (pstHiHdrCfg->hihdr_v1_y2r_en);

            VDP_HIHDR_V_SetHihdrY2r2(&pstHiHdrCfg->stHiHdrY2RCfg);

        }
    }
    return HI_SUCCESS;
}


//------------------------------------
//  Initial function for tc
//------------------------------------



