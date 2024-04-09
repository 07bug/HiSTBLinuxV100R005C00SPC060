/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : drv_pq_ext.h
  Version       : Initial Draft
  Author        : sdk sdk
  Created       : 2014/04/01
  Description   :

******************************************************************************/

#ifndef __DRV_PQ_EXT_V4_H__
#define __DRV_PQ_EXT_V4_H__

#include "hi_type.h"
#include "hi_drv_video.h"
#include "hi_reg_common.h"
#ifndef HI_BUILD_IN_BOOT
#include "hi_drv_dev.h"
#include "drv_pq_ext_hdr.h"
#endif

#include "drv_pq_ext_zme.h"
#include "drv_pq_ext_csc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if defined(CHIP_TYPE_hi3798cv200)
#define ACC_HISTGRAM0_SIZE      3
#define ACC_HISTGRAM1_SIZE      8
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
#define ACC_HISTGRAM0_SIZE      3
#define ACC_HISTGRAM1_SIZE      8
#elif defined(CHIP_TYPE_hi3798mv310)
#define ACC_HISTGRAM0_SIZE      3
#define ACC_HISTGRAM1_SIZE      64
#endif

typedef S_CAS_REGS_TYPE    PQ_VPSS_CFG_REG_S;
typedef S_VPSSWB_REGS_TYPE PQ_VPSS_WBC_REG_S;

/* display ID */
typedef enum hiPQ_DISPLAY_E
{
    HI_PQ_DISPLAY_0 = 0,   /**< DISPLAY0,Compatible with SD */
    HI_PQ_DISPLAY_1,       /**< DISPLAY1, HD */
    HI_PQ_DISPLAY_2,       /**< DISPLAY2, HD, temp not used */
    HI_PQ_DISPLAY_BUTT
} HI_PQ_DISPLAY_E;

/* Layer ID */
typedef enum hiPQ_VDP_LAYER_VID_E
{
    PQ_VDP_LAYER_VID0  = 0, /* VDP_LAYER_V0 */
    PQ_VDP_LAYER_VID1  = 1, /* VDP_LAYER_V1 */
    PQ_VDP_LAYER_VID2  = 2, /* VDP_LAYER_V2 */
    PQ_VDP_LAYER_VID3  = 3, /* VDP_LAYER_V3 */
    PQ_VDP_LAYER_VID4  = 4, /* VDP_LAYER_V4 */

    PQ_VDP_LAYER_VID_BUTT
} HI_PQ_VDP_LAYER_VID_E;


/* VPSS��Ƶ��Ϣ */
typedef struct hiHI_VPSS_PQ_INFO_S
{
    HI_U32              u32Width;           /* ͼ���� */
    HI_U32              u32Height;          /* ͼ��߶� */
    HI_U32              u32FrameRate;       /* ����֡�� */
    HI_BOOL             bInterlace;         /* �Ƿ�����ź� */
} HI_VPSS_PQ_INFO_S;

typedef struct hiHI_VDP_CHANNEL_TIMING_S
{
    HI_RECT_S  stFmtRect;
    HI_U32     u32RefreshRate;
    HI_BOOL    bProgressive;
    HI_DRV_COLOR_SPACE_E enOutColorSpace;
} HI_VDP_CHANNEL_TIMING_S;

/* �㷨��λ�� */
typedef enum hiPQ_ALGIP_SEL_E
{
    HI_PQ_ALGIP_SEL_VDP = 0,   /* Alg Sel Vdp */
    HI_PQ_ALGIP_SEL_VPSS   ,   /* Alg Sel Vpss */

    HI_PQ_ALGIP_SEL_BUTT
} HI_PQ_ALGIP_SEL_E;

/* GRAPH CSC LAYER */
typedef enum hiPQ_GFX_LAYER_E
{
    PQ_GFX_GP0 = 0  , /* HD */
    PQ_GFX_GP1      , /* SD */
    PQ_GFX_WBC_GP   ,

    PQ_GFX_LAYER_BUTT
} HI_PQ_GFX_LAYER_E;


