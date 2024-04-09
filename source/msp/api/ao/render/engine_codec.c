/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: engine_codec.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <dlfcn.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"

#include "render_common.h"
#include "engine_codec.h"
#include "engine_codec_private.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


#define HA_DECODEC_ENTRY       "ha_audio_decode_entry"
#define HA_DOLBY_MS12_LIB_NAME "libHA.AUDIO.DOLBYMS12.decode.so"


static HI_S32 HACodecCheckEntry(const HI_HA_DECODE_S* pEntry)
{
    CHECK_AO_NULL_PTR(pEntry->DecInit);
    CHECK_AO_NULL_PTR(pEntry->DecDeInit);
    CHECK_AO_NULL_PTR(pEntry->DecSetConfig);
    CHECK_AO_NULL_PTR(pEntry->DecGetMaxPcmOutSize);
    CHECK_AO_NULL_PTR(pEntry->DecGetMaxBitsOutSize);

    return  HI_SUCCESS;
}

static HI_S32 HADecLoadLib(ENGINE_CODEC_S* pstCodec)
{
    HI_S32 s32Ret;
    HI_VOID* pDllModule;
    HI_HA_DECODE_S* pEntry;

#ifdef ANDROID
    pDllModule = dlopen(HA_DOLBY_MS12_LIB_NAME, RTLD_LAZY | RTLD_GLOBAL);
#else
    pDllModule = dlopen(HA_DOLBY_MS12_LIB_NAME, RTLD_LAZY | RTLD_GLOBAL | RTLD_DEEPBIND);
#endif
    if (HI_NULL == pDllModule)
    {
        HI_ERR_AO("dlopen %s failed(%s)\n", HA_DOLBY_MS12_LIB_NAME, dlerror());
        return HI_FAILURE;
    }

    pEntry = (HI_HA_DECODE_S*)dlsym(pDllModule, HA_DECODEC_ENTRY);
    if (HI_NULL == pEntry)
    {
        HI_ERR_AO("dlsym %s failed(%s)\n", HA_DOLBY_MS12_LIB_NAME, dlerror());
        goto ERR_DLOPEN;
    }

    s32Ret = HACodecCheckEntry(pEntry);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HACodecCheckEntry failed(0x%x)\n", s32Ret);
        goto ERR_DLOPEN;
    }

    pstCodec->pEntry = pEntry;
    pstCodec->pDllModule = pDllModule;

    return HI_SUCCESS;

ERR_DLOPEN:
    (HI_VOID)dlclose(pDllModule);

    return HI_FAILURE;
}

static HI_VOID HADecUnLoadLib(ENGINE_CODEC_S* pstCodec)
{
    (HI_VOID)dlclose(pstCodec->pDllModule);
}

static HI_BOOL HACodecCheckIsRenderLibInited(ENGINE_CODEC_S* pstCodec)
{
    return pstCodec->bLibInited;
}

static HI_S32 HaCodecRegistProc(ENGINE_CODEC_S* pstCodec)
{
    pstCodec->pstMs12Proc->enCmd = HA_CODEC_MS12_SET_PROCINFO_CMD;

    return pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pstCodec->pstMs12Proc);
}

static HI_S32 HACodecInit_Default(ENGINE_CODEC_S* pstCodec)
{
    HI_S32 s32Ret;
    HI_HADECODE_OPENPARAM_S stOpenParam;

    HA_DOLBYMS12_CodecGetDefaultOpenConfig(&pstCodec->stMs12Cfg);
    HA_DOLBYMS12_CodecGetDefaultOpenParam(&stOpenParam, &pstCodec->stMs12Cfg);

    s32Ret = pstCodec->pEntry->DecInit(&pstCodec->hDecoder, &stOpenParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DecInit failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    pstCodec->enCodecID = HA_AUDIO_ID_MS12_DDP;

    return HI_SUCCESS;
}

static HI_S32 HACodecDeInit(ENGINE_CODEC_S* pstCodec)
{
    HI_S32 s32Ret;

    s32Ret = pstCodec->pEntry->DecDeInit(pstCodec->hDecoder);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DecDeInit failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_S32 HACodecCtlCommand(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_VOID* pCmdData)
{
    HI_S32 s32Ret;
    HA_MS12_SET_STREAM_INDEX_S stStreamIndex;

    HACODEC_INST_LOCK();

    if (HI_FALSE == HACodecCheckIsRenderLibInited(pstCodec))
    {
        HI_ERR_AO("HACodecCtlCommand render lib is not inited\n");
        HACODEC_INST_UNLOCK();
        return HI_ERR_AO_INVALID_PARA;
    }

    stStreamIndex.enCmd = HA_CODEC_MS12_SET_STREAM_INDEX_CMD;
    stStreamIndex.u32Index = enSourceID;

    (HI_VOID)pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, &stStreamIndex);

    s32Ret = pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pCmdData);

    HACODEC_INST_UNLOCK();

    return s32Ret;
}

