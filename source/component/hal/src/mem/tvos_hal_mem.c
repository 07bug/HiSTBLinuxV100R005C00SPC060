#define LOG_TAG "hal_mem"
//#define LOG_NDEBUG 0
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#include "tvos_hal_errno.h"
#include "tvos_hal_common.h"
#include "tvos_hal_mem.h"
#include "hi_common.h"
#include "mpi_mmz.h"

/***************************** Macro Definition ************************/

#define MEM_HEADER_VERSION       (1)
#define MEM_DEVICE_API_VERSION_1_0 HARDWARE_DEVICE_API_VERSION_2(1, 0, MEM_HEADER_VERSION)

#ifndef __unused
#define __unused
#endif

#define DEBUG_V
#ifdef  DEBUG_V
#define trace()  HAL_DEBUG("%s called", __func__)
#define dbg      HAL_DEBUG
#else
#define trace()
#define dbg(fmt, ...)
#endif

#define MEM_LOG_ERROR       HAL_ERROR
#define MEM_LOG_INFO        HAL_ERROR
#define MEM_MALLOC          malloc
#define MEM_FREE            free

#define MEM_TYPE_NORMAL      0
#define MEM_TYPE_SECURE      1

typedef struct
{
    HI_U32   phyaddr;   /**<Physical address of an MMZ buffer*/
    HI_VOID *viraddr;   /**<Virtual address of an MMZ buffer*/
    E_MEM_USAGE eUsage; /**<Indicate to alloc mem from the non-secure or secure memory*/
    HI_U32   bufsize;   /**<Size of an MMZ buffer*/
}MEM_INFO_S;

#define HAL_MEM_CHK_PARA( val  ) \
    do                                                      \
    {                                                       \
        if (val)                                            \
        {                                                   \
            MEM_LOG_ERROR("Invalid Param");                 \
            return ERROR_INVALID_PARAM;                     \
        };                                                  \
    } while (0)


S32 tvos_mem_alloc(struct _MEM_DEVICE_S* pstDev,
              IN E_MEM_USAGE eUsage,
              IN S32 u32Size,
              IN CHAR * pszName,
              OUT MEM_HANDLE* hHandle)
{
    MEM_INFO_S *mem = HI_NULL;
#if defined(HI_SMMU_SUPPORT) && defined(HI_TEE_SUPPORT)
    HI_S32 ret = FAILURE;
    HI_MPI_SMMU_SEC_ATTR_S SecAttr;
    HI_MPI_SMMU_SEC_BUF_S  SecBuf;
#endif

    HAL_DEBUG_ENTER();

    HAL_MEM_CHK_PARA(HI_NULL == pstDev);
    HAL_MEM_CHK_PARA(HI_NULL == pszName);
    HAL_MEM_CHK_PARA(HI_NULL == hHandle);
    HAL_MEM_CHK_PARA(E_MEM_USEAGE_VES_BUT <= eUsage);

    mem = (MEM_INFO_S *)MEM_MALLOC(sizeof(MEM_INFO_S));
    if (HI_NULL == mem)
    {
       MEM_LOG_ERROR("mem malloc handle failed\n");
       return ERROR_NO_MEMORY;
    }
    memset(mem, 0, sizeof(MEM_INFO_S));

    mem->eUsage  = eUsage;
    mem->bufsize = u32Size;

    if (E_MEM_USEAGE_VES == eUsage)
    {
        mem->phyaddr = (HI_U32)HI_MMZ_New(u32Size, 0, NULL, pszName);
        if (0 == mem->phyaddr)
        {
            MEM_LOG_ERROR("New phyaddr failed!\n");
            MEM_FREE(mem);
            mem = HI_NULL;
            return ERROR_NO_MEMORY;
        }
    }
    else
    {
#if defined(HI_SMMU_SUPPORT) && defined(HI_TEE_SUPPORT)
        strncpy(SecAttr.bufname, pszName, sizeof(SecAttr.bufname));
        SecAttr.bufsize  = u32Size;
        SecBuf.smmu_size = u32Size;
        ret = HI_MPI_SMMU_SecMemAlloc(&SecAttr, &SecBuf);
        if (HI_SUCCESS != ret)
        {
            MEM_LOG_ERROR("New secure phyaddr failed!\n");
            MEM_FREE(mem);
            return ERROR_NO_MEMORY;
        }
        mem->phyaddr = SecBuf.smmu_addr;
#else
        MEM_LOG_ERROR("Can't malloc secure Physical address\n");
        MEM_FREE(mem);
        return ERROR_NOT_SUPPORTED;
#endif
    }

    *hHandle = (MEM_HANDLE)mem;

    HAL_DEBUG_EXIT();
    return SUCCESS;
}

S32 tvos_mem_free(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle)
{
    HI_S32 ret = FAILURE;
    MEM_INFO_S *mem = HI_NULL;
#if defined(HI_SMMU_SUPPORT) && defined(HI_TEE_SUPPORT)
    HI_MPI_SMMU_SEC_BUF_S  SecBuf;
#endif

    HAL_DEBUG_ENTER();

    HAL_MEM_CHK_PARA(HI_NULL == pstDev);
    HAL_MEM_CHK_PARA(INVALID_MEM_HANDLE == hHandle);

    mem = (MEM_INFO_S *)hHandle;

    if (E_MEM_USEAGE_VES == mem->eUsage)
    {
        ret = HI_MMZ_Delete(mem->phyaddr);
        if (HI_SUCCESS != ret)
        {
            MEM_LOG_ERROR("Delete phyaddr failed!\n");
            MEM_FREE(mem);
            return ERROR_INVALID_PARAM;
        }
    }
    else
    {
#if defined(HI_SMMU_SUPPORT) && defined(HI_TEE_SUPPORT)
        SecBuf.smmu_addr = mem->phyaddr;
        SecBuf.smmu_size = mem->bufsize;
        ret = HI_MPI_SMMU_SecMemFree(&SecBuf);
        if (HI_SUCCESS != ret)
        {
            MEM_LOG_ERROR("Delete secure phyaddr failed!\n");
            MEM_FREE(mem);
            return ERROR_INVALID_PARAM;
        }
#else
        MEM_LOG_ERROR("Can't free secure Physical address\n");
        MEM_FREE(mem);
        return ERROR_NOT_SUPPORTED;
#endif
    }

    MEM_FREE(mem);
    mem = HI_NULL;

    HAL_DEBUG_EXIT();
    return SUCCESS;
}

S32 tvos_mem_phy_addr(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle, OUT void** ppvPhyAddr)
{
    MEM_INFO_S *mem = HI_NULL;

    HAL_DEBUG_ENTER();

    HAL_MEM_CHK_PARA(HI_NULL == pstDev);
    HAL_MEM_CHK_PARA(INVALID_MEM_HANDLE == hHandle);
    HAL_MEM_CHK_PARA(HI_NULL == ppvPhyAddr);

    mem = (MEM_INFO_S *)hHandle;
    *ppvPhyAddr = (void*)mem->phyaddr;

    HAL_DEBUG_EXIT();
    return SUCCESS;
}

S32 tvos_mem_map(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle, OUT void** ppvVirAddr)
{
    MEM_INFO_S *mem = HI_NULL;

    HAL_DEBUG_ENTER();

    HAL_MEM_CHK_PARA(HI_NULL == pstDev);
    HAL_MEM_CHK_PARA(HI_NULL == hHandle);
    HAL_MEM_CHK_PARA(HI_NULL == ppvVirAddr);

    mem = (MEM_INFO_S *)hHandle;

    if (E_MEM_USEAGE_VES == mem->eUsage)
    {
        *ppvVirAddr = HI_MMZ_Map(mem->phyaddr, HI_TRUE);
        if (HI_NULL == *ppvVirAddr)
        {
            MEM_LOG_ERROR("Map phyaddr 0x%x failed!\n", mem->phyaddr);
            return ERROR_INVALID_PARAM;
        }
    }
    else
    {
        MEM_LOG_ERROR("Can't map secure Physical address\n");
        return ERROR_NOT_SUPPORTED;
    }

    HAL_DEBUG_EXIT();
    return SUCCESS;
}

S32 tvos_mem_unmap(struct _MEM_DEVICE_S* pstDev,IN MEM_HANDLE hHandle)
{
    HI_S32 ret = FAILURE;
    MEM_INFO_S *mem = HI_NULL;

    HAL_DEBUG_ENTER();

    HAL_MEM_CHK_PARA(HI_NULL == pstDev);
    HAL_MEM_CHK_PARA(INVALID_MEM_HANDLE == hHandle);

    mem = (MEM_INFO_S *)hHandle;

    if (E_MEM_USEAGE_VES == mem->eUsage)
    {
        ret = HI_MMZ_Unmap(mem->phyaddr);
        if (HI_SUCCESS != ret)
        {
            MEM_LOG_ERROR("Unmap phyaddr failed!\n");
            return ERROR_INVALID_PARAM;
        }
    }
    else
    {
        MEM_LOG_ERROR("Can't unmap secure Physical address\n");
        return ERROR_NOT_SUPPORTED;
    }

    HAL_DEBUG_EXIT();
    return SUCCESS;
}

S32 tvos_mem_flush(struct _MEM_DEVICE_S* pstDev, IN MEM_HANDLE hHandle)
{
    HI_S32 ret = FAILURE;
    MEM_INFO_S *mem = HI_NULL;

    HAL_DEBUG_ENTER();

    HAL_MEM_CHK_PARA(HI_NULL == pstDev);
    HAL_MEM_CHK_PARA(INVALID_MEM_HANDLE == hHandle);

    mem = (MEM_INFO_S *)hHandle;

    if (E_MEM_USEAGE_VES == mem->eUsage)
    {
        ret = HI_MMZ_Flush(mem->phyaddr);
        if (HI_SUCCESS != ret)
        {
            MEM_LOG_ERROR("Flush phyaddr failed!\n");
            return ERROR_INVALID_PARAM;
        }
    }
    else
    {
        MEM_LOG_ERROR("Can't Flush secure Physical address\n");
        return ERROR_NOT_SUPPORTED;
    }

    HAL_DEBUG_EXIT();
    return SUCCESS;
}

#ifdef ANDROID_HAL_MODULE_USED
static int tvos_mem_close(hw_device_t *device)
{
    HI_S32 ret = FAILURE;

    ret = HI_SYS_DeInit();
    if (HI_SUCCESS != ret)
    {
        MEM_LOG_ERROR("system deinit failed!\n");
        return ERROR_SYSTEM_DEINIT_FAILED;
    }

    if(HI_NULL != device)
    {
        MEM_FREE(device);
        device = HI_NULL;
    }

    return SUCCESS;
}

static int tvos_mem_open(const struct hw_module_t* module, const char* name,
                           struct hw_device_t** device)
{
    HI_S32 ret = FAILURE;
    MEM_DEVICE_S *pstDev = HI_NULL;

    if (strcmp(name, MEM_HARDWARE_MEM0) != 0)
        return -EINVAL;

    if (HI_NULL == device)
    {
        return -EINVAL;
    }

    ret = HI_SYS_Init();
    if (HI_SUCCESS != ret)
    {
        MEM_LOG_ERROR("system init failed!\n");
        return ERROR_SYSTEM_INIT_FAILED;
    }

    pstDev = (MEM_DEVICE_S *)MEM_MALLOC(sizeof(MEM_DEVICE_S));
    if (HI_NULL == pstDev)
        return -ENOMEM;

    memset(pstDev, 0, sizeof(struct _MEM_DEVICE_S));

    pstDev->stCommon.tag     = HARDWARE_DEVICE_TAG;
    pstDev->stCommon.version = MEM_DEVICE_API_VERSION_1_0;
    pstDev->stCommon.module  = (hw_module_t*)module;
    pstDev->stCommon.close   = tvos_mem_close;

    pstDev->mem_alloc       = tvos_mem_alloc;
    pstDev->mem_free        = tvos_mem_free;
    pstDev->mem_phy_addr    = tvos_mem_phy_addr;
    pstDev->mem_map         = tvos_mem_map;
    pstDev->mem_unmap       = tvos_mem_unmap;
    pstDev->mem_flush       = tvos_mem_flush;

    pstDev->mem_alloc_video_frame = HI_NULL;
    pstDev->mem_free_video_frame  = HI_NULL;

    *device = &(pstDev->stCommon);

    return SUCCESS;
}

static struct hw_module_methods_t hal_module_methods = {
    .open = tvos_mem_open,
};

MEM_MODULE_S HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = 1,
        .id = MEM_HARDWARE_MODULE_ID,
        .name = "Hisi mem",
        .author = "His mem",
        .methods = &hal_module_methods,
    },
};
#endif

static MEM_DEVICE_S s_stMemDev=
{
    /* register the callbacks */
    .mem_alloc       = tvos_mem_alloc,
    .mem_free        = tvos_mem_free,
    .mem_phy_addr    = tvos_mem_phy_addr,
    .mem_map         = tvos_mem_map,
    .mem_unmap       = tvos_mem_unmap,
    .mem_flush       = tvos_mem_flush,

    .mem_alloc_video_frame = HI_NULL,
    .mem_free_video_frame  = HI_NULL,
};

MEM_DEVICE_S* getMemDevice(void)
{
    return &s_stMemDev;
}

