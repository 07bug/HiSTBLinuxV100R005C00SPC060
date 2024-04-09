#ifndef __HAL_VID_H__
#define __HAL_VID_H__

#include "vdp_define.h"
#include "vdp_ip_define.h"

#if EDA_TEST
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif

// #if VDP_C_COMPILE
// #include "vdp_alg.h"
// #endif
//-------------------------------------------------------------------
//VID_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_VID_SetReqCtrl             (HI_U32 u32Data, HI_U32 u32ReqCtrl);


HI_VOID VDP_VID_SetPreReadEnable       (HI_U32 u32Data, HI_U32 u32Enable );
HI_VOID VDP_VID_SetNoSecFlag           (HI_U32 u32Data, HI_U32 u32Enable );
HI_VOID VDP_VID_SetLayerEnable         (HI_U32 u32Data, HI_U32 u32bEnable );
HI_VOID VDP_VID_SetTileStride          (HI_U32 u32Data, HI_U32 u32LStr, HI_U32 u32CStr);
HI_VOID VDP_VID_SetLayerAddr           (HI_U32 u32Data, HI_U32 u32Chan, HI_U32 u32LAddr, HI_U32 u32CAddr, HI_U32 u32LStr, HI_U32 u32CStr);
HI_VOID VDP_VID_SetHeadAddr            (HI_U32 u32Data, HI_U32 u32LHeadAddr, HI_U32 u32CHeadAddr);
HI_VOID VDP_VID_SetHeadSize            (HI_U32 u32Data, HI_U32 u32HeadSize);
HI_VOID VDP_VID_SetHeadStride          (HI_U32 u32Data, HI_U32 u32HeadStride);
HI_VOID VDP_VID_SetInDataFmt           (HI_U32 u32Data, VDP_VID_IFMT_E  enDataFmt);
HI_VOID VDP_VID_SetDataWidth           (HI_U32 u32Data, HI_U32 DataWidth);
HI_VOID VDP_VID_SetReadMode            (HI_U32 u32Data, VDP_DATA_RMODE_E enLRMode, VDP_DATA_RMODE_E enCRMode);
HI_VOID VDP_VID_SetMuteEnable          (HI_U32 u32Data, HI_U32 bEnable);
HI_VOID VDP_VID_SetInReso              (HI_U32 u32Data, VDP_RECT_S  stRect);
HI_VOID VDP_VID_SetOutReso             (HI_U32 u32Data, VDP_RECT_S  stRect);
HI_VOID VDP_VID_SetVideoPos            (HI_U32 u32Data, VDP_RECT_S  stRect);
HI_VOID VDP_VID_SetDispPos             (HI_U32 u32Data, VDP_RECT_S  stRect);
HI_VOID VDP_VID_SetSrOutReso           (HI_U32 u32Data, VDP_RECT_S  stRect);

//U V Order
HI_VOID VDP_VID_SetUvorder             (HI_U32 u32Data, HI_U32 u32bUvorder);

//DCMP
HI_VOID VDP_VID_SetTileDcmpEnable      (HI_U32 u32Data, HI_U32 u32bEnable );
HI_VOID VDP_VID_SetDcmpOffset          (HI_U32 u32Data, HI_U32 u32laddr_offset , HI_U32  u32caddr_offset );

HI_VOID VDP_VID_SetIfirMode            (HI_U32 u32Data, VDP_IFIRMODE_E enMode);
HI_VOID VDP_VID_SetIfirCoef            (HI_U32 u32Data, HI_S32 *s32Coef);

HI_VOID VDP_VID_SetLayerGalpha         (HI_U32 u32Data, HI_U32 u32Alpha0);

HI_VOID VDP_VID_SetCropReso            (HI_U32 u32Data, VDP_RECT_S stRect);

HI_VOID VDP_VID_SetLayerBkg            (HI_U32 u32Data, VDP_BKG_S stBkg);

HI_VOID VDP_VID_SetCscDcCoef           (HI_U32 u32Data, VDP_CSC_DC_COEF_S pstCscCoef);
HI_VOID VDP_VID_SetCscCoef             (HI_U32 u32Data, VDP_CSC_COEF_S stCscCoef);
HI_VOID VDP_VID_SetCscEnable           (HI_U32 u32Data, HI_U32 u32bCscEn);

HI_VOID VDP_SetWbcMd                   (HI_U32 enMdSel);
HI_VOID VDP_SetInDataWidth             (HI_U32 u32Data, HI_U32 u32idatawth);
HI_VOID VDP_SetWbcOutMode              (HI_U32 u32Data, VDP_DATA_RMODE_E enRdMode);
//HI_VOID VDP_SetTimeOut                 (HI_U32 u32Data, HI_U32 u32TData);
HI_VOID VDP_VID_SetDrawMode            (HI_U32 u32Data, HI_U32 u32ModeLuma, HI_U32 u32ModeChroma);
HI_VOID VDP_VID_SetDrawPixelMode       (HI_U32 u32Data, HI_U32 u32DrawPixelMode);


