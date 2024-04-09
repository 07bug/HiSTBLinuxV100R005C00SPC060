/*
 * GStreamer - HalAudio sink
 * gsthalaudiosink.h:
 */

#ifndef __GST_HALAUDIO_SINK_H__
#define __GST_HALAUDIO_SINK_H__

#include <gst/gst.h>
#include <gst/audio/gstaudiosink.h>

G_BEGIN_DECLS

#define GST_TYPE_HALAUDIO_SINK            (gst_halaudiosink_get_type())
#define GST_HALAUDIO_SINK(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_HALAUDIO_SINK,GstHalAudioSink))
#define GST_HALAUDIO_SINK_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_HALAUDIO_SINK,GstHalAudioSinkClass))
#define GST_IS_HALAUDIO_SINK(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_HALAUDIO_SINK))
#define GST_IS_HALAUDIO_SINK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_HALAUDIO_SINK))

typedef struct _GstHalAudioSink GstHalAudioSink;
typedef struct _GstHalAudioSinkClass GstHalAudioSinkClass;

struct _GstHalAudioSink {
  GstAudioSink    sink;

  void *aout_handle;

  guint bytes_per_sample;

  /* mutex and gcond used to control the write method */
  GMutex *write_mutex;
  GCond *sleep_cond;
  gboolean flushing;
};

struct _GstHalAudioSinkClass {
  GstAudioSinkClass parent_class;
};

GType gst_halaudiosink_get_type(void);

G_END_DECLS

#endif /* __GST_HALAUDIO_SINK_H__ */

