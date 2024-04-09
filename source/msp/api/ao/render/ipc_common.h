/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipc_common.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __IPC_COMMON_H__
#define  __IPC_COMMON_H__

#include <pthread.h>

#include "hi_type.h"
#include "hi_unf_sound.h"
#include "hi_drv_ao.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if 0
#define DLOG   HI_WARN_AO
#define ELOG   HI_ERR_AO
#else
#define DLOG   HI_INFO_AO
#define ELOG   HI_ERR_AO
#endif

#if 0
#define DDLOG  HI_WARN_AO
#else
#define DDLOG  HI_INFO_AO
#endif

#define IPC_ACK_CLIENT_WRITE        (0xAA55)
#define IPC_ACK_SERVER_WRITE        (0x55AA)
#define IPC_PAYLOAD_MAX_BYTES       (0x200)

#define IPC_CLIENT_CONNECT_DELAYMS   (20)
#define IPC_CLIENT_CONNECT_MAXTIMES  (5)
#define IPC_SERVER_LISTEN_MAXCONNECT (32)
#define INVALID_SOCKET_VALUE         (0xffffffff)

typedef enum
{
    CMD_SOURCE_APPLYID = 0x00,          /* 0x00 */
    CMD_SOURCE_DEAPPLYID,               /* 0x01 */
    CMD_SOURCE_CHECKISMEDIACREATED,     /* 0x02 */
    CMD_SOURCE_CREATETRACKWITHID,       /* 0x03 */
    CMD_SOURCE_DESTROYTRACKWITHID,      /* 0x04 */
    CMD_SOURCE_SETTRACKATTR,            /* 0x05 */
    CMD_SOURCE_GETTRACKATTR,            /* 0x06 */
    CMD_SOURCE_CREATETRACK,             /* 0x07 */
    CMD_SOURCE_DESTROYTRACK,            /* 0x08 */
    CMD_SOURCE_STARTTRACK,              /* 0x09 */
    CMD_SOURCE_STOPTRACK,               /* 0x0A */
    CMD_SOURCE_PAUSETRACK,              /* 0x0B */
    CMD_SOURCE_FLUSHTRACK,              /* 0x0C */
    CMD_SOURCE_SETTARGETPTS,            /* 0x0D */
    CMD_SOURCE_SETREPEATTARGETPTS,      /* 0x0E */
    CMD_SOURCE_GETTRACKPTS,             /* 0x0F */
    CMD_SOURCE_DROPTRACKSTREAM,         /* 0x10 */
    CMD_SOURCE_DROPFRAME,               /* 0x11 */
    CMD_SOURCE_SETSYNCMODE,             /* 0x12 */
    CMD_SOURCE_GETDELAYMS,              /* 0x13 */
    CMD_SOURCE_SETEOSFLAG,              /* 0x14 */
    CMD_SOURCE_GETEOSFLAG,              /* 0x15 */
    CMD_SOURCE_GETCAPABILITY,           /* 0x16 */
    CMD_SOURCE_SETTRACKCONFIG,          /* 0x17 */
    CMD_SOURCE_GETTRACKCONFIG,          /* 0x18 */
    CMD_SOURCE_SETTRACKCMD,             /* 0x19 */
    CMD_SOURCE_GETBUFFERSTATUS,         /* 0x1A */
    CMD_SOURCE_CHECKNEWEVENT,           /* 0x1B */
    CMD_SOURCE_ACTIVETRACK,             /* 0x1C */
    CMD_SOURCE_SETTRACKMUTE,            /* 0x1D */
    CMD_SOURCE_SETTRACKPRESCALE,        /* 0x1E */
    CMD_SOURCE_GETRENDERALLINFO,        /* 0x1F */
    CMD_SOURCE_SETTRACKSOURCE,          /* 0x20 */
    CMD_SOURCE_GETSTREAMINFO,           /* 0x21 */

    CMD_DONE,
} COMMAND_E;

typedef struct
{
    HI_U32    u32AckData;
    HI_U32    u32Command;
    HI_BOOL   bNeedReply;    //client write
    HI_BOOL   bReply;        //client write
    HI_S32    s32ReplyValue; //server write

    HI_UNF_SND_E enSound;
    HI_HANDLE    hTrack;
    HI_HANDLE    hExtTrack;

    HI_U32       aPayload[IPC_PAYLOAD_MAX_BYTES];
} IPC_CMM;

HI_S32  IPC_Common_CreateServer(HI_S32* ps32ServerFd, HI_CHAR* Path);
HI_VOID IPC_Common_DestroyServer(HI_S32 s32ServerFd);
HI_S32  IPC_Common_AcceptServer(HI_S32 s32ServerFd, HI_S32* ps32ClientFd);
HI_S32  IPC_Common_SetupServerCommThread(pthread_t* pThreadId, HI_S32* ps32ClientFd, HI_VOID*(*HiClientIpcthread)(HI_VOID*));
HI_S32  IPC_Common_TryCreateClient(HI_VOID);
HI_VOID IPC_Common_TryDestroyClient(HI_VOID);
HI_S32  IPC_Common_SetClientCmd(IPC_CMM* pstIPCcmm);
HI_S32  IPC_Common_GetClientCmd(IPC_CMM* pstIPCcmm);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
