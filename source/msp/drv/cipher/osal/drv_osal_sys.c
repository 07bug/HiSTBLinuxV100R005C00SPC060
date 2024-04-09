/******************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ext_aead.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "drv_klad_ext.h"

/************************* Internal Structure Definition *********************/
/** \addtogroup      base type*/
/** @{*/  /** <!-- [base]*/


/* under TEE, we only can malloc secure mmz at system steup,
 * then map the mmz to Smmu, but the smmu can't map to cpu address,
 * so we must save the cpu address in a static table when malloc and map mmz.
 * when call crypto_mem_map, we try to query the table to get cpu address firstly,
 * if can't get cpu address from the table, then call system api to map it.
 */
#define CRYPTO_MEM_MAP_TABLE_DEPTH      32

typedef struct
{
    u32 valid;
    compat_addr dma;
    void       *via;
}crypto_mem_map_table;

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      base*/
/** @{*/  /** <!--[base]*/

/*****************************************************************
 *                       mmz/mmu api                             *
 *****************************************************************/

/*brief allocate and map a mmz or smmu memory
* we can't allocate smmu directly during TEE boot period.
* in addition, the buffer of cipher node list must be mmz.
* so here we have to allocate a mmz memory then map to smmu if necessary.
*/
static s32 crypto_mem_alloc_remap(crypto_mem *mem, u32 type, s8 const *name, u32 size)
{
    crypto_memset(mem, sizeof(crypto_mem), 0, sizeof(crypto_mem));

    HI_LOG_DEBUG("mem_alloc_remap()- name %s, size 0x%x\n", name, size);

#ifdef WITH_HI3798MX_PLATFORM

    /* allocate mmz, only support 32-bit ddr */

    ADDR_L32(mem->mmz_addr) = new_mmb(name, size, SEC_MMZ, "SEC-MMZ");
    if(0 == ADDR_L32(mem->mmz_addr))
    {
        return HI_LOG_ERR_MEM;
    }
    ADDR_L32(mem->dma_addr) = ADDR_L32(mem->mmz_addr);
    mem->dma_size = size;

    /* map mmz to cpu */
    mem->dma_virt = (void*)remap_mmb(ADDR_L32(mem->mmz_addr));
    if(HI_NULL == mem->dma_virt)
    {
        (HI_VOID)delete_mmb(ADDR_L32(mem->mmz_addr));
        return HI_LOG_ERR_MEM;
    }
#else
    {
        s32 ret = HI_FAILURE;
        MMZ_BUFFER_S stSecMBuf;
        SMMU_BUFFER_S stSecSmmuBuf;

        stSecSmmuBuf.u32StartSmmuAddr = 0;
        stSecSmmuBuf.pu8StartVirAddr = 0;
        stSecSmmuBuf.u32Size = 0;

        /* allocate mmz, only support 32-bit ddr */
        stSecMBuf.u32Size = size;
        ret = HI_DRV_MMZ_Alloc(name, HI_NULL, size, 16, &stSecMBuf);
        if (HI_SUCCESS != ret)
        {
            return HI_LOG_ERR_MEM;
        }

        /* map mmz to cpu */
        ret = HI_DRV_MMZ_Map(&stSecMBuf);
        if (HI_SUCCESS != ret)
        {
            (HI_VOID)HI_DRV_MMZ_Release(&stSecMBuf);
            return HI_LOG_ERR_MEM;
        }
        mem->dma_virt = stSecMBuf.pu8StartVirAddr;
        ADDR_L32(mem->dma_addr) = stSecMBuf.u32StartPhyAddr;
        ADDR_L32(mem->mmz_addr) = stSecMBuf.u32StartPhyAddr;
        mem->dma_size = size;

#ifdef CRYPTO_SMMU_SUPPORT
        /* mmz map to smmu */
        ADDR_L32(mem->dma_addr) = HI_DRV_MMZ_MapToSmmu(&stSecMBuf);
        if (0x00 == ADDR_L32(mem->dma_addr))
        {
            (HI_VOID)HI_DRV_MMZ_Unmap(&stSecMBuf);
            (HI_VOID)HI_DRV_MMZ_Release(&stSecMBuf);
            return HI_LOG_ERR_MEM;
        }
#endif
     }
    HI_LOG_DEBUG("MMZ/MMU malloc, MMZ 0x%x, MMZ/MMU 0x%x, VIA 0x%p, SIZE 0x%x\n",
        ADDR_L32(mem->mmz_addr), ADDR_L32(mem->dma_addr), mem->dma_virt, size);
#endif

    mem->user_buf = HI_NULL;

    return HI_SUCCESS;
}

