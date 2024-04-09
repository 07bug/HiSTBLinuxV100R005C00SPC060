
/**
 * \file hi_muxer_intf.h
 * \brief Describes the information about HiSilicion Muxer (HiMuxer).
*/

#ifndef __HI_MUXER_INTF_H__
#define __HI_MUXER_INTF_H__

#include "hi_type.h"
#include "hi_muxer.h"

/***************************** Macro Definition ******************************/
/** \addtogroup      HiMuxer */
/** @{ */  /** <!��[HiMuxer]*/
#define TS_DEFAULT_MUXER  "ts_default"
#define MAX_DLLNAME_LEN 100
#define MAX_SPS_PPS_BUF (256)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HiMuxer */
/** @{*/  /** <!��[HiMuxer]*/

typedef struct tagHI_MuxerInfo_S
{
    const HI_PCHAR szName;                                     /**<muxer name*//**<CNcomment:���û�����ķ�װ������ */
    const HI_U32 enMuxerType;                                 /**<muxer type*//**<CNcomment:��װ�����ͣ��Ѿ�����ķ�װö����ο�Transcoder_MuxerType */
    const HI_PCHAR pszDescription;                       /**<muxer description, unify this muxer.*//**<CNcomment:�û������Ψһ��ʾ��װ������ */
    HI_CHAR szDllName[MAX_DLLNAME_LEN];  /**<Set empty*//**<CNcomment:���û�����Ϊ���ִ�*/
    HI_VOID*   pDllModule;                                         /**<Set NULL*//**<CNcomment:���û�����ΪNULL*/
    HI_S32 (*MuxerCreate)(HI_ULONG* hMuxerHandle, HI_U32 muxerType, const Transcoder_MuxerAttr* muxerAttr);     /**<muxer create*/ /**<CNcomment:muxer �����ӿ� */
    HI_S32 (*MuxerDestroy)(HI_ULONG phHandle); /**<muxer destroy*//**<CNcomment:muxer destroy�ӿ� */
    HI_S32 (*MuxerGetHeader)(HI_ULONG hMuxerHandle, const HI_CHAR* pTAGFrame, HI_S32* ps32Len);     /**<muxer getheader*/ /**<CNcomment:muxer ��ȡ��װͷ�ӿ� */
    HI_S32 (*DoMuxer)(HI_ULONG hMuxerHandle, HI_CHAR* pTAGFrame, HI_S32* ps32Len, const TRANSCODER_STRAM* pstTranFrame);    /**<muxer domux*/ /**<CNcomment:muxer ��װ�ӿ� */
    HI_S32 (*setPrivate)(HI_ULONG hMuxerHandle, const HI_VOID* stAttr, HI_S32 s32Len); /**<muxer setprivate*/ /**<CNcomment:muxer ����˽�����Լ��ӿ� */
    struct tagHI_MuxerInfo_S* next;                          /**<muxer linkList, user set NULL*//**<CNcomment:muxer �����û��ÿ� */
} HI_MuxerInfo_S;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

#endif /* __HI_MUXER_INTF_H__*/
