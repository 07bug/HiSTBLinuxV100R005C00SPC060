/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_hal_lchdr.c
  Version       : Initial Draft
  Author        : sdk
                      sdk
  Created      : 2018/01/12
  Description  :

******************************************************************************/
#include <linux/string.h>

#include "hi_type.h"
#include "hi_math.h"

#include "pq_hal_comm.h"
#include "drv_pq_ext.h"
#include "pq_hal_lchdr.h"

static HI_BOOL sg_bHalSetEn     = HI_TRUE;
static HI_BOOL sg_bHalProcessEn = HI_FALSE;

typedef HI_S32 (*PF_PQ_Hal_GetLCHdrPathCfg) (HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS);

static HI_PQ_HDR_MODE_E aenPqHalLCHDRPathMode[HI_DRV_VIDEO_FRAME_TYPE_BUTT][HI_PQ_DISP_TYPE_BUTT] =
{
    {HI_PQ_HDR_MODE_SDR_TO_SDR,     HI_PQ_HDR_MODE_SDR_TO_HDR10,    HI_PQ_HDR_MODE_SDR_TO_HLG   },   /* sdr */
    {HI_PQ_HDR_MODE_BUTT,           HI_PQ_HDR_MODE_BUTT,            HI_PQ_HDR_MODE_BUTT         },   /* bl */
    {HI_PQ_HDR_MODE_BUTT,           HI_PQ_HDR_MODE_BUTT,            HI_PQ_HDR_MODE_BUTT         },   /* el */
    {HI_PQ_HDR_MODE_HDR10_TO_SDR,   HI_PQ_HDR_MODE_HDR10_TO_HDR10,  HI_PQ_HDR_MODE_HDR10_TO_HLG },   /* hdr10 */
    {HI_PQ_HDR_MODE_HLG_TO_SDR,     HI_PQ_HDR_MODE_HLG_TO_HDR10,    HI_PQ_HDR_MODE_HLG_TO_HLG   },   /* hlg */
    {HI_PQ_HDR_MODE_SLF_TO_SDR,     HI_PQ_HDR_MODE_SLF_TO_HDR10,    HI_PQ_HDR_MODE_SLF_TO_HLG   },   /* slf */
    {HI_PQ_HDR_MODE_BUTT,           HI_PQ_HDR_MODE_BUTT,            HI_PQ_HDR_MODE_BUTT         },   /* tech */
};

static HI_PQ_HDR_MODE_E sg_enLCHDRMode    = HI_PQ_HDR_MODE_SDR_TO_SDR;

/*********************** hdr102sdrtypical ***********************************/
static const HI_U16 hdr102sdrtypc_ylutlim[TM_LUT_SIZE] = //12bit
{
    256 ,       256 ,       268 ,       278 ,       288 ,       298 ,       320 ,       343 ,
    368 ,       395 ,       425 ,       457 ,       491 ,       529 ,       569 ,       612 ,
    659 ,       709 ,       763 ,       821 ,       882 ,       949 ,      1019 ,      1095 ,
    1175 ,      1261 ,      1352 ,      1448 ,      1551 ,      1658 ,      1772 ,      1890 ,
    2014 ,      2143 ,      2276 ,      2412 ,      2551 ,      2690 ,      2828 ,      2964 ,
    3095 ,      3219 ,      3333 ,      3435 ,      3523 ,      3596 ,      3653 ,      3695 ,
    3724 ,      3742 ,      3752 ,      3757 ,      3759 ,      3760 ,      3760 ,      3760 ,
    3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,
};

static const HI_U16 hdr102sdrtypc_ylutfull[TM_LUT_SIZE] = //12bit
{
    0 ,        13 ,        23 ,        32 ,        42 ,        53 ,        63 ,        74 ,
    86 ,        97 ,       109 ,       122 ,       135 ,       148 ,       162 ,       177 ,
    192 ,       207 ,       223 ,       240 ,       257 ,       274 ,       293 ,       372 ,
    462 ,       564 ,       678 ,       807 ,       952 ,      1114 ,      1293 ,      1491 ,
    1709 ,      1945 ,      2199 ,      2467 ,      2744 ,      3021 ,      3157 ,      3289 ,
    3414 ,      3533 ,      3641 ,      3739 ,      3825 ,      3897 ,      3956 ,      4002 ,
    4036 ,      4060 ,      4075 ,      4084 ,      4088 ,      4091 ,      4092 ,      4092 ,
    4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,
};

static const HI_U16 hdr102sdrtypc_satlutlimit[SatM_LUT_SIZE] =   // 10bit
{

    102 ,       102 ,       102 ,       102 ,       102 ,       115 ,       136 ,       160 ,
    179 ,       191 ,       197 ,       200 ,       203 ,       208 ,       217 ,       227 ,
    236 ,       241 ,       244 ,       243 ,       241 ,       244 ,       259 ,       289 ,
    332 ,       384 ,       441 ,       499 ,       558 ,       614 ,       666 ,       711 ,
    746 ,       772 ,       791 ,       807 ,       824 ,       846 ,       872 ,       898 ,
    922 ,       941 ,       961 ,       986 ,      1015 ,      1023 ,      1023 ,      1023 ,
    1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,
    1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,      1023 ,
    1023 ,
} ;

static const HI_U16 hdr102sdrtypc_satlutfull[SatM_LUT_SIZE] =   // 10bit
{
    307 ,       314 ,       321 ,       327 ,       331 ,       334 ,       335 ,       336 ,
    337 ,       337 ,       338 ,       340 ,       343 ,       345 ,       346 ,       347 ,
    350 ,       361 ,       379 ,       402 ,       426 ,       448 ,       466 ,       482 ,
    496 ,       508 ,       518 ,       529 ,       539 ,       550 ,       562 ,       576 ,
    592 ,       610 ,       628 ,       645 ,       658 ,       667 ,       670 ,       672 ,
    677 ,       689 ,       712 ,       741 ,       769 ,       791 ,       807 ,       819 ,
    828 ,       835 ,       839 ,       842 ,       844 ,       845 ,       845 ,       845 ,
    845 ,       846 ,       847 ,       849 ,       853 ,       858 ,       866 ,       876 ,
    888 ,
} ;

