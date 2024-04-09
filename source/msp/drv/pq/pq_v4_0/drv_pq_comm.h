/******************************************************************************

  Copyright (C), 2015, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_pq_comm.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2015/9/7
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_COMM_H__
#define __PQ_MNG_COMM_H__

#include "drv_pq_ext.h"
#include "hi_drv_pq.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define NUM2LEVEL(Num)   (((Num) * 100 + 127) / 255)
#define LEVEL2NUM(Level) (((Level) * 255 + 50) / 100)

#define ALG_NAME_MAX_LEN 32
#define GET_ALG(AlgID)  PQ_COMM_GetAlg(AlgID)
#define GET_ALG_FUN(AlgID)  PQ_COMM_GetAlg(AlgID)->pFun
#define PQ_FUNC_CALL(alg, func)(GET_ALG(alg) && GET_ALG_FUN(alg)->func)

/*PQ Reg Type*/
typedef enum hiPQ_REG_TYPE_E
{
    REG_TYPE_VPSS = 0,
    REG_TYPE_VDP  = 1,
    REG_TYPE_ALL  = 2,

    REG_TYPE_BUTT,
} PQ_REG_TYPE_E;

/**enum define about ZME enable mode*/
typedef enum hiPQ_ZME_MODE_E
{
    PQ_ZME_MODE_VDP_FIR  = 0,  /**< VDP ZME fir mode */
    PQ_ZME_MODE_VDP_MED  = 1,  /**< VDP ZME med mode */
    PQ_ZME_MODE_VPSS_FIR = 2,  /**< VPSS ZME fir mode  */
    PQ_ZME_MODE_VPSS_MED = 3,  /**< VPSS ZME med mode  */

    PQ_ZME_MODE_BUTT
} PQ_ZME_MODE_E;

typedef enum
{
    PQ_DEMO_ENABLE_L = 0,
    PQ_DEMO_ENABLE_R,

    PQ_DEMO_BUTT
} PQ_DEMO_MODE_E;

typedef enum hiPQ_BIN_ADAPT_TYPE_E
{
    PQ_BIN_ADAPT_SINGLE = 0,
    PQ_BIN_ADAPT_MULTIPLE,

    PQ_BIN_ADAPT_BUTT
} PQ_BIN_ADAPT_TYPE_E;

typedef enum hiPQ_DIE_OUT_MODE_E
{
    PQ_DIE_OUT_MODE_AUTO = 0,
    PQ_DIE_OUT_MODE_FIR,
    PQ_DIE_OUT_MODE_COPY,

    PQ_DIE_OUT_MODE_BUTT
} HI_PQ_DIE_OUT_MODE_E;

typedef enum hiPQ_FOD_MODE_E
{
    PQ_FOD_ENABLE_AUTO  = 1,
    PQ_FOD_TOP_FIRST    = 2,
    PQ_FOD_BOTTOM_FIRST = 3,

    PQ_FOD_MODE_BUTT
} HI_PQ_FOD_MODE_E;

typedef enum HiPQ_TUN_MODE_E
{
    PQ_TUN_NORMAL  = 0,
    PQ_TUN_DEBUG      ,

    PQ_TUN_BUTT
} PQ_TUN_MODE_E;

typedef enum hiPQ_LAYER_VP_E
{
    PQ_VDP_LAYER_VP0   = 0,
    PQ_VDP_LAYER_VP1   = 1,
    PQ_VDP_LAYER_DHD0  = 2,

    PQ_VDP_LAYER_VP_BUTT

} PQ_LAYER_VP_E;

typedef enum hiPQ_COMM_IMAGE_MODE_E
{
    PQ_IMAGE_MODE_NORMAL     = 0,
    PQ_IMAGE_MODE_VIDEOPHONE = 1,
    PQ_IMAGE_MODE_GALLERY    = 2,

    PQ_IMAGE_MODE_BUTT,
} PQ_COMM_IMAGE_MODE_E;
/*PQ status info*/
typedef struct  hiPQ_STATUS_S
{
    HI_BOOL                     bIsogenyMode;
    HI_BOOL                     b3dType;
    HI_VDP_CHANNEL_TIMING_S     stTimingInfo[HI_PQ_DISPLAY_BUTT];
    PQ_TUN_MODE_E               enTunMode;
    PQ_COMM_IMAGE_MODE_E        enImageMode;
} PQ_STATUS_S;


