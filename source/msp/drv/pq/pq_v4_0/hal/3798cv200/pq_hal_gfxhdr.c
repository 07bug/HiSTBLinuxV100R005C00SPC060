/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_hal_gfxhdr.c
  Version       : Initial Draft
  Author        : sdk
                      sdk
  Created      : 2018/01/29
  Description  :

******************************************************************************/
#include <linux/string.h>

#include "hi_type.h"
#include "hi_math.h"

#include "pq_hal_comm.h"
#include "drv_pq_ext.h"
#include "pq_hal_gfxhdr.h"

extern HI_S32 PQ_GFX_SIN_TABLE[PQ_GFX_TABLE_MAX];
extern HI_U32 PQ_GFX_COS_TABLE[PQ_GFX_TABLE_MAX];

static HI_PQ_HDR_MODE_E     sg_enGfxHdrMode    = HI_PQ_HDR_MODE_SDR_TO_HDR10;
static PQ_GFXHDR_TM_COEF_S  sg_stGfxHdrTmClutBinOrCode;
static PQ_PARAM_S           *sg_pstGfxHdrBinPara  = HI_NULL;

static HI_U32   g_au32TmapCoefTmp[PQ_GFXHDR_TM_CLUT_SIZE] = {0};

//u32ParaModeUse : 选择HDR参数模式。0:固定参数，1:工具调试参数
static HI_PQ_GFXHDR_MODE_S sg_stToolGfxHdrMode = {0};
static HI_PQ_GFXHDR_TMAP_S sg_stToolGfxHdrTmap = {{0}};
static HI_PQ_GFXHDR_STEP_S sg_stToolGfxHdrStep = {{0}};

HI_S16 g_aDstGfxHdrCSCTable[3][3];
HI_S16 g_as16DcGfxHdrOutR2Y[3] = { 64,  512,  512 };

HI_S16 g_aDstGfxHdrOffsetCSCTable[HI_PQ_HDR_MODE_BUTT][3][3];
HI_S16 g_as16GfxHdrOffsetDcOutR2Y[HI_PQ_HDR_MODE_BUTT][3] =
{
    { 64,  512,  512 },
    { 64,  512,  512 },
    { 64,  512,  512 },

    { 64,  512,  512 },
    { 64,  512,  512 },
    { 64,  512,  512 },

    { 64,  512,  512 },
    { 64,  512,  512 },
    { 64,  512,  512 },

    { 64,  512,  512 },
    { 64,  512,  512 },
    { 64,  512,  512 }
};

/* ---------------------------------------------- */

/************* DeGamma Params **************/
static const HI_U32 au32GfxHdrDeGmm_step[PQ_GFXHDR_DEGMM_SEG_SIZE] =
{
    4, 4, 4, 5
};

static const HI_U32 au32GfxHdrDeGmm_pos[PQ_GFXHDR_DEGMM_SEG_SIZE]  =
{
    672, 832, 992, 1023
};

static const HI_U32 au32GfxHdrDeGmm_num[PQ_GFXHDR_DEGMM_SEG_SIZE]  =
{
    42, 10, 10, 1
};

/* ------------------ToneMapping---------------------------- */
/*static const HI_U16 u16GfxHdrScaleLumaCal       = 14;                */
static const HI_U16 au16GfxHdrM3LumaCal_2020[3] = {1076, 2777, 243};
static const HI_U16 au16GfxHdrM3LumaCal_709[3]  = {1076, 2777, 243};
static const HI_U16 au16GfxHdrM3LumaCal_601[3]  = {1076, 2777, 243};

static const HI_U16 u16GfxHdrScaleCoefTM       = 8;
static const HI_U32 u32GfxHdrClipMinTM         = 0;
static const HI_U32 u32GfxHdrClipMaxTM         = 65535;

/* ------------------GamutMapping---------------------------- */
/* GamutMapping Params: 20bit in, 20bit out  */
static const HI_U16 u16GfxHdrScaleGMap   = 14;
static const HI_U32 u32GfxHdrClipMinGMap = 0;
static const HI_U32 u32GfxHdrClipMaxGMap = 65535;

static const HI_S16 as16GfxHdrM33GMap_709to2020[3][3] =
{
    {10279 ,       5396  ,       710},
    {1134  ,     15064   ,      187 },
    {268   ,     1442    ,   14673  }
};

static const HI_S16 as16GfxHdrM33GMap_linear[3][3] =                  /*  S1.14 [-2^15, 2^15-1] = [-32768, 32767] */
{
    /* Linear */
    { 16384,       0  ,       0 },
    {     0,     16384,       0 },
    {     0,       0  ,   16384 }
};

static const HI_S16 as16GfxHdrM33GMAP_Pal_601_709[3][3] =
{
    //BT601 to BT709
    {17106  ,      -724      ,    -1 },
    { -2   ,    16386    ,       0 },
    { 1    ,    193     ,  16191  }
};

static const HI_S16 as16GfxHdrM33GMAP_Ntsc_601_709[3][3] =
{
    //BT601ntsc to BT709
    { 15394  ,       820     ,    167 },
    {  290   ,    15826    ,     269},
    {  -26   ,      -72   ,    16483  }
};

static const HI_S16 as16GfxHdrM33GMAP_Pal_601_2020[3][3] =
{
    //BT601 to BT2020
    { 10731 ,       4951   ,      701 },
    { 1182  ,     15018   ,      184 },
    {  280   ,     1603   ,   14500  }
};

static const HI_S16 as16GfxHdrM33GMAP_Ntsc_601_2020[3][3] =
{
    //BT601ntsc to BT2020
    {  9752    ,    5723   ,      908 },
    { 1331    ,   14606    ,     447 },
    {  254    ,    1342    ,   14788  }
};

static const HI_U32 au32GfxHdrTMapStep[PQ_GFXHDR_TMAP_SEG_SIZE] =        /* U5.0  [0,20] */
{
    9, 10, 12, 13
};

static const HI_U32 au32GfxHdrTMapNum[PQ_GFXHDR_TMAP_SEG_SIZE]  =        /* U6.0  [0,63] */
{
    16, 8, 2, 5
};

static const HI_U32 au32GfxHdrTMapPos[PQ_GFXHDR_TMAP_SEG_SIZE]  =        /* U20.0 [0,1048575] */
{
    8192, 16384, 24576, 65535
};

/* ToneMapping Lut: SDR to HDR10 */
static const HI_U16 u16GfxHdrScaleCoefTM_SDR2HDR1000 = 15;         /* U4.0  [0,15] */
static const HI_U32 au32GfxHdrTMLut_SDR2HDR1000[PQ_GFXHDR_TMAP_LUT_SIZE] =                   //U1.15 [0,65535]
{
    0,    6121, 5994,  5929,  5910,  5896,  5905,  5916,
    5929, 5962, 5975,  6003,  6034,  6065,  6111,  6141,
    6189, 6259, 6337,  6425,  6526,  6620,  6711,  6799,
    6917, 7349, 7831,  8915,  10252, 11871, 13877, 16384,
};

// ToneMapping Lut:  SDR to HLG
static const HI_U16 u16GfxHdrScaleCoefTM_SDR2HLG = 12 ;
static const HI_U32 au32GfxHdrTMLut_SDR2HLG[PQ_GFXHDR_TMAP_LUT_SIZE] =                    //U9.7 [0,65535]
{
    256,    256,    256,    256,    256,    256,    256,    256,
    256,    256,    256,    256,    256,    256,    256,    256,
    256,    256,    256,    256,    256,    256,    256,    256,
    256,    256,    256,    256,    256,    256,    256,    256
};

/******************* Gmm-8 Lut Params *************************/
static const HI_U32 au32GfxHdrGmmStep[PQ_GFXHDR_GMM_SEG_SIZE] =        /* U5.0  [0,31] */
{
    0, 2, 4, 5, 6, 8, 10, 12
};

static const HI_U32 au32GfxHdrGmmPos[PQ_GFXHDR_GMM_SEG_SIZE]  =        /* U20.0 [0,1048575] */
{
    4, 32, 64, 192, 512, 4096, 20480, 65535
};

static const HI_U32 au32GfxHdrGmmNum[PQ_GFXHDR_GMM_SEG_SIZE]  =        /* U6.0  [0,63] */
{
    4, 11, 13, 17, 22, 36, 52, 63
};

// PQ Curve

static const HI_U32 au32GfxHdrGmmLut_PQ1600[PQ_GFXHDR_GMM_LUT_SIZE] =              //U12.0 [0,4095]
{
    0   ,    77  ,    108 ,    132 ,    151 ,    206 ,    246 ,    278 ,
    304 ,    327 ,    348 ,    367 ,    429 ,    477 ,    551 ,    609 ,
    657 ,    697 ,    765 ,    820 ,    867 ,    908 ,    945 ,    1061,
    1149,    1220,    1279,    1331,    1376,    1417,    1454,    1487,
    1519,    1548,    1575,    1600,    1624,    1708,    1778,    1838,
    1891,    1938,    1980,    2019,    2054,    2087,    2118,    2146,
    2173,    2198,    2222,    2245,    2267,    2344,    2410,    2467,
    2518,    2564,    2606,    2644,    2679,    2712,    2742,    2771
};

