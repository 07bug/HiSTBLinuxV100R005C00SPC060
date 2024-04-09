#ifndef __ASF_PRIV_H__
#define __ASF_PRIV_H__

#define __ASF_GID_NUM__ 16

extern const HI_U8 ASF_HEADER_OBJECT_GUID[];
extern const HI_U8 ff_asf_file_header[];
extern const HI_U8 ff_asf_stream_header[];
extern const HI_U8 ff_asf_ext_stream_header[];
extern const HI_U8 ASF_AUDIO_MEDIA_GUID[];
extern const HI_U8 ff_asf_audio_conceal_none[];
extern const HI_U8 ff_asf_audio_conceal_spread[];
extern const HI_U8 ASF_VIDEO_MEDIA_GUID[];
extern const HI_U8 ff_asf_video_conceal_none[];
extern const HI_U8 ff_asf_command_stream[];
extern const HI_U8 ff_asf_comment_header[];
extern const HI_U8 ff_asf_codec_comment_header[];
extern const HI_U8 ff_asf_codec_comment1_header[];
extern const HI_U8 ASF_DATA_OBJECT_GUID[];
extern const HI_U8 ff_asf_head1_guid[];
extern const HI_U8 ff_asf_head2_guid[];
extern const HI_U8 ff_asf_extended_content_header[];
extern const HI_U8 ASF_SIMPLE_INDEX_OBJECT_GUID[];
extern const HI_U8 ff_asf_ext_stream_embed_stream_header[];
extern const HI_U8 ff_asf_ext_stream_audio_stream[];
extern const HI_U8 ff_asf_metadata_header[];
extern const HI_U8 ff_asf_marker_header[];
extern const HI_U8 ff_asf_language_guid[];
extern const HI_U8 ASF_CONTENT_ENCRYPTION_BOJECT_GUID[];
extern const HI_U8 ASF_EXTENDED_CONTENT_ENCRYPTION_GUID[];
extern const HI_U8 ff_asf_digital_signature[];

//  ASF STRUCTURE

//   ASF data packet structure
//   =========================
//  -----------------------------------
// | Error Correction Data             |  Optional
//  -----------------------------------
// | Payload Parsing Information (PPI) |
//  -----------------------------------
// | Payload Data                      |
//  -----------------------------------
// | Padding Data                      |
//  -----------------------------------

#endif
