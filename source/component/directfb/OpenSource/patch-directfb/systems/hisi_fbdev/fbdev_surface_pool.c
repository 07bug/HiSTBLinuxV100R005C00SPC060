/*
   (c) Copyright 2012-2013  DirectFB integrated media GmbH
   (c) Copyright 2001-2013  The world wide DirectFB Open Source Community (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Shimokawa <andi@directfb.org>,
              Marek Pikarski <mass@directfb.org>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrj盲l盲 <syrjala@sci.fi> and
              Claudio Ciccani <klan@users.sf.net>.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/



//#define DIRECT_ENABLE_DEBUG

#include <config.h>

#include <direct/debug.h>
#include <direct/mem.h>

#include <core/surface_pool.h>

#include <gfx/convert.h>

#include "fbdev.h"
#include "surfacemanager.h"

extern FBDev *dfb_fbdev;

D_DEBUG_DOMAIN( FBDev_Surfaces, "FBDev/Surfaces", "FBDev Framebuffer Surface Pool" );
D_DEBUG_DOMAIN( FBDev_SurfLock, "FBDev/SurfLock", "FBDev Framebuffer Surface Pool Locks" );

/**********************************************************************************************************************/

typedef struct {
     int             magic;

     SurfaceManager *manager;
} FBDevPoolData;

typedef struct {
     int             magic;

     CoreDFB        *core;
} FBDevPoolLocalData;

typedef struct {
     int    magic;

     Chunk *chunk;
#ifdef CONFIG_HISI_MEM_SUPPORT
     hisi_mem_surface mmz_surface;
#endif
} FBDevAllocationData;


#ifdef CONFIG_HISI_MEM_SUPPORT
#include "hi_common.h"
hisi_mem_dev_info dfb_mmz_info;
#include "hisi_mem_pool.c"
#endif

/**********************************************************************************************************************/

static int
fbdevPoolDataSize( void )
{
     return sizeof(FBDevPoolData);
}

static int
fbdevPoolLocalDataSize( void )
{
     return sizeof(FBDevPoolLocalData);
}

static int
fbdevAllocationDataSize( void )
{
     return sizeof(FBDevAllocationData);
}

static DFBResult
fbdevInitPool( CoreDFB                    *core,
               CoreSurfacePool            *pool,
               void                       *pool_data,
               void                       *pool_local,
               void                       *system_data,
               CoreSurfacePoolDescription *ret_desc )
{
     unsigned long mem_pool_size = 0;
     DFBResult           ret;
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s()\n", __FUNCTION__ );

     D_ASSERT( core != NULL );
     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_ASSERT( data != NULL );
     D_ASSERT( local != NULL );
     D_ASSERT( ret_desc != NULL );

#ifdef CONFIG_HISI_MEM_SUPPORT
 	 hisi_mem_open_log();

 	 if (CONFIG_HISI_MEMPOOL_SIZE)
     {
 		ret = hisi_mem_alloc_pools();
         if (DFB_OK != ret)
         {
             return ret;
         }
 	 }
     mem_pool_size = (0 == (CONFIG_HISI_MEMPOOL_SIZE)) ? dfb_fbdev->shared->fix.smem_len : CONFIG_HISI_MEMPOOL_SIZE;
 #else
     mem_pool_size = dfb_fbdev->shared->fix.smem_len;
#endif

     ret = dfb_surfacemanager_create( core, mem_pool_size, &data->manager );
     if (ret)
          return ret;

     ret_desc->caps              = CSPCAPS_PHYSICAL | CSPCAPS_VIRTUAL;
     ret_desc->access[CSAID_CPU] = CSAF_READ | CSAF_WRITE | CSAF_SHARED;
     ret_desc->access[CSAID_GPU] = CSAF_READ | CSAF_WRITE | CSAF_SHARED;
     ret_desc->types             = CSTF_LAYER | CSTF_WINDOW | CSTF_CURSOR | CSTF_FONT | CSTF_SHARED | CSTF_EXTERNAL;
     ret_desc->priority          = CSPP_DEFAULT;

     /* For hardware layers */
     ret_desc->access[CSAID_LAYER0] = CSAF_READ;
     ret_desc->access[CSAID_LAYER1] = CSAF_READ;
     ret_desc->access[CSAID_LAYER2] = CSAF_READ;
     ret_desc->access[CSAID_LAYER3] = CSAF_READ;
     ret_desc->access[CSAID_LAYER4] = CSAF_READ;
     ret_desc->access[CSAID_LAYER5] = CSAF_READ;
     ret_desc->access[CSAID_LAYER6] = CSAF_READ;
     ret_desc->access[CSAID_LAYER7] = CSAF_READ;
     ret_desc->access[CSAID_LAYER8] = CSAF_READ;
     ret_desc->access[CSAID_LAYER9] = CSAF_READ;
     ret_desc->access[CSAID_LAYER10] = CSAF_READ;
     ret_desc->access[CSAID_LAYER11] = CSAF_READ;
     ret_desc->access[CSAID_LAYER12] = CSAF_READ;
     ret_desc->access[CSAID_LAYER13] = CSAF_READ;
     ret_desc->access[CSAID_LAYER14] = CSAF_READ;
     ret_desc->access[CSAID_LAYER15] = CSAF_READ;

     snprintf( ret_desc->name, DFB_SURFACE_POOL_DESC_NAME_LENGTH, "Frame Buffer Memory" );

     local->core = core;

     D_MAGIC_SET( data, FBDevPoolData );
     D_MAGIC_SET( local, FBDevPoolLocalData );


     D_ASSERT( dfb_fbdev != NULL );
     D_ASSERT( dfb_fbdev->shared != NULL );

     dfb_fbdev->shared->manager = data->manager;

     return DFB_OK;
}

