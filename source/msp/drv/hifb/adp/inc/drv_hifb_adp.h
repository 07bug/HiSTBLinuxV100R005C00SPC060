/**************************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : drv_hifb_adp.h
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     :
Function List   :


History         :
Date                  Author            Modification
2018/01/01            sdk               Created file
***************************************************************************************************/
#ifndef __DRV_HIFB_ADP_H__
#define __DRV_HIFB_ADP_H__


/*********************************add include here*************************************************/
#ifndef HI_BUILD_IN_BOOT
#include "hi_type.h"
#include "hi_common.h"
#include "drv_disp_ext.h"
#include "drv_hifb_common.h"
#else
#include "hifb_debug.h"
#include "hi_drv_disp.h"
#endif

#include "drv_hifb_hal.h"

#include "hi_gfx_comm_k.h"
#include "optm_define.h"

#ifdef CONFIG_GFX_PQ
#include "drv_pq_ext.h"
#endif

/**************************************************************************************************/


/**************************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ***************************************************/

#ifdef HI_BUILD_IN_BOOT
#define HIFB_ERROR(fmt...)              HI_ERR_PRINT(HI_ID_FB, fmt)
#define HIFB_WARNING(fmt...)            HI_WARN_PRINT(HI_ID_FB, fmt)
#define HIFB_INFO(fmt...)               HI_INFO_PRINT(HI_ID_FB, fmt)
#endif

#define OPTM_ENABLE                      1
#define OPTM_DISABLE                     0

#define OPTM_MASTER_GPID                 OPTM_GFX_GP_0
#define OPTM_SLAVER_GPID                 OPTM_GFX_GP_1
#define OPTM_SLAVER_LAYERID              HIFB_LAYER_SD_0
#define OPTM_MAX_LOGIC_HIFB_LAYER        ((HI_U32)HIFB_LAYER_ID_BUTT)

#define OPTM_CMAP_SIZE                   0x400

#define IS_MASTER_GP(enGpId) ((g_enOptmGfxWorkMode == HIFB_GFX_MODE_HD_WBC)&&(enGpId == OPTM_GFX_GP_0))
#define IS_SLAVER_GP(enGpId) ((g_enOptmGfxWorkMode == HIFB_GFX_MODE_HD_WBC)&&(enGpId == OPTM_GFX_GP_1))


#ifndef CONFIG_HIFB_LOWPOWER_MAX_PARA_CNT
#define CONFIG_HIFB_LOWPOWER_MAX_PARA_CNT  17
#endif

typedef enum tagOPTM_GFX_GP_E
{
    OPTM_GFX_GP_0 = 0x0,  /** process gfx0,gfx1,gfx2,gfx3   */
    OPTM_GFX_GP_1,        /** process gfx4,gfx5             */
    OPTM_GFX_GP_BUTT
}OPTM_GFX_GP_E;


#define OPTM_CheckGPMask_BYLayerID(u32LayerID)  \
            do{\
                if (u32LayerID >= OPTM_MAX_LOGIC_HIFB_LAYER)\
                {\
                    return HI_FAILURE;\
                }\
                if (g_pstGfxDevice[u32LayerID]->enGPId >= OPTM_GFX_GP_BUTT)\
                {\
                    return HI_FAILURE;\
                }\
                if (g_pstGfxGPDevice[g_pstGfxDevice[u32LayerID]->enGPId]->bMaskFlag)\
                {\
                    return HI_SUCCESS;\
                }\
            }while(0)


#define OPTM_CheckGPMask_BYGPID(enGPId) \
            do{\
                if (enGPId >= OPTM_GFX_GP_BUTT)\
                {\
                    return HI_FAILURE;\
                }\
                if (g_pstGfxGPDevice[enGPId]->bMaskFlag)\
                {\
                    return HI_SUCCESS;\
                }\
            }while(0)

/*************************** Structure Definition ****************************/
typedef struct tagOPTM_GFX_CSC_PARA_S
{
    HI_U32               u32Bright;
    HI_U32               u32Contrast;
    HI_U32               u32Saturation;
    HI_U32               u32Hue;
    HI_U32               u32Kr;
    HI_U32               u32Kg;
    HI_U32               u32Kb;
}OPTM_GFX_CSC_PARA_S;