/*********************** sdr2hdr10typical ***********************************/

static const HI_U16 sdr2hdr10typc_ylutlim[TM_LUT_SIZE] =
{
    256 ,       256 ,       296 ,       341 ,       395 ,       457 ,       581 ,       676 ,
    754 ,       835 ,       906 ,       970 ,      1031 ,      1092 ,      1149 ,      1204 ,
    1256 ,      1306 ,      1356 ,      1404 ,      1449 ,      1497 ,      1539 ,      1583 ,
    1627 ,      1674 ,      1715 ,      1760 ,      1806 ,      1849 ,      1890 ,      1936 ,
    1980 ,      2025 ,      2070 ,      2117 ,      2164 ,      2210 ,      2260 ,      2310 ,
    2363 ,      2416 ,      2468 ,      2506 ,      2541 ,      2574 ,      2606 ,      2636 ,
    2665 ,      2692 ,      2718 ,      2742 ,      2766 ,      2789 ,      2812 ,      2833 ,
    2855 ,      2876 ,      2879 ,      2881 ,      2884 ,      2887 ,      2889 ,      2891 ,
} ;


static const HI_U16 sdr2hdr10typc_ylutful[TM_LUT_SIZE] =
{
    1 ,        39 ,        83 ,       134 ,       193 ,       256 ,       320 ,       379 ,
    430 ,       474 ,       520 ,       557 ,       594 ,       632 ,       676 ,       711 ,
    747 ,       780 ,       810 ,       845 ,       873 ,       905 ,       937 ,      1052 ,
    1158 ,      1259 ,      1356 ,      1449 ,      1534 ,      1627 ,      1710 ,      1800 ,
    1887 ,      1973 ,      2064 ,      2154 ,      2249 ,      2347 ,      2397 ,      2448 ,
    2503 ,      2554 ,      2601 ,      2638 ,      2673 ,      2706 ,      2738 ,      2768 ,
    2797 ,      2825 ,      2852 ,      2877 ,      2902 ,      2926 ,      2949 ,      2972 ,
    2994 ,      3016 ,      3037 ,      3059 ,      3069 ,      3077 ,      3077 ,      3077 ,
} ;

static const HI_U16 sdr2hdr10typc_satlutlimit[SatM_LUT_SIZE] =   // 10bit
{
    123 ,       123 ,       123 ,       123 ,       123 ,       123 ,       123 ,       123 ,
    123 ,       124 ,       125 ,       125 ,       124 ,       121 ,       117 ,       113 ,
    110 ,       109 ,       110 ,       110 ,       110 ,       110 ,       110 ,       110 ,
    110 ,       110 ,       111 ,       113 ,       115 ,       118 ,       120 ,       122 ,
    123 ,       124 ,       124 ,       123 ,       123 ,       123 ,       122 ,       123 ,
    123 ,       123 ,       123 ,       122 ,       119 ,       116 ,       113 ,       110 ,
    107 ,       105 ,       102 ,       101 ,        99 ,        98 ,        96 ,        95 ,
    94 ,        92 ,        91 ,        89 ,        87 ,        85 ,        83 ,        80 ,
    77 ,
};

static const HI_U16 sdr2hdr10typc_satlutful[SatM_LUT_SIZE] =   // 10bit
{
    123 ,       123 ,       123 ,       123 ,       123 ,       123 ,       124 ,       125 ,
    125 ,       124 ,       122 ,       119 ,       115 ,       112 ,       110 ,       109 ,
    110 ,       110 ,       110 ,       110 ,       110 ,       110 ,       110 ,       110 ,
    110 ,       111 ,       113 ,       115 ,       117 ,       119 ,       120 ,       122 ,
    123 ,       124 ,       124 ,       124 ,       123 ,       123 ,       123 ,       122 ,
    123 ,       123 ,       123 ,       123 ,       123 ,       121 ,       118 ,       115 ,
    112 ,       110 ,       107 ,       105 ,       103 ,       102 ,       100 ,        99 ,
    97 ,        96 ,        95 ,        94 ,        93 ,        92 ,        90 ,        89 ,
    87 ,
};
/*********************** hlg2hdr10typical ***********************************/

static const HI_U16 hlg2hdr10typc_ylutlim[TM_LUT_SIZE] = //12bit
{
    255 ,       255 ,       299 ,       356 ,       414 ,       470 ,       574 ,       668 ,
    754 ,       834 ,       907 ,       976 ,      1040 ,      1100 ,      1157 ,      1210 ,
    1261 ,      1310 ,      1356 ,      1401 ,      1443 ,      1484 ,      1523 ,      1561 ,
    1597 ,      1633 ,      1667 ,      1700 ,      1731 ,      1762 ,      1792 ,      1822 ,
    1852 ,      1884 ,      1916 ,      1950 ,      1984 ,      2019 ,      2056 ,      2092 ,
    2130 ,      2169 ,      2208 ,      2248 ,      2288 ,      2330 ,      2371 ,      2413 ,
    2456 ,      2499 ,      2543 ,      2587 ,      2631 ,      2675 ,      2720 ,      2765 ,
    2811 ,      2856 ,      2862 ,      2868 ,      2873 ,      2879 ,      2885 ,      2890 ,
} ;

