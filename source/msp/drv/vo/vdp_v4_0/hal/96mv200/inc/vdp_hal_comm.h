#ifndef __HAL_COMM_H__
#define __HAL_COMM_H__

#include "vdp_define.h"
#include "hi_reg_common.h"

#if EDA_TEST
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ahb_bus_sys.h"
#endif


#ifndef __DISP_PLATFORM_BOOT__
#if VDP_CBB_FPGA
#include "linux/kernel.h"
#include <linux/string.h>

#endif

#endif


//HI_U32 VDP_RegRead(HI_U32 a);
//HI_VOID VDP_RegWrite(HI_U32 a, HI_U32 b);

HI_U32 VDP_RegRead( HI_ULONG a);
HI_VOID VDP_RegWrite( HI_ULONG  a, HI_U32 b);

#if (EDA_TEST & !BT_TEST)

HI_VOID vWrDis2Txt(char *DesFile, char *DesData);
HI_VOID vWrDat2Txt(char *DesFile, HI_U32 DesAddr, HI_U32 DesData);
HI_VOID vWrCoef2Txt(char *DesFile, HI_U32 DesAddr, HI_U32 DesData);
HI_VOID vWrDat2Bin(FILE *fpCfgOut, HI_U64  DesData);

//HI_U32 VDP_RegRead(HI_U32 * a);
//HI_VOID VDP_RegWrite(HI_U32 * a, HI_U32 b);
HI_U32 VDP_RegRead( HI_ULONG a);
HI_VOID VDP_RegWrite( HI_ULONG  a, HI_U32 b);

#endif

//-------------------------------------------------------------------
//Bus Function BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_SetVDPMemLowPower (HI_VOID);
HI_VOID VDP_SetClkGateEn       ( HI_U32 u32Data);
HI_VOID VDP_SetWrOutStd        ( HI_U32 u32Data, HI_U32 u32BusId, HI_U32 u32OutStd);
HI_VOID VDP_SetRdOutStd        ( HI_U32 u32Data, HI_U32 u32BusId, HI_U32 u32OutStd);
HI_VOID VDP_SetRdMultiIdEnable ( HI_U32 u32Data, HI_U32 u32Enable);

HI_VOID VDP_SetM0AndM1Sel (HI_U32 u32Data, HI_U32 u32MasterNum);
HI_VOID VDP_SetM2AndM3Sel (HI_U32 u32Data, HI_U32 u32MasterNum);
HI_VOID VDP_SetRdBusId    (HI_U32 u32bMode);

HI_VOID VDP_SetAxiMidEnable    (HI_U32 u32Enable);
//-------------------------------------------------------------------
//Bus Function END
//-------------------------------------------------------------------



//-------------------------------------------------------------------
//MIXER_BEGIN
//-------------------------------------------------------------------
HI_VOID VDP_CBM_SetMixerBkg              (VDP_CBM_MIX_E u32mixer_id, VDP_BKG_S stBkg);
HI_VOID VDP_CBM_Clear_MixvPrio           (HI_U32 u32layer_id);
HI_VOID VDP_CBM_SetMixerPrio             (VDP_CBM_MIX_E u32mixer_id, HI_U32 u32layer_id, HI_U32 u32prio);
//-------------------------------------------------------------------
//MIXER_END
//-------------------------------------------------------------------


HI_VOID VDP_SetCheckSumEnable          (HI_U32 bEnable);
HI_VOID VDP_SetTwoChnEnable            (HI_U32 bEnable);
HI_VOID VDP_SetTwoChnMode              (HI_U32 u32Data);

#endif//__HAL_COMM_H__