/* DCIͳ�ƴ��� */
typedef struct  hiPQ_DCI_WIN_S
{
    HI_U16      u16HStar;
    HI_U16      u16HEnd;
    HI_U16      u16VStar;
    HI_U16      u16VEnd;
} HI_PQ_DCI_WIN_S;

typedef struct
{
    HI_S32 IsProgressiveSeq;
    HI_S32 IsProgressiveFrm;
    HI_S32 RealFrmRate;

} PQ_VDEC_INFO_S;

typedef enum hiDRV_PQ_MCDI_SPLIT_MODE_E
{
    HI_DRV_PQ_MCDI_SPLIT_MODE_0 = 0, /* Mcdi Split Mode */
    HI_DRV_PQ_MCDI_SPLIT_MODE_1 = 1, /* Mcdi Split Mode */
    HI_DRV_PQ_MCDI_SPLIT_MODE_2 = 2, /* Mcdi Split Mode */
    HI_DRV_PQ_MCDI_SPLIT_MODE_3 = 3, /* Mcdi Split Mode */
    HI_DRV_PQ_MCDI_SPLIT_MODE_4 = 4, /* Mcdi Split Mode */
    HI_DRV_PQ_MCDI_SPLIT_MODE_5 = 5, /* Mcdi Split Mode */

    HI_DRV_PQ_MCDI_SPLIT_MODE_BUTT
} HI_DRV_PQ_MCDI_SPLIT_MODE_E;

/* IFMD���㷨�����������������VPSS->PQ */
typedef struct hi_PQ_IFMD_CALC_S
{
    HI_U32  u32HandleNo;
    HI_U32  u32WidthY;
    HI_U32  u32HeightY;
    HI_S32  s32FieldOrder;                 /* ���׳��� �������ȵ׳����� */
    HI_S32  s32FieldMode;                  /* ���׳���־ */
    HI_U32  u32FrameRate;
    HI_BOOL bPreInfo;                      /* DEI�߼�����timeout���Ծɴ�����һ�� */
    HI_DRV_PQ_MCDI_SPLIT_MODE_E enSplitMode; /*Mcdei �Ƿ�ʹ�ò��ģʽ����FHD���Ϊ���SD֡����*/
    PQ_VDEC_INFO_S      stVdecInfo;
    S_VPSSWB_REGS_TYPE *pstIfmdHardOutReg; /* ��ȡifmd��״̬�Ĵ��� */

} HI_PQ_IFMD_CALC_S;

typedef struct
{
    HI_S32  die_reset;
    HI_S32  die_stop;
    HI_S32  dir_mch;
    HI_S32  die_out_sel;
    HI_S32  jud_en;
    //HI_S32  ChromaVertFltEn;
    HI_S32  s32FieldOrder;    /* ���س��� */
    HI_S32  s32SceneChanged;  /* �����л���Ϣ */
    HI_S32  s32FilmType;      /* ��Ӱģʽ */
    HI_U32  u32KeyValue;      /* �ؼ�֡ */
    HI_U32  u32EdgeSmoothEn;

} HI_PQ_IFMD_PLAYBACK_S;

/* Brightness/Contrast/Hue/Saturation setting */
typedef struct hiPQ_PICTURE_SETTING_S
{
    HI_U16 u16Brightness;
    HI_U16 u16Contrast;
    HI_U16 u16Hue;
    HI_U16 u16Saturation;
} HI_PQ_PICTURE_SETTING_S;

/* Vdec����Э��; 0: H265, 1: H264, 2: Mpeg2, 3: VP9, 4: mndet */
typedef enum hiPQ_VDEC_PROTOCOL_E
{
    HI_PQ_VDEC_PROTOCOL_H265 = 0,
    HI_PQ_VDEC_PROTOCOL_H264    ,
    HI_PQ_VDEC_PROTOCOL_MPEG2   ,
    HI_PQ_VDEC_PROTOCOL_VP9     ,
    HI_PQ_VDEC_PROTOCOL_MNDET   ,

    HI_PQ_VDEC_PROTOCOL_BUTT    ,

} HI_PQ_VDEC_PROTOCOL_E;

