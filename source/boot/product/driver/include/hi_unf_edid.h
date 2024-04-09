/******************************************************************************

  Copyright (C), 2001-2013, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_edid.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013-8-28
  Description   :
  History       :
  1.Date        : 2013-8-28
    Author      : 
    Modification: Created file

*******************************************************************************/
#ifndef __HI_UNF_EDID_H__
#define __HI_UNF_EDID_H__

//#include "hi_unf_common.h"
//#include "hi_unf_audio.h"
//#include "hi_unf_video.h"

#include "hi_type.h"
#include "hi_unf_disp.h"
#include "hi_debug.h"
#include <uboot.h>
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "exports.h"
#ifdef HI_ADVCA_FUNCTION_RELEASE
#define HI_ERR_HDMI(format, arg...)    
#define HI_INFO_HDMI(format, arg...)  
#else
#define HI_ERR_HDMI(format, arg...)   
#define HI_INFO_HDMI(format, arg...)   
#endif

/**extern begin**/
/**CNcomment: ������Ƶ������ö��*/
typedef enum hiUNF_SAMPLE_RATE_E
{
    HI_UNF_SAMPLE_RATE_UNKNOWN=0,       /**<Unknown*/ /**<CNcomment: δ֪����Ƶ�� */
    HI_UNF_SAMPLE_RATE_8K    = 8000,    /**<8 kHz sampling rate*/ /**<CNcomment: 8K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_11K   = 11025,   /**<11.025 kHz sampling rate*/ /**<CNcomment: 11.025K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_12K   = 12000,   /**<12 kHz sampling rate*/ /**<CNcomment: 12K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_16K   = 16000,   /**<16 kHz sampling rate*/ /**<CNcomment: 16K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_22K   = 22050,   /**<22.050 kHz sampling rate*/ /**<CNcomment: 22.050K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_24K   = 24000,   /**<24 kHz sampling rate*/ /**<CNcomment: 24K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_32K   = 32000,   /**<32 kHz sampling rate*/ /**<CNcomment: 32K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_44K   = 44100,   /**<44.1 kHz sampling rate*/ /**<CNcomment: 44.1K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_48K   = 48000,   /**<48 kHz sampling rate*/ /**<CNcomment: 48K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_88K   = 88200,   /**<88.2 kHz sampling rate*/ /**<CNcomment: 88.2K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_96K   = 96000,   /**<96 kHz sampling rate*/ /**<CNcomment: 96K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_176K  = 176400,	/**<176 kHz sampling rate*/ /**<CNcomment: 176K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_192K  = 192000,  /**<192 kHz sampling rate*/ /**<CNcomment: 192K����Ƶ�� */

    HI_UNF_SAMPLE_RATE_BUTT
}HI_UNF_SAMPLE_RATE_E;

/**Defines the bit depth during audio sampling.*/
/**CNcomment: ������Ƶ����λ��ö��*/
typedef enum hiUNF_BIT_DEPTH_E
{
    HI_UNF_BIT_DEPTH_UNKNOWN =0,/**<Unknown*/ /**<CNcomment: δ֪����λ��  */
    HI_UNF_BIT_DEPTH_8  = 8,    /**< 8-bit depth*/ /**<CNcomment: 8λ����λ��  */
    HI_UNF_BIT_DEPTH_16 = 16,   /**<16-bit depth*/ /**<CNcomment: 16λ����λ�� */
    HI_UNF_BIT_DEPTH_18 = 18,   /**<18-bit depth*/ /**<CNcomment: 18λ����λ�� */
    HI_UNF_BIT_DEPTH_20 = 20,   /**<20-bit depth*/ /**<CNcomment: 20λ����λ�� */
    HI_UNF_BIT_DEPTH_24 = 24,   /**<24-bit depth*/ /**<CNcomment: 24λ����λ�� */
    HI_UNF_BIT_DEPTH_32 = 32,   /**<32-bit depth*/ /**<CNcomment: 32λ����λ�� */

    HI_UNF_BIT_DEPTH_BUTT
}HI_UNF_BIT_DEPTH_E;

