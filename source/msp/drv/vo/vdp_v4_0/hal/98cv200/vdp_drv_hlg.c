#include "hi_type.h"
#include "vdp_define.h"
#include "vdp_drv_pq_hdr.h"
#include "vdp_drv_hdr.h"
#include "vdp_hal_hdr.h"
#include "vdp_hal_vid.h"
#include "vdp_hal_gfx.h"
#include "vdp_hal_mmu.h"
#include "vdp_hal_chn.h"
#include "drv_pq_ext.h"
#include "vdp_drv_func.h"

#include "vdp_drv_comm.h"
#include "vdp_drv_pq_zme.h"
#include "vdp_hal_comm.h"
#if VDP_CBB_FPGA
#include "hi_drv_mmz.h"
#endif
#include "vdp_drv_hihdr.h"
#include "vdp_drv_bt2020.h"


HI_VOID VDP_DRV_SetHisiGdmHdr10InHlgOut(VDP_HISI_HDR_CFG_S  *stHdrCfg)
{
#if 1
    HI_U32 g_degamma_en = 1;
    HI_U32 g_gamma_en = 1;
    HI_U32 gcvm_en = 1;
    HI_U32 cvm_sel = 0;
    HI_U32 gdm_en = 1;
    HI_U32 g_rgb2lms_en ;
    int16_t csc_coef[3][3] = {{0}, {0}, {0}};
    HI_S32 csc_offset[3] = {0};
    HI_U32 g_degmm_step[4] ;
    HI_U32 g_degmm_pos[4] ;
    HI_U32 g_degmm_num[4] ;
    HI_U32 g_gmm_step[4] ;
    HI_U32 g_gmm_pos[4] ;
    HI_U32 g_gmm_num[4] ;
    HI_U32 g_rgb2yuv_en ;
    HI_U32 u32Pre ;
    HI_U32 u32DcPre ;
    HI_U32 u32Scale;
    HI_S32 m33Yuv2Rgb[3][3] = {{0}, {0}, {0}};
    HI_S32 m33Yuv2RgbDc[3] = {0};
    g_rgb2lms_en = 1;
    g_rgb2yuv_en = 1;
    g_degmm_pos[0] = 64;
    g_degmm_pos[1] = 64 * 2;
    g_degmm_pos[2] = 64 * 3;
    g_degmm_pos[3] = 252;//255;
    g_degmm_step[0] = 2;
    g_degmm_step[1] = 2;
    g_degmm_step[2] = 2;
    g_degmm_step[3] = 2;
    g_degmm_num[0] = 16;
    g_degmm_num[1] = 16;
    g_degmm_num[2] = 16;
    g_degmm_num[3] = 15;
#if 1
    g_gmm_pos[0] = 557056 ;
    g_gmm_pos[1] = 2916352 ;
    g_gmm_pos[2] = 14450688 ;
    g_gmm_pos[3] = 29130752;
    g_gmm_step[0] = 15;
    g_gmm_step[1] = 17;
    g_gmm_step[2] = 19;
    g_gmm_step[3] = 21;
    g_gmm_num[0] = 17;
    g_gmm_num[1] = 18;
    g_gmm_num[2] = 22;
    g_gmm_num[3] = 7;
#endif
    VDP_HDR_SetGDmEn(gdm_en);
    VDP_HDR_SetGDmDegammaEn ( g_degamma_en);
    VDP_HDR_SetGDmRgb2lmsEn ( g_rgb2lms_en ) ;
    csc_coef[0][0] = 10279;
    csc_coef[0][1] = 5396;
    csc_coef[0][2] = 710;
    csc_coef[1][0] = 1134;
    csc_coef[1][1] = 15064;
    csc_coef[1][2] = 187;
    csc_coef[2][0] = 268;
    csc_coef[2][1] = 1442;
    csc_coef[2][2] = 14673;
    if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        csc_coef[0][0] = 16384;
        csc_coef[0][1] = 0;
        csc_coef[0][2] = 0;
        csc_coef[1][0] = 0;
        csc_coef[1][1] = 16384;
        csc_coef[1][2] = 0;
        csc_coef[2][0] = 0;
        csc_coef[2][1] = 0;
        csc_coef[2][2] = 16384;
    }
    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;
    VDP_HDR_SetGDmImapRgb2lms ( csc_coef ) ;
    VDP_HDR_SetGDmImapRgb2lmsscale2p ( 14 ) ;
    VDP_HDR_SetGDmImapRgb2lmsmin ( 0 );
    VDP_HDR_SetGDmImapRgb2lmsmax ( 26214400 );
    VDP_HDR_SetGDmImapRgb2lmsOutDc ( csc_offset ) ;
#if 1//Full rgb -> Full yuv out
    VDP_HDR_SetCvmEn (true);
    VDP_HDR_SetGCvmRgb2yuvEn (true);
    u32Pre = 1 << 10;
    u32Scale = 1 << (15 - 10 );
    u32DcPre = 4 * 64;
    m33Yuv2Rgb[0][0] = (HI_S32)( 0.2249 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][1] = (HI_S32)( 0.5806 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][2] = (HI_S32)( 0.0508 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][0] = (HI_S32)(-0.1223* 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][1] = (HI_S32)(-0.3156* 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][2] = (HI_S32)( 0.4379* 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][0] = (HI_S32)( 0.4379* 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][1] = (HI_S32)( -0.4027* 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][2] = (HI_S32)(-0.0352* 0.5 * u32Pre * u32Scale / 2);

    if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        m33Yuv2Rgb[0][0] = (HI_S32)( 0.1821 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][1] = (HI_S32)( 0.6124 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][2] = (HI_S32)( 0.0618 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][0] = (HI_S32)(-0.1003* 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][1] = (HI_S32)(-0.3376* 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][2] = (HI_S32)( 0.4379* 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][0] = (HI_S32)( 0.4379* 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][1] = (HI_S32)( -0.3978* 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][2] = (HI_S32)(-0.0402* 0.5 * u32Pre * u32Scale / 2);
    }
    m33Yuv2RgbDc[0] = (HI_S32)(16 * u32DcPre / 2);
    m33Yuv2RgbDc[1] = (HI_S32)(128 * u32DcPre / 2);
    m33Yuv2RgbDc[2] = (HI_S32)(128 * u32DcPre / 2);
    VDP_HDR_SetGCvmOmapRgb2yuvscale2p(15 | (1 << 5) );
    VDP_HDR_SetGCvmOmapRgb2yuv (m33Yuv2Rgb );
    VDP_HDR_SetGCvmOmapRgb2yuvOutDc (m33Yuv2RgbDc );
    VDP_HDR_SetGCvmOmapRgb2yuvmin (0);
    VDP_HDR_SetGCvmOmapRgb2yuvmax (0x7FFF);
