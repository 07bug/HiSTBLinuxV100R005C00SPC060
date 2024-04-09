#ifndef __VDP_HAL_COMM_H__
#define __VDP_HAL_COMM_H__

#include "vdp_define.h"
//#include "vdp_reg.h"
#include "hi_reg_common.h"
#include "vdp_hal_ip_master.h"
//#include "hi_drv_mmz.h"
//#include "xdp_basefunc.h"
//#include <linux/kernel.h>
//#include <linux/vmalloc.h>
#include "drv_disp_osal.h"


HI_U32 VDP_RegRead( HI_ULONG a);
HI_VOID VDP_RegWrite( HI_ULONG  a, HI_U32 b);
HI_U32  VDP_DdrRead(volatile HI_U32* a);

HI_U32  VDP_RegReadEx(HI_U32 a);
HI_VOID VDP_RegWriteEx(HI_U32 a, HI_U32 b);

HI_VOID VDP_SetVdpFpgaDebugWrite(HI_U32 u32Data);
HI_S32 VDP_SetVdpFpgaDebugRead(HI_VOID);
#ifndef __DISP_PLATFORM_BOOT__
HI_S32 XDP_CalcRunTime(HI_VOID);
#endif

//-------------------------------------------------------------------
//Bus Function BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_SetVDPMemLowPower (HI_VOID);
//MV300 MST
HI_VOID VDP_SetWrOutStd        ( HI_U32 u32Data, HI_U32 u32BusId, HI_U32 u32OutStd);
HI_VOID VDP_SetRdOutStd        ( HI_U32 u32Data, HI_U32 u32BusId, HI_U32 u32OutStd);
HI_VOID VDP_SetRdMultiIdEnable ( HI_U32 u32Data, HI_U32 u32Enable);
HI_VOID VDP_SetAxiMidEnable    ( HI_U32 u32Enable);
HI_VOID VDP_SetArbMode         ( HI_U32 u32Data, HI_U32 u32bMode);
HI_VOID VDP_SetParaMasterSel   ( HI_U32 u32MasterNum);
HI_VOID VDP_SetAxiEdgeMode     ( VDP_AXI_EDGE_MODE_E EdgeMode);

//MV300 SYSTEM
HI_VOID VDP_SetClkGateEn       ( HI_U32 u32Data);
HI_VOID VDP_SetCheckSumEnable  ( HI_U32 bEnable);
HI_VOID VDP_CBM_Clear_MixvPrio ( HI_U32 u32layer_id);
HI_VOID VDP_CBM_SetMixerBkg    ( VDP_CBM_MIX_E u32mixer_id, VDP_BKG_S stBkg);
HI_VOID VDP_CBM_SetMixerPrio   ( VDP_CBM_MIX_E u32mixer_id, HI_U32 u32layer_id,HI_U32 u32prio);
HI_VOID VDP_CBM_ResetMixerPrio ( VDP_CBM_MIX_E u32mixer_id);

#endif//__HAL_COMM_H__
