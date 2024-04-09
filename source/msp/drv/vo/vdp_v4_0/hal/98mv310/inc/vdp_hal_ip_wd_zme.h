#ifndef __VDP_HAL_IP_WD_ZME_H__
#define __VDP_HAL_IP_WD_ZME_H__

#include "hi_reg_common.h"
#include "vdp_hal_comm.h"


HI_VOID VDP_WBC_VZME_SetCkGtEn(HI_U32 ck_gt_en);
HI_VOID VDP_WBC_VZME_SetOutFld(HI_U32 out_fld);
HI_VOID VDP_WBC_VZME_SetOutPro(HI_U32 out_pro);
HI_VOID VDP_WBC_VZME_SetOutHeight(HI_U32 out_height);
HI_VOID VDP_WBC_VZME_SetVlmscEn(HI_U32 vlmsc_en);
HI_VOID VDP_WBC_VZME_SetVchmscEn(HI_U32 vchmsc_en);
HI_VOID VDP_WBC_VZME_SetVlmidEn(HI_U32 vlmid_en);
HI_VOID VDP_WBC_VZME_SetVchmidEn(HI_U32 vchmid_en);
HI_VOID VDP_WBC_VZME_SetVlfirEn(HI_U32 vlfir_en);
HI_VOID VDP_WBC_VZME_SetVchfirEn(HI_U32 vchfir_en);
HI_VOID VDP_WBC_VZME_SetZmeOutFmt(HI_U32 zme_out_fmt);
HI_VOID VDP_WBC_VZME_SetZmeInFmt(HI_U32 zme_in_fmt);
HI_VOID VDP_WBC_VZME_SetVratio(HI_U32 vratio);
HI_VOID VDP_WBC_VZME_SetVlumaOffset(HI_U32 vluma_offset);
HI_VOID VDP_WBC_VZME_SetVchromaOffset(HI_U32 vchroma_offset);
HI_VOID VDP_WBC_VZME_SetVblumaOffset(HI_U32 vbluma_offset);
HI_VOID VDP_WBC_VZME_SetVbchromaOffset(HI_U32 vbchroma_offset);
HI_VOID VDP_WBC_VZME_SetApbVhdVfLren(HI_U32 apb_vhd_vf_lren);
HI_VOID VDP_WBC_VZME_SetApbVhdVfCren(HI_U32 apb_vhd_vf_cren);
HI_VOID VDP_WBC_VZME_SetApbVhdVcoefRaddr(HI_U32 apb_vhd_vcoef_raddr);

HI_VOID VDP_WBC_HZME_SetOutFmt(HI_U32 out_fmt);
HI_VOID VDP_WBC_HZME_SetCkGtEn(HI_U32 ck_gt_en);
HI_VOID VDP_WBC_HZME_SetOutWidth(HI_U32 out_width);
HI_VOID VDP_WBC_HZME_SetHlmscEn(HI_U32 hlmsc_en);
HI_VOID VDP_WBC_HZME_SetHchmscEn(HI_U32 hchmsc_en);
HI_VOID VDP_WBC_HZME_SetHlmidEn(HI_U32 hlmid_en);
HI_VOID VDP_WBC_HZME_SetHchmidEn(HI_U32 hchmid_en);
HI_VOID VDP_WBC_HZME_SetHlfirEn(HI_U32 hlfir_en);
HI_VOID VDP_WBC_HZME_SetHchfirEn(HI_U32 hchfir_en);
HI_VOID VDP_WBC_HZME_SetHratio(HI_U32 hratio);
HI_VOID VDP_WBC_HZME_SetHorLoffset(HI_U32 hor_loffset);
HI_VOID VDP_WBC_HZME_SetHorCoffset(HI_U32 hor_coffset);
HI_VOID VDP_WBC_HZME_SetApbVhdHfLren(HI_U32 apb_vhd_hf_lren);
HI_VOID VDP_WBC_HZME_SetApbVhdHfCren(HI_U32 apb_vhd_hf_cren);
HI_VOID VDP_WBC_HZME_SetApbVhdHycoefRaddr(HI_U32 apb_vhd_hycoef_raddr);
HI_VOID VDP_WBC_HZME_SetApbVhdHccoefRaddr(HI_U32 apb_vhd_hccoef_raddr);

#endif


