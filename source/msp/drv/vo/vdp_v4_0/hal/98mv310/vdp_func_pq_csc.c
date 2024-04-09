#include "hi_type.h"
#include "vdp_hal_vid.h"
#include "vdp_func_pq_csc.h"

extern volatile S_VDP_REGS_TYPE* pVdpReg;


HI_S32 VDP_FUNC_GetCSCCoef(HI_PQ_CSC_CRTL_S* pstCscCtrl, VDP_CSC_MODE_E enCscMode, HI_PQ_CSC_COEF_S* pstCscCoef, HI_PQ_CSC_DCCOEF_S* pstCscDcCoef)
{
#if 1
	HI_S32 u32Pre = (1<<10);
	HI_S32 u32DcPre = 4;//1:8bit; 4:10bit

	if(enCscMode == VDP_CSC_RGB2YUV_601)//limit range
	{
		pstCscCoef->csc_coef00	   = (HI_S32)(0.257  * u32Pre);
		pstCscCoef->csc_coef01	   = (HI_S32)(0.504  * u32Pre);
		pstCscCoef->csc_coef02	   = (HI_S32)(0.098  * u32Pre);
		pstCscCoef->csc_coef10	   = (HI_S32)(-0.148 * u32Pre);
		pstCscCoef->csc_coef11	   = (HI_S32)(-0.291 * u32Pre);
		pstCscCoef->csc_coef12	   = (HI_S32)( 0.439  * u32Pre);
		pstCscCoef->csc_coef20	   = (HI_S32)( 0.439  * u32Pre);
		pstCscCoef->csc_coef21	   = (HI_S32)(-0.368 * u32Pre);
		pstCscCoef->csc_coef22	   = (HI_S32)(-0.071 * u32Pre);

		pstCscDcCoef->csc_in_dc0  = 0 * u32DcPre;
		pstCscDcCoef->csc_in_dc1  = 0 * u32DcPre;
		pstCscDcCoef->csc_in_dc2  = 0 * u32DcPre;
		pstCscDcCoef->csc_out_dc0 =  16 * u32DcPre;
		pstCscDcCoef->csc_out_dc1 = 128 * u32DcPre;
		pstCscDcCoef->csc_out_dc2 = 128 * u32DcPre;
	}
	else if(enCscMode == VDP_CSC_YUV2RGB_601)//limit range
	{
		pstCscCoef->csc_coef00	   = (HI_S32)( 1.164 * u32Pre);
		pstCscCoef->csc_coef01	   = (HI_S32)(-0.002 * u32Pre);
		pstCscCoef->csc_coef02	   = (HI_S32)( 1.596 * u32Pre);
		pstCscCoef->csc_coef10	   = (HI_S32)( 1.164 * u32Pre);
		pstCscCoef->csc_coef11	   = (HI_S32)(-0.391 * u32Pre);
		pstCscCoef->csc_coef12	   = (HI_S32)(-0.813 * u32Pre);
		pstCscCoef->csc_coef20	   = (HI_S32)( 1.164 * u32Pre);
		pstCscCoef->csc_coef21	   = (HI_S32)(-2.018  * u32Pre);
		pstCscCoef->csc_coef22	   = (HI_S32)(-0.001  * u32Pre);
		pstCscDcCoef->csc_in_dc0  = -16  * u32DcPre;
		pstCscDcCoef->csc_in_dc1  = -128 * u32DcPre;
		pstCscDcCoef->csc_in_dc2  = -128 * u32DcPre;
		pstCscDcCoef->csc_out_dc0 =  0 * u32DcPre;
		pstCscDcCoef->csc_out_dc1 =  0 * u32DcPre;
		pstCscDcCoef->csc_out_dc2 =  0 * u32DcPre;
	}
	else if(enCscMode == VDP_CSC_RGB2YUV_709)//limit range
	{
		pstCscCoef->csc_coef00	   = (HI_S32)( 0.183 * u32Pre);
		pstCscCoef->csc_coef01	   = (HI_S32)( 0.614 * u32Pre);
		pstCscCoef->csc_coef02	   = (HI_S32)( 0.062 * u32Pre);
		pstCscCoef->csc_coef10	   = (HI_S32)(-0.101 * u32Pre);
		pstCscCoef->csc_coef11	   = (HI_S32)(-0.338 * u32Pre);
		pstCscCoef->csc_coef12	   = (HI_S32)( 0.439 * u32Pre);
		pstCscCoef->csc_coef20	   = (HI_S32)( 0.439 * u32Pre);
		pstCscCoef->csc_coef21	   = (HI_S32)(-0.399 * u32Pre);
		pstCscCoef->csc_coef22	   = (HI_S32)(-0.040 * u32Pre);
		pstCscDcCoef->csc_in_dc0  = 0 * u32DcPre;
		pstCscDcCoef->csc_in_dc1  = 0 * u32DcPre;
		pstCscDcCoef->csc_in_dc2  = 0 * u32DcPre;
		pstCscDcCoef->csc_out_dc0 = 16  * u32DcPre;
		pstCscDcCoef->csc_out_dc1 = 128 * u32DcPre;
		pstCscDcCoef->csc_out_dc2 = 128 * u32DcPre;
	}
	else if(enCscMode == VDP_CSC_YUV2RGB_709)//limit range inverse to rgb2yuv
	{
		pstCscCoef->csc_coef00	   = (HI_S32)(    1  * u32Pre);
		pstCscCoef->csc_coef01	   = (HI_S32)(    0  * u32Pre);
		pstCscCoef->csc_coef02	   = (HI_S32)(1.540  * u32Pre);
		pstCscCoef->csc_coef10	   = (HI_S32)(     1 * u32Pre);
		pstCscCoef->csc_coef11	   = (HI_S32)(-0.183 * u32Pre);
		pstCscCoef->csc_coef12	   = (HI_S32)(-0.459 * u32Pre);
		pstCscCoef->csc_coef20	   = (HI_S32)(    1  * u32Pre);
		pstCscCoef->csc_coef21	   = (HI_S32)(1.816  * u32Pre);
		pstCscCoef->csc_coef22	   = (HI_S32)(    0  * u32Pre);
		pstCscDcCoef->csc_in_dc0  = -16  * u32DcPre;
		pstCscDcCoef->csc_in_dc1  = -128 * u32DcPre;
		pstCscDcCoef->csc_in_dc2  = -128 * u32DcPre;
		pstCscDcCoef->csc_out_dc0 = 0 * u32DcPre;
		pstCscDcCoef->csc_out_dc1 = 0 * u32DcPre;
		pstCscDcCoef->csc_out_dc2 = 0 * u32DcPre;
	}
	else if(enCscMode == VDP_CSC_YUV2YUV_709_601)
	{
		pstCscCoef->csc_coef00	   = (HI_S32)(	   1 * u32Pre);
		pstCscCoef->csc_coef01	   = (HI_S32)( 0.100 * u32Pre);
		pstCscCoef->csc_coef02	   = (HI_S32)( 0.191 * u32Pre);
		pstCscCoef->csc_coef10	   = (HI_S32)(	   0 * u32Pre);
		pstCscCoef->csc_coef11	   = (HI_S32)( 0.990 * u32Pre);
		pstCscCoef->csc_coef12	   = (HI_S32)(-0.110 * u32Pre);
		pstCscCoef->csc_coef20	   = (HI_S32)(	   0 * u32Pre);
		pstCscCoef->csc_coef21	   = (HI_S32)(-0.072 * u32Pre);
		pstCscCoef->csc_coef22	   = (HI_S32)( 0.984 * u32Pre);
		pstCscDcCoef->csc_in_dc0  = -16  * u32DcPre;
		pstCscDcCoef->csc_in_dc1  = -128 * u32DcPre;
		pstCscDcCoef->csc_in_dc2  = -128 * u32DcPre;
		pstCscDcCoef->csc_out_dc0 =   16 * u32DcPre;
		pstCscDcCoef->csc_out_dc1 =  128 * u32DcPre;
		pstCscDcCoef->csc_out_dc2 =  128 * u32DcPre;
	}
	else if(enCscMode == VDP_CSC_YUV2YUV_601_709)
	{
		pstCscCoef->csc_coef00	   = (HI_S32)(	   1 * u32Pre);
		pstCscCoef->csc_coef01	   = (HI_S32)(-0.116 * u32Pre);
		pstCscCoef->csc_coef02	   = (HI_S32)( 0.208 * u32Pre);
		pstCscCoef->csc_coef10	   = (HI_S32)(	   0 * u32Pre);
		pstCscCoef->csc_coef11	   = (HI_S32)( 1.018 * u32Pre);
		pstCscCoef->csc_coef12	   = (HI_S32)( 0.114 * u32Pre);
		pstCscCoef->csc_coef20	   = (HI_S32)(	   0 * u32Pre);
		pstCscCoef->csc_coef21	   = (HI_S32)( 0.074 * u32Pre);
		pstCscCoef->csc_coef22	   = (HI_S32)( 1.025 * u32Pre);
		pstCscDcCoef->csc_in_dc0  = -16  * u32DcPre;
		pstCscDcCoef->csc_in_dc1  = -128 * u32DcPre;
		pstCscDcCoef->csc_in_dc2  = -128 * u32DcPre;
		pstCscDcCoef->csc_out_dc0 =   16 * u32DcPre;
		pstCscDcCoef->csc_out_dc1 =  128 * u32DcPre;
		pstCscDcCoef->csc_out_dc2 =  128 * u32DcPre;
	}
	else if(enCscMode == VDP_CSC_YUV2YUV_MIN)
	{
		pstCscCoef->csc_coef00	   = 0;
		pstCscCoef->csc_coef01	   = 0;
		pstCscCoef->csc_coef02	   = 0;
		pstCscCoef->csc_coef10	   = 0;
		pstCscCoef->csc_coef11	   = 0;
		pstCscCoef->csc_coef12	   = 0;
		pstCscCoef->csc_coef20	   = 0;
		pstCscCoef->csc_coef21	   = 0;
		pstCscCoef->csc_coef22	   = 0;
		pstCscDcCoef->csc_in_dc0  = 0;
		pstCscDcCoef->csc_in_dc1  = 0;
		pstCscDcCoef->csc_in_dc2  = 0;
		pstCscDcCoef->csc_out_dc0 = 0;
		pstCscDcCoef->csc_out_dc1 = 0;
		pstCscDcCoef->csc_out_dc2 =  0;
	}
	else
	{
		pstCscCoef->csc_coef00	   = (HI_S32)1 * u32Pre;
		pstCscCoef->csc_coef01	   = (HI_S32)0 * u32Pre;
		pstCscCoef->csc_coef02	   = (HI_S32)0 * u32Pre;
		pstCscCoef->csc_coef10	   = (HI_S32)0 * u32Pre;
		pstCscCoef->csc_coef11	   = (HI_S32)1 * u32Pre;
		pstCscCoef->csc_coef12	   = (HI_S32)0 * u32Pre;
		pstCscCoef->csc_coef20	   = (HI_S32)0 * u32Pre;
		pstCscCoef->csc_coef21	   = (HI_S32)0 * u32Pre;
		pstCscCoef->csc_coef22	   = (HI_S32)1 * u32Pre;
		pstCscDcCoef->csc_in_dc0  = -16  * u32DcPre;
		pstCscDcCoef->csc_in_dc1  = -128 * u32DcPre;
		pstCscDcCoef->csc_in_dc2  = -128 * u32DcPre;
		pstCscDcCoef->csc_out_dc0 =  16 * u32DcPre;
		pstCscDcCoef->csc_out_dc1 = 128 * u32DcPre;
		pstCscDcCoef->csc_out_dc2 = 128 * u32DcPre;
	}

#endif

return HI_SUCCESS;
}

HI_VOID VDP_FUNC_SetCSC1DcCoef(HI_PQ_CSC_DCCOEF_S  *pstCscDcCoef)
{
    U_HIHDR_V_YUV2RGB_IN_DC00    HIHDR_V_YUV2RGB_IN_DC00      ; /* 0xb050 */
    U_HIHDR_V_YUV2RGB_IN_DC01    HIHDR_V_YUV2RGB_IN_DC01      ; /* 0xb054 */
    U_HIHDR_V_YUV2RGB_IN_DC02    HIHDR_V_YUV2RGB_IN_DC02      ; /* 0xb058 */
    U_HIHDR_V_YUV2RGB_OUT_DC00   HIHDR_V_YUV2RGB_OUT_DC00    ; /* 0xb05c */
    U_HIHDR_V_YUV2RGB_OUT_DC01   HIHDR_V_YUV2RGB_OUT_DC01    ; /* 0xb060 */
    U_HIHDR_V_YUV2RGB_OUT_DC02   HIHDR_V_YUV2RGB_OUT_DC02    ; /* 0xb064 */

	HIHDR_V_YUV2RGB_IN_DC00.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC00.u32 ));
	HIHDR_V_YUV2RGB_IN_DC01.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC01.u32 ));
	HIHDR_V_YUV2RGB_IN_DC02.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC02.u32 ));
	HIHDR_V_YUV2RGB_OUT_DC00.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC00.u32));
	HIHDR_V_YUV2RGB_OUT_DC01.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC01.u32));
	HIHDR_V_YUV2RGB_OUT_DC02.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC02.u32));

    HIHDR_V_YUV2RGB_IN_DC00.bits.hihdr_y2r_idc00 = pstCscDcCoef->csc_in_dc0;
    HIHDR_V_YUV2RGB_IN_DC01.bits.hihdr_y2r_idc01 = pstCscDcCoef->csc_in_dc1;
    HIHDR_V_YUV2RGB_IN_DC02.bits.hihdr_y2r_idc02 = pstCscDcCoef->csc_in_dc2;

    HIHDR_V_YUV2RGB_OUT_DC00.bits.hihdr_y2r_odc00 = pstCscDcCoef->csc_out_dc0;
    HIHDR_V_YUV2RGB_OUT_DC01.bits.hihdr_y2r_odc01 = pstCscDcCoef->csc_out_dc1;
    HIHDR_V_YUV2RGB_OUT_DC02.bits.hihdr_y2r_odc02 = pstCscDcCoef->csc_out_dc2;

	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC00.u32 ),HIHDR_V_YUV2RGB_IN_DC00.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC01.u32 ),HIHDR_V_YUV2RGB_IN_DC01.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC02.u32 ),HIHDR_V_YUV2RGB_IN_DC02.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC00.u32),HIHDR_V_YUV2RGB_OUT_DC00.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC01.u32),HIHDR_V_YUV2RGB_OUT_DC01.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC02.u32),HIHDR_V_YUV2RGB_OUT_DC02.u32);

    return ;
}