/* VPSS WBC ���ݸ�De-Blocking����������Ϣ */
typedef struct hiPQ_DB_CALC_INFO_S
{
    HI_U32  u32HandleNo;

    HI_U32  u32BitDepth;            /* ͨ·����λ�� */
    HI_U32  u32Width;               /* ʵ�ʴ���Ŀ�� */
    HI_U32  u32Height;              /* ʵ�ʴ���ĸ߶� */
    HI_U32  u32LeftOffset;
    HI_U32  u32TopOffset;
    HI_U32  u32RightOffset;
    HI_U32  u32BottomOffset;

    HI_BOOL bDbBlkPosModeEn;        /* VDH ��Ϣʹ�� */
    HI_BOOL bDbFltDetModeEn;        /* ��⿪�� */
    HI_BOOL bDBLumHorEn;            /* ˮƽ�˲����� */
    HI_BOOL bDBLumVerEn;            /* ��ֱ�˲����� */

    HI_U32  u32SingleModeFlag;      /* ����ģʽ��ʶ; 1:����;0:�ǵ��� */
    HI_U32  u32DBDeiEnFlag;         /* DEI ʹ�ܱ�ʶ */

    HI_U32  u32Protocol;            /* ����Э�� */
    HI_U32  u32ImageAvgQP;          /* ͼ��ƽ�� QP */
    HI_U32  u32VdhInfoAddr;         /* dbinfo ��ַ */
    HI_U32  u32VdhInfoStride;       /* ��Ϣstride, �㷨Լ��Ϊ(ͼ����+7)/8 */
    HI_U32  u32ImageStruct;         /* ֡/�������ʶ */
    HI_U32  u32FlagLine;            /* ��ǰ�����Ա�ʶ */

    S_STT_REGS_TYPE *pstVPSSWbcReg;

    HI_DRV_PQ_MCDI_SPLIT_MODE_E enSplitMode; /* �ֿ�ģʽ */
} HI_PQ_DB_CALC_INFO_S;

typedef enum hiPQ_SOURCE_MODE_E
{
    PQ_SOURCE_MODE_NO = 0,
    PQ_SOURCE_MODE_SD,
    PQ_SOURCE_MODE_HD,
    PQ_SOURCE_MODE_UHD,

    PQ_SOURCE_MODE_BUTT,
} PQ_SOURCE_MODE_E;

typedef enum hiPQ_OUTPUT_MODE_E
{
    PQ_OUTPUT_MODE_NO = 0,
    PQ_OUTPUT_MODE_SD,
    PQ_OUTPUT_MODE_HD,
    PQ_OUTPUT_MODE_UHD,
    OUTPUT_MODE_PREVIEW,
    OUTPUT_MODE_REMOTE,

    PQ_OUTPUT_MODE_BUTT,
} PQ_OUTPUT_MODE_E;


