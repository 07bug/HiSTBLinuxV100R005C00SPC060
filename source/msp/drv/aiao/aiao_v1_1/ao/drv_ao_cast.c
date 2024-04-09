/*******************************************************************************
 *              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: drv_ao_cast.c
 * Description: aiao interface of module.
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 * main\1
 ********************************************************************************/
#include "hi_type.h"

#include "hi_error_mpi.h"

#include "audio_util.h"
#include "drv_ao_op.h"
#include "hal_aoe_func.h"
#include "hal_aiao_func.h"
#include "hal_aiao_common.h"
#include "hal_aoe_common.h"
#include "hal_aoe.h"
#include "hal_cast.h"

#include "drv_ao_track.h"

#include "drv_ao_cast.h"

/* always use this to get pCast from pCard */
#define CAST_FIND_BY_ID(pCard, u32CastID, pCast) \
    do { \
        if (AO_MAX_CAST_NUM <= u32CastID) { \
            HI_ERR_AO("Invalid Cast ID(0x%x)\n", u32CastID); \
            return HI_ERR_AO_INVALID_ID; \
        } \
        pCast = (SND_CAST_STATE_S*)pCard->pCast[u32CastID]; \
        if (HI_NULL == pCast) { \
            HI_ERR_AO("Cast State is NULL (u32CastID = 0x%x)\n", u32CastID); \
            return HI_ERR_AO_NULL_PTR; \
        } \
    } while (0)

static AOE_ENGINE_ID_E CASTGetEngineByType(SND_CARD_STATE_S* pCard, SND_ENGINE_TYPE_E enEngineType)
{
    SND_ENGINE_STATE_S* pEngine;

    if (SND_ENGINE_TYPE_BUTT <= enEngineType)
    {
        return AOE_ENGINE_BUTT;
    }

    pEngine = (SND_ENGINE_STATE_S*)pCard->pSndEngine[enEngineType];
    if (HI_NULL == pEngine)
    {
        return AOE_ENGINE_BUTT;
    }

    return pEngine->enEngine;
}

static AOE_AOP_ID_E CASTGetAopById(SND_CARD_STATE_S* pCard, HI_U32 u32CastID)
{
    SND_OP_STATE_S* pSndOp;

    if (AO_MAX_CAST_NUM <= u32CastID)
    {
        HI_ERR_AO("Invalid CastId\n");
        return AOE_AOP_BUTT;
    }

    pSndOp = (SND_OP_STATE_S*)pCard->pCastOp[u32CastID];
    if (HI_NULL == pSndOp)
    {
        HI_ERR_AO("Cast Op is NULL\n");
        return AOE_AOP_BUTT;
    }

    if (AO_SNDOP_MAX_AOP_NUM <= pSndOp->ActiveId)
    {
        HI_ERR_AO("Invalid ActiveId in SND_OP_STATE_S\n");
        return AOE_AOP_BUTT;
    }

    return pSndOp->enAOP[pSndOp->ActiveId];
}

static HI_S32 CASTSetEnable(SND_CARD_STATE_S* pCard, SND_CAST_STATE_S* pCast, HI_BOOL bEnable)
{
    AOE_AOP_ID_E enAOP;
    AOE_ENGINE_ID_E enEngine;

    enAOP = CASTGetAopById(pCard, pCast->CastId);
    if (AOE_AOP_BUTT == enAOP)
    {
        HI_ERR_AO("CASTGetAopById failed\n");
        return HI_FAILURE;
    }

    enEngine = CASTGetEngineByType(pCard, SND_ENGINE_TYPE_PCM);
    if (AOE_ENGINE_BUTT == enEngine)
    {
        pCast->enCurnStatus = SND_CAST_STATUS_STOP;
        HI_WARN_AO("Try to %s Cast(%d), but pcm engine not found.\n", (HI_TRUE == bEnable) ? "Enable" : "Disable", pCast->CastId);
        return HI_SUCCESS;
    }

    if (HI_TRUE == bEnable)
    {
        HAL_AOE_ENGINE_AttachAop(enEngine, enAOP);
        SND_StartCastOp(pCard, pCast->CastId);
        pCast->enCurnStatus = SND_CAST_STATUS_START;
    }
    else
    {
        SND_StopCastOp(pCard, pCast->CastId);
        HAL_AOE_ENGINE_DetachAop(enEngine, enAOP);
        pCast->enCurnStatus = SND_CAST_STATUS_STOP;
    }

    return HI_SUCCESS;
}