/**extern end**/

typedef enum hiUNF_EDID_AUDIO_FORMAT_CODE_E
{
    HI_UNF_EDID_AUDIO_FORMAT_CODE_RESERVED  = 0x00,        
    HI_UNF_EDID_AUDIO_FORMAT_CODE_PCM,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_AC3,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_MPEG1,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_MP3,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_MPEG2,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_AAC,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_DTS,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_ATRAC,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_ONE_BIT,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_DDP,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_DTS_HD,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_MAT,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_DST,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_WMA_PRO,
    HI_UNF_EDID_AUDIO_FORMAT_CODE_BUTT,
  
}HI_UNF_EDID_AUDIO_FORMAT_CODE_E;

#define MAX_SAMPE_RATE_NUM 8
#define MAX_BIT_DEPTH_NUM  6

typedef struct hiUNF_EDID_AUDIO_INFO_S
{
    HI_UNF_EDID_AUDIO_FORMAT_CODE_E enAudFmtCode;
    HI_UNF_SAMPLE_RATE_E            enSupportSampleRate[MAX_SAMPE_RATE_NUM];   /*sample rate*/
    HI_U32                          u32SupportSampleRateNum;
    HI_U8                           u8AudChannel;      /*audio_channel*/
    /*sample bit depth,when audio format code is HI_UNF_EDID_AUDIO_FORMAT_CODE_PCM*/
    HI_UNF_BIT_DEPTH_E              bSupportBitDepth[MAX_BIT_DEPTH_NUM];
    HI_U32                          u32SupportBitDepthNum;
    /**enter max bit rate,when audio format code is HI_UNF_EDID_AUDIO_FORMAT_CODE_AC3 - HI_UNF_EDID_AUDIO_FORMAT_CODE_ATRAC**/
    HI_U32                          u32MaxBitRate;               
}HI_UNF_EDID_AUDIO_INFO_S;

typedef enum hiUNF_EDID_AUDIO_SPEAKER_E
{
    HI_UNF_EDID_AUDIO_SPEAKER_FL_FR   ,
    HI_UNF_EDID_AUDIO_SPEAKER_LFE     , 
    HI_UNF_EDID_AUDIO_SPEAKER_FC      , 
    HI_UNF_EDID_AUDIO_SPEAKER_RL_RR   ,
    HI_UNF_EDID_AUDIO_SPEAKER_RC      ,
    HI_UNF_EDID_AUDIO_SPEAKER_FLC_FRC , 
    HI_UNF_EDID_AUDIO_SPEAKER_RLC_RRC ,
    HI_UNF_EDID_AUDIO_SPEAKER_FLW_FRW ,
    HI_UNF_EDID_AUDIO_SPEAKER_FLH_FRH ,
    HI_UNF_EDID_AUDIO_SPEAKER_TC      ,
    HI_UNF_EDID_AUDIO_SPEAKER_FCH     ,
    HI_UNF_EDID_AUDIO_SPEAKER_BUTT    ,
} HI_UNF_EDID_AUDIO_SPEAKER_E;

typedef struct hiUNF_EDID_MANUFACTURE_INFO_E
{
    HI_U8               u8MfrsName[4];   /**<Manufacture name*//**<CNcomment:�豸���̱�ʶ */
    HI_U32              u32ProductCode;  /**<Product code*//**<CNcomment:�豸ID */
    HI_U32              u32SerialNumber; /**<Serial numeber of Manufacture*//**<CNcomment:�豸���к� */
    HI_U32              u32Week;        /**<the week of manufacture*//**<CNcomment:�豸��������(��) */
    HI_U32              u32Year;        /**<the year of manufacture*//**<CNcomment:�豸��������(��) */
}HI_UNF_EDID_MANUFACTURE_INFO_S;

