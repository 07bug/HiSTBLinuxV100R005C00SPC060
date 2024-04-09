/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_thread.h
 * Description   : �߳�����ͷ�ļ�
 *
 * History       :
 * Version     Date        DefectNum    Modification:
 * 1.1         2009-2-27   NULL         Created file
 *
 ******************************************************************************/

#ifndef __HI_ADPT_THREAD_H__
#define __HI_ADPT_THREAD_H__

#include "hi_type.h"
#include <stdarg.h>
#include "hi_adp_interface.h"

#if HI_OS_TYPE == HI_OS_LINUX
#include <errno.h>
#elif HI_OS_TYPE == HI_OS_WIN32
#else
#error YOU MUST DEFINE HI OS TYPE HI_OS_TYPE == HI_OS_WIN32 OR HI_OS_LINUX !
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*************************** Structure Definition ****************************/
/** @defgroup hi_adpt_thread_structure threadģ�����ݽṹ
 *  @ingroup H2
 *  @brief ��ϸ����threadģ������ݽṹ
 *  @{  */

/*----------------------------------------------*
 * macros
 *----------------------------------------------*/

/*----------------------------------------------*
 * types
 *----------------------------------------------*/

typedef HI_U32 HI_Pthread_T;

#define HI_ERR_OSCALL_ERROR  (-1)
#define HI_INFINITE            0xFFFFFFFF
typedef HI_VOID * (*HI_ThreadFun)(HI_VOID *);
/* Data structure to describe a process' schedulability.  */
typedef struct HI_sched_param
{
    HI_S32 sched_priority;
}HI_SchedParam_S;

/* Attributes for threads.  */
typedef struct HIpthread_attr_s
{
    HI_S32 detachstate;
    HI_S32 schedpolicy;
    HI_SchedParam_S schedparam;
    HI_S32 inheritsched;
    HI_S32 scope;
    HI_SIZE_T guardsize;
    HI_S32 stackaddr_set;
    HI_VOID *stackaddr;
    HI_SIZE_T stacksize;
} HI_ThreadAttr_S;

/*�����������ȼ�*/
typedef enum hiVpriority_which
{
    HI_PRIO_PROCESS = 0,             /* WHO is a process ID.  */
    HI_PRIO_PGRP = 1,                /* WHO is a process group ID.  */
    HI_PRIO_USER = 2                 /* WHO is a user ID.  */
}HI_E_Which;

typedef enum hiVrusage_who
{
    /* The calling process.  */
    HI_RUSAGE_SELF = 0,

    /* All of its terminated child processes.  */
    HI_RUSAGE_CHILDREN = -1,

    /* Both.  */
    HI_RUSAGE_BOTH = -2
}HI_E_Who;

/*����errno*/
HI_S32 HI_GetLastErr(HI_VOID);
/*����errno*/
HI_VOID HI_SetLastErr(HI_S32 newErrNo);

/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/
/*----------------------------------------------*
 * ���̲���
 *----------------------------------------------*/
//HI_S32 HI_Execv(const HI_CHAR *path, HI_CHAR *const argv[]);
//HI_S32 HI_Execvp(const HI_CHAR *file, HI_CHAR *const argv[]);
HI_S32 HI_Waitpid(HI_PID_T pid,  HI_S32 *status, HI_S32 options);

#ifdef HI_OS_SUPPORT_UCLINUX
#define HI_Fork vfork
#else
HI_PID_T HI_Fork(HI_VOID);
#endif
HI_PID_T HI_Wait(const HI_S32 *status);

#define HI_REBOOT_CMD_RESTART        0x01234567
#define HI_REBOOT_CMD_HALT           0xCDEF0123
#define HI_REBOOT_CMD_CAD_ON         0x89ABCDEF
#define HI_REBOOT_CMD_CAD_OFF        0x00000000
#define HI_REBOOT_CMD_POWER_OFF      0x4321FEDC
#define HI_REBOOT_CMD_RESTART2       0xA1B2C3D4

/** @} */  /*! <!-- Structure Definition end */
/******************************* API declaration *****************************/
/** @defgroup hi_adpt_thread_api semģ��api�ӿ�
*   @ingroup H1
*   @brief ��ϸ����threadģ���API����
*   @{  */