typedef struct tagOPTM_GFX_OFFSET_S
{
    HI_U32 u32Left;    /** left offset   */
    HI_U32 u32Top;     /** top offset    */
    HI_U32 u32Right;   /** right offset  */
    HI_U32 u32Bottom;  /** bottom offset */
}OPTM_GFX_OFFSET_S;

/** csc state*/
typedef enum tagOPTM_CSC_STATE_E
{
    OPTM_CSC_SET_PARA_ENABLE = 0x0,
    OPTM_CSC_SET_PARA_RGB         ,
    OPTM_CSC_SET_PARA_BGR         ,
    OPTM_CSC_SET_PARA_CLUT        ,
    OPTM_CSC_SET_PARA_CbYCrY      ,
    OPTM_CSC_SET_PARA_YCbYCr      ,
    OPTM_CSC_SET_PARA_BUTT
}OPTM_CSC_STATE_E;

typedef enum optm_COLOR_SPACE_E
{
    OPTM_CS_UNKNOWN = 0,

    OPTM_CS_BT601_YUV_LIMITED, /** for BT.601 mod **/
    OPTM_CS_BT601_YUV_FULL,
    OPTM_CS_BT601_RGB_LIMITED,
    OPTM_CS_BT601_RGB_FULL,

    OPTM_CS_BT709_YUV_LIMITED, /** for BT.709 mod  **/
    OPTM_CS_BT709_YUV_FULL,
    OPTM_CS_BT709_RGB_LIMITED,
    OPTM_CS_BT709_RGB_FULL,

    OPTM_CS_BUTT
} OPTM_COLOR_SPACE_E;


#ifndef HI_BUILD_IN_BOOT
typedef struct tagOPTM_GFX_WORK_S
{
    HI_U32 u32Data;
    struct work_struct work;
}OPTM_GFX_WORK_S;
#endif

typedef union tagOPTM_GFX_UP_FLAG_U
{
    struct
    {
        unsigned int    IsNeedRegUp     : 1 ; /*  [0] */
        unsigned int    IsEnable        : 1 ; /*  [1] */
        unsigned int    IsNeedUpInRect  : 1 ; /*  [2] */
        unsigned int    OutRect         : 1 ; /*  [3] */
        unsigned int    IsNeedUpAlpha   : 1 ; /*  [4] */
        unsigned int    IsNeedUpPreMult : 1 ; /*  [5] */
        unsigned int    WbcMode         : 1 ; /*  [6] */
        unsigned int    Reserved        : 25; /*  [31...7] */
    } bits;
    unsigned int    u32;
}OPTM_GFX_UP_FLAG_U;

typedef enum tagOPTM_DISPCHANNEL_E
{
    OPTM_DISPCHANNEL_0 = 0,    /** gfx4,gfx5             **/
    OPTM_DISPCHANNEL_1 = 1,    /** gfx0,gfx1,gfx2,gfx3   **/
    OPTM_DISPCHANNEL_BUTT
}OPTM_DISPCHANNEL_E;

typedef struct tagHIFB_ADP_LOWPOWER_INFO_S
{
    HI_BOOL LowPowerEn;
    HI_U32 LpInfo[CONFIG_HIFB_LOWPOWER_MAX_PARA_CNT];
}HIFB_ADP_LOWPOWER_INFO_S;

typedef struct tagOPTM_GFX_GP_S
{
    HI_BOOL bOpen;
    HI_BOOL bHdr;
    HI_BOOL bPreHdr;
    HI_BOOL bMaskFlag;
    HI_BOOL bBGRState;
    HI_BOOL bInterface;
    HI_BOOL bGpClose;
    HI_BOOL bHasBeenReOpen[2];    /** 要是待机或者切制式，这个时候没有中断了，中断需要的信息需要复位 **/
    HI_BOOL bResume;
    HI_BOOL bResumeForPowerOff;
    HI_BOOL bRecoveryInNextVT;
    HI_BOOL bNeedExtractLine;
    HI_BOOL bDispInitial;
    HI_RECT_S stInRect;
    HI_RECT_S stOutRect;
    HI_U32    u32ZmeDeflicker;
#ifdef CHIP_TYPE_hi3798cv200/** hdmi cts need **/
    HI_DRV_DISP_FMT_E         enDispFmt;
#endif
    HIFB_STEREO_MODE_E        enTriDimMode;
    OPTM_GFX_CSC_PARA_S       stCscPara;
#ifndef CONFIG_GFX_PQ
    OPTM_COLOR_SPACE_E        enInputCsc;
    OPTM_COLOR_SPACE_E        enOutputCsc;
#else
    HI_PQ_GFX_COLOR_SPACE_E   enInputCsc;
    HI_PQ_GFX_COLOR_SPACE_E   enOutputCsc;
#endif
    OPTM_VDP_LAYER_GP_E       enGpHalId;
    OPTM_DISPCHANNEL_E        enDispCh;
    OPTM_GFX_UP_FLAG_U        unUpFlag;

#ifndef HI_BUILD_IN_BOOT
    struct workqueue_struct   *queue;
    OPTM_GFX_WORK_S           stOpenSlvWork;
    OPTM_GFX_WORK_S           st3DModeChgWork;
#endif
    HI_U32 u32Prior;
    HI_U32 u32Alpha;
    OPTM_VDP_DATA_RMODE_E     enReadMode;
    OPTM_VDP_BKG_S            stBkg;
    OPTM_VDP_CBM_MIX_E        enMixg;
}OPTM_GFX_GP_S;

