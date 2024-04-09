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

#include "gstomxh264dec.h"

GST_DEBUG_CATEGORY_STATIC (gst_omx_h264_dec_debug_category);
#define GST_CAT_DEFAULT gst_omx_h264_dec_debug_category

#define SME_AVC_NAL_SIZE_LEN     4
#define M_SME_AVC_CFG_ITEM_MAX   256
#define SME_AVC_NAL_SIZE_LEN_2   2
#define SME_AVC_NAL_SIZE_LEN_1   1

#define SME_GET_UINT_FOR_BGE_2(pu8Data)\
((((guint32)pu8Data[0]) << 8) | ((guint32)pu8Data[1]))


typedef struct _tagAvcNalCfgItem
{
    guint32 u32Len;
    guint8 au8SpsOrPps[0];
}ST_AVCNALCFG_ITEM, *PST_AVCNALCFG_ITEM;

typedef struct _tagAvcNalCfgList
{
    guint32 u32Count;
    PST_AVCNALCFG_ITEM pstItem[M_SME_AVC_CFG_ITEM_MAX];//every item should be freed Independently
}ST_AVCNALCFG_LIST, *PST_AVCNALCFG_LIST;


/* prototypes */
static gboolean gst_omx_h264_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);
static gboolean gst_omx_h264_dec_set_format (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state);
static gboolean gst_omx_h264_dec_parse_codec_data(GstOMXVideoDec *self,
    PST_SME_CFG_DATA pstInCfgData, PST_SME_CFG_DATA pstCfgData);
gboolean gst_omx_h264_dec_raw_codec_to_nal(ST_SME_CFG_DATA stCfgData,
    PST_AVCNALCFG_LIST pstAvcCfgSet,
    guint32* pu32Profile,
    guint8* pu8NalUnitSizeLen);
static GstFlowReturn gst_omx_h264_dec_handle_frame (GstOMXVideoDec * self,
    GstVideoCodecFrame * frame);
static void gst_omx_h264_dec_add_nal_header(guint8* pu8Data, guint32 u32Len);
static gboolean gst_omx_h264_dec_handle_nal_header(const guint8 u8NalUnitSizeLen,
    guint8 *pu8DataSrc, guint32 u32LenSrc, guint32 u32MaxLenDst,
    guint8 *pu8DataDst,guint32 *pu32LenDst);



enum
{
  PROP_0
};

/* class initialization */

#define DEBUG_INIT \
  GST_DEBUG_CATEGORY_INIT (gst_omx_h264_dec_debug_category, "omxh264dec", 0, \
      "debug category for gst-omx video decoder base class");

G_DEFINE_TYPE_WITH_CODE (GstOMXH264Dec, gst_omx_h264_dec,
    GST_TYPE_OMX_VIDEO_DEC, DEBUG_INIT);

