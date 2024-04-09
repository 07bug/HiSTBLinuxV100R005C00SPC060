/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name         : hi_png_api.c
Version           : Initial Draft
Author            : sdk
Created           : 2018/01/01
Description       : implemention of PNG application interface
Function List     :

History           :
Date                       Author                       Modification
2018/01/01                  sdk                         Created file
**************************************************************************************************/

/*********************************add include here***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <assert.h>

#include "hi_png_api.h"
#include "hi_png_errcode.h"

#include "hi_drv_png.h"
#include "hi_gfx_comm.h"

#include "hi_gfx_sys.h"


/***************************** Macro Definition *************************************************/


/*************************** Enum Definition ****************************************************/
static const HI_CHAR *g_pPngDevPath = "/dev/hi_png";

static HI_S32 g_s32PngFd = -1;
static HI_U32 g_u32PngRef = 0;
#ifdef CONFIG_GFX_MEM_ION
static HI_S32 g_s32MemFd = -1;
#endif

static pthread_mutex_t g_PngMutex = PTHREAD_MUTEX_INITIALIZER;

#define PNG_CHECK_DEVSTATE() do \
    {\
        if (g_s32PngFd < 0)\
        {\
            return HI_ERR_PNG_DEV_NOOPEN; \
        } \
    } while (0)

#define PNG_CHECK_HANDLE(handle) do \
	{\
		if ((handle <= 0) || (handle > PNG_MAX_HANDLE) || !gs_PngApiInstance[handle - 1].bValid)\
		{\
			return HI_ERR_PNG_INVALID_HANDLE;\
		}\
	} while(0)

#define PNG_CHECK_HANDLE_UNRETURN(handle) do \
    {\
        if ((handle <= 0) || (handle > PNG_MAX_HANDLE) || !gs_PngApiInstance[handle - 1].bValid)\
        {\
            return;\
        }\
    } while(0)

#define PNG_BUF_DEFAULTSIZE  (128 * 1024)

/*************************** Structure Definition ***********************************************/
typedef struct hiPNG_STREAM_BUF_S
{
    HI_U32 u32PhyAddr;    /* physical addr of the buffer*/
    HI_VOID *pVir;        /* virtual addr of the buffer*/
    HI_U32 u32Size;       /* buffer size */
	HI_U32 u32Len;        /* stream size */
	HI_VOID *pMemHandle;
}HIPNG_STREAM_BUF_S;

/* list struct, mapping physical address /virtual address */
typedef struct tagPNG_MEM_NODE_S
{
    HIPNG_STREAM_BUF_S stBuf;             /* memory information */
    struct tagPNG_MEM_NODE_S *pNext;      /* next node */
} PNG_MEM_NODE_S;

/* buf r/w info struct */
typedef struct tagPNG_READ_INFO_S
{
    HI_U32 u32Read;              /* length of code by read */
	PNG_MEM_NODE_S *pstMemNode;
} PNG_READ_INFO_S;

/* user decode instance, maintain the relation on mapping  physical addr and user virtual addr */
typedef struct tagPNG_API_INSTANCE_S
{
    pthread_mutex_t stLock;       /* Instance lock       */
    PNG_MEM_NODE_S *pMemHead;     /* list head of memory */
	PNG_MEM_NODE_S *pMemTail;
    PNG_READ_INFO_S *pReadParam;  /* read parameter      */
	HI_BOOL bValid;
} PNG_API_INSTANCE_S;


/********************** Global Variable declaration *********************************************/
/* user decoder instance array */
static PNG_API_INSTANCE_S gs_PngApiInstance[PNG_MAX_HANDLE];

static HI_U32 HIPNG_Read(HI_UCHAR *pBuf, HI_U32 u32Len, HI_PNG_HANDLE s32Handle);