static HI_S32 HACodecSetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData)
{
    HI_S32 s32Ret;

    HACODEC_INST_LOCK();

    if (HI_FALSE == HACodecCheckIsRenderLibInited(pstCodec))
    {
        HI_ERR_PrintInfo("render lib is not inited");
        HACODEC_INST_UNLOCK();
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pCmdData);

    HACODEC_INST_UNLOCK();

    return s32Ret;
}

static HI_S32 HACodecGetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData)
{
    HI_S32 s32Ret;

    HACODEC_INST_LOCK();

    if (HI_FALSE == HACodecCheckIsRenderLibInited(pstCodec))
    {
        HI_ERR_PrintInfo("render lib is not inited");
        HACODEC_INST_UNLOCK();
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pCmdData);

    HACODEC_INST_UNLOCK();

    return s32Ret;
}

static HI_BOOL HACodecCheckIsSameConfig(ENGINE_CODEC_S* pstCodec, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    DOLBYMS12_CODEC_OPENCONFIG_S* pstLoadCfg = (DOLBYMS12_CODEC_OPENCONFIG_S*)pstRenderAttr->stDecodeParam.pCodecPrivateData;
    if (0 == memcmp(&pstCodec->stMs12Cfg, pstLoadCfg, sizeof(DOLBYMS12_CODEC_OPENCONFIG_S)))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_S32 HACodecChangeDecodeConfig(ENGINE_CODEC_S* pstCodec, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    DOLBYMS12_CODEC_OPENCONFIG_S* pstLoadCfg = (DOLBYMS12_CODEC_OPENCONFIG_S*)pstRenderAttr->stDecodeParam.pCodecPrivateData;

    if (pstCodec->stMs12Cfg.enInputType != pstLoadCfg->enInputType)
    {
        HA_MS12_SET_INPUTTYPE_S stType;
        stType.enCmd = HA_CODEC_MS12_SET_INPUTTYPE_CMD;
        stType.enInputType = pstLoadCfg->enInputType;
        s32Ret  = pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, &stType);
        HI_WARN_PrintH32(s32Ret);
    }

    if (pstCodec->stMs12Cfg.enDrcMode != pstLoadCfg->enDrcMode)
    {
        HA_MS12_SET_DRC_MODE_S stMode;
        stMode.enCmd = HA_CODEC_MS12_SET_DRC_MODE_CMD;
        stMode.enDrcMode = pstLoadCfg->enDrcMode;
        s32Ret |= pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, &stMode);
        HI_WARN_PrintH32(s32Ret);
    }

    if (pstCodec->stMs12Cfg.enDmxMode != pstLoadCfg->enDmxMode)
    {
        HA_MS12_SET_DMX_MODE_S stMode;
        stMode.enCmd = HA_CODEC_MS12_SET_DMX_MODE_CMD;
        stMode.enDmxMode = pstLoadCfg->enDmxMode;
        s32Ret |= pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, &stMode);
        HI_WARN_PrintH32(s32Ret);
    }

    if ((pstCodec->stMs12Cfg.u32DrcCut != pstLoadCfg->u32DrcCut) ||
        (pstCodec->stMs12Cfg.u32DrcBoost != pstLoadCfg->u32DrcBoost))
    {
        HA_MS12_SET_DYNSCALE_MODE_S stMode;
        stMode.enCmd = HA_CODEC_MS12_SET_DRC_SCALE_CMD;
        stMode.u32DrcCut = pstLoadCfg->u32DrcCut;
        stMode.u32DrcBoost = pstLoadCfg->u32DrcBoost;
        s32Ret |= pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, &stMode);
        HI_WARN_PrintH32(s32Ret);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintErrCode(s32Ret);
        return s32Ret;
    }

    memcpy(&pstCodec->stMs12Cfg, pstLoadCfg, sizeof(DOLBYMS12_CODEC_OPENCONFIG_S));

    return HI_SUCCESS;
}