static void
gst_omx_h264_dec_class_init (GstOMXH264DecClass * klass)
{
  GstOMXVideoDecClass *videodec_class = GST_OMX_VIDEO_DEC_CLASS (klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GstVideoDecoderClass *video_decoder_class = GST_VIDEO_DECODER_CLASS (klass);

  videodec_class->is_format_change =
      GST_DEBUG_FUNCPTR (gst_omx_h264_dec_is_format_change);
  videodec_class->set_format = GST_DEBUG_FUNCPTR (gst_omx_h264_dec_set_format);
  video_decoder_class->handle_frame = GST_DEBUG_FUNCPTR (gst_omx_h264_dec_handle_frame);
#ifndef SME_GST_OMX
  videodec_class->cdata.default_sink_template_caps = "video/x-h264, "
      "parsed=(boolean) true, "
      "alignment=(string) au, "
      "stream-format=(string) byte-stream, "
      "width=(int) [1,MAX], " "height=(int) [1,MAX]";
#else
  videodec_class->cdata.default_sink_template_caps = "video/x-h264";
#endif

  gst_element_class_set_static_metadata (element_class,
      "OpenMAX H.264 Video Decoder",
      "Codec/Decoder/Video",
      "Decode H.264 video streams",
      "Sebastian Dröge <sebastian.droege@collabora.co.uk>");

  gst_omx_set_default_role (&videodec_class->cdata, "video_decoder.avc");
}

static void
gst_omx_h264_dec_init (GstOMXH264Dec * self)
{
}

static gboolean
gst_omx_h264_dec_is_format_change (GstOMXVideoDec * dec,
    GstOMXPort * port, GstVideoCodecState * state)
{
  GstCaps *old_caps = NULL;
  GstCaps *new_caps = state->caps;
  GstStructure *old_structure, *new_structure;
  const gchar *old_profile, *old_level, *new_profile, *new_level;

  if (dec->input_state) {
    old_caps = dec->input_state->caps;
  }

  if (!old_caps) {
    return FALSE;
  }

  old_structure = gst_caps_get_structure (old_caps, 0);
  new_structure = gst_caps_get_structure (new_caps, 0);
  old_profile = gst_structure_get_string (old_structure, "profile");
  old_level = gst_structure_get_string (old_structure, "level");
  new_profile = gst_structure_get_string (new_structure, "profile");
  new_level = gst_structure_get_string (new_structure, "level");

  if (g_strcmp0 (old_profile, new_profile) != 0
      || g_strcmp0 (old_level, new_level) != 0) {
    return TRUE;
  }

  return FALSE;
}

static gboolean
gst_omx_h264_dec_set_format (GstOMXVideoDec * dec, GstOMXPort * port,
    GstVideoCodecState * state)
{
  gboolean ret;
  OMX_PARAM_PORTDEFINITIONTYPE port_def;
  ST_SME_CFG_DATA stInCfgData;
  ST_SME_CFG_DATA stOutCfgData;
  GstMapInfo info;
  GstBuffer *codec_data = state->codec_data;
  GstBuffer *new_codec;

  gst_omx_port_get_port_definition (port, &port_def);
  port_def.format.video.eCompressionFormat = OMX_VIDEO_CodingAVC;
  ret = gst_omx_port_update_port_definition (port, &port_def) == OMX_ErrorNone;


  if(!codec_data)
    return ret;

  /* Parser cfg data */
  gst_buffer_map (codec_data, &info, GST_MAP_READ);

  stInCfgData.pu8CfgData = info.data;
  stInCfgData.u32CfgDataSize = info.size;
  stOutCfgData.pu8CfgData = NULL;
  stOutCfgData.u32CfgDataSize = 0;
  gst_omx_h264_dec_parse_codec_data(dec, &stInCfgData, &stOutCfgData);

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

static gboolean gst_omx_h264_dec_parse_codec_data(GstOMXVideoDec *self, PST_SME_CFG_DATA pstInCfgData, PST_SME_CFG_DATA pstCfgData)
{
  guint32             u32ExtraLen      = 0;
  ST_SME_CFG_DATA     stCfgDataTmp ;
  ST_AVCNALCFG_LIST   stAvcCfgSet;
  gboolean            bRes             = FALSE;
  //use 4 bytes as default value.
  guint8              u8NalUnitSizeLen = SME_AVC_NAL_SIZE_LEN;

  GST_INFO("gst_omx_h264_dec_parse_codec_data in.");
  do
  {
    memset(&stAvcCfgSet, 0, sizeof(stAvcCfgSet));

    stCfgDataTmp.pu8CfgData = pstInCfgData->pu8CfgData;
    stCfgDataTmp.u32CfgDataSize = pstInCfgData->u32CfgDataSize;
    bRes = gst_omx_h264_dec_raw_codec_to_nal(stCfgDataTmp, &stAvcCfgSet, NULL, &u8NalUnitSizeLen);
    if(!bRes)
    {
      if((pstInCfgData->u32CfgDataSize >= 3)
          && (!pstInCfgData->pu8CfgData[0] && !pstInCfgData->pu8CfgData[1]
              && pstInCfgData->pu8CfgData[2] <= 1)){
        self->bNeedAddVideoFrameHeader = FALSE;
      }else{
        self->bNeedAddVideoFrameHeader = TRUE;
        self->u8NalUnitSizeLen = u8NalUnitSizeLen;
      }

      GST_INFO("gst_omx_h264_dec_parse_codec_data failed, try use raw, "
          "bNeedFrameHeader=%d, NalUnitSizeLen=%d",
          self->bNeedAddVideoFrameHeader, u8NalUnitSizeLen);

      u32ExtraLen = (guint32)pstInCfgData->u32CfgDataSize;
      //for fortify.
      if(0 == u32ExtraLen){
        GST_WARNING("extra len zero !");
        bRes = FALSE;
        break;
      }

      guint8* pu8CfgData = (guint8*)g_malloc(u32ExtraLen);
      if(!pu8CfgData){
        GST_WARNING("no memory.");
        bRes = FALSE;
        break;
      }

      memset(pu8CfgData, 0, u32ExtraLen);
      memcpy(pu8CfgData, pstInCfgData->pu8CfgData, pstInCfgData->u32CfgDataSize);

      pstCfgData->u32CfgDataSize = pstInCfgData->u32CfgDataSize;
      if (pstCfgData->pu8CfgData)
         g_free(pstCfgData->pu8CfgData);
      pstCfgData->pu8CfgData = pu8CfgData;
      break;
    }

    GST_WARNING("gst_omx_h264_dec_raw_codec_to_nal cnt=%d, NalUnitSizeLen=%d",
        stAvcCfgSet.u32Count, u8NalUnitSizeLen);
    self->u8NalUnitSizeLen = u8NalUnitSizeLen;

    /* BEGIN: Added for DTS2015071608573 by liurongliang(l00180035), 2015/7/17 */
    self->bNeedAddVideoFrameHeader = TRUE;
    if(0 == stAvcCfgSet.u32Count){
      GST_WARNING("no cfg data");
      bRes = FALSE;
      break;
    }
    /* END:   Added for DTS2015071608573 by liurongliang(l00180035), 2015/7/17 */

    //for fortify
    guint64 u64ExtraLenTmp = (guint64)u32ExtraLen;
    for(guint32 j = 0; j < stAvcCfgSet.u32Count; j++){
      //u32ExtraLen += stAvcCfgSet.pstItem[j]->u32Len;
      u64ExtraLenTmp += (guint64)(stAvcCfgSet.pstItem[j]->u32Len & 0xFFFF);
    }
    u32ExtraLen = (guint32)u64ExtraLenTmp;
    if(M_SME_UINT32_MAX < u64ExtraLenTmp || 0 == u32ExtraLen){
      GST_WARNING("extradata len overflow");
      bRes = FALSE;
      break;
    }

    guint8* pu8CfgData = (guint8*)g_malloc(u32ExtraLen);
    if(!pu8CfgData){
      GST_WARNING("no memory.");
      bRes = FALSE;
      break;
    }

    memset(pu8CfgData, 0, u32ExtraLen);

    guint32 u32ExtraLenUsed = 0;
    for(guint32 j = 0; j < stAvcCfgSet.u32Count; j++){
      memcpy(pu8CfgData + u32ExtraLenUsed,
        stAvcCfgSet.pstItem[j]->au8SpsOrPps,
        (guint32)stAvcCfgSet.pstItem[j]->u32Len);
      u32ExtraLenUsed += stAvcCfgSet.pstItem[j]->u32Len;
    }

    pstCfgData->u32CfgDataSize = u32ExtraLenUsed;
    /** BEGIN: Added for DTS2015082904200  by baihaili(b00311320), 2015/8/29 */
    if (pstCfgData->pu8CfgData)
        g_free(pstCfgData->pu8CfgData);
    /* END:   Added by baihaili(b00311320), 2015/8/29 */
    pstCfgData->pu8CfgData = pu8CfgData;
  } while ( FALSE );

  for(guint32 j = 0; j < stAvcCfgSet.u32Count; j++){
    if(NULL != stAvcCfgSet.pstItem[j]){
      g_free(stAvcCfgSet.pstItem[j]);
      stAvcCfgSet.pstItem[j] = NULL;
    }
  }

  return bRes;
}


// refer to ISO/IEC 14496-15
gboolean gst_omx_h264_dec_raw_codec_to_nal(ST_SME_CFG_DATA stCfgData,
                        PST_AVCNALCFG_LIST pstAvcCfgSet,
                        guint32* pu32Profile,
                        guint8* pu8NalUnitSizeLen)
{
  gboolean bRet = FALSE;
  const guint8* pu8Tmp = (const guint8 *)stCfgData.pu8CfgData;
  guint32 u32CfgDataLen = 0;
  gint32 idx = 0;
  gint32 i32SpsSetCount = 0;
  gint32 i32PpsSetCount = 0;
  guint32 u32CfgItemLen = 0;

  GST_INFO("gst_omx_h264_dec_raw_codec_to_nal in");

  if(NULL == pstAvcCfgSet || NULL == pu8NalUnitSizeLen){
    GST_ERROR("invalid args, pstAvcCfgSet or pu32NalUnitSizeLen is null pointer");
    return FALSE;
  }

  pstAvcCfgSet->u32Count = 0;

  if((NULL == stCfgData.pu8CfgData) || (stCfgData.u32CfgDataSize < GST_AVC_CFG_LEN_MIN)){
    GST_ERROR("invalid args, null pointer");
    goto EXIT;
  }

  memset(pstAvcCfgSet->pstItem, 0, sizeof(pstAvcCfgSet->pstItem));

  /* Determine minimum size and version == 1*/
  if (pu8Tmp[0] != 1){
    /* some config in parser has been OK, return directly */
    GST_ERROR("unsupport the data");
    goto EXIT;
  }

  if(NULL != pu32Profile){
    //profile
    *pu32Profile = pu8Tmp[1];
  }

  //NAL unit size length
  *pu8NalUnitSizeLen = (pu8Tmp[4] & 3) + 1;

  /* refer to ISO/IEC 14496-15:
   * NAL unit size length must be 1, 2, 4
   */
  if ((*pu8NalUnitSizeLen != SME_AVC_NAL_SIZE_LEN)
      && (*pu8NalUnitSizeLen != SME_AVC_NAL_SIZE_LEN_2)
      && (*pu8NalUnitSizeLen != SME_AVC_NAL_SIZE_LEN_1)){
    GST_ERROR("unsupport the data, NalUnitSizeLen=%d", *pu8NalUnitSizeLen);
    goto EXIT;
  }

  GST_INFO("avc Profile=%u, NAL_Unit_Size_Len=%d", pu8Tmp[1], *pu8NalUnitSizeLen);

  pu8Tmp = (const guint8 *)stCfgData.pu8CfgData;
  u32CfgDataLen = stCfgData.u32CfgDataSize;
  i32SpsSetCount = pu8Tmp[5] & 31;
  pu8Tmp += 6;
  u32CfgDataLen -= 6;

  if(i32SpsSetCount <= 0){
    GST_ERROR("numSeqParameterSets is 0");
    goto EXIT;
  }

  /*deal with sps first */
  for (idx = 0; idx < i32SpsSetCount; ++idx)
  {
    guint32 u32SpsLen = 0;
    if (u32CfgDataLen < 2){
      GST_ERROR("sps err");
      goto EXIT;
    }

    //for fortify
    u32SpsLen = (pu8Tmp[0] << 8 | pu8Tmp[1]) & 0xFFFF;

    pu8Tmp += 2;
    u32CfgDataLen -= 2;

    if (u32CfgDataLen < u32SpsLen){
      GST_ERROR("sps len err");
      goto EXIT;
    }

    if(pstAvcCfgSet->u32Count >= M_SME_AVC_CFG_ITEM_MAX){
      GST_ERROR("cfg count too long");
      goto EXIT;
    }
    u32CfgItemLen = (guint32)(sizeof(ST_AVCNALCFG_ITEM) + u32SpsLen + SME_AVC_NAL_HEAD_LEN);
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count] =
        (PST_AVCNALCFG_ITEM)g_malloc(u32CfgItemLen);
    if(NULL == pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]){
      GST_ERROR("malloc sp failed");
      goto EXIT;
    }
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[0] = 0;
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[1] = 0;
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[2] = 0;
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[3] = 1;

    memcpy(&pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[SME_AVC_NAL_HEAD_LEN], pu8Tmp,  u32SpsLen);

    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->u32Len = u32SpsLen + SME_AVC_NAL_HEAD_LEN;
    pstAvcCfgSet->u32Count++;
    GST_ERROR("gst_omx_h264_dec_raw_codec_to_nal get sps,len=%d,count=%d", u32SpsLen,pstAvcCfgSet->u32Count);
    pu8Tmp += u32SpsLen;
    u32CfgDataLen -= u32SpsLen;
  }

  if (u32CfgDataLen < 1){
    GST_ERROR("u32CfgDataLen left err");
    goto EXIT;
  }

  /* deal with pps */
  //for coverity
  i32PpsSetCount = (*pu8Tmp) & 0xFF;
  ++pu8Tmp;
  --u32CfgDataLen;

  for (idx = 0; idx < i32PpsSetCount; ++idx)
  {
    guint32 u32PpsLen = 0;
    if (u32CfgDataLen < 2){
      GST_ERROR("sps err");
      goto EXIT;
    }

    //for fortify
    u32PpsLen = (pu8Tmp[0] << 8 | pu8Tmp[1]) & 0xFFFF;

    pu8Tmp += 2;
    u32CfgDataLen -= 2;

    if (u32CfgDataLen < u32PpsLen){
      GST_ERROR("pps len err");
      goto EXIT;
    }

    if(pstAvcCfgSet->u32Count >= M_SME_AVC_CFG_ITEM_MAX){
      GST_ERROR("cfg count too long");
      goto EXIT;
    }

    u32CfgItemLen = (guint32)(sizeof(ST_AVCNALCFG_ITEM) +
        u32PpsLen + SME_AVC_NAL_HEAD_LEN);
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count] =
        (PST_AVCNALCFG_ITEM)g_malloc(u32CfgItemLen);
    if(NULL == pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]){
      GST_ERROR("malloc pps failed");
      goto EXIT;
    }
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[0] = 0;
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[1] = 0;
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[2] = 0;
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[3] = 1;

    memcpy(&pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->au8SpsOrPps[SME_AVC_NAL_HEAD_LEN], pu8Tmp,  u32PpsLen);
    pstAvcCfgSet->pstItem[pstAvcCfgSet->u32Count]->u32Len = u32PpsLen + SME_AVC_NAL_HEAD_LEN;
    pstAvcCfgSet->u32Count++;
    GST_ERROR("gst_omx_h264_dec_raw_codec_to_nal get pps,len=%d,count=%d", u32PpsLen,pstAvcCfgSet->u32Count);
    pu8Tmp += u32PpsLen;
    u32CfgDataLen -= u32PpsLen;
  }

  bRet = TRUE;