typedef struct tagOPTM_GFX_LAYER_S{
    HI_BOOL              bOpened;
    HI_BOOL              bMaskFlag;
    HI_BOOL              bSharpEnable;
    HI_BOOL              bExtractLine;
    HI_BOOL              bEnable;
    HI_S32               s32Depth;
    HI_BOOL              bPreMute;
    HI_U32               u32ZOrder;
    HI_BOOL              bCmpOpened;
    HI_BOOL              bDmpOpened;
    HI_BOOL              bBufferChged;
    HI_U32               s32BufferChgCount;
    HI_U32               NoCmpBufAddr;
    HI_U32               ARHeadDdr;
    HI_U32               ARDataDdr;
    HI_U32               GBHeadDdr;
    HI_U32               GBDataDdr;
    HI_U32               u32TriDimAddr;
    HI_U16               Stride;           /** no compression mode stride  */
    HI_U16               CmpStride;        /** compression mode stride     */
    HIFB_COLOR_FMT_E     enDataFmt;
    HIFB_RECT            stInRect;         /** Inres of gfx                */
    HIFB_ALPHA_S         stAlpha;
    HIFB_COLORKEYEX_S    stColorkey;
    HIFB_STEREO_MODE_E   enTriDimMode;
    OPTM_VDP_BKG_S       stBkg;
    OPTM_VDP_GFX_BITEXTEND_E enBitExtend;  /** the g_ctrl of bitext        **/
    OPTM_VDP_DATA_RMODE_E    enReadMode;
    OPTM_VDP_DATA_RMODE_E    enUpDateMode;
    OPTM_VDP_LAYER_GFX_E     enGfxHalId;   /** the gfx's hal id            */
    OPTM_GFX_GP_E            enGPId;       /** which gp the gfx belong to  */
    OPTM_CSC_STATE_E         CscState;
    volatile HI_U32          vblflag;
    wait_queue_head_t        vblEvent;
    GFX_MMZ_BUFFER_S         stCluptTable;
}OPTM_GFX_LAYER_S;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            initial operation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef struct
{
    HI_S32  (*HIFB_DRV_CloseLayer)                    (HIFB_LAYER_ID_E enLayerId);
#ifndef HI_BUILD_IN_BOOT
    HI_S32  (*HIFB_DRV_ColorConvert)                  (const struct fb_var_screeninfo *pstVar, HIFB_COLORKEYEX_S *pCkey);
#endif
    HI_S32  (*HIFB_DRV_EnableLayer)                   (HIFB_LAYER_ID_E enLayerId,HI_BOOL bEnable);
    HI_VOID (*HIFB_DRV_GetGFXCap)                     (const HIFB_CAPABILITY_S **pstCap);
#ifndef HI_BUILD_IN_BOOT
    HI_VOID (*HIFB_DRV_GetOSDData)                    (HIFB_LAYER_ID_E enLayerId, HIFB_OSD_DATA_S  *pstLayerData);
    HI_VOID (*HIFB_DRV_GetLogoData)                   (HIFB_LAYER_ID_E enLayerId, HIFB_LOGO_DATA_S *pstLogoData);
#endif
    HI_S32  (*HIFB_DRV_GetLayerPriority)              (HIFB_LAYER_ID_E enLayerId, HI_U32 *pU32Priority);
    HI_S32  (*HIFB_DRV_GfxDeInit)                     (HI_VOID);
    HI_S32  (*HIFB_DRV_GfxInit)                       (HI_VOID);
    HI_S32  (*HIFB_DRV_OpenLayer)                     (HIFB_LAYER_ID_E enLayerId);
    HI_S32  (*HIFB_DRV_PauseCompression)              (HIFB_LAYER_ID_E enLayerId);
    HI_S32  (*HIFB_DRV_ResumeCompression)             (HIFB_LAYER_ID_E enLayerId);
    HI_S32  (*HIFB_DRV_SetColorReg)                   (HIFB_LAYER_ID_E enLayerId, HI_U32 u32OffSet, HI_U32 u32Color, HI_S32 UpFlag);
    HI_S32  (*HIFB_DRV_SetTriDimMode)                 (HIFB_LAYER_ID_E enLayerId, HIFB_STEREO_MODE_E enStereoMode, HIFB_STEREO_MODE_E enWbcSteroMode);
    HI_S32  (*HIFB_DRV_SetTriDimAddr)                 (HIFB_LAYER_ID_E enLayerId, HI_U32 u32StereoAddr);
    HI_S32  (*HIFB_DRV_SetLayerAddr)                  (HIFB_LAYER_ID_E enLayerId, HI_U32 u32Addr);
    HI_S32  (*HIFB_DRV_GetLayerAddr)                  (HIFB_LAYER_ID_E enLayerId, HI_U32 *pu32Addr);
    HI_S32  (*HIFB_DRV_SetLayerAlpha)                 (HIFB_LAYER_ID_E enLayerId, HIFB_ALPHA_S *pstAlpha);
    HI_S32  (*HIFB_DRV_SetLayerDataFmt)               (HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt);
    HI_S32  (*HIFB_DRV_SetLayerDeFlicker)             (HIFB_LAYER_ID_E enLayerId, HIFB_DEFLICKER_S *pstDeFlicker);
    HI_S32  (*HIFB_DRV_SetLayerPriority)              (HIFB_LAYER_ID_E enLayerId, HIFB_ZORDER_E enZOrder);
    HI_S32  (*HIFB_DRV_UpdataLayerReg)                (HIFB_LAYER_ID_E enLayerId);
    HI_VOID (*HIFB_DRV_GetDhd0Info)                   (HIFB_LAYER_ID_E LayerId, HI_ULONG *pExpectIntLineNumsForVoCallBack,HI_ULONG *pExpectIntLineNumsForEndCallBack,HI_ULONG *pActualIntLineNumsForVoCallBack,HI_ULONG *pHardIntCntForVoCallBack);
    HI_VOID (*HIFB_ADP_GetCloseState)                 (HIFB_LAYER_ID_E LayerId, HI_BOOL *pHasBeenClosedForVoCallBack, HI_BOOL *pHasBeenClosedForEndCallBack);
    HI_S32  (*HIFB_DRV_WaitVBlank)                    (HIFB_LAYER_ID_E enLayerId);
    HI_S32  (*HIFB_DRV_SetLayerKeyMask)               (HIFB_LAYER_ID_E enLayerId, const HIFB_COLORKEYEX_S* pstColorkey);
    HI_S32  (*HIFB_DRV_SetLayerPreMult)               (HIFB_LAYER_ID_E enLayerId, HI_BOOL bPreMul);
    HI_VOID (*HIFB_DRV_GetLayerPreMult)               (HIFB_LAYER_ID_E enLayerId, HI_BOOL *pPreMul);
    HI_VOID (*HIFB_DRV_GetLayerHdr)                   (HIFB_LAYER_ID_E enLayerId, HI_BOOL *pHdr);
    HI_VOID (*HIFB_DRV_GetClosePreMultState)          (HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbShouldClosePreMult);
    HI_VOID (*HIFB_DRV_ReadRegister)                  (HI_U32 Offset);
    HI_VOID (*HIFB_DRV_WriteRegister)                 (HI_U32 Offset, HI_U32 Value);
    HI_VOID (*HIFB_DRV_WhetherDiscardFrame)           (HIFB_LAYER_ID_E enLayerId, HI_BOOL *pNoDiscardFrame);
    HI_S32  (*HIFB_DRV_SetIntCallback)                (HIFB_CALLBACK_TPYE_E enCType, IntCallBack pCallBack, HIFB_LAYER_ID_E enLayerId);
    HI_S32  (*HIFB_DRV_SetLayerStride)                (HIFB_LAYER_ID_E enLayerId, HI_U32 u32Stride);
    HI_S32  (*HIFB_DRV_SetLayerInRect)                (HIFB_LAYER_ID_E enLayerId, const HIFB_RECT *pstInputRect);
    HI_S32  (*HIFB_DRV_GetLayerOutRect)               (HIFB_LAYER_ID_E enLayerId, HIFB_RECT *pstOutputRect);
    HI_S32  (*HIFB_DRV_GetLayerInRect)                (HIFB_LAYER_ID_E enLayerId, HIFB_RECT *pstOutputRect);
    HI_S32  (*HIFB_DRV_SetLayerMaskFlag)              (HIFB_LAYER_ID_E enLayerId, HI_BOOL bFlag);
    HI_S32  (*HIFB_DRV_GetLayerMaskFlag)              (HIFB_LAYER_ID_E enLayerId);
    HI_S32  (*HIFB_DRV_GetDispSize)                   (HIFB_LAYER_ID_E enLayerId, HIFB_RECT *pstOutputRect);
    HI_S32  (*HIFB_DRV_ClearLogo)                     (HIFB_LAYER_ID_E enLayerId);
    HI_S32  (*HIFB_DRV_SetStereoDepth)                (HIFB_LAYER_ID_E enLayerId, HI_S32 s32Depth);
    HI_S32  (*HIFB_DRV_SetTCFlag)                     (HI_BOOL bFlag);
    HI_VOID (*HIFB_DRV_SetDeCmpSwitch)                (HIFB_LAYER_ID_E enLayerId, HI_BOOL bOpen);
    HI_VOID (*HIFB_DRV_SetDeCmpDdrInfo)               (HIFB_LAYER_ID_E enLayerId, HI_U32 ARHeadDdr,HI_U32 ARDataDdr,HI_U32 GBHeadDdr,HI_U32 GBDataDdr,HI_U32 DeCmpStride);
    HI_VOID (*HIFB_OSI_SetLowPowerInfo)               (HIFB_LAYER_ID_E enLayerId, HIFB_ADP_LOWPOWER_INFO_S *pstLowPowerInfo);
    HI_VOID (*HIFB_DRV_GetDecompressStatus)           (HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbARDataDecompressErr, HI_BOOL *pbGBDataDecompressErr);
    HI_VOID (*HIFB_DRV_GetResumeStatus)               (HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbResume);
    HI_VOID (*HIFB_DRV_GetResumeForPowerOffStatus)    (HIFB_LAYER_ID_E enLayerId, HI_BOOL *ResumeForPowerOff);
    HI_S32  (*HIFB_DRV_SetGpDeflicker)                (HI_U32 u32DispChn, HI_BOOL bDeflicker);
    HI_S32  (*HIFB_DRV_GetHaltDispStatus)             (HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbDispInit);
}HIFB_DRV_OPS_S;

