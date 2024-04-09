/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
 File Name     : hi_mpi_aenc.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#ifndef __HI_MPI_AENC_H__
#define __HI_MPI_AENC_H__

#include "hi_type.h"
#include "hi_unf_sound.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
typedef struct
{
    HI_U32               u32CodecID;
    HI_U32               u32InBufSize;             /* Input buffer size */
    HI_U32               u32OutBufNum;             /* Output buffer number, buffer size depend on u32CodecID */
    HI_HAENCODE_OPENPARAM_S sOpenParam;
} AENC_ATTR_S;

/* Input audio stream structure */
typedef struct
{
    HI_U8*  pu8Data;
    HI_U32  u32Bytes;
    HI_U32  u32PtsMs;
} AENC_STREAM_S;

HI_S32 HI_MPI_AENC_RegisterEncoder(const HI_CHAR* pszCodecDllName);
HI_S32 HI_MPI_AENC_SetConfigEncoder(HI_HANDLE hAenc, HI_VOID* pstConfigStructure);
HI_S32 HI_MPI_AENC_Init(HI_VOID);
HI_S32 HI_MPI_AENC_DeInit(HI_VOID);
HI_S32 HI_MPI_AENC_Open(HI_HANDLE* phAenc, const HI_UNF_AENC_ATTR_S* pstAencAttr);
HI_S32 HI_MPI_AENC_Close (HI_HANDLE hAenc);
HI_S32 HI_MPI_AENC_SendBuffer(HI_HANDLE hAenc, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame);
HI_S32 HI_MPI_AENC_ReceiveStream(HI_HANDLE hAenc, AENC_STREAM_S* pstStream, HI_U32 u32TimeoutMs);
HI_S32 HI_MPI_AENC_ReleaseStream(HI_HANDLE hAenc, const AENC_STREAM_S* pstStream);
HI_S32 HI_MPI_AENC_SetEnable(HI_HANDLE hAenc, HI_BOOL bEnable);
HI_S32 HI_MPI_AENC_AttachInput(HI_HANDLE hAenc, HI_HANDLE hSource);
HI_S32 HI_MPI_AENC_GetAttachSrc(HI_HANDLE hAenc, HI_HANDLE* hSrc);
HI_S32 HI_MPI_AENC_DetachInput(HI_HANDLE hAenc);
HI_S32 HI_MPI_AENC_SetAttr(HI_HANDLE hAenc, const HI_UNF_AENC_ATTR_S* pstAencAttr);
HI_S32 HI_MPI_AENC_GetAttr(HI_HANDLE hAenc, HI_UNF_AENC_ATTR_S* pstAencAttr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MPI_AENC_H__ */