EXIT:
  if(FALSE == bRet){
    for(guint32 i = 0; i < pstAvcCfgSet->u32Count; i++){
      if(pstAvcCfgSet->pstItem[i]){
        g_free(pstAvcCfgSet->pstItem[i]);
        pstAvcCfgSet->pstItem[i] = NULL;
      }
    }
    pstAvcCfgSet->u32Count = 0;
  }
  GST_INFO("gst_omx_h264_dec_raw_codec_to_nal out,bRet=%d, count=%d", (gint32)bRet, pstAvcCfgSet->u32Count);

  return bRet;
}



// For AVC, NalUnitSizeLen == 2 or NalUnitSizeLen == 1:
// 1) replace NAL unit size bytes with 0x0000 0001
// 2) copy frame
static gboolean gst_omx_h264_dec_handle_nal_header(const guint8 u8NalUnitSizeLen,
                                      guint8 *pu8DataSrc,
                                      guint32 u32LenSrc,
                                      guint32 u32MaxLenDst,
                                      guint8 *pu8DataDst,
                                      guint32 *pu32LenDst)
{
  guint32 u32Idx = 0;
  guint32 u32Idx_in_buf = 0;

  if((NULL == pu8DataSrc) || (u32LenSrc <= SME_AVC_NAL_HEAD_LEN)){
    GST_WARNING("parameter invalid: pu8DataSrc is %p, u32LenSrc=%d", pu8DataSrc, u32LenSrc);
    return FALSE;
  }

  if((u8NalUnitSizeLen != SME_AVC_NAL_SIZE_LEN_2)
        && (u8NalUnitSizeLen != SME_AVC_NAL_SIZE_LEN_1)){
    GST_WARNING("u8NalUnitSizeLen=%d is invalid", u8NalUnitSizeLen);
    return FALSE;
  }

/*
  //if begin with 0x0000 0001, copy frame.
  if(SME_HAS_AVC_NAL(pu8DataSrc)){
    //copy Frame
    memcpy(pu8DataDst, pu8DataSrc, (guint32)u32LenSrc);
    *pu32LenDst = u32LenSrc;
    return TRUE;
  }
*/

  while((u32Idx + u8NalUnitSizeLen ) < u32LenSrc)
  {
    guint8* pu8Temp = &pu8DataSrc[u32Idx];
    guint32 u32FrameLen;

    if (u8NalUnitSizeLen == SME_AVC_NAL_SIZE_LEN_2) {
        u32FrameLen = SME_GET_UINT_FOR_BGE_2(pu8Temp);
    } else {
        u32FrameLen = pu8Temp[0];
    }

    if(0 == u32FrameLen)
        break;

    //ICS_LOGI("u8NalUnitSizeLen=%d, u32FrameLen=%u, u32LenSrc=%u",
    //    u8NalUnitSizeLen, u32FrameLen, u32LenSrc);

    if((u32Idx + u8NalUnitSizeLen + u32FrameLen) > u32LenSrc){
      GST_WARNING("invalid len, u32FrameLen=%d, u32LenSrc=%d", u32FrameLen, u32LenSrc);
      return FALSE;
    }

    if((u32Idx_in_buf + SME_AVC_NAL_HEAD_LEN + u32FrameLen) > u32MaxLenDst){
      GST_WARNING("invalid len, u32FrameLen=%d, u32MaxLenDst=%d", u32FrameLen, u32MaxLenDst);
      return FALSE;
    }

    pu8DataDst[u32Idx_in_buf] = 0;
    pu8DataDst[u32Idx_in_buf + 1] = 0;
    pu8DataDst[u32Idx_in_buf + 2] = 0;
    pu8DataDst[u32Idx_in_buf + 3] = 1;

    //copy Frame
    memcpy(
        &(pu8DataDst[u32Idx_in_buf + SME_AVC_NAL_HEAD_LEN]),
        &(pu8Temp[u32Idx + u8NalUnitSizeLen]), (guint32)u32FrameLen);

    u32Idx_in_buf += (SME_AVC_NAL_HEAD_LEN + u32FrameLen);
    u32Idx += (u8NalUnitSizeLen + u32FrameLen);
  }

  if (u32Idx_in_buf > 0){
    *pu32LenDst = u32Idx_in_buf;
    return TRUE;
  }

  return FALSE;
}