/**
\brief ��ʼ��һ���߳�
\attention \n
��
\param[in] attr �߳�����

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_PthreadAttrInit(HI_ThreadAttr_S *attr);

/**
\brief ����һ���߳�
\attention \n
��
\param[in] attr �߳�����

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_PthreadAttrDestroy(HI_ThreadAttr_S *attr);

/**
\brief �����̵߳ķ�������
\attention \n
��
\param[in] attr �߳�����
\param[in] detachstate �������ԣ���Ϸ�ֵ����������:
            a)PTHREAD_CREATE_DETACHED���Է���״̬�����߳�
            b)PTHREAD_CREATE_JOINABLE�����������߳�

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_PthreadAttrSetdetachstate(HI_ThreadAttr_S *attr, HI_S32 detachstate);

/**
\brief ���õ�ǰ�̵߳�ȡ��ʹ������
\attention \n
��
\param[in] state �µ�Ҫ���õ�ȡ��ʹ�����ԣ�ȡ��״̬ʹ��������:PTHREAD_CANCEL_ENABLE��PTHREAD_CANCEL_DISABLE.
\param[out] oldstate ��ǰ��ȡ��ʹ������
\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_PthreadSetCancelState(HI_S32 state, HI_S32 *oldstate);

/**
\brief ���õ�ǰ�̵߳�ȡ����������
\attention \n
��
\param[in] state �µ�Ҫ���õ�ȡ���������ԣ�ȡ������������:PTHREAD_CANCEL_DEFERRED��PTHREAD_CANCEL_ASYNCHRONOUS.
\param[out] oldstate ��ǰ��ȡ��ʹ������
\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_PthreadSetCancelType(HI_S32 type, HI_S32 *oldtype);

/**
\brief ��ָ�����̴߳��ڷ���״̬
\attention \n
��
\param[in] th �߳̾��

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_PthreadDetach (HI_Pthread_T th) ;

HI_S32 HI_GetPriority(HI_S32 which, HI_S32 who);

HI_S32 HI_SetPriority(HI_S32 which, HI_S32 who, HI_S32 prio);

/**
\brief ����һ���߳�
\attention \n
��
\param[in] attr �߳�����
\param[in] start_routine �߳���ʼִ�к���
\param[in] arg start_routine�����������
\param[out] threadp �߳̾��

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32  HI_PthreadCreate (HI_Pthread_T *threadp,
                          const HI_ThreadAttr_S *attr,
                          HI_ThreadFun start_routine,
                          HI_VOID *arg) ;

/**
\brief ��ȡ��ǰ�̵߳ľ��
\attention \n
��
\param[in] attr �߳�����

\retval ::��ǰ�߳̾��

\see \n
��
*/
HI_Pthread_T  HI_PthreadSelf (HI_VOID);

/**
\brief �߳��˳�
\attention \n
��
\param[in] retVal �߳���ֹ��

\retval  \n
��

\see \n
��
*/
HI_VOID HI_PthreadExit ( HI_VOID* retVal);

/**
\brief ȡ��ͬһ�����е������߳�
\attention \n
��
\param[in] thread �߳̾��

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_PthreadCancel(HI_Pthread_T thread);

/**
\brief �����ȴ�ָ�����̷߳��ػ�ȡ��
\attention \n
��
\param[in] ��

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_PthreadJoin (HI_Pthread_T th, HI_VOID **thread_return);

/**
\brief �ӳ�ָ��������
\attention \n
��
\param[in] seconds ����

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_U32 HI_Sleep(HI_U32 seconds);

/**
\brief �ӳ�ָ���ĺ�����
\attention \n
��
\param[in] seconds ������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_U32 HI_SleepMs(HI_U32 ms);

/*��ȡ��ǰ�߳�ID*/
HI_U32 HI_GetPID(HI_VOID);

/*�˳�*/
HI_VOID HI_Exit(HI_S32 status);

HI_S32 HI_Kill(HI_PID_T pid, HI_S32 sig);

HI_S32 HI_System(HI_CHAR *cmd);

/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#endif /* __HI_ADPT_THREAD_H__ */
