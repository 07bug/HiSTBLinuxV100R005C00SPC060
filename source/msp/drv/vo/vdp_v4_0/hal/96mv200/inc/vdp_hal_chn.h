#ifndef __HAL_CHN_H__
#define __HAL_CHN_H__

#if EDA_TEST
#include <stdio.h>
#include <stdlib.h>
#include <vdp_assert.h>
#endif
#include "vdp_define.h"
#include "vdp_ip_define.h"
#if VDP_CBB_FPGA
//#include "vdp_assert.h"
#endif

//-------------------------------------------------------------------
//DISP_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_DISP_SetDispMode           (HI_U32 u32hd_id, HI_U32 u32DispMode);
//HI_VOID VDP_DISP_SetFramePackingEn     (HI_U32 u32hd_id, HI_U32 u32Enable);
HI_VOID VDP_DISP_SetHdmiMode           (HI_U32 u32hd_id, HI_U32 u32hdmi_md);
HI_VOID VDP_DISP_SetRegUp              (HI_U32 u32hd_id);
HI_VOID VDP_DISP_SetIntfEnable         (HI_U32 u32hd_id, HI_U32 bTrue);
HI_VOID VDP_DISP_SetIntMask            (HI_U32 u32masktypeen);
HI_VOID VDP_DISP_SetIntDisable         (HI_U32 u32masktypeen);
HI_U32 VDP_DISP_GetDispMode(HI_U32 u32hd_id);

HI_VOID VDP_DISP_OpenIntf              (HI_U32 u32hd_id, VDP_DISP_SYNCINFO_S stSyncInfo);
HI_VOID VDP_DISP_SetSyncInv            (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf,  VDP_DISP_SYNCINV_S enInv);
HI_VOID VDP_DISP_SetIntfMuxSel         (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf);

HI_U32  VDP_DISP_GetIntSta             (HI_U32 u32intmask);
HI_VOID VDP_DISP_ClearIntSta           (HI_U32 u32intmask);
HI_VOID VDP_DISP_SetVtThdMode          (HI_U32 u32hd_id, HI_U32 u32uthdnum, HI_U32 u32mode);
HI_VOID VDP_DISP_SetVtThd              (HI_U32 u32hd_id, HI_U32 u32uthdnum, HI_U32 u32vtthd);

HI_VOID VDP_DISP_SetNxgDataSwapEnable(HI_U32 u32hd_id, HI_U32 enable);

//-------------------------------------------------------------------
//DISP_END
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//IPU_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_DISP_SetClipCoef           (HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, VDP_DISP_CLIP_S stClipData);
HI_VOID VDP_DISP_SetCscEnable          (HI_U32 u32hd_id, HI_U32  enCSC);
HI_VOID VDP_DISP_SetProToInterEnable   (HI_U32 u32hd_id, HI_U32 u32Enable);
//-------------------------------------------------------------------
//IPU_END
//-------------------------------------------------------------------

//LVDS
HI_VOID VDP_DISP_SetNxgDataSwapEnable(HI_U32 u32hd_id, HI_U32 enable);
HI_VOID VDP_DISP_GetVactState(HI_U32 u32hd_id, HI_BOOL *pbBtm, HI_U32 *pu32Vcnt);


#endif
