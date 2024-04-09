#include "hi_type.h"
#include "vdp_drv_comm.h"
#include "vdp_drv_vid.h"
#include "vdp_hal_mmu.h"
#include "vdp_drv_pq_csc.h"
#include "vdp_drv_pq_zme.h"
#include "vdp_hal_comm.h"
#include "vdp_drv_ip_vdm.h"
#include "vdp_hdr_cfg.h"
#include "vdp_drv_vdm_coef.h"
#include "vdp_fpga_define.h"

#include "vdp_drv_bkg_process.h"
#include "vdp_drv_gdm_coef.h"


#include "vdp_hal_hdr.h"
#include "vdp_hal_chn.h"

#if (!EDA_TEST)
#include <linux/string.h>
#include <linux/kernel.h>
#else
#include <string.h>
#endif


extern VDP_COEF_ADDR_S gstVdpCoefBufAddr;

HI_S32  XDP_DRV_GfxHdrRegClean(HI_BOOL bRgbOutColorSpace)
{
    //------db clean------//
    VDP_HDR_SetHdrEnable(HI_FALSE);
    VDP_DISP_SetNxgDataSwapEnable (VDP_CHN_DHD0, 0);
    VDP_DISP_SetHdmiMode(VDP_CHN_DHD0, bRgbOutColorSpace);
    VDP_GP_SetHdrSel               (0 );

    VDP_HDR_SetGCvmEn              (0) ;
    VDP_HDR_SetGCvmS2uEn           (0);

    //GDM
    VDP_HDR_SetGDmEn               (0);
    VDP_HDR_SetGDmDegammaEn        (0);
    VDP_HDR_SetGDmRgb2lmsEn        (0) ;
    VDP_HDR_SetGDmGammaEn          (0);

    VDP_GP_SetGdmGdmGmmEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmTmapEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmDegmmEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmEn(VDP_LAYER_GP0, HI_FALSE);
    
    VDP_HDR_SetRegUp();
    VDP_DISP_SetRegUp (VDP_CHN_DHD0);

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
    HI_U32 gdm_tmap_rd_en     =    0;
    HI_U32 gdm_tmap_para_data     =    0;
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
    HI_U32 gdm_gamma_rd_en      =  0;
    HI_U32 gdm_gamma_para_data      =  0;

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
    HI_U32 gdm_dither_sed_y2    =  0;
    HI_U32 gdm_dither_sed_u2    =  0;
    HI_U32 gdm_dither_sed_v2    =  0;
    HI_U32 gdm_dither_sed_w2    =  0;
    HI_U32 gdm_dither_sed_y3    =  0;
    HI_U32 gdm_dither_sed_u3    =  0;
    HI_U32 gdm_dither_sed_v3    =  0;
    HI_U32 gdm_dither_sed_w3    =  0;
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

    VDP_GP_SetGdmGdmTmapInBdp(VDP_LAYER_GP0, gdm_tmap_in_bdp);
    VDP_GP_SetGdmGdmGmmEn(VDP_LAYER_GP0, gdm_gmm_en);
    VDP_GP_SetGdmGdmTmapEn(VDP_LAYER_GP0, gdm_tmap_en);
    VDP_GP_SetGdmGdmDegmmEn(VDP_LAYER_GP0, gdm_degmm_en);
    VDP_GP_SetGdmGdmEn(VDP_LAYER_GP0, gdm_en);
    VDP_GP_SetGdmGdmLumaCoef0Tmap(VDP_LAYER_GP0, gdm_luma_coef0_tmap);
    VDP_GP_SetGdmGdmLumaCoef1Tmap(VDP_LAYER_GP0, gdm_luma_coef1_tmap);
    VDP_GP_SetGdmGdmLumaCoef2Tmap(VDP_LAYER_GP0, gdm_luma_coef2_tmap);
    VDP_GP_SetGdmGdmTmapLumaScale(VDP_LAYER_GP0, gdm_tmap_luma_scale);
    VDP_GP_SetGdmGdmTmapCoefScale(VDP_LAYER_GP0, gdm_tmap_coef_scale);
    VDP_GP_SetGdmGdmTmapOutClipMin(VDP_LAYER_GP0, gdm_tmap_out_clip_min);
    VDP_GP_SetGdmGdmTmapOutClipMax(VDP_LAYER_GP0, gdm_tmap_out_clip_max);
    VDP_GP_SetGdmGGmmX5Num(VDP_LAYER_GP0, g_gmm_x5_num);
    VDP_GP_SetGdmGGmmX6Num(VDP_LAYER_GP0, g_gmm_x6_num);
    VDP_GP_SetGdmGGmmX7Num(VDP_LAYER_GP0, g_gmm_x7_num);
    VDP_GP_SetGdmGGmmX8Num(VDP_LAYER_GP0, g_gmm_x8_num);
    VDP_GP_SetGdmGGmmX7Pos(VDP_LAYER_GP0, g_gmm_x7_pos);
    VDP_GP_SetGdmGGmmX8Pos(VDP_LAYER_GP0, g_gmm_x8_pos);
    VDP_GP_SetGdmGGmmX5Pos(VDP_LAYER_GP0, g_gmm_x5_pos);
    VDP_GP_SetGdmGGmmX6Pos(VDP_LAYER_GP0, g_gmm_x6_pos);
    VDP_GP_SetGdmGGmmX5Step(VDP_LAYER_GP0, g_gmm_x5_step);
    VDP_GP_SetGdmGGmmX6Step(VDP_LAYER_GP0, g_gmm_x6_step);
    VDP_GP_SetGdmGGmmX7Step(VDP_LAYER_GP0, g_gmm_x7_step);
    VDP_GP_SetGdmGGmmX8Step(VDP_LAYER_GP0, g_gmm_x8_step);
    VDP_GP_SetGdmGDegmmX4Step(VDP_LAYER_GP0, g_degmm_x4_step);
    VDP_GP_SetGdmGDegmmX3Step(VDP_LAYER_GP0, g_degmm_x3_step);
    VDP_GP_SetGdmGDegmmX2Step(VDP_LAYER_GP0, g_degmm_x2_step);
    VDP_GP_SetGdmGDegmmX1Step(VDP_LAYER_GP0, g_degmm_x1_step);
    VDP_GP_SetGdmGDegmmX2Pos(VDP_LAYER_GP0, g_degmm_x2_pos);
    VDP_GP_SetGdmGDegmmX1Pos(VDP_LAYER_GP0, g_degmm_x1_pos);
    VDP_GP_SetGdmGDegmmX4Pos(VDP_LAYER_GP0, g_degmm_x4_pos);
    VDP_GP_SetGdmGDegmmX3Pos(VDP_LAYER_GP0, g_degmm_x3_pos);
    VDP_GP_SetGdmGDegmmX4Num(VDP_LAYER_GP0, g_degmm_x4_num);
    VDP_GP_SetGdmGDegmmX3Num(VDP_LAYER_GP0, g_degmm_x3_num);
    VDP_GP_SetGdmGDegmmX2Num(VDP_LAYER_GP0, g_degmm_x2_num);
    VDP_GP_SetGdmGDegmmX1Num(VDP_LAYER_GP0, g_degmm_x1_num);
    VDP_GP_SetGdmGdmTmapRdEn(VDP_LAYER_GP0, gdm_tmap_rd_en);
    VDP_GP_SetGdmGdmTmapParaData(VDP_LAYER_GP0, gdm_tmap_para_data);
    VDP_GP_SetGdmGTmapX4Step(VDP_LAYER_GP0, g_tmap_x4_step);
    VDP_GP_SetGdmGTmapX3Step(VDP_LAYER_GP0, g_tmap_x3_step);
    VDP_GP_SetGdmGTmapX2Step(VDP_LAYER_GP0, g_tmap_x2_step);
    VDP_GP_SetGdmGTmapX1Step(VDP_LAYER_GP0, g_tmap_x1_step);
    VDP_GP_SetGdmGTmapX1Pos(VDP_LAYER_GP0, g_tmap_x1_pos);
    VDP_GP_SetGdmGTmapX2Pos(VDP_LAYER_GP0, g_tmap_x2_pos);
    VDP_GP_SetGdmGTmapX4Num(VDP_LAYER_GP0, g_tmap_x4_num);
    VDP_GP_SetGdmGTmapX3Num(VDP_LAYER_GP0, g_tmap_x3_num);
    VDP_GP_SetGdmGTmapX2Num(VDP_LAYER_GP0, g_tmap_x2_num);
    VDP_GP_SetGdmGTmapX1Num(VDP_LAYER_GP0, g_tmap_x1_num);
    VDP_GP_SetGdmGTmapX3Pos(VDP_LAYER_GP0, g_tmap_x3_pos);
    VDP_GP_SetGdmGTmapX4Pos(VDP_LAYER_GP0, g_tmap_x4_pos);
    VDP_GP_SetGdmGdmGammaRdEn(VDP_LAYER_GP0, gdm_gamma_rd_en);
    VDP_GP_SetGdmGdmGammaParaData(VDP_LAYER_GP0, gdm_gamma_para_data);
    VDP_GP_SetGdmGGmmX4Step(VDP_LAYER_GP0, g_gmm_x4_step);
    VDP_GP_SetGdmGGmmX3Step(VDP_LAYER_GP0, g_gmm_x3_step);
    VDP_GP_SetGdmGGmmX2Step(VDP_LAYER_GP0, g_gmm_x2_step);
    VDP_GP_SetGdmGGmmX1Step(VDP_LAYER_GP0, g_gmm_x1_step);
    VDP_GP_SetGdmGGmmX2Pos(VDP_LAYER_GP0, g_gmm_x2_pos);
    VDP_GP_SetGdmGGmmX1Pos(VDP_LAYER_GP0, g_gmm_x1_pos);
    VDP_GP_SetGdmGGmmX4Pos(VDP_LAYER_GP0, g_gmm_x4_pos);
    VDP_GP_SetGdmGGmmX3Pos(VDP_LAYER_GP0, g_gmm_x3_pos);
    VDP_GP_SetGdmGGmmX4Num(VDP_LAYER_GP0, g_gmm_x4_num);
    VDP_GP_SetGdmGGmmX3Num(VDP_LAYER_GP0, g_gmm_x3_num);
    VDP_GP_SetGdmGGmmX2Num(VDP_LAYER_GP0, g_gmm_x2_num);
    VDP_GP_SetGdmGGmmX1Num(VDP_LAYER_GP0, g_gmm_x1_num);
    VDP_GP_SetGdmGdmCscEn(VDP_LAYER_GP0, gdm_csc_en);
    VDP_GP_SetGdmGdmCoef00Csc(VDP_LAYER_GP0, gdm_coef00_csc);
    VDP_GP_SetGdmGdmCoef01Csc(VDP_LAYER_GP0, gdm_coef01_csc);
    VDP_GP_SetGdmGdmCoef02Csc(VDP_LAYER_GP0, gdm_coef02_csc);
    VDP_GP_SetGdmGdmCoef10Csc(VDP_LAYER_GP0, gdm_coef10_csc);
    VDP_GP_SetGdmGdmCoef11Csc(VDP_LAYER_GP0, gdm_coef11_csc);
    VDP_GP_SetGdmGdmCoef12Csc(VDP_LAYER_GP0, gdm_coef12_csc);
    VDP_GP_SetGdmGdmCoef20Csc(VDP_LAYER_GP0, gdm_coef20_csc);
    VDP_GP_SetGdmGdmCoef21Csc(VDP_LAYER_GP0, gdm_coef21_csc);
    VDP_GP_SetGdmGdmCoef22Csc(VDP_LAYER_GP0, gdm_coef22_csc);
    VDP_GP_SetGdmGdmCscScale(VDP_LAYER_GP0, gdm_csc_scale);
    VDP_GP_SetGdmGdmCscClipMin(VDP_LAYER_GP0, gdm_csc_clip_min);
    VDP_GP_SetGdmGdmCscClipMax(VDP_LAYER_GP0, gdm_csc_clip_max);
    VDP_GP_SetGdmGdmRgb2yuvEn(VDP_LAYER_GP0, gdm_rgb2yuv_en);
    VDP_GP_SetGdmGdm00Rgb2yuv(VDP_LAYER_GP0, gdm_00_rgb2yuv);
    VDP_GP_SetGdmGdm01Rgb2yuv(VDP_LAYER_GP0, gdm_01_rgb2yuv);
    VDP_GP_SetGdmGdm02Rgb2yuv(VDP_LAYER_GP0, gdm_02_rgb2yuv);
    VDP_GP_SetGdmGdm10Rgb2yuv(VDP_LAYER_GP0, gdm_10_rgb2yuv);
    VDP_GP_SetGdmGdm11Rgb2yuv(VDP_LAYER_GP0, gdm_11_rgb2yuv);
    VDP_GP_SetGdmGdm12Rgb2yuv(VDP_LAYER_GP0, gdm_12_rgb2yuv);
    VDP_GP_SetGdmGdm20Rgb2yuv(VDP_LAYER_GP0, gdm_20_rgb2yuv);
    VDP_GP_SetGdmGdm21Rgb2yuv(VDP_LAYER_GP0, gdm_21_rgb2yuv);
    VDP_GP_SetGdmGdm22Rgb2yuv(VDP_LAYER_GP0, gdm_22_rgb2yuv);
    VDP_GP_SetGdmGdmRgb2yuvscale2p(VDP_LAYER_GP0, gdm_rgb2yuvscale2p);
    VDP_GP_SetGdmGdmRgb2yuv0InDc(VDP_LAYER_GP0, gdm_rgb2yuv_0_in_dc);
    VDP_GP_SetGdmGdmRgb2yuv1InDc(VDP_LAYER_GP0, gdm_rgb2yuv_1_in_dc);
    VDP_GP_SetGdmGdmRgb2yuv2InDc(VDP_LAYER_GP0, gdm_rgb2yuv_2_in_dc);
    VDP_GP_SetGdmGdmRgb2yuv0OutDc(VDP_LAYER_GP0, gdm_rgb2yuv_0_out_dc);
    VDP_GP_SetGdmGdmRgb2yuv1OutDc(VDP_LAYER_GP0, gdm_rgb2yuv_1_out_dc);
    VDP_GP_SetGdmGdmRgb2yuv2OutDc(VDP_LAYER_GP0, gdm_rgb2yuv_2_out_dc);
    VDP_GP_SetGdmGdmRgb2yuvClipMin(VDP_LAYER_GP0, gdm_rgb2yuv_clip_min);
    VDP_GP_SetGdmGdmRgb2yuvClipMax(VDP_LAYER_GP0, gdm_rgb2yuv_clip_max);
    VDP_GP_SetGdmGdmDitherRoundUnlim(VDP_LAYER_GP0, gdm_dither_round_unlim);
    VDP_GP_SetGdmGdmDitherEn(VDP_LAYER_GP0, gdm_dither_en);
    VDP_GP_SetGdmGdmDitherMode(VDP_LAYER_GP0, gdm_dither_mode);
    VDP_GP_SetGdmGdmDitherRound(VDP_LAYER_GP0, gdm_dither_round);
    VDP_GP_SetGdmGdmDitherDomainMode(VDP_LAYER_GP0, gdm_dither_domain_mode);
    VDP_GP_SetGdmGdmDitherTapMode(VDP_LAYER_GP0, gdm_dither_tap_mode);
    VDP_GP_SetGdmGdmDitherSedY0(VDP_LAYER_GP0, gdm_dither_sed_y0);
    VDP_GP_SetGdmGdmDitherSedU0(VDP_LAYER_GP0, gdm_dither_sed_u0);
    VDP_GP_SetGdmGdmDitherSedV0(VDP_LAYER_GP0, gdm_dither_sed_v0);
    VDP_GP_SetGdmGdmDitherSedW0(VDP_LAYER_GP0, gdm_dither_sed_w0);
    VDP_GP_SetGdmGdmDitherSedY1(VDP_LAYER_GP0, gdm_dither_sed_y1);
    VDP_GP_SetGdmGdmDitherSedU1(VDP_LAYER_GP0, gdm_dither_sed_u1);
    VDP_GP_SetGdmGdmDitherSedV1(VDP_LAYER_GP0, gdm_dither_sed_v1);
    VDP_GP_SetGdmGdmDitherSedW1(VDP_LAYER_GP0, gdm_dither_sed_w1);
    VDP_GP_SetGdmGdmDitherSedY2(VDP_LAYER_GP0, gdm_dither_sed_y2);
    VDP_GP_SetGdmGdmDitherSedU2(VDP_LAYER_GP0, gdm_dither_sed_u2);
    VDP_GP_SetGdmGdmDitherSedV2(VDP_LAYER_GP0, gdm_dither_sed_v2);
    VDP_GP_SetGdmGdmDitherSedW2(VDP_LAYER_GP0, gdm_dither_sed_w2);
    VDP_GP_SetGdmGdmDitherSedY3(VDP_LAYER_GP0, gdm_dither_sed_y3);
    VDP_GP_SetGdmGdmDitherSedU3(VDP_LAYER_GP0, gdm_dither_sed_u3);
    VDP_GP_SetGdmGdmDitherSedV3(VDP_LAYER_GP0, gdm_dither_sed_v3);
    VDP_GP_SetGdmGdmDitherSedW3(VDP_LAYER_GP0, gdm_dither_sed_w3);
    VDP_GP_SetGdmGdmDitherThrMax(VDP_LAYER_GP0, gdm_dither_thr_max);
    VDP_GP_SetGdmGdmDitherThrMin(VDP_LAYER_GP0, gdm_dither_thr_min);

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

//#endif
