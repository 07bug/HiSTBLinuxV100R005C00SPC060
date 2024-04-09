/***********************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : hisi_mem_pool.c
Version          : Initial Draft
Author           :
Created          : 2017/10/01
Description      : The user will use this api to realize some function
Function List    :


History           :
Date                      Author                    Modification
2017/10/01                sdk                        Created file
************************************************************************************************/


/****************************  add include here     ********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/***************************** Macro Definition     ********************************************/

/***************************** Structure Definition ********************************************/

/********************** Global Variable declaration ********************************************/

/********************** API forward declarations    ********************************************/

/**********************       API realization       ********************************************/
static DFBResult hisi_mem_open_log(void)
{
    DFBResult ret;
    DirectLogType log_type = DLT_FILE;
    const char *log_param = "/var/dfb.log";

    ret = direct_log_create(log_type, log_param, &dfb_mmz_info.mmz_log);
    if (ret)
    {
      return DFB_FAILURE;
    }

    return DFB_OK;
}

static DFBResult hisi_mem_close_log(void)
{
   if (NULL == dfb_mmz_info.mmz_log)
   {
      return DFB_OK;
   }

   direct_log_destroy(dfb_mmz_info.mmz_log);
   dfb_mmz_info.mmz_log = NULL;

   return DFB_OK;
}


static DFBResult hisi_mem_alloc_pools(void)
{
    int shm_key;
    hisi_mem_share_data *shard_mmz_data = NULL;

    dfb_mmz_info.pool_phy_addr = (void*)HI_MMZ_New(CONFIG_HISI_MEMPOOL_SIZE, 0, NULL, "DFB");
    if (!dfb_mmz_info.pool_phy_addr)
    {
    	D_ERROR("[dfbmmz]HI_MMZ_New Error==%s,%d==\n",__FUNCTION__,__LINE__);
    	return DFB_FAILURE;
    }

    dfb_mmz_info.pool_vir_addr = HI_MMZ_Map((HI_U32)dfb_mmz_info.pool_phy_addr, 0);
    if (!dfb_mmz_info.pool_vir_addr)
    {
    	HI_MMZ_Unmap((HI_U32)dfb_mmz_info.pool_phy_addr);
    	HI_MMZ_Delete((HI_U32)dfb_mmz_info.pool_phy_addr);
    	D_ERROR("[dfbmmz]HI_MMZ_Map Error==%s,%d==\n",__FUNCTION__,__LINE__);
    	return DFB_FAILURE;
    }

    shm_key = ftok("/usr", 0);
    if ((dfb_mmz_info.shmid = shmget(shm_key, sizeof(hisi_mem_share_data) ,IPC_CREAT)) ==-1)
    {
    	D_ERROR("[dfbmmz]shmget error ==%s,%d==\n",__FUNCTION__,__LINE__);
    	HI_MMZ_Unmap((HI_U32)dfb_mmz_info.pool_phy_addr);
    	HI_MMZ_Delete((HI_U32)dfb_mmz_info.pool_phy_addr);
    	return DFB_FAILURE;
    }

    if ((int)(dfb_mmz_info.shmptr = shmat(dfb_mmz_info.shmid,0,0))== -1)
    {
    	D_ERROR("[dfbmmz]shmat error ==%s,%d==\n",__FUNCTION__,__LINE__);
    	HI_MMZ_Unmap((HI_U32)dfb_mmz_info.pool_phy_addr);
    	HI_MMZ_Delete((HI_U32)dfb_mmz_info.pool_phy_addr);
    	return DFB_FAILURE;
    }

    shard_mmz_data = (hisi_mem_share_data*)dfb_mmz_info.shmptr;

    shard_mmz_data->pool_phy_addr = dfb_mmz_info.pool_phy_addr;
    shard_mmz_data->pool_vir_addr = dfb_mmz_info.pool_vir_addr;
    shard_mmz_data->mmz_log       =  dfb_mmz_info.mmz_log;

    return DFB_OK;
}

