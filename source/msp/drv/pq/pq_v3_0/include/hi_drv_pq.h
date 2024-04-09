/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : hi_drv_pq.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2014/04/01
  Description   :
******************************************************************************/

#ifndef __HI_DRV_PQ_V3_H__
#define __HI_DRV_PQ_V3_H__

#include <linux/ioctl.h>
#include "hi_module.h"

#include "hi_type.h"
#include "hi_debug.h"
#include "drv_pq_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef PQ_PROC_CTRL_SUPPORT
#define HI_FATAL_PQ(fmt...) HI_TRACE(HI_LOG_LEVEL_FATAL, HI_ID_PQ, fmt)
#define HI_ERR_PQ(fmt...)   HI_TRACE(HI_LOG_LEVEL_ERROR, HI_ID_PQ, fmt)
#define HI_WARN_PQ(fmt...)  HI_TRACE(HI_LOG_LEVEL_WARNING, HI_ID_PQ, fmt)
#define HI_INFO_PQ(fmt...)  HI_TRACE(HI_LOG_LEVEL_INFO, HI_ID_PQ, fmt)
#define HI_DEBUG_PQ(fmt...) HI_TRACE(HI_LOG_LEVEL_DBG, HI_ID_PQ, fmt)
#else
#define HI_FATAL_PQ(fmt...)
#define HI_ERR_PQ(fmt...)
#define HI_WARN_PQ(fmt...)
#define HI_INFO_PQ(fmt...)
#define HI_DEBUG_PQ(fmt...)
#endif


/* PQ~{D#?i~} */
typedef enum hiHIPQ_MODULE_E
{
    HI_PQ_MODULE_FMD = 0      ,
    HI_PQ_MODULE_TNR          ,
    HI_PQ_MODULE_SNR          ,
    HI_PQ_MODULE_DB           ,
    HI_PQ_MODULE_DR           ,
    HI_PQ_MODULE_DM           ,
    HI_PQ_MODULE_DBM          ,
    HI_PQ_MODULE_SHARPNESS    ,
    HI_PQ_MODULE_DCI          ,
    HI_PQ_MODULE_COLOR        ,
    HI_PQ_MODULE_SR           ,
    HI_PQ_MODULE_CSC          ,
    HI_PQ_MODULE_ZME          ,
    HI_PQ_MODULE_DEI          ,
    HI_PQ_MODULE_DS           ,
    HI_PQ_MODULE_ARTDS        ,
    HI_PQ_MODULE_GFXCSC       ,
    HI_PQ_MODULE_GFXZME       ,
    HI_PQ_MODULE_ALL          ,

    HI_PQ_MODULE_BUTT
}  HI_PQ_MODULE_E;

/*~{AA6H~}/~{6T1H6H~}/~{I+5w~}/~{1%:M6HIh6(~}*/
typedef struct hiPQ_IMAGE_PARAM_S
{
    HI_U16 u16Brightness;
    HI_U16 u16Contrast;
    HI_U16 u16Hue;
    HI_U16 u16Saturation;

} HI_PQ_IMAGE_PARAM_S;

typedef enum hiPQ_HDR_MODE_E
{
    HI_PQ_HDR_MODE_HDR10_TO_SDR   = 0,
    HI_PQ_HDR_MODE_HDR10_TO_HDR10 = 1,
    HI_PQ_HDR_MODE_HDR10_TO_HLG   = 2,
    HI_PQ_HDR_MODE_HLG_TO_SDR     = 3,
    HI_PQ_HDR_MODE_HLG_TO_HDR10   = 4,
    HI_PQ_HDR_MODE_HLG_TO_HLG     = 5,
    HI_PQ_HDR_MODE_SLF_TO_SDR     = 6,
    HI_PQ_HDR_MODE_SLF_TO_HDR10   = 7,
    HI_PQ_HDR_MODE_SLF_TO_HLG     = 8,
    HI_PQ_HDR_MODE_SDR_TO_SDR     = 9,
    HI_PQ_HDR_MODE_SDR_TO_HDR10   = 10,
    HI_PQ_HDR_MODE_SDR_TO_HLG     = 11,

    HI_PQ_HDR_MODE_BUTT,
} HI_PQ_HDR_MODE_E;


typedef struct hiPQ_SETHDROFFSET_S
{
    HI_PQ_HDR_MODE_E enHdrProcessScene;
    HI_U32       u32HdrMode;
    HI_U32       u32Bright;
    HI_U32       u32Contrast;
    HI_U32       u32Satu;
    HI_U32       u32Hue;
    HI_U32       u32R;
    HI_U32       u32G;
    HI_U32       u32B;
    HI_U32       u32darkCv;
    HI_U32       u32brightCv;
    HI_U32       u32ACCdark;
    HI_U32       u32ACCbrigt;
} HI_PQ_SETHDROFFSET_S;
/*
 * ~{D#?i?*9XJtPT~}
 */
typedef struct hiPQ_MODULE_S
{
    HI_PQ_MODULE_E enModule;
    HI_U32 u32OnOff; /*~{?*9X~}*/
} HI_PQ_MODULE_S;

/*
 * ~{Bt3!D#J=JtPT~}
 */
typedef struct hiPQ_DEMO_S
{
    HI_PQ_MODULE_E enModule;
    HI_BOOL      bOnOff; /*~{?*9X~}*/
} HI_PQ_DEMO_S;

/* ~{Bt3!D#J=~} ~{OTJ>7=J=~}*/
typedef enum hiPQ_DEMO_MODE_E
{
    HI_PQ_DEMO_MODE_FIXED_R = 0,
    HI_PQ_DEMO_MODE_FIXED_L,
    HI_PQ_DEMO_MODE_SCROLL_R,
    HI_PQ_DEMO_MODE_SCROLL_L,

    HI_PQ_DEMO_MODE_BUTT
} HI_PQ_DEMO_MODE_E;

/*
 * ~{<D4fFwJtPT~}
 */
typedef struct hiPQ_REGISTER_S
{
    HI_U32 u32RegAddr;     /* register addr */
    HI_U8  u8Lsb;          /* register lsb */
    HI_U8  u8Msb;          /* register msb */
    HI_U8  u8SourceMode;   /* video source */
    HI_U8  u8OutputMode;   /* output mode */
    HI_U32 u32Module;      /* module */
    HI_U32 u32Value;       /* register value */
} HI_PQ_REGISTER_S;

/*ACM ~{<D4fFw?XVF2NJ}=a99~}*/
typedef struct hiPQ_COLOR_CTRL_S
{
    HI_U32 u32En;
    HI_U32 u32DbgEn;
    HI_U32 u32Stretch;
    HI_U32 u32Cliprange;
    HI_U32 u32Cliporwrap;
    HI_U32 u32Cbcrthr;
} HI_PQ_COLOR_CTRL_S;

