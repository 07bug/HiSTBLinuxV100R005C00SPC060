/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OMX_VideoExt_h
#define OMX_VideoExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully
 */
#include <OMX_Core.h>
#include <OMX_Component.h>
#include <OMX_Index.h>

/* CodecType Relative */
#define OMX_VENC_COMPONENT_NAME            "OMX.hisi.video.encoder"
#define OMX_VDEC_NORMAL_COMPONENT_NAME     "OMX.hisi.video.decoder"
#define OMX_VDEC_SECURE_COMPONENT_NAME     "OMX.hisi.video.decoder.secure"
/* define support real , default not support real */
#define REAL8_SUPPORT
#define REAL9_SUPPORT

#define MAX_NAME_LENGTH 256

//omx extrension flag
#define OMX_BUFFERFLAG_OCCOUPYFRAME       (0x20000000)

/** Enum for video codingtype extensions */
typedef enum OMX_VIDEO_CODINGEXTTYPE {
    OMX_VIDEO_ExtCodingUnused = OMX_VIDEO_CodingKhronosExtensions,
    OMX_VIDEO_CodingVC1,
    OMX_VIDEO_CodingDIVX3,      /**< Divx3 */
    OMX_VIDEO_CodingVP6,        /**< VP6 */
    OMX_VIDEO_CodingMPEG1,      /**< MPEG1 */
    OMX_VIDEO_CodingAVS,        /**< AVS */
    OMX_VIDEO_CodingAVS2,       /**< AVS2 */
    OMX_VIDEO_CodingSorenson,   /**< Sorenson */
    OMX_VIDEO_CodingMVC,        /**< MVC */
    OMX_VIDEO_CodingButt,       /**< MAX */
} OMX_VIDEO_CODINGEXTTYPE;

/** VP6 Versions */
typedef enum OMX_VIDEO_VP6FORMATTYPE {
    OMX_VIDEO_VP6FormatUnused = 0x01,   /**< Format unused or unknown */
    OMX_VIDEO_VP6      = 0x02,   /**< On2 VP6 */
    OMX_VIDEO_VP6F     = 0x04,   /**< On2 VP6 (Flash version) */
    OMX_VIDEO_VP6A     = 0x08,   /**< On2 VP6 (Flash version, with alpha channel) */
    OMX_VIDEO_VP6FormatKhronosExtensions = 0x6F000000, /**< Reserved region for introducing Khronos
                                                            Standard Extensions */
    OMX_VIDEO_VP6FormatVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
    OMX_VIDEO_VP6FormatMax    = 0x7FFFFFFF
} OMX_VIDEO_VP6FORMATTYPE;

/**
  * VP6 Params
  *
  * STRUCT MEMBERS:
  *  nSize      : Size of the structure in bytes
  *  nVersion   : OMX specification version information
  *  nPortIndex : Port that this structure applies to
  *  eFormat    : VP6 format
  */
typedef struct OMX_VIDEO_PARAM_VP6TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_VIDEO_VP6FORMATTYPE eFormat;
} OMX_VIDEO_PARAM_VP6TYPE;



/** VP8 profiles */
typedef enum OMX_VIDEO_VP8PROFILETYPE {
    OMX_VIDEO_VP8ProfileMain = 0x01,
    OMX_VIDEO_VP8ProfileUnknown = 0x6EFFFFFF,
    OMX_VIDEO_VP8ProfileMax = 0x7FFFFFFF
} OMX_VIDEO_VP8PROFILETYPE;

/** VP8 levels */
typedef enum OMX_VIDEO_VP8LEVELTYPE {
    OMX_VIDEO_VP8Level_Version0 = 0x01,
    OMX_VIDEO_VP8Level_Version1 = 0x02,
    OMX_VIDEO_VP8Level_Version2 = 0x04,
    OMX_VIDEO_VP8Level_Version3 = 0x08,
    OMX_VIDEO_VP8LevelUnknown = 0x6EFFFFFF,
    OMX_VIDEO_VP8LevelMax = 0x7FFFFFFF
} OMX_VIDEO_VP8LEVELTYPE;