/***************************  The enum of Jpeg image format  **************************************/

/********************** Global Variable declaration ***********************************************/


/******************************* API declaration **************************************************/
/**************************************************************************************************
* func        : DRV_HIFB_GetAdpCallBackFunction
* description : CNcomment: 获取设备上下文 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************************/
HI_VOID DRV_HIFB_GetAdpCallBackFunction(HIFB_DRV_OPS_S *AdpCallBackFunction);

/**************************************************************************************************
* func          : OPTM_UnmapAndRelease
* description   : unmap the ddr and release it\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_VOID OPTM_UnmapAndRelease(GFX_MMZ_BUFFER_S *psMBuf);

/**************************************************************************************************
* func          : OPTM_AllocAndMap
* description   : CNcomment: alloc and map mem CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, GFX_MMZ_BUFFER_S *psMBuf);


/**************************************************************************************************
* func          : OPTM_GfxInitLayer
* description   : CNcomment: 初始化图层信息 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_VOID OPTM_GfxInitLayer(HIFB_LAYER_ID_E enLayerId);

/**************************************************************************************************
* func          : OPTM_GPOpen
* description   : CNcomment: 打开GP设备并设置ZME系数 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_GPOpen(OPTM_GFX_GP_E enGPId);

/**************************************************************************************************
* func          : OPTM_GFX_ReleaseClutBuf
* description   : CNcomment: 释放调色板内存 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_GFX_ReleaseClutBuf(HIFB_LAYER_ID_E enLayerId);

/**************************************************************************************************
* func          : OPTM_GfxSetLayerReadMode
* description   : CNcomment: 设置读取数据模式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_GfxSetLayerReadMode(HIFB_LAYER_ID_E enLayerId, OPTM_VDP_DATA_RMODE_E enReadMode);

/**************************************************************************************************
* func          : OPTM_PixerFmtTransferToHalFmt
* description   : CNcomment: 根据像素数据转换成像素格式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
OPTM_VDP_GFX_IFMT_E OPTM_PixerFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt);


/**************************************************************************************************
* func          : DRV_HIFB_ADP_UpDataCallBack
* description   : CNcomment: 注册寄存器更新回调函数 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_VOID DRV_HIFB_ADP_UpDataCallBack(HI_VOID* u32Param0, HI_VOID* u32Param1);

/**************************************************************************************************
* func            : OPTM_GfxSetLayerAddr
* description    : CNcomment: 设置显示地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:        : NA
***************************************************************************************************/
HI_S32 OPTM_GfxSetLayerAddr(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Addr);

