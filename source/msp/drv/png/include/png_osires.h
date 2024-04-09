/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name           : png_osires.h
Version             : Initial Draft
Author              :
Created             : 2018/01/01
Description         : PNG osires layer code     CNcomment:PNG osiresʵ��
Function List       :


History             :
Date                         Author                     Modification
2018/01/01                   sdk                        Created file
**************************************************************************************************/
#ifndef __PNG_OSIRES_H__
#define __PNG_OSIRES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#include <linux/semaphore.h>
#include "hi_png_type.h"

/* Handle instance struct */
typedef struct tag_PNG_INSTANCE_S
{
    HI_BOOL bInUse;                   /* is used now? */
    HI_BOOL bSync;                    /* is decode synchronously? */
    HI_BOOL bInBlockQuery;            /* Application block quering this decoder */
    HI_BOOL bClutAlpha;               /* is effective of alpha channel in palette */
    HI_PNG_STATE_E eState;            /* decode state */
    HI_U32 u32ClutPhyaddr;            /* color palette physical address */
    HI_U32 u32Phyaddr;                /* target physical address */
    HI_U32 u32Stride;                 /* target stride */
    HI_PNG_INFO_S stPngInfo;          /* png picture information */
    HI_U32 u32Transform;              /* format translation information */
    HI_PNG_COLORFMT_E eOutFmt;        /* output format of target when 32bit traslate to 16bit */
    HI_U32 u32FilterBufPhyaddr;       /* physical address of fliter buffer */
    HI_U32 u32StartBufPhyAddr;        /* physical addresss of start buffer */
    HI_VOID *pStartBufVir;            /* virtual address of start buffer */
    HI_U32 u32EndBufPhyAddr;          /* physical addresss of end buffer */
    HI_VOID *pEndBufVir;              /* virtual addresss of end buffer */
    HI_U32 u32HwUseBufPhyAddr;        /* buffer physical address reading by hardware */
    HI_VOID *pHwUseBufVir;            /* virtual address reading by hardware */
    struct semaphore stInstanceLock;  /* instance lock */
} PNG_INSTANCE_S;

/********************************************************************************************
* func    : handle initialization
* in      : none
* out     : none
* ret     : 1--32   invalid decoder handle
* ret     : HI_ERR_PNG_NOOPEN   device is not open
* ret     : HI_ERR_PNG_NOHANDLE no decoder resource
* others  : support 32 decoder at most
*********************************************************************************************/
HI_S32 PngOsiResInitHandle(HI_VOID);

/********************************************************************************************
* func    : handle destroy initialization
* in      : none
* out     : none
* ret     : none
* others  : support 32 decoder at most
*********************************************************************************************/
HI_VOID PngOsiResDeinitHandle(HI_VOID);

/********************************************************************************************
* func    : apply handle
* in      : none
* out     : ps32Handle decoder handle pointer
* ret     : HI_SUCCESS
* ret     : HI_ERR_PNG_NOHANDLE no handle resource
* ret     : HI_ERR_PNG_NULLPTR pointer is null
* others  : support 32 handle at most
*********************************************************************************************/
HI_S32 PngOsiResAllocHandle(HI_PNG_HANDLE *ps32Handle);

/********************************************************************************************
* func     : release handle
* in       : s32Handle   decoder handle
* out      : none
* ret      : HI_SUCCESS
* ret      : HI_ERR_PNG_INVALID_HANDLE   invalid decoder handle
* others:
*********************************************************************************************/
HI_S32 PngOsiResReleaseHandle(HI_PNG_HANDLE s32Handle);

/********************************************************************************************
* func     : get handle instance
* in       : s32Handle   decoder handle
* out      : none
* ret      : HI_SUCCESS
* ret      : HI_ERR_PNG_INVALID_HANDLE   invalid decoder handle
* others   :
*********************************************************************************************/
HI_S32 PngOsiResGetInstance(HI_PNG_HANDLE s32Handle, PNG_INSTANCE_S **ppstInstance);

/* --------------------------------------------------------------------------------------------- */


/* -----------------------------------memory manage--------------------------------------------- */

/********************************************************************************************
* func     : alloc memory
* in       : pName: memory module name
* in       : u32Size: memory size applied
* in       : u32Align: align  setting
* out      : pu32Phyaddr: start physical address in memory
* ret      : HI_SUCCESS
* ret      : HI_ERR_PNG_NOMEM    memory is not enough
* others   :
*****************************************************************/
HI_S32 PngOsiResAllocMem(HI_UCHAR *pName, HI_U32 u32Size, HI_U32 u32Align, HI_U32 *pu32Phyaddr);

/********************************************************************************************
* func     : release memory
* in       : u32Phyaddr: start physical address in memory by free
* out      : none
* ret      : none
* others   :
*********************************************************************************************/
HI_VOID PngOsiResReleaseMem(HI_U32 u32Phyaddr);

HI_VOID PngOsiShowInstanceState(struct seq_file *p);

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* __PNG_OSIRES_H__ */