/** VP9 profiles */
typedef enum OMX_VIDEO_VP9PROFILETYPE {
    OMX_VIDEO_VP9Profile0       = 0x1,
    OMX_VIDEO_VP9Profile1       = 0x2,
    OMX_VIDEO_VP9Profile2       = 0x4,
    OMX_VIDEO_VP9Profile3       = 0x8,
    // HDR profiles also support passing HDR metadata
    OMX_VIDEO_VP9Profile2HDR    = 0x1000,
    OMX_VIDEO_VP9Profile3HDR    = 0x2000,
    OMX_VIDEO_VP9ProfileUnknown = 0x6EFFFFFF,
    OMX_VIDEO_VP9ProfileMax     = 0x7FFFFFFF
} OMX_VIDEO_VP9PROFILETYPE;

/** VP9 levels */
typedef enum OMX_VIDEO_VP9LEVELTYPE {
    OMX_VIDEO_VP9Level1       = 0x1,
    OMX_VIDEO_VP9Level11      = 0x2,
    OMX_VIDEO_VP9Level2       = 0x4,
    OMX_VIDEO_VP9Level21      = 0x8,
    OMX_VIDEO_VP9Level3       = 0x10,
    OMX_VIDEO_VP9Level31      = 0x20,
    OMX_VIDEO_VP9Level4       = 0x40,
    OMX_VIDEO_VP9Level41      = 0x80,
    OMX_VIDEO_VP9Level5       = 0x100,
    OMX_VIDEO_VP9Level51      = 0x200,
    OMX_VIDEO_VP9Level52      = 0x400,
    OMX_VIDEO_VP9Level6       = 0x800,
    OMX_VIDEO_VP9Level61      = 0x1000,
    OMX_VIDEO_VP9Level62      = 0x2000,
    OMX_VIDEO_VP9LevelUnknown = 0x6EFFFFFF,
    OMX_VIDEO_VP9LevelMax     = 0x7FFFFFFF
} OMX_VIDEO_VP9LEVELTYPE;

/** VP8 Param */
typedef struct OMX_VIDEO_PARAM_VP8TYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_VIDEO_VP8PROFILETYPE eProfile;
    OMX_VIDEO_VP8LEVELTYPE eLevel;
    OMX_U32 nDCTPartitions;
    OMX_BOOL bErrorResilientMode;
} OMX_VIDEO_PARAM_VP8TYPE;

/** Structure for configuring VP8 reference frames */
typedef struct OMX_VIDEO_VP8REFERENCEFRAMETYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bPreviousFrameRefresh;
    OMX_BOOL bGoldenFrameRefresh;
    OMX_BOOL bAlternateFrameRefresh;
    OMX_BOOL bUsePreviousFrame;
    OMX_BOOL bUseGoldenFrame;
    OMX_BOOL bUseAlternateFrame;
} OMX_VIDEO_VP8REFERENCEFRAMETYPE;

/** Structure for querying VP8 reference frame type */
typedef struct OMX_VIDEO_VP8REFERENCEFRAMEINFOTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bIsIntraFrame;
    OMX_BOOL bIsGoldenOrAlternateFrame;
} OMX_VIDEO_VP8REFERENCEFRAMEINFOTYPE;

/** Maximum number of VP8 temporal layers */
#define OMX_VIDEO_ANDROID_MAXVP8TEMPORALLAYERS 3

/** VP8 temporal layer patterns */
typedef enum OMX_VIDEO_ANDROID_VPXTEMPORALLAYERPATTERNTYPE {
    OMX_VIDEO_VPXTemporalLayerPatternNone = 0,
    OMX_VIDEO_VPXTemporalLayerPatternWebRTC = 1,
    OMX_VIDEO_VPXTemporalLayerPatternMax = 0x7FFFFFFF
} OMX_VIDEO_ANDROID_VPXTEMPORALLAYERPATTERNTYPE;

/**
 * Android specific VP8 encoder params
 *
 * STRUCT MEMBERS:
 *  nSize                      : Size of the structure in bytes
 *  nVersion                   : OMX specification version information
 *  nPortIndex                 : Port that this structure applies to
 *  nKeyFrameInterval          : Key frame interval in frames
 *  eTemporalPattern           : Type of temporal layer pattern
 *  nTemporalLayerCount        : Number of temporal coding layers
 *  nTemporalLayerBitrateRatio : Bitrate ratio allocation between temporal
 *                               streams in percentage
 *  nMinQuantizer              : Minimum (best quality) quantizer
 *  nMaxQuantizer              : Maximum (worst quality) quantizer
 */
