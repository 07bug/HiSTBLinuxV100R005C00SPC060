#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>              /* inet_pton */
#include <netdb.h>                  /* gethostbyname */
#include <unistd.h>
#include <sys/socket.h>             /* socket/bind/etc. */

#include "asf_parser.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_adp_mpi.h"
#include "hi_error_mpi.h"
#include "asf_priv.h"
#include "hi_playready.h"
#include "hi_playreadyhttp.h"

#include "ModularDrmInterface.h"
#include "CryptoInterface.h"

//#define __ASF_VIDEO_DEBUG__
//#define __ASF_AUDIO_DEBUG__

#define ASF_BUFFER_MAX_SIZE 1 * 1024 * 1024
#define PAYLOAD_BUFFER_MAX_LENGTH 1 * 1024 * 1024

HI_IS_WHAT_ENCRYPT g_IsWhatEncryp = IS_WMDRM_ENCRYPT;

//static HI_CHAR *ps8ServerIp =NULL;
//static HI_U32 u32ServerPort = 0;

HI_U8 *g_replicatedData;
HI_U32 g_replicatedLength;
extern HI_BOOL isTvp;

/********************************PLAYREADY DEFINED GUID***************************************************/
const HI_U8 ASF_PROTECTION_SYSTEM_IDENTIFIER_OBJECT_GUID[] = {
    0x79, 0xF0, 0x04, 0x9A, 0x40, 0x98, 0x86, 0x42, 0xAB, 0x92, 0xE6, 0x5B, 0xE0, 0x88, 0x5F, 0x95
}; //79 F0 04 9A 40 98 86 42 AB 92 E6 5B E0 88 5F 95

const HI_U8 ASF_CONTENT_PROTECTION_SYSTEM_MICROSOFT_PLAYREADY_GUID[] = {
    0x10, 0x70, 0x63, 0xF4, 0xC3, 0x03, 0xCD, 0x42, 0xB9, 0x32, 0xB4, 0x8A, 0xDF, 0x3A, 0x6A, 0x54
}; //10 70 63 F4 C3 03 CD 42 B9 32 B4 8A DF 3A 6A 54

const HI_U8 ASF_STREAMTYPE_PLAYREADY_ENCRYPTED_COMMAND_MEDIA_GUID[] = {
    0x3A, 0x97, 0x83, 0x86, 0x39, 0x66, 0x3A, 0x46, 0xAB, 0xD7, 0x64, 0xF1, 0xCE, 0x3E, 0xEA, 0xE0
};

/************************************************************************************************/
const HI_U8 ASF_PAYLOAD_Extension_System_Encryption_Sample_ID[] = {
    0x4E, 0xB8, 0x98, 0x66, 0xFA, 0x0A, 0x30, 0x43, 0xAE, 0xB2, 0x1C, 0x0A, 0x98, 0xD7, 0xA4, 0x4D
};

const HI_U8 ASF_HEADER_OBJECT_GUID[] = {
    0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11, 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
};

const HI_U8 ASF_FILE_PROPERTIES_OBJECT_GUID[] = {
    0xA1, 0xDC, 0xAB, 0x8C, 0x47, 0xA9, 0xCF, 0x11, 0x8E, 0xE4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65
};

const HI_U8 ASF_STREAM_PROPERTIES_OBJECT_GUID[] = {
    0x91, 0x07, 0xDC, 0xB7, 0xB7, 0xA9, 0xCF, 0x11, 0x8E, 0xE6, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65
};

const HI_U8 ASF_HEADER_EXTERNSION_OBJECT_GUID[] = {
    0xb5, 0x03, 0xbf, 0x5f, 0x2E, 0xA9, 0xCF, 0x11, 0x8e, 0xe3, 0x00, 0xc0, 0x0c, 0x20, 0x53, 0x65
};

const HI_U8 ASF_CONTENT_ENCRYPTION_BOJECT_GUID[] = {
    0xfb, 0xb3, 0x11, 0x22, 0x23, 0xbd, 0xd2, 0x11, 0xb4, 0xb7, 0x00, 0xa0, 0xc9, 0x55, 0xfc, 0x6e
};

const HI_U8 ASF_EXTENDED_CONTENT_ENCRYPTION_GUID[] = {
    0x14, 0xe6, 0x8a, 0x29, 0x22, 0x26, 0x17, 0x4c, 0xb9, 0x35, 0xda, 0xe0, 0x7e, 0xe9, 0x28, 0x9c
};

const HI_U8 AS_EXTENED_STREAM_PROPERTIES_OBJECT_GUID[] = {
    0xCB, 0xA5, 0xE6, 0x14, 0x72, 0xC6, 0x32, 0x43, 0x83, 0x99, 0xA9, 0x69, 0x52, 0x06, 0x5B, 0x5A
};

const HI_U8 ASF_AUDIO_MEDIA_GUID[] = {
    0x40, 0x9E, 0x69, 0xF8, 0x4D, 0x5B, 0xCF, 0x11, 0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B
};

const HI_U8 ff_asf_audio_conceal_none[] = {
    // 0x40, 0xa4, 0xf1, 0x49, 0x4ece, 0x11d0, 0xa3, 0xac, 0x00, 0xa0, 0xc9, 0x03, 0x48, 0xf6
    // New value lifted from avifile
    0x00, 0x57, 0xfb, 0x20, 0x55, 0x5B, 0xCF, 0x11, 0xa8, 0xfd, 0x00, 0x80, 0x5f, 0x5c, 0x44, 0x2b
};

const HI_U8 ff_asf_audio_conceal_spread[] = {
    0x50, 0xCD, 0xC3, 0xBF, 0x8F, 0x61, 0xCF, 0x11, 0x8B, 0xB2, 0x00, 0xAA, 0x00, 0xB4, 0xE2, 0x20
};

const HI_U8 ASF_VIDEO_MEDIA_GUID[] = {
    0xC0, 0xEF, 0x19, 0xBC, 0x4D, 0x5B, 0xCF, 0x11, 0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B
};

const HI_U8 ff_asf_video_conceal_none[] = {
    0x00, 0x57, 0xFB, 0x20, 0x55, 0x5B, 0xCF, 0x11, 0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B
};

const HI_U8 ff_asf_command_stream[] = {
    0xC0, 0xCF, 0xDA, 0x59, 0xE6, 0x59, 0xD0, 0x11, 0xA3, 0xAC, 0x00, 0xA0, 0xC9, 0x03, 0x48, 0xF6
};

const HI_U8 ff_asf_comment_header[] = {
    0x33, 0x26, 0xb2, 0x75, 0x8E, 0x66, 0xCF, 0x11, 0xa6, 0xd9, 0x00, 0xaa, 0x00, 0x62, 0xce, 0x6c
};

const HI_U8 ff_asf_codec_comment_header[] = {
    0x40, 0x52, 0xD1, 0x86, 0x1D, 0x31, 0xD0, 0x11, 0xA3, 0xA4, 0x00, 0xA0, 0xC9, 0x03, 0x48, 0xF6
};
const HI_U8 ff_asf_codec_comment1_header[] = {
    0x41, 0x52, 0xd1, 0x86, 0x1D, 0x31, 0xD0, 0x11, 0xa3, 0xa4, 0x00, 0xa0, 0xc9, 0x03, 0x48, 0xf6
};

const HI_U8 ASF_DATA_OBJECT_GUID[] = {
    0x36, 0x26, 0xb2, 0x75, 0x8E, 0x66, 0xCF, 0x11, 0xa6, 0xd9, 0x00, 0xaa, 0x00, 0x62, 0xce, 0x6c
};

const HI_U8 ff_asf_header_reserve_1[] = {
    0x11, 0xd2, 0xd3, 0xab, 0xBA, 0xA9, 0xCF, 0x11, 0x8e, 0xe6, 0x00, 0xc0, 0x0c, 0x20, 0x53, 0x65
};

const HI_U8 ff_asf_extended_content_header[] = {
    0x40, 0xA4, 0xD0, 0xD2, 0x07, 0xE3, 0xD2, 0x11, 0x97, 0xF0, 0x00, 0xA0, 0xC9, 0x5E, 0xA8, 0x50
};

const HI_U8 ASF_SIMPLE_INDEX_OBJECT_GUID[] = {
    0x90, 0x08, 0x00, 0x33, 0xB1, 0xE5, 0xCF, 0x11, 0x89, 0xF4, 0x00, 0xA0, 0xC9, 0x03, 0x49, 0xCB
};

const HI_U8 ASF_INDEX_OBJECT_GUID[] = {
    0xD3, 0x29, 0xE2, 0xD6, 0xDA, 0x35, 0xD1, 0x11, 0x34, 0x90, 0x00, 0xA0, 0xC9, 0x03, 0x49, 0xBE
};

const HI_U8 ASF_MEDIA_OBJECT_INDEX_OBJECT_GUID[] = {
    0xF8, 0x03, 0xB1, 0xFE, 0xAD, 0x12, 0x64, 0x4C, 0x0F, 0x84, 0x2A, 0x1D, 0x2F, 0x7A, 0xD4, 0x8C
};

const HI_U8 ASF_TIMECODE_INDEX_OBJECT_GUID[] = {
    0xD0, 0x3F, 0xB7, 0x3C, 0x4A, 0x0C, 0x03, 0x48, 0x3D, 0x95, 0xED, 0xF7, 0xB6, 0x22, 0x8F, 0x0C
};

const HI_U8 ff_asf_ext_stream_embed_stream_header[] = {
    0xe2, 0x65, 0xfb, 0x3a, 0xEF, 0x47, 0xF2, 0x40, 0xac, 0x2c, 0x70, 0xa9, 0x0d, 0x71, 0xd3, 0x43
};

const HI_U8 ff_asf_ext_stream_audio_stream[] = {
    0x9d, 0x8c, 0x17, 0x31, 0xE1, 0x03, 0x28, 0x45, 0xb5, 0x82, 0x3d, 0xf9, 0xdb, 0x22, 0xf5, 0x03
};

const HI_U8 ff_asf_metadata_header[] = {
    0xea, 0xcb, 0xf8, 0xc5, 0xaf, 0x5b, 0x77, 0x48, 0x84, 0x67, 0xaa, 0x8c, 0x44, 0xfa, 0x4c, 0xca
};

const HI_U8 ff_asf_marker_header[] = {
    0x01, 0xCD, 0x87, 0xF4, 0x51, 0xA9, 0xCF, 0x11, 0x8E, 0xE6, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65
};

const HI_U8 ff_asf_language_guid[] = {
    0xa9, 0x46, 0x43, 0x7c, 0xe0, 0xef, 0xfc, 0x4b, 0xb2, 0x29, 0x39, 0x3e, 0xde, 0x41, 0x5c, 0x85
};

const HI_U8 ASF_DIGITAL_SIGNATURE_OBJECT_HEADER[] = {
    0xfc, 0xb3, 0x11, 0x22, 0x23, 0xbd, 0xd2, 0x11, 0xb4, 0xb7, 0x00, 0xa0, 0xc9, 0x55, 0xfc, 0x6e
};

typedef struct
{
    HI_U8 *pu8BufferBase;

    //HI_UNF_STREAM_BUF_S *asfPayloadData; //point to the malloc buffer base
    HI_U32              u32CurrentBufferLen; //current buffer len
    HI_U32              u32BufferSize;  //total size of buffer
    HI_UNF_STREAM_BUF_S stESVidBuffer;
    HI_U8 *             pu8Consumeraddr; //current written addr
    HI_U32              PTS;
} ASF_PAYLOAD_DEC_BUFFER_S;
ASF_PAYLOAD_DEC_BUFFER_S g_AsfBuffer;

typedef struct
{
    HI_U8  HeaderFlag;
    HI_U32 headerobjectNum;

    HI_U8  DataObjectFlag;
    HI_U32 DataObjectSize;
    HI_U32 TotalDataPackets;

    HI_U8  PacketFlag;
    HI_U32 CurrentDataPacketIndex;

    HI_U8 FILEID[16];

    HI_U32 PackSize;

    HI_U32 Video_Stream_Number;

    HI_U32 Audio_Stream_Number;
    HI_U32 Audio_Format_Tag;

    HI_PR_Content_Encryption_Ver1_S    EncryVer1;
    HI_PR_Content_Encryption_Ver2_S    EncryVer2;
    ASF_WMV_VIDEO_Type_Specific_Data_S VideoSpecific;
    ASF_WMA_FORMAT_S                   AudioSpecific;

    HI_U32 CurrentStreamNumber;
    HI_U32 CurrentMediaObjectNumber;
    HI_U32 LastMediaObjectNumber;
} ASF_STATAUS_S;

typedef struct
{
    HI_U8    *pu8BaseAddr;             //Base Address
    HI_U32    u32TotalSize;            //Total size
    HI_U32    u32ReadOffset;           //Read offset
    HI_U32    u32WriteOffset;          //Write offset
    HI_U32    u32RealEndOffset;        //Real End offset of valid data
    HI_BOOL   bLoopFlag;               //Data have loop around

    HI_U32 u32LastGetOffset;        //Last Get offset
    HI_U32 u32LastNeedSize;         //Last Need Size

    HI_U8    *pu8CosumerAddr;          //Cosumer Temp Address
} FIFO_CIRCLE_BUFFER_S;

typedef struct
{
    HI_U8    *pu8BaseAddr;              //Base Address
    HI_U32    u32MaxSize;                   //Max Buffer size

    HI_U32 u32ActualASFSize;         //Actual Read ASF file size;

    HI_U8    *pu8CosumerAddr;           //Cosumer Temp Address

    HI_U32 u32CurrentOffset;         //current buffer offset
} ASF_PACKET_BUFFER_S;

typedef struct
{
    HI_U32 u32FIFOOverflowNum;     //Count FIFO buffer overflow

    HI_U32 u32VideoESPackNum;     //Count Video pack input number
    HI_U32 u32AudioESPackNum;     //Count Audio pack input number

    HI_U32 u32VideoESOverflowNum; //Count Video ES buffer overflow
    HI_U32 u32AudioESOverflowNum; //Count Auido ES buffer overflow

    HI_U32 u32VideoPTS;           //record video latest PTS
    HI_U32 u32AudioPTS;           //record audio latest PTS

    HI_U32 u32FileParseOffset;
} STREAM_STATISTIC_S;

typedef struct
{
    HI_BOOL                OpenFlag;       //Open flag of these ASF Handle
    HI_UNF_AVPLAY_STATUS_E PlayState;

    pthread_mutex_t Mutex;     //Lock Mutex
    HI_U32          Mutex_Count;           //Mutex COunt

    pthread_t asfThreadID;  //ASF thread handle
    HI_U32    threadRunFlag;               //ASF thread running flag

    HI_HANDLE avhandle;     //Relative AV Play handle
    HI_U32   Videocodec_id;
    HI_U32   Audiocodec_id;
    HI_BOOL   VideoEnable;
    HI_BOOL   AudioEnable;

    //FIFO_CIRCLE_BUFFER_S     fifobuffer;    //Relative FIFO Circle-buffer
    ASF_PACKET_BUFFER_S asfbuffer;     //temporally store the asf file
    HI_UNF_STREAM_BUF_S stESVidBuffer;
    HI_UNF_STREAM_BUF_S stESAudBuffer;

    HI_U32 u32VdecType;  //ASF Video type
    HI_U32 u32AudioType; //ASF Audio type

    HI_UNF_ASF_INFO_S info;      //ASF information
    ASF_STATAUS_S     streaminfo;

    STREAM_STATISTIC_S statics;       //Statistic parameter

    FILE                    *pfvideoES;    //Video ES dump file
    FILE                    *pfaudioES;    //Audio ES dump file

    HI_PLAYREADY_Handle WMDRMhandle;

    /*add for modular drm */
    //ModularDrmInterface *pAsfDrmHandle;
    //CryptoInterface *pAsfCryptoHandle;
    HI_U8 uuid[16];
    Vector<HI_U8> drmInitdata;
    //Vector<HI_U8> sessionId;
    //Vector<HI_U8> keyId;
    HI_BOOL bneedDrm;
} HI_ASF_HANDLE;

#define ErrorAndReturn(x) do {\
        HI_ERR_ASF("Error: Return Code: %x, FUNC: %s, Line: %d.\n", ret, __FUNCTION__, __LINE__); \
        return x; \
    } while (0)

#define WaitAndContinue {\
        usleep(10 * 1000); \
        continue; \
    }

#define HI_STREAM_LOCK(ASFHandle) \
    do {                                                         \
        ASFHandle->Mutex_Count++;                                    \
        (void)pthread_mutex_lock(&(ASFHandle->Mutex));        \
    } while (0)

#define HI_STREAM_UNLOCK(ASFHandle) \
    do {                                                          \
        ASFHandle->Mutex_Count--;                                      \
        (void)pthread_mutex_unlock(&(ASFHandle->Mutex));      \
    } while (0)

#define STREAM_CHECK_NULL_PTR(ptr) \
    do {                                                     \
        if (NULL == (ptr))                                  \
        {                                                   \
            HI_ERR_ASF("poiner is NULL!!\n" );              \
            return HI_FAILURE;                              \
        }                                                   \
    } while (0)

/* get the handle of ASF */
#define D_STREAM_GET_HANDLE(enhandle, ASFHandle) \
    do {                                               \
        if (enhandle == 0) \
            return HI_FAILURE;\
        ASFHandle = (HI_ASF_HANDLE *)enhandle;        \
    } while (0)

static pthread_mutex_t AsfModualMutex;
static HI_S32 g_Count = 0;

static HI_VOID * ASF_Malloc(HI_U32 x)
{
    //printf("Malloc:%d\n", x);
    return malloc(x);
}

static HI_VOID ASF_Free(HI_VOID *x)
{
    //printf("Free:%d\n", x);
    free(x);
}