/* VDP��Ƶ��Ϣ */
typedef struct hiHI_VDP_PQ_INFO_S
{
    HI_PQ_VDP_LAYER_VID_E       enLayerId;          /* ͨ���µĲ� */
    HI_U32                      u32Width;           /* ͼ���� */
    HI_U32                      u32Height;          /* ͼ��߶� */
    HI_U32                      u32FrameRate;       /* ����֡�� */
    HI_BOOL                     bInterlace;         /* �Ƿ�����ź� */
    HI_BOOL                     bSRState;           /* SR ���� */
    HI_BOOL                     bIsogenyMode;       /* �Ƿ�ͬԴģʽ */
    HI_BOOL                     bHdrMode;           /* �Ƿ�hdrģʽ*/
    HI_BOOL                     bPartUpdate;        /* �Ƿ񲿷ָ��²��� */
    HI_BOOL                     b3dType;            /* �Ƿ�3D���� */
    HI_VDP_CHANNEL_TIMING_S     stChannelTiming[HI_PQ_DISPLAY_BUTT];
    HI_RECT_S                   stVideo;            /* ��Чͼ������ */
} HI_VDP_PQ_INFO_S;

typedef struct hiPQ_VPSS_MODULE_S
{
    HI_PQ_SCENEMODE_E           enSceneMode;

} HI_PQ_VPSS_MODULE_S;

/* VPSS �����������Ϣ */
typedef struct hiPQ_WBC_INFO_S
{
    /* Common */
    HI_U32    u32HandleNo;
    HI_U32    u32BitDepth;              /* ͨ·����λ�� */
    HI_U32    u32Width;                 /* ʵ�ʴ���Ŀ�� */
    HI_U32    u32Height;                /* ʵ�ʴ���ĸ߶� */
    HI_RECT_S stOriCoordinate;          /* ԭͼ���� */
    HI_RECT_S stCropCoordinate;         /* Crop֮������ */
    HI_BOOL   bProgressive;             /* ��������Ϣ */
    HI_S32    s32FieldMode;             /* ��ǰ�����Ա�ʶ: 0:Top; 1:Bottom */
    HI_U32    u32DeiEnFlag;             /* DEI ʹ�ܱ�ʶ */
    HI_BOOL   bMcnrEnableFlag;          /* MCNR ʹ�ܱ�־, tile,rwzb disable mcnr */
    S_VPSSWB_REGS_TYPE *pstVPSSWbcReg;  /* ifmd��Globlal Motion and DB�Ļ�д��Ϣ */

    /* GlobalMotion */
    HI_U32   u32Scd;
    HI_U32   stride;
    HI_VOID *pRGMV;

    /* IFMD */
    HI_S32   s32FieldOrder;              /* ���׳��� �������ȵ׳����� */
    HI_U32   u32FrameRate;               /* ֡�� */
    HI_BOOL  bPreInfo;                   /* DEI�߼�����timeout, �Ծɴ�����һ�� */
    PQ_VDEC_INFO_S stVdecInfo;           /* VDEC ���ݵĸ�������Ϣ */

    /* DNR */
    HI_BOOL bCropBeforeDB;               /* 0: ��DB֮��Crop;1: ��DB ֮ǰCrop */
    HI_U32  u32SingleModeFlag;           /* ����ģʽ��ʶ; 1:����;0:�ǵ��� */
    HI_U32  u32Protocol;                 /* ����Э�� */
    HI_U32  u32ImageAvgQP;               /* ͼ��ƽ�� QP */
    HI_U32  u32VdhInfoAddr;              /* dbinfo ��ַ */
    HI_U32  u32VdhInfoStride;            /* ��Ϣstride, �㷨Լ��Ϊ(ͼ����+7)/8 */
    HI_U32  u32ImageStruct;              /* ֡/�������ʶ */

    HI_DRV_PQ_MCDI_SPLIT_MODE_E enSplitMode; /*Mcdei �Ƿ�ʹ�ò��ģʽ����FHD���Ϊ���SD֡����*/
    HI_U32  u32StreamId;                /* ����ʶ���ʶ */
    HI_U32  u32FrameIndex;

} HI_PQ_WBC_INFO_S;