typedef struct OMX_VIDEO_PARAM_ANDROID_VP8ENCODERTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nKeyFrameInterval;
    OMX_VIDEO_ANDROID_VPXTEMPORALLAYERPATTERNTYPE eTemporalPattern;
    OMX_U32 nTemporalLayerCount;
    OMX_U32 nTemporalLayerBitrateRatio[OMX_VIDEO_ANDROID_MAXVP8TEMPORALLAYERS];
    OMX_U32 nMinQuantizer;
    OMX_U32 nMaxQuantizer;
} OMX_VIDEO_PARAM_ANDROID_VP8ENCODERTYPE;


/** HEVC Profile enum type */
typedef enum OMX_VIDEO_HEVCPROFILETYPE {
    OMX_VIDEO_HEVCProfileUnknown = 0x0,
    OMX_VIDEO_HEVCProfileMain    = 0x1,
    OMX_VIDEO_HEVCProfileMain10  = 0x2,
    // Main10 profile with HDR SEI support.
    OMX_VIDEO_HEVCProfileMain10HDR10  = 0x1000,
    OMX_VIDEO_HEVCProfileMax     = 0x7FFFFFFF
} OMX_VIDEO_HEVCPROFILETYPE;

/** HEVC Level enum type */
typedef enum OMX_VIDEO_HEVCLEVELTYPE {
    OMX_VIDEO_HEVCLevelUnknown    = 0x0,
    OMX_VIDEO_HEVCMainTierLevel1  = 0x1,
    OMX_VIDEO_HEVCHighTierLevel1  = 0x2,
    OMX_VIDEO_HEVCMainTierLevel2  = 0x4,
    OMX_VIDEO_HEVCHighTierLevel2  = 0x8,
    OMX_VIDEO_HEVCMainTierLevel21 = 0x10,
    OMX_VIDEO_HEVCHighTierLevel21 = 0x20,
    OMX_VIDEO_HEVCMainTierLevel3  = 0x40,
    OMX_VIDEO_HEVCHighTierLevel3  = 0x80,
    OMX_VIDEO_HEVCMainTierLevel31 = 0x100,
    OMX_VIDEO_HEVCHighTierLevel31 = 0x200,
    OMX_VIDEO_HEVCMainTierLevel4  = 0x400,
    OMX_VIDEO_HEVCHighTierLevel4  = 0x800,
    OMX_VIDEO_HEVCMainTierLevel41 = 0x1000,
    OMX_VIDEO_HEVCHighTierLevel41 = 0x2000,
    OMX_VIDEO_HEVCMainTierLevel5  = 0x4000,
    OMX_VIDEO_HEVCHighTierLevel5  = 0x8000,
    OMX_VIDEO_HEVCMainTierLevel51 = 0x10000,
    OMX_VIDEO_HEVCHighTierLevel51 = 0x20000,
    OMX_VIDEO_HEVCMainTierLevel52 = 0x40000,
    OMX_VIDEO_HEVCHighTierLevel52 = 0x80000,
    OMX_VIDEO_HEVCMainTierLevel6  = 0x100000,
    OMX_VIDEO_HEVCHighTierLevel6  = 0x200000,
    OMX_VIDEO_HEVCMainTierLevel61 = 0x400000,
    OMX_VIDEO_HEVCHighTierLevel61 = 0x800000,
    OMX_VIDEO_HEVCMainTierLevel62 = 0x1000000,
    OMX_VIDEO_HEVCHighTierLevel62 = 0x2000000,
    OMX_VIDEO_HEVCHighTiermax     = 0x7FFFFFFF
} OMX_VIDEO_HEVCLEVELTYPE;

/** Structure for controlling HEVC video encoding and decoding */
typedef struct OMX_VIDEO_PARAM_HEVCTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_VIDEO_HEVCPROFILETYPE eProfile;
    OMX_VIDEO_HEVCLEVELTYPE eLevel;
    OMX_U32 nKeyFrameInterval;
} OMX_VIDEO_PARAM_HEVCTYPE;

/*========================================================================
Open MAX   Component: Video Decoder
This module contains the class definition for openMAX decoder component.
author: sdk
==========================================================================*/