#endif
    VDP_HDR_SetGDmDegmmPos ( g_degmm_pos);
    VDP_HDR_SetGDmDegmmStep ( g_degmm_step);
    VDP_HDR_SetGDmDegmmNum ( g_degmm_num);
    VDP_HDR_SetGDmGammaEn ( g_gamma_en);
    VDP_HDR_SetGDmGammaPos ( g_gmm_pos);
    VDP_HDR_SetGDmGammaStep ( g_gmm_step);
    VDP_HDR_SetGDmGmmNum ( g_gmm_num);
    VDP_HDR_SetAuthEn ( gcvm_en);
    VDP_HDR_SetCvmSel ( cvm_sel);
#endif
}

HI_VOID VDP_DRV_SetHisiGdmHlgInHlgOut(VDP_HISI_HDR_CFG_S  *stHdrCfg)
{
#if 1
    HI_U32 g_degamma_en = 1;
    HI_U32 g_gamma_en = 1;
    HI_U32 gcvm_en = 1;
    HI_U32 cvm_sel = 0;
    HI_U32 gdm_en = 1;
    HI_U32 g_rgb2lms_en ;
    int16_t csc_coef[3][3] = {{0}, {0}, {0}};
    HI_S32 csc_offset[3] = {0};
    HI_U32 g_degmm_step[4] ;
    HI_U32 g_degmm_pos[4] ;
    HI_U32 g_degmm_num[4] ;
    HI_U32 g_gmm_step[4] ;
    HI_U32 g_gmm_pos[4] ;
    HI_U32 g_gmm_num[4] ;
    HI_U32 g_rgb2yuv_en ;
    HI_U32 u32Pre ;
    HI_U32 u32DcPre ;
    HI_U32 u32Scale;
    HI_S32 m33Yuv2Rgb[3][3] = {{0}, {0}, {0}};
    HI_S32 m33Yuv2RgbDc[3] = {0};
    g_rgb2lms_en = 1;
    g_rgb2yuv_en = 1;
    g_degmm_pos[0] = 64;
    g_degmm_pos[1] = 64 * 2;
    g_degmm_pos[2] = 64 * 3;
    g_degmm_pos[3] = 252;//255;
    g_degmm_step[0] = 2;
    g_degmm_step[1] = 2;
    g_degmm_step[2] = 2;
    g_degmm_step[3] = 2;
    g_degmm_num[0] = 16;
    g_degmm_num[1] = 16;
    g_degmm_num[2] = 16;
    g_degmm_num[3] = 15;
#if 1
    g_gmm_pos[0] = 557056 ;
    g_gmm_pos[1] = 2916352 ;
    g_gmm_pos[2] = 14450688 ;
    g_gmm_pos[3] = 29130752;
    g_gmm_step[0] = 15;
    g_gmm_step[1] = 17;
    g_gmm_step[2] = 19;
    g_gmm_step[3] = 21;
    g_gmm_num[0] = 17;
    g_gmm_num[1] = 18;
    g_gmm_num[2] = 22;
    g_gmm_num[3] = 7;
#endif
    VDP_HDR_SetGDmEn(gdm_en);
    VDP_HDR_SetGDmDegammaEn ( g_degamma_en);
    VDP_HDR_SetGDmRgb2lmsEn ( g_rgb2lms_en ) ;
    csc_coef[0][0] = 10279;
    csc_coef[0][1] = 5396;
    csc_coef[0][2] = 710;
    csc_coef[1][0] = 1134;
    csc_coef[1][1] = 15064;
    csc_coef[1][2] = 187;
    csc_coef[2][0] = 268;
    csc_coef[2][1] = 1442;
    csc_coef[2][2] = 14673;
    if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        csc_coef[0][0] = 16384;
        csc_coef[0][1] = 0;
        csc_coef[0][2] = 0;
        csc_coef[1][0] = 0;
        csc_coef[1][1] = 16384;
        csc_coef[1][2] = 0;
        csc_coef[2][0] = 0;
        csc_coef[2][1] = 0;
        csc_coef[2][2] = 16384;
    }
    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;
    VDP_HDR_SetGDmImapRgb2lms ( csc_coef ) ;
    VDP_HDR_SetGDmImapRgb2lmsscale2p ( 14 ) ;
    VDP_HDR_SetGDmImapRgb2lmsmin ( 0 );
    VDP_HDR_SetGDmImapRgb2lmsmax ( 26214400 );
    VDP_HDR_SetGDmImapRgb2lmsOutDc ( csc_offset ) ;
#if 1//Full rgb -> Full yuv out
    VDP_HDR_SetCvmEn (true);
    VDP_HDR_SetGCvmRgb2yuvEn (true);
    u32Pre = 1 << 10;
    u32Scale = 1 << (15 - 10 );
    u32DcPre = 4 * 64;
    m33Yuv2Rgb[0][0] = (HI_S32)( 0.2249 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][1] = (HI_S32)( 0.5806 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][2] = (HI_S32)( 0.0508 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][0] = (HI_S32)(-0.1223 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][1] = (HI_S32)(-0.3156 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][2] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][0] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][1] = (HI_S32)( -0.4027 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][2] = (HI_S32)(-0.0352 * u32Pre * u32Scale / 2);

    if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        m33Yuv2Rgb[0][0] = (HI_S32)( 0.1821 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][1] = (HI_S32)( 0.6124 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][2] = (HI_S32)( 0.0618 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][0] = (HI_S32)(-0.1003 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][1] = (HI_S32)(-0.3376 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][2] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][0] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][1] = (HI_S32)( -0.3978 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][2] = (HI_S32)(-0.0402 * u32Pre * u32Scale / 2);
    }
    m33Yuv2RgbDc[0] = (HI_S32)(16 * u32DcPre / 2);
    m33Yuv2RgbDc[1] = (HI_S32)(128 * u32DcPre / 2);
    m33Yuv2RgbDc[2] = (HI_S32)(128 * u32DcPre / 2);
    VDP_HDR_SetGCvmOmapRgb2yuvscale2p(15 | (1 << 5) );
    VDP_HDR_SetGCvmOmapRgb2yuv (m33Yuv2Rgb );
    VDP_HDR_SetGCvmOmapRgb2yuvOutDc (m33Yuv2RgbDc );
    VDP_HDR_SetGCvmOmapRgb2yuvmin (0);
    VDP_HDR_SetGCvmOmapRgb2yuvmax (0x7FFF);
#endif
    VDP_HDR_SetGDmDegmmPos ( g_degmm_pos);
    VDP_HDR_SetGDmDegmmStep ( g_degmm_step);
    VDP_HDR_SetGDmDegmmNum ( g_degmm_num);
    VDP_HDR_SetGDmGammaEn ( g_gamma_en);
    VDP_HDR_SetGDmGammaPos ( g_gmm_pos);
    VDP_HDR_SetGDmGammaStep ( g_gmm_step);
    VDP_HDR_SetGDmGmmNum ( g_gmm_num);
    VDP_HDR_SetAuthEn ( gcvm_en);
    VDP_HDR_SetCvmSel ( cvm_sel);
