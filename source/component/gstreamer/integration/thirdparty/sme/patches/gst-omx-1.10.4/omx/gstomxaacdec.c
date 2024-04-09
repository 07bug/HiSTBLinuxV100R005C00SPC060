/*
 * Copyright (C) 2014, Sebastian Dröge <sebastian@centricular.com>
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

#include "gstomxaacdec.h"

GST_DEBUG_CATEGORY_STATIC (gst_omx_aac_dec_debug_category);
#define GST_CAT_DEFAULT gst_omx_aac_dec_debug_category

/* prototypes */
static gboolean gst_omx_aac_dec_set_format (GstOMXAudioDec * dec,
    GstOMXPort * port, GstCaps * caps);
static gboolean gst_omx_aac_dec_is_format_change (GstOMXAudioDec * dec,
    GstOMXPort * port, GstCaps * caps);
static gint gst_omx_aac_dec_get_samples_per_frame (GstOMXAudioDec * dec,
    GstOMXPort * port);
static gboolean gst_omx_aac_dec_get_channel_positions (GstOMXAudioDec * dec,
    GstOMXPort * port, GstAudioChannelPosition position[OMX_AUDIO_MAXCHANNELS]);

#ifdef FIX_ADD_HEADER
static  gboolean gst_omx_aac_dec_check_need_header (GstOMXAudioDec * self, OMX_U8 * buf, OMX_U32 len, OMX_U8 ** header_buf, OMX_U32 *header_len);
static  OMX_U32 gst_omx_aac_dec_get_header_len (GstOMXAudioDec * self, OMX_U8 * buf, OMX_U32 len);
#endif

/* class initialization */

#define DEBUG_INIT \
  GST_DEBUG_CATEGORY_INIT (gst_omx_aac_dec_debug_category, "omxaacdec", 0, \
      "debug category for gst-omx aac audio decoder");

G_DEFINE_TYPE_WITH_CODE (GstOMXAACDec, gst_omx_aac_dec,
    GST_TYPE_OMX_AUDIO_DEC, DEBUG_INIT);

static void
gst_omx_aac_dec_class_init (GstOMXAACDecClass * klass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
  GstOMXAudioDecClass *audiodec_class = GST_OMX_AUDIO_DEC_CLASS (klass);

  audiodec_class->set_format = GST_DEBUG_FUNCPTR (gst_omx_aac_dec_set_format);
  audiodec_class->is_format_change =
      GST_DEBUG_FUNCPTR (gst_omx_aac_dec_is_format_change);
  audiodec_class->get_samples_per_frame =
      GST_DEBUG_FUNCPTR (gst_omx_aac_dec_get_samples_per_frame);
  audiodec_class->get_channel_positions =
      GST_DEBUG_FUNCPTR (gst_omx_aac_dec_get_channel_positions);
#ifdef FIX_ADD_HEADER
  audiodec_class->check_need_header = GST_DEBUG_FUNCPTR(gst_omx_aac_dec_check_need_header);
  audiodec_class->get_header_len    = GST_DEBUG_FUNCPTR(gst_omx_aac_dec_get_header_len);
#endif

#if defined SME_GST_OMX
  /**< hisi aac decoder doesn't support raw and adif */
  audiodec_class->cdata.default_sink_template_caps = "audio/mpeg, "
      "mpegversion=(int){2, 4}, "
      "stream-format=(string) { raw, adts, adif, loas }, "
      "rate=(int)[8000,96000], "
      "channels=(int)[1,9]";
#else
  audiodec_class->cdata.default_sink_template_caps = "audio/mpeg, "
      "mpegversion=(int){2, 4}, "
      "stream-format=(string) { raw, adts, adif, loas }, "
      "rate=(int)[8000,48000], "
      "channels=(int)[1,9], " "framed=(boolean) true";
#endif

  gst_element_class_set_static_metadata (element_class,
      "OpenMAX AAC Audio Decoder",
      "Codec/Decoder/Audio",
      "Decode AAC audio streams",
      "Sebastian Dröge <sebastian@centricular.com>");

  gst_omx_set_default_role (&audiodec_class->cdata, "audio_decoder.aac");
}

static void
gst_omx_aac_dec_init (GstOMXAACDec * self)
{
  /* FIXME: Other values exist too! */
  self->spf = 1024;
}