HI_VOID VDP_FUNC_SetCSC1Coef(HI_PQ_CSC_COEF_S  *pstCscCoef)
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

	HIHDR_V_YUV2RGB_COEF00.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF00.u32  ));
	HIHDR_V_YUV2RGB_COEF01.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF01.u32  ));
	HIHDR_V_YUV2RGB_COEF02.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF02.u32  ));
	HIHDR_V_YUV2RGB_COEF03.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF03.u32  ));
	HIHDR_V_YUV2RGB_COEF04.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF04.u32  ));
	HIHDR_V_YUV2RGB_COEF05.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF05.u32  ));
	HIHDR_V_YUV2RGB_COEF06.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF06.u32  ));
	HIHDR_V_YUV2RGB_COEF07.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF07.u32  ));
	HIHDR_V_YUV2RGB_COEF08.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF08.u32  ));

    HIHDR_V_YUV2RGB_COEF00.bits.hihdr_y2r_coef00 = pstCscCoef->csc_coef00;
    HIHDR_V_YUV2RGB_COEF01.bits.hihdr_y2r_coef01 = pstCscCoef->csc_coef01;
    HIHDR_V_YUV2RGB_COEF02.bits.hihdr_y2r_coef02 = pstCscCoef->csc_coef02;
    HIHDR_V_YUV2RGB_COEF03.bits.hihdr_y2r_coef03 = pstCscCoef->csc_coef10;
    HIHDR_V_YUV2RGB_COEF04.bits.hihdr_y2r_coef04 = pstCscCoef->csc_coef11;
    HIHDR_V_YUV2RGB_COEF05.bits.hihdr_y2r_coef05 = pstCscCoef->csc_coef12;
    HIHDR_V_YUV2RGB_COEF06.bits.hihdr_y2r_coef06 = pstCscCoef->csc_coef20;
    HIHDR_V_YUV2RGB_COEF07.bits.hihdr_y2r_coef07 = pstCscCoef->csc_coef21;
    HIHDR_V_YUV2RGB_COEF08.bits.hihdr_y2r_coef08 = pstCscCoef->csc_coef22;

	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF00.u32  ),HIHDR_V_YUV2RGB_COEF00.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF01.u32  ),HIHDR_V_YUV2RGB_COEF01.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF02.u32  ),HIHDR_V_YUV2RGB_COEF02.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF03.u32  ),HIHDR_V_YUV2RGB_COEF03.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF04.u32  ),HIHDR_V_YUV2RGB_COEF04.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF05.u32  ),HIHDR_V_YUV2RGB_COEF05.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF06.u32  ),HIHDR_V_YUV2RGB_COEF06.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF07.u32  ),HIHDR_V_YUV2RGB_COEF07.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF08.u32  ),HIHDR_V_YUV2RGB_COEF08.u32  );
    return ;
}