typedef struct hiPQ_ALG_FUNCS_S
{
    /*common*/
    HI_S32 (*Init)            (PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault);
    HI_S32 (*DeInit)          (HI_VOID);
    HI_S32 (*SetEnable)       (HI_BOOL bOnOff);
    HI_S32 (*GetEnable)       (HI_BOOL *pbOnOff);
    HI_S32 (*SetStrength)     (HI_U32 u32Strength);
    HI_S32 (*GetStrength)     (HI_U32 *pu32Strength);
    HI_S32 (*SetDemo)         (HI_BOOL bOnOff);
    HI_S32 (*GetDemo)         (HI_BOOL *pbOnOff);
    HI_S32 (*SetDemoMode)     (PQ_DEMO_MODE_E enMode);
    HI_S32 (*GetDemoMode)     (PQ_DEMO_MODE_E *penMode);
    HI_S32 (*SetDemoModeCoor) (HI_U32 u32XPos);
    HI_S32 (*SetTunMode)      (PQ_TUN_MODE_E enTunMode);
    HI_S32 (*GetTunMode)      (PQ_TUN_MODE_E *penTunMode);
    HI_S32 (*SetIsogenyMode)  (HI_BOOL bIsogenyMode);
    HI_S32 (*GetIsogenyMode)  (HI_BOOL *pbIsogenyMode);
    HI_S32 (*SetResume)       (HI_BOOL bDefault);
    /*CSC*/
    HI_S32 (*GetCSCMode)         (HI_PQ_CSC_TYPE_E enCscTypeId, HI_PQ_VDP_CSC_S *pstCscMode);
    HI_S32 (*GetCSCVideoSetting) (HI_PQ_DISPLAY_E enDisp, HI_PQ_PICTURE_SETTING_S *pstPicSetting);
    HI_S32 (*SetCSCVideoSetting) (HI_PQ_DISPLAY_E enDisp, HI_PQ_PICTURE_SETTING_S *pstPicSetting);
    HI_S32 (*GetCSCCoef)         (HI_PQ_CSC_CRTL_S *pstCscCtrl, HI_PQ_CSC_MODE_E enCscMode, HI_PQ_CSC_COEF_S *pstCscCoef, HI_PQ_CSC_DCCOEF_S *pstCscDcCoef);
    HI_S32 (*Get8BitCSCCoef)     (HI_PQ_CSC_MODE_E  enMode, HI_PQ_CSC_COEF_S *pstCoef, HI_PQ_CSC_DCCOEF_S *pstDCCoef);
    HI_S32 (*GetColorTemp)       (HI_PQ_COLORTEMPERATURE_S *pstTemperature);
    HI_S32 (*SetColorTemp)       (HI_PQ_COLORTEMPERATURE_S *pstTemperature);
    /*GFX CSC*/
    HI_S32 (*SetGfxCscCoef)           (HI_PQ_GFX_LAYER_E enGfxCscLayer, HI_PQ_GFX_CSC_PARA_S *pstGfxCscPara);
    HI_S32 (*GetGfxCSCPictureSetting) (HI_PQ_DISPLAY_E enDisp, HI_PQ_PICTURE_SETTING_S *pstPicSetting);
    HI_S32 (*SetGfxCSCPictureSetting) (HI_PQ_DISPLAY_E enDisp, HI_PQ_PICTURE_SETTING_S *pstPicSetting);
    /*ZME*/
    HI_S32 (*SetZmeEnMode)      (PQ_ZME_MODE_E enMode, HI_BOOL bOnOff);
    HI_S32 (*GetZmeEnMode)      (PQ_ZME_MODE_E enMode, HI_BOOL *pbOnOff);
    HI_S32 (*SetVdpZme)         (HI_PQ_ZME_LAYER_E enLayerId, HI_PQ_ZME_PARA_IN_S *pstZmePara, HI_BOOL  bFirEnable);
    HI_S32 (*SetVpssZme)        (HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_ZME_PARA_IN_S *pstZmePara, HI_BOOL  bFirEnable);
    HI_S32 (*GetZmeCoef)        (HI_PQ_ZME_COEF_RATIO_E enCoefRatio, HI_PQ_ZME_COEF_TYPE_E enCoefType, HI_PQ_ZME_TAP_E enZmeTap, HI_S16 *ps16Coef);
    HI_S32 (*GetVdpZmeStrategy) (HI_PQ_ZME_LAYER_E enLayerId, HI_PQ_ZME_STRATEGY_IN_U *pstZmeIn, HI_PQ_ZME_STRATEGY_OUT_U *pstZmeOut);
    HI_S32 (*SetZmeDefault)     (HI_BOOL bOnOff);
    HI_S32 (*SetHDCPEn)         (HI_BOOL bOnOff);
    HI_S32 (*SetFrostLevel)     (HI_PQ_FROST_LEVEL_E enFrostLevel);
    HI_S32 (*SetImageMode)      (HI_PQ_IMAGE_MODE_E enImageMode);
    HI_S32 (*GetImageMode)      (HI_PQ_IMAGE_MODE_E *penImageMode);
    HI_S32 (*SetProcVdpZmeStrategy) (HI_PQ_PROC_VDPZME_STRATEGY_S stProcVdpZmeStrategy);
    HI_S32 (*GetProcVdpZmeStrategy) (HI_PQ_PROC_VDPZME_STRATEGY_S *pstProcVdpZmeStrategy);
    HI_S32 (*GetProcVdpZmeReso)     (HI_PQ_PROC_VDPZME_RESO_S *pstProcVdpZmeReso);
    HI_S32 (*GetProcWbcStrategy)    (HI_PQ_PROC_WBC_LAYER_E enProcWbcLayer, HI_PQ_PROC_WBC_STRATEGY_S *pstProcWbcStrategy);

    /*GFX ZME*/
    HI_S32 (*SetGfxZme)         (HI_PQ_GFX_LAYER_E enGfxZmeLayer, HI_PQ_GFX_ZME_PARA_S *pstGfxZmePara);
    /*GFX HDR*/
    HI_S32 (*GetGfxHdrCfg)      (HI_PQ_GFXHDR_HDR_INFO *pstGfxHdrInfo, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg);
    /*DEI*/
    HI_S32 (*SetDeiParam) (HI_PQ_WBC_INFO_S *pstVpssWbcInfo);
    HI_S32 (*GetMaEnable) (HI_BOOL *pbOnOff);
    HI_S32 (*GetMcEnable) (HI_BOOL *pbOnOff);
    /*FMD*/
    HI_S32 (*SofeParaInitByHandle) (HI_U32 u32HandleNo);
    HI_S32 (*IfmdDect)             (HI_PQ_IFMD_CALC_S *pstIfmdCalc, HI_PQ_IFMD_PLAYBACK_S *pstIfmdResult);
    HI_S32 (*GetIfmdDectInfo)      (HI_PQ_IFMD_PLAYBACK_S *pstIfmdInfo);
    HI_S32 (*SetFodMode)           (HI_PQ_FOD_MODE_E enMode);
    HI_S32 (*SetDeiOutMode)        (HI_PQ_DIE_OUT_MODE_E enMode);
    HI_S32 (*GetDeiMdLum)          (HI_VOID);
    HI_S32 (*GetMCDIMode)          (HI_U32 u32HandleNo, HI_BOOL *pbMCDIMode);
    /*DB*/
    HI_S32 (*DBCfgRefresh)     (HI_U32 u32HandleNo, HI_U32 u32Height, HI_U32 u32Width, HI_U32 u32FRate);
    HI_S32 (*DBCalcConfigCfg)  (HI_PQ_DB_CALC_INFO_S *pstDbCalcInfo);
    HI_S32 (*SetVdpDbmParaUpd) (HI_U32 u32Data);
    HI_S32 (*InitVdpDbm)       (HI_VOID);
    HI_S32 (*SetVdpDbmInfo)    (HI_PQ_VDP_WBC_INFO_S *pstInfo);
    /*DM*/
    HI_S32 (*DMCfgRefresh)    (HI_U32 u32HandleNo, HI_U32 u32Height, HI_U32 u32Width, HI_U32 u32FRate);
    HI_S32 (*DMCalcConfigCfg) (HI_PQ_DB_CALC_INFO_S *pstDbCalcInfo);
    /*DR*/
    /*DS*/
    HI_S32 (*SetDeShootThr)   (HI_U32 u32ID, HI_U32 u32Width);
    /*TNR*/
    HI_S32 (*InitVdpTnr)       (HI_VOID);
    HI_S32 (*DeInitVdpTnr)     (HI_VOID);
    HI_S32 (*SetVdpTnrParaUpd) (HI_U32 u32Data);
    HI_S32 (*SetVdpTnrLutUpd)  (HI_U32 u32Data);
    HI_S32 (*UpdateMCNRCfg)    (HI_PQ_WBC_INFO_S *pstVpssWbcInfo);
    HI_S32 (*EnableMCNR)       (HI_BOOL bOnOff);
    HI_S32 (*GetMCNREnable)    (HI_BOOL *pbOnOff);
    HI_S32 (*SetTNRBlendingAlphaLut) (HI_U32 u32HandleNo);
    /*SNR*/
    HI_S32 (*SetSNRCbCrLut)       (HI_VOID);
    HI_S32 (*SetSNRMotionEdgeLut) (HI_U32 u32Width);
    HI_S32 (*SetVdpSnrParaUpd)    (HI_U32 u32Data);
    HI_S32 (*InitVdpSnr)          (HI_VOID);
    /*DCI*/
    HI_S32 (*EnableDciBS)  (HI_BOOL bOnOff);
    HI_S32 (*UpdateDCIWin) (HI_PQ_DCI_WIN_S *pstWin);
    HI_S32 (*CalDCIScd)    (HI_VOID);
    HI_S32 (*UpdatDCICoef) (HI_PQ_VDP_LAYER_VID_E enVId);
    HI_S32 (*SetDciScd)    (HI_BOOL bSceneChange);
    HI_S32 (*GetDciScd)    (HI_BOOL *pbSceneChange);
    HI_S32 (*GetACCHistGram) (HI_PQ_ACC_HISTGRAM_S *pstACCHist);
    /*ACM*/
    HI_S32 (*SetFleshToneLevel)    (HI_PQ_FLESHTONE_E enGainLevel);
    HI_S32 (*GetFleshToneLevel)    (HI_U32 *pu32FleshToneLevel);
    HI_S32 (*SetACMGain)           (HI_VOID);
    HI_S32 (*SetSixBaseColorLevel) (HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColorOffset);
    HI_S32 (*GetSixBaseColorLevel) (HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColorOffset);
    HI_S32 (*SetColorEnhanceMode)  (HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode);
    HI_S32 (*GetColorEnhanceMode)  (HI_U32 *pu32ColorEnhanceMode);
    HI_S32 (*UpdatACMCoef)         (PQ_LAYER_VP_E enLayer);
    /*HDR*/
    HI_S32 (*GetHdrCfg)            (HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo, HI_PQ_HDR_CFG *pstPqHdrCfg);
    HI_S32 (*SetHdrDefaultCfg)     (HI_BOOL bDefault);
    HI_S32 (*SetHdrACCHistGram)    (HI_U32 u32ACCOutWidth, HI_U32 u32ACCOutHeight, HI_PQ_ACC_HISTGRAM_S *pstACCHistGram);
    HI_S32 (*SetHdrCSCVideoSetting)(HI_PQ_PICTURE_SETTING_S *pstPicSetting);
    HI_S32 (*SetHdrOffset)         (HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara);
    HI_S32 (*SetHdrTMCurve)        (HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara);
    /* ZME Send Para to Sharp */
    HI_S32 (*SetSharpResoInfo)     (HI_PQ_SHARP_RESO_S *pstSharpReso);
    /*LCHDR*/
    HI_S32 (*GetLCHdrCfg)          (HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo);
    HI_S32 (*SetStreamId)          (HI_U32 u32StreamId);
    HI_S32 (*SetStreamSetON)       (HI_U32 u32StreamIdSetMode);

    /* VPSS VideoPhone Scene Mode Get */
    HI_S32 (*SetVPType)            (HI_DRV_PQ_VP_TYPE_E enDrvPqVPType);
    HI_S32 (*UpdateVpssCsc)        (HI_U32 u32HandleNo, HI_DRV_PQ_VP_MODE_E enDrvPqVPImageMode);
    HI_S32 (*GetVPCscSetting)      (HI_DRV_PQ_VP_TYPE_E enDrvPqVPType, HI_PQ_PICTURE_SETTING_S *pstPicSetting);
    HI_S32 (*SetVPCscSetting)      (HI_DRV_PQ_VP_TYPE_E enDrvPqVPType, HI_PQ_PICTURE_SETTING_S *pstPicSetting);
    HI_S32 (*UpdateVpssGammaCoef)  (HI_U32 u32HandleNo, HI_DRV_PQ_VP_MODE_E enDrvPqVPImageMode);
} stPQAlgFuncs;

