//lint -e19
//lint -e64
//lint -e528
//lint -e551
//lint -e655
//lint -e818
//lint -e826

#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include "osal_mem.h"
#include "gstsmevideosink_hihal_sec_allcator.h"

#define GST_ALLOCATOR_HIVOSECMMZ_NAME "GstAllocatorHiVOSECMMZ"
//extern gToBeFree;

GType gst_allocator_sme_hivosecmmz_get_type (void);
G_DEFINE_TYPE (GstAllocatorHiVOSECMMZ, gst_allocator_sme_hivosecmmz, GST_TYPE_ALLOCATOR);

static inline void
_hivo_memory_sec_init (GstAllocatorHiVOSECMMZ * allocator, gpointer MemorySecPtr, GstMemoryHiVOSEC * mem,
    GstMemoryFlags flags,GstMemory * parent, gsize slice_size,
    gpointer data, gsize maxsize, gsize align, gsize offset, gsize size,
    gpointer user_data, GDestroyNotify notify)
{
  gst_memory_init (GST_MEMORY_CAST (mem),
      flags, allocator, parent, maxsize, align, offset, size);
  mem->slice_size = slice_size;
  mem->data = data;
  mem->sec_mem = MemorySecPtr;
  mem->user_data = user_data;
  mem->notify = notify;
}

static GstMemoryHiVOSEC *
_hivommz_new_block (GstAllocatorHiVOSECMMZ * allocator, GstMemoryFlags flags,
    gsize maxsize, gsize align, gsize offset, gsize size)
{
  GstMemoryHiVOSEC * hivommz_mem;
  gsize slice_size;
  HI_S32 l_return;
  guint data;
  HI_MPI_SMMU_SEC_ATTR_S SecAttr;
  HI_MPI_SMMU_SEC_BUF_S smmu_sec_buf_s;
  V_INT32 flag_snp;
  static int vdec_outbuf_num = 0;

  (V_VOID)size;

  if (E_SME_MEM_OK != VOS_Memset_S (
    &SecAttr,
    sizeof(HI_MPI_SMMU_SEC_ATTR_S),
    0,
    sizeof(HI_MPI_SMMU_SEC_ATTR_S)))
  {
    GST_ERROR ("SECURE: VOS_Memset_S return failed.");
  }

  slice_size = sizeof(GstMemoryHiVOSEC) + (gsize)(maxsize);
  hivommz_mem = (GstMemoryHiVOSEC *)g_malloc(sizeof(GstMemoryHiVOSEC));

  flag_snp = VOS_Snprintf_S(SecAttr.bufname, sizeof(SecAttr.bufname),
	sizeof(SecAttr.bufname) - 1, "TVP-%d", g_atomic_int_add(&vdec_outbuf_num, 1));
  if(flag_snp <= 0){
      g_free(hivommz_mem);
      GST_ERROR("init SecAttr.bufname failed");
      return NULL;
  }

  SecAttr.bufsize = maxsize;

  l_return = HI_MPI_SMMU_SecMemAlloc (&SecAttr, &smmu_sec_buf_s);

  if (HI_SUCCESS != l_return) {
    GST_ERROR ("Allocate GstMemoryHiVOSEC Failed, return=%d", l_return);
    return NULL;
  }

  GST_INFO ("Allocate sec memory, return=%d, buf_size=%u, bugfix: smmu_addr=%x",
    l_return, SecAttr.bufsize, smmu_sec_buf_s.smmu_addr);

  data = smmu_sec_buf_s.smmu_addr;

  GstSecMemInfo* item = g_malloc(sizeof(GstSecMemInfo));
  if (E_SME_MEM_OK != VOS_Memcpy_S (
    &item->sec_buf_s,
    sizeof(smmu_sec_buf_s),
    &smmu_sec_buf_s,
    sizeof(smmu_sec_buf_s)))
  {
    GST_ERROR ("SECURE: VOS_Memcpy_S return failed.");
  }
  item->pPhyAddr = (void*)data;
  item->mmz_is_vo = FALSE;

  g_mutex_lock (&allocator->vsink->mmz_is_vo_muxtex);
  g_queue_push_tail (&allocator->vsink->q_mmz_is_vo, item);
  g_mutex_unlock (&allocator->vsink->mmz_is_vo_muxtex);
  _hivo_memory_sec_init (allocator, (gpointer)smmu_sec_buf_s.smmu_addr, hivommz_mem, flags, NULL, slice_size, (gpointer)data,
    0, align, offset, maxsize, NULL, NULL);

  return hivommz_mem;
}

