#include "vmm_osal.h"
#include "vmm_memory_ops.h"
#include "vmm_osal.h"

static SINT32 VMM_IsSmmuSupport(VOID)
{
#ifdef HI_SMMU_SUPPORT
    return MEM_OPS_TRUE;
#else
    return MEM_OPS_FALSE;
#endif
}

static SINT32 VMM_Alloc_MMZ(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;
    MMZ_BUFFER_S stMMZBuf;
    OSAL_FP_memset(&stMMZBuf, 0, sizeof(MMZ_BUFFER_S));

    Ret = HI_DRV_MMZ_Alloc(pBufferName, NULL, BufSize, 64, &stMMZBuf);

    if ((Ret != MEM_OPS_SUCCESS) || (stMMZBuf.u32StartPhyAddr == 0))
    {
        return MEM_OPS_ALLOC_FAILED;
    }

    pOutBufInfo->pStartVirAddr  = (ULONG)stMMZBuf.pu8StartVirAddr;
    pOutBufInfo->StartPhyAddr   = stMMZBuf.u32StartPhyAddr;
    pOutBufInfo->Size           = stMMZBuf.u32Size;
    PRINT(PRN_DBG, "%s,%d, Phyaddr = 0x%x, VirAddr = 0x%lx, Size = %d\n", __func__, __LINE__,
          pOutBufInfo->StartPhyAddr, pOutBufInfo->pStartVirAddr, pOutBufInfo->Size);
    return Ret;
}

static VOID VMM_Release_MMZ(VMM_BUFFER_S *pBufInfo)
{
    MMZ_BUFFER_S stMMZBuf;
    OSAL_FP_memset(&stMMZBuf, 0, sizeof(MMZ_BUFFER_S));

    stMMZBuf.u32StartPhyAddr  = pBufInfo->StartPhyAddr;
    stMMZBuf.pu8StartVirAddr  = UINT64_PTR(pBufInfo->pStartVirAddr);
    stMMZBuf.u32Size          = pBufInfo->Size;

    HI_DRV_MMZ_Release(&stMMZBuf);
    PRINT(PRN_DBG, "%s,%d, Phyaddr = 0x%x, VirAddr = 0x%lx, Size = %d\n", __func__, __LINE__,
          pBufInfo->StartPhyAddr, pBufInfo->pStartVirAddr, pBufInfo->Size);
    return;
}

static SINT32 VMM_Map_MMZ(UINT32 IsCached, VMM_BUFFER_S *pBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;
    MMZ_BUFFER_S stMMZBuf;
    OSAL_FP_memset(&stMMZBuf, 0, sizeof(MMZ_BUFFER_S));

    stMMZBuf.u32StartPhyAddr  = pBufInfo->StartPhyAddr;
    stMMZBuf.u32Size          = pBufInfo->Size;

    if (IsCached)
    {
        Ret = HI_DRV_MMZ_MapCache(&stMMZBuf);
    }
    else
    {
        Ret = HI_DRV_MMZ_Map(&stMMZBuf);
    }

    if (Ret == MEM_OPS_SUCCESS)
    {
        pBufInfo->pStartVirAddr  = (ULONG)stMMZBuf.pu8StartVirAddr;
    }

    return Ret;
}

static VOID VMM_Unmap_MMZ(VMM_BUFFER_S *pBufInfo)
{
    MMZ_BUFFER_S stMMZBuf;
    OSAL_FP_memset(&stMMZBuf, 0, sizeof(MMZ_BUFFER_S));

    stMMZBuf.u32StartPhyAddr  = pBufInfo->StartPhyAddr;
    stMMZBuf.pu8StartVirAddr  = UINT64_PTR(pBufInfo->pStartVirAddr);
    stMMZBuf.u32Size          = pBufInfo->Size;

    HI_DRV_MMZ_Unmap(&stMMZBuf);

    return;
}