typedef struct hiPQ_ALG_REG_S
{
    HI_U32                   u32AlgID;
    HI_U32                   u32TypeID;
    HI_U32                   u32AdapeType;
    HI_U8                    u8AlgName[ALG_NAME_MAX_LEN];
    HI_VOID                 *Data;
    const stPQAlgFuncs      *pFun;
} PQ_ALG_REG_S;

extern PQ_STATUS_S g_stPqStatus;

HI_S32 PQ_COMM_SetPqStatus(PQ_STATUS_S *pstPqStatus);

HI_S32 PQ_COMM_GetPqStatus(PQ_STATUS_S *pstPqStatus);

HI_S32 PQ_COMM_CheckChipName(HI_CHAR *pchChipName);

HI_S32 PQ_COMM_AlgRegister( HI_PQ_MODULE_E       enModule,
                            PQ_REG_TYPE_E                enRegType,
                            PQ_BIN_ADAPT_TYPE_E          enAdaptType,
                            const HI_U8                 *pu8AlgName,
                            HI_VOID                     *pData,
                            const stPQAlgFuncs          *pFuncs);

HI_S32 PQ_COMM_AlgUnRegister( HI_PQ_MODULE_E      enModule);

HI_U32 PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_E    enModule );

HI_U32 PQ_COMM_GetAlgAdapeType(HI_PQ_MODULE_E    enModule );

PQ_ALG_REG_S *PQ_COMM_GetAlg(HI_PQ_MODULE_E    enModule );

HI_U8 *PQ_COMM_GetAlgName(HI_PQ_MODULE_E    enModule );

HI_U8 PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_E  enModule, PQ_SOURCE_MODE_E enSrcMode);

HI_VOID PQ_COMM_SetMoudleCtrl(HI_PQ_MODULE_E  enModule, PQ_SOURCE_MODE_E enSrcMode, HI_U8 u8OnOff);

PQ_SOURCE_MODE_E PQ_COMM_CheckSourceMode(HI_U32 u32Width);

PQ_OUTPUT_MODE_E PQ_COMM_CheckOutputMode(HI_S32 s32Width);

PQ_SOURCE_MODE_E PQ_COMM_GetSourceMode(HI_VOID);

HI_VOID PQ_COMM_SetSourceMode(PQ_SOURCE_MODE_E enMode);

PQ_OUTPUT_MODE_E PQ_COMM_GetOutputMode(HI_VOID);

HI_VOID PQ_COMM_SetOutputMode(PQ_OUTPUT_MODE_E enMode);

HI_ULONG PQ_GetTimeUs(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
