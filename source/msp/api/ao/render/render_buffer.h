/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render_buffer.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __RENDER_BUFFER_H__
#define  __RENDER_BUFFER_H__

#include "hi_type.h"
#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define RBUFFER_ERR_BUFFER_FULL (0x80000001)

HI_S32  RENDER_ServerBuffer_Init(HI_VOID** phHandle, SOURCE_ID_E enSourceID, HI_U32 u32BufSize, HI_VOID* pExtOutBuf);
HI_S32  RENDER_ServerBuffer_DeInit(HI_VOID* handle);
HI_S32  RENDER_ServerBuffer_Acquire(HI_VOID* handle, HI_U32 u32NeedSize, HI_U8** ppu8Data, HI_U32* pu32Size);
HI_S32  RENDER_ServerBuffer_Release(HI_VOID* handle, HI_U32 u32Size);
HI_S32  RENDER_ServerFrame_Acquire(HI_VOID* handle, HI_U32 u32NeedSize, HI_HADECODE_OUTPUT_S* pstPackOut, HI_U32* pu32Size);
HI_S32  RENDER_ServerFrame_Release(HI_VOID* handle, HI_HADECODE_OUTPUT_S* pstPackOut, HI_U32 u32Size);
HI_S32  RENDER_ServerBuffer_Enquire(HI_VOID* handle, HI_U32 *pu32UsedSize, HI_U32 *pu32TotSize);
HI_S32  RENDER_ServerBuffer_Reset(HI_VOID* handle);
HI_S32  RENDER_ServerBuffer_GetDataSize(HI_VOID* handle, HI_U32* pu32BufSize);
HI_S32  RENDER_ServerBuffer_GetISBHandle(HI_VOID* handle, HI_VOID** phISB);
HI_S32  RENDER_ServerBuffer_GetISBAttr(HI_VOID* handle, HI_MPI_AO_SB_ATTR_S* pstSBAttr);
HI_S32  RENDER_ServerBuffer_GetFrameInfo(HI_VOID* handle, HI_HADECODE_OUTPUT_S* pstPackOut);

HI_S32  RENDER_ClientBuffer_Init(HI_VOID** phHandle, SOURCE_ID_E enSourceID, HI_MPI_AO_SB_ATTR_S* pstSBAttr);
HI_S32  RENDER_ClientBuffer_DeInit(HI_VOID* handle);
HI_S32  RENDER_ClientBuffer_Send(HI_VOID* handle, HI_U8* pu8Data, HI_U32 u32Size);
HI_S32  RENDER_ClientBuffer_SendAoFrame(HI_VOID* handle, HI_HADECODE_OUTPUT_S* pstPackOut);
HI_S32  RENDER_ClientBuffer_GetISBHandle(HI_VOID* handle, HI_VOID** phISB);
HI_S32  RENDER_ClientBuffer_Get(HI_VOID* handle, HI_U32 u32RequestSize, HI_U8** ppu8Data);
HI_S32  RENDER_ClientBuffer_Put(HI_VOID* handle, HI_U32 u32DataSize, HI_U8* pu8Data);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