/*ACM table~{=a99~}*/
typedef struct hiPQ_DRV_ACM_LUT_S
{
    HI_U32 u32LutType;           /*ACM ~{2iUR1mGzO_@`PM~}*/
    HI_S16 as16Lut[ACM_Y_NUM][ACM_S_NUM][ACM_H_NUM];   /*ACM ~{2iUR1m~}*/
} HI_PQ_ACM_LUT_S;

/*DCI~{GzO_EdVC1m~}*/
typedef struct hiPQ_DCI_WGT_S
{
    HI_S16 s16WgtCoef0[33];
    HI_S16 s16WgtCoef1[33];
    HI_S16 s16WgtCoef2[33];
    HI_U16 u16Gain0;
    HI_U16 u16Gain1;
    HI_U16 u16Gain2;
} HI_PQ_DCI_WGT_S;

/*DCI Black Stretch Lut*/
typedef struct hiPQ_DCI_BS_LUT_S
{
    HI_S16 s16BSDelta[320];
} HI_PQ_DCI_BS_LUT_S;

/*DCI~{V17=M<=a99~}*/
typedef struct hiPQ_DCI_HISTGRAM_S
{
    HI_S32 s32HistGram[32];
} HI_PQ_DCI_HISTGRAM_S;

typedef struct
{
    HI_U16  u16GammCoef[1024];
} HI_PQ_CSC_GAMM_PARA_S;

/*TNR~{M(SC=a99~}*/
typedef struct hiPQ_TNR_S
{
    HI_S32 s32MappingMax;
    HI_S32 s32MappingMin;
    HI_S32 s32MappingR[5];
    HI_S32 s32MappingT[6];
    HI_S32 s32MappingK[4];
} HI_PQ_TNR_S;

/* YFmotion ~{5DS3IdGzO_~}  */
typedef struct hiPQ_TNR_FMOTION_S
{
    HI_S16 s16YFmotion[32];
    HI_S16 s16CFmotion[32];
} HI_PQ_TNR_FMOTION_S;

/*SNR~{5D~}pixmean-ratio~{=a99~}*/
typedef struct hiPQ_SNR_PIXMEAN_2_RATIO_S
{
    HI_U8  u8EdgeMaxRatio;
    HI_U8  u8EdgeMinRatio;
    HI_U8  u8EdgeOriRatio;
    HI_U8  u8Reserve;
    HI_U16 u16EdgeMeanTh[8];
    HI_U8  u8EdgeMeanK[8];
    HI_U16 u16PixMeanRatio[8];
} HI_PQ_SNR_PIXMEAN_2_RATIO_S;

/*SNR ~{5D~}pixdiff-edgestr~{=a99~}*/
typedef struct hiPQ_SNR_PIXDIFF_2_EDGESTR_S
{
    HI_U8  u8EdgeOriStrength;
    HI_U8  u8EdgeMaxStrength;
    HI_U8  u8EdgeMinStrength;
    HI_U8  u8Reserve1;
    HI_U16 u16EdgeStrTh[3];
    HI_U16 u16Reserve2;
    HI_U8  u8EdgeStrK[3];
    HI_U8  u8Reserve3;
    HI_U8  u8EdgeStr[3];
    HI_U8  u8Reserve4;
} HI_PQ_SNR_PIXDIFF_2_EDGESTR_S;

typedef struct  hiPQ_SNR_MEAN_RATIO_S
{
    HI_S32 s32MappingMax;    /*meanedgeratio max~{S3Id1mWn4sV5~} 0~~127 */
    HI_S32 s32MappingMin;    /*meanedgeratio min~{S3Id1mWnP!V5~} 0~~127 */
    HI_S32 s32MappingX[6];   /*meanedgeratio X*/
    HI_S32 s32MappingY[5];   /*meanedgeratio Y*/
    HI_S32 s32MappingK[4];   /*meanedgeratio K*/

} HI_PQ_SNR_MEAN_RATIO_S;

typedef struct  hiPQ_SNR_EDGE_STR_S
{
    HI_S32 s32MappingMax;    /*edgestrmapping max~{S3Id1mWn4sV5~} 0~~63*/
    HI_S32 s32MappingMin;    /*edgestrmapping min~{S3Id1mWnP!V5~} 0~~63*/
    HI_S32 s32MappingX[8];   /*edgestrmapping X*/
    HI_S32 s32MappingY[7];   /*edgestrmapping Y*/
    HI_S32 s32MappingK[6];   /*edgestrmapping K*/

} HI_PQ_SNR_EDGE_STR_S;


/*SR~{Q]J>D#J=~}*/
typedef enum hiPQ_SR_DEMO_E
{
    HI_PQ_SR_DISABLE  = 0,/* ~{9X~}SR,~{V;~}ZME */
    HI_PQ_SR_ENABLE_R,    /* ~{SR1_~}SR */
    HI_PQ_SR_ENABLE_L,    /* ~{Ws1_~}SR */
    HI_PQ_SR_ENABLE_A,    /* ~{H+FA~} */

    HI_PQ_SR_DEMO_BUTT
} HI_PQ_SR_DEMO_E;

/*~{Ay;yI+TvG?2NJ}~}*/
typedef struct hiPQ_SIX_BASE_COLOR_S
{
    HI_U32  u32Red;         /* Range:0~~100 */
    HI_U32  u32Green;       /* Range:0~~100 */
    HI_U32  u32Blue;        /* Range:0~~100 */
    HI_U32  u32Cyan;        /* Range:0~~100 */
    HI_U32  u32Magenta;     /* Range:0~~100 */
    HI_U32  u32Yellow;      /* Range:0~~100 */
} HI_PQ_SIX_BASE_COLOR_S;

/*ACM GAIN ~{O{O"=a99~}*/
typedef struct hiPQ_COLOR_GAIN_S
{
    HI_U32 u32GainMode;   /* 0:SD;1:HD;2:UHD */
    HI_U32 u32Gainluma;   /* ~{1mJ>6T~}Hue~{5DTvRf#,~}Range:0-1023 */
    HI_U32 u32Gainhue;    /* ~{1mJ>6T~}Hue~{5DTvRf#,~}Range:0-1023 */
    HI_U32 u32Gainsat;    /* ~{1mJ>6T~}Luma~{5DTvRf~} */
} HI_PQ_COLOR_GAIN_S;

/*~{QUI+TvG?@`PM~}*/
typedef enum hiPQ_COLOR_ENHANCE_E
{
    HI_PQ_COLOR_ENHANCE_FLESHTONE = 0,    /* ~{7tI+TvG?~} */
    HI_PQ_COLOR_ENHANCE_SIX_BASE,         /* ~{Ay;yI+TvG?~},~{WT6(ReQUI+5DTvG?~} */
    HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE,  /* ~{9L6(D#J=5DQUI+TvG?D#J=~} */
    HI_PQ_COLOR_ENHANCE_BUTT
} HI_PQ_COLOR_ENHANCE_E;

