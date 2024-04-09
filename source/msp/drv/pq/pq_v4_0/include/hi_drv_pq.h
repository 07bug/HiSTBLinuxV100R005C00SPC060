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

#ifndef __HI_DRV_PQ_V4_H__
#define __HI_DRV_PQ_V4_H__

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


/* PQģ�� */
typedef enum hiHIPQ_MODULE_E
{
    HI_PQ_MODULE_FMD       = 0 ,
    HI_PQ_MODULE_TNR       = 1 ,
    HI_PQ_MODULE_SNR       = 2 ,
    HI_PQ_MODULE_DB        = 3 ,
    HI_PQ_MODULE_DR        = 4 ,
    HI_PQ_MODULE_DM        = 5 ,
    HI_PQ_MODULE_DBM       = 6 ,
    HI_PQ_MODULE_SHARPNESS = 7 ,
    HI_PQ_MODULE_DCI       = 8 ,
    HI_PQ_MODULE_COLOR     = 9 ,
    HI_PQ_MODULE_SR        = 10,
    HI_PQ_MODULE_CSC       = 11,
    HI_PQ_MODULE_ZME       = 12,
    HI_PQ_MODULE_DEI       = 13,
    HI_PQ_MODULE_DS        = 14,
    HI_PQ_MODULE_ARTDS     = 15,
    HI_PQ_MODULE_GFXCSC    = 16,
    HI_PQ_MODULE_GFXZME    = 17,
    HI_PQ_MODULE_HDR       = 18,
    HI_PQ_MODULE_GFXHDR    = 19,
    HI_PQ_MODULE_VPSSCSC   = 20,
    HI_PQ_MODULE_VPSSGAMMA = 21,
    HI_PQ_MODULE_VDP4KSNR  = 22,
    HI_PQ_MODULE_LCHDR     = 23,
    HI_PQ_MODULE_ALL       = 24,

    HI_PQ_MODULE_BUTT
}  HI_PQ_MODULE_E;

/*����/�Աȶ�/ɫ��/���Ͷ��趨*/
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
 * ģ�鿪������
 */
typedef struct hiPQ_MODULE_S
{
    HI_PQ_MODULE_E enModule;
    HI_U32 u32OnOff; /*����*/
} HI_PQ_MODULE_S;

/*
 * ����ģʽ����
 */
typedef struct hiPQ_DEMO_S
{
    HI_PQ_MODULE_E enModule;
    HI_BOOL      bOnOff; /*����*/
} HI_PQ_DEMO_S;

/* ����ģʽ ��ʾ��ʽ*/
typedef enum hiPQ_DEMO_MODE_E
{
    HI_PQ_DEMO_MODE_FIXED_R = 0,
    HI_PQ_DEMO_MODE_FIXED_L,
    HI_PQ_DEMO_MODE_SCROLL_R,
    HI_PQ_DEMO_MODE_SCROLL_L,

    HI_PQ_DEMO_MODE_BUTT
} HI_PQ_DEMO_MODE_E;

/*
 * �Ĵ�������
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

/* COLOR LUT�ṹ */
typedef struct hiPQ_COLOR_LUT_S
{
    HI_S16 as16Color[ACM_Y_NUM][ACM_S_NUM][ACM_H_NUM];  /* ACM ���ұ� */
} HI_PQ_COLOR_LUT_S;

/*ACM table�ṹ*/
typedef struct hiPQ_DRV_ACM_LUT_S
{
    HI_U32 u32LutType;           /*ACM ���ұ���������*/
    HI_S16 as16Lut[ACM_Y_NUM][ACM_S_NUM][ACM_H_NUM];   /*ACM ���ұ�*/
} HI_PQ_ACM_LUT_S;

/*DCI�������ñ�*/
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

/*DCIֱ��ͼ�ṹ*/
typedef struct hiPQ_DCI_HISTGRAM_S
{
    HI_S32 s32HistGram[32];
} HI_PQ_DCI_HISTGRAM_S;

typedef struct
{
    HI_U16  u16GammCoef[1024];
} HI_PQ_CSC_GAMM_PARA_S;

/*TNRͨ�ýṹ*/
typedef struct hiPQ_TNR_S
{
    HI_S32 s32MappingMax;
    HI_S32 s32MappingMin;
    HI_S32 s32MappingR[5];
    HI_S32 s32MappingT[6];
    HI_S32 s32MappingK[4];
} HI_PQ_TNR_S;

