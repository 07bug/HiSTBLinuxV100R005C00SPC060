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
#include "gstomxh265dec.h"


#define GST_HEVC_CFG_LEN_MIN 22
#define SME_HEVC_NAL_HEAD_LEN 4


GST_DEBUG_CATEGORY_STATIC (gst_omx_h265_dec_debug_category);
#define GST_CAT_DEFAULT gst_omx_h265_dec_debug_category

/* prototypes */
static gboolean gst_omx_h265_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);
static gboolean gst_omx_h265_dec_set_format (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);
static GstFlowReturn gst_omx_h265_dec_handle_frame (GstOMXVideoDec * self,
    GstVideoCodecFrame * frame);
static void gst_omx_h265_dec_add_nal_header(guint8* pu8Data, guint32 u32Len);
static gboolean gst_omx_h265_dec_parse_codec_data(GstOMXVideoDec *self,
    PST_SME_CFG_DATA pstInCfgData, PST_SME_CFG_DATA pstCfgData);
static gboolean gst_omx_h265_dec_raw_codec_to_nal(ST_SME_CFG_DATA stCfgData,
    PST_HEVCNALCFG_LIST pstHevcCfgSet);




/* class initialization */

#define DEBUG_INIT_HEVC \
  GST_DEBUG_CATEGORY_INIT (gst_omx_h265_dec_debug_category, "omxh265dec", 0, \
      "debug category for gst-omx video decoder base class");

G_DEFINE_TYPE_WITH_CODE (GstOMXH265Dec, gst_omx_h265_dec,
    GST_TYPE_OMX_VIDEO_DEC, DEBUG_INIT_HEVC);



static void
gst_omx_h265_dec_class_init (GstOMXH265DecClass * klass)
{
  GstOMXVideoDecClass *videodec_class = GST_OMX_VIDEO_DEC_CLASS (klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GstVideoDecoderClass *video_decoder_class = GST_VIDEO_DECODER_CLASS (klass);



  GST_INFO("gst_omx_h265_dec_class_init");
  videodec_class->is_format_change =
      GST_DEBUG_FUNCPTR (gst_omx_h265_dec_is_format_change);
  videodec_class->set_format = GST_DEBUG_FUNCPTR (gst_omx_h265_dec_set_format);
  video_decoder_class->handle_frame = GST_DEBUG_FUNCPTR (gst_omx_h265_dec_handle_frame);


  //videodec_class->cdata.default_sink_template_caps = "video/x-h265, "
  //    "width=(int) [1,MAX], " "height=(int) [1,MAX], "
  //    "framerate=" GST_VIDEO_FPS_RANGE;
  videodec_class->cdata.default_sink_template_caps = "video/x-h265";

  gst_element_class_set_static_metadata (element_class,
      "OpenMAX H.265 Video Decoder",
      "Codec/Decoder/Video",
      "Decode H.265 video streams",
      "Sebastian Dröge <sebastian.droege@collabora.co.uk>");

  gst_omx_set_default_role (&videodec_class->cdata, "video_decoder.hevc");
}

static void
gst_omx_h265_dec_init (GstOMXH265Dec * self)
{
}

static gboolean
gst_omx_h265_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state)
{
  return FALSE;
}

static gboolean
gst_omx_h265_dec_set_format (GstOMXVideoDec * dec, GstOMXPort * port,
    GstVideoCodecState * state)
{
  gboolean ret;
  OMX_PARAM_PORTDEFINITIONTYPE port_def;
  ST_SME_CFG_DATA stInCfgData;
  ST_SME_CFG_DATA stOutCfgData;
  GstMapInfo info;
  GstBuffer *codec_data = state->codec_data;
  GstBuffer *new_codec;

  GST_INFO("gst_omx_h265_dec_set_format");
  gst_omx_port_get_port_definition (port, &port_def);
  port_def.format.video.eCompressionFormat = OMX_VIDEO_CodingHEVC;
  ret = gst_omx_port_update_port_definition (port, &port_def) == OMX_ErrorNone;

  if(!codec_data)
    return ret;

  /* Parser cfg data */
  gst_buffer_map (codec_data, &info, GST_MAP_READ);

  stInCfgData.pu8CfgData = info.data;
  stInCfgData.u32CfgDataSize = info.size;
  stOutCfgData.pu8CfgData = NULL;
  stOutCfgData.u32CfgDataSize = 0;
  gst_omx_h265_dec_parse_codec_data(dec, &stInCfgData, &stOutCfgData);

  new_codec = gst_buffer_new_wrapped (stOutCfgData.pu8CfgData, stOutCfgData.u32CfgDataSize);
  if(NULL != new_codec){
    gst_buffer_unmap (codec_data, &info);
    gst_buffer_unref (state->codec_data);
    state->codec_data = new_codec;
  }else{
    gst_buffer_unmap (codec_data, &info);
    GST_WARNING("alloc new codec data failed,so we use default codec data,something must be wrong");
    if(stOutCfgData.pu8CfgData){
      g_free(stOutCfgData.pu8CfgData);
    }
  }

  return ret;
}

