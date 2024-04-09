#ifndef __VTOP_MSG_INTERFACE_DEFS_H__
#define __VTOP_MSG_INTERFACE_DEFS_H__

#ifdef    __cplusplus
extern "C"{
#endif

#include "hi_type.h"
#include <sys/types.h>

/* ÿ����Ϣ������ߴ� */
#define VTOP_MSG_MAX_MSG_SIZE    4096

#define VTOP_MSG_MAX_NAME_LEN    16
#define VTOP_MSG_MAX_TASK_NAME_LEN    VTOP_MSG_MAX_NAME_LEN

typedef char VTOP_MSG_TASKNAME[VTOP_MSG_MAX_TASK_NAME_LEN];

/* ID & �������: ��0��ʼ��-1��Ч */
typedef int VTOP_TASK_ID;
#define VTOP_INVALID_TASK_ID        (-1)

/* msg id: ��0��ʼ�����������������0xffffffffffffffffΪ��Ч */
typedef unsigned int  VTOP_MSG_ID;

/* �û��Զ�����Ϣ����: 0x00000000 ~ 0x7FFFFFFF    */
/* ϵͳ������Ϣ����:   0x80000000 ~ 0xFFFFFFFE    */
typedef unsigned int VTOP_MSG_TYPE;
#define VTOP_INVALID_MSG_TYPE    (0xFFFFFFFF)
#define VTOP_MSG_TYPE_SYS(msgType)    (msgType | 0x80000000)
#define VTOP_MSG_TYPE_USER(msgType)    (msgType & 0x7fffffff)

/* ============== ��Ϣ���ȼ� ============== */
typedef enum
{
    VTOP_MSG_PRIO_LOW     = 0,
    VTOP_MSG_PRIO_MID   = 1,
    VTOP_MSG_PRIO_HIGH     = 2,

    VTOP_MSG_PRIO_BUTT
}VTOP_MSG_E_Prio;

#define VTOP_MSG_PRIO_DEFAULT VTOP_MSG_PRIO_MID

/* ============== ��Ϣ������ ============== */
typedef enum
{
    VTOP_MSG_BL_0     = 0,        /*256  Bytes*/
    VTOP_MSG_BL_1   = 1,        /*512  Bytes*/
    VTOP_MSG_BL_2     = 2,        /*1024 Bytes*/
    VTOP_MSG_BL_3   = 3,        /*4096 Bytes*/
    VTOP_MSG_BL_BUTT
}VTOP_MSG_E_BufferLevel;

typedef size_t VTOP_MSG_BLOCKNUM[VTOP_MSG_BL_BUTT];

/* ============== ��Ϣ FLAG ============== */
#define VTOP_MSG_FLG_SYNC          0x00000001  /* ͬ����־λ */
#define VTOP_MSG_FLG_ASYNC         0x00000002  /* �첽��־λ */
#define VTOP_MSG_FLG_ACK        0x00000008  /* Ӧ���־λ */
#define VTOP_MSG_FLG_RESP       0x00000010  /* ͬ����Ϣ��Ӧ��־ */

#define VTOP_MSG_FLG_P2P          0x00000100  /* ��Ե���Ϣ */
#define VTOP_MSG_FLG_SP         0x00000200  /* ������Ϣ */
/* 0x00001000 ~ 0x00008000 reserved for system */

#define VTOP_MSG_isSyncMsg(flag)    ((flag) & VTOP_MSG_FLG_SYNC)
#define VTOP_MSG_isASyncMsg(flag)   ((flag) & VTOP_MSG_FLG_ASYNC)
#define VTOP_MSG_isRespMsg(flag)    ((flag) & VTOP_MSG_FLG_RESP)

#define VTOP_MSG_isP2PMsg(flag)     ((flag) & VTOP_MSG_FLG_P2P)
#define VTOP_MSG_isSPMsg(flag)      ((flag) & VTOP_MSG_FLG_SP)

/* ============== �����붨�� ============== */

/******************************************************************************
|----------------------------------------------------------------|
| 1 |   APP_ID   |   MOD_ID    | ERR_LEVEL |   ERR_ID            |
|----------------------------------------------------------------|
|<--><--7bits----><----8bits---><--3bits---><------13bits------->|
******************************************************************************/

//#define SCP_APPID  (0x80L | 0x22L)    /* 34=0x22, including errid flag "1"=0x80UL */
//#define SCP_MSG_MODID    0x01L
#define SCP_APP_MOD_ID    (0xA2010000)    /* =(SCP_APPID | SCP_MSG_MODID) */

/* ����8���ȼ�*/
typedef enum
{
    VTOP_LOG_LEVEL_DEBUG = 0,  /* debug-level                                  */
    VTOP_LOG_LEVEL_INFO,       /* informational                                */
    VTOP_LOG_LEVEL_NOTICE,     /* normal but significant condition             */
    VTOP_LOG_LEVEL_WARNING,    /* warning conditions                           */
    VTOP_LOG_LEVEL_ERROR,      /* error conditions                             */
    VTOP_LOG_LEVEL_CRIT,       /* critical conditions                          */
    VTOP_LOG_LEVEL_ALERT,      /* action must be taken immediately             */
    VTOP_LOG_LEVEL_FATAL,      /* just for compatibility with previous version */

    VTOP_LOG_LEVEL_BUTT
} VTOP_LOG_ERRLEVEL_E;

#if 0
#define SCP_DEF_ERR(level, errid) \
    ( SCP_APP_MOD_ID | ((level)<<13) | (errid) )
#endif

#define SCP_DEF_ERR(level, errid) \
    ((int)SCP_APP_MOD_ID|((((int)(level))&0x00000007)<<13)|(((int)(errid))&0x00001FFF))

typedef enum
{
    VTOP_MSG_ERRID_GENERAL=0x000,        /* ͨ�ô���                     */
    VTOP_MSG_ERRID_UNKNOWN,                /* δ֪����                     */
    VTOP_MSG_ERRID_NOMEM,                /* �����ڴ�ʧ��                 */
    VTOP_MSG_ERRID_NULLPTR,                /* ��ָ��                         */
    VTOP_MSG_ERRID_INVALIDPARA,            /* ��Ч����(��ָ�����)         */
    VTOP_MSG_ERRID_VERSION,             /* �汾�������̲�ƥ��         */

    VTOP_MSG_ERRID_NOSHMMEM=0x100,        /* ���빲���ڴ�ʧ��             */
    VTOP_MSG_ERRID_SHMEXIST,            /* ���빲���ڴ��Ѿ�����         */
    VTOP_MSG_ERRID_SHMNOTEXIST,            /* ���빲���ڴ治����             */
    VTOP_MSG_ERRID_SHMATTACH,            /* �ҽӹ����ڴ治����             */
    VTOP_MSG_ERRID_SEMINIT,                /* ��ʼ���ź���ʧ��                */
    VTOP_MSG_ERRID_SEMGET,                /* ��ȡ�ź���ʧ��                */
    VTOP_MSG_ERRID_SEMDESTROY,            /* �����ź���ʧ��                */
    VTOP_MSG_ERRID_SEMLOCK,                /* �����ź���ʧ��                */
    VTOP_MSG_ERRID_SEMUNLOCK,            /* �����ź���ʧ��                */

    VTOP_MSG_ERRID_DSEXIST=0x200,        /* �߳������Ѿ�����             */
    VTOP_MSG_ERRID_DSNOTEXIST,            /* �߳����ݲ�����                 */
    VTOP_MSG_ERRID_DSSMALLMEM,            /* �û��������ڴ��С             */

    VTOP_MSG_ERRID_PROCEXIST=0x300,        /* ��Ϣ��������Ѿ�����         */
    VTOP_MSG_ERRID_PROCNOTEXIST,        /* ��Ϣ������򲻴���             */
    VTOP_MSG_ERRID_PROCMSGBUFFULL,        /* ��Ϣ���������Ϣ���ջ�������    */
    VTOP_MSG_ERRID_PROCSTART,           /* ��Ϣ�����������ʧ��    */

    VTOP_MSG_ERRID_TASKEXIST=0x400,        /* ��Ϣ�����Ѿ�����             */
    VTOP_MSG_ERRID_TASKNOTEXIST,        /* ��Ϣ���񲻴���                 */
    VTOP_MSG_ERRID_TASKFULL,            /* �ﵽ��Ϣ���������ֵ         */

    VTOP_MSG_ERRID_SUBEXIST=0x600,        /* ���ı��Ѿ�����                 */
    VTOP_MSG_ERRID_SUBNOTEXIST,            /* ���ı�����                 */
    VTOP_MSG_ERRID_SUBFULL,                /* �ﵽ���ı������ֵ             */
    VTOP_MSG_ERRID_SUBMEMBERFULL,        /* ���ı��г�Ա����                */
    VTOP_MSG_ERRID_NOTSUBMEMBER,        /* �Ƕ�����                      */

    VTOP_MSG_ERRID_MSGBUFFULL=0x700,    /* �Է���Ϣ���ջ�������         */
    VTOP_MSG_ERRID_TIMEOUT,                /* ���ͳ�ʱ                     */
    VTOP_MSG_ERRID_RESPTIMEOUT,         /* ������Ӧ��Ϣ��ʱ             */
    VTOP_MSG_ERRID_MSGRCV,                /* ��Ϣ����ʧ��                    */
    VTOP_MSG_ERRID_MSGSND,                /* ��Ϣ����ʧ��                    */
    VTOP_MSG_ERRID_MSGSIZE,             /* ��Ϣ��С�Ƿ������ܳ����������*/
    VTOP_MSG_ERRID_CLOSECONN,           /* �ر����ӣ���������*/

    VTOP_MSG_ERRID_BUTT
}VTOP_MSG_E_ERRID;

// 0xA8018000
#define VTOP_MSG_ERR_GENERAL         SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_GENERAL)
#define VTOP_MSG_ERR_UNKNOWN         SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_UNKNOWN)
#define VTOP_MSG_ERR_NOMEM            SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_NOMEM)
#define VTOP_MSG_ERR_NULLPTR        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_NULLPTR)
#define VTOP_MSG_ERR_INVALIDPARA    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_INVALIDPARA)
#define VTOP_MSG_ERR_VERSION        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_VERSION)

// 0xA8018100
#define VTOP_MSG_ERR_NOSHMMEM        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_NOSHMMEM)
#define VTOP_MSG_ERR_SHMEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SHMEXIST)
#define VTOP_MSG_ERR_SHMNOTEXIST    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SHMNOTEXIST)
#define VTOP_MSG_ERR_SHMATTCH        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SHMATTACH)
#define VTOP_MSG_ERR_SEMINIT        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMINIT)
#define VTOP_MSG_ERR_SEMGET            SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMGET)
#define VTOP_MSG_ERR_SEMDESTROY        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMDESTROY)
#define VTOP_MSG_ERR_SEMLOCK        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMLOCK)
#define VTOP_MSG_ERR_SEMUNLOCK        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SEMUNLOCK)

// 0xA8018200
#define VTOP_MSG_ERR_DSEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_DSEXIST)
#define VTOP_MSG_ERR_DSNOTEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_DSNOTEXIST)
#define VTOP_MSG_ERR_DSSMALLMEM        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_DSSMALLMEM)

// 0xA8018300
#define VTOP_MSG_ERR_PROCEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_PROCEXIST)
#define VTOP_MSG_ERR_PROCNOTEXIST    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_PROCNOTEXIST)
#define VTOP_MSG_ERR_PROCMSGBUFFULL    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_PROCMSGBUFFULL)
#define VTOP_MSG_ERR_PROCSTART      SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_PROCSTART)

// 0xA8018400
#define VTOP_MSG_ERR_TASKEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_TASKEXIST)
#define VTOP_MSG_ERR_TASKNOTEXIST    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_TASKNOTEXIST)
#define VTOP_MSG_ERR_TASKFULL        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_TASKFULL)

// 0xA8018600
#define VTOP_MSG_ERR_SUBEXIST        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SUBEXIST)
#define VTOP_MSG_ERR_SUBNOTEXIST    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SUBNOTEXIST)
#define VTOP_MSG_ERR_SUBFULL        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SUBFULL)
#define VTOP_MSG_ERR_SUBMEMBERFULL    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_SUBMEMBERFULL)
#define VTOP_MSG_ERR_NOTSUBMEMBER    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_NOTSUBMEMBER)

// 0xA8018700
#define VTOP_MSG_ERR_MSGBUFFULL        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_MSGBUFFULL)
#define VTOP_MSG_ERR_TIMEOUT        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_TIMEOUT)
#define VTOP_MSG_ERR_RESPTIMEOUT    SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_RESPTIMEOUT)
#define VTOP_MSG_ERR_MSGRCV            SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_MSGRCV)
#define VTOP_MSG_ERR_MSGSND            SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_MSGSND)
#define VTOP_MSG_ERR_MSGSIZE        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_MSGSIZE)
#define VTOP_MSG_ERR_CLOSECONN        SCP_DEF_ERR(VTOP_LOG_LEVEL_ERROR, VTOP_MSG_ERRID_CLOSECONN)

/* ============== ��Ϣ�ṹ ============== */
typedef struct
{
    VTOP_TASK_ID    sndTaskId;    // ��Ϣ������ID
    VTOP_TASK_ID    rcvTaskId;    // ��Ϣ������ID
    VTOP_MSG_TYPE   msgType;    // ��Ϣ����������
    VTOP_MSG_ID        msgID;        // ϵͳ���ã��û�ֻ��

    unsigned int     ulPrio;        // VTOP_MSG_E_Prio����, ��Ϣ���ȼ�����Ϣ���������á�P2Pͬ����Ϣ������Ч.
    unsigned int     ulFlag;        // ��ϵͳ���ã��û�ֻ�������"msg flags"
    unsigned int     ulMsgLen;    // ��Ϣ���ݳ���
    unsigned char   *pMsgBody;    // ��Ϣ����
}VTOP_MSG_S_Block;

/* ============== ��Ϣ��������������� ============== */
typedef struct
{
    unsigned int  ulMaxTask;         /* ��Ϣ���̻����߳����ֵ��0ΪĬ��ֵ      */
    unsigned int  ulMaxSub;          /* ��Ϣ���ı����������0ΪĬ��ֵ      */
    unsigned int  ulMaxMem;             /* ��Ϣϵͳ���õ�����ڴ棺0ΪĬ��ֵ      */
    VTOP_MSG_BLOCKNUM blockNum;     /* ��Ϣϵͳ������������: ȫ0ΪĬ��ֵ   */
}VTOP_MSG_S_Config;

/* ============== ��Ϣ������򷽷����� ============== */
typedef void (*PFUNC_VTOP_MSG_Log)(
        const char *file,             /* ������ļ��������ļ���������·����    */
        const char *function,        /* ����ĺ���                            */
        int line,                /* �����λ�ã����������ļ��е�����    */
        int err,                /* ������                                */
        VTOP_LOG_ERRLEVEL_E err_level,    /* ����ļ���                            */
        const char *perr);            /* ������Ϣ����������ַ������͡�        */

typedef struct
{
    /* msg module log function, implement by user */
    PFUNC_VTOP_MSG_Log pMsgLog;/*del '*' by qushen*/

    // ����������ӿڿ������
}VTOP_MSG_S_ops;

/* ============== ��Ϣ������Ϣ������ ============== */
typedef void (*PFUNC_VTOP_MSG_Handler)(VTOP_MSG_S_Block *pMsg);

/* ============== ��Ϣ�����б� ============== */
typedef struct tag_VTOP_MSG_S_TaskListNode
{
    VTOP_TASK_ID taskId;
    struct tag_VTOP_MSG_S_TaskListNode * pNext;
}VTOP_MSG_S_TaskListNode;

/* ============== �����б� ============== */
typedef struct tag_VTOP_MSG_S_SubListNode
{
    VTOP_MSG_TYPE msgType;
    struct tag_VTOP_MSG_S_SubListNode * pNext;
}VTOP_MSG_S_SubListNode;

/* ʹ����Ϣϵͳ֮ǰ������������Ϣ������� */
int VTOP_MSG_Main(VTOP_MSG_S_Config * pMsgConfig, VTOP_MSG_S_ops * pMsg_ops);

/* ��Ϣ��������쳣�˳���������Ϣϵͳ���õ�ϵͳ��Դ���繲���ڴ棬ϵͳ��Ϣ���е� */
int VTOP_MSG_Destroy(HI_BOOL bExitByForce);

/* ��ʼ����Ϣģ�� */
int  VTOP_MSG_Register(
        const VTOP_MSG_TASKNAME taskName,
        PFUNC_VTOP_MSG_Handler pMsgHandler,
        PFUNC_VTOP_MSG_Log  pTaskLog,
        VTOP_TASK_ID * pTaskId);

/* ��Ϣ�ϲ��ӿڣ�ָ����Ϣ���ͺ���ȡ��Ϣ�������������͵���Ϣ, qushen, 2009-04-24 */
int VTOP_MSG_SetMerge(VTOP_TASK_ID taskId, VTOP_MSG_TYPE msgtype);

/*  ȥ��ʼ����Ϣģ��  */
int VTOP_MSG_UnRegister(VTOP_TASK_ID taskId);

VTOP_TASK_ID VTOP_MSG_GetTaskId(const VTOP_MSG_TASKNAME taskName);
int VTOP_MSG_GetTaskName(VTOP_TASK_ID taskId, VTOP_MSG_TASKNAME taskName);

/*ͬ��Ϣ���ͳ�ʱ����һ�£�timeoutΪ���ʾ�������������ʾ����(>0,������ʱʱ��ms��-1Ϊһֱ����)*/
int VTOP_MSG_GetAndDispatch(
        VTOP_TASK_ID taskId,
        int timeout);

/*---------------------- ��Ϣģʽ1: P2P: Point to Point ----------------------------*/
/* ͬ����Ϣ���� */
int VTOP_MSG_SynSend(
        VTOP_MSG_S_Block *pMsg,
        VTOP_MSG_S_Block** ppMsgResp,
        int timeout);

/* ͬ����Ϣ���������յ���Ϣ��������Ӧ����֮��Ӧ�õ��ñ��ӿ������߷���һ����Ӧ��Ϣ*/
int VTOP_MSG_SendResp(
                VTOP_MSG_S_Block* pMsg,
                VTOP_MSG_S_Block *pMsgResp );

/* ͬ����Ϣ���������յ���Ӧ��Ϣ֮��Ӧ�õ��ñ��ӿ��ͷŻ�Ӧ��Ϣ������ */
int VTOP_MSG_SynRespFree(VTOP_MSG_S_Block * pMsgResp);

/* �첽��Ϣ���� */
int VTOP_MSG_AsynSend(VTOP_MSG_S_Block *pMsg);

/* �û�������ȡ��Ϣ�ӿ� */
int VTOP_MSG_Recv(VTOP_TASK_ID taskId, VTOP_MSG_S_Block **ppMsg, int timeout);

/* ��ȡ��Ϣ����ͷŽӿ� */
int VTOP_MSG_RecvFree(VTOP_MSG_S_Block *pMsg);

/*---------------------- ��Ϣģʽ2: Pub/Sub: Publish/Subscribe ----------------------------*/
// ����ĳ�����͵���Ϣ
int VTOP_MSG_Subscribe(VTOP_TASK_ID taskId, VTOP_MSG_TYPE msgType);

// ȡ��ĳ�����͵���Ϣ����
int VTOP_MSG_UnSubscribe(VTOP_TASK_ID taskId, VTOP_MSG_TYPE msgType);

// ����ĳ�����͵���Ϣ,��Ϣ������pMsg->ulMsgType�и���
int VTOP_MSG_Publish(VTOP_MSG_S_Block *pMsg);

// ���е�subscriber(������)ͨ�� VTOP_MSG_Get ����publisher��������Ϣ.

char* VTOP_MSG_GetVersion(void);

/* ���Խӿ� */
void VTOP_MSG_Show(VTOP_MSG_S_Block * pMsg, const char * file, const char * func, int line);

#define THIS_FILE ((strrchr(__FILE__, '/') ?: __FILE__ - 1) + 1)
#define VTOP_MSG_SHOW(pMsg)    VTOP_MSG_Show(pMsg, THIS_FILE, __FUNCTION__, __LINE__)

#ifdef    __cplusplus
}
#endif

#endif /*  __VTOP_MSG_INTERFACE_DEFS_H__  */