/*brief release and unmap a mmz or smmu memory */
static s32 crypto_mem_release_unmap(crypto_mem *mem)
{
    s32 ret = HI_FAILURE;

    HI_LOG_DEBUG("mem_release_unmap()- dma 0x%x, via 0x%p, size 0x%x\n",
        ADDR_L32(mem->dma_addr), mem->dma_virt, mem->dma_size);

#ifdef WITH_HI3798MX_PLATFORM
    (void)unmap_mmb(mem->dma_virt);
    (void)delete_mmb(ADDR_L32(mem->mmz_addr));

#else
#ifdef CRYPTO_SMMU_SUPPORT
    {
        SMMU_BUFFER_S stSmmuBuf;

        /* umap mmz from smmu */
        stSmmuBuf.pu8StartVirAddr = mem->dma_virt;
        stSmmuBuf.u32StartSmmuAddr = ADDR_L32(mem->dma_addr);
        stSmmuBuf.u32Size = mem->dma_size;
        ret = HI_DRV_MMZ_UnmapFromSmmu(&stSmmuBuf);
    }
#endif
    {
        MMZ_BUFFER_S stSecMBuf;

        /* umap and free mmz */
        stSecMBuf.u32StartPhyAddr = ADDR_L32(mem->mmz_addr);
        stSecMBuf.pu8StartVirAddr = mem->dma_virt;
        stSecMBuf.u32Size = mem->dma_size;
        HI_DRV_MMZ_Unmap(&stSecMBuf);
        HI_DRV_MMZ_Release(&stSecMBuf);
        ret = HI_SUCCESS;
    }
#endif

    crypto_memset(mem, sizeof(crypto_mem), 0, sizeof(crypto_mem));

    return ret;
}

/*brief map a mmz or smmu memory */
static s32 crypto_mem_map(crypto_mem *mem)
{
    HI_LOG_DEBUG("crypto_mem_map()- dma 0x%x, size 0x%x\n",
        ADDR_L32(mem->dma_addr), mem->dma_size);

#ifdef WITH_HI3798MX_PLATFORM
    /* map mmz to cpu */
    mem->dma_virt = (u8*)remap_mmb(ADDR_L32(mem->dma_addr));
    if(HI_NULL == mem->dma_virt)
    {
        return HI_LOG_ERR_MEM;
    }

#elif defined(CRYPTO_SMMU_SUPPORT)
    {
        s32 ret = HI_SUCCESS;
        SMMU_BUFFER_S stSmmuBuf;

        /* map mmu to cpu */
        stSmmuBuf.u32StartSmmuAddr= ADDR_L32(mem->dma_addr);
        stSmmuBuf.u32Size = mem->dma_size;
        ret = HI_DRV_SMMU_Map(&stSmmuBuf);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(HI_DRV_SMMU_Map, ret);
            return ret;
        }
        mem->dma_virt = stSmmuBuf.pu8StartVirAddr;
        HI_LOG_DEBUG("mem_map()- smmu 0x%x, vai 0x%p\n", ADDR_L32(mem->dma_addr), mem->dma_virt);
    }