HI_VOID VDP_FUNC_SetCSC2DcCoef(HI_PQ_CSC_DCCOEF_S  *pstCscDcCoef)
{
    U_HIHDR_V_YUV2RGB_IN_DC10    HIHDR_V_YUV2RGB_IN_DC10      ; /* 0xb050 */
    U_HIHDR_V_YUV2RGB_IN_DC11    HIHDR_V_YUV2RGB_IN_DC11      ; /* 0xb054 */
    U_HIHDR_V_YUV2RGB_IN_DC12    HIHDR_V_YUV2RGB_IN_DC12      ; /* 0xb058 */
    U_HIHDR_V_YUV2RGB_OUT_DC10   HIHDR_V_YUV2RGB_OUT_DC10    ; /* 0xb05c */
    U_HIHDR_V_YUV2RGB_OUT_DC11   HIHDR_V_YUV2RGB_OUT_DC11    ; /* 0xb060 */
    U_HIHDR_V_YUV2RGB_OUT_DC12   HIHDR_V_YUV2RGB_OUT_DC12    ; /* 0xb064 */

	HIHDR_V_YUV2RGB_IN_DC10.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC10.u32 ));
	HIHDR_V_YUV2RGB_IN_DC11.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC11.u32 ));
	HIHDR_V_YUV2RGB_IN_DC12.u32  = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC12.u32 ));
	HIHDR_V_YUV2RGB_OUT_DC10.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC10.u32));
	HIHDR_V_YUV2RGB_OUT_DC11.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC11.u32));
	HIHDR_V_YUV2RGB_OUT_DC12.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC12.u32));

    HIHDR_V_YUV2RGB_IN_DC10.bits.hihdr_y2r_idc10 = pstCscDcCoef->csc_in_dc0;
    HIHDR_V_YUV2RGB_IN_DC11.bits.hihdr_y2r_idc11 = pstCscDcCoef->csc_in_dc1;
    HIHDR_V_YUV2RGB_IN_DC12.bits.hihdr_y2r_idc12 = pstCscDcCoef->csc_in_dc2;

    HIHDR_V_YUV2RGB_OUT_DC10.bits.hihdr_y2r_odc10 = pstCscDcCoef->csc_out_dc0;
    HIHDR_V_YUV2RGB_OUT_DC11.bits.hihdr_y2r_odc11 = pstCscDcCoef->csc_out_dc1;
    HIHDR_V_YUV2RGB_OUT_DC12.bits.hihdr_y2r_odc12 = pstCscDcCoef->csc_out_dc2;

	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC10.u32 ),HIHDR_V_YUV2RGB_IN_DC10.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC11.u32 ),HIHDR_V_YUV2RGB_IN_DC11.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_IN_DC12.u32 ),HIHDR_V_YUV2RGB_IN_DC12.u32 );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC10.u32),HIHDR_V_YUV2RGB_OUT_DC10.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC11.u32),HIHDR_V_YUV2RGB_OUT_DC11.u32);
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_OUT_DC12.u32),HIHDR_V_YUV2RGB_OUT_DC12.u32);

    return ;
}