static GstFlowReturn
gst_omx_h265_dec_handle_frame (GstOMXVideoDec * self,
    GstVideoCodecFrame * frame)
{
  GstMapInfo info;
  GstFlowReturn ret = GST_FLOW_OK;

  gst_buffer_map (frame->input_buffer, &info, GST_MAP_READ);
  if(self->bNeedAddVideoFrameHeader){
    gst_omx_h265_dec_add_nal_header(info.data, info.size);
  }
  gst_buffer_unmap (frame->input_buffer, &info);

  ret = GST_VIDEO_DECODER_CLASS(gst_omx_h265_dec_parent_class)->handle_frame(GST_VIDEO_DECODER (self), frame);

  return ret;
}

static void gst_omx_h265_dec_add_nal_header(guint8* pu8Data, guint32 u32Len)
{
  gst_omx_video_dec_add_nal_header(pu8Data, u32Len);

  return;
}


static gboolean gst_omx_h265_dec_parse_codec_data(GstOMXVideoDec *self, PST_SME_CFG_DATA pstInCfgData, PST_SME_CFG_DATA pstCfgData)
{

  guint32             u32ExtraLen     = 0;
  ST_SME_CFG_DATA     stCfgDataTmp ;
  ST_HEVCNALCFG_LIST  stHevcCfgSet;
  gboolean            bRes            = FALSE;

  GST_DEBUG("gst_omx_h265_dec_parse_codec_data in");
  if(NULL == pstCfgData){
    GST_ERROR("pstCfgData = NULL");
    return FALSE;
  }
  do
  {
    memset(&stHevcCfgSet, 0, sizeof(stHevcCfgSet));
    stCfgDataTmp.pu8CfgData = pstInCfgData->pu8CfgData;
    stCfgDataTmp.u32CfgDataSize = pstInCfgData->u32CfgDataSize;
    bRes = gst_omx_h265_dec_raw_codec_to_nal(stCfgDataTmp, &stHevcCfgSet);
    if(!bRes){
      GST_WARNING("gst_omx_h265_dec_raw_codec_to_nal failed,try use raw");
      u32ExtraLen = pstInCfgData->pu8CfgData;
      if(0 == u32ExtraLen){
        GST_ERROR("extralen = 0");
        return FALSE;
      }

      guint8* pu8CfgData = (guint8*)g_malloc(u32ExtraLen);
      if(NULL == pu8CfgData){
        GST_ERROR("no memory.");
        return FALSE;
      }

      memset(pu8CfgData, 0, u32ExtraLen);
      memcpy(pu8CfgData, pstInCfgData->pu8CfgData, pstInCfgData->u32CfgDataSize);

      pstCfgData->u32CfgDataSize = pstInCfgData->u32CfgDataSize;
      pstCfgData->pu8CfgData = pu8CfgData;
      if((pstInCfgData->u32CfgDataSize >= 3)
          && (!pstInCfgData->pu8CfgData[0] && !pstInCfgData->pu8CfgData[1]
              && pstInCfgData->pu8CfgData[2] <= 1)){
        self->bNeedAddVideoFrameHeader = FALSE;
      }else{
        self->bNeedAddVideoFrameHeader = TRUE;
      }
      break;
    }

    GST_WARNING("gst_omx_h265_dec_raw_codec_to_nal cnt=%d", stHevcCfgSet.u32Count);

    /* BEGIN: Added  for DTS2015071608573 by liurongliang(l00180035), 2015/7/17 */
    self->bNeedAddVideoFrameHeader = TRUE;
    if(0 == stHevcCfgSet.u32Count){
      GST_WARNING("no cfg data");
      bRes = TRUE;
      break;
    }
    /* END:   Added  for DTS2015071608573 by liurongliang(l00180035), 2015/7/17 */

    //for fortify
    guint64 u64ExtraLenTmp = (guint64)u32ExtraLen;
    for(guint32 j = 0; j < stHevcCfgSet.u32Count; j++){
      //u32ExtraLen += stHevcCfgSet.pstItem[j]->u32Len;
      u64ExtraLenTmp += (guint64)stHevcCfgSet.pstItem[j]->u32Len;
    }
    u32ExtraLen = (guint64)u64ExtraLenTmp;
    if((M_SME_UINT32_MAX < u64ExtraLenTmp) || (0 == u32ExtraLen)){
      GST_WARNING("extradata len overflow");
      bRes = FALSE;
      break;
    }

    guint8* pu8CfgData = (guint8*)g_malloc(u32ExtraLen);
    if(NULL == pu8CfgData){
      GST_ERROR("no memory.");
      return FALSE;
    }
    memset(pu8CfgData, 0, u32ExtraLen);

    guint32 u32ExtraLenUsed = 0;
    for(guint32 j = 0; j < stHevcCfgSet.u32Count; j++){
      memcpy(pu8CfgData + u32ExtraLenUsed,
          stHevcCfgSet.pstItem[j]->au8Cfgs,
          (guint32)stHevcCfgSet.pstItem[j]->u32Len);
      u32ExtraLenUsed += stHevcCfgSet.pstItem[j]->u32Len;
    }

    pstCfgData->u32CfgDataSize = u32ExtraLenUsed;
    if (pstCfgData->pu8CfgData){
      g_free(pstCfgData->pu8CfgData);
    }
    pstCfgData->pu8CfgData = pu8CfgData;
  } while ( FALSE);

  for(guint32 j = 0; j < stHevcCfgSet.u32Count ; j++){
    if(NULL != stHevcCfgSet.pstItem[j]){
      g_free(stHevcCfgSet.pstItem[j]);
      stHevcCfgSet.pstItem[j] = NULL;
    }
  }

  return bRes;
}


