/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_hw.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include "drv_win_buffer.h"
#include "drv_disp_bufcore.h"
#include "drv_disp_buffer.h"
#include "drv_window.h"
#include "drv_win_priv.h"
#include "drv_vdec_ext.h"
#include "hi_drv_module.h"

#include "drv_win_hdr.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define  TMP_MMZ_BUFFER_NUM 32

#if defined(HI_NVR_SUPPORT)
#define  MMZ_REF_COUNT_MAX  782
#define  OPEN_REFCNT 0
#else
#define  MMZ_REF_COUNT_MAX  392
#define  OPEN_REFCNT 1
#endif

typedef struct MemBufRef
{
    spinlock_t NodeSpinLock;
    DISP_MMZ_BUF_S  aMMZMemBufForReferenceOpt[MMZ_REF_COUNT_MAX];
    volatile HI_U32  u32MemBufWrPtr;
    volatile HI_U32  u32MemBufRdPtr;
} MemBufRef_S;

HI_VOID WinBuf_DebugAddIncreaseMemRefCnt(WB_DEBUG_INFO_S *pstInfo);
HI_VOID WinBuf_DebugAddDecreaseMemRefCnt(WB_DEBUG_INFO_S *pstInfo);

MemBufRef_S g_stMemBufRef =
{
    .NodeSpinLock = __SPIN_LOCK_UNLOCKED(g_stMemBufRef.NodeSpinLock),
    .aMMZMemBufForReferenceOpt = {{0, 0, 0, 0, 0}},
    .u32MemBufWrPtr = 0,
    .u32MemBufRdPtr = 0,
};

#if OPEN_REFCNT
static MemBufRef_S *GetMemBufRef(HI_VOID)
{
    return &g_stMemBufRef;
}
#endif

static HI_S32 CheckWhetherFrameRefcnt(HI_U32 u32Addr, HI_BOOL bSecure, HI_BOOL *bRefcnt)
{
    HI_S32 s32IsIonMemType;
#ifdef  HI_SMMU_SUPPORT
    SMMU_BUFFER_S stSMMU_MMZBuf = {0};
#else
    MMZ_BUFFER_S  stSMMU_MMZBuf = {0};
#endif

    /* No reference count operation if Unsecure-ION type menery .
       Equal to 4K picture sence*/
    if (!bSecure)
    {
        stSMMU_MMZBuf.u32StartSmmuAddr = u32Addr;
        if (HI_SUCCESS != HI_DRV_SMMU_Query_Buffer_Source(&stSMMU_MMZBuf, &s32IsIonMemType))
        {
            WIN_ERROR("Call HI_DRV_SMMU_Query_Buffer_Source failed !\n");
            return HI_FAILURE;
        }

        if (s32IsIonMemType)
        {
            *bRefcnt = HI_FALSE;
            return HI_SUCCESS;
        }
    }

    *bRefcnt = HI_TRUE;

    return HI_SUCCESS;
}

static HI_S32 IncreaseFrameMemRefcnt(HI_U32  u32StartPhyAddr,
                                     HI_U32  u32Size,
                                     HI_BOOL bSecure)
{
#if OPEN_REFCNT
    HI_S32 s32Ret = HI_FAILURE;

#ifdef  HI_SMMU_SUPPORT
    SMMU_BUFFER_S stSMMUBuf = {0};
#else
    MMZ_BUFFER_S stMMZBuf = {0};
#endif

    if (HI_TRUE == bSecure)
    {
#ifdef  HI_SMMU_SUPPORT
        stSMMUBuf.pu8StartVirAddr  =  0;
        stSMMUBuf.u32StartSmmuAddr =  u32StartPhyAddr;
        stSMMUBuf.u32Size          =  u32Size;

        s32Ret = HI_DRV_SECSMMU_Buffer_Get(&stSMMUBuf);
#else
        stMMZBuf.pu8StartVirAddr = 0;
        stMMZBuf.u32StartPhyAddr = u32StartPhyAddr;
        stMMZBuf.u32Size         = u32Size;

        s32Ret = HI_DRV_SECMMZ_Buffer_Get(&stMMZBuf);
#endif
    }
    else
    {
#ifdef  HI_SMMU_SUPPORT
        stSMMUBuf.pu8StartVirAddr  =  0;
        stSMMUBuf.u32StartSmmuAddr =  u32StartPhyAddr;
        stSMMUBuf.u32Size          =  u32Size;

        s32Ret = HI_DRV_SMMU_Buffer_Get(&stSMMUBuf);
#else
        stMMZBuf.pu8StartVirAddr = 0;
        stMMZBuf.u32StartPhyAddr = u32StartPhyAddr;
        stMMZBuf.u32Size         = u32Size;

        s32Ret = HI_DRV_MMZ_Buffer_Get(&stMMZBuf);
#endif
    }

    return s32Ret;
#else
    return HI_SUCCESS;
#endif
}

static HI_S32 DecreaseFrameMemRefcnt(HI_U32  u32StartPhyAddr,
                                     HI_U32  u32Size,
                                     HI_BOOL bSecure)
{
#if  OPEN_REFCNT
    HI_SIZE_T irqflag = 0;
    HI_U32  u32Wptr = 0, u32Rdtr = 0;
    HI_S32 s32Ret = HI_FAILURE;
    MemBufRef_S *pMemBufRef = GetMemBufRef();

    spin_lock_irqsave(&pMemBufRef->NodeSpinLock, irqflag);

    u32Wptr = pMemBufRef->u32MemBufWrPtr;
    u32Rdtr = pMemBufRef->u32MemBufRdPtr;

    if (((u32Wptr  + 1) % MMZ_REF_COUNT_MAX) == u32Rdtr)
    {
        WIN_FATAL("The mem ref buf is full,wr:%d, rd:%d\n", u32Wptr, u32Rdtr);
        s32Ret = HI_ERR_VO_BUFQUE_FULL;
        goto __DECREASE_CNT_EXIT;
    }

    pMemBufRef->aMMZMemBufForReferenceOpt[u32Wptr].pu8StartVirAddr = 0;
    pMemBufRef->aMMZMemBufForReferenceOpt[u32Wptr].u32StartPhyAddr = u32StartPhyAddr;
    pMemBufRef->aMMZMemBufForReferenceOpt[u32Wptr].u32Size = u32Size;
    pMemBufRef->aMMZMemBufForReferenceOpt[u32Wptr].bSecure = bSecure;

#ifdef  HI_SMMU_SUPPORT
    pMemBufRef->aMMZMemBufForReferenceOpt[u32Wptr].bSmmu   = HI_TRUE;
#else
    pMemBufRef->aMMZMemBufForReferenceOpt[u32Wptr].bSmmu   = HI_FALSE;
#endif

    pMemBufRef->u32MemBufWrPtr = (u32Wptr  + 1) % MMZ_REF_COUNT_MAX;
    s32Ret = HI_SUCCESS;

__DECREASE_CNT_EXIT:

    spin_unlock_irqrestore(&pMemBufRef->NodeSpinLock, irqflag);
    return s32Ret;
#else
    return HI_SUCCESS;
#endif

}