/******************************* API declaration ************************************************/
HI_S32 HI_PNG_Open(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = pthread_mutex_lock(&g_PngMutex);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_ERR_PNG_DEV_BUSY;
    }

    if (g_s32PngFd >= 0)
    {
        g_u32PngRef++;
        pthread_mutex_unlock(&g_PngMutex);
        return HI_SUCCESS;
    }

    g_s32PngFd = open(g_pPngDevPath, O_RDWR | O_SYNC, S_IRUSR);
    if (g_s32PngFd < 0)
    {
        pthread_mutex_unlock(&g_PngMutex);
        return HI_ERR_PNG_DEV_NOEXIST;
    }

#ifdef CONFIG_GFX_MEM_ION
    g_s32MemFd = gfx_mem_open();
    if (g_s32MemFd < 0)
    {
        close(g_s32PngFd);
	    g_s32PngFd = -1;
        pthread_mutex_unlock(&g_PngMutex);
        return HI_ERR_PNG_DEV_NOEXIST;
    }
#endif

    g_u32PngRef++;

    HI_GFX_Memset(gs_PngApiInstance, 0, sizeof(gs_PngApiInstance));

    pthread_mutex_unlock(&g_PngMutex);

    return HI_SUCCESS;
}

/********************************************************************************************
* func    : close PNG device
* in      : none
* out     : none
* ret     : none
* others  : pair wirh HI_PNG_Open
********************************************************************************************/
HI_VOID HI_PNG_Close(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = pthread_mutex_lock(&g_PngMutex);
    if (HI_SUCCESS != s32Ret)
    {
        return;
    }

    if (g_s32PngFd < 0)
    {
        pthread_mutex_unlock(&g_PngMutex);
        return;
    }

    if (--g_u32PngRef == 0)
    {
        close(g_s32PngFd);
        g_s32PngFd = -1;

#ifdef CONFIG_GFX_MEM_ION
        gfx_mem_close(g_s32MemFd);
        g_s32MemFd = -1;
#endif

        pthread_mutex_unlock(&g_PngMutex);

        return;
    }

    pthread_mutex_unlock(&g_PngMutex);

    return;
}

/********************************************************************************************
* func   : create decoder
* in     : none
* out    : ps32Handle decoder handle pointer
* ret    : HI_SUCCESS
* ret    : HI_ERR_PNG_NOOPEN	device is not open
* ret    : HI_ERR_PNG_NOHANDLE	no decoder resource
* ret    : HI_ERR_PNG_NULLPTR  Null pointer
* others : support create 32 decoder at most
*********************************************************************************************/
HI_S32 HI_PNG_CreateDecoder(HI_PNG_HANDLE *ps32Handle)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_NULL == ps32Handle)
    {
        return HI_ERR_PNG_NULLPTR;
    }

    PNG_CHECK_DEVSTATE();

    s32Ret = ioctl(g_s32PngFd, PNG_CREATE_DECODER, ps32Handle);
    if (s32Ret < 0)
    {
        return s32Ret;
    }

    if ((*ps32Handle <= 0) || (*ps32Handle > PNG_MAX_HANDLE))
    {
		return HI_ERR_PNG_INVALID_HANDLE;
	}

    pthread_mutex_init(&gs_PngApiInstance[*ps32Handle - 1].stLock, HI_NULL);

    gs_PngApiInstance[*ps32Handle - 1].pMemHead   = HI_NULL;
	gs_PngApiInstance[*ps32Handle - 1].pMemTail   = HI_NULL;
    gs_PngApiInstance[*ps32Handle - 1].pReadParam = HI_NULL;
	gs_PngApiInstance[*ps32Handle - 1].bValid     = HI_TRUE;

    return HI_SUCCESS;
}