#endif
}

HI_VOID VDP_DRV_SetHisiGdmHdr10InHdr10OutTmpHyx(VDP_HISI_HDR_CFG_S  *stHdrCfg)
{
#if 1
    HI_U32 g_degamma_en = 0;
    HI_U32 g_gamma_en = 0;
    HI_U32 gcvm_en = 0;
    HI_U32 cvm_sel = 0;
    HI_U32 gdm_en = 0;
    HI_U32 g_rgb2lms_en ;
    int16_t csc_coef[3][3] = {{0}, {0}, {0}};
    HI_S32 csc_offset[3] = {0};
    HI_U32 g_degmm_step[4] ;
    HI_U32 g_degmm_pos[4] ;
    HI_U32 g_degmm_num[4] ;
    HI_U32 g_gmm_step[4] ;
    HI_U32 g_gmm_pos[4] ;
    HI_U32 g_gmm_num[4] ;
    HI_U32 g_rgb2yuv_en ;
    HI_U32 u32Pre ;
    HI_U32 u32DcPre ;
    HI_U32 u32Scale;
    HI_S32 m33Yuv2Rgb[3][3] = {{0}, {0}, {0}};
    HI_S32 m33Yuv2RgbDc[3] = {0};
    g_rgb2lms_en = 1;
    g_rgb2yuv_en = 1;
    g_degmm_pos[0] = 64;
    g_degmm_pos[1] = 64 * 2;
    g_degmm_pos[2] = 64 * 3;
    g_degmm_pos[3] = 252;//255;
    g_degmm_step[0] = 2;
    g_degmm_step[1] = 2;
    g_degmm_step[2] = 2;
    g_degmm_step[3] = 2;
    g_degmm_num[0] = 16;
    g_degmm_num[1] = 16;
    g_degmm_num[2] = 16;
    g_degmm_num[3] = 15;
#if 1
    g_gmm_pos[0] = 557056 ;
    g_gmm_pos[1] = 2916352 ;
    g_gmm_pos[2] = 14450688 ;
    g_gmm_pos[3] = 29130752;
    g_gmm_step[0] = 15;
    g_gmm_step[1] = 17;
    g_gmm_step[2] = 19;
    g_gmm_step[3] = 21;
    g_gmm_num[0] = 17;
    g_gmm_num[1] = 18;
    g_gmm_num[2] = 22;
    g_gmm_num[3] = 7;
#endif
    VDP_HDR_SetGDmEn(gdm_en);
    VDP_HDR_SetGDmDegammaEn ( g_degamma_en);
    VDP_HDR_SetGDmRgb2lmsEn ( g_rgb2lms_en ) ;
    csc_coef[0][0] = 10279;
    csc_coef[0][1] = 5396;
    csc_coef[0][2] = 710;
    csc_coef[1][0] = 1134;
    csc_coef[1][1] = 15064;
    csc_coef[1][2] = 187;
    csc_coef[2][0] = 268;
    csc_coef[2][1] = 1442;
    csc_coef[2][2] = 14673;

    //if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        csc_coef[0][0] = 16384;
        csc_coef[0][1] = 0;
        csc_coef[0][2] = 0;
        csc_coef[1][0] = 0;
        csc_coef[1][1] = 16384;
        csc_coef[1][2] = 0;
        csc_coef[2][0] = 0;
        csc_coef[2][1] = 0;
        csc_coef[2][2] = 16384;
    }
    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;
    VDP_HDR_SetGDmImapRgb2lms ( csc_coef ) ;
    VDP_HDR_SetGDmImapRgb2lmsscale2p ( 14 ) ;
    VDP_HDR_SetGDmImapRgb2lmsmin ( 0 );
    VDP_HDR_SetGDmImapRgb2lmsmax ( 26214400 );
    VDP_HDR_SetGDmImapRgb2lmsOutDc ( csc_offset ) ;
#if 1//Full rgb -> Full yuv out
    VDP_HDR_SetCvmEn (true);
    VDP_HDR_SetGCvmRgb2yuvEn (true);
    u32Pre = 1 << 10;
    u32Scale = 1 << (15 - 10 );
    u32DcPre = 4 * 64;
    m33Yuv2Rgb[0][0] = (HI_S32)( 0.2249 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][1] = (HI_S32)( 0.5806 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][2] = (HI_S32)( 0.0508 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][0] = (HI_S32)(-0.1223 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][1] = (HI_S32)(-0.3156 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][2] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][0] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][1] = (HI_S32)( -0.4027 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][2] = (HI_S32)(-0.0352 * u32Pre * u32Scale / 2);
    // if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        m33Yuv2Rgb[0][0] = (HI_S32)( 1 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][1] = (HI_S32)( 0 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][2] = (HI_S32)( 0 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][0] = (HI_S32)(0 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][1] = (HI_S32)(1 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][2] = (HI_S32)( 0 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][0] = (HI_S32)( 0 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][1] = (HI_S32)( 0 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][2] = (HI_S32)(1 * u32Pre * u32Scale / 2);
    }
    m33Yuv2RgbDc[0] = 0;//(HI_S32)(16 * u32DcPre / 2);
    m33Yuv2RgbDc[1] = 0;//(HI_S32)(128 * u32DcPre / 2);
    m33Yuv2RgbDc[2] = 0;//(HI_S32)(128 * u32DcPre / 2);
    VDP_HDR_SetGCvmOmapRgb2yuvscale2p(15 | (1 << 5) );
    VDP_HDR_SetGCvmOmapRgb2yuv (m33Yuv2Rgb );
    VDP_HDR_SetGCvmOmapRgb2yuvOutDc (m33Yuv2RgbDc );
    VDP_HDR_SetGCvmOmapRgb2yuvmin (0);
    VDP_HDR_SetGCvmOmapRgb2yuvmax (0x7FFF);
#endif
    VDP_HDR_SetGDmDegmmPos ( g_degmm_pos);
    VDP_HDR_SetGDmDegmmStep ( g_degmm_step);
    VDP_HDR_SetGDmDegmmNum ( g_degmm_num);
    VDP_HDR_SetGDmGammaEn ( g_gamma_en);
    VDP_HDR_SetGDmGammaPos ( g_gmm_pos);
    VDP_HDR_SetGDmGammaStep ( g_gmm_step);
    VDP_HDR_SetGDmGmmNum ( g_gmm_num);
    VDP_HDR_SetAuthEn ( gcvm_en);
    VDP_HDR_SetCvmSel ( cvm_sel);
#endif
}


