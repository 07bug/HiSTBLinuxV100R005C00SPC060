/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_mutex.h
 * Description   : posix�̻߳��������䣬ͷ�ļ�
 *
 * History       :
 * Version     Date       DefectNum    Modification:
 * 1.1         2009-2-27  NULL         Created file
 *
 ******************************************************************************/

#include "hi_type.h"
#include "hi_adp_thread.h"

#ifndef __HI_ADPT_MUTEX_H__
#define __HI_ADPT_MUTEX_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*************************** Structure Definition ****************************/
/** @defgroup hi_adpt_mutex_structure mutex��������ݽṹ
 *  @ingroup H2
 *  @brief ��ϸ����mutex�����ģ������ݽṹ
 *  @{  */

/*----------------------------------------------*
 * types
 *----------------------------------------------*/
typedef HI_VOID *HI_ThreadDescr;
/**< Fast locks (not abstract because mutexes and conditions aren't abstract). */
typedef struct HIpthread_fastlock{
    HI_S32 status;      /**< "Free" or "taken" or head of waiting list */
    HI_S32 spinlock;    /**< Used by compare_and_swap emulation. Also,           adaptive SMP lock stores spin count here. */
}HI_ThreadFastLock_S;

/**< pthread_mutex_t */
#if HI_OS_TYPE == HI_OS_LINUX
typedef struct HI_mutex_t
{
    HI_S32 m_reserved;          /**< Reserved for future use */
    HI_S32 m_count;             /**< Depth of recursive locking */
    HI_ThreadDescr m_owner;     /**< Owner thread (if recursive or errcheck) */
    HI_S32 m_kind;              /**< Mutex kind: fast, recursive or errcheck */
    HI_ThreadFastLock_S m_lock; /**< Underlying fast lock */
} HI_ThreadMutex_S;
#elif HI_OS_TYPE == HI_OS_WIN32

typedef struct hiLIST_ENTRY_S
{
   struct __LIST_ENTRY *Flink;
   struct __LIST_ENTRY *Blink;
} HI_LIST_ENTRY_S;

typedef struct HI_RTL_CRITICAL_SECTION_DEBUG
{
    HI_S16 Type;
    HI_S16   CreatorBackTraceIndex;
    struct HI_RTL_CRITICAL_SECTION *CriticalSection;
    HI_LIST_ENTRY_S ProcessLocksList;
    HI_S32 EntryCount;
    HI_S32 ContentionCount;
    HI_S32 Spare[ 2 ];
} HI_CRITICAL_SECTION_DEBUG;

typedef struct HI_RTL_CRITICAL_SECTION
{
    HI_CRITICAL_SECTION_DEBUG DebugInfo;
    HI_S32 LockCount;
    HI_S32 RecursionCount;
    HI_VOID *OwningThread;        /* from the thread's ClientId->UniqueThread*/
    HI_VOID * LockSemaphore;
    HI_S32 SpinCount;
} HI_ThreadMutex_S;

#else
#error YOU MUST DEFINE HI OS TYPE WIN32 OR LINUX !
#endif

typedef enum
{
    HI_MUTEX_TIMED_NP,
    HI_MUTEX_RECURSIVE_NP,
    HI_MUTEX_ERRORCHECK_NP,
    HI_MUTEX_ADAPTIVE_NP
} HI_MutexType_E;

/*----------------------------------------------*
 * macros
 *----------------------------------------------*/

#define LT_SPINLOCK_INIT 0
#define LOCK_INITIALIZER { 0, LT_SPINLOCK_INIT }

#define HI_MUTEX_INITIALIZER  {0, 0, 0, HI_MUTEX_TIMED_NP, LOCK_INITIALIZER}
#define HI_RECURSIVE_MUTEX_INITIALIZER_NP {0, 0, 0, HI_MUTEX_RECURSIVE_NP, LOCK_INITIALIZER}
#define HI_ERRORCHECK_MUTEX_INITIALIZER_NP {0, 0, 0, HI_MUTEX_ERRORCHECK_NP, LOCK_INITIALIZER}
#define HI_ADAPTIVE_MUTEX_INITIALIZER_NP {0, 0, 0, HI_MUTEX_ADAPTIVE_NP, LOCK_INITIALIZER}

/** @} */  /*! <!-- Structure Definition end */
/******************************* API declaration *****************************/
/** @defgroup hi_adpt_mutex_api widget�ؼ�api�ӿ�
*   @ingroup H1
*   @brief ��ϸ����widgetģ���API����
*   @{  */

/**
\brief ��ʼ���߳���,�ýӿڿ���ʹ��"HI_MUTEX_INITIALIZER"�����,��:HI_ThreadMutex_S *mutex=HI_MUTEX_INITIALIZER;
\attention \n
��
\param[in] mutex �߳������
\param[in] mutex_attr �߳�������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32  HI_MutexInit (HI_ThreadMutex_S *mutex,const HI_ThreadAttr_S *mutex_attr);

/**
\brief �߳������ٽӿ�
\attention \n
��
\param[in] mutex �߳������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_MutexDestroy (HI_ThreadMutex_S *mutex);

/**
\brief ��ͼ�����������ʵ��������ýӿ�������������������
\attention \n
��
\param[in] mutex �߳������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_MutexTryLock (const HI_ThreadMutex_S *mutex) ;

/**
\brief �߳���
\attention \n
��
\param[in] mutex �߳������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_MutexLock (HI_ThreadMutex_S *mutex);

/**
\brief �����ӿ�
\attention \n
��
\param[in] mutex �߳������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_MutexUnLock (HI_ThreadMutex_S *mutex);

/*****************************************************************************
 * Function     : HI_MutexRecursiveInit
 * Description  : ��ʼ��һ���ݹ���
 * Input        : HI_ThreadMutex_S *mutex,�߳������
 * Input        : HI_ThreadAttr_S *mutex_attr,�߳�������
 * Output       : None
 * Return       : HI_S32
 * Data Accessed: None
 * Data Updated : None
 * Others       : None
 *****************************************************************************/
HI_S32 HI_MutexRecursiveInit(HI_ThreadMutex_S *mutex, HI_ThreadAttr_S *mutex_attr);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* __HI_ADPT_MUTEX_H__ */