typedef struct hiUNF_EDID_COLORIMETRY_S
{
    HI_BOOL    bxvYCC601      ; 
    HI_BOOL    bxvYCC709      ; 
    HI_BOOL    bsYCC601       ; 
    HI_BOOL    bAdobleYCC601  ; 
    HI_BOOL    bAdobleRGB     ;  
} HI_UNF_EDID_COLORIMETRY_S;

typedef struct hiUNF_EDID_COLOR_SPACE_S
{
    HI_BOOL    bRGB444        ;
    HI_BOOL    bYCbCr422      ; 
    HI_BOOL    bYCbCr444      ; 
} HI_UNF_EDID_COLOR_SPACE_S;

typedef struct hiUNF_EDID_CEC_ADDRESS_S
{
    HI_BOOL    bPhyAddrValid   ; 
    HI_U8      u8PhyAddrA      ; 
    HI_U8      u8PhyAddrB      ; 
    HI_U8      u8PhyAddrC      ; 
    HI_U8      u8PhyAddrD      ;  
} HI_UNF_EDID_CEC_ADDRESS_S;

typedef struct hiUNF_EDID_DEEP_COLOR_S
{
    HI_BOOL    bDeepColorY444   ; 
    HI_BOOL    bDeepColor30Bit  ; 
    HI_BOOL    bDeepColor36Bit  ; 
    HI_BOOL    bDeepColor48Bit  ; 
} HI_UNF_EDID_DEEP_COLOR_S;


/**HDMI InfoFrame struct type*/
/**CNcomment: HDMI ��Ϣ֡���ݽṹ���� */
typedef enum hiUNF_EDID_3D_TYPE_E
{
    HI_UNF_EDID_3D_FRAME_PACKETING                 = 0x00, /**<3d type:Frame Packing*//**<CNcomment:3d ģʽ:֡��װ*/
    HI_UNF_EDID_3D_FIELD_ALTERNATIVE               = 0x01, /**<3d type:Field alternative*//**<CNcomment:3d ģʽ:������*/
    HI_UNF_EDID_3D_LINE_ALTERNATIVE                = 0x02, /**<3d type:Line alternative*//**<CNcomment:3d ģʽ:�н���*/
    HI_UNF_EDID_3D_SIDE_BY_SIDE_FULL               = 0x03, /**<3d type:Side by side full*//**<CNcomment:3d ģʽ:����ʽ ����ȫ��*/
    HI_UNF_EDID_3D_L_DEPTH                         = 0x04, /**<3d type:L+depth*//**<CNcomment:3d ģʽ:L+DEPTH*/
    HI_UNF_EDID_3D_L_DEPTH_GRAPHICS_GRAPHICS_DEPTH = 0x05, /**<3d type:L+depth+Graphics+Graphics-depth*//**<CNcomment:3d ģʽ:L+depth+Graphics+Graphics-depth*/
    HI_UNF_EDID_3D_TOP_AND_BOTTOM                  = 0x06, /**<3d type:Top and Bottom*//**<CNcomment:3d ģʽ:����ģʽ*/
    HI_UNF_EDID_3D_SIDE_BY_SIDE_HALF               = 0x08, /**<3d type:Side by side half*//**<CNcomment:3d ģʽ:����ʽ ���Ұ��*/
    HI_UNF_EDID_3D_BUTT,                           //set 2d mode
}HI_UNF_EDID_3D_TYPE_E;

typedef struct hiUNF_EDID_3D_INFO_S
{
    HI_BOOL    bSupport3D  ; 
    HI_BOOL    bSupport3DType[HI_UNF_EDID_3D_BUTT] ; 
} HI_UNF_EDID_3D_INFO_S;