HI_VOID VDP_DRV_SetHisiGdmHlgInSdrOut(VDP_HISI_HDR_CFG_S  *stHdrCfg)
{
#if 1
    HI_U32 g_degamma_en = 1;
    HI_U32 g_gamma_en = 1;
    HI_U32 gcvm_en = 1;
    HI_U32 cvm_sel = 0;
    HI_U32 gdm_en = 1;
    HI_U32 g_rgb2lms_en ;
    int16_t csc_coef[3][3] = {{0}, {0}, {0}};
    HI_S32 csc_offset[3] = {0};
    HI_U32 g_degmm_step[4] ;
    HI_U32 g_degmm_pos[4] ;
    HI_U32 g_degmm_num[4] ;
    HI_U32 g_gmm_step[4] ;
    HI_U32 g_gmm_pos[4] ;
    HI_U32 g_gmm_num[4] ;
    HI_U32 g_rgb2yuv_en ;
    HI_U32 u32Pre ;
    HI_U32 u32DcPre ;
    HI_U32 u32Scale;
    HI_S32 m33Yuv2Rgb[3][3] = {{0}, {0}, {0}};
    HI_S32 m33Yuv2RgbDc[3] = {0};
    g_rgb2lms_en = 1;
    g_rgb2yuv_en = 1;
    g_degmm_pos[0] = 64;
    g_degmm_pos[1] = 64 * 2;
    g_degmm_pos[2] = 64 * 3;
    g_degmm_pos[3] = 252;//255;
    g_degmm_step[0] = 2;
    g_degmm_step[1] = 2;
    g_degmm_step[2] = 2;
    g_degmm_step[3] = 2;
    g_degmm_num[0] = 16;
    g_degmm_num[1] = 16;
    g_degmm_num[2] = 16;
    g_degmm_num[3] = 15;
#if 1

    g_gmm_pos[0] = 557056 ;
    g_gmm_pos[1] = 2916352 ;
    g_gmm_pos[2] = 14450688 ;
    g_gmm_pos[3] = 29130752;
    g_gmm_step[0] = 15;
    g_gmm_step[1] = 17;
    g_gmm_step[2] = 19;
    g_gmm_step[3] = 21;
    g_gmm_num[0] = 17;
    g_gmm_num[1] = 18;
    g_gmm_num[2] = 22;
    g_gmm_num[3] = 7;
#endif
    VDP_HDR_SetGDmEn(gdm_en);
    VDP_HDR_SetGDmDegammaEn ( g_degamma_en);
    VDP_HDR_SetGDmRgb2lmsEn ( g_rgb2lms_en ) ;

    csc_coef[0][0] = 16384;
    csc_coef[0][1] = 0;
    csc_coef[0][2] = 0;
    csc_coef[1][0] = 0;
    csc_coef[1][1] = 16384;
    csc_coef[1][2] = 0;
    csc_coef[2][0] = 0;
    csc_coef[2][1] = 0;
    csc_coef[2][2] = 16384;

    if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        csc_coef[0][0] = 16384;
        csc_coef[0][1] = 0;
        csc_coef[0][2] = 0;
        csc_coef[1][0] = 0;
        csc_coef[1][1] = 16384;
        csc_coef[1][2] = 0;
        csc_coef[2][0] = 0;
        csc_coef[2][1] = 0;
        csc_coef[2][2] = 16384;
    }

    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;
    VDP_HDR_SetGDmImapRgb2lms ( csc_coef ) ;
    VDP_HDR_SetGDmImapRgb2lmsscale2p ( 14 ) ;
    VDP_HDR_SetGDmImapRgb2lmsmin ( 0 );
    VDP_HDR_SetGDmImapRgb2lmsmax ( 26214400 );
    VDP_HDR_SetGDmImapRgb2lmsOutDc ( csc_offset ) ;
#if 1//Full rgb -> Full yuv out
    VDP_HDR_SetCvmEn (true);
    VDP_HDR_SetGCvmRgb2yuvEn (true);
    u32Pre = 1 << 10;
    u32Scale = 1 << (15 - 10 );
    u32DcPre = 4 * 64;

    /*m33Yuv2Rgb[0][0] = (HI_S32)( 0.2249 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][1] = (HI_S32)( 0.5806 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][2] = (HI_S32)( 0.0508 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][0] = (HI_S32)(-0.1223 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][1] = (HI_S32)(-0.3156 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][2] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][0] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][1] = (HI_S32)( -0.4027 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][2] = (HI_S32)(-0.0352 * u32Pre * u32Scale / 2);

    if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)*/

    {
        m33Yuv2Rgb[0][0] = (HI_S32)( 0.1821 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][1] = (HI_S32)( 0.6124 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][2] = (HI_S32)( 0.0618 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][0] = (HI_S32)(-0.1003 * 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][1] = (HI_S32)(-0.3376 * 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][2] = (HI_S32)( 0.4379 * 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][0] = (HI_S32)( 0.4379 * 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][1] = (HI_S32)( -0.3978 * 0.5 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][2] = (HI_S32)(-0.0402 * 0.5 * u32Pre * u32Scale / 2);
    }



    VDP_PRINT("m33Yuv2Rgb[0][0] = %d \n", m33Yuv2Rgb[0][0]);
    VDP_PRINT("m33Yuv2Rgb[0][1] = %d \n", m33Yuv2Rgb[0][1]);
    VDP_PRINT("m33Yuv2Rgb[0][2] = %d \n", m33Yuv2Rgb[0][2]);
    VDP_PRINT("m33Yuv2Rgb[1][0] = %d \n", m33Yuv2Rgb[1][0]);
    VDP_PRINT("m33Yuv2Rgb[1][1] = %d \n", m33Yuv2Rgb[1][1]);
    VDP_PRINT("m33Yuv2Rgb[1][2] = %d \n", m33Yuv2Rgb[1][2]);
    VDP_PRINT("m33Yuv2Rgb[2][0] = %d \n", m33Yuv2Rgb[2][0]);
    VDP_PRINT("m33Yuv2Rgb[2][1] = %d \n", m33Yuv2Rgb[2][1]);
    VDP_PRINT("m33Yuv2Rgb[2][2] = %d \n", m33Yuv2Rgb[2][2]);


    m33Yuv2RgbDc[0] = (HI_S32)(16 * u32DcPre / 2);
    m33Yuv2RgbDc[1] = (HI_S32)(128 * u32DcPre / 2);
    m33Yuv2RgbDc[2] = (HI_S32)(128 * u32DcPre / 2);
    VDP_HDR_SetGCvmOmapRgb2yuvscale2p(15 | (1 << 5) );
    VDP_HDR_SetGCvmOmapRgb2yuv (m33Yuv2Rgb );
    VDP_HDR_SetGCvmOmapRgb2yuvOutDc (m33Yuv2RgbDc );
    VDP_HDR_SetGCvmOmapRgb2yuvmin (0);
    VDP_HDR_SetGCvmOmapRgb2yuvmax (0x7FFF);
