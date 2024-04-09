#include "hi_type.h"
#include "vdp_hal_vid.h"
#include "vdp_func_pq_csc.h"



HI_S32 VDP_FUNC_GetCSCCoef(HI_PQ_CSC_CRTL_S *pstCscCtrl, VDP_CSC_MODE_E enCscMode, HI_PQ_CSC_COEF_S *pstCscCoef, HI_PQ_CSC_DCCOEF_S *pstCscDcCoef)
{
#if 1
    HI_S32 s32Pre = (1 << 10);
    HI_S32 s32DcPre = 4;//1:8bit; 4:10bit


    //  if(HI_PQ_CSC_TUNING_V3 == pstCscCtrl->enCscType)
    //  {
    //      s32Pre = (1<<10);
    //  }
    //  else //if(pstCscCtrl->enCscType == HI_PQ_CSC_TUNING_V0)
    //  {
    //      s32Pre  = (1 << 13);
    //  }

#if 1



    if (enCscMode == VDP_CSC_RGB2YUV_601) //limit range
    {
        pstCscCoef->csc_coef00     = (HI_S32)(0.257  * s32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)(0.504  * s32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)(0.098  * s32Pre);
        pstCscCoef->csc_coef10     = (HI_S32)(-0.148 * s32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)(-0.291 * s32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)( 0.439  * s32Pre);
        pstCscCoef->csc_coef20     = (HI_S32)( 0.439  * s32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)(-0.368 * s32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)(-0.071 * s32Pre);

        pstCscDcCoef->csc_in_dc0  = 0 * s32DcPre;
        pstCscDcCoef->csc_in_dc1  = 0 * s32DcPre;
        pstCscDcCoef->csc_in_dc2  = 0 * s32DcPre;
        pstCscDcCoef->csc_out_dc0 =  16 * s32DcPre;
        pstCscDcCoef->csc_out_dc1 = 128 * s32DcPre;
        pstCscDcCoef->csc_out_dc2 = 128 * s32DcPre;
    }
    else if (enCscMode == VDP_CSC_YUV2RGB_601) //limit range
    {
        pstCscCoef->csc_coef00     = (HI_S32)( 1.164 * s32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)(-0.002 * s32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)( 1.596 * s32Pre);
        pstCscCoef->csc_coef10     = (HI_S32)( 1.164 * s32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)(-0.391 * s32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)(-0.813 * s32Pre);
        pstCscCoef->csc_coef20     = (HI_S32)( 1.164 * s32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)(-2.018  * s32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)(-0.001  * s32Pre);
        pstCscDcCoef->csc_in_dc0  = -16  * s32DcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * s32DcPre;
        pstCscDcCoef->csc_in_dc2  = -128 * s32DcPre;
        pstCscDcCoef->csc_out_dc0 =  0 * s32DcPre;
        pstCscDcCoef->csc_out_dc1 =  0 * s32DcPre;
        pstCscDcCoef->csc_out_dc2 =  0 * s32DcPre;
    }
    else if (enCscMode == VDP_CSC_RGB2YUV_709) //limit range
    {
        pstCscCoef->csc_coef00     = (HI_S32)( 0.183 * s32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)( 0.614 * s32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)( 0.062 * s32Pre);
        pstCscCoef->csc_coef10     = (HI_S32)(-0.101 * s32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)(-0.338 * s32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)( 0.439 * s32Pre);
        pstCscCoef->csc_coef20     = (HI_S32)( 0.439 * s32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)(-0.399 * s32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)(-0.040 * s32Pre);
        pstCscDcCoef->csc_in_dc0  = 0 * s32DcPre;
        pstCscDcCoef->csc_in_dc1  = 0 * s32DcPre;
        pstCscDcCoef->csc_in_dc2  = 0 * s32DcPre;
        pstCscDcCoef->csc_out_dc0 = 16  * s32DcPre;
        pstCscDcCoef->csc_out_dc1 = 128 * s32DcPre;
        pstCscDcCoef->csc_out_dc2 = 128 * s32DcPre;
    }
    else if (enCscMode == VDP_CSC_YUV2RGB_709) //limit range inverse to rgb2yuv
    {
        pstCscCoef->csc_coef00     = (HI_S32)( 1.164 * s32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)( 0     * s32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)( 1.793 * s32Pre);
        pstCscCoef->csc_coef10     = (HI_S32)( 1.164 * s32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)(-0.213 * s32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)(-0.534 * s32Pre);
        pstCscCoef->csc_coef20     = (HI_S32)( 1.164 * s32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)( 2.115 * s32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)( 0     * s32Pre);
        pstCscDcCoef->csc_in_dc0  = -16  * s32DcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * s32DcPre;
        pstCscDcCoef->csc_in_dc2  = -128 * s32DcPre;
        pstCscDcCoef->csc_out_dc0 = 0 * s32DcPre;
        pstCscDcCoef->csc_out_dc1 = 0 * s32DcPre;
        pstCscDcCoef->csc_out_dc2 = 0 * s32DcPre;
    }
    else if (enCscMode == VDP_CSC_YUV2YUV_709_601)
    {
        pstCscCoef->csc_coef00     = (HI_S32)(     1 * s32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)( 0.100 * s32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)( 0.191 * s32Pre);
        pstCscCoef->csc_coef10     = (HI_S32)(     0 * s32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)( 0.990 * s32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)(-0.110 * s32Pre);
        pstCscCoef->csc_coef20     = (HI_S32)(     0 * s32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)(-0.072 * s32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)( 0.984 * s32Pre);
        pstCscDcCoef->csc_in_dc0  = -16  * s32DcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * s32DcPre;
        pstCscDcCoef->csc_in_dc2  = -128 * s32DcPre;
        pstCscDcCoef->csc_out_dc0 =   16 * s32DcPre;
        pstCscDcCoef->csc_out_dc1 =  128 * s32DcPre;
        pstCscDcCoef->csc_out_dc2 =  128 * s32DcPre;
    }
    else if (enCscMode == VDP_CSC_YUV2YUV_601_709)
    {
        pstCscCoef->csc_coef00     = (HI_S32)(     1 * s32Pre);
        pstCscCoef->csc_coef01     = (HI_S32)(-0.116 * s32Pre);
        pstCscCoef->csc_coef02     = (HI_S32)( 0.208 * s32Pre);
        pstCscCoef->csc_coef10     = (HI_S32)(     0 * s32Pre);
        pstCscCoef->csc_coef11     = (HI_S32)( 1.018 * s32Pre);
        pstCscCoef->csc_coef12     = (HI_S32)( 0.114 * s32Pre);
        pstCscCoef->csc_coef20     = (HI_S32)(     0 * s32Pre);
        pstCscCoef->csc_coef21     = (HI_S32)( 0.074 * s32Pre);
        pstCscCoef->csc_coef22     = (HI_S32)( 1.025 * s32Pre);
        pstCscDcCoef->csc_in_dc0  = -16  * s32DcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * s32DcPre;
        pstCscDcCoef->csc_in_dc2  = -128 * s32DcPre;
        pstCscDcCoef->csc_out_dc0 =   16 * s32DcPre;
        pstCscDcCoef->csc_out_dc1 =  128 * s32DcPre;
        pstCscDcCoef->csc_out_dc2 =  128 * s32DcPre;
    }
    else if (enCscMode == VDP_CSC_YUV2YUV_MIN)
    {
        pstCscCoef->csc_coef00     = 0;
        pstCscCoef->csc_coef01     = 0;
        pstCscCoef->csc_coef02     = 0;
        pstCscCoef->csc_coef10     = 0;
        pstCscCoef->csc_coef11     = 0;
        pstCscCoef->csc_coef12     = 0;
        pstCscCoef->csc_coef20     = 0;
        pstCscCoef->csc_coef21     = 0;
        pstCscCoef->csc_coef22     = 0;
        pstCscDcCoef->csc_in_dc0  = 0;
        pstCscDcCoef->csc_in_dc1  = 0;
        pstCscDcCoef->csc_in_dc2  = 0;
        pstCscDcCoef->csc_out_dc0 = 0;
        pstCscDcCoef->csc_out_dc1 = 0;
        pstCscDcCoef->csc_out_dc2 =  0;
    }
    else
    {
        pstCscCoef->csc_coef00     = 1 * s32Pre;
        pstCscCoef->csc_coef01     = 0 * s32Pre;
        pstCscCoef->csc_coef02     = 0 * s32Pre;
        pstCscCoef->csc_coef10     = 0 * s32Pre;
        pstCscCoef->csc_coef11     = 1 * s32Pre;
        pstCscCoef->csc_coef12     = 0 * s32Pre;
        pstCscCoef->csc_coef20     = 0 * s32Pre;
        pstCscCoef->csc_coef21     = 0 * s32Pre;
        pstCscCoef->csc_coef22     = 1 * s32Pre;
        pstCscDcCoef->csc_in_dc0  = -16  * s32DcPre;
        pstCscDcCoef->csc_in_dc1  = -128 * s32DcPre;
        pstCscDcCoef->csc_in_dc2  = -128 * s32DcPre;
        pstCscDcCoef->csc_out_dc0 =  16 * s32DcPre;
        pstCscDcCoef->csc_out_dc1 = 128 * s32DcPre;
        pstCscDcCoef->csc_out_dc2 = 128 * s32DcPre;
    }

#endif

#endif

    return HI_SUCCESS;
}


HI_S32 VDP_FUNC_GetWcgGmmCoef(HI_U32 u32Layer, HI_U16 *pu16GmmCoef)
{

    return HI_SUCCESS;
}

HI_S32 VDP_FUNC_GetWcgDegmmCoef(HI_U32 u32Layer, HI_U16 *pu16DegmmCoef)
{
    return HI_SUCCESS;
}