typedef struct hiUNF_EDID_TIMING_S
{
    HI_U32                        u32VFB;            /**<vertical front blank*//**<CNcomment:��ֱǰ����*/
    HI_U32                        u32VBB;            /**<vertical back blank*//**<CNcomment:��ֱ������*/
    HI_U32                        u32VACT;           /**<vertical active area*//**<CNcomment:��ֱ��Ч��*/
    HI_U32                        u32HFB;            /**<horizonal front blank*//**<CNcomment:ˮƽǰ����*/
    HI_U32                        u32HBB;            /**<horizonal back blank*//**<CNcomment:ˮƽ������*/
    HI_U32                        u32HACT;           /**<horizonal active area*/ /**<CNcomment:ˮƽ��Ч��*/
    HI_U32                        u32VPW;            /**<vertical sync pluse width*//**<CNcomment:��ֱ������*/
    HI_U32                        u32HPW;            /**<horizonal sync pluse width*/ /**<CNcomment:ˮƽ������*/
    HI_BOOL                       bIDV;            /**< flag of data valid signal is needed flip*//**<CNcomment:��Ч�����ź��Ƿ�ת*/
    HI_BOOL                       bIHS;            /**<flag of horizonal sync pluse is needed flip*//**<CNcomment:ˮƽͬ�������ź��Ƿ�ת*/
    HI_BOOL                       bIVS;            /**<flag of vertical sync pluse is needed flip*//**<CNcomment:��ֱͬ�������ź��Ƿ�ת*/
    HI_U32                        u32ImageWidth;
    HI_U32                        u32ImageHeight;
    HI_BOOL                       bInterlace;  
    HI_S32                        u32PixelClk;
} HI_UNF_EDID_TIMING_S;


#define HI_UNF_EDID_MAX_AUDIO_CAP_COUNT  16

/**HDMI sink capability of interface*/
/**CNcomment: HDMI sink �ӿ������� */
typedef struct hiUNF_EDID_BASE_INFO_S
{
    HI_BOOL                         bSupportHdmi;             /**<The Device suppot HDMI or not,the device is DVI when nonsupport HDMI*//**<CNcomment:�豸�Ƿ�֧��HDMI�������֧�֣���ΪDVI�豸.*/
    HI_UNF_ENC_FMT_E                enNativeFormat;      /**<The sink native video format*//**<CNcomment:��ʾ�豸����ֱ��� */
    HI_BOOL                         bSupportFormat[HI_UNF_ENC_FMT_BUTT]; /**<video capability,HI_TRUE:support the video display format;HI_FALSE:nonsupport the video display foramt*//**<CNcomment:��Ƶ������,HI_TRUE��ʾ֧��������ʾ��ʽ��HI_FALSE��ʾ��֧�� */
    HI_UNF_EDID_3D_INFO_S           st3DInfo;
    HI_UNF_EDID_DEEP_COLOR_S        stDeepColor;
    HI_UNF_EDID_COLORIMETRY_S       stColorMetry;
    HI_UNF_EDID_COLOR_SPACE_S       stColorSpace;            
    
    HI_UNF_EDID_AUDIO_INFO_S        stAudioInfo[HI_UNF_EDID_MAX_AUDIO_CAP_COUNT];
    HI_U32                          u32AudioInfoNum;
    HI_BOOL                         bSupportAudioSpeaker[HI_UNF_EDID_AUDIO_SPEAKER_BUTT];
    
    HI_U8                           u8ExtBlockNum;
    
    HI_U8                           u8Version;                /**<the version of manufacture*//**<CNcomment:�豸�汾�� */
    HI_U8                           u8Revision;               /**<the revision of manufacture*//**<CNcomment:�豸�Ӱ汾�� */
    HI_UNF_EDID_MANUFACTURE_INFO_S  stMfrsInfo;
 
    HI_UNF_EDID_CEC_ADDRESS_S       stCECAddr;
    HI_BOOL                         bSupportDVIDual;
    HI_BOOL                         bSupportsAI; 
    HI_UNF_EDID_TIMING_S            stPerferTiming; //for tc

} HI_UNF_EDID_BASE_INFO_S;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_EDID_H__ */