static HI_S32 CASTSetMute(SND_CARD_STATE_S* pCard, SND_CAST_STATE_S* pCast, HI_BOOL bMute)
{
    AOE_AOP_ID_E enAOP = AOE_AOP_BUTT;

    enAOP = CASTGetAopById(pCard, pCast->CastId);
    if (AOE_AOP_BUTT == enAOP)
    {
        HI_ERR_AO("CASTGetAopById failed\n");
        return HI_FAILURE;
    }

    return HAL_AOE_AOP_SetMute(enAOP, bMute);
}

#ifdef __DPT__
HI_S32 CAST_SetAllMute(SND_CARD_STATE_S* pCard, HI_BOOL bMute)
{
    HI_U32 CastId;
    SND_CAST_STATE_S* pCast;

    for (CastId = 0; CastId < AO_MAX_CAST_NUM; CastId++)
    {
        pCast = (SND_CAST_STATE_S*)pCard->pCast[CastId];
        if (HI_NULL == pCast)
        {
            continue;
        }

        if (HI_FALSE == pCast->bMute && HI_FALSE == bMute)
        {
            HI_INFO_AO("Set cast(%d) unmute\n", CastId);
            CASTSetMute(pCard, pCast, HI_FALSE);
        }
        else
        {
            HI_INFO_AO("Set cast(%d) mute\n", CastId);
            CASTSetMute(pCard, pCast, HI_TRUE);
        }
    }

    return HI_SUCCESS;
}
#endif

HI_S32 CAST_SetMute(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, HI_BOOL bMute)
{
    SND_CAST_STATE_S* pCast;

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    if (
#ifdef __DPT__
        HI_FALSE == pCard->bAllCastMute &&
#endif
        HI_FALSE == bMute)
    {
        HI_INFO_AO("Set cast(%d) unmute\n", u32CastID);
        CASTSetMute(pCard, pCast, HI_FALSE);
    }
    else
    {
        HI_INFO_AO("Set cast(%d) mute\n", u32CastID);
        CASTSetMute(pCard, pCast, HI_TRUE);
    }

    pCast->bMute = bMute;

    return HI_SUCCESS;
}

HI_S32 CAST_GetMute(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, HI_BOOL* pbMute)
{
    SND_CAST_STATE_S* pCast;

    if (HI_NULL == pbMute)
    {
        return HI_FAILURE;
    }

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    *pbMute = pCast->bMute;

    return HI_SUCCESS;
}

static HI_S32 CASTSetVolume(SND_CARD_STATE_S* pCard, SND_CAST_STATE_S* pCast, HI_U32 u32VolumeLdB, HI_U32 u32VolumeRdB)
{
    AOE_AOP_ID_E enAOP = AOE_AOP_BUTT;

    enAOP = CASTGetAopById(pCard, pCast->CastId);
    if (AOE_AOP_BUTT == enAOP)
    {
        HI_ERR_AO("CASTGetAopById failed\n");
        return HI_FAILURE;
    }

    return HAL_AOE_AOP_SetLRVolume(enAOP, u32VolumeLdB, u32VolumeRdB);
}