typedef enum OMX_HISI_EXTERN_INDEXTYPE {
    OMX_HisiIndexChannelAttributes = (OMX_IndexVendorStartUnused + 1),
    OMX_GoogleIndexEnableAndroidNativeBuffers,
    OMX_GoogleIndexAllocateNativeHandle,
    OMX_GoogleIndexGetAndroidNativeBufferUsage,
    OMX_GoogleIndexUseAndroidNativeBuffer,
    OMX_GoogleIndexUseAndroidNativeBuffer2,

    /*just for decoder*/
    OMX_HISIIndexFlexibleYUVDescription,
    OMX_HisiIndexFastOutputMode,
    OMX_HISIIndexParamVideoAdaptivePlaybackMode,
    OMX_HISIIndexVideoPostProcessBypassInfo,
    OMX_GoogleAndroidIndexConfigureVideoTunnelMode,
    OMX_HisiIndexSetMetaDataAlloc,
    OMX_HISIIndexSetCallerName,

    OMX_GoogleAndroidIndexDescribeHDRStaticInfo,
    OMX_GoogleAndroidIndexDescribeColorAspects,
    /*just for encoder*/
    OMX_GoogleIndexStoreMetaDataInBuffers,
    OMX_GoogleIndexPrependSPSPPSToIDRFrames,
    OMX_HisiIndexGetParameterSet,
    OMX_HisiIndexAutoRequestIFrm,
}OMX_HISI_EXTERN_INDEXTYPE;

/**
* A pointer to this struct is passed to the OMX_SetParameter when the extension
* index for the 'OMX.Hisi.Index.ChannelAttributes' extension
* is given.
* The corresponding extension Index is OMX_HisiIndexChannelAttributes.
*/
typedef struct OMX_HISI_PARAM_CHANNELATTRIBUTES  {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPrior;
    OMX_U32 nErrorThreshold;
    OMX_U32 nStreamOverflowThreshold;
    OMX_U32 nDecodeMode;
    OMX_U32 nPictureOrder;
    OMX_U32 nLowdlyEnable;
    OMX_U32 xFramerate;
    OMX_BOOL bIsOnlive;
    OMX_BOOL bIsGst;
}  OMX_HISI_PARAM_CHANNELATTRIBUTES;

typedef struct OMX_HISI_CALLER_NAME {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U8 strCallerName[MAX_NAME_LENGTH];
} OMX_HISI_CALLER_NAME;

typedef struct OMX_VIDEO_RENDEREVENTTYPE {
    OMX_S64 nMediaTimeUs;  // timestamp of rendered video frame
    OMX_S64 nSystemTimeNs; // system monotonic time at the time frame was rendered
                           // Use INT64_MAX for nMediaTimeUs to signal that the EOS
                           // has been reached. In this case, nSystemTimeNs MUST be
                           // the system time when the last frame was rendered.
                           // This MUST be done in addition to returning (and
                           // following) the render information for the last frame.
} OMX_VIDEO_RENDEREVENTTYPE;

/**
 * A pointer to this struct is passed to the OMX_SetParameter when the extension
 * index for the 'OMX.HISI.android.index.VideoPostProcessBypassInfo' extension
 * is given.
 * The corresponding extension Index is OMX_HISIIndexVideoPostProcessBypasInfo.
 * nSurfaceType        : 1: surface view  0:surface texture
 * nShouldBypassEnable : 1: bypass  0: not bypass
 *
 */
typedef struct OMX_HISI_PARAM_VIDEOBYPASSINFO  {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nSurfaceType;
    OMX_U32 nShouldBypassEnable;
} OMX_HISI_PARAM_VIDEOBYPASSINFO;

typedef enum OMX_VIDEO_DOLBYVISIONPROFILETYPE {
    OMX_VIDEO_DolbyVisionProfileUnknown = 0x0,
    OMX_VIDEO_DolbyVisionProfileDvavPer = 0x1,
    OMX_VIDEO_DolbyVisionProfileDvavPen = 0x2,
    OMX_VIDEO_DolbyVisionProfileDvheDer = 0x4,
    OMX_VIDEO_DolbyVisionProfileDvheDen = 0x8,
    OMX_VIDEO_DolbyVisionProfileDvheDtr = 0x10,
    OMX_VIDEO_DolbyVisionProfileDvheStn = 0x20,
    OMX_VIDEO_DolbyVisionProfileDvheDth = 0x40,
    OMX_VIDEO_DolbyVisionProfileDvheDtb = 0x80,
    OMX_VIDEO_DolbyVisionProfileMax     = 0x7FFFFFFF
} OMX_VIDEO_DOLBYVISIONPROFILETYPE;
typedef enum OMX_VIDEO_DOLBYVISIONLEVELTYPE {
    OMX_VIDEO_DolbyVisionLevelUnknown = 0x0,
    OMX_VIDEO_DolbyVisionLevelHd24    = 0x1,
    OMX_VIDEO_DolbyVisionLevelHd30    = 0x2,
    OMX_VIDEO_DolbyVisionLevelFhd24   = 0x4,
    OMX_VIDEO_DolbyVisionLevelFhd30   = 0x8,
    OMX_VIDEO_DolbyVisionLevelFhd60   = 0x10,
    OMX_VIDEO_DolbyVisionLevelUhd24   = 0x20,
    OMX_VIDEO_DolbyVisionLevelUhd30   = 0x40,
    OMX_VIDEO_DolbyVisionLevelUhd48   = 0x80,
    OMX_VIDEO_DolbyVisionLevelUhd60   = 0x100,
    OMX_VIDEO_DolbyVisionLevelmax     = 0x7FFFFFFF
} OMX_VIDEO_DOLBYVISIONLEVELTYPE;

