#include "vpss_alg_buf.h"
#include "vpss_stt_mcdei.h"

HI_VOID VPSS_AlgBuf_Print1(VPSS_ALG_BUF *pstBuf)
{
    HI_U32 n;
    ALG_MEM_NODE *pstMemPool = pstBuf->stMemPool;
    HI_PRINT("=============VpssAlgBuf%d=%#x=============\n", pstBuf->u32Index, pstBuf->stMMUBuf.u32StartSmmuAddr);
    for (n = 0; n < VPSS_ALG_BUTT; n++)
    {
        HI_PRINT("type:%d offset:%ukb size:%ukb in_use:%d need_init:%d addr:%#x vaddr:0x%p\n",
                 pstMemPool[n].enType, pstMemPool[n].u32MemOffset / 1024, pstMemPool[n].u32MemSize / 1024,
                 pstMemPool[n].bInUse, pstMemPool[n].bNeedMap,
                 pstMemPool[n].stMMUBuf.u32StartSmmuAddr, pstMemPool[n].stMMUBuf.pu8StartVirAddr);
    }
    HI_PRINT("total size:%ukb start_phyaddr:%#x start_viraddr:0x%p total_use_count:%d\n",
             pstBuf->u32TotalSize / 1024,  pstBuf->stMMUBuf.u32StartSmmuAddr,
             pstBuf->stMMUBuf.pu8StartVirAddr, pstBuf->u32TotalUseCount);
    HI_PRINT("=====================================\n");
    pstMemPool = NULL;
    return ;
}

HI_S32 VPSS_AlgBuf_Init(VPSS_ALG_BUF *pstBuf, HI_U32 u32Index)
{
    HI_U32 n;
    ALG_MEM_NODE *pstMemPool = NULL;
    HI_U32 u32BuffSize = 0;
    HI_U32 u32Offset = 0;
    if (NULL == pstBuf)
    {
        return HI_FAILURE;
    }
    pstMemPool = pstBuf->stMemPool;
    memset((void *)pstBuf, 0, sizeof(VPSS_ALG_BUF));
    pstBuf->u32Index = u32Index;
    for (n = 0; n < VPSS_ALG_BUTT; n++)
    {
        pstMemPool[n].enType = n;
        switch (pstMemPool[n].enType)
        {
            case VPSS_ALG_WBC:
                u32BuffSize = WBC_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_TRUE; //如果数据是tile格式，需要把虚拟地址传出去，给入网指标用的
                break;
            case VPSS_ALG_STTRGME:
                u32BuffSize = STTRGME_BUFF_SIZE ;
                pstMemPool[n].bNeedMap = HI_TRUE;
                break;
            case VPSS_ALG_STTPRJH:
                u32BuffSize = STTPRJH_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_TRUE;
                break;
            case VPSS_ALG_STTPRJV:
                u32BuffSize = STTPRJV_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_TRUE;
                break;
            case VPSS_ALG_BLEND_WBC:
                u32BuffSize = BLEND_WBC_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_FALSE;
                break;
            case VPSS_ALG_RGME_WBC:
                u32BuffSize = RGME_WBC_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_FALSE;
                break;
            case VPSS_ALG_STTBLKMV:
                u32BuffSize = STTBLKMV_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_TRUE;
                break;
#ifdef VPSS_SUPPORT_BLKMT
            case VPSS_ALG_STTBLKMT:
                u32BuffSize = STTBLKMT_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_TRUE;
                break;
#endif
#ifdef VPSS_SUPPORT_DICNT
            case VPSS_ALG_STTDICNT:
                u32BuffSize = STTDICNT_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_TRUE;
                break;
#endif
            case VPSS_ALG_STTDIE:
                u32BuffSize = STTDIE_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_TRUE;
                break;
            case VPSS_ALG_STTNR:
                u32BuffSize = STTNR_BUFF_SIZE;
                pstMemPool[n].bNeedMap = HI_TRUE;
                break;
            case VPSS_ALG_STTWBC:
                u32BuffSize = VPSS_STTWBC_SIZE;
                pstMemPool[n].bNeedMap = HI_TRUE;
                break;
            default:
                break;
        }
        pstMemPool[n].u32MemSize = u32BuffSize;
        pstMemPool[n].u32MemOffset = u32Offset;
        u32Offset += u32BuffSize;
        pstBuf->u32TotalSize += pstMemPool[n].u32MemSize;
    }
#if VPSS_ALGBUF_DEG
    HI_PRINT("Init vpss alg buffer info\n");
    VPSS_AlgBuf_Print1(pstBuf);
#endif
    return HI_SUCCESS;
}