static HI_U32  Stream_Extract(HI_ASF_HANDLE *ASFHandle);
static HI_U8   Stream_GetOneByteAndMoveOn(ASF_PACKET_BUFFER_S *pstData);
static HI_U16  Stream_GetLittleEndianU16AndMoveOn(ASF_PACKET_BUFFER_S *pstData);
static HI_U32  Stream_GetLittleEndianU32AndMoveOn(ASF_PACKET_BUFFER_S *pstData);
static HI_VOID Stream_SeekBufferAndMoveOn(ASF_PACKET_BUFFER_S *pstData, HI_U32 SeekNum);
static HI_VOID Stream_CopyBufferAndMoveOn(ASF_PACKET_BUFFER_S *pstData, HI_U8 *DstPtr, HI_U32 CopyNum);
static HI_U32  ASF_Parse_HeaderObject(HI_ASF_HANDLE *ASFHandle, HI_U32 HeaderSize);

static int guidcmp(const void *g1, const void *g2)
{
    return memcmp(g1, g2, (sizeof(HI_U8) * 16));
}

extern HI_S32  ASF_StartPLAYREADY(HI_PR_Content_Encryption_Ver1_S *pVer1, HI_PR_Content_Encryption_Ver2_S *pVer2,
                                  HI_PLAYREADY_Handle *pWMDRMhandle, HI_IS_WHAT_ENCRYPT IsWhatEncryp);
extern HI_U32  ASF_StartAVplay(HI_HANDLE AVPlayHandle, HI_U32 enVideoCodec, HI_BOOL IsHighProfile,
                               HI_U32 u32AdecTypeCodec,
                               ASF_WMA_FORMAT_S  *pWMAPrivateData, HI_U32 *VideoEnable,
                               HI_U32 *AudioEnable);

enum CodecID
{
    CODEC_ID_NONE,

    /* video codecs */
    CODEC_ID_MPEG1VIDEO,
    CODEC_ID_MPEG2VIDEO, ///< preferred ID for MPEG-1/2 video decoding
    CODEC_ID_MPEG2VIDEO_XVMC,
    CODEC_ID_H261,
    CODEC_ID_H263,
    CODEC_ID_RV10,
    CODEC_ID_RV20,
    CODEC_ID_MJPEG,
    CODEC_ID_MJPEGB,
    CODEC_ID_LJPEG,
    CODEC_ID_SP5X,
    CODEC_ID_JPEGLS,
    CODEC_ID_MPEG4,
    CODEC_ID_RAWVIDEO,
    CODEC_ID_MSMPEG4V1,
    CODEC_ID_MSMPEG4V2,
    CODEC_ID_MSMPEG4V3,
    CODEC_ID_WMV1,
    CODEC_ID_WMV2,
    CODEC_ID_H263P,
    CODEC_ID_H263I,
    CODEC_ID_FLV1,
    CODEC_ID_SVQ1,
    CODEC_ID_SVQ3,
    CODEC_ID_DVVIDEO,
    CODEC_ID_HUFFYUV,
    CODEC_ID_CYUV,
    CODEC_ID_H264,
    CODEC_ID_INDEO3,
    CODEC_ID_VP3,
    CODEC_ID_THEORA,
    CODEC_ID_ASV1,
    CODEC_ID_ASV2,
    CODEC_ID_FFV1,
    CODEC_ID_4XM,
    CODEC_ID_VCR1,
    CODEC_ID_CLJR,
    CODEC_ID_MDEC,
    CODEC_ID_ROQ,
    CODEC_ID_INTERPLAY_VIDEO,
    CODEC_ID_XAN_WC3,
    CODEC_ID_XAN_WC4,
    CODEC_ID_RPZA,
    CODEC_ID_CINEPAK,
    CODEC_ID_WS_VQA,
    CODEC_ID_MSRLE,
    CODEC_ID_MSVIDEO1,
    CODEC_ID_IDCIN,
    CODEC_ID_8BPS,
    CODEC_ID_SMC,
    CODEC_ID_FLIC,
    CODEC_ID_TRUEMOTION1,
    CODEC_ID_VMDVIDEO,
    CODEC_ID_MSZH,
    CODEC_ID_ZLIB,
    CODEC_ID_QTRLE,
    CODEC_ID_SNOW,
    CODEC_ID_TSCC,
    CODEC_ID_ULTI,
    CODEC_ID_QDRAW,
    CODEC_ID_VIXL,
    CODEC_ID_QPEG,
#if LIBAVCODEC_VERSION_MAJOR < 53
    CODEC_ID_XVID,
#endif
    CODEC_ID_PNG,
    CODEC_ID_PPM,
    CODEC_ID_PBM,
    CODEC_ID_PGM,
    CODEC_ID_PGMYUV,
    CODEC_ID_PAM,
    CODEC_ID_FFVHUFF,
    CODEC_ID_RV30,
    CODEC_ID_RV40,
    CODEC_ID_VC1,
    CODEC_ID_WMV3,
    CODEC_ID_LOCO,
    CODEC_ID_WNV1,
    CODEC_ID_AASC,
    CODEC_ID_INDEO2,
    CODEC_ID_FRAPS,
    CODEC_ID_TRUEMOTION2,
    CODEC_ID_BMP,
    CODEC_ID_CSCD,
    CODEC_ID_MMVIDEO,
    CODEC_ID_ZMBV,
    CODEC_ID_AVS,
    CODEC_ID_SMACKVIDEO,
    CODEC_ID_NUV,
    CODEC_ID_KMVC,
    CODEC_ID_FLASHSV,
    CODEC_ID_CAVS,
    CODEC_ID_JPEG2000,
    CODEC_ID_VMNC,
    CODEC_ID_VP5,
    CODEC_ID_VP6,
    CODEC_ID_VP6F,
    CODEC_ID_TARGA,
    CODEC_ID_DSICINVIDEO,
    CODEC_ID_TIERTEXSEQVIDEO,
    CODEC_ID_TIFF,
    CODEC_ID_GIF,
    CODEC_ID_FFH264,
    CODEC_ID_DXA,
    CODEC_ID_DNXHD,
    CODEC_ID_THP,
    CODEC_ID_SGI,
    CODEC_ID_C93,
    CODEC_ID_BETHSOFTVID,
    CODEC_ID_PTX,
    CODEC_ID_TXD,
    CODEC_ID_VP6A,
    CODEC_ID_AMV,
    CODEC_ID_VB,
    CODEC_ID_PCX,
    CODEC_ID_SUNRAST,
    CODEC_ID_INDEO4,
    CODEC_ID_INDEO5,
    CODEC_ID_MIMIC,
    CODEC_ID_RL2,
    CODEC_ID_8SVX_EXP,
    CODEC_ID_8SVX_FIB,
    CODEC_ID_ESCAPE124,
    CODEC_ID_DIRAC,
    CODEC_ID_BFI,
    CODEC_ID_CMV,
    CODEC_ID_MOTIONPIXELS,
    CODEC_ID_TGV,
    CODEC_ID_TGQ,
    CODEC_ID_TQI,
    CODEC_ID_AURA,
    CODEC_ID_AURA2,
    CODEC_ID_V210X,
    CODEC_ID_TMV,
    CODEC_ID_V210,
    CODEC_ID_DPX,
    CODEC_ID_MAD,
    CODEC_ID_FRWU,
    CODEC_ID_FLASHSV2,
    CODEC_ID_CDGRAPHICS,
    CODEC_ID_R210,
    CODEC_ID_ANM,
    CODEC_ID_BINKVIDEO,
    CODEC_ID_IFF_ILBM,
    CODEC_ID_IFF_BYTERUN1,
    CODEC_ID_KGV1,
    CODEC_ID_YOP,
    CODEC_ID_VP8,

    /* various PCM "codecs" */
    CODEC_ID_PCM_S16LE = 0x10000,
    CODEC_ID_PCM_S16BE,
    CODEC_ID_PCM_U16LE,
    CODEC_ID_PCM_U16BE,
    CODEC_ID_PCM_S8,
    CODEC_ID_PCM_U8,
    CODEC_ID_PCM_MULAW,
    CODEC_ID_PCM_ALAW,
    CODEC_ID_PCM_S32LE,
    CODEC_ID_PCM_S32BE,
    CODEC_ID_PCM_U32LE,
    CODEC_ID_PCM_U32BE,
    CODEC_ID_PCM_S24LE,
    CODEC_ID_PCM_S24BE,
    CODEC_ID_PCM_U24LE,
    CODEC_ID_PCM_U24BE,
    CODEC_ID_PCM_S24DAUD,
    CODEC_ID_PCM_ZORK,
    CODEC_ID_PCM_S16LE_PLANAR,
    CODEC_ID_PCM_DVD,
    CODEC_ID_PCM_F32BE,
    CODEC_ID_PCM_F32LE,
    CODEC_ID_PCM_F64BE,
    CODEC_ID_PCM_F64LE,
    CODEC_ID_PCM_BLURAY,

    /* various ADPCM codecs */
    CODEC_ID_ADPCM_IMA_QT = 0x11000,
    CODEC_ID_ADPCM_IMA_WAV,
    CODEC_ID_ADPCM_IMA_DK3,
    CODEC_ID_ADPCM_IMA_DK4,
    CODEC_ID_ADPCM_IMA_WS,
    CODEC_ID_ADPCM_IMA_SMJPEG,
    CODEC_ID_ADPCM_MS,
    CODEC_ID_ADPCM_4XM,
    CODEC_ID_ADPCM_XA,
    CODEC_ID_ADPCM_ADX,
    CODEC_ID_ADPCM_EA,
    CODEC_ID_ADPCM_G726,
    CODEC_ID_ADPCM_CT,
    CODEC_ID_ADPCM_SWF,
    CODEC_ID_ADPCM_YAMAHA,
    CODEC_ID_ADPCM_SBPRO_4,
    CODEC_ID_ADPCM_SBPRO_3,
    CODEC_ID_ADPCM_SBPRO_2,
    CODEC_ID_ADPCM_THP,
    CODEC_ID_ADPCM_IMA_AMV,
    CODEC_ID_ADPCM_EA_R1,
    CODEC_ID_ADPCM_EA_R3,
    CODEC_ID_ADPCM_EA_R2,
    CODEC_ID_ADPCM_IMA_EA_SEAD,
    CODEC_ID_ADPCM_IMA_EA_EACS,
    CODEC_ID_ADPCM_EA_XAS,
    CODEC_ID_ADPCM_EA_MAXIS_XA,
    CODEC_ID_ADPCM_IMA_ISS,

    /* AMR */
    CODEC_ID_AMR_NB = 0x12000,
    CODEC_ID_AMR_WB,

    /* RealAudio codecs*/
    CODEC_ID_RA_144 = 0x13000,
    CODEC_ID_RA_288,

    /* various DPCM codecs */
    CODEC_ID_ROQ_DPCM = 0x14000,
    CODEC_ID_INTERPLAY_DPCM,
    CODEC_ID_XAN_DPCM,
    CODEC_ID_SOL_DPCM,

    /* audio codecs */
    CODEC_ID_MP2 = 0x15000,
    CODEC_ID_MP3, ///< preferred ID for decoding MPEG audio layer 1, 2 or 3
    CODEC_ID_AAC,
    CODEC_ID_AC3,
    CODEC_ID_DTS,
    CODEC_ID_VORBIS,
    CODEC_ID_DVAUDIO,
    CODEC_ID_WMAV1,
    CODEC_ID_WMAV2,
    CODEC_ID_MACE3,
    CODEC_ID_MACE6,
    CODEC_ID_VMDAUDIO,
    CODEC_ID_SONIC,
    CODEC_ID_SONIC_LS,
    CODEC_ID_FLAC,
    CODEC_ID_MP3ADU,
    CODEC_ID_MP3ON4,
    CODEC_ID_SHORTEN,
    CODEC_ID_ALAC,
    CODEC_ID_WESTWOOD_SND1,
    CODEC_ID_GSM, ///< as in Berlin toast format
    CODEC_ID_QDM2,
    CODEC_ID_COOK,
    CODEC_ID_TRUESPEECH,
    CODEC_ID_TTA,
    CODEC_ID_SMACKAUDIO,
    CODEC_ID_QCELP,
    CODEC_ID_WAVPACK,
    CODEC_ID_DSICINAUDIO,
    CODEC_ID_IMC,
    CODEC_ID_MUSEPACK7,
    CODEC_ID_MLP,
    CODEC_ID_GSM_MS, /* as found in WAV */
    CODEC_ID_ATRAC3,
    CODEC_ID_VOXWARE,
    CODEC_ID_APE,
    CODEC_ID_NELLYMOSER,
    CODEC_ID_MUSEPACK8,
    CODEC_ID_SPEEX,
    CODEC_ID_WMAVOICE,
    CODEC_ID_WMAPRO,
    CODEC_ID_WMALOSSLESS,
    CODEC_ID_ATRAC3P,
    CODEC_ID_EAC3,
    CODEC_ID_SIPR,
    CODEC_ID_MP1,
    CODEC_ID_TWINVQ,
    CODEC_ID_TRUEHD,
    CODEC_ID_MP4ALS,
    CODEC_ID_ATRAC1,
    CODEC_ID_BINKAUDIO_RDFT,
    CODEC_ID_BINKAUDIO_DCT,

    /* subtitle codecs */
    CODEC_ID_DVD_SUBTITLE = 0x17000,
    CODEC_ID_DVB_SUBTITLE,
    CODEC_ID_TEXT,  ///< raw UTF-8 text
    CODEC_ID_XSUB,
    CODEC_ID_SSA,
    CODEC_ID_MOV_TEXT,
    CODEC_ID_HDMV_PGS_SUBTITLE,
    CODEC_ID_DVB_TELETEXT,

    /* other specific kind of codecs (generally used for attachments) */
    CODEC_ID_TTF = 0x18000,

    CODEC_ID_PROBE = 0x19000, ///< codec_id is not known (like CODEC_ID_NONE) but lavf should attempt to identify it

    CODEC_ID_MPEG2TS = 0x20000,/**< _FAKE_ codec to indicate a raw MPEG-2 TS
                                * stream (only used by libavformat) */
};

#define MKTAG(a, b, c, d) (a | (b << 8) | (c << 16) | (d << 24))
typedef struct AVCodecTag
{
    enum CodecID id;
    unsigned int tag;
} AVCodecTag;

