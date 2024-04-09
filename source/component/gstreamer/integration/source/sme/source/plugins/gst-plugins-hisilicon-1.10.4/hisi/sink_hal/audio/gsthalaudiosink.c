/*
 * GStreamer - HalAudio sink
 * gsthalaudiosink.c:
 */

/**
 * SECTION:element-halaudiosink
 *
 * halaudiosink is an audio sink designed to work with the Hisi HiHal
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch-1.0 audiotestsrc volume=0.5 ! halaudiosink
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <fcntl.h>
#include <string.h>
#include <stropts.h>
#include <unistd.h>
#include <sys/mman.h>

#include "gsthalaudiosink.h"

#include "securec.h"
#include "tvos_hal_aout.h"
#include "tvos_hal_type.h"

//GST_DEBUG_CATEGORY_EXTERN (halaudio_debug);
#define GST_CAT_DEFAULT gst_smeaudiosink_hihal_debug

#define GST_SMEAUDIOSINK_HIHAL_NAME "smeaudiosink_hihal"
GST_DEBUG_CATEGORY_STATIC (gst_smeaudiosink_hihal_debug);

#define _do_init \
        GST_DEBUG_CATEGORY_INIT (gst_smeaudiosink_hihal_debug,  \
                                 GST_SMEAUDIOSINK_HIHAL_NAME,   \
                                 0, "smehisihalaudiosink element");

#define TIMEOUT_CNT 64
#define DEFAULT_SAMPLERATE 48000
#define DEFAULT_CHANNEL 2
#define AOUT_TRACK_BUFFER_MS 300 //300ms

#define UTILS_MSAFEFREE(p) \
    if(NULL != p)\
{\
    free(p);\
    p = NULL;\
}

typedef enum _MemSecureRet
{
    E_MEM_OK = 0,
    E_MEM_ERANGE = 34,
    E_MEM_EINVAL = 22,
    E_MEM_EINVAL_AND_RESET = 150,
    E_MEM_ERANGE_AND_RESET = 162,
    E_MEM_EOVERLAP_AND_RESET = 182,
} E_MEM_SECURE_RET;

typedef struct _tag_SME_AUDIO_OUT_HDL_INFO
{
    AOUT_DEVICE_S *pstAoutdev;
    HANDLE psthAout;
    HANDLE psthTrack;
    AOUT_TRACK_PARAMS_S stParams;
    gboolean bStop;
    gboolean bOpen;
    guint32 u32Align;
} ST_SME_AUDIO_OUT_HDL_INFO, *PST_SME_AUDIO_OUT_HDL_INFO;

static void gst_halaudiosink_base_init (gpointer g_class);
static void gst_halaudiosink_class_init (GstHalAudioSinkClass * klass);
static void gst_halaudiosink_init (GstHalAudioSink * filter);
static void gst_halaudiosink_dispose (GObject * object);
static void gst_halaudiosink_finalize (GObject * object);

static void gst_halaudiosink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_halaudiosink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);

static GstCaps *gst_halaudiosink_getcaps (GstBaseSink * bsink);

static gboolean gst_halaudiosink_open (GstAudioSink * asink);
static gboolean gst_halaudiosink_close (GstAudioSink * asink);
static gboolean gst_halaudiosink_prepare (GstAudioSink * asink,
    GstAudioRingBufferSpec * spec);
static gboolean gst_halaudiosink_unprepare (GstAudioSink * asink);
static guint gst_halaudiosink_write (GstAudioSink * asink, gpointer data,
    guint length);
static guint gst_halaudiosink_delay (GstAudioSink * asink);
static void gst_halaudiosink_reset (GstAudioSink * asink);

static GstStaticPadTemplate gst_halaudiosink_factory =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("audio/x-raw, "
        "format = (string) { S16LE }, "
        "layout = (string) interleaved, "
        "rate = (int) [ 1, MAX ], " "channels = (int) [ 1, MAX ]; "
        )
    );

static GstElementClass *parent_class = NULL;

gboolean gst_smeaudiosink_hihal_register (GstPlugin * plugin);

GType
gst_halaudiosink_get_type (void)
{
  static GType plugin_type = 0;

  if (!plugin_type) {
    static const GTypeInfo plugin_info = {
      sizeof (GstHalAudioSinkClass),
      gst_halaudiosink_base_init,
      NULL,
      (GClassInitFunc) gst_halaudiosink_class_init,
      NULL,
      NULL,
      sizeof (GstHalAudioSink),
      0,
      (GInstanceInitFunc) gst_halaudiosink_init,
    };

    plugin_type = g_type_register_static (GST_TYPE_AUDIO_SINK,
        "GstHalAudioSink", &plugin_info, 0);
  }
  return plugin_type;
}

//register
gboolean
gst_smeaudiosink_hihal_register (GstPlugin * plugin)
{
    GST_INFO ("registering sme audio hisi hal sink in.");

    if (!gst_element_register (plugin, GST_SMEAUDIOSINK_HIHAL_NAME,
                               GST_RANK_SECONDARY +
                               ((GST_RANK_PRIMARY - GST_RANK_SECONDARY) >> 1),
                               GST_TYPE_HALAUDIO_SINK)) {
        GST_WARNING ("Register of type %s failed", GST_SMEAUDIOSINK_HIHAL_NAME);
        return FALSE;
    }
    GST_INFO ("registering sme audio hisi hal sink out.");

  return TRUE;
}

static void
gst_halaudiosink_dispose (GObject * object)
{
  G_OBJECT_CLASS (parent_class)->dispose (object);
}

static void
gst_halaudiosink_finalize (GObject * object)
{
  GstHalAudioSink *halaudiosink = GST_HALAUDIO_SINK (object);

  g_mutex_free (halaudiosink->write_mutex);
  g_cond_free (halaudiosink->sleep_cond);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
gst_halaudiosink_base_init (gpointer g_class)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (g_class);

  gst_element_class_add_static_pad_template (element_class,
      &gst_halaudiosink_factory);
  gst_element_class_set_static_metadata (element_class,
        "Sme Audio Sink Hisi Hal",
        "Sink/Audio",
        "Sme Audio sink element based on Hisi Hal",
        "SME TEAM ");
}

static void
gst_halaudiosink_class_init (GstHalAudioSinkClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;
  GstBaseSinkClass *gstbasesink_class;
  GstAudioSinkClass *gstaudiosink_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;
  gstbasesink_class = (GstBaseSinkClass *) klass;
  gstaudiosink_class = (GstAudioSinkClass *) klass;

  parent_class = g_type_class_peek_parent (klass);

  gobject_class->dispose = gst_halaudiosink_dispose;
  gobject_class->finalize = gst_halaudiosink_finalize;

  gobject_class->set_property = gst_halaudiosink_set_property;
  gobject_class->get_property = gst_halaudiosink_get_property;

  gstbasesink_class->get_caps = GST_DEBUG_FUNCPTR (gst_halaudiosink_getcaps);

  gstaudiosink_class->open = GST_DEBUG_FUNCPTR (gst_halaudiosink_open);
  gstaudiosink_class->close = GST_DEBUG_FUNCPTR (gst_halaudiosink_close);
  gstaudiosink_class->prepare = GST_DEBUG_FUNCPTR (gst_halaudiosink_prepare);
  gstaudiosink_class->unprepare =
      GST_DEBUG_FUNCPTR (gst_halaudiosink_unprepare);
  gstaudiosink_class->write = GST_DEBUG_FUNCPTR (gst_halaudiosink_write);
  gstaudiosink_class->delay = GST_DEBUG_FUNCPTR (gst_halaudiosink_delay);
  gstaudiosink_class->reset = GST_DEBUG_FUNCPTR (gst_halaudiosink_reset);

}

static void
gst_halaudiosink_init (GstHalAudioSink * halaudiosink)
{
  const char *audiodev;

  GST_DEBUG_OBJECT (halaudiosink, "initializing halaudiosink");


  /* mutex and gcond used to control the write method */
  halaudiosink->write_mutex = g_mutex_new ();
  halaudiosink->sleep_cond = g_cond_new ();
}

