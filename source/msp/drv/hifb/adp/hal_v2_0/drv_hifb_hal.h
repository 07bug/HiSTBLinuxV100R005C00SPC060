/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name       : drv_hifb_hal.h
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     :
Function List   :


History         :
Date                 Author                Modification
2018/01/01            sdk                   Created file
************************************************************************************************/
#ifndef __DRV_HIFB_HAL_H__
#define __DRV_HIFB_HAL_H__


/*********************************add include here**********************************************/

#ifndef HI_BUILD_IN_BOOT
#include <linux/kernel.h>
#endif

#include "optm_define.h"


/***********************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


/***************************** Macro Definition ************************************************/



/*************************** Structure Definition **********************************************/

/***************************  The enum of Jpeg image format  ***********************************/

/********************** Global Variable declaration ********************************************/


/******************************* API declaration ***********************************************/
#ifndef HI_BUILD_IN_BOOT
HI_VOID HIFB_HAL_GetDhd0Vtthd3 (HI_ULONG *pExpectIntLineNumsForEndCallBack);
HI_VOID HIFB_HAL_GetDhd0Vtthd  (HI_ULONG *pExpectIntLineNumsForVoCallBack);
HI_VOID HIFB_HAL_GetDhd0State  (HI_ULONG *pActualIntLineNumsForCallBack,HI_ULONG *pHardIntCntForCallBack);
HI_VOID HIFB_HAL_GetWorkedLayerAddr    (HI_U32 u32Data, HI_U32 *pu32Addr);
HI_VOID HIFB_HAL_GetWillWorkLayerAddr  (HI_U32 u32Data, HI_U32 *pu32Addr);
#endif

HI_VOID OPTM_VDP_DRIVER_Initial    (volatile HI_U32* virAddr);
HI_VOID OPTM_VDP_SetLayerConnect   (HI_U32 u32Data);
HI_VOID OPTM_VDP_OpenGFX3          (HI_BOOL bOpen);

//-------------------------------------------------------------------
//GFX_BEGIN
//-------------------------------------------------------------------
#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_GetLayerAddr        (HI_U32 u32Data, HI_U32 *pu32Addr);
HI_VOID OPTM_VDP_GFX_GetLayerEnable      (HI_U32 u32Data, HI_U32 *pu32Enable );
HI_VOID OPTM_VDP_GP_GetRect              (HI_U32 u32Data, OPTM_VDP_DISP_RECT_S *pstRect);
HI_VOID  OPTM_VDP_GFX_GetLayerInRect     (HI_U32 u32Data, OPTM_VDP_DISP_RECT_S *stInRect);
HI_VOID OPTM_VDP_GFX_GetLayerStride      (HI_U32 u32Data, HI_U32 *pu32Stride);
HI_VOID OPTM_VDP_GFX_GetPalpha           (HI_U32 u32Data, HI_U32 *pbAlphaEn,HI_U32 *pbArange,HI_U8 *pu8Alpha0,HI_U8 *pu8Alpha1);
HI_VOID OPTM_VDP_GFX_GetLayerGalpha      (HI_U32 u32Data, HI_U8 *pu8Alpha0);
HI_VOID OPTM_VDP_GFX_GetKeyMask          (HI_U32 u32Data, OPTM_VDP_GFX_MASK_S *pstMsk);
HI_VOID OPTM_VDP_GFX_GetColorKey         (HI_U32 u32Data, HI_U32 *pbkeyEn,OPTM_VDP_GFX_CKEY_S *pstKey);
HI_VOID OPTM_VDP_GFX_GetInDataFmt        (HI_U32 u32Data, OPTM_VDP_GFX_IFMT_E  *enDataFmt);
HI_VOID OPTM_VDP_WBC_GetEnable           (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 *pEnable);
#endif