const AVCodecTag ff_codec_bmp_tags[] = {
    { CODEC_ID_H264,        MKTAG('H', '2', '6', '4') },
    { CODEC_ID_H264,        MKTAG('h', '2', '6', '4') },
    { CODEC_ID_H264,        MKTAG('X', '2', '6', '4') },
    { CODEC_ID_H264,        MKTAG('x', '2', '6', '4') },
    { CODEC_ID_H264,        MKTAG('a', 'v', 'c', '1') },
    { CODEC_ID_H264,        MKTAG('V', 'S', 'S', 'H') },
    { CODEC_ID_H263,        MKTAG('H', '2', '6', '3') },
    { CODEC_ID_H263,        MKTAG('X', '2', '6', '3') },
    { CODEC_ID_H263,        MKTAG('T', '2', '6', '3') },
    { CODEC_ID_H263,        MKTAG('L', '2', '6', '3') },
    { CODEC_ID_H263,        MKTAG('V', 'X', '1', 'K') },
    { CODEC_ID_H263,        MKTAG('Z', 'y', 'G', 'o') },
    { CODEC_ID_H263P,        MKTAG('H', '2', '6', '3') },
    { CODEC_ID_H263I,        MKTAG('I', '2', '6', '3') }, /* intel h263 */
    { CODEC_ID_H261,        MKTAG('H', '2', '6', '1') },
    { CODEC_ID_H263P,        MKTAG('U', '2', '6', '3') },
    { CODEC_ID_H263P,        MKTAG('v', 'i', 'v', '1') },
    { CODEC_ID_MPEG4,        MKTAG('F', 'M', 'P', '4') },
    { CODEC_ID_MPEG4,        MKTAG('D', 'I', 'V', 'X') },
    { CODEC_ID_MPEG4,        MKTAG('D', 'X', '5', '0') },
    { CODEC_ID_MPEG4,        MKTAG('X', 'V', 'I', 'D') },
    { CODEC_ID_MPEG4,        MKTAG('M', 'P', '4', 'S') },
    { CODEC_ID_MPEG4,        MKTAG('M', '4', 'S', '2') },
    { CODEC_ID_MPEG4,        MKTAG( 4,    0,   0,  0 ) }, /* some broken avi use this */
    { CODEC_ID_MPEG4,        MKTAG('D', 'I', 'V', '1') },
    { CODEC_ID_MPEG4,        MKTAG('B', 'L', 'Z', '0') },
    { CODEC_ID_MPEG4,        MKTAG('m', 'p', '4', 'v') },
    { CODEC_ID_MPEG4,        MKTAG('U', 'M', 'P', '4') },
    { CODEC_ID_MPEG4,        MKTAG('W', 'V', '1', 'F') },
    { CODEC_ID_MPEG4,        MKTAG('S', 'E', 'D', 'G') },
    { CODEC_ID_MPEG4,        MKTAG('R', 'M', 'P', '4') },
    { CODEC_ID_MPEG4,        MKTAG('3', 'I', 'V', '2') },
    { CODEC_ID_MPEG4,        MKTAG('F', 'F', 'D', 'S') },
    { CODEC_ID_MPEG4,        MKTAG('F', 'V', 'F', 'W') },
    { CODEC_ID_MPEG4,        MKTAG('D', 'C', 'O', 'D') },
    { CODEC_ID_MPEG4,        MKTAG('M', 'V', 'X', 'M') },
    { CODEC_ID_MPEG4,        MKTAG('P', 'M', '4', 'V') },
    { CODEC_ID_MPEG4,        MKTAG('S', 'M', 'P', '4') },
    { CODEC_ID_MPEG4,        MKTAG('D', 'X', 'G', 'M') },
    { CODEC_ID_MPEG4,        MKTAG('V', 'I', 'D', 'M') },
    { CODEC_ID_MPEG4,        MKTAG('M', '4', 'T', '3') },
    { CODEC_ID_MPEG4,        MKTAG('G', 'E', 'O', 'X') },
    { CODEC_ID_MPEG4,        MKTAG('H', 'D', 'X', '4') }, /* flipped video */
    { CODEC_ID_MPEG4,        MKTAG('D', 'M', 'K', '2') },
    { CODEC_ID_MPEG4,        MKTAG('D', 'I', 'G', 'I') },
    { CODEC_ID_MPEG4,        MKTAG('I', 'N', 'M', 'C') },
    { CODEC_ID_MPEG4,        MKTAG('E', 'P', 'H', 'V') }, /* Ephv MPEG-4 */
    { CODEC_ID_MPEG4,        MKTAG('E', 'M', '4', 'A') },
    { CODEC_ID_MPEG4,        MKTAG('M', '4', 'C', 'C') }, /* Divio MPEG-4 */
    { CODEC_ID_MPEG4,        MKTAG('S', 'N', '4', '0') },
    { CODEC_ID_MPEG4,        MKTAG('V', 'S', 'P', 'X') },
    { CODEC_ID_MPEG4,        MKTAG('U', 'L', 'D', 'X') },
    { CODEC_ID_MPEG4,        MKTAG('G', 'E', 'O', 'V') },
    { CODEC_ID_MPEG4,        MKTAG('S', 'I', 'P', 'P') }, /* Samsung SHR-6040 */
    { CODEC_ID_MSMPEG4V3,    MKTAG('D', 'I', 'V', '3') }, /* default signature when using MSMPEG4 */
    { CODEC_ID_MSMPEG4V3,    MKTAG('M', 'P', '4', '3') },
    { CODEC_ID_MSMPEG4V3,    MKTAG('M', 'P', 'G', '3') },
    { CODEC_ID_MSMPEG4V3,    MKTAG('D', 'I', 'V', '5') },
    { CODEC_ID_MSMPEG4V3,    MKTAG('D', 'I', 'V', '6') },
    { CODEC_ID_MSMPEG4V3,    MKTAG('D', 'I', 'V', '4') },
    { CODEC_ID_MSMPEG4V3,    MKTAG('D', 'V', 'X', '3') },
    { CODEC_ID_MSMPEG4V3,    MKTAG('A', 'P', '4', '1') },
    { CODEC_ID_MSMPEG4V3,    MKTAG('C', 'O', 'L', '1') },
    { CODEC_ID_MSMPEG4V3,    MKTAG('C', 'O', 'L', '0') },
    { CODEC_ID_MSMPEG4V2,    MKTAG('M', 'P', '4', '2') },
    { CODEC_ID_MSMPEG4V2,    MKTAG('D', 'I', 'V', '2') },
    { CODEC_ID_MSMPEG4V1,    MKTAG('M', 'P', 'G', '4') },
    { CODEC_ID_MSMPEG4V1,    MKTAG('M', 'P', '4', '1') },
    { CODEC_ID_WMV1,        MKTAG('W', 'M', 'V', '1') },
    { CODEC_ID_WMV2,        MKTAG('W', 'M', 'V', '2') },
    { CODEC_ID_DVVIDEO,        MKTAG('d', 'v', 's', 'd') },
    { CODEC_ID_DVVIDEO,        MKTAG('d', 'v', 'h', 'd') },
    { CODEC_ID_DVVIDEO,        MKTAG('d', 'v', 'h', '1') },
    { CODEC_ID_DVVIDEO,        MKTAG('d', 'v', 's', 'l') },
    { CODEC_ID_DVVIDEO,        MKTAG('d', 'v', '2', '5') },
    { CODEC_ID_DVVIDEO,        MKTAG('d', 'v', '5', '0') },
    { CODEC_ID_DVVIDEO,        MKTAG('c', 'd', 'v', 'c') }, /* Canopus DV */
    { CODEC_ID_DVVIDEO,        MKTAG('C', 'D', 'V', 'H') }, /* Canopus DV */
    { CODEC_ID_DVVIDEO,        MKTAG('d', 'v', 'c', ' ') },
    { CODEC_ID_DVVIDEO,        MKTAG('d', 'v', 'c', 's') },
    { CODEC_ID_DVVIDEO,        MKTAG('d', 'v', 'h', '1') },
    { CODEC_ID_MPEG1VIDEO,    MKTAG('m', 'p', 'g', '1') },
    { CODEC_ID_MPEG1VIDEO,    MKTAG('m', 'p', 'g', '2') },
    { CODEC_ID_MPEG2VIDEO,    MKTAG('m', 'p', 'g', '2') },
    { CODEC_ID_MPEG2VIDEO,    MKTAG('M', 'P', 'E', 'G') },
    { CODEC_ID_MPEG1VIDEO,    MKTAG('P', 'I', 'M', '1') },
    { CODEC_ID_MPEG2VIDEO,    MKTAG('P', 'I', 'M', '2') },
    { CODEC_ID_MPEG1VIDEO,    MKTAG('V', 'C', 'R', '2') },
    { CODEC_ID_MPEG1VIDEO,    MKTAG( 1,    0,   0,  16) },
    { CODEC_ID_MPEG2VIDEO,    MKTAG( 2,    0,   0,  16) },
    { CODEC_ID_MPEG4,        MKTAG( 4,    0,   0,  16) },
    { CODEC_ID_MPEG2VIDEO,    MKTAG('D', 'V', 'R', ' ') },
    { CODEC_ID_MPEG2VIDEO,    MKTAG('M', 'M', 'E', 'S') },
    { CODEC_ID_MPEG2VIDEO,    MKTAG('L', 'M', 'P', '2') }, /* Lead MPEG2 in avi */
    { CODEC_ID_MPEG2VIDEO,    MKTAG('s', 'l', 'i', 'f') },
    { CODEC_ID_MPEG2VIDEO,    MKTAG('E', 'M', '2', 'V') },
    { CODEC_ID_MJPEG,        MKTAG('M', 'J', 'P', 'G') },
    { CODEC_ID_MJPEG,        MKTAG('L', 'J', 'P', 'G') },
    { CODEC_ID_MJPEG,        MKTAG('d', 'm', 'b', '1') },
    { CODEC_ID_MJPEG,        MKTAG('m', 'j', 'p', 'a') },
    { CODEC_ID_LJPEG,        MKTAG('L', 'J', 'P', 'G') },
    { CODEC_ID_MJPEG,        MKTAG('J', 'P', 'G', 'L') }, /* Pegasus lossless JPEG */
    { CODEC_ID_JPEGLS,        MKTAG('M', 'J', 'L', 'S') }, /* JPEG-LS custom FOURCC for avi - encoder */
    { CODEC_ID_MJPEG,        MKTAG('M', 'J', 'L', 'S') }, /* JPEG-LS custom FOURCC for avi - decoder */
    { CODEC_ID_MJPEG,        MKTAG('j', 'p', 'e', 'g') },
    { CODEC_ID_MJPEG,        MKTAG('I', 'J', 'P', 'G') },
    { CODEC_ID_MJPEG,        MKTAG('A', 'V', 'R', 'n') },
    { CODEC_ID_MJPEG,        MKTAG('A', 'C', 'D', 'V') },
    { CODEC_ID_MJPEG,        MKTAG('Q', 'I', 'V', 'G') },
    { CODEC_ID_MJPEG,        MKTAG('S', 'L', 'M', 'J') }, /* SL M-JPEG */
    { CODEC_ID_MJPEG,        MKTAG('C', 'J', 'P', 'G') }, /* Creative Webcam JPEG */
    { CODEC_ID_MJPEG,        MKTAG('I', 'J', 'L', 'V') }, /* Intel JPEG Library Video Codec */
    { CODEC_ID_MJPEG,        MKTAG('M', 'V', 'J', 'P') }, /* Midvid JPEG Video Codec */
    { CODEC_ID_MJPEG,        MKTAG('A', 'V', 'I', '1') },
    { CODEC_ID_MJPEG,        MKTAG('A', 'V', 'I', '2') },
    { CODEC_ID_MJPEG,        MKTAG('M', 'T', 'S', 'J') },
    { CODEC_ID_MJPEG,        MKTAG('Z', 'J', 'P', 'G') }, /* Paradigm Matrix M-JPEG Codec */
    { CODEC_ID_HUFFYUV,        MKTAG('H', 'F', 'Y', 'U') },
    { CODEC_ID_FFVHUFF,        MKTAG('F', 'F', 'V', 'H') },
    { CODEC_ID_CYUV,        MKTAG('C', 'Y', 'U', 'V') },
    { CODEC_ID_RAWVIDEO,    MKTAG( 0,    0,   0,  0 ) },
    { CODEC_ID_RAWVIDEO,    MKTAG( 3,    0,   0,  0 ) },
    { CODEC_ID_RAWVIDEO,    MKTAG('I', '4', '2', '0') },
    { CODEC_ID_RAWVIDEO,    MKTAG('Y', 'U', 'Y', '2') },
    { CODEC_ID_RAWVIDEO,    MKTAG('Y', '4', '2', '2') },
    { CODEC_ID_RAWVIDEO,    MKTAG('V', '4', '2', '2') },
    { CODEC_ID_RAWVIDEO,    MKTAG('Y', 'U', 'N', 'V') },
    { CODEC_ID_RAWVIDEO,    MKTAG('U', 'Y', 'N', 'V') },
    { CODEC_ID_RAWVIDEO,    MKTAG('U', 'Y', 'N', 'Y') },
    { CODEC_ID_RAWVIDEO,    MKTAG('u', 'y', 'v', '1') },
    { CODEC_ID_RAWVIDEO,    MKTAG('2', 'V', 'u', '1') },
    { CODEC_ID_RAWVIDEO,    MKTAG('2', 'v', 'u', 'y') },
    { CODEC_ID_RAWVIDEO,    MKTAG('P', '4', '2', '2') },
    { CODEC_ID_RAWVIDEO,    MKTAG('Y', 'V', '1', '2') },
    { CODEC_ID_RAWVIDEO,    MKTAG('U', 'Y', 'V', 'Y') },
    { CODEC_ID_RAWVIDEO,    MKTAG('V', 'Y', 'U', 'Y') },
    { CODEC_ID_RAWVIDEO,    MKTAG('I', 'Y', 'U', 'V') },
    { CODEC_ID_RAWVIDEO,    MKTAG('Y', '8', '0', '0') },
    { CODEC_ID_RAWVIDEO,    MKTAG('H', 'D', 'Y', 'C') },
    { CODEC_ID_RAWVIDEO,    MKTAG('Y', 'V', 'U', '9') },
    { CODEC_ID_RAWVIDEO,    MKTAG('V', 'D', 'T', 'Z') }, /* SoftLab-NSK VideoTizer */
    { CODEC_ID_FRWU,        MKTAG('F', 'R', 'W', 'U') },
    { CODEC_ID_R210,        MKTAG('r', '2', '1', '0') },
    { CODEC_ID_V210,        MKTAG('v', '2', '1', '0') },
    { CODEC_ID_INDEO3,        MKTAG('I', 'V', '3', '1') },
    { CODEC_ID_INDEO3,        MKTAG('I', 'V', '3', '2') },
    { CODEC_ID_INDEO4,        MKTAG('I', 'V', '4', '1') },
    { CODEC_ID_INDEO5,        MKTAG('I', 'V', '5', '0') },
    { CODEC_ID_VP3,            MKTAG('V', 'P', '3', '1') },
    { CODEC_ID_VP3,            MKTAG('V', 'P', '3', '0') },
    { CODEC_ID_VP5,            MKTAG('V', 'P', '5', '0') },
    { CODEC_ID_VP6,            MKTAG('V', 'P', '6', '0') },
    { CODEC_ID_VP6,            MKTAG('V', 'P', '6', '1') },
    { CODEC_ID_VP6,            MKTAG('V', 'P', '6', '2') },
    { CODEC_ID_VP6F,        MKTAG('V', 'P', '6', 'F') },
    { CODEC_ID_VP6F,        MKTAG('F', 'L', 'V', '4') },
    { CODEC_ID_VP8,            MKTAG('V', 'P', '8', '0') },
    { CODEC_ID_ASV1,        MKTAG('A', 'S', 'V', '1') },
    { CODEC_ID_ASV2,        MKTAG('A', 'S', 'V', '2') },
    { CODEC_ID_VCR1,        MKTAG('V', 'C', 'R', '1') },
    { CODEC_ID_FFV1,        MKTAG('F', 'F', 'V', '1') },
    { CODEC_ID_XAN_WC4,        MKTAG('X', 'x', 'a', 'n') },
    { CODEC_ID_MIMIC,        MKTAG('L', 'M', '2', '0') },
    { CODEC_ID_MSRLE,        MKTAG('m', 'r', 'l', 'e') },
    { CODEC_ID_MSRLE,        MKTAG( 1,    0,   0,  0 ) },
    { CODEC_ID_MSRLE,        MKTAG( 2,    0,   0,  0 ) },
    { CODEC_ID_MSVIDEO1,    MKTAG('M', 'S', 'V', 'C') },
    { CODEC_ID_MSVIDEO1,    MKTAG('m', 's', 'v', 'c') },
    { CODEC_ID_MSVIDEO1,    MKTAG('C', 'R', 'A', 'M') },
    { CODEC_ID_MSVIDEO1,    MKTAG('c', 'r', 'a', 'm') },
    { CODEC_ID_MSVIDEO1,    MKTAG('W', 'H', 'A', 'M') },
    { CODEC_ID_MSVIDEO1,    MKTAG('w', 'h', 'a', 'm') },
    { CODEC_ID_CINEPAK,        MKTAG('c', 'v', 'i', 'd') },
    { CODEC_ID_TRUEMOTION1, MKTAG('D', 'U', 'C', 'K') },
    { CODEC_ID_TRUEMOTION1, MKTAG('P', 'V', 'E', 'Z') },
    { CODEC_ID_MSZH,        MKTAG('M', 'S', 'Z', 'H') },
    { CODEC_ID_ZLIB,        MKTAG('Z', 'L', 'I', 'B') },
    { CODEC_ID_SNOW,        MKTAG('S', 'N', 'O', 'W') },
    { CODEC_ID_4XM,            MKTAG('4', 'X', 'M', 'V') },
    { CODEC_ID_FLV1,        MKTAG('F', 'L', 'V', '1') },
    { CODEC_ID_FLASHSV,        MKTAG('F', 'S', 'V', '1') },
    { CODEC_ID_SVQ1,        MKTAG('s', 'v', 'q', '1') },
    { CODEC_ID_TSCC,        MKTAG('t', 's', 'c', 'c') },
    { CODEC_ID_ULTI,        MKTAG('U', 'L', 'T', 'I') },
    { CODEC_ID_VIXL,        MKTAG('V', 'I', 'X', 'L') },
    { CODEC_ID_QPEG,        MKTAG('Q', 'P', 'E', 'G') },
    { CODEC_ID_QPEG,        MKTAG('Q', '1', '.', '0') },
    { CODEC_ID_QPEG,        MKTAG('Q', '1', '.', '1') },
    { CODEC_ID_WMV3,        MKTAG('W', 'M', 'V', '3') },
    { CODEC_ID_VC1,            MKTAG('W', 'V', 'C', '1') },
    { CODEC_ID_VC1,            MKTAG('W', 'M', 'V', 'A') },
    { CODEC_ID_LOCO,        MKTAG('L', 'O', 'C', 'O') },
    { CODEC_ID_WNV1,        MKTAG('W', 'N', 'V', '1') },
    { CODEC_ID_AASC,        MKTAG('A', 'A', 'S', 'C') },
    { CODEC_ID_INDEO2,        MKTAG('R', 'T', '2', '1') },
    { CODEC_ID_FRAPS,        MKTAG('F', 'P', 'S', '1') },
    { CODEC_ID_THEORA,        MKTAG('t', 'h', 'e', 'o') },
    { CODEC_ID_TRUEMOTION2, MKTAG('T', 'M', '2', '0') },
    { CODEC_ID_CSCD,        MKTAG('C', 'S', 'C', 'D') },
    { CODEC_ID_ZMBV,        MKTAG('Z', 'M', 'B', 'V') },
    { CODEC_ID_KMVC,        MKTAG('K', 'M', 'V', 'C') },
    { CODEC_ID_CAVS,        MKTAG('C', 'A', 'V', 'S') },
    { CODEC_ID_JPEG2000,    MKTAG('M', 'J', '2', 'C') },
    { CODEC_ID_VMNC,        MKTAG('V', 'M', 'n', 'c') },
    { CODEC_ID_TARGA,        MKTAG('t', 'g', 'a', ' ') },
    { CODEC_ID_PNG,            MKTAG('M', 'P', 'N', 'G') },
    { CODEC_ID_PNG,            MKTAG('P', 'N', 'G', '1') },
    { CODEC_ID_CLJR,        MKTAG('c', 'l', 'j', 'r') },
    { CODEC_ID_DIRAC,        MKTAG('d', 'r', 'a', 'c') },
    { CODEC_ID_RPZA,        MKTAG('a', 'z', 'p', 'r') },
    { CODEC_ID_RPZA,        MKTAG('R', 'P', 'Z', 'A') },
    { CODEC_ID_RPZA,        MKTAG('r', 'p', 'z', 'a') },
    { CODEC_ID_SP5X,        MKTAG('S', 'P', '5', '4') },
    { CODEC_ID_AURA,        MKTAG('A', 'U', 'R', 'A') },
    { CODEC_ID_AURA2,        MKTAG('A', 'U', 'R', '2') },
    { CODEC_ID_DPX,            MKTAG('d', 'p', 'x', ' ') },
    { CODEC_ID_KGV1,        MKTAG('K', 'G', 'V', '1') },
    { CODEC_ID_NONE, 0 }
};