static const HI_U32 au32GfxHdrGmmLut_PQ1500[PQ_GFXHDR_GMM_LUT_SIZE] =              //U12.0 [0,4095]
{
    0,   132,   181,   217,   246,   327,   384,   429,
    466,   498,   526,   551,   634,   697,   794,   867,
    927,   978,  1061,  1129,  1186,  1235,  1279,  1417,
    1519,  1600,  1668,  1727,  1778,  1824,  1865,  1903,
    1938,  1970,  2000,  2028,  2054,  2146,  2222,  2287,
    2344,  2394,  2440,  2481,  2518,  2553,  2586,  2616,
    2644,  2671,  2696,  2720,  2742,  2823,  2891,  2950,
    3003,  3050,  3092,  3131,  3167,  3200,  3231,  3260,
};

static HI_U32 g_au32GfxHdrTmBasicLut[256] =     // U24 (20b in, 24b out)
{
    85,      85,      85,      85,      85,      85,      85,      85,
    85,      85,      85,      85,      88,      95,     104,     119,
    141,     221,     287,     349,     410,     468,     527,     584,
    638,     697,     757,     815,     869,     920,     971,    1026,
    1083,    1136,    1186,    1239,    1296,    1353,    1407,    1458,
    1509,    1560,    1612,    1663,    1715,    1922,    2128,    2336,
    2543,    2751,    2959,    3169,    3361,    3768,    4164,    4572,
    4958,    5353,    5761,    6142,    6517,    6934,    7309,    7683,
    8101,    8482,    8853,    9253,    9662,   10410,   11161,   11907,
    12721,   13477,   14228,   14979,   15729,   16479,   17229,   17979,
    18729,   19478,   20228,   20977,   21727,   22476,   23226,   23975,
    24725,   27725,   30727,   33731,   36591,   39591,   42595,   45602,
    48613,   51462,   54441,   57453,   60469,   63488,   66528,   69298,
    72308,   75332,   78359,   81389,   84423,   87460,   90500,   93543,
    96589,   99638,   102691,  105746,  108804,  111865,  114929,  117996,
    121065,  124137,  127212,  130290,  133371,  136454,  139539,  142627,
    145687,  148940,  152394,  155502,  158601,  161712,  164826,  167911,
    171123,  174648,  177885,  180984,  184120,  187238,  190383,  193862,
    197309,  210163,  223199,  236648,  250175,  263813,  277903,  291445,
    306069,  319666,  334398,  348533,  362968,  377848,  392807,  407843,
    422873,  439248,  454631,  469943,  486154,  502314,  517800,  534934,
    550767,  568132,  584137,  601832,  619570,  637238,  653532,  671587,
    689681,  707875,  726167,  744421,  763975,  783788,  802343,  821146,
    841860,  861235,  881102,  901997,  921164,  942060,  963515,  984987,
    1006587, 1028314, 1050166, 1072143, 1094244, 1116467, 1138811, 1161277,
    1183826, 1206384, 1230502, 1255618, 1280914, 1305136, 1328256, 1353208,
    1379069, 1483144, 1589427, 1705480, 1821074, 1944581, 2072822, 2206172,
    2348807, 2494317, 2650839, 2809902, 2977802, 3157838, 3337980, 3532184,
    3732155, 3949307, 4172173, 4402177, 4651658, 4908006, 5171077, 5455412,
    5751030, 6070628, 6399038, 6744628, 7111678, 7499749, 7910258, 8332163,
    8778848, 9262486, 9771750, 10307621, 10877046, 11469037, 12113218, 12877825,
    13620506, 14388091, 15209051, 16139633, 16777216, 16777216, 16777216, 16777216,
};

//HLG Curve
static const HI_U32 au32GfxHdrGmmLut_HLG[PQ_GFXHDR_GMM_LUT_SIZE] =              //U12.0 [0,4095]
{
    0   ,    28  ,    39  ,    48  ,    55  ,    78  ,    96  ,    111 ,
    124 ,    136 ,    147 ,    157 ,    192 ,    222 ,    271 ,    313 ,
    350 ,    384 ,    443 ,    496 ,    543 ,    586 ,    627 ,    768 ,
    887 ,    991 ,    1086,    1173,    1254,    1330,    1402,    1470,
    1536,    1598,    1659,    1717,    1773,    1982,    2165,    2313,
    2436,    2541,    2633,    2714,    2788,    2854,    2916,    2972,
    3024,    3073,    3119,    3162,    3203,    3346,    3466,    3569,
    3660,    3740,    3812,    3878,    3939,    3995,    4047,    4095
};

// Gamma Curve
static const HI_U32 au32GfxHdrGmmLut_22[PQ_GFXHDR_GMM_LUT_SIZE] =              //U12.0 [0,4095]
{
    0 ,        26 ,        36 ,        44 ,        50 ,        68 ,        82 ,        93 ,       103 ,       112 ,       120 ,       128 ,       154 ,       175 ,       211 ,       240 ,
    266 ,       289 ,       329 ,       364 ,       396 ,       425 ,       451 ,       543 ,       618 ,       684 ,       744 ,       798 ,       847 ,       894 ,       938 ,       979 ,
    1019 ,      1057 ,      1093 ,      1128 ,      1161 ,      1285 ,      1396 ,      1498 ,      1591 ,      1679 ,      1761 ,      1839 ,      1913 ,      1984 ,      2052 ,      2118 ,
    2181 ,      2242 ,      2301 ,      2358 ,      2413 ,      2622 ,      2812 ,      2988 ,      3153 ,      3307 ,      3454 ,      3593 ,      3726 ,      3854 ,      3977 ,      4095
};

static const HI_U32 au32GfxHdrGmmLut_bt709[PQ_GFXHDR_GMM_LUT_SIZE] =              //U12.0 [0,4095]
{
    0 ,         0 ,         1 ,         1 ,         1 ,         2 ,         3 ,         4 ,         6 ,         7 ,         8 ,         9 ,        13 ,        18 ,        27 ,        36 ,
    45 ,        54 ,        72 ,        90 ,       108 ,       126 ,       144 ,       216 ,       288 ,       360 ,       426 ,       486 ,       541 ,       592 ,       641 ,       686 ,
    730 ,       772 ,       812 ,       850 ,       887 ,      1024 ,      1146 ,      1257 ,      1360 ,      1456 ,      1547 ,      1632 ,      1713 ,      1791 ,      1866 ,      1937 ,
    2006 ,      2073 ,      2138 ,      2200 ,      2261 ,      2489 ,      2697 ,      2889 ,      3068 ,      3237 ,      3397 ,      3549 ,      3694 ,      3833 ,      3966 ,      4095 ,
};

/* --------------R2Y:RGB2YUV-------------------------------- */

static const HI_U16 u16GfxHdrScaleR2Y        = 14;
static const HI_U16 u16GfxHdrClipMinRF2YL    = 0;
static const HI_U16 u16GfxHdrClipMaxRF2YL    = 1023;
static const HI_U16 u16GfxHdrClipMinRF2YF    = 0;
static const HI_U16 u16GfxHdrClipMaxRF2YF    = 1023;

static const HI_S16 as16GfxHdrDcInRF2YL[3] =                            /* S10.0  [-1024, 1023] */
{
    0,
    0,
    0
};

static const  HI_S16 as16GfxHdrDcInRF2YF[3] =      // S10.0  [-1024, 1023]
{
    0,
    0,
    0
};

static HI_S16 as16GfxHdrM33RF2YL_709[3][3] =      // S1.14 [-32768, 32767]
{
    //BT709
    {2984  ,     10034   ,     1013  },
    { -1643 ,      -5531  ,      7175 },
    {7175  ,     -6518   ,     -659  }
};

static const HI_S16 as16GfxHdrM33RF2YL_2020NCL[3][3] =      // S1.14 [-32768, 32767]
{
    //BT2020
    {3685  ,      9512  ,       832  },
    { -2004 ,      -5171 ,       7175 },
    {7175  ,     -6598  ,      -577  }
};

static const HI_S16 as16GfxHdrM33RF2YL_601[3][3] =      // S1.14 [-32768, 32767]
{
    //BT601
    {4195    ,    8235   ,     1599  },
    { -2421 ,      -4754  ,      7175 },
    {7175   ,    -6004    ,   -1167  }
};

static const HI_S16  as16GfxHdrM33RF2YF_709[3][3] =      // S1.14 [-32768, 32767]
{
    //BT709
    {3483    ,   11718     ,   1183  },
    { -1877  ,     -6315   ,     8192 },
    { 8192   ,    -7441    ,    -751  }
};

static const HI_S16  as16GfxHdrM33RF2YF_2020NCL[3][3] =      // S1.14 [-32768, 32767]
{
    //BT2020
    { 4304   ,    11108    ,     972  },
    { -2288   ,    -5904   ,     8192 },
    {8192     ,  -7533     ,   -659  }
};

static const HI_S16 as16GfxHdrM33RF2YF_601[3][3] =      // S1.14 [-32768, 32767]
{
    //BT601
    {4899    ,    9617     ,   1868 },
    { -2765   ,    -5427    ,    8192 },
    { 8192   ,    -6855    ,   -1332 }
};

static const HI_S16 as16GfxHdrDcOutRF2YL[3]  =       /* s10.0  [-1024,1023] */
{
    64,
    512,
    512
};

static const HI_S16 as16GfxHdrDcOutRF2YF[3] =
{
    0,
    512,
    512
};  // s10.0  [-1024,1023]