/* YFmotion ��ӳ������  */
typedef struct hiPQ_TNR_FMOTION_S
{
    HI_S16 s16YFmotion[32];
    HI_S16 s16CFmotion[32];
} HI_PQ_TNR_FMOTION_S;

/*SNR��pixmean-ratio�ṹ*/
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

/*SNR ��pixdiff-edgestr�ṹ*/
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
    HI_S32 s32MappingMax;    /*meanedgeratio maxӳ������ֵ 0~127 */
    HI_S32 s32MappingMin;    /*meanedgeratio minӳ�����Сֵ 0~127 */
    HI_S32 s32MappingX[6];   /*meanedgeratio X*/
    HI_S32 s32MappingY[5];   /*meanedgeratio Y*/
    HI_S32 s32MappingK[4];   /*meanedgeratio K*/

} HI_PQ_SNR_MEAN_RATIO_S;

typedef struct  hiPQ_SNR_EDGE_STR_S
{
    HI_S32 s32MappingMax;    /*edgestrmapping maxӳ������ֵ 0~63*/
    HI_S32 s32MappingMin;    /*edgestrmapping minӳ�����Сֵ 0~63*/
    HI_S32 s32MappingX[8];   /*edgestrmapping X*/
    HI_S32 s32MappingY[7];   /*edgestrmapping Y*/
    HI_S32 s32MappingK[6];   /*edgestrmapping K*/

} HI_PQ_SNR_EDGE_STR_S;


/*SR��ʾģʽ*/
typedef enum hiPQ_SR_DEMO_E
{
    HI_PQ_SR_DISABLE  = 0,/* ��SR,ֻZME */
    HI_PQ_SR_ENABLE_R,    /* �ұ�SR */
    HI_PQ_SR_ENABLE_L,    /* ���SR */
    HI_PQ_SR_ENABLE_A,    /* ȫ�� */

    HI_PQ_SR_DEMO_BUTT
} HI_PQ_SR_DEMO_E;

/*����ɫ��ǿ����*/
typedef struct hiPQ_SIX_BASE_COLOR_S
{
    HI_U32  u32Red;         /* Range:0~100 */
    HI_U32  u32Green;       /* Range:0~100 */
    HI_U32  u32Blue;        /* Range:0~100 */
    HI_U32  u32Cyan;        /* Range:0~100 */
    HI_U32  u32Magenta;     /* Range:0~100 */
    HI_U32  u32Yellow;      /* Range:0~100 */
} HI_PQ_SIX_BASE_COLOR_S;

/*ACM GAIN ��Ϣ�ṹ*/
typedef struct hiPQ_COLOR_GAIN_S
{
    HI_U32 u32GainMode;   /* 0:SD;1:HD;2:UHD */
    HI_U32 u32Gainluma;   /* ��ʾ��Hue�����棬Range:0-1023 */
    HI_U32 u32Gainhue;    /* ��ʾ��Hue�����棬Range:0-1023 */
    HI_U32 u32Gainsat;    /* ��ʾ��Luma������ */
} HI_PQ_COLOR_GAIN_S;

/*��ɫ��ǿ����*/
typedef enum hiPQ_COLOR_ENHANCE_E
{
    HI_PQ_COLOR_ENHANCE_FLESHTONE = 0,    /* ��ɫ��ǿ */
    HI_PQ_COLOR_ENHANCE_SIX_BASE,         /* ����ɫ��ǿ,�Զ�����ɫ����ǿ */
    HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE,  /* �̶�ģʽ����ɫ��ǿģʽ */
    HI_PQ_COLOR_ENHANCE_BUTT
} HI_PQ_COLOR_ENHANCE_E;

/*��ɫ�������*/
typedef enum hiPQ_FLESHTONE_E
{
    HI_PQ_FLESHTONE_GAIN_OFF = 0,
    HI_PQ_FLESHTONE_GAIN_LOW,
    HI_PQ_FLESHTONE_GAIN_MID,
    HI_PQ_FLESHTONE_GAIN_HIGH,

    HI_PQ_FLESHTONE_GAIN_BUTT
}  HI_PQ_FLESHTONE_E;