static gboolean
gst_omx_aac_dec_set_format (GstOMXAudioDec * dec, GstOMXPort * port,
    GstCaps * caps)
{
  GstOMXAACDec *self = GST_OMX_AAC_DEC (dec);
  OMX_PARAM_PORTDEFINITIONTYPE port_def;
  OMX_AUDIO_PARAM_AACPROFILETYPE aac_param;
  OMX_ERRORTYPE err;
  GstStructure *s;
  gint rate, channels, mpegversion;
  const gchar *stream_format;

  gst_omx_port_get_port_definition (port, &port_def);
  port_def.format.audio.eEncoding = OMX_AUDIO_CodingAAC;
  err = gst_omx_port_update_port_definition (port, &port_def);
  if (err != OMX_ErrorNone) {
    GST_ERROR_OBJECT (self,
        "Failed to set AAC format on component: %s (0x%08x)",
        gst_omx_error_to_string (err), err);
    return FALSE;
  }

  GST_OMX_INIT_STRUCT (&aac_param);
  aac_param.nPortIndex = port->index;

  err =
      gst_omx_component_get_parameter (dec->dec, OMX_IndexParamAudioAac,
      &aac_param);
  if (err != OMX_ErrorNone) {
    GST_ERROR_OBJECT (self,
        "Failed to get AAC parameters from component: %s (0x%08x)",
        gst_omx_error_to_string (err), err);
    return FALSE;
  }

  s = gst_caps_get_structure (caps, 0);

  if (!gst_structure_get_int (s, "mpegversion", &mpegversion) ||
      !gst_structure_get_int (s, "rate", &rate) ||
      !gst_structure_get_int (s, "channels", &channels)) {
    GST_ERROR_OBJECT (self, "Incomplete caps");
    return FALSE;
  }

  stream_format = gst_structure_get_string (s, "stream-format");
  if (!stream_format) {
    GST_ERROR_OBJECT (self, "Incomplete caps");
    return FALSE;
  }

  aac_param.nChannels = channels;
  aac_param.nSampleRate = rate;
  aac_param.nBitRate = 0;       /* unknown */
  aac_param.nAudioBandWidth = 0;        /* decoder decision */
  aac_param.eChannelMode = 0;   /* FIXME */
  if (mpegversion == 2)
    aac_param.eAACStreamFormat = OMX_AUDIO_AACStreamFormatMP2ADTS;
  else if (strcmp (stream_format, "adts") == 0)
    aac_param.eAACStreamFormat = OMX_AUDIO_AACStreamFormatMP4ADTS;
  else if (strcmp (stream_format, "loas") == 0)
    aac_param.eAACStreamFormat = OMX_AUDIO_AACStreamFormatMP4LOAS;
  else if (strcmp (stream_format, "adif") == 0)
    aac_param.eAACStreamFormat = OMX_AUDIO_AACStreamFormatADIF;
  else if (strcmp (stream_format, "raw") == 0) {
#ifdef FIX_ADD_HEADER
    const GValue *codec_data = gst_structure_get_value (s, "codec_data");
    if (codec_data) {
      GstBuffer * codec_data_buffer;
      GstMapInfo minfo;

      codec_data_buffer = gst_value_get_buffer (codec_data);
      gst_buffer_map (codec_data_buffer, &minfo, GST_MAP_READ);
      if (minfo.size <= sizeof(self->extradata)) {
          memcpy(self->extradata,minfo.data,minfo.size);
          self->extradata_size = minfo.size;
      } else {
      }
      gst_buffer_unmap (codec_data_buffer, &minfo);
    }

    aac_param.eAACStreamFormat = OMX_AUDIO_AACStreamFormatMP4ADTS;
    self->bNeedAdtsHeader = TRUE;
    if (self->extradata_size <= 0) {
        GST_WARNING_OBJECT (self, "codec_data error, maybe can't add correct adts header!");
    }
#else
    aac_param.eAACStreamFormat = OMX_AUDIO_AACStreamFormatRAW;
#endif
  }
  else {
    GST_ERROR_OBJECT (self, "Unexpected format: %s", stream_format);
    return FALSE;
  }

#ifdef FIX_ADD_HEADER
  self->channels    = aac_param.nChannels;
  self->sample_rate = aac_param.nSampleRate;
#endif

  err =
      gst_omx_component_set_parameter (dec->dec, OMX_IndexParamAudioAac,
      &aac_param);
  if (err != OMX_ErrorNone) {
    GST_ERROR_OBJECT (self, "Error setting AAC parameters: %s (0x%08x)",
        gst_omx_error_to_string (err), err);
    return FALSE;
  }

  return TRUE;
}