static GstFlowReturn
gst_omx_h264_dec_handle_frame (GstOMXVideoDec * self,
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
    gst_buffer_map (frame->input_buffer, &info, GST_MAP_READ);

    if(self->u8NalUnitSizeLen == SME_AVC_NAL_SIZE_LEN_1
        || self->u8NalUnitSizeLen == SME_AVC_NAL_SIZE_LEN_2){
      i32ExtHdSize = 1024;
      pu8RawData = (guint8*)g_malloc(info.size + i32ExtHdSize + 3);

      if(NULL == pu8RawData){
        GST_WARNING("no memory,malloc pu8RawData failed");
        break;
      }

      //if begin with 0x0000 0001, return  directly.
      if(SME_HAS_AVC_NAL(info.data)){
        break;
      }

      if (!gst_omx_h264_dec_handle_nal_header(self->u8NalUnitSizeLen, info.data, info.size,
          (guint32)(i32ExtHdSize + info.size), pu8RawData, &u32RawDataLen)){
        GST_WARNING("gst_omx_h264_dec_handle_nal_header failed");
        gst_buffer_unmap (frame->input_buffer, &info);
        g_free(pu8RawData);
        break;
      }

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
    }else{
      gst_omx_h264_dec_add_nal_header(info.data, info.size);
      gst_buffer_unmap (frame->input_buffer, &info);
    }
  }while(FALSE);

  ret = GST_VIDEO_DECODER_CLASS(gst_omx_h264_dec_parent_class)->handle_frame(GST_VIDEO_DECODER (self), frame);

  return ret;
}

static void gst_omx_h264_dec_add_nal_header(guint8* pu8Data, guint32 u32Len)
{
    gst_omx_video_dec_add_nal_header(pu8Data, u32Len);

    return;
}



