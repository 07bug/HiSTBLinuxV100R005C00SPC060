/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : gstsmevideosink_hivo_sec_allocator.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年9月25日
  最近修改   :
  功能描述   : video sink & vdec 共享安全内存分配器
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月25日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __GSTSMEVIDEOSINK_HIHAL_SEC_ALLCATOR_H__
#define __GSTSMEVIDEOSINK_HIHAL_SEC_ALLCATOR_H__

#include <gst/gstallocator.h>
#include "gstsmevideosink_hihal.h"
#include "mpi_mmz.h"

typedef struct
{
  GstMemory mem;
  gsize slice_size; // sizeof(GstMemoryHiVOMMZ) + data size
  guint8 *data; // ture frame memory
  gpointer sec_mem; // For SMMU secure buffer
  gpointer user_data;
  GDestroyNotify notify;
} GstMemoryHiVOSEC;

#define GST_TYPE_ALLOCATOR_HIVOSECMMZ            (gst_allocator_sme_hivosecmmz_get_type())
#define GST_IS_ALLOCATOR_HIVOSECMMZ(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_ALLOCATOR_HIVOSECMMZ))
#define GST_IS_ALLOCATOR_HIVOSECMMZ_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_ALLOCATOR_HIVOSECMMZ))
#define GST_ALLOCATOR_HIVOSECMMZ_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_ALLOCATOR_HIVOSECMMZ, GstAllocatorHiVOSECMMZClass))
#define GST_ALLOCATOR_HIVOSECMMZ(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_ALLOCATOR_HIVOSECMMZ, GstAllocatorHiVOSECMMZ))
#define GST_ALLOCATOR_HIVOSECMMZ_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_ALLOCATOR_HIVOSECMMZ, GstAllocatorHiVOSECMMZClass))
#define GST_ALLOCATOR_HIVOSECMMZ_CAST(obj)       ((GstAllocatorHiVOSECMMZ*)(obj))

typedef struct _GstAllocatorHiVOSECMMZ GstAllocatorHiVOSECMMZ;
typedef struct _GstAllocatorHiVOSECMMZClass GstAllocatorHiVOSECMMZClass;

struct _GstAllocatorHiVOSECMMZ
{
  GstAllocator parent;
  GstSmeVideoSinkHiHal* vsink; //vsink element指针
};

struct _GstAllocatorHiVOSECMMZClass {
  GstAllocatorClass p_class;
};

//@vsink:video sink element 指针
//return: GstAllocatorHiVOMMZ对象指针
GstAllocator* gst_allcator_sme_hivosecmmz_new(GstSmeVideoSinkHiHal* vsink);

#endif//__GSTSMEVIDEOSINK_HIHAL_SEC_ALLCATOR_H__