/**************************************************************************************************
* func          : OPTM_GfxSetLayerStride
* description   : CNcomment: 设置图层stride CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_GfxSetLayerStride(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Stride);

/**************************************************************************************************
* func          : OPTM_Adapt_AllocAndMap
* description   : CNcomment: 分配内存并映射地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_Adapt_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, GFX_MMZ_BUFFER_S *psMBuf);

/**************************************************************************************************
* func          : OPTM_SetCallbackToDisp
* description   : CNcomment: 向Display注册中断 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
#ifndef HI_BUILD_IN_BOOT
HI_S32 OPTM_SetCallbackToDisp(OPTM_GFX_GP_E enGPId, IntCallBack pCallBack, HI_DRV_DISP_CALLBACK_TYPE_E eType, HI_BOOL bFlag);
#endif

/**************************************************************************************************
* func          : OPTM_GfxSetEnable
* description   : CNcomment: 设置图层使能 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_GfxSetEnable(HIFB_LAYER_ID_E enLayerId, HI_BOOL bEnable);

/**************************************************************************************************
* func          : OPTM_GfxSetLayerRect
* description   : CNcomment: 设置图层分辨率 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_GfxSetLayerRect(HIFB_LAYER_ID_E enLayerId, const HIFB_RECT *pstRect);

/**************************************************************************************************
* func          : OPTM_GfxSetGpRect
* description   : CNcomment: 设置图层对应的GP分辨率 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_GfxSetGpRect(OPTM_GFX_GP_E enGpId, const HIFB_RECT * pstInputRect);

/**************************************************************************************************
* func          : OPTM_GfxCloseLayer
* description   : CNcomment: 关闭图层 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************************/
HI_S32 OPTM_GfxCloseLayer(HIFB_LAYER_ID_E enLayerId);