HI_VOID VDP_FUNC_SetCSC2Coef(HI_PQ_CSC_COEF_S  *pstCscCoef)
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

	HIHDR_V_YUV2RGB_COEF10.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF10.u32  ));
	HIHDR_V_YUV2RGB_COEF11.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF11.u32  ));
	HIHDR_V_YUV2RGB_COEF12.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF12.u32  ));
	HIHDR_V_YUV2RGB_COEF13.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF13.u32  ));
	HIHDR_V_YUV2RGB_COEF14.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF14.u32  ));
	HIHDR_V_YUV2RGB_COEF15.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF15.u32  ));
	HIHDR_V_YUV2RGB_COEF16.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF16.u32  ));
	HIHDR_V_YUV2RGB_COEF17.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF17.u32  ));
	HIHDR_V_YUV2RGB_COEF18.u32   = VDP_RegRead((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF18.u32  ));


    HIHDR_V_YUV2RGB_COEF10.bits.hihdr_y2r_coef10 = pstCscCoef->csc_coef00;
    HIHDR_V_YUV2RGB_COEF11.bits.hihdr_y2r_coef11 = pstCscCoef->csc_coef01;
    HIHDR_V_YUV2RGB_COEF12.bits.hihdr_y2r_coef12 = pstCscCoef->csc_coef02;
    HIHDR_V_YUV2RGB_COEF13.bits.hihdr_y2r_coef13 = pstCscCoef->csc_coef10;
    HIHDR_V_YUV2RGB_COEF14.bits.hihdr_y2r_coef14 = pstCscCoef->csc_coef11;
    HIHDR_V_YUV2RGB_COEF15.bits.hihdr_y2r_coef15 = pstCscCoef->csc_coef12;
    HIHDR_V_YUV2RGB_COEF16.bits.hihdr_y2r_coef16 = pstCscCoef->csc_coef20;
    HIHDR_V_YUV2RGB_COEF17.bits.hihdr_y2r_coef17 = pstCscCoef->csc_coef21;
    HIHDR_V_YUV2RGB_COEF18.bits.hihdr_y2r_coef18 = pstCscCoef->csc_coef22;


	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF10.u32  ),HIHDR_V_YUV2RGB_COEF10.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF11.u32  ),HIHDR_V_YUV2RGB_COEF11.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF12.u32  ),HIHDR_V_YUV2RGB_COEF12.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF13.u32  ),HIHDR_V_YUV2RGB_COEF13.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF14.u32  ),HIHDR_V_YUV2RGB_COEF14.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF15.u32  ),HIHDR_V_YUV2RGB_COEF15.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF16.u32  ),HIHDR_V_YUV2RGB_COEF16.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF17.u32  ),HIHDR_V_YUV2RGB_COEF17.u32  );
	VDP_RegWrite((HI_ULONG)&(pVdpReg->HIHDR_V_YUV2RGB_COEF18.u32  ),HIHDR_V_YUV2RGB_COEF18.u32  );

    return ;
}