HI_S32 CAST_SetAbsGain(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, HI_UNF_SND_ABSGAIN_ATTR_S* pstCastAbsGain)
{
    SND_CAST_STATE_S* pCast;
    HI_U32 u32dBLReg;
    HI_U32 u32dBRReg;

    if (HI_NULL == pstCastAbsGain)
    {
        return HI_FAILURE;
    }
    if (HI_TRUE == pstCastAbsGain->bLinearMode)
    {
        CHECK_AO_LINEARVOLUME(pstCastAbsGain->s32GainL);
        CHECK_AO_LINEARVOLUME(pstCastAbsGain->s32GainR);

        u32dBLReg = AUTIL_VolumeLinear2RegdB((HI_U32)pstCastAbsGain->s32GainL);
        u32dBRReg = AUTIL_VolumeLinear2RegdB((HI_U32)pstCastAbsGain->s32GainR);
    }
    else
    {
        CHECK_AO_ABSLUTEVOLUMEEXT(pstCastAbsGain->s32GainL);
        CHECK_AO_ABSLUTEVOLUMEEXT(pstCastAbsGain->s32GainR);

        u32dBLReg = AUTIL_VolumedB2RegdB(pstCastAbsGain->s32GainL);
        u32dBRReg = AUTIL_VolumedB2RegdB(pstCastAbsGain->s32GainR);
    }

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    CASTSetVolume(pCard, pCast, u32dBLReg, u32dBRReg);

    pCast->stCastAbsGain.bLinearMode = pstCastAbsGain->bLinearMode;
    pCast->stCastAbsGain.s32GainL = pstCastAbsGain->s32GainL;
    pCast->stCastAbsGain.s32GainR = pstCastAbsGain->s32GainR;
    return HI_SUCCESS;
}

HI_S32 CAST_GetAbsGain(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, HI_UNF_SND_ABSGAIN_ATTR_S* pstCastAbsGain)
{
    SND_CAST_STATE_S* pCast;

    if (HI_NULL == pstCastAbsGain)
    {
        return HI_FAILURE;
    }
    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    pstCastAbsGain->bLinearMode = pCast->stCastAbsGain.bLinearMode;
    pstCastAbsGain->s32GainL = pCast->stCastAbsGain.s32GainL;
    pstCastAbsGain->s32GainR = pCast->stCastAbsGain.s32GainR;
    return HI_SUCCESS;
}

HI_S32 CAST_SetAefBypass(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, HI_BOOL bBypass)
{
    AOE_AOP_ID_E enAOP = AOE_AOP_BUTT;
    SND_CAST_STATE_S* pCast;

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    enAOP = CASTGetAopById(pCard, pCast->CastId);
    if (AOE_AOP_BUTT == enAOP)
    {
        HI_ERR_AO("CASTGetAopById failed\n");
        return HI_FAILURE;
    }

    return HAL_AOE_AOP_SetAefBypass(enAOP, bBypass);
}