static gboolean
gst_omx_aac_dec_is_format_change (GstOMXAudioDec * dec, GstOMXPort * port,
    GstCaps * caps)
{
  GstOMXAACDec *self = GST_OMX_AAC_DEC (dec);
  OMX_AUDIO_PARAM_AACPROFILETYPE aac_param;
  OMX_ERRORTYPE err;
  GstStructure *s;
  gint rate, channels, mpegversion;
  const gchar *stream_format;

  GST_OMX_INIT_STRUCT (&aac_param);
  aac_param.nPortIndex = port->index;

  err =
      gst_omx_component_get_parameter (dec->dec, OMX_IndexParamAudioAac,
      &aac_param);
  if (err != OMX_ErrorNone) {
    GST_ERROR_OBJECT (self,
        "Failed to get AAC parameters from component: %s (0x%08x)",
        gst_omx_error_to_string (err), err);
    return FALSE;
  }

  s = gst_caps_get_structure (caps, 0);

  if (!gst_structure_get_int (s, "mpegversion", &mpegversion) ||
      !gst_structure_get_int (s, "rate", &rate) ||
      !gst_structure_get_int (s, "channels", &channels)) {
    GST_ERROR_OBJECT (self, "Incomplete caps");
    return FALSE;
  }

  stream_format = gst_structure_get_string (s, "stream-format");
  if (!stream_format) {
    GST_ERROR_OBJECT (self, "Incomplete caps");
    return FALSE;
  }

  if (aac_param.nChannels != channels)
    return TRUE;

  if (aac_param.nSampleRate != rate)
    return TRUE;

  if (mpegversion == 2
      && aac_param.eAACStreamFormat != OMX_AUDIO_AACStreamFormatMP2ADTS)
    return TRUE;
  if (aac_param.eAACStreamFormat == OMX_AUDIO_AACStreamFormatMP4ADTS &&
      strcmp (stream_format, "adts") != 0)
    return TRUE;
  if (aac_param.eAACStreamFormat == OMX_AUDIO_AACStreamFormatMP4LOAS &&
      strcmp (stream_format, "loas") != 0)
    return TRUE;
  if (aac_param.eAACStreamFormat == OMX_AUDIO_AACStreamFormatADIF &&
      strcmp (stream_format, "adif") != 0)
    return TRUE;
#ifdef FIX_ADD_HEADER
  if (aac_param.eAACStreamFormat == OMX_AUDIO_AACStreamFormatMP4ADTS &&
      strcmp (stream_format, "raw") != 0)
    return TRUE;
#else
  if (aac_param.eAACStreamFormat == OMX_AUDIO_AACStreamFormatRAW &&
      strcmp (stream_format, "raw") != 0)
    return TRUE;
#endif

  return FALSE;
}

static gint
gst_omx_aac_dec_get_samples_per_frame (GstOMXAudioDec * dec, GstOMXPort * port)
{
  return GST_OMX_AAC_DEC (dec)->spf;
}

