/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_sem.h
 * Description   : �ź�������ͷ�ļ�
 *
 * History       :
 * Version     Date         DefectNum    Modification:
 * 1.1         2009-2-27    NULL         Created file
 *
 ******************************************************************************/

#ifndef __HI_ADPT_SEM_H__
#define __HI_ADPT_SEM_H__

#include "hi_type.h"
//#include "hi_adp_interface.h"
#include "hi_adp_time.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** @defgroup hi_adpt_sem_structure semģ�����ݽṹ
 *  @ingroup H2
 *  @brief ��ϸ����semģ������ݽṹ
 *  @{  */

/*----------------------------------------------*
 * macros
 *----------------------------------------------*/
#define HI_ADPT_SEM_SIZEOF_SEM_T 16
/*----------------------------------------------*
 * types
 *----------------------------------------------*/
typedef union hiSEM_T
{
  HI_CHAR aszSize[HI_ADPT_SEM_SIZEOF_SEM_T];
  HI_S32  s32Align;
} HI_SEM_T;

/** @} */  /*! <!-- Structure Definition end */
/******************************* API declaration *****************************/
/** @defgroup hi_adpt_sem_api semģ��api�ӿ�
*   @ingroup H1
*   @brief ��ϸ����semģ���API����
*   @{  */

/**
\brief ��ʼ��һ���ź�������linux��ͨ��man sem_init���Ի�ȡ��ϸ��Ϣ
\attention \n
��
\param[in] s32Pshared �Ƿ���̡��̼߳乲��0:����;��0:������
\param[in] u32Value �ź����ĳ�ʼ��ֵ
\param[out] pSem �ź������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_SEM_Init(HI_SEM_T *pSem, HI_S32 s32Pshared, HI_U32 u32Value);

/**
\brief ����һ���ź�������linux��ͨ��man sem_destroy���Ի�ȡ��ϸ��Ϣ
\attention \n
��
\param[in] pSem �ź������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_SEM_Destroy(HI_SEM_T *pSem);

/**
\brief ��һ���ź�����������ź����������򴴽�֮
\attention \n
��
\param[in] pszName �ź�������
\param[in] s32Oflag �ź�����������
\param[in] tMode �ź���������ԣ�����ź����Ѿ����ڣ��ò���������
\param[in] u32Value �ź�����ʼֵ������ź����Ѿ����ڣ��ò���������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_SEM_T * HI_SEM_Open(const HI_CHAR *pszName, HI_S32 s32Oflag,HI_MODE_T tMode,
                       HI_U32 u32Value);

/**
\brief �ر�һ���ź���
\attention \n
��
\param[in] pSem �ź������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_SEM_Close(HI_SEM_T *pSem);

/**
\brief �ȴ�һ���ź���
\attention \n
��
\param[in] pSem �ź������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_SEM_Wait(HI_SEM_T *pSem);

/**
\brief ��ͼ�ȴ�һ���ź�����������ź����Ѿ���ռ����ֱ�ӷ���
\attention \n
��
\param[in] pSem �ź������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_SEM_TryWait(HI_SEM_T *pSem);

/**
\brief ����ʱ���ȴ�һ���ź���������ڹ涨ʱ���ڵȲ����ź�����ֱ�ӷ���
\attention \n
��
\param[in] pSem �ź������
\param[in] pstAbs_timeout �ȴ���ʱʱ��

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_SEM_TimedWait(HI_SEM_T *pSem,const HI_Timespec_S* pstAbs_timeout);

/**
\brief �ͷ�һ���ź���
\attention \n
��
\param[in] pSem �ź������

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_SEM_Post(HI_SEM_T *pSem);

/**
\brief ��ȡ�ź�����ǰֵ
\attention \n
��
\param[in] pSem �ź������
\param[out] ps32Sval �ź�����ֵ

\retval ::HI_SUCCESS
\retval ::HI_ERRCODE

\see \n
��
*/
HI_S32 HI_SEM_Getvalue(HI_SEM_T *pSem,HI_S32* ps32Sval);
/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__HI_ADPT_SEM_H__*/
