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

#include "gstomxwmvdec.h"

GST_DEBUG_CATEGORY_STATIC (gst_omx_wmv_dec_debug_category);
#define GST_CAT_DEFAULT gst_omx_wmv_dec_debug_category

/* prototypes */
static gboolean gst_omx_wmv_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);
static gboolean gst_omx_wmv_dec_set_format (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);
static gboolean gst_omx_wmv_dec_parse_codec_data(GstOMXVideoDec *self,
    PST_SME_CFG_DATA pstInCfgData, PST_SME_CFG_DATA pstCfgData);
static GstFlowReturn gst_omx_wmv_dec_handle_frame (GstOMXVideoDec * self,
    GstVideoCodecFrame * frame);



enum
{
  PROP_0
};

/* class initialization */

#define DEBUG_INIT \
  GST_DEBUG_CATEGORY_INIT (gst_omx_wmv_dec_debug_category, "omxwmvdec", 0, \
      "debug category for gst-omx video decoder base class");

G_DEFINE_TYPE_WITH_CODE (GstOMXWMVDec, gst_omx_wmv_dec,
    GST_TYPE_OMX_VIDEO_DEC, DEBUG_INIT);

static void
gst_omx_wmv_dec_class_init (GstOMXWMVDecClass * klass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GstOMXVideoDecClass *videodec_class = GST_OMX_VIDEO_DEC_CLASS (klass);
  GstVideoDecoderClass *video_decoder_class = GST_VIDEO_DECODER_CLASS (klass);

  GST_INFO("gst_omx_wmv_dec_class_init");

  videodec_class->is_format_change =
      GST_DEBUG_FUNCPTR (gst_omx_wmv_dec_is_format_change);
  videodec_class->set_format = GST_DEBUG_FUNCPTR (gst_omx_wmv_dec_set_format);
  video_decoder_class->handle_frame = GST_DEBUG_FUNCPTR (gst_omx_wmv_dec_handle_frame);

#ifndef SME_GST_OMX
  videodec_class->cdata.default_sink_template_caps = "video/x-wmv, "
      "width=(int) [1,MAX], " "height=(int) [1,MAX]";
#else
  videodec_class->cdata.default_sink_template_caps = "video/x-wmv, "
      "width=(int) [1,MAX], " "height=(int) [1,MAX], " "wmvversion=(int)3" ;
#endif
  gst_element_class_set_static_metadata (element_class,
      "OpenMAX WMV Video Decoder",
      "Codec/Decoder/Video",
      "Decode WMV video streams",
      "Sebastian Dröge <sebastian.droege@collabora.co.uk>");

  gst_omx_set_default_role (&videodec_class->cdata, "video_decoder.wmv");
}

static void
gst_omx_wmv_dec_init (GstOMXWMVDec * self)
{
}

static gboolean
gst_omx_wmv_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state)
{
  return FALSE;
}

static gboolean
gst_omx_wmv_dec_set_format (GstOMXVideoDec * dec, GstOMXPort * port,
    GstVideoCodecState * state)
{
  gboolean ret;
  OMX_PARAM_PORTDEFINITIONTYPE port_def;
  OMX_VIDEO_PARAM_VC1TYPE VideoVC1;
  gchar* caps_tostring = NULL;
  ST_SME_CFG_DATA stInCfgData;
  ST_SME_CFG_DATA stOutCfgData;
  GstMapInfo info;
  GstBuffer *codec_data = state->codec_data;
  GstBuffer *new_codec;

  GST_INFO("gst_omx_wmv_dec_set_format");

  gst_omx_port_get_port_definition (port, &port_def);
  port_def.format.video.eCompressionFormat = OMX_VIDEO_CodingVC1;
  ret = gst_omx_port_update_port_definition (port, &port_def) == OMX_ErrorNone;

  /* BEGIN: Added by liurongliang(l00180035), 2015/4/1 */
  if(state->caps){
    GstStructure *structure = gst_caps_get_structure (state->caps, 0);
    const gchar *format = NULL;
    caps_tostring = gst_caps_to_string((const GstCaps*)state->caps);
    if (gst_structure_has_name (structure, "video/x-wmv")) {
      if (NULL != (format = gst_structure_get_string (structure, "format"))){
        GST_INFO("wmv format=%s", format);
        /*add frame header for advanced vc1 (profile=3).*/
        if(!g_ascii_strncasecmp(format, "WVC1", MIN(sizeof(format),sizeof("WVC1")))){
          /* set config to OMX-IL to tell , now it is advanced */
          gst_omx_component_get_parameter (port->comp, OMX_IndexParamVideoVC1, &VideoVC1);
          GST_INFO("get OMX_IndexParamVideoVC1: VideoVC1.nPortIndex=%ld,profile=%d",
            VideoVC1.nPortIndex, VideoVC1.eProfile);
          VideoVC1.eProfile = OMX_VIDEO_VC1ProfileAdvanced;
          VideoVC1.nSize   = sizeof(OMX_VIDEO_PARAM_VC1TYPE);
          gst_omx_component_set_parameter (port->comp, OMX_IndexParamVideoVC1, &VideoVC1);
          gst_omx_component_get_parameter (port->comp, OMX_IndexParamVideoVC1, &VideoVC1);
          GST_INFO("after set, get OMX_IndexParamVideoVC1: VideoVC1.nPortIndex=%ld, profile=%d",
            VideoVC1.nPortIndex, VideoVC1.eProfile);

          if(!codec_data)
            return ret;

          /* Parser cfg data */
          gst_buffer_map (codec_data, &info, GST_MAP_READ);

          stInCfgData.pu8CfgData = info.data;
          stInCfgData.u32CfgDataSize = info.size;
          stOutCfgData.pu8CfgData = NULL;
          stOutCfgData.u32CfgDataSize = 0;
          gst_omx_wmv_dec_parse_codec_data(dec, &stInCfgData, &stOutCfgData);
          new_codec = gst_buffer_new_wrapped (stOutCfgData.pu8CfgData, stOutCfgData.u32CfgDataSize);
          if(NULL != new_codec)
          {
            gst_buffer_unmap (codec_data, &info);
            gst_buffer_unref (state->codec_data);
            state->codec_data = new_codec;
          }else{
            gst_buffer_unmap (codec_data, &info);
            if(stOutCfgData.pu8CfgData)
            {
                g_free(stOutCfgData.pu8CfgData);
            }
            GST_WARNING("alloc new codec data failed,so we use default codec data,something must be wrong");
          }
        }
      }
    }
  }
  /* END:   Added by liurongliang(l00180035), 2015/4/1 */

  return ret;
}