HI_S32  IncreaseFrameCntAccordingToFrame(HI_DRV_VIDEO_FRAME_S *pstFrame,
        WB_DEBUG_INFO_S *pstInfo)
{
    HI_U32 u32PhyAddr_Y               = 0;
    HI_U32 u32PhyAddr_Y_RightEye      = 0;
    HI_S32 s32Ret = HI_FAILURE;
    HI_BOOL bRefcnt;

    if (pstFrame->ePixFormat >= HI_DRV_PIX_BUTT)
    {
        WIN_ERROR("parameter out of range.\n");
        return HI_ERR_VO_FRAME_INFO_ERROR;
    }

    if (((pstFrame->ePixFormat >= HI_DRV_PIX_FMT_NV08_CMP)
         && (pstFrame->ePixFormat <= HI_DRV_PIX_FMT_NV42_CMP))
        || (pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
        || (pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP))
    {
        u32PhyAddr_Y            = pstFrame->stBufAddr[0].u32PhyAddr_YHead;
        u32PhyAddr_Y_RightEye   = pstFrame->stBufAddr[1].u32PhyAddr_YHead;
    }
    else
    {
        u32PhyAddr_Y            = pstFrame->stBufAddr[0].u32PhyAddr_Y;
        u32PhyAddr_Y_RightEye   = pstFrame->stBufAddr[1].u32PhyAddr_Y;
    }

    if (HI_SUCCESS != CheckWhetherFrameRefcnt(u32PhyAddr_Y, pstFrame->bSecure, &bRefcnt))
    {
        return HI_ERR_VO_FRAME_INFO_ERROR;
    }

    if (!bRefcnt)
    {
        return HI_SUCCESS;
    }

    s32Ret = IncreaseFrameMemRefcnt(u32PhyAddr_Y, 0, pstFrame->bSecure);
    if (HI_SUCCESS == s32Ret)
    {
        WinBuf_DebugAddIncreaseMemRefCnt(pstInfo);
    }
    else
    {
        WIN_ERROR("IncreaseFrameMemRefcnt fai,maybe addr is invalib.\n");
        return HI_ERR_VO_FRAME_INFO_ERROR;
    }

    if (HI_DRV_FT_NOT_STEREO != pstFrame->eFrmType)
    {
        s32Ret = IncreaseFrameMemRefcnt(u32PhyAddr_Y_RightEye, 0, pstFrame->bSecure);
        if (HI_SUCCESS == s32Ret)
        {
            WinBuf_DebugAddIncreaseMemRefCnt(pstInfo);
        }
        else
        {
            WIN_ERROR("IncreaseFrameMemRefcnt fai,maybe addr is invalib.\n");
            return HI_ERR_VO_FRAME_INFO_ERROR;
        }
    }


    return HI_SUCCESS;
}

static HI_VOID  GetFrameAddr(HI_DRV_VIDEO_FRAME_S *pstFrame,
                             HI_U32 *pu32PhyAddr_Y,
                             HI_U32 *pu32PhyAddr_Y_RightEye)
{

    if (((pstFrame->ePixFormat >= HI_DRV_PIX_FMT_NV08_CMP)
         && (pstFrame->ePixFormat <= HI_DRV_PIX_FMT_NV42_CMP))
        || (pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
        || (pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP))
    {
        *pu32PhyAddr_Y            = pstFrame->stBufAddr[0].u32PhyAddr_YHead;
        *pu32PhyAddr_Y_RightEye   = pstFrame->stBufAddr[1].u32PhyAddr_YHead;
    }
    else
    {
        *pu32PhyAddr_Y            = pstFrame->stBufAddr[0].u32PhyAddr_Y;
        *pu32PhyAddr_Y_RightEye   = pstFrame->stBufAddr[1].u32PhyAddr_Y;
    }

    return;
}

static HI_VOID DecreaseFrameCntAccordingToFrame(HI_DRV_VIDEO_FRAME_S *pstFrame,
                                   WB_DEBUG_INFO_S *pstInfo)
{
    HI_U32 u32PhyAddr_Y               = 0;
    HI_U32 u32PhyAddr_Y_RightEye      = 0;
    HI_S32 s32Ret = HI_FAILURE;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;
    DISP_BUF_NODE_S *pstDispBufNode = HI_NULL;
    HI_DRV_VIDEO_FRAME_S  *pstELFrm = HI_NULL;

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstFrame->u32Priv[0]);
    if ((HI_TRUE == pstPriv->bForFenceUse)
        || (HI_DRV_FRAME_VDP_ALLOCATE_STILL == pstFrame->u32StillFrame))
    {
        return;
    }

    (HI_VOID)GetFrameAddr(pstFrame, &u32PhyAddr_Y, &u32PhyAddr_Y_RightEye);

    s32Ret = DecreaseFrameMemRefcnt(u32PhyAddr_Y, 0, pstFrame->bSecure);
    if (HI_SUCCESS == s32Ret)
    {
        /*first  add the release  statistics value*/
        WinBuf_DebugAddDecreaseMemRefCnt(pstInfo);
    }

    /*second,   release  3d right eye or el frame.*/
    if (HI_DRV_FT_NOT_STEREO != pstFrame->eFrmType)
    {
        s32Ret = DecreaseFrameMemRefcnt(u32PhyAddr_Y_RightEye, 0, pstFrame->bSecure);
        if (HI_SUCCESS == s32Ret)
        {
            WinBuf_DebugAddDecreaseMemRefCnt(pstInfo);
        }
    }
    else
    {
        /*judge whether el frame exist, if exist then release.*/
        pstDispBufNode = container_of((HI_U32 *)pstFrame, DISP_BUF_NODE_S, u32Data[0]);
        if (pstDispBufNode->bValidData2)
        {
            pstELFrm = (HI_DRV_VIDEO_FRAME_S *)pstDispBufNode->u32Data2;

            GetFrameAddr(pstELFrm, &u32PhyAddr_Y, &u32PhyAddr_Y_RightEye);
            s32Ret = DecreaseFrameMemRefcnt(u32PhyAddr_Y, 0, pstFrame->bSecure);
            if (HI_SUCCESS == s32Ret)
            {
                WinBuf_DebugAddDecreaseMemRefCnt(pstInfo);
            }
        }
    }



    return;
}



#if OPEN_REFCNT
static HI_VOID PutMemBuf(DISP_MMZ_BUF_S *pstTmpBufNode, HI_U32 u32NodeNum)
{
    HI_U32 i = 0;
    HI_BOOL bRefcnt;
#ifdef  HI_SMMU_SUPPORT
    SMMU_BUFFER_S stSMMU_MMZBuf = {0};
#else
    MMZ_BUFFER_S  stSMMU_MMZBuf = {0};
#endif

    for (i = 0; i < u32NodeNum; i ++)
    {
        if (pstTmpBufNode[i].bSecure)
        {
#ifdef  HI_SMMU_SUPPORT
            stSMMU_MMZBuf.pu8StartVirAddr  = pstTmpBufNode[i].pu8StartVirAddr;
            stSMMU_MMZBuf.u32StartSmmuAddr = pstTmpBufNode[i].u32StartPhyAddr;
            stSMMU_MMZBuf.u32Size          = pstTmpBufNode[i].u32Size;

            if (HI_SUCCESS != CheckWhetherFrameRefcnt(stSMMU_MMZBuf.u32StartSmmuAddr, pstTmpBufNode[i].bSecure, &bRefcnt))
            {
                continue;
            }
            if (!bRefcnt)
            {
                continue;
            }
            HI_DRV_SECSMMU_Buffer_Put(&stSMMU_MMZBuf);

#else
            stSMMU_MMZBuf.pu8StartVirAddr  = pstTmpBufNode[i].pu8StartVirAddr;
            stSMMU_MMZBuf.u32StartPhyAddr  = pstTmpBufNode[i].u32StartPhyAddr;
            stSMMU_MMZBuf.u32Size          = pstTmpBufNode[i].u32Size;

            if (HI_SUCCESS != CheckWhetherFrameRefcnt(stSMMU_MMZBuf.u32StartSmmuAddr, pstTmpBufNode[i].bSecure, &bRefcnt))
            {
                continue;
            }
            if (!bRefcnt)
            {
                continue;
            }
            HI_DRV_SECMMZ_Buffer_Put(&stSMMU_MMZBuf);
#endif
        }
        else
        {
#ifdef  HI_SMMU_SUPPORT
            stSMMU_MMZBuf.pu8StartVirAddr  = pstTmpBufNode[i].pu8StartVirAddr;
            stSMMU_MMZBuf.u32StartSmmuAddr = pstTmpBufNode[i].u32StartPhyAddr;
            stSMMU_MMZBuf.u32Size          = pstTmpBufNode[i].u32Size;

            if (HI_SUCCESS != CheckWhetherFrameRefcnt(stSMMU_MMZBuf.u32StartSmmuAddr, pstTmpBufNode[i].bSecure, &bRefcnt))
            {
                continue;
            }
            if (!bRefcnt)
            {
                continue;
            }
            HI_DRV_SMMU_Buffer_Put(&stSMMU_MMZBuf);
#else
            stSMMU_MMZBuf.pu8StartVirAddr  = pstTmpBufNode[i].pu8StartVirAddr;
            stSMMU_MMZBuf.u32StartPhyAddr  = pstTmpBufNode[i].u32StartPhyAddr;
            stSMMU_MMZBuf.u32Size          = pstTmpBufNode[i].u32Size;

            if (HI_SUCCESS != CheckWhetherFrameRefcnt(stSMMU_MMZBuf.u32StartSmmuAddr, pstTmpBufNode[i].bSecure, &bRefcnt))
            {
                continue;
            }
            if (!bRefcnt)
            {
                continue;
            }
            HI_DRV_MMZ_Buffer_Put(&stSMMU_MMZBuf);
#endif
        }
    }


    return;
}

#endif

HI_VOID WinBuf_CheckMemRefCntReset(HI_U32 u32WinIndex, WB_POOL_S *pstWinBP)
{
    if (pstWinBP->pstDebugInfo->u32IncreaseMemRefCnt !=
        pstWinBP->pstDebugInfo->u32DecreaseMemRefCnt)
    {
        WIN_FATAL("Memleak, Windex:%x, GetRef:%d, PutRef:%d!\n", u32WinIndex,
                  pstWinBP->pstDebugInfo->u32IncreaseMemRefCnt,
                  pstWinBP->pstDebugInfo->u32DecreaseMemRefCnt);
    }

    return;
}

HI_VOID WinBuf_RetAllMemRefCnts(HI_VOID)
{
#if  OPEN_REFCNT
    HI_SIZE_T irqflag = 0;
    HI_U32  u32MemBufWrPtr = 0, u32MemBufRdPtr = 0, i = 0;
    MemBufRef_S *pMemBufRef = GetMemBufRef();
    DISP_MMZ_BUF_S stTmpBufNode[TMP_MMZ_BUFFER_NUM] = {{0, 0, 0, 0, 0}};

    spin_lock_irqsave(&pMemBufRef->NodeSpinLock, irqflag);

    for (i = 0; i < TMP_MMZ_BUFFER_NUM; i ++ )
    {
        u32MemBufWrPtr = pMemBufRef->u32MemBufWrPtr;
        u32MemBufRdPtr = pMemBufRef->u32MemBufRdPtr;

        if (u32MemBufRdPtr == u32MemBufWrPtr)
        {
            break;
        }

        stTmpBufNode[i].u32StartPhyAddr = pMemBufRef->aMMZMemBufForReferenceOpt[u32MemBufRdPtr].u32StartPhyAddr;
        stTmpBufNode[i].pu8StartVirAddr   = pMemBufRef->aMMZMemBufForReferenceOpt[u32MemBufRdPtr].pu8StartVirAddr;
        stTmpBufNode[i].u32Size       = pMemBufRef->aMMZMemBufForReferenceOpt[u32MemBufRdPtr].u32Size;
        stTmpBufNode[i].bSecure       = pMemBufRef->aMMZMemBufForReferenceOpt[u32MemBufRdPtr].bSecure;

        pMemBufRef->u32MemBufRdPtr = (pMemBufRef->u32MemBufRdPtr + 1) % MMZ_REF_COUNT_MAX;
    }

    spin_unlock_irqrestore(&pMemBufRef->NodeSpinLock, irqflag);

    (HI_VOID) PutMemBuf(stTmpBufNode, i);
#endif

    return;
}

WB_DEBUG_INFO_S *WinBuf_DebugCreate(HI_U32 recordnum)
{
    WB_DEBUG_INFO_S *pstInfo;

    if (0 == recordnum)
    {
        return HI_NULL;
    }

    pstInfo = (WB_DEBUG_INFO_S *)DISP_MALLOC(sizeof(WB_DEBUG_INFO_S));
    if (!pstInfo)
    {
        return HI_NULL;
    }

    DISP_MEMSET(pstInfo, 0 , sizeof(WB_DEBUG_INFO_S));

    pstInfo->u32RecordNumber = recordnum;
    return pstInfo;
}


HI_VOID WinBuf_DebugDestroy(WB_DEBUG_INFO_S *pstInfo)
{
    if (pstInfo)
    {
        DISP_FREE(pstInfo);
    }
}

HI_VOID WinBuf_DebugAddInput(WB_DEBUG_INFO_S *pstInfo, HI_U32 u32FrameId)
{
    pstInfo->u32InputFrameID[pstInfo->u32InputPos] = u32FrameId;

    if (0 != pstInfo->u32RecordNumber)
    {
        pstInfo->u32InputPos = (pstInfo->u32InputPos + 1) % pstInfo->u32RecordNumber;
    }
    else
    {
        WIN_ERROR("Denominator may be zero !\n");
    }
    pstInfo->u32Input++;
}

HI_VOID WinBuf_DebugAddCfg(WB_DEBUG_INFO_S *pstInfo, HI_U32 u32FrameId)
{
    pstInfo->u32CfgFrameID[pstInfo->u32CfgPos] = u32FrameId;

    if (0 != pstInfo->u32RecordNumber)
    {
        pstInfo->u32CfgPos = (pstInfo->u32CfgPos + 1) % pstInfo->u32RecordNumber;
    }
    else
    {
        WIN_ERROR("Denominator may be zero !\n");
    }
    pstInfo->u32Config++;
}

HI_VOID WinBuf_DebugAddRls(WB_DEBUG_INFO_S *pstInfo, HI_U32 u32FrameId)
{
    pstInfo->u32RlsFrameID[pstInfo->u32RlsPos] = u32FrameId;

    if (0 != pstInfo->u32RecordNumber)
    {
        pstInfo->u32RlsPos = (pstInfo->u32RlsPos + 1) % pstInfo->u32RecordNumber;
    }
    else
    {
        WIN_ERROR("Denominator may be zero !\n");
    }
    pstInfo->u32Release++;
}

HI_VOID WinBuf_DebugAddTryQF(WB_DEBUG_INFO_S *pstInfo)
{
    pstInfo->u32TryQueueFrame++;
}

HI_VOID WinBuf_DebugAddQFOK(WB_DEBUG_INFO_S *pstInfo)
{
    pstInfo->u32QueueFrame++;
}

HI_VOID WinBuf_DebugAddUnderload(WB_DEBUG_INFO_S *pstInfo)
{
    pstInfo->u32Underload++;
}

HI_VOID WinBuf_DebugAddDisacard(WB_DEBUG_INFO_S *pstInfo)
{
    pstInfo->u32Disacard++;
}

HI_VOID WinBuf_DebugAddIncreaseMemRefCnt(WB_DEBUG_INFO_S *pstInfo)
{
    pstInfo->u32IncreaseMemRefCnt++;
}

HI_VOID WinBuf_DebugAddDecreaseMemRefCnt(WB_DEBUG_INFO_S *pstInfo)
{
    pstInfo->u32DecreaseMemRefCnt++;
}

static HI_S32 WinBuf_AddEmptyNode(WB_POOL_S *pstWinBP,
                                  HI_DRV_VIDEO_FRAME_S *pstDispFrame,
                                  DISP_BUF_NODE_S *pstNodeEmpty)
{
    (HI_VOID)DecreaseFrameCntAccordingToFrame(pstDispFrame, pstWinBP->pstDebugInfo);
    return DispBuf_AddEmptyNode(&pstWinBP->stBuffer, pstNodeEmpty);
}

HI_S32 WinBuf_Create(HI_U32 u32BufNum, HI_U32 u32MemType, WIN_BUF_ALLOC_PARA_S *pstAlloc, WB_POOL_S *pstWinBP)
{
    HI_S32 nRet = HI_SUCCESS;

    WIN_CHECK_NULL_RETURN(pstWinBP);

    if (u32MemType != WIN_BUF_MEM_SRC_SUPPLY)
    {
        WIN_FATAL("Win buffer NOT SURPPORT ALLOC MEMORY NOW!\n");
        return HI_FAILURE;
    }

    if ( (u32BufNum == 0) || (u32BufNum > DISP_BUF_NODE_MAX_NUMBER))
    {
        WIN_FATAL("Win buffer number is invalid = %d\n", u32BufNum);
        return HI_FAILURE;
    }

    DISP_MEMSET(pstWinBP, 0, sizeof(WB_POOL_S));
    DISP_ASSERT(sizeof(HI_DRV_VIDEO_FRAME_S) <= (sizeof(((pstWinBP->stBuffer).pstBufArray[0])->u32Data)));

    pstWinBP->u32BufNumber = u32BufNum;
    pstWinBP->u32MemType   = u32MemType;

    nRet = DispBuf_Create(&pstWinBP->stBuffer, u32BufNum);
    if (nRet != HI_SUCCESS)
    {
        WIN_FATAL("Win create buffer failed\n");
        return nRet;
    }

#ifdef _WIN_BUF_MEM_FB_SUPPLY_
    if (u32MemType == WIN_BUF_MEM_FB_SUPPLY)
    {
        DISP_BUF_NODE_S *pstNode;
        HI_U32 u;

        for (u = 0; u < pstWinBP->u32BufNumber; u++)
        {
            (HI_VOID)DispBuf_GetNodeContent(&pstWinBP->stBuffer, u, &pstNode);
        }

        pstWinBP->u32MemType = WIN_BUF_MEM_FB_SUPPLY;
    }
#endif

    pstWinBP->pstDisplay = HI_NULL;
    pstWinBP->pstConfig  = HI_NULL;

    pstWinBP->pstDebugInfo = WinBuf_DebugCreate(WB_BUFFER_DEBUG_FRAME_RECORD_NUMBER);
    if (!pstWinBP->pstDebugInfo)
    {
        goto __ERR_EXIT_;
    }

    return HI_SUCCESS;

__ERR_EXIT_:
    if (pstWinBP->u32MemType == WIN_BUF_MEM_FB_SUPPLY)
    {
        DISP_BUF_NODE_S *pstNode;
        HI_U32 u;

        for (u = 0; u < pstWinBP->u32BufNumber; u++)
        {
            (HI_VOID)DispBuf_GetNodeContent(&pstWinBP->stBuffer, u, &pstNode);
        }
    }

    (HI_VOID)DispBuf_Destoy(&pstWinBP->stBuffer);

    return HI_FAILURE;
}

HI_S32 WinBuf_Destroy(WB_POOL_S *pstWinBP)
{
    HI_S32 nRet;

    WIN_CHECK_NULL_RETURN(pstWinBP);
    WinBuf_DebugDestroy(pstWinBP->pstDebugInfo);

    if (pstWinBP->u32MemType == WIN_BUF_MEM_FB_SUPPLY)
    {
        DISP_BUF_NODE_S *pstNode;
        HI_U32 u;

        for (u = 0; u < pstWinBP->u32BufNumber; u++)
        {
            nRet = DispBuf_GetNodeContent(&pstWinBP->stBuffer, u, &pstNode);
        }
    }


    nRet = DispBuf_Destoy(&pstWinBP->stBuffer);

    return HI_SUCCESS;
}

HI_S32 WinBuf_SetSource(WB_POOL_S *pstWinBP, WB_SOURCE_INFO_S *pstSrc)
{
    WIN_CHECK_NULL_RETURN(pstWinBP);
    WIN_CHECK_NULL_RETURN(pstSrc);

    pstWinBP->stSrcInfo.hSrc = pstSrc->hSrc;
    pstWinBP->stSrcInfo.hSecondSrc = pstSrc->hSecondSrc;

    if (HI_NULL != pstSrc->pfAcqFrame)
    {
        pstWinBP->stSrcInfo.pfAcqFrame = pstSrc->pfAcqFrame;
    }

    if (HI_NULL != pstSrc->pfRlsFrame)
    {
        pstWinBP->stSrcInfo.pfRlsFrame = pstSrc->pfRlsFrame;
    }

    return HI_SUCCESS;
}

HI_DRV_VIDEO_FRAME_S *WinBuf_GetConfigFrame(WB_POOL_S *pstWinBP)
{
    DISP_BUF_NODE_S *pstNode;
    HI_DRV_VIDEO_FRAME_S *pstFrm;
    HI_S32 nRet;

    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

    if (pstWinBP->pstDisplay)
    {
        if (pstWinBP->pstDisplay->u32PlayCnt)
        {
            HI_DRV_VIDEO_FRAME_S *pstTmpFrm;

            pstWinBP->pstDisplay->u32PlayCnt--;
            pstWinBP->pstConfig = pstWinBP->pstDisplay;

            pstTmpFrm = (HI_DRV_VIDEO_FRAME_S *)pstWinBP->pstConfig->u32Data;
#if 0
            WIN_ERROR("idx %d %d %#x\n",
                      pstTmpFrm->u32FrameIndex,
                      pstWinBP->pstDisplay->u32PlayCnt,
                      pstTmpFrm->stBufAddr[0].u32PhyAddr_Y);
#endif
            return (HI_DRV_VIDEO_FRAME_S *)pstWinBP->pstConfig->u32Data;
        }
    }

    nRet = DispBuf_GetFullNode(&pstWinBP->stBuffer, &pstNode);
    if (nRet != HI_SUCCESS)
    {
        WinBuf_DebugAddUnderload(pstWinBP->pstDebugInfo);
        return HI_NULL;
    }

    nRet = DispBuf_DelFullNode(&pstWinBP->stBuffer, pstNode);
    DISP_ASSERT(nRet == HI_SUCCESS);

    DISP_ASSERT(HI_NULL == pstWinBP->pstConfig);

    pstWinBP->pstConfig = pstNode;
    pstFrm = (HI_DRV_VIDEO_FRAME_S *)pstNode->u32Data;

    if (pstNode->u32PlayCnt)
    {
        pstNode->u32PlayCnt--;
    }

    WinBuf_DebugAddCfg(pstWinBP->pstDebugInfo, pstFrm->u32FrameIndex);

    return  pstFrm;
}


HI_S32 WinBuf_SetCaptureFrame(WB_POOL_S *pstWinBP)
{
    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

    if (HI_TRUE == pstWinBP->bCaptureFrame)
    {
       WIN_FATAL("do not support continous capturing.\n");
       return HI_ERR_VO_WIN_UNSUPPORT;
    }

    if (HI_NULL == pstWinBP->pstConfig)
    {
        WIN_ERROR("-capture should not be null ptr.\n");
        return HI_ERR_VO_INVALID_OPT;
    }

    pstWinBP->stCapture =  *(pstWinBP->pstConfig);
    pstWinBP->bCaptureFrame = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 WinBuf_ReleaseCaptureFrame(WB_POOL_S *pstWinBP, HI_DRV_VIDEO_FRAME_S *pstFrame, HI_BOOL u32WinCapMMZvalid)
{
    HI_DRV_VIDEO_FRAME_S *pstCaptureFrame = HI_NULL;
    WIN_CHECK_NULL_RETURN(pstWinBP);
    WIN_CHECK_NULL_RETURN(pstFrame);

    /*we may capture normal frame or black frame, so there exists a branch. */
    if (pstWinBP->bCaptureFrame)
    {
        pstCaptureFrame = (HI_DRV_VIDEO_FRAME_S *)pstWinBP->stCapture.u32Data;
    }
    else
    {
        pstCaptureFrame =   BP_GetBlackFrameInfo();
    }

    /* when release, if capture not equal to capture frame nor equal to black
       frame,return error.
    */
    WIN_CHECK_NULL_RETURN(pstCaptureFrame);

    if (pstFrame->stBufAddr[0].u32PhyAddr_Y != pstCaptureFrame->stBufAddr[0].u32PhyAddr_Y)
    {
        WIN_FATAL("-you release wrong capture frame.\n");
        return HI_ERR_VO_INVALID_OPT;
    }

    memset(&pstWinBP->stCapture, 0, sizeof(pstWinBP->stCapture));
    pstWinBP->bCaptureFrame = HI_FALSE;

    return HI_SUCCESS;
}

HI_DRV_VIDEO_FRAME_S *WinBuf_GetCapturedFrame(WB_POOL_S *pstWinBP)
{
    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

    if (pstWinBP->bCaptureFrame)
    {
        return (HI_DRV_VIDEO_FRAME_S *)pstWinBP->stCapture.u32Data;
    }
    else
    {
        return HI_NULL;
    }
}

static HI_S32  ReturnFrameToUselessList(WIN_BUFFER_S *pstBuffer,
                                        HI_DRV_VIDEO_FRAME_S *pstFrame,
                                        HI_BOOL bFrameEverDisplayed)
{
    HI_U32 WP1;
    HI_SIZE_T irqflag = 0;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    /*in  android fence,  just stop return frame to list,  because nobody call dequeue
            because fence take effect.*/
    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstFrame->u32Priv[0]);
    if (HI_TRUE == pstPriv->bForFenceUse)
    {
        return HI_SUCCESS;
    }

    spin_lock_irqsave(&pstBuffer->stUselessBuf.stUlsLock, irqflag);
    WP1 = (pstBuffer->stUselessBuf.u32ULSWtPtr + 1) % WIN_USELESS_FRAME_MAX_NUMBER;

    if (WP1 == pstBuffer->stUselessBuf.u32ULSRdPtr)
    {
        WIN_ERROR("usl full\n");
        spin_unlock_irqrestore(&pstBuffer->stUselessBuf.stUlsLock, irqflag);
        return HI_ERR_VO_BUFQUE_FULL;
    }

    pstBuffer->stUselessBuf.stUselessFrame[pstBuffer->stUselessBuf.u32ULSWtPtr] = *pstFrame;
    pstBuffer->stUselessBuf.u32ULSWtPtr = WP1;
    pstBuffer->stUselessBuf.u32ULSIn++;

    spin_unlock_irqrestore(&pstBuffer->stUselessBuf.stUlsLock, irqflag);

    return HI_SUCCESS;
}

HI_S32 WinBufferPutULSFrame(WIN_BUFFER_S *pstBuffer,
                            HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    /*when user queue useless frame,  or drop frame as a result of frc,
          just set the bFrameEverDisplayed to false because it is not be displayed.*/
    return ReturnFrameToUselessList(pstBuffer, pstFrame, HI_FALSE);
}

HI_S32 WinBufferGetULSFrame(WIN_BUFFER_S *pstBuffer, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    HI_SIZE_T irqflag = 0;
    HI_DRV_VIDEO_FRAME_S *pstFrameTmp = HI_NULL;
    HI_S32 ret = HI_FAILURE;

    spin_lock_irqsave(&pstBuffer->stUselessBuf.stUlsLock, irqflag);

    while (pstBuffer->stUselessBuf.u32ULSWtPtr != pstBuffer->stUselessBuf.u32ULSRdPtr)
    {
        pstFrameTmp = &pstBuffer->stUselessBuf.stUselessFrame[pstBuffer->stUselessBuf.u32ULSRdPtr];
        pstBuffer->stUselessBuf.u32ULSRdPtr = (pstBuffer->stUselessBuf.u32ULSRdPtr + 1) % WIN_USELESS_FRAME_MAX_NUMBER;
        pstBuffer->stUselessBuf.u32ULSOut++;

        if (HI_DRV_FRAME_SWITCH_PROGRAM_STILL != pstFrameTmp->u32StillFrame)
        {
            break;
        }
    }

    if ((HI_NULL != pstFrameTmp) && (HI_DRV_FRAME_SWITCH_PROGRAM_STILL != pstFrameTmp->u32StillFrame))
    {
        memcpy((HI_VOID *)pstFrame, (HI_VOID *)pstFrameTmp, sizeof(HI_DRV_VIDEO_FRAME_S));
        ret =  HI_SUCCESS;
    }
    else
    {
        ret =  HI_ERR_VO_NO_FRAME_TO_RELEASE;
    }

    spin_unlock_irqrestore(&pstBuffer->stUselessBuf.stUlsLock, irqflag);

    return ret;
}

HI_S32 WinReturnDisplayedFrameToUseless(WIN_BUFFER_S *pstBuffer, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    return ReturnFrameToUselessList(pstBuffer, pstFrame, HI_TRUE);
}

/*
  *this func is for  queue/dequeue  function pairs in UNF level.
  *vdp  should store the displayed frame to useless array, and wait dequeue
  * unf func to retrieve the frame.
  */
HI_S32 Win_ReleaseDisplayedFrame_ForDequeue(HI_HANDLE hpstWin, HI_DRV_VIDEO_FRAME_S *pstFrm)
{
    HI_S32 nRet = 0;
    WINDOW_S *pstWin = HI_NULL;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    WinCheckWindow(hpstWin, pstWin);
    WinCheckNullPointer(pstFrm);

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstFrm->u32Priv[0]);

    /*Win_ReleaseDisplayedFrame_ForDequeue is for Scenes under which
      vdec and window not attached. in non-attached mode,  there are 2 ways for frame operation:
      1) user can call queue/dequeue;
      2) user queue frame into window ,  window release by fence.
            when frame released  by fence, we should not put the frames into a list to wait for user calling dequeue,
         because  in this condition, user will never call dequeue to get their frames, because they use fence to release.
      */

    nRet = WinReturnDisplayedFrameToUseless(&pstWin->stBuffer, pstFrm);
    return nRet;
}