static const HI_U16 hlg2hdr10typc_ylutfull[TM_LUT_SIZE] = //12bit
{
    0 ,        41 ,        98 ,       156 ,       213 ,       267 ,       320 ,       371 ,
    419 ,       466 ,       510 ,       554 ,       595 ,       635 ,       674 ,       712 ,
    748 ,       783 ,       817 ,       851 ,       883 ,       914 ,       945 ,      1060 ,
    1165 ,      1261 ,      1350 ,      1433 ,      1511 ,      1584 ,      1652 ,      1717 ,
    1778 ,      1838 ,      1900 ,      1965 ,      2034 ,      2106 ,      2143 ,      2181 ,
    2219 ,      2258 ,      2298 ,      2338 ,      2378 ,      2420 ,      2461 ,      2503 ,
    2546 ,      2589 ,      2632 ,      2675 ,      2719 ,      2764 ,      2808 ,      2853 ,
    2898 ,      2943 ,      2988 ,      3034 ,      3056 ,      3076 ,      3076 ,      3076 ,
} ;

/*********************** HDR2HLGtypical ***********************************/

static const HI_U16 HDR2HLGtypc_ylutlim[TM_LUT_SIZE] =
{
    256 ,       257 ,       300 ,       336 ,       372 ,       409 ,       449 ,       492 ,
    539 ,       588 ,       639 ,       693 ,       752 ,       816 ,       883 ,       955 ,
    1032 ,      1112 ,      1199 ,      1292 ,      1389 ,      1493 ,      1604 ,      1723 ,
    1848 ,      1984 ,      2120 ,      2248 ,      2368 ,      2484 ,      2592 ,      2699 ,
    2751 ,      2803 ,      2855 ,      2904 ,      2953 ,      3004 ,      3052 ,      3100 ,
    3148 ,      3196 ,      3243 ,      3288 ,      3336 ,      3383 ,      3428 ,      3473 ,
    3520 ,      3565 ,      3611 ,      3656 ,      3701 ,      3744 ,      3761 ,      3760 ,
    3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,

} ;

static const HI_U16 HDR2HLGtypc_ylutfull[TM_LUT_SIZE] = //12bit
{
    0 ,        26 ,        46 ,        62 ,        81 ,        99 ,       116 ,       135 ,
    154 ,       172 ,       192 ,       212 ,       232 ,       254 ,       275 ,       323 ,
    370 ,       419 ,       472 ,       530 ,       589 ,       653 ,       719 ,       791 ,
    865 ,       945 ,      1026 ,      1114 ,      1208 ,      1304 ,      1408 ,      1515 ,
    1630 ,      1750 ,      1877 ,      2014 ,      2152 ,      2280 ,      2404 ,      2519 ,
    2636 ,      2743 ,      2850 ,      2953 ,      3057 ,      3154 ,      3254 ,      3350 ,
    3446 ,      3537 ,      3633 ,      3724 ,      3816 ,      3906 ,      3997 ,      4082 ,
    4088 ,      4092 ,      4093 ,      4093 ,      4093 ,      4092 ,      4092 ,      4092 ,
};

static const HI_U16 HDR2HLGtypc_satlutlimit[SatM_LUT_SIZE] =   // 10bit
{

    102 ,       102 ,       102 ,       102 ,       102 ,       119 ,       133 ,       144 ,
    154 ,       164 ,       179 ,       202 ,       229 ,       257 ,       282 ,       307 ,
    333 ,       360 ,       389 ,       416 ,       443 ,       467 ,       489 ,       509 ,
    525 ,       538 ,       545 ,       548 ,       548 ,       546 ,       543 ,       540 ,
    537 ,       536 ,       536 ,       537 ,       538 ,       538 ,       537 ,       537 ,
    538 ,       539 ,       539 ,       535 ,       527 ,       515 ,       499 ,       479 ,
    457 ,       434 ,       410 ,       385 ,       361 ,       338 ,       316 ,       294 ,
    275 ,       257 ,       241 ,       227 ,       216 ,       208 ,       204 ,       202 ,
    205 ,
} ;

static const HI_U16 HDR2HLGtypc_satlutfull[SatM_LUT_SIZE] =   // 10bit
{
    256 ,       290 ,       321 ,       348 ,       372 ,       393 ,       411 ,       427 ,
    441 ,       453 ,       464 ,       473 ,       482 ,       489 ,       496 ,       504 ,
    511 ,       518 ,       527 ,       536 ,       546 ,       558 ,       571 ,       586 ,
    600 ,       613 ,       623 ,       631 ,       639 ,       646 ,       656 ,       668 ,
    683 ,       700 ,       718 ,       733 ,       745 ,       752 ,       751 ,       743 ,
    723 ,       692 ,       647 ,       586 ,       508 ,       416 ,       329 ,       270 ,
    253 ,       256 ,       252 ,       244 ,       239 ,       237 ,       235 ,       234 ,
    233 ,       232 ,       231 ,       231 ,       231 ,       230 ,       230 ,       230 ,
    230 ,
} ;

/*********************** HLG2SDR ***********************************/

static const HI_U16 HLG2SDRtypc_ylutlim[TM_LUT_SIZE] = //12bit
{
    256 ,       256 ,       273 ,       292 ,       312 ,       332 ,       375 ,       418 ,
    463 ,       508 ,       555 ,       601 ,       648 ,       696 ,       744 ,       792 ,
    841 ,       890 ,       938 ,       988 ,      1037 ,      1086 ,      1136 ,      1185 ,
    1235 ,      1284 ,      1333 ,      1383 ,      1432 ,      1481 ,      1530 ,      1580 ,
    1632 ,      1688 ,      1747 ,      1809 ,      1875 ,      1945 ,      2017 ,      2094 ,
    2173 ,      2256 ,      2343 ,      2432 ,      2524 ,      2618 ,      2715 ,      2813 ,
    2912 ,      3012 ,      3111 ,      3208 ,      3304 ,      3396 ,      3484 ,      3567 ,
    3643 ,      3713 ,      3721 ,      3729 ,      3737 ,      3745 ,      3752 ,      3760 ,
} ;

