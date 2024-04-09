/******************************************************************************

Copyright (C), 2009-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_aiao_func.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/09/22
Last Modified :
Description   : aiao
Function List :
History       :
* main\1    2012-09-22   sdk     init.
******************************************************************************/
#ifndef __HI_AIAO_FUNC_H__
#define __HI_AIAO_FUNC_H__

#include "hi_type.h"
#include "hal_aoe_common.h"
#include "hi_audsp_aoe.h"
#include "hi_drv_ao.h"
#ifdef __DPT__
#include "hi_unf_ai.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ******************************/

/* global function */
/* global function */
HI_S32                  iHAL_AOE_Init(HI_VOID);
HI_VOID                 iHAL_AOE_DeInit(HI_VOID);

/* AIP function */
HI_S32                  iHAL_AOE_AIP_Create(AOE_AIP_ID_E enAIP, AOE_AIP_CHN_ATTR_S* pstAttr);
HI_S32                  iHAL_AOE_AIP_SetAttr(AOE_AIP_ID_E enAIP, AOE_AIP_CHN_ATTR_S* pstAttr);
HI_S32                  iHAL_AOE_AIP_SetCmd(AOE_AIP_ID_E enAIP, AOE_AIP_CMD_E newcmd);
HI_U32                  iHAL_AOE_AIP_Group_SetCmd(AOE_AIP_CMD_E newcmd, HI_U32 u32SetCmdMask);
HI_VOID                 iHAL_AOE_AIP_SetVolume(AOE_AIP_ID_E enAIP, HI_U32 u32VolumedB);
HI_S32                  iHAL_AOE_AIP_SetSpeed(AOE_AIP_ID_E enAIP, HI_S32 u32AdjSpeed);
HI_VOID                 iHAL_AOE_AIP_SetLRVolume(AOE_AIP_ID_E enAIP, HI_U32 u32VolumeLdB, HI_U32 u32VolumeRdB);
HI_VOID                 iHAL_AOE_AIP_SetPrescale(AOE_AIP_ID_E enAIP, HI_U32 u32IntdB, HI_S32 s32DecdB);
HI_U32                  iHAL_AOE_AIP_GetRegAddr(AOE_AIP_ID_E enAIP);
HI_VOID                 iHAL_AOE_AIP_SetMute(AOE_AIP_ID_E enAIP, HI_BOOL bMute);
HI_VOID                 iHAL_AOE_AIP_SetChannelMode(AOE_AIP_ID_E enAIP, HI_U32 u32ChannelMode);
#ifdef __DPT__
HI_VOID                 iHAL_AOE_AIP_SetNRAttr(AOE_AIP_ID_E enAIP, HI_UNF_AI_NR_ATTR_S* pstNRParam);
#endif
HI_U32                  iHAL_AOE_AIP_GetFiFoDelayMs(AOE_AIP_ID_E enAIP);
HI_VOID                 iHAL_AOE_AIP_GetRptrAndWptrRegAddr(AOE_AIP_ID_E enAIP, HI_U32** ppu32WptrReg, HI_U32** ppu32RptrReg);
HI_VOID                 iHAL_AOE_AIP_ReSetRptrAndWptrReg(AOE_AIP_ID_E enAIP);

HI_VOID                 iHAL_AOE_AIP_EnableAlsa(AOE_AIP_ID_E enAIP, HI_BOOL bEnableAlsa);