static SINT32 VMM_AllocAndMap_MMZ(SINT8 *pBufferName, UINT32 BufSize, UINT32 IsCached, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    Ret = VMM_Alloc_MMZ(pBufferName, BufSize, pOutBufInfo);

    if (Ret != MEM_OPS_SUCCESS)
    {
        return MEM_OPS_ALLOC_FAILED;
    }

    Ret = VMM_Map_MMZ(IsCached, pOutBufInfo);

    if (Ret != MEM_OPS_SUCCESS)
    {
        VMM_Release_MMZ(pOutBufInfo);

        return MEM_OPS_MAP_FAILED;
    }

    PRINT(PRN_DBG, "%s,%d, Phyaddr = 0x%x, VirAddr = 0x%lx, Size = %d\n", __func__, __LINE__,
          pOutBufInfo->StartPhyAddr, pOutBufInfo->pStartVirAddr, pOutBufInfo->Size);
    return Ret;
}

static VOID VMM_UnmapAndRelease_MMZ(VMM_BUFFER_S *pBufInfo)
{
    VMM_Unmap_MMZ(pBufInfo);

    VMM_Release_MMZ(pBufInfo);
    PRINT(PRN_DBG, "%s,%d, Phyaddr = 0x%x, VirAddr = 0x%lx, Size = %d\n", __func__, __LINE__,
          pBufInfo->StartPhyAddr, pBufInfo->pStartVirAddr, pBufInfo->Size);
    return;
}

static SINT32 VMM_Alloc_MMZ_SEC(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

#ifdef HI_TEE_SUPPORT
    MMZ_BUFFER_S stMMZBuf;
    OSAL_FP_memset(&stMMZBuf, 0, sizeof(MMZ_BUFFER_S));

    Ret = HI_DRV_SECMMZ_Alloc(pBufferName, BufSize, 64, &stMMZBuf);

    if ((Ret != MEM_OPS_SUCCESS) || (stMMZBuf.u32StartPhyAddr == 0))
    {
        return MEM_OPS_ALLOC_FAILED;
    }

    pOutBufInfo->pStartVirAddr  = (ULONG)stMMZBuf.pu8StartVirAddr;
    pOutBufInfo->StartPhyAddr   = stMMZBuf.u32StartPhyAddr;
    pOutBufInfo->Size           = stMMZBuf.u32Size;
#else
    PRINT(PRN_ERROR, "%s,%d, this chip not support TEE!", __func__, __LINE__);

    Ret = MEM_OPS_NOT_SUPPORT;
#endif
    return Ret;
}

#ifdef HI_TEE_SUPPORT
static VOID VMM_Release_MMZ_SEC(VMM_BUFFER_S *pBufInfo)
{
    MMZ_BUFFER_S stMMZBuf;
    OSAL_FP_memset(&stMMZBuf, 0, sizeof(MMZ_BUFFER_S));

    stMMZBuf.u32StartPhyAddr  = pBufInfo->StartPhyAddr;
    stMMZBuf.pu8StartVirAddr  = UINT64_PTR(pBufInfo->pStartVirAddr);
    stMMZBuf.u32Size          = pBufInfo->Size;

    HI_DRV_SECMMZ_Release(&stMMZBuf);

    return;
}
#else
#define VMM_Release_MMZ_SEC(args...) do {PRINT(PRN_ERROR,"%s,%d, this chip not support TEE!", __func__, __LINE__);} while(0)
#endif

#ifdef HI_SMMU_SUPPORT
static SINT32 VMM_Alloc_SMMU(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;
    SMMU_BUFFER_S stSMMUBuf;
    OSAL_FP_memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));

    Ret = HI_DRV_SMMU_Alloc(pBufferName, BufSize, 64, &stSMMUBuf);

    if ((Ret != MEM_OPS_SUCCESS) || (stSMMUBuf.u32StartSmmuAddr == 0))
    {
        return MEM_OPS_ALLOC_FAILED;
    }

    pOutBufInfo->pStartVirAddr  = (ULONG)stSMMUBuf.pu8StartVirAddr;
    pOutBufInfo->StartPhyAddr   = stSMMUBuf.u32StartSmmuAddr;
    pOutBufInfo->Size           = stSMMUBuf.u32Size;

    PRINT(PRN_DBG, "%s,%d, Phyaddr = 0x%x, VirAddr = 0x%lx, Size = %d\n", __func__, __LINE__,
          pOutBufInfo->StartPhyAddr, pOutBufInfo->pStartVirAddr, pOutBufInfo->Size);
    return Ret;
}

