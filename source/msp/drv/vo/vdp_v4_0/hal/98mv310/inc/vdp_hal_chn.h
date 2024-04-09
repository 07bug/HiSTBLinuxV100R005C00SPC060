#ifndef __VDP_HAL_CHN_H__
#define __VDP_HAL_CHN_H__

#if EDA_TEST
#include <stdio.h>
#include <stdlib.h>
#include <vdp_assert.h>
#endif
#include "vdp_define.h"
#include "vdp_ip_define.h"

//-------------------------------------------------------------------
//DISP_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_DISP_SetUfOffineEn         (HI_U32 u32hd_id, HI_U32 u32UfOfflineEn);
HI_VOID VDP_DISP_SetDispMode           (HI_U32 u32hd_id, HI_U32 u32DispMode);
HI_VOID VDP_DISP_SetHdmiMode           (HI_U32 u32hd_id, HI_U32 u32hdmi_md);
HI_VOID VDP_DISP_SetHdmi420Enable      (HI_U32 u32hd_id, HI_U32 u32Enable);
HI_VOID VDP_DISP_SetHdmi420CSel        (HI_U32 u32hd_id, HI_U32 u32CSel);
HI_VOID VDP_DISP_SetRegUp              (HI_U32 u32hd_id);
HI_VOID VDP_DISP_SetIntfEnable         (HI_U32 u32hd_id, HI_U32 bTrue);
HI_VOID VDP_DISP_SetIntMask            (HI_U32 u32masktypeen);
HI_VOID VDP_DISP_SetIntDisable         (HI_U32 u32masktypeen);
HI_VOID VDP_DISP_SetOflIntMask         (HI_U32 u32masktypeen);
HI_VOID VDP_DISP_SetOflIntDisable      (HI_U32 u32masktypeen);
HI_VOID VDP_DISP_BfmClkSel             (HI_U32 u32Num);
HI_VOID VDP_DISP_OpenIntf              (HI_U32 u32hd_id, VDP_DISP_SYNCINFO_S stSyncInfo);
HI_VOID VDP_DISP_OpenTypIntf           (HI_U32 u32hd_id, VDP_DISP_DIGFMT_E enDigFmt);
HI_VOID VDP_DISP_SetVSync              (HI_U32 u32hd_id, HI_U32 u32vfb, HI_U32 u32vbb, HI_U32 u32vact);
HI_VOID VDP_DISP_SetVSyncPlus          (HI_U32 u32hd_id, HI_U32 u32bvfb, HI_U32 u32bvbb, HI_U32 u32vact);
HI_VOID VDP_DISP_SetHSync              (HI_U32 u32hd_id, HI_U32 u32hfb, HI_U32 u32hbb, HI_U32 u32hact);
HI_VOID VDP_DISP_SetSyncInv            (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf,  VDP_DISP_SYNCINV_S enInv);
HI_VOID VDP_DISP_SetPlusWidth          (HI_U32 u32hd_id, HI_U32 u32hpw, HI_U32 u32vpw);
HI_VOID VDP_DISP_SetPlusPhase          (HI_U32 u32hd_id, HI_U32 u32ihs, HI_U32 u32ivs, HI_U32 u32idv);
HI_VOID VDP_DISP_SetIntfMuxSel         (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf);
HI_VOID VDP_DISP_SetSplitMode          (HI_U32 u32hd_id, HI_U32 u32SplitMode);

HI_U32  VDP_DISP_GetIntSta             (HI_U32 u32intmask);
HI_VOID VDP_DISP_ClearIntSta           (HI_U32 u32intmask);
HI_VOID VDP_DISP_SetVtThdMode          (HI_U32 u32hd_id, HI_U32 u32uthdnum, HI_U32 u32mode);
HI_VOID VDP_DISP_SetVtThd              (HI_U32 u32hd_id, HI_U32 u32uthdnum, HI_U32 u32vtthd);

HI_VOID VDP_DISP_SetWcgEnable         (HI_U32 u32Data, HI_U32 u32Enable);
HI_VOID VDP_DISP_SetWcgCoef           (HI_U32 u32Data, VDP_WCG_COEF_S stWcgCoef);