HI_BOOL HACodec_CheckIsRenderLibLoaded(ENGINE_CODEC_S* pstCodec)
{
    return HACodecCheckIsRenderLibInited(pstCodec);
}

HI_S32 HACodec_Init(ENGINE_CODEC_S** ppstCodec)
{
    ENGINE_CODEC_S* pstCodec;

    pstCodec = (ENGINE_CODEC_S*)malloc(sizeof(ENGINE_CODEC_S));
    if (HI_NULL == pstCodec)
    {
        HI_ERR_PrintInfo("HACodec malloc failed!\n");
        return HI_FAILURE;
    }
    memset(pstCodec, 0, sizeof(ENGINE_CODEC_S));

    pstCodec->pstMs12Proc = (HA_MS12_SET_PROCINFO_S*)malloc(sizeof(HA_MS12_SET_PROCINFO_S));
    if (HI_NULL == pstCodec->pstMs12Proc)
    {
        HI_ERR_PrintInfo("HAMs12Proc malloc failed!\n");
        free(pstCodec);
        return HI_FAILURE;
    }
    memset(pstCodec->pstMs12Proc, 0, sizeof(HA_MS12_SET_PROCINFO_S));

    //pstCodec->pstMs12Proc->stProc.u32DebugLevel = 2;

    *ppstCodec = pstCodec;

    return HI_SUCCESS;
}

HI_VOID HACodec_DeInit(ENGINE_CODEC_S* pstCodec)
{
    if (HI_NULL != pstCodec)
    {
        if (HI_NULL != pstCodec->pstMs12Proc)
        {
            free(pstCodec->pstMs12Proc);
        }
        free(pstCodec);
    }
}