/* ------------------R2Y:RGB2RGB---------------------------- */
static const HI_U16  u16GfxHdrScaleRF2RF   = 14;   // U4.0  [0,15]
static const HI_U16  u16GfxHdrClipMinRF2RF = 0;    // U10.0  [0,1023]
static const HI_U16  u16GfxHdrClipMaxRF2RF = 1023; // U10.0  [0,1023]

static const HI_S16   as16GfxHdrDcInRF2RF[3] =      // S10.0  [-1024, 1023]
{
    0,
    0,
    0
};

static const HI_S16   as16GfxHdrM33RF2RF[3][3] =      // S1.14 [-32768, 32767]
{
    {16384    ,   0     ,   0  },
    { 0  ,     16384   ,     0 },
    { 0   ,    0    ,    16384  }
};

static const HI_S16   as16GfxHdrDcOutRF2RF[3] =
{
    0,
    0,
    0
};  // s10.0  [-1024,1023]

static HI_U32 g_u32GfxHdrBright   = 128;
static HI_U32 g_u32GfxHdrContrast = 128;
static HI_U32 g_u32GfxHdrSatu     = 128;
static HI_U32 g_u32GfxHdrHue      = 128;

static HI_U32 g_u32GfxHdrRed      = 128;
static HI_U32 g_u32GfxHdrGreen    = 128;
static HI_U32 g_u32GfxHdrBlue     = 128;

static HI_U32 g_u32GfxHdrOffsetBright[HI_PQ_HDR_MODE_BUTT]   =
{
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
};

static HI_U32 g_u32GfxHdrOffsetContrast[HI_PQ_HDR_MODE_BUTT] =
{
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
};

static HI_U32 g_u32GfxHdrOffsetSatu[HI_PQ_HDR_MODE_BUTT]     =
{
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
};

static HI_U32 g_u32GfxHdrOffsetHue[HI_PQ_HDR_MODE_BUTT]      =
{
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
};

static HI_U32 g_u32GfxHdrOffsetRed[HI_PQ_HDR_MODE_BUTT]      =
{
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
};

static HI_U32 g_u32GfxHdrOffsetGreen[HI_PQ_HDR_MODE_BUTT]    =
{
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
};

static HI_U32 g_u32GfxHdrOffsetBlue[HI_PQ_HDR_MODE_BUTT]     =
{
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
    128,    128,    128,
};

static HI_U32 g_u32GfxDarkCvStr[HI_PQ_HDR_MODE_BUTT]    =
{
    50,    50,    50,
    50,    50,    50,
    50,    50,    50,
    50,    50,    50,
};

static HI_U32 g_u32GfxBrightCvStr[HI_PQ_HDR_MODE_BUTT]  =
{
    50,    50,    50,
    50,    50,    50,
    50,    50,    50,
    50,    50,    50,
};

HI_S32 PQ_HAL_SetGfxHdrCscSetting(HI_PQ_PICTURE_SETTING_S *pstPicSetting)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPicSetting);

    /* gfx csc use 0 -100 , convert to 0 - 255 to sdr2hdr*/
    g_u32GfxHdrBright   = LEVEL2NUM(pstPicSetting->u16Brightness);
    g_u32GfxHdrContrast = LEVEL2NUM(pstPicSetting->u16Contrast);
    g_u32GfxHdrSatu     = LEVEL2NUM(pstPicSetting->u16Hue);
    g_u32GfxHdrHue      = LEVEL2NUM(pstPicSetting->u16Saturation);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetGfxHdrOffset(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrOffsetPara);

    g_u32GfxHdrOffsetBright[pstHdrOffsetPara->enHdrProcessScene]   = pstHdrOffsetPara->u32Bright;
    g_u32GfxHdrOffsetContrast[pstHdrOffsetPara->enHdrProcessScene] = pstHdrOffsetPara->u32Contrast;
    g_u32GfxHdrOffsetSatu[pstHdrOffsetPara->enHdrProcessScene]     = pstHdrOffsetPara->u32Satu;
    g_u32GfxHdrOffsetHue[pstHdrOffsetPara->enHdrProcessScene]      = pstHdrOffsetPara->u32Hue;
    g_u32GfxHdrOffsetRed[pstHdrOffsetPara->enHdrProcessScene]      = pstHdrOffsetPara->u32R;
    g_u32GfxHdrOffsetGreen[pstHdrOffsetPara->enHdrProcessScene]    = pstHdrOffsetPara->u32G;
    g_u32GfxHdrOffsetBlue[pstHdrOffsetPara->enHdrProcessScene]     = pstHdrOffsetPara->u32B;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetGfxHDRTMCurve(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrOffsetPara);

    g_u32GfxDarkCvStr[pstHdrOffsetPara->enHdrProcessScene]      = pstHdrOffsetPara->u32darkCv;
    g_u32GfxBrightCvStr[pstHdrOffsetPara->enHdrProcessScene]    = pstHdrOffsetPara->u32brightCv;

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_SetGfxHdrModeByTool(HI_PQ_GFXHDR_MODE_S *pstMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstMode);

    sg_stToolGfxHdrMode.u32HdrScene    = pstMode->u32HdrScene;
    sg_stToolGfxHdrMode.u32ParaModeUse = pstMode->u32ParaModeUse;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetGfxHdrModeByTool(HI_PQ_GFXHDR_MODE_S *pstMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstMode);

    pstMode->u32HdrScene    = sg_stToolGfxHdrMode.u32HdrScene;
    pstMode->u32ParaModeUse = sg_stToolGfxHdrMode.u32ParaModeUse;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetGfxHdrTmapByTool(HI_PQ_GFXHDR_TMAP_S *pstTmap)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTmap);

    PQ_SAFE_MEMCPY(&sg_stToolGfxHdrTmap, pstTmap, sizeof(sg_stToolGfxHdrTmap));

    if (HI_PQ_HDR_MODE_SDR_TO_HDR10 == sg_enGfxHdrMode)
    {
        PQ_SAFE_MEMCPY(sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HDRClut, sg_stToolGfxHdrTmap.au32Clut, sizeof(sg_stToolGfxHdrTmap.au32Clut));
    }
    else if (HI_PQ_HDR_MODE_SDR_TO_HLG == sg_enGfxHdrMode)
    {
        PQ_SAFE_MEMCPY(sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HLGClut, sg_stToolGfxHdrTmap.au32Clut, sizeof(sg_stToolGfxHdrTmap.au32Clut));
    }

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetGfxHdrTmapByTool(HI_PQ_GFXHDR_TMAP_S *pstTmap)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTmap);

    PQ_SAFE_MEMCPY(pstTmap, &sg_stToolGfxHdrTmap, sizeof(sg_stToolGfxHdrTmap));

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetGfxHdrStepByTool(HI_PQ_GFXHDR_STEP_S *pstStep)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstStep);

    PQ_SAFE_MEMCPY(sg_stToolGfxHdrStep.au32X_step, pstStep->au32X_step, sizeof(sg_stToolGfxHdrStep.au32X_step));
    PQ_SAFE_MEMCPY(sg_stToolGfxHdrStep.au32X_num,  pstStep->au32X_num,  sizeof(sg_stToolGfxHdrStep.au32X_num));
    PQ_SAFE_MEMCPY(sg_stToolGfxHdrStep.au32X_pos,  pstStep->au32X_pos,  sizeof(sg_stToolGfxHdrStep.au32X_pos));

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetGfxHdrStepByTool(HI_PQ_GFXHDR_STEP_S *pstStep)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstStep);

    PQ_SAFE_MEMCPY(pstStep->au32X_step, sg_stToolGfxHdrStep.au32X_step,  sizeof(sg_stToolGfxHdrStep.au32X_step));
    PQ_SAFE_MEMCPY(pstStep->au32X_num,  sg_stToolGfxHdrStep.au32X_num,   sizeof(sg_stToolGfxHdrStep.au32X_num));
    PQ_SAFE_MEMCPY(pstStep->au32X_pos,  sg_stToolGfxHdrStep.au32X_pos,   sizeof(sg_stToolGfxHdrStep.au32X_pos));

    return HI_SUCCESS;
}

static HI_U32 HiGfxHdr_LutCal(HI_U32 *lut, HI_U32 u32Base, HI_U32 u32Step, HI_U32 u32IndexBase, HI_U32 u32InMax, HI_U32 u32InData)
{
    HI_U32 u32IndexOff, u32Index;
    HI_U32 u32y0, u32y1, u32y;

    u32IndexOff = (u32InData - u32Base) >> u32Step;
    u32Index = u32IndexOff + u32IndexBase;

    PQ_CHECK_OVER_RANGE_RE_FAIL(u32Index + 1, 256);

    u32y0 = lut[u32Index];
    u32y1 = lut[u32Index + 1];
    if (u32InData <= u32InMax)
    {
        u32y = (HI_U32)((((HI_S64)u32y1 - (HI_S64)u32y0) * ((HI_S64)u32InData - (HI_S64)(u32IndexOff * (1 << u32Step) + u32Base)) >> u32Step) + u32y0);
    }
    else
    {
        u32y = u32y0;
    }

    return u32y;
}