/*��ɫ��ǿ����*/
typedef enum hiPQ_COLOR_SPEC_MODE_E
{
    HI_PQ_COLOR_MODE_RECOMMEND = 0, /* �Ƽ�����ɫ��ǿģʽ */
    HI_PQ_COLOR_MODE_BLUE      = 1, /* �̶�����ɫ��ǿģʽ */
    HI_PQ_COLOR_MODE_GREEN     = 2, /* �̶�����ɫ��ǿģʽ */
    HI_PQ_COLOR_MODE_BG        = 3, /* �̶�������ɫ��ǿģʽ */
    HI_PQ_COLOR_MODE_ORIGINAL  = 4, /* ԭʼ��ɫģʽ */

    HI_PQ_COLOR_MODE_BUTT
} HI_PQ_COLOR_SPEC_MODE_E;

/*��ɫ��ǿ����*/
typedef struct  hiPQ_COLOR_ENHANCE_S
{
    HI_PQ_COLOR_ENHANCE_E    enColorEnhanceType; /* ɫ����ǿ���� */
    union
    {
        HI_PQ_FLESHTONE_E       enFleshtone;   /* ��ɫ��ǿ���� */
        HI_PQ_SIX_BASE_COLOR_S  stSixBase;     /* ����ɫ��ǿ���� */
        HI_PQ_COLOR_SPEC_MODE_E enColorMode;   /* �̶�����ɫ��ǿģʽ */

    } unColorGain;
} HI_PQ_COLOR_ENHANCE_S;

typedef struct  hiPQ_COLORTEMPERATURE_S
{
    HI_U32  u32Red;       /**<Red; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
    HI_U32  u32Green;     /**<Green; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
    HI_U32  u32Blue;      /**<Blue; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
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
    HI_U32 u32ParaModeUse;   /*ѡ��HDR����ģʽ��0:�̶�������1:���ߵ��Բ���*/
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
    HI_U32 u32ParaModeUse;   /*ѡ��HDR����ģʽ��0:�̶�������1:���ߵ��Բ���*/
} HI_PQ_HDR_ACM_MODE_S;

typedef struct hiPQ_HDR_ACM_REGCFG_S
{
    HI_S32 as32Regcfg[PQ_HDR_ACM_REGCFG_SIZE];
} HI_PQ_HDR_ACM_REGCFG_S;

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
    HI_DRV_PQ_VIDEOPHONE_MODE_RECOMMEND = 0, /**<Optimization Model */ /**<CNcomment:����ģʽ CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_BLACK     = 1, /**<BlackWhite Model */ /**<CNcomment:��ɫ��ǿģʽ CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_COLORFUL  = 2, /**<Colorful Model */ /**<CNcomment:��ɫ��ǿģʽ CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_BRIGHT    = 3, /**<Bright Model */ /**<CNcomment:������ǿģʽ CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_WARM      = 4, /**<Warm Model */ /**<CNcomment:ԭʼ��ɫģʽ CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_COOL      = 5, /**<Cool Model */ /**<CNcomment:ԭʼ��ɫģʽ CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_OLD       = 6, /**<Old Model */ /**<CNcomment:ԭʼ��ɫģʽ CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_USER      = 7, /**<Old Model */ /**<CNcomment:ԭʼ��ɫģʽ CNend*/
    HI_DRV_PQ_VIDEOPHONE_MODE_BUTT
} HI_DRV_PQ_VP_MODE_E;

/*�û��ӿ�*/

#define HIIOC_PQ_S_SD_BRIGHTNESS        _IOW(HI_ID_PQ, 3, HI_U32)                     /* ���ñ���BRIGHTNESS level*/
#define HIIOC_PQ_G_SD_BRIGHTNESS        _IOWR(HI_ID_PQ, 4, HI_U32)                     /* ��ȡ����BRIGHTNESS level*/

#define HIIOC_PQ_S_SD_CONTRAST          _IOW(HI_ID_PQ, 5, HI_U32)                     /* ���ñ���CONTRAST level*/
#define HIIOC_PQ_G_SD_CONTRAST          _IOWR(HI_ID_PQ, 6, HI_U32)                     /* ��ȡ����CONTRAST level*/

#define HIIOC_PQ_S_SD_SATURATION        _IOW(HI_ID_PQ, 7, HI_U32)                     /* ���ñ���SATURATION level*/
#define HIIOC_PQ_G_SD_SATURATION        _IOWR(HI_ID_PQ, 8, HI_U32)                     /* ��ȡ����SATURATION level*/

#define HIIOC_PQ_S_SD_HUE               _IOW(HI_ID_PQ, 9, HI_U32)                     /* ���ñ���HUE level*/
#define HIIOC_PQ_G_SD_HUE               _IOWR(HI_ID_PQ, 10, HI_U32)                    /* ��ȡ����HUE level*/

