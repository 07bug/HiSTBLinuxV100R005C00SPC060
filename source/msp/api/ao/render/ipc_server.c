/******************************************************************************

  Copyright (C), 2011-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipc_server.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/prctl.h>

#include "hi_mpi_ao.h"
#include "hi_error_mpi.h"

#include "render_common.h"
#include "ipc_common.h"
#include "render_source.h"
#include "render_engine.h"
#include "engine_codec_private.h"
#include "HA.AUDIO.DOLBYMS12.decode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define SOCKET_CONNECT_MAX_NUM    (20)
#define SOCKET_TRACK_MAX_NUM      (6)    //track created max num by one socket

static pthread_t g_hMainThread;
static HI_S32    g_s32ServerSockFd = INVALID_SOCKET_VALUE;
static HI_BOOL   g_bMainTHDDoRun;

typedef struct
{
    HI_HANDLE hTrack[SOCKET_TRACK_MAX_NUM];
    HI_S32    s32SocketFd;
    HI_BOOL   bContinueCtrl;
} SOCKET_RECORD_S;

typedef struct
{
    SOCKET_RECORD_S stRecordList[SOCKET_CONNECT_MAX_NUM];
    HI_HANDLE hActiveTrack;
} SOCKET_SERVER_S;

typedef struct
{
    pthread_t hThread[SOCKET_CONNECT_MAX_NUM];
    HI_S32    s32ClientFd[SOCKET_CONNECT_MAX_NUM];
    HI_BOOL   bOccupied[SOCKET_CONNECT_MAX_NUM];
} SOCKET_CLIENT_S;


static SOCKET_SERVER_S g_stServer;
static SOCKET_CLIENT_S g_stClient;

static HI_BOOL CheckIsAboutContinueConfig(HI_UNF_AUDIOTRACK_CONFIG_S* pstConfig, HI_BOOL* pbEnalbe)
{
    if (CONFIG_SETCONTINUOUSOUTPUTSTATUS == pstConfig->u32ConfigType)
    {
        SETCONTINUOUSOUTPUT_CONFIG_S* pstContinuousOutput = pstConfig->pConfigData;
        *pbEnalbe = pstContinuousOutput->bEnable;
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_VOID IPCServerRecordListInit(HI_VOID)
{
    int i, j;

    g_stServer.hActiveTrack = HI_INVALID_HANDLE;

    for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
    {
        for (j = 0; j < SOCKET_TRACK_MAX_NUM; j++)
        {
            g_stServer.stRecordList[i].hTrack[j] = HI_INVALID_HANDLE;
        }

        g_stServer.stRecordList[i].s32SocketFd = HI_INVALID_HANDLE;
        g_stServer.stRecordList[i].bContinueCtrl = HI_FALSE;
    }
}

static HI_VOID IPCServerRecordListDeInit(HI_VOID)
{
    IPCServerRecordListInit();
}

static HI_S32 IPCServerRecordListInsertNode(HI_S32 s32SocketFd)
{
    int i;

    for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
    {
        if (HI_INVALID_HANDLE == g_stServer.stRecordList[i].s32SocketFd)
        {
            break;
        }
    }

    if (SOCKET_CONNECT_MAX_NUM == i)
    {
        DLOG("Too much socket created\n");
        return HI_FAILURE;
    }

    g_stServer.stRecordList[i].s32SocketFd = s32SocketFd;

    return HI_SUCCESS;
}

static HI_VOID IPCServerRecordListDeleteNode(HI_S32 s32SocketFd)
{
    int i;

    for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
    {
        if (s32SocketFd == g_stServer.stRecordList[i].s32SocketFd)
        {
            break;
        }
    }

    if (SOCKET_CONNECT_MAX_NUM == i)
    {
        DLOG("Socket(0x%x) is not created\n", s32SocketFd);
        return;
    }

    g_stServer.stRecordList[i].s32SocketFd = HI_INVALID_HANDLE;
    memset(g_stServer.stRecordList[i].hTrack, HI_INVALID_HANDLE, SOCKET_TRACK_MAX_NUM);
}

static HI_S32 IPCServerRecordListInsertContinueFlag(HI_S32 s32SocketFd, HI_BOOL bEnable)
{
    int i;

    for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
    {
        if (s32SocketFd == g_stServer.stRecordList[i].s32SocketFd)
        {
            break;
        }
    }

    if (SOCKET_CONNECT_MAX_NUM == i)
    {
        DLOG("Too much socket created\n");
        return HI_FAILURE;
    }

    g_stServer.stRecordList[i].bContinueCtrl = bEnable;

    return HI_SUCCESS;
}

static HI_S32 IPCServerRecordListRegisterTrack(HI_S32 s32SocketFd, HI_HANDLE hTrack)
{
    int i, j;

    for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
    {
        if (s32SocketFd == g_stServer.stRecordList[i].s32SocketFd)
        {
            break;
        }
    }

    if (SOCKET_CONNECT_MAX_NUM == i)
    {
        DLOG("Socket(0x%x) is not created\n", s32SocketFd);
        return HI_FAILURE;
    }

    for (j = 0; j < SOCKET_TRACK_MAX_NUM; j++)
    {
        if (HI_INVALID_HANDLE == g_stServer.stRecordList[i].hTrack[j])
        {
            break;
        }
    }

    if (SOCKET_TRACK_MAX_NUM == j)
    {
        DLOG("Too much treak created\n");
        return HI_FAILURE;
    }

    g_stServer.stRecordList[i].hTrack[j] = hTrack;

    return HI_SUCCESS;
}

static HI_S32 IPCServerRecordListUnRegisterTrack(HI_S32 s32SocketFd, HI_HANDLE hTrack)
{
    int i, j;

    for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
    {
        if (s32SocketFd == g_stServer.stRecordList[i].s32SocketFd)
        {
            break;
        }
    }

    if (SOCKET_CONNECT_MAX_NUM == i)
    {
        DLOG("Socket(0x%x) is not created\n", s32SocketFd);
        return HI_FAILURE;
    }

    for (j = 0; j < SOCKET_TRACK_MAX_NUM; j++)
    {
        if (hTrack == g_stServer.stRecordList[i].hTrack[j])
        {
            break;
        }
    }

    if (SOCKET_TRACK_MAX_NUM == j)
    {
        DLOG("Track(0x%x) is not created\n", hTrack);
        return HI_FAILURE;
    }

    g_stServer.stRecordList[i].hTrack[j] = HI_INVALID_HANDLE;

    return HI_SUCCESS;
}

static HI_VOID IPCServerRecordListDestoryAllTrack(HI_S32 s32SocketFd)
{
    HI_U32 i, j;
    HI_S32 s32Ret;

    for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
    {
        if (s32SocketFd == g_stServer.stRecordList[i].s32SocketFd)
        {
            break;
        }
    }

    if (SOCKET_CONNECT_MAX_NUM == i)
    {
        DLOG("Socket(0x%x) is not created\n", s32SocketFd);
        return;
    }

    if (HI_TRUE == g_stServer.stRecordList[i].bContinueCtrl)
    {
        HI_UNF_AUDIOTRACK_CONFIG_S stTrackConfig;
        SETCONTINUOUSOUTPUT_CONFIG_S stContinuousOutput;
        stContinuousOutput.bEnable = HI_FALSE;
        stTrackConfig.u32ConfigType = CONFIG_SETCONTINUOUSOUTPUTSTATUS;
        stTrackConfig.pConfigData = &stContinuousOutput;
        Engine_SetTrackConfig(SOURCE_ID_MAIN, &stTrackConfig);
        g_stServer.stRecordList[i].bContinueCtrl = HI_FALSE;
    }

    for (j = 0; j < SOCKET_TRACK_MAX_NUM; j++)
    {
        HI_HANDLE hTrack = g_stServer.stRecordList[i].hTrack[j];
        if (HI_INVALID_HANDLE != hTrack)
        {
            DLOG("Socket(0x%x) Destory track(0x%x) created\n", s32SocketFd, hTrack);

            s32Ret = Source_Server_DestroyTrack(hTrack);
            if (HI_SUCCESS != s32Ret)
            {
                ELOG("Source_Server_DestroyTrack Track(0x%x) failed(0x%x)\n", hTrack, s32Ret);
            }

            if (HI_TRUE == Source_Server_CheckIsMediaTrack(hTrack))
            {
                s32Ret = Source_Server_DeallocID(hTrack);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_AO("SourceDeallocID Track failed(0x%x)\n", s32Ret);
                }
            }

            if (hTrack == g_stServer.hActiveTrack)
            {
                HI_WARN_AO("Deactive Track(0x%x)\n", hTrack);
                g_stServer.hActiveTrack = HI_INVALID_HANDLE;
            }

            g_stServer.stRecordList[i].hTrack[j] = HI_INVALID_HANDLE;
        }
    }
}

static HI_S32 IPCServerRecordListActiveTrack(HI_HANDLE hTrack, HI_BOOL bActived)
{
    if (HI_TRUE == bActived)
    {
        if (HI_INVALID_HANDLE == g_stServer.hActiveTrack)
        {
            HI_WARN_AO("Track(0x%x) Actived\n", hTrack);
            g_stServer.hActiveTrack = hTrack;
            return HI_SUCCESS;
        }

        if (hTrack == g_stServer.hActiveTrack)
        {
            HI_WARN_AO("Track(0x%x) being Actived\n", hTrack);
            return HI_SUCCESS;
        }

        HI_WARN_AO("Track(0x%x) being Actived, Active Track(0x%x) Failed\n", g_stServer.hActiveTrack, hTrack);
        return HI_ERR_AO_DEVICE_BUSY;
    }

    if ((HI_INVALID_HANDLE != g_stServer.hActiveTrack) && (hTrack == g_stServer.hActiveTrack))
    {
        HI_WARN_AO("Track(0x%x) Deactived\n", hTrack);
        g_stServer.hActiveTrack = HI_INVALID_HANDLE;
    }

    return HI_SUCCESS;
}

static HI_BOOL IPCServerCheckIsActiveTrack(HI_HANDLE hTrack)
{
    return (hTrack == g_stServer.hActiveTrack) ? HI_TRUE : HI_FALSE;
}

static HI_VOID IPCServerCreateTrack(HI_S32 s32SocketFd, IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_MPI_AO_SB_ATTR_S* pstIsbAttr;
    HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr;
    HI_HANDLE hTrack;

    pstTrackAttr = (HI_UNF_AUDIOTRACK_ATTR_S*)pstCmmDate->aPayload;

    s32Ret = Source_Server_Create(pstCmmDate->enSound, pstTrackAttr, &hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_Server_Create failed(0x%x)\n", s32Ret);
        pstCmmDate->s32ReplyValue = s32Ret;
        return;
    }

    DLOG("Source_Server_Create hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        HI_MPI_RENDER_SOURCE_TYPE_E enType = Source_Server_GetSourceTypeforTrackType(pstTrackAttr->enTrackType);

        memset(pstCmmDate, 0, sizeof(IPC_CMM));

        if (HI_SUCCESS == s32Ret)
        {
            pstIsbAttr = (HI_MPI_AO_SB_ATTR_S*)pstCmmDate->aPayload;
            pstIsbAttr->enType = enType;
            s32Ret = Source_Server_GetIsbAddr(pstCmmDate->enSound, pstIsbAttr);
            if (HI_SUCCESS != s32Ret)
            {
                ELOG("Source_Server_GetIsbAddr failed(0x%x)\n", s32Ret);
                (HI_VOID)Source_Server_DestroyTrack(hTrack);
            }
            else
            {
                HI_S32 s32RegRet;
                s32RegRet = IPCServerRecordListRegisterTrack(s32SocketFd, hTrack);
                if (HI_SUCCESS != s32RegRet)
                {
                    ELOG("IPCServerRecordListRegisterTrack failed(0x%x)\n", s32RegRet);
                }
            }
        }
        pstCmmDate->s32ReplyValue = s32Ret;
        pstCmmDate->hTrack = hTrack;
    }
}

static HI_VOID IPCServerDestroyTrack(HI_S32 s32SocketFd, IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;

    hTrack = pstCmmDate->hTrack;

    s32Ret = Source_Server_DestroyTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_DestroyTrack failed(0x%x)\n", s32Ret);
        // not return
    }

    DLOG("Source_Server_DestroyTrack hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

    IPCServerRecordListUnRegisterTrack(s32SocketFd, hTrack);

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerCreateTrackWithID(HI_S32 s32SocketFd, IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;

    DLOG("Source_Server_CreateWithID hTrack(0x%x)\n", pstCmmDate->hTrack);

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        HI_MPI_AO_SB_ATTR_S* pstIsbAttr;

        memset(pstCmmDate, 0, sizeof(IPC_CMM));

        pstIsbAttr = (HI_MPI_AO_SB_ATTR_S*)pstCmmDate->aPayload;
        pstIsbAttr->enType = HI_MPI_RENDER_SOURCE_TYPE_MAIN;
        s32Ret = Source_Server_GetIsbAddr(pstCmmDate->enSound, pstIsbAttr);

        pstIsbAttr++;
        pstIsbAttr->enType = HI_MPI_RENDER_SOURCE_TYPE_ASSOC;
        s32Ret |= Source_Server_GetIsbAddr(pstCmmDate->enSound, pstIsbAttr);

        pstIsbAttr++;
        pstIsbAttr->enType = HI_MPI_RENDER_SOURCE_TYPE_EXTMAIN;
        s32Ret |= Source_Server_GetIsbAddr(pstCmmDate->enSound, pstIsbAttr);

        if (HI_SUCCESS != s32Ret)
        {
            ELOG("Source_Server_GetIsbAddr failed(0x%x)\n", s32Ret);
        }

        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerDestroyTrackWithID(HI_S32 s32SocketFd, IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack = pstCmmDate->hTrack;

    s32Ret = Source_Server_DestroyTrackWithID(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_DestroyTrackWithID hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);
        // not return
    }

    DLOG("Source_Server_DestroyTrackWithID hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerSetTrackAttr(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;
    HI_UNF_ACODEC_ATTR_S* pstAttr;

    hTrack = pstCmmDate->hTrack;
    pstAttr = (HI_UNF_ACODEC_ATTR_S*)pstCmmDate->aPayload;
    pstAttr->stDecodeParam.pCodecPrivateData = (HI_U8*)pstCmmDate->aPayload + sizeof(HI_UNF_ACODEC_ATTR_S);

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        ELOG("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto EXIT;
    }

    if (SOURCE_ID_EXTDEC == enSourceID)
    {
        pstAttr->enType = HA_AUDIO_ID_PCM;
    }

    s32Ret = Engine_SetAttr(enSourceID, pstAttr);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_SetAttr failed(0x%x)\n", s32Ret);
    }

    DLOG("Engine_SetAttr hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerGetTrackAttr(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S stAttr = {0};

    hTrack = pstCmmDate->hTrack;

    s32Ret = Source_Server_GetTrackAttr(hTrack, &stAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_Server_GetBufferStatus failed(0x%x)\n", s32Ret);
    }

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        memcpy((HI_VOID*)pstCmmDate->aPayload, &stAttr, sizeof(HI_UNF_AUDIOTRACK_ATTR_S));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerGetRenderAllInfo(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_MPI_AO_RENDER_ALLINFO_S stAllInfo;

    s32Ret = Engine_GetAllInfo(&stAllInfo);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_GetAllInfo failed(0x%x)\n", s32Ret);
    }

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        memcpy((HI_VOID*)pstCmmDate->aPayload, &stAllInfo, sizeof(HI_MPI_AO_RENDER_ALLINFO_S));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerSetTrackConfig(HI_S32 s32SocketFd, IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_BOOL bTargetCmd = HI_FALSE;
    HI_HANDLE hTrack;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;
    HI_UNF_AUDIOTRACK_CONFIG_S* pstConfig;

    hTrack = pstCmmDate->hTrack;
    pstConfig = (HI_UNF_AUDIOTRACK_CONFIG_S*)pstCmmDate->aPayload;
    pstConfig->pConfigData = (HI_U8*)pstCmmDate->aPayload + sizeof(HI_UNF_AUDIOTRACK_CONFIG_S);

    s32Ret = Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto ERR;
    }

    HI_INFO_PrintU32(enSourceID);
    HI_INFO_PrintU32(pstConfig->u32ConfigType);

    if (HI_FALSE == Engine_CheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        s32Ret = HI_ERR_AO_INVALID_PARA;
        goto ERR;
    }

    if (HI_TRUE == CheckIsAboutContinueConfig(pstConfig, &bTargetCmd))
    {
        IPCServerRecordListInsertContinueFlag(s32SocketFd, bTargetCmd);
    }

    s32Ret = Engine_SetTrackConfig(enSourceID, pstConfig);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_SetTrackConfig failed(0x%x)\n", s32Ret);
    }

ERR:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerGetTrackConfig(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;
    HI_UNF_AUDIOTRACK_CONFIG_S stConfig;

    hTrack = pstCmmDate->hTrack;

    s32Ret = Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        pstCmmDate->s32ReplyValue = s32Ret;
        return;
    }

    stConfig.u32ConfigType = pstCmmDate->aPayload[0];
    stConfig.pConfigData = &pstCmmDate->aPayload[1];

    HI_INFO_PrintU32(enSourceID);
    HI_INFO_PrintU32(stConfig.u32ConfigType);

    s32Ret = Engine_GetTrackConfig(enSourceID, (HI_VOID*)(&stConfig));
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_GetTrackConfig failed(0x%x)\n", s32Ret);
    }

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerActiveTrack(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;

    s32Ret = IPCServerRecordListActiveTrack(pstCmmDate->hTrack, (HI_BOOL)(pstCmmDate->aPayload[0]));
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("IPCServerRecordListActiveTrack failed(0x%x)\n", s32Ret);
    }

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerSetTrackCmd(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;

    hTrack = pstCmmDate->hTrack;

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        ELOG("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto EXIT;
    }

    if (HI_FALSE == Engine_CheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        s32Ret = HI_ERR_AO_INVALID_PARA;
        goto EXIT;
    }

    s32Ret = Engine_SetCmd(enSourceID, (HI_VOID*)pstCmmDate->aPayload);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_SetCmd failed(0x%x)\n", s32Ret);
    }

    DLOG("Engine_SetCmd hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        // can not clear pstCmmDate because of getcmd usage
        //memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerSetEosFlag(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;

    hTrack = pstCmmDate->hTrack;

    if (HI_TRUE == Source_Server_CheckIsMediaTrack(hTrack))
    {
        if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
        {
            ELOG("Track(0x%x) Not Actived\n", hTrack);
            s32Ret = HI_ERR_AO_NOT_ACTIVED;
            goto EXIT;
        }
    }

    s32Ret = Source_Server_SetEosFlag(hTrack, (HI_BOOL)pstCmmDate->aPayload[0]);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_Server_SetEosFlag failed(0x%x)\n", s32Ret);
    }

    s32Ret |= Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto EXIT;
    }

    s32Ret |= Engine_SetEosFlag(enSourceID, (HI_BOOL)pstCmmDate->aPayload[0]);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_SetEosFlag (SourceID:%d) failed(0x%x)\n", enSourceID, s32Ret);
    }

    if (HI_TRUE == Source_Server_CheckIsMediaTrackDuplicate(hTrack))
    {
        s32Ret |= Engine_SetEosFlag(SOURCE_ID_ASSOC, (HI_BOOL)pstCmmDate->aPayload[0]);
        if (HI_SUCCESS != s32Ret)
        {
            ELOG("Engine_SetEosFlag (ID:%d) failed(0x%x)\n", enSourceID, s32Ret);
        }
    }

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerGetEosFlag(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_HANDLE hTrack = pstCmmDate->hTrack;

    s32Ret = Source_Server_GetEosState(hTrack, (HI_BOOL*)pstCmmDate->aPayload);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Server_GetEosState, s32Ret);
    }

    pstCmmDate->s32ReplyValue = s32Ret;
}

#ifdef DPT
static HI_VOID IPCServerSetTrackMute(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;
    HA_MS12_SET_SOURCEMUTE_S stMute;

    hTrack = pstCmmDate->hTrack;

    s32Ret = Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto EXIT;
    }

    if (HI_FALSE == Engine_CheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        s32Ret = HI_ERR_AO_INVALID_PARA;
        goto EXIT;
    }

    stMute.enCmd = HA_CODEC_MS12_SET_SOURCEMUTE_CMD;
    stMute.bEnable = (HI_BOOL)pstCmmDate->aPayload[0];

    s32Ret = Engine_SetCmd(enSourceID, (HI_VOID*)&stMute);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_SetCmd (SourceID:%d) failed(0x%x)\n", enSourceID, s32Ret);
    }

    if (HI_TRUE == Source_Server_CheckIsMediaTrackDuplicate(hTrack))
    {
        s32Ret = Engine_SetCmd(SOURCE_ID_ASSOC, (HI_VOID*)&stMute);
        if (HI_SUCCESS != s32Ret)
        {
            ELOG("Engine_SetCmd (SourceID:%d) failed(0x%x)\n", SOURCE_ID_ASSOC, s32Ret);
        }
    }

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerSetTrackPrescale(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;
    HI_UNF_SND_PRECIGAIN_ATTR_S* pstPreciGain = HI_NULL;
    HA_MS12_SET_SOURCEPRESCALE_S stPrescale = {0};

    hTrack = pstCmmDate->hTrack;

    s32Ret = Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto EXIT;
    }

    if (HI_FALSE == Engine_CheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        s32Ret = HI_ERR_AO_INVALID_PARA;
        goto EXIT;
    }

    pstPreciGain = (HI_UNF_SND_PRECIGAIN_ATTR_S*)pstCmmDate->aPayload;

    stPrescale.enCmd = HA_CODEC_MS12_SET_SOURCEPRESCALE_CMD;
    stPrescale.s32IntegerGain = pstPreciGain->s32IntegerGain;
    stPrescale.s32DecimalGain = pstPreciGain->s32DecimalGain;

    s32Ret = Engine_SetCmd(enSourceID, (HI_VOID*)&stPrescale);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_SetCmd (SourceID:%d) failed(0x%x)\n", enSourceID, s32Ret);
    }

    if (HI_TRUE == Source_Server_CheckIsMediaTrackDuplicate(hTrack))
    {
        s32Ret = Engine_SetCmd(SOURCE_ID_ASSOC, (HI_VOID*)&stPrescale);
        if (HI_SUCCESS != s32Ret)
        {
            ELOG("Engine_SetCmd (SourceID:%d) failed(0x%x)\n", SOURCE_ID_ASSOC, s32Ret);
        }
    }

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerSetTrackSource(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;

    hTrack = pstCmmDate->hTrack;

    s32Ret = Source_Server_SetTrackSource(hTrack, (HI_UNF_SND_SOURCE_E)(pstCmmDate->aPayload[0]));
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_SetTrackSource failed(0x%x)\n", s32Ret);
    }

    DLOG("Source_Server_SetTrackSource hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}
#endif

static HI_VOID IPCServerGetTrackDelayMS(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    HI_U32* pu32SinkDelayMs;
    HI_U32 u32SinkDelayMs = 0;
    HI_U32 u32SourceDelayMs = 0;

    hTrack = pstCmmDate->hTrack;
    pu32SinkDelayMs = (HI_U32*)pstCmmDate->aPayload;

    if (HI_TRUE == Source_Server_CheckIsMediaTrack(hTrack))
    {
        if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
        {
            ELOG("Track(0x%x) Not Actived\n", hTrack);
            s32Ret = HI_ERR_AO_NOT_ACTIVED;
            goto EXIT;
        }
    }

    s32Ret = Engine_GetSinkDelayMs(&u32SinkDelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Engine_GetSinkDelayMs failed(0x%x)\n", s32Ret);
    }

    s32Ret |= Source_Server_GetDelayMs(hTrack, &u32SourceDelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_Server_GetDelayMs failed(0x%x)\n", s32Ret);
    }

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        *pu32SinkDelayMs = u32SinkDelayMs + u32SourceDelayMs;
        pstCmmDate->s32ReplyValue = s32Ret;
    }

    HI_WARN_AO("DelayMs:%d (SourceDelayMs:%d SinkDelayMs:%d)\n", *pu32SinkDelayMs, u32SourceDelayMs, u32SinkDelayMs);
}

static HI_VOID IPCServerApplyTrackID(HI_S32 s32SocketFd, IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr;
    HI_HANDLE hMainTrack = 0;
    HI_HANDLE hExtMainTrack = 0;

    //check valid argv
    pstTrackAttr = (HI_UNF_AUDIOTRACK_ATTR_S*)pstCmmDate->aPayload;

    s32Ret = Source_Server_ApllyID(pstTrackAttr, &hMainTrack, &hExtMainTrack);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_ApllyID failed(0x%x)\n", s32Ret);
    }

    DLOG("Source_Server_ApllyID hMainTrack(0x%x) hExtMainTrack(0x%x) Ret(0x%x)\n", hMainTrack, hExtMainTrack, s32Ret);

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
        pstCmmDate->hTrack = hMainTrack;
        pstCmmDate->hExtTrack = hExtMainTrack;

        if (HI_SUCCESS == s32Ret)
        {
            HI_S32 s32RegRet;
            s32RegRet = IPCServerRecordListRegisterTrack(s32SocketFd, hMainTrack);
            s32RegRet |= IPCServerRecordListRegisterTrack(s32SocketFd, hExtMainTrack);
            if (HI_SUCCESS != s32RegRet)
            {
                ELOG("IPCServerRecordListRegisterTrack failed(0x%x)\n", s32RegRet);
            }
        }
    }
}

static HI_VOID IPCServerDeApplyTrackID(HI_S32 s32SocketFd, IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    HI_HANDLE hExtTrack;

    hTrack = pstCmmDate->hTrack;
    hExtTrack = pstCmmDate->hExtTrack;

    s32Ret = Source_Server_DeApllyID(hTrack, hExtTrack);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_DeApllyID failed(0x%x)\n", s32Ret);
    }

    DLOG("Source_Server_DeApllyID hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

    IPCServerRecordListUnRegisterTrack(s32SocketFd, hTrack);
    IPCServerRecordListUnRegisterTrack(s32SocketFd, hExtTrack);

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerStartTrack(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;

    //check valid argv
    hTrack = pstCmmDate->hTrack;

    if (HI_TRUE == Source_Server_CheckIsMediaTrack(hTrack))
    {
        if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
        {
            ELOG("Track(0x%x) Not Actived\n", hTrack);
            s32Ret = HI_ERR_AO_NOT_ACTIVED;
            goto EXIT;
        }
    }

    s32Ret = Source_Server_StartTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_StartTrack failed(0x%x)\n", s32Ret);
    }

EXIT:
    DLOG("Source_Server_StartTrack hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerStopTrack(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;

    hTrack = pstCmmDate->hTrack;

    if (HI_TRUE == Source_Server_CheckIsMediaTrack(hTrack))
    {
        if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
        {
            s32Ret = HI_ERR_AO_NOT_ACTIVED;
            goto EXIT;
        }
    }

    s32Ret = Source_Server_StopTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_StopTrack failed(0x%x)\n", s32Ret);
    }

    s32Ret |= Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto EXIT;
    }

    s32Ret |= Engine_ResetDecoder(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_ResetDecoder (SourceID:%d) failed(0x%x)\n", enSourceID, s32Ret);
    }

    if (HI_TRUE == Source_Server_CheckIsMediaTrackDuplicate(hTrack))
    {
        s32Ret |= Engine_ResetDecoder(SOURCE_ID_ASSOC);
        if (HI_SUCCESS != s32Ret)
        {
            ELOG("Engine_ResetDecoder (ID:%d) failed(0x%x)\n", enSourceID, s32Ret);
        }
    }

    DLOG("Source_Server_StopTrack hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerFlushTrack(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;

    hTrack = pstCmmDate->hTrack;

    if (HI_TRUE == Source_Server_CheckIsMediaTrack(hTrack))
    {
        if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
        {
            ELOG("Track(0x%x) Not Actived\n", hTrack);
            s32Ret = HI_ERR_AO_NOT_ACTIVED;
            goto EXIT;
        }
    }

    s32Ret = Source_Server_FlushTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_FlushTrack failed(0x%x)\n", s32Ret);
    }

    s32Ret |= Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto EXIT;
    }

    s32Ret |= Engine_ResetDecoder(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_ResetDecoder (SourceID:%d) failed(0x%x)\n", enSourceID, s32Ret);
    }

    if (HI_TRUE == Source_Server_CheckIsMediaTrackDuplicate(hTrack))
    {
        s32Ret |= Engine_ResetDecoder(SOURCE_ID_ASSOC);
        if (HI_SUCCESS != s32Ret)
        {
            ELOG("Engine_ResetDecoder (ID:%d) failed(0x%x)\n", enSourceID, s32Ret);
        }
    }

    DLOG("Source_Server_FlushTrack hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerPauseTrack(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;

    hTrack = pstCmmDate->hTrack;

    if (HI_TRUE == Source_Server_CheckIsMediaTrack(hTrack))
    {
        if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
        {
            ELOG("Track(0x%x) Not Actived\n", hTrack);
            s32Ret = HI_ERR_AO_NOT_ACTIVED;
            goto EXIT;
        }
    }

    s32Ret = Source_Server_PauseTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_PauseTrack failed(0x%x)\n", s32Ret);
    }

    DLOG("Source_Server_PauseTrack hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerGetCapability(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HA_MS12_GET_CAPABILITY_S stCapability;

    stCapability.enCmd = HA_CODEC_MS12_GET_CAPABILITY_CMD;
    stCapability.u32Capability = 0;

    s32Ret = Engine_GetCmd(&stCapability);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_GetCmd failed(0x%x)\n", s32Ret);
    }

    DLOG("Engine_GetCmd Capability(0x%x) Ret(0x%x)\n", stCapability.u32Capability, s32Ret);

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->aPayload[0] = stCapability.u32Capability;
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerSetSyncMode(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;

    hTrack = pstCmmDate->hTrack;

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        ELOG("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_Server_SetSyncMode(hTrack, (HI_MPI_AUDIOTRACK_SYNCMODE_E)(pstCmmDate->aPayload[0]));
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_SetSyncMode failed(0x%x)\n", s32Ret);
    }

    DLOG("Source_Server_SetSyncMode hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerDropTrackStream(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;
    HI_HANDLE hTrack = pstCmmDate->hTrack;

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        ELOG("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto EXIT;
    }

    s32Ret |= Engine_DropTrackStream(enSourceID, pstCmmDate->aPayload[0]);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Engine_DropTrackStream failed(0x%x)\n", s32Ret);
    }

    if (HI_TRUE == Source_Server_CheckIsMediaTrackDuplicate(hTrack))
    {
        s32Ret |= Engine_DropTrackStream(SOURCE_ID_ASSOC, pstCmmDate->aPayload[0]);
    }

    DLOG("Engine_DropTrackStream hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerDropFrame(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack = pstCmmDate->hTrack;

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        ELOG("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_Server_DropFrame(hTrack, pstCmmDate->aPayload[0]);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_DropFrame failed(0x%x)\n", s32Ret);
    }

    DLOG("Source_Server_DropFrame hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerSetTargetPts(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;

    hTrack = pstCmmDate->hTrack;

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        ELOG("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_Server_SetTargetPts(hTrack, pstCmmDate->aPayload[0]);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_SetTargetPts failed(0x%x)\n", s32Ret);
    }

    DLOG("Source_Server_SetTargetPts hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerSetRepeatTargetPts(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;

    hTrack = pstCmmDate->hTrack;

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        ELOG("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_Server_SetRepeatTargetPts(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_Server_SetRepeatTargetPts failed(0x%x)\n", s32Ret);
    }

    DLOG("Source_Server_SetRepeatTargetPts hTrack(0x%x) Ret(0x%x)\n", hTrack, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerGetTrackPts(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_U32 u32PtsMs = 0;
	HI_U32 u32OrgPtsMs = 0;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;
    HI_HANDLE hTrack = pstCmmDate->hTrack;

    HI_LOG_FuncEnter();

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        ELOG("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_GetSourceIDFromTrackID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        ELOG("Source_GetSourceIDFromTrackID hTrack(0x%x) failed(0x%x)\n", hTrack, s32Ret);
        goto EXIT;
    }

    s32Ret = Engine_GetTrackPts(enSourceID, &u32PtsMs, &u32OrgPtsMs);

    DLOG("Engine_GetTrackPts SourceID(%d) u32PtsMs(%d) u32OrgPtsMs(%d) Ret(0x%x)\n", enSourceID, u32PtsMs, u32OrgPtsMs, s32Ret);

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->aPayload[0] = u32PtsMs;
        pstCmmDate->aPayload[1] = u32OrgPtsMs;
        pstCmmDate->s32ReplyValue = s32Ret;
    }

    HI_LOG_FuncExit();
}

static HI_VOID IPCServerGetBufferStatus(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    ADEC_BUFSTATUS_S stBufStatus = {0};

    hTrack = pstCmmDate->hTrack;

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        HI_WARN_AO("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_Server_GetBufferStatus(hTrack, &stBufStatus);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_Server_GetBufferStatus failed(0x%x)\n", s32Ret);
    }

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        memcpy((HI_VOID*)pstCmmDate->aPayload, &stBufStatus, sizeof(ADEC_BUFSTATUS_S));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerGetStreamInfo(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    ADEC_STREAMINFO_S stStreamInfo = {0};

    hTrack = pstCmmDate->hTrack;

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        HI_WARN_AO("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_Server_GetStreamInfo(hTrack, &stStreamInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_Server_GetStreamInfo failed(0x%x)\n", s32Ret);
    }

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        memcpy((HI_VOID*)pstCmmDate->aPayload, &stStreamInfo, sizeof(ADEC_STREAMINFO_S));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerCheckNewEvent(IPC_CMM* pstCmmDate)
{
    HI_S32 s32Ret;
    HI_HANDLE hTrack;
    HI_MPI_AO_RENDER_EVENT_S stEvent = {0};

    hTrack = pstCmmDate->hTrack;

    if (HI_FALSE == IPCServerCheckIsActiveTrack(hTrack))
    {
        HI_WARN_AO("Track(0x%x) Not Actived\n", hTrack);
        s32Ret = HI_ERR_AO_NOT_ACTIVED;
        goto EXIT;
    }

    s32Ret = Source_Server_GetNewEvent(hTrack, &stEvent);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_Server_CheckNewEvent failed(0x%x)\n", s32Ret);
    }

EXIT:
    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        memcpy((HI_VOID*)pstCmmDate->aPayload, &stEvent, sizeof(HI_MPI_AO_RENDER_EVENT_S));
        pstCmmDate->s32ReplyValue = s32Ret;
    }
}

static HI_VOID IPCServerCheckIsMediaTrackCreate(IPC_CMM* pstCmmDate)
{
    HI_BOOL bCreate;
    HI_HANDLE hTrack;

    hTrack = pstCmmDate->hTrack;
    bCreate = Source_Server_CheckIsMediaTrackCreated(hTrack);

    DLOG("Source_Server_CheckIsMediaTrackCreated hTrack(0x%x) bCreate(%d)\n", hTrack, bCreate);

    if (HI_TRUE == pstCmmDate->bNeedReply)
    {
        memset(pstCmmDate, 0, sizeof(IPC_CMM));
        pstCmmDate->s32ReplyValue = HI_SUCCESS;
        pstCmmDate->aPayload[0] = (HI_U32)bCreate;
    }
}

static HI_VOID IPCServerExceptionProcess(HI_S32 s32SocketFd)
{
    IPCServerRecordListDestoryAllTrack(s32SocketFd);
}

static HI_VOID IPCServerCmdProcess(HI_S32 s32SocketFd, IPC_CMM* pstCmmDate)
{
    HI_U32 u32CmmBytes;
    HI_U32 u32DoneBytes;
    HI_U32 bNeedReply = pstCmmDate->bNeedReply;

    u32CmmBytes = sizeof(IPC_CMM);

    DDLOG("Reading[0x%x] COMM ack        0x%x\n", s32SocketFd, pstCmmDate->u32AckData);
    DDLOG("Reading[0x%x] COMM command    0x%x\n", s32SocketFd, pstCmmDate->u32Command);
    DDLOG("Reading[0x%x] COMM bNeedReply 0x%x\n", s32SocketFd, pstCmmDate->bNeedReply);
    HI_WARN_AO("COMM command=0x%x\n", pstCmmDate->u32Command);

    switch (pstCmmDate->u32Command)
    {
        case CMD_SOURCE_APPLYID:
            HI_WARN_AO("process SourceApplyID\n");
            IPCServerApplyTrackID(s32SocketFd, pstCmmDate);
            break;
        case CMD_SOURCE_DEAPPLYID:
            HI_WARN_AO("process SourceDeApplyID\n");
            IPCServerDeApplyTrackID(s32SocketFd, pstCmmDate);
            break;
        case CMD_SOURCE_CREATETRACK:
            HI_WARN_AO("process CreateTrack\n");
            IPCServerCreateTrack(s32SocketFd, pstCmmDate);
            break;
        case CMD_SOURCE_DESTROYTRACK:
            HI_WARN_AO("process DestroyTrack\n");
            IPCServerDestroyTrack(s32SocketFd, pstCmmDate);
            break;
        case CMD_SOURCE_STARTTRACK:
            HI_WARN_AO("process StartTrack\n");
            IPCServerStartTrack(pstCmmDate);
            break;
        case CMD_SOURCE_STOPTRACK:
            HI_WARN_AO("process StopTrack\n");
            IPCServerStopTrack(pstCmmDate);
            break;
        case CMD_SOURCE_GETCAPABILITY:
            HI_WARN_AO("process GetCapability\n");
            IPCServerGetCapability(pstCmmDate);
            break;
        case CMD_SOURCE_SETTARGETPTS:
            HI_WARN_AO("process SetTargetPts\n");
            IPCServerSetTargetPts(pstCmmDate);
            break;
        case CMD_SOURCE_SETREPEATTARGETPTS:
            HI_WARN_AO("process SetRepeatTargetPts\n");
            IPCServerSetRepeatTargetPts(pstCmmDate);
            break;
        case CMD_SOURCE_GETTRACKPTS:
            HI_WARN_AO("process GetTrackPts\n");
            IPCServerGetTrackPts(pstCmmDate);
            break;
        case CMD_SOURCE_SETSYNCMODE:
            HI_WARN_AO("process SetSyncMode\n");
            IPCServerSetSyncMode(pstCmmDate);
            break;
        case CMD_SOURCE_CHECKISMEDIACREATED:
            HI_WARN_AO("process CheckIsMediaTrackCreate\n");
            IPCServerCheckIsMediaTrackCreate(pstCmmDate);
            break;
        case CMD_SOURCE_CREATETRACKWITHID:
            HI_WARN_AO("process CreateTrackWithID\n");
            IPCServerCreateTrackWithID(s32SocketFd, pstCmmDate);
            break;
        case CMD_SOURCE_DESTROYTRACKWITHID:
            HI_WARN_AO("process DestroyTrackWithID\n");
            IPCServerDestroyTrackWithID(s32SocketFd, pstCmmDate);
            break;
        case CMD_SOURCE_SETTRACKATTR:
            HI_WARN_AO("process SetTrackAttr\n");
            IPCServerSetTrackAttr(pstCmmDate);
            break;
        case CMD_SOURCE_GETTRACKATTR:
            HI_WARN_AO("process GetTrackAttr\n");
            IPCServerGetTrackAttr(pstCmmDate);
            break;
        case CMD_SOURCE_SETTRACKCONFIG:
            HI_WARN_AO("process SetTrackConfig\n");
            IPCServerSetTrackConfig(s32SocketFd, pstCmmDate);
            break;
        case CMD_SOURCE_GETTRACKCONFIG:
            HI_WARN_AO("process GetTrackConfig\n");
            IPCServerGetTrackConfig(pstCmmDate);
            break;
        case CMD_SOURCE_GETDELAYMS:
            HI_WARN_AO("process GetTrackDelayMS\n");
            IPCServerGetTrackDelayMS(pstCmmDate);
            break;
        case CMD_SOURCE_DROPTRACKSTREAM:
            HI_WARN_AO("process DropTrackStream\n");
            IPCServerDropTrackStream(pstCmmDate);
            break;
        case CMD_SOURCE_SETTRACKCMD:
            HI_WARN_AO("process SetTrackCmd\n");
            IPCServerSetTrackCmd(pstCmmDate);
            break;
        case CMD_SOURCE_ACTIVETRACK:
            HI_WARN_AO("process ActiveTrackCmd\n");
            IPCServerActiveTrack(pstCmmDate);
            break;
        case CMD_SOURCE_GETBUFFERSTATUS:
            HI_WARN_AO("process GetBufferStatus\n");
            IPCServerGetBufferStatus(pstCmmDate);
            break;
        case CMD_SOURCE_CHECKNEWEVENT:
            HI_WARN_AO("process CheckNewEvent\n");
            IPCServerCheckNewEvent(pstCmmDate);
            break;
        case CMD_SOURCE_DROPFRAME:
            HI_WARN_AO("process DropFrame\n");
            IPCServerDropFrame(pstCmmDate);
            break;
        case CMD_SOURCE_SETEOSFLAG:
            HI_WARN_AO("process SetEOSFlag\n");
            IPCServerSetEosFlag(pstCmmDate);
            break;
        case CMD_SOURCE_GETEOSFLAG:
            HI_WARN_AO("process GetEOSFlag\n");
            IPCServerGetEosFlag(pstCmmDate);
            break;
        case CMD_SOURCE_FLUSHTRACK:
            HI_WARN_AO("process FlushTrack\n");
            IPCServerFlushTrack(pstCmmDate);
            break;
        case CMD_SOURCE_PAUSETRACK:
            HI_WARN_AO("process PauseTrack\n");
            IPCServerPauseTrack(pstCmmDate);
            break;
        case CMD_SOURCE_GETRENDERALLINFO:
            HI_WARN_AO("process GetRenderAllInfo\n");
            IPCServerGetRenderAllInfo(pstCmmDate);
            break;
        case CMD_SOURCE_GETSTREAMINFO:
            HI_WARN_AO("process GetStreamInfo\n");
            IPCServerGetStreamInfo(pstCmmDate);
            break;
#ifdef DPT
       case CMD_SOURCE_SETTRACKMUTE:
            HI_WARN_AO("process SetTrackMute\n");
            IPCServerSetTrackMute(pstCmmDate);
            break;
        case CMD_SOURCE_SETTRACKPRESCALE:
            HI_WARN_AO("process SetTrackPrescale\n");
            IPCServerSetTrackPrescale(pstCmmDate);
            break;
        case CMD_SOURCE_SETTRACKSOURCE:
            HI_WARN_AO("process SetTrackSource\n");
            IPCServerSetTrackSource(pstCmmDate);
            break;
#endif
        default:
            HI_ERR_AO("Invalid command(0x%x)\n", pstCmmDate->u32Command);
            break;
    }

    if (HI_TRUE == bNeedReply)
    {
        pstCmmDate->u32AckData = IPC_ACK_SERVER_WRITE;

        u32DoneBytes = write(s32SocketFd, pstCmmDate, u32CmmBytes);
        if (u32DoneBytes != u32CmmBytes)
        {
            DLOG("Write[0x%x] failed(0x%x)\n", s32SocketFd, u32DoneBytes);
        }
        else
        {
            DDLOG("Reply[0x%x] successfully\n", s32SocketFd);
        }
    }
}

static HI_VOID IPCServerDestroyClientFd()
{
    HI_S32 i;
    for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
    {
        if (HI_TRUE == g_stClient.bOccupied[i] && g_stClient.s32ClientFd[i] >= 0)
        {
            HI_WARN_AO("SocketFd(0x%x) i=%d\n", g_stClient.s32ClientFd[i], i);

            close(g_stClient.s32ClientFd[i]);
            g_stClient.bOccupied[i] = HI_FALSE;
            g_stClient.s32ClientFd[i] = INVALID_SOCKET_VALUE;
            //pthread_join(g_stClient.hThread[i], HI_NULL);
        }
    }
}

static HI_VOID* HiClientIpcthread(HI_VOID* pClientFd)
{
    HI_S32 i;
    HI_S32 s32SocketFd = *(HI_S32*)pClientFd;

    if (s32SocketFd < 0)
    {
        DLOG("\nInvalid ClientSocket Fd!\n");
        return NULL;
    }

    DLOG("CommThread start SocketFd(0x%x)\n", s32SocketFd);

    IPCServerRecordListInsertNode(s32SocketFd);

    prctl(PR_SET_NAME, "HiRenderClientIpcThread");

#ifdef HI_LINUX_PRODUCT
    {
        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(CPU_MASK, &mask);
        if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0)
        {
            HI_WARN_AO("set thread HiRenderClientIpcThread affinity failed\n");
        }
        else
        {
            HI_WARN_AO("set thread HiRenderClientIpcThread affinity success\n");
        }
    }
#endif

    while (1)
    {
        HI_U32 u32DoneBytes;
        HI_U32 u32CmmBytes;
        IPC_CMM stCmmDate;

        u32CmmBytes = sizeof(stCmmDate);

        memset(&stCmmDate, 0, u32CmmBytes);

        DDLOG("CommThread waiting for Reading(0x%x) ...\n", s32SocketFd);
        u32DoneBytes = read(s32SocketFd, &stCmmDate, u32CmmBytes);
        if (u32DoneBytes <= 0)
        {
            DLOG("Read failed(0x%x)\n", u32DoneBytes);
            IPCServerExceptionProcess(s32SocketFd);
            break;
        }

        DDLOG("Read 0x%x Ok %dbytes\n", s32SocketFd, u32DoneBytes);

        if (IPC_ACK_CLIENT_WRITE != stCmmDate.u32AckData)
        {
            DLOG("Should be disconnect status, ack is 0x%x\n", stCmmDate.u32AckData);
            break;
        }

        IPCServerCmdProcess(s32SocketFd, &stCmmDate);
    }

    IPCServerRecordListDeleteNode(s32SocketFd);

    for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
    {
        if (g_stClient.s32ClientFd[i] == s32SocketFd)
        {
            break;
        }
    }

    if (i >= SOCKET_CONNECT_MAX_NUM)
    {
        HI_ERR_AO("Can not find Client SocketFd!\n");
    }
    else
    {
        close(s32SocketFd);
        g_stClient.bOccupied[i] = HI_FALSE;
        g_stClient.s32ClientFd[i] = INVALID_SOCKET_VALUE;
    }

    DLOG("CommThread exit SocketFd(0x%x)\n", s32SocketFd);

    return HI_NULL;
}

static HI_VOID* HiMainIpcthread(HI_VOID* argv)
{
    HI_S32 s32Ret;
    HI_S32 i;

    DLOG("Server Mainthread Start ...\n");

    prctl(PR_SET_NAME, "HiRenderMainIpcThread");

#ifdef HI_LINUX_PRODUCT
    {
        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(CPU_MASK, &mask);
        if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0)
        {
            HI_WARN_AO("set thread HiRenderMainIpcThread affinity failed\n");
        }
        else
        {
            HI_WARN_AO("set thread HiRenderMainIpcThread affinity success\n");
        }
    }
#endif

    while (HI_TRUE == g_bMainTHDDoRun)
    {
        for (i = 0; i < SOCKET_CONNECT_MAX_NUM; i++)
        {
            if (HI_FALSE == g_stClient.bOccupied[i])
            {
                break;
            }
        }

        if (i >= SOCKET_CONNECT_MAX_NUM)
        {
            HI_ERR_AO("Connect too many socket!\n");
            continue;
        }

        s32Ret = IPC_Common_AcceptServer(g_s32ServerSockFd, &g_stClient.s32ClientFd[i]);
        if (HI_SUCCESS != s32Ret)
        {
            DLOG("ServerAccept failed(0x%x)\n", s32Ret);
            continue;
        }

        g_stClient.bOccupied[i] = HI_TRUE;

        s32Ret = IPC_Common_SetupServerCommThread(&g_stClient.hThread[i], &g_stClient.s32ClientFd[i], HiClientIpcthread);
        if (HI_SUCCESS != s32Ret)
        {
            DLOG("ServerSetupSeparateCommThread failed(0x%x)\n", s32Ret);
            close(g_stClient.s32ClientFd[i]);
            g_stClient.bOccupied[i] = HI_FALSE;
            g_stClient.s32ClientFd[i] = INVALID_SOCKET_VALUE;
            return HI_NULL;
        }
    }

    return HI_NULL;
}

HI_S32 IPC_Service_Create(HI_CHAR* Path)
{
    HI_S32 s32Ret;

    s32Ret = IPC_Common_CreateServer(&g_s32ServerSockFd, Path);
    if (HI_SUCCESS != s32Ret)
    {
        DLOG("ServerCreate failed(0x%x)\n", s32Ret);
        return HI_FAILURE;
    }

    IPCServerRecordListInit();

    g_bMainTHDDoRun = HI_TRUE;

    s32Ret = pthread_create(&g_hMainThread, NULL, HiMainIpcthread, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        DLOG("Server create Mainthread Failed(0x%x)\n", s32Ret);
        IPC_Common_DestroyServer(g_s32ServerSockFd);
        g_s32ServerSockFd = INVALID_SOCKET_VALUE;
    }

    signal(SIGPIPE, SIG_IGN);   //ignore broken pipe exception caused by closing socket

    return s32Ret;
}

HI_VOID IPC_Service_Destroy(HI_VOID)
{
    DLOG("##### FUNC TO ADD force to break socket\n");

    if (HI_TRUE == g_bMainTHDDoRun)
    {
        g_bMainTHDDoRun = HI_FALSE;

        IPCServerDestroyClientFd();
        IPC_Common_DestroyServer(g_s32ServerSockFd);
        g_s32ServerSockFd = INVALID_SOCKET_VALUE;
        pthread_detach(g_hMainThread);
        IPCServerRecordListDeInit();
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
