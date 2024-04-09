/******************************************************************************

  Copyright (C), 2011-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render_source.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdlib.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"
#include "hi_mpi_ao.h"

#include "ipc_client.h"
#include "ipc_common.h"
#include "render_common.h"
#include "engine_codec_private.h"
#include "HA.AUDIO.DOLBYMS12.decode.h"
#include "HA.AUDIO.DOLBYMS12EXT.decode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


static pthread_mutex_t g_ClientMutex = PTHREAD_MUTEX_INITIALIZER;

static HI_VOID CLIENT_LOCK(HI_VOID)
{
    (void)pthread_mutex_lock(&g_ClientMutex);
}

static HI_VOID CLIENT_UNLOCK(HI_VOID)
{
    (void)pthread_mutex_unlock(&g_ClientMutex);
}

static HI_S32 HALTryCreateSetGetCmd(IPC_CMM* pstCMM)
{
    HI_S32 s32Ret;

    CLIENT_LOCK();

    s32Ret = IPC_Common_TryCreateClient();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("IPC_TryCreateClient failed(0x%x)\n", s32Ret);
        CLIENT_UNLOCK();
        return s32Ret;
    }

    s32Ret = IPC_Common_SetClientCmd(pstCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientSetCmd failed(0x%x)\n", s32Ret);
        goto ERR_CMD;
    }

    memset(pstCMM, 0, sizeof(IPC_CMM));

    s32Ret = IPC_Common_GetClientCmd(pstCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientGetCmd failed(0x%x)\n", s32Ret);
        goto ERR_CMD;
    }

    CLIENT_UNLOCK();
    return HI_SUCCESS;

ERR_CMD:
    IPC_Common_TryDestroyClient();
    CLIENT_UNLOCK();

    return s32Ret;
}

static HI_S32 HALSetGetCmd(IPC_CMM* pstCMM)
{
    HI_S32 s32Ret;

    //HI_WARN_AO("Enter COMM command=0x%x\n", pstCMM->u32Command);

    CLIENT_LOCK();

    s32Ret = IPC_Common_SetClientCmd(pstCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_AO("ClientSetCmd failed(0x%x)\n", s32Ret);
        CLIENT_UNLOCK();
        return s32Ret;
    }

   //HI_WARN_AO("Midle COMM command=0x%x\n", pstCMM->u32Command);

    memset(pstCMM, 0, sizeof(IPC_CMM)); //Check

    s32Ret = IPC_Common_GetClientCmd(pstCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientGetCmd failed(0x%x)\n", s32Ret);
        CLIENT_UNLOCK();
        return s32Ret;
    }

    CLIENT_UNLOCK();

    //HI_WARN_AO("Exit  COMM command=0x%x\n", pstCMM->u32Command);

    return HI_SUCCESS;
}

static HI_VOID HALTryDestroyCmd(HI_VOID)
{
    CLIENT_LOCK();
    IPC_Common_TryDestroyClient();
    CLIENT_UNLOCK();
}

HI_BOOL IPC_Client_CheckISMediaTrackCreate(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_CHECKISMEDIACREATED;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
    }

    return (HI_BOOL)(stCMM.aPayload[0]);
}

HI_S32  IPC_Client_ApllyID(const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* pMAINhTrack, HI_HANDLE* pExtMainhTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_APPLYID;
    stCMM.bNeedReply = HI_TRUE;

    if (sizeof(HI_UNF_AUDIOTRACK_ATTR_S) > IPC_PAYLOAD_MAX_BYTES)
    {
        return HI_FAILURE;
    }

    memcpy(stCMM.aPayload, pstTrackAttr, sizeof(HI_UNF_AUDIOTRACK_ATTR_S));

    s32Ret = HALTryCreateSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        HI_WARN_AO("Apply TrackID(0x%x) ExtTrackID(0x%x)\n", stCMM.hTrack, stCMM.hExtTrack);
        *pMAINhTrack = stCMM.hTrack;
        *pExtMainhTrack = stCMM.hExtTrack;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_DeApllyID(HI_HANDLE hTrack, HI_HANDLE hExtTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_DEAPPLYID;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;
    stCMM.hExtTrack = hExtTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    HALTryDestroyCmd();

    return stCMM.s32ReplyValue;
}

HI_S32 IPC_Client_CreateTrackWithID(HI_HANDLE hTrack, HI_MPI_AO_SB_ATTR_S* pstAoIsbAttr)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_CREATETRACKWITHID;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        memcpy(pstAoIsbAttr, stCMM.aPayload, sizeof(HI_MPI_AO_SB_ATTR_S) * MAINASSOCAUDIOPAYLOADCNT);
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_DestroyTrackWithID(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_DESTROYTRACKWITHID;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_CreateTrack(HI_UNF_SND_E enSound, const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack, HI_MPI_AO_SB_ATTR_S* pstAoIsbAttr)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_CREATETRACK;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.enSound = enSound;

    if (sizeof(HI_UNF_AUDIOTRACK_ATTR_S) > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", sizeof(HI_UNF_AUDIOTRACK_ATTR_S), IPC_PAYLOAD_MAX_BYTES);
        return HI_FAILURE;
    }

    memcpy(stCMM.aPayload, pstTrackAttr, sizeof(HI_UNF_AUDIOTRACK_ATTR_S));

    s32Ret = HALTryCreateSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        *phTrack = stCMM.hTrack;
        memcpy(pstAoIsbAttr, stCMM.aPayload, sizeof(HI_MPI_AO_SB_ATTR_S));
    }

    HI_WARN_AO("New Track(0x%x), ReplyValue(0x%x)\n", stCMM.hTrack, stCMM.s32ReplyValue);

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_DestroyTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_DESTROYTRACK;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    // TODO:
    HALTryDestroyCmd();

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_ActiveTrack(HI_HANDLE hTrack, HI_BOOL bActived)
{
    HI_S32 s32Ret;
    HI_U32 u32StructSize = 0;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_ACTIVETRACK;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    u32StructSize = sizeof(HI_BOOL);

    if (u32StructSize > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", u32StructSize, IPC_PAYLOAD_MAX_BYTES);
        return HI_ERR_AO_INVALID_PARA;
    }

    memcpy(stCMM.aPayload, &bActived, u32StructSize);

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    HI_WARN_AO("ActiveTrack Track(0x%x), ReplyValue(0x%x)\n", hTrack, stCMM.s32ReplyValue);

    return stCMM.s32ReplyValue;
}


HI_S32  IPC_Client_SetTrackConfig(HI_HANDLE hTrack, const HI_VOID* pstConfig)
{
    HI_S32 s32Ret;
    HI_U32 u32StructSize = 0;
    IPC_CMM stCMM;
    HI_UNF_AUDIOTRACK_CONFIG_S* pstParam;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETTRACKCONFIG;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    pstParam = (HI_UNF_AUDIOTRACK_CONFIG_S*)pstConfig;
    u32StructSize = sizeof(HI_UNF_AUDIOTRACK_CONFIG_S);

    switch (pstParam->u32ConfigType)
    {
        case CONFIG_VOLUME:
            u32StructSize += sizeof(VOLUME_CONFIG_S);
            break;
        case CONFIG_SETEOSFLAG:
            u32StructSize += sizeof(SETEOSFLAG_CONFIG_S);
            break;
        case CONFIG_SETMEDIAVOLUMEATTENUATION:
            u32StructSize += sizeof(SETMEDIAVOLUMEATTENUATION_CONFIG_S);
            break;
        case CONFIG_SETCONTINUOUSOUTPUTSTATUS:
            u32StructSize += sizeof(SETCONTINUOUSOUTPUT_CONFIG_S);
            break;
        case CONFIG_SETATMOSLOCKOUTPUT:
            u32StructSize += sizeof(SETATMOSLOCK_CONFIG_S);
            break;
        case CONFIG_SETCONTINUOUSOUTPUTWITHDEEPBUF:
            u32StructSize += sizeof(SETDEEPBUFCONTINUOUSOUTPUT_CONFIG_S);
            break;
        default:
            HI_ERR_AO("Invalid u32ConfigType(0x%x)!", pstParam->u32ConfigType);
            return HI_ERR_AO_INVALID_PARA;
    }

    if (u32StructSize > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", u32StructSize, IPC_PAYLOAD_MAX_BYTES);
        return HI_ERR_AO_INVALID_PARA;
    }

    memcpy(stCMM.aPayload, pstParam, sizeof(HI_UNF_AUDIOTRACK_CONFIG_S));
    memcpy((HI_U8*)stCMM.aPayload + sizeof(HI_UNF_AUDIOTRACK_CONFIG_S), pstParam->pConfigData,
           u32StructSize - sizeof(HI_UNF_AUDIOTRACK_CONFIG_S));

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    HI_WARN_AO("SetTrackConfig Track(0x%x), ReplyValue(0x%x)\n", hTrack, stCMM.s32ReplyValue);

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_GetTrackConfig(HI_HANDLE hTrack, HI_VOID* pstConfig)
{
    HI_S32 s32Ret;
    HI_U32 u32StructSize = 0;
    IPC_CMM stCMM;
    HI_UNF_AUDIOTRACK_CONFIG_S* pstParam;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_GETTRACKCONFIG;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    pstParam = (HI_UNF_AUDIOTRACK_CONFIG_S*)pstConfig;
    u32StructSize += sizeof(pstParam->u32ConfigType);

    switch (pstParam->u32ConfigType)
    {
        case CONFIG_VOLUME:
            u32StructSize += sizeof(VOLUME_CONFIG_S);
            break;
        case CONFIG_GETSYSTEMTRACKALONEFLAG:
            u32StructSize += sizeof(GETSYSTRACKALONE_CONFIG_S);
            break;
        case CONFIG_GETAUDIOOUTPUTUSECASE:
            u32StructSize += sizeof(GETAUDIOOUTPUTUSECASE_CONFIG_S);
            break;
        default:
            HI_ERR_AO("Invalid u32ConfigType(0x%x)!", pstParam->u32ConfigType);
            return HI_ERR_AO_INVALID_PARA;
    }

    if (u32StructSize > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", u32StructSize, IPC_PAYLOAD_MAX_BYTES);
        return HI_ERR_AO_INVALID_PARA;
    }

    stCMM.aPayload[0] = pstParam->u32ConfigType;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        memcpy(pstParam->pConfigData, &stCMM.aPayload[1], u32StructSize - sizeof(pstParam->u32ConfigType));
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_SetTrackCmd(HI_HANDLE hTrack, HI_VOID* pstRenderCmd)
{
    HI_S32 s32Ret;
    HI_U32 u32StructSize = 0;
    IPC_CMM stCMM;
    HA_CODEC_PARAMETER_QUERY_S* pstParam;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETTRACKCMD;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    pstParam = (HA_CODEC_PARAMETER_QUERY_S*)pstRenderCmd;
    switch (pstParam->enCmd)
    {
        case HA_CODEC_MS12_SET_VOLUME_CMD:
        case HA_CODEC_MS12_GET_VOLUME_CMD:
            u32StructSize += sizeof(HA_MS12_VOLUME_S);
            break;
        case HA_CODEC_MS12_SET_PTS_MUTE_CMD:
            u32StructSize += sizeof(HA_MS12_SET_PTS_MUTE_S);
            break;
        case HA_CODEC_MS12_SET_PES_DATA_CMD:
            u32StructSize += sizeof(HA_MS12_SET_PES_DATA_S);
            break;
        case HA_CODEC_MS12_SET_AD_BALANCE_CMD:
            u32StructSize += sizeof(HA_MS12_SET_AD_BALANCE_S);
            break;
        case HA_CODEC_MS12_SET_DRC_MODE_CMD:
            u32StructSize += sizeof(HA_MS12_SET_DRC_MODE_S);
            break;
        case HA_CODEC_MS12_SET_LFE_MODE_CMD:
            u32StructSize += sizeof(HA_MS12_SET_LFE_MODE_S);
            break;
        case HA_CODEC_MS12_SET_DMX_MODE_CMD:
            u32StructSize += sizeof(HA_MS12_SET_DMX_MODE_S);
            break;
        case HA_CODEC_MS12_SET_DYNSCALE_MODE_CMD:
            u32StructSize += sizeof(HA_MS12_SET_DYNSCALE_MODE_S);
            break;
        case HA_CODEC_MS12_SET_DRC_SCALE_CMD:
            u32StructSize += sizeof(HA_MS12_SET_DRC_SCALE_S);
            break;
        case HA_CODEC_MS12_SET_DUAL_MODE_CMD:
            u32StructSize += sizeof(HA_MS12_SET_DUAL_MODE_S);
            break;
        case HA_CODEC_MS12_GET_STREAM_INFO_CMD:
        case HA_CODEC_MS12_GET_AD_STREAM_INFO_CMD:
            u32StructSize += sizeof(HA_MS12_GET_STREAM_INFO_S);
            break;
        default:
            HI_ERR_AO("Invalid Cmd(0x%x)!\n", pstParam->enCmd);
            return HI_ERR_AO_INVALID_PARA;
    }

    if (u32StructSize > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", u32StructSize, IPC_PAYLOAD_MAX_BYTES);
        return HI_ERR_AO_INVALID_PARA;
    }
    memcpy(stCMM.aPayload, pstParam, u32StructSize);

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    HI_WARN_AO("SetTrackCmd Track(0x%x), Cmd(0x%x), ReplyValue(0x%x)\n", hTrack, pstParam->enCmd, stCMM.s32ReplyValue);

    if (HI_SUCCESS != stCMM.s32ReplyValue)
    {
        return stCMM.s32ReplyValue;
    }

    // only for get cmd
    switch (pstParam->enCmd)
    {
        case HA_CODEC_MS12_GET_VOLUME_CMD:
            memcpy(pstParam, stCMM.aPayload, sizeof(HA_MS12_VOLUME_S));
            break;
        case HA_CODEC_MS12_GET_STREAM_INFO_CMD:
        case HA_CODEC_MS12_GET_AD_STREAM_INFO_CMD:
            memcpy(pstParam, stCMM.aPayload, sizeof(HA_MS12_GET_STREAM_INFO_S));
            break;
        default:
            HI_INFO_AO("Invalid GetCmd(0x%x)!\n", pstParam->enCmd);
            break;
    }

    return HI_SUCCESS;
}

HI_S32  IPC_Client_SetTrackAttr(const HI_HANDLE hTrack, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret;
    HI_U32 u32StructSize;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETTRACKATTR;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    u32StructSize = sizeof(HI_UNF_ACODEC_ATTR_S) + pstRenderAttr->stDecodeParam.u32CodecPrivateDataSize;

    if (u32StructSize > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", u32StructSize, IPC_PAYLOAD_MAX_BYTES);
        return HI_FAILURE;
    }

    memcpy(stCMM.aPayload, pstRenderAttr, sizeof(HI_UNF_ACODEC_ATTR_S));
    if (HI_NULL != pstRenderAttr->stDecodeParam.pCodecPrivateData)
    {
        memcpy((HI_U8*)stCMM.aPayload + sizeof(HI_UNF_ACODEC_ATTR_S), pstRenderAttr->stDecodeParam.pCodecPrivateData,
               pstRenderAttr->stDecodeParam.u32CodecPrivateDataSize);
    }

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    HI_WARN_AO("SetTrackAttr Track(0x%x), ReplyValue(0x%x)\n", hTrack, stCMM.s32ReplyValue);

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_GETTRACKATTR;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    if (sizeof(HI_UNF_AUDIOTRACK_ATTR_S) > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", sizeof(HI_UNF_AUDIOTRACK_ATTR_S), IPC_PAYLOAD_MAX_BYTES);
        return HI_FAILURE;
    }

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        memcpy(pstAttr, stCMM.aPayload, sizeof(HI_UNF_AUDIOTRACK_ATTR_S));
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_StartTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_STARTTRACK;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_StopTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_STOPTRACK;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_PauseTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_PAUSETRACK;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_FlushTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_FLUSHTRACK;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_SetTargetPts(HI_HANDLE hTrack, HI_U32 u32TargetPts)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETTARGETPTS;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    stCMM.aPayload[0] = u32TargetPts;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_SetRepeatTargetPts(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETREPEATTARGETPTS;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32 IPC_Client_GetTrackPts(HI_HANDLE hTrack, HI_U32* pu32PtsMs, HI_U32* pu32OrgPtsMs)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    HI_LOG_FuncEnter();

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_GETTRACKPTS;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        *pu32PtsMs = (HI_U32)(stCMM.aPayload[0]);
        *pu32OrgPtsMs = (HI_U32)(stCMM.aPayload[1]);
    }

    HI_WARN_AO("Get Pts(%d), OrgPts(%d), Ret(0x%x)\n", *pu32PtsMs, *pu32OrgPtsMs, stCMM.s32ReplyValue);
    HI_LOG_FuncExit();
    return stCMM.s32ReplyValue;
}

HI_S32 IPC_Client_DropTrackStream(HI_HANDLE hTrack, HI_U32 u32SeekPts)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_DROPTRACKSTREAM;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;
    stCMM.aPayload[0] = u32SeekPts;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_DropFrame(HI_HANDLE hTrack, HI_U32 u32FrameCnt)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_DROPFRAME;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;
    stCMM.aPayload[0] = u32FrameCnt;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_SetSyncMode(HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETSYNCMODE;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    stCMM.aPayload[0] = (HI_U32)enSyncMode;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_GETDELAYMS;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    *pu32DelayMs = *((HI_U32*)(stCMM.aPayload));

    return stCMM.s32ReplyValue;;
}

#ifdef DPT
HI_S32  IPC_Client_SetTrackMute(HI_HANDLE hTrack, HI_BOOL bMute)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETTRACKMUTE;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;
    stCMM.aPayload[0] = bMute;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_SetTrackPrescale(HI_HANDLE hTrack, const HI_UNF_SND_PRECIGAIN_ATTR_S* pstPreciGain)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;
    HI_U32 u32StructSize;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETTRACKPRESCALE;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    u32StructSize = sizeof(HI_UNF_SND_PRECIGAIN_ATTR_S);
    if (u32StructSize > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", u32StructSize, IPC_PAYLOAD_MAX_BYTES);
        return HI_FAILURE;
    }

    memcpy(stCMM.aPayload, pstPreciGain, sizeof(HI_UNF_SND_PRECIGAIN_ATTR_S));

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_SetTrackSource(HI_HANDLE hTrack, HI_UNF_SND_SOURCE_E enSource)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETTRACKSOURCE;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    stCMM.aPayload[0] = (HI_U32)enSource;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}
#endif

HI_S32  IPC_Client_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_SETEOSFLAG;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;
    stCMM.aPayload[0] = bEosFlag;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_GetEosState(HI_HANDLE hTrack, HI_BOOL* bEosState)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_GETEOSFLAG;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    *bEosState = (HI_BOOL)(stCMM.aPayload[0]);

    return stCMM.s32ReplyValue;
}

HI_S32 IPC_Client_GetCapability(HI_U32* pu32Capability)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_GETCAPABILITY;
    stCMM.bNeedReply = HI_TRUE;

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    *pu32Capability = (HI_U32)(stCMM.aPayload[0]);

    return stCMM.s32ReplyValue;
}

HI_S32 IPC_Client_GetBufferStatus(HI_HANDLE hTrack, ADEC_BUFSTATUS_S* pstBufStatus)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_GETBUFFERSTATUS;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    if (sizeof(ADEC_BUFSTATUS_S) > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", sizeof(ADEC_BUFSTATUS_S), IPC_PAYLOAD_MAX_BYTES);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        memcpy(pstBufStatus, stCMM.aPayload, sizeof(ADEC_BUFSTATUS_S));
    }

    return stCMM.s32ReplyValue;
}

HI_S32 IPC_Client_GetStreamInfo(HI_HANDLE hTrack, ADEC_STREAMINFO_S* pstBufStatus)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_GETSTREAMINFO;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    if (sizeof(ADEC_STREAMINFO_S) > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", sizeof(ADEC_STREAMINFO_S), IPC_PAYLOAD_MAX_BYTES);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        memcpy(pstBufStatus, stCMM.aPayload, sizeof(ADEC_STREAMINFO_S));
    }

    return stCMM.s32ReplyValue;
}

HI_S32 IPC_Client_CheckNewEvent(HI_HANDLE hTrack, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_CHECKNEWEVENT;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    if (sizeof(HI_MPI_AO_RENDER_EVENT_S) > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", sizeof(HI_MPI_AO_RENDER_EVENT_S), IPC_PAYLOAD_MAX_BYTES);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        memcpy(pstNewEvent, stCMM.aPayload, sizeof(HI_MPI_AO_RENDER_EVENT_S));
    }

    return stCMM.s32ReplyValue;
}

HI_S32  IPC_Client_GetRenderAllInfo(HI_HANDLE hTrack, HI_MPI_AO_RENDER_ALLINFO_S* pstAllInfo)
{
    HI_S32 s32Ret;
    IPC_CMM stCMM;

    memset(&stCMM, 0, sizeof(stCMM));

    stCMM.u32AckData = IPC_ACK_CLIENT_WRITE;
    stCMM.u32Command = CMD_SOURCE_GETRENDERALLINFO;
    stCMM.bNeedReply = HI_TRUE;
    stCMM.hTrack = hTrack;

    if (sizeof(HI_MPI_AO_RENDER_ALLINFO_S) > IPC_PAYLOAD_MAX_BYTES)
    {
        HI_ERR_AO("Oversized Payload(%d/%d)\n", sizeof(HI_MPI_AO_RENDER_ALLINFO_S), IPC_PAYLOAD_MAX_BYTES);
        return HI_FAILURE;
    }

    s32Ret = HALSetGetCmd(&stCMM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HALSetGetCmd failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_SUCCESS == stCMM.s32ReplyValue)
    {
        memcpy(pstAllInfo, stCMM.aPayload, sizeof(HI_MPI_AO_RENDER_ALLINFO_S));
    }

    return stCMM.s32ReplyValue;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