#ifdef HI_PROC_SUPPORT
HI_VOID CAST_ReadProc(struct seq_file* p, SND_CARD_STATE_S* pCard)
{
    SND_CAST_STATE_S* pCast;
    HI_U32 i;
    HI_VOID* pSndOp;
    AOE_AOP_ID_E Aop;

    for (i = 0; i < AO_MAX_CAST_NUM; i++)
    {
        if (!(pCard->uSndCastInitFlag & ((HI_U32)1L << i)))
        {
            continue;
        }

        pCast = (SND_CAST_STATE_S*)pCard->pCast[i];
        pSndOp = pCard->pCastOp[pCast->CastId];
        Aop = SND_GetOpAopId(pSndOp);
        PROC_PRINT(p,
                   "Cast(%d): *Aop(0x%x), Status(%s), UserEnable(%s), Weight(%.3d/%.3d%s), Mute(%s)",
                   pCast->CastId,
                   (HI_U32)Aop,
                   (HI_CHAR*)((SND_CAST_STATUS_START == pCast->enCurnStatus) ? "start" : ((SND_CAST_STATUS_STOP == pCast->enCurnStatus) ? "stop" : "pause")),
                   (HI_CHAR*)((pCast->bUserEnableSetting == HI_TRUE) ? "On" : "Off"),
                   pCast->stCastAbsGain.s32GainL,
                   pCast->stCastAbsGain.s32GainR,
                   (HI_TRUE == pCast->stCastAbsGain.bLinearMode) ? "" : "dB",
                   (HI_FALSE == pCast->bMute) ? "off" : "on"
                  );
        if (pCard->bCastSimulateOp == HI_TRUE)
        {
            PROC_PRINT(p,
                       ", *CastSimulatedOp(%s)\n",
                       AUTIL_Port2Name(pCard->enCastSimulatePort)
                      );
        }
        else
        {
            PROC_PRINT(p, "\n");
        }
        PROC_PRINT(p,
                   "         SampleRate(%.6d), Channel(%.2d), BitWidth(%2d)\n",
                   pCast->u32SampleRate,
                   pCast->u32Channels,
                   pCast->s32BitPerSample
                  );
        PROC_PRINT(p,
                   "         MaxFrameNum(%.2d), SamplePerFrame(%.5d), AcquireFrame(%s)\n",
                   pCast->stUserCastAttr.u32PcmFrameMaxNum,  //verify
                   pCast->stUserCastAttr.u32PcmSamplesPerFrame,  //verify
                   (HI_CHAR*)((pCast->bAcquireCastFrameFlag == HI_TRUE) ? "On" : "Off")
                  );
    }
}
#endif

HI_S32 CAST_GetDefAttr(HI_UNF_SND_CAST_ATTR_S* pstAttr)
{
    pstAttr->bAddMute = HI_TRUE;
    pstAttr->u32PcmFrameMaxNum = AO_CAST_DEFATTR_FRAMEMAXNUM;
    pstAttr->u32PcmSamplesPerFrame = AO_CAST_DEFATTR_SAMPLESPERFRAME;
    return HI_SUCCESS;
}

HI_S32 CAST_CreateChn(SND_CARD_STATE_S* pCard, HI_UNF_SND_CAST_ATTR_S* pstCastAttr, MMZ_BUFFER_S* pstMMz, HI_HANDLE hCast)
{
    HI_U32 CastID = AO_MAX_CAST_NUM;
    HI_S32 s32Ret = HI_FAILURE;
    SND_CAST_STATE_S* pCast = HI_NULL;

    pCast = (SND_CAST_STATE_S*)HI_KMALLOC(HI_ID_AO, sizeof(SND_CAST_STATE_S), GFP_KERNEL);
    if (HI_NULL == pCast)
    {
        HI_FATAL_AO("malloc SND_CAST_STATE_S failed\n");
        return HI_FAILURE;
    }

    memset(pCast, 0, sizeof(SND_CAST_STATE_S));

    memcpy(&pCast->stUserCastAttr, pstCastAttr, sizeof(HI_UNF_SND_CAST_ATTR_S));

    s32Ret = SND_CreateCastOp(pCard, &CastID, pstCastAttr, pstMMz);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SND_CreateCastOp failed(0x%x)\n", s32Ret);
        HI_KFREE(HI_ID_AO, pCast);
        return s32Ret;
    }

    pCast->tPhyAddr = pstMMz->u32StartPhyAddr;
    pCast->tKernelVirtAddr = pstMMz->pu8StartVirAddr - (HI_U8*)HI_NULL;
    pCast->hCast  = hCast;
    pCast->CastId = CastID;

    pCast->u32Channels = 2;
    pCast->u32SampleRate = 48000;
    pCast->s32BitPerSample = 16;

    pCast->u32SampleBytes = AUTIL_CalcFrameSize(pCast->u32Channels , (HI_U32)pCast->s32BitPerSample);
    pCast->u32FrameBytes = pstCastAttr->u32PcmSamplesPerFrame *  pCast->u32SampleBytes;
    pCast->u32FrameSamples = pstCastAttr->u32PcmSamplesPerFrame;
    pCast->bAddMute = pstCastAttr->bAddMute;

    pCast->bUserEnableSetting = HI_FALSE;
    pCast->enCurnStatus = SND_CAST_STATUS_STOP;
    pCast->bAcquireCastFrameFlag = HI_FALSE;
    pCast->stCastAbsGain.bLinearMode = HI_TRUE;
    pCast->stCastAbsGain.s32GainL = AO_MAX_LINEARVOLUME;
    pCast->stCastAbsGain.s32GainR = AO_MAX_LINEARVOLUME;
    pCast->bMute = HI_FALSE;

    pCard->pCast[CastID] = (HI_VOID*)pCast;
    pCard->uSndCastInitFlag |= ((HI_U32)1L << CastID);

    return HI_SUCCESS;
}