HI_VOID PNG_UnMap_DecoderBuf(HI_PNG_HANDLE s32Handle)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PNG_MEM_NODE_S *pTemp = HI_NULL;

    PNG_CHECK_HANDLE_UNRETURN(s32Handle);

    s32Ret = pthread_mutex_lock(&gs_PngApiInstance[s32Handle - 1].stLock);
    if (HI_SUCCESS != s32Ret)
    {
        return;
    }

    while (gs_PngApiInstance[s32Handle - 1].pMemHead != HI_NULL)
    {
        pTemp = gs_PngApiInstance[s32Handle - 1].pMemHead->pNext;
#ifdef CONFIG_GFX_MEM_MMZ
		HI_GFX_Unmap(gs_PngApiInstance[s32Handle - 1].pMemHead->stBuf.u32PhyAddr, HI_TRUE);
		HI_GFX_FreeMem(gs_PngApiInstance[s32Handle - 1].pMemHead->stBuf.u32PhyAddr, HI_TRUE);
#else
		HI_GFX_Unmap(g_s32MemFd, gs_PngApiInstance[s32Handle - 1].pMemHead->stBuf.u32PhyAddr, gs_PngApiInstance[s32Handle - 1].pMemHead->stBuf.pMemHandle);
		HI_GFX_FreeMem(g_s32MemFd, gs_PngApiInstance[s32Handle - 1].pMemHead->stBuf.u32PhyAddr, gs_PngApiInstance[s32Handle - 1].pMemHead->stBuf.pMemHandle, HI_TRUE);
#endif
		free(gs_PngApiInstance[s32Handle - 1].pMemHead);
        gs_PngApiInstance[s32Handle - 1].pMemHead = pTemp;
    }

    if (gs_PngApiInstance[s32Handle - 1].pReadParam)
    {
        free(gs_PngApiInstance[s32Handle - 1].pReadParam);
        gs_PngApiInstance[s32Handle - 1].pReadParam = HI_NULL;
    }

    pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);

    return;
}

/********************************************************************************************
* func     : destroy decoder
* in       : s32Handle	decoder handle
* out      : none
* ret      : HI_SUCCESS
* ret      : HI_ERR_PNG_NOOPEN	device is not open
* ret      : HI_ERR_PNG_INVALID_HANDLE	unlawful decoder handle
* others   : pair with HI_PNG_CreateDecoder
********************************************************************************************/
HI_S32 HI_PNG_DestroyDecoder(HI_PNG_HANDLE s32Handle)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PNG_CHECK_DEVSTATE();

	PNG_CHECK_HANDLE(s32Handle);

    PNG_UnMap_DecoderBuf(s32Handle);

	gs_PngApiInstance[s32Handle - 1].bValid = HI_FALSE;

    s32Ret = ioctl(g_s32PngFd, PNG_DESTROY_DECODER, &s32Handle);
    if (s32Ret < 0)
    {
        return s32Ret;
    }

    return HI_SUCCESS;
}

/********************************************************************************************
* func     : Alloc code stream buffer
* in       : s32Handle	decoder handle
* in       : pstBuf->u32Len	apply the size of buffer
* out      : pstBuf	return buf information,include  basic physical addr and the size of buffer
* ret      : HI_SUCCESS
* ret      : HI_ERR_PNG_NOOPEN	device is not open
* ret      : HI_ERR_PNG_INVALID_HANDLE	unlawful decoder handle
* ret      : HI_ERR_PNG_NOMEM	memory is not enough
* ret      : HI_ERR_PNG_NULLPTR	pointer is null
* others   :
             Get code stream buffer, write into code steam data;
             if pstBuf->u32Len = 0, alloc default size in memory,
             otherwise alloc by the size of pstBuf->u32Len.
             while output, the value of pstBuf->u32Len equal to its used
********************************************************************************************/
HI_S32 HI_PNG_AllocBuf(HI_PNG_HANDLE s32Handle, HI_PNG_BUF_S *pstBuf)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PNG_GETBUF_CMD_S stCmd;
    PNG_MEM_NODE_S *pstMemNode = HI_NULL;
	HI_U32 u32Size = 0;
	HI_VOID *pMemHandle = HI_NULL;
	HI_BOOL bMmu = HI_TRUE;

#ifdef CONFIG_GFX_MMU_SUPPORT
	HI_CHAR *pZoneName = "iommu";
#else
	HI_CHAR *pZoneName = NULL;