static const HI_U16 HLG2SDRtypc_ylutfull[TM_LUT_SIZE] = //12bit
{
    0 ,        17 ,        35 ,        55 ,        75 ,        96 ,       117 ,       138 ,
    160 ,       182 ,       204 ,       226 ,       249 ,       272 ,       294 ,       317 ,
    341 ,       364 ,       387 ,       411 ,       434 ,       458 ,       482 ,       577 ,
    674 ,       772 ,       870 ,       968 ,      1067 ,      1166 ,      1265 ,      1364 ,
    1462 ,      1562 ,      1671 ,      1791 ,      1923 ,      2066 ,      2143 ,      2222 ,
    2304 ,      2389 ,      2477 ,      2567 ,      2660 ,      2754 ,      2850 ,      2948 ,
    3047 ,      3146 ,      3246 ,      3345 ,      3442 ,      3538 ,      3631 ,      3721 ,
    3807 ,      3888 ,      3964 ,      4033 ,      4065 ,      4092 ,      4092 ,      4092 ,
} ;

static const HI_U16 HLG2SDRtypc_satlutlimit[SatM_LUT_SIZE] =   // 10bit
{
    216 ,       221 ,       225 ,       228 ,       230 ,       232 ,       234 ,       235 ,
    236 ,       236 ,       237 ,       237 ,       237 ,       237 ,       238 ,       238 ,
    239 ,       240 ,       240 ,       241 ,       241 ,       241 ,       241 ,       242 ,
    244 ,       246 ,       248 ,       250 ,       251 ,       250 ,       248 ,       247 ,
    248 ,       253 ,       261 ,       274 ,       290 ,       308 ,       329 ,       350 ,
    371 ,       392 ,       412 ,       430 ,       445 ,       460 ,       472 ,       483 ,
    493 ,       502 ,       510 ,       517 ,       524 ,       530 ,       536 ,       541 ,
    547 ,       552 ,       558 ,       565 ,       572 ,       580 ,       588 ,       598 ,
    609 ,
} ;

static const HI_U16 HLG2SDRtypc_satlutfull[SatM_LUT_SIZE] =   // 10bit
{
    230 ,       232 ,       234 ,       235 ,       236 ,       236 ,       236 ,       237 ,
    237 ,       237 ,       237 ,       237 ,       238 ,       238 ,       239 ,       240 ,
    240 ,       241 ,       241 ,       241 ,       241 ,       242 ,       242 ,       244 ,
    246 ,       248 ,       250 ,       251 ,       251 ,       249 ,       248 ,       247 ,
    248 ,       252 ,       259 ,       269 ,       282 ,       297 ,       314 ,       332 ,
    351 ,       370 ,       388 ,       406 ,       422 ,       436 ,       450 ,       462 ,
    473 ,       482 ,       491 ,       499 ,       507 ,       513 ,       519 ,       525 ,
    530 ,       535 ,       540 ,       545 ,       550 ,       555 ,       560 ,       566 ,
    572 ,
} ;

/*********************** sdr2hlg ***********************************/

static const HI_U16 sdr2hlgtypc_ylutlim[TM_LUT_SIZE] = //12bit
{
    256 ,       256 ,       291 ,       325 ,       359 ,       392 ,       458 ,       523 ,
    587 ,       650 ,       712 ,       775 ,       837 ,       900 ,       964 ,      1028 ,
    1094 ,      1161 ,      1230 ,      1301 ,      1374 ,      1450 ,      1528 ,      1608 ,
    1689 ,      1772 ,      1854 ,      1935 ,      2016 ,      2094 ,      2171 ,      2246 ,
    2321 ,      2397 ,      2474 ,      2553 ,      2635 ,      2720 ,      2807 ,      2893 ,
    2974 ,      3050 ,      3116 ,      3171 ,      3218 ,      3258 ,      3294 ,      3328 ,
    3363 ,      3400 ,      3442 ,      3487 ,      3534 ,      3581 ,      3627 ,      3670 ,
    3708 ,      3741 ,      3744 ,      3748 ,      3751 ,      3754 ,      3757 ,      3759 ,
} ;

static const HI_U16 sdr2hlgtypc_ylutfull[TM_LUT_SIZE] = //12bit
{
    0 ,        35 ,        69 ,       103 ,       137 ,       170 ,       203 ,       236 ,
    268 ,       301 ,       333 ,       365 ,       396 ,       428 ,       459 ,       491 ,
    522 ,       553 ,       584 ,       616 ,       647 ,       678 ,       710 ,       837 ,
    967 ,      1102 ,      1243 ,      1392 ,      1550 ,      1713 ,      1877 ,      2039 ,
    2195 ,      2346 ,      2497 ,      2652 ,      2817 ,      2990 ,      3076 ,      3158 ,
    3235 ,      3305 ,      3366 ,      3419 ,      3464 ,      3504 ,      3540 ,      3575 ,
    3609 ,      3644 ,      3683 ,      3725 ,      3770 ,      3817 ,      3865 ,      3911 ,
    3956 ,      3998 ,      4035 ,      4068 ,      4081 ,      4090 ,      4090 ,      4090 ,
} ;

/*********************** slf2sdrtypical ***********************************/
static const HI_U16 slf2sdrtypc_ylutlim[TM_LUT_SIZE] = //12bit
{
    256 ,       257 ,       271 ,       274 ,       277 ,       282 ,       292 ,       306 ,
    322 ,       341 ,       364 ,       390 ,       421 ,       455 ,       493 ,       535 ,
    582 ,       633 ,       689 ,       750 ,       817 ,       889 ,       968 ,      1053 ,
    1146 ,      1245 ,      1351 ,      1464 ,      1585 ,      1712 ,      1845 ,      1985 ,
    2129 ,      2277 ,      2428 ,      2580 ,      2732 ,      2881 ,      3026 ,      3164 ,
    3293 ,      3411 ,      3516 ,      3606 ,      3681 ,      3740 ,      3760 ,      3760 ,
    3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,
    3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,

};