/***************************************************************************************
* func        : HIFB_PARA_CHECK_SUPPORT
* description : CNcomment: 判断输入参数是否支持 CNend\n
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 HIFB_PARA_CHECK_SUPPORT(HI_U32 Mask, HI_U32 Width, HI_U32 Height, HI_U32 Stride, HI_U32 Fmt, HI_U32 BitsPerPixel);

#ifdef HI_BUILD_IN_BOOT
HI_S32  OPTM_GfxInit(HI_VOID);
HI_S32  OPTM_GfxOpenLayer(HIFB_LAYER_ID_E enLayerId);
HI_S32  OPTM_GfxSetLayerAlpha(HIFB_LAYER_ID_E enLayerId, HIFB_ALPHA_S *pstAlpha);
HI_S32  OPTM_GfxSetLayerDataFmt(HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt);
HI_S32  OPTM_GfxUpLayerReg(HIFB_LAYER_ID_E enLayerId);
HI_S32  OPTM_GpInitFromDisp(OPTM_GFX_GP_E enGPId, HI_BOOL Support4KLogo);
HI_S32  OPTM_GFX_SetTCFlag(HI_BOOL bFlag);
HI_BOOL HIFB_ADP_GetIsGfxWorkAtWbc(HI_VOID);
#endif

HI_S32  OPTM_GfxSetDispFMTSize(OPTM_GFX_GP_E enGpId, const HI_RECT_S *pstOutRect);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
