#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include "gstomxddpdec.h"

#if defined (GST_OMX_DDP_DEC_ENABLE)
#include "OMX_Audio_Hisi.h"
#include "OMX_AudioExt.h"

GST_DEBUG_CATEGORY_STATIC (gst_omx_ddp_dec_debug_category);
#define GST_CAT_DEFAULT gst_omx_ddp_dec_debug_category

/* prototypes */
static gboolean gst_omx_ddp_dec_set_format (GstOMXAudioDec * dec,
                                            GstOMXPort * port, GstCaps * caps);
static gboolean gst_omx_ddp_dec_is_format_change (GstOMXAudioDec * dec,
                                                  GstOMXPort * port, GstCaps * caps);
static gint gst_omx_ddp_dec_get_samples_per_frame (GstOMXAudioDec * dec,
                                                   GstOMXPort * port);
static gboolean gst_omx_ddp_dec_get_channel_positions (GstOMXAudioDec * dec,
                                                       GstOMXPort * port, GstAudioChannelPosition position[OMX_AUDIO_MAXCHANNELS]);

/* class initialization */

#define DEBUG_INIT                                                      \
    GST_DEBUG_CATEGORY_INIT (gst_omx_ddp_dec_debug_category, "omxddpdec", 0, \
                             "debug category for gst-omx ddp audio decoder");

G_DEFINE_TYPE_WITH_CODE (GstOMXDDPDec, gst_omx_ddp_dec,
                         GST_TYPE_OMX_AUDIO_DEC, DEBUG_INIT);


static void
gst_omx_ddp_dec_class_init (GstOMXDDPDecClass * klass)
{
    GstElementClass *element_class = GST_ELEMENT_CLASS (klass);
    GstOMXAudioDecClass *audiodec_class = GST_OMX_AUDIO_DEC_CLASS (klass);

    audiodec_class->set_format = GST_DEBUG_FUNCPTR (gst_omx_ddp_dec_set_format);
    audiodec_class->is_format_change =
        GST_DEBUG_FUNCPTR (gst_omx_ddp_dec_is_format_change);
    audiodec_class->get_samples_per_frame =
        GST_DEBUG_FUNCPTR (gst_omx_ddp_dec_get_samples_per_frame);
    audiodec_class->get_channel_positions =
        GST_DEBUG_FUNCPTR (gst_omx_ddp_dec_get_channel_positions);
    audiodec_class->cdata.default_sink_template_caps =
        "audio/x-ac3, "
        "rate=(int)[32000,48000], "
        "channels=(int)[1,6];"
        "audio/x-eac3, "
        "rate=(int)[32000,48000], "
        "channels=(int)[1,8]";

    gst_element_class_set_static_metadata (element_class,
                                           "OpenMAX DDP Audio Decoder",
                                           "Codec/Decoder/Audio",
                                           "Decode DDP audio streams",
                                           "anonymous author");

    gst_omx_set_default_role (&audiodec_class->cdata, "audio_decoder.ddp");
}

static void
gst_omx_ddp_dec_init (GstOMXDDPDec * self)
{
    self->spf = -1;
}

static gboolean
gst_omx_ddp_dec_set_format (GstOMXAudioDec * dec, GstOMXPort * port,
                            GstCaps * caps)
{
    GstOMXDDPDec *self = GST_OMX_DDP_DEC (dec);
    OMX_PARAM_PORTDEFINITIONTYPE port_def;
    OMX_HA_PARAM_DOLBYTYPE ddp_param;
    OMX_ERRORTYPE err;
    GstStructure *s;
    gint rate, channels;

    gst_omx_port_get_port_definition (port, &port_def);
//#ifdef __HI3796MV100__
#if 1
    port_def.format.audio.eEncoding = OMX_AUDIO_CodingAndroidEAC3;
#else
    port_def.format.audio.eEncoding = OMX_AUDIO_CodingDDP;
#endif
    err = gst_omx_port_update_port_definition (port, &port_def);
    if (err != OMX_ErrorNone) {
        GST_ERROR_OBJECT (self,
                          "Failed to set DDP format on component: %s (0x%08x)",
                          gst_omx_error_to_string (err), err);
        return FALSE;
    }

    GST_OMX_INIT_STRUCT (&ddp_param);
    ddp_param.nPortIndex = port->index;

    err =
        gst_omx_component_get_parameter (dec->dec, OMX_HA_IndexParamAudioDolby,
                                         &ddp_param);
    if (err != OMX_ErrorNone) {
        GST_ERROR_OBJECT (self,
                          "Failed to get DDP parameters from component: "
                          "%s (0x%08x)",
                          gst_omx_error_to_string (err), err);
        return FALSE;
    }

    s = gst_caps_get_structure (caps, 0);

    if (!gst_structure_get_int (s, "rate", &rate) ||
        !gst_structure_get_int (s, "channels", &channels)) {
        GST_ERROR_OBJECT (self, "Incomplete caps");
        return FALSE;
    }

    ddp_param.nChannels = channels;
    ddp_param.nBitRate = 0;       /* unknown */
    ddp_param.nSampleRate = rate;

    /** TODO: other parameters such as DRC may need to be set */

    err =
        gst_omx_component_set_parameter (dec->dec, OMX_HA_IndexParamAudioDolby,
                                         &ddp_param);
    if (err != OMX_ErrorNone) {
        GST_ERROR_OBJECT (self, "Error setting DDP parameters: %s (0x%08x)",
                          gst_omx_error_to_string (err), err);
        return FALSE;
    }

    return TRUE;
}

static gboolean
gst_omx_ddp_dec_is_format_change (GstOMXAudioDec * dec, GstOMXPort * port,
                                  GstCaps * caps)
{
    GstOMXDDPDec *self = GST_OMX_DDP_DEC (dec);
    OMX_HA_PARAM_DOLBYTYPE ddp_param;
    OMX_ERRORTYPE err;
    GstStructure *s;
    gint rate, channels;

    GST_OMX_INIT_STRUCT (&ddp_param);
    ddp_param.nPortIndex = port->index;

    err =
        gst_omx_component_get_parameter (dec->dec, OMX_HA_IndexParamAudioDolby,
                                         &ddp_param);
    if (err != OMX_ErrorNone) {
        GST_ERROR_OBJECT (self,
                          "Failed to get DDP parameters from component: "
                          "%s (0x%08x)",
                          gst_omx_error_to_string (err), err);
        return FALSE;
    }

    s = gst_caps_get_structure (caps, 0);

    if (!gst_structure_get_int (s, "rate", &rate) ||
        !gst_structure_get_int (s, "channels", &channels)) {
        GST_ERROR_OBJECT (self, "Incomplete caps");
        return FALSE;
    }

    if (ddp_param.nChannels != channels)
        return TRUE;

    if (ddp_param.nSampleRate != rate)
        return TRUE;

    return FALSE;
}

static gint
gst_omx_ddp_dec_get_samples_per_frame (GstOMXAudioDec * dec, GstOMXPort * port)
{
    return GST_OMX_DDP_DEC (dec)->spf;
}

static gboolean
gst_omx_ddp_dec_get_channel_positions (GstOMXAudioDec * dec,
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

    switch (pcm_param.nChannels) {
        case 1:
            position[0] = GST_AUDIO_CHANNEL_POSITION_MONO;
            break;
        case 2:
            position[0] = GST_AUDIO_CHANNEL_POSITION_FRONT_LEFT;
            position[1] = GST_AUDIO_CHANNEL_POSITION_FRONT_RIGHT;
            break;
        default:
            return FALSE;
    }

    return TRUE;
}

#endif