/* PQ Calc ����VPSS��������Ϣ */
typedef struct hiPQ_CFG_INFO_S
{
    /* GlobalMotion */

    /* IFMD */
    HI_S32  die_reset;
    HI_S32  die_stop;
    HI_S32  dir_mch;
    HI_S32  die_out_sel;
    HI_S32  jud_en;
    HI_S32  ChromaVertFltEn;
    HI_S32  s32FieldOrder;    /* ���س��� */
    HI_S32  s32SceneChanged;  /* �����л���Ϣ */
    HI_S32  s32FilmType;      /* ��Ӱģʽ */
    HI_U32  u32KeyValue;      /* �ؼ�֡ */
    /* DNR */

} HI_PQ_CFG_INFO_S;

typedef struct hiPQ_VDP_WBC_INFO_S
{
    /* Common */
    HI_PQ_VDP_LAYER_VID_E  enLayerId;          /* �� */
    HI_U32                 u32BitDepth;        /* ͨ·����λ�� */
    HI_RECT_S              stOriCoordinate;    /* Crop֮ǰ���� */
    HI_RECT_S              stCropCoordinate;   /* Crop֮������ */
    HI_PQ_ALGIP_SEL_E      enAlgIPSel;         /* �㷨��λ�� */
    S_VPSSWB_REGS_TYPE    *pstVdpWbcReg;       /* ifmd��Globlal Motion and DB�Ļ�д��Ϣ */
    HI_U32                 u32VdpWbcRegPhyAddr;

    /* DNR */
    HI_BOOL                bCropBeforeDB;      /* 0: ��DB֮��Crop;1: ��DB ֮ǰCrop */
    HI_U32                 u32SingleModeFlag;  /* ����ģʽ��ʶ; 1:����;0:�ǵ��� */
    HI_U32                 u32ImageAvgQP;      /* ͼ��ƽ�� QP */
    HI_U32                 u32VdhInfoAddr;     /* dbinfo ��ַ */
    HI_U32                 u32VdhInfoStride;   /* ��Ϣstride, �㷨Լ��Ϊ(ͼ����+7)/8 */
    HI_U32                 u32ImageStruct;     /* ֡/�������ʶ */
    HI_PQ_VDEC_PROTOCOL_E  enVdecProtocol;     /* ����Э�� */

} HI_PQ_VDP_WBC_INFO_S;

typedef struct
{
    HI_U16  u16GammCoef[1024];
} HI_PQ_GAMM_PARA_S;

typedef struct hiPQ_ACC_HISTGRAM_S
{
    HI_U32 u32HistGram0[ACC_HISTGRAM0_SIZE];
    HI_U32 u32HistGram1[ACC_HISTGRAM1_SIZE];
} HI_PQ_ACC_HISTGRAM_S;

#ifndef HI_BUILD_IN_BOOT