/*~{7tI+TvRf2NJ}~}*/
typedef enum hiPQ_FLESHTONE_E
{
    HI_PQ_FLESHTONE_GAIN_OFF = 0,
    HI_PQ_FLESHTONE_GAIN_LOW,
    HI_PQ_FLESHTONE_GAIN_MID,
    HI_PQ_FLESHTONE_GAIN_HIGH,

    HI_PQ_FLESHTONE_GAIN_BUTT
}  HI_PQ_FLESHTONE_E;


/*~{QUI+TvG?@`PM~}*/
typedef enum hiPQ_COLOR_SPEC_MODE_E
{
    HI_PQ_COLOR_MODE_RECOMMEND = 0, /* ~{MF<v5DQUI+TvG?D#J=~} */
    HI_PQ_COLOR_MODE_BLUE      = 1, /* ~{9L6(5D@6I+TvG?D#J=~} */
    HI_PQ_COLOR_MODE_GREEN     = 2, /* ~{9L6(5DBLI+TvG?D#J=~} */
    HI_PQ_COLOR_MODE_BG        = 3, /* ~{9L6(5D@6BLI+TvG?D#J=~} */
    HI_PQ_COLOR_MODE_ORIGINAL  = 4, /* ~{T-J<QUI+D#J=~} */

    HI_PQ_COLOR_MODE_BUTT
} HI_PQ_COLOR_SPEC_MODE_E;

/*~{QUI+TvG?2NJ}~}*/
typedef struct  hiPQ_COLOR_ENHANCE_S
{
    HI_PQ_COLOR_ENHANCE_E    enColorEnhanceType; /* ~{I+2JTvG?@`PM~} */
    union
    {
        HI_PQ_FLESHTONE_E       enFleshtone;   /* ~{7tI+TvG?2NJ}~} */
        HI_PQ_SIX_BASE_COLOR_S  stSixBase;     /* ~{Ay;yI+TvG?2NJ}~} */
        HI_PQ_COLOR_SPEC_MODE_E enColorMode;   /* ~{9L6(5DQUI+TvG?D#J=~} */

    } unColorGain;
} HI_PQ_COLOR_ENHANCE_S;

typedef struct  hiPQ_COLORTEMPERATURE_S
{
    HI_U32  u32Red;       /**<Red; Range:0~~100 */ /**<CNcomment:~{:lI+#;76N'~}:0~~100 CNend*/
    HI_U32  u32Green;     /**<Green; Range:0~~100 */ /**<CNcomment:~{:lI+#;76N'~}:0~~100 CNend*/
    HI_U32  u32Blue;      /**<Blue; Range:0~~100 */ /**<CNcomment:~{:lI+#;76N'~}:0~~100 CNend*/
} HI_PQ_COLORTEMPERATURE_S;

typedef struct hiPQ_HDR_TM_LUT_S
{
    HI_S16 as16TMLutI[512];
    HI_S16 as16TMLutS[512];
    HI_S16 as16SMLutI[512];
    HI_S16 as16SMLutS[512];
} HI_PQ_HDR_TM_LUT_S;

typedef struct hiPQ_HDR_PARA_MODE_S
{
    HI_U32 u32HdrTmMode;
    HI_U32 u32HdrSmMode;
} HI_PQ_HDR_PARA_MODE_S;

typedef struct hiPQ_HDR_TMAP_S
{
    HI_U32 au32X_step[8];
    HI_U32 au32X_num[8];
    HI_U32 au32X_pos[8];
    HI_U32 au32Y_LUT[64];
} HI_PQ_HDR_TMAP_S;

typedef struct hiPQ_HDR_SMAP_S
{
    HI_U32 au32X_step[8];
    HI_U32 au32X_num[8];
    HI_U32 au32X_pos[8];
    HI_U32 au32Y_LUT[64]; /* 310 only 32 segment */
} HI_PQ_HDR_SMAP_S;

typedef struct hiPQ_GFXHDR_MODE_S
{
    HI_U32 u32HdrScene;     /* sdr2hdr:0; sdr2hlg:1 */
    HI_U32 u32ParaModeUse;   /*~{Q!Tq~}HDR~{2NJ}D#J=!#~}0:~{9L6(2NJ}#,~}1:~{9$>_5wJT2NJ}~}*/
} HI_PQ_GFXHDR_MODE_S;

typedef struct hiPQ_GFXHDR_STEP_S
{
    HI_U32 au32X_step[4];
    HI_U32 au32X_num[4];
    HI_U32 au32X_pos[4];
} HI_PQ_GFXHDR_STEP_S;

typedef struct hiPQ_GFXHDR_TMAP_S
{
    HI_U32 au32Clut[32];
} HI_PQ_GFXHDR_TMAP_S;

typedef struct hiPQ_HDR_ACM_MODE_S
{
    HI_U32 u32ParaModeUse;   /*~{Q!Tq~}HDR~{2NJ}D#J=!#~}0:~{9L6(2NJ}#,~}1:~{9$>_5wJT2NJ}~}*/
} HI_PQ_HDR_ACM_MODE_S;

typedef struct hiPQ_HDR_ACM_REGCFG_S
{
    HI_S32 as32Regcfg[PQ_HDR_ACM_REGCFG_SIZE];
} HI_PQ_HDR_ACM_REGCFG_S;

/* acc alg */
typedef struct HI_PQ_HDR_DYN_TM_TUNING_S
{
    // ~{PiDb<D4fFw#,~}PQ tool xml~{5w=Z~}
    HI_U32 u32MaxLumiDisplay;       //[0,100000000]~~[0,10000nits]

    HI_U32 u32DarkDetailGain;       //[0,4096]~~[0,4.0]
    HI_U32 u32DarkDetailGmm;        //[0,4096]~~[0,4.0]
    HI_U32 u32BrightDetailGain;     //[0,4096]~~[0,4.0]
    HI_U32 u32BrightDetailGmm;      //[0,4096]~~[0,4.0]
    HI_U32 u32DynTmGain;            //[0,4096]~~[0,4.0]
    HI_U32 u32DynTmGmm;             //[0,4096]~~[0,4.0]

    HI_U32 u32DarkSceneDynTM;       //[0,1024]~~[0,1.0]
    HI_U32 u32DarkLimit;            //[0,65536]
    HI_U32 u32BleachingLevel;       //[0,100]

	HI_U32 u32TemporalSmooth;		//[0,1024]~~[0,1.0] default:1024;
} HI_PQ_HDR_DYN_TM_TUNING_S;

typedef enum hiPQ_IMAGE_MODE_E
{
    HI_PQ_IMAGE_MODE_NORMAL     = 0,
    HI_PQ_IMAGE_MODE_VIDEOPHONE = 1,
    HI_PQ_IMAGE_MODE_GALLERY    = 2,

    HI_PQ_IMAGE_MODE_BUTT,
} HI_PQ_IMAGE_MODE_E;