/**
 * A pointer to this struct is passed to the OMX_SetParameter when the extension
 * index for the 'OMX.Hisi.Param.Index.FastOutputMode' extension
 * is given.
 * The corresponding extension Index is OMX_HisiIndexFastOutputMode.
 */
typedef struct OMX_HISI_PARAM_FASTOUTPUT  {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_BOOL bEnabled;
} OMX_HISI_PARAM_FASTOUTPUT;

#ifdef ANDROID // native buffer
/**
* A pointer to this struct is passed to the OMX_SetParameter when the extension
* index for the 'OMX.google.android.index.enableAndroidNativeBuffers' extension
* is given.
* The corresponding extension Index is OMX_GoogleIndexUseAndroidNativeBuffer.
* This will be used to inform OMX about the presence of gralloc pointers
instead
* of virtual pointers
*/
typedef struct EnableAndroidNativeBuffersParams  {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
} EnableAndroidNativeBuffersParams;

/**
* A pointer to this struct is passed to OMX_GetParameter when the extension
* index for the 'OMX.google.android.index.getAndroidNativeBufferUsage'
* extension is given.
* The corresponding extension Index is OMX_GoogleIndexGetAndroidNativeBufferUsage.
* The usage bits returned from this query will be used to allocate the Gralloc
* buffers that get passed to the useAndroidNativeBuffer command.
*/
typedef struct GetAndroidNativeBufferUsageParams  {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_U32 nUsage;
} GetAndroidNativeBufferUsageParams;


typedef enum Type
{
    MEDIA_IMAGE_TYPE_UNKNOWN = 0,
    MEDIA_IMAGE_TYPE_YUV,
}Type;

typedef enum PlaneIndex
{
    Y = 0,
    U,
    V,
    MAX_NUM_PLANES
}PlaneIndex;

typedef struct
{
    size_t mOffset;             // offset of first pixel of the plane in bytes
                                // from buffer offset
    size_t mColInc;             // column increment in bytes
    size_t mRowInc;             // row increment in bytes
    size_t mHorizSubsampling;   // subsampling compared to the largest plane
    size_t mVertSubsampling;    // subsampling compared to the largest plane
}PlaneInfo ;
// Structure describing a media image (frame)
// Currently only supporting YUV
typedef struct {

    Type mType;
    size_t mNumPlanes;              // number of planes
    size_t mWidth;                  // width of largest plane (unpadded, as in nFrameWidth)
    size_t mHeight;                 // height of largest plane (unpadded, as in nFrameHeight)
    size_t mBitDepth;               // useable bit depth

    PlaneInfo mPlane[MAX_NUM_PLANES];
}MediaImage;