static gboolean
gst_omx_aac_dec_get_channel_positions (GstOMXAudioDec * dec,
    GstOMXPort * port, GstAudioChannelPosition position[OMX_AUDIO_MAXCHANNELS])
{
  OMX_AUDIO_PARAM_PCMMODETYPE pcm_param;
  OMX_ERRORTYPE err;

  GST_OMX_INIT_STRUCT (&pcm_param);
  pcm_param.nPortIndex = port->index;
  err =
      gst_omx_component_get_parameter (dec->dec, OMX_IndexParamAudioPcm,
      &pcm_param);
  if (err != OMX_ErrorNone) {
    GST_ERROR_OBJECT (dec, "Failed to get PCM parameters: %s (0x%08x)",
        gst_omx_error_to_string (err), err);
    return FALSE;
  }

  /* FIXME: Rather arbitrary values here, based on what we do in gstfaac.c */
  switch (pcm_param.nChannels) {
    case 1:
      position[0] = GST_AUDIO_CHANNEL_POSITION_MONO;
      break;
    case 2:
      position[0] = GST_AUDIO_CHANNEL_POSITION_FRONT_LEFT;
      position[1] = GST_AUDIO_CHANNEL_POSITION_FRONT_RIGHT;
      break;
    case 3:
      position[0] = GST_AUDIO_CHANNEL_POSITION_FRONT_CENTER;
      position[1] = GST_AUDIO_CHANNEL_POSITION_FRONT_LEFT;
      position[2] = GST_AUDIO_CHANNEL_POSITION_FRONT_RIGHT;
      break;
    case 4:
      position[0] = GST_AUDIO_CHANNEL_POSITION_FRONT_CENTER;
      position[1] = GST_AUDIO_CHANNEL_POSITION_FRONT_LEFT;
      position[2] = GST_AUDIO_CHANNEL_POSITION_FRONT_RIGHT;
      position[3] = GST_AUDIO_CHANNEL_POSITION_REAR_CENTER;
      break;
    case 5:
      position[0] = GST_AUDIO_CHANNEL_POSITION_FRONT_CENTER;
      position[1] = GST_AUDIO_CHANNEL_POSITION_FRONT_LEFT;
      position[2] = GST_AUDIO_CHANNEL_POSITION_FRONT_RIGHT;
      position[3] = GST_AUDIO_CHANNEL_POSITION_REAR_LEFT;
      position[4] = GST_AUDIO_CHANNEL_POSITION_REAR_RIGHT;
      break;
    case 6:
      position[0] = GST_AUDIO_CHANNEL_POSITION_FRONT_CENTER;
      position[1] = GST_AUDIO_CHANNEL_POSITION_FRONT_LEFT;
      position[2] = GST_AUDIO_CHANNEL_POSITION_FRONT_RIGHT;
      position[3] = GST_AUDIO_CHANNEL_POSITION_REAR_LEFT;
      position[4] = GST_AUDIO_CHANNEL_POSITION_REAR_RIGHT;
      position[5] = GST_AUDIO_CHANNEL_POSITION_LFE1;
      break;
    default:
      return FALSE;
  }

  return TRUE;
}