static HI_S32  ReturnFrameToProducer(WB_POOL_S *pstWinBP,
                                     HI_HANDLE            hsrc,
                                     HI_DRV_VIDEO_FRAME_S *pstFrm,
                                     HI_BOOL               bSwitchProgramStill)
{

    if (pstWinBP->stSrcInfo.pfRlsFrame)
    {
        pstWinBP->stSrcInfo.pfRlsFrame(hsrc, pstFrm);
    }
    else
    {
        /*fix last frame switch status then destroy window mem Leak*/
        if (HI_TRUE == bSwitchProgramStill)
        {

            VDEC_EXPORT_FUNC_S *pstVdecFunc = HI_NULL;
            HI_S32 s32Ret = HI_SUCCESS;

            s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_VDEC, (HI_VOID **) & (pstVdecFunc));
            if (HI_SUCCESS != s32Ret || pstVdecFunc == HI_NULL)
            {
                WIN_ERROR("get vdec func error.\n");
                return HI_FAILURE;
            }
            pstVdecFunc->pfnVORlsFrame(HI_INVALID_HANDLE, pstFrm);
        }
    }

    return HI_SUCCESS;
}

HI_S32 WinBuf_RlsFrameWithHandle(WB_POOL_S *pstWinBP, HI_DRV_VIDEO_FRAME_S *pstFrm)
{
    HI_S32 Ret = HI_SUCCESS;
    DISP_BUF_NODE_S      *pstDispBufNode = HI_NULL;
    HI_DRV_VIDEO_FRAME_S *pstELFrm = HI_NULL;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;
    HI_BOOL                 bSwitchProgramStill = HI_FALSE;

    WIN_CHECK_NULL_RETURN(pstWinBP);
    WIN_CHECK_NULL_RETURN(pstFrm);

    /*android fence frame does not need release, because it use fence.*/
    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstFrm->u32Priv[0]);
    if (pstPriv->bForFenceUse == HI_TRUE)
    {
        goto _UPDATE_DEBUG_;
    }

    /*still frame allocated by vdp  should take it's own branch.*/
    if (HI_DRV_FRAME_VDP_ALLOCATE_STILL == pstFrm->u32StillFrame)
    {
        WIN_DestroyStillFrame(pstFrm);
        goto _UPDATE_DEBUG_;
    }

    bSwitchProgramStill = (HI_DRV_FRAME_SWITCH_PROGRAM_STILL == pstFrm->u32StillFrame) ? HI_TRUE : HI_FALSE;
    Ret = ReturnFrameToProducer(pstWinBP,
                                pstWinBP->stSrcInfo.hSrc,
                                pstFrm,
                                bSwitchProgramStill);
    if (HI_SUCCESS != Ret)
    {
        goto _UPDATE_DEBUG_;
    }

    /*use container_of method to get the node.*/
    pstDispBufNode = container_of((HI_U32 *)pstFrm, DISP_BUF_NODE_S, u32Data[0]);
    if (pstDispBufNode->bValidData2)
    {
        pstELFrm = (HI_DRV_VIDEO_FRAME_S *)pstDispBufNode->u32Data2;
        if (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_EL == pstELFrm->enSrcFrameType)
        {
            Ret = ReturnFrameToProducer(pstWinBP,
                                        pstWinBP->stSrcInfo.hSecondSrc,
                                        pstELFrm,
                                        bSwitchProgramStill);
        }
    }