static VOID VMM_Release_SMMU(VMM_BUFFER_S *pBufInfo)
{
    SMMU_BUFFER_S stSMMUBuf;
    OSAL_FP_memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));

    stSMMUBuf.u32StartSmmuAddr = pBufInfo->StartPhyAddr;
    stSMMUBuf.pu8StartVirAddr  = UINT64_PTR(pBufInfo->pStartVirAddr);
    stSMMUBuf.u32Size          = pBufInfo->Size;

    HI_DRV_SMMU_Release(&stSMMUBuf);
    PRINT(PRN_DBG, "%s,%d, Phyaddr = 0x%x, VirAddr = 0x%lx, Size = %d\n", __func__, __LINE__,
          pBufInfo->StartPhyAddr, pBufInfo->pStartVirAddr, pBufInfo->Size);
    return;
}

static SINT32 VMM_Map_SMMU(UINT32 IsCached, VMM_BUFFER_S *pBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;
    SMMU_BUFFER_S stSMMUBuf;
    OSAL_FP_memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));

    stSMMUBuf.u32StartSmmuAddr = pBufInfo->StartPhyAddr;
    stSMMUBuf.u32Size          = pBufInfo->Size;

    if (IsCached)
    {
        Ret = HI_DRV_SMMU_MapCache(&stSMMUBuf);
    }
    else
    {
        Ret = HI_DRV_SMMU_Map(&stSMMUBuf);
    }

    if (Ret == MEM_OPS_SUCCESS)
    {
        pBufInfo->pStartVirAddr  = (ULONG)stSMMUBuf.pu8StartVirAddr;
    }

    return Ret;
}

static VOID VMM_Unmap_SMMU(VMM_BUFFER_S *pBufInfo)
{
    SMMU_BUFFER_S stSMMUBuf;
    OSAL_FP_memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));

    stSMMUBuf.u32StartSmmuAddr = pBufInfo->StartPhyAddr;
    stSMMUBuf.pu8StartVirAddr  = UINT64_PTR(pBufInfo->pStartVirAddr);
    stSMMUBuf.u32Size          = pBufInfo->Size;

    HI_DRV_SMMU_Unmap(&stSMMUBuf);

    return;
}

static SINT32 VMM_AllocAndMap_SMMU(SINT8 *pBufferName, UINT32 BufSize, UINT32 IsCached, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    Ret = VMM_Alloc_SMMU(pBufferName, BufSize, pOutBufInfo);

    if (Ret != MEM_OPS_SUCCESS)
    {
        return MEM_OPS_ALLOC_FAILED;
    }

    Ret = VMM_Map_SMMU(IsCached, pOutBufInfo);

    if (Ret != MEM_OPS_SUCCESS)
    {
        VMM_Release_SMMU(pOutBufInfo);

        return MEM_OPS_MAP_FAILED;
    }

    PRINT(PRN_DBG, "%s,%d, Phyaddr = 0x%x, VirAddr = 0x%lx, Size = %d\n", __func__, __LINE__,
          pOutBufInfo->StartPhyAddr, pOutBufInfo->pStartVirAddr, pOutBufInfo->Size);
    return Ret;
}

static VOID VMM_UnmapAndRelease_SMMU(VMM_BUFFER_S *pBufInfo)
{
    VMM_Unmap_SMMU(pBufInfo);

    VMM_Release_SMMU(pBufInfo);
    PRINT(PRN_DBG, "%s,%d, Phyaddr = 0x%x, VirAddr = 0x%lx, Size = %d\n", __func__, __LINE__,
          pBufInfo->StartPhyAddr, pBufInfo->pStartVirAddr, pBufInfo->Size);
    return;
}