#if defined(ALGBUF_MANAGE_MODE1)
VPSS_ALG_BUF g_VpssAlgBuf = {0};
HI_S32 VPSS_AlgBuf_Malloc(VPSS_ALG_BUF *pstBuf, VPSS_ALG_BUF_TYPE_E enAlgType,
                          HI_CHAR *pAlgName, HI_U32 u32SizeNeed, HI_U32 u32Align, SMMU_BUFFER_S *pSmmuBuf)
{
    HI_S32 s32Ret = 0;
    HI_S32 i;
    ALG_MEM_NODE *pstMemPool = NULL;
    if (NULL == pstBuf)
    {
        VPSS_ERROR("VPSS AlgBuf Malloc error: null pointer \n");
        return HI_FAILURE;
    }
    pstMemPool = pstBuf->stMemPool;
    if (pstBuf->u32TotalUseCount == 0)
    {
        VPSS_OSAL_IntfTime_Start(VPSS_INTF_MALLOC_ALGBUF);
        s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_AlgBuf", pstBuf->u32TotalSize, u32Align, &(pstBuf->stMMUBuf));
        if (s32Ret == HI_FAILURE)
        {
            VPSS_FATAL("VPSS SMMU AllocAndMap Failed!\n");
            return HI_FAILURE;
        }
        VPSS_OSAL_IntfTime_Stop(VPSS_INTF_MALLOC_ALGBUF);
        for (i = 0; i < VPSS_ALG_BUTT; i++)
        {
            pstMemPool[i].stMMUBuf.pu8StartVirAddr = (HI_U8 *)((HI_U32)pstBuf->stMMUBuf.pu8StartVirAddr + pstMemPool[i].u32MemOffset);
            pstMemPool[i].stMMUBuf.u32StartSmmuAddr = pstBuf->stMMUBuf.u32StartSmmuAddr + pstMemPool[i].u32MemOffset;
            pstMemPool[i].stMMUBuf.u32Size = pstMemPool[i].u32MemSize;

        }
#if VPSS_ALGBUF_DEG
        VPSS_AlgBuf_Print1(pstBuf);
#endif
    }

    for (i = 0; i < VPSS_ALG_BUTT; i++)
    {
        if (pstMemPool[i].enType == enAlgType)
        {
            if (pstMemPool[i].bNeedMap == 1)
            {
                pSmmuBuf->u32Size = u32SizeNeed;
                pSmmuBuf->u32StartSmmuAddr = pstMemPool[i].stMMUBuf.u32StartSmmuAddr;
                pSmmuBuf->pu8StartVirAddr = pstMemPool[i].stMMUBuf.pu8StartVirAddr;
            }
            else
            {
                pSmmuBuf->u32Size = u32SizeNeed;
                pSmmuBuf->u32StartSmmuAddr = pstMemPool[i].stMMUBuf.u32StartSmmuAddr;
                pSmmuBuf->pu8StartVirAddr = NULL;
            }
            break;
        }
    }
    if (i == VPSS_ALG_BUTT)
    {
        VPSS_ERROR("Can't find mem type %d in mem pool\n", enAlgType);
        return HI_FAILURE;
    }
    else if (pSmmuBuf->u32StartSmmuAddr == 0 || pSmmuBuf->u32Size == 0)
    {
        VPSS_ERROR("Get wrong smmu addr \n");
        return HI_FAILURE;
    }
    pstMemPool[i].bInUse = HI_TRUE;
    pstBuf->u32TotalUseCount ++;
    return HI_SUCCESS;
}

HI_S32 VPSS_AlgBuf_Free(VPSS_ALG_BUF *pstBuf, SMMU_BUFFER_S *pstMMUBuf, VPSS_ALG_BUF_TYPE_E enAlgType)
{
    HI_S32 i;
    ALG_MEM_NODE *pstMemPool = NULL;
    if (NULL == pstBuf || NULL == pstMMUBuf)
    {
        VPSS_ERROR("VPSS AlgBuf Free error: null pointer \n");
        return HI_FAILURE;
    }
    pstMemPool = pstBuf->stMemPool;
    if (pstBuf->stMMUBuf.u32StartSmmuAddr == 0)
    {
        VPSS_ERROR("VPSS AlgBuf Free error: null smmu addr \n");
        return HI_FAILURE;
    }
    for (i = 0; i < VPSS_ALG_BUTT; i++)
    {
        if (pstMemPool[i].enType == enAlgType)
        {
            pstMemPool[i].bInUse = HI_FALSE;
            pstMemPool[i].u32MemSize = 0;
            pstMemPool[i].u32MemOffset = 0;
            memset(&(pstMemPool[i].stMMUBuf) , 0, sizeof(SMMU_BUFFER_S));
            pstBuf->u32TotalUseCount--;
            break;
        }
    }
    if (i == VPSS_ALG_BUTT)
    {
        VPSS_ERROR("VPSS AlgBuf Free error: can't find the type \n");
        return HI_FAILURE;
    }
    if (pstBuf->u32TotalUseCount == 0)
    {
        HI_DRV_SMMU_UnmapAndRelease(&(pstBuf->stMMUBuf));
#if VPSS_ALGBUF_DEG
        VPSS_AlgBuf_Print1(pstBuf);
#endif
    }
    return HI_SUCCESS;
}

#elif (defined(ALGBUF_MANAGE_MODE2))

VPSS_ALG_BUF g_VpssAlgBuf[VPSS_INSTANCE_ALGFIXSIZE_NUM] = {{{{0}}}};
HI_S32 VPSS_AlgBuf_Malloc(VPSS_ALG_BUF *pstBuf)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i;
    ALG_MEM_NODE *pstMemPool = NULL;
    HI_CHAR acBufName[32] = {'\0'};
    if (NULL == pstBuf)
    {
        VPSS_ERROR("VPSS AlgBuf Malloc error: null pointer \n");
        return HI_FAILURE;
    }
    pstMemPool = pstBuf->stMemPool;
    if (pstBuf->stMMUBuf.u32StartSmmuAddr != 0)
    {
        VPSS_ERROR("repeat alg buffer malloc \n");
        return HI_FAILURE;
    }
    HI_OSAL_Snprintf(acBufName, 32, "VPSS_AlgBuf%d", pstBuf->u32Index);
    VPSS_OSAL_IntfTime_Start(VPSS_INTF_MALLOC_ALGBUF);
    s32Ret = HI_DRV_SMMU_AllocAndMap(acBufName, pstBuf->u32TotalSize, 0, &(pstBuf->stMMUBuf));
    if (s32Ret == HI_FAILURE)
    {
        VPSS_FATAL("VPSS SMMU AllocAndMap Failed!\n");
        return HI_FAILURE;
    }
    for (i = 0; i < VPSS_ALG_BUTT; i++)
    {
        pstMemPool[i].stMMUBuf.pu8StartVirAddr = (HI_U8 *)(pstBuf->stMMUBuf.pu8StartVirAddr + pstMemPool[i].u32MemOffset);
        pstMemPool[i].stMMUBuf.u32StartSmmuAddr = pstBuf->stMMUBuf.u32StartSmmuAddr + pstMemPool[i].u32MemOffset;
        pstMemPool[i].stMMUBuf.u32Size = pstMemPool[i].u32MemSize;
    }
    VPSS_OSAL_IntfTime_Stop(VPSS_INTF_MALLOC_ALGBUF);
#if VPSS_ALGBUF_DEG
    HI_PRINT("After malloc vpss alg buffer\n");
    VPSS_AlgBuf_Print1(pstBuf);
#endif
    return HI_SUCCESS;
}

HI_S32 VPSS_AlgBuf_Free(VPSS_ALG_BUF *pstBuf)
{
    if (NULL == pstBuf)
    {
        VPSS_ERROR("Vpss algbuf free error: null pointer \n");
        return HI_FAILURE;
    }
    if (0 == pstBuf->stMMUBuf.u32StartSmmuAddr || 0 == pstBuf->stMMUBuf.u32Size)
    {
        VPSS_ERROR("Vpss algbuf free error: invalid smmu addr \n");
        return HI_FAILURE;
    }
    if (pstBuf->u32TotalUseCount != 0)
    {
        VPSS_ERROR("Can't free algbuf, %d buffers in use", pstBuf->u32TotalUseCount);
        return HI_FAILURE;
    }
    HI_DRV_SMMU_UnmapAndRelease(&(pstBuf->stMMUBuf));
    return HI_SUCCESS;
}

HI_S32 VPSS_AlgBuf_Get(VPSS_ALG_BUF *pstBuf, VPSS_ALG_BUF_TYPE_E enAlgType,
                       HI_CHAR *pAlgName, HI_U32 u32SizeNeed, HI_U32 u32Align, SMMU_BUFFER_S *pSmmuBuf)
{
    HI_U32 i;
    ALG_MEM_NODE *pstMemPool = NULL;
    if (NULL == pstBuf)
    {
        VPSS_ERROR("Vpss algbuf get error: null pointer pstBuf\n");
        return HI_FAILURE;
    }
    pstMemPool = pstBuf->stMemPool;
    if (NULL == pSmmuBuf)
    {
        VPSS_ERROR("Vpss algbuf get error: null pointer pSmmuBuf\n");
        return HI_FAILURE;
    }

    for (i = 0; i < VPSS_ALG_BUTT; i++)
    {
        if (pstMemPool[i].enType == enAlgType)
        {
            if (u32SizeNeed > pstMemPool[i].u32MemSize)
            {
                VPSS_ERROR("Buffer(type %d) size needed %u is larger than real size already malloc %u\n",
                           enAlgType, u32SizeNeed, pSmmuBuf->u32Size);
                return HI_FAILURE;
            }
            if (0)
                HI_PRINT("i:%d StartAddr:%#x StartVirAddr:%#x size:%ukb \n",
                         i, pstMemPool[i].stMMUBuf.u32StartSmmuAddr,
                         (HI_U32)pstMemPool[i].stMMUBuf.pu8StartVirAddr,
                         pstMemPool[i].stMMUBuf.u32Size / 1024);
            if (pstMemPool[i].bNeedMap == HI_TRUE)
            {
                pSmmuBuf->u32Size = u32SizeNeed;
                pSmmuBuf->u32StartSmmuAddr = pstMemPool[i].stMMUBuf.u32StartSmmuAddr;
                pSmmuBuf->pu8StartVirAddr = pstMemPool[i].stMMUBuf.pu8StartVirAddr;
            }
            else
            {
                pSmmuBuf->u32Size = u32SizeNeed;
                pSmmuBuf->u32StartSmmuAddr = pstMemPool[i].stMMUBuf.u32StartSmmuAddr;
                pSmmuBuf->pu8StartVirAddr = NULL;
            }
            break;
        }
    }
    if (i == VPSS_ALG_BUTT)
    {
        VPSS_ERROR("Can't find mem type %d in mem pool\n", enAlgType);
        return HI_FAILURE;
    }
    else if (pSmmuBuf->u32StartSmmuAddr == 0 || pSmmuBuf->u32Size == 0)
    {
        VPSS_ERROR("Get wrong smmu addr \n");
        return HI_FAILURE;
    }
    pstMemPool[i].bInUse = HI_TRUE;
    pstBuf->u32TotalUseCount++;
#if VPSS_ALGBUF_DEG
    HI_PRINT("get AlgBuf success enAlgType:%d\n", enAlgType);
    VPSS_AlgBuf_Print1(pstBuf);
#endif
    return HI_SUCCESS;
}

HI_S32 VPSS_AlgBuf_Rel(VPSS_ALG_BUF *pstBuf, SMMU_BUFFER_S *pstMMUBuf, VPSS_ALG_BUF_TYPE_E enAlgType)
{
    HI_S32 i;
    ALG_MEM_NODE *pstMemPool = NULL;
    if (NULL == pstBuf || NULL == pstMMUBuf)
    {
        VPSS_ERROR("Vpss algbuf release error: null pointer \n");
        return HI_FAILURE;
    }
    pstMemPool = pstBuf->stMemPool;
    if (pstBuf->stMMUBuf.u32StartSmmuAddr == 0)
    {
        VPSS_ERROR("Vpss algbuf release error: invalid smmu addr \n");
        return HI_FAILURE;
    }
    for (i = 0; i < VPSS_ALG_BUTT; i++)
    {
        if (pstMemPool[i].enType == enAlgType && pstMemPool[i].bInUse == HI_TRUE)
        {
#if VPSS_ALGBUF_DEG
            HI_PRINT("Do VPSS_AlgBuf_Rel type:%d\n", enAlgType);
            VPSS_AlgBuf_Print1(pstBuf);
#endif
            pstMemPool[i].bInUse = HI_FALSE;
            pstBuf->u32TotalUseCount--;
            break;
        }
        else if (pstMemPool[i].enType == enAlgType && pstMemPool[i].bInUse == HI_FALSE)
        {
            VPSS_ERROR("Vpss algbuf repeat release type:%d\n", enAlgType);
            return HI_SUCCESS;
        }
    }
    if (i == VPSS_ALG_BUTT)
    {
        VPSS_ERROR("Can't find mem type %d in mem pool\n", enAlgType);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}
#endif