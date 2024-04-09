#ifndef __HAL_GFX_H__
#define __HAL_GFX_H__
#if EDA_TEST
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif
#include "vdp_define.h"
#include "vdp_ip_define.h"


//-------------------------------------------------------------------
//GFX_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_GFX_SetReqCtrl             (HI_U32 u32Data, HI_U32 u32ReqCtrl);

HI_VOID VDP_GFX_SetPreMultEnable      (HI_U32 u32Data, HI_U32 bEnable);
HI_VOID VDP_GFX_MixvBypassEn (HI_U32 u32En);
HI_VOID VDP_GFX_MixvPremultEn (HI_U32 u32En);
HI_VOID VDP_GFX_MixvBypassMode (HI_U32 u32Mode);
HI_VOID VDP_DRV_GetGfxState(HI_BOOL *pbNeedProcessGfx);
//-------------------------------------------------------------------
//GFX_END
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//GP_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_GP_SetRegUp                (HI_U32 u32Data);
HI_VOID VDP_GP_SetDePreMultEnable      (HI_U32 u32Data, HI_U32 bEnable);
HI_VOID VDP_GP_SetCscDcCoef   (HI_U32 u32Data, VDP_CSC_DC_COEF_S pstCscCoef);
HI_VOID VDP_GP_SetCscCoef(HI_U32 u32Data, VDP_CSC_COEF_S stCscCoef);


//-------------------------------------------------------------------
//GPX_END
//-------------------------------------------------------------------



#endif
