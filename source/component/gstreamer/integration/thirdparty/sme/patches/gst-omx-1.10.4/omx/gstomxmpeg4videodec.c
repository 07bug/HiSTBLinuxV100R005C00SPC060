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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>

#include "gstomxmpeg4videodec.h"

GST_DEBUG_CATEGORY_STATIC (gst_omx_mpeg4_video_dec_debug_category);
#define GST_CAT_DEFAULT gst_omx_mpeg4_video_dec_debug_category

/* prototypes */
static gboolean gst_omx_mpeg4_video_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);
static gboolean gst_omx_mpeg4_video_dec_set_format (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);

enum
{
  PROP_0
};

/* class initialization */

#define DEBUG_INIT \
  GST_DEBUG_CATEGORY_INIT (gst_omx_mpeg4_video_dec_debug_category, "omxmpeg4videodec", 0, \
      "debug category for gst-omx video decoder base class");

G_DEFINE_TYPE_WITH_CODE (GstOMXMPEG4VideoDec, gst_omx_mpeg4_video_dec,
    GST_TYPE_OMX_VIDEO_DEC, DEBUG_INIT);


static void
gst_omx_mpeg4_video_dec_class_init (GstOMXMPEG4VideoDecClass * klass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GstOMXVideoDecClass *videodec_class = GST_OMX_VIDEO_DEC_CLASS (klass);

  videodec_class->is_format_change =
      GST_DEBUG_FUNCPTR (gst_omx_mpeg4_video_dec_is_format_change);
  videodec_class->set_format =
      GST_DEBUG_FUNCPTR (gst_omx_mpeg4_video_dec_set_format);


#ifndef SME_GST_OMX
  videodec_class->cdata.default_sink_template_caps = "video/mpeg, "
      "mpegversion=(int) 4, "
      "systemstream=(boolean) false, "
      "parsed=(boolean) true, " "width=(int) [1,MAX], " "height=(int) [1,MAX]";
#else
  videodec_class->cdata.default_sink_template_caps = "video/mpeg, "
    "mpegversion=(int)4";
#endif

  gst_element_class_set_static_metadata (element_class,
      "OpenMAX MPEG4 Video Decoder",
      "Codec/Decoder/Video",
      "Decode MPEG4 video streams",
      "Sebastian Dröge <sebastian.droege@collabora.co.uk>");

  gst_omx_set_default_role (&videodec_class->cdata, "video_decoder.mpeg4");
}

static void
gst_omx_mpeg4_video_dec_init (GstOMXMPEG4VideoDec * self)
{
}

static gboolean
gst_omx_mpeg4_video_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state)
{
  return FALSE;
}

static gboolean
gst_omx_mpeg4_video_dec_set_format (GstOMXVideoDec * dec, GstOMXPort * port,
    GstVideoCodecState * state)
{
  gboolean ret;
  OMX_PARAM_PORTDEFINITIONTYPE port_def;

  gst_omx_port_get_port_definition (port, &port_def);
  port_def.format.video.eCompressionFormat = OMX_VIDEO_CodingMPEG4;
  ret = gst_omx_port_update_port_definition (port, &port_def) == OMX_ErrorNone;

  return ret;
}