#endif

    if (HI_NULL == pstBuf)
    {
        return HI_ERR_PNG_NULLPTR;
    }

    PNG_CHECK_DEVSTATE();

    PNG_CHECK_HANDLE(s32Handle);

    HI_GFX_Memset(&stCmd, 0x0, sizeof(PNG_GETBUF_CMD_S));

	u32Size = (pstBuf->u32Size > PNG_BUF_DEFAULTSIZE) ? (pstBuf->u32Size) : (PNG_BUF_DEFAULTSIZE);
    if (u32Size > (UINT_MAX - 0xf))
    {
        return HI_ERR_PNG_NOMEM;
    }

    u32Size = ((u32Size + 0xf) & 0xfffffff0);

#ifdef CONFIG_GFX_MEM_MMZ
	pstBuf->u32PhyAddr = HI_GFX_AllocMem(u32Size, 16, pZoneName, "HIPNG_STREAM_BUF", &bMmu);
#else
	pstBuf->u32PhyAddr = HI_GFX_AllocMem(g_s32MemFd, u32Size, 16, pZoneName, "HIPNG_STREAM_BUF", &pMemHandle, &bMmu);
#endif
	if (0 == pstBuf->u32PhyAddr)
	{
#ifdef CONFIG_GFX_MEM_MMZ
        HI_GFX_FreeMem(pstBuf->u32PhyAddr, bMmu);
#else
        HI_GFX_FreeMem(g_s32MemFd, pstBuf->u32PhyAddr, pMemHandle, bMmu);
#endif
		return HI_ERR_PNG_NOMEM;
	}

#ifdef CONFIG_GFX_MEM_MMZ
	pstBuf->pVir = HI_GFX_MapCached(pstBuf->u32PhyAddr, bMmu);
#else
	pstBuf->pVir = HI_GFX_MapCached(g_s32MemFd, pstBuf->u32PhyAddr, pMemHandle);
#endif
	if (NULL == pstBuf->pVir)
	{
#ifdef CONFIG_GFX_MEM_MMZ
		HI_GFX_FreeMem(pstBuf->u32PhyAddr, bMmu);
#else
		HI_GFX_FreeMem(g_s32MemFd, pstBuf->u32PhyAddr, pMemHandle, bMmu);
#endif
		return HI_ERR_PNG_NOMEM;
	}

	pstBuf->u32Size = u32Size;

    stCmd.s32Handle        = s32Handle;
    stCmd.stBuf.u32PhyAddr = pstBuf->u32PhyAddr;
	stCmd.stBuf.u32Size    = pstBuf->u32Size;
	stCmd.stBuf.u64Vir     = (HI_U64)(unsigned long)(pstBuf->pVir);

	s32Ret = ioctl(g_s32PngFd, PNG_ALLOC_BUF, &stCmd);
    if (s32Ret < 0)
    {
#ifdef CONFIG_GFX_MEM_MMZ
		HI_GFX_Unmap(pstBuf->u32PhyAddr, bMmu);
		HI_GFX_FreeMem(pstBuf->u32PhyAddr, bMmu);
#else
    	HI_GFX_Unmap(g_s32MemFd, pstBuf->u32PhyAddr, pMemHandle);
		HI_GFX_FreeMem(g_s32MemFd, pstBuf->u32PhyAddr, pMemHandle, bMmu);
#endif
        return s32Ret;
    }

    pstMemNode = (PNG_MEM_NODE_S *)malloc(sizeof(PNG_MEM_NODE_S));
    if (HI_NULL == pstMemNode)
    {
#ifdef CONFIG_GFX_MEM_MMZ
		HI_GFX_Unmap(pstBuf->u32PhyAddr, bMmu);
		HI_GFX_FreeMem(pstBuf->u32PhyAddr, bMmu);
#else
		HI_GFX_Unmap(g_s32MemFd, pstBuf->u32PhyAddr, pMemHandle);
		HI_GFX_FreeMem(g_s32MemFd, pstBuf->u32PhyAddr, pMemHandle, bMmu);
#endif
        return HI_ERR_PNG_NOMEM;
    }

    HI_GFX_Memcpy(&pstMemNode->stBuf, pstBuf, sizeof(HI_PNG_BUF_S));
	pstMemNode->stBuf.u32Len = 0;
	pstMemNode->stBuf.pMemHandle = pMemHandle;
	pstMemNode->pNext = HI_NULL;

    s32Ret = pthread_mutex_lock(&gs_PngApiInstance[s32Handle - 1].stLock);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    /* insert node into list head */
	if (gs_PngApiInstance[s32Handle - 1].pMemHead)
	{
		gs_PngApiInstance[s32Handle - 1].pMemTail->pNext = pstMemNode;
	}
	else
	{
		gs_PngApiInstance[s32Handle - 1].pMemHead = pstMemNode;
	}
	gs_PngApiInstance[s32Handle - 1].pMemTail = pstMemNode;

    pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);

    return HI_SUCCESS;
}