#define HIIOC_PQ_S_TNR                  _IOW(HI_ID_PQ, 11, HI_U32)                    /* ����TNR level*/
#define HIIOC_PQ_G_TNR                  _IOWR(HI_ID_PQ, 12, HI_U32)                    /* ��ȡTNR level*/

#define HIIOC_PQ_S_SHARPNESS            _IOW(HI_ID_PQ, 13, HI_U32)                    /* ����SHARPNESS level*/
#define HIIOC_PQ_G_SHARPNESS            _IOWR(HI_ID_PQ, 14, HI_U32)                    /* ��ȡSHARPNESS level*/

#define HIIOC_PQ_S_DB                   _IOW(HI_ID_PQ, 15, HI_U32)                    /* ����De-blocking level*/
#define HIIOC_PQ_G_DB                   _IOWR(HI_ID_PQ, 16, HI_U32)                    /* ��ȡDe-blocking level*/

#define HIIOC_PQ_S_DR                   _IOW(HI_ID_PQ, 17, HI_U32)                    /* ����De-Ring level*/
#define HIIOC_PQ_G_DR                   _IOWR(HI_ID_PQ, 18, HI_U32)                    /* ��ȡDe-Ring level*/

#define HIIOC_PQ_S_FLESHTONE            _IOW(HI_ID_PQ, 21, HI_PQ_FLESHTONE_E)         /* ����FleshTone level*/
#define HIIOC_PQ_G_FLESHTONE            _IOWR(HI_ID_PQ, 22, HI_PQ_FLESHTONE_E)         /* ��ȡFleshTone level*/

#define HIIOC_PQ_S_MODULE               _IOW(HI_ID_PQ, 27, HI_PQ_MODULE_S)            /* ���ø��㷨ģ�鿪��*/
#define HIIOC_PQ_G_MODULE               _IOWR(HI_ID_PQ, 28, HI_PQ_MODULE_S)           /* ��ȡ���㷨ģ�鿪��*/

#define HIIOC_PQ_S_DEMO                 _IOW(HI_ID_PQ, 29, HI_PQ_DEMO_S)              /* ���ø��㷨ģ������ģʽ����*/

#define HIIOC_PQ_S_SIXBASECOLOR         _IOW(HI_ID_PQ, 30, HI_PQ_SIX_BASE_COLOR_S)    /* ���� ����ɫ����*/
#define HIIOC_PQ_G_SIXBASECOLOR         _IOWR(HI_ID_PQ, 31, HI_PQ_SIX_BASE_COLOR_S)    /* ��ȡ����ɫ����*/

#define HIIOC_PQ_S_SR_DEMO              _IOW(HI_ID_PQ, 35, HI_PQ_SR_DEMO_E)           /* ����SR��ʾģʽ*/
#define HIIOC_PQ_G_SR_DEMO              _IOWR(HI_ID_PQ, 36, HI_PQ_SR_DEMO_E)           /* ��ȡSR��ʾģʽ*/

#define HIIOC_PQ_S_REGISTER             _IOW(HI_ID_PQ, 44, HI_PQ_REGISTER_S)          /* д�Ĵ���*/
#define HIIOC_PQ_G_REGISTER             _IOWR(HI_ID_PQ, 45, HI_PQ_REGISTER_S)         /*���Ĵ���*/

#define HIIOC_PQ_S_DCI                 _IOW(HI_ID_PQ, 48, HI_PQ_DCI_WGT_S)            /*дDCI����*/
#define HIIOC_PQ_G_DCI                 _IOWR(HI_ID_PQ, 49, HI_PQ_DCI_WGT_S)            /*��DCI����*/

#define HIIOC_PQ_S_ACM_GAIN            _IOW(HI_ID_PQ, 50, HI_PQ_COLOR_GAIN_S)         /*дCOLOR GAIN*/
#define HIIOC_PQ_G_ACM_GAIN            _IOWR(HI_ID_PQ, 51, HI_PQ_COLOR_GAIN_S)         /*��COLOR GAIN*/

#define HIIOC_PQ_S_ACM_LUMA            _IOW(HI_ID_PQ, 52, HI_PQ_ACM_LUT_S)            /*дCOLOR LUMA����*/
#define HIIOC_PQ_G_ACM_LUMA            _IOWR(HI_ID_PQ, 53, HI_PQ_ACM_LUT_S)            /*��COLOR LUMA����*/

