/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : gstsmevideosink_hivo_allocator.h
  �� �� ��   : ����
  ��    ��   : liurongliang(l00180035)
  ��������   : 2015��9��25��
  ����޸�   :
  ��������   : video sink & vdec �����ڴ������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��25��
    ��    ��   : liurongliang(l00180035)
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __GSTSMEVIDEOSINK_HIHAL_ALLCATOR_H__
#define __GSTSMEVIDEOSINK_HIHAL_ALLCATOR_H__

#include <gst/gstallocator.h>
#include "gstsmevideosink_hihal.h"
#include <hi_common.h>

typedef struct
{
  GstMemory mem;
  gsize slice_size;//sizeof(GstMemoryHiVOMMZ) + data size
  guint8 *data;//ture frame memory
  HI_MMZ_BUF_S stMmzBuf;//for free MMZ
  gpointer user_data;
  GDestroyNotify notify;

} GstMemoryHiVOMMZ;


#define GST_TYPE_ALLOCATOR_HIVOMMZ            (gst_allocator_sme_hivommz_get_type())
#define GST_IS_ALLOCATOR_HIVOMMZ(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_ALLOCATOR_HIVOMMZ))
#define GST_IS_ALLOCATOR_HIVOMMZ_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_ALLOCATOR_HIVOMMZ))
#define GST_ALLOCATOR_HIVOMMZ_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_ALLOCATOR_HIVOMMZ, GstAllocatorHiVOMMZClass))
#define GST_ALLOCATOR_HIVOMMZ(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_ALLOCATOR_HIVOMMZ, GstAllocatorHiVOMMZ))
#define GST_ALLOCATOR_HIVOMMZ_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_ALLOCATOR_HIVOMMZ, GstAllocatorHiVOMMZClass))
#define GST_ALLOCATOR_HIVOMMZ_CAST(obj)       ((GstAllocatorHiVOMMZ*)(obj))


typedef struct _GstAllocatorHiVOMMZ GstAllocatorHiVOMMZ;
typedef struct _GstAllocatorHiVOMMZClass GstAllocatorHiVOMMZClass;

//typedef struct _GstSmeVideoSinkHiVO GstSmeVideoSinkHiVO;
struct _GstAllocatorHiVOMMZ
{
  GstAllocator parent;
  GstSmeVideoSinkHiHal* vsink;//vsink elementָ��
};

struct _GstAllocatorHiVOMMZClass {
  GstAllocatorClass p_class;
};

//@vsink:video sink element ָ��
//return: GstAllocatorHiVOMMZ����ָ��
GstAllocator* gst_allcator_sme_hivommz_new(GstSmeVideoSinkHiHal* vsink);

#endif