#endif
    VDP_HDR_SetGDmDegmmPos ( g_degmm_pos);
    VDP_HDR_SetGDmDegmmStep ( g_degmm_step);
    VDP_HDR_SetGDmDegmmNum ( g_degmm_num);
    VDP_HDR_SetGDmGammaEn ( g_gamma_en);
    VDP_HDR_SetGDmGammaPos ( g_gmm_pos);
    VDP_HDR_SetGDmGammaStep ( g_gmm_step);
    VDP_HDR_SetGDmGmmNum ( g_gmm_num);
    VDP_HDR_SetAuthEn ( gcvm_en);
    VDP_HDR_SetCvmSel ( cvm_sel);
#endif
}



HI_VOID VDP_DRV_SetHisiGdmHlgInHdr10Out(VDP_HISI_HDR_CFG_S  *stHdrCfg)
{
#if 1
    HI_U32 g_degamma_en = 1;
    HI_U32 g_gamma_en = 1;
    HI_U32 gcvm_en = 1;
    HI_U32 cvm_sel = 0;
    HI_U32 gdm_en = 1;
    HI_U32 g_rgb2lms_en ;
    int16_t csc_coef[3][3] = {{0}, {0}, {0}};
    HI_S32 csc_offset[3] = {0};
    HI_U32 g_degmm_step[4] ;
    HI_U32 g_degmm_pos[4] ;
    HI_U32 g_degmm_num[4] ;
    HI_U32 g_gmm_step[4] ;
    HI_U32 g_gmm_pos[4] ;
    HI_U32 g_gmm_num[4] ;
    HI_U32 g_rgb2yuv_en ;
    HI_U32 u32Pre ;
    HI_U32 u32DcPre ;
    HI_U32 u32Scale;
    HI_S32 m33Yuv2Rgb[3][3] = {{0}, {0}, {0}};
    HI_S32 m33Yuv2RgbDc[3] = {0};
    g_rgb2lms_en = 1;
    g_rgb2yuv_en = 1;
    g_degmm_pos[0] = 64;
    g_degmm_pos[1] = 64 * 2;
    g_degmm_pos[2] = 64 * 3;
    g_degmm_pos[3] = 252;//255;
    g_degmm_step[0] = 2;
    g_degmm_step[1] = 2;
    g_degmm_step[2] = 2;
    g_degmm_step[3] = 2;
    g_degmm_num[0] = 16;
    g_degmm_num[1] = 16;
    g_degmm_num[2] = 16;
    g_degmm_num[3] = 15;
#if 1
    g_gmm_pos[0] = 557056 ;
    g_gmm_pos[1] = 2916352 ;
    g_gmm_pos[2] = 14450688 ;
    g_gmm_pos[3] = 29130752;
    g_gmm_step[0] = 15;
    g_gmm_step[1] = 17;
    g_gmm_step[2] = 19;
    g_gmm_step[3] = 21;
    g_gmm_num[0] = 17;
    g_gmm_num[1] = 18;
    g_gmm_num[2] = 22;
    g_gmm_num[3] = 7;
#endif
    VDP_HDR_SetGDmEn(gdm_en);
    VDP_HDR_SetGDmDegammaEn ( g_degamma_en);
    VDP_HDR_SetGDmRgb2lmsEn ( g_rgb2lms_en ) ;
    csc_coef[0][0] = 10279;
    csc_coef[0][1] = 5396;
    csc_coef[0][2] = 710;
    csc_coef[1][0] = 1134;
    csc_coef[1][1] = 15064;
    csc_coef[1][2] = 187;
    csc_coef[2][0] = 268;
    csc_coef[2][1] = 1442;
    csc_coef[2][2] = 14673;

#if 0
    if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        csc_coef[0][0] = 16384;
        csc_coef[0][1] = 0;
        csc_coef[0][2] = 0;
        csc_coef[1][0] = 0;
        csc_coef[1][1] = 16384;
        csc_coef[1][2] = 0;
        csc_coef[2][0] = 0;
        csc_coef[2][1] = 0;
        csc_coef[2][2] = 16384;
    }
#endif
    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;
    VDP_HDR_SetGDmImapRgb2lms ( csc_coef ) ;
    VDP_HDR_SetGDmImapRgb2lmsscale2p ( 14 ) ;
    VDP_HDR_SetGDmImapRgb2lmsmin ( 0 );
    VDP_HDR_SetGDmImapRgb2lmsmax ( 26214400 );
    VDP_HDR_SetGDmImapRgb2lmsOutDc ( csc_offset ) ;
