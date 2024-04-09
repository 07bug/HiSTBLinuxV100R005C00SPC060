/*
 * Copyright (C) 2011, Hewlett-Packard Development Company, L.P.
 *   Author: Sebastian Dröge <sebastian.droege@collabora.co.uk>, Collabora Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 */

#ifndef __GST_OMX_VIDEO_DEC_H__
#define __GST_OMX_VIDEO_DEC_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideodecoder.h>

#include "gstomx.h"
#include <stdio.h>


G_BEGIN_DECLS

//#define GST_OMX_DUMP_ES
//#define GST_OMX_DUMP_RAW

#define M_SME_HEVC_CFG_ITEM_MAX 256
#define GST_AVC_CFG_LEN_MIN 7
#define SME_AVC_NAL_HEAD_LEN 4
#define M_SME_UINT32_MAX (0xFFFFFFFF)

#define SME_HAS_AVC_NAL(pu8Data)\
(((0 == pu8Data[0]) && (0 == pu8Data[1])\
&& (0 == pu8Data[2]) && (1 == pu8Data[3])) ? TRUE : FALSE)

#define GST_TYPE_OMX_VIDEO_DEC \
  (gst_omx_video_dec_get_type())
#define GST_OMX_VIDEO_DEC(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_OMX_VIDEO_DEC,GstOMXVideoDec))
#define GST_OMX_VIDEO_DEC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_OMX_VIDEO_DEC,GstOMXVideoDecClass))
#define GST_OMX_VIDEO_DEC_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS((obj),GST_TYPE_OMX_VIDEO_DEC,GstOMXVideoDecClass))
#define GST_IS_OMX_VIDEO_DEC(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_OMX_VIDEO_DEC))
#define GST_IS_OMX_VIDEO_DEC_CLASS(obj) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_OMX_VIDEO_DEC))

typedef struct _GstOMXVideoDec GstOMXVideoDec;
typedef struct _GstOMXVideoDecClass GstOMXVideoDecClass;

struct _GstOMXVideoDec
{
  GstVideoDecoder parent;

  /* < protected > */
  GstOMXComponent *dec;
  GstOMXPort *dec_in_port, *dec_out_port;
  
  GstBufferPool *in_port_pool, *out_port_pool;

  /* < private > */
  GstVideoCodecState *input_state;
  GstBuffer *codec_data;
  /* TRUE if the component is configured and saw
   * the first buffer */
  gboolean started;

  GstClockTime last_upstream_ts;

  /* Draining state */
  GMutex drain_lock;
  GCond drain_cond;
  /* TRUE if EOS buffers shouldn't be forwarded */
  gboolean draining;

  GstFlowReturn downstream_flow_ret;
#ifdef USE_OMX_TARGET_RPI
  GstOMXComponent *egl_render;
  GstOMXPort *egl_in_port, *egl_out_port;
  gboolean eglimage;
#endif

#ifdef GST_OMX_DUMP_ES
  FILE * dump_es_file;
  gint dump_es_time;
#endif

#ifdef GST_OMX_DUMP_RAW
  FILE * dump_raw_file;
#endif
  gboolean bNeedAddVideoFrameHeader;
  guint8 u8NalUnitSizeLen;
  unsigned long omx_frame_rate;
#ifdef GST_CORRECT_PTS_BY_DIFF
  guint64 last_vaild_pts;
  guint64 last_calc_dur;
  gint between_vaild_pts_num;
#endif
};

struct _GstOMXVideoDecClass
{
  GstVideoDecoderClass parent_class;

  GstOMXClassData cdata;

  gboolean (*is_format_change) (GstOMXVideoDec * self, GstOMXPort * port, GstVideoCodecState * state);
  gboolean (*set_format)       (GstOMXVideoDec * self, GstOMXPort * port, GstVideoCodecState * state);
  GstFlowReturn (*prepare_frame)   (GstOMXVideoDec * self, GstVideoCodecFrame *frame);
};

typedef struct _tagConfigData
{
  guint32 u32CfgDataSize;
  guint8* pu8CfgData;
}ST_SME_CFG_DATA, *PST_SME_CFG_DATA;

//bla or sps pps
typedef struct _tagHevcNalCfgItem
{
  guint32 u32Len;
  guint8 au8Cfgs[0];
}ST_HEVCNALCFG_ITEM, *PST_HEVCNALCFG_ITEM;


typedef struct _tagHevcNalCfgList
{
  guint32 u32Count;
  PST_HEVCNALCFG_ITEM pstItem[M_SME_HEVC_CFG_ITEM_MAX];//Ã¿¸öItem¶¼Òª¶ÀÁ¢ÊÍ·Å
}ST_HEVCNALCFG_LIST, *PST_HEVCNALCFG_LIST;

void gst_omx_video_dec_add_nal_header(guint8* pu8Data, guint32 u32Len);
GType gst_omx_video_dec_get_type (void);

G_END_DECLS

#endif /* __GST_OMX_VIDEO_DEC_H__ */
