/**
 * \file
 * \brief asf stream decode sample
 */
#include "hi_unf_common.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
//#include "HA.AUDIO.TRUEHD.decode.h"
#include "HA.AUDIO.DTSHD.decode.h"
#ifdef __FFMPEG_DECODE__
 #include "HA.AUDIO.FFMPEG_DECODE.decode.h"
#endif

#ifndef __ASF_PARSER_H__
 #define __ASF_PARSER_H__

#include <cutils/log.h>

#include "ModularDrmInterface.h"
#include "CryptoInterface.h"

#define HI_ERR_PLAYREADY(fmt, args...) \
 do{ \
         printf("[err] %s(), %d: " fmt, __FUNCTION__,__LINE__, ## args); \
 }while(0);

#if 0
 #define HI_FATAL_ASF(fmt...) \
    HI_TRACE(HI_LOG_LEVEL_FATAL, HI_ID_CA, fmt)

 #define HI_ERR_ASF(fmt...) \
    HI_TRACE(HI_LOG_LEVEL_ERROR, HI_ID_CA, fmt)

 #define HI_WARN_ASF(fmt...) \
    HI_TRACE(HI_LOG_LEVEL_WARNING, HI_ID_CA, fmt)

 #define HI_INFO_ASF(fmt...) \
    HI_TRACE(HI_LOG_LEVEL_INFO, HI_ID_CA, fmt)

#else

#define HI_FATAL_ASF(fmt, args...) \
do{ \
{\
    printf("[info] %s(), %d: " fmt, __FUNCTION__,__LINE__, ## args); \
}\
}while(0);


#define HI_ERR_ASF(fmt, args...) \
do{ \
{\
    printf("[info] %s(), %d: " fmt, __FUNCTION__,__LINE__, ## args); \
}\
}while(0);


#define HI_WARN_ASF(fmt, args...) \
do{ \
{\
    printf("[info] %s(), %d: " fmt, __FUNCTION__,__LINE__, ## args); \
}\
}while(0);

#ifdef DEBUG
#define HI_INFO_ASF(fmt, args...) \
do{ \
{\
    printf("[info] %s(), %d: " fmt, __FUNCTION__,__LINE__, ## args); \
}\
}while(0);

#define HI_RAW_DATA_INFO_ASF(fmt, args...) \
do{ \
{\
    printf(fmt,##args); \
}\
}while(0);
#else
#define HI_INFO_ASF(fmt, args...)
#define HI_RAW_DATA_INFO_ASF(fmt, args...)
#endif

#endif

typedef struct
{
    HI_U32 FormatDataSize;
    HI_U32 ImageWidth;
    HI_U32 ImageHeight;
    HI_U32 Reserved;
    HI_U32 BitsPerPixelCount;
    HI_U32 CompressionID;
    HI_U32 ImageSize;
    HI_U32 HorizotalPixelsPerMeter;
    HI_U32 VerticalPixelsPerMeter;
    HI_U32 ColorsUserdCount;
    HI_U32 ImportantColorCount;
    HI_U32 CodecSDataLength;
    HI_U8 *CodecSpecificData;
} ASF_WMV_VIDEO_Type_Specific_Data_S;

typedef struct
{
    HI_U16 wFormatTag;          /* format type,0x160->WMAV1,0x161->WMAV2, 0x162->WMAV3 */
    HI_U16 nChannels;            /* number of channels (i.e. mono, stereo...) */
    HI_U32 nSamplesPerSec;   /* sample rate */
    HI_U32 nAvgBytesPerSec;  /* for buffer estimation */
    HI_U16 nBlockAlign;          /* block size of data */
    HI_U16 wBitsPerSample;   /* number of bits per sample of mono data */
    HI_U16 cbSize;                /* the count in bytes of the size of */
    HI_U16 cbExtWord[20 /*16*/];      /* extra information (after cbSize).
                                      WMAV1: need  4 Bytes extra information at least
                                      WMAV2: need 10 Bytes extra information at least
                                      WMAV3: need 18 Bytes extra information at least
                                       */
} ASF_WMA_FORMAT_S;

typedef struct hiUNF_ASF_INFO_S
{} HI_UNF_ASF_INFO_S;

/**< ASF Stream Type definition */
enum
{
    HI_UNF_ASF_STREAM_TYPE_NULL,
    HI_UNF_ASF_STREAM_TYPE_VIDEO_MPEG2,
    HI_UNF_ASF_STREAM_TYPE_VIDEO_MPEG4,
    HI_UNF_ASF_STREAM_TYPE_VIDEO_H264,
    HI_UNF_ASF_STREAM_TYPE_VIDEO_H263,
    HI_UNF_ASF_STREAM_TYPE_VIDEO_VC1,
    HI_UNF_ASF_STREAM_TYPE_VIDEO_UNKNOW,

    HI_UNF_ASF_STREAM_TYPE_AUDIO_AAC,
    HI_UNF_ASF_STREAM_TYPE_AUDIO_MP3,
    HI_UNF_ASF_STREAM_TYPE_AUDIO_AC3,
    HI_UNF_ASF_STREAM_TYPE_AUDIO_EAC3,
    HI_UNF_ASF_STREAM_TYPE_AUDIO_DTS,
    HI_UNF_ASF_STREAM_TYPE_AUDIO_PCM,
    HI_UNF_ASF_STREAM_TYPE_AUDIO_DDPLUS,
    HI_UNF_ASF_STREAM_TYPE_AUDIO_WMA9,
    HI_UNF_ASF_STREAM_TYPE_AUDIO_UNKNOW,

    HI_UNF_ASF_STREAM_TYPE_BUTT
};

typedef struct hiUNF_ASF_OPEN_S
{
    HI_HANDLE hAVPlay;            /**<AVPlay Handle */
    HI_U32    u32VdecType;                             /**<ASF Video type, if do not open video decoder, please select HI_UNF_ASF_STREAM_TYPE_VIDEO_UNKNOW */
    HI_U32    u32AudioType;                            /**<ASF Audio type, if do not open video decoder, please select HI_UNF_ASF_STREAM_TYPE_AUDIO_UNKNOW */
    HI_U32    u32ASFBufferSize;                        /**<ASF packet Max size is 64KB, so it should be >= 100KB.*/
} HI_ASF_OPEN_S;

/**
\brief open ASF module
\attention \n
\param stOpenParam ASF open parameter
\retval ::HI_SUCCESS Success
\retval ::HI_FAILURE   Invalid
\see \n
none
*/
HI_S32 HI_ASF_Open(HI_ASF_OPEN_S *pstOpenParam, HI_HANDLE *handle);

/**
\brief Close ASF module
\attention \n
\param handle ASF handle
\retval ::HI_SUCCESS Success
\retval ::HI_FAILURE   Invalid
\see \n
none
*/
HI_S32 HI_ASF_Close(HI_HANDLE handle);

/**
\brief ASF Get Buffer
\attention \n
\param handle ASF Handle
\param u32ReqSize: the size of the buffer, must be less than the whole PS Buffer, the recommended size is 1 /n * whole buffer size
\retval ::HI_SUCCESS Success
\retval ::HI_FAILURE   Invalid
\see \n
none
*/
HI_S32 HI_ASF_GetBuffer(HI_HANDLE handle, HI_U32 u32ReqLen, HI_UNF_STREAM_BUF_S *pstData);

/*
brief: After ASF data is filled, send the data to PS module to process
attention: must be used with HI_UNF_PS_GetPSBuffer.
retval: 0:Success others:Failure
\see \n
none
*/
HI_S32 HI_ASF_PutBuffer(HI_HANDLE handle, HI_U32 u32ValidDatalen);

/**
 \brief ASF header parser, get the packet size and the file offset from start to Data Object.
 \attention \n
 \param handle ASF handle
\param asfHeaderBuffer: buffer of header
\param u32HeaderBufferLen:  size of header buffer
\param pLenToPacket:  file offset from start to Data Object
\param pPacketSize: one packet size
 \retval ::HI_SUCCESS success
 \retval ::HI_FAILURE  the header buffer too samll to parse
 \see \n
none
 */
HI_S32 HI_ASF_Head_Parser(HI_HANDLE handle, HI_U32 *pLenToPacket, HI_U32 *pPacketSize, HI_U8* asfHeaderBuffer,
                              HI_U32 u32HeaderBufferLen);


HI_S32 ASF_MediaDrm_Prepare(const HI_U8 uuid[16],Vector<HI_U8> &initData);
HI_S32 ASF_Crypto_Prepare(const HI_U8 uuid[16],Vector<HI_U8> &initData);
HI_S32 ASF_Crypto_release();
HI_S32 ASF_MediaDrm_Release();
HI_S32 ASF_MediaDrm_Decrypt(HI_U8* iv,HI_S32 ivLen,HI_CHAR* pSrc,HI_S32 s32srcSize,HI_VOID *pDst);
HI_VOID PRINT_VECTOR(Vector<HI_U8> &data,HI_CHAR *printinfo);

#endif /*__ASF_PARSER_H__*/