_UPDATE_DEBUG_:
    if (HI_SUCCESS == Ret)
    {
        WinBuf_DebugAddRls(pstWinBP->pstDebugInfo, pstFrm->u32FrameIndex);
    }

    return Ret;
}


//release frame that has been displayed and set configed frame as displayed frame.
HI_S32 WinBuf_RlsAndUpdateUsingFrame(WB_POOL_S *pstWinBP)
{
    HI_DRV_VIDEO_FRAME_S *pstDispFrame, *pstCfgFrame;
    HI_S32 nRet;

    WIN_CHECK_NULL_RETURN(pstWinBP);

    if (pstWinBP->pstDisplay != HI_NULL)
    {
        pstDispFrame = (HI_DRV_VIDEO_FRAME_S *)pstWinBP->pstDisplay->u32Data;

        /*1) display not null, and config == display,this
            means repeate-playing  controlled by vdp itself.
              2) not the same with repeate-playing controlled by avplay
                : pstDisplay != pstconfig, but the ptr points the same frame.
              */
        if (pstWinBP->pstDisplay == pstWinBP->pstConfig)
        {
            pstWinBP->pstConfig  = HI_NULL;
        }
        else if (pstWinBP->pstConfig != HI_NULL)
        {
            /*this branch means normal playing:
                          we get new config node, and if not repeated by avplay ,we
                         will release the display node and  move forward.*/
            pstCfgFrame = (HI_DRV_VIDEO_FRAME_S *)pstWinBP->pstConfig->u32Data;

            /*if display and config not points the same frame, we will release display node.*/
            if ( (pstDispFrame->stBufAddr[0].u32PhyAddr_Y
                  != pstCfgFrame->stBufAddr[0].u32PhyAddr_Y))
            {
                (HI_VOID)WinBuf_RlsFrameWithHandle(pstWinBP, pstDispFrame);
            }

            /* release disp buffer*/
            nRet = WinBuf_AddEmptyNode(pstWinBP, pstDispFrame, pstWinBP->pstDisplay);
            DISP_ASSERT(nRet == HI_SUCCESS);

            /*move forward.*/
            pstWinBP->pstDisplay = pstWinBP->pstConfig;
            pstWinBP->pstConfig  = HI_NULL;
        }
        else
        {
            /*this branch means: in last intr,we undergo a reset, and in black frame mode. so we did
                         not receive new frame from avplay, in this intr, we should release it.
                      */
            (HI_VOID)WinBuf_RlsFrameWithHandle(pstWinBP, pstDispFrame);

            nRet = WinBuf_AddEmptyNode(pstWinBP, pstDispFrame, pstWinBP->pstDisplay);
            DISP_ASSERT(nRet == HI_SUCCESS);
            pstWinBP->pstDisplay = HI_NULL;
        }

    }
    else if (pstWinBP->pstConfig != HI_NULL)
    {
        pstWinBP->pstDisplay = pstWinBP->pstConfig;

        pstWinBP->pstConfig = HI_NULL;
    }

    return HI_SUCCESS;
}

