/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : gstsmevideosink_hivo_sec_allocator.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2015��9��25��
  ����޸�   :
  ��������   : video sink & vdec ����ȫ�ڴ������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��25��
    ��    ��   :
    �޸�����   : �����ļ�

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
  GstSmeVideoSinkHiHal* vsink; //vsink elementָ��
};

struct _GstAllocatorHiVOSECMMZClass {
  GstAllocatorClass p_class;
};

//@vsink:video sink element ָ��
//return: GstAllocatorHiVOMMZ����ָ��
GstAllocator* gst_allcator_sme_hivosecmmz_new(GstSmeVideoSinkHiHal* vsink);

#endif//__GSTSMEVIDEOSINK_HIHAL_SEC_ALLCATOR_H__