static const HI_U16 slf2sdrtypc_ylutfull[TM_LUT_SIZE] = //12bit
{
    1 ,        16 ,        20 ,        23 ,        27 ,        32 ,        37 ,        42 ,
    49 ,        55 ,        63 ,        71 ,        80 ,        89 ,        99 ,       110 ,
    122 ,       134 ,       147 ,       161 ,       176 ,       192 ,       208 ,       283 ,
    372 ,       476 ,       597 ,       738 ,       900 ,      1085 ,      1294 ,      1528 ,
    1784 ,      2062 ,      2355 ,      2658 ,      2961 ,      3253 ,      3391 ,      3521 ,
    3642 ,      3752 ,      3850 ,      3936 ,      4008 ,      4066 ,      4092 ,      4092 ,
    4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,
    4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,
};

static const HI_U16 slf2sdrtypc_satlutlimit[SatM_LUT_SIZE] =   // 10bit
{
    42 ,        67 ,        84 ,        96 ,       102 ,       106 ,       108 ,       110 ,
    113 ,       120 ,       130 ,       146 ,       170 ,       203 ,       248 ,       304 ,
    358 ,       382 ,       385 ,       385 ,       394 ,       411 ,       433 ,       459 ,
    486 ,       511 ,       533 ,       549 ,       560 ,       568 ,       575 ,       581 ,
    590 ,       602 ,       618 ,       637 ,       659 ,       685 ,       713 ,       741 ,
    768 ,       792 ,       811 ,       826 ,       836 ,       844 ,       850 ,       856 ,
    862 ,       867 ,       870 ,       873 ,       875 ,       875 ,       875 ,       875 ,
    874 ,       873 ,       871 ,       870 ,       869 ,       869 ,       868 ,       869 ,
    871 ,
} ;

static const HI_U16 slf2sdrtypc_satlutfull[SatM_LUT_SIZE] =   // 10bit
{
    102 ,       106 ,       108 ,       109 ,       112 ,       115 ,       122 ,       132 ,
    146 ,       167 ,       194 ,       230 ,       275 ,       327 ,       368 ,       383 ,
    385 ,       384 ,       391 ,       404 ,       422 ,       443 ,       466 ,       490 ,
    512 ,       531 ,       546 ,       557 ,       565 ,       571 ,       576 ,       583 ,
    590 ,       601 ,       614 ,       630 ,       648 ,       670 ,       693 ,       718 ,
    742 ,       766 ,       787 ,       805 ,       820 ,       830 ,       838 ,       845 ,
    850 ,       856 ,       861 ,       865 ,       869 ,       872 ,       874 ,       875 ,
    875 ,       875 ,       875 ,       874 ,       873 ,       872 ,       871 ,       870 ,
    869 ,
} ;

/*********************** slf2hdr10typical ***********************************/
static const HI_U16 slf2hdr10typc_ylutlim[TM_LUT_SIZE] = //12bit
{
    256 ,       257 ,       282 ,       288 ,       297 ,       306 ,       330 ,       360 ,
    395 ,       436 ,       481 ,       532 ,       587 ,       646 ,       708 ,       773 ,
    841 ,       911 ,       982 ,      1055 ,      1128 ,      1203 ,      1277 ,      1352 ,
    1427 ,      1502 ,      1577 ,      1651 ,      1724 ,      1797 ,      1869 ,      1941 ,
    2011 ,      2081 ,      2150 ,      2219 ,      2286 ,      2353 ,      2419 ,      2484 ,
    2549 ,      2613 ,      2676 ,      2739 ,      2802 ,      2864 ,      2927 ,      2989 ,
    3052 ,      3115 ,      3179 ,      3244 ,      3311 ,      3379 ,      3450 ,      3525 ,
    3604 ,      3690 ,      3701 ,      3713 ,      3724 ,      3736 ,      3748 ,      3760 ,
};

static const HI_U16 slf2hdr10typc_ylutfull[TM_LUT_SIZE] = //12bit
{
    2 ,        28 ,        35 ,        43 ,        52 ,        62 ,        74 ,        87 ,
    100 ,       116 ,       132 ,       150 ,       168 ,       188 ,       209 ,       232 ,
    255 ,       279 ,       305 ,       331 ,       358 ,       386 ,       415 ,       538 ,
    671 ,       811 ,       956 ,      1104 ,      1254 ,      1404 ,      1553 ,      1700 ,
    1846 ,      1989 ,      2129 ,      2267 ,      2402 ,      2534 ,      2599 ,      2664 ,
    2728 ,      2792 ,      2855 ,      2918 ,      2981 ,      3043 ,      3106 ,      3168 ,
    3231 ,      3294 ,      3357 ,      3421 ,      3486 ,      3552 ,      3620 ,      3690 ,
    3763 ,      3839 ,      3919 ,      4005 ,      4050 ,      4092 ,      4092 ,      4092 ,
};

static const HI_U16 slf2hdr10typc_satlutlimit[SatM_LUT_SIZE] =   // 10bit
{
    140 ,       140 ,       140 ,       140 ,       140 ,       162 ,       190 ,       220 ,
    242 ,       253 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,
};

static const HI_U16 slf2hdr10typc_satlutfull[SatM_LUT_SIZE] =   // 10bit
{
    134 ,       160 ,       185 ,       210 ,       232 ,       246 ,       254 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       255 ,       255 ,       255 ,       255 ,
    255 ,       255 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,       256 ,
    256 ,
};

/*********************** slf2hlgtypical ***********************************/
static const HI_U16 slf2hlgtypc_ylutlim[TM_LUT_SIZE] = //12bit
{
    256 ,       258 ,       278 ,       281 ,       287 ,       292 ,       304 ,       321 ,
    341 ,       365 ,       392 ,       421 ,       457 ,       497 ,       540 ,       592 ,
    647 ,       708 ,       775 ,       848 ,       928 ,      1015 ,      1108 ,      1211 ,
    1320 ,      1437 ,      1564 ,      1697 ,      1841 ,      1995 ,      2147 ,      2287 ,
    2416 ,      2541 ,      2657 ,      2768 ,      2877 ,      2980 ,      3080 ,      3176 ,
    3272 ,      3365 ,      3457 ,      3547 ,      3635 ,      3724 ,      3760 ,      3760 ,
    3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,
    3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,      3760 ,
};