const AVCodecTag ff_codec_wav_tags[] = {
    { CODEC_ID_PCM_S16LE,                0x0001 },
    { CODEC_ID_PCM_U8,                    0x0001 }, /* must come after s16le in this list */
    { CODEC_ID_PCM_S24LE,                0x0001 },
    { CODEC_ID_PCM_S32LE,                0x0001 },
    { CODEC_ID_ADPCM_MS,                0x0002 },
    { CODEC_ID_PCM_F32LE,                0x0003 },
    { CODEC_ID_PCM_F64LE,                0x0003 }, /* must come after f32le in this list */
    { CODEC_ID_PCM_ALAW,                0x0006 },
    { CODEC_ID_PCM_MULAW,                0x0007 },
    { CODEC_ID_WMAVOICE,                0x000A },
    { CODEC_ID_ADPCM_IMA_WAV,            0x0011 },
    { CODEC_ID_PCM_ZORK,                0x0011 }, /* must come after adpcm_ima_wav in this list */
    { CODEC_ID_ADPCM_YAMAHA,            0x0020 },
    { CODEC_ID_TRUESPEECH,                0x0022 },
    { CODEC_ID_GSM_MS,                    0x0031 },
    { CODEC_ID_ADPCM_G726,                0x0045 },
    { CODEC_ID_MP2,                        0x0050 },
    { CODEC_ID_MP3,                        0x0055 },
    { CODEC_ID_AMR_NB,                    0x0057 },
    { CODEC_ID_AMR_WB,                    0x0058 },
    { CODEC_ID_ADPCM_IMA_DK4,            0x0061 }, /* rogue format number */
    { CODEC_ID_ADPCM_IMA_DK3,            0x0062 }, /* rogue format number */
    { CODEC_ID_ADPCM_IMA_WAV,            0x0069 },
    { CODEC_ID_VOXWARE,                    0x0075 },
    { CODEC_ID_AAC,                        0x00ff },
    { CODEC_ID_SIPR,                    0x0130 },
    { CODEC_ID_WMAV1,                    0x0160 },
    { CODEC_ID_WMAV2,                    0x0161 },
    { CODEC_ID_WMAPRO,                    0x0162 },
    { CODEC_ID_WMALOSSLESS,                0x0163 },
    { CODEC_ID_ADPCM_CT,                0x0200 },
    { CODEC_ID_ATRAC3,                    0x0270 },
    { CODEC_ID_IMC,                        0x0401 },
    { CODEC_ID_GSM_MS,                    0x1500 },
    { CODEC_ID_TRUESPEECH,                0x1501 },
    { CODEC_ID_AC3,                        0x2000 },
    { CODEC_ID_DTS,                        0x2001 },
    { CODEC_ID_SONIC,                    0x2048 },
    { CODEC_ID_SONIC_LS,                0x2048 },
    { CODEC_ID_PCM_MULAW,                0x6c75 },
    { CODEC_ID_AAC,                        0x706d },
    { CODEC_ID_AAC,                        0x4143 },
    { CODEC_ID_FLAC,                    0xF1AC },
    { CODEC_ID_ADPCM_SWF,     ('S' << 8) + 'F' },
    { CODEC_ID_VORBIS,        ('V' << 8) + 'o' }, //HACK/FIXME, does vorbis in WAV/AVI have an (in)official id?

    /* FIXME: All of the IDs below are not 16 bit and thus illegal. */

    // for NuppelVideo (nuv.c)
    { CODEC_ID_PCM_S16LE,     MKTAG('R', 'A', 'W', 'A')},
    { CODEC_ID_MP3,           MKTAG('L', 'A', 'M', 'E')},
    { CODEC_ID_MP3,           MKTAG('M', 'P', '3', ' ')},
    { CODEC_ID_NONE,                         0 },
};

enum CodecID ff_codec_get_id(const AVCodecTag *tags, unsigned int tag)
{
    int i;

    for (i = 0; tags[i].id != CODEC_ID_NONE; i++)
    {
        if (tag == tags[i].tag)
        {
            return tags[i].id;
        }
    }

    for (i = 0; tags[i].id != CODEC_ID_NONE; i++)
    {
        if ((toupper((tag >> 0) & 0xFF) == toupper((tags[i].tag >> 0) & 0xFF))
            && (toupper((tag >> 8) & 0xFF) == toupper((tags[i].tag >> 8) & 0xFF))
            && (toupper((tag >> 16) & 0xFF) == toupper((tags[i].tag >> 16) & 0xFF))
            && (toupper((tag >> 24) & 0xFF) == toupper((tags[i].tag >> 24) & 0xFF)))
        {
            return tags[i].id;
        }
    }

    return CODEC_ID_NONE;
}

#if 1 //#ifdef DEBUG
 #define PRINT_IF_GUID(g, cmp) \
    if (!guidcmp(g, cmp)) \
        HI_INFO_ASF("(GUID: %s) ", # cmp)

static void print_guid(const HI_U8 *g)
{
    int i;
    PRINT_IF_GUID(g, ASF_HEADER_OBJECT_GUID);
    else PRINT_IF_GUID(g, ASF_FILE_PROPERTIES_OBJECT_GUID);
    else PRINT_IF_GUID(g, ASF_STREAM_PROPERTIES_OBJECT_GUID);
    else PRINT_IF_GUID(g, ASF_AUDIO_MEDIA_GUID);
    else PRINT_IF_GUID(g, ff_asf_audio_conceal_none);
    else PRINT_IF_GUID(g, ASF_VIDEO_MEDIA_GUID);
    else PRINT_IF_GUID(g, ff_asf_video_conceal_none);
    else PRINT_IF_GUID(g, ff_asf_command_stream);
    else PRINT_IF_GUID(g, ff_asf_comment_header);
    else PRINT_IF_GUID(g, ff_asf_codec_comment_header);
    else PRINT_IF_GUID(g, ff_asf_codec_comment1_header);
    else PRINT_IF_GUID(g, ASF_DATA_OBJECT_GUID);
    else PRINT_IF_GUID(g, ASF_HEADER_EXTERNSION_OBJECT_GUID);
    else PRINT_IF_GUID(g, ff_asf_header_reserve_1);
    else PRINT_IF_GUID(g, AS_EXTENED_STREAM_PROPERTIES_OBJECT_GUID);
    else PRINT_IF_GUID(g, ff_asf_extended_content_header);
    else PRINT_IF_GUID(g, ff_asf_ext_stream_embed_stream_header);
    else PRINT_IF_GUID(g, ff_asf_ext_stream_audio_stream);
    else PRINT_IF_GUID(g, ff_asf_metadata_header);
    else PRINT_IF_GUID(g, ff_asf_marker_header);
    else PRINT_IF_GUID(g, ff_asf_language_guid);
    else
        HI_INFO_ASF( "(GUID: unknown) ");

    for(i=0;i<16;i++)
        HI_INFO_ASF(" 0x%02x,", ((HI_U8 *)g)[i]);
    HI_INFO_ASF("}\n");

}

#else
 #define print_guid(g)
#endif

HI_S32 HI_ASF_Open(HI_ASF_OPEN_S *pstOpenParam, HI_HANDLE *handle)
{
    HI_U8                      *PsBufferPtr;
    HI_ASF_HANDLE              *asfhandle;

    HI_INFO_ASF("Now Call the HI_UNF_ASF_Open!\n");
    asfhandle = ASF_Malloc(sizeof(HI_ASF_HANDLE));
    if (asfhandle == HI_NULL_PTR)
    {
        return HI_FAILURE;
    }

    // 1. Alloc and Init PS Buffer
    PsBufferPtr = ASF_Malloc(pstOpenParam->u32ASFBufferSize);
    if (PsBufferPtr == HI_NULL_PTR)
    {
        HI_INFO_ASF("can't alloc the PS Buffer\n");
        ASF_Free(asfhandle);
        return HI_FAILURE;
    }

    memset(asfhandle, 0, sizeof(HI_ASF_HANDLE));

    asfhandle->OpenFlag = HI_TRUE;
    asfhandle->asfbuffer.pu8BaseAddr = (HI_U8 *)PsBufferPtr;
    asfhandle->asfbuffer.u32MaxSize = pstOpenParam->u32ASFBufferSize;
    asfhandle->asfbuffer.pu8CosumerAddr   = asfhandle->asfbuffer.pu8BaseAddr;
    asfhandle->asfbuffer.u32ActualASFSize = 0;
    asfhandle->asfbuffer.u32CurrentOffset = 0;

    asfhandle->avhandle = pstOpenParam->hAVPlay;

    HI_INFO_ASF("asfhandle->asfbuffer.pu8BaseAddr:0x%x, asfhandle->asfbuffer.u32TotalSize:0x%x\n",
                (HI_U32)asfhandle->asfbuffer.pu8BaseAddr, asfhandle->asfbuffer.u32ActualASFSize);

    asfhandle->threadRunFlag = HI_TRUE;

    asfhandle->u32VdecType  = pstOpenParam->u32VdecType;
    asfhandle->u32AudioType = pstOpenParam->u32AudioType;

    memset(&(asfhandle->info), 0, sizeof(HI_UNF_ASF_INFO_S));
    asfhandle->PlayState = HI_UNF_AVPLAY_STATUS_PLAY;

    asfhandle->streaminfo.LastMediaObjectNumber = 0xffffffff;
    if(0 == g_Count)
    {
        pthread_mutex_init(&AsfModualMutex,HI_NULL);
        memset(&g_AsfBuffer, 0, sizeof(ASF_PAYLOAD_DEC_BUFFER_S));
        g_AsfBuffer.pu8BufferBase   = ASF_Malloc( 1024 * 1024);   //provided 1M packetsize,
        g_AsfBuffer.pu8Consumeraddr = g_AsfBuffer.pu8BufferBase;
    }
    g_Count++;
    *handle = (HI_U32)(asfhandle);
    HI_INFO_ASF("can't alloc the PS Buffer\n");

    return HI_SUCCESS;
}

HI_S32 HI_ASF_Close(HI_HANDLE handle)
{
    HI_ASF_HANDLE              *ASFHandle;

    HI_INFO_ASF("Info: HI_ASF_Close\n");

    D_STREAM_GET_HANDLE(handle, ASFHandle);

    HI_STREAM_LOCK(ASFHandle);
    ASFHandle->PlayState = HI_UNF_AVPLAY_STATUS_STOP;

    ASFHandle->threadRunFlag = HI_FALSE;
    HI_INFO_ASF("ASFHandle:0x%x, ASFHandle->threadRunFlag:%d\n", (HI_U32)ASFHandle, (HI_U32)ASFHandle->threadRunFlag);

    HI_INFO_ASF("Info: HI_UNF_ASF_Stop Now\n");

    HI_STREAM_UNLOCK(ASFHandle);
    if(g_Count == 1)
    {
        pthread_mutex_destroy(&ASFHandle->Mutex);
    }
    g_Count--;
    // 3. Free PS Buffer
    ASF_Free((HI_VOID *)(ASFHandle->asfbuffer.pu8BaseAddr));
    ASF_Free((HI_VOID *)(ASFHandle));
    ASF_Free((HI_VOID *)(g_AsfBuffer.pu8BufferBase));

    HI_INFO_ASF("Info: HI_UNF_ASF_Close OK.\n");
    return HI_SUCCESS;
}

HI_S32 HI_ASF_Head_Parser(HI_HANDLE handle, HI_U32 *pLenToPacket, HI_U32 *pPacketSize, HI_U8* asfHeaderBuffer,
                          HI_U32 u32HeaderBufferLen)
{
    HI_U32 u32Readlen;
    HI_ASF_HANDLE           *ASFHandle;
    HI_U32 u32MinHeaderLen = 64 * 1024;               //Minum Size of File Header is 64K.
    ASF_PACKET_BUFFER_S *pASFHeaderData;
    HI_U8 TempBuffer[20];
    HI_U32 u32CurrentLen;
    HI_U32 SubHeaderSize = 0;
    HI_U32 ObjectSize = 0;

    HI_U32 tempCounter = 0;

    D_STREAM_GET_HANDLE(handle, ASFHandle);
    pASFHeaderData = &(ASFHandle->asfbuffer);

    HI_INFO_ASF("##################DEBUG in HI_UNF_ASF_Head_Parser##########################\n");
    do
    {
        if (pASFHeaderData->pu8CosumerAddr != pASFHeaderData->pu8BaseAddr)
        {
            memcpy(pASFHeaderData->pu8BaseAddr + pASFHeaderData->u32ActualASFSize, asfHeaderBuffer, sizeof(HI_S8)
                   * u32HeaderBufferLen);
            pASFHeaderData->pu8CosumerAddr    = pASFHeaderData->pu8BaseAddr;
            pASFHeaderData->u32ActualASFSize += u32HeaderBufferLen;
            pASFHeaderData->u32CurrentOffset  = 0;
            u32Readlen = pASFHeaderData->u32ActualASFSize;
            HI_INFO_ASF("11111111111111111pASFHeaderData->u32ActualASFSize:%d\n", pASFHeaderData->u32ActualASFSize);
        }
        else
        {
            memcpy(pASFHeaderData->pu8BaseAddr, asfHeaderBuffer, sizeof(HI_S8) * u32HeaderBufferLen);
            pASFHeaderData->u32ActualASFSize = u32HeaderBufferLen;
            u32Readlen = u32HeaderBufferLen;
        }

        if (u32Readlen > 30)
        {
            u32CurrentLen = 0;

            /********************************Parse the Header Object**********************************************/
            Stream_CopyBufferAndMoveOn(pASFHeaderData, TempBuffer, __ASF_GID_NUM__);
            u32CurrentLen += __ASF_GID_NUM__;

            // Parse Header Object
            HI_INFO_ASF("Parse the Header Object!\n");

            if (guidcmp(TempBuffer, ASF_HEADER_OBJECT_GUID) != 0)
            {
                HI_INFO_ASF("Bad Header!\n");
                return HI_FAILURE;
            }

            //Get Size
            ObjectSize = Stream_GetLittleEndianU32AndMoveOn(pASFHeaderData);

            if (ObjectSize + 16 > u32Readlen)
            {
                HI_WARN_ASF("Not Enough Header!\n");
                return HI_FAILURE;
            }

            Stream_SeekBufferAndMoveOn(pASFHeaderData, 4);

            u32CurrentLen += 8;

            ASFHandle->streaminfo.headerobjectNum = Stream_GetLittleEndianU32AndMoveOn(pASFHeaderData);
            u32CurrentLen += 4;

            Stream_SeekBufferAndMoveOn(pASFHeaderData, 2);
            u32CurrentLen += 2; /*2 byes Reserved data*/

            SubHeaderSize = ObjectSize - (16 + 8 + 4 + 2);
            pthread_mutex_lock(&AsfModualMutex);

            ASF_Parse_HeaderObject(ASFHandle, SubHeaderSize);
            pthread_mutex_unlock(&AsfModualMutex);

            u32CurrentLen += SubHeaderSize;

            if (u32Readlen - u32CurrentLen < 50)
            {
                printf("No Enough Buffer to Read!\n");
                return HI_FAILURE;
            }

            /***********************************Parse the Data Object***************************************************/
            Stream_CopyBufferAndMoveOn(pASFHeaderData, TempBuffer, __ASF_GID_NUM__);
            u32CurrentLen += __ASF_GID_NUM__;

            //return HI_FAILURE;
            tempCounter = 0;
            while (u32CurrentLen < u32MinHeaderLen)
            {
                print_guid(TempBuffer);
                if (guidcmp(TempBuffer, ASF_DATA_OBJECT_GUID) == 0)
                {
                    break;
                }

                u32CurrentLen++;
                Stream_CopyBufferAndMoveOn(pASFHeaderData, TempBuffer, __ASF_GID_NUM__);
                u32CurrentLen += __ASF_GID_NUM__;
            }

            if (u32CurrentLen >= u32MinHeaderLen)
            {
                printf("No Enough Buffer to Read!\n");
                return HI_FAILURE;
            }

            //Get Size
            ASFHandle->streaminfo.DataObjectSize = Stream_GetLittleEndianU32AndMoveOn(pASFHeaderData);
            Stream_SeekBufferAndMoveOn(pASFHeaderData, 4);
            u32CurrentLen += 8;

            //Get File ID
            Stream_CopyBufferAndMoveOn(pASFHeaderData, (ASFHandle->streaminfo.FILEID), __ASF_GID_NUM__);
            u32CurrentLen += __ASF_GID_NUM__;

            //Get Total Data packet
            ASFHandle->streaminfo.TotalDataPackets = Stream_GetLittleEndianU32AndMoveOn(pASFHeaderData);
            Stream_SeekBufferAndMoveOn(pASFHeaderData, 4); //ignore upper 4Bytes
            u32CurrentLen += 8;

            Stream_SeekBufferAndMoveOn(pASFHeaderData, 2); //Resever 2 Bytes:0x0101
            u32CurrentLen += 2;

            ASFHandle->statics.u32FileParseOffset = u32CurrentLen;
            ASFHandle->streaminfo.DataObjectFlag = HI_TRUE;
            ASFHandle->streaminfo.CurrentDataPacketIndex = 0;

            *pLenToPacket = u32CurrentLen;
            *pPacketSize = (ASFHandle->streaminfo.PackSize);

            HI_INFO_ASF("pLenToPacket:%d, pPacketSize:%d\n", *pLenToPacket, *pPacketSize);
        }
        else
        {
            HI_WARN_ASF("file too small!\n");
            return HI_FAILURE;
        }
    } while (0);

    return HI_SUCCESS;
}

HI_S32 HI_ASF_GetBuffer(HI_HANDLE handle, HI_U32 u32ReqLen, HI_UNF_STREAM_BUF_S *pstData)
{
    HI_ASF_HANDLE           *ASFHandle;

    D_STREAM_GET_HANDLE(handle, ASFHandle);

    if (u32ReqLen > (ASFHandle->asfbuffer.u32MaxSize) && (u32ReqLen > 0))
    {
        HI_ERR_ASF("Request Buffer is too large. Please Change it smaller!\n");
        return HI_FAILURE;
    }

    pstData->pu8Data = ASFHandle->asfbuffer.pu8BaseAddr;
    ASFHandle->asfbuffer.u32CurrentOffset = 0;
    ASFHandle->asfbuffer.pu8CosumerAddr = ASFHandle->asfbuffer.pu8BaseAddr;

    return HI_SUCCESS;
}

HI_S32 HI_ASF_PutBuffer(HI_HANDLE handle, HI_U32 u32ValidDatalen)
{
    HI_ASF_HANDLE           *ASFHandle;
    HI_S32 ret;

    D_STREAM_GET_HANDLE(handle, ASFHandle);
    pthread_mutex_lock(&AsfModualMutex);
    ASFHandle->asfbuffer.u32ActualASFSize = u32ValidDatalen;

    ret = Stream_Extract( ASFHandle);
    if (ret == HI_SUCCESS)
    {
        HI_INFO_ASF("YES! Pakets Parser Return Successful!\n");
    }
    pthread_mutex_unlock(&AsfModualMutex);

    return ret;
}

static HI_U8 Stream_GetOneByteAndMoveOn(ASF_PACKET_BUFFER_S *pstData)
{
    HI_U8 CurrChar;

    CurrChar = *(pstData->pu8CosumerAddr);
    pstData->u32CurrentOffset++;
    pstData->pu8CosumerAddr++;

    return CurrChar;
}

static HI_U16 Stream_GetLittleEndianU16AndMoveOn(ASF_PACKET_BUFFER_S *pstData)
{
    HI_U32 DstPtr = 0;

    DstPtr  = Stream_GetOneByteAndMoveOn(pstData);
    DstPtr += Stream_GetOneByteAndMoveOn(pstData) * 0x100;

    return DstPtr;
}

static HI_U32 Stream_GetLittleEndianU32AndMoveOn(ASF_PACKET_BUFFER_S *pstData)
{
    HI_U32 DstPtr = 0;

    DstPtr  = Stream_GetOneByteAndMoveOn(pstData);
    DstPtr += Stream_GetOneByteAndMoveOn(pstData) * 0x100;
    DstPtr += Stream_GetOneByteAndMoveOn(pstData) * 0x10000;
    DstPtr += Stream_GetOneByteAndMoveOn(pstData) * 0x1000000;

    return DstPtr;
}

static HI_VOID Stream_SeekBufferAndMoveOn(ASF_PACKET_BUFFER_S *pstData, HI_U32 SeekNum)
{
    pstData->pu8CosumerAddr   += SeekNum;
    pstData->u32CurrentOffset += SeekNum;

    return;
}

static HI_VOID Stream_CopyBufferAndMoveOn(ASF_PACKET_BUFFER_S *pstData, HI_U8 *DstPtr, HI_U32 CopyNum)
{
    memcpy(DstPtr, pstData->pu8CosumerAddr, CopyNum);

    pstData->pu8CosumerAddr   += CopyNum;
    pstData->u32CurrentOffset += CopyNum;

    return;
}

static HI_U32 ASF_ES_AddExtraData(HI_ASF_HANDLE *ASFHandle, HI_U32 codec_id, HI_U32 IsMONChange, HI_U8 *Header,
                                  HI_U32 IsKeyFrame, HI_U8 *pExtraData,
                                  HI_U8 *Length)
{
    HI_S32 ret = HI_SUCCESS;

    if (pExtraData == NULL)
    {
        return HI_FAILURE;
    }

    if ((codec_id == CODEC_ID_WMV3) || (codec_id == CODEC_ID_WMV2) || (codec_id == CODEC_ID_WMV1))
    {
        if (IsMONChange == HI_FALSE)
        {
            *Length = 0;
            return ret;
        }

        memset(pExtraData, 0, 16);
        memcpy((pExtraData + 0), (HI_U8 *)(&ASFHandle->streaminfo.VideoSpecific.ImageWidth), 4);
        memcpy((pExtraData + 4), (HI_U8 *)(&ASFHandle->streaminfo.VideoSpecific.ImageHeight), 4);
        if (ASFHandle->streaminfo.VideoSpecific.CodecSDataLength > 4)
        {
            memcpy((pExtraData + 8), ASFHandle->streaminfo.VideoSpecific.CodecSpecificData, 4);
        }
        else
        {
            memcpy((pExtraData + 8), ASFHandle->streaminfo.VideoSpecific.CodecSpecificData,
                   ASFHandle->streaminfo.VideoSpecific.CodecSDataLength);
        }

        *Length = 16;
        return ret;
    }
    else if ((codec_id == CODEC_ID_VC1)|| (codec_id == CODEC_ID_H264))
    {
        //*Length = 0;
        if (IsMONChange == HI_FALSE)
        {
            *Length = 0;
            return ret;
        }
        if ((IsKeyFrame) && (ASFHandle->streaminfo.VideoSpecific.CodecSDataLength > 1))
        {
            memcpy((pExtraData + 0), ASFHandle->streaminfo.VideoSpecific.CodecSpecificData,
                   ASFHandle->streaminfo.VideoSpecific.CodecSDataLength);
            *Length += ASFHandle->streaminfo.VideoSpecific.CodecSDataLength;
        }

        if (!((Header[0] == 0x00) && (Header[1] == 0x00) && (Header[2] == 0x01)))
        {
            //There is not header in this frame
            pExtraData[*Length] = 0X00;
            (*Length)++;
            pExtraData[*Length] = 0X00;
            (*Length)++;
            pExtraData[*Length] = 0X01;
            (*Length)++;
            pExtraData[*Length] = 0X0D;
            (*Length)++;
        }

        return ret;
    }

    return HI_SUCCESS;
}

static HI_VOID ASF_OneFrameToPlay(HI_ASF_HANDLE *ASFHandle)
{
    HI_S32 ret;

    if (g_AsfBuffer.u32CurrentBufferLen == 0)
    {
        HI_INFO_ASF("Packet Start Parse the Payload!\n");
        return;
    }

    //handle one frame Payload Data

    if ((ASFHandle->Videocodec_id == CODEC_ID_H264) || (ASFHandle->Videocodec_id == CODEC_ID_VC1) || (ASFHandle->Videocodec_id == CODEC_ID_WMV3)
        || (ASFHandle->Videocodec_id == CODEC_ID_WMV2)
        || (ASFHandle->Videocodec_id == CODEC_ID_WMV1))
    {
        ASFHandle->stESVidBuffer.u32Size = g_AsfBuffer.u32CurrentBufferLen;
        do
        {
            ret = HI_UNF_AVPLAY_GetBuf(ASFHandle->avhandle, HI_UNF_AVPLAY_BUF_ID_ES_VID,
                                       ASFHandle->stESVidBuffer.u32Size, &(ASFHandle->stESVidBuffer), 0);
            if (ret != HI_SUCCESS)
            {
                HI_INFO_ASF("HI_UNF_AVPLAY_GetBuf Failed!\n");
                usleep(1 * 1000);
            }
        } while (ret != HI_SUCCESS);

        if (g_IsWhatEncryp == IS_PLAYREADY_ENCRYPT)
        {
            HI_U32 dr = HI_SUCCESS;
            HI_PLAYREADY_DECRYPTPARM_S stDecryptParam;
            stDecryptParam.u8Data = g_AsfBuffer.pu8BufferBase + 16;
            stDecryptParam.u32Length = ASFHandle->stESVidBuffer.u32Size - 16;

            if(g_replicatedLength > 8)  //the last 8 bytes is iv for ASF files, bigend
            {
                stDecryptParam.u8ReplicatedData = &g_replicatedData[g_replicatedLength - 8];
                stDecryptParam.u32ReplicatedLength = 8;
            }
            else
            {
                stDecryptParam.u8ReplicatedData = g_replicatedData;
                stDecryptParam.u32ReplicatedLength = g_replicatedLength;
            }
            if (HI_TRUE == isTvp)
            {
                dr = ASF_MediaDrm_Decrypt(stDecryptParam.u8ReplicatedData,stDecryptParam.u32ReplicatedLength,
                                   g_AsfBuffer.pu8BufferBase,ASFHandle->stESVidBuffer.u32Size,ASFHandle->stESVidBuffer.pu8Data);
            }
            else
            {
                dr = ASF_MediaDrm_Decrypt(stDecryptParam.u8ReplicatedData,stDecryptParam.u32ReplicatedLength,
                                   stDecryptParam.u8Data,stDecryptParam.u32Length,stDecryptParam.u8Data);
            }

            if (dr != HI_SUCCESS)
            {
                //HI_ERR_ASF(" Error to Descrambel Data\n");
            }
        }

        if (ASFHandle->stESVidBuffer.pu8Data != NULL && HI_FALSE == isTvp)
        {
            memcpy(ASFHandle->stESVidBuffer.pu8Data, g_AsfBuffer.pu8BufferBase, ASFHandle->stESVidBuffer.u32Size);
        }

        ret = HI_UNF_AVPLAY_PutBuf(ASFHandle->avhandle, HI_UNF_AVPLAY_BUF_ID_ES_VID, ASFHandle->stESVidBuffer.u32Size,

                                   /*-1*/ g_AsfBuffer.PTS);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_ASF("HI_UNF_AVPLAY_PutBuf Failed!\n");
            return;
        }

        g_AsfBuffer.pu8Consumeraddr = g_AsfBuffer.pu8BufferBase;
        g_AsfBuffer.u32CurrentBufferLen = 0;
    }
    else
    {
        HI_ERR_ASF("\nIt's not WMV\2\1 Codec.\n");
        HI_ERR_ASF("\nWe didn't support no WMV format!\n");
        HI_ERR_ASF("ASFHandle->Videocodec_id:%d\n", ASFHandle->Videocodec_id);
        g_AsfBuffer.pu8Consumeraddr = g_AsfBuffer.pu8BufferBase;
        g_AsfBuffer.u32CurrentBufferLen = 0;
    }

    return;
}