#define HIIOC_PQ_S_ACM_HUE             _IOW(HI_ID_PQ, 54, HI_PQ_ACM_LUT_S)            /*дCOLOR HUE����*/
#define HIIOC_PQ_G_ACM_HUE             _IOWR(HI_ID_PQ, 55, HI_PQ_ACM_LUT_S)            /*��COLOR HUE����*/

#define HIIOC_PQ_S_ACM_SAT             _IOW(HI_ID_PQ, 56, HI_PQ_ACM_LUT_S)            /*дCOLOR SAT����*/
#define HIIOC_PQ_G_ACM_SAT             _IOWR(HI_ID_PQ, 57, HI_PQ_ACM_LUT_S)            /*��COLOR SAT����*/

#define HIIOC_PQ_G_DCI_HIST            _IOWR(HI_ID_PQ, 58, HI_PQ_DCI_HISTGRAM_S)       /*��DCIֱ��ͼ*/

#define HIIOC_PQ_S_DCI_BS              _IOW(HI_ID_PQ, 60, HI_PQ_DCI_BS_LUT_S)         /*дDCI ����չ����*/
#define HIIOC_PQ_G_DCI_BS              _IOWR(HI_ID_PQ, 61, HI_PQ_DCI_BS_LUT_S)         /*��DCI ����չ����*/

#define HIIOC_PQ_S_TNR_Y_PIXMEAN_2_RATIO       _IOW(HI_ID_PQ, 62, HI_PQ_TNR_S)        /*дTNR������PixMean-to-Ratio*/
#define HIIOC_PQ_G_TNR_Y_PIXMEAN_2_RATIO       _IOWR(HI_ID_PQ, 63, HI_PQ_TNR_S)        /*��TNR������PixMean-to-Ratio*/

#define HIIOC_PQ_S_TNR_C_PIXMEAN_2_RATIO       _IOW(HI_ID_PQ, 64, HI_PQ_TNR_S)        /*дTNR ɫ��PixMean-to-Ratioӳ������*/
#define HIIOC_PQ_G_TNR_C_PIXMEAN_2_RATIO       _IOWR(HI_ID_PQ, 65, HI_PQ_TNR_S)        /*��TNR ɫ��PixMean-to-Ratioӳ������*/

#define HIIOC_PQ_S_TNR_Y_MOTION_MAPPING        _IOW(HI_ID_PQ, 66, HI_PQ_TNR_S)        /*дTNR����MotionMapping����*/
#define HIIOC_PQ_G_TNR_Y_MOTION_MAPPING        _IOWR(HI_ID_PQ, 67, HI_PQ_TNR_S)        /*��TNR����MotionMapping����*/

#define HIIOC_PQ_S_TNR_C_MOTION_MAPPING        _IOW(HI_ID_PQ, 68, HI_PQ_TNR_S)        /*дTNRɫ��MotionMapping����*/
#define HIIOC_PQ_G_TNR_C_MOTION_MAPPING        _IOWR(HI_ID_PQ, 69, HI_PQ_TNR_S)        /*��TNRɫ��MotionMapping����*/

#define HIIOC_PQ_S_TNR_Y_FINAL_MOTION_MAPPING  _IOW(HI_ID_PQ, 70, HI_PQ_TNR_S)        /*дTNR����FINAL MotionMapping����*/
#define HIIOC_PQ_G_TNR_Y_FINAL_MOTION_MAPPING  _IOWR(HI_ID_PQ, 71, HI_PQ_TNR_S)        /*��TNR����FINAL MotionMapping����*/

#define HIIOC_PQ_S_TNR_C_FINAL_MOTION_MAPPING  _IOW(HI_ID_PQ, 72, HI_PQ_TNR_S)        /*дTNRɫ��FINAL MotionMapping����*/
#define HIIOC_PQ_G_TNR_C_FINAL_MOTION_MAPPING  _IOWR(HI_ID_PQ, 73, HI_PQ_TNR_S)        /*��TNRɫ��FINAL MotionMapping����*/

#define HIIOC_PQ_S_SNR_PIXMEAN_2_RATIO         _IOW(HI_ID_PQ, 74, HI_PQ_SNR_PIXMEAN_2_RATIO_S)     /*дSNR ��pixmean-ratioӳ������*/
#define HIIOC_PQ_G_SNR_PIXMEAN_2_RATIO         _IOWR(HI_ID_PQ, 75, HI_PQ_SNR_PIXMEAN_2_RATIO_S)     /*��SNR ��pixmean-ratioӳ������*/