static const HI_U16 slf2hlgtypc_ylutfull[TM_LUT_SIZE] = //12bit
{
    2 ,        24 ,        28 ,        33 ,        38 ,        45 ,        51 ,        56 ,
    64 ,        72 ,        84 ,        93 ,       103 ,       115 ,       127 ,       139 ,
    153 ,       168 ,       180 ,       199 ,       217 ,       234 ,       254 ,       339 ,
    446 ,       569 ,       716 ,       885 ,      1078 ,      1296 ,      1545 ,      1822 ,
    2128 ,      2412 ,      2664 ,      2894 ,      3109 ,      3310 ,      3406 ,      3502 ,
    3598 ,      3689 ,      3780 ,      3868 ,      3957 ,      4045 ,      4093 ,      4092 ,
    4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,
    4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,      4092 ,
};

static const HI_U16 slf2hlgtypc_satlutlimit[SatM_LUT_SIZE] =   // 10bit
{
    618 ,       502 ,       404 ,       322 ,       256 ,       205 ,       167 ,       141 ,
    127 ,       124 ,       130 ,       145 ,       166 ,       194 ,       228 ,       265 ,
    306 ,       349 ,       392 ,       434 ,       474 ,       511 ,       543 ,       569 ,
    589 ,       603 ,       614 ,       623 ,       632 ,       641 ,       651 ,       666 ,
    684 ,       704 ,       723 ,       740 ,       751 ,       754 ,       746 ,       725 ,
    689 ,       634 ,       558 ,       460 ,       355 ,       278 ,       254 ,       256 ,
    250 ,       242 ,       238 ,       236 ,       234 ,       233 ,       232 ,       231 ,
    231 ,       231 ,       230 ,       230 ,       230 ,       230 ,       231 ,       231 ,
    230 ,
} ;

static const HI_U16 slf2hlgtypc_satlutfull[SatM_LUT_SIZE] =   // 10bit
{
    256 ,       210 ,       175 ,       149 ,       133 ,       125 ,       125 ,       132 ,
    145 ,       163 ,       187 ,       215 ,       247 ,       281 ,       317 ,       355 ,
    392 ,       429 ,       465 ,       498 ,       528 ,       554 ,       575 ,       591 ,
    604 ,       613 ,       621 ,       629 ,       636 ,       645 ,       655 ,       668 ,
    684 ,       702 ,       719 ,       735 ,       747 ,       753 ,       753 ,       744 ,
    724 ,       693 ,       647 ,       586 ,       508 ,       416 ,       329 ,       270 ,
    253 ,       256 ,       252 ,       244 ,       239 ,       237 ,       235 ,       234 ,
    233 ,       232 ,       231 ,       231 ,       231 ,       230 ,       230 ,       230 ,
    230 ,
} ;

static HI_S32 LoadLut(HI_U32 *reg, const HI_U16 *lut, HI_U32 u32Size)
{
    HI_U32 u32Index;

    for (u32Index = 0; u32Index < u32Size / 2; u32Index++)
    {
        *(reg + u32Index) = ((*(lut + u32Index * 2) & 0xffff) << 16) +  (*(lut + u32Index * 2 + 1) & 0xffff);
    }

    if (0 != u32Size % 2)
    {
        *(reg + u32Size - 1) = *(lut + u32Size - 1);
    }
    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetLCHDR_HDR2HDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en           = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

    pstVpssReg->VPSS_CTRL.bits.hdr_in                   = HI_TRUE;

    if (HI_TRUE == sg_bHalProcessEn)
    {
        HI_ERR_PQ("Cannot Support Now!\n");
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetLCHDR_HDR2SDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    /* LCHDR en control */
    pstVpssReg->VPSS_CTRL.bits.hdr_in                   = HI_TRUE;

    /*
    if (set == 0)
        reg = 0
    else if(proc == 1)
        reg = reg_process
     else
        reg = 0
    */
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en           = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;


    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen         = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen       = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen    = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen        = HI_TRUE;

    /* 当前处理是按照 输入limit->limit, full->full  处理的*/
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_FALSE;   /* limit/full 表示输入源 */
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_TRUE;   /* limit/full 表示输入源 */
    }

    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale  = 13;

    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 5461;
    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 8192;

    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 3;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 1;

    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 52;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 6;

    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;
    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 96;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 928;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 940;

    /* Dither */
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

    if (1 == pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt)
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, hdr102sdrtypc_ylutfull, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, hdr102sdrtypc_satlutfull, SatM_LUT_SIZE);
    }
    else
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, hdr102sdrtypc_ylutlim, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, hdr102sdrtypc_satlutlimit, SatM_LUT_SIZE);
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetLCHDR_HDR2HLGCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_CTRL.bits.hdr_in                   = HI_TRUE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en            = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen          = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen        = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen     = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen         = HI_TRUE;

    /* 当前处理是按照 输入limit->limit, full->full  处理的*/
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_FALSE;   /* limit/full 表示输入源 */
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_TRUE;   /* limit/full 表示输入源 */
    }

    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 7373;
    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 8192;

    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale = 13;

    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 8;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 3;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;

    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 1;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 23;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 30;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;

    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 544;
    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;

    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 984;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 728;

    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

    if (1 == pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt)
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, HDR2HLGtypc_ylutfull, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, HDR2HLGtypc_satlutfull, SatM_LUT_SIZE);
    }
    else
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, HDR2HLGtypc_ylutlim, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, HDR2HLGtypc_satlutlimit, SatM_LUT_SIZE);
    }

    return HI_SUCCESS;
}