static DFBResult
fbdevJoinPool( CoreDFB                    *core,
               CoreSurfacePool            *pool,
               void                       *pool_data,
               void                       *pool_local,
               void                       *system_data )
{
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s()\n", __FUNCTION__ );

     D_ASSERT( core != NULL );
     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_ASSERT( local != NULL );

     (void) data;

     local->core = core;

     D_MAGIC_SET( local, FBDevPoolLocalData );

#ifndef CONFIG_HISI_MEM_SUPPORT
     return DFB_OK;
#else
    return hisi_mem_join_pools();
#endif
}

static DFBResult
fbdevDestroyPool( CoreSurfacePool *pool,
                  void            *pool_data,
                  void            *pool_local )
{
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s()\n", __FUNCTION__ );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );

     dfb_surfacemanager_destroy( data->manager );

     D_MAGIC_CLEAR( data );
     D_MAGIC_CLEAR( local );
#ifdef CONFIG_HISI_MEM_SUPPORT
     hisi_mem_free_pools();
#endif

#ifdef CFG_DEBUG_MMZ
     hisi_mem_close_log();
#endif

     return DFB_OK;
}

static DFBResult
fbdevLeavePool( CoreSurfacePool *pool,
                void            *pool_data,
                void            *pool_local )
{
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s()\n", __FUNCTION__ );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );

     (void) data;

     D_MAGIC_CLEAR( local );

#ifdef CONFIG_HISI_MEM_SUPPORT
     hisi_mem_leave_pools();
#endif
     return DFB_OK;
}

static DFBResult
fbdevTestConfig( CoreSurfacePool         *pool,
                 void                    *pool_data,
                 void                    *pool_local,
                 CoreSurfaceBuffer       *buffer,
                 const CoreSurfaceConfig *config )
{
     DFBResult           ret;
     CoreSurface        *surface;
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s( %p )\n", __FUNCTION__, buffer );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );

     surface = buffer->surface;
     D_MAGIC_ASSERT( surface, CoreSurface );

     if ((surface->type & CSTF_LAYER) && surface->resource_id == DLID_PRIMARY)
          return DFB_OK;
#ifdef CONFIG_HISI_MEM_SUPPORT
	if (CONFIG_HISI_MEMPOOL_SIZE >= 0)
    {
		return DFB_OK;
	}
#else
     ret = dfb_surfacemanager_allocate( local->core, data->manager, buffer, NULL, NULL );
#endif
     D_DEBUG_AT( FBDev_Surfaces, "  -> %s\n", DirectFBErrorString(ret) );

     return ret;
}

static DFBResult
fbdevAllocateBuffer( CoreSurfacePool       *pool,
                     void                  *pool_data,
                     void                  *pool_local,
                     CoreSurfaceBuffer     *buffer,
                     CoreSurfaceAllocation *allocation,
                     void                  *alloc_data )
{
     DFBResult            ret;
     CoreSurface         *surface;
     FBDevPoolData       *data  = pool_data;
     FBDevPoolLocalData  *local = pool_local;
     FBDevAllocationData *alloc = alloc_data;

     D_DEBUG_AT( FBDev_Surfaces, "%s( %p )\n", __FUNCTION__, buffer );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );

     surface = buffer->surface;
     D_MAGIC_ASSERT( surface, CoreSurface );

     if (surface->type & CSTF_LAYER && surface->resource_id == DLID_PRIMARY) {
          D_DEBUG_AT( FBDev_Surfaces, "  -> primary layer buffer (index %d)\n", dfb_surface_buffer_index( buffer ) );

          dfb_surface_calc_buffer_size( surface, 8, 1, NULL, &allocation->size );
     }
     else
     {
      //HISILICON add begin
      //[TAG]:  allocate mmz memory from pool or  Dynamic allocation
      #ifdef CONFIG_HISI_MEM_SUPPORT
    	if (0 == CONFIG_HISI_MEMPOOL_SIZE)
        {
            ret = hisi_mem_alloc_buffer(buffer,allocation,alloc_data,false);
            if (ret)
            {
               D_ERROR("[dfbmmz]DFB_HISI_AllocBuffer failure function:%s line:%d\n",__FUNCTION__,__LINE__);
    		   return ret;
            }
    	}
        else
        {
            /**<-- get mem from hisi mem pool **/
    		ret = dfb_surfacemanager_allocate( local->core, data->manager, buffer, allocation, &alloc->chunk );
    		if (DFB_OK == ret)
    		{
                allocation->offset = alloc->chunk->offset;
    	        allocation->size   = alloc->chunk->length;
                D_MAGIC_SET( alloc, FBDevAllocationData );
                return DFB_OK;
    		}

           #if 1
            /** user only need video memory, should not malloc sys mem again **/
            D_ERROR("[dfbmmz]dfb_surfacemanager_allocate failure function:%s line:%d\n",__FUNCTION__,__LINE__);
            return ret;
           #else
            /**<-- if mem pool exhaustion, alloc mem again **/
     		ret = hisi_mem_alloc_buffer(buffer,allocation,alloc_data,true);
            if (ret)
            {
               D_ERROR("[dfbmmz]DFB_HISI_AllocBuffer failure function:%s line:%d\n",__FUNCTION__,__LINE__);
    		   return ret;
            }
           #endif
    	}
    #else
    	ret = dfb_surfacemanager_allocate( local->core, data->manager, buffer, allocation, &alloc->chunk );
    	if (ret)
    	{
    		return ret;
    	}

        D_MAGIC_ASSERT( alloc->chunk, Chunk );

    	allocation->offset = alloc->chunk->offset;
    	allocation->size   = alloc->chunk->length;
    #endif
    //HISILICON add end
    }

     D_MAGIC_SET( alloc, FBDevAllocationData );

     return DFB_OK;
}

static DFBResult
fbdevDeallocateBuffer( CoreSurfacePool       *pool,
                       void                  *pool_data,
                       void                  *pool_local,
                       CoreSurfaceBuffer     *buffer,
                       CoreSurfaceAllocation *allocation,
                       void                  *alloc_data )
{
     FBDevPoolData       *data  = pool_data;
     FBDevAllocationData *alloc = alloc_data;

     D_DEBUG_AT( FBDev_Surfaces, "%s( %p )\n", __FUNCTION__, buffer );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( alloc, FBDevAllocationData );
#ifdef CONFIG_HISI_MEM_SUPPORT
	hisi_mem_free_buffer(pool_data,alloc_data);
#else
     if (alloc->chunk)
          dfb_surfacemanager_deallocate( data->manager, alloc->chunk );

#endif
     D_MAGIC_CLEAR( alloc );

     return DFB_OK;
}

static DFBResult
fbdevMuckOut( CoreSurfacePool   *pool,
              void              *pool_data,
              void              *pool_local,
              CoreSurfaceBuffer *buffer )
{
     FBDevPoolData      *data  = pool_data;
     FBDevPoolLocalData *local = pool_local;

     D_DEBUG_AT( FBDev_Surfaces, "%s( %p )\n", __FUNCTION__, buffer );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( data, FBDevPoolData );
     D_MAGIC_ASSERT( local, FBDevPoolLocalData );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );

     return dfb_surfacemanager_displace( local->core, data->manager, buffer );
}


//HISILICON add begin
//tag, support fence sync
#ifdef CONFIG_DFB_SUPPORT_FENCE
static DFBResult sync_wait(int layer_id, int buffer_id)
{
    CoreLayerRegionConfig *config = NULL;

    if (NULL == dfb_fbdev)
    {
       D_WARN("++++++++++++++ dfb_fbdev handle is null\n");
       return DFB_OK;
    }

    if (NULL == dfb_fbdev->shared)
    {
       D_WARN("++++++++++++++ dfb_fbdev->shared is null\n");
       return DFB_OK;
    }

    config = &(dfb_fbdev->shared->config);

    if ((DLBM_UNKNOWN == config->buffermode) || (DLBM_BACKSYSTEM == config->buffermode))
    {
       return DFB_OK;
    }

    dfb_fbdev_fence_sync_wait(-1, layer_id, buffer_id);

    return DFB_OK;
}
#endif
//HISILICON add end


static DFBResult
fbdevLock( CoreSurfacePool       *pool,
           void                  *pool_data,
           void                  *pool_local,
           CoreSurfaceAllocation *allocation,
           void                  *alloc_data,
           CoreSurfaceBufferLock *lock )
{
     FBDevAllocationData *alloc  = alloc_data;
     FBDevShared         *shared = dfb_fbdev->shared;
//HISILICON add begin
//tag, support fence sync
#ifdef CONFIG_DFB_SUPPORT_FENCE
     int buffer_num = 0;
     int free_buffer_id = -1;
#endif
//HISILICON add end

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( allocation, CoreSurfaceAllocation );
     D_MAGIC_ASSERT( alloc, FBDevAllocationData );
     D_MAGIC_ASSERT( lock, CoreSurfaceBufferLock );

     D_DEBUG_AT( FBDev_SurfLock, "%s( %p )\n", __FUNCTION__, lock->buffer );

     if (allocation->type & CSTF_LAYER && allocation->resource_id == DLID_PRIMARY) {
          int index = allocation->index;

          D_DEBUG_AT( FBDev_Surfaces, "  -> primary layer buffer (index %d)\n", index );
//HISILICON add begin
//tag, support fence sync
#ifdef CONFIG_DFB_SUPPORT_FENCE
          dfb_fbdev_quene_buffnum(0,&buffer_num);
        #ifdef CONFIG_DFB_DISCARD_FRAME
        /** 实际意义上的丢帧，也就是释放该帧的fence **/
          if (index < buffer_num)
          {/** 如果当前的要获取的buffer是显存buffer,则判断是否需要释放空闲buffer **/
              while (-1 == free_buffer_id)
              {
                 dfb_fbdev_quene_free_buffer_id(0, &free_buffer_id);
              }
              index = free_buffer_id;
          }
          if (index == free_buffer_id)
        #else
          if (index < buffer_num)
        #endif
        {
           sync_wait(0,free_buffer_id);
        }
#endif
//HISILICON add end

          lock->pitch  = shared->fix.line_length;
          lock->offset = index * allocation->config.size.h * lock->pitch;

          #if D_DEBUG_ENABLED
          allocation->offset = lock->offset;
          #endif

          lock->addr = dfb_fbdev->framebuffer_base + lock->offset;
          lock->phys = dfb_fbdev->shared->fix.smem_start + lock->offset;
     }
#ifdef CONFIG_HISI_MEM_SUPPORT
     else
     {
     	hisi_mem_lock_buffer(alloc_data, lock);
     }
#else
     else
     {
    	D_MAGIC_ASSERT( alloc->chunk, Chunk );
    	lock->pitch  = alloc->chunk->pitch;
    	lock->offset = alloc->chunk->offset;
	 }

     lock->addr = dfb_fbdev->framebuffer_base + lock->offset;
     lock->phys = dfb_fbdev->shared->fix.smem_start + lock->offset;
#endif

     D_DEBUG_AT( FBDev_SurfLock, "  -> offset %lu, pitch %d, addr %p, phys 0x%08lx\n",
                 lock->offset, lock->pitch, lock->addr, lock->phys );

     return DFB_OK;
}

static DFBResult
fbdevUnlock( CoreSurfacePool       *pool,
             void                  *pool_data,
             void                  *pool_local,
             CoreSurfaceAllocation *allocation,
             void                  *alloc_data,
             CoreSurfaceBufferLock *lock )
{
     FBDevAllocationData *alloc = alloc_data;

     D_MAGIC_ASSERT( pool, CoreSurfacePool );
     D_MAGIC_ASSERT( allocation, CoreSurfaceAllocation );
     D_MAGIC_ASSERT( alloc, FBDevAllocationData );
     D_MAGIC_ASSERT( lock, CoreSurfaceBufferLock );

     D_DEBUG_AT( FBDev_SurfLock, "%s( %p )\n", __FUNCTION__, lock->buffer );

#ifdef CONFIG_HISI_MEM_SUPPORT
     hisi_mem_unlock_buffer(alloc_data, lock);
#endif

     (void) alloc;

     return DFB_OK;
}

const SurfacePoolFuncs fbdevSurfacePoolFuncs = {
     .PoolDataSize       = fbdevPoolDataSize,
     .PoolLocalDataSize  = fbdevPoolLocalDataSize,
     .AllocationDataSize = fbdevAllocationDataSize,

     .InitPool           = fbdevInitPool,
     .JoinPool           = fbdevJoinPool,
     .DestroyPool        = fbdevDestroyPool,
     .LeavePool          = fbdevLeavePool,

     .TestConfig         = fbdevTestConfig,
     .AllocateBuffer     = fbdevAllocateBuffer,
     .DeallocateBuffer   = fbdevDeallocateBuffer,

     .MuckOut            = fbdevMuckOut,

     .Lock               = fbdevLock,
     .Unlock             = fbdevUnlock,
};