HI_S32 CAST_DestroyChn(SND_CARD_STATE_S* pCard, HI_U32 u32CastID)
{
    SND_CAST_STATE_S* pCast = HI_NULL;

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    if (SND_CAST_STATUS_STOP != pCast->enCurnStatus)
    {
        CASTSetEnable(pCard, pCast, HI_FALSE);
    }

    SND_DestoryCastOp(pCard, u32CastID);

    pCard->uSndCastInitFlag &= ~((HI_U32)1L << u32CastID);
    pCard->pCast[u32CastID] = HI_NULL;

    AUTIL_AO_FREE(HI_ID_AO, pCast);
    return HI_SUCCESS;
}

HI_S32 CAST_SetInfo(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, HI_VIRT_ADDR_T tUserVirtAddr)
{
    SND_CAST_STATE_S* pCast;

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    pCast->tUserVirtAddr = tUserVirtAddr;

    return HI_SUCCESS;
}

HI_S32 CAST_GetInfo(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, AO_Cast_Info_Param_S* pstInfo)
{
    SND_CAST_STATE_S* pCast;

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    pstInfo->tUserVirtAddr = pCast->tUserVirtAddr;
    pstInfo->tKernelVirtAddr = pCast->tKernelVirtAddr;
    pstInfo->tPhyAddr = pCast->tPhyAddr;
    pstInfo->u32FrameBytes = pCast->u32FrameBytes;
    pstInfo->u32FrameSamples = pCast->u32FrameSamples;

    pstInfo->u32Channels = pCast->u32Channels;
    pstInfo->s32BitPerSample = pCast->s32BitPerSample;

    return HI_SUCCESS;
}

HI_VOID CAST_GetSettings(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, SND_CAST_SETTINGS_S* pstCastSettings)
{
    SND_CAST_STATE_S* pCast;

    if (AO_MAX_CAST_NUM <= u32CastID)
    {
        HI_ERR_AO("Invalid Cast ID(0x%x)\n", u32CastID);
        return;
    }

    pCast = (SND_CAST_STATE_S*)pCard->pCast[u32CastID];
    if (HI_NULL == pCast)
    {
        HI_ERR_AO("Cast State is NULL (u32CastID = 0x%x)\n", u32CastID);
        return;
    }

    pstCastSettings->bMute = pCast->bMute;
    memcpy(&pstCastSettings->stCastAbsGain, &pCast->stCastAbsGain, sizeof(HI_UNF_SND_ABSGAIN_ATTR_S));
    pstCastSettings->tUserVirtAddr = pCast->tUserVirtAddr;
    pstCastSettings->bUserEnableSetting = pCast->bUserEnableSetting;
}