HI_S32 pq_hal_GetLCHDR_HLG2SDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_CTRL.bits.hdr_in                 = HI_TRUE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en         = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen       = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen     = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen  = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen      = HI_TRUE;

    /* 当前处理是按照 输入limit->limit, full->full  处理的*/
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_FALSE;   /* limit/full 表示输入源 */
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_TRUE;   /* limit/full 表示输入源 */
    }

    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 8192;
    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 13107;

    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale = 13;

    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 1;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 3;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;

    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 6;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 52;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;

    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 96;
    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;

    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 940;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 928;

    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

    if (1 == pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt)
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, HLG2SDRtypc_ylutfull, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, HLG2SDRtypc_satlutfull, SatM_LUT_SIZE);
    }
    else
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, HLG2SDRtypc_ylutlim, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, HLG2SDRtypc_satlutlimit, SatM_LUT_SIZE);
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetLCHDR_HLG2HDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_CTRL.bits.hdr_in                = HI_TRUE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en        = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen      = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen    = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen = HI_FALSE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen     = HI_TRUE;

    /* 当前处理是按照 输入limit->limit, full->full  处理的*/
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_FALSE;   /* limit/full 表示输入源 */
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_TRUE;   /* limit/full 表示输入源 */
    }

    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 4506;
    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 4096;

    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale = 13;

    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 1;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 3;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;

    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 6;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 52;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;

    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 96;
    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;

    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 940;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 928;

    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

    if (1 == pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt)
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, hlg2hdr10typc_ylutfull, TM_LUT_SIZE);
    }
    else
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, hlg2hdr10typc_ylutlim, TM_LUT_SIZE);
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetLCHDR_HLG2HLGCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_CTRL.bits.hdr_in          = HI_TRUE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en  = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

    if (HI_TRUE == sg_bHalProcessEn)
    {
        HI_ERR_PQ("Cannot Support Now!\n");
    }

    return HI_SUCCESS;
}


static HI_S32 pq_hal_GetLCHDR_SLF2SDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_CTRL.bits.hdr_in                = HI_TRUE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en        = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen      = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen    = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen     = HI_TRUE;

    /* 当前处理是按照 输入limit->limit, full->full  处理的*/
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_FALSE;   /* limit/full 表示输入源 */
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_TRUE;   /* limit/full 表示输入源 */
    }

    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 6553;
    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 8192;

    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale = 13;

    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 1;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 3;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;

    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 6;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 52;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;

    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 96;
    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;

    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 940;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 928;

    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

    if (1 == pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt)
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, slf2sdrtypc_ylutfull, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, slf2sdrtypc_satlutfull, SatM_LUT_SIZE);
    }
    else
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, slf2sdrtypc_ylutlim, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, slf2sdrtypc_satlutlimit, SatM_LUT_SIZE);
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetLCHDR_SLF2HDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_CTRL.bits.hdr_in                   = HI_TRUE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en        = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen      = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen    = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen     = HI_FALSE;

    /* 当前处理是按照 输入limit->limit, full->full  处理的*/
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_FALSE;   /* limit/full 表示输入源 */
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_TRUE;   /* limit/full 表示输入源 */
    }

    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 8192;
    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 8192;

    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale = 13;

    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 1;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 3;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;

    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 6;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 52;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;

    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 96;
    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;

    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 940;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 928;

    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

    if (1 == pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt)
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, slf2hdr10typc_ylutfull, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, slf2hdr10typc_satlutfull, SatM_LUT_SIZE);
    }
    else
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, slf2hdr10typc_ylutlim, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, slf2hdr10typc_satlutlimit, SatM_LUT_SIZE);
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetLCHDR_SLF2HLGCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    HI_ERR_PQ("Cannot Support Now!\n");

    return HI_FAILURE;
}