typedef HI_S32 (*FN_PQ_Suspend) (PM_BASEDEV_S *pdev, pm_message_t state);
typedef HI_S32 (*FN_PQ_Resume) (PM_BASEDEV_S *pdev);
typedef HI_S32 (*FN_PQ_UpdateVpssPQ)(HI_U32 u32HandleNo, HI_VPSS_PQ_INFO_S *pstTimingInfo, PQ_VPSS_CFG_REG_S *pstVPSSReg, PQ_VPSS_WBC_REG_S *pstWbcReg, HI_PQ_VPSS_MODULE_S *pstPQModule);
typedef HI_S32 (*FN_PQ_UpdateVdpPQ)(HI_PQ_DISPLAY_E enDisplayId, HI_VDP_PQ_INFO_S *pstTimingInfo, S_VDP_REGS_TYPE *pstVDPReg);
typedef HI_S32 (*FN_PQ_UpdateVdpCSC)(HI_PQ_CSC_TYPE_E enCscTypeId, HI_PQ_VDP_CSC_S *pstCscMode);
typedef HI_S32 (*FN_PQ_UpdateDCIWin)(HI_PQ_DCI_WIN_S *pstWin, HI_BOOL bDciEnable);
typedef HI_S32 (*FN_PQ_GetACCHistGram)(HI_PQ_ACC_HISTGRAM_S *pstACCHistGram);
typedef HI_S32 (*FN_PQ_UpdateACCHistGram)(HI_PQ_ACC_HISTGRAM_S *pstACCHistGram);
typedef HI_S32 (*FN_PQ_SetZme)(HI_PQ_ZME_LAYER_E u32LayerId, HI_PQ_ZME_PARA_IN_S *pstZmeDrvPara, HI_BOOL  bFirEnable);
typedef HI_S32 (*FN_PQ_SetVpssZme)(HI_PQ_VPSS_ZME_LAYER_E e32LayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_ZME_PARA_IN_S *pstZmeDrvPara, HI_BOOL  bFirEnable);
typedef HI_S32 (*FN_PQ_SetVpssLCHDR)(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo);
typedef HI_S32 (*FN_PQ_GetCSCCoef)(HI_PQ_CSC_CRTL_S *pstCscCtrl, HI_PQ_CSC_MODE_E enCscMode, HI_PQ_CSC_COEF_S *pstCscCoef, HI_PQ_CSC_DCCOEF_S *pstCscDcCoef);
typedef HI_S32 (*FN_PQ_Get8BitCSCCoef)(HI_PQ_CSC_MODE_E  enCSCMode, HI_PQ_CSC_COEF_S *pstCSCCoef, HI_PQ_CSC_DCCOEF_S *pstCSCDCCoef);
typedef HI_S32 (*FN_PQ_GetWbcInfo)(HI_PQ_WBC_INFO_S *pstVpssWbcInfo);
typedef HI_S32 (*FN_PQ_SetAlgCalcCfg)(HI_PQ_WBC_INFO_S *pstVpssWbcInfo, HI_PQ_CFG_INFO_S *pstVpssCfgInfo);
typedef HI_S32 (*FN_PQ_SetVdpAlgCalcCfg)(HI_PQ_VDP_WBC_INFO_S *pstVdpWbcInfo);
typedef HI_S32 (*FN_PQ_GetSetting)(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);
typedef HI_S32 (*FN_PQ_SetSetting)(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);
typedef HI_S32 (*FN_PQ_GetVdpZmeCoef)(HI_PQ_ZME_COEF_RATIO_E enCoefRatio, HI_PQ_ZME_COEF_TYPE_E enCoefType, HI_PQ_ZME_TAP_E enZmeTap, HI_S16 *ps16Coef);
typedef HI_S32 (*FN_PQ_GetVdpZmeStrategy) (HI_PQ_ZME_LAYER_E enLayerId, HI_PQ_ZME_STRATEGY_IN_U *pstZmeIn, HI_PQ_ZME_STRATEGY_OUT_U *pstZmeOut);
typedef HI_S32 (*FN_PQ_SetGfxZme) (HI_PQ_GFX_LAYER_E enGfxZmeLayer, HI_PQ_GFX_ZME_PARA_S *pstGfxZmePara);
typedef HI_S32 (*FN_PQ_GetGfxHdrCfg) (HI_PQ_GFXHDR_HDR_INFO *pstGfxHdrInfo, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg);
typedef HI_S32 (*FN_PQ_SetGfxCscCoef) (HI_PQ_GFX_LAYER_E enGfxCscLayer, HI_PQ_GFX_CSC_PARA_S *pstGfxCscPara);
typedef HI_S32 (*FN_PQ_GetHdrCfg) (HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo, HI_PQ_HDR_CFG *pstPqHdrCfg);
typedef HI_S32 (*FN_PQ_GetMcdiSplitMode)(HI_U32 u32HandleNo, HI_DRV_PQ_MCDI_SPLIT_MODE_E *penSplitMode);