static HI_U32 ASF_Payload(HI_ASF_HANDLE *ASFHandle, HI_U32 PayloadSize, HI_U32 Stream_Number, HI_U32 Send_Time,
                          HI_U32 IsKeyFrame, HI_BOOL isEncrypt, HI_U8 *Replicated_Data, HI_U32 Replicated_Data_Length)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_STREAM_BUF_S stESBuffer;
    HI_U32 dr = HI_SUCCESS;
    ASF_PACKET_BUFFER_S   *pstPacketBuffer = &(ASFHandle->asfbuffer);

    HI_PLAYREADY_DECRYPTPARM_S stDecryptParam;

    if (PayloadSize < 3)
    {
        HI_ERR_ASF("error PayloadSize %d\n", PayloadSize);
        Stream_SeekBufferAndMoveOn(pstPacketBuffer, PayloadSize);
        return HI_SUCCESS;

        //return -1;
    }

    if (ASFHandle->streaminfo.Video_Stream_Number == Stream_Number)
    {
        HI_U8 Header[3] = {0x00, 0x00, 0x00};
        HI_BOOL IsMONChange = HI_FALSE;
        HI_U8 ExtraData[255], ExtraLength = 0;

        if (ASFHandle->VideoEnable != HI_TRUE)
        {
            Stream_SeekBufferAndMoveOn(pstPacketBuffer, PayloadSize);
            return HI_SUCCESS;
        }
        //HI_INFO_ASF("WMDRMhandle:0x%x\n",ASFHandle->WMDRMhandle);

        //First Get 3 Bytes to check wether we need add specail header
        Stream_CopyBufferAndMoveOn(pstPacketBuffer, Header, 3);
        if (ASFHandle->streaminfo.CurrentMediaObjectNumber != ASFHandle->streaminfo.LastMediaObjectNumber)
        {
            IsMONChange = HI_TRUE;
            ASF_OneFrameToPlay(ASFHandle);
        }

        ASFHandle->streaminfo.LastMediaObjectNumber = ASFHandle->streaminfo.CurrentMediaObjectNumber;

        memset(ExtraData, 0, 255);
        ASF_ES_AddExtraData(ASFHandle, ASFHandle->Videocodec_id, IsMONChange, Header, IsKeyFrame, ExtraData,
                            &ExtraLength);

        //Get Video ES buffer

        memcpy(g_AsfBuffer.pu8Consumeraddr, ExtraData, ExtraLength);
        memcpy((g_AsfBuffer.pu8Consumeraddr + ExtraLength), Header, 3);
        Stream_CopyBufferAndMoveOn(pstPacketBuffer, (g_AsfBuffer.pu8Consumeraddr + ExtraLength + 3), (PayloadSize - 3));

        memcpy(g_replicatedData, Replicated_Data, Replicated_Data_Length);
        g_replicatedLength = Replicated_Data_Length;

        if ((g_IsWhatEncryp != IS_PLAYREADY_ENCRYPT) && (isEncrypt == HI_TRUE))
        {
            stDecryptParam.u8Data = (g_AsfBuffer.pu8Consumeraddr + ExtraLength);
            stDecryptParam.u32Length = PayloadSize;

            if(Replicated_Data_Length > 8)  //the last 8 bytes is iv for ASF files, bigend
            {
                stDecryptParam.u8ReplicatedData = &Replicated_Data[Replicated_Data_Length - 8];
                stDecryptParam.u32ReplicatedLength = 8;
            }
            else
            {
                stDecryptParam.u8ReplicatedData = Replicated_Data;
                stDecryptParam.u32ReplicatedLength = Replicated_Data_Length;
            }

            //dr = HI_PLAYREADY_Decrypt(ASFHandle->WMDRMhandle, &stDecryptParam);
            dr = ASF_MediaDrm_Decrypt(stDecryptParam.u8ReplicatedData,stDecryptParam.u32ReplicatedLength,
                                   stDecryptParam.u8Data,stDecryptParam.u32Length,g_AsfBuffer.pu8BufferBase);
            if (dr != HI_SUCCESS)
            {
                //HI_ERR_ASF("Error to Descrambel Data\n");
            }
        }

        //HI_INFO_ASF("Video PTS:%d\n", Send_Time);
        if (Send_Time != 0)
        {
            g_AsfBuffer.PTS = Send_Time;
        }

        g_AsfBuffer.pu8Consumeraddr += PayloadSize + ExtraLength;
        g_AsfBuffer.u32CurrentBufferLen += PayloadSize + ExtraLength;
        ASFHandle->statics.u32VideoESPackNum++;
    }
    else if (ASFHandle->streaminfo.Audio_Stream_Number == Stream_Number)
    {
        if (ASFHandle->AudioEnable != HI_TRUE)
        {
            Stream_SeekBufferAndMoveOn(pstPacketBuffer, PayloadSize);
            return HI_SUCCESS;
        }

        //Get Audio ES buffer
        HI_UNF_STREAM_BUF_S StreamBuf;

        //Get ES buffer from ES, if we can get it, input!
        ret = HI_UNF_AVPLAY_GetBuf(ASFHandle->avhandle, HI_UNF_AVPLAY_BUF_ID_ES_AUD, PayloadSize, &StreamBuf, 0);
        if (ret != HI_SUCCESS)
        {
            //HI_ERR_ASF("Get Audio Buffer Error\n");
            if (HI_ERR_VDEC_BUFFER_FULL == ret)
            {
                HI_ERR_ASF("ADec full\n");
            }

            ASFHandle->statics.u32AudioESOverflowNum++;
            return HI_FAILURE;
        }

        stESBuffer.pu8Data = StreamBuf.pu8Data;
        stESBuffer.u32Size = StreamBuf.u32Size;

        Stream_CopyBufferAndMoveOn(pstPacketBuffer, stESBuffer.pu8Data, PayloadSize);

        if (isEncrypt == HI_TRUE)
        {
            stDecryptParam.u8Data = stESBuffer.pu8Data;
            stDecryptParam.u32Length = PayloadSize;

            if(Replicated_Data_Length > 8)  // the last 8 bytes is iv for ASF files, bigend
            {
                stDecryptParam.u8ReplicatedData = &Replicated_Data[Replicated_Data_Length - 8];
                stDecryptParam.u32ReplicatedLength = 8;
            }
            else
            {
                stDecryptParam.u8ReplicatedData = Replicated_Data;
                stDecryptParam.u32ReplicatedLength = Replicated_Data_Length;
            }

            //dr = HI_PLAYREADY_Decrypt(ASFHandle->WMDRMhandle, &stDecryptParam);
            dr = ASF_MediaDrm_Decrypt(stDecryptParam.u8ReplicatedData,stDecryptParam.u32ReplicatedLength,
                                   stDecryptParam.u8Data,stDecryptParam.u32Length,stESBuffer.pu8Data);
            if (dr != HI_SUCCESS)
            {
                //printf("Error to Descrambel Data\n");
            }
            ret = HI_UNF_AVPLAY_PutBuf(ASFHandle->avhandle, HI_UNF_AVPLAY_BUF_ID_ES_AUD,
                PayloadSize,Send_Time);
            if (ret != HI_SUCCESS)
            {
                return ret;
            }
        }
        else
        {
            //printf("PayloadSize : %d\n");
            ret = HI_UNF_AVPLAY_PutBuf(ASFHandle->avhandle, HI_UNF_AVPLAY_BUF_ID_ES_AUD,
                PayloadSize, Send_Time);
            if (ret != HI_SUCCESS)
            {
                return ret;
            }
        }

        HI_INFO_ASF("Audio PTS:%d\n", Send_Time);
    }
    else
    {
        HI_ERR_ASF("Unkown Stream_Number:0x%x\n", Stream_Number);

        //HI_ERR_ASF("Sorry, We can't parse this freak stream!\n", Stream_Number);
        return HI_FAILURE;

        //Stream_SeekBufferAndMoveOn(pstPacketBuffer, PayloadSize);
    }

    return HI_SUCCESS;
}

Vector<HI_U8> drmInitdata;