#define HIIOC_PQ_S_SNR_PIXDIFF_2_EDGESTR       _IOW(HI_ID_PQ, 76, HI_PQ_SNR_PIXDIFF_2_EDGESTR_S)   /*дSNR ��pixdiff-edgestrӳ������*/
#define HIIOC_PQ_G_SNR_PIXDIFF_2_EDGESTR       _IOWR(HI_ID_PQ, 77, HI_PQ_SNR_PIXDIFF_2_EDGESTR_S)   /*��SNR ��pixdiff-edgestrӳ������*/

#define HIIOC_PQ_S_HD_BRIGHTNESS        _IOW(HI_ID_PQ, 84, HI_U32)                    /* ���ø���BRIGHTNESS level*/
#define HIIOC_PQ_G_HD_BRIGHTNESS        _IOWR(HI_ID_PQ, 85, HI_U32)                    /* ��ȡ����BRIGHTNESS level*/

#define HIIOC_PQ_S_HD_CONTRAST          _IOW(HI_ID_PQ, 86, HI_U32)                    /* ���ø���CONTRAST level*/
#define HIIOC_PQ_G_HD_CONTRAST          _IOWR(HI_ID_PQ, 87, HI_U32)                    /* ��ȡ����CONTRAST level*/

#define HIIOC_PQ_S_HD_SATURATION        _IOW(HI_ID_PQ, 88, HI_U32)                    /* ���ø���SATURATION level*/
#define HIIOC_PQ_G_HD_SATURATION        _IOWR(HI_ID_PQ, 89, HI_U32)                    /* ��ȡ����SATURATION level*/

#define HIIOC_PQ_S_HD_HUE               _IOW(HI_ID_PQ, 90, HI_U32)                    /* ���ø���HUE level*/
#define HIIOC_PQ_G_HD_HUE               _IOWR(HI_ID_PQ, 91, HI_U32)                    /* ��ȡ����HUE level*/

#define HIIOC_PQ_S_DCI_LEVEL            _IOW(HI_ID_PQ, 92, HI_U32)                    /* ����DCI level*/
#define HIIOC_PQ_G_DCI_LEVEL            _IOWR(HI_ID_PQ, 93, HI_U32)                    /* ��ȡDCI level*/

#define HIIOC_PQ_G_BIN_ADDR             _IOWR(HI_ID_PQ, 94, HI_U32)                    /* ��ȡPQBin�������ַ*/

#define HIIOC_PQ_S_COLOR_ENHANCE_MODE   _IOW(HI_ID_PQ, 95, HI_PQ_COLOR_SPEC_MODE_E)   /* ������ɫ��ǿģʽ*/
#define HIIOC_PQ_G_COLOR_ENHANCE_MODE   _IOWR(HI_ID_PQ, 96, HI_PQ_COLOR_SPEC_MODE_E)   /* ��ȡ��ɫ��ǿģʽ*/

#define HIIOC_PQ_S_DEMO_MODE            _IOW(HI_ID_PQ, 99, HI_PQ_DEMO_MODE_E)         /* ���ø��㷨ģ������ģʽ��ʾ��ʽ*/
#define HIIOC_PQ_G_DEMO_MODE            _IOWR(HI_ID_PQ, 100, HI_PQ_DEMO_MODE_E)        /* ��ȡ���㷨ģ������ģʽ��ʾ��ʽ*/

#define HIIOC_PQ_S_GRAPH_SD_PARAM       _IOW(HI_ID_PQ, 101, HI_PQ_IMAGE_PARAM_S)      /* ����ͼ�α������*/
#define HIIOC_PQ_G_GRAPH_SD_PARAM       _IOWR(HI_ID_PQ, 102, HI_PQ_IMAGE_PARAM_S)      /* ��ȡͼ�α������*/

#define HIIOC_PQ_S_GRAPH_HD_PARAM       _IOW(HI_ID_PQ, 103, HI_PQ_IMAGE_PARAM_S)      /* ����ͼ�θ������*/
#define HIIOC_PQ_G_GRAPH_HD_PARAM       _IOWR(HI_ID_PQ, 104, HI_PQ_IMAGE_PARAM_S)      /* ��ȡͼ�θ������*/

