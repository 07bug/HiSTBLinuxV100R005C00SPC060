#ifndef __HI_DRV_EDID_H__
#define __HI_DRV_EDID_H__

#include "hi_type.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

typedef struct hiHDMI_DOLBY_CAPS_VER_0_S
{
    HI_BOOL     bYUV422_12Bit;          /* support(HI_TRUE) or not support(HI_FALSE) a YUV422-12Bit dolby singal */
    HI_BOOL     b2160P60;               /* capable of processing a max timming 3840X2160p60(HI_TRUE) /3840X2160p30(HI_FALSE) */
    HI_BOOL     bGlobalDimming;         /**<support(HI_TRUE) or not support(HI_FALSE) global dimming. */
    HI_U16      u16White_X;             /* white point chromaticity coordinate x   ,bit[11:0]valid.Real value =SUM OF bit[N]*2^-(12-N), only support when u8VSVDBVersion = 0. */
    HI_U16      u16White_Y;             /* white point  chromaticity coordinate y  ,bit[11:0]valid.Real value =SUM OF bit[N]*2^-(12-N), only support when u8VSVDBVersion = 0.*/
    HI_U8       u8DMmajorVersion;       /* the major version of display management implemented. only support when u8VSVDBVersion = 0.*/
    HI_U8       u8DMminorVersion;       /* the minor version of display management implemented. only support when u8VSVDBVersion = 0.*/
    HI_U16      u16TargetMinPQ;         /* Perceptual quantization(PQ)-encoded value of minimum display luminance */
    HI_U16      u16TargetMaxPQ;         /* PQ-encoded value of maximum display luminance */
}HI_HDMI_DOLBY_CAPS_VER_0_S;

typedef struct hiHDMI_DOLBY_CAPS_VER_1_S
{
    HI_BOOL     bYUV422_12Bit;          /* support(HI_TRUE) or not support(HI_FALSE) a YUV422-12Bit dolby singal; For low-latency dolbyvision this flag is ingnored */
    HI_BOOL     b2160P60;               /* capable of processing a max timming 3840X2160p60(HI_TRUE) /3840X2160p30(HI_FALSE); For low-latency dolbyvision this bit maybe ingnored,relay on supported video format from the E-EDID */
    HI_BOOL     bGlobalDimming;         /**<support(HI_TRUE) or not support(HI_FALSE) global dimming. */
    HI_BOOL     bColorimetry;           /* this bit is valid only u8VSVDBVersion = 1. 0: Dolby Vision HDMI sink's colorimetry is close to Rec.709, 1: EDR HDMI sink's colorimetry is close to P3, if Byte[9] to Byte[14] are present, ignores this bit. *//**<CNcomment:若为0，Dolby Vision Sink设备色域接近Rec.709，若为1，Dolby Vision Sink设备色域接近P3，但如果Byte[9]到Byte[14]有声明，则忽略此标志。*/
    HI_U8       u8DMVersion;            /* 0:based on display management v2.x; 1:based on the video and blending pipeline v3.x; 2-7: reserved. only support when u8VSVDBVersion = 1. */
    HI_U8       u8LowLatency;           /* 0:supports only standard DolbyVison; 1: Supports low latency with 12-bit YCbCr 4:2:2 interface using the HDMI native 12-bit YCbCr4:2:2 pixel encoding and standard Dolby Vision interface; 2-3:reserved */
    HI_U16      u16TargetMinLuminance;  /* minimum display luminance = (100+50*CV)cd/m2, where CV is the value */
    HI_U16      u16TargetMaxLuminance;  /* maximum display luminance = (CV/127)^2cd/m2, where CV is the value */
}HI_HDMI_DOLBY_CAPS_VER_1_S;

typedef struct hiHDMI_DOLBY_CAPS_VER_2_S
{
    HI_BOOL     bYUV422_12Bit;          /* support(HI_TRUE) or not support(HI_FALSE) a YUV422-12Bit dolby singal */
    HI_BOOL     bBackLightContol;       /* supports Backlight Control */
    HI_BOOL     bGlobalDimming;         /**<support(HI_TRUE) or not support(HI_FALSE) global dimming. */
    HI_U8       u8DMVersion;            /* 0:based on display management v2.x; 1:based on the video and blending pipeline v3.x; 2-7: reserved. only support when u8VSVDBVersion = 1. */
    HI_U8       u8BackLtMinLuma;        /* minimum luminance level 0:25cd/m2 1:50cd/m2 2:75cd/m2 3:100cd/m2 */
    HI_U8       u8Interface;            /* 0:support only "low latency with YUV422" 1:support both "low latency with YUV422" and YUV444/RGB_10/12bit* 2:support both "standard DolbyVision" and "low latency with YUV422" 3:support "standard DolbyVision" "low latency YUV422 YUV444/RGB_10/12bit" */
    HI_U8       u8YUV444RGB444_10b12b;  /* 0:not support 1:support YUV444/RGB444_10bit 2:support YUV444/RGB444_12bit 3:reserved */
    HI_U16      u16TargetMinPQv2;       /* maximum display luminance, in the PQ-encoded value= u16TargetMinPQv2*20. A code value of 31 is approximately equivalent to 1cd/m2 */
    HI_U16      u16TargetMaxPQv2;       /* minimum display luminance, in the PQ-encoded value= 2055+u16TargetMaxPQv2*65. */
}HI_HDMI_DOLBY_CAPS_VER_2_S;