static SINT32 VMM_Alloc_SMMU_SEC(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

#ifdef HI_TEE_SUPPORT
    SMMU_BUFFER_S stSMMUBuf;
    OSAL_FP_memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));

    Ret = HI_DRV_SECSMMU_Alloc(pBufferName, BufSize, 64, &stSMMUBuf);

    if ((Ret != MEM_OPS_SUCCESS) || (stSMMUBuf.u32StartSmmuAddr == 0))
    {
        return MEM_OPS_ALLOC_FAILED;
    }

    pOutBufInfo->pStartVirAddr  = (ULONG)stSMMUBuf.pu8StartVirAddr;
    pOutBufInfo->StartPhyAddr   = stSMMUBuf.u32StartSmmuAddr;
    pOutBufInfo->Size           = stSMMUBuf.u32Size;
#else
    PRINT(PRN_ERROR, "%s,%d, this chip not support TEE!", __func__, __LINE__);
    Ret = MEM_OPS_NOT_SUPPORT;
#endif

    return Ret;
}

#ifdef HI_TEE_SUPPORT
static VOID VMM_Release_SMMU_SEC(VMM_BUFFER_S *pBufInfo)
{
    SMMU_BUFFER_S stSMMUBuf;
    OSAL_FP_memset(&stSMMUBuf, 0, sizeof(SMMU_BUFFER_S));

    stSMMUBuf.u32StartSmmuAddr = pBufInfo->StartPhyAddr;
    stSMMUBuf.pu8StartVirAddr  = UINT64_PTR(pBufInfo->pStartVirAddr);
    stSMMUBuf.u32Size          = pBufInfo->Size;

    HI_DRV_SECSMMU_Release(&stSMMUBuf);

    return;
}
#else
#define VMM_Release_SMMU_SEC(args...) do {PRINT(PRN_ERROR,"%s,%d, this chip not support TEE!", __func__, __LINE__);} while(0)
#endif

#else

static SINT32 VMM_Alloc_SMMU(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    PRINT(PRN_ERROR, "%s,%d, alloc Name '%s', size = %d, this chip not support smmu!", __func__, __LINE__, pBufferName, BufSize);

    return MEM_OPS_NOT_SUPPORT;
}

static VOID VMM_Release_SMMU(VMM_BUFFER_S *pBufInfo)
{
    PRINT(PRN_ERROR, "%s,%d, release Addr = 0x%x, this chip not support smmu!", __func__, __LINE__, pBufInfo->StartPhyAddr);

    return MEM_OPS_NOT_SUPPORT;
}

static SINT32 VMM_Map_SMMU(UINT32 IsCached, VMM_BUFFER_S *pBufInfo)
{
    PRINT(PRN_ERROR, "%s,%d, map Addr = 0x%x, this chip not support smmu!", __func__, __LINE__, pBufInfo->StartPhyAddr);

    return MEM_OPS_NOT_SUPPORT;
}

static VOID VMM_Unmap_SMMU(VMM_BUFFER_S *pBufInfo)
{
    PRINT(PRN_ERROR, "%s,%d, unmap Addr = 0x%x, this chip not support smmu!", __func__, __LINE__, pBufInfo->StartPhyAddr);

    return;
}

static SINT32 VMM_AllocAndMap_SMMU(SINT8 *pBufferName, UINT32 BufSize, UINT32 IsCached, VMM_BUFFER_S *pOutBufInfo)
{
    PRINT(PRN_ERROR, "%s,%d, alloc Name '%s', size = %d, this chip not support smmu!", __func__, __LINE__, pBufferName, BufSize);

    return MEM_OPS_NOT_SUPPORT;
}