static HI_U32 ASF_Parse_HeaderObject(HI_ASF_HANDLE *ASFHandle, HI_U32 HeaderSize)
{
    HI_U32 DataNum = HeaderSize;
    ASF_PACKET_BUFFER_S    *pstData;
    HI_U8 TempBuffer[20];
    HI_U32 ObjectSize;
    HI_U32 VdecType, AdecType, IsHighProfile = HI_FALSE;
    ASF_WMA_FORMAT_S WMAPrivateData;

    pstData = &(ASFHandle->asfbuffer);
    g_IsWhatEncryp = IS_WMDRM_ENCRYPT;

    HI_INFO_ASF("##################DEBUG IN ASF_Parse_HeaderObject##########################");
    HI_INFO_ASF("hejinghai HeaderSize:%d, asfbuffer.pu8CosumerAddr:0x%x\n", HeaderSize,
                (HI_U32)ASFHandle->asfbuffer.pu8CosumerAddr);
    while (DataNum > (__ASF_GID_NUM__ + 8))
    {
        Stream_CopyBufferAndMoveOn(pstData, TempBuffer, __ASF_GID_NUM__);

        ObjectSize = Stream_GetLittleEndianU32AndMoveOn(pstData);
        Stream_SeekBufferAndMoveOn(pstData, 4);
        if (ObjectSize > DataNum)
        {
            print_guid(TempBuffer);
            HI_ERR_ASF("Error DATA, DataNum:%d, ObjectSize:0x%x\n", DataNum, ObjectSize);
            break;
        }

        DataNum -= (__ASF_GID_NUM__ + 8);

        //Now We can parse ASF Header SubObject
        if (guidcmp(TempBuffer, ASF_FILE_PROPERTIES_OBJECT_GUID) == 0)
        {
            //ASF_FILE_Properties_Object
            HI_INFO_ASF("ASF_FILE_Properties_Object, ObjectSize:0x%x\n", ObjectSize);
            HI_U8 FILE_ID[__ASF_GID_NUM__];
            HI_U32 FileSize, CreationDate, Data_Packets_Count, Play_Duration, Preroll;
            HI_U32 Flags, Broadcast_Flag, Seekable_Flag, Send_Duration;
            HI_U32 Minimum_Data_Packet_Size, Maximum_Data_Packet_Size, Maximum_Bitrate;

            //FILE_ID
            Stream_CopyBufferAndMoveOn(pstData, FILE_ID, __ASF_GID_NUM__);
            DataNum -= __ASF_GID_NUM__;

            //FileSize
            FileSize = Stream_GetLittleEndianU32AndMoveOn(pstData);
            Stream_SeekBufferAndMoveOn(pstData, 4);
            DataNum -= 8;

            //CreationDate
            CreationDate = Stream_GetLittleEndianU32AndMoveOn(pstData);
            Stream_SeekBufferAndMoveOn(pstData, 4);
            DataNum -= 8;

            //Data_Packets_Count
            Data_Packets_Count = Stream_GetLittleEndianU32AndMoveOn(pstData);
            Stream_SeekBufferAndMoveOn(pstData, 4);
            DataNum -= 8;

            //Play_Duration
            Play_Duration = Stream_GetLittleEndianU32AndMoveOn(pstData);
            Stream_SeekBufferAndMoveOn(pstData, 4);
            DataNum -= 8;
            //Send Duration
            Send_Duration = Stream_GetLittleEndianU32AndMoveOn(pstData);
            Stream_SeekBufferAndMoveOn(pstData, 4);
            DataNum -= 8;

            //Preroll
            Preroll = Stream_GetLittleEndianU32AndMoveOn(pstData);
            Stream_SeekBufferAndMoveOn(pstData, 4);
            DataNum -= 8;

            //Flags
            Flags    = Stream_GetLittleEndianU32AndMoveOn(pstData);
            DataNum -= 4;
            Broadcast_Flag = Flags & 0x01;
            Seekable_Flag = (Flags & 0x02) >> 1;

            //Minimum_Data_Packet_Size
            Minimum_Data_Packet_Size = Stream_GetLittleEndianU32AndMoveOn(pstData);
            DataNum -= 4;

            //Maximum_Data_Packet_Size
            Maximum_Data_Packet_Size = Stream_GetLittleEndianU32AndMoveOn(pstData);
            DataNum -= 4;

            //Maximum_Bitrate
            Maximum_Bitrate = Stream_GetLittleEndianU32AndMoveOn(pstData);
            DataNum -= 4;

            //Output constant Packet Size
            ASFHandle->streaminfo.PackSize = Maximum_Data_Packet_Size;
            HI_INFO_ASF("ASF FileSize:%d, Constant Packet Size:0x%x\n", FileSize, ASFHandle->streaminfo.PackSize);
        }
        else if (guidcmp(TempBuffer, ASF_STREAM_PROPERTIES_OBJECT_GUID) == 0)
        {
            //ASF_Stream_Properties_Object
            HI_INFO_ASF("ASF_Stream_Properties_Object, ObjectSize:0x%x\n", ObjectSize);
            HI_U8 Stream_Type[__ASF_GID_NUM__], Error_Correction_Type[__ASF_GID_NUM__];
            HI_U32 Time_Offset, Type_Specific_Data_Length, Error_Correction_Data_Length;
            HI_U32 Flags, Stream_Number, Encrypted_Content_Flag;

            //Stream_Type
            Stream_CopyBufferAndMoveOn(pstData, Stream_Type, __ASF_GID_NUM__);
            DataNum -= __ASF_GID_NUM__;

            //Error_Correction_Type
            Stream_CopyBufferAndMoveOn(pstData, Error_Correction_Type, __ASF_GID_NUM__);
            DataNum -= __ASF_GID_NUM__;

            //Time_Offset
            Time_Offset = Stream_GetLittleEndianU32AndMoveOn(pstData);
            Stream_SeekBufferAndMoveOn(pstData, 4);
            DataNum -= 8;

            //Type_Specific_Data_Length
            Type_Specific_Data_Length = Stream_GetLittleEndianU32AndMoveOn(pstData);
            DataNum -= 4;

            //Error_Correction_Data_Length
            Error_Correction_Data_Length = Stream_GetLittleEndianU32AndMoveOn(pstData);
            DataNum -= 4;

            //Flags
            Flags    = Stream_GetLittleEndianU16AndMoveOn(pstData);
            DataNum -= 2;
            Stream_Number = Flags & 0x7F; //Very Important Type specific
            Encrypted_Content_Flag = (Flags & 0x8000) >> 15; //Very Important Type specific
            HI_INFO_ASF("Type_Specific_Data_Length:0x%x, Error_Correction_Data_Length:0x%x, Flags:0x%x, Encrypted_Content_Flag:0x%x\n",
                        Type_Specific_Data_Length, Error_Correction_Data_Length, Flags, Encrypted_Content_Flag);

            //Reserved
            Stream_SeekBufferAndMoveOn(pstData, 4);
            DataNum -= 4;

            //Type-Specific Data
            if ((guidcmp(Stream_Type, ASF_VIDEO_MEDIA_GUID) == 0))
            {
                //Video
                HI_U32 Encoded_Image_Width, Encoded_Image_Height, Format_Data_Size;
                HI_U32 biSize, Image_Width, Image_Height, Bits_Per_Pixel_Count;
                HI_U32 Compression_ID, Image_Size, Horizontal_Pixels_Per_Meter;
                HI_U32 Vertical_Pixels_Per_Meter, Colors_Used_Count, Important_Colors_Count;
                HI_U32 BeforeOffset, UsedOffset;
                HI_U8 Tag[4], index;
                ASF_WMV_VIDEO_Type_Specific_Data_S *pVideoSpecific;

                BeforeOffset = Type_Specific_Data_Length;

                //ASF_Video_Media
                //Encoded Image Width
                Encoded_Image_Width = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;

                //Encoded Image Height
                Encoded_Image_Height = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;
                HI_INFO_ASF("Encoded_Image_Width:0x%x, Encoded_Image_Height:0x%x\n", Encoded_Image_Width,
                            Encoded_Image_Height);

                //Reserved Flags:0x02
                Stream_SeekBufferAndMoveOn(pstData, 1);
                DataNum -= 1;
                BeforeOffset -= 1;

                //Format Data Size
                Format_Data_Size = Stream_GetLittleEndianU16AndMoveOn(pstData);
                DataNum -= 2;
                BeforeOffset -= 2;

                //Format Data:BITMAPINFOHEADER structure

                /*
                typedef struct tagBITMAPINFOHEADER {
                    DWORD biSize;          //4B
                    LONG  biWidth;         //4B
                    LONG  biHeight;        //4B
                    WORD  biPlanes;        //2B
                    WORD  biBitCount;      //2B
                    DWORD biCompression;   //4B
                    DWORD biSizeImage;     //4B
                    LONG  biXPelsPerMeter; //4B
                    LONG  biYPelsPerMeter; //4B
                    DWORD biClrUsed;       //4B
                    DWORD biClrImportant;  //4B
                } BITMAPINFOHEADER;
                 */

                //Format Data Size(biSize)
                biSize = Stream_GetLittleEndianU32AndMoveOn(pstData);
                HI_INFO_ASF("biSize:%d\n", biSize);
                DataNum -= 4;
                BeforeOffset -= 4;

                //Image Width
                Image_Width = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;

                //Image Height
                Image_Height = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;
                HI_INFO_ASF("Image_Width:0x%x, Image_Height:0x%x\n", Image_Width, Image_Height);

                //Reserved
                Stream_SeekBufferAndMoveOn(pstData, 2);
                DataNum -= 2;
                BeforeOffset -= 2;

                //Bits Per Pixel Count
                Bits_Per_Pixel_Count = Stream_GetLittleEndianU16AndMoveOn(pstData);
                DataNum -= 2;
                BeforeOffset -= 2;

                //Compression ID:We can use this as video compress tag!
                Compression_ID = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;

                //Image Size
                Image_Size = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;

                //Horizontal Pixels Per Meter
                Horizontal_Pixels_Per_Meter = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;

                //Vertical Pixels Per Meter
                Vertical_Pixels_Per_Meter = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;

                //Colors Used Count
                Colors_Used_Count = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;

                //Important Colors Count
                Important_Colors_Count = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;
                BeforeOffset -= 4;

                //Codec Specific Data:Varies length
                UsedOffset = DataNum;

                pVideoSpecific = &(ASFHandle->streaminfo.VideoSpecific);
                memset(pVideoSpecific, 0, sizeof(ASF_WMV_VIDEO_Type_Specific_Data_S));
                pVideoSpecific->FormatDataSize = biSize;
                pVideoSpecific->ImageWidth  = Image_Width;
                pVideoSpecific->ImageHeight = Image_Height;
                pVideoSpecific->Reserved = 0;
                pVideoSpecific->BitsPerPixelCount = Bits_Per_Pixel_Count;
                pVideoSpecific->CompressionID = Compression_ID;
                pVideoSpecific->ImageSize = Image_Size;
                pVideoSpecific->HorizotalPixelsPerMeter = Horizontal_Pixels_Per_Meter;
                pVideoSpecific->VerticalPixelsPerMeter = Vertical_Pixels_Per_Meter;
                pVideoSpecific->ColorsUserdCount = Colors_Used_Count;
                pVideoSpecific->ImportantColorCount = Important_Colors_Count;

                pVideoSpecific->CodecSDataLength = BeforeOffset;

                if (pVideoSpecific->CodecSDataLength > 0)
                {
                    pVideoSpecific->CodecSpecificData = ASF_Malloc(BeforeOffset);
                    Stream_CopyBufferAndMoveOn(pstData, (pVideoSpecific->CodecSpecificData), BeforeOffset);
                    DataNum -= BeforeOffset;
                }

                HI_INFO_ASF("pVideoSpecific->CodecSDataLength:0x%x\n", pVideoSpecific->CodecSDataLength);
                for (index = 0; index < pVideoSpecific->CodecSDataLength; index++)
                {
                    HI_INFO_ASF("%02x ", pVideoSpecific->CodecSpecificData[index]);
                }

                HI_INFO_ASF("\n");

                HI_INFO_ASF("pVideoSpecific->CodecSpecificData[index-1]:%x\n", pVideoSpecific->CodecSpecificData[index - 1]);
                HI_INFO_ASF("pVideoSpecific->CodecSpecificData[index-2]:%x\n", pVideoSpecific->CodecSpecificData[index - 2]);
                HI_INFO_ASF("pVideoSpecific->CodecSpecificData[index-3]:%x\n", pVideoSpecific->CodecSpecificData[index - 3]);
                HI_INFO_ASF("pVideoSpecific->CodecSpecificData[index-4]:%x\n", pVideoSpecific->CodecSpecificData[index - 4]);
                HI_INFO_ASF("\n");

                //  0x59445250 ==‘PRDY’.
                if (0x59445250 == Compression_ID)
                {
                    HI_INFO_ASF("PlayReady Protected Video!\n");
                    DataNum -= 4;
                    BeforeOffset -= 4;

                    Compression_ID = 0;
                    Compression_ID = (pVideoSpecific->CodecSpecificData[index - 1] << 24) + \
                                     (pVideoSpecific->CodecSpecificData[index - 2] << 16) + \
                                     (pVideoSpecific->CodecSpecificData[index - 3] << 8) + \
                                     (pVideoSpecific->CodecSpecificData[index - 4]);

                    HI_INFO_ASF("Compression_ID:0x%x\n", Compression_ID);
                    pVideoSpecific->CompressionID = Compression_ID;
                    g_IsWhatEncryp = IS_PLAYREADY_ENCRYPT;
                    HI_ERR_PLAYREADY("g_IsWhatEncryp = IS_PLAYREADY_ENCRYPT\n");
                }
                else
                {
                    HI_INFO_ASF("g_IsWhatEncryp = IS_WMDRM_ENCRYPT\n");
                    g_IsWhatEncryp = IS_WMDRM_ENCRYPT;
                }

                ASFHandle->Videocodec_id = ff_codec_get_id(ff_codec_bmp_tags, Compression_ID);
                memcpy(Tag, (HI_U8 *)(&Compression_ID), 4);
                HI_INFO_ASF("Video codec_id:%x, Video Tag:%c%c%c%c\n", ASFHandle->Videocodec_id, Tag[0], Tag[1], Tag[2],
                       Tag[3]);

                ASFHandle->streaminfo.Video_Stream_Number = Stream_Number;
                HI_INFO_ASF("Type_Specific_Data_Length:0x%x, Video_Stream_Number:0x%x\n", Type_Specific_Data_Length,
                       ASFHandle->streaminfo.Video_Stream_Number);
            }
            else if ((guidcmp(Stream_Type, ASF_AUDIO_MEDIA_GUID) == 0))
            {
                HI_U32 Format_Tag, Number_of_Channels, Samples_Per_Second, Average_Number_of_Bytes_per_Second;
                HI_U32 Block_Alignment, Bits_Per_Sample, Codec_Specific_Data_Size, index;
                HI_U8 Codec_Specific_Data[255];
                HI_U32 Real_Format_Tag = 0;

                /*Standard WAVEFORMATEX Structure
                typedefstruct {
                    WORD wFormatTag;      //2B, wFormatTag是格式标签，如pcm格式是0,Adpcm是1,杜比Ac3是30
                    WORD nChannels;       //2B,nChannels是声道数
                    DWORD nSamplesPerSec; //4B,采样率
                    DWORD nAvgBytesPerSec;//24B,平均传输速率
                    WORD nBlockAlign;     //2B,数据块调整度(块对其,字节)，其值为通道数*样本的数据位值/8
                    WORD wBitsPerSample;  //2B,每个样本的位数
                    WORD cbSize;
                }WAVEFORMATEX;
                 */

                //ASF_Audio_Media:Specifies the unique ID of the codec used to encode the audio data
                Format_Tag = Stream_GetLittleEndianU16AndMoveOn(pstData);
                DataNum -= 2;
                if (Format_Tag == 0x161)
                {
                    HI_INFO_ASF("Audio Type Windows Media Audio\n");
                }
                /*
                                else if (Format_Tag == 0x161)
                                {
                                    printf("Audio Type Windows Media Audio 9 Professional\n");
                                }
                                else if (Format_Tag == 0x162)
                                {
                                    printf("Audio Type Windows Media Audio 9 Lossless\n");
                                }
                                else if (Format_Tag == 0x163)
                                {
                                    printf("Audio Type GSM-AMR: Fixed bit rate, no SID\n");
                                }
                                else if (Format_Tag == 0x7A21)
                                {
                                    printf("Audio Type GSM-AMR: Variable bit rate, including SID\n");
                                }
                                else if (Format_Tag == 0x7A22)
                                {
                                    printf("Audio Type Windows Media Audio\n");
                                }
                                else if (Format_Tag == 0x00)
                                {
                                    //PCM
                                }
                                else if (Format_Tag == 0x01)
                                {
                                    //ADPCM
                                }
                                else if (Format_Tag == 30)
                                {
                                    //AC3
                                }
                 */
                else if (Format_Tag == 0x5052)
                {
                    HI_INFO_ASF("PlayReady Protected Audio!\n");
                }
                else
                {
                    HI_INFO_ASF("\n###########Unsupported Audio!###########\n");
                    HI_ERR_ASF("\n###########Unsupported Audio!###########\n");
                }

                //Number of Channels
                Number_of_Channels = Stream_GetLittleEndianU16AndMoveOn(pstData);
                DataNum -= 2;

                //Samples Per Second
                Samples_Per_Second = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;

                //Average Number of Bytes per Second
                Average_Number_of_Bytes_per_Second = Stream_GetLittleEndianU32AndMoveOn(pstData);
                DataNum -= 4;

                //Block Alignment
                Block_Alignment = Stream_GetLittleEndianU16AndMoveOn(pstData);
                DataNum -= 2;

                //Bits Per Sample
                Bits_Per_Sample = Stream_GetLittleEndianU16AndMoveOn(pstData);
                DataNum -= 2;

                //Codec Specific Data Size
                Codec_Specific_Data_Size = Stream_GetLittleEndianU16AndMoveOn(pstData);
                DataNum -= 2;

                //Codec Specific Data
                for (index = 0; index < Codec_Specific_Data_Size; index++)
                {
                    Codec_Specific_Data[index] = Stream_GetOneByteAndMoveOn(pstData);
                    DataNum -= 1;
                }

                //Audio payloads do not need to be of equal size!

                if (Format_Tag == 0x5052)
                {
                    Real_Format_Tag = Codec_Specific_Data[index - 2] + (((HI_U32)Codec_Specific_Data[index - 1]) << 8);

                    Format_Tag = Real_Format_Tag;
                    HI_ERR_PLAYREADY("g_IsWhatEncryp = IS_PLAYREADY_ENCRYPT\n");
                    g_IsWhatEncryp = IS_PLAYREADY_ENCRYPT;
                }
                else
                {
                    HI_ERR_PLAYREADY("g_IsWhatEncryp = IS_WMDRM_ENCRYPT\n");
                    g_IsWhatEncryp = IS_WMDRM_ENCRYPT;
                }

                if (Format_Tag != 0x5052)
                {
                    ASFHandle->Audiocodec_id = ff_codec_get_id(ff_codec_wav_tags, Format_Tag);
                }
                else
                {
                    ASFHandle->Audiocodec_id = ff_codec_get_id(ff_codec_wav_tags, Real_Format_Tag);
                }

                HI_INFO_ASF("Audio codec_id:0x%x, Format_Tag:0x%04x\n", ASFHandle->Audiocodec_id, Format_Tag);

                memset(&WMAPrivateData, 0, sizeof(ASF_WMA_FORMAT_S));
                WMAPrivateData.wFormatTag = Format_Tag;
                WMAPrivateData.nChannels = Number_of_Channels;
                WMAPrivateData.nSamplesPerSec  = Samples_Per_Second;
                WMAPrivateData.nAvgBytesPerSec = Average_Number_of_Bytes_per_Second;
                WMAPrivateData.nBlockAlign = Block_Alignment;
                WMAPrivateData.wBitsPerSample = Bits_Per_Sample;
                WMAPrivateData.cbSize = Codec_Specific_Data_Size;
                for (index = 0; index < Codec_Specific_Data_Size; index++)
                {
                    //WMAPrivateData.cbExtWord[index] = Codec_Specific_Data[index];
                    ;
                }

                memcpy((HI_U8*)&(WMAPrivateData.cbExtWord), (HI_U8*)Codec_Specific_Data, WMAPrivateData.cbSize);

                HI_INFO_ASF("wFormatTag:0x%x\n", WMAPrivateData.wFormatTag);
                HI_INFO_ASF("nChannels:0x%x\n", WMAPrivateData.nChannels);
                HI_INFO_ASF("nSamplesPerSec:0x%x\n", WMAPrivateData.nSamplesPerSec);
                HI_INFO_ASF("nAvgBytesPerSec:0x%x\n", WMAPrivateData.nAvgBytesPerSec);
                HI_INFO_ASF("nBlockAlign:0x%x\n", WMAPrivateData.nBlockAlign);
                HI_INFO_ASF("wBitsPerSample:0x%x\n", WMAPrivateData.wBitsPerSample);
                HI_INFO_ASF("cbSize:0x%x\n", WMAPrivateData.cbSize);
                for (index = 0; index < WMAPrivateData.cbSize; index++)
                {
                    HI_INFO_ASF("%02x ", WMAPrivateData.cbExtWord[index]);
                }

                HI_INFO_ASF("\n");

                ASFHandle->streaminfo.Audio_Stream_Number = Stream_Number;
                ASFHandle->streaminfo.Audio_Format_Tag = Format_Tag;
                HI_INFO_ASF("Audio_Stream_Number:0x%x\n", ASFHandle->streaminfo.Audio_Stream_Number);

                memcpy(&(ASFHandle->streaminfo.AudioSpecific), &WMAPrivateData, sizeof(ASF_WMA_FORMAT_S));
            }
            else
            {
                print_guid(Stream_Type);
                Stream_SeekBufferAndMoveOn(pstData, Type_Specific_Data_Length);
                DataNum -= Type_Specific_Data_Length;
            }

            //Error Correction Data
            //HI_INFO_ASF("Error_Correction_Data_Length:0x%x\n", Error_Correction_Data_Length);
            Stream_SeekBufferAndMoveOn(pstData, Error_Correction_Data_Length);
            DataNum -= Error_Correction_Data_Length;
        }
        else if (guidcmp(TempBuffer, ASF_CONTENT_ENCRYPTION_BOJECT_GUID) == 0)
        {
            HI_INFO_ASF("%s,%d:enter parse ASF_CONTENT_ENCRYPTION_BOJECT_GUID \n",__FUNCTION__,__LINE__);
        }
        else if (guidcmp(TempBuffer, ASF_EXTENDED_CONTENT_ENCRYPTION_GUID) == 0)
        {
            HI_INFO_ASF("%s,%d:enter parse ASF_EXTENDED_CONTENT_ENCRYPTION_GUID \n",__FUNCTION__,__LINE__);
        }
        else if (guidcmp(TempBuffer, ASF_PROTECTION_SYSTEM_IDENTIFIER_OBJECT_GUID) == 0)
        {
            HI_U32 loop;
            HI_U32 u32SystemVersion = 0;
            HI_U32 dataLen = 0;
            HI_U8 *stringData = NULL;

            Stream_CopyBufferAndMoveOn(pstData, TempBuffer, __ASF_GID_NUM__);
            if (guidcmp(TempBuffer, ASF_CONTENT_PROTECTION_SYSTEM_MICROSOFT_PLAYREADY_GUID) != 0)
            {
                HI_INFO_ASF("IT'S NOT MICROSOFT PLAYREADY PROTECTION SYSTEM!\n");
                print_guid(TempBuffer);
                break;
            }

            g_IsWhatEncryp = IS_PLAYREADY_ENCRYPT;

            u32SystemVersion = Stream_GetLittleEndianU32AndMoveOn(pstData);
            HI_INFO_ASF("u32SystemVersion:%d\n", u32SystemVersion);

            HI_INFO_ASF("ASF_PROTECTION_SYSTEM_IDENTIFIER_OBJECT, ObjectSize:0x%x\n", ObjectSize);

            //Data Size
            dataLen = Stream_GetLittleEndianU32AndMoveOn(pstData);
            DataNum -= 4;

            //Secret Data
            stringData = (HI_U8 *)ASF_Malloc(dataLen + 1);
            memset(stringData, 0, dataLen + 1);
            Stream_CopyBufferAndMoveOn(pstData, stringData, dataLen);
            DataNum -= dataLen;

            HI_INFO_ASF("Data.length:%d\n", dataLen);

            //(ASFHandle->drmInitdata).setCapacity(dataLen);
            HI_INFO_ASF("start append initdata\n");
            //Vector<HI_U8> drmInitdata;
            //(ASFHandle->drmInitdata).appendArray(stringData,10);
            drmInitdata.appendArray(stringData,dataLen);
            //check data
            //PRINT_VECTOR(drmInitdata,"initdata");

            /*construct a uuid for playready,as no 'pssh' data*/
            const HI_U8 kPlayReadyUuid[16] = {
                0x9a, 0x04, 0xF0, 0x79, 0x98, 0x40, 0x42, 0x86,
                0xAB, 0x92, 0xE6, 0x5B, 0xE0, 0x88, 0x5F, 0x95
            };
            memset(ASFHandle->uuid,0,16);
            memcpy(ASFHandle->uuid,kPlayReadyUuid,16);

            ASFHandle->bneedDrm = HI_TRUE;

        }
        else if (guidcmp(TempBuffer, ASF_STREAM_PROPERTIES_OBJECT_GUID) == 0)
        {
            HI_INFO_ASF("ASF_STREAM_PROPERTIES_OBJECT_GUID\n");
        }
        else if (guidcmp(TempBuffer, ASF_PAYLOAD_Extension_System_Encryption_Sample_ID) == 0)
        {
            HI_INFO_ASF("ASF_PAYLOAD_Extension_System_Encryption_Sample_ID!!!!!!!\n");
        }
        else
        {
            //Do not need to deal with those object
            HI_INFO_ASF("Unknow GUID ObjectSize:0x%x\n", ObjectSize);
            print_guid(TempBuffer);
            Stream_SeekBufferAndMoveOn(pstData, (ObjectSize - __ASF_GID_NUM__ - 8));
            DataNum -= (ObjectSize - __ASF_GID_NUM__ - 8);
        }
    }

    VdecType = HI_UNF_VCODEC_TYPE_BUTT;
    if ((ASFHandle->Videocodec_id == CODEC_ID_WMV1) || (ASFHandle->Videocodec_id == CODEC_ID_WMV2)
        || (ASFHandle->Videocodec_id == CODEC_ID_WMV3))
    {
        HI_INFO_ASF("Video is WMV\n");
        VdecType = HI_UNF_VCODEC_TYPE_VC1;
        IsHighProfile = HI_FALSE;
    }
    else if (ASFHandle->Videocodec_id == CODEC_ID_VC1)
    {
        HI_INFO_ASF("Video is VC1\n");
        VdecType = HI_UNF_VCODEC_TYPE_VC1;
        IsHighProfile = HI_TRUE;
    }
    else if (ASFHandle->Videocodec_id == CODEC_ID_H264)
    {
        HI_INFO_ASF("Video is H264\n");
        VdecType = HI_UNF_VCODEC_TYPE_H264;
    }
    else  if (ASFHandle->Videocodec_id == CODEC_ID_MPEG4)
    {
        HI_INFO_ASF("Video is MPEG4\n");
        VdecType = HI_UNF_VCODEC_TYPE_MPEG4;
    }
    else if (ASFHandle->Videocodec_id == CODEC_ID_MPEG2VIDEO)
    {
        HI_INFO_ASF("Video is MPEG2\n");
        VdecType = HI_UNF_VCODEC_TYPE_MPEG2;
    }

    AdecType = 0;
    if ((ASFHandle->Audiocodec_id == CODEC_ID_WMAV1) || (ASFHandle->Audiocodec_id == CODEC_ID_WMAV2))
    {
        AdecType = HA_AUDIO_ID_WMA9STD;
    }

#ifdef __FFMPEG_DECODE__
    else if (ASFHandle->Audiocodec_id == CODEC_ID_WMAPRO)
    {
        AdecType = HA_AUDIO_ID_FFMPEG_DECODE;
    }
#endif
    else if (ASFHandle->Audiocodec_id == CODEC_ID_AC3)
    {
        // AdecType = HA_AUDIO_ID_AC3;
        ;
    }
    else if (ASFHandle->Audiocodec_id == CODEC_ID_WMALOSSLESS)
    {}
    else if ((ASFHandle->Audiocodec_id == CODEC_ID_MP2) || (ASFHandle->Audiocodec_id == CODEC_ID_MP3))
    {
        AdecType = HA_AUDIO_ID_MP3;
    }

    HI_INFO_ASF("Set AVPlay start VdecType:0x%x, AdecType:0x%x\n", VdecType, AdecType);
    ASF_StartAVplay(ASFHandle->avhandle, VdecType, IsHighProfile, AdecType, &WMAPrivateData, (HI_U32*)&(ASFHandle->VideoEnable),
                    (HI_U32*)&(ASFHandle->AudioEnable));
    HI_INFO_ASF("Set AVPlay start VdecType:0x%x, AdecType:0x%x, ASFHandle->VideoEnable:%d\n", VdecType, AdecType,
           ASFHandle->VideoEnable);

    /*prepare drm for decrypt*/
    if (ASFHandle->bneedDrm == HI_TRUE)
    {
        HI_INFO_ASF("start to open drm \n");
        ASF_MediaDrm_Prepare(ASFHandle->uuid,drmInitdata);
    }

    HI_INFO_ASF("ASFHandle->WMDRMhandle:0x%x\n", ASFHandle->WMDRMhandle);

    return HI_SUCCESS;
}