typedef enum hiHI_DRV_PQ_VP_TYPE_E
{
    HI_DRV_PQ_VP_TYPE_NORMAL  = 0,  /* VPSS VideoPhone Normal */
    HI_DRV_PQ_VP_TYPE_PREVIEW = 1,  /* VPSS VideoPhone Preview */
    HI_DRV_PQ_VP_TYPE_REMOTE  = 2,  /* VPSS VideoPhone Remote */

    HI_DRV_PQ_VP_TYPE_BUTT
} HI_DRV_PQ_VP_TYPE_E;

typedef enum hiDRV_PQ_VIDEOPHONE_MODE_E
{
    HI_DRV_PQ_VIDEOPHONE_MODE_RECOMMEND = 0, /**<Optimization Model */ /**<CNcomment:~{WnSED#J=~} CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_BLACK     = 1, /**<BlackWhite Model */ /**<CNcomment:~{@6I+TvG?D#J=~} CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_COLORFUL  = 2, /**<Colorful Model */ /**<CNcomment:~{BLI+TvG?D#J=~} CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_BRIGHT    = 3, /**<Bright Model */ /**<CNcomment:~{@6BLTvG?D#J=~} CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_WARM      = 4, /**<Warm Model */ /**<CNcomment:~{T-J<QUI+D#J=~} CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_COOL      = 5, /**<Cool Model */ /**<CNcomment:~{T-J<QUI+D#J=~} CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_OLD       = 6, /**<Old Model */ /**<CNcomment:~{T-J<QUI+D#J=~} CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_USER      = 7, /**<Old Model */ /**<CNcomment:~{T-J<QUI+D#J=~} CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_BUTT
} HI_DRV_PQ_VP_MODE_E;

/*~{SC;'=S?Z~}*/

#define HIIOC_PQ_S_SD_BRIGHTNESS        _IOW(HI_ID_PQ, 3, HI_U32)                     /* ~{IhVC1jGe~}BRIGHTNESS level*/
#define HIIOC_PQ_G_SD_BRIGHTNESS        _IOWR(HI_ID_PQ, 4, HI_U32)                     /* ~{;qH!1jGe~}BRIGHTNESS level*/

#define HIIOC_PQ_S_SD_CONTRAST          _IOW(HI_ID_PQ, 5, HI_U32)                     /* ~{IhVC1jGe~}CONTRAST level*/
#define HIIOC_PQ_G_SD_CONTRAST          _IOWR(HI_ID_PQ, 6, HI_U32)                     /* ~{;qH!1jGe~}CONTRAST level*/

#define HIIOC_PQ_S_SD_SATURATION        _IOW(HI_ID_PQ, 7, HI_U32)                     /* ~{IhVC1jGe~}SATURATION level*/
#define HIIOC_PQ_G_SD_SATURATION        _IOWR(HI_ID_PQ, 8, HI_U32)                     /* ~{;qH!1jGe~}SATURATION level*/

#define HIIOC_PQ_S_SD_HUE               _IOW(HI_ID_PQ, 9, HI_U32)                     /* ~{IhVC1jGe~}HUE level*/
#define HIIOC_PQ_G_SD_HUE               _IOWR(HI_ID_PQ, 10, HI_U32)                    /* ~{;qH!1jGe~}HUE level*/

#define HIIOC_PQ_S_TNR                  _IOW(HI_ID_PQ, 11, HI_U32)                    /* ~{IhVC~}TNR level*/
#define HIIOC_PQ_G_TNR                  _IOWR(HI_ID_PQ, 12, HI_U32)                    /* ~{;qH!~}TNR level*/

#define HIIOC_PQ_S_SHARPNESS            _IOW(HI_ID_PQ, 13, HI_U32)                    /* ~{IhVC~}SHARPNESS level*/
#define HIIOC_PQ_G_SHARPNESS            _IOWR(HI_ID_PQ, 14, HI_U32)                    /* ~{;qH!~}SHARPNESS level*/

#define HIIOC_PQ_S_DB                   _IOW(HI_ID_PQ, 15, HI_U32)                    /* ~{IhVC~}De-blocking level*/
#define HIIOC_PQ_G_DB                   _IOWR(HI_ID_PQ, 16, HI_U32)                    /* ~{;qH!~}De-blocking level*/

#define HIIOC_PQ_S_DR                   _IOW(HI_ID_PQ, 17, HI_U32)                    /* ~{IhVC~}De-Ring level*/
#define HIIOC_PQ_G_DR                   _IOWR(HI_ID_PQ, 18, HI_U32)                    /* ~{;qH!~}De-Ring level*/

#define HIIOC_PQ_S_FLESHTONE            _IOW(HI_ID_PQ, 21, HI_PQ_FLESHTONE_E)         /* ~{IhVC~}FleshTone level*/
#define HIIOC_PQ_G_FLESHTONE            _IOWR(HI_ID_PQ, 22, HI_PQ_FLESHTONE_E)         /* ~{;qH!~}FleshTone level*/

#define HIIOC_PQ_S_MODULE               _IOW(HI_ID_PQ, 27, HI_PQ_MODULE_S)            /* ~{IhVC8wKc7(D#?i?*9X~}*/
#define HIIOC_PQ_G_MODULE               _IOWR(HI_ID_PQ, 28, HI_PQ_MODULE_S)           /* ~{;qH!8wKc7(D#?i?*9X~}*/

#define HIIOC_PQ_S_DEMO                 _IOW(HI_ID_PQ, 29, HI_PQ_DEMO_S)              /* ~{IhVC8wKc7(D#?iBt3!D#J=?*9X~}*/

#define HIIOC_PQ_S_SIXBASECOLOR         _IOW(HI_ID_PQ, 30, HI_PQ_SIX_BASE_COLOR_S)    /* ~{IhVC~} ~{Ay;yI+@`PM~}*/
#define HIIOC_PQ_G_SIXBASECOLOR         _IOWR(HI_ID_PQ, 31, HI_PQ_SIX_BASE_COLOR_S)    /* ~{;qH!Ay;yI+@`PM~}*/

#define HIIOC_PQ_S_SR_DEMO              _IOW(HI_ID_PQ, 35, HI_PQ_SR_DEMO_E)           /* ~{IhVC~}SR~{Q]J>D#J=~}*/
#define HIIOC_PQ_G_SR_DEMO              _IOWR(HI_ID_PQ, 36, HI_PQ_SR_DEMO_E)           /* ~{;qH!~}SR~{Q]J>D#J=~}*/

#define HIIOC_PQ_S_REGISTER             _IOW(HI_ID_PQ, 44, HI_PQ_REGISTER_S)          /* ~{P4<D4fFw~}*/
#define HIIOC_PQ_G_REGISTER             _IOWR(HI_ID_PQ, 45, HI_PQ_REGISTER_S)         /*~{6A<D4fFw~}*/

#define HIIOC_PQ_S_DCI                 _IOW(HI_ID_PQ, 48, HI_PQ_DCI_WGT_S)            /*~{P4~}DCI~{GzO_~}*/
#define HIIOC_PQ_G_DCI                 _IOWR(HI_ID_PQ, 49, HI_PQ_DCI_WGT_S)            /*~{6A~}DCI~{GzO_~}*/

#define HIIOC_PQ_S_ACM_GAIN            _IOW(HI_ID_PQ, 50, HI_PQ_COLOR_GAIN_S)         /*~{P4~}COLOR GAIN*/
#define HIIOC_PQ_G_ACM_GAIN            _IOWR(HI_ID_PQ, 51, HI_PQ_COLOR_GAIN_S)         /*~{6A~}COLOR GAIN*/

#define HIIOC_PQ_S_ACM_LUMA            _IOW(HI_ID_PQ, 52, HI_PQ_ACM_LUT_S)            /*~{P4~}COLOR LUMA~{GzO_~}*/
#define HIIOC_PQ_G_ACM_LUMA            _IOWR(HI_ID_PQ, 53, HI_PQ_ACM_LUT_S)            /*~{6A~}COLOR LUMA~{GzO_~}*/

#define HIIOC_PQ_S_ACM_HUE             _IOW(HI_ID_PQ, 54, HI_PQ_ACM_LUT_S)            /*~{P4~}COLOR HUE~{GzO_~}*/
#define HIIOC_PQ_G_ACM_HUE             _IOWR(HI_ID_PQ, 55, HI_PQ_ACM_LUT_S)            /*~{6A~}COLOR HUE~{GzO_~}*/

#define HIIOC_PQ_S_ACM_SAT             _IOW(HI_ID_PQ, 56, HI_PQ_ACM_LUT_S)            /*~{P4~}COLOR SAT~{GzO_~}*/
#define HIIOC_PQ_G_ACM_SAT             _IOWR(HI_ID_PQ, 57, HI_PQ_ACM_LUT_S)            /*~{6A~}COLOR SAT~{GzO_~}*/

#define HIIOC_PQ_G_DCI_HIST            _IOWR(HI_ID_PQ, 58, HI_PQ_DCI_HISTGRAM_S)       /*~{6A~}DCI~{V17=M<~}*/

#define HIIOC_PQ_S_DCI_BS              _IOW(HI_ID_PQ, 60, HI_PQ_DCI_BS_LUT_S)         /*~{P4~}DCI ~{:Z@)U9GzO_~}*/
#define HIIOC_PQ_G_DCI_BS              _IOWR(HI_ID_PQ, 61, HI_PQ_DCI_BS_LUT_S)         /*~{6A~}DCI ~{:Z@)U9GzO_~}*/

#define HIIOC_PQ_S_TNR_Y_PIXMEAN_2_RATIO       _IOW(HI_ID_PQ, 62, HI_PQ_TNR_S)        /*~{P4~}TNR~{5DAA6H~}PixMean-to-Ratio*/
#define HIIOC_PQ_G_TNR_Y_PIXMEAN_2_RATIO       _IOWR(HI_ID_PQ, 63, HI_PQ_TNR_S)        /*~{6A~}TNR~{5DAA6H~}PixMean-to-Ratio*/

#define HIIOC_PQ_S_TNR_C_PIXMEAN_2_RATIO       _IOW(HI_ID_PQ, 64, HI_PQ_TNR_S)        /*~{P4~}TNR ~{I+6H~}PixMean-to-Ratio~{S3IdGzO_~}*/
#define HIIOC_PQ_G_TNR_C_PIXMEAN_2_RATIO       _IOWR(HI_ID_PQ, 65, HI_PQ_TNR_S)        /*~{6A~}TNR ~{I+6H~}PixMean-to-Ratio~{S3IdGzO_~}*/

#define HIIOC_PQ_S_TNR_Y_MOTION_MAPPING        _IOW(HI_ID_PQ, 66, HI_PQ_TNR_S)        /*~{P4~}TNR~{AA6H~}MotionMapping~{GzO_~}*/
#define HIIOC_PQ_G_TNR_Y_MOTION_MAPPING        _IOWR(HI_ID_PQ, 67, HI_PQ_TNR_S)        /*~{6A~}TNR~{AA6H~}MotionMapping~{GzO_~}*/

#define HIIOC_PQ_S_TNR_C_MOTION_MAPPING        _IOW(HI_ID_PQ, 68, HI_PQ_TNR_S)        /*~{P4~}TNR~{I+6H~}MotionMapping~{GzO_~}*/
#define HIIOC_PQ_G_TNR_C_MOTION_MAPPING        _IOWR(HI_ID_PQ, 69, HI_PQ_TNR_S)        /*~{6A~}TNR~{I+6H~}MotionMapping~{GzO_~}*/

#define HIIOC_PQ_S_TNR_Y_FINAL_MOTION_MAPPING  _IOW(HI_ID_PQ, 70, HI_PQ_TNR_S)        /*~{P4~}TNR~{AA6H~}FINAL MotionMapping~{GzO_~}*/
#define HIIOC_PQ_G_TNR_Y_FINAL_MOTION_MAPPING  _IOWR(HI_ID_PQ, 71, HI_PQ_TNR_S)        /*~{6A~}TNR~{AA6H~}FINAL MotionMapping~{GzO_~}*/

#define HIIOC_PQ_S_TNR_C_FINAL_MOTION_MAPPING  _IOW(HI_ID_PQ, 72, HI_PQ_TNR_S)        /*~{P4~}TNR~{I+6H~}FINAL MotionMapping~{GzO_~}*/
#define HIIOC_PQ_G_TNR_C_FINAL_MOTION_MAPPING  _IOWR(HI_ID_PQ, 73, HI_PQ_TNR_S)        /*~{6A~}TNR~{I+6H~}FINAL MotionMapping~{GzO_~}*/

#define HIIOC_PQ_S_SNR_PIXMEAN_2_RATIO         _IOW(HI_ID_PQ, 74, HI_PQ_SNR_PIXMEAN_2_RATIO_S)     /*~{P4~}SNR ~{5D~}pixmean-ratio~{S3IdGzO_~}*/
#define HIIOC_PQ_G_SNR_PIXMEAN_2_RATIO         _IOWR(HI_ID_PQ, 75, HI_PQ_SNR_PIXMEAN_2_RATIO_S)     /*~{6A~}SNR ~{5D~}pixmean-ratio~{S3IdGzO_~}*/

#define HIIOC_PQ_S_SNR_PIXDIFF_2_EDGESTR       _IOW(HI_ID_PQ, 76, HI_PQ_SNR_PIXDIFF_2_EDGESTR_S)   /*~{P4~}SNR ~{5D~}pixdiff-edgestr~{S3IdGzO_~}*/
#define HIIOC_PQ_G_SNR_PIXDIFF_2_EDGESTR       _IOWR(HI_ID_PQ, 77, HI_PQ_SNR_PIXDIFF_2_EDGESTR_S)   /*~{6A~}SNR ~{5D~}pixdiff-edgestr~{S3IdGzO_~}*/

#define HIIOC_PQ_S_HD_BRIGHTNESS        _IOW(HI_ID_PQ, 84, HI_U32)                    /* ~{IhVC8_Ge~}BRIGHTNESS level*/
#define HIIOC_PQ_G_HD_BRIGHTNESS        _IOWR(HI_ID_PQ, 85, HI_U32)                    /* ~{;qH!8_Ge~}BRIGHTNESS level*/

#define HIIOC_PQ_S_HD_CONTRAST          _IOW(HI_ID_PQ, 86, HI_U32)                    /* ~{IhVC8_Ge~}CONTRAST level*/
#define HIIOC_PQ_G_HD_CONTRAST          _IOWR(HI_ID_PQ, 87, HI_U32)                    /* ~{;qH!8_Ge~}CONTRAST level*/

#define HIIOC_PQ_S_HD_SATURATION        _IOW(HI_ID_PQ, 88, HI_U32)                    /* ~{IhVC8_Ge~}SATURATION level*/
#define HIIOC_PQ_G_HD_SATURATION        _IOWR(HI_ID_PQ, 89, HI_U32)                    /* ~{;qH!8_Ge~}SATURATION level*/

#define HIIOC_PQ_S_HD_HUE               _IOW(HI_ID_PQ, 90, HI_U32)                    /* ~{IhVC8_Ge~}HUE level*/
#define HIIOC_PQ_G_HD_HUE               _IOWR(HI_ID_PQ, 91, HI_U32)                    /* ~{;qH!8_Ge~}HUE level*/

#define HIIOC_PQ_S_DCI_LEVEL            _IOW(HI_ID_PQ, 92, HI_U32)                    /* ~{IhVC~}DCI level*/
#define HIIOC_PQ_G_DCI_LEVEL            _IOWR(HI_ID_PQ, 93, HI_U32)                    /* ~{;qH!~}DCI level*/

#define HIIOC_PQ_G_BIN_ADDR             _IOWR(HI_ID_PQ, 94, HI_U32)                    /* ~{;qH!~}PQBin~{5DNo@m5XV7~}*/

#define HIIOC_PQ_S_COLOR_ENHANCE_MODE   _IOW(HI_ID_PQ, 95, HI_PQ_COLOR_SPEC_MODE_E)   /* ~{IhVCQUI+TvG?D#J=~}*/
#define HIIOC_PQ_G_COLOR_ENHANCE_MODE   _IOWR(HI_ID_PQ, 96, HI_PQ_COLOR_SPEC_MODE_E)   /* ~{;qH!QUI+TvG?D#J=~}*/

#define HIIOC_PQ_S_DEMO_MODE            _IOW(HI_ID_PQ, 99, HI_PQ_DEMO_MODE_E)         /* ~{IhVC8wKc7(D#?iBt3!D#J=OTJ>7=J=~}*/
#define HIIOC_PQ_G_DEMO_MODE            _IOWR(HI_ID_PQ, 100, HI_PQ_DEMO_MODE_E)        /* ~{;qH!8wKc7(D#?iBt3!D#J=OTJ>7=J=~}*/

#define HIIOC_PQ_S_GRAPH_SD_PARAM       _IOW(HI_ID_PQ, 101, HI_PQ_IMAGE_PARAM_S)      /* ~{IhVCM<PN1jGe2NJ}~}*/
#define HIIOC_PQ_G_GRAPH_SD_PARAM       _IOWR(HI_ID_PQ, 102, HI_PQ_IMAGE_PARAM_S)      /* ~{;qH!M<PN1jGe2NJ}~}*/

#define HIIOC_PQ_S_GRAPH_HD_PARAM       _IOW(HI_ID_PQ, 103, HI_PQ_IMAGE_PARAM_S)      /* ~{IhVCM<PN8_Ge2NJ}~}*/
#define HIIOC_PQ_G_GRAPH_HD_PARAM       _IOWR(HI_ID_PQ, 104, HI_PQ_IMAGE_PARAM_S)      /* ~{;qH!M<PN8_Ge2NJ}~}*/

#define HIIOC_PQ_S_VIDEO_SD_PARAM       _IOW(HI_ID_PQ, 105, HI_PQ_IMAGE_PARAM_S)      /* ~{IhVCJSF51jGe2NJ}~}*/
#define HIIOC_PQ_G_VIDEO_SD_PARAM       _IOWR(HI_ID_PQ, 106, HI_PQ_IMAGE_PARAM_S)      /* ~{;qH!JSF51jGe2NJ}~}*/

#define HIIOC_PQ_S_VIDEO_HD_PARAM       _IOW(HI_ID_PQ, 107, HI_PQ_IMAGE_PARAM_S)      /* ~{IhVCJSF58_Ge2NJ}~}*/
#define HIIOC_PQ_G_VIDEO_HD_PARAM       _IOWR(HI_ID_PQ, 108, HI_PQ_IMAGE_PARAM_S)      /* ~{;qH!JSF58_Ge2NJ}~}*/

#define HIIOC_PQ_S_TNR_FMOTION_MAPPING  _IOW(HI_ID_PQ, 109, HI_PQ_TNR_FMOTION_S)      /*~{P4~}TNR FMotionMapping ~{GzO_~}*/
#define HIIOC_PQ_G_TNR_FMOTION_MAPPING  _IOWR(HI_ID_PQ, 110, HI_PQ_TNR_FMOTION_S)      /*~{6A~}TNR FMotionMapping ~{GzO_~}*/

#define HIIOC_PQ_S_DEFAULT_PARAM        _IOW(HI_ID_PQ, 111, HI_BOOL)                  /*~{IhVC~}PQ ~{5DD,HOV5~}*/

#define HIIOC_PQ_S_SNR                  _IOW(HI_ID_PQ, 112, HI_U32)                   /* set SNR level*/
#define HIIOC_PQ_G_SNR                  _IOWR(HI_ID_PQ, 113, HI_U32)                   /* get SNR level*/

#define HIIOC_PQ_S_SNR_MEAN_RATIO       _IOW(HI_ID_PQ, 114, HI_PQ_SNR_MEAN_RATIO_S)   /*~{P4~}SNR ~{5D~}MEAN RATIO~{S3IdGzO_~}*/
#define HIIOC_PQ_G_SNR_MEAN_RATIO       _IOWR(HI_ID_PQ, 115, HI_PQ_SNR_MEAN_RATIO_S)   /*~{6A~}SNR ~{5D~}MEAN RATIO~{S3IdGzO_~}*/

#define HIIOC_PQ_S_SNR_EDGE_STR         _IOW(HI_ID_PQ, 116, HI_PQ_SNR_EDGE_STR_S)     /*~{P4~}SNR ~{5D~}EDGE STR~{S3IdGzO_~}*/
#define HIIOC_PQ_G_SNR_EDGE_STR         _IOWR(HI_ID_PQ, 117, HI_PQ_SNR_EDGE_STR_S)     /*~{6A~}SNR ~{5D~}EDGE STR~{S3IdGzO_~}*/

#define HIIOC_PQ_S_GAMM_PARA            _IOW(HI_ID_PQ, 118, HI_PQ_CSC_GAMM_PARA_S)
#define HIIOC_PQ_G_GAMM_PARA            _IOWR(HI_ID_PQ, 119, HI_PQ_CSC_GAMM_PARA_S)

#define HIIOC_PQ_S_DEGAMM_PARA          _IOW(HI_ID_PQ, 120, HI_PQ_CSC_GAMM_PARA_S)
#define HIIOC_PQ_G_DEGAMM_PARA          _IOWR(HI_ID_PQ, 121, HI_PQ_CSC_GAMM_PARA_S)

#define HIIOC_PQ_S_GFX_GAMM_PARA        _IOW(HI_ID_PQ, 122, HI_PQ_CSC_GAMM_PARA_S)
#define HIIOC_PQ_G_GFX_GAMM_PARA        _IOWR(HI_ID_PQ, 123, HI_PQ_CSC_GAMM_PARA_S)

#define HIIOC_PQ_S_GFX_DEGAMM_PARA      _IOW(HI_ID_PQ, 124, HI_PQ_CSC_GAMM_PARA_S)
#define HIIOC_PQ_G_GFX_DEGAMM_PARA      _IOWR(HI_ID_PQ, 125, HI_PQ_CSC_GAMM_PARA_S)

#define HIIOC_PQ_S_DEMO_COORDINATE      _IOW(HI_ID_PQ, 126, HI_U32)                   /* set demo coordinate*/
#define HIIOC_PQ_G_DEMO_COORDINATE      _IOWR(HI_ID_PQ, 127, HI_U32)                   /* get demo coordinate*/

#define HIIOC_PQ_S_DM                   _IOW(HI_ID_PQ, 128, HI_U32)                   /* set dm level*/
#define HIIOC_PQ_G_DM                   _IOWR(HI_ID_PQ, 129, HI_U32)                   /* get dm level*/

#define HIIOC_PQ_S_HDR_TMLUT            _IOW(HI_ID_PQ, 132, HI_PQ_HDR_TM_LUT_S)       /* set HDR TM Lut*/
#define HIIOC_PQ_G_HDR_TMLUT            _IOWR(HI_ID_PQ, 133, HI_PQ_HDR_TM_LUT_S)       /* get HDR TM Lut*/

#define HIIOC_PQ_S_IMAGE_MODE           _IOW(HI_ID_PQ, 134, HI_PQ_IMAGE_MODE_E)       /* set VideoPhone mode*/
#define HIIOC_PQ_G_IMAGE_MODE           _IOWR(HI_ID_PQ, 135, HI_PQ_IMAGE_MODE_E)       /* get VideoPhone mode*/

#define HIIOC_PQ_S_ACC_LUT              _IOW(HI_ID_PQ, 136, PQ_ACC_LUT_S)             /* set ACC Lut*/
#define HIIOC_PQ_G_ACC_LUT              _IOWR(HI_ID_PQ, 137, PQ_ACC_LUT_S)             /* get ACC Lut*/

#define HIIOC_PQ_S_HDROFFSET_PARAM      _IOW(HI_ID_PQ, 138, HI_PQ_SETHDROFFSET_S)     /* set HDR Offset Para */
#define HIIOC_PQ_S_GfxHDROFFSET_PARAM   _IOW(HI_ID_PQ, 139, HI_PQ_SETHDROFFSET_S)     /* set GFXHDR Offset Para */

#define HIIOC_PQ_S_MCDI_SPLIT_MODE      _IOW(HI_ID_PQ, 140, HI_U32)  /* set Mcdi Split mode*/

#define HIIOC_PQ_S_SD_TEMPERATURE       _IOW(HI_ID_PQ, 142, HI_PQ_COLORTEMPERATURE_S)  /* ~{IhVC1jGeI+NB~}*/
#define HIIOC_PQ_G_SD_TEMPERATURE       _IOWR(HI_ID_PQ,143, HI_PQ_COLORTEMPERATURE_S)  /* ~{;qH!1jGeI+NB~}*/

#define HIIOC_PQ_S_HD_TEMPERATURE       _IOW(HI_ID_PQ, 144, HI_PQ_COLORTEMPERATURE_S)  /* ~{IhVC8_GeI+NB~}*/
#define HIIOC_PQ_G_HD_TEMPERATURE       _IOWR(HI_ID_PQ,145, HI_PQ_COLORTEMPERATURE_S)  /* ~{;qH!8_GeI+NB~}*/

#define HIIOC_PQ_S_VP_PREVIEW_IMAGE_MODE   _IOW(HI_ID_PQ, 146, HI_DRV_PQ_VP_MODE_E)  /* set VideoPhone Preview mode*/
#define HIIOC_PQ_G_VP_PREVIEW_IMAGE_MODE   _IOWR(HI_ID_PQ, 147, HI_DRV_PQ_VP_MODE_E)  /* get VideoPhone Preview mode*/

#define HIIOC_PQ_S_VP_REMOTE_IMAGE_MODE    _IOW(HI_ID_PQ, 148, HI_DRV_PQ_VP_MODE_E)  /* set VideoPhone Preview mode*/
#define HIIOC_PQ_G_VP_REMOTE_IMAGE_MODE    _IOWR(HI_ID_PQ, 149, HI_DRV_PQ_VP_MODE_E)  /* get VideoPhone Preview mode*/

#define HIIOC_PQ_S_VP_PREVIEW_BRIGHTNESS   _IOW(HI_ID_PQ, 150, HI_U32)     /* ~{IhVC~}VPSS PREVIEW BRIGHTNESS level*/
#define HIIOC_PQ_G_VP_PREVIEW_BRIGHTNESS   _IOWR(HI_ID_PQ, 151, HI_U32)     /* ~{;qH!~}VPSS PREVIEW BRIGHTNESS level*/

#define HIIOC_PQ_S_VP_PREVIEW_CONTRAST     _IOW(HI_ID_PQ, 152, HI_U32)     /* ~{IhVC~}VPSS PREVIEW CONTRAST level*/
#define HIIOC_PQ_G_VP_PREVIEW_CONTRAST     _IOWR(HI_ID_PQ, 153, HI_U32)     /* ~{;qH!~}VPSS PREVIEW CONTRAST level*/

#define HIIOC_PQ_S_VP_PREVIEW_SATURATION   _IOW(HI_ID_PQ, 154, HI_U32)     /* ~{IhVC~}VPSS PREVIEW SATURATION level*/
#define HIIOC_PQ_G_VP_PREVIEW_SATURATION   _IOWR(HI_ID_PQ, 155, HI_U32)     /* ~{;qH!~}VPSS PREVIEW SATURATION level*/

#define HIIOC_PQ_S_VP_PREVIEW_HUE          _IOW(HI_ID_PQ, 156, HI_U32)     /* ~{IhVC~}VPSS PREVIEW HUE level*/
#define HIIOC_PQ_G_VP_PREVIEW_HUE          _IOWR(HI_ID_PQ, 157, HI_U32)     /* ~{;qH!~}VPSS PREVIEW HUE level*/

#define HIIOC_PQ_S_VP_PREVIEW_VIDEO_PARAM  _IOW(HI_ID_PQ, 158, HI_PQ_IMAGE_PARAM_S)  /* ~{IhVC~}VPSS ~{JSF58_Ge2NJ}~}*/
#define HIIOC_PQ_G_VP_PREVIEW_VIDEO_PARAM  _IOWR(HI_ID_PQ, 159, HI_PQ_IMAGE_PARAM_S)  /* ~{;qH!~}VPSS ~{JSF58_Ge2NJ}~}*/

#define HIIOC_PQ_S_VP_REMOTE_BRIGHTNESS    _IOW(HI_ID_PQ, 160, HI_U32)     /* ~{IhVC~}VPSS REMOTE BRIGHTNESS level*/
#define HIIOC_PQ_G_VP_REMOTE_BRIGHTNESS    _IOWR(HI_ID_PQ, 161, HI_U32)     /* ~{;qH!~}VPSS REMOTE BRIGHTNESS level*/

#define HIIOC_PQ_S_VP_REMOTE_CONTRAST      _IOW(HI_ID_PQ, 162, HI_U32)     /* ~{IhVC~}VPSS REMOTE CONTRAST level*/
#define HIIOC_PQ_G_VP_REMOTE_CONTRAST      _IOWR(HI_ID_PQ, 163, HI_U32)     /* ~{;qH!~}VPSS REMOTE CONTRAST level*/

#define HIIOC_PQ_S_VP_REMOTE_SATURATION    _IOW(HI_ID_PQ, 164, HI_U32)     /* ~{IhVC~}VPSS REMOTE SATURATION level*/
#define HIIOC_PQ_G_VP_REMOTE_SATURATION    _IOWR(HI_ID_PQ, 165, HI_U32)     /* ~{;qH!~}VPSS REMOTE SATURATION level*/

#define HIIOC_PQ_S_VP_REMOTE_HUE           _IOW(HI_ID_PQ, 166, HI_U32)     /* ~{IhVC~}VPSS REMOTE HUE level*/
#define HIIOC_PQ_G_VP_REMOTE_HUE           _IOWR(HI_ID_PQ, 167, HI_U32)     /* ~{;qH!~}VPSS REMOTE HUE level*/

#define HIIOC_PQ_S_VP_REMOTE_VIDEO_PARAM   _IOW(HI_ID_PQ, 168, HI_PQ_IMAGE_PARAM_S)  /* ~{IhVC~}VPSS ~{JSF58_Ge2NJ}~}*/
#define HIIOC_PQ_G_VP_REMOTE_VIDEO_PARAM   _IOWR(HI_ID_PQ, 169, HI_PQ_IMAGE_PARAM_S)  /* ~{;qH!~}VPSS ~{JSF58_Ge2NJ}~}*/

#define HIIOC_PQ_S_HDR_PARA_MODE           _IOW(HI_ID_PQ, 170, HI_PQ_HDR_PARA_MODE_S)    /* set HDR Lwavg*/
#define HIIOC_PQ_G_HDR_PARA_MODE           _IOWR(HI_ID_PQ, 171, HI_PQ_HDR_PARA_MODE_S)    /* get HDR Lwavg*/

#define HIIOC_PQ_S_HDR_TMAP                _IOW(HI_ID_PQ, 172, HI_PQ_HDR_TMAP_S)      /* set HDR Tmap*/
#define HIIOC_PQ_G_HDR_TMAP                _IOWR(HI_ID_PQ, 173, HI_PQ_HDR_TMAP_S)      /* get HDR Tmap*/
#define HIIOC_PQ_S_HDR_SMAP                _IOW(HI_ID_PQ, 174, HI_PQ_HDR_SMAP_S)      /* set HDR Smap*/
#define HIIOC_PQ_G_HDR_SMAP                _IOWR(HI_ID_PQ, 175, HI_PQ_HDR_SMAP_S)      /* get HDR Smap*/

#define HIIOC_PQ_S_GFXHDR_MODE             _IOW(HI_ID_PQ, 180, HI_PQ_GFXHDR_MODE_S)    /* set GFXHDR TmMode*/
#define HIIOC_PQ_G_GFXHDR_MODE             _IOWR(HI_ID_PQ, 181, HI_PQ_GFXHDR_MODE_S)    /* get GFXHDR TmMode*/
#define HIIOC_PQ_S_GFXHDR_TMAP             _IOW(HI_ID_PQ, 182, HI_PQ_GFXHDR_TMAP_S)      /* set GFXHDR Tmap*/
#define HIIOC_PQ_G_GFXHDR_TMAP             _IOWR(HI_ID_PQ, 183, HI_PQ_GFXHDR_TMAP_S)      /* get GFXHDR Tmap*/
#define HIIOC_PQ_S_GFXHDR_STEP             _IOW(HI_ID_PQ, 184, HI_PQ_GFXHDR_STEP_S)      /* set GFXHDR Step*/
#define HIIOC_PQ_G_GFXHDR_STEP             _IOWR(HI_ID_PQ, 185, HI_PQ_GFXHDR_STEP_S)      /* get GFXHDR Step*/

#define HIIOC_PQ_S_HDR_ACM_MODE            _IOW(HI_ID_PQ, 190, HI_PQ_HDR_ACM_MODE_S)    /* set Hdr Acm Mode*/
#define HIIOC_PQ_G_HDR_ACM_MODE            _IOWR(HI_ID_PQ, 191, HI_PQ_HDR_ACM_MODE_S)   /* get Hdr Acm Mode*/
#define HIIOC_PQ_S_HDR_ACM_REGCFG          _IOW(HI_ID_PQ, 192, HI_PQ_HDR_ACM_REGCFG_S)  /* set Hdr Acm RegCfg*/
#define HIIOC_PQ_G_HDR_ACM_REGCFG          _IOWR(HI_ID_PQ, 193, HI_PQ_HDR_ACM_REGCFG_S) /* get Hdr Acm RegCfg*/

#define HIIOC_PQ_S_HDR_DYN_MODE            _IOW(HI_ID_PQ, 194, HI_PQ_HDR_DYN_TM_TUNING_S)    /* set Hdr Dyn Mode*/
#define HIIOC_PQ_G_HDR_DYN_MODE            _IOWR(HI_ID_PQ, 195, HI_PQ_HDR_DYN_TM_TUNING_S)   /* get Hdr Dyn Mode*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __HI_DRV_PQ_H__ */