typedef union hiHDMI_DOLBY_CAPS_U
{
    HI_HDMI_DOLBY_CAPS_VER_0_S stVer0;
    HI_HDMI_DOLBY_CAPS_VER_1_S stVer1;
    HI_HDMI_DOLBY_CAPS_VER_2_S stVer2;
}HI_HDMI_DOLBY_CAPS_U;

/* Sink capability of Dolby */
typedef struct hiHDMI_DOLBY_SINK_CAPS_S
{
    HI_U8       u8VSVDBVersion;
    HI_HDMI_DOLBY_CAPS_U unVersionCaps;
}HI_HDMI_DOLBY_SINK_CAPS_S;

typedef struct hiHDMI_HDR_EOTF_CAPS_S
{
    HI_BOOL bEotfSdr;
    HI_BOOL bEotfHdr;
    HI_BOOL bEotfSmpteSt2084;
    HI_BOOL bEotfHLG;
    HI_BOOL bEotfFuture;
}HI_HDMI_HDR_EOTF_CAPS_S;

typedef struct hiHDMI_HDR_METADATA_CAPS_S
{
    HI_BOOL     bDescriptorType1;
}HI_HDMI_HDR_METADATA_CAPS_S;

typedef struct hiHDMI_HDR_SINK_CAPS_S
{
    HI_HDMI_HDR_EOTF_CAPS_S         stEotf;
    HI_HDMI_HDR_METADATA_CAPS_S     stMetadata;
    HI_U8                           u8MaxLuminance_CV;
    HI_U8                           u8AverageLumin_CV;
    HI_U8                           u8MinLuminance_CV;
}HI_HDMI_HDR_SINK_CAPS_S;

typedef struct
{
    HI_BOOL    bxvYCC601;
    HI_BOOL    bxvYCC709;
    HI_BOOL    bsYCC601;
    HI_BOOL    bAdobleYCC601;
    HI_BOOL    bAdobleRGB;
    HI_BOOL    bBT2020cYCC;
    HI_BOOL    bBT2020YCC;
    HI_BOOL    bBT2020RGB;
}HI_HDMI_COLORIMETRY_CAPS_S;
typedef struct hiHDMI_VIDEO_CAPABILITY_S
{
    HI_BOOL                         bYccQrangeSelectable;   /* Sink要求YCC量化范围是否满/限制 范围可选。HI_TRUE表示sink要求范围可选，HI_FALSE表示sink要求默认范围。 */
    HI_BOOL                         bRgbQrangeSelectable;   /* Sink要求RGB量化范围是否满/限制 范围可选。HI_TRUE表示sink要求范围可选，HI_FALSE表示sink要求默认范围。 */
    HI_BOOL                         bDolbySupport;
    HI_BOOL                         bHdrSupport;
    HI_HDMI_DOLBY_SINK_CAPS_S       stDolbyCaps;
    HI_HDMI_HDR_SINK_CAPS_S         stHdrCaps;
    HI_HDMI_COLORIMETRY_CAPS_S      stColorimetry;
}HI_DRV_HDMI_VIDEO_CAPABILITY_S;

/**EDID Display Base Parameters struct*//**CNcomment:EDID 显示屏基本参数 */
typedef struct
{
    HI_U8      u8MaxImageWidth;               /**<The disp image max width  (0~255)cm*//**<CNcomment: 可显示图像最大宽 */
    HI_U8      u8MaxImageHeight;              /**<The disp image max height (0~255)cm*//**<CNcomment: 可显示图像最大高 */
}HI_DRV_HDMI_BASE_DISP_PARA_S;

typedef struct
{
    HI_DRV_HDMI_BASE_DISP_PARA_S  stBasicDispPara;
}HI_DRV_HDMI_SINK_CAPABILITY_S;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