#if 1//Full rgb -> Full yuv out
    VDP_HDR_SetCvmEn (true);
    VDP_HDR_SetGCvmRgb2yuvEn (true);
    u32Pre = 1 << 10;
    u32Scale = 1 << (15 - 10 );
    u32DcPre = 4 * 64;
    m33Yuv2Rgb[0][0] = (HI_S32)( 0.2249 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][1] = (HI_S32)( 0.5806 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[0][2] = (HI_S32)( 0.0508 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][0] = (HI_S32)(-0.1223 * 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][1] = (HI_S32)(-0.3156 * 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[1][2] = (HI_S32)( 0.4379 * 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][0] = (HI_S32)( 0.4379 * 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][1] = (HI_S32)( -0.4027 * 0.5 * u32Pre * u32Scale / 2);
    m33Yuv2Rgb[2][2] = (HI_S32)(-0.0352 * 0.5 * u32Pre * u32Scale / 2);
    if (stHdrCfg->enOutClr == VDP_CLR_SPACE_YUV_709_L)
    {
        m33Yuv2Rgb[0][0] = (HI_S32)( 0.1821 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][1] = (HI_S32)( 0.6124 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[0][2] = (HI_S32)( 0.0618 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][0] = (HI_S32)(-0.1003 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][1] = (HI_S32)(-0.3376 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[1][2] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][0] = (HI_S32)( 0.4379 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][1] = (HI_S32)( -0.3978 * u32Pre * u32Scale / 2);
        m33Yuv2Rgb[2][2] = (HI_S32)(-0.0402 * u32Pre * u32Scale / 2);
    }

    VDP_PRINT("m33Yuv2Rgb[0][0] = %d \n", m33Yuv2Rgb[0][0]);
    VDP_PRINT("m33Yuv2Rgb[0][1] = %d \n", m33Yuv2Rgb[0][1]);
    VDP_PRINT("m33Yuv2Rgb[0][2] = %d \n", m33Yuv2Rgb[0][2]);
    VDP_PRINT("m33Yuv2Rgb[1][0] = %d \n", m33Yuv2Rgb[1][0]);
    VDP_PRINT("m33Yuv2Rgb[1][1] = %d \n", m33Yuv2Rgb[1][1]);
    VDP_PRINT("m33Yuv2Rgb[1][2] = %d \n", m33Yuv2Rgb[1][2]);
    VDP_PRINT("m33Yuv2Rgb[2][0] = %d \n", m33Yuv2Rgb[2][0]);
    VDP_PRINT("m33Yuv2Rgb[2][1] = %d \n", m33Yuv2Rgb[2][1]);
    VDP_PRINT("m33Yuv2Rgb[2][2] = %d \n", m33Yuv2Rgb[2][2]);


    m33Yuv2RgbDc[0] = (HI_S32)(16 * u32DcPre / 2);
    m33Yuv2RgbDc[1] = (HI_S32)(128 * u32DcPre / 2);
    m33Yuv2RgbDc[2] = (HI_S32)(128 * u32DcPre / 2);
    VDP_HDR_SetGCvmOmapRgb2yuvscale2p(15 | (1 << 5) );
    VDP_HDR_SetGCvmOmapRgb2yuv (m33Yuv2Rgb );
    VDP_HDR_SetGCvmOmapRgb2yuvOutDc (m33Yuv2RgbDc );
    VDP_HDR_SetGCvmOmapRgb2yuvmin (0);
    VDP_HDR_SetGCvmOmapRgb2yuvmax (0x7FFF);
#endif
    VDP_HDR_SetGDmDegmmPos ( g_degmm_pos);
    VDP_HDR_SetGDmDegmmStep ( g_degmm_step);
    VDP_HDR_SetGDmDegmmNum ( g_degmm_num);
    VDP_HDR_SetGDmGammaEn ( g_gamma_en);
    VDP_HDR_SetGDmGammaPos ( g_gmm_pos);
    VDP_HDR_SetGDmGammaStep ( g_gmm_step);
    VDP_HDR_SetGDmGmmNum ( g_gmm_num);
    VDP_HDR_SetAuthEn ( gcvm_en);
    VDP_HDR_SetCvmSel ( cvm_sel);
#endif
}

HI_S32 VDP_DRV_SetHisiVdmHdr102Hlg(HI_VOID)
{
    int32_t v3IptOff[3];
    int16_t csc_coef[3][3] = {{0}, {0}, {0}};
    HI_S32  csc_offset[3] = {0};

    //composer up sample
    VDP_VID_SetComposeElUpsampleMax    (16383);
    VDP_VID_SetComposeElUpsampleMin    (0);

    //vdm_yuv2rgb
    VDP_HDR_SetVDmYuv2rgbEn            ( 1 );
    VDP_HDR_SetVDmYuv2rgbV0En          ( 1 );
    VDP_HDR_SetVDmYuv2rgbV1En          ( 0 );

    csc_coef[0][0] = 8192 ;
    csc_coef[0][1] = 0    ;
    csc_coef[0][2] = 0    ;
    csc_coef[1][0] = 0 ;
    csc_coef[1][1] = 8192    ;
    csc_coef[1][2] = 0    ;
    csc_coef[2][0] = 0 ;
    csc_coef[2][1] = 0    ;
    csc_coef[2][2] = 8192        ;

    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;

    VDP_HDR_SetVDmImap0Yuv2rgb         (csc_coef);
    VDP_HDR_SetVDmImapYuv2rgbscale2p   (13);
    VDP_HDR_SetVDmImapYuv2rgbOutDc0    (csc_offset);

    VDP_HDR_SetVDmInBits               ( 1 );

    //vdm_rgb2lms
    VDP_HDR_SetVDmRgb2lmsEn            ( 1 );

    csc_coef[0][0] = 16384     ;
    csc_coef[0][1] = 0     ;
    csc_coef[0][2] = 0     ;
    csc_coef[1][0] = 0     ;
    csc_coef[1][1] = 16384    ;
    csc_coef[1][2] = 0     ;
    csc_coef[2][0] = 0      ;
    csc_coef[2][1] = 0     ;
    csc_coef[2][2] = 16384    ;

    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;

    VDP_HDR_SetVDmImapRgb2lms          ( csc_coef );
    VDP_HDR_SetVDmImapRgb2lmsscale2p   ( 14);
    VDP_HDR_SetVDmImapRgb2lmsmin       ( 0 );
    //VDP_HDR_SetVDmImapRgb2lmsmax       ( (HI_U32)((HI_U64)10000*(1<<18))  );
    VDP_HDR_SetVDmImapRgb2lmsmax        ( 0x9c400000  );//(10000LL*(1<<18))

    //cvm1_lms2ipt
    VDP_HDR_SetVCvmLms2iptEn           ( 1 );
    VDP_HDR_SetVDmImapLms2iptmin       (-32768);//  ( 0-((1<<15)-1) );
    VDP_HDR_SetVDmImapLms2iptmax      (32767);// ( ((1<<15)-1) );

    csc_coef[0][0] = 4096     ;
    csc_coef[0][1] = 0     ;
    csc_coef[0][2] = 0            ;
    csc_coef[1][0] = 0     ;
    csc_coef[1][1] = 4096   ;
    csc_coef[1][2] = 0     ;
    csc_coef[2][0] = 0        ;
    csc_coef[2][1] = 0   ;
    csc_coef[2][2] = 4096      ;

    csc_offset[0] = 0;
    csc_offset[1] = -16384;
    csc_offset[2] = -16384;

    VDP_HDR_SetVCvmImapLms2ipt         ( csc_coef         );
    VDP_HDR_SetVCvmImapLms2iptscale2p  ( 12 + 1);//从王正拿过来的参数是12，要加1配置
    VDP_HDR_SetVCvmImapLms2iptOutDc(csc_offset);

    //cvm1_ipt2lms
    VDP_HDR_SetVCvmIpt2lmsEn           ( 1 );


#if 0
    csc_coef[0][0] = 8192    ;
    csc_coef[0][1] = 0  ;
    csc_coef[0][2] = 0 ;
    csc_coef[1][0] = 0    ;
    csc_coef[1][1] = 8192 ;
    csc_coef[1][2] = 0    ;
    csc_coef[2][0] = 0    ;
    csc_coef[2][1] = 0 ;
    csc_coef[2][2] = 8192    ;


    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;

#else

    csc_coef[0][0] =8192 ;
    csc_coef[0][1] =0 ;
    csc_coef[0][2] =12901 ;
    csc_coef[1][0] =8192  ;
    csc_coef[1][1] =-1535;
    csc_coef[1][2] = -3835 ;
    csc_coef[2][0] =8192 ;
    csc_coef[2][1] =15201 ;
    csc_coef[2][2] =0 ;



    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;

#endif

    VDP_HDR_SetVCvmOmapIpt2lms         ( csc_coef      );

    VDP_HDR_SetVCvmOmapIpt2lmsscale2p  ( 13);
    VDP_HDR_SetVDmOmapIpt2lmsmin       ( 0 );
    VDP_HDR_SetVDmOmapIpt2lmsmax      (65535);// ( (1<<16)-1 );

    //cvm1_lms2rgb
    VDP_HDR_SetVCvmLms2rgbEn           ( 1 );

    csc_coef[0][0] = 16384   ;
    csc_coef[0][1] = 0;
    csc_coef[0][2] = 0 ;
    csc_coef[1][0] = 0   ;
    csc_coef[1][1] = 16384   ;
    csc_coef[1][2] = 0   ;
    csc_coef[2][0] =  0    ;
    csc_coef[2][1] = 0   ;
    csc_coef[2][2] = 16384    ;

    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;


    VDP_HDR_SetVCvmOmapLms2rgb         ( csc_coef       );
    VDP_HDR_SetVCvmOmapLms2rgbscale2p  ( 14);
    VDP_HDR_SetVDmOmapLms2rgbmin       ( 0     );
    VDP_HDR_SetVDmOmapLms2rgbmax       ( 2621440000u  );

    //cvm1_rgb2yuv
    VDP_HDR_SetVCvmRgb2yuvEn           ( 1 );

#if 0
    csc_coef[0][0] = 16384 ;
    csc_coef[0][1] = 0    ;
    csc_coef[0][2] = 0 ;
    csc_coef[1][0] = 0    ;
    csc_coef[1][1] = 16384   ;
    csc_coef[1][2] = 0    ;
    csc_coef[2][0] = 0    ;
    csc_coef[2][1] = 0   ;
    csc_coef[2][2] = 16384  ;



    csc_offset[0] = 0;
    csc_offset[1] = 0;//2048;
    csc_offset[2] = 0;//2048;

#else

    csc_coef[0][0] = 3483  ;
    csc_coef[0][1] = 11718  ;
    csc_coef[0][2] = 1183  ;
    csc_coef[1][0] =  -1877  ;
    csc_coef[1][1] =  -6315  ;
    csc_coef[1][2] = 8192  ;
    csc_coef[2][0] = 8192  ;
    csc_coef[2][1] = -7441 ;
    csc_coef[2][2] = -751 ;

    csc_offset[0] = 0;
    csc_offset[1] = 2048;//2048;
    csc_offset[2] = 2048;//2048;

#endif

    VDP_HDR_SetVCvmOmapRgb2yuv         ( csc_coef      );
    VDP_HDR_SetVCvmOmapRgb2yuvscale2p  ( 14);
    VDP_HDR_SetVCvmOmapRgb2yuvOutDc    ( csc_offset     );

    //VDM_PQ2L

    VDP_HDR_SetVDmInEotf               ( 1 );
    VDP_HDR_SetVDmDegammaEn            ( 1 );
    VDP_HDR_SetVCvmEn                  ( 1 );
    VDP_HDR_SetVCvmDegammaEn           ( 1 );
    VDP_HDR_SetVCvmMGammaEn            ( 1 );
    VDP_HDR_SetVDmGammaEn              ( 1 );
    VDP_HDR_SetVDmNormEn               ( 1 );
    VDP_HDR_SetVDmImapRangeMin         ( 0 );
    VDP_HDR_SetVDmImapRange            ( 16383);
    VDP_HDR_SetVDmImapRangeInv         ( 65540     );
    VDP_HDR_SetVCvmOmapRangeMin        ( 0     );
    VDP_HDR_SetVCvmOmapRangeOver       ( 0x0000fff0 );

    VDP_HDR_SetCvmOutBits              ( 2 );//12bit
    VDP_HDR_SetVCvmDenormEn            ( 1 );

    v3IptOff[0] = 64;
    v3IptOff[1] = 512;
    v3IptOff[2] = 512;

    VDP_HDR_SetVDmImapIptoff           ( v3IptOff               );
    VDP_HDR_SetVDmImapIptScale         ( 4902930u                );

    VDP_HDR_SetVDmInColor              ( 1 );//yuv
    VDP_HDR_SetCvmOutColor             ( 1 );//yuv

    v3IptOff[0] = 256;
    v3IptOff[1] = 2048;
    v3IptOff[2] = 2048;

    VDP_HDR_SetVCvmOmapIptoff          ( v3IptOff );
    VDP_HDR_SetVCvmOmapIptScale        ( 3504);

    //downsample
    VDP_HDR_SetDmHdrDsMax              ( 4095 );
    VDP_HDR_SetDmHdrDsMin              ( 0 );

    return HI_SUCCESS;
}
HI_S32 VDP_DRV_SetHisiVdmHlg2Hdr10(HI_VOID)
{
    int32_t v3IptOff[3];
    int16_t csc_coef[3][3] = {{0}, {0}, {0}};
    HI_S32  csc_offset[3] = {0};

    //composer up sample
    VDP_VID_SetComposeElUpsampleMax    (16383);
    VDP_VID_SetComposeElUpsampleMin    (0);

    //vdm_yuv2rgb
    VDP_HDR_SetVDmYuv2rgbEn            ( 1 );
    VDP_HDR_SetVDmYuv2rgbV0En          ( 1 );
    VDP_HDR_SetVDmYuv2rgbV1En          ( 0 );

    csc_coef[0][0] = 8192 ;
    csc_coef[0][1] = 0    ;
    csc_coef[0][2] = 0    ;
    csc_coef[1][0] = 0 ;
    csc_coef[1][1] = 8192    ;
    csc_coef[1][2] = 0    ;
    csc_coef[2][0] = 0 ;
    csc_coef[2][1] = 0    ;
    csc_coef[2][2] = 8192        ;

    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;

    VDP_HDR_SetVDmImap0Yuv2rgb         (csc_coef);
    VDP_HDR_SetVDmImapYuv2rgbscale2p   (13);
    VDP_HDR_SetVDmImapYuv2rgbOutDc0    (csc_offset);

    VDP_HDR_SetVDmInBits               ( 1 );

    //vdm_rgb2lms
    VDP_HDR_SetVDmRgb2lmsEn            ( 1 );

    csc_coef[0][0] = 16384     ;
    csc_coef[0][1] = 0     ;
    csc_coef[0][2] = 0     ;
    csc_coef[1][0] = 0     ;
    csc_coef[1][1] = 16384    ;
    csc_coef[1][2] = 0     ;
    csc_coef[2][0] = 0      ;
    csc_coef[2][1] = 0     ;
    csc_coef[2][2] = 16384    ;

    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;

    VDP_HDR_SetVDmImapRgb2lms          ( csc_coef );
    VDP_HDR_SetVDmImapRgb2lmsscale2p   ( 14);
    VDP_HDR_SetVDmImapRgb2lmsmin       ( 0 );
    //VDP_HDR_SetVDmImapRgb2lmsmax       ( (HI_U32)((HI_U64)10000*(1<<18))  );
    VDP_HDR_SetVDmImapRgb2lmsmax        ( 0x9c400000  );//(10000LL*(1<<18))

    //cvm1_lms2ipt
    VDP_HDR_SetVCvmLms2iptEn           ( 1 );
    VDP_HDR_SetVDmImapLms2iptmin       (-32768);//  ( 0-((1<<15)-1) );
    VDP_HDR_SetVDmImapLms2iptmax      (32767);// ( ((1<<15)-1) );

    csc_coef[0][0] = 4096     ;
    csc_coef[0][1] = 0     ;
    csc_coef[0][2] = 0            ;
    csc_coef[1][0] = 0     ;
    csc_coef[1][1] = 4096   ;
    csc_coef[1][2] = 0     ;
    csc_coef[2][0] = 0        ;
    csc_coef[2][1] = 0   ;
    csc_coef[2][2] = 4096      ;

    csc_offset[0] = 0;
    csc_offset[1] = -16384;
    csc_offset[2] = -16384;

    VDP_HDR_SetVCvmImapLms2ipt         ( csc_coef         );
    VDP_HDR_SetVCvmImapLms2iptscale2p  ( 12 + 1);//从王正拿过来的参数是12，要加1配置
    VDP_HDR_SetVCvmImapLms2iptOutDc(csc_offset);

    //cvm1_ipt2lms
    VDP_HDR_SetVCvmIpt2lmsEn           ( 1 );


#if 0
    csc_coef[0][0] = 8192    ;
    csc_coef[0][1] = 0  ;
    csc_coef[0][2] = 0 ;
    csc_coef[1][0] = 0    ;
    csc_coef[1][1] = 8192 ;
    csc_coef[1][2] = 0    ;
    csc_coef[2][0] = 0    ;
    csc_coef[2][1] = 0 ;
    csc_coef[2][2] = 8192    ;


    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;

#else

    csc_coef[0][0] = 8192    ;
    csc_coef[0][1] = 0  ;
    csc_coef[0][2] = 12080 ;
    csc_coef[1][0] = 8192    ;
    csc_coef[1][1] =  -1348 ;
    csc_coef[1][2] =  -4681    ;
    csc_coef[2][0] = 8192    ;
    csc_coef[2][1] = 15412 ;
    csc_coef[2][2] = 0    ;

    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;

#endif

    VDP_HDR_SetVCvmOmapIpt2lms         ( csc_coef      );

    VDP_HDR_SetVCvmOmapIpt2lmsscale2p  ( 13);
    VDP_HDR_SetVDmOmapIpt2lmsmin       ( 0 );
    VDP_HDR_SetVDmOmapIpt2lmsmax      (65535);// ( (1<<16)-1 );

    //cvm1_lms2rgb
    VDP_HDR_SetVCvmLms2rgbEn           ( 1 );

    csc_coef[0][0] = 16384   ;
    csc_coef[0][1] = 0;
    csc_coef[0][2] = 0 ;
    csc_coef[1][0] = 0   ;
    csc_coef[1][1] = 16384   ;
    csc_coef[1][2] = 0   ;
    csc_coef[2][0] =  0    ;
    csc_coef[2][1] = 0   ;
    csc_coef[2][2] = 16384    ;

    csc_offset[0] = 0;
    csc_offset[1] = 0;
    csc_offset[2] = 0;


    VDP_HDR_SetVCvmOmapLms2rgb         ( csc_coef       );
    VDP_HDR_SetVCvmOmapLms2rgbscale2p  ( 14);
    VDP_HDR_SetVDmOmapLms2rgbmin       ( 0     );
    VDP_HDR_SetVDmOmapLms2rgbmax       ( 2621440000u  );

    //cvm1_rgb2yuv
    VDP_HDR_SetVCvmRgb2yuvEn           ( 1 );

#if 0
    csc_coef[0][0] = 16384 ;
    csc_coef[0][1] = 0    ;
    csc_coef[0][2] = 0 ;
    csc_coef[1][0] = 0    ;
    csc_coef[1][1] = 16384   ;
    csc_coef[1][2] = 0    ;
    csc_coef[2][0] = 0    ;
    csc_coef[2][1] = 0   ;
    csc_coef[2][2] = 16384  ;



    csc_offset[0] = 0;
    csc_offset[1] = 0;//2048;
    csc_offset[2] = 0;//2048;

#else
    csc_coef[0][0] = 4304 ;
    csc_coef[0][1] = 11108    ;
    csc_coef[0][2] = 972 ;
    csc_coef[1][0] = -2288    ;
    csc_coef[1][1] = -5904   ;
    csc_coef[1][2] = 8192    ;
    csc_coef[2][0] = 8192    ;
    csc_coef[2][1] = -7533   ;
    csc_coef[2][2] = -659   ;

    csc_offset[0] = 0;
    csc_offset[1] = 2048;//2048;
    csc_offset[2] = 2048;//2048;

#endif

    VDP_HDR_SetVCvmOmapRgb2yuv         ( csc_coef      );
    VDP_HDR_SetVCvmOmapRgb2yuvscale2p  ( 14);
    VDP_HDR_SetVCvmOmapRgb2yuvOutDc    ( csc_offset     );

    //VDM_PQ2L

    VDP_HDR_SetVDmInEotf               ( 1 );
    VDP_HDR_SetVDmDegammaEn            ( 1 );
    VDP_HDR_SetVCvmEn                  ( 1 );
    VDP_HDR_SetVCvmDegammaEn           ( 1 );
    VDP_HDR_SetVCvmMGammaEn            ( 1 );
    VDP_HDR_SetVDmGammaEn              ( 1 );
    VDP_HDR_SetVDmNormEn               ( 1 );
    VDP_HDR_SetVDmImapRangeMin         ( 0 );
    VDP_HDR_SetVDmImapRange            ( 16383);
    VDP_HDR_SetVDmImapRangeInv         ( 65540     );
    VDP_HDR_SetVCvmOmapRangeMin        ( 0     );
    VDP_HDR_SetVCvmOmapRangeOver       ( 0x0000fff0 );

    VDP_HDR_SetCvmOutBits              ( 2 );//12bit
    VDP_HDR_SetVCvmDenormEn            ( 1 );

    v3IptOff[0] = 64;
    v3IptOff[1] = 512;
    v3IptOff[2] = 512;

    VDP_HDR_SetVDmImapIptoff           ( v3IptOff               );
    VDP_HDR_SetVDmImapIptScale         ( 4902930u                );

    VDP_HDR_SetVDmInColor              ( 1 );//yuv
    VDP_HDR_SetCvmOutColor             ( 1 );//yuv

    v3IptOff[0] = 256;
    v3IptOff[1] = 2048;
    v3IptOff[2] = 2048;

    VDP_HDR_SetVCvmOmapIptoff          ( v3IptOff );
    VDP_HDR_SetVCvmOmapIptScale        ( 3504);

    //downsample
    VDP_HDR_SetDmHdrDsMax              ( 4095 );
    VDP_HDR_SetDmHdrDsMin              ( 0 );

    return HI_SUCCESS;
}