static gboolean gst_omx_wmv_dec_parse_codec_data(GstOMXVideoDec *self, PST_SME_CFG_DATA pstInCfgData, PST_SME_CFG_DATA pstCfgData)
{
  guint8*        pu8CfgData      = NULL;
  guint32        u32Len          = 0;

  GST_DEBUG("ParseCfgDataOfVC1AP in");

  if(pstInCfgData->u32CfgDataSize <= 1){
    u32Len = pstInCfgData->u32CfgDataSize;
  }else{
    u32Len = pstInCfgData->u32CfgDataSize - 1;
  }

  if(0 == u32Len){
    GST_WARNING("extra len = 0");
    return FALSE;
  }

  pu8CfgData = (guint8*)g_malloc(u32Len);
  if(!pu8CfgData){
    GST_ERROR("no memory.");
    return FALSE;
  }

  memset(pu8CfgData, 0, u32Len);
  memcpy(pu8CfgData,
      pstInCfgData->pu8CfgData + 1,
      pstInCfgData->u32CfgDataSize - 1);

  pstCfgData->u32CfgDataSize = u32Len;
  if (pstCfgData->pu8CfgData)
      g_free(pstCfgData->pu8CfgData);
  pstCfgData->pu8CfgData = pu8CfgData;
  self->bNeedAddVideoFrameHeader = TRUE;

  return TRUE;
}

static GstFlowReturn
gst_omx_wmv_dec_handle_frame (GstOMXVideoDec * self,
    GstVideoCodecFrame * frame)
{
  GstMapInfo info;
  gint32 i32ExtHdSize = 0;
  guint32 u32RawDataLen = 0;
  guint8* pu8RawData = NULL;
  GstFlowReturn ret = GST_FLOW_OK;
  GstBuffer * pNewInBuf = NULL;

  do
  {
    if(!self->bNeedAddVideoFrameHeader){
      break;
    }

    i32ExtHdSize = 4;
    gst_buffer_map (frame->input_buffer, &info, GST_MAP_READ);
    pu8RawData = (guint8*)g_malloc(info.size + i32ExtHdSize + 3);

    if(NULL == pu8RawData){
      GST_WARNING("no memory,malloc pu8RawData failed");
      break;
    }
    pu8RawData[0] = 0;
    pu8RawData[1] = 0;
    pu8RawData[2] = 1;
    pu8RawData[3] = 13;
    memcpy(pu8RawData+i32ExtHdSize, info.data, info.size);
    u32RawDataLen = info.size + i32ExtHdSize;

    pNewInBuf = gst_buffer_new_wrapped (pu8RawData, u32RawDataLen);
    if(NULL != pNewInBuf){
      gst_buffer_unmap (frame->input_buffer, &info);
      gst_buffer_unref (frame->input_buffer);
      frame->input_buffer = pNewInBuf;
    }else{
      gst_buffer_unmap (frame->input_buffer, &info);
      g_free(pu8RawData);
      GST_WARNING("alloc new_in_buf failed,something must be wrong");
    }
  }while(FALSE);

  ret = GST_VIDEO_DECODER_CLASS(gst_omx_wmv_dec_parent_class)->handle_frame(GST_VIDEO_DECODER (self), frame);

  return ret;
}