static DFBResult hisi_mem_free_pools(void)
{
    if (0 == CONFIG_HISI_MEMPOOL_SIZE)
    {
        hisi_mem_close_log();
        return DFB_OK;
	}

	if (shmdt(dfb_mmz_info.shmptr) == -1)
    {
		D_ERROR("[dfbmmz]shmdt error ==%s,%d==\n",__FUNCTION__,__LINE__);
		return DFB_FAILURE;
	}

	if (shmctl(dfb_mmz_info.shmid,IPC_RMID,0) == -1)
    {
		D_ERROR("[dfbmmz]shmctl error ==%s,%d==\n",__FUNCTION__,__LINE__);
		return DFB_FAILURE;
	}

    if (dfb_mmz_info.pool_phy_addr)
    {
		HI_MMZ_Unmap((HI_U32)dfb_mmz_info.pool_phy_addr);
		HI_MMZ_Delete((HI_U32)dfb_mmz_info.pool_phy_addr);
    }

    return DFB_OK;
}


static DFBResult hisi_mem_join_pools(void)
{
    int shm_key;
    hisi_mem_share_data *shard_mmz_data;

    if (0 == CONFIG_HISI_MEMPOOL_SIZE)
    {
        return DFB_OK;
	}

    shm_key= ftok("/usr", 0);
    if ((dfb_mmz_info.shmid = shmget(shm_key,sizeof(hisi_mem_share_data ),IPC_CREAT)) == -1)
    {
        D_ERROR("[dfbmmz]shmget error ==%s,%d==\n",__FUNCTION__,__LINE__);
        return DFB_FAILURE;
    }

    if ((int)(dfb_mmz_info.shmptr = shmat(dfb_mmz_info.shmid,0,0)) == -1)
    {
        D_ERROR("[dfbmmz]shmat error ==%s,%d==\n",__FUNCTION__,__LINE__);
        return DFB_FAILURE;
    }

    shard_mmz_data = (hisi_mem_share_data *)dfb_mmz_info.shmptr;

    if (NULL == shard_mmz_data->pool_phy_addr)
    {
        D_ERROR("[dfbmmz] phy address is zero function:%s line:%d\n",__FUNCTION__,__LINE__);
           return DFB_FAILURE;
    }

    dfb_mmz_info.pool_phy_addr = shard_mmz_data->pool_phy_addr;
    dfb_mmz_info.pool_vir_addr = HI_MMZ_Map((unsigned long)shard_mmz_data->pool_phy_addr,0);
    if (NULL == dfb_mmz_info.pool_vir_addr)
    {
        D_ERROR("[dfbmmz] phy address is zero function:%s line:%d\n",__FUNCTION__,__LINE__);
        return DFB_FAILURE;
    }

    dfb_mmz_info.mmz_log = shard_mmz_data->mmz_log;

    return DFB_OK;
}

static DFBResult hisi_mem_leave_pools(void)
{
    if (0 == CONFIG_HISI_MEMPOOL_SIZE)
    {
       return DFB_OK;
    }

    if (NULL != dfb_mmz_info.pool_phy_addr)
    {
       HI_MMZ_Unmap((HI_U32)dfb_mmz_info.pool_phy_addr);
    }

    if (shmdt(dfb_mmz_info.shmptr) == -1)
    {
        D_ERROR("[dfbmmz]shmdt error ==%s,%d==\n",__FUNCTION__,__LINE__);
        return DFB_FAILURE;
    }

    return DFB_OK;
}


static DFBResult hisi_mem_alloc_buffer(CoreSurfaceBuffer *buffer,
                                      CoreSurfaceAllocation *allocation,
                                      void *alloc_data,
                                      bool use_mem_pool)
{
    void* phys_addr = NULL;
    DFBResult Ret = DFB_OK;
    CoreSurface *surface = buffer->surface;
    FBDevAllocationData *alloc = alloc_data;

    dfb_surface_calc_buffer_size(surface, 8, 1, &alloc->mmz_surface.pitch, &allocation->size);

    phys_addr = (void*)HI_MMZ_New(allocation->size, 0, NULL, "DFB");
	if (NULL == phys_addr)
    {
		D_ERROR("[dfbmmz]HI_MMZ_New Error==%s,%d==\n",__FUNCTION__,__LINE__);
		return DFB_FAILURE;
	}

	alloc->mmz_surface.vir_addr = NULL;
	alloc->mmz_surface.phy_addr = phys_addr;
    alloc->mmz_surface.pool_use_up = use_mem_pool;

    #ifdef CFG_DEBUG_MMZ
	direct_log_printf(dfb_mmz_info.mmz_log, "[dynamic] allocate mem length: %d\n", allocation->size);
    #endif

    return DFB_OK;
}

static DFBResult hisi_mem_free_buffer(void *pool_data, void *alloc_data)
{
     FBDevPoolData *data  = pool_data;
     FBDevAllocationData *alloc = alloc_data;

     if (0 == CONFIG_HISI_MEMPOOL_SIZE)
     {
		if (alloc->mmz_surface.phy_addr)
        {
			HI_MMZ_Delete((HI_U32)alloc->mmz_surface.phy_addr);
            #ifdef CFG_DEBUG_MMZ
			direct_log_printf(dfb_mmz_info.mmz_log, "[dynamic] release mem length: %d\n", allocation->size );
            #endif
		}

        return DFB_OK;
	}

	if (alloc->chunk)
	{
		dfb_surfacemanager_deallocate(data->manager, alloc->chunk);
	}

	if (alloc->mmz_surface.phy_addr)
    {
		HI_MMZ_Delete((HI_U32)alloc->mmz_surface.phy_addr);
        #ifdef CFG_DEBUG_MMZ
		direct_log_printf(dfb_mmz_info.mmz_log, "[dynamic] release mem length: %d\n", allocation->size );
        #endif
	}

    return DFB_OK;
}


static DFBResult hisi_mem_lock_buffer(void *alloc_data, CoreSurfaceBufferLock *lock)
{
    FBDevAllocationData *alloc  = alloc_data;

    if (0 == CONFIG_HISI_MEMPOOL_SIZE)
    {
        lock->pitch  = alloc->mmz_surface.pitch;
        lock->offset = 0;
        lock->phys = (unsigned long) alloc->mmz_surface.phy_addr;
        lock->addr = (void*) HI_MMZ_Map((HI_U32)lock->phys, 0);
        if (lock->addr == NULL)
        {
            return DFB_FAILURE;
        }

        return DFB_OK;
    }

    if (false == alloc->mmz_surface.pool_use_up)
    {
        D_MAGIC_ASSERT( alloc->chunk, Chunk );
        lock->pitch  = alloc->chunk->pitch;
        lock->offset = alloc->chunk->offset;

        lock->phys = (unsigned long)dfb_mmz_info.pool_phy_addr + lock->offset;
        lock->addr = (void*) (unsigned long)dfb_mmz_info.pool_vir_addr + lock->offset;

    }
    else
    {
        lock->pitch  = alloc->mmz_surface.pitch;
        lock->offset = 0;
        lock->addr = (void*)HI_MMZ_Map((HI_U32)alloc->mmz_surface.phy_addr, 0);
        lock->phys = (unsigned long) alloc->mmz_surface.phy_addr;
        if(lock->addr == NULL)
        {
            return DFB_FAILURE;
        }
    }

    return DFB_OK;
}

static void hisi_mem_unlock_buffer(void *alloc_data, CoreSurfaceBufferLock *lock)
{
    FBDevAllocationData *alloc  = alloc_data;

    if (0 == CONFIG_HISI_MEMPOOL_SIZE)
    {
        if (alloc->mmz_surface.phy_addr == lock->phys)
        {
           HI_MMZ_Unmap((HI_U32)lock->phys);
        }

        return;
    }

    if (alloc->mmz_surface.pool_use_up)
    {
        HI_MMZ_Unmap((HI_U32)lock->phys);
    }

    return;
}
