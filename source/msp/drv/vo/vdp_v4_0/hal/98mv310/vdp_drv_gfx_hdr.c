#include "hi_type.h"
#include "drv_pq_ext.h"
#include "vdp_drv_gfx_hdr.h"
#include "vdp_drv_gdm_coef.h"
#include "vdp_hal_ip_hihdr_g.h"

HI_S32  XDP_DRV_GfxHdrRegClean(HI_BOOL bRgbOutColorSpace)
{
	VDP_HIHDR_G_SetGhdrDegmmEn(0);
	VDP_HIHDR_G_SetGhdrEn(0);
	VDP_HIHDR_G_SetGhdrGamutEn(0);
	VDP_HIHDR_G_SetGhdrTmapEn(0);
	VDP_HIHDR_G_SetGhdrGmmEn(0);
    //VDP_HIHDR_G_SetHihdrR2yEn(0);

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetHiHdrGfxCfg(HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    HI_U32 gdm_en     =    0;
    HI_U32 gdm_degmm_en    =  0;
    HI_U32 gdm_csc_en     =    0;
    HI_U32 gdm_tmap_en      =  0;
    HI_U32 gdm_gmm_en     =    0;
    HI_U32 gdm_dither_en    =  0;
    HI_U32 gdm_rgb2yuv_en     =    0;

    HI_U32 gdm_tmap_in_bdp      =  0;
    HI_U32 gdm_dither_mode      =  0;

    HI_U16 gdm_luma_coef0_tmap      =  0;
    HI_U16 gdm_luma_coef1_tmap      =  0;
    HI_U16 gdm_luma_coef2_tmap      =  0;
    HI_U16 gdm_tmap_luma_scale      =  0;
    HI_U16 gdm_tmap_coef_scale      =  0;
    HI_U16 gdm_tmap_out_clip_min    =  0;
    HI_U16 gdm_tmap_out_clip_max    =  0;
    HI_U32 g_degmm_x4_step      =  0;
    HI_U32 g_degmm_x3_step      =  0;
    HI_U32 g_degmm_x2_step      =  0;
    HI_U32 g_degmm_x1_step      =  0;
    HI_U32 g_degmm_x2_pos     =    0;
    HI_U32 g_degmm_x1_pos     =    0;
    HI_U32 g_degmm_x4_pos     =    0;
    HI_U32 g_degmm_x3_pos     =    0;
    HI_U32 g_degmm_x4_num     =    0;
    HI_U32 g_degmm_x3_num     =    0;
    HI_U32 g_degmm_x2_num     =    0;
    HI_U32 g_degmm_x1_num     =    0;
    HI_U32 g_tmap_x4_step     =    0;
    HI_U32 g_tmap_x3_step     =    0;
    HI_U32 g_tmap_x2_step     =    0;
    HI_U32 g_tmap_x1_step     =    0;
    HI_U32 g_tmap_x1_pos    =  0;
    HI_U32 g_tmap_x2_pos    =  0;
    HI_U32 g_tmap_x4_num    =  0;
    HI_U32 g_tmap_x3_num    =  0;
    HI_U32 g_tmap_x2_num    =  0;
    HI_U32 g_tmap_x1_num    =  0;
    HI_U32 g_tmap_x3_pos    =  0;
    HI_U32 g_tmap_x4_pos    =  0;

    //add_regs
    HI_U32 g_gmm_x8_step = 0;
    HI_U32 g_gmm_x7_step = 0;
    HI_U32 g_gmm_x6_step = 0;
    HI_U32 g_gmm_x5_step = 0;
    HI_U32 g_gmm_x6_pos = 0;
    HI_U32 g_gmm_x5_pos = 0;
    HI_U32 g_gmm_x8_pos = 0;
    HI_U32 g_gmm_x7_pos = 0;
    HI_U32 g_gmm_x8_num = 0;
    HI_U32 g_gmm_x7_num = 0;
    HI_U32 g_gmm_x6_num = 0;
    HI_U32 g_gmm_x5_num = 0;

    HI_U32 g_gmm_x4_step    =  0;
    HI_U32 g_gmm_x3_step    =  0;
    HI_U32 g_gmm_x2_step    =  0;
    HI_U32 g_gmm_x1_step    =  0;
    HI_U32 g_gmm_x2_pos    =  0;
    HI_U32 g_gmm_x1_pos    =  0;
    HI_U32 g_gmm_x4_pos    =  0;
    HI_U32 g_gmm_x3_pos    =  0;
    HI_U32 g_gmm_x4_num    =  0;
    HI_U32 g_gmm_x3_num    =  0;
    HI_U32 g_gmm_x2_num    =  0;
    HI_U32 g_gmm_x1_num    =  0;
    HI_S16 gdm_coef00_csc     =    0;
    HI_S16 gdm_coef01_csc     =    0;
    HI_S16 gdm_coef02_csc     =    0;
    HI_S16 gdm_coef10_csc     =    0;
    HI_S16 gdm_coef11_csc     =    0;
    HI_S16 gdm_coef12_csc     =    0;
    HI_S16 gdm_coef20_csc     =    0;
    HI_S16 gdm_coef21_csc     =    0;
    HI_S16 gdm_coef22_csc     =    0;
    HI_U16 gdm_csc_scale    =  0;
    HI_U32 gdm_csc_clip_min    =  0;
    HI_U32 gdm_csc_clip_max    =  0;
    HI_S16 gdm_00_rgb2yuv     =    0;
    HI_S16 gdm_01_rgb2yuv     =    0;
    HI_S16 gdm_02_rgb2yuv     =    0;
    HI_S16 gdm_10_rgb2yuv     =    0;
    HI_S16 gdm_11_rgb2yuv     =    0;
    HI_S16 gdm_12_rgb2yuv     =    0;
    HI_S16 gdm_20_rgb2yuv     =    0;
    HI_S16 gdm_21_rgb2yuv     =    0;
    HI_S16 gdm_22_rgb2yuv     =    0;
    HI_U16 gdm_rgb2yuvscale2p     =    0;
    HI_S16 gdm_rgb2yuv_0_in_dc      =  0;
    HI_S16 gdm_rgb2yuv_1_in_dc      =  0;
    HI_S16 gdm_rgb2yuv_2_in_dc      =  0;
    HI_S16 gdm_rgb2yuv_0_out_dc    =  0;
    HI_S16 gdm_rgb2yuv_1_out_dc    =  0;
    HI_S16 gdm_rgb2yuv_2_out_dc    =  0;
    HI_U16 gdm_rgb2yuv_clip_min    =  0;
    HI_U16 gdm_rgb2yuv_clip_max    =  0;
    HI_U32 gdm_dither_round_unlim     =    0;
    HI_U32 gdm_dither_round    =  0;
    HI_U32 gdm_dither_domain_mode     =    0;
    HI_U32 gdm_dither_tap_mode      =  0;
    HI_U32 gdm_dither_sed_y0    =  0;
    HI_U32 gdm_dither_sed_u0    =  0;
    HI_U32 gdm_dither_sed_v0    =  0;
    HI_U32 gdm_dither_sed_w0    =  0;
    HI_U32 gdm_dither_sed_y1    =  0;
    HI_U32 gdm_dither_sed_u1    =  0;
    HI_U32 gdm_dither_sed_v1    =  0;
    HI_U32 gdm_dither_sed_w1    =  0;
    HI_U32 gdm_dither_thr_max     =    0;
    HI_U32 gdm_dither_thr_min     =    0;

    gdm_tmap_in_bdp   = 0 ;
    gdm_gmm_en          = pstPqGfxHdrCfg->bGammaEn ;
    gdm_tmap_en       = pstPqGfxHdrCfg->bTMapEn  ;
    gdm_degmm_en      = pstPqGfxHdrCfg->bDegammaEn;
    gdm_en              = pstPqGfxHdrCfg->bHdrEn;
    gdm_rgb2yuv_en      = pstPqGfxHdrCfg->bR2YEn;
    gdm_csc_en          = pstPqGfxHdrCfg->bGMapEn;
    gdm_dither_en      = pstPqGfxHdrCfg->bDitherEn;
    gdm_dither_mode   = pstPqGfxHdrCfg->bDitherMode ;

    gdm_luma_coef0_tmap       = pstPqGfxHdrCfg->stTMAP.au16M3LumaCal[0] ;
    gdm_luma_coef1_tmap       = pstPqGfxHdrCfg->stTMAP.au16M3LumaCal[1] ;
    gdm_luma_coef2_tmap       = pstPqGfxHdrCfg->stTMAP.au16M3LumaCal[2] ;
    gdm_tmap_luma_scale       = pstPqGfxHdrCfg->stTMAP.u16ScaleLumaCal ;
    gdm_tmap_coef_scale       = pstPqGfxHdrCfg->stTMAP.u16ScaleCoefTM  ;
    gdm_tmap_out_clip_min      = pstPqGfxHdrCfg->stTMAP.u32ClipMinTM      ;
    gdm_tmap_out_clip_max      = pstPqGfxHdrCfg->stTMAP.u32ClipMaxTM      ;

    g_degmm_x1_step   = pstPqGfxHdrCfg->stDeGmm.au32Step[0];
    g_degmm_x2_step   = pstPqGfxHdrCfg->stDeGmm.au32Step[1];
    g_degmm_x3_step   = pstPqGfxHdrCfg->stDeGmm.au32Step[2];
    g_degmm_x4_step   = pstPqGfxHdrCfg->stDeGmm.au32Step[3];
    g_degmm_x1_pos      = pstPqGfxHdrCfg->stDeGmm.au32Pos[0];
    g_degmm_x2_pos      = pstPqGfxHdrCfg->stDeGmm.au32Pos[1];
    g_degmm_x3_pos      = pstPqGfxHdrCfg->stDeGmm.au32Pos[2];
    g_degmm_x4_pos      = pstPqGfxHdrCfg->stDeGmm.au32Pos[3];
    g_degmm_x1_num      = pstPqGfxHdrCfg->stDeGmm.au32Num[0];
    g_degmm_x2_num      = pstPqGfxHdrCfg->stDeGmm.au32Num[1];
    g_degmm_x3_num      = pstPqGfxHdrCfg->stDeGmm.au32Num[2];
    g_degmm_x4_num      = pstPqGfxHdrCfg->stDeGmm.au32Num[3];


    g_tmap_x1_step       = pstPqGfxHdrCfg->stTMAP.au32StepTM[0];
    g_tmap_x2_step       = pstPqGfxHdrCfg->stTMAP.au32StepTM[1];
    g_tmap_x3_step       = pstPqGfxHdrCfg->stTMAP.au32StepTM[2];
    g_tmap_x4_step       = pstPqGfxHdrCfg->stTMAP.au32StepTM[3];
    g_tmap_x1_pos       = pstPqGfxHdrCfg->stTMAP.au32PosTM[0];
    g_tmap_x2_pos       = pstPqGfxHdrCfg->stTMAP.au32PosTM[1];
    g_tmap_x3_pos       = pstPqGfxHdrCfg->stTMAP.au32PosTM[2];
    g_tmap_x4_pos       = pstPqGfxHdrCfg->stTMAP.au32PosTM[3];
    g_tmap_x1_num       = pstPqGfxHdrCfg->stTMAP.au32NumTM[0];
    g_tmap_x2_num       = pstPqGfxHdrCfg->stTMAP.au32NumTM[1];
    g_tmap_x3_num       = pstPqGfxHdrCfg->stTMAP.au32NumTM[2];
    g_tmap_x4_num       = pstPqGfxHdrCfg->stTMAP.au32NumTM[3];

    g_gmm_x1_step      = pstPqGfxHdrCfg->stGmm.au32Step[0] ;
    g_gmm_x2_step      = pstPqGfxHdrCfg->stGmm.au32Step[1] ;
    g_gmm_x3_step      = pstPqGfxHdrCfg->stGmm.au32Step[2] ;
    g_gmm_x4_step      = pstPqGfxHdrCfg->stGmm.au32Step[3] ;
    g_gmm_x5_step      = pstPqGfxHdrCfg->stGmm.au32Step[4] ;
    g_gmm_x6_step      = pstPqGfxHdrCfg->stGmm.au32Step[5] ;
    g_gmm_x7_step      = pstPqGfxHdrCfg->stGmm.au32Step[6] ;
    g_gmm_x8_step      = pstPqGfxHdrCfg->stGmm.au32Step[7] ;
    g_gmm_x1_pos      = pstPqGfxHdrCfg->stGmm.au32Pos[0] ;
    g_gmm_x2_pos      = pstPqGfxHdrCfg->stGmm.au32Pos[1] ;
    g_gmm_x3_pos      = pstPqGfxHdrCfg->stGmm.au32Pos[2] ;
    g_gmm_x4_pos      = pstPqGfxHdrCfg->stGmm.au32Pos[3] ;
    g_gmm_x5_pos      = pstPqGfxHdrCfg->stGmm.au32Pos[4] ;
    g_gmm_x6_pos      = pstPqGfxHdrCfg->stGmm.au32Pos[5] ;
    g_gmm_x7_pos      = pstPqGfxHdrCfg->stGmm.au32Pos[6] ;
    g_gmm_x8_pos      = pstPqGfxHdrCfg->stGmm.au32Pos[7] ;
    g_gmm_x1_num      = pstPqGfxHdrCfg->stGmm.au32Num[0] ;
    g_gmm_x2_num      = pstPqGfxHdrCfg->stGmm.au32Num[1] ;
    g_gmm_x3_num      = pstPqGfxHdrCfg->stGmm.au32Num[2] ;
    g_gmm_x4_num      = pstPqGfxHdrCfg->stGmm.au32Num[3] ;
    g_gmm_x5_num      = pstPqGfxHdrCfg->stGmm.au32Num[4] ;
    g_gmm_x6_num      = pstPqGfxHdrCfg->stGmm.au32Num[5] ;
    g_gmm_x7_num      = pstPqGfxHdrCfg->stGmm.au32Num[6] ;
    g_gmm_x8_num      = pstPqGfxHdrCfg->stGmm.au32Num[7] ;

    gdm_coef00_csc         = pstPqGfxHdrCfg->stGMAP.as16M33GMAP[0][0] ;
    gdm_coef01_csc         = pstPqGfxHdrCfg->stGMAP.as16M33GMAP[0][1] ;
    gdm_coef02_csc         = pstPqGfxHdrCfg->stGMAP.as16M33GMAP[0][2] ;
    gdm_coef10_csc         = pstPqGfxHdrCfg->stGMAP.as16M33GMAP[1][0] ;
    gdm_coef11_csc         = pstPqGfxHdrCfg->stGMAP.as16M33GMAP[1][1] ;
    gdm_coef12_csc         = pstPqGfxHdrCfg->stGMAP.as16M33GMAP[1][2] ;
    gdm_coef20_csc         = pstPqGfxHdrCfg->stGMAP.as16M33GMAP[2][0] ;
    gdm_coef21_csc         = pstPqGfxHdrCfg->stGMAP.as16M33GMAP[2][1] ;
    gdm_coef22_csc         = pstPqGfxHdrCfg->stGMAP.as16M33GMAP[2][2] ;
    gdm_csc_scale         = pstPqGfxHdrCfg->stGMAP.u16ScaleGMAP      ;
    gdm_csc_clip_min     = pstPqGfxHdrCfg->stGMAP.u32ClipMinGMAP  ;
    gdm_csc_clip_max     = pstPqGfxHdrCfg->stGMAP.u32ClipMaxGMAP  ;

    gdm_rgb2yuvscale2p       = pstPqGfxHdrCfg->stR2Y.u16ScaleR2Y        ;
    gdm_rgb2yuv_0_in_dc    = pstPqGfxHdrCfg->stR2Y.as16DcInR2Y[0]   ;
    gdm_rgb2yuv_1_in_dc    = pstPqGfxHdrCfg->stR2Y.as16DcInR2Y[1]   ;
    gdm_rgb2yuv_2_in_dc    = pstPqGfxHdrCfg->stR2Y.as16DcInR2Y[2]   ;
    gdm_rgb2yuv_0_out_dc   = pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y[0]  ;
    gdm_rgb2yuv_1_out_dc   = pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y[1]  ;
    gdm_rgb2yuv_2_out_dc   = pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y[2]  ;
    gdm_rgb2yuv_clip_min   = pstPqGfxHdrCfg->stR2Y.u16ClipMinR2Y;
    gdm_rgb2yuv_clip_max   = pstPqGfxHdrCfg->stR2Y.u16ClipMaxR2Y;

    gdm_00_rgb2yuv           = pstPqGfxHdrCfg->stR2Y.as16M33R2Y[0][0];
    gdm_01_rgb2yuv           = pstPqGfxHdrCfg->stR2Y.as16M33R2Y[0][1];
    gdm_02_rgb2yuv           = pstPqGfxHdrCfg->stR2Y.as16M33R2Y[0][2];
    gdm_10_rgb2yuv           = pstPqGfxHdrCfg->stR2Y.as16M33R2Y[1][0];
    gdm_11_rgb2yuv           = pstPqGfxHdrCfg->stR2Y.as16M33R2Y[1][1];
    gdm_12_rgb2yuv           = pstPqGfxHdrCfg->stR2Y.as16M33R2Y[1][2];
    gdm_20_rgb2yuv           = pstPqGfxHdrCfg->stR2Y.as16M33R2Y[2][0];
    gdm_21_rgb2yuv           = pstPqGfxHdrCfg->stR2Y.as16M33R2Y[2][1];
    gdm_22_rgb2yuv           = pstPqGfxHdrCfg->stR2Y.as16M33R2Y[2][2];

    gdm_dither_round       = 1;
    gdm_dither_domain_mode = 0;
    gdm_dither_tap_mode    = 0;
    gdm_dither_round_unlim = 0;
    gdm_dither_sed_y0       = 2147483647 ;
    gdm_dither_sed_u0       = 2147483647 ;
    gdm_dither_sed_v0       = 2147483647 ;
    gdm_dither_sed_w0       = 2147483647 ;
    gdm_dither_sed_y1       = 2140000000 ;
    gdm_dither_sed_u1       = 2140000000 ;
    gdm_dither_sed_v1       = 2140000000 ;
    gdm_dither_sed_w1       = 2140000000 ;
    gdm_dither_thr_max       = 65535 ;
    gdm_dither_thr_min       = 0 ;

        VDP_HIHDR_G_SetGhdrDegmmEn( gdm_degmm_en);
        VDP_HIHDR_G_SetGhdrEn( gdm_en);
        VDP_HIHDR_G_SetGhdrGamutEn( gdm_csc_en);
        VDP_HIHDR_G_SetGhdrGamutCoef00( gdm_coef00_csc);
        VDP_HIHDR_G_SetGhdrGamutCoef01( gdm_coef01_csc);
        VDP_HIHDR_G_SetGhdrGamutCoef02( gdm_coef02_csc);
        VDP_HIHDR_G_SetGhdrGamutCoef10( gdm_coef10_csc);
        VDP_HIHDR_G_SetGhdrGamutCoef11( gdm_coef11_csc);
        VDP_HIHDR_G_SetGhdrGamutCoef12( gdm_coef12_csc);
        VDP_HIHDR_G_SetGhdrGamutCoef20( gdm_coef20_csc);
        VDP_HIHDR_G_SetGhdrGamutCoef21( gdm_coef21_csc);
        VDP_HIHDR_G_SetGhdrGamutCoef22( gdm_coef22_csc);
        VDP_HIHDR_G_SetGhdrGamutScale( gdm_csc_scale);
        VDP_HIHDR_G_SetGhdrGamutClipMin( gdm_csc_clip_min);
        VDP_HIHDR_G_SetGhdrGamutClipMax( gdm_csc_clip_max);
        VDP_HIHDR_G_SetGhdrTmapEn( gdm_tmap_en);
        VDP_HIHDR_G_SetGTmapX4Step( g_tmap_x4_step);
        VDP_HIHDR_G_SetGTmapX3Step( g_tmap_x3_step);
        VDP_HIHDR_G_SetGTmapX2Step( g_tmap_x2_step);
        VDP_HIHDR_G_SetGTmapX1Step( g_tmap_x1_step);
        VDP_HIHDR_G_SetGTmapX1Pos( g_tmap_x1_pos);
        VDP_HIHDR_G_SetGTmapX2Pos( g_tmap_x2_pos);
        VDP_HIHDR_G_SetGTmapX3Pos( g_tmap_x3_pos);
        VDP_HIHDR_G_SetGTmapX4Pos( g_tmap_x4_pos);
        VDP_HIHDR_G_SetGTmapX4Num( g_tmap_x4_num);
        VDP_HIHDR_G_SetGTmapX3Num( g_tmap_x3_num);
        VDP_HIHDR_G_SetGTmapX2Num( g_tmap_x2_num);
        VDP_HIHDR_G_SetGTmapX1Num( g_tmap_x1_num);
        VDP_HIHDR_G_SetGhdrTmapLumaCoef0(  gdm_luma_coef0_tmap   );
        VDP_HIHDR_G_SetGhdrTmapLumaCoef1(  gdm_luma_coef1_tmap   );
        VDP_HIHDR_G_SetGhdrTmapLumaCoef2(  gdm_luma_coef2_tmap   );
        VDP_HIHDR_G_SetGhdrTmapLumaScale(  gdm_tmap_luma_scale   );
        VDP_HIHDR_G_SetGhdrTmapCoefScale(  gdm_tmap_coef_scale   );
        VDP_HIHDR_G_SetGhdrTmapOutClipMin( gdm_tmap_out_clip_min );
        VDP_HIHDR_G_SetGhdrTmapOutClipMax( gdm_tmap_out_clip_max );
        VDP_HIHDR_G_SetGhdrGmmEn( gdm_gmm_en);
        VDP_HIHDR_G_SetGGmmX4Step( g_gmm_x4_step);
        VDP_HIHDR_G_SetGGmmX3Step( g_gmm_x3_step);
        VDP_HIHDR_G_SetGGmmX2Step( g_gmm_x2_step);
        VDP_HIHDR_G_SetGGmmX1Step( g_gmm_x1_step);
        VDP_HIHDR_G_SetGGmmX8Step( g_gmm_x8_step);
        VDP_HIHDR_G_SetGGmmX7Step( g_gmm_x7_step);
        VDP_HIHDR_G_SetGGmmX6Step( g_gmm_x6_step);
        VDP_HIHDR_G_SetGGmmX5Step( g_gmm_x5_step);
        VDP_HIHDR_G_SetGGmmX2Pos( g_gmm_x2_pos);
        VDP_HIHDR_G_SetGGmmX1Pos( g_gmm_x1_pos);
        VDP_HIHDR_G_SetGGmmX4Pos( g_gmm_x4_pos);
        VDP_HIHDR_G_SetGGmmX3Pos( g_gmm_x3_pos);
        VDP_HIHDR_G_SetGGmmX6Pos( g_gmm_x6_pos);
        VDP_HIHDR_G_SetGGmmX5Pos( g_gmm_x5_pos);
        VDP_HIHDR_G_SetGGmmX8Pos( g_gmm_x8_pos);
        VDP_HIHDR_G_SetGGmmX7Pos( g_gmm_x7_pos);
        VDP_HIHDR_G_SetGGmmX4Num( g_gmm_x4_num);
        VDP_HIHDR_G_SetGGmmX3Num( g_gmm_x3_num);
        VDP_HIHDR_G_SetGGmmX2Num( g_gmm_x2_num);
        VDP_HIHDR_G_SetGGmmX1Num( g_gmm_x1_num);
        VDP_HIHDR_G_SetGGmmX8Num( g_gmm_x8_num);
        VDP_HIHDR_G_SetGGmmX7Num( g_gmm_x7_num);
        VDP_HIHDR_G_SetGGmmX6Num( g_gmm_x6_num);
        VDP_HIHDR_G_SetGGmmX5Num( g_gmm_x5_num);

        VDP_HIHDR_G_SetGhdrDitherRoundUnlim ( gdm_dither_round_unlim);
        VDP_HIHDR_G_SetGhdrDitherEn         ( gdm_dither_en);
        VDP_HIHDR_G_SetGhdrDitherMode       ( gdm_dither_mode);
        VDP_HIHDR_G_SetGhdrDitherRound      ( gdm_dither_round);
        VDP_HIHDR_G_SetGhdrDitherDomainMode ( gdm_dither_domain_mode);
        VDP_HIHDR_G_SetGhdrDitherTapMode    ( gdm_dither_tap_mode);
        VDP_HIHDR_G_SetGhdrDitherThrMax     ( gdm_dither_thr_max);
        VDP_HIHDR_G_SetGhdrDitherThrMin     ( gdm_dither_thr_min);
        VDP_HIHDR_G_SetGhdrDitherSedY0      ( gdm_dither_sed_y0);
        VDP_HIHDR_G_SetGhdrDitherSedU0      ( gdm_dither_sed_u0);
        VDP_HIHDR_G_SetGhdrDitherSedV0      ( gdm_dither_sed_v0);
        VDP_HIHDR_G_SetGhdrDitherSedW0      ( gdm_dither_sed_w0);
        VDP_HIHDR_G_SetGhdrDitherSedY1      ( gdm_dither_sed_y1);
        VDP_HIHDR_G_SetGhdrDitherSedU1      ( gdm_dither_sed_u1);
        VDP_HIHDR_G_SetGhdrDitherSedV1      ( gdm_dither_sed_v1);
        VDP_HIHDR_G_SetGhdrDitherSedW1      ( gdm_dither_sed_w1);

        VDP_HIHDR_G_SetHihdrR2yEn( gdm_rgb2yuv_en);
        VDP_HIHDR_G_SetHihdrR2yCoef00( gdm_00_rgb2yuv);
        VDP_HIHDR_G_SetHihdrR2yCoef01( gdm_01_rgb2yuv);
        VDP_HIHDR_G_SetHihdrR2yCoef02( gdm_02_rgb2yuv);
        VDP_HIHDR_G_SetHihdrR2yCoef10( gdm_10_rgb2yuv);
        VDP_HIHDR_G_SetHihdrR2yCoef11( gdm_11_rgb2yuv);
        VDP_HIHDR_G_SetHihdrR2yCoef12( gdm_12_rgb2yuv);
        VDP_HIHDR_G_SetHihdrR2yCoef20( gdm_20_rgb2yuv);
        VDP_HIHDR_G_SetHihdrR2yCoef21( gdm_21_rgb2yuv);
        VDP_HIHDR_G_SetHihdrR2yCoef22( gdm_22_rgb2yuv);
        VDP_HIHDR_G_SetHihdrR2yScale2p( gdm_rgb2yuvscale2p);
        VDP_HIHDR_G_SetHihdrR2yIdc0( gdm_rgb2yuv_0_in_dc );
        VDP_HIHDR_G_SetHihdrR2yIdc1( gdm_rgb2yuv_1_in_dc );
        VDP_HIHDR_G_SetHihdrR2yIdc2( gdm_rgb2yuv_2_in_dc );
        VDP_HIHDR_G_SetHihdrR2yOdc0( gdm_rgb2yuv_0_out_dc);
        VDP_HIHDR_G_SetHihdrR2yOdc1( gdm_rgb2yuv_1_out_dc);
        VDP_HIHDR_G_SetHihdrR2yOdc2( gdm_rgb2yuv_2_out_dc);
        VDP_HIHDR_G_SetHihdrR2yClipMin( gdm_csc_clip_min);
        VDP_HIHDR_G_SetHihdrR2yClipMax( gdm_csc_clip_max);

    return HI_SUCCESS;

}

HI_S32 VDP_DRV_SetHisiGfxHdr(HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg, VDP_CLR_SPACE_E enOutColorSpace)
{
    HI_BOOL bRgbOutColorSpace = HI_FALSE;

    if ((VDP_CLR_SPACE_RGB_601 == enOutColorSpace)
        || (VDP_CLR_SPACE_RGB_601_L == enOutColorSpace)
        || (VDP_CLR_SPACE_RGB_709 == enOutColorSpace)
        || (VDP_CLR_SPACE_RGB_709_L == enOutColorSpace)
        || (VDP_CLR_SPACE_RGB_2020 == enOutColorSpace)
        || (VDP_CLR_SPACE_RGB_2020_L == enOutColorSpace))
    {
        bRgbOutColorSpace = HI_TRUE;
    }
    else
    {
        bRgbOutColorSpace = HI_FALSE;
    }

    XDP_DRV_GfxHdrRegClean(bRgbOutColorSpace);

    if (HI_NULL == pstPqGfxHdrCfg)
    {
        VDP_PRINT("HI_PQ_GFXHDR_CFG is NULL !!!\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstPqGfxHdrCfg->bHdrEn)
    {
        return HI_FAILURE;
    }

    Vdp_Drv_SetGdmCoef_Tmmp(pstPqGfxHdrCfg);
    Vdp_Drv_SetGdmCoef_Gmma(pstPqGfxHdrCfg);

    VDP_DRV_SetHiHdrGfxCfg(pstPqGfxHdrCfg);

    return HI_SUCCESS;
}