static HI_U32 HiGfxHdr_TF_8(HI_U32 u32InData, PQ_GFXHDR_TF_PARA *pGmmPara)
{
    HI_U32 u32Base, u32Step, u32IndexBase;

    if (u32InData <= pGmmPara->x_pos[0])
    {
        u32Base = 0;
        u32Step = pGmmPara->x_step[0];
        u32IndexBase = 0;
    }
    else if (u32InData <= pGmmPara->x_pos[1])
    {
        u32Base = pGmmPara->x_pos[0];
        u32Step = pGmmPara->x_step[1];
        u32IndexBase = pGmmPara->x_num[0];
    }
    else if (u32InData <= pGmmPara->x_pos[2])
    {
        u32Base = pGmmPara->x_pos[1];
        u32Step = pGmmPara->x_step[2];
        u32IndexBase = pGmmPara->x_num[1];
    }
    else if (u32InData <= pGmmPara->x_pos[3])
    {
        u32Base = pGmmPara->x_pos[2];
        u32Step = pGmmPara->x_step[3];
        u32IndexBase = pGmmPara->x_num[2];
    }
    else if (u32InData <= pGmmPara->x_pos[4])
    {
        u32Base = pGmmPara->x_pos[3];
        u32Step = pGmmPara->x_step[4];
        u32IndexBase = pGmmPara->x_num[3];
    }
    else if (u32InData <= pGmmPara->x_pos[5])
    {
        u32Base = pGmmPara->x_pos[4];
        u32Step = pGmmPara->x_step[5];
        u32IndexBase = pGmmPara->x_num[4];
    }
    else if (u32InData <= pGmmPara->x_pos[6])
    {
        u32Base = pGmmPara->x_pos[5];
        u32Step = pGmmPara->x_step[6];
        u32IndexBase = pGmmPara->x_num[5];
    }
    else
    {
        u32Base = pGmmPara->x_pos[6];
        u32Step = pGmmPara->x_step[7];
        u32IndexBase = pGmmPara->x_num[6];
    }
    return HiGfxHdr_LutCal(pGmmPara->lut, u32Base, u32Step, u32IndexBase, pGmmPara->x_pos[7], u32InData);
}

