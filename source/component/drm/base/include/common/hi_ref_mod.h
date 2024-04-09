/**
 \file
 \brief ģ�鹫������
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author Hisilicon STB Step-2 software group
 \date 2009/03/19
 */

#ifndef __HI_REF_MOD_H__
#define __HI_REF_MOD_H__

#include "hi_type.h"
#include "utils/Logger.h"
#include "hi_unf_version.h"
#if (UNF_VERSION_CODE >= UNF_VERSION(3, 1))
#include "hi_module.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cplusplus */
#endif /* __cplusplus */

/***************************** Macro Definition ******************************/
#if (UNF_VERSION_CODE >= UNF_VERSION(3, 1))
#define HI_MOD_ID_NULL       (HI_ID_USR_START + (0))     /** ��ʼmod id */
#else
#define HI_MOD_ID_NULL       (0xB0)                      /** ��ʼmod id */
#endif
#define HI_MOD_MAX_NUM       (HI_MOD_ID_NULL + (100))    /** ���mod���� */

#define HI_MOD_INVALID_ID    (-1)    /** �Ƿ�mod id */
#define HI_MOD_NAME_LEN      (32)    /** mod�����ֽ��� */
#define HI_MSG_APPID         (0x0)
#define HI_DEF_MSGTYPE(mid, MSYTYPE) \
    ( ((HI_MSG_APPID)<<24) | (((HI_S32)mid) << 16 ) | (HI_S32)(MSYTYPE) )

/******************************* API declaration *****************************/

/**
\brief ����ģ��IDȡģ����
\attention \n
��
\param[in] u32ModID ģ��ID

\retval ::ģ����
\retval ::���u32ModID�Ƿ�,���ؿ��ַ���""

\see \n
��
*/
const HI_CHAR * HI_MOD_GetNameById(HI_U32 u32ModID);

/**
\brief ����ģ��IDȡģ����
\attention \n
��
\param[in] pszModName ģ������
\param[out] pu32ModId ��ȡ����mod id

\retval ::�ɹ���HI_SUCCESS
\retval ::ʧ�ܣ�HI_FAILURE

\see \n
��
*/
HI_S32 HI_MOD_GetIdByName(HI_CHAR *pszModName, HI_U32 *pu32ModId);

/**
\brief ע��ģ��id
\attention \n
��
\param[in] u32ModId ģ��ID���ϲ㶨���modid,��Χ0-(HI_MOD_MAX_NUM-1)
\param[in] pszModName ģ������

\retval ::�ɹ���HI_SUCCESS
\retval ::ʧ�ܣ�HI_FAILURE

\see \n
��
*/
HI_S32 HI_MOD_Register(HI_U32 u32ModId, HI_CHAR* pszModName);

/** ע��mod */
#define REG_MOD(MODID, MODNAME) \
do { \
    HI_S32 ret = HI_MOD_Register(MODID, #MODNAME); \
    if (HI_SUCCESS != ret) \
    { \
        HI_LOGE("ret = %d", ret); \
    } \
} while (0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__HI_REF_MOD_H__*/
