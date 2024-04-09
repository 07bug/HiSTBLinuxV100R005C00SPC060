#include <linux/list.h>


//#include "hi_unf_audio.h"

#include "hal_aoe.h"
#include "drv_ao_track.h"
#include "drv_ao_engine.h"
#include "drv_ao_op.h"
#include "hi_aiao_log.h"

static HI_VOID ENGINEAttachOp(SND_CARD_STATE_S* pCard, SND_ENGINE_STATE_S* state)
{
    HI_U32 u32OpNum;

    for (u32OpNum = 0; u32OpNum < HI_UNF_SND_OUTPUTPORT_MAX; u32OpNum++)
    {
        HI_VOID* pSndOp = pCard->pSndOp[u32OpNum];
        if (HI_NULL == pSndOp)
        {
            continue;
        }

        if (state->enEngineType == SND_GetOpGetOutType(pSndOp))
        {
            AOE_AOP_ID_E enAOP = SND_GetOpAopId(pSndOp);
            HAL_AOE_ENGINE_AttachAop(state->enEngine, enAOP);
        }
    }
}

static HI_VOID ENGINEGetCreateAttr(SND_CARD_STATE_S* pCard, SND_ENGINE_TYPE_E enEngineType, AOE_ENGINE_CHN_ATTR_S* pstEngineAttr)
{
    memset(pstEngineAttr, 0, sizeof(AOE_ENGINE_CHN_ATTR_S));

    switch (enEngineType)
    {
        case SND_ENGINE_TYPE_PCM:
        {
            pstEngineAttr->u32BitPerSample = AO_TRACK_BITDEPTH_LOW;
            pstEngineAttr->u32Channels = AO_TRACK_NORMAL_CHANNELNUM;
            /* pcm engine must follows SND's samplerate */
            pstEngineAttr->u32SampleRate = pCard->enUserSampleRate;
            pstEngineAttr->u32DataFormat = 0;
            break;
        }

        case SND_ENGINE_TYPE_SPDIF_RAW:
        {
            pstEngineAttr->u32BitPerSample = AO_TRACK_BITDEPTH_LOW;
            pstEngineAttr->u32Channels = AO_TRACK_NORMAL_CHANNELNUM;
            pstEngineAttr->u32SampleRate = HI_UNF_SAMPLE_RATE_48K;
            pstEngineAttr->u32DataFormat = 1;
            break;
        }

        case SND_ENGINE_TYPE_HDMI_RAW:
        {
            pstEngineAttr->u32BitPerSample = AO_TRACK_BITDEPTH_LOW;
            pstEngineAttr->u32Channels = AO_TRACK_MUTILPCM_CHANNELNUM;
            pstEngineAttr->u32SampleRate = HI_UNF_SAMPLE_RATE_192K;
            pstEngineAttr->u32DataFormat = 1;
            break;
        }

        default:
        {
            HI_LOG_ERR("Invalid engine type\n");
            break;
        }
    }
}

static HI_VOID ENGINESetAttr(SND_CARD_STATE_S* pCard, AOE_ENGINE_ID_E enEngine)
{
#ifdef __DPT__
    HI_U32  u32AefId;
    HI_BOOL bMcProcess = HI_FALSE;   //The flag of whether to do mc process

    for (u32AefId = 0; u32AefId < AOE_AEF_MAX_CHAN_NUM; u32AefId++)
    {
        if (pCard->u32AttAef & ((HI_U32)1L << u32AefId))
        {
            HAL_AOE_ENGINE_AttachAef(enEngine, u32AefId);
        }
    }

    for (u32AefId = 0; u32AefId < AOE_AEF_MAX_CHAN_NUM; u32AefId++)
    {
        if (pCard->u32AttAef & ((HI_U32)1L << u32AefId))
        {
            bMcProcess = (pCard->u32AefMcSupported & (1 << u32AefId)) ? HI_TRUE : HI_FALSE;
            break;
        }
    }
    HAL_AOE_ENGINE_SetAefAttr(enEngine, bMcProcess, pCard->u32AefFrameDelay);
    HAL_AOE_ENGINE_SetGeqAttr(enEngine, &pCard->stGeqAttr);
    HAL_AOE_ENGINE_SetGeqEnable(enEngine, pCard->bGeqEnable);
#endif

    HAL_AOE_ENGINE_SetAvcAttr(enEngine, &pCard->stAvcAttr);
    HAL_AOE_ENGINE_SetAvcEnable(enEngine, pCard->bAvcEnable);

    HAL_AOE_ENGINE_SetConOutputEnable(enEngine, pCard->bConOutputEnable);
    HAL_AOE_ENGINE_SetOutputAtmosEnable(enEngine, pCard->bOutputAtmosEnable);
}

#if 0
static HI_S32 ENGINEStart(SND_CARD_STATE_S* pCard)
{
    HI_U32 u32Startmask = 0;
    SND_ENGINE_STATE_S* pEngine = pCard->pSndEngine[SND_ENGINE_TYPE_PCM];

    u32Startmask |= (HI_U32)(1 << pEngine->enEngine);

    if (SND_MODE_NONE != pCard->enSpdifPassthrough)
    {
        pEngine = pCard->pSndEngine[SND_ENGINE_TYPE_SPDIF_RAW];
        u32Startmask |= (HI_U32)(1 << pEngine->enEngine);
    }

    if (SND_MODE_NONE != pCard->enHdmiPassthrough)
    {
        pEngine = pCard->pSndEngine[SND_ENGINE_TYPE_HDMI_RAW];
        u32Startmask |= (HI_U32)(1 << pEngine->enEngine);
    }

    return HAL_AOE_ENGINE_Group_Start(u32Startmask);
}
#endif