HI_S32                  iHAL_AOE_AIP_SetFifoBypass(AOE_AIP_ID_E enAIP, HI_BOOL bEnable);
HI_S32                  iHAL_AOE_AIP_SetMixPriority(AOE_AIP_ID_E enAIP, HI_BOOL bMixPriority);
HI_VOID                 iHAL_AOE_AIP_SetFifoLatency(AOE_AIP_ID_E enAIP, HI_U32 u32LatencyMs);
HI_S32                  iHAL_AOE_AIP_AttachAop(AOE_AIP_ID_E enAIP, AOE_AOP_ID_E enAOP, HI_U32 u32SkipMs);
HI_S32                  iHAL_AOE_AIP_DetachAop(AOE_AIP_ID_E enAIP, AOE_AOP_ID_E enAOP);
HI_VOID                 iHAL_AOE_AIP_SetEos(AOE_AIP_ID_E enAIP, HI_BOOL bEos);
HI_VOID                 iHAL_AOE_AIP_SetResumeThresholdMs(AOE_AIP_ID_E enAIP, HI_U32 u32ThresholdMs);
HI_VOID                 iHAL_AOE_AIP_SetFade(AOE_AIP_ID_E enAIP, HI_BOOL bEnable, HI_U32 u32FadeinMs, HI_U32 u32FadeOutMs);

/* AOP function */
HI_VOID                 iHAL_AOE_AOP_SetLRVolume(AOE_AOP_ID_E enAOP, HI_U32 u32VolumeLdB, HI_U32 u32VolumeRdB);
HI_VOID                 iHAL_AOE_AOP_SetMute(AOE_AOP_ID_E enAOP, HI_BOOL bMute);
HI_VOID                 iHAL_AOE_AOP_SetPreciVol(AOE_AOP_ID_E enAOP, HI_U32 u32IntdB, HI_S32 s32DecdB);
HI_VOID                 iHAL_AOE_AOP_SetBalance(AOE_AOP_ID_E enAOP, HI_S32 s32Balance);
HI_S32                  iHAL_AOE_AOP_Create(AOE_AOP_ID_E enAOP, AOE_AOP_CHN_ATTR_S* pstAttr);
HI_VOID                 iHAL_AOE_AOP_Destroy(AOE_AOP_ID_E enAOP);
HI_S32                  iHAL_AOE_AOP_SetAttr(AOE_AOP_ID_E enAOP, AOE_AOP_CHN_ATTR_S* pstAttr);
HI_VOID                 iHAL_AOE_AOP_GetRptrAndWptrRegAddr(AOE_AOP_ID_E enAOP, HI_VOID** ppu32WptrReg, HI_VOID** ppu32RptrReg);
HI_S32                  iHAL_AOE_AOP_SetCmd(AOE_AOP_ID_E enAOP, AOE_AOP_CMD_E newcmd);
HI_S32                  iHAL_AOE_AOP_SetAefBypass(AOE_AOP_ID_E enAOP, HI_BOOL bBypass);

HI_S32                  iHAL_AOE_AOP_SetDrcEnable(AOE_AOP_ID_E enAOP, HI_BOOL bEnable);
HI_S32                  iHAL_AOE_AOP_SetDrcAttr(AOE_AOP_ID_E enAOP, HI_UNF_SND_DRC_ATTR_S* pstDrcAttr);
HI_S32                  iHAL_AOE_AOP_SetDrcChangeAttr(AOE_AOP_ID_E enAOP, HI_BOOL bEnable);
HI_S32                  iHAL_AOE_AOP_SetADOutputEnable(AOE_AOP_ID_E enAOP, HI_BOOL bEnable);
HI_S32                  iHAL_AOE_AOP_SetPeqAttr(AOE_AOP_ID_E enAOP, HI_UNF_SND_PEQ_ATTR_S* pstPeqAttr);
HI_S32                  iHAL_AOE_AOP_SetPeqEnable(AOE_AOP_ID_E enAop, HI_BOOL bEnable);
HI_S32                  iHAL_AOE_AOP_SetPeqChangeAttr(AOE_AOP_ID_E enAOP, HI_BOOL bEnable);
HI_S32                  iHAL_AOE_AOP_SetGeqChangeAttr(AOE_ENGINE_ID_E enEngine, HI_BOOL bEnable);

HI_S32                  iHAL_AOE_AOP_SetLatency(AOE_AOP_ID_E enAOP, HI_U32 u32Latency);
HI_S32                  iHAL_AOE_AOP_GetLatency(AOE_AOP_ID_E enAOP, HI_U32* pu32Latency);