HI_VOID VDP_VID_SetMultiModeEnable     (HI_U32 u32Data, HI_U32 u32Enable );
HI_VOID VDP_VID_SetRegionEnable        (HI_U32 u32Data, HI_U32 u32Num, HI_U32 u32bEnable );
HI_VOID VDP_VID_SetAllRegionDisable    (HI_U32 u32Data );
HI_BOOL VDP_VID_CheckRegionState(HI_U32 u32Data);
HI_VOID VDP_VID_SetRegionAddr          (HI_U32 u32Data, HI_U32 u32Num, HI_U32 u32LAddr, HI_U32 u32CAddr, HI_U32 u32LStr, HI_U32 u32CStr);
HI_VOID VDP_VID_SetRegionReso          (HI_U32 u32Data, HI_U32 u32Num, VDP_RECT_S  stRect);
HI_VOID VDP_VID_SetRegionMuteEnable    (HI_U32 u32Data, HI_U32 u32Num, HI_U32 bEnable);

HI_VOID VDP_VID_SetRegUp               (HI_U32 u32Data);

//-------------------------------------------------------------------
//ZME_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_VID_SetZmeEnable           (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetVtapReduce          (HI_U32 u32Data, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetZmeShootCtrlEnable  (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable, HI_U32 u32bMode);
HI_VOID VDP_VID_SetZmePhase            (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_S32 s32Phase);
HI_VOID VDP_VID_SetZmeFirEnable        (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetZmeMidEnable        (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetZmeHorRatio         (HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID VDP_VID_SetZmeVerRatio         (HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID VDP_VID_SetZmeHfirOrder        (HI_U32 u32Data, HI_U32 u32HfirOrder);
HI_VOID VDP_VID_SetZmeCoefAddr         (HI_U32 u32Data, HI_U32 u32Mode, HI_U32 u32Addr);
HI_VOID VDP_VID_SetZmeInFmt            (HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt);
HI_VOID VDP_VID_SetZmeOutFmt           (HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt);
HI_VOID  VDP_VID_SetHdrElZme           (HI_U32 u32Data, HI_U32 u32bEnable);
// VID.ZME.NONLINE begin

HI_VOID VDP_VID_SetParaUpd             (HI_U32 u32Data, VDP_VID_PARA_E enMode);

#if VID_ZME2_EN
//-------------------------------------------------------------------
//ZME2_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_VID_SetZme2Enable           (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetZme2VtapReduce          (HI_U32 u32Data, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetZme2Phase            (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_S32 s32Phase);
HI_VOID VDP_VID_SetZme2FirEnable        (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetZme2MidEnable        (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable);
HI_VOID VDP_VID_SetZme2HorRatio         (HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID VDP_VID_SetZme2VerRatio         (HI_U32 u32Data, HI_U32 u32Ratio);
HI_VOID VDP_VID_SetZme2CoefAddr         (HI_U32 u32Data, HI_U32 u32Mode, HI_U32 u32Addr);
// VID.ZME.NONLINE begin
#endif


//-------------------------------------------------------------------
//VID_END
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//VP_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_VP_SetVideoPos             (HI_U32 u32Data, VDP_RECT_S  stRect);
HI_VOID VDP_VP_SetDispPos              (HI_U32 u32Data, VDP_RECT_S  stRect);
HI_VOID VDP_VP_SetInReso               (HI_U32 u32Data, VDP_RECT_S  stRect);
HI_VOID VDP_VP_SetRegUp                (HI_U32 u32Data);
HI_VOID VDP_VP_SetLayerGalpha          (HI_U32 u32Data, HI_U32 u32Alpha);
HI_VOID VDP_VP_SetMuteEnable           (HI_U32 u32Data, HI_U32 bEnable);
HI_VOID VDP_VP_SetMuteBkg              (HI_U32 u32Data, VDP_VP_MUTE_BK_S stVpMuteBkg);

//-------------------------------------------------------------------
//VP_END
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//ACM_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_VP_SetAcmEnable            (HI_U32 u32Data, HI_U32 u32bAcmEn);
//-------------------------------------------------------------------
//ACM_END
//-------------------------------------------------------------------
HI_VOID VDP_VP_SetAccWeightAddr        (HI_U32 u32Data, HI_U32 uAccAddr);
//acc
HI_VOID vSetAccCoef                    (VDP_LAYER_VP_E enLayer);

HI_VOID VDP_VID_SetConnection          (HI_U32 u32LayerId, HI_U32 u32Data );
HI_U32  VDP_ReadCoefData(HI_VOID);

HI_VOID VDP_VP_SetDciEnable(HI_U32 u32Data, HI_U32 u32DciEn);

HI_VOID VDP_VID_SetSrcCropReso        (HI_U32 u32Data, VDP_RECT_S stRect);

//add HZME
HI_VOID VDP_VID_SetHpzmeHpzmeEn(HI_U32 u32Data, HI_U32 hpzme_en);
//HI_VOID VDP_VID_SetHpzmeHpzmeMidEn(HI_U32 u32Data, HI_U32 hpzme_mid_en);
HI_VOID VDP_VID_SetHpzmeHpzmeMode(HI_U32 u32Data, HI_U32 hpzme_mode);
HI_VOID VDP_VID_SetHpzmeCoef2(HI_U32 u32Data, HI_U32 coef2);
HI_VOID VDP_VID_SetHpzmeCoef1(HI_U32 u32Data, HI_U32 coef1);
HI_VOID VDP_VID_SetHpzmeCoef0(HI_U32 u32Data, HI_U32 coef0);
#endif