static HI_S32 ENGINECreateByType(SND_CARD_STATE_S* pCard, SND_ENGINE_TYPE_E enEngineType)
{
    HI_S32 s32Ret;
    SND_ENGINE_STATE_S* pEngine = HI_NULL;

    pEngine = (SND_ENGINE_STATE_S*)HI_KMALLOC(HI_ID_AO, sizeof(SND_ENGINE_STATE_S), GFP_KERNEL);
    if (HI_NULL == pEngine)
    {
        HI_LOG_ERR("malloc SND_ENGINE_STATE_S failed\n");
        return HI_FAILURE;
    }

    memset(pEngine, 0, sizeof(SND_ENGINE_STATE_S));
    ENGINEGetCreateAttr(pCard, enEngineType, &pEngine->stUserEngineAttr);
    s32Ret = HAL_AOE_ENGINE_Create(&pEngine->enEngine, &pEngine->stUserEngineAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PrintCallFunErr(HAL_AOE_ENGINE_Create, s32Ret);
        HI_KFREE(HI_ID_AO, pEngine);
        return s32Ret;
    }

    pEngine->enEngineType = enEngineType;
    ENGINESetAttr(pCard, pEngine->enEngine);

    HI_LOG_DBG("malloc engine node\n");
    HI_DBG_PrintVoid(pEngine);
    HI_DBG_PrintU32(enEngineType);

    pCard->pSndEngine[enEngineType] = (HI_VOID*)pEngine;

    HAL_AOE_ENGINE_Start(pEngine->enEngine);
    ENGINEAttachOp(pCard, pEngine);

    return s32Ret;
}

HI_VOID AO_ENGINE_DeInit(SND_CARD_STATE_S* pCard)
{
    SND_ENGINE_TYPE_E enType;
    SND_ENGINE_STATE_S* pEngine;

    for (enType = SND_ENGINE_TYPE_PCM; enType < SND_ENGINE_TYPE_BUTT; enType++)
    {
        pEngine = (SND_ENGINE_STATE_S*)pCard->pSndEngine[enType];
        if (HI_NULL == pEngine)
        {
            continue;
        }

        HAL_AOE_ENGINE_Stop(pEngine->enEngine);
        HAL_AOE_ENGINE_Destroy(pEngine->enEngine);
        HI_KFREE(HI_ID_AO, pEngine);

        pCard->pSndEngine[enType] = HI_NULL;
    }

    HI_LOG_INFO("Destory pcm engine and raw engine.\n");
}

HI_S32 AO_ENGINE_Init(SND_CARD_STATE_S* pCard)
{
    HI_S32 s32Ret = HI_SUCCESS;

    /* always create pcm engine */
    s32Ret = ENGINECreateByType(pCard, SND_ENGINE_TYPE_PCM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PrintCallFunErr(ENGINECreateByType, s32Ret);
        return s32Ret;
    }

    if (SND_MODE_NONE != pCard->enSpdifPassthrough)
    {
        s32Ret = ENGINECreateByType(pCard, SND_ENGINE_TYPE_SPDIF_RAW);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PrintCallFunErr(ENGINECreateByType, s32Ret);
            goto ERR_EXIT;
        }
    }

    if (SND_MODE_NONE != pCard->enHdmiPassthrough)
    {
        s32Ret = ENGINECreateByType(pCard, SND_ENGINE_TYPE_HDMI_RAW);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PrintCallFunErr(ENGINECreateByType, s32Ret);
            goto ERR_EXIT;
        }
    }


#ifdef __DPT__
    if (SND_MODE_NONE != pCard->enArcPassthrough)
    {
        s32Ret = ENGINECreateByType(pCard, SND_ENGINE_TYPE_ARC_RAW);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PrintCallFunErr(ENGINECreateByType, s32Ret);
            goto ERR_EXIT;
        }
    }
#endif
    HI_LOG_INFO("Create pcm engine and raw engine success.\n");

    return s32Ret;

ERR_EXIT:
    AO_ENGINE_DeInit(pCard);
    return s32Ret;
}

/* AO Engine PM */
HI_S32 AO_ENGINE_Suspend(SND_CARD_STATE_S* pCard)
{
    SND_ENGINE_TYPE_E enType;
    SND_ENGINE_STATE_S* pEngine;

    for (enType = SND_ENGINE_TYPE_PCM; enType < SND_ENGINE_TYPE_BUTT; enType++)
    {
        pEngine = (SND_ENGINE_STATE_S*)pCard->pSndEngine[enType];
        if (HI_NULL == pEngine)
        {
            continue;
        }

        HAL_AOE_ENGINE_Stop(pEngine->enEngine);
        HAL_AOE_ENGINE_Destroy(pEngine->enEngine);
    }

    return HI_SUCCESS;
}

HI_S32 AO_ENGINE_Resume(SND_CARD_STATE_S* pCard)
{
    HI_S32 s32Ret;
    SND_ENGINE_TYPE_E enType;
    SND_ENGINE_STATE_S* pEngine;

    for (enType = SND_ENGINE_TYPE_PCM; enType < SND_ENGINE_TYPE_BUTT; enType++)
    {
        pEngine = (SND_ENGINE_STATE_S*)pCard->pSndEngine[enType];
        if (HI_NULL == pEngine)
        {
            continue;
        }

        s32Ret = HAL_AOE_ENGINE_Create(&pEngine->enEngine, &pEngine->stUserEngineAttr);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PrintCallFunErr(HAL_AOE_ENGINE_Create, s32Ret);
            return s32Ret;
        }

        ENGINESetAttr(pCard, pEngine->enEngine);

        HAL_AOE_ENGINE_Start(pEngine->enEngine);
        ENGINEAttachOp(pCard, pEngine);
    }

    return HI_SUCCESS;
}