typedef struct tagPQ_EXPORT_FUNC_S
{
    FN_PQ_Suspend                 pfnPqSuspend;
    FN_PQ_Resume                  pfnPqResume;
    FN_PQ_UpdateVpssPQ            pfnPQ_UpdateVpssPQ;
    FN_PQ_UpdateVdpPQ             pfnPQ_UpdateVdpPQ;
    FN_PQ_UpdateVdpCSC            pfnPQ_UpdateVdpCSC;
    FN_PQ_UpdateDCIWin            pfnPQ_UpdateDCIWin;
    FN_PQ_GetACCHistGram          pfnPQ_GetACCHistGram;
    FN_PQ_UpdateACCHistGram       pfnPQ_UpdateACCHistGram;
    FN_PQ_SetZme                  pfnPQ_SetZme;
    FN_PQ_SetVpssZme              pfnPQ_SetVpssZme;
    FN_PQ_SetVpssLCHDR            pfnPQ_SetVpssLCHDR;
    FN_PQ_GetCSCCoef              pfnPQ_GetCSCCoef;
    FN_PQ_Get8BitCSCCoef          pfnPQ_Get8BitCSCCoef;
    FN_PQ_GetWbcInfo              pfnPQ_GetWbcInfo;
    FN_PQ_SetAlgCalcCfg           pfnPQ_SetAlgCalcCfg;
    FN_PQ_SetVdpAlgCalcCfg        pfnPQ_SetVdpAlgCalcCfg;
    FN_PQ_GetSetting              pfnPQ_GetHDPictureSetting;
    FN_PQ_GetSetting              pfnPQ_GetSDPictureSetting;
    FN_PQ_SetSetting              pfnPQ_SetHDPictureSetting;
    FN_PQ_SetSetting              pfnPQ_SetSDPictureSetting;
    FN_PQ_GetSetting              pfnPQ_GetHDVideoSetting;
    FN_PQ_GetSetting              pfnPQ_GetSDVideoSetting;
    FN_PQ_SetSetting              pfnPQ_SetHDVideoSetting;
    FN_PQ_SetSetting              pfnPQ_SetSDVideoSetting;
    FN_PQ_GetVdpZmeCoef           pfnPQ_GetVdpZmeCoef;
    FN_PQ_GetVdpZmeStrategy       pfnPQ_GetVdpZmeStrategy;
    FN_PQ_SetGfxZme               pfnPQ_SetGfxZme;
    FN_PQ_SetGfxCscCoef           pfnPQ_SetGfxCscCoef;
    FN_PQ_GetGfxHdrCfg            pfnPQ_GetGfxHdrCfg;
    FN_PQ_GetHdrCfg               pfnPQ_GetHdrCfg;
    FN_PQ_GetMcdiSplitMode        pfnPQ_GetMcdiSplitMode;
} PQ_EXPORT_FUNC_S;


HI_S32  PQ_DRV_ModInit(HI_VOID);

HI_VOID PQ_DRV_ModuleExit(HI_VOID);

HI_S32  HI_DRV_PQ_Init(HI_CHAR *pszPath);

HI_S32  HI_DRV_PQ_DeInit(HI_VOID);


