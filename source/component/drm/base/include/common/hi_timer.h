/***********************************************************
*                      Copyright    , 2009-2050, Hisilicon Tech. Co., Ltd.
*                                   ALL RIGHTS RESERVED
* FileName:  hi_timer.h
* Description:timer�������ͷ�ļ�
*
* History:
* Version   Date               DefectNum     Description
* main\1    2009-3-17          NULL          Create this file.
************************************************************/
#ifndef __HI_TIMER_H__
#define __HI_TIMER_H__

/*include header files*/
#include "hi_type.h"
#include <pthread.h>
#include "petimer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/******************************* API declaration *****************************/
/** @defgroup hi_timer_api timerģ��api�ӿ�
*   @ingroup H1
*   @brief ��ϸ����timerģ���API����
*   @{  */

/**
\brief ����һ��timer
\attention \n
��
\param[in] HI_VOID (*timeout)(HI_VOID *) timer��ʱ�ص�����
\param[in] mode timerģʽ������������:
           a)PETF_AUTO_RESTART:timer��ʱ��ʱ�Զ�������һ��timer��ʱ
           b)PETF_ONE_SHOOT:timer��ʱ��ʱֹͣ
           c)PETF_AUTO_FREE:timer��ʱ��ʱ�Զ�����

\retval ::timer���
\retval ::HI_ERRCODE

\see \n
��
*/
petimer_t  HI_TIMER_Create(HI_VOID (*timeout)(HI_VOID *), HI_S32 mode);

/**
\brief ����һ��timer
\attention \n
��
\param[in] timer timer���

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32  HI_TIMER_Destroy(petimer_t timer);

/**
\brief ȥʹ��һ��timer
\attention \n
��
\param[in] timer timer���

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32  HI_TIMER_Disable(petimer_t timer);

/**
\brief ʹ��һ��timer
\attention \n
��
\param[in] timer timer���
\param[in] msec timerʱ����

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32  HI_TIMER_Enable (petimer_t timer, HI_U32 msec);

/**
\brief ʹ��һ��timer
\attention \n
��
\param[in] timer timer���
\param[in] msec timerʱ����
\param[in] args timer�ص��������������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32  HI_TIMER_EnableEx (petimer_t timer, HI_U32 msec, HI_VOID *args);

/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif  /* __cplusplus */
#endif /*__HI_TIMER_H__*/