/*include decrypt if have encrypt data*/
static HI_U32 ASF_Parse_Packet(HI_ASF_HANDLE *ASFHandle, HI_U32 PacketSize)
{
    HI_U32 DataNum = PacketSize;
    ASF_PACKET_BUFFER_S *pAsfPacketBuffer;
    HI_U32 Error_Correction_Flags, Error_Correction_Data_Length, Opaque_Data_Present;
    HI_U32 Length_Type_Flags, Multiple_Payloads_Present, Sequence_Type, Padding_Length_Type;
    HI_U32 Packet_Length_Type, Error_Correction_Present, Property_Flags, Replicated_Data_Length_Type;
    HI_U32 Offset_Into_Media_Object_Length_Type, Media_Object_Number_Length_Type, Stream_Number_Length_Type;
    HI_U32 Packet_Length, Sequence, Padding_Length, Duration;
    HI_U32 Stream_Number, IsKeyFrame, Media_Object_Number, Offset_Into_Media_Object, Replicated_Data_Length = 0,
           Payload_Length;
    HI_U32 Payload_Flags, Number_of_Payloads, Payload_Length_Type;
    HI_U32 Presentation_Time_Delta, Sub_PayloadFlag = HI_FALSE;
    HI_S32 Send_Time;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32TempTimeStamp;

    HI_U8 Replicated_Data[256];

    HI_BOOL IsEncrypt = HI_FALSE;

    pAsfPacketBuffer = &(ASFHandle->asfbuffer);

    //if ((ASFHandle->streaminfo.EncryVer1.Valid == HI_TRUE) || (ASFHandle->streaminfo.EncryVer2.Valid == HI_TRUE))
    //{
    //    IsEncrypt = HI_TRUE;
    //}

    if (ASFHandle->bneedDrm == HI_TRUE)
    {
        IsEncrypt = HI_TRUE;
    }

    //HI_INFO_ASF("ASF_Parse_Packet\n");

    //Error Correction Flags
    Error_Correction_Flags = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
    DataNum -= 1;

    if ((Error_Correction_Flags & 0x80) == 0x80)
    {
        //Error Correction Present
        Error_Correction_Data_Length = Error_Correction_Flags & 0x0F;
        Stream_SeekBufferAndMoveOn(pAsfPacketBuffer, Error_Correction_Data_Length);
        DataNum -= Error_Correction_Data_Length;

        Opaque_Data_Present = Error_Correction_Flags & 0x10;
        if (Opaque_Data_Present)
        {
            //Opaque Data Occur, No useful payload data
            HI_INFO_ASF("Opaque Data Occur\n");
            return HI_SUCCESS;
        }
    }

   // HI_INFO_ASF("Error_Correction_Flags:0x%x\n", Error_Correction_Flags);
    //HI_INFO_ASF("Error_Correction_Data_Length:0x%x\n", Error_Correction_Data_Length);

    //payload parsing information
    Length_Type_Flags = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
    DataNum -= 1;

    Multiple_Payloads_Present = Length_Type_Flags & 0x01;
    Sequence_Type = (Length_Type_Flags & 0x06) >> 1;
    Padding_Length_Type = (Length_Type_Flags & 0x18) >> 3;
    Packet_Length_Type = (Length_Type_Flags & 0x60) >> 5;
    Error_Correction_Present = (Length_Type_Flags & 0x80) >> 7;

    Property_Flags = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
    DataNum -= 1;
    Replicated_Data_Length_Type = Property_Flags & 0x03;
    Offset_Into_Media_Object_Length_Type = (Property_Flags & 0x0c) >> 2;
    Media_Object_Number_Length_Type = (Property_Flags & 0x30) >> 4;
    Stream_Number_Length_Type = (Property_Flags & 0xc0) >> 6;

    //Packet Length
    if (Packet_Length_Type == 0x03)
    {
        Packet_Length = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
        DataNum -= 4;
    }
    else if (Packet_Length_Type == 0x02)
    {
        Packet_Length = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
        DataNum -= 2;
    }
    else if (Packet_Length_Type == 0x01)
    {
        Packet_Length = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
        DataNum -= 1;
    }
    else
    {
        Packet_Length = 0;
    }

#if 0
    //Adjust by FFMPEG
    if (Packet_Length == 0)
    {
        Packet_Length = ASFHandle->streaminfo.PackSize;
    }
#endif

    //Sequence
    if (Sequence_Type == 0x03)
    {
        Sequence = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
        DataNum -= 4;
    }
    else if (Sequence_Type == 0x02)
    {
        Sequence = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
        DataNum -= 2;
    }
    else if (Sequence_Type == 0x01)
    {
        Sequence = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
        DataNum -= 1;
    }
    else
    {
        Sequence = 0;
    }

    //Padding Length
    if (Padding_Length_Type == 0x03)
    {
        Padding_Length = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
        DataNum -= 4;
    }
    else if (Padding_Length_Type == 0x02)
    {
        Padding_Length = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
        DataNum -= 2;
    }
    else if (Padding_Length_Type == 0x01)
    {
        Padding_Length = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
        DataNum -= 1;
    }
    else
    {
        Padding_Length = 0;
    }

    //Send Time
    Send_Time = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
    DataNum -= 4;

    //Duration
    Duration = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
    DataNum -= 2;

   // HI_INFO_ASF("Length_Type_Flags:0x%x\n", Length_Type_Flags);
   // HI_INFO_ASF("Multiple_Payloads_Present:0x%x\n", Multiple_Payloads_Present);
    //HI_INFO_ASF("Sequence_Type:0x%x\n", Sequence_Type);
    //HI_INFO_ASF("Padding_Length_Type:0x%x\n", Padding_Length_Type);
   // HI_INFO_ASF("Packet_Length_Type:0x%x\n", Packet_Length_Type);
    //HI_INFO_ASF("Error_Correction_Present:0x%x\n", Error_Correction_Present);
   // HI_INFO_ASF("Property_Flags:0x%x\n", Property_Flags);
    //HI_INFO_ASF("Replicated_Data_Length_Type:0x%x\n", Replicated_Data_Length_Type);
    //HI_INFO_ASF("Offset_Into_Media_Object_Length_Type:0x%x\n", Offset_Into_Media_Object_Length_Type);
    //HI_INFO_ASF("Media_Object_Number_Length_Type:0x%x\n", Media_Object_Number_Length_Type);
   // HI_INFO_ASF("Stream_Number_Length_Type:0x%x\n", Stream_Number_Length_Type);
   // HI_INFO_ASF("Packet_Length:0x%x\n", Packet_Length);
   // HI_INFO_ASF("Sequence:0x%x\n", Sequence);
   // HI_INFO_ASF("Padding_Length:0x%x\n", Padding_Length);
   // HI_INFO_ASF("Send_Time:0x%x\n", Send_Time);
   // HI_INFO_ASF("Duration:0x%x\n", Duration);

    //payload data
    if (Multiple_Payloads_Present == 0)  //Single Payload
    {
        //Stream Number
        Stream_Number = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);

        //  HI_INFO_ASF("Stream_Number:0x%x\n", Stream_Number);
        IsKeyFrame = (Stream_Number & 0x80) >> 7;
        Stream_Number = Stream_Number & 0x7f;
        DataNum -= 1;

        //Media Object Number
        if (Media_Object_Number_Length_Type == 0x03)
        {
            Media_Object_Number = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
            DataNum -= 4;
        }
        else if (Media_Object_Number_Length_Type == 0x02)
        {
            Media_Object_Number = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
            DataNum -= 2;
        }
        else if (Media_Object_Number_Length_Type == 0x01)
        {
            Media_Object_Number = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
            DataNum -= 1;
        }
        else
        {
            Media_Object_Number = 0;
        }

        //Offset Into Media Object
        if (Offset_Into_Media_Object_Length_Type == 0x03)
        {
            Offset_Into_Media_Object = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
            DataNum -= 4;
        }
        else if (Offset_Into_Media_Object_Length_Type == 0x02)
        {
            Offset_Into_Media_Object = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
            DataNum -= 2;
        }
        else if (Offset_Into_Media_Object_Length_Type == 0x01)
        {
            Offset_Into_Media_Object = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
            DataNum -= 1;
        }
        else
        {
            Offset_Into_Media_Object = 0;
        }

        //Replicated Data Length
        if (Replicated_Data_Length_Type == 0x03)
        {
            Replicated_Data_Length = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
            DataNum -= 4;
        }
        else if (Replicated_Data_Length_Type == 0x02)
        {
            Replicated_Data_Length = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
            DataNum -= 2;
        }
        else if (Replicated_Data_Length_Type == 0x01)
        {
            Replicated_Data_Length = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
            DataNum -= 1;
        }
        else
        {
            Replicated_Data_Length = 0;
        }

        //Skip Replicated Data
        if (Replicated_Data_Length == 1)
        {
            //If the value of Replicated_Data_Length is set to 1, the payload should be interpreted as a compressed payload
            Presentation_Time_Delta = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
            DataNum -= 1;
            Sub_PayloadFlag = HI_TRUE;
        }
        else if ((Replicated_Data_Length == 0) || (Replicated_Data_Length >= 8))
        {
            //Stream_SeekBufferAndMoveOn(pAsfPacketBuffer, Replicated_Data_Length);

            memset(Replicated_Data, 0, 256);
            if (Replicated_Data_Length > 256)
            {
                HI_ERR_ASF("Replicated_Data_Length Parse TOO LARGE!!\n");
                return HI_FAILURE;
            }

            //HI_INFO_ASF("Replicated_Data_Length:%d\n", Replicated_Data_Length);
            Stream_CopyBufferAndMoveOn(pAsfPacketBuffer, Replicated_Data, Replicated_Data_Length);
            {
                HI_U32 i = 0;
                HI_INFO_ASF("Replicated_Data_Length:%d\n", Replicated_Data_Length);
               // for (i = 0; i < Replicated_Data_Length; i++)
                {
                    HI_RAW_DATA_INFO_ASF("0x%x, ", Replicated_Data[i]);
                }
                HI_RAW_DATA_INFO_ASF("\n");
                memcpy(&u32TempTimeStamp,Replicated_Data + 4,4);
               // HI_INFO_ASF("TimeStamp : %u\n",u32TempTimeStamp);
            }

            DataNum -= Replicated_Data_Length;
            Sub_PayloadFlag = HI_FALSE;
        }
        else
        {
            HI_ERR_ASF("Invalid Replicated_Data_Length!\n");
            return HI_FAILURE;
        }

        //HI_INFO_ASF("IsKeyFrame:0x%x, Stream_Number:0x%x\n", IsKeyFrame, Stream_Number);
        //HI_INFO_ASF("Media_Object_Number:0x%x\n", Media_Object_Number);
       // HI_INFO_ASF("Offset_Into_Media_Object:0x%x\n", Offset_Into_Media_Object);
        //HI_INFO_ASF("Replicated_Data_Length:0x%x\n", Replicated_Data_Length);

        //We Now come to real payload data!
        Payload_Length = DataNum - Padding_Length;

        if (Sub_PayloadFlag == HI_TRUE)
        {
            //printf("Sub_PayloadFlag is True\n");
            do
            {
                HI_U8 Sub_Payload_X_Data_Length = 0;

                Sub_Payload_X_Data_Length = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
                if (Payload_Length < Sub_Payload_X_Data_Length)
                {
                    //HI_ERR_ASF("Error SubPayload size\n");
                    break;
                }

                DataNum -= Sub_Payload_X_Data_Length;
                Payload_Length -= Sub_Payload_X_Data_Length;
                //HI_INFO_ASF("send time : %u,Duration : %u,Stream_Number : %u\n",Send_Time,Duration,Stream_Number);
                ASFHandle->streaminfo.CurrentStreamNumber = Stream_Number;
                ASFHandle->streaminfo.CurrentMediaObjectNumber = Media_Object_Number;
                ret = ASF_Payload(ASFHandle, Sub_Payload_X_Data_Length, Stream_Number, u32TempTimeStamp, IsKeyFrame, IsEncrypt,
                                  Replicated_Data, Replicated_Data_Length);
                if (ret != HI_SUCCESS)
                {
                    return ret;
                }
            } while (Payload_Length > 0);
        }
        else
        {
            //HI_INFO_ASF("send time : %u,Duration : %u,Stream_Number : %u\n",Send_Time,Duration,Stream_Number);
            ASFHandle->streaminfo.CurrentStreamNumber = Stream_Number;
            ASFHandle->streaminfo.CurrentMediaObjectNumber = Media_Object_Number;
            ret = ASF_Payload(ASFHandle, Payload_Length, Stream_Number, u32TempTimeStamp, IsKeyFrame, IsEncrypt,
                              Replicated_Data, Replicated_Data_Length);
            if (ret != HI_SUCCESS)
            {
                return ret;
            }
        }
    }
    else //Multiple Payload
    {
        HI_U32 index;

        Payload_Flags = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
        DataNum -= 1;
        Number_of_Payloads  = Payload_Flags & 0x3f;
        Payload_Length_Type = (Payload_Flags & 0xc0) >> 6;

       // HI_INFO_ASF("Multiple Payload Payload_Flags:0x%x\n", Payload_Flags);
        //HI_INFO_ASF("Number_of_Payloads:0x%x\n", Number_of_Payloads);
        //HI_INFO_ASF("Payload_Length_Type:0x%x\n", Payload_Length_Type);

        if (Payload_Length_Type != 0x02)
        {
            HI_ERR_ASF("Number_of_Payloads:0x%x\n", Number_of_Payloads);
            HI_ERR_ASF("Multiple Payload Payload_Length_Type ERROR:0x%x !=0x02\n", Payload_Length_Type);
            return HI_FAILURE;
        }

        for (index = 0; index < Number_of_Payloads; index++)
        {
            //Stream Number
            Stream_Number = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
            IsKeyFrame = (Stream_Number & 0x80) >> 7;
            Stream_Number = Stream_Number & 0x7f;

            //printf("Stream_Number:%d\n", Stream_Number);

            DataNum -= 1;

            //Media Object Number
            if (Media_Object_Number_Length_Type == 0x03)
            {
                Media_Object_Number = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
                DataNum -= 4;
            }
            else if (Media_Object_Number_Length_Type == 0x02)
            {
                Media_Object_Number = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
                DataNum -= 2;
            }
            else if (Media_Object_Number_Length_Type == 0x01)
            {
                Media_Object_Number = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
                DataNum -= 1;
            }
            else
            {
                Media_Object_Number = 0;
            }

            //Offset Into Media Object
            if (Offset_Into_Media_Object_Length_Type == 0x03)
            {
                Offset_Into_Media_Object = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
                DataNum -= 4;
            }
            else if (Offset_Into_Media_Object_Length_Type == 0x02)
            {
                Offset_Into_Media_Object = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
                DataNum -= 2;
            }
            else if (Offset_Into_Media_Object_Length_Type == 0x01)
            {
                Offset_Into_Media_Object = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
                DataNum -= 1;
            }
            else
            {
                Offset_Into_Media_Object = 0;
            }

            //Replicated Data Length
            if (Replicated_Data_Length_Type == 0x03)
            {
                Replicated_Data_Length = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
                DataNum -= 4;
            }
            else if (Replicated_Data_Length_Type == 0x02)
            {
                Replicated_Data_Length = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
                DataNum -= 2;
            }
            else if (Replicated_Data_Length_Type == 0x01)
            {
                Replicated_Data_Length = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
                DataNum -= 1;
            }
            else
            {
                Replicated_Data_Length = 0;
            }

           // HI_INFO_ASF("index:0x%x, IsKeyFrame:0x%x, Stream_Number:0x%x\n", index, IsKeyFrame, Stream_Number);
           // HI_INFO_ASF("Media_Object_Number:0x%x\n", Media_Object_Number);
           // HI_INFO_ASF("Offset_Into_Media_Object:0x%x\n", Offset_Into_Media_Object);
            //HI_INFO_ASF("Replicated_Data_Length:0x%x\n", Replicated_Data_Length);

            //Skip Replicated Data
            if (Replicated_Data_Length == 1)
            {
                //If the value of Replicated_Data_Length is set to 1, the payload should be interpreted as a compressed payload
                Presentation_Time_Delta = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
                DataNum -= 1;
                Sub_PayloadFlag = HI_TRUE;
            }
            else if ((Replicated_Data_Length == 0) || (Replicated_Data_Length >= 8))
            {
                //Stream_SeekBufferAndMoveOn(pAsfPacketBuffer, Replicated_Data_Length);

                memset(Replicated_Data, 0, 256);
                if (Replicated_Data_Length > 256)
                {
                    HI_ERR_ASF("Replicated_Data_Length Parse TOO LARGE!!\n");
                    return HI_FAILURE;
                }

                Stream_CopyBufferAndMoveOn(pAsfPacketBuffer, Replicated_Data, Replicated_Data_Length);
                {
                    int i = 0;
                    //HI_INFO_ASF("Replicated_Data_Length:%d\n", Replicated_Data_Length);
                    for (i = 0; i < Replicated_Data_Length; i++)
                    {
                        HI_RAW_DATA_INFO_ASF("0x%x, ", Replicated_Data[i]);
                    }

                    HI_RAW_DATA_INFO_ASF("\n");
                    memcpy(&u32TempTimeStamp,Replicated_Data + 4,4);
                   // HI_INFO_ASF("TimeStamp : %u\n",u32TempTimeStamp);
                }
                Sub_PayloadFlag = HI_FALSE;
            }
            else
            {
                HI_ERR_ASF("Invalid Replicated_Data_Length!\n");
                return HI_FAILURE;
            }

            //Payload Length
            if (Payload_Length_Type == 0x03)
            {
                Payload_Length = Stream_GetLittleEndianU32AndMoveOn(pAsfPacketBuffer);
                DataNum -= 4;
            }
            else if (Payload_Length_Type == 0x02)
            {
                Payload_Length = Stream_GetLittleEndianU16AndMoveOn(pAsfPacketBuffer);
                DataNum -= 2;
            }
            else if (Payload_Length_Type == 0x01)
            {
                Payload_Length = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
                DataNum -= 1;
            }
            else
            {
                Payload_Length = 0;
            }

            //HI_INFO_ASF("Payload_Length_Type:0x%x\n", Payload_Length_Type);
           // HI_INFO_ASF("Payload_Length:0x%x\n", Payload_Length);
            if (Sub_PayloadFlag == HI_TRUE)
            {
                HI_U32 CompressIndex = 0;

                // HI_INFO_ASF("Compressed data\n");
                do
                {
                    HI_U8 Sub_Payload_X_Data_Length = 0;

                    Sub_Payload_X_Data_Length = Stream_GetOneByteAndMoveOn(pAsfPacketBuffer);
                    if (Payload_Length < Sub_Payload_X_Data_Length)
                    {
                        HI_ERR_ASF("Error SubPayload size\n");
                        break;
                    }

                    DataNum -= Sub_Payload_X_Data_Length;
                    Payload_Length -= Sub_Payload_X_Data_Length;

                    //HI_INFO_ASF("Compressed index :0x%x,sublength:0x%x,\n", CompressIndex, Sub_Payload_X_Data_Length);
                    //HI_INFO_ASF("111send time : %u,Duration : %u,Stream_Number : %u\n",Send_Time,Duration,Stream_Number);
                    ASFHandle->streaminfo.CurrentStreamNumber = Stream_Number;
                    ASFHandle->streaminfo.CurrentMediaObjectNumber = Media_Object_Number;
                    ret = ASF_Payload(ASFHandle, Sub_Payload_X_Data_Length, Stream_Number, u32TempTimeStamp, IsKeyFrame,
                                      IsEncrypt, Replicated_Data, Replicated_Data_Length);
                    if (ret != HI_SUCCESS)
                    {
                        return ret;
                    }

                    CompressIndex++;
                } while (Payload_Length > 0);
            }
            else
            {
                ASFHandle->streaminfo.CurrentStreamNumber = Stream_Number;
                ASFHandle->streaminfo.CurrentMediaObjectNumber = Media_Object_Number;
                //HI_INFO_ASF("222send time : %u,Duration : %u,Stream_Number : %u\n",Send_Time,Duration,Stream_Number);
                ret = ASF_Payload(ASFHandle, Payload_Length, Stream_Number, u32TempTimeStamp, IsKeyFrame, IsEncrypt,
                                  Replicated_Data, Replicated_Data_Length);
                if (ret != HI_SUCCESS)
                {
                    return ret;
                }
            }
        } //for()
    } //if()

    return HI_SUCCESS;
}