/**
\brief Timming�仯�����VPSS PQ��������
\attention \n
��

\param[in] *u32HandleNo:VPSSͨ����
\param[in] *pstTimingInfo: Timming Info
\param[in] *pstVPSSReg:VPSS ����Ĵ�����ַ�����ΪNULL�����ʾ���ٸ�·��ַ,
һ��handleNo��Ӧһ����ַ������ַ�����仯���Ż����¸���ʼֵ�����򲻸���ʼֵ��
\param[out] *pstPQModule:PQ���������Ŀ��ز���

\retval ::HI_SUCCESS

*/

HI_S32 DRV_PQ_UpdateVpssPQ(HI_U32 u32HandleNo, HI_VPSS_PQ_INFO_S *pstTimingInfo, PQ_VPSS_CFG_REG_S *pstVPSSReg, PQ_VPSS_WBC_REG_S *pstWbcReg, HI_PQ_VPSS_MODULE_S *pstPQModule);

/**
 \brief Timming�仯�����VDP PQ��������
 \attention \n
��

 \param[in] u32DisplayId
 \param[in] pstTimingInfo: Timming Info
 \param[in] *pstVDPReg:VDP ����Ĵ�����ַ

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_UpdateVdpPQ(HI_PQ_DISPLAY_E enDisplayId, HI_VDP_PQ_INFO_S *pstTimingInfo, S_VDP_REGS_TYPE *pstVDPReg);

/**
 \brief ����VDP��ͨ����CSC
 \attention \n
��

 \param[in] enDisplayId:
 \param[in] pstCscMode: ɫ�ʿռ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateVdpCSC(HI_PQ_CSC_TYPE_E enCscTypeId, HI_PQ_VDP_CSC_S *pstCscMode);

/**
 \brief ����DCIֱ��ͼͳ�ƴ���
 \attention \n
��

 \param[in] *pstWin;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateDCIWin(HI_PQ_DCI_WIN_S *pstWin, HI_BOOL bDciEnable);

/**
 \brief ����ZME
 \attention \n
��

 \param[in] u32LayerId:
 \param[in] pstZmeDrvPara:
 \param[in] bFirEnable

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetZme(HI_PQ_ZME_LAYER_E e32LayerId, HI_PQ_ZME_PARA_IN_S *pstZmeDrvPara, HI_BOOL bFirEnable);

/**
 \brief ����ZME
 \attention \n
��

 \param[in] u32LayerId:
 \param[in] pstZmeDrvPara:
 \param[in] bFirEnable

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetVpssZme(HI_PQ_VPSS_ZME_LAYER_E e32LayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_ZME_PARA_IN_S *pstZmeDrvPara, HI_BOOL bFirEnable);


/**
 \brief ����LCHDR
 \attention \n
��

 \param[in] u32LayerId:
 \param[in] pstReg:
 \param[in] pstXdrFrameInfo

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetVpssLCHDR(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo);

/**
 \brief ��ȡCSCϵ��
 \attention \n
��

 \param[in] enCSCMode:
 \param[out] pstCSCCoef:
 \param[out] pstCSCDCCoef:

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetCSCCoef(HI_PQ_CSC_CRTL_S *pstCscCtrl, HI_PQ_CSC_MODE_E enCscMode, HI_PQ_CSC_COEF_S *pstCscCoef, HI_PQ_CSC_DCCOEF_S *pstCscDcCoef);

/**
 \brief ��ȡ8bit CSCϵ��
 \attention \n
��

 \param[in] enCSCMode:
 \param[out] pstCSCCoef:
 \param[out] pstCSCDCCoef:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_Get8BitCSCCoef(HI_PQ_CSC_MODE_E enCSCMode, HI_PQ_CSC_COEF_S *pstCSCCoef, HI_PQ_CSC_DCCOEF_S *pstCSCDCCoef);


/**
 \brief �����㷨������֮��ļĴ���
 \attention \n
��

 \param[in]  *pstWbcInfo
 \param[out]
 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetAlgCalcCfg(HI_PQ_WBC_INFO_S *pstVpssWbcInfo, HI_PQ_CFG_INFO_S *pstVpssCfgInfo);

/**
 \brief �����㷨������֮��ļĴ���
 \attention \n
��

 \param[in]  *pstWbcInfo
 \param[out]
 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetVdpAlgCalcCfg(HI_PQ_VDP_WBC_INFO_S *pstVdpWbcInfo);

/**
 \brief ��ȡWbcInfo��Ϣ
 \attention \n
��

 \param[in]  HI_PQ_WBC_INFO_S* pstWbcInfo

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetWbcInfo(HI_PQ_WBC_INFO_S *pstVpssWbcInfo);


/**
 \brief ��ȡͼ�θ�������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);

/**
 \brief ��ȡͼ�α�������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);


/**
 \brief ����ͼ�θ�������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);

/**
 \brief ����ͼ�α�������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);

/**
 \brief ��ȡ��Ƶ��������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);

/**
 \brief ��ȡ��Ƶ��������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);


/**
 \brief ������Ƶ��������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);

/**
 \brief ������Ƶ��������/�Աȶ�/ɫ��/���Ͷ�
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting);

/**
 \brief ��ȡ��Ƶͨ����������/�Աȶ�/ɫ��/���Ͷ�
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetVPPreviewVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting);

/**
 \brief ������Ƶͨ����������/�Աȶ�/ɫ��/���Ͷ�
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetVPPreviewVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting);

/**
 \brief ��ȡ��Ƶͨ��Զ������/�Աȶ�/ɫ��/���Ͷ�
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetVPRemoteVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting);

/**
 \brief ������Ƶͨ��Զ������/�Աȶ�/ɫ��/���Ͷ�
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetVPRemoteVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting);

/**
 \brief ��ȡVPSS MCDI �ֿ����
��

 \param[in] �ֿ����0 ��1 : ���ֿ飻5 : ��Ϊ5 ��

 \retval ::

 */