static HI_S32 pq_hal_GfxHdrAdjustBasicTMCore(PQ_GFXHDR_TF_PARA *pstTMParaBasic, PQ_GFXHDR_TF_PARA *pstTMPara,
        HI_U16 u16ScaleCoefTM, HI_S32 u32Ratio, HI_S32 u32PeakLuminance, HI_U32 *pu32OutputLut)
{
    HI_U32 i = 0, k = 0;
    static HI_S32 as32OriginalLutPos[PQ_GFXHDR_TMAP_SEG_SIZE * 8] = { 0 };
    static HI_S32 as32NewLut[PQ_GFXHDR_TMAP_SEG_SIZE * 8] = { 0 };
    HI_U32 u32TmpNum = 0;
    HI_S32 s32TmpPos = 0;
    HI_U16 u16RatioScale = 9;
    HI_U16 u16BitDepthLUTIn = 20;
    HI_U16 u16BitDepthData = 16;    // data bit depth in video is 20b, in graphic is 16b
    HI_S32 as32NewLutMax;
    HI_S32 s32Input;
    HI_S64 s64Tmp;
    HI_U32 u32ScaleTMFactor = (1 << u16ScaleCoefTM) - 1;
    HI_U32 u32halfScaleRatio = (1 << (u16RatioScale - 1));
    HI_U32 u32LutSZ = PQ_GFXHDR_TMAP_SEG_SIZE * 8;

    u32Ratio = 205 + 307 * u32Ratio / 100;  // normalize from [0, 100] to [205, 512](40% ~ 100%)
    u32Ratio = GFXHDR_CLIP3(0, 512, u32Ratio);
    u32PeakLuminance = 500 + u32PeakLuminance * 10; // normalize from [0, 100] to [500, 1500]
    u32PeakLuminance = GFXHDR_CLIP3(500, PQ_GFXHDR_MAX_LUMINANCE, u32PeakLuminance);

    // in graphic layer, the x_num is not accumulative sum
    for (i = 1; i < PQ_GFXHDR_TMAP_SEG_SIZE; ++i)
    {
        pstTMPara->x_num[i] = pstTMPara->x_num[i - 1] + pstTMPara->x_num[i];
    }

    // get origin lut pos
    as32OriginalLutPos[0] = 1;
    for (i = 1; i < u32LutSZ - 1; ++i)
    {
        u32TmpNum = i;
        if (u32TmpNum <= pstTMPara->x_num[0])
        {
            s32TmpPos = (1 << pstTMPara->x_step[0]) * u32TmpNum + 1;
        }
        else
        {
            for (k = 1; k < PQ_GFXHDR_TMAP_SEG_SIZE; ++k)
            {
                if (u32TmpNum <= pstTMPara->x_num[k])
                {
                    s32TmpPos = pstTMPara->x_pos[k - 1] + (1 << pstTMPara->x_step[k]) * (u32TmpNum - pstTMPara->x_num[k - 1]) + 1;
                    break;
                }
            }
        }
        as32OriginalLutPos[i] = s32TmpPos;
    }

    // match bitdepth of LUT pos
    for (i = 0; i < u32LutSZ; ++i)
    {
        as32OriginalLutPos[i] = as32OriginalLutPos[i] << (u16BitDepthLUTIn - u16BitDepthData);
    }
    as32OriginalLutPos[u32LutSZ - 1] = (1 << u16BitDepthLUTIn) - 1;

    // normalise pos
    as32NewLutMax = HiGfxHdr_TF_8((as32OriginalLutPos[u32LutSZ - 1] * u32Ratio + (1 << (u16RatioScale - 1))) >> u16RatioScale, pstTMParaBasic);
    PQ_CHECK_ZERO_RE_FAIL(as32NewLutMax);

    for (i = 0; i < u32LutSZ; ++i)
    {
        s32Input = ((as32OriginalLutPos[i] * u32Ratio + u32halfScaleRatio) >> u16RatioScale);

        s64Tmp = HiGfxHdr_TF_8(s32Input, pstTMParaBasic);
        s64Tmp = (s64Tmp * as32OriginalLutPos[u32LutSZ - 1] * u32Ratio + (1 << (u16RatioScale - 1))) >> u16RatioScale;
        if (s32Input <= 0)
        {
            s32Input = 1;
        }

        //s64Tmp = s64Tmp / s32Input * ((HI_U64)u32ScaleTMFactor) / as32NewLutMax;    // 64位除法！ s64Tmp = div64_s64(div64_s64(s64Tmp, s32Input) * (HI_U64)u32ScaleTMFactor, as32NewLutMax);
        s64Tmp = div64_s64(div64_s64(s64Tmp, s32Input) * ((HI_U64)u32ScaleTMFactor) , as32NewLutMax);  // 64位除法！ s64Tmp = div64_s64(div64_s64(s64Tmp, s32Input) * (HI_U64)u32ScaleTMFactor, as32NewLutMax);
        //as32NewLut[i] = (HI_S32)(s64Tmp * u32PeakLuminance / PQ_GFXHDR_MAX_LUMINANCE);  // 64位除法！       as32NewLut[i] = (HI_S32)div64_s64(s64Tmp * u32PeakLuminance, PQ_MAX_LUMINANCE);
        as32NewLut[i] = (HI_S32)div64_s64(s64Tmp * u32PeakLuminance, PQ_GFXHDR_MAX_LUMINANCE);  // 64位除法！       as32NewLut[i] = (HI_S32)div64_s64(s64Tmp * u32PeakLuminance, PQ_MAX_LUMINANCE);
    }
    as32NewLut[0] = 0;

    for (i = 0; i < u32LutSZ; ++i)
    {
        as32NewLut[i] = GFXHDR_CLIP3(0, u32ScaleTMFactor, as32NewLut[i]);
    }

    memcpy(pu32OutputLut, as32NewLut, sizeof(as32NewLut));

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GfxHdrAdjustBasicTM(const HI_U32 *pu32Step, const HI_U32 *pu32Num, const HI_U32 *pu32Pos,
        HI_U16 u16ScaleCoefTM, HI_S32 u32Ratio, HI_S32 u32PeakLuminance, HI_U32 *pu32OutputLut)
{
    PQ_GFXHDR_TF_PARA gs_stTMParaBasic;
    PQ_GFXHDR_TF_PARA gs_stTMPara;
    static HI_U32 u32TMLutXStepTmp[PQ_GFXHDR_TMAP_SEG_SIZE] = { 0 };
    static HI_U32 u32TMLutXNumTmp[PQ_GFXHDR_TMAP_SEG_SIZE]  = { 0 };
    static HI_U32 u32TMLutXPosTmp[PQ_GFXHDR_TMAP_SEG_SIZE]  = { 0 };
    static HI_U32 u32TMLutBasicXStep[8] = { 2, 4, 6, 7, 8, 10, 12, 14 };
    static HI_U32 u32TMLutBasicXNum[8] = { 16, 44, 52, 68, 88, 144, 208, 252 };
    static HI_U32 u32TMLutBasicXPos[8] = { 64, 512, 1024, 3072, 8192, 65536, 327680, 1048575 };

    memcpy(u32TMLutXStepTmp, pu32Step, sizeof(u32TMLutXStepTmp));
    memcpy(u32TMLutXNumTmp,  pu32Num,  sizeof(u32TMLutXNumTmp));
    memcpy(u32TMLutXPosTmp,  pu32Pos,  sizeof(u32TMLutXPosTmp));

    gs_stTMParaBasic.x_step = u32TMLutBasicXStep;
    gs_stTMParaBasic.x_num  = u32TMLutBasicXNum;
    gs_stTMParaBasic.x_pos  = u32TMLutBasicXPos;
    gs_stTMParaBasic.lut    = g_au32GfxHdrTmBasicLut;

    gs_stTMPara.x_step = u32TMLutXStepTmp;
    gs_stTMPara.x_num  = u32TMLutXNumTmp;
    gs_stTMPara.x_pos  = u32TMLutXPosTmp;

    pq_hal_GfxHdrAdjustBasicTMCore(&gs_stTMParaBasic, &gs_stTMPara, u16ScaleCoefTM, u32Ratio, u32PeakLuminance, pu32OutputLut);

    return HI_SUCCESS;
}


static HI_VOID PQ_hal_CalGfxHdrCSCCoefRGBtoYCbCr(HI_U32 Contrast, HI_U32 Saturation, HI_U32 Hue,
        HI_U32 Kr, HI_U32 Kg, HI_U32 Kb, HI_S16 pCSCTable[3][3], HI_S16 pDstCSCTable[3][3])
{
    HI_S32 ContrastAdjust;
    HI_S32 SaturationAdjust;
    HI_S32 rGain, gGain, bGain;

    ContrastAdjust   = Contrast   * 40 / 51;
    SaturationAdjust = Saturation * 40 / 51;
    Hue   = Hue * 60 / 255;
    rGain = Kr  * 40 / 51;
    gGain = Kg  * 40 / 51;
    bGain = Kb  * 40 / 51;

    g_aDstGfxHdrCSCTable[0][0] = (HI_S16)((HI_S32)pCSCTable[0][0] * ContrastAdjust * rGain  / 10000);
    g_aDstGfxHdrCSCTable[0][1] = (HI_S16)((HI_S32)pCSCTable[0][1] * ContrastAdjust * gGain  / 10000);
    g_aDstGfxHdrCSCTable[0][2] = (HI_S16)((HI_S32)pCSCTable[0][2] * ContrastAdjust * bGain  / 10000);
    g_aDstGfxHdrCSCTable[1][0]  = (HI_S16)(((HI_S32)(pCSCTable[1][0] * PQ_GFX_COS_TABLE[Hue]) / 1000
                                            + (HI_S32)(pCSCTable[2][0] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
                                           * SaturationAdjust * rGain / 10000);
    g_aDstGfxHdrCSCTable[1][1]  = (HI_S16)(((HI_S32)(pCSCTable[1][1] * PQ_GFX_COS_TABLE[Hue]) / 1000
                                            + (HI_S32)(pCSCTable[2][1] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
                                           * SaturationAdjust * gGain  / 10000);
    g_aDstGfxHdrCSCTable[1][2]  = (HI_S16)(((HI_S32)(pCSCTable[1][2] * PQ_GFX_COS_TABLE[Hue]) / 1000
                                            + (HI_S32)(pCSCTable[2][2] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
                                           * SaturationAdjust * bGain  / 10000);
    g_aDstGfxHdrCSCTable[2][0] = (HI_S16)(((HI_S32)(pCSCTable[2][0] * PQ_GFX_COS_TABLE[Hue]) / 1000
                                           - (HI_S32)(pCSCTable[1][0] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
                                          * SaturationAdjust * rGain  / 10000);
    g_aDstGfxHdrCSCTable[2][1] = (HI_S16)(((HI_S32)(pCSCTable[2][1] * PQ_GFX_COS_TABLE[Hue]) / 1000
                                           - (HI_S32)(pCSCTable[1][1] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
                                          * SaturationAdjust * gGain  / 10000);
    g_aDstGfxHdrCSCTable[2][2] = (HI_S16)(((HI_S32)(pCSCTable[2][2] * PQ_GFX_COS_TABLE[Hue]) / 1000
                                           - (HI_S32)(pCSCTable[1][2] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
                                          * SaturationAdjust * bGain  / 10000);
    return;
}

static HI_VOID PQ_hal_GfxHdrOffsetCalCSCCoefRGBtoYCbCr(HI_PQ_HDR_MODE_E enHdrProcessScene, HI_U32 Contrast, HI_U32 Saturation,
        HI_U32 Hue, HI_U32 Kr, HI_U32 Kg, HI_U32 Kb, HI_S16 pCSCTable[3][3], HI_S16 pDstCSCTable[3][3])
{
    HI_S32 ContrastAdjust;
    HI_S32 SaturationAdjust;
    HI_S32 rGain, gGain, bGain;

    ContrastAdjust   = Contrast   * 40 / 51;
    SaturationAdjust = Saturation * 40 / 51;
    Hue   = Hue * 60 / 255;
    rGain = Kr  * 40 / 51;
    gGain = Kg  * 40 / 51;
    bGain = Kb  * 40 / 51;

    g_aDstGfxHdrOffsetCSCTable[enHdrProcessScene][0][0] = (HI_S16)((HI_S32)pCSCTable[0][0] * ContrastAdjust * rGain  / 10000);
    g_aDstGfxHdrOffsetCSCTable[enHdrProcessScene][0][1] = (HI_S16)((HI_S32)pCSCTable[0][1] * ContrastAdjust * gGain  / 10000);
    g_aDstGfxHdrOffsetCSCTable[enHdrProcessScene][0][2] = (HI_S16)((HI_S32)pCSCTable[0][2] * ContrastAdjust * bGain  / 10000);
    g_aDstGfxHdrOffsetCSCTable[enHdrProcessScene][1][0]  = (HI_S16)(((HI_S32)(pCSCTable[1][0] * PQ_GFX_COS_TABLE[Hue]) / 1000
            + (HI_S32)(pCSCTable[2][0] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
            * SaturationAdjust * rGain / 10000);
    g_aDstGfxHdrOffsetCSCTable[enHdrProcessScene][1][1]  = (HI_S16)(((HI_S32)(pCSCTable[1][1] * PQ_GFX_COS_TABLE[Hue]) / 1000
            + (HI_S32)(pCSCTable[2][1] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
            * SaturationAdjust * gGain  / 10000);
    g_aDstGfxHdrOffsetCSCTable[enHdrProcessScene][1][2]  = (HI_S16)(((HI_S32)(pCSCTable[1][2] * PQ_GFX_COS_TABLE[Hue]) / 1000
            + (HI_S32)(pCSCTable[2][2] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
            * SaturationAdjust * bGain  / 10000);
    g_aDstGfxHdrOffsetCSCTable[enHdrProcessScene][2][0] = (HI_S16)(((HI_S32)(pCSCTable[2][0] * PQ_GFX_COS_TABLE[Hue]) / 1000
            - (HI_S32)(pCSCTable[1][0] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
            * SaturationAdjust * rGain  / 10000);
    g_aDstGfxHdrOffsetCSCTable[enHdrProcessScene][2][1] = (HI_S16)(((HI_S32)(pCSCTable[2][1] * PQ_GFX_COS_TABLE[Hue]) / 1000
            - (HI_S32)(pCSCTable[1][1] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
            * SaturationAdjust * gGain  / 10000);
    g_aDstGfxHdrOffsetCSCTable[enHdrProcessScene][2][2] = (HI_S16)(((HI_S32)(pCSCTable[2][2] * PQ_GFX_COS_TABLE[Hue]) / 1000
            - (HI_S32)(pCSCTable[1][2] * PQ_GFX_SIN_TABLE[Hue]) / 1000)
            * SaturationAdjust * bGain  / 10000);
    return;
}

static HI_S32 pq_hal_SetGfxGamutMappingPara(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    /* GamutMapping */
    pstPqGfxHdrCfg->stGMAP.u16ScaleGMAP = u16GfxHdrScaleGMap;

    pstPqGfxHdrCfg->stGMAP.u32ClipMinGMAP = u32GfxHdrClipMinGMap;
    pstPqGfxHdrCfg->stGMAP.u32ClipMaxGMAP = u32GfxHdrClipMaxGMap;

    if (((HI_DRV_CS_BT709_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_FULL == enInCS))
        && ((HI_DRV_CS_BT2020_YUV_LIMITED == enOutCS) || (HI_DRV_CS_BT2020_YUV_FULL == enOutCS)))/* 709->2020 */
    {
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGMAP.as16M33GMAP, as16GfxHdrM33GMap_709to2020, sizeof(pstPqGfxHdrCfg->stGMAP.as16M33GMAP));
    }
    else if (((HI_DRV_CS_BT601_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT601_YUV_FULL == enInCS))
             && ((HI_DRV_CS_BT2020_YUV_LIMITED == enOutCS) || (HI_DRV_CS_BT2020_YUV_FULL == enOutCS)))/* 601->2020 */
    {
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGMAP.as16M33GMAP, as16GfxHdrM33GMAP_Pal_601_2020, sizeof(pstPqGfxHdrCfg->stGMAP.as16M33GMAP));
    }
    else if (((HI_DRV_CS_BT601_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT601_YUV_FULL == enInCS))
             && ((HI_DRV_CS_BT709_YUV_LIMITED == enOutCS) || (HI_DRV_CS_BT709_YUV_FULL == enOutCS)))/* 601->709 */
    {
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGMAP.as16M33GMAP, as16GfxHdrM33GMAP_Pal_601_709, sizeof(pstPqGfxHdrCfg->stGMAP.as16M33GMAP));
    }
    else
    {
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGMAP.as16M33GMAP, as16GfxHdrM33GMap_linear, sizeof(pstPqGfxHdrCfg->stGMAP.as16M33GMAP));
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_SetGfxHDRTMap(HI_DRV_COLOR_SPACE_E enInCS, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    HI_U32 u32Ratio, u32PeakLuminance;
    pstPqGfxHdrCfg->stTMAP.u16ScaleLumaCal = 12;

    if ((HI_DRV_CS_BT709_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_FULL == enInCS))
    {
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.au16M3LumaCal, au16GfxHdrM3LumaCal_709, sizeof(pstPqGfxHdrCfg->stTMAP.au16M3LumaCal));
    }
    else if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT2020_YUV_FULL == enInCS))
    {
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.au16M3LumaCal, au16GfxHdrM3LumaCal_2020, sizeof(pstPqGfxHdrCfg->stTMAP.au16M3LumaCal));
    }
    else
    {
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.au16M3LumaCal, au16GfxHdrM3LumaCal_601, sizeof(pstPqGfxHdrCfg->stTMAP.au16M3LumaCal));
    }

    pstPqGfxHdrCfg->stTMAP.u32ClipMinTM = u32GfxHdrClipMinTM;
    pstPqGfxHdrCfg->stTMAP.u32ClipMaxTM = u32GfxHdrClipMaxTM;
    PQ_SAFE_MEMSET(pstPqGfxHdrCfg->stTMAP.as32TMOff, 0, sizeof(pstPqGfxHdrCfg->stTMAP.as32TMOff));

    switch (sg_enGfxHdrMode)
    {
        case HI_PQ_HDR_MODE_SDR_TO_HDR10:
            pstPqGfxHdrCfg->stTMAP.u16ScaleCoefTM = 14;
            PQ_SAFE_MEMCPY(g_au32TmapCoefTmp, sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HDRClut, sizeof(g_au32TmapCoefTmp));
            break;
        case HI_PQ_HDR_MODE_SDR_TO_HLG:
            pstPqGfxHdrCfg->stTMAP.u16ScaleCoefTM = 8;
            PQ_SAFE_MEMCPY(g_au32TmapCoefTmp, sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HLGClut, sizeof(g_au32TmapCoefTmp));
            break;
        case HI_PQ_HDR_MODE_SDR_TO_SDR:
            pstPqGfxHdrCfg->stTMAP.u16ScaleCoefTM = 14;
            PQ_SAFE_MEMCPY(g_au32TmapCoefTmp, au32GfxHdrTMLut_SDR2HLG, sizeof(g_au32TmapCoefTmp));
            break;
        default:
            pstPqGfxHdrCfg->stTMAP.u16ScaleCoefTM = 14;
            PQ_SAFE_MEMCPY(g_au32TmapCoefTmp, au32GfxHdrTMLut_SDR2HLG, sizeof(g_au32TmapCoefTmp));
    }

    /* SDR2HDR SoftAlg */
    if (HI_PQ_HDR_MODE_SDR_TO_HDR10 == sg_enGfxHdrMode)
    {
        u32Ratio         = g_u32GfxBrightCvStr[HI_PQ_HDR_MODE_SDR_TO_HDR10];
        u32PeakLuminance = g_u32GfxDarkCvStr[HI_PQ_HDR_MODE_SDR_TO_HDR10];
        pq_hal_GfxHdrAdjustBasicTM(pstPqGfxHdrCfg->stTMAP.au32StepTM, pstPqGfxHdrCfg->stTMAP.au32NumTM, pstPqGfxHdrCfg->stTMAP.au32PosTM, \
                                   pstPqGfxHdrCfg->stTMAP.u16ScaleCoefTM, u32Ratio, u32PeakLuminance, pstPqGfxHdrCfg->stTMAP.pu32LUTTM);
    }

    if (0 == sg_stToolGfxHdrMode.u32ParaModeUse)
    {
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.au32StepTM, au32GfxHdrTMapStep, sizeof(pstPqGfxHdrCfg->stTMAP.au32StepTM));
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.au32NumTM,  au32GfxHdrTMapNum,  sizeof(pstPqGfxHdrCfg->stTMAP.au32NumTM ));
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.au32PosTM,  au32GfxHdrTMapPos,  sizeof(pstPqGfxHdrCfg->stTMAP.au32PosTM ));

        PQ_SAFE_MEMCPY(sg_stToolGfxHdrStep.au32X_step, pstPqGfxHdrCfg->stTMAP.au32StepTM, sizeof(sg_stToolGfxHdrStep.au32X_step));
        PQ_SAFE_MEMCPY(sg_stToolGfxHdrStep.au32X_num,  pstPqGfxHdrCfg->stTMAP.au32NumTM,  sizeof(sg_stToolGfxHdrStep.au32X_num));
        PQ_SAFE_MEMCPY(sg_stToolGfxHdrStep.au32X_pos,  pstPqGfxHdrCfg->stTMAP.au32PosTM,  sizeof(sg_stToolGfxHdrStep.au32X_pos));

        PQ_SAFE_MEMCPY(sg_stToolGfxHdrTmap.au32Clut, g_au32TmapCoefTmp, sizeof(sg_stToolGfxHdrTmap.au32Clut));
    }
    else if (1 == sg_stToolGfxHdrMode.u32ParaModeUse)
    {

        PQ_SAFE_MEMCPY(g_au32TmapCoefTmp, sg_stToolGfxHdrTmap.au32Clut, sizeof(sg_stToolGfxHdrTmap.au32Clut));

        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.au32StepTM, sg_stToolGfxHdrStep.au32X_step, sizeof(pstPqGfxHdrCfg->stTMAP.au32StepTM));
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.au32NumTM,  sg_stToolGfxHdrStep.au32X_num,  sizeof(pstPqGfxHdrCfg->stTMAP.au32NumTM ));
        PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.au32PosTM,  sg_stToolGfxHdrStep.au32X_pos,  sizeof(pstPqGfxHdrCfg->stTMAP.au32PosTM ));
    }

    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stTMAP.pu32LUTTM, g_au32TmapCoefTmp, sizeof(pstPqGfxHdrCfg->stTMAP.pu32LUTTM));

    return HI_SUCCESS;
}

static HI_S32 pq_hal_SetGfxR2YMatrix(HI_DRV_COLOR_SPACE_E enOutCS, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    /* RGB2YUV */
    pstPqGfxHdrCfg->stR2Y.u16ScaleR2Y = u16GfxHdrScaleR2Y;

    switch (enOutCS)
    {
        case HI_DRV_CS_BT2020_YUV_LIMITED:
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   as16GfxHdrM33RF2YL_2020NCL,  sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y,  as16GfxHdrDcInRF2YL,         sizeof(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, as16GfxHdrDcOutRF2YL,        sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));
            pstPqGfxHdrCfg->stR2Y.u16ClipMinR2Y = u16GfxHdrClipMinRF2YL;
            pstPqGfxHdrCfg->stR2Y.u16ClipMaxR2Y = u16GfxHdrClipMaxRF2YL;
            break;
        case HI_DRV_CS_BT2020_YUV_FULL:
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   as16GfxHdrM33RF2YF_2020NCL,  sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y,  as16GfxHdrDcInRF2YF,         sizeof(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, as16GfxHdrDcOutRF2YF,        sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));
            pstPqGfxHdrCfg->stR2Y.u16ClipMinR2Y = u16GfxHdrClipMinRF2YF;
            pstPqGfxHdrCfg->stR2Y.u16ClipMaxR2Y = u16GfxHdrClipMaxRF2YF;
            break;
        case HI_DRV_CS_BT709_YUV_LIMITED:
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   as16GfxHdrM33RF2YL_709,      sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y,  as16GfxHdrDcInRF2YL,         sizeof(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, as16GfxHdrDcOutRF2YL,        sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));
            pstPqGfxHdrCfg->stR2Y.u16ClipMinR2Y = u16GfxHdrClipMinRF2YL;
            pstPqGfxHdrCfg->stR2Y.u16ClipMaxR2Y = u16GfxHdrClipMaxRF2YL;
            break;
        case HI_DRV_CS_BT709_YUV_FULL:
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   as16GfxHdrM33RF2YF_709,      sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y,  as16GfxHdrDcInRF2YF,         sizeof(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, as16GfxHdrDcOutRF2YF,        sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));
            pstPqGfxHdrCfg->stR2Y.u16ClipMinR2Y = u16GfxHdrClipMinRF2YF;
            pstPqGfxHdrCfg->stR2Y.u16ClipMaxR2Y = u16GfxHdrClipMaxRF2YF;
            break;
        case HI_DRV_CS_BT601_YUV_LIMITED:
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   as16GfxHdrM33RF2YL_601,      sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y,  as16GfxHdrDcInRF2YL,         sizeof(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, as16GfxHdrDcOutRF2YL,        sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));
            pstPqGfxHdrCfg->stR2Y.u16ClipMinR2Y = u16GfxHdrClipMinRF2YL;
            pstPqGfxHdrCfg->stR2Y.u16ClipMaxR2Y = u16GfxHdrClipMaxRF2YL;
            break;
        case HI_DRV_CS_BT601_YUV_FULL:
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   as16GfxHdrM33RF2YF_601,      sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y,  as16GfxHdrDcInRF2YF,         sizeof(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, as16GfxHdrDcOutRF2YF,        sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));
            pstPqGfxHdrCfg->stR2Y.u16ClipMinR2Y = u16GfxHdrClipMinRF2YF;
            pstPqGfxHdrCfg->stR2Y.u16ClipMaxR2Y = u16GfxHdrClipMaxRF2YF;
            break;
        case HI_DRV_CS_BT2020_RGB_FULL: /*R2R */
        case HI_DRV_CS_BT709_RGB_FULL: /*R2R */
        case HI_DRV_CS_BT601_RGB_FULL: /*R2R */
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   as16GfxHdrM33RF2RF,          sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y,  as16GfxHdrDcInRF2RF,         sizeof(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, as16GfxHdrDcOutRF2RF,        sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));
            pstPqGfxHdrCfg->stR2Y.u16ClipMinR2Y = u16GfxHdrClipMinRF2RF;
            pstPqGfxHdrCfg->stR2Y.u16ClipMaxR2Y = u16GfxHdrClipMaxRF2RF;
            break;
        default:
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   as16GfxHdrM33RF2YL_709,      sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y,  as16GfxHdrDcInRF2YL,         sizeof(pstPqGfxHdrCfg->stR2Y.as16DcInR2Y));
            PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, as16GfxHdrDcOutRF2YL,        sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));
            pstPqGfxHdrCfg->stR2Y.u16ClipMinR2Y = u16GfxHdrClipMinRF2YL;
            pstPqGfxHdrCfg->stR2Y.u16ClipMaxR2Y = u16GfxHdrClipMaxRF2YL;
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetGfxSDR2HDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    pstPqGfxHdrCfg->bHdrEn         = HI_TRUE ;
    pstPqGfxHdrCfg->bDegammaEn     = HI_TRUE ;
    pstPqGfxHdrCfg->bTMapEn        = HI_TRUE ;
    pstPqGfxHdrCfg->bGMapEn        = HI_TRUE ;
    pstPqGfxHdrCfg->bGammaEn       = HI_TRUE ;
    pstPqGfxHdrCfg->bDitherEn      = HI_TRUE ;
    pstPqGfxHdrCfg->bR2YEn         = HI_TRUE ;
    pstPqGfxHdrCfg->bDitherMode    = HI_TRUE ;

    /* DeGamma */
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.au32Step,  au32GfxHdrDeGmm_step,   sizeof(pstPqGfxHdrCfg->stDeGmm.au32Step));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.au32Pos ,  au32GfxHdrDeGmm_pos,    sizeof(pstPqGfxHdrCfg->stDeGmm.au32Pos ));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.au32Num ,  au32GfxHdrDeGmm_num,    sizeof(pstPqGfxHdrCfg->stDeGmm.au32Num ));
    /*PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.pu32LUT ,  au32GfxHdrDeGmmLut_24,  sizeof(pstPqGfxHdrCfg->stDeGmm.pu32LUT ));*/

    /* ToneMapping */
    pq_hal_SetGfxHDRTMap(enInCS, pstPqGfxHdrCfg);

    /* GamutMapping */
    pq_hal_SetGfxGamutMappingPara(enInCS, enOutCS, pstPqGfxHdrCfg);

    /*  Gamma */
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.au32Step,  au32GfxHdrGmmStep,        sizeof(pstPqGfxHdrCfg->stGmm.au32Step));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.au32Pos ,  au32GfxHdrGmmPos,         sizeof(pstPqGfxHdrCfg->stGmm.au32Pos ));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.au32Num ,  au32GfxHdrGmmNum,         sizeof(pstPqGfxHdrCfg->stGmm.au32Num ));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.pu32LUT ,  au32GfxHdrGmmLut_PQ1500,  sizeof(pstPqGfxHdrCfg->stGmm.pu32LUT ));

    /* RGB2YUV */
    pq_hal_SetGfxR2YMatrix(enOutCS, pstPqGfxHdrCfg);

    /* Hdr Offset Adjust */
    PQ_hal_GfxHdrOffsetCalCSCCoefRGBtoYCbCr(HI_PQ_HDR_MODE_SDR_TO_HDR10,
                                            g_u32GfxHdrOffsetContrast[HI_PQ_HDR_MODE_SDR_TO_HDR10],
                                            g_u32GfxHdrOffsetSatu[HI_PQ_HDR_MODE_SDR_TO_HDR10] * 125 / 100,
                                            g_u32GfxHdrOffsetHue[HI_PQ_HDR_MODE_SDR_TO_HDR10],
                                            g_u32GfxHdrOffsetRed[HI_PQ_HDR_MODE_SDR_TO_HDR10],
                                            g_u32GfxHdrOffsetGreen[HI_PQ_HDR_MODE_SDR_TO_HDR10],
                                            g_u32GfxHdrOffsetBlue[HI_PQ_HDR_MODE_SDR_TO_HDR10],
                                            pstPqGfxHdrCfg->stR2Y.as16M33R2Y,
                                            g_aDstGfxHdrOffsetCSCTable[HI_PQ_HDR_MODE_SDR_TO_HDR10]);

    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   g_aDstGfxHdrOffsetCSCTable[HI_PQ_HDR_MODE_SDR_TO_HDR10], sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));

    PQ_SAFE_MEMCPY(g_as16GfxHdrOffsetDcOutR2Y[HI_PQ_HDR_MODE_SDR_TO_HDR10], pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, sizeof(g_as16GfxHdrOffsetDcOutR2Y[HI_PQ_HDR_MODE_SDR_TO_HDR10]));

    g_as16GfxHdrOffsetDcOutR2Y[HI_PQ_HDR_MODE_SDR_TO_HDR10][0] = g_as16GfxHdrOffsetDcOutR2Y[HI_PQ_HDR_MODE_SDR_TO_HDR10][0] +
            (g_u32GfxHdrOffsetBright[HI_PQ_HDR_MODE_SDR_TO_HDR10] - 128) * 4;

    /* Hdr Normal Adjust */
    PQ_hal_CalGfxHdrCSCCoefRGBtoYCbCr(g_u32GfxHdrContrast, g_u32GfxHdrSatu, g_u32GfxHdrHue,
                                      g_u32GfxHdrRed, g_u32GfxHdrGreen, g_u32GfxHdrBlue, pstPqGfxHdrCfg->stR2Y.as16M33R2Y, g_aDstGfxHdrCSCTable);

    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   g_aDstGfxHdrCSCTable, sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));

    g_as16GfxHdrOffsetDcOutR2Y[HI_PQ_HDR_MODE_SDR_TO_HDR10][0] = g_as16GfxHdrOffsetDcOutR2Y[HI_PQ_HDR_MODE_SDR_TO_HDR10][0] + (g_u32GfxHdrBright - 128) * 4;

    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, g_as16GfxHdrOffsetDcOutR2Y[HI_PQ_HDR_MODE_SDR_TO_HDR10], sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetGfxSDR2SDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    /* WCG */
    if (enInCS != enOutCS)
    {
        pstPqGfxHdrCfg->bHdrEn         = HI_TRUE;
        pstPqGfxHdrCfg->bDegammaEn     = HI_TRUE;
        pstPqGfxHdrCfg->bTMapEn        = HI_FALSE;
        pstPqGfxHdrCfg->bGMapEn        = HI_TRUE;
        pstPqGfxHdrCfg->bGammaEn       = HI_TRUE;
        pstPqGfxHdrCfg->bDitherEn      = HI_TRUE;
        pstPqGfxHdrCfg->bR2YEn         = HI_TRUE;

        pstPqGfxHdrCfg->bDitherMode    = HI_TRUE;
    }
    else
    {
        pstPqGfxHdrCfg->bHdrEn         = HI_FALSE;
        pstPqGfxHdrCfg->bDegammaEn     = HI_FALSE;
        pstPqGfxHdrCfg->bTMapEn        = HI_FALSE;
        pstPqGfxHdrCfg->bGMapEn        = HI_FALSE;
        pstPqGfxHdrCfg->bGammaEn       = HI_FALSE;
        pstPqGfxHdrCfg->bDitherEn      = HI_FALSE;
        pstPqGfxHdrCfg->bR2YEn         = HI_FALSE;

        pstPqGfxHdrCfg->bDitherMode    = HI_FALSE;
    }

    /* DeGamma */
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.au32Step,  au32GfxHdrDeGmm_step,  sizeof(pstPqGfxHdrCfg->stDeGmm.au32Step));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.au32Pos ,  au32GfxHdrDeGmm_pos,   sizeof(pstPqGfxHdrCfg->stDeGmm.au32Pos ));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.au32Num ,  au32GfxHdrDeGmm_num,   sizeof(pstPqGfxHdrCfg->stDeGmm.au32Num ));
    /*PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.pu32LUT ,  au32GfxHdrDeGmmLut_22, sizeof(pstPqGfxHdrCfg->stDeGmm.pu32LUT ));*/

    /* ToneMapping Tmap */
    pq_hal_SetGfxHDRTMap(enInCS, pstPqGfxHdrCfg);

    /* GamutMapping */
    pq_hal_SetGfxGamutMappingPara(enInCS, enOutCS, pstPqGfxHdrCfg);

    /*  Gamma */
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.au32Step, au32GfxHdrGmmStep,     sizeof(pstPqGfxHdrCfg->stGmm.au32Step));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.au32Pos ,  au32GfxHdrGmmPos,     sizeof(pstPqGfxHdrCfg->stGmm.au32Pos ));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.au32Num ,  au32GfxHdrGmmNum,     sizeof(pstPqGfxHdrCfg->stGmm.au32Num ));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.pu32LUT ,  au32GfxHdrGmmLut_22,  sizeof(pstPqGfxHdrCfg->stGmm.pu32LUT ));

    /* RGB2YUV */
    pq_hal_SetGfxR2YMatrix(enOutCS, pstPqGfxHdrCfg);
    /* Hdr Normal Adjust */
    PQ_hal_CalGfxHdrCSCCoefRGBtoYCbCr(g_u32GfxHdrContrast, g_u32GfxHdrSatu, g_u32GfxHdrHue,
                                      g_u32GfxHdrRed, g_u32GfxHdrGreen, g_u32GfxHdrBlue, pstPqGfxHdrCfg->stR2Y.as16M33R2Y, g_aDstGfxHdrCSCTable);
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   g_aDstGfxHdrCSCTable, sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));

    PQ_SAFE_MEMCPY(g_as16DcGfxHdrOutR2Y, pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, sizeof(g_as16DcGfxHdrOutR2Y));
    g_as16DcGfxHdrOutR2Y[0] = g_as16DcGfxHdrOutR2Y[0] + (g_u32GfxHdrBright - 128) * 4;
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, g_as16DcGfxHdrOutR2Y, sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetGfxSDR2HLGCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    pstPqGfxHdrCfg->bHdrEn         = HI_TRUE ;
    pstPqGfxHdrCfg->bDegammaEn     = HI_TRUE ;
    pstPqGfxHdrCfg->bTMapEn        = HI_TRUE ;
    pstPqGfxHdrCfg->bGMapEn        = HI_TRUE ;
    pstPqGfxHdrCfg->bGammaEn       = HI_TRUE ;
    pstPqGfxHdrCfg->bDitherEn      = HI_TRUE ;
    pstPqGfxHdrCfg->bR2YEn         = HI_TRUE ;
    pstPqGfxHdrCfg->bDitherMode    = HI_TRUE ;

    /* DeGamma */
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.au32Step,  au32GfxHdrDeGmm_step, sizeof(pstPqGfxHdrCfg->stDeGmm.au32Step));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.au32Pos ,  au32GfxHdrDeGmm_pos,  sizeof(pstPqGfxHdrCfg->stDeGmm.au32Pos ));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.au32Num ,  au32GfxHdrDeGmm_num,  sizeof(pstPqGfxHdrCfg->stDeGmm.au32Num ));
    /*PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stDeGmm.pu32LUT ,  au32GfxHdrDeGmmLut_24,        sizeof(pstPqGfxHdrCfg->stDeGmm.pu32LUT ));*/
    /* ToneMapping */
    pq_hal_SetGfxHDRTMap(enInCS, pstPqGfxHdrCfg);

    /* GamutMapping */
    pq_hal_SetGfxGamutMappingPara(enInCS, enOutCS, pstPqGfxHdrCfg);

    /*  Gamma */
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.au32Step,  au32GfxHdrGmmStep,       sizeof(pstPqGfxHdrCfg->stGmm.au32Step));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.au32Pos ,  au32GfxHdrGmmPos,        sizeof(pstPqGfxHdrCfg->stGmm.au32Pos ));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.au32Num ,  au32GfxHdrGmmNum,        sizeof(pstPqGfxHdrCfg->stGmm.au32Num ));
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stGmm.pu32LUT ,  au32GfxHdrGmmLut_HLG,    sizeof(pstPqGfxHdrCfg->stGmm.pu32LUT ));

    /* RGB2YUV */
    pq_hal_SetGfxR2YMatrix(enOutCS, pstPqGfxHdrCfg);
    /* Hdr Normal Adjust */
    PQ_hal_CalGfxHdrCSCCoefRGBtoYCbCr(g_u32GfxHdrContrast, g_u32GfxHdrSatu, g_u32GfxHdrHue,
                                      g_u32GfxHdrRed, g_u32GfxHdrGreen, g_u32GfxHdrBlue, pstPqGfxHdrCfg->stR2Y.as16M33R2Y, g_aDstGfxHdrCSCTable);
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16M33R2Y,   g_aDstGfxHdrCSCTable, sizeof(pstPqGfxHdrCfg->stR2Y.as16M33R2Y));

    PQ_SAFE_MEMCPY(g_as16DcGfxHdrOutR2Y, pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, sizeof(g_as16DcGfxHdrOutR2Y));
    g_as16DcGfxHdrOutR2Y[0] = g_as16DcGfxHdrOutR2Y[0] + (g_u32GfxHdrBright - 128) * 4;
    PQ_SAFE_MEMCPY(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y, g_as16DcGfxHdrOutR2Y, sizeof(pstPqGfxHdrCfg->stR2Y.as16DcOutR2Y));

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetGfxHdrCfg(HI_PQ_GFXHDR_HDR_INFO *pstGfxHdrInfo, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if ((HI_DRV_VIDEO_FRAME_TYPE_SDR == pstGfxHdrInfo->enSrcFrameType) && (HI_PQ_DISP_TYPE_HDR10 == pstGfxHdrInfo->enDispType))
    {
        sg_enGfxHdrMode = HI_PQ_HDR_MODE_SDR_TO_HDR10;
        s32Ret       = pq_hal_GetGfxSDR2HDRCfg(pstGfxHdrInfo->enInCS, pstGfxHdrInfo->enOutCS, pstPqGfxHdrCfg);
    }
    else if ((HI_DRV_VIDEO_FRAME_TYPE_SDR == pstGfxHdrInfo->enSrcFrameType) && (HI_PQ_DISP_TYPE_NORMAL == pstGfxHdrInfo->enDispType))
    {
        sg_enGfxHdrMode = HI_PQ_HDR_MODE_SDR_TO_SDR;
        s32Ret       = pq_hal_GetGfxSDR2SDRCfg(pstGfxHdrInfo->enInCS, pstGfxHdrInfo->enOutCS, pstPqGfxHdrCfg);
    }
    else if ((HI_DRV_VIDEO_FRAME_TYPE_SDR == pstGfxHdrInfo->enSrcFrameType) && (HI_PQ_DISP_TYPE_HLG == pstGfxHdrInfo->enDispType))
    {
        sg_enGfxHdrMode = HI_PQ_HDR_MODE_SDR_TO_HLG;
        s32Ret       = pq_hal_GetGfxSDR2HLGCfg(pstGfxHdrInfo->enInCS, pstGfxHdrInfo->enOutCS, pstPqGfxHdrCfg);
    }
    else
    {
        HI_ERR_PQ("Gfx Hdr Cannot Support !!!\n");
    }

    return s32Ret;
}