static VOID VMM_UnmapAndRelease_SMMU(VMM_BUFFER_S *pBufInfo)
{
    PRINT(PRN_ERROR, "%s,%d, release Addr = 0x%x, this chip not support smmu!", __func__, __LINE__, pBufInfo->StartPhyAddr);

    return;
}

static SINT32 VMM_Alloc_SMMU_SEC(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    PRINT(PRN_ERROR, "%s,%d, alloc Name '%s', size = %d, this chip not support smmu!", __func__, __LINE__, pBufferName, BufSize);

    return MEM_OPS_NOT_SUPPORT;
}

static VOID VMM_Release_SMMU_SEC(VMM_BUFFER_S *pBufInfo)
{
    PRINT(PRN_ERROR, "%s,%d, release Addr = 0x%x, this chip not support smmu!", __func__, __LINE__, pBufInfo->StartPhyAddr);

    return;
}
#endif

static SINT32 VMM_Alloc_ForceMMZ(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    return VMM_Alloc_MMZ(pBufferName, BufSize, pOutBufInfo);
}

static VOID VMM_Release_ForceMMZ(VMM_BUFFER_S *pBufInfo)
{
    return VMM_Release_MMZ(pBufInfo);
}

static SINT32 VMM_Map_ForceMMZ(UINT32 IsCached, VMM_BUFFER_S *pBufInfo)
{
    return VMM_Map_MMZ(IsCached, pBufInfo);
}

static VOID VMM_Unmap_ForceMMZ(VMM_BUFFER_S *pBufInfo)
{
    VMM_Unmap_MMZ(pBufInfo);

    return;
}

static SINT32 VMM_AllocAndMap_ForceMMZ(SINT8 *pBufferName, UINT32 BufSize, UINT32 IsCached, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    Ret = VMM_AllocAndMap_MMZ(pBufferName, BufSize, IsCached, pOutBufInfo);

    return Ret;
}

static VOID VMM_UnmapAndRelease_ForceMMZ(VMM_BUFFER_S *pBufInfo)
{
    return VMM_UnmapAndRelease_MMZ(pBufInfo);
}

static SINT32 VMM_Alloc_SEC_ForceMMZ(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

#ifdef HI_TEE_SUPPORT
    Ret = VMM_Alloc_MMZ_SEC(pBufferName, BufSize, pOutBufInfo);
#else
    PRINT(PRN_ERROR, "%s,%d, alloc Name '%s', size = %d, this chip not support TEE!", __func__, __LINE__, pBufferName, BufSize);
    Ret = MEM_OPS_NOT_SUPPORT;
#endif

    return Ret;
}

static VOID VMM_Release_SEC_ForceMMZ(VMM_BUFFER_S *pBufInfo)
{
#ifdef HI_TEE_SUPPORT
    VMM_Release_MMZ_SEC(pBufInfo);
#else
    PRINT(PRN_ERROR, "%s,%d, release Addr = 0x%x, this chip not support TEE!", __func__, __LINE__, pBufInfo->StartPhyAddr);
#endif

    return;
}

static SINT32 VMM_Alloc_Adapt(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    if (VMM_IsSmmuSupport())
    {
        Ret = VMM_Alloc_SMMU(pBufferName, BufSize, pOutBufInfo);
    }
    else
    {
        Ret = VMM_Alloc_MMZ(pBufferName, BufSize, pOutBufInfo);
    }

    return Ret;
}

static VOID VMM_Release_Adapt(VMM_BUFFER_S *pBufInfo)
{
    if (VMM_IsSmmuSupport())
    {
        VMM_Release_SMMU(pBufInfo);
    }
    else
    {
        VMM_Release_MMZ(pBufInfo);
    }

    return;
}

static SINT32 VMM_Map_Adapt(UINT32 IsCached, VMM_BUFFER_S *pBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    if (VMM_IsSmmuSupport())
    {
        Ret = VMM_Map_SMMU(IsCached, pBufInfo);
    }
    else
    {
        Ret = VMM_Map_MMZ(IsCached, pBufInfo);
    }

    return Ret;
}