#else /*MMZ*/
    {
        s32 ret = HI_SUCCESS;
        MMZ_BUFFER_S stMmzBuf;

        /* map mmz to cpu */
        stMmzBuf.u32StartPhyAddr = ADDR_L32(mem->dma_addr);
        stMmzBuf.u32Size = mem->dma_size;
        ret = HI_DRV_MMZ_Map(&stMmzBuf);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(HI_DRV_MMZ_Map, ret);
            return ret;
        }

        mem->dma_virt = stMmzBuf.pu8StartVirAddr;
    }
#endif

    if (HI_NULL == mem->dma_virt)
    {
        HI_LOG_PrintErrCode(HI_LOG_ERR_MEM);
        return HI_LOG_ERR_MEM;
    }

    HI_LOG_INFO("crypto_mem_map()- via 0x%p\n", mem->dma_virt);

    return HI_SUCCESS;

}

/*brief unmap a mmz or smmu memory */
static s32 crypto_mem_unmap(crypto_mem *mem)
{
    HI_LOG_DEBUG("crypto_mem_unmap()- dma 0x%x, size 0x%x\n",
        ADDR_L32(mem->dma_addr), mem->dma_size);

#ifdef WITH_HI3798MX_PLATFORM
    /* umap mmz */
    return unmap_mmb(mem->dma_virt);

#elif defined(CRYPTO_SMMU_SUPPORT)
    {
        SMMU_BUFFER_S stSmmuBuf;

        /* umap smmu */
        stSmmuBuf.u32StartSmmuAddr= ADDR_L32(mem->dma_addr);
        stSmmuBuf.pu8StartVirAddr = mem->dma_virt;
        stSmmuBuf.u32Size = mem->dma_size;
        mem->dma_virt = HI_NULL;
        HI_DRV_SMMU_Unmap(&stSmmuBuf);
    }
#else /*MMZ*/
    {
        MMZ_BUFFER_S stMmzBuf;

        /* umap mmz */
        stMmzBuf.u32StartPhyAddr = ADDR_L32(mem->dma_addr);
        stMmzBuf.pu8StartVirAddr = mem->dma_virt;
        stMmzBuf.u32Size = mem->dma_size;
        mem->dma_virt = HI_NULL;
        HI_DRV_MMZ_Unmap(&stMmzBuf);
    }
#endif
    return HI_SUCCESS;
}

void crypto_mem_init(void)
{

}

void crypto_mem_deinit(void)
{

}

s32 crypto_mem_create(crypto_mem *mem, u32 type, const s8 *name, u32 size)
{
    CRYPTO_ASSERT(HI_NULL != mem);

    return crypto_mem_alloc_remap(mem, type, name, size);
}

s32 crypto_mem_destory(crypto_mem *mem)
{
    CRYPTO_ASSERT(HI_NULL != mem);

    return crypto_mem_release_unmap(mem);
}

s32 crypto_mem_open(crypto_mem *mem, compat_addr dma_addr, u32 dma_size)
{
    CRYPTO_ASSERT(HI_NULL != mem);

    mem->dma_addr = dma_addr;
    mem->dma_size = dma_size;

    if (0 == mem->dma_size)
    {
        return HI_SUCCESS;
    }

    return crypto_mem_map(mem);
}

s32 crypto_mem_close(crypto_mem *mem)
{
    CRYPTO_ASSERT(HI_NULL != mem);

    if (0 == mem->dma_size)
    {
        return HI_SUCCESS;
    }

    return crypto_mem_unmap(mem);
}

s32 crypto_mem_attach(crypto_mem *mem, void *buffer)
{
    CRYPTO_ASSERT(HI_NULL != mem);

    mem->user_buf = buffer;

    return HI_SUCCESS;
}

s32 crypto_mem_flush(crypto_mem *mem, u32 dma2user, u32 offset, u32 data_size)
{
    CRYPTO_ASSERT(HI_NULL != mem);
    CRYPTO_ASSERT(HI_NULL != mem->dma_virt);
    CRYPTO_ASSERT(HI_NULL != mem->user_buf);
    CRYPTO_ASSERT(data_size <= mem->dma_size);

    if (dma2user)
    {
        crypto_memcpy((u8*)mem->user_buf + offset, data_size,
            (u8*)mem->dma_virt + offset, data_size);
    }
    else
    {
        crypto_memcpy((u8*)mem->dma_virt + offset, data_size,
            (u8*)mem->user_buf + offset, data_size);
    }

    return HI_SUCCESS;
}

s32 crypto_mem_phys(crypto_mem *mem, compat_addr *dma_addr)
{
    CRYPTO_ASSERT(HI_NULL != mem);

    dma_addr->phy = ADDR_U64(mem->dma_addr);

    return HI_SUCCESS;
}

void * crypto_mem_virt(crypto_mem *mem)
{
    if (HI_NULL == mem)
    {
        return HI_NULL;
    }

    return mem->dma_virt;
}

s32 crypto_copy_from_user(void *to, const void  *from, unsigned long n)
{
    if (0 == n)
    {
        return HI_SUCCESS;
    }

    HI_LOG_CHECK_PARAM(HI_NULL == to);
    HI_LOG_CHECK_PARAM(HI_NULL == from);

    return copy_from_user(to, from, n);
}

s32 crypto_copy_to_user(void *to, const void  *from, unsigned long n)
{
    if (0 == n)
    {
        return HI_SUCCESS;
    }

    HI_LOG_CHECK_PARAM(HI_NULL == to);
    HI_LOG_CHECK_PARAM(HI_NULL == from);

    return copy_to_user(to, from, n);
}

u32 crypto_is_sec_cpu(void)
{
    return module_get_secure();
}

void smmu_get_table_addr(u64 *rdaddr, u64 *wraddr, u64 *table)
{
#ifdef CRYPTO_SMMU_SUPPORT
    u32 smmu_e_raddr, smmu_e_waddr, mmu_pgtbl;
    HI_DRV_SMMU_GetPageTableAddr(&mmu_pgtbl, &smmu_e_raddr, &smmu_e_waddr);

    *rdaddr = smmu_e_raddr;
    *wraddr = smmu_e_waddr;
    *table = mmu_pgtbl;
#else
    *rdaddr = 0x00;
    *wraddr = 0x00;
    *table  = 0x00;
#endif
}

void crypto_load_symc_clean_key(u32 chn_num, u32 key[AES_IV_SIZE], u32 odd)
{
#ifdef CA_FRAMEWORK_V200_SUPPORT
    s32 ret = HI_FAILURE;
    EXT_CLEAR_CW_KLAD_PARA_S stCfg = {0};
    KLAD_EXPORT_FUNC_S *klad_func = HI_NULL;

    ret = HI_DRV_MODULE_GetFunction(HI_ID_CA, (HI_VOID**)&klad_func);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncWar(HI_DRV_MODULE_GetFunction, ret);
        return;
    }

    if ((HI_NULL == klad_func) || (HI_NULL == klad_func->pSetClearkey))
    {
        HI_LOG_WARN("Get klad function failed, please insert the hi_advca.ko.");
        return;
    }

    HI_LOG_INFO("KLAD Load CPU Key, chn_num %d, odd %d\n", chn_num, odd);

    stCfg.handle   = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, chn_num);
    stCfg.enEngine = HI_UNF_KLAD_TARGET_ENGINE_FIXED;
    stCfg.bOdd     = odd;
    stCfg.enSecEn  = (crypto_is_sec_cpu() ? KLAD_SEC_ENABLE : KLAD_SEC_DISABLE);
    crypto_memcpy(stCfg.u8Key, HI_UNF_KLAD_MAX_KEY_LEN, key, AES_IV_SIZE);
    ret = klad_func->pSetClearkey(&stCfg);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(klad_func->pSetClearkey, ret);
        return;
    }
#endif
    return;
}


/** @}*/  /** <!-- ==== API Code end ====*/