static HI_U32 Stream_Extract(HI_ASF_HANDLE *ASFHandle)
{
    HI_S32 ret;
    HI_U8 *pPrevAddr, u32PrevOffset;

    //ASF_PACKET_BUFFER_S *pPacketBuffer = &(ASFHandle->asfbuffer);
    g_replicatedData = (HI_U8 *)malloc(sizeof(HI_U8) * 256);

    ASFHandle->asfbuffer.pu8CosumerAddr = ASFHandle->asfbuffer.pu8BaseAddr;

    //printf("TotalDataPackets:%d\n", ASFHandle->streaminfo.TotalDataPackets);
    while (ASFHandle->asfbuffer.u32ActualASFSize > 0)
    {
        if (ASFHandle->streaminfo.CurrentDataPacketIndex == 0)
        {
            HI_INFO_ASF("\nPacket parse begin!\n");
        }

        pPrevAddr = ASFHandle->asfbuffer.pu8CosumerAddr;
        u32PrevOffset = ASFHandle->asfbuffer.u32CurrentOffset;

        //printf("CurrentDataPacketIndex:%d\n", ASFHandle->streaminfo.CurrentDataPacketIndex);

        //Now We can parser ASF Packet.
        ret = ASF_Parse_Packet(ASFHandle, ASFHandle->streaminfo.PackSize);
        if (ret != HI_SUCCESS)
        {
            HI_INFO_ASF("ASF_Parse_Packet Return FAILURE!!!!!\n");
            ASFHandle->asfbuffer.pu8CosumerAddr   = pPrevAddr;
            ASFHandle->asfbuffer.u32CurrentOffset = u32PrevOffset;
            Stream_SeekBufferAndMoveOn(&(ASFHandle->asfbuffer), ASFHandle->streaminfo.PackSize);

            ASFHandle->streaminfo.CurrentDataPacketIndex++;

            if (ASFHandle->streaminfo.CurrentDataPacketIndex >= ASFHandle->streaminfo.TotalDataPackets)
            {
                printf("\nLatest Packet has parsed!\n");
                break;
            }

            ASFHandle->asfbuffer.u32ActualASFSize -= ASFHandle->streaminfo.PackSize;
            continue;
        }

        ASFHandle->asfbuffer.pu8CosumerAddr   = pPrevAddr;
        ASFHandle->asfbuffer.u32CurrentOffset = u32PrevOffset;
        Stream_SeekBufferAndMoveOn(&(ASFHandle->asfbuffer), ASFHandle->streaminfo.PackSize);

        ASFHandle->streaminfo.CurrentDataPacketIndex++;

        //printf("CurrentDataPacketIndex:%d!\n", ASFHandle->streaminfo.CurrentDataPacketIndex);

        if (ASFHandle->streaminfo.CurrentDataPacketIndex == ASFHandle->streaminfo.TotalDataPackets)
        {
            printf("\nLatest Packet has parsed!\n");
            break;
        }

        ASFHandle->asfbuffer.u32ActualASFSize -= ASFHandle->streaminfo.PackSize;
    }

    if (g_replicatedData != NULL)
    {
        free(g_replicatedData);
    }

    return HI_SUCCESS;
}

/*------------------------------------END---------------------------------------------*/
