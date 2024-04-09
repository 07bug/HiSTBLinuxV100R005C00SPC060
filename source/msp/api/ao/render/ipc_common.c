/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: ipc_common.c
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
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <errno.h>
//#include <error.h>

#include "hi_error_mpi.h"
#include "render_common.h"
#include "ipc_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


static HI_S32 g_s32ClientSocketFd = INVALID_SOCKET_VALUE;
static HI_U32 g_s32ClientNum = 0;

static HI_BOOL ClientCheckValidConnect(HI_VOID)
{
    return (0 == g_s32ClientNum) ? HI_FALSE : HI_TRUE;
}

HI_S32 IPC_Common_CreateServer(HI_S32* ps32ServerFd, HI_CHAR* Path)
{
    HI_S32 s32Ret;
    HI_S32 s32ServerLen;
    struct sockaddr_un stServerAddr = {0};

    if (strlen(Path) + 1 >= AO_COMM_PATH_MAX_LENGTH)
    {
        HI_ERR_AO("Invalid socket path(%s) too long\n", strlen(Path));
        return HI_FAILURE;
    }

    (HI_VOID)unlink(Path);

    *ps32ServerFd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (INVALID_SOCKET_VALUE == *ps32ServerFd)
    {
        HI_ERR_AO("create socket failed\n");
        return HI_FAILURE;
    }

    HI_WARN_AO("Socket path(%s)\n", Path);

    stServerAddr.sun_family = AF_UNIX;
    strncpy(stServerAddr.sun_path, Path, sizeof(stServerAddr.sun_path) - 1);
    s32ServerLen = sizeof(stServerAddr);

    s32Ret = bind(*ps32ServerFd, (struct sockaddr*)&stServerAddr, s32ServerLen);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("bind failed(0x%x)\n", s32Ret);
        close(*ps32ServerFd);
        *ps32ServerFd = INVALID_SOCKET_VALUE;
        return HI_FAILURE;
    }

    s32Ret = listen(*ps32ServerFd, IPC_SERVER_LISTEN_MAXCONNECT);
    if (INVALID_SOCKET_VALUE == s32Ret)
    {
        HI_ERR_AO("listen failed(0x%x)\n", s32Ret);
        close(*ps32ServerFd);
        *ps32ServerFd = INVALID_SOCKET_VALUE;
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID IPC_Common_DestroyServer(HI_S32 s32ServerFd)
{
    if (INVALID_SOCKET_VALUE != s32ServerFd)
    {
        close(s32ServerFd);
    }
}

HI_S32 IPC_Common_AcceptServer(HI_S32 s32ServerFd, HI_S32* ps32ClientFd)
{
    HI_S32 s32ClientLen;
    struct sockaddr_un stClientAddr;

    s32ClientLen = sizeof(stClientAddr);

    *ps32ClientFd = accept(s32ServerFd, (struct sockaddr*)&stClientAddr, (socklen_t*)(&s32ClientLen));
    if (*ps32ClientFd < 0)
    {
        HI_ERR_AO("server accept Error(0x%x)\n", errno);
        return HI_FAILURE;
    }

    HI_WARN_AO("Server accept successfully 0x%x\n", *ps32ClientFd);

    return HI_SUCCESS;
}

HI_S32 IPC_Common_SetupServerCommThread(pthread_t* pThreadId, HI_S32* ps32ClientFd, HI_VOID*(*HiClientIpcthread)(HI_VOID*))
{
    HI_S32 s32Ret;

    s32Ret = pthread_create(pThreadId, NULL, HiClientIpcthread, (HI_VOID*)ps32ClientFd);
    if (HI_SUCCESS == s32Ret)
    {
        HI_WARN_AO("Server create new thread process comm(0x%x) and detach\n", *ps32ClientFd);
        pthread_detach(*pThreadId);
    }

    return s32Ret;
}

HI_S32 IPC_Common_TryCreateClient(HI_VOID)
{
    HI_S32 s32Ret;
    HI_U32 u32ConnectTime = 0;
    struct sockaddr_un stClientAddr = {0};
    AO_RENDER_ATTR_S stRenderAttr;
    struct timespec stSlpTm;

    if (0 != g_s32ClientNum)
    {
        g_s32ClientNum++;
        HI_WARN_AO("Socket have been connected(0x%x)\n", g_s32ClientNum);
        return HI_SUCCESS;
    }

    /* Get COMM path form DRV */
    s32Ret = HI_MPI_AO_SND_GetRenderParam(HI_UNF_SND_0, &stRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SND_GetRenderParam, s32Ret);
        return s32Ret;
    }

    if (HI_TRUE != stRenderAttr.bSupport)
    {
        HI_ERR_AO("Render not support in drv\n");
        return HI_FAILURE;
    }

    while (1)
    {
        if (u32ConnectTime >= IPC_CLIENT_CONNECT_MAXTIMES)
        {
            HI_ERR_AO("Socket connect timeout failed(0x%x) 0x%x\n", s32Ret, errno);
            return HI_FAILURE;
        }

        g_s32ClientSocketFd = socket(PF_LOCAL, SOCK_STREAM, 0);
        if (g_s32ClientSocketFd < 0)
        {
            HI_ERR_AO("Create client socket failure\n");
            return HI_FAILURE;
        }

        HI_WARN_AO("Try to connect server(%s)\n", stRenderAttr.aCommPath);

        stClientAddr.sun_family = AF_UNIX;
        strncpy(stClientAddr.sun_path, stRenderAttr.aCommPath, sizeof(stClientAddr.sun_path) - 1);

        s32Ret = connect(g_s32ClientSocketFd, (struct sockaddr*)&stClientAddr, sizeof(stClientAddr));
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Socket connect failed(0x%x) 0x%x\n", s32Ret, errno);
            //perror("fail ");
            close(g_s32ClientSocketFd);
            u32ConnectTime++;

            stSlpTm.tv_sec = 0;
            stSlpTm.tv_nsec = IPC_CLIENT_CONNECT_DELAYMS * 1000 * 1000;
            if(0 != nanosleep(&stSlpTm, NULL))
            {
                HI_ERR_AO("nanosleep err.\n");
            }
            continue;
        }
        DLOG("Connect server successfully (0x%x)\n", s32Ret);

        break;
    }

    g_s32ClientNum++;

    DLOG("Socket connected successfully(0x%x)\n", g_s32ClientNum);

    return HI_SUCCESS;
}

HI_VOID IPC_Common_TryDestroyClient(HI_VOID)
{
    if (1 == g_s32ClientNum)
    {
        close(g_s32ClientSocketFd);
        g_s32ClientSocketFd = INVALID_SOCKET_VALUE;
    }

    g_s32ClientNum = (g_s32ClientNum >= 1) ? (g_s32ClientNum - 1) : 0;
}

HI_S32 IPC_Common_SetClientCmd(IPC_CMM* pstIPCcmm)
{
    HI_U32 u32WroteBytes;
    HI_U32 u32CmmBytes = sizeof(IPC_CMM);

    if (HI_FALSE == ClientCheckValidConnect())
    {
        HI_WARN_AO("Socket(0x%x) is not built\n");
        return HI_ERR_AO_INVALID_PARA;
    }

    u32WroteBytes = write(g_s32ClientSocketFd, pstIPCcmm, u32CmmBytes);
    if (u32CmmBytes != u32WroteBytes)
    {
        HI_ERR_AO("Write socket(0x%x) failed (0x%x/0x%x)\n", g_s32ClientSocketFd, u32CmmBytes, u32WroteBytes);
        return HI_FAILURE;
    }

    DDLOG("Socket(0x%x) setCmd success\n", g_s32ClientSocketFd);

    return HI_SUCCESS;
}

HI_S32 IPC_Common_GetClientCmd(IPC_CMM* pstIPCcmm)
{
    HI_U32 u32ReadBytes;
    HI_U32 u32CmmBytes = sizeof(IPC_CMM);

    if (HI_FALSE == ClientCheckValidConnect())
    {
        return HI_FAILURE;
    }

    u32ReadBytes = read(g_s32ClientSocketFd, pstIPCcmm, u32CmmBytes);
    if (u32CmmBytes != u32ReadBytes)
    {
        DLOG("Read socket(0x%x) failed (0x%x/0x%x)\n", g_s32ClientSocketFd, u32CmmBytes, u32ReadBytes);
        return HI_FAILURE;
    }

    DDLOG("Socket(0x%x) getCmd success\n", g_s32ClientSocketFd);

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