/* bDefault : 0 / bin success; 1 / bin fail */
HI_S32 PQ_HAL_InitGfxHdr(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault)
{
    HI_U32 u32HdrTmapBinCheckSum0 = 0;
    HI_U32 u32HdrTmapBinCheckSum1 = 0;
    HI_U32 i = 0;

    sg_pstGfxHdrBinPara = pstPqParam;

    PQ_CHECK_NULL_PTR_RE_FAIL(sg_pstGfxHdrBinPara);

    for (i = 0; i < PQ_GFXHDR_TMAP_LUT_SIZE; i++)
    {
        u32HdrTmapBinCheckSum0 += sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HDRClut[i];
        u32HdrTmapBinCheckSum1 += sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HLGClut[i];
    }

    if (HI_TRUE != bParaUseTableDefault)
    {
        if (u32HdrTmapBinCheckSum0 > 0)
        {
            PQ_SAFE_MEMCPY(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HDRClut, &(sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HDRClut), \
                           sizeof(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HDRClut));
        }
        else
        {
            PQ_SAFE_MEMCPY(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HDRClut, au32GfxHdrTMLut_SDR2HDR1000, sizeof(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HDRClut));
            PQ_SAFE_MEMCPY(sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HDRClut, sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HDRClut, \
                           sizeof(sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HDRClut));
        }

        if (u32HdrTmapBinCheckSum1 > 0)
        {
            PQ_SAFE_MEMCPY(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HLGClut, &(sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HLGClut), \
                           sizeof(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HLGClut));
        }
        else
        {
            PQ_SAFE_MEMCPY(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HLGClut, au32GfxHdrTMLut_SDR2HLG, sizeof(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HLGClut));
            PQ_SAFE_MEMCPY(sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HLGClut, sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HLGClut, \
                           sizeof(sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef.au32TMSdr2HLGClut));
        }
    }
    else
    {
        PQ_SAFE_MEMCPY(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HDRClut, au32GfxHdrTMLut_SDR2HDR1000, sizeof(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HDRClut));
        PQ_SAFE_MEMCPY(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HLGClut, au32GfxHdrTMLut_SDR2HLG,      sizeof(sg_stGfxHdrTmClutBinOrCode.au32TMSdr2HLGClut));

        PQ_SAFE_MEMCPY(&(sg_pstGfxHdrBinPara->stPQCoef.stGfxHdrTmCoef), &sg_stGfxHdrTmClutBinOrCode, sizeof(sg_stGfxHdrTmClutBinOrCode));
    }

    return HI_SUCCESS;
}