static void
gst_halaudiosink_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstHalAudioSink *halaudiosink;

  halaudiosink = GST_HALAUDIO_SINK (object);

  switch (prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_halaudiosink_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstHalAudioSink *halaudiosink;

  halaudiosink = GST_HALAUDIO_SINK (object);

  switch (prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static GstCaps *
gst_halaudiosink_getcaps (GstBaseSink * bsink)
{
  GstPadTemplate *pad_template;
  GstCaps *caps = NULL;
  GstHalAudioSink *halaudiosink = GST_HALAUDIO_SINK (bsink);

  GST_DEBUG_OBJECT (halaudiosink, "getcaps called");

  pad_template = gst_static_pad_template_get (&gst_halaudiosink_factory);
  caps = gst_caps_copy (gst_pad_template_get_caps (pad_template));

  gst_object_unref (pad_template);

  return caps;
}

static gint32
sme_hihal_init_aout_module(AOUT_DEVICE_S **ppstAoutdev)
{
    gint32 i32Ret = SUCCESS;

    *ppstAoutdev = getAOutDevice();

    if (NULL == *ppstAoutdev)
    {
        GST_ERROR("%s device failed to initialize\n",
                      AOUT_HARDWARE_AOUT0);
        i32Ret = -1;
    }

    return i32Ret;
}

static gint32
sme_hihal_deinit_aout_module(const AOUT_DEVICE_S *pstAoutdev)
{
    g_return_val_if_fail((pstAoutdev != NULL), FAILURE);
    return SUCCESS;
}

static void *
sme_hihal_aout_create(void)
{
    PST_SME_AUDIO_OUT_HDL_INFO pstAuOutHdlInfo = NULL;
    AOUT_OPEN_PARAMS_S stOpenParams;
    AOUT_CAPABILITY_S stCapability;
    AOUT_DEVICE_S *pstAoutdev = NULL;
    gint32 i32Ret = FALSE;
    E_MEM_SECURE_RET eMemSecRet = E_MEM_OK;
    //gint32 i = 0;

    pstAuOutHdlInfo = (PST_SME_AUDIO_OUT_HDL_INFO)
        g_malloc(sizeof(ST_SME_AUDIO_OUT_HDL_INFO));
    if (NULL == pstAuOutHdlInfo) {
        GST_ERROR("pstAuOutHdlInfo Malloc Failed!");
        return NULL;
    }

    eMemSecRet = memset_s(pstAuOutHdlInfo, sizeof(ST_SME_AUDIO_OUT_HDL_INFO), 0, sizeof(ST_SME_AUDIO_OUT_HDL_INFO));
    if(eMemSecRet != E_MEM_OK)
    {
        GST_ERROR("memset_s failed:%d", eMemSecRet);
    }

    // load aout module
    GST_INFO("enter sme_hihal_aout_create");
    pstAoutdev = pstAuOutHdlInfo->pstAoutdev;
    i32Ret = sme_hihal_init_aout_module(&pstAoutdev);
    if(SUCCESS != i32Ret)
    {
        GST_ERROR("error, hisi hal aout open failed!");
        UTILS_MSAFEFREE(pstAuOutHdlInfo);
        return NULL;
    }
    pstAuOutHdlInfo->pstAoutdev = pstAoutdev;
    GST_INFO("load aout module success!pstAoutdev:%p",pstAoutdev);

    i32Ret = pstAoutdev->aout_init(NULL, NULL);
    if (SUCCESS != i32Ret)
    {
        GST_ERROR("error, aout init failed!");
        sme_hihal_deinit_aout_module(pstAoutdev);
        UTILS_MSAFEFREE(pstAuOutHdlInfo);
        return NULL;
    }
    GST_INFO("ok, aout init success!");

    //get aout support track num
    i32Ret = pstAoutdev->aout_get_capability(NULL, &stCapability);
    if(SUCCESS != i32Ret)
    {
        GST_ERROR("aout_get_capability failed 0x%x",i32Ret);
        sme_hihal_deinit_aout_module(pstAoutdev);
        pstAoutdev->aout_term(NULL,NULL);
        UTILS_MSAFEFREE(pstAuOutHdlInfo);
        return NULL;
    }

/*
    //for(i = 0; i < stCapability.u8SupportedId; i++)
    for (i = 0; i < stCapability.u8SupportedIdNum; i++)
    {
        GST_ERROR("%d aOutputDevice:%d u8SupportedTrackNum:%d",
                      i,
                      //stCapability.aenOutputDevice[i],
                      stCapability.enOutputDevice[i],
                      stCapability.u8SupportedTrackNum[i]);
    }
*/

    stOpenParams.enId = AOUT_ID_0;
    stOpenParams.stSettings.enOutputDevice = AOUT_DEVICE_ALL;
    i32Ret = pstAoutdev->aout_open(NULL,
                                   &(pstAuOutHdlInfo->psthAout),
                                   &stOpenParams);
    if(SUCCESS != i32Ret)
    {
        GST_ERROR("aout_open failed 0x%x",i32Ret);
        sme_hihal_deinit_aout_module(pstAoutdev);
        pstAoutdev->aout_term(NULL,NULL);
        UTILS_MSAFEFREE(pstAuOutHdlInfo);
        return NULL;
    }

    /*to create an hTrack*/
    pstAuOutHdlInfo->stParams.enFormat = AOUT_DATA_FORMAT_LE_PCM_16_BIT;
    pstAuOutHdlInfo->stParams.u32SampleRate = DEFAULT_SAMPLERATE;
    pstAuOutHdlInfo->stParams.u32Channels = DEFAULT_CHANNEL;
    pstAuOutHdlInfo->stParams.u32BufferSize =
        DEFAULT_CHANNEL * 2 * DEFAULT_SAMPLERATE * AOUT_TRACK_BUFFER_MS /1000; //300ms

    i32Ret = pstAoutdev->track_create(NULL,
                                      pstAuOutHdlInfo->psthAout,
                                      &(pstAuOutHdlInfo->psthTrack),
                                      &(pstAuOutHdlInfo->stParams));
    if(SUCCESS != i32Ret)
    {
        GST_ERROR("track_create failed 0x%x", i32Ret);
        sme_hihal_deinit_aout_module(pstAoutdev);
        pstAoutdev->aout_term(NULL, NULL);
        pstAoutdev->aout_close(NULL, pstAuOutHdlInfo->psthAout, NULL);
        UTILS_MSAFEFREE(pstAuOutHdlInfo);
        return NULL;
    }
    GST_INFO("track_create ghTrack:0x%x ok.",pstAuOutHdlInfo->psthTrack);

    pstAuOutHdlInfo->bStop = FALSE;
    pstAuOutHdlInfo->bOpen = TRUE;

    return (void *)pstAuOutHdlInfo;
}

static void sme_hihal_aout_destroy(void * hdlAOut)
{
    PST_SME_AUDIO_OUT_HDL_INFO pstAuOutHdlInfo = NULL;
    HANDLE psthTrack = 0;
    AOUT_DEVICE_S *pstAoutdev = NULL;

    pstAuOutHdlInfo = (PST_SME_AUDIO_OUT_HDL_INFO)hdlAOut;
    if (NULL == pstAuOutHdlInfo) {
        return;
    }

    psthTrack = pstAuOutHdlInfo->psthTrack;
    pstAoutdev = pstAuOutHdlInfo->pstAoutdev;

    GST_INFO("sme_hihal_aout_destroy");

    if(pstAuOutHdlInfo->bOpen)
    {
        pstAoutdev->track_destroy(NULL, psthTrack);
        pstAoutdev->aout_close(NULL, pstAuOutHdlInfo->psthAout, NULL);
        pstAoutdev->aout_term(NULL, NULL);
        sme_hihal_deinit_aout_module(pstAoutdev);
    }

    free(pstAuOutHdlInfo);
    pstAuOutHdlInfo = NULL;

    return ;
}

static gboolean
gst_halaudiosink_open (GstAudioSink * asink)
{
  GstHalAudioSink *halaudiosink = GST_HALAUDIO_SINK (asink);
  int fd, ret;

  GST_OBJECT_LOCK (halaudiosink);

  halaudiosink->aout_handle = sme_hihal_aout_create();
  if (NULL == halaudiosink->aout_handle)
  {
      GST_WARNING("Fail to create hisi hal aout handle");
      GST_OBJECT_UNLOCK (halaudiosink);
      goto open_failed;
  }
  GST_OBJECT_UNLOCK (halaudiosink);

  return TRUE;

open_failed:
  GST_ELEMENT_ERROR (halaudiosink, RESOURCE, OPEN_WRITE, (NULL),
      ("can't open connection to Hal Audio device"));
  return FALSE;
}

static gboolean
gst_halaudiosink_close (GstAudioSink * asink)
{
  GstHalAudioSink *halaudiosink = GST_HALAUDIO_SINK (asink);

  GST_OBJECT_LOCK (halaudiosink);
  if (halaudiosink->aout_handle)
  {
      sme_hihal_aout_destroy(halaudiosink->aout_handle);
  }
  GST_OBJECT_UNLOCK (halaudiosink);

  return TRUE;
}

static gboolean
gst_halaudiosink_prepare (GstAudioSink * asink, GstAudioRingBufferSpec * spec)
{
  GstHalAudioSink *halaudiosink = GST_HALAUDIO_SINK (asink);
  int i32Ret;
  PST_SME_AUDIO_OUT_HDL_INFO pstAuOutHdlInfo = NULL;
  AOUT_DEVICE_S *pstAoutdev = NULL;

  pstAuOutHdlInfo = (PST_SME_AUDIO_OUT_HDL_INFO)halaudiosink->aout_handle;
  if (NULL == pstAuOutHdlInfo) {
      GST_ELEMENT_ERROR (halaudiosink, RESOURCE, SETTINGS, (NULL), ("%s",
                  strerror (errno)));
      return FALSE;
  }
  pstAoutdev = pstAuOutHdlInfo->pstAoutdev;


  pstAuOutHdlInfo->stParams.enFormat = AOUT_DATA_FORMAT_LE_PCM_16_BIT;
  pstAuOutHdlInfo->stParams.u32SampleRate = GST_AUDIO_INFO_RATE (&spec->info);
  pstAuOutHdlInfo->stParams.u32Channels = GST_AUDIO_INFO_CHANNELS (&spec->info);
  pstAuOutHdlInfo->stParams.u32BufferSize =
      pstAuOutHdlInfo->stParams.u32Channels * 2 * pstAuOutHdlInfo->stParams.u32SampleRate * AOUT_TRACK_BUFFER_MS /1000;    //300ms
  pstAuOutHdlInfo->u32Align = pstAuOutHdlInfo->stParams.u32Channels * 2;

  halaudiosink->bytes_per_sample = GST_AUDIO_INFO_BPF (&spec->info);

  GST_WARNING("sme_hihal_aout_set, i32SampleRate:%d,"
          " i32Channels:%d, i32BytesPerSample:%d",
          pstAuOutHdlInfo->stParams.u32SampleRate,pstAuOutHdlInfo->stParams.u32Channels, halaudiosink->bytes_per_sample);
  GST_WARNING("begin to track_stop pstAoutdev:%p, track handle:0x%x",
          pstAoutdev,
          pstAuOutHdlInfo->psthTrack);

  i32Ret = pstAoutdev->track_stop(pstAoutdev, pstAuOutHdlInfo->psthTrack);
  if (SUCCESS != i32Ret) {
      GST_ERROR("track stop failed :%d, can not set params",i32Ret);
      GST_ELEMENT_ERROR (halaudiosink, RESOURCE, SETTINGS, (NULL), (strerror (errno)));
      return FALSE;
  }

  GST_INFO("track_stop ok, begin to set params, BufferSize:%u",
          pstAuOutHdlInfo->stParams.u32BufferSize);
  i32Ret = pstAoutdev->track_set_params(pstAoutdev,
          pstAuOutHdlInfo->psthTrack,
          &(pstAuOutHdlInfo->stParams));
  if (SUCCESS != i32Ret) {
    GST_ELEMENT_ERROR (halaudiosink, RESOURCE, SETTINGS, (NULL), (strerror (errno)));
    return FALSE;
  }
  GST_INFO("track_set_params ok.");

  return TRUE;
}

static gboolean
gst_halaudiosink_unprepare (GstAudioSink * asink)
{
  return TRUE;
}

static guint
gst_halaudiosink_write (GstAudioSink * asink, gpointer data, guint length)
{
  GstHalAudioSink *sink = GST_HALAUDIO_SINK (asink);
  PST_SME_AUDIO_OUT_HDL_INFO pstAuOutHdlInfo = NULL;
  AOUT_DEVICE_S *pstAoutdev;
  gint32 i32Count = 0;
  guint32 u32AvailBytes = 0;
  guint32 u32BufOffset = 0;
  guint32 u32BufLen = 0;
  gint32 i32Ret;

  gint bytes_written, err;

  g_mutex_lock (sink->write_mutex);
  if (sink->flushing) {
    /* Exit immediately if reset tells us to */
    g_mutex_unlock (sink->write_mutex);
    return length;
  }

  pstAuOutHdlInfo = (PST_SME_AUDIO_OUT_HDL_INFO)sink->aout_handle;
  pstAoutdev = pstAuOutHdlInfo->pstAoutdev;
  while(!(pstAuOutHdlInfo->bStop) &&
          (i32Count) < TIMEOUT_CNT &&
          (u32BufOffset) < length)
  {
      //1.get available size
      i32Ret = pstAoutdev->track_get_buf_avail(NULL,
              pstAuOutHdlInfo->psthTrack,
              &u32AvailBytes);
      if(SUCCESS != i32Ret)
      {
          GST_WARNING("track_get_buf_avail failed 0x%x\n",i32Ret);
          usleep((guint32)20*1000);
          continue;
      }
      //GST_INFO("track_get_buf_avail:%u/%u, count %d",u32AvailBytes,length,i32Count);
      //2. send data
      if (u32AvailBytes >= pstAuOutHdlInfo->u32Align*2048 || u32AvailBytes >= (length - u32BufOffset))
      {
          u32BufLen = length - u32BufOffset;
          if (u32BufLen > u32AvailBytes) {
              u32BufLen = u32AvailBytes;
          }
          u32BufLen -= u32BufLen % pstAuOutHdlInfo->u32Align;
          //GST_DEBUG("track_write: before, offset %u, len %u",u32BufOffset,u32BufLen);
          i32Ret = pstAoutdev->track_write(NULL,
                  pstAuOutHdlInfo->psthTrack,
                  data+u32BufOffset,
                  u32BufLen);
          //GST_DEBUG("track_write: return %d", i32Ret);
          if (SUCCESS == i32Ret)
          {
              u32BufOffset += u32BufLen;
          }else {
              GST_WARNING("track write failed: return %d",i32Ret);
              usleep((guint32)20*1000);
              i32Count++;
              continue;
          }
      } else {
          i32Count++;
          usleep((guint32)20*1000);
      }

      if (u32BufOffset >= length) {
          break;
      }

  }

  if (i32Count >= TIMEOUT_CNT) {
      GST_WARNING("track_write error timeout!,%u",length);
  }

  g_mutex_unlock (sink->write_mutex);
  return length;

write_error:
  g_mutex_unlock (sink->write_mutex);

  GST_ELEMENT_ERROR (sink, RESOURCE, OPEN_WRITE, (NULL),
      ("Playback error on device : %s", strerror (errno)));
  return length;                /* Say we wrote the segment to let the ringbuffer exit */
}

/*
 * Provide the current number of unplayed samples that have been written
 * to the device */
static guint
gst_halaudiosink_delay (GstAudioSink * asink)
{
  GstHalAudioSink *sink = GST_HALAUDIO_SINK (asink);
  guint offset = 0;

  return offset;
}

static void
gst_halaudiosink_reset (GstAudioSink * asink)
{
  /* Get current values */
  GstHalAudioSink *halaudiosink = GST_HALAUDIO_SINK (asink);

  /* Now, we take the write_mutex and signal to ensure the write thread
   * is not busy, and we signal the condition to wake up any sleeper,
   * then we flush again in case the write wrote something after we flushed,
   * and finally release the lock and unpause */
  g_mutex_lock (halaudiosink->write_mutex);
  halaudiosink->flushing = TRUE;

  g_cond_signal (halaudiosink->sleep_cond);

  halaudiosink->flushing = FALSE;
  g_mutex_unlock (halaudiosink->write_mutex);
}

#ifdef HAVE_CONFIG_H
//#include "config.h"
//for dynamic load smeplugin
#ifdef GST_PLUGIN_BUILD_STATIC
#undef GST_PLUGIN_BUILD_STATIC
#endif
#endif

static gboolean
plugin_init (GstPlugin * plugin)
{
    GST_INFO("register sme audio sink based on hisi hal  begin...");
    if (!gst_smeaudiosink_hihal_register (plugin))
        GST_WARNING("register sme hisi-hal audio sink  fail.");
    GST_WARNING("register sme audio sink based on hisi end");
    return TRUE;
}

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    sme_gstplugin_asink_hisi_hal,
    "sme plugin asink based on hisi hal driver.",
    plugin_init, VERSION, GST_LICENSE, GST_PACKAGE_NAME, GST_PACKAGE_ORIGIN)
