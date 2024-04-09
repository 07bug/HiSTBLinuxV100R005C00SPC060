/******************************************************************************

  Copyright (C), 2011-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ao_isb.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/07/25
  Description  :
  History       :
  1.Date        : 2017/07/25
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __AO_ISB_H__
#define  __AO_ISB_H__

#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define RENDER_BUFFER_SIZE    (512 * 1024)

// LBR(200 * 1024, about 25Frames) + HBR(824 * 1024, about 25Frames)
#define RENDER_BITSTREAM_SIZE (1 * 1024 * 1024)

typedef struct
{
    HI_U32         u32Read;
    HI_U32         u32Write;
    HI_U32         u32ServerLinearSize;
    HI_U8          au8Data[RENDER_BUFFER_SIZE];
} BUFFER_S;

typedef struct
{
    HI_U32         u32Read;
    HI_U32         u32Write;
    HI_U32         u32ServerLinearSize;
    HI_U8          au8Data[RENDER_BITSTREAM_SIZE]; // LBR + HBR
} BITSTREAM_S;

typedef struct
{
    HI_PHYS_ADDR_T tPhyIsbAddr;
    HI_U32         u32IsbSize;
    SOURCE_ID_E    enSourceID;
} ISB_ATTR_S;

typedef struct
{
    HI_U8*         pu8Data;
    HI_U32         u32Size;
} ISB_BUF_S;


HI_S32  AO_ISB_Create(HI_VOID** phISB, ISB_ATTR_S* pstIsbAttr);
HI_VOID AO_ISB_Destroy(HI_VOID* hISB);
HI_S32  AO_ISB_SendData(HI_VOID* hISB, ISB_BUF_S* pstIsbBuf);
HI_S32  AO_ISB_ReadData(HI_VOID* hISB, ISB_BUF_S* pstIsbBuf);
HI_S32  AO_ISB_SendBitstream(HI_VOID* hISB, ISB_BUF_S* pstIsbBuf);
HI_S32  AO_ISB_ReadBitstream(HI_VOID* hISB, ISB_BUF_S* pstIsbBuf);
HI_S32  AO_ISB_SendFrameInfo(HI_VOID* hISB, HI_HADECODE_OUTPUT_S* pstPackOut);
HI_S32  AO_ISB_CheckFrameInfo(HI_VOID* hISB);
HI_S32  AO_ISB_GetBusyFrames(HI_VOID* hISB, HI_U32* pu32FrameCnt);
HI_S32  AO_ISB_AcquireFrameInfo(HI_VOID* hISB, HI_HADECODE_OUTPUT_S* pstPackOut);
HI_S32  AO_ISB_ReleaseFrameInfo(HI_VOID* hISB, HI_U32 u32Len);
HI_S32  AO_ISB_GetPtsQue(HI_VOID* hISB, HI_VOID** phPtsQue);
HI_S32  AO_ISB_GetBusyBytes(HI_VOID* hISB, HI_U32* pu32BusyBytes);
HI_S32  AO_ISB_GetFreeBytes(HI_VOID* hISB, HI_U32* pu32AllFreeBytes, HI_U32* pu32LinearFreeBytes);
HI_S32  AO_ISB_GetBistreamFreeBytes(HI_VOID* hISB, HI_U32* pu32AllFreeBytes, HI_U32* pu32LinearFreeBytes);
HI_S32  AO_ISB_SetLinearBusyBytes(HI_VOID* hISB, HI_U32 u32FreeBytes);
HI_S32  AO_ISB_SetBistreamLinearBusyBytes(HI_VOID* hISB, HI_U32 u32LinearBusy);
HI_S32  AO_ISB_GetWptr(HI_VOID* hISB, HI_U8** ppu8Data);
HI_S32  AO_ISB_UpdateWptr(HI_VOID* hISB, HI_U32 u32DataSize);
HI_S32  AO_ISB_Reset(HI_VOID* hISB);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif
