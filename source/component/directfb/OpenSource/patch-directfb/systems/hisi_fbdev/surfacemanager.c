/*
   (c) Copyright 2012-2013  DirectFB integrated media GmbH
   (c) Copyright 2001-2013  The world wide DirectFB Open Source Community (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Shimokawa <andi@directfb.org>,
              Marek Pikarski <mass@directfb.org>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrjälä <syrjala@sci.fi> and
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



#include <config.h>

#include <fusion/shmalloc.h>

#include <directfb.h>
#include <directfb_util.h>

#include <core/core.h>

#include <core/gfxcard.h>
#include <core/surface.h>
#include <core/surface_buffer.h>

#include <direct/debug.h>
#include <direct/messages.h>
#include <direct/util.h>

#include <gfx/convert.h>

#include "surfacemanager.h"

#ifdef CONFIG_HISI_MEM_SUPPORT
extern hisi_mem_dev_info dfb_mmz_info;
#include "hisi_mem_manager.c"
#endif

D_DEBUG_DOMAIN( SurfMan, "SurfaceManager", "DirectFB Surface Manager" );


static Chunk *split_chunk ( SurfaceManager *manager,
                            Chunk          *chunk,
                            int             length );

static Chunk *free_chunk  ( SurfaceManager *manager,
                            Chunk          *chunk );

static Chunk *occupy_chunk( SurfaceManager        *manager,
                            Chunk                 *chunk,
                            CoreSurfaceAllocation *allocation,
                            int                    length,
                            int                    pitch );


DFBResult
dfb_surfacemanager_create( CoreDFB         *core,
                           unsigned int     length,
                           SurfaceManager **ret_manager )
{
     FusionSHMPoolShared *pool;
     SurfaceManager      *manager;
     Chunk               *chunk;

     D_DEBUG_AT( SurfMan, "%s( %p, %d )\n", __FUNCTION__, core, length );

     D_ASSERT( core != NULL );
     D_ASSERT( ret_manager != NULL );

     pool = dfb_core_shmpool( core );

     manager = SHCALLOC( pool, 1, sizeof(SurfaceManager) );
     if (!manager)
          return D_OOSHM();

     chunk = SHCALLOC( pool, 1, sizeof(Chunk) );
     if (!chunk) {
          D_OOSHM();
          SHFREE( pool, manager );
          return DFB_NOSHAREDMEMORY;
     }

     manager->shmpool = pool;
     manager->chunks  = chunk;
     manager->offset  = 0;
     manager->length  = length;
     manager->avail   = manager->length - manager->offset;

     D_MAGIC_SET( manager, SurfaceManager );

     chunk->offset    = manager->offset;
     chunk->length    = manager->avail;

     D_MAGIC_SET( chunk, Chunk );

     D_DEBUG_AT( SurfMan, "  -> %p\n", manager );

     *ret_manager = manager;

     return DFB_OK;
}

void
dfb_surfacemanager_destroy( SurfaceManager *manager )
{
     Chunk *chunk;
     void  *next;

     D_DEBUG_AT( SurfMan, "%s( %p )\n", __FUNCTION__, manager );

     D_MAGIC_ASSERT( manager, SurfaceManager );

     /* Deallocate all video chunks. */
     chunk = manager->chunks;
     while (chunk) {
          next = chunk->next;

          D_MAGIC_CLEAR( chunk );

          SHFREE( manager->shmpool, chunk );

          chunk = next;
     }

     D_MAGIC_CLEAR( manager );

     /* Deallocate manager struct. */
     SHFREE( manager->shmpool, manager );
}

DFBResult dfb_surfacemanager_adjust_heap_offset( SurfaceManager *manager,
                                                 int             offset )
{
     D_MAGIC_ASSERT( manager, SurfaceManager );
     D_ASSERT( offset >= 0 );

     D_DEBUG_AT( SurfMan, "%s( %p, %d )\n", __FUNCTION__, manager, offset );

/*FIXME_SC_2     if (manager->limits.surface_byteoffset_alignment > 1) {
          offset += manager->limits.surface_byteoffset_alignment - 1;
          offset -= offset % manager->limits.surface_byteoffset_alignment;
     }
*/
     /*
      * Adjust the offset of the heap.
      */
#ifdef CONFIG_HISI_MEM_SUPPORT
     return DFB_OK;
#endif
     if (manager->chunks->buffer == NULL) {
          /* first chunk is free */
          if (offset <= manager->chunks->offset + manager->chunks->length) {
               /* ok, just recalculate offset and length */
               manager->chunks->length = manager->chunks->offset +
                                         manager->chunks->length - offset;
               manager->chunks->offset = offset;
          }
          else {
               D_WARN("unable to adjust heap offset");
               /* more space needed than free at the beginning */
               /* TODO: move/destroy instances */
          }
     }
     else {
          D_WARN("unable to adjust heap offset");
          /* very rare case that the first chunk is occupied */
          /* TODO: move/destroy instances */
     }

     manager->avail -= offset - manager->offset;
     manager->offset = offset;

     return DFB_OK;
}

/** public functions NOT locking the surfacemanger theirself,
    to be called between lock/unlock of surfacemanager **/

DFBResult dfb_surfacemanager_allocate( CoreDFB                *core,
                                       SurfaceManager         *manager,
                                       CoreSurfaceBuffer      *buffer,
                                       CoreSurfaceAllocation  *allocation,
                                       Chunk                 **ret_chunk )
{
     int pitch;
     int length;
     Chunk *c;
     CoreGraphicsDevice *device;

     Chunk *best_free = NULL;

     D_MAGIC_ASSERT( manager, SurfaceManager );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );
     D_MAGIC_ASSERT( buffer->surface, CoreSurface );

     if (ret_chunk)
          D_MAGIC_ASSERT( allocation, CoreSurfaceAllocation );
     else
          D_ASSUME( allocation == NULL );

     D_DEBUG_AT( SurfMan, "%s( %p ) <- %dx%d %s\n", __FUNCTION__, buffer,
                 buffer->surface->config.size.w, buffer->surface->config.size.h,
                 dfb_pixelformat_name( buffer->surface->config.format ) );

     if (manager->suspended)
          return DFB_SUSPENDED;

     /* FIXME: Only one global device at the moment. */
     device = dfb_core_get_part( core, DFCP_GRAPHICS );
     D_ASSERT( device != NULL );

     dfb_gfxcard_calc_buffer_size( device, buffer, &pitch, &length );

     D_DEBUG_AT( SurfMan, "  -> pitch %d, length %d, available %d\n", pitch, length, manager->avail );

#ifdef CONFIG_HISI_MEM_SUPPORT
     hisi_mem_manager_log(manager);
#endif

     if (manager->avail < length)
          return DFB_TEMPUNAVAIL;

     /* examine chunks */
     c = manager->chunks;
     D_MAGIC_ASSERT( c, Chunk );

#ifndef CONFIG_HISI_MEM_SUPPORT
     /* FIXME_SC_2  Workaround creation happening before graphics driver initialization. */
     if (!c->next) {
          int length = dfb_gfxcard_memory_length();

          if (c->length != length - manager->offset) {
               D_WARN( "workaround" );

               manager->length = length;
               manager->avail  = length - manager->offset;

               c->length = length - manager->offset;
          }
     }
#endif
     while (c) {
          D_MAGIC_ASSERT( c, Chunk );

          if (!c->buffer && c->length >= length) {
               /* NULL means check only. */
               if (!ret_chunk)
                    return DFB_OK;

               /* found a nice place to chill */
               if (!best_free  ||  best_free->length > c->length)
                    /* first found or better one? */
                    best_free = c;

               if (c->length == length)
                    break;
          }

          c = c->next;
     }

     /* if we found a place */
     if (best_free) {
          D_DEBUG_AT( SurfMan, "  -> found free (%d)\n", best_free->length );

          /* NULL means check only. */
          if (ret_chunk)
               *ret_chunk = occupy_chunk( manager, best_free, allocation, length, pitch );

          return DFB_OK;
     }

     D_DEBUG_AT( SurfMan, "  -> failed (%d/%d avail)\n", manager->avail, manager->length );

     /* no luck */
     return DFB_NOVIDEOMEMORY;
}

DFBResult dfb_surfacemanager_displace( CoreDFB           *core,
                                       SurfaceManager    *manager,
                                       CoreSurfaceBuffer *buffer )
{
     int                    length;
     Chunk                 *multi_start = NULL;
     int                    multi_size  = 0;
     int                    multi_tsize = 0;
     int                    multi_count = 0;
     Chunk                 *bestm_start = NULL;
     int                    bestm_count = 0;
     int                    bestm_size  = 0;
     int                    min_toleration;
     Chunk                 *chunk;
     CoreGraphicsDevice    *device;
     CoreSurfaceAllocation *smallest = NULL;

     D_MAGIC_ASSERT( manager, SurfaceManager );
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );
     D_MAGIC_ASSERT( buffer->surface, CoreSurface );

     D_DEBUG_AT( SurfMan, "%s( %p ) <- %dx%d %s\n", __FUNCTION__, buffer,
                 buffer->surface->config.size.w, buffer->surface->config.size.h,
                 dfb_pixelformat_name( buffer->surface->config.format ) );

     /* FIXME: Only one global device at the moment. */
     device = dfb_core_get_part( core, DFCP_GRAPHICS );
     D_ASSERT( device != NULL );
     D_UNUSED_P( device );

     dfb_gfxcard_calc_buffer_size( dfb_core_get_part( core, DFCP_GRAPHICS ), buffer, NULL, &length );

     min_toleration = manager->min_toleration/8 + 2;

     D_DEBUG_AT( SurfMan, "  -> %7d required, min toleration %d\n", length, min_toleration );

     chunk = manager->chunks;
     while (chunk) {
          CoreSurfaceAllocation *allocation;

          D_MAGIC_ASSERT( chunk, Chunk );

          allocation = chunk->allocation;
          if (allocation) {
               CoreSurfaceBuffer *other;
               int                size, locks;

               D_MAGIC_ASSERT( allocation, CoreSurfaceAllocation );
               D_ASSERT( chunk->buffer == allocation->buffer );
               D_ASSERT( chunk->length >= allocation->size );

               other = allocation->buffer;
               D_MAGIC_ASSERT( other, CoreSurfaceBuffer );

               locks = dfb_surface_allocation_locks( allocation );
               if (locks) {
                    D_DEBUG_AT( SurfMan, "  ++ %7d locked %dx\n", allocation->size, locks );
                    goto next_reset;
               }

               if (other->policy > buffer->policy) {
                    D_DEBUG_AT( SurfMan, "  ++ %7d policy %d > %d\n", allocation->size, other->policy, buffer->policy );
                    goto next_reset;
               }

               if (other->policy == CSP_VIDEOONLY) {
                    D_DEBUG_AT( SurfMan, "  ++ %7d policy videoonly\n", allocation->size );
                    goto next_reset;
               }

               chunk->tolerations++;
               if (chunk->tolerations > 0xff)
                    chunk->tolerations = 0xff;

               if (other->policy == buffer->policy && chunk->tolerations < min_toleration) {
                    D_DEBUG_AT( SurfMan, "  ++ %7d tolerations %d/%d\n",
                                allocation->size, chunk->tolerations, min_toleration );
                    goto next_reset;
               }

               size = allocation->size;

               if (chunk->prev && !chunk->prev->allocation)
                    size += chunk->prev->length;

               if (chunk->next && !chunk->next->allocation)
                    size += chunk->next->length;

               if (size >= length) {
                    if (!smallest || smallest->size > allocation->size) {
                         D_DEBUG_AT( SurfMan, "  => %7d [%d] < %d, tolerations %d\n",
                                     allocation->size, size, smallest ? smallest->size : 0, chunk->tolerations );

                         smallest = allocation;
                    }
                    else
                         D_DEBUG_AT( SurfMan, "  -> %7d [%d] > %d\n", allocation->size, size, smallest->size );
               }
               else
                    D_DEBUG_AT( SurfMan, "  -> %7d [%d]\n", allocation->size, size );
          }
          else
               D_DEBUG_AT( SurfMan, "  -  %7d free\n", chunk->length );


          if (!smallest) {
               if (!multi_start) {
                    multi_start = chunk;
                    multi_tsize = chunk->length;
                    multi_size  = chunk->allocation ? chunk->length : 0;
                    multi_count = chunk->allocation ? 1 : 0;
               }
               else {
                    multi_tsize += chunk->length;
                    multi_size  += chunk->allocation ? chunk->length : 0;
                    multi_count += chunk->allocation ? 1 : 0;

                    while (multi_tsize >= length && multi_count > 1) {
                         if (!bestm_start || bestm_size > multi_size * multi_count / bestm_count) {
                              D_DEBUG_AT( SurfMan, "                =====> %7d, %7d %2d used [%7d %2d]\n",
                                          multi_tsize, multi_size, multi_count, bestm_size, bestm_count );

                              bestm_size  = multi_size;
                              bestm_start = multi_start;
                              bestm_count = multi_count;
                         }
                         else
                              D_DEBUG_AT( SurfMan, "                -----> %7d, %7d %2d used\n",
                                          multi_tsize, multi_size, multi_count );

                         if (multi_count <= 2)
                              break;

                         if (!multi_start->allocation) {
                              multi_tsize -= multi_start->length;
                              multi_start  = multi_start->next;
                         }

                         D_ASSUME( multi_start->allocation != NULL );

                         multi_tsize -= multi_start->length;
                         multi_size  -= multi_start->allocation ? multi_start->length : 0;
                         multi_count -= multi_start->allocation ? 1 : 0;
                         multi_start  = multi_start->next;
                    }
               }
          }

          chunk = chunk->next;

          continue;


next_reset:
          multi_start = NULL;

          chunk = chunk->next;
     }

     if (smallest) {
          D_MAGIC_ASSERT( smallest, CoreSurfaceAllocation );
          D_MAGIC_ASSERT( smallest->buffer, CoreSurfaceBuffer );

          smallest->flags |= CSALF_MUCKOUT;

          D_DEBUG_AT( SurfMan, "  -> offset %lu, size %d\n", smallest->offset, smallest->size );

          return DFB_OK;
     }

     if (bestm_start) {
          chunk = bestm_start;

          while (bestm_count) {
               CoreSurfaceAllocation *allocation = chunk->allocation;

               if (allocation) {
                    D_MAGIC_ASSERT( allocation, CoreSurfaceAllocation );
                    D_MAGIC_ASSERT( allocation->buffer, CoreSurfaceBuffer );

                    allocation->flags |= CSALF_MUCKOUT;

                    bestm_count--;
               }

               D_DEBUG_AT( SurfMan, "  ---> offset %d, length %d\n", chunk->offset, chunk->length );

               chunk = chunk->next;
          }

          return DFB_OK;
     }

     return DFB_NOVIDEOMEMORY;
}

DFBResult dfb_surfacemanager_deallocate( SurfaceManager *manager,
                                         Chunk          *chunk )
{
     CoreSurfaceBuffer *buffer;

     D_MAGIC_ASSERT( manager, SurfaceManager );
     D_MAGIC_ASSERT( chunk, Chunk );

     buffer = chunk->buffer;
     D_MAGIC_ASSERT( buffer, CoreSurfaceBuffer );
     D_MAGIC_ASSERT( buffer->surface, CoreSurface );
     D_UNUSED_P( buffer );

     D_DEBUG_AT( SurfMan, "%s( %p ) <- %dx%d %s\n", __FUNCTION__, buffer,
                 buffer->surface->config.size.w, buffer->surface->config.size.h,
                 dfb_pixelformat_name( buffer->surface->config.format ) );

     free_chunk( manager, chunk );

     return DFB_OK;
}

/** internal functions NOT locking the surfacemanager **/

static Chunk *
split_chunk( SurfaceManager *manager, Chunk *c, int length )
{
     Chunk *newchunk;

     D_MAGIC_ASSERT( c, Chunk );

     if (c->length == length)          /* does not need be splitted */
          return c;

     newchunk = (Chunk*) SHCALLOC( manager->shmpool, 1, sizeof(Chunk) );
     if (!newchunk) {
          D_OOSHM();
          return NULL;
     }

     /* calculate offsets and lengths of resulting chunks */
     newchunk->offset = c->offset + c->length - length;
     newchunk->length = length;
     c->length -= newchunk->length;

     /* insert newchunk after chunk c */
     newchunk->prev = c;
     newchunk->next = c->next;
     if (c->next)
          c->next->prev = newchunk;
     c->next = newchunk;

     D_MAGIC_SET( newchunk, Chunk );

     return newchunk;
}

static Chunk *
free_chunk( SurfaceManager *manager, Chunk *chunk )
{
     D_MAGIC_ASSERT( manager, SurfaceManager );
     D_MAGIC_ASSERT( chunk, Chunk );

     if (!chunk->buffer) {
          D_BUG( "freeing free chunk" );
          return chunk;
     }

     D_DEBUG_AT( SurfMan, "%s( %d bytes at offset %d )\n", __FUNCTION__, chunk->length, chunk->offset );

     //if (chunk->buffer->policy == CSP_VIDEOONLY)
          manager->avail += chunk->length;

     D_DEBUG_AT( SurfMan, "  -> freed %d, available %d\n", chunk->length, manager->avail );

#ifdef CONFIG_HISI_MEM_SUPPORT
     hisi_mem_manager_log(manager);
#endif

     chunk->allocation = NULL;
     chunk->buffer     = NULL;

     manager->min_toleration--;

     if (chunk->prev  &&  !chunk->prev->buffer) {
          Chunk *prev = chunk->prev;

          //D_DEBUG_AT( SurfMan, "  -> merging with previous chunk at %d\n", prev->offset );

          prev->length += chunk->length;

          prev->next = chunk->next;
          if (prev->next)
               prev->next->prev = prev;

          //D_DEBUG_AT( SurfMan, "  -> freeing %p (prev %p, next %p)\n", chunk, chunk->prev, chunk->next);

          D_MAGIC_CLEAR( chunk );

          SHFREE( manager->shmpool, chunk );
          chunk = prev;
     }

     if (chunk->next  &&  !chunk->next->buffer) {
          Chunk *next = chunk->next;

          //D_DEBUG_AT( SurfMan, "  -> merging with next chunk at %d\n", next->offset );

          chunk->length += next->length;

          chunk->next = next->next;
          if (chunk->next)
               chunk->next->prev = chunk;

          D_MAGIC_CLEAR( next );

          SHFREE( manager->shmpool, next );
     }

     return chunk;
}

static Chunk *
occupy_chunk( SurfaceManager *manager, Chunk *chunk, CoreSurfaceAllocation *allocation, int length, int pitch )
{
     D_MAGIC_ASSERT( manager, SurfaceManager );
     D_MAGIC_ASSERT( chunk, Chunk );
     D_MAGIC_ASSERT( allocation, CoreSurfaceAllocation );
     D_MAGIC_ASSERT( allocation->buffer, CoreSurfaceBuffer );

     if (allocation->buffer->policy == CSP_VIDEOONLY)
          manager->avail -= length;

     chunk = split_chunk( manager, chunk, length );
     if (!chunk)
          return NULL;

     D_DEBUG_AT( SurfMan, "%s( %d bytes at offset %d )\n", __FUNCTION__, chunk->length, chunk->offset );

     D_DEBUG_AT( SurfMan, "  -> occupied %d, available %d\n", chunk->length, manager->avail );

#ifdef CONFIG_HISI_MEM_SUPPORT
     hisi_mem_manager_log(manager);
#endif

     chunk->allocation = allocation;
     chunk->buffer     = allocation->buffer;
     chunk->pitch      = pitch;

     manager->min_toleration++;

     return chunk;
}

