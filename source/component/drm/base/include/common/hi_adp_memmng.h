/******************************************************************************
 *
 *             Copyright 2009 - 2009, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 *
 ******************************************************************************
 * File Name     : hi_adp_memmng.h
 * Description   : �ڴ����ͷ�ļ�
 *
 * History       :
 * Version     Date        DefectNum    Modification:
 * 1.1         2009-2-27   NULL         Created file
 *
 ******************************************************************************/
#ifndef __HI_ADP_MEMMNG_H__
#define __HI_ADP_MEMMNG_H__

#include "hi_type.h"
#include "hi_unf_version.h"
#include "hi_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

//#define HI_MEMORY_DEBUG
#ifdef HI_ADVCA_FUNCTION_RELEASE
#undef HI_MEMORY_DEBUG
#endif

/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/

/** @defgroup hi_adpt_memmng_api �ڴ���������api�ӿ�
*   @ingroup H1
*   @brief ��ϸ�����ڴ����������API����
*   @{  */

/**
\brief �����ڴ�
\attention \n
��
\param[in] u32ModId ģ��ID
\param[in] u32Size �������ڴ�Ĵ�С
\param[in] pszFileName ���øýӿڵ��ļ���������ʹ��"__FILE__"
\param[in] u32LineNo ���øýӿڵ��ļ������У�����ʹ��"__LINE__"

\retval ::���뵽���ڴ��׵�ַ
\retval ::HI_NULL �����ڴ�ʧ��

\see \n
��
*/
HI_VOID *HI_MemMng_MallocD(const HI_U32 u32ModId,const HI_U32 u32Size,
                           const HI_CHAR *pszFileName, const HI_U32 u32LineNo);

/**
\brief �ͷ��ڴ�
\attention \n
��
\param[in] u32ModId ģ��ID
\param[in] pvMemAddr �ڴ��׵�ַ
\param[in] pszFileName ���øýӿڵ��ļ���������ʹ��"__FILE__"
\param[in] u32LineNo ���øýӿڵ��ļ������У�����ʹ��"__LINE__"

\retval ::HI_SUCCESS �ͷųɹ�
\retval ::HI_LOG_EPAERM ģ��ID����
\retval ::HI_FAILURE ��ַ����

\see \n
��
*/
HI_S32 HI_MemMng_Free(const HI_U32 u32ModId,const HI_VOID* pvMemAddr,
                      const HI_CHAR *pszFileName, const HI_U32 u32LineNo);

/** @} */  /*! <!-- API declaration end */

/*----------------------------------------------*
 * macros
 *----------------------------------------------*/

#ifdef HI_MEMORY_DEBUG

/*****************************************************************************
 * Function     : HI_MEMMNG_MALLOC
 * Description  : �����ڴ�
 * Input        : enModId,ģ��ID
 *                u32Size,�������ڴ��С
 * Output       : None
 * Return       : HI_VOID *,���뵽���ڴ��׵�ַ����Ϊδ���뵽
 * Data Accessed: None
 * Data Updated : None
 * Others       : None
 *****************************************************************************/
#define HI_MEMMNG_MALLOC(u32ModId,u32Size)   \
    HI_MemMng_MallocD((u32ModId),(u32Size), (const HI_CHAR *)__FILE__, __LINE__)

/*****************************************************************************
 * Function     : HI_MEMMNG_REALLOC
 * Description  : �����ڴ�
 * Input        : enModId,ģ��ID
                : pSrcMem Դ�ڴ��ַ.
 *                u32Size,�������ڴ��С
 * Output       : None
 * Return       : HI_VOID *,���뵽���ڴ��׵�ַ����Ϊδ���뵽
 * Data Accessed: None
 * Data Updated : None
 * Others       : None
 *****************************************************************************/
#define HI_MEMMNG_REALLOC(u32ModId,pSrcMem, u32Size)   \
    HI_MemMng_ReallocD((u32ModId), (pSrcMem), (u32Size), (const HI_CHAR *)__FILE__, __LINE__)

/*****************************************************************************
 * Function     : HI_MEMMNG_FREE
 * Description  : �ͷ��ڴ�
 * Input        : enModId,ģ��ID
 *                pvMemAddr,�ڴ��׵�ַ
 * Output       : None
 * Return       : HI_S32
 * Data Accessed: None
 * Data Updated : None
 * Others       : None
 *****************************************************************************/
#define HI_MEMMNG_FREE(u32ModId,pvMemAddr)   \
    HI_MemMng_Free((u32ModId),(pvMemAddr), (const HI_CHAR *)__FILE__, __LINE__)

#else
#define HI_MEMMNG_MALLOC(u32ModId,u32Size)    malloc((u32Size))
#define HI_MEMMNG_REALLOC(u32ModId,pSrcMem, u32Size)   realloc((pSrcMem), (u32Size))
#define HI_MEMMNG_FREE(u32ModId,pvMemAddr)   free((pvMemAddr))
#endif

#ifndef HI_ADVCA_FUNCTION_RELEASE
/*----------------------------------------------*
 * routine prototypes
 *----------------------------------------------*/
/*
memprint
    -mod [0~52|all] ;��ӡָ��ģ������ڴ����
*/

#if (UNF_VERSION_CODE >= UNF_VERSION(3, 1))
HI_S32 HI_CMD_MemMng_Queue(HI_PROC_SHOW_BUFFER_S * pstBuf, HI_VOID *pPrivData);
#else
HI_S32  HI_CMD_MemMng_Queue(HI_U32 u32Handle,int argc, const char* argv[]);
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__HI_ADP_MEMMNG_H__*/