static VOID VMM_Unmap_Adapt(VMM_BUFFER_S *pBufInfo)
{
    if (VMM_IsSmmuSupport())
    {
        VMM_Unmap_SMMU(pBufInfo);
    }
    else
    {
        VMM_Unmap_MMZ(pBufInfo);
    }

    return;
}

static SINT32 VMM_AllocAndMap_Adapt(SINT8 *pBufferName, UINT32 BufSize, UINT32 IsCached, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    if (VMM_IsSmmuSupport())
    {
        Ret = VMM_AllocAndMap_SMMU(pBufferName, BufSize, IsCached, pOutBufInfo);
    }
    else
    {
        Ret = VMM_AllocAndMap_MMZ(pBufferName, BufSize, IsCached, pOutBufInfo);
    }

    return Ret;
}

static VOID VMM_UnmapAndRelease_Adapt(VMM_BUFFER_S *pBufInfo)
{
    if (VMM_IsSmmuSupport())
    {
        VMM_UnmapAndRelease_SMMU(pBufInfo);
    }
    else
    {
        VMM_UnmapAndRelease_MMZ(pBufInfo);
    }

    return;
}

static SINT32 VMM_Alloc_SEC_Adapt(SINT8 *pBufferName, UINT32 BufSize, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    if (VMM_IsSmmuSupport())
    {
        Ret = VMM_Alloc_SMMU_SEC(pBufferName, BufSize, pOutBufInfo);
    }
    else
    {
        Ret = VMM_Alloc_MMZ_SEC(pBufferName, BufSize, pOutBufInfo);
    }

    return Ret;
}

static VOID VMM_Release_SEC_Adapt(VMM_BUFFER_S *pBufInfo)
{
    if (VMM_IsSmmuSupport())
    {
        VMM_Release_SMMU_SEC(pBufInfo);
    }
    else
    {
        VMM_Release_MMZ_SEC(pBufInfo);
    }

    return;
}

static SINT32 VMM_AllocAndMap(SINT8 *pBufferName, UINT32 BufSize, UINT32 IsCached, VMM_MEM_TYPE_E MemType, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    switch (MemType)
    {
        case VMM_MEM_TYPE_SYS_ADAPT:
            Ret = VMM_AllocAndMap_Adapt(pBufferName, BufSize, IsCached, pOutBufInfo);
            break;

        case VMM_MEM_TYPE_FORCE_MMZ:
            Ret = VMM_AllocAndMap_ForceMMZ(pBufferName, BufSize, IsCached, pOutBufInfo);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d,memType (%d) not support\n", __func__, __LINE__, MemType);
            break;
    }

    return Ret;
}

static VOID VMM_UnmapAndRelease(VMM_BUFFER_S *pBufInfo)
{
    VMM_MEM_TYPE_E MemType = pBufInfo->MemType;

    switch (MemType)
    {
        case VMM_MEM_TYPE_SYS_ADAPT:
            VMM_UnmapAndRelease_Adapt(pBufInfo);
            break;

        case VMM_MEM_TYPE_FORCE_MMZ:
            VMM_UnmapAndRelease_ForceMMZ(pBufInfo);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d,memType (%d) not support\n", __func__, __LINE__, MemType);
            break;
    }

    return;
}

static SINT32 VMM_Alloc(SINT8 *pBufferName, UINT32 BufSize, VMM_MEM_TYPE_E MemType, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    switch (MemType)
    {
        case VMM_MEM_TYPE_SYS_ADAPT:
            Ret = VMM_Alloc_Adapt(pBufferName, BufSize, pOutBufInfo);
            break;

        case VMM_MEM_TYPE_FORCE_MMZ:
            Ret = VMM_Alloc_ForceMMZ(pBufferName, BufSize, pOutBufInfo);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d,memType (%d) not support\n", __func__, __LINE__, MemType);
            break;
    }

    return Ret;
}