HI_S32 HACodec_LoadRenderLib_Default(ENGINE_CODEC_S* pstCodec)
{
    HI_S32 s32Ret;

    if (HI_TRUE == pstCodec->bLibInited)
    {
        HI_WARN_AO("Render lib already load\n");
        return HI_SUCCESS;
    }

    s32Ret = HADecLoadLib(pstCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HADecLoadLib failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HACodecInit_Default(pstCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HADecInit failed(0x%x)\n", s32Ret);
        HADecUnLoadLib(pstCodec);
        return s32Ret;
    }

    s32Ret = HaCodecRegistProc(pstCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HaCodecRegistProc default failed(0x%x)\n", s32Ret);
        HACodecDeInit(pstCodec);
        HADecUnLoadLib(pstCodec);
        return s32Ret;
    }

    pstCodec->bLibInited = HI_TRUE;

    return HI_SUCCESS;
}

HI_VOID HACodec_UnLoadRenderLib(ENGINE_CODEC_S* pstCodec)
{
    if (HI_TRUE == pstCodec->bLibInited)
    {
        HACodecDeInit(pstCodec);
        HADecUnLoadLib(pstCodec);
    }

    pstCodec->pEntry = HI_NULL;
    pstCodec->pDllModule = HI_NULL;
    pstCodec->bLibInited = HI_FALSE;
}

HI_S32 HACodec_InitDecodeInfo(ENGINE_CODEC_S* pstCodec, HA_MS12_DECODE_STREAM_S* pstDecodeStream)
{
    HI_S32 s32Ret;
    HI_U32 u32Index = 0;
    HI_U32 u32TotalSize = 0;
    HI_U32 u32InpkgSize = 0;
    HI_U32 u32OutputSize = 0;
    HI_U32 u32RsrcSize = 0;

    HI_U32 u32MallocPcmSize = 0;
    HI_U32 u32MallocBitSize = 0;
    HI_U8* pu8Memory = HI_NULL;

    CHECK_AO_NULL_PTR(pstDecodeStream);

    u32InpkgSize = sizeof(HI_HADECODE_INPACKET_S);
    u32OutputSize = sizeof(HI_HADECODE_OUTPUT_S);

    s32Ret = pstCodec->pEntry->DecGetMaxPcmOutSize(pstCodec->hDecoder, &u32MallocPcmSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Hacoder DecGetMaxPcmOutSize failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = pstCodec->pEntry->DecGetMaxBitsOutSize(pstCodec->hDecoder, &u32MallocBitSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Hacoder DecGetMaxBitsOutSize failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    u32RsrcSize = (200 * 48000 * 2 * 8 / 1000);   //max 8ch 16bit 200ms

    u32TotalSize = u32InpkgSize * SOURCE_ID_BUTT + u32OutputSize + u32MallocPcmSize + u32MallocBitSize
                   + u32RsrcSize * 2;

    pstCodec->pAdecIOMem = (HI_VOID*)malloc(u32TotalSize);
    if (HI_NULL == pstCodec->pAdecIOMem)
    {
        HI_ERR_AO("Malloc pAdecIOMem failed\n");
        return HI_FAILURE;
    }

    memset(pstCodec->pAdecIOMem, 0, u32TotalSize);
    pu8Memory = pstCodec->pAdecIOMem;

    memset(pstDecodeStream, 0, sizeof(HA_MS12_DECODE_STREAM_S));

    for (u32Index = 0; u32Index < SOURCE_ID_BUTT; u32Index++)
    {
        pstDecodeStream->stStream.stInput.pstInPack[u32Index] = (HI_HADECODE_INPACKET_S*)pu8Memory;
        pu8Memory += u32InpkgSize;
    }

    for (u32Index = 0; u32Index < 2; u32Index++)
    {
        pstDecodeStream->stStream.stInput.acUnifyWorkBuf[u32Index] = (HI_CHAR*)pu8Memory;
        pu8Memory += u32RsrcSize;
    }

    pstDecodeStream->stStream.stInput.bPassthruBypass = HI_FALSE;

    pstDecodeStream->stStream.stOutput.pstOutput = (HI_HADECODE_OUTPUT_S*)pu8Memory;
    pu8Memory += u32OutputSize;

    pstDecodeStream->stStream.stOutput.pstOutput->ps32PcmOutBuf = (HI_S32*)pu8Memory;
    pu8Memory += u32MallocPcmSize;

    pstDecodeStream->stStream.stOutput.pstOutput->ps32BitsOutBuf = (HI_S32*)pu8Memory;

    return HI_SUCCESS;
}

HI_VOID HACodec_DeInitDecodeInfo(ENGINE_CODEC_S* pstCodec)
{
    if (HI_NULL != pstCodec->pAdecIOMem)
    {
        free(pstCodec->pAdecIOMem);
        pstCodec->pAdecIOMem = HI_NULL;
    }
}

HI_S32 HACodec_SetRenderAttr(ENGINE_CODEC_S* pstCodec, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    MS12_INPUT_TYPE_E enInputType;
    HA_MS12_SET_INPUTTYPE_S stType;

    switch (pstRenderAttr->enType)
    {
        case HA_AUDIO_ID_MS12_AAC:
        case HA_AUDIO_ID_MS12_DDP:
            if (HI_TRUE == HACodecCheckIsSameConfig(pstCodec, pstRenderAttr))
            {
                HI_WARN_AO("The same codec type(0x%x) and config\n", pstRenderAttr->enType);
                return HI_SUCCESS;
            }

            s32Ret = HACodecChangeDecodeConfig(pstCodec, pstRenderAttr);
            if (HI_SUCCESS != s32Ret)
            {
                HI_LOG_PrintFuncErr(HACodecChangeDecodeConfig, s32Ret);
            }
            return s32Ret;
        case HA_AUDIO_ID_MP2:
        case HA_AUDIO_ID_MP3:
            enInputType = MS12_MPEG;
            break;
        case HA_AUDIO_ID_AAC:
            enInputType = MS12_HEAAC;
            break;
        case HA_AUDIO_ID_DOLBY_PLUS:
            enInputType = MS12_DOLBY_DIGITAL_PLUS;
            break;
        default:
            enInputType = MS12_EXTERNAL_PCM;
            break;
    }

    stType.enCmd = HA_CODEC_MS12_SET_INPUTTYPE_CMD;
    stType.enInputType = enInputType;
    s32Ret  = pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, &stType);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DecSetConfig InputType failed(0x%x)\n", s32Ret);
        return s32Ret;
    }
    pstCodec->stMs12Cfg.enInputType = enInputType;

    return s32Ret;
}

HI_S32 HACodec_Render(ENGINE_CODEC_S* pstCodec, HI_VOID* pstConfigStructure)
{
    return pstCodec->pEntry->DecSetConfig(pstCodec->hDecoder, pstConfigStructure);
}

HI_S32 HACodec_CtlCommand(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_VOID* pCmdData)
{
    return HACodecCtlCommand(pstCodec, enSourceID, pCmdData);
}

HI_S32 HACodec_SetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData)
{
    return HACodecSetCmd(pstCodec, pCmdData);
}