static gboolean gst_omx_h265_dec_raw_codec_to_nal(ST_SME_CFG_DATA stCfgData,
    PST_HEVCNALCFG_LIST pstHevcCfgSet)
{
  gboolean bRet = FALSE;
  const guint8* pu8Tmp = (const guint8 *)stCfgData.pu8CfgData;
  guint32 u32CfgDataLen = 0;
  gint32 idx = 0;
  gint32 i32NalLenSize = 0;
  gint32 i32SetNum = 0;
  guint32 u32CfgItemLen = 0;

  GST_ERROR("SME_AvcRawCfgDataToNal in");

  if(NULL == pstHevcCfgSet){
    GST_ERROR("invalid args, pstAvcCfgSet null pointer");
    return FALSE;
  }

  pstHevcCfgSet->u32Count = 0;

  if((NULL == stCfgData.pu8CfgData) || (stCfgData.u32CfgDataSize < GST_HEVC_CFG_LEN_MIN)){
    GST_ERROR("invalid args, null pointer");
    goto EXIT;
  }

  memset(pstHevcCfgSet->pstItem, 0, sizeof(pstHevcCfgSet->pstItem));

  /* Determine minimum size and version == 1*/
  if (!pu8Tmp[0] && !pu8Tmp[1] && pu8Tmp[2] <= 1)
  {
    /* some config in parser has been OK, return directly */
    GST_ERROR("unsupport the data");
    goto EXIT;
  }

  pu8Tmp = (const guint8 *)(stCfgData.pu8CfgData + GST_HEVC_CFG_LEN_MIN - 1);
  u32CfgDataLen = (stCfgData.u32CfgDataSize - GST_HEVC_CFG_LEN_MIN) + 1;

  i32NalLenSize = (pu8Tmp[0] & 3) + 1;
  GST_ERROR("hevc i32NalLenSize=%d", i32NalLenSize);

  if(u32CfgDataLen <= 2){
    GST_ERROR("left size is too small");
    goto EXIT;
  }
  i32SetNum = pu8Tmp[1];

  GST_ERROR("hevc i32SetNum=%d", i32SetNum);
  pu8Tmp += 2;
  u32CfgDataLen -= 2;

  for (idx = 0; idx < i32SetNum; idx++)
  {
    if(u32CfgDataLen <= 3){
      GST_ERROR("left size is too small!");
      goto EXIT;
    }

    gint32 i32Type = pu8Tmp[0] & 0x3f;
    gint32 i32Cnt  = (gint32)(((pu8Tmp[1] << 8) | pu8Tmp[2]) & 0xFFFF);

    pu8Tmp += 3;
    u32CfgDataLen -= 3;

    for (gint32 j = 0; j < i32Cnt && j < M_SME_HEVC_CFG_ITEM_MAX; j++)
    {
      if(pstHevcCfgSet->u32Count >= M_SME_HEVC_CFG_ITEM_MAX){
        GST_ERROR("hevc cfg count too long");
        goto EXIT;
      }

      if(u32CfgDataLen <= 2){
        GST_ERROR("left size is too small!");
        goto EXIT;
      }

      gint32 i32Nalsize  = (gint32)(((pu8Tmp[0] << 8) | pu8Tmp[1]) & 0xFFFF);
      if(u32CfgDataLen < (guint32)(2 + i32Nalsize)){
        GST_ERROR("left is too small!");
        goto EXIT;
      }

      u32CfgItemLen = (guint32)(sizeof(ST_HEVCNALCFG_ITEM) +
              (guint32)(i32Nalsize + SME_HEVC_NAL_HEAD_LEN));
      pstHevcCfgSet->pstItem[pstHevcCfgSet->u32Count] =
          (PST_HEVCNALCFG_ITEM)g_malloc(u32CfgItemLen);
      if(NULL == pstHevcCfgSet->pstItem[pstHevcCfgSet->u32Count]){
        GST_ERROR("malloc nal failed");
        goto EXIT;
      }

      pstHevcCfgSet->pstItem[pstHevcCfgSet->u32Count]->au8Cfgs[0] = 0;
      pstHevcCfgSet->pstItem[pstHevcCfgSet->u32Count]->au8Cfgs[1] = 0;
      pstHevcCfgSet->pstItem[pstHevcCfgSet->u32Count]->au8Cfgs[2] = 0;
      pstHevcCfgSet->pstItem[pstHevcCfgSet->u32Count]->au8Cfgs[3] = 1;

      memcpy(&pstHevcCfgSet->pstItem[pstHevcCfgSet->u32Count]->au8Cfgs[SME_HEVC_NAL_HEAD_LEN],
          &pu8Tmp[2], (guint32)i32Nalsize);

      pstHevcCfgSet->pstItem[pstHevcCfgSet->u32Count]->u32Len = (guint32)(i32Nalsize + SME_HEVC_NAL_HEAD_LEN);
      pstHevcCfgSet->u32Count++;
      GST_ERROR("gst_omx_h265_dec_raw_codec_to_nal get nal type=%d, len=%d, count=%d", i32Type,
          i32Nalsize, pstHevcCfgSet->u32Count);
      pu8Tmp += 2 + i32Nalsize;
      u32CfgDataLen -= (guint32)(2 + i32Nalsize);
    }
  }

  bRet = TRUE;

EXIT:
  if(FALSE == bRet){
    for(guint32 i = 0; i < pstHevcCfgSet->u32Count; i++){
        if(pstHevcCfgSet->pstItem[i]){
          g_free(pstHevcCfgSet->pstItem[i]);
          pstHevcCfgSet->pstItem[i] = NULL;
        }
    }
    pstHevcCfgSet->u32Count = 0;
  }

  GST_ERROR("gst_omx_h265_dec_raw_codec_to_nal out,bRet=%d, count=%d", (gint32)bRet, pstHevcCfgSet->u32Count);

  return bRet;
}