// A pointer to this struct is passed to OMX_GetParameter when the extension
// index for the 'OMX.google.android.index.describeColorFormat'
// extension is given.  This method can be called from any component state
// other than invalid.  The color-format, frame width/height, and stride/
// slice-height parameters are ones that are associated with a raw video
// port (input or output), but the stride/slice height parameters may be
// incorrect. bUsingNativeBuffers is OMX_TRUE if native android buffers will
// be used (while specifying this color format).
//
// The component shall fill out the MediaImage structure that
// corresponds to the described raw video format, and the potentially corrected
// stride and slice-height info.
//
// The behavior is slightly different if bUsingNativeBuffers is OMX_TRUE,
// though most implementations can ignore this difference. When using native buffers,
// the component may change the configured color format to an optimized format.
// Additionally, when allocating these buffers for flexible usecase, the framework
// will set the SW_READ/WRITE_OFTEN usage flags. In this case (if bUsingNativeBuffers
// is OMX_TRUE), the component shall fill out the MediaImage information for the
// scenario when these SW-readable/writable buffers are locked using gralloc_lock.
// Note, that these buffers may also be locked using gralloc_lock_ycbcr, which must
// be supported for vendor-specific formats.
//
// For non-YUV packed planar/semiplanar image formats, or if bUsingNativeBuffers
// is OMX_TRUE and the component does not support this color format with native
// buffers, the component shall set mNumPlanes to 0, and mType to MEDIA_IMAGE_TYPE_UNKNOWN.
typedef struct DescribeColorFormatParams {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    // input: parameters from OMX_VIDEO_PORTDEFINITIONTYPE
    OMX_COLOR_FORMATTYPE eColorFormat;
    OMX_U32 nFrameWidth;
    OMX_U32 nFrameHeight;
    OMX_U32 nStride;
    OMX_U32 nSliceHeight;
    OMX_BOOL bUsingNativeBuffers;

    // output: fill out the MediaImage fields
    MediaImage sMediaImage;
}DescribeColorFormatParams;


// A pointer to this struct is passed to OMX_SetParameter() when the extension
// index "OMX.google.android.index.prepareForAdaptivePlayback" is given.
//
// This method is used to signal a video decoder, that the user has requested
// seamless resolution change support (if bEnable is set to OMX_TRUE).
// nMaxFrameWidth and nMaxFrameHeight are the dimensions of the largest
// anticipated frames in the video.  If bEnable is OMX_FALSE, no resolution
// change is expected, and the nMaxFrameWidth/Height fields are unused.
//
// If the decoder supports dynamic output buffers, it may ignore this
// request.  Otherwise, it shall request resources in such a way so that it
// avoids full port-reconfiguration (due to output port-definition change)
// during resolution changes.
//
// DO NOT USE THIS STRUCTURE AS IT WILL BE REMOVED.  INSTEAD, IMPLEMENT
// METADATA SUPPORT FOR VIDEO DECODERS.
typedef struct PrepareForAdaptivePlaybackParams {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
    OMX_U32 nMaxFrameWidth;
    OMX_U32 nMaxFrameHeight;
}PrepareForAdaptivePlaybackParams;
typedef struct ConfigureVideoTunnelModeParams {
    OMX_U32 nSize;              // IN
    OMX_VERSIONTYPE nVersion;   // IN
    OMX_U32 nPortIndex;         // IN
    OMX_BOOL bTunneled;         // IN/OUT
    OMX_U32 nAudioHwSync;       // IN
    OMX_PTR pSidebandWindow;    // OUT
}ConfigureVideoTunnelModeParams;

// this is in sync with the range values in graphics.h
typedef enum Range {
    RangeUnspecified,
    RangeFull,
    RangeLimited,
    RangeOther = 0xff,
} Range;

typedef enum Primaries {
    PrimariesUnspecified,
    PrimariesBT709_5,       // Rec.ITU-R BT.709-5 or equivalent
    PrimariesBT470_6M,      // Rec.ITU-R BT.470-6 System M or equivalent
    PrimariesBT601_6_625,   // Rec.ITU-R BT.601-6 625 or equivalent
    PrimariesBT601_6_525,   // Rec.ITU-R BT.601-6 525 or equivalent
    PrimariesGenericFilm,   // Generic Film
    PrimariesBT2020,        // Rec.ITU-R BT.2020 or equivalent
    PrimariesOther = 0xff,
} Primaries;

// this partially in sync with the transfer values in graphics.h prior to the transfers
// unlikely to be required by Android section
typedef enum Transfer {
    TransferUnspecified,
    TransferLinear,         // Linear transfer characteristics
    TransferSRGB,           // sRGB or equivalent
    TransferSMPTE170M,      // SMPTE 170M or equivalent (e.g. BT.601/709/2020)
    TransferGamma22,        // Assumed display gamma 2.2
    TransferGamma28,        // Assumed display gamma 2.8
    TransferST2084,         // SMPTE ST 2084 for 10/12/14/16 bit systems
    TransferHLG,            // ARIB STD-B67 hybrid-log-gamma

    // transfers unlikely to be required by Android
    TransferSMPTE240M = 0x40, // SMPTE 240M
    TransferXvYCC,          // IEC 61966-2-4
    TransferBT1361,         // Rec.ITU-R BT.1361 extended gamut
    TransferST428,          // SMPTE ST 428-1
    TransferOther = 0xff,
} Transfer;

typedef enum MatrixCoeffs {
    MatrixUnspecified,
    MatrixBT709_5,          // Rec.ITU-R BT.709-5 or equivalent
    MatrixBT470_6M,         // KR=0.30, KB=0.11 or equivalent
    MatrixBT601_6,          // Rec.ITU-R BT.601-6 625 or equivalent
    MatrixSMPTE240M,        // SMPTE 240M or equivalent
    MatrixBT2020,           // Rec.ITU-R BT.2020 non-constant luminance
    MatrixBT2020Constant,   // Rec.ITU-R BT.2020 constant luminance
    MatrixOther = 0xff,
} MatrixCoeffs;

// this is in sync with the standard values in graphics.h
typedef enum Standard {
    StandardUnspecified,
    StandardBT709,                  // PrimariesBT709_5 and MatrixBT709_5
    StandardBT601_625,              // PrimariesBT601_6_625 and MatrixBT601_6
    StandardBT601_625_Unadjusted,   // PrimariesBT601_6_625 and KR=0.222, KB=0.071
    StandardBT601_525,              // PrimariesBT601_6_525 and MatrixBT601_6
    StandardBT601_525_Unadjusted,   // PrimariesBT601_6_525 and MatrixSMPTE240M
    StandardBT2020,                 // PrimariesBT2020 and MatrixBT2020
    StandardBT2020Constant,         // PrimariesBT2020 and MatrixBT2020Constant
    StandardBT470M,                 // PrimariesBT470_6M and MatrixBT470_6M
    StandardFilm,                   // PrimariesGenericFilm and KR=0.253, KB=0.068
    StandardOther = 0xff,
} Standard;

typedef struct __attribute__ ((__packed__)) ColorAspects {
    Range mRange;                // IN/OUT
    Primaries mPrimaries;        // IN/OUT
    Transfer mTransfer;          // IN/OUT
    MatrixCoeffs mMatrixCoeffs;  // IN/OUT
} ColorAspects;

typedef struct DataSpace
{
    OMX_U32 legacy_custom : 16;
    OMX_U32 standard      : 6;
    OMX_U32 transfer      : 5;
    OMX_U32 range         : 3;
    OMX_U32 rev           : 2;
} DataSpace;

typedef struct DescribeColorAspectsParams {
    OMX_U32 nSize;                 // IN
    OMX_VERSIONTYPE nVersion;      // IN
    OMX_U32 nPortIndex;            // IN
    OMX_BOOL bRequestingDataSpace; // IN
    OMX_BOOL bDataSpaceChanged;    // IN
    OMX_U32 nPixelFormat;          // IN
    DataSpace nDataSpace;          // OUT
    ColorAspects sAspects;         // IN/OUT
} DescribeColorAspectsParams;

typedef enum ID {
    kType1 = 0, // Static Metadata Type 1
} ID;

typedef struct __attribute__ ((__packed__)) Primaries1 {
    // values are in units of 0.00002
    OMX_U16 x;
    OMX_U16 y;
} Primaries1;

// Static Metadata Descriptor Type 1
typedef struct __attribute__ ((__packed__)) Type1 {
    Primaries1 mR; // display primary 0
    Primaries1 mG; // display primary 1
    Primaries1 mB; // display primary 2
    Primaries1 mW; // white point
    OMX_U16 mMaxDisplayLuminance; // in cd/m^2
    OMX_U16 mMinDisplayLuminance; // in 0.0001 cd/m^2
    OMX_U16 mMaxContentLightLevel; // in cd/m^2
    OMX_U16 mMaxFrameAverageLightLevel; // in cd/m^2
} Type1;

typedef struct __attribute__ ((__packed__)) HDRStaticInfo {
    OMX_U8 mID;
    Type1 sType1;
} HDRStaticInfo;

typedef struct DescribeHDRStaticInfoParams {
    OMX_U32 nSize;                 // IN
    OMX_VERSIONTYPE nVersion;      // IN
    OMX_U32 nPortIndex;            // IN
    HDRStaticInfo sInfo;           // IN/OUT
} DescribeHDRStaticInfoParams;
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_VideoExt_h */