HI_S32 WinBuf_RepeatDisplayedFrame(WB_POOL_S *pstWinBP)
{
    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

    DISP_ASSERT(HI_NULL == pstWinBP->pstConfig);

    pstWinBP->pstConfig = pstWinBP->pstDisplay;

    return HI_SUCCESS;
}

HI_S32 WinBuf_DiscardDisplayedFrame(WB_POOL_S *pstWinBP)
{
    HI_BOOL bInFullList = HI_FALSE;
    HI_DRV_VIDEO_FRAME_S *pstDispFrame = HI_NULL;
    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

    if (pstWinBP->pstConfig != HI_NULL)
    {
        WIN_ERROR("DiscardDisplayedFrame Error.\n");
        return HI_FAILURE;
    }

    if (pstWinBP->pstDisplay != HI_NULL)
    {
        pstDispFrame = (HI_DRV_VIDEO_FRAME_S *)pstWinBP->pstDisplay->u32Data;

        bInFullList = DispBuf_FullListHasSameNode(&(pstWinBP->stBuffer),
                      pstWinBP->pstDisplay);
        if (!bInFullList)
        {
            (HI_VOID)WinBuf_RlsFrameWithHandle(pstWinBP, pstDispFrame);
        }

        (HI_VOID)WinBuf_AddEmptyNode(pstWinBP, pstDispFrame, pstWinBP->pstDisplay);
    }

    pstWinBP->pstConfig = HI_NULL;
    pstWinBP->pstDisplay = HI_NULL;

    return HI_SUCCESS;
}
HI_DRV_VIDEO_FRAME_S *WinBuf_GetDisplayedFrame(WB_POOL_S *pstWinBP)
{
    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

    if (pstWinBP->pstDisplay != HI_NULL)
    {
        return (HI_DRV_VIDEO_FRAME_S *)pstWinBP->pstDisplay->u32Data;
    }

    return HI_NULL;
}

HI_DRV_VIDEO_FRAME_S *WinBuf_GetConfigedFrame(WB_POOL_S *pstWinBP)
{
    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

    if (pstWinBP->pstConfig != HI_NULL)
    {
        return (HI_DRV_VIDEO_FRAME_S *)pstWinBP->pstConfig->u32Data;
    }

    return HI_NULL;
}

HI_S32 WinBuf_ForceReleaseFrame(WB_POOL_S *pstWinBP, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    WIN_CHECK_NULL_RETURN(pstWinBP);

    if (HI_NULL == pstFrame)
    {
        return HI_SUCCESS;
    }

    (HI_VOID)WinBuf_RlsFrameWithHandle(pstWinBP, pstFrame);
    if (HI_NULL != pstWinBP->pstDisplay)
    {
        (HI_VOID)WinBuf_AddEmptyNode(pstWinBP, pstFrame, pstWinBP->pstDisplay);
    }

    return HI_SUCCESS;
}

HI_S32 WinBuf_ReleaseOneFrame(WB_POOL_S *pstWinBP, HI_DRV_VIDEO_FRAME_S *pstPreFrame)
{
    DISP_BUF_NODE_S *pstWBNode, *pstWBNextNode;
    HI_DRV_VIDEO_FRAME_S *pstCurrFrame, *pstNextFrame;
    HI_U32 u32UsingAddrY;
    HI_U32 u32UsingIdx;
    HI_S32 nRet;

    WIN_CHECK_NULL_RETURN(pstWinBP);

    if (pstPreFrame)
    {
        u32UsingAddrY = pstPreFrame->stBufAddr[0].u32PhyAddr_Y;
        u32UsingIdx = pstPreFrame->u32FrameIndex;
    }
    else
    {
        u32UsingAddrY = 0;
        u32UsingIdx = 0xffffffff;
    }

    nRet = DispBuf_GetFullNode(&pstWinBP->stBuffer, &pstWBNode);
    if (nRet != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    nRet = DispBuf_GetNextFullNode(&pstWinBP->stBuffer, &pstWBNextNode);
    if (nRet != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    pstCurrFrame = (HI_DRV_VIDEO_FRAME_S *)pstWBNode->u32Data;
    pstNextFrame = (HI_DRV_VIDEO_FRAME_S *)pstWBNextNode->u32Data;

    if ((pstCurrFrame->stBufAddr[0].u32PhyAddr_Y != u32UsingAddrY)
        && (pstCurrFrame->stBufAddr[0].u32PhyAddr_Y !=
            pstNextFrame->stBufAddr[0].u32PhyAddr_Y))
    {
        (HI_VOID)WinBuf_RlsFrameWithHandle(pstWinBP, pstCurrFrame);
    }
    /*
       why add Idx != UsingIdx?
       1.vo may release the same addr frame twice
       2.if 1,vpss will check the error ,then don't release the addr
       3.if 2,vo may receive two same addr frame with diff Idx.
       4.if 3,vpss is blocked
       to avoid this situation,add add Idx != UsingIdx here.
     */
    else if ((pstCurrFrame->stBufAddr[0].u32PhyAddr_Y != u32UsingAddrY
              || pstCurrFrame->u32FrameIndex != u32UsingIdx)
             && (pstCurrFrame->stBufAddr[0].u32PhyAddr_Y !=
                 pstNextFrame->stBufAddr[0].u32PhyAddr_Y)
            )
    {
        // if the current frame is different with next frame and not using,
        // release it.
        (HI_VOID)WinBuf_RlsFrameWithHandle(pstWinBP, pstCurrFrame);

    }

    // release node of current frame and add to empty array.
    nRet = DispBuf_DelFullNode(&pstWinBP->stBuffer, pstWBNode);
    DISP_ASSERT(nRet == HI_SUCCESS);

    nRet = WinBuf_AddEmptyNode(pstWinBP, pstCurrFrame, pstWBNode);
    DISP_ASSERT(nRet == HI_SUCCESS);

    WinBuf_DebugAddDisacard(pstWinBP->pstDebugInfo);

    return HI_SUCCESS;
}

HI_S32 WinBuf_FlushWaitingFrame(WB_POOL_S *pstWinBP, HI_DRV_VIDEO_FRAME_S *pstPreFrame)
{
    DISP_BUF_NODE_S *pstWBNode, *pstWBNextNode;
    HI_DRV_VIDEO_FRAME_S *pstCurrFrame;
    HI_U32 u32UsingAddrY;
    HI_U32 u32UsingIdx;
    HI_S32 nRet;

    WIN_CHECK_NULL_RETURN(pstWinBP);

    if (pstPreFrame)
    {
        u32UsingAddrY = pstPreFrame->stBufAddr[0].u32PhyAddr_Y;
        u32UsingIdx = pstPreFrame->u32FrameIndex;
    }
    else
    {
        u32UsingAddrY = 0;
        u32UsingIdx = 0xffffffff;
    }

    nRet = DispBuf_GetFullNode(&pstWinBP->stBuffer, &pstWBNode);
    if (nRet != HI_SUCCESS)
    {
        return HI_SUCCESS;
    }

    nRet = DispBuf_GetNextFullNode(&pstWinBP->stBuffer, &pstWBNextNode);

    while (nRet == HI_SUCCESS)
    {
        WinBuf_ReleaseOneFrame(pstWinBP, pstPreFrame);

        // update position, 'pstWBNextNode' becomes current node, and get new next node
        pstWBNode = pstWBNextNode;

        nRet = DispBuf_GetNextFullNode(&pstWinBP->stBuffer, &pstWBNextNode);
    }

    // all node is clean exept the last one, now release it.

    pstCurrFrame = (HI_DRV_VIDEO_FRAME_S *)pstWBNode->u32Data;

    if (pstCurrFrame->stBufAddr[0].u32PhyAddr_Y != u32UsingAddrY)
    {
        (HI_VOID)WinBuf_RlsFrameWithHandle(pstWinBP, pstCurrFrame);
    }
    /*
       why add Idx != UsingIdx?
       1.vo may release the same addr frame twice
       2.if 1,vpss will check the error ,then don't release the addr
       3.if 2,vo may receive two same addr frame with diff Idx.
       4.if 3,vpss is blocked
       to avoid this situation,add add Idx != UsingIdx here.
     */
    else if (pstCurrFrame->stBufAddr[0].u32PhyAddr_Y != u32UsingAddrY
             || pstCurrFrame->u32FrameIndex != u32UsingIdx)
    {
        (HI_VOID)WinBuf_RlsFrameWithHandle(pstWinBP, pstCurrFrame);
    }

    nRet = DispBuf_DelFullNode(&pstWinBP->stBuffer, pstWBNode);
    DISP_ASSERT(nRet == HI_SUCCESS);

    nRet = WinBuf_AddEmptyNode(pstWinBP, pstCurrFrame, pstWBNode);
    DISP_ASSERT(nRet == HI_SUCCESS);

    return HI_SUCCESS;
}

HI_DRV_VIDEO_FRAME_S *WinBuf_GetFrameByDisplayInfo(WB_POOL_S *pstWinBP,
        HI_DRV_VIDEO_FRAME_S *pstRefFrame,
        HI_U32 u32RefRate,
        HI_DRV_FIELD_MODE_E enDstField)
{
    DISP_BUF_NODE_S *pstWBNode, *pstWBNextNode;
    HI_DRV_VIDEO_FRAME_S *pstCurrFrame;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    HI_S32 nRet;

    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

#ifdef WIN_BUF_GetFrameByDisplayInfo_PRINT
    printk("[df=%d]", enDstField);
#endif

    while (1)
    {
        // get new frame
        nRet = DispBuf_GetFullNode(&pstWinBP->stBuffer, &pstWBNode);
        if (nRet != HI_SUCCESS)
        {
#ifdef WIN_BUF_GetFrameByDisplayInfo_PRINT
            printk("U.");
#endif
            return HI_NULL;
        }

        pstCurrFrame = (HI_DRV_VIDEO_FRAME_S *)pstWBNode->u32Data;
        pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstCurrFrame->u32Priv[0]);

        // compare field and frame rate
        if ( (pstPriv->eOriginField == HI_DRV_FIELD_ALL)
             || (pstPriv->eOriginField == enDstField)
             || (abs((HI_S32)(pstCurrFrame->u32OriFrameRate / 10) - (HI_S32)u32RefRate) >= 100)
           )
        {
            return WinBuf_GetConfigFrame(pstWinBP);
        }
        // process current frame according to sync info
        switch (pstCurrFrame->enTBAdjust)
        {
            case HI_DRV_VIDEO_TB_REPEAT:
                // this frame may delay than audio
                pstCurrFrame->enTBAdjust = HI_DRV_VIDEO_TB_PLAY;
#ifdef WIN_BUF_GetFrameByDisplayInfo_PRINT
                printk("R.");
#endif
                return HI_NULL;
            case HI_DRV_VIDEO_TB_DISCARD:
                // this frame may advacne than audio, so get next
                nRet = DispBuf_GetNextFullNode(&pstWinBP->stBuffer, &pstWBNextNode);
#ifdef WIN_BUF_GetFrameByDisplayInfo_PRINT
                printk("D.");
#endif
                if (nRet == HI_SUCCESS)
                {
#ifdef WIN_BUF_GetFrameByDisplayInfo_PRINT
                    printk("DR.");
#endif
                    WinBuf_ReleaseOneFrame(pstWinBP, pstRefFrame);
                    break;
                }
                else
                {
#ifdef WIN_BUF_GetFrameByDisplayInfo_PRINT
                    printk("DC.");
#endif
                    return WinBuf_GetConfigFrame(pstWinBP);
                }
            case HI_DRV_VIDEO_TB_PLAY:
            default:
                // this frame should not adjust
#ifdef WIN_BUF_GetFrameByDisplayInfo_PRINT
                printk("P.");
#endif
                return WinBuf_GetConfigFrame(pstWinBP);
        }

    }

    return HI_NULL;
}

HI_DRV_VIDEO_FRAME_S *WinBuf_GetNewestFrame(WB_POOL_S *pstWinBP, HI_DRV_VIDEO_FRAME_S *pstRefFrame)
{
    DISP_BUF_NODE_S *pstWBNode, *pstWBNextNode;
    HI_DRV_VIDEO_FRAME_S *pstCurrFrame, *pstNextFrame;
    HI_S32 nRet;

    WIN_CHECK_NULL_RETURN_NULL(pstWinBP);

    nRet = DispBuf_GetFullNode(&pstWinBP->stBuffer, &pstWBNode);
    if (nRet != HI_SUCCESS)
    {
        return HI_NULL;
    }

    pstCurrFrame = (HI_DRV_VIDEO_FRAME_S *)pstWBNode->u32Data;

    nRet = DispBuf_GetNextFullNode(&pstWinBP->stBuffer, &pstWBNextNode);
    while (nRet == HI_SUCCESS)
    {
        pstNextFrame = (HI_DRV_VIDEO_FRAME_S *)pstWBNextNode->u32Data;

        WinBuf_ReleaseOneFrame(pstWinBP, pstRefFrame);

        // update position, 'pstWBNextNode' becomes current node, and get new next node
        pstWBNode = pstWBNextNode;

        nRet = DispBuf_GetNextFullNode(&pstWinBP->stBuffer, &pstWBNextNode);
    }

    // get node
    nRet = DispBuf_DelFullNode(&pstWinBP->stBuffer, pstWBNode);
    DISP_ASSERT(nRet == HI_SUCCESS);

    DISP_ASSERT(HI_NULL == pstWinBP->pstConfig);

    // all node is clean exept the last one, now release it.
    pstWinBP->pstConfig = pstWBNode;

    pstCurrFrame = (HI_DRV_VIDEO_FRAME_S *)pstWBNode->u32Data;

    WinBuf_DebugAddCfg(pstWinBP->pstDebugInfo, pstCurrFrame->u32FrameIndex);

    return pstCurrFrame;
}

HI_S32 WinBuf_GetFullBufNum(WB_POOL_S *pstWinBP, HI_U32 *pu32BufNum)
{
    WIN_CHECK_NULL_RETURN(pstWinBP);
    WIN_CHECK_NULL_RETURN(pu32BufNum);

    return DispBuf_GetFullNodeNumber(&pstWinBP->stBuffer, pu32BufNum);
}

HI_S32 WinBuf_GetStateInfo(WB_POOL_S *pstWinBP, WB_STATE_S *pstWinBufState)
{
    DISP_BUF_NODE_S *pstNode;
    HI_DRV_VIDEO_FRAME_S *pstFrame;
    HI_S32 i, nRet;

    WIN_CHECK_NULL_RETURN(pstWinBP);
    WIN_CHECK_NULL_RETURN(pstWinBufState);

    pstWinBufState->u32Number = pstWinBP->u32BufNumber;

    pstWinBufState->u32EmptyRPtr = pstWinBP->stBuffer.u32EmptyReadPos;
    pstWinBufState->u32EmptyWPtr = pstWinBP->stBuffer.u32EmptyWritePos;
    pstWinBufState->u32FullRPtr  = pstWinBP->stBuffer.u32FullReaddPos;
    pstWinBufState->u32FullWPtr  = pstWinBP->stBuffer.u32FullWritePos;

    for (i = 0; i < pstWinBP->u32BufNumber; i++)
    {
        nRet = DispBuf_GetNodeContent(&pstWinBP->stBuffer, i, &pstNode);
        if ( nRet == HI_SUCCESS)
        {
            pstWinBufState->stNode[i].u32State = pstNode->u32State;
            pstWinBufState->stNode[i].u32Empty = pstNode->u32EmptyCount;
            pstWinBufState->stNode[i].u32Full  = pstNode->u32FullCount;

            pstFrame = (HI_DRV_VIDEO_FRAME_S *)pstNode->u32Data;
            pstWinBufState->stNode[i].u32FrameIndex = pstFrame->u32FrameIndex;
        }
        else
        {
            pstWinBufState->stNode[i].u32State = 0;
            pstWinBufState->stNode[i].u32Empty = 0;
            pstWinBufState->stNode[i].u32Full  = 0;
            pstWinBufState->stNode[i].u32FrameIndex = 0;
        }
    }

    if (HI_NULL == pstWinBP->pstDebugInfo)
    {
        return HI_ERR_VO_NULL_PTR;
    }

    memcpy(&pstWinBufState->stRecord, pstWinBP->pstDebugInfo, sizeof(WB_DEBUG_INFO_S));

    memcpy(&pstWinBufState->u32EmptyArray, pstWinBP->stBuffer.u32EmptyArray, sizeof(pstWinBP->stBuffer.u32EmptyArray));
    memcpy(&pstWinBufState->u32FullArray, pstWinBP->stBuffer.u32FullArray, sizeof(pstWinBP->stBuffer.u32FullArray));

    pstFrame = WinBuf_GetDisplayedFrame(pstWinBP);
    if (pstFrame)
    {
        memcpy(&pstWinBufState->stCurrentFrame, pstFrame, sizeof(HI_DRV_VIDEO_FRAME_S));
    }

    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
