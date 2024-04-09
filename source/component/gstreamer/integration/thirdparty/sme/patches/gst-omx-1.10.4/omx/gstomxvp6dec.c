/*
 * Copyright (C) 2013, Collabora Ltd.
 *   Author: Sebastian Dröge <sebastian.droege@collabora.co.uk>
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
#include "gstomxvp6dec.h"
#include "OMX_IndexExt.h"

GST_DEBUG_CATEGORY_STATIC (gst_omx_vp6_dec_debug_category);
#define GST_CAT_DEFAULT gst_omx_vp6_dec_debug_category

/* prototypes */
static gboolean gst_omx_vp6_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);
static gboolean gst_omx_vp6_dec_set_format (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);
static gboolean gst_omx_vp6a_dec_parse_codec_data(GstOMXVideoDec *self,
    PST_SME_CFG_DATA pstInCfgData, PST_SME_CFG_DATA pstCfgData);


enum
{
  PROP_0
};

/* class initialization */

#define DEBUG_INIT \
  GST_DEBUG_CATEGORY_INIT (gst_omx_vp6_dec_debug_category, "omxvp6dec", 0, \
      "debug category for gst-omx video decoder base class");

G_DEFINE_TYPE_WITH_CODE (GstOMXVP6Dec, gst_omx_vp6_dec,
    GST_TYPE_OMX_VIDEO_DEC, DEBUG_INIT);

static void
gst_omx_vp6_dec_class_init (GstOMXVP6DecClass * klass)
{
  GstOMXVideoDecClass *videodec_class = GST_OMX_VIDEO_DEC_CLASS (klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);

  GST_INFO("gst_omx_vp6_dec_class_init");

  videodec_class->is_format_change =
      GST_DEBUG_FUNCPTR (gst_omx_vp6_dec_is_format_change);
  videodec_class->set_format = GST_DEBUG_FUNCPTR (gst_omx_vp6_dec_set_format);

  videodec_class->cdata.default_sink_template_caps = "video/x-vp6-flash, "
      "width=(int) [1,MAX], " "height=(int) [1,MAX];"
      "video/x-vp6, "
      "width=(int) [1,MAX], " "height=(int) [1,MAX];"
      "video/x-vp6-alpha, "
      "width=(int) [1,MAX], " "height=(int) [1,MAX]";

  gst_element_class_set_static_metadata (element_class,
      "OpenMAX VP6 Video Decoder",
      "Codec/Decoder/Video",
      "Decode VP6 video streams",
      "Sebastian Dröge <sebastian.droege@collabora.co.uk>");

  gst_omx_set_default_role (&videodec_class->cdata, "video_decoder.vp6");
}

static void
gst_omx_vp6_dec_init (GstOMXVP6Dec * self)
{
}

static gboolean
gst_omx_vp6_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state)
{
  return FALSE;
}