HI_VOID CAST_RestoreSettings(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, SND_CAST_SETTINGS_S* pstCastSettings)
{
    SND_CAST_STATE_S* pCast;

    if (AO_MAX_CAST_NUM <= u32CastID)
    {
        HI_ERR_AO("Invalid Cast ID(0x%x)\n", u32CastID);
        return;
    }

    pCast = (SND_CAST_STATE_S*)pCard->pCast[u32CastID];
    if (HI_NULL == pCast)
    {
        HI_ERR_AO("Cast State is NULL (u32CastID = 0x%x)\n", u32CastID);
        return;
    }

    pCast->tUserVirtAddr = pstCastSettings->tUserVirtAddr;

    /* fource discard ReleaseCastFrame after resume */
    pCast->bAcquireCastFrameFlag = HI_FALSE;
    if (pstCastSettings->bUserEnableSetting != pCast->bUserEnableSetting)
    {
        CAST_SetEnable(pCard, u32CastID, pstCastSettings->bUserEnableSetting);
        CAST_SetAbsGain(pCard, u32CastID, &pstCastSettings->stCastAbsGain);
        CAST_SetMute(pCard, u32CastID, pstCastSettings->bMute);
    }
}

HI_S32 CAST_SetEnable(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, HI_BOOL bEnable)
{
    SND_CAST_STATE_S* pCast;

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    pCast->bUserEnableSetting = bEnable;

    return CASTSetEnable(pCard, pCast, bEnable);
}

HI_S32 CAST_GetEnable(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, HI_BOOL* pbEnable)
{
    SND_CAST_STATE_S* pCast;

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    *pbEnable = pCast->bUserEnableSetting;
    return HI_SUCCESS;
}

HI_S32 CAST_ReadData(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, AO_Cast_Data_Param_S* pstCastData)
{
    SND_CAST_STATE_S* pCast;

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    pstCastData->stAOFrame.u32PcmSamplesPerFrame = 0;

    if (HI_FALSE == pCast->bUserEnableSetting)
    {
        return HI_FAILURE;
    }

    if (SND_CAST_STATUS_STOP == pCast->enCurnStatus)
    {
        HI_S32 s32Ret;

        HI_WARN_AO("Cast is stop, try to enable cast(u32CastID = 0x%x)\n", u32CastID);
        s32Ret = CASTSetEnable(pCard, pCast, HI_TRUE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("call CASTSetEnable failed\n");
            return s32Ret;
        }
    }

    if (SND_CAST_STATUS_STOP == pCast->enCurnStatus)
    {
        return HI_SUCCESS;
    }

    pstCastData->u32FrameBytes = pCast->u32FrameBytes;
    pstCastData->u32SampleBytes = pCast->u32SampleBytes;

    pstCastData->stAOFrame.s32BitPerSample = pCast->s32BitPerSample;
    pstCastData->stAOFrame.u32Channels = pCast->u32Channels;
    pstCastData->stAOFrame.u32SampleRate = pCast->u32SampleRate;
    pstCastData->stAOFrame.u32PcmSamplesPerFrame = pCast->stUserCastAttr.u32PcmSamplesPerFrame;
    pstCastData->stAOFrame.bInterleaved = HI_TRUE;

    if (0 == SND_ReadCastData(pCard, pCast->CastId, pstCastData))
    {
        pstCastData->stAOFrame.u32PcmSamplesPerFrame = 0;
        return HI_SUCCESS;
    }

    pCast->bAcquireCastFrameFlag = HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 CAST_ReleaseData(SND_CARD_STATE_S* pCard, HI_U32 u32CastID, AO_Cast_Data_Param_S* pstCastData)
{
    SND_CAST_STATE_S* pCast;

    CAST_FIND_BY_ID(pCard, u32CastID, pCast);

    /* discard ReleaseCastFrame before call AcquireCastFrame */
    if (HI_FALSE == pCast->bAcquireCastFrameFlag)
    {
        return HI_SUCCESS;
    }

    pstCastData->u32FrameBytes  = pCast->u32FrameBytes;
    pstCastData->u32SampleBytes = pCast->u32SampleBytes;

    if (0 == SND_ReleaseCastData(pCard, pCast->CastId, pstCastData))
    {
        return HI_FAILURE;
    }

    pCast->bAcquireCastFrameFlag = HI_FALSE;

    return HI_SUCCESS;
}