static GstMemoryHiVOSEC *
gst_allocator_sme_hivosecmmz_alloc (GstAllocatorHiVOSECMMZ * allocator, gsize size,
    GstAllocationParams * params)
{
  GstMemoryHiVOSEC * hivommz_mem;
  gsize maxsize = size + params->prefix + params->padding;
  hivommz_mem = _hivommz_new_block (allocator, GST_MEMORY_FLAG_ZERO_PREFIXED | GST_MEMORY_FLAG_ZERO_PADDED,
    maxsize, params->align, params->prefix, size);
  return hivommz_mem;
}

static void
gst_allocator_sme_hivosecmmz_free (GstAllocatorHiVOSECMMZ * allocator, GstMemory * mem)
{
  GstMemoryHiVOSEC *hivo_mem = (GstMemoryHiVOSEC *) mem;
  guint idx;
  guint ilen;
  gsize data_size = hivo_mem->slice_size;
  if(!hivo_mem)
    return;

  if (hivo_mem->notify)
    hivo_mem->notify(hivo_mem->user_data);

  g_mutex_lock (&allocator->vsink->mmz_is_vo_muxtex);

  ilen = g_queue_get_length (&allocator->vsink->q_mmz_is_vo);
  for (idx = 0; idx < ilen; idx++) {
    GstSecMemInfo* item = g_queue_peek_nth (&allocator->vsink->q_mmz_is_vo, idx);
    if (!item) {
        GST_ERROR ("peek GstVideoMmzVoFlag %d:is null, why?", idx);
        continue;
    }

    if (item->sec_buf_s.smmu_addr == (guint)hivo_mem->data) {
      gint l_return;

      l_return = HI_MPI_SMMU_SecMemFree (&item->sec_buf_s);
      if (0 != l_return)
        GST_ERROR ("free sec mmz fialed");
      else
        GST_DEBUG ("free sec mmz succeed");

      g_free (item);

      g_queue_pop_nth (&allocator->vsink->q_mmz_is_vo, idx);
      break;
    }
  }
  g_mutex_unlock (&allocator->vsink->mmz_is_vo_muxtex);

  hivo_mem->data = NULL;
  g_free (hivo_mem);

  GST_DEBUG ("FREE SIZE: %d", data_size);

  return;
}

static void
gst_allocator_sme_hivosecmmz_finalize (GObject * obj)
{
  GstAllocatorHiVOSECMMZ* allocator_hivommz = GST_ALLOCATOR_HIVOSECMMZ (obj);
  gst_object_unref (allocator_hivommz->vsink);
  return;
}

static void
gst_allocator_sme_hivosecmmz_class_init (GstAllocatorHiVOSECMMZClass * klass)
{
  GObjectClass *gobject_class;
  GstAllocatorClass *allocator_class;

  gobject_class = (GObjectClass *) klass;
  allocator_class = (GstAllocatorClass *) klass;
  gobject_class->finalize = gst_allocator_sme_hivosecmmz_finalize;
  allocator_class->alloc = gst_allocator_sme_hivosecmmz_alloc;
  allocator_class->free = gst_allocator_sme_hivosecmmz_free;
  return;

}

static gpointer
gst_memory_sme_hivosecmmz_map (GstMemoryHiVOSEC * mem)
{
  return mem->data;
}

static void
gst_memory_sme_hivosecmmz_unmap (GstMemoryHiVOSEC * mem)
{
  (V_VOID)mem;
  return;
}

static void
gst_allocator_sme_hivosecmmz_init (GstAllocatorHiVOSECMMZ * allocator)
{
  GstAllocator *alloc = GST_ALLOCATOR_CAST (allocator);

  alloc->mem_type = GST_ALLOCATOR_HIVOSECMMZ_NAME;
  alloc->mem_map = (GstMemoryMapFunction) gst_memory_sme_hivosecmmz_map;
  alloc->mem_unmap = (GstMemoryUnmapFunction) gst_memory_sme_hivosecmmz_unmap;
  alloc->mem_copy = NULL;
  alloc->mem_share = NULL;
  alloc->mem_is_span = NULL;
  return;
}

GstAllocator* gst_allcator_sme_hivosecmmz_new(GstSmeVideoSinkHiHal* vsink)
{
  GstAllocatorHiVOSECMMZ* allocator_hivommz;

  allocator_hivommz = g_object_new (gst_allocator_sme_hivosecmmz_get_type(), NULL);
  allocator_hivommz->vsink = gst_object_ref (vsink);

  return GST_ALLOCATOR(allocator_hivommz);
}