static VOID VMM_Release(VMM_BUFFER_S *pBufInfo)
{
    VMM_MEM_TYPE_E MemType = pBufInfo->MemType;

    switch (MemType)
    {
        case VMM_MEM_TYPE_SYS_ADAPT:
            VMM_Release_Adapt(pBufInfo);
            break;

        case VMM_MEM_TYPE_FORCE_MMZ:
            VMM_Release_ForceMMZ(pBufInfo);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d,memType (%d) not support\n", __func__, __LINE__, MemType);
            break;
    }

    return;
}

static SINT32 VMM_Map(UINT32 IsCached, VMM_BUFFER_S *pBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;
    VMM_MEM_TYPE_E MemType = pBufInfo->MemType;

    switch (MemType)
    {
        case VMM_MEM_TYPE_SYS_ADAPT:
            Ret = VMM_Map_Adapt(IsCached, pBufInfo);
            break;

        case VMM_MEM_TYPE_FORCE_MMZ:
            Ret = VMM_Map_ForceMMZ(IsCached, pBufInfo);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d,memType (%d) not support\n", __func__, __LINE__, MemType);
            break;
    }

    return Ret;
}

static VOID VMM_Unmap(VMM_BUFFER_S *pBufInfo)
{
    VMM_MEM_TYPE_E MemType = pBufInfo->MemType;

    switch (MemType)
    {
        case VMM_MEM_TYPE_SYS_ADAPT:
            VMM_Unmap_Adapt(pBufInfo);
            break;

        case VMM_MEM_TYPE_FORCE_MMZ:
            VMM_Unmap_ForceMMZ(pBufInfo);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d,memType (%d) not support\n", __func__, __LINE__, MemType);
            break;
    }

    return;
}

static SINT32 VMM_Alloc_SEC(SINT8 *pBufferName, UINT32 BufSize, VMM_MEM_TYPE_E MemType, VMM_BUFFER_S *pOutBufInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    switch (MemType)
    {
        case VMM_MEM_TYPE_SYS_ADAPT:
            Ret = VMM_Alloc_SEC_Adapt(pBufferName, BufSize, pOutBufInfo);
            break;

        case VMM_MEM_TYPE_FORCE_MMZ:
            Ret = VMM_Alloc_SEC_ForceMMZ(pBufferName, BufSize, pOutBufInfo);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d,memType (%d) not support\n", __func__, __LINE__, MemType);
            break;
    }

    return Ret;
}

static VOID VMM_Release_SEC(VMM_BUFFER_S *pBufInfo)
{
    VMM_MEM_TYPE_E MemType = pBufInfo->MemType;

    switch (MemType)
    {
        case VMM_MEM_TYPE_SYS_ADAPT:
            VMM_Release_SEC_Adapt(pBufInfo);
            break;

        case VMM_MEM_TYPE_FORCE_MMZ:
            VMM_Release_SEC_ForceMMZ(pBufInfo);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d,memType (%d) not support\n", __func__, __LINE__, MemType);
            break;
    }

    return;
}

SINT32 VMM_Ops_Alloc(VMM_BUFFER_S *pMemInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    D_VMM_CHECK_PTR_RET(pMemInfo, MEM_OPS_NULL_PTR);

    if (pMemInfo->SecFlag)
    {
        Ret = VMM_Alloc_SEC(pMemInfo->BufName, pMemInfo->Size, pMemInfo->MemType, pMemInfo);

        if (Ret != VMM_SUCCESS)
        {
            PRINT(PRN_ERROR, "%s,%d, ERROR: Alloc sec mem %s size %d failed.\n", __func__, __LINE__, pMemInfo->BufName, pMemInfo->Size);
        }
        else
        {
            pMemInfo->pStartVirAddr = (pMemInfo->Map) ? (ULONG)pMemInfo->StartPhyAddr : 0;
        }
    }
    else
    {
        //PRINT(PRN_ALWS, "%s, %d\n", __func__, __LINE__);

        if (pMemInfo->Map)
        {
            Ret = VMM_AllocAndMap(pMemInfo->BufName, pMemInfo->Size, pMemInfo->Cache, pMemInfo->MemType, pMemInfo);
        }
        else
        {
            Ret = VMM_Alloc(pMemInfo->BufName, pMemInfo->Size, pMemInfo->MemType, pMemInfo);
        }

        if (Ret == VMM_SUCCESS)
        {
            if (MEM_AddMemRecord(pMemInfo->StartPhyAddr, (VOID *)pMemInfo->pStartVirAddr, pMemInfo->Size) != VMM_SUCCESS)
            {
                PRINT(PRN_ERROR, "%s,%d, WARNING:MEM_AddMemRecord return Failed!\n", __func__, __LINE__);
            }
        }
    }

    return Ret;
}