static HI_S32 pq_hal_GetLCHDR_SDR2HDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_CTRL.bits.hdr_in                = HI_FALSE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en        = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen      = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen    = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen = HI_FALSE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen     = HI_TRUE;

    /* 当前处理是按照 输入limit->limit, full->full  处理的*/
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_FALSE;   /* limit/full 表示输入源 */
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_TRUE;   /* limit/full 表示输入源 */
    }

    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 3523;
    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 0;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 3523;

    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale = 13;

    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 1;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 3;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;

    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 6;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 52;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;

    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 96;
    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;

    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 940;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 928;

    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

    if (1 == pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt)
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, sdr2hdr10typc_ylutful, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, sdr2hdr10typc_satlutful, SatM_LUT_SIZE);
    }
    else
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, sdr2hdr10typc_ylutlim, TM_LUT_SIZE);
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_SMAP_LUT0, sdr2hdr10typc_satlutlimit, SatM_LUT_SIZE);
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetLCHDR_SDR2HLGCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_CTRL.bits.hdr_in                = HI_FALSE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en        = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen      = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen    = HI_TRUE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen = HI_FALSE;
    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen     = HI_TRUE;

    /* 当前处理是按照 输入limit->limit, full->full  处理的*/
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_FALSE;   /* limit/full 表示输入源 */
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_TRUE;   /* limit/full 表示输入源 */
    }

    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 7164;
    pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = -67;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 104;
    pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 4632;

    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale = 13;

    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 1;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 3;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;

    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 6;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 52;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;

    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 96;
    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;

    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 940;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 928;

    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

    if (1 == pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt)
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, sdr2hlgtypc_ylutfull, TM_LUT_SIZE);
    }
    else
    {
        LoadLut((HI_U32 *)&pstVpssReg->VPSS_LCHDR_TMAP_LUT0, sdr2hlgtypc_ylutlim, TM_LUT_SIZE);
    }

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetLCHDR_SDR2SDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    pstVpssReg->VPSS_CTRL.bits.hdr_in                = HI_FALSE;

    if (enInCS == enOutCS)
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en        = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen      = HI_FALSE;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen    = HI_FALSE;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen = HI_FALSE;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen     = HI_FALSE;
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_en        = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;

        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_tmen      = HI_FALSE;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_dithen    = HI_TRUE;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_satmapyen = HI_FALSE;
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_cscen     = HI_TRUE;
    }

    /* 当前处理是按照 输入limit->limit, full->full  处理的*/
    if ((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_LIMITED == enInCS))
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_FALSE;   /* limit/full 表示输入源 */
    }
    else
    {
        pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_fullorlimt   = HI_TRUE;   /* limit/full 表示输入源 */
    }

    if (((HI_DRV_CS_BT2020_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT2020_YUV_FULL == enInCS))
        && ((HI_DRV_CS_BT709_YUV_LIMITED == enOutCS) || (HI_DRV_CS_BT709_YUV_FULL == enOutCS)))
    {
        pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 9364;
        pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = 135;
        pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = -209;
        pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 14485;
    }
    else if (((HI_DRV_CS_BT709_YUV_LIMITED == enInCS) || (HI_DRV_CS_BT709_YUV_FULL == enInCS))
             && ((HI_DRV_CS_BT2020_YUV_LIMITED == enOutCS) || (HI_DRV_CS_BT2020_YUV_FULL == enOutCS)))
    {
        pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef11 = 7164;
        pstVpssReg->VPSS_LCHDR_CSC_COEF0.bits.lchdr_csc_coef12 = -67;
        pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef21 = 104;
        pstVpssReg->VPSS_LCHDR_CSC_COEF1.bits.lchdr_csc_coef22 = 4632;
    }

    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_satsclcoef = 8;
    pstVpssReg->VPSS_LCHDR_SCALE2P.bits.lchdr_csc_scale = 13;

    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x4_step = 1;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x3_step = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x2_step = 3;
    pstVpssReg->VPSS_LCHDR_TMAP_STEP.bits.gmm_x1_step = 6;

    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x4_num = 6;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x3_num = 52;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x2_num = 4;
    pstVpssReg->VPSS_LCHDR_TMAP_NUM.bits.gmm_x1_num = 1;

    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x2_pos = 96;
    pstVpssReg->VPSS_LCHDR_TMAP_POS0.bits.gmm_x1_pos = 64;

    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x4_pos = 940;
    pstVpssReg->VPSS_LCHDR_TMAP_POS1.bits.gmm_x3_pos = 928;

    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_domain_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_tap_mode = 0;
    pstVpssReg->VPSS_LCHDR_DITHER_FUNC.bits.lchdr_dither_round_unlim = 0;

    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_max = 65535;
    pstVpssReg->VPSS_LCHDR_DITHER_THR.bits.lchdr_dither_thr_min = 0;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetLCHDREn(HI_U32 u32HandleNo, HI_BOOL bEnable)
{
    S_CAS_REGS_TYPE *pstVirReg = HI_NULL;

    pstVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVirReg);

    if (HI_FALSE == bEnable)
    {
        pstVirReg->VPSS_LCHDR_CTRL.bits.lchdr_en = HI_FALSE;
        sg_bHalSetEn = HI_FALSE;
    }
    else
    {
        pstVirReg->VPSS_LCHDR_CTRL.bits.lchdr_en = (sg_bHalSetEn & sg_bHalProcessEn) ? HI_TRUE : HI_FALSE;
        sg_bHalSetEn = HI_TRUE;
    }

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetLCHDREn(HI_BOOL *pbEnable)
{
    *pbEnable = sg_bHalSetEn & sg_bHalProcessEn;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetLCHDRDemoEn(HI_U32 u32HandleNo, HI_BOOL bEnable)
{
    S_CAS_REGS_TYPE *pstVirReg = HI_NULL;

    pstVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVirReg);
    pstVirReg->VPSS_LCHDR_CTRL.bits.lchdr_demo_en = bEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetLCHDRDemoMode(HI_U32 u32HandleNo, PQ_DEMO_MODE_E enMode)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssReg);

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_demo_mode = (HI_U32)enMode;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetLCHDRDemoPos(HI_U32 u32HandleNo, HI_U32 u32XPos)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssReg);

    pstVpssReg->VPSS_LCHDR_CTRL.bits.lchdr_demo_pos = u32XPos;

    return HI_SUCCESS;
}

PF_PQ_Hal_GetLCHdrPathCfg pfPqHalGetLCHDRPathCfg[HI_PQ_HDR_MODE_BUTT] =
{
    pq_hal_GetLCHDR_HDR2SDRCfg,
    pq_hal_GetLCHDR_HDR2HDRCfg,
    pq_hal_GetLCHDR_HDR2HLGCfg,

    pq_hal_GetLCHDR_HLG2SDRCfg,
    pq_hal_GetLCHDR_HLG2HDRCfg,
    pq_hal_GetLCHDR_HLG2HLGCfg,

    pq_hal_GetLCHDR_SLF2SDRCfg,
    pq_hal_GetLCHDR_SLF2HDRCfg,
    pq_hal_GetLCHDR_SLF2HLGCfg,

    pq_hal_GetLCHDR_SDR2SDRCfg,
    pq_hal_GetLCHDR_SDR2HDRCfg,
    pq_hal_GetLCHDR_SDR2HLGCfg,
};

HI_S32 PQ_HAL_GetLCHDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    sg_enLCHDRMode = aenPqHalLCHDRPathMode[pstXdrFrameInfo->enSrcFrameType][pstXdrFrameInfo->enDispType];

    PQ_CHECK_OVER_RANGE_RE_FAIL(sg_enLCHDRMode, HI_PQ_HDR_MODE_BUTT);

    if (((HI_PQ_HDR_MODE_HDR10_TO_HDR10 == sg_enLCHDRMode)
         || (HI_PQ_HDR_MODE_HLG_TO_HLG == sg_enLCHDRMode)
         || (HI_PQ_HDR_MODE_SDR_TO_SDR == sg_enLCHDRMode))
        && (pstXdrFrameInfo->enInCS == pstXdrFrameInfo->enOutCS))
    {
        sg_bHalProcessEn = HI_FALSE;
    }
    else
    {
        sg_bHalProcessEn = HI_TRUE;
    }

    s32Ret  = pfPqHalGetLCHDRPathCfg[sg_enLCHDRMode](enLayerId, pstVpssReg, pstXdrFrameInfo->enInCS, pstXdrFrameInfo->enOutCS);

    return s32Ret;
}