HI_VOID VDP_DISP_SetHbiSyncEnable     ( HI_U32 u32Data, HI_U32 u32HbiSyncEnable );
HI_VOID VDP_DISP_SetHbiHcEnable       ( HI_U32 u32Data, HI_U32 u32HbiHcEnable   );
HI_VOID VDP_DISP_SetHbiOsdEnable      ( HI_U32 u32Data, HI_U32 u32HbiOsdEnable  );
HI_VOID VDP_DISP_SetVbiEnable         ( HI_U32 u32Data, HI_U32 u32VbiEnable     );
HI_VOID VDP_DISP_SetVbiData           (HI_U32 u32Data, HI_U32 u32VbiAddr, HI_U32 u32VbiData);
HI_VOID VDP_DISP_SetHbiHcThd          ( HI_U32 u32Data, HI_U32 u32HbiHcThd);
HI_VOID VDP_DISP_SetHbiOsdThd         ( HI_U32 u32Data, HI_U32 u32HbiOsdThd);
HI_VOID VDP_DISP_ClearIntMask         (HI_U32 u32masktypeen);
HI_VOID VDP_DISP_SetPauseMode         (HI_U32 u32hd_id, HI_U32 enable);
HI_VOID VDP_DISP_SetPreStartPos       (HI_U32 pre_start_pos);
HI_VOID VDP_DISP_SetPreStartLinePos   (HI_U32 pre_start_line_pos);
HI_VOID VDP_DISP_SetIntfRgbModeEn     (HI_U32 u32En);

//-------------------------------------------------------------------
//DISP_END
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//CBAR_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_DISP_SetCbarEnable         (HI_U32 u32hd_id,HI_U32 bTrue);
HI_VOID VDP_DISP_SetCbarSel            (HI_U32 u32hd_id,HI_U32 u32cbar_sel);
//-------------------------------------------------------------------
//CBAR_END
//-------------------------------------------------------------------


//-------------------------------------------------------------------
//IPU_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_DISP_SetDitherMode         (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, VDP_DITHER_E enDitherMode);
HI_VOID VDP_DISP_SetDitherRoundEnable  (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, HI_U32 u32Enable);
HI_VOID VDP_DISP_SetDitherEnable       (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, HI_U32 u32Enable);
HI_VOID VDP_DISP_SetDitherCoef         (HI_U32 u32hd_id, VDP_DISP_INTF_E enChan, VDP_DITHER_COEF_S dither_coefs);

HI_VOID VDP_DISP_SetClipEnable         (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf);
HI_VOID VDP_DISP_SetClipCoef           (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, VDP_DISP_CLIP_S stClipData);

HI_VOID VDP_DISP_SetCscEnable          (HI_U32 u32hd_id, HI_U32  enCSC);
HI_VOID VDP_DISP_SetCscDcCoef          (HI_U32 u32hd_id, VDP_CSC_DC_COEF_S stCscCoef);
HI_VOID VDP_DISP_SetCscCoef            (HI_U32 u32hd_id, VDP_CSC_COEF_S stCscCoef);
HI_VOID VDP_DISP_SetCscMode            (HI_U32 u32hd_id, VDP_CSC_MODE_E enCscMode);

HI_VOID VDP_DISP_SetGammaEnable        (HI_U32 u32hd_id, HI_U32 u32GmmEn);
HI_VOID VDP_DISP_SetGammaAddr          (HI_U32 u32hd_id, HI_U32 u32uGmmAddr);
HI_VOID VDP_DISP_SetMirrorEnable       (HI_U32 u32hd_id, HI_U32 u32MirrEn);
HI_VOID VDP_DISP_SetParaUpd            (HI_U32 u32hd_id, VDP_DISP_PARA_E enPara);
HI_VOID VDP_DISP_SetProToInterEnable   (HI_U32 u32hd_id, HI_U32 u32Enable);
//-------------------------------------------------------------------
//IPU_END
//-------------------------------------------------------------------

HI_VOID VDP_DISP_SetStartPos (HI_U32 u32Data, HI_U32 u32StartPos);
HI_VOID VDP_DISP_SetParaLoadPos (HI_U32 u32Data, HI_U32 u32StartPos);

HI_VOID VDP_DISP_GetVactState(HI_U32 u32hd_id, HI_BOOL *pbBtm, HI_U32 *pu32Vcnt);

HI_U32 VDP_DISP_GetDispMode(HI_U32 u32hd_id);

HI_VOID VDP_DISP_GetDHD0VblankState(HI_BOOL *bVblank);

HI_VOID VDP_DISP_SetNxgDataSwapEnable(HI_U32 u32hd_id, HI_U32 enable);

#endif