HI_VOID OPTM_VDP_CBM_GetMixerPrio           (OPTM_VDP_CBM_MIX_E u32mixer_id, HI_U32 *pu32prio);
HI_VOID OPTM_VDP_SetMixgPrio                (OPTM_VDP_CBM_MIX_E u32mixer_id, HI_U32 u32prio);
HI_VOID OPTM_VDP_GFX_SetLayerReso           (HI_U32 u32Data, OPTM_VDP_DISP_RECT_S *pstRect);
HI_VOID OPTM_VDP_GFX_SetLayerEnable         (HI_U32 u32Data, HI_U32 u32bEnable );
HI_VOID OPTM_VDP_GFX_SetLayerAddrEX         (HI_U32 u32Data, HI_U32 u32LAddr);
HI_VOID OPTM_VDP_GFX_SetLayerStride         (HI_U32 u32Data, HI_U32 u32Stride);
HI_VOID OPTM_VDP_GFX_SetInDataFmt           (HI_U32 u32Data, OPTM_VDP_GFX_IFMT_E enDataFmt);
HI_VOID OPTM_VDP_GFX_SetReadMode            (HI_U32 u32Data, HI_U32 u32Mode);
HI_VOID OPTM_VDP_GFX_SetBitExtend           (HI_U32 u32Data, OPTM_VDP_GFX_BITEXTEND_E u32mode);
HI_VOID OPTM_VDP_GFX_SetColorKey            (HI_U32 u32Data, HI_U32  bkeyEn,OPTM_VDP_GFX_CKEY_S *pstKey);
HI_VOID OPTM_VDP_GFX_SetKeyMask             (HI_U32 u32Data, OPTM_VDP_GFX_MASK_S *pstMsk);


HI_VOID  OPTM_VDP_GFX_SetParaUpd            (HI_U32 u32Data, OPTM_VDP_DISP_COEFMODE_E enMode);
HI_VOID  OPTM_VDP_GFX_SetLutAddr            (HI_U32 u32Data, HI_U32 u32LutAddr);
HI_VOID  OPTM_VDP_GFX_SetNoSecFlag          (HI_U32 u32Data, HI_U32 u32Enable);
HI_VOID  OPTM_VDP_GFX_SetDcmpEnable         (HI_U32 u32Data, HI_U32 u32bEnable);
HI_VOID  DRV_HAL_SetDeCmpDdrInfo            (HI_U32 u32Data, HI_U32 ARHeadDdr,HI_U32 ARDataDdr,HI_U32 GBHeadDdr,HI_U32 GBDataDdr,HI_U32 DeCmpStride);
HI_VOID  DRV_HAL_GetDeCmpStatus             (HI_U32 u32Data, HI_BOOL *pbARDataDecompressErr, HI_BOOL *pbGBDataDecompressErr);

//3D
#ifndef HI_BUILD_IN_BOOT
HI_VOID  OPTM_VDP_GFX_SetThreeDimDofEnable  (HI_U32 u32Data, HI_U32 bEnable);
HI_VOID  OPTM_VDP_GFX_SetThreeDimDofStep    (HI_U32 u32Data, HI_S32 s32LStep, HI_S32 s32RStep);
HI_VOID  HIFB_HAL_SetLowPowerInfo           (HI_U32 u32Data, HI_U32 *pLowPowerInfo);
HI_VOID  HIFB_HAL_EnableLayerLowPower       (HI_U32 u32Data, HI_BOOL EnLowPower);
HI_VOID  HIFB_HAL_EnableGpLowPower          (HI_U32 u32Data, HI_BOOL EnLowPower);
#endif