SINT32 VMM_Ops_Release(VMM_BUFFER_S *pMemInfo)
{
    D_VMM_CHECK_PTR_RET(pMemInfo, MEM_OPS_NULL_PTR);

    if (pMemInfo->SecFlag)
    {
        VMM_Release_SEC(pMemInfo);
    }
    else
    {
        if (pMemInfo->Map)
        {
            VMM_UnmapAndRelease(pMemInfo);
        }
        else
        {
            VMM_Release(pMemInfo);
        }

        if (MEM_DelMemRecord(pMemInfo->StartPhyAddr, (VOID *)pMemInfo->pStartVirAddr, pMemInfo->Size) != VMM_SUCCESS)
        {
            PRINT(PRN_ERROR, "%s,%d, WARNING:MEM_DelMemRecord return Failed!\n", __func__, __LINE__);
        }
    }

    return MEM_OPS_SUCCESS;
}

SINT32 VMM_Ops_Map(VMM_BUFFER_S *pMemInfo)
{
    SINT32 Ret = MEM_OPS_SUCCESS;

    D_VMM_CHECK_PTR_RET(pMemInfo, MEM_OPS_NULL_PTR);

    VMM_ASSERT(pMemInfo->Map == 0);

    if (pMemInfo->SecFlag)
    {
        PRINT(PRN_ERROR, "%s,%d, WARNING:SEC MEMORY NOT SUPPORT MAP VirAddr.\n", __func__, __LINE__);

        return MEM_OPS_NOT_SUPPORT;
    }

    if (pMemInfo->pStartVirAddr != 0)
    {
        PRINT(PRN_ERROR, "%s,%d, WARNING:BufName = %s, pStartVirAddr = 0x%llx already map!\n", __func__, __LINE__,
              pMemInfo->BufName, pMemInfo->pStartVirAddr);

        return MEM_OPS_MAP_FAILED;
    }

    Ret = VMM_Map(pMemInfo->Cache, pMemInfo);

    if (Ret == MEM_OPS_SUCCESS)
    {
        pMemInfo->Map = 1;
    }

    return Ret;
}

SINT32 VMM_Ops_Unmap(VMM_BUFFER_S *pMemInfo)
{
    D_VMM_CHECK_PTR_RET(pMemInfo, MEM_OPS_NULL_PTR);

    VMM_ASSERT(pMemInfo->Map == 1);

    if (pMemInfo->SecFlag)
    {
        PRINT(PRN_ERROR, "%s,%d, WARNING:SEC MEMORY NOT SUPPORT MAP VirAddr.\n", __func__, __LINE__);

        return MEM_OPS_NOT_SUPPORT;
    }

    VMM_Unmap(pMemInfo);

    pMemInfo->Map = 0;
    pMemInfo->Cache = 0;
    pMemInfo->pStartVirAddr = 0;

    return MEM_OPS_SUCCESS;
}

SINT32 VMM_Ops_ConfigMemBlock(VMM_BUFFER_S *pMemBlk)   //preAllocUse
{
    D_VMM_CHECK_PTR_RET(pMemBlk, MEM_OPS_NULL_PTR);

    return MEM_OPS_NOT_SUPPORT;
}