HI_S32 HACodec_GetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData)
{
    return HACodecGetCmd(pstCodec, pCmdData);
}

HI_S32 HACodec_EnableDecoder(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_BOOL bEnable)
{
    HA_MS12_DECODE_ENABLE_S stDecodeEnable;

    stDecodeEnable.enCmd = HA_CODEC_MS12_ENABLE_DECODE_CMD;
    stDecodeEnable.bEnable = bEnable;

    SYNC_PRINTF("HADecEnableDecoder bEnableDecoder = %d\n", bEnable);

    return HACodecCtlCommand(pstCodec, enSourceID, &stDecodeEnable);
}

HI_S32 HACodec_EnableMixer(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_BOOL bEnable)
{
    HA_MS12_MIX_ENABLE_S stMixerEnable;

    stMixerEnable.enCmd = HA_CODEC_MS12_ENABLE_MIX_CMD;
    stMixerEnable.bEnable = bEnable;

    SYNC_PRINTF("HADecEnableMixer bEnableMixer = %d\n", bEnable);

    return HACodecCtlCommand(pstCodec, enSourceID, &stMixerEnable);
}

HI_S32 HACodec_DropPts(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_S32 s32DropPts)
{
    HA_MS12_ADJUST_STRATEGY_S stStrategyAdjust;

    stStrategyAdjust.enCmd = HA_CODEC_MS12_ADJUST_STRATEGY_CMD;
    stStrategyAdjust.s32AdjustTime = s32DropPts > 0 ? s32DropPts : 0;

    SYNC_PRINTF("HADecDropPts s32AdjustTime = %d\n", s32DropPts);

    return HACodecCtlCommand(pstCodec, enSourceID, &stStrategyAdjust);
}

HI_S32 HACodec_DropFrame(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_U32 u32FrameCnt)
{
    HA_MS12_DROP_FRAME_S stDropFrame;

    stDropFrame.enCmd = HA_CODEC_MS12_DROP_FRAME_CMD;
    stDropFrame.u32FrameCnt = u32FrameCnt;

    SYNC_PRINTF("HADecDropFrame u32FrameCnt = %d\n", u32FrameCnt);

    return HACodecCtlCommand(pstCodec, enSourceID, &stDropFrame);
}

HI_VOID HACodec_UpdateDataStatus(ENGINE_CODEC_S* pstCodec, HI_BOOL* pbStreamDataEnough)
{
    memcpy(pstCodec->bDataAvailable, pbStreamDataEnough, sizeof(pstCodec->bDataAvailable));
}

HI_S32 HACodec_SoftResetDecoder(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID)
{
    HI_S32 s32Cmd = HA_CODEC_MS12_SOFTRESET_CMD;

    return HACodecCtlCommand(pstCodec, enSourceID, (HI_VOID*)&s32Cmd);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