/********************************************************************************************
* func     : release code stream buffer
* in       : s32Handle	decoder handle
* out      : none
* ret      : HI_SUCCESS
* ret      : HI_ERR_PNG_NOOPEN	device is not open
* ret      : HI_ERR_PNG_INVALID_HANDLE	unlawful decoder handle
* others   :
*********************************************************************************************/
HI_S32 HI_PNG_ReleaseBuf(HI_PNG_HANDLE s32Handle)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PNG_CHECK_DEVSTATE();

    PNG_CHECK_HANDLE(s32Handle);

    s32Ret = ioctl(g_s32PngFd, PNG_RELEASE_BUF, &s32Handle);
    if (s32Ret < 0)
    {
        PNG_UnMap_DecoderBuf(s32Handle);
        return s32Ret;
    }

    /* Unmap in user */
    PNG_UnMap_DecoderBuf(s32Handle);

    return HI_SUCCESS;
}

/********************************************************************************************
* func      : set code stream size
* in        : s32Handle	decoder handle
* in        : pstBuf	 info of code stream buffer
* out       :
* ret       : HI_SUCCESS
* ret       : HI_ERR_PNG_NOOPEN	device is not open
* ret       : HI_ERR_PNG_INVALID_HANDLE	unlawful decoder handle
* ret       : HI_ERR_PNG_INVALID_PARAM	invalid code stream size
* ret       : HI_ERR_PNG_NULLPTR  point is null
* others    :
              set the size of code stream, after get code stream buffer and write code stream data
              the size of code stream is not more than the size of buffer
*********************************************************************************************/
HI_S32 HI_PNG_SetStreamLen(HI_PNG_HANDLE s32Handle, HI_U32 u32Phyaddr, HI_U32 u32Len)
{
    PNG_SETSTREAM_CMD_S stCmd;
    HI_S32 s32Ret = HI_SUCCESS;
    PNG_MEM_NODE_S *pTemp = HI_NULL;

    PNG_CHECK_DEVSTATE();
    PNG_CHECK_HANDLE(s32Handle);
    if ((0 == u32Phyaddr) || (0 == u32Len))
    {
        return HI_FAILURE;
    }
    HI_GFX_Memset(&stCmd, 0x0, sizeof(PNG_SETSTREAM_CMD_S));

    stCmd.s32Handle  = s32Handle;
    stCmd.u32Phyaddr = u32Phyaddr;
    stCmd.u32Len     = u32Len;
    s32Ret = ioctl(g_s32PngFd, PNG_SET_STREAMLEN, &stCmd);
    if (s32Ret < 0)
    {
        return s32Ret;
    }

    s32Ret = pthread_mutex_lock(&gs_PngApiInstance[s32Handle - 1].stLock);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

	if (HI_NULL == gs_PngApiInstance[s32Handle - 1].pMemHead)
	{
		pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
		return HI_ERR_PNG_INVALID_PARAM;
	}

	pTemp = gs_PngApiInstance[s32Handle - 1].pMemHead;
    while (pTemp)
    {
        if (pTemp->stBuf.u32PhyAddr == u32Phyaddr)
        {
            break;
        }
        pTemp = pTemp->pNext;
    }

	if ((HI_NULL == pTemp) || (pTemp->stBuf.u32Size < u32Len))
	{
		pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
		return HI_ERR_PNG_INVALID_PARAM;
	}
	else
	{
		pTemp->stBuf.u32Len = u32Len;
	}

    pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);

    return HI_SUCCESS;
}

