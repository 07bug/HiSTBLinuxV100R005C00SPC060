
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
/** @{ */  /** <!—[HiMuxer]*/
#define TS_DEFAULT_MUXER  "ts_default"
#define MAX_DLLNAME_LEN 100
#define MAX_SPS_PPS_BUF (256)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HiMuxer */
/** @{*/  /** <!—[HiMuxer]*/

typedef struct tagHI_MuxerInfo_S
{
    const HI_PCHAR szName;                                     /**<muxer name*//**<CNcomment:由用户定义的封装的名称 */
    const HI_U32 enMuxerType;                                 /**<muxer type*//**<CNcomment:封装的类型，已经定义的封装枚举请参考Transcoder_MuxerType */
    const HI_PCHAR pszDescription;                       /**<muxer description, unify this muxer.*//**<CNcomment:用户定义的唯一标示封装的描述 */
    HI_CHAR szDllName[MAX_DLLNAME_LEN];  /**<Set empty*//**<CNcomment:由用户设置为空字串*/
    HI_VOID*   pDllModule;                                         /**<Set NULL*//**<CNcomment:由用户设置为NULL*/
    HI_S32 (*MuxerCreate)(HI_ULONG* hMuxerHandle, HI_U32 muxerType, const Transcoder_MuxerAttr* muxerAttr);     /**<muxer create*/ /**<CNcomment:muxer 创建接口 */
    HI_S32 (*MuxerDestroy)(HI_ULONG phHandle); /**<muxer destroy*//**<CNcomment:muxer destroy接口 */
    HI_S32 (*MuxerGetHeader)(HI_ULONG hMuxerHandle, const HI_CHAR* pTAGFrame, HI_S32* ps32Len);     /**<muxer getheader*/ /**<CNcomment:muxer 获取封装头接口 */
    HI_S32 (*DoMuxer)(HI_ULONG hMuxerHandle, HI_CHAR* pTAGFrame, HI_S32* ps32Len, const TRANSCODER_STRAM* pstTranFrame);    /**<muxer domux*/ /**<CNcomment:muxer 封装接口 */
    HI_S32 (*setPrivate)(HI_ULONG hMuxerHandle, const HI_VOID* stAttr, HI_S32 s32Len); /**<muxer setprivate*/ /**<CNcomment:muxer 设置私有属性集接口 */
    struct tagHI_MuxerInfo_S* next;                          /**<muxer linkList, user set NULL*//**<CNcomment:muxer 链表，用户置空 */
} HI_MuxerInfo_S;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

#endif /* __HI_MUXER_INTF_H__*/