#ifdef FIX_ADD_HEADER
static void gst_omx_aac_write_adts_header (OMX_U8 *pAdtsHeader,
                          OMX_U32 ui32Id,
                          OMX_U32 ui32Profile,
                          OMX_U32 ui32SampleRate,
                          OMX_U32 ui32ChannelConfig,
                          OMX_U32 ui32FrameLen,
                          OMX_U8 *pExtraData,
                          OMX_S32 i32ExtraDataSize)
{
    OMX_U32 ui32SampRateIdx = 0;
    OMX_U32 ui32FsIdx = 0, ui32ObjType = 0, ui32ChanConf = 0;

    /* parse audio specific configure and get related information */
    if (pExtraData != NULL && i32ExtraDataSize > 1)
    {
        OMX_U8 *pBuf = pExtraData;
        ui32ObjType = (pBuf[0] & 0xf8) >> 3;
        if (ui32ObjType == 0x1f)
        {
            GST_DEBUG("Unsupported, escaped object type");
        }
        if (ui32ObjType < 4)
        {
            ui32Profile = ui32ObjType - 1;
        }

        ui32FsIdx = ((pBuf[0] & 0x7) << 1) | ((pBuf[1] & 0x80) >> 7);
        if (ui32FsIdx == 0xf)
        {
            GST_DEBUG("Unsupported, escaped sample rate index");
        }

        if (ui32FsIdx != 0xf)
        {
            ui32SampRateIdx = ui32FsIdx;
        }
        ui32ChanConf = (pBuf[1] & 0x78) >> 3;
        if (ui32ChanConf <= 8)
        {
            ui32ChannelConfig = ui32ChanConf;
        }
    }

    if (ui32SampRateIdx == 0)
    {
        /* get sample rate index */
        switch (ui32SampleRate)
        {
            case 96000:
                ui32SampRateIdx = 0;
                break;
            case 882000:
                ui32SampRateIdx = 1;
                break;
            case 64000:
                ui32SampRateIdx = 2;
                break;
            case 48000:
                ui32SampRateIdx = 3;
                break;
            case 44100:
                ui32SampRateIdx = 4;
                break;
            case 32000:
                ui32SampRateIdx = 5;
                break;
            case 24000:
                ui32SampRateIdx = 6;
                break;
            case 22050:
                ui32SampRateIdx = 7;
                break;
            case 16000:
                ui32SampRateIdx = 8;
                break;
            case 12000:
                ui32SampRateIdx = 9;
                break;
            case 11025:
                ui32SampRateIdx = 10;
                break;
            case 8000:
                ui32SampRateIdx = 11;
                break;
            default:
                ui32SampRateIdx = 15;
                break;
        }
    }

    /* Sync point over a full byte */
    pAdtsHeader[0] = 0xFF;
    pAdtsHeader[1] = 0xF0;
    /* ID */
    pAdtsHeader[1] |= (ui32Id & 0x1) << 3;
    /* layer and protection bit, fix it to 00b and 1b */
    pAdtsHeader[1] |= 0x01;
    /* profile over first 2 bits */
    pAdtsHeader[2] = (ui32Profile & 0x3) << 6;
    /* rate index over next 4 bits */
    pAdtsHeader[2] |= (ui32SampRateIdx & 0xf) << 2;
    /* channels over last 2 bits */
    pAdtsHeader[2] |= (ui32ChannelConfig & 0x4) >> 2;
    /* channels continued over next 2 bits + 4 bits at zero */
    pAdtsHeader[3] = (ui32ChannelConfig & 0x3) << 6;
    /* frame size over last 2 bits */
    pAdtsHeader[3] |= (ui32FrameLen & 0x1800) >> 11;
    /* frame size continued over full byte */
    pAdtsHeader[4] = (ui32FrameLen & 0x7F8) >> 3;
    /* frame size continued first 3 bits */
    pAdtsHeader[5] = (ui32FrameLen & 0x7) << 5;
    /* buffer fullness (0x7FF for VBR) over 5 last bits */
    pAdtsHeader[5] |= 0x1F;
    /* buffer fullness (0x7FF for VBR) continued over 6 first bits + 2 zeros for
     * number of raw data blocks */
    pAdtsHeader[6] = 0xFC;

//  pAdtsHeader[6] |= 0x1;

    return;
}

static  OMX_U32 gst_omx_aac_dec_get_header_len (GstOMXAudioDec * self, OMX_U8 * buf, OMX_U32 len)
{
    OMX_U32 header_len = 0;
    GstOMXAACDec *aac_self ;

    if (!self || !buf || len < 2) {
        return header_len;
    }

    aac_self = GST_OMX_AAC_DEC (self);

    if (aac_self->bNeedAdtsHeader && (buf[0] != 0xff || (buf[1] & 0xf0) != 0xf0))
    {
        header_len = ADTS_HEADER_LEN;
    }

    return header_len;
}

static  gboolean gst_omx_aac_dec_check_need_header (GstOMXAudioDec * self, OMX_U8 * buf, OMX_U32 len, OMX_U8 ** header_buf, OMX_U32 *header_len)
{
    gboolean bNeedAdtsHeader = FALSE;
    GstOMXAACDec *aac_self ;

    if (!self || !buf || len < 2 || !header_buf || !header_len) {
        return bNeedAdtsHeader;
    }

    aac_self = GST_OMX_AAC_DEC (self);

    if (aac_self->bNeedAdtsHeader && (buf[0] != 0xff || (buf[1] & 0xf0) != 0xf0))
    {
        bNeedAdtsHeader = TRUE;
        gst_omx_aac_write_adts_header(aac_self->adts_header,
            0, /* mpeg2 */
            1, /* LC profile */
            aac_self->sample_rate,
            aac_self->channels,
            len+ADTS_HEADER_LEN,
            aac_self->extradata,
            aac_self->extradata_size);
        *header_buf = aac_self->adts_header;
        *header_len = ADTS_HEADER_LEN;
    } else {
        *header_buf = NULL;
        *header_len = 0;
    }

    return bNeedAdtsHeader;
}
#endif