HI_S32 DRV_PQ_GetMcdiSplitMode(HI_U32 u32HandleNo, HI_DRV_PQ_MCDI_SPLIT_MODE_E *penSplitMode);

HI_S32 DRV_PQ_GetVdpZmeCoef(HI_PQ_ZME_COEF_RATIO_E enCoefRatio, HI_PQ_ZME_COEF_TYPE_E enCoefType, HI_PQ_ZME_TAP_E enZmeTap, HI_S16 *ps16Coef);

HI_S32 DRV_PQ_GetVdpZmeStrategy (HI_PQ_ZME_LAYER_E enLayerId, HI_PQ_ZME_STRATEGY_IN_U *pstZmeIn, HI_PQ_ZME_STRATEGY_OUT_U *pstZmeOut);

HI_S32 DRV_PQ_GetHdrCfg(HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo, HI_PQ_HDR_CFG *pstPqHdrCfg);

HI_S32 DRV_PQ_GetGfxHdrCfg(HI_PQ_GFXHDR_HDR_INFO *pstGfxHdrInfo, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg);

HI_S32 DRV_PQ_SetDefaultParam(HI_BOOL bDefault);

HI_S32 DRV_PQ_GetACCHistGram(HI_PQ_ACC_HISTGRAM_S *pstACCHistGram);

HI_S32 DRV_PQ_UpdateACCHistGram(HI_PQ_ACC_HISTGRAM_S *pstACCHistGram);

#endif

HI_S32 DRV_PQ_InitGfxZme(HI_VOID);

HI_S32 DRV_PQ_SetGfxZme(HI_PQ_GFX_LAYER_E enGfxZmeLayer, HI_PQ_GFX_ZME_PARA_S *pstGfxZmePara);

HI_S32 DRV_PQ_SetGfxCscCoef(HI_PQ_GFX_LAYER_E enGfxCscLayer, HI_PQ_GFX_CSC_PARA_S *pstGfxCscPara);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_PQ_EXT_H__ */