#define HIIOC_PQ_S_VIDEO_SD_PARAM       _IOW(HI_ID_PQ, 105, HI_PQ_IMAGE_PARAM_S)      /* ������Ƶ�������*/
#define HIIOC_PQ_G_VIDEO_SD_PARAM       _IOWR(HI_ID_PQ, 106, HI_PQ_IMAGE_PARAM_S)      /* ��ȡ��Ƶ�������*/

#define HIIOC_PQ_S_VIDEO_HD_PARAM       _IOW(HI_ID_PQ, 107, HI_PQ_IMAGE_PARAM_S)      /* ������Ƶ�������*/
#define HIIOC_PQ_G_VIDEO_HD_PARAM       _IOWR(HI_ID_PQ, 108, HI_PQ_IMAGE_PARAM_S)      /* ��ȡ��Ƶ�������*/

#define HIIOC_PQ_S_TNR_FMOTION_MAPPING  _IOW(HI_ID_PQ, 109, HI_PQ_TNR_FMOTION_S)      /*дTNR FMotionMapping ����*/
#define HIIOC_PQ_G_TNR_FMOTION_MAPPING  _IOWR(HI_ID_PQ, 110, HI_PQ_TNR_FMOTION_S)      /*��TNR FMotionMapping ����*/

#define HIIOC_PQ_S_DEFAULT_PARAM        _IOW(HI_ID_PQ, 111, HI_BOOL)                  /*����PQ ��Ĭ��ֵ*/

#define HIIOC_PQ_S_SNR                  _IOW(HI_ID_PQ, 112, HI_U32)                   /* set SNR level*/
#define HIIOC_PQ_G_SNR                  _IOWR(HI_ID_PQ, 113, HI_U32)                   /* get SNR level*/

#define HIIOC_PQ_S_SNR_MEAN_RATIO       _IOW(HI_ID_PQ, 114, HI_PQ_SNR_MEAN_RATIO_S)   /*дSNR ��MEAN RATIOӳ������*/
#define HIIOC_PQ_G_SNR_MEAN_RATIO       _IOWR(HI_ID_PQ, 115, HI_PQ_SNR_MEAN_RATIO_S)   /*��SNR ��MEAN RATIOӳ������*/

#define HIIOC_PQ_S_SNR_EDGE_STR         _IOW(HI_ID_PQ, 116, HI_PQ_SNR_EDGE_STR_S)     /*дSNR ��EDGE STRӳ������*/
#define HIIOC_PQ_G_SNR_EDGE_STR         _IOWR(HI_ID_PQ, 117, HI_PQ_SNR_EDGE_STR_S)     /*��SNR ��EDGE STRӳ������*/

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

#define HIIOC_PQ_S_SD_TEMPERATURE       _IOW(HI_ID_PQ, 142, HI_PQ_COLORTEMPERATURE_S)  /* ���ñ���ɫ��*/
#define HIIOC_PQ_G_SD_TEMPERATURE       _IOWR(HI_ID_PQ,143, HI_PQ_COLORTEMPERATURE_S)  /* ��ȡ����ɫ��*/

#define HIIOC_PQ_S_HD_TEMPERATURE       _IOW(HI_ID_PQ, 144, HI_PQ_COLORTEMPERATURE_S)  /* ���ø���ɫ��*/
#define HIIOC_PQ_G_HD_TEMPERATURE       _IOWR(HI_ID_PQ,145, HI_PQ_COLORTEMPERATURE_S)  /* ��ȡ����ɫ��*/

#define HIIOC_PQ_S_VP_PREVIEW_IMAGE_MODE   _IOW(HI_ID_PQ, 146, HI_DRV_PQ_VP_MODE_E)  /* set VideoPhone Preview mode*/
#define HIIOC_PQ_G_VP_PREVIEW_IMAGE_MODE   _IOWR(HI_ID_PQ, 147, HI_DRV_PQ_VP_MODE_E)  /* get VideoPhone Preview mode*/

#define HIIOC_PQ_S_VP_REMOTE_IMAGE_MODE    _IOW(HI_ID_PQ, 148, HI_DRV_PQ_VP_MODE_E)  /* set VideoPhone Preview mode*/
#define HIIOC_PQ_G_VP_REMOTE_IMAGE_MODE    _IOWR(HI_ID_PQ, 149, HI_DRV_PQ_VP_MODE_E)  /* get VideoPhone Preview mode*/

#define HIIOC_PQ_S_VP_PREVIEW_BRIGHTNESS   _IOW(HI_ID_PQ, 150, HI_U32)     /* ����VPSS PREVIEW BRIGHTNESS level*/
#define HIIOC_PQ_G_VP_PREVIEW_BRIGHTNESS   _IOWR(HI_ID_PQ, 151, HI_U32)     /* ��ȡVPSS PREVIEW BRIGHTNESS level*/