/* BEGIN: Modified for DTS2015042111297 by liurongliang(l00180035), 2015/5/11 */
static gboolean
gst_omx_vp6_dec_set_format (GstOMXVideoDec * dec, GstOMXPort * port,
    GstVideoCodecState * state)
{
  gboolean ret;
  OMX_PARAM_PORTDEFINITIONTYPE port_def;
  OMX_VIDEO_PARAM_VP6TYPE VideoVp6;
  OMX_CONFIG_MIRRORTYPE cfg_mr_type;
  gchar* caps_tostring = NULL;
  ST_SME_CFG_DATA stInCfgData;
  ST_SME_CFG_DATA stOutCfgData;
  GstMapInfo info;
  GstBuffer *codec_data = state->codec_data;
  GstBuffer *new_codec;

  GST_INFO_OBJECT(dec, "gst_omx_vp6_dec_set_format");

  gst_omx_port_get_port_definition (port, &port_def);
  port_def.format.video.eCompressionFormat = OMX_VIDEO_CodingVP6;
  ret = gst_omx_port_update_port_definition (port, &port_def) == OMX_ErrorNone;

  /* BEGIN: Added by liurongliang(l00180035), 2015/4/9 */
  if(state->caps){
    GstStructure *structure = gst_caps_get_structure (state->caps, 0);
    const gchar *vp6_format = NULL;

    caps_tostring = gst_caps_to_string((const GstCaps*)state->caps);
    if(caps_tostring){
      GST_INFO("vp6 caps is %s", caps_tostring);
      g_free(caps_tostring);
    }else{
      GST_WARNING("vp6 caps is null, something must be wrong");
    }

    gst_omx_component_get_parameter (port->comp, OMX_IndexParamVideoVp6, &VideoVp6);
    cfg_mr_type.nSize=sizeof(OMX_CONFIG_MIRRORTYPE);
    cfg_mr_type.nPortIndex=OMX_DirOutput;
    cfg_mr_type.eMirror=OMX_MirrorNone;
    gst_omx_component_get_config(port->comp, OMX_IndexConfigCommonMirror, &cfg_mr_type);
    GST_INFO("get OMX_IndexParamVideoVp6: VideoVp6.nPortIndex=%ld,eFormat=%d,mirror_type=%d",
        VideoVp6.nPortIndex, VideoVp6.eFormat, cfg_mr_type.eMirror);

    if (gst_structure_has_name (structure, "video/x-vp6-flash")){
      VideoVp6.eFormat = OMX_VIDEO_VP6F;
      VideoVp6.nSize   = sizeof(OMX_VIDEO_PARAM_VP6TYPE);
      cfg_mr_type.eMirror=OMX_MirrorVertical;
    }else if(gst_structure_has_name (structure, "video/x-vp6")){
      VideoVp6.eFormat = OMX_VIDEO_VP6;
      VideoVp6.nSize   = sizeof(OMX_VIDEO_PARAM_VP6TYPE);
      cfg_mr_type.eMirror=OMX_MirrorNone;
    }else if(gst_structure_has_name (structure, "video/x-vp6-alpha")){
      VideoVp6.eFormat = OMX_VIDEO_VP6A;
      VideoVp6.nSize   = sizeof(OMX_VIDEO_PARAM_VP6TYPE);
      cfg_mr_type.eMirror=OMX_MirrorNone;

      if(codec_data){
        /* Parser cfg data */
        gst_buffer_map (codec_data, &info, GST_MAP_READ);

        stInCfgData.pu8CfgData = info.data;
        stInCfgData.u32CfgDataSize = info.size;
        stOutCfgData.pu8CfgData = NULL;
        stOutCfgData.u32CfgDataSize = 0;

        gst_omx_vp6a_dec_parse_codec_data(dec, &stInCfgData, &stOutCfgData);

        new_codec = gst_buffer_new_wrapped (stOutCfgData.pu8CfgData, stOutCfgData.u32CfgDataSize);
        if(NULL != new_codec){
          gst_buffer_unmap (codec_data, &info);
          gst_buffer_unref (state->codec_data);
          state->codec_data = new_codec;
        }else{
          gst_buffer_unmap (codec_data, &info);
          if(stOutCfgData.pu8CfgData){
            g_free(stOutCfgData.pu8CfgData);
          }
          GST_WARNING("alloc new codec data failed,so we use default codec data,something must be wrong");
        }

      }

    }

    gst_omx_component_set_parameter (port->comp, OMX_IndexParamVideoVp6, &VideoVp6);
    gst_omx_component_set_config(port->comp, OMX_IndexConfigCommonMirror, &cfg_mr_type);
    gst_omx_component_get_parameter (port->comp, OMX_IndexParamVideoVp6, &VideoVp6);
    gst_omx_component_get_config(port->comp, OMX_IndexConfigCommonMirror, &cfg_mr_type);
    GST_INFO("after set, get OMX_IndexParamVideoVp6: VideoVp6.nPortIndex=%ld,"
      " eFormat=%d,mirror_type=%d",
      VideoVp6.nPortIndex, VideoVp6.eFormat, cfg_mr_type.eMirror);

  }
  /* END:   Added by liurongliang(l00180035), 2015/4/9 */

  return ret;
}
/* END:   Modified for DTS2015042111297 by liurongliang(l00180035), 2015/5/11 */

static gboolean gst_omx_vp6a_dec_parse_codec_data(GstOMXVideoDec *self, PST_SME_CFG_DATA pstInCfgData, PST_SME_CFG_DATA pstCfgData)
{
  guint8*        pu8CfgData      = NULL;
  guint32        u32Len          = 0;

  GST_INFO("ParseCfgDataOfVP6Ain");

  if(pstInCfgData->u32CfgDataSize <= 1){
    pstCfgData->u32CfgDataSize = 0;
    pstCfgData->pu8CfgData = NULL;
    return TRUE;
  }
  u32Len = (guint32)pstInCfgData->u32CfgDataSize - 1;
  if(0 == u32Len){
    GST_WARNING("extra len = 0");
    return FALSE;
  }

  pu8CfgData = (guint8*)g_malloc(u32Len);

  if(!pu8CfgData){
    GST_WARNING("no memory.");
    return FALSE;
  }

  memset(pu8CfgData, 0, u32Len);
  memcpy(pu8CfgData, pstCfgData->pu8CfgData + 1, pstInCfgData->u32CfgDataSize - 1);

  pstCfgData->u32CfgDataSize = u32Len;
  if (pstCfgData->pu8CfgData)
      g_free(pstCfgData->pu8CfgData);
  pstCfgData->pu8CfgData = pu8CfgData;
  self->bNeedAddVideoFrameHeader = TRUE;

  return TRUE;
}
