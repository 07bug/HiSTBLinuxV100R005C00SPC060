/******************************************************************************
 Copyright (C), 2015-2025, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : svr_proc.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/24
  Description   : Common apis for hisilicon system.
  History       :
  1.Date        : 2015/08/24
    Author      :
    Modification: Created file

*******************************************************************************/

#ifndef SVR_PROC_H__
#define SVR_PROC_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C"{
#endif /* End of #ifdef __cplusplus */

/*******************************Structure declaration *****************************/
/** @addtogroup     COMMON */
/** @{ */ /** <!--  [COMMON] */

/** Defines user mode proc show buffer */
/**CNcomment: �û�̬PROC buffer���� */
typedef struct hiSVR_PROCSHOW_BUFFER_S
{
    HI_U8* pu8Buf;                  /**<Buffer address*/ /**<CNcomment: Buffer��ַ */
    HI_U32 u32Size;                 /**<Buffer size*/     /**<CNcomment: Buffer��С */
    HI_U32 u32Offset;               /**<Offset*/         /**<CNcomment: ��ӡƫ�Ƶ�ַ */
} SVR_PROCSHOW_BUFFER_S;

/** Proc show function */
/**CNcomment: Proc��Ϣ��ʾ�ص����� */
typedef HI_S32 (* SVR_PROCSHOW_FN)(SVR_PROCSHOW_BUFFER_S * pstBuf, HI_VOID *pPrivData);

/** Proc command function */
/**CNcomment: Proc���ƻص����� */
typedef HI_S32 (* SVR_PROCCMD_FN)(SVR_PROCSHOW_BUFFER_S * pstBuf, HI_U32 u32Argc, HI_U8 *pu8Argv[], HI_VOID *pPrivData);

/** Defines user mode proc entry */
/**CNcomment: �û�̬PROC��ڶ��� */
typedef struct hiSVR_PROCENTRY_S
{
    HI_CHAR *pszEntryName;          /**<Entry name*/            /**<CNcomment: ����ļ��� */
    HI_CHAR *pszDirectory;          /**<Directory name. If null, the entry will be added to /proc/hisi directory*/
                                    /**<CNcomment: Ŀ¼�������Ϊ�գ���������/proc/hisiĿ¼�� */
    SVR_PROCSHOW_FN pfnShowProc;    /**<Proc show function*/    /**<CNcomment: Proc��Ϣ��ʾ�ص����� */
    SVR_PROCCMD_FN pfnCmdProc;      /**<Proc command function*/ /**<CNcomment: Proc���ƻص����� */
    HI_VOID *pPrivData;             /**<Private data*/          /**<CNcomment: Buffer��ַ */
}SVR_PROCENTRY_S;

#ifndef __KERNEL__
#include <time.h>

/**
@brief Register one module to manager. CNcomment:ģ��ע�ᣬ���ڹ��� CNend
@attention Before manager someone module, calling this interface. CNcomment:�������ģ�飬�ô˽ӿ���ע�� CNend
@param[in] pszModuleName The module name CNcomment:ģ������ CNend
@param[in] u32ModuleID   The module ID. CNcomment:ģ��ID CNend
@retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
@retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
@see \n
N/A CNcomment:�� CNend
*/
HI_S32 SVR_MODULE_Register(HI_U32 u32ModuleID, const HI_CHAR * pszModuleName);

/**
@brief Register one moudle by name. CNcomment:ģ��ע�ᣬID��ϵͳ���� CNend
@attention Before manager someone module, calling this interface. CNcomment:�������ģ�飬�ô˽ӿ���ע�� CNend
@param[in] pszModuleName The module name CNcomment:ģ������ CNend
@param[out] pu32ModuleID The module id allocated by system. CNcomment:ϵͳ�����ģ��ID CNend
@retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
@retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
@see \n
N/A CNcomment:�� CNend
*/
HI_S32 SVR_MODULE_RegisterByName(const HI_CHAR * pszModuleName, HI_U32* pu32ModuleID);

/**
@brief UnRegister one module to trace. CNcomment:ģ���Ƴ� CNend
@attention Before stopping to manage someone module, calling this interface. CNcomment:����Ҫ�����ģ��ʱ��ʹ�ô˽ӿ��Ƴ�ģ�� CNend
@param[in] u32ModuleID The module ID. CNcomment:ģ��ID CNend
@param[out] None CNcomment:�� CNend
@retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
@retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
@see \n
N/A CNcomment:�� CNend
*/
HI_S32 SVR_MODULE_UnRegister(HI_U32 u32ModuleID);

/**
@brief User mode proc cretea directory. CNcomment:�û�̬proc����Ŀ¼ CNend
@attention You need register module before calling this API. Only support create one level directory. CNcomment:��Ҫ��ע��ģ�飬ֻ֧�ִ���һ��Ŀ¼ CNend
@param[in] pszName The directory name. CNcomment:Ŀ¼�� CNend
@param[out] None CNcomment:�� CNend
@retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
@retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
@see \n
N/A CNcomment:�� CNend
*/
HI_S32 SVR_PROC_AddDir(const HI_CHAR *pszName);

/**
@brief User mode proc remove directory. CNcomment:�û�̬procɾ��Ŀ¼ CNend
@attention It will return fail if there are entries in the directory. CNcomment:���Ŀ¼�»�������ļ�,����ɾ��ʧ�� CNend
@param[in] pszName The directory name. CNcomment:Ŀ¼�� CNend
@retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
@retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
@see \n
N/A CNcomment:�� CNend
*/
HI_S32 SVR_PROC_RemoveDir(const HI_CHAR *pszName);

/**
@brief User mode proc add entry. CNcomment:�û�̬proc������� CNend
@attention \n
N/A CNcomment: �� CNend
@param[in] u32ModuleID Module ID. CNcomment:ģ��ID CNend
@param[in] pstEntry Parameter of entry. CNcomment:������ڲ��� CNend
@retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
@retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
@see \n
N/A CNcomment:�� CNend
*/
HI_S32 SVR_PROC_AddEntry(HI_U32 u32ModuleID, const SVR_PROCENTRY_S* pstEntry);

/**
@brief User mode proc remove entry. CNcomment:�û�̬procɾ����� CNend
@attention \n
N/A CNcomment: �� CNend
@param[in] u32ModuleID Module ID. CNcomment:ģ��ID CNend
@param[in] pstEntry Parameter of entry. CNcomment:ɾ����ڲ��� CNend
@retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
@retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
@see \n
N/A CNcomment:�� CNend
*/
HI_S32 SVR_PROC_RemoveEntry(HI_U32 u32ModuleID, const SVR_PROCENTRY_S* pstEntry);

/**
@brief User mode proc print function. CNcomment:�û�̬proc��ӡ���ݵĺ��� CNend
@attention \n
N/A CNcomment: �� CNend
@param[in] pstBuf Output buffer parameter. CNcomment:���buffer���� CNend
@param[in] pFmt Format parameter. CNcomment:��ӡ��ʽ������ CNend
@retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
@retval ::HI_FAILURE Failure CNcomment:ʧ�� CNend
@see \n
N/A CNcomment:�� CNend
*/
HI_S32 SVR_PROC_Printf(SVR_PROCSHOW_BUFFER_S *pstBuf, const HI_CHAR *pFmt, ...);

/** @} */ /** <!-- ==== API declaration end ==== */

#endif /* endif __KERNEL__ */
#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */
#endif /* SVR_PROC_H__ */