#define HIIOC_PQ_S_VP_PREVIEW_CONTRAST     _IOW(HI_ID_PQ, 152, HI_U32)     /* ����VPSS PREVIEW CONTRAST level*/
#define HIIOC_PQ_G_VP_PREVIEW_CONTRAST     _IOWR(HI_ID_PQ, 153, HI_U32)     /* ��ȡVPSS PREVIEW CONTRAST level*/

#define HIIOC_PQ_S_VP_PREVIEW_SATURATION   _IOW(HI_ID_PQ, 154, HI_U32)     /* ����VPSS PREVIEW SATURATION level*/
#define HIIOC_PQ_G_VP_PREVIEW_SATURATION   _IOWR(HI_ID_PQ, 155, HI_U32)     /* ��ȡVPSS PREVIEW SATURATION level*/

#define HIIOC_PQ_S_VP_PREVIEW_HUE          _IOW(HI_ID_PQ, 156, HI_U32)     /* ����VPSS PREVIEW HUE level*/
#define HIIOC_PQ_G_VP_PREVIEW_HUE          _IOWR(HI_ID_PQ, 157, HI_U32)     /* ��ȡVPSS PREVIEW HUE level*/

#define HIIOC_PQ_S_VP_PREVIEW_VIDEO_PARAM  _IOW(HI_ID_PQ, 158, HI_PQ_IMAGE_PARAM_S)  /* ����VPSS ��Ƶ�������*/
#define HIIOC_PQ_G_VP_PREVIEW_VIDEO_PARAM  _IOWR(HI_ID_PQ, 159, HI_PQ_IMAGE_PARAM_S)  /* ��ȡVPSS ��Ƶ�������*/

#define HIIOC_PQ_S_VP_REMOTE_BRIGHTNESS    _IOW(HI_ID_PQ, 160, HI_U32)     /* ����VPSS REMOTE BRIGHTNESS level*/
#define HIIOC_PQ_G_VP_REMOTE_BRIGHTNESS    _IOWR(HI_ID_PQ, 161, HI_U32)     /* ��ȡVPSS REMOTE BRIGHTNESS level*/

#define HIIOC_PQ_S_VP_REMOTE_CONTRAST      _IOW(HI_ID_PQ, 162, HI_U32)     /* ����VPSS REMOTE CONTRAST level*/
#define HIIOC_PQ_G_VP_REMOTE_CONTRAST      _IOWR(HI_ID_PQ, 163, HI_U32)     /* ��ȡVPSS REMOTE CONTRAST level*/

#define HIIOC_PQ_S_VP_REMOTE_SATURATION    _IOW(HI_ID_PQ, 164, HI_U32)     /* ����VPSS REMOTE SATURATION level*/
#define HIIOC_PQ_G_VP_REMOTE_SATURATION    _IOWR(HI_ID_PQ, 165, HI_U32)     /* ��ȡVPSS REMOTE SATURATION level*/

#define HIIOC_PQ_S_VP_REMOTE_HUE           _IOW(HI_ID_PQ, 166, HI_U32)     /* ����VPSS REMOTE HUE level*/
#define HIIOC_PQ_G_VP_REMOTE_HUE           _IOWR(HI_ID_PQ, 167, HI_U32)     /* ��ȡVPSS REMOTE HUE level*/

#define HIIOC_PQ_S_VP_REMOTE_VIDEO_PARAM   _IOW(HI_ID_PQ, 168, HI_PQ_IMAGE_PARAM_S)  /* ����VPSS ��Ƶ�������*/
#define HIIOC_PQ_G_VP_REMOTE_VIDEO_PARAM   _IOWR(HI_ID_PQ, 169, HI_PQ_IMAGE_PARAM_S)  /* ��ȡVPSS ��Ƶ�������*/

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

#define HIIOC_PQ_S_HDR_DYN_MODE            _IOW(HI_ID_PQ, 194, HI_PQ_HDR_DYN_TM_TUNING_S)    /* set Hdr Dyn Cfg*/
#define HIIOC_PQ_G_HDR_DYN_MODE            _IOWR(HI_ID_PQ, 195, HI_PQ_HDR_DYN_TM_TUNING_S)   /* get Hdr Dyn Cfg*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __HI_DRV_PQ_H__ */