/* ENGINE function */
HI_S32                  iHAL_AOE_ENGINE_Create(AOE_ENGINE_ID_E enENGINE, AOE_ENGINE_CHN_ATTR_S* pstAttr);
HI_VOID                 iHAL_AOE_ENGINE_Destroy(AOE_ENGINE_ID_E enENGINE);
HI_S32                  iHAL_AOE_ENGINE_SetCmd(AOE_ENGINE_ID_E enEngine, AOE_ENGINE_CMD_E newcmd);
HI_U32                  iHAL_AOE_ENGINE_Group_SetCmd(AOE_ENGINE_ID_E newcmd, HI_U32 u32SetCmdMask);

HI_S32                  iHAL_AOE_ENGINE_SetAttr(AOE_ENGINE_ID_E enENGINE, AOE_ENGINE_CHN_ATTR_S* pstAttr);
HI_S32                  iHAL_AOE_ENGINE_SetAvcAttr(AOE_ENGINE_ID_E enEngine, HI_UNF_SND_AVC_ATTR_S* pstAvcAttr);
HI_S32                  iHAL_AOE_ENGINE_SetAvcEnable(AOE_ENGINE_ID_E enEngine, HI_BOOL bEnable);
HI_S32                  iHAL_AOE_ENGINE_SetAvcChangeAttr(AOE_ENGINE_ID_E enEngine, HI_BOOL bEnable);

#ifdef __DPT__
HI_S32                  iHAL_AOE_ENGINE_SetGeqAttr(AOE_ENGINE_ID_E enEngine, HI_UNF_SND_GEQ_ATTR_S* pstGeqAttr);
HI_S32                  iHAL_AOE_ENGINE_SetGeqEnable(AOE_ENGINE_ID_E enEngine, HI_BOOL bEnable);
HI_S32                  iHAL_AOE_ENGINE_SetGeqGain(AOE_ENGINE_ID_E enEngine, HI_U32 u32Band, HI_S32 s32Gain);
#endif

HI_S32                  iHAL_AOE_ENGINE_AttachAip(AOE_ENGINE_ID_E enENGINE, AOE_AIP_ID_E enAIP);
HI_S32                  iHAL_AOE_ENGINE_DetachAip(AOE_ENGINE_ID_E enENGINE, AOE_AIP_ID_E enAIP);
HI_S32                  iHAL_AOE_ENGINE_AttachAop(AOE_ENGINE_ID_E enENGINE, AOE_AOP_ID_E enAOP);
HI_S32                  iHAL_AOE_ENGINE_DetachAop(AOE_ENGINE_ID_E enENGINE, AOE_AOP_ID_E enAOP);
HI_VOID                 iHAL_AOE_AOP_SetDelay(AOE_AOP_ID_E enAOP, HI_U32 u32RealDelayMS);
HI_VOID                 iHAL_AOE_AOP_GetDelay(AOE_AOP_ID_E enAOP, HI_U32* pu32RealDelayMS);

#ifdef __DPT__
HI_S32                  iHAL_AOE_ENGINE_AttachAef(AOE_ENGINE_ID_E enEngine, HI_U32 u32AefId);
HI_S32                  iHAL_AOE_ENGINE_DetachAef(AOE_ENGINE_ID_E enEngine, HI_U32 u32AefId);
#endif

HI_S32                  iHAL_AOE_ENGINE_SetConOutputEnable(AOE_ENGINE_ID_E enEngine, HI_BOOL bEnable);
HI_VOID                 iHAL_AOE_ENGINE_SetOutputAtmosEnable(AOE_ENGINE_ID_E enEngine, HI_BOOL bEnable);
HI_VOID                 iHAL_AOE_AIP_GetStatusPhy(HI_U32 aip, HI_PHYS_ADDR_T* tPhyDelayAddr);
HI_VOID                 iHAL_AOE_AIP_UpdateLatency(AOE_AIP_ID_E enAIP, HI_U32 u32Datams);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // __HI_AIAO_FUNC_H__