/********************************************************************************************
* func    :	Get code stream size
* in      : s32Handle	decoder handle
* in      : u32Phyaddr	physical size of buffer
* out     :	pu32Len length of code stream
* ret     :	HI_SUCCESS
* ret     : HI_ERR_PNG_NOOPEN	device is not open
* ret     : HI_ERR_PNG_INVALID_HANDLE	invalid decoder handle
* ret     : HI_ERR_PNG_NULLPTR  pointer is null
* others  :
*********************************************************************************************/
HI_S32 HI_PNG_GetStreamLen(HI_PNG_HANDLE s32Handle, HI_U32 u32Phyaddr, HI_U32 *pu32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PNG_SETSTREAM_CMD_S stCmd;

    if (pu32Len == HI_NULL)
    {
        return HI_ERR_PNG_NULLPTR;
    }

    PNG_CHECK_DEVSTATE();
    PNG_CHECK_HANDLE(s32Handle);
    HI_GFX_Memset(&stCmd, 0x0, sizeof(PNG_SETSTREAM_CMD_S));

    stCmd.s32Handle  = s32Handle;
    stCmd.u32Phyaddr = u32Phyaddr;

    s32Ret = ioctl(g_s32PngFd, PNG_GET_STREAMLEN, &stCmd);
    if (s32Ret < 0)
    {
        return s32Ret;
    }

    *pu32Len = stCmd.u32Len;

    return HI_SUCCESS;
}

/********************************************************************************************
* func      : start decode
* in        : s32Handle	decoder handle
* in        : pstDecInfo	decoder setting information
* out       :
* ret       : HI_SUCCESS
* ret       : HI_ERR_PNG_NOOPEN	device is not open
* ret       : HI_ERR_PNG_INVALID_HANDLE	invalid decoder handle
* ret       : HI_ERR_PNG_NULLPTR pointer is null
* ret       : HI_ERR_PNG_NOSTREAM  no code stream
* ret       : HI_PNG_ERR_INTERNAL  decode error
* others    :
*********************************************************************************************/
HI_S32 HI_PNG_Decode(HI_PNG_HANDLE s32Handle,  const HI_PNG_DECINFO_S *pstDecInfo)
{
    PNG_DECODE_CMD_S stCmd;
#ifndef CONFIG_GFX_MEM_MMZ
    HI_S32 s32Ret = HI_SUCCESS;
	PNG_MEM_NODE_S *pTemp = HI_NULL;
#endif

    if (HI_NULL == pstDecInfo)
    {
        return HI_ERR_PNG_NULLPTR;
    }

    PNG_CHECK_DEVSTATE();
    PNG_CHECK_HANDLE(s32Handle);
    HI_GFX_Memset(&stCmd,0x0,sizeof(PNG_DECODE_CMD_S));

#ifdef CONFIG_GFX_MEM_MMZ
    HI_GFX_Flush(0,HI_TRUE);
#else

    s32Ret = pthread_mutex_lock(&gs_PngApiInstance[s32Handle - 1].stLock);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    if (HI_NULL == gs_PngApiInstance[s32Handle - 1].pMemHead)
    {
        pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
        return HI_ERR_PNG_INVALID_PARAM;
    }

    pTemp = gs_PngApiInstance[s32Handle - 1].pMemHead;
    while (pTemp)
    {
        HI_GFX_Flush(g_s32MemFd, 0, pTemp->stBuf.pMemHandle);
		pTemp = pTemp->pNext;
	}
#endif

    stCmd.s32Handle = s32Handle;

    HI_GFX_Memcpy(&stCmd.stDecInfo, pstDecInfo, sizeof(HI_PNG_DECINFO_S));

    pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);

    return ioctl(g_s32PngFd, PNG_DECODE, &stCmd);
}

/********************************************************************************************
* func    :	Get decode result
* in      :	s32Handle	decoder handle
* in      :	bBlock		if block
* out     :	pstDecResult	decode result
* ret     :	HI_SUCCESS
* ret     :	HI_ERR_PNG_NOOPEN	device is not open
* ret     :	HI_ERR_PNG_INVALID_HANDLE	invalid decoder handle
* ret     :	HI_ERR_PNG_NULLPTR	pointer is null
* others  :
********************************************************************************************/
HI_S32 HI_PNG_GetResult(HI_PNG_HANDLE s32Handle, HI_BOOL bBlock, HI_PNG_STATE_E * peDecState)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PNG_DECRESULT_CMD_S stCmd;

    if (HI_NULL == peDecState)
    {
        return HI_ERR_PNG_NULLPTR;
    }

    PNG_CHECK_DEVSTATE();
    PNG_CHECK_HANDLE(s32Handle);
    HI_GFX_Memset(&stCmd,0x0,sizeof(PNG_DECRESULT_CMD_S));

    stCmd.s32Handle = s32Handle;
    stCmd.bBlock    = bBlock;

    s32Ret = ioctl(g_s32PngFd, PNG_GET_DECRESULT, &stCmd);

    *peDecState = stCmd.eDecResult;

    return s32Ret;
}

/********************************************************************************************
* func     : Get read function pointer
* in       : s32Handle	decoder handle
* out      : pReadFunc 	read fuction
* ret      : HI_SUCCESS
* ret      : HI_ERR_PNG_NOOPEN	device is not open
* ret      : HI_ERR_PNG_INVALID_HANDLE	invalid decoder handle
* ret      : HI_ERR_PNG_NULLPTR	pointer is null
* others   :
*********************************************************************************************/
HI_S32 HI_PNG_GetReadPtr(HI_PNG_HANDLE s32Handle, HI_PNG_READ_FN *ppReadFunc)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_NULL == ppReadFunc)
    {
        return HI_ERR_PNG_NULLPTR;
    }

	PNG_CHECK_DEVSTATE();

	PNG_CHECK_HANDLE(s32Handle);

    s32Ret = pthread_mutex_lock(&gs_PngApiInstance[s32Handle - 1].stLock);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

	if (HI_NULL == gs_PngApiInstance[s32Handle - 1].pMemHead)
	{
		pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
		*ppReadFunc = HI_NULL;
		return HI_SUCCESS;
	}

    if (HI_NULL == gs_PngApiInstance[s32Handle - 1].pReadParam)
    {
        gs_PngApiInstance[s32Handle - 1].pReadParam = (PNG_READ_INFO_S *)malloc(sizeof(PNG_READ_INFO_S));
        if (HI_NULL == gs_PngApiInstance[s32Handle - 1].pReadParam)
        {
            pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
            return HI_ERR_PNG_NOMEM;
        }
        gs_PngApiInstance[s32Handle - 1].pReadParam->u32Read = 0;
        gs_PngApiInstance[s32Handle - 1].pReadParam->pstMemNode = gs_PngApiInstance[s32Handle - 1].pMemHead;
    }

    pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);

    *ppReadFunc = HIPNG_Read;

    return HI_SUCCESS;
}

/********************************************************************************************
* func    : Read data form code stream buffer in driver
* in      : u32Len  lenth
* in      : s32Handle decoder handle
* out     :	get code stream data
* ret     : bytes read in fact
* others  :
********************************************************************************************/
static HI_U32 HIPNG_Read(HI_UCHAR *pBuf, HI_U32 u32Len, HI_PNG_HANDLE s32Handle)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UCHAR *pViraddr = HI_NULL;
    HI_U32 u32ReadLen = 0;
    HI_U32 u32TmpLen = 0;
	PNG_READ_INFO_S *pReadParam = NULL;

    PNG_CHECK_HANDLE(s32Handle);

    pReadParam = gs_PngApiInstance[s32Handle - 1].pReadParam;

    if ((HI_NULL == pBuf) || (HI_NULL == pReadParam) || (HI_NULL == pReadParam->pstMemNode))
    {
        return 0;
    }

    s32Ret = pthread_mutex_lock(&gs_PngApiInstance[s32Handle - 1].stLock);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    pViraddr = pReadParam->pstMemNode->stBuf.pVir;

    while (pViraddr)
    {
        if (pReadParam->pstMemNode->stBuf.u32Len < pReadParam->u32Read)
        {
            return HI_FAILURE;
        }

        u32TmpLen = pReadParam->pstMemNode->stBuf.u32Len - pReadParam->u32Read;

        if (u32Len <= u32TmpLen)
        {
            HI_GFX_Memcpy(pBuf + u32ReadLen, pViraddr + pReadParam->u32Read, u32Len);
            pReadParam->u32Read += u32Len;
            u32ReadLen += u32Len;
            pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
            return u32ReadLen;
        }
        else
        {
            HI_GFX_Memcpy(pBuf + u32ReadLen, pViraddr + pReadParam->u32Read, u32TmpLen);
            u32ReadLen += u32TmpLen;
            u32Len -= u32TmpLen;

            pReadParam->u32Read = 0;
			pReadParam->pstMemNode = pReadParam->pstMemNode->pNext;
            if (NULL == pReadParam->pstMemNode)
            {
                pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
                return u32ReadLen;
            }

            pViraddr = pReadParam->pstMemNode->stBuf.pVir;
        }
    }

    pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);

    return u32ReadLen;
}


/*****************************************************************
* func   : HI_PNG_GetStream
* in     : Á÷Ê½½âÂë
* out    :
* ret    : HI_SUCCESS
*		 : HI_FAILURE
* others :
*****************************************************************/
#ifdef HIPNG_PUSH_DECODE
HI_VOID HI_PNG_GetStream(HI_PNG_HANDLE s32Handle, HI_VOID **ppStream, HI_U32 *pu32Len)
{
    PNG_READ_INFO_S *pReadParam = NULL;
    HI_S32 s32Ret = HI_SUCCESS;

    PNG_CHECK_HANDLE_UNRETURN(s32Handle);

    if ((NULL == ppStream) || (NULL == pu32Len))
    {
        return;
    }

    s32Ret = pthread_mutex_lock(&gs_PngApiInstance[s32Handle - 1].stLock);
    if (HI_SUCCESS != s32Ret)
    {
        return;
    }

    if (HI_NULL == gs_PngApiInstance[s32Handle - 1].pMemHead)
    {
        pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
        *ppStream = NULL;
        *pu32Len = 0;
        return;
    }

    if (HI_NULL == gs_PngApiInstance[s32Handle - 1].pReadParam)
    {
        gs_PngApiInstance[s32Handle - 1].pReadParam = (PNG_READ_INFO_S *)malloc(sizeof(PNG_READ_INFO_S));
        if (HI_NULL == gs_PngApiInstance[s32Handle - 1].pReadParam)
        {
            pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
            *ppStream = NULL;
            *pu32Len = 0;
            return;
        }
        gs_PngApiInstance[s32Handle - 1].pReadParam->u32Read = 0;
        gs_PngApiInstance[s32Handle - 1].pReadParam->pstMemNode = gs_PngApiInstance[s32Handle - 1].pMemHead;
    }

    pReadParam = gs_PngApiInstance[s32Handle - 1].pReadParam;
    if (NULL == pReadParam->pstMemNode)
    {
        pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);
        *ppStream = NULL;
        *pu32Len = 0;
        return;
    }
    *ppStream = pReadParam->pstMemNode->stBuf.pVir;
    *pu32Len = pReadParam->pstMemNode->stBuf.u32Len;

    pReadParam->pstMemNode = pReadParam->pstMemNode->pNext;

    pthread_mutex_unlock(&gs_PngApiInstance[s32Handle - 1].stLock);

    return;
}
#endif