HI_VOID  OPTM_VDP_GFX_GetPreMultEnable      (HI_U32 u32Data, HI_U32 *pbEnable);
HI_VOID  OPTM_VDP_GFX_SetPreMultEnable      (HI_U32 u32Data, HI_U32 bEnable, HI_BOOL bHdr);
HI_VOID  OPTM_VDP_GFX_SetLayerBkg           (HI_U32 u32Data, OPTM_VDP_BKG_S *pstBkg);
HI_VOID  OPTM_VDP_GFX_SetLayerGalpha        (HI_U32 u32Data, HI_U32 u32Alpha0);
HI_VOID  OPTM_VDP_GFX_SetPalpha             (HI_U32 u32Data, HI_U32 bAlphaEn,HI_U32 bArange,HI_U32 u32Alpha0,HI_U32 u32Alpha1);
HI_VOID  OPTM_VDP_GFX_ReadRegister          (HI_U32 Offset);
HI_VOID  OPTM_VDP_GFX_WriteRegister         (HI_U32 Offset,HI_U32 Value);

#ifndef HI_BUILD_IN_BOOT
HI_VOID  OPTM_VDP_GFX_SetLayerNAddr         (HI_U32 u32Data, HI_U32 u32NAddr);
#endif
HI_VOID  OPTM_VDP_GFX_SetUpdMode            (HI_U32 u32Data, HI_U32 u32Mode);
HI_VOID  OPTM_VDP_GFX_SetRegUp              (HI_U32 u32Data);


//-------------------------------------------------------------------
//GP_BEGIN
//-------------------------------------------------------------------
HI_VOID OPTM_VDP_GP_SetLayerReso            (HI_U32 u32Data, OPTM_VDP_DISP_RECT_S *pstRect);

HI_VOID OPTM_VDP_GP_SetReadMode             (HI_U32 u32Data, HI_U32 u32Mode);
HI_VOID OPTM_VDP_GP_SetUpMode               (HI_U32 u32Data, HI_U32 u32Mode);
HI_VOID OPTM_VDP_GP_SetParaUpd              (HI_U32 u32Data, OPTM_VDP_GP_PARA_E enMode);
HI_VOID OPTM_VDP_GP_SetRegUp                (HI_U32 u32Data);
HI_VOID OPTM_VDP_GP_SetLayerGalpha          (HI_U32 u32Data, HI_U32 u32Alpha);

//-------------------------------------------------------------------
//MIXER_BEGIN
//-------------------------------------------------------------------
HI_VOID OPTM_VDP_CBM_SetMixerBkg            (OPTM_VDP_CBM_MIX_E u32mixer_id, OPTM_VDP_BKG_S *pstBkg);
HI_VOID OPTM_VDP_CBM_SetMixerPrio           (OPTM_VDP_CBM_MIX_E u32mixer_id, HI_U32 u32layer_id, HI_U32 u32prio);

//-------------------------------------------------------------------
//WBC_DHD0_BEGIN
//-------------------------------------------------------------------
HI_VOID OPTM_VDP_WBC_SetEnable              (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 bEnable);
HI_VOID OPTM_VDP_WBC_SetOutIntf             (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DATA_RMODE_E u32RdMode);
HI_VOID OPTM_VDP_WBC_SetOutFmt              (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_WBC_OFMT_E stIntfFmt);
HI_VOID OPTM_VDP_WBC_SetLayerAddr           (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32LAddr,HI_U32 u32CAddr,HI_U32 u32LStr, HI_U32 u32CStr);
HI_VOID OPTM_VDP_WBC_SetLayerReso           (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DISP_RECT_S *pstRect);
HI_VOID OPTM_VDP_WBC_SetDitherMode          (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DITHER_E enDitherMode);
HI_VOID OPTM_VDP_WBC_SetCropReso            (OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DISP_RECT_S *pstRect);
HI_VOID OPTM_VDP_WBC_SetRegUp               (OPTM_VDP_LAYER_WBC_E enLayer);

HI_VOID OPTM_VDP_WBC_SetThreeMd             (OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 bMode);

HI_U32 OPTM_VDP_DISP_GetIntSignal           (HI_U32 u32intmask);
HI_VOID OPTM_ClearIntSignal                 (HI_U32 u32intmask);
OPTM_VDP_DISP_MODE_E OPTM_DISP_GetDispMode  (HI_U32 u32Data);


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif
