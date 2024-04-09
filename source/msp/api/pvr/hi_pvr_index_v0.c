/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_pvr_index.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2008/04/16
  Description   : INDEX module
  History       :
  1.Date        : 2008/04/16
    Author      : sdk
    Modification: Created file

******************************************************************************/
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/times.h>
#include <assert.h>
#include "hi_module.h"
#include "hi_mpi_mem.h"

#include "pvr_debug.h"
#include "hi_pvr_index.h"
#include "hi_pvr_index_inter.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* End of #ifdef __cplusplus */

#define PVR_IDX_TRANSFER_FRM_TO_OFFSET0(Frm, handle) ((Frm) * sizeof(PVR_INDEX_ENTRY_S) + handle->u32IdxStartOffsetLen)

#ifdef HI_PVR_EXTRA_BUF_SUPPORT
static HI_BOOL PVRIndexChechBeCached0(HI_U32 u32ReadFrm, HI_U32 u32StartNum, HI_U32 u32UsedNum)
{
    if ((u32ReadFrm >= u32StartNum) && (u32ReadFrm < (u32StartNum + u32UsedNum)))
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}

static HI_BOOL PVRIndexCheckReadCacheHeadValid0(HI_U32 u32Head, HI_U32 u32ReadFrm, PVR_CYC_HEADER_INFO_S *pstCycHeaderInfo)
{
    //���Ƶ��������ȡ֡����start���֣���֤head��С��start��
    //��ȡ֡����end���֣���headʼ����Ч
    if (pstCycHeaderInfo->u32StartFrame > pstCycHeaderInfo->u32EndFrame)
    {
        if (u32ReadFrm >= pstCycHeaderInfo->u32StartFrame && u32Head >= pstCycHeaderInfo->u32StartFrame)
            return HI_TRUE;

        if (u32ReadFrm <= pstCycHeaderInfo->u32EndFrame)
            return HI_TRUE;
    }
    //�ǻ����������֤head����start����Ч
    else
    {
        if (u32Head >= pstCycHeaderInfo->u32StartFrame)
            return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL PVRIndexCheckReadCacheTailValid0(HI_U32 u32Tail, HI_U32 u32ReadFrm, PVR_CYC_HEADER_INFO_S *pstCycHeaderInfo)
{
    if (pstCycHeaderInfo->u32StartFrame > pstCycHeaderInfo->u32EndFrame)
    {
        if (u32ReadFrm <= pstCycHeaderInfo->u32EndFrame && u32Tail <= pstCycHeaderInfo->u32EndFrame)
            return HI_TRUE;
        
        if (u32ReadFrm >= pstCycHeaderInfo->u32StartFrame)
            return HI_TRUE;
    }
    else
    {
        if (u32Tail <=  pstCycHeaderInfo->u32EndFrame)
            return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL PVRIndexCheckReadFrmIsInCache0(PVR_CYC_MGR_S *pstCycMgr,HI_U32 u32ReadFrm, HIPVR_IDX_BUF_S *pstIdxBuf)
{
    HI_U32 u32ReadFrmInWriteCache, u32WriteFrmInWriteCache;

    if (pstIdxBuf->u32UsedNum == 0)
    {
        return HI_FALSE;
    }

    u32WriteFrmInWriteCache = pstCycMgr->u32EndFrame;
    u32ReadFrmInWriteCache = PVR_IDX_PREV_N_POS_IN_CYC(pstCycMgr->u32EndFrame, 
                                PVR_IDX_DISTANCE_IN_CYC(pstIdxBuf->u32Write,pstIdxBuf->u32Read,PVR_INDEX_WRITE_CACHE_NUM),
                                (pstCycMgr->u32LastFrame + 1));

//���Cache  ��û�з������ƣ����ȡ��֡����С�ڵ���endframe
    if (u32WriteFrmInWriteCache > u32ReadFrmInWriteCache)
    {
        if ((u32ReadFrm <= pstCycMgr->u32EndFrame) && (u32ReadFrm >= u32ReadFrmInWriteCache))
        {
            return HI_TRUE;
        }
    }
//���Cache  �з������ƣ����ȡ��֡����С�ڵ���
    else
    {
        if ((u32ReadFrm <= pstCycMgr->u32EndFrame) || (u32ReadFrm >= u32ReadFrmInWriteCache))
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}


static HI_BOOL PVRIndexCheckReadFrmIsInFile0(HI_U32 u32ReadFrm,PVR_CYC_HEADER_INFO_S *pstCycHeaderInfo)
{
    HI_U32 u32StartFrame, u32EndFrame, u32LastFrame;

    u32StartFrame = pstCycHeaderInfo->u32StartFrame;
    u32EndFrame   = pstCycHeaderInfo->u32EndFrame;
    u32LastFrame  = pstCycHeaderInfo->u32LastFrame;

    /*just beginning of recording*/
    if (0 == u32LastFrame)
    {
        return HI_FALSE;
    }

    if (u32StartFrame < u32EndFrame)
    {
        if ((u32ReadFrm >= u32StartFrame) && (u32ReadFrm <= u32EndFrame))
        {
            return HI_TRUE;
        }
    }
    else
    {
        /* rewind case */
        if (((u32ReadFrm >= u32StartFrame) && (u32ReadFrm <= u32LastFrame))
            || (u32ReadFrm <= u32EndFrame))
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}

static ssize_t PVRIndexReadIndexFromCache0(PVR_INDEX_HANDLE hIndex, HI_VOID *pBuf, HI_U32 u32ReadFrm)
{
    HI_S32 s32Start, s32ReadSize;
    HI_U32 u32CacheEndNum, u32CacheSize;
    HI_BOOL bReadCacheInvalid = HI_FALSE;
    HIPVR_IDX_BUF_S *pstReadCache = HI_NULL;

    if ((-1 == hIndex->stCycMgr.u32EndFrame ) || (-1 == hIndex->stCycMgr.u32LastFrame))
    {
        HI_WARN_PVR("Cache and file has no data!!!\n");
        return -1;
    }

    pstReadCache = &hIndex->stIdxReadCache;

    u32CacheSize = PVR_INDEX_READ_CACHE_NUM * sizeof(PVR_INDEX_ENTRY_S);

    //ʱ�Ƴ������ȼ���Ƿ���writecache��
    if (hIndex->bIsRec)
    {
        PVR_IDX_CACHE_LOCK(&(hIndex->stIdxWriteCache.stCacheMutex));
        if (PVRIndexCheckReadFrmIsInCache0(&hIndex->stCycMgr, u32ReadFrm, &hIndex->stIdxWriteCache))
        {
            HI_U32 u32Read;
            u32Read = PVR_IDX_PREV_N_POS_IN_CYC(PVR_IDX_PREV_N_POS_IN_CYC(hIndex->stIdxWriteCache.u32Write, 1, PVR_INDEX_WRITE_CACHE_NUM),
                                                PVR_IDX_DISTANCE_IN_CYC(hIndex->stCycMgr.u32EndFrame, u32ReadFrm, (hIndex->stCycMgr.u32LastFrame + 1)),
                                                PVR_INDEX_WRITE_CACHE_NUM);
            memcpy(pBuf, hIndex->stIdxWriteCache.pu8Addr + u32Read*sizeof(PVR_INDEX_ENTRY_S),
                   sizeof(PVR_INDEX_ENTRY_S));
            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxWriteCache.stCacheMutex));
            return sizeof(PVR_INDEX_ENTRY_S);
        }
        PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxWriteCache.stCacheMutex));
    }

    //����Ƿ����ļ���
    if (!PVRIndexCheckReadFrmIsInFile0(u32ReadFrm, &hIndex->pstExtraBuffer->stFileCycInfo))
    {
        HI_WARN_PVR("ReadFrm %d is not in file or cache! s/e/l:%d/%d/%d\n",
                    u32ReadFrm, hIndex->pstExtraBuffer->stFileCycInfo.u32StartFrame, hIndex->pstExtraBuffer->stFileCycInfo.u32EndFrame,
                    hIndex->pstExtraBuffer->stFileCycInfo.u32LastFrame);
        return 0;
    }

    //���readcache  ����û���ݣ���start  ��ʼ��ȡ
    PVR_IDX_CACHE_LOCK(&(hIndex->stIdxReadCache.stCacheMutex));

    if (hIndex->stIdxReadCache.u32UsedNum == 0)
    {
        s32Start = hIndex->pstExtraBuffer->stFileCycInfo.u32StartFrame;
        if ((s32Start + PVR_INDEX_READ_CACHE_NUM) > hIndex->pstExtraBuffer->stFileCycInfo.u32LastFrame)
        {
            u32CacheSize = (hIndex->pstExtraBuffer->stFileCycInfo.u32LastFrame - s32Start + 1)*sizeof(PVR_INDEX_ENTRY_S);
        }

        s32ReadSize = PVR_READALL(hIndex->stIdxReadCache.pu8Addr, u32CacheSize, hIndex->s32ReadFd,
                        (off_t)PVR_IDX_TRANSFER_FRM_TO_OFFSET0(s32Start, hIndex));

        if ((s32ReadSize <= 0) || (s32ReadSize % sizeof(PVR_INDEX_ENTRY_S)))
        {
            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));
            HI_ERR_PVR("Readcache no data and read failed! start=%d want=%d readed=%d\n",
                        s32Start, u32CacheSize, s32ReadSize);
            return -1;
        }
        else
        {
            hIndex->stIdxReadCache.u32StartNum = s32Start;
            hIndex->stIdxReadCache.u32UsedNum = s32ReadSize/sizeof(PVR_INDEX_ENTRY_S);
        }
    }

//��readcache���б߽��飬��֤ͷ����β��������Ч������
    if (PVRIndexCheckReadCacheHeadValid0(hIndex->stIdxReadCache.u32StartNum, u32ReadFrm, &hIndex->pstExtraBuffer->stFileCycInfo) &&
        PVRIndexCheckReadCacheTailValid0(hIndex->stIdxReadCache.u32StartNum + hIndex->stIdxReadCache.u32UsedNum - 1, u32ReadFrm, &hIndex->pstExtraBuffer->stFileCycInfo))
    {
        bReadCacheInvalid = HI_FALSE;
    }
    else
    {
        bReadCacheInvalid = HI_TRUE;
    }

//���readcacheû�����ǲ���readcache�߽���Ч�������Ƿ�cache�ɹ����ɹ��򷵻أ�ʧ�������¶�ȡ
    if ((pstReadCache->bDirty == HI_FALSE) && (bReadCacheInvalid == HI_FALSE))
    {
        if (PVRIndexChechBeCached0(u32ReadFrm, hIndex->stIdxReadCache.u32StartNum, hIndex->stIdxReadCache.u32UsedNum))
        {
            memcpy(pBuf,hIndex->stIdxReadCache.pu8Addr+(u32ReadFrm - hIndex->stIdxReadCache.u32StartNum)*sizeof(PVR_INDEX_ENTRY_S),
                   sizeof(PVR_INDEX_ENTRY_S));

            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));

            return sizeof(PVR_INDEX_ENTRY_S);
        }
    }
//��������ǻ���ûcache  �У����¶�ȡcache

    {
        /* readcache  ���ô��ڻ��ƣ���read  Ϊ���ĵĴ���*/
        s32Start = (HI_S32)(u32ReadFrm - PVR_INDEX_READ_CACHE_NUM/2);
        if (s32Start < 0)
        {
            s32Start = 0;
        }
        //��ͷ�����б߽��飬��֤ͷ��������Ч������
        if (!PVRIndexCheckReadCacheHeadValid0((HI_U32)s32Start, u32ReadFrm, &hIndex->pstExtraBuffer->stFileCycInfo))
        {
            s32Start = hIndex->pstExtraBuffer->stFileCycInfo.u32StartFrame;
        }

        u32CacheEndNum = s32Start + PVR_INDEX_READ_CACHE_NUM - 1;
        if (u32CacheEndNum > hIndex->pstExtraBuffer->stFileCycInfo.u32LastFrame)
        {
            u32CacheEndNum = hIndex->pstExtraBuffer->stFileCycInfo.u32LastFrame;
            u32CacheSize = (u32CacheEndNum - s32Start + 1) * sizeof(PVR_INDEX_ENTRY_S);
        }
        //��β�����б߽��飬��֤β��������Ч������
        if (!PVRIndexCheckReadCacheTailValid0(u32CacheEndNum, u32ReadFrm, &hIndex->pstExtraBuffer->stFileCycInfo))
        {
            u32CacheEndNum = hIndex->pstExtraBuffer->stFileCycInfo.u32EndFrame;
            u32CacheSize = (u32CacheEndNum - s32Start + 1)*sizeof(PVR_INDEX_ENTRY_S);
        }

        s32ReadSize = PVR_READALL(hIndex->stIdxReadCache.pu8Addr, u32CacheSize, hIndex->s32ReadFd,
                        (off_t)PVR_IDX_TRANSFER_FRM_TO_OFFSET0(s32Start, hIndex));
        if ((s32ReadSize <= 0) || (s32ReadSize % sizeof(PVR_INDEX_ENTRY_S)))
        {
            HI_ERR_PVR("Read file to cache failed! start=%d want=%d readed=%d s/e/l:%d/%d/%d\n",
                        s32Start, u32CacheSize, s32ReadSize, hIndex->pstExtraBuffer->stFileCycInfo.u32StartFrame,
                        hIndex->pstExtraBuffer->stFileCycInfo.u32EndFrame, hIndex->pstExtraBuffer->stFileCycInfo.u32LastFrame);
            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));
            return -1;
        }

        hIndex->stIdxReadCache.u32StartNum = (HI_U32)s32Start;
        hIndex->stIdxReadCache.u32UsedNum  = (HI_U32)(s32ReadSize)/sizeof(PVR_INDEX_ENTRY_S);

        if (!PVRIndexChechBeCached0(u32ReadFrm, hIndex->stIdxReadCache.u32StartNum, hIndex->stIdxReadCache.u32UsedNum))
        {
            HI_ERR_PVR("Readcache is still not cached! readfrm %d end %d last %d cachestart %d usdnum %d cachesize %d readsize %d\n",
                        u32ReadFrm, hIndex->stCycMgr.u32EndFrame, hIndex->stCycMgr.u32LastFrame,hIndex->stIdxReadCache.u32StartNum,
                        hIndex->stIdxReadCache.u32UsedNum,u32CacheSize, s32ReadSize);
            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));
            return -1;
        }

        memcpy(pBuf, hIndex->stIdxReadCache.pu8Addr + (u32ReadFrm - hIndex->stIdxReadCache.u32StartNum)*sizeof(PVR_INDEX_ENTRY_S),
               sizeof(PVR_INDEX_ENTRY_S));
        pstReadCache->bDirty = HI_FALSE;

    }

    PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));

    /*PVR_INDEX_ENTRY_S *ptmp = (PVR_INDEX_ENTRY_S *)pBuf;
    HI_INFO_PVR("read cache index %d startnum %d, cachesize=%d displaytime %d\n",
             u32ReadFrm,
             hIndex->stIdxReadCache.u32StartNum,
             u32CacheSize,
             ptmp->u32DisplayTimeMs);*/
    return sizeof(PVR_INDEX_ENTRY_S);
}
#endif

#ifndef HI_PVR_EXTRA_BUF_SUPPORT
/*check if the offset in read cache:1 all in cache,0 not in cache,2 offset in cache*/
static HI_S32 PVRIndexIfOffsetReadCache0(PVR_INDEX_HANDLE handle, HI_U32 u32Offset, HI_U32 u32Size)
{
    if (handle->stIdxReadCache.u32BufferLen && handle->stIdxReadCache.u32UsedSize)/*have data cached*/
    {
        if ((u32Offset >= handle->stIdxReadCache.u32StartOffset) && 
            ((u32Offset - handle->stIdxReadCache.u32StartOffset) <= handle->stIdxReadCache.u32UsedSize))
        {
            if ((u32Offset - handle->stIdxReadCache.u32StartOffset + u32Size) <= handle->stIdxReadCache.u32UsedSize)
            {
                return 1;
            }
            return 2;
        }
    }
    return 0;
}

static ssize_t PVRIndexCacheReadIdx0(PVR_INDEX_HANDLE handle, PVR_FILE fd, HI_VOID* pData, size_t size, HI_U32 u32Offset)
{
    ssize_t readNum = 0;
    HI_S32 s32CachedFlag;
    HI_S32 s32CacheStartReadOffset;
    HI_U8* pDataAddr;
    static HI_U32 u32CacheNum = 0,NotCacheNum = 0;

    PVR_IDX_CACHE_LOCK(&(handle->stIdxReadCache.stCacheMutex));

    /*no read cache or beyond the cache size, read data from the file*/
    if ((HI_NULL == handle->stIdxReadCache.pu8Addr)
        || (0 == handle->stIdxReadCache.u32BufferLen)
        || (size > handle->stIdxReadCache.u32BufferLen))
    {
        PVR_READ_INDEX_DIRECTLY(readNum, pData, size, fd, (off_t)u32Offset, handle);
        NotCacheNum++;
    }
    else
    {
        s32CachedFlag = PVRIndexIfOffsetReadCache0(handle, u32Offset,size);
        if (s32CachedFlag == 1)/*cached*/
        {
            pDataAddr = handle->stIdxReadCache.pu8Addr + u32Offset - handle->stIdxReadCache.u32StartOffset;
            memcpy(pData,pDataAddr,size);
            readNum = size;
            u32CacheNum ++;
        }
        else/*not cached*/
        {
            /*
            flush cache buffer:
            --------------------------------------------------
            |                    /     \                     |
            |       offset in middle of cache buffer         |
            |                    \     /                     |
            ------------------------X-------------------------
            /\                      /\                      /\
            ||                      ||                      ||
            cache start        offset          cache end
            */
            s32CacheStartReadOffset = (HI_S32)(u32Offset - (handle->stIdxReadCache.u32BufferLen / 2));
            if (s32CacheStartReadOffset < 0)
            {
                s32CacheStartReadOffset = 0;
            }

            PVR_READ_INDEX_DIRECTLY(readNum, handle->stIdxReadCache.pu8Addr, handle->stIdxReadCache.u32BufferLen,
                                    fd, (off_t)s32CacheStartReadOffset, handle);
            handle->stIdxReadCache.u32UsedSize = readNum;
            handle->stIdxReadCache.u32StartOffset = s32CacheStartReadOffset;
            s32CachedFlag = PVRIndexIfOffsetReadCache0(handle, u32Offset, size);/*check again*/
            if (s32CachedFlag == 1)
            {
                pDataAddr = handle->stIdxReadCache.pu8Addr + u32Offset - handle->stIdxReadCache.u32StartOffset;
                memcpy(pData,pDataAddr,size);
                readNum = size;
                NotCacheNum++;
            }
            else/*try read directly */
            {
                HI_WARN_PVR("idx read cache not works!\n");
                PVR_READ_INDEX_DIRECTLY(readNum, pData, size, fd, (off_t)u32Offset, handle);
                NotCacheNum++;
            }
        }
    }

    if ((!(u32CacheNum%5000 ) && u32CacheNum != 0) || (!(NotCacheNum %5000) && NotCacheNum != 0))
    {
        HI_INFO_PVR(">>>> u32CacheNum:%d,NotCacheNum:%d\n",u32CacheNum,NotCacheNum);
    }
    PVR_IDX_CACHE_UNLOCK(&(handle->stIdxReadCache.stCacheMutex));
    return readNum;
}

#if 0  /*obsolete APIs*/
HI_S32 PVRIndex_CacheWriteIdx0(PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_NEW_S* pstEntry,
                               HI_S32 s32Num, HI_U32 u32Offset,HI_BOOL* bWriteFlag)
{
    HI_U32 u32SaveSz;
    HI_U8 *pu8Data = HI_NULL;
    HI_U32 u32Len = 0;

    PVR_IDX_CACHE_LOCK(&(handle->stIdxWriteCache.stCacheMutex));
    pu8Data = (HI_U8 *)&(pstEntry->stEntry1);
    u32Len = sizeof(PVR_INDEX_ENTRY_S) * s32Num;

    if (handle->stIdxWriteCache.u32BufferLen == 0)/*no cache buffer*/
    {
        PVR_WRITE_INDEX(u32SaveSz, u32Len, pu8Data, handle->s32WriteFd,u32Offset, handle);
        *bWriteFlag = HI_TRUE;
    }
    else
    {
        /*
        1. Data offset jump,may be means idx rewind.
        2. Cache buffer not enough
        should flush cache first(write all cached data to file),the write new data into cache.
        */
        //1.flush cache first(write all cached data to file)
        if ((u32Offset != (handle->stIdxWriteCache.u32StartOffset + handle->stIdxWriteCache.u32UsedSize))
            ||((handle->stIdxWriteCache.u32BufferLen - handle->stIdxWriteCache.u32UsedSize) < u32Len))

        {
            //lint -e774
            PVR_WRITE_INDEX(u32SaveSz, handle->stIdxWriteCache.u32UsedSize,handle->stIdxWriteCache.pu8Addr,
                            handle->s32WriteFd,handle->stIdxWriteCache.u32StartOffset, handle);
            *bWriteFlag = HI_TRUE;
            handle->stIdxWriteCache.u32UsedSize = 0;
            handle->stIdxWriteCache.u32StartOffset = 0;
            //lint +e774
        }
        //2. write new data into cache
        memcpy(handle->stIdxWriteCache.pu8Addr + handle->stIdxWriteCache.u32UsedSize,pu8Data,u32Len);
        if(handle->stIdxWriteCache.u32UsedSize == 0)//cache is empty
        {
           handle->stIdxWriteCache.u32StartOffset = u32Offset;
        }
        handle->stIdxWriteCache.u32UsedSize +=  u32Len;
    }
    PVR_IDX_CACHE_UNLOCK(&(handle->stIdxWriteCache.stCacheMutex));

    PVR_IDX_CACHE_LOCK(&(handle->stIdxReadCache.stCacheMutex));
    if (PVRIndexIfOffsetReadCache0(handle,u32Offset,u32Len))//write data been cached or appears in cache
    {
        handle->stIdxReadCache.u32UsedSize = 0;//invalid the read cache buffer
    }
    PVR_IDX_CACHE_UNLOCK(&(handle->stIdxReadCache.stCacheMutex));

    return HI_SUCCESS;
}
#endif
#endif
size_t PVRIndex_ReadIndex0(PVR_INDEX_ENTRY_NEW_S *pstEntryBuf, PVR_FILE fd, HI_U64 u64Offset, PVR_INDEX_HANDLE handle)
{
    size_t readSz = 0;

    if (HI_NULL == pstEntryBuf || (HI_NULL == handle) || (PVR_FILE_INVALID_FILE == fd))
    {
        HI_ERR_PVR("some parameters is invalid! pstEntryBuf(%p), handle(%p), fd(%d)\n", pstEntryBuf, handle, fd);
        return 0;
    }

#ifndef HI_PVR_EXTRA_BUF_SUPPORT
    readSz = PVRIndexCacheReadIdx0(handle, fd, &(pstEntryBuf->stEntry1), (HI_U32)sizeof(PVR_INDEX_ENTRY_S), (off_t)u64Offset);
#else
    readSz = PVRIndexReadIndexFromCache0(handle,(HI_VOID*)&(pstEntryBuf->stEntry1), u64Offset/sizeof(PVR_INDEX_ENTRY_S));
#endif
    return readSz;
}


HI_S32 PVRIndex_GetFrameInfoByHeaderInfo0(PVR_IDX_HEADER_INFO_S *pstHeaderInfo,
                                                        PVR_INDEX_ENTRY_NEW_S *pstStartEntry,
                                                        PVR_INDEX_ENTRY_NEW_S*pstEndEntry,
                                                        HI_S32 s32FdIdx)
{
    HI_S32 s32Offset = 0;
    size_t readNum = 0;

    PVR_CHECK_POINTER(pstHeaderInfo);
    PVR_CHECK_POINTER(pstStartEntry);
    PVR_CHECK_POINTER(pstEndEntry);

    s32Offset = (HI_S32)(pstHeaderInfo->u32HeaderLen + sizeof(PVR_INDEX_ENTRY_S) * pstHeaderInfo->stCycInfo.u32StartFrame);
    readNum = PVR_READ(&(pstStartEntry->stEntry1), sizeof(PVR_INDEX_ENTRY_S), s32FdIdx, s32Offset);
    if (readNum != (HI_S32)sizeof(PVR_INDEX_ENTRY_S))
    {
        HI_ERR_PVR("read start_idx failed, offset:%d.\n", s32Offset);
        HI_ERR_PVR("The index file is too small, can't play.\n");
        return HI_ERR_PVR_FILE_CANT_READ;
    }

    s32Offset = (HI_S32)(pstHeaderInfo->u32HeaderLen + sizeof(PVR_INDEX_ENTRY_S) *
                pstHeaderInfo->stCycInfo.u32EndFrame);
    readNum = PVR_READ(&(pstEndEntry->stEntry1), sizeof(PVR_INDEX_ENTRY_S), s32FdIdx, s32Offset);
    if (readNum != (HI_S32)sizeof(PVR_INDEX_ENTRY_S))
    {
        HI_ERR_PVR("read end_idx failed, endframe:%d, offset:%d.\n",pstHeaderInfo->stCycInfo.u32EndFrame, s32Offset);
        return HI_ERR_PVR_FILE_CANT_READ;
    }
    return HI_SUCCESS;
}

HI_S32 PVRIndex_GetEntryByNum0(const PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_NEW_S *pEntry, HI_U32 u32FrameNum)
{
    ssize_t readNum ;

    PVR_CHECK_POINTER(handle);
    PVR_CHECK_POINTER(pEntry);

    readNum = PVRIndex_ReadIndex0(pEntry,handle->s32ReadFd,(u32FrameNum * sizeof(PVR_INDEX_ENTRY_S)),handle);
    if (readNum != (ssize_t)sizeof(PVR_INDEX_ENTRY_S))
    {
        if (-1 == readNum)
        {
            HI_WARN_PVR("read failed in PVRIndexGetEntryByNum");
            return HI_ERR_PVR_FILE_CANT_READ;
        }
        else
        {
            HI_WARN_PVR("read to end, S:%d, E:%d, L:%d, C:%d G:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
                   handle->stCycMgr.u32LastFrame, handle->u32ReadFrame, u32FrameNum);
            return HI_ERR_PVR_FILE_TILL_END;
        }
    }

    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

