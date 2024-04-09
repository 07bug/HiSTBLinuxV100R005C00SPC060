#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>              /* inet_pton */
#include <netdb.h>

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"

extern "C" {
#include "hi_adp_mpi.h"
#include "hi_adp_hdmi.h"
}

#include "hi_unf_avplay.h"
#include "hi_playready.h"
#include "hi_playreadyhttp.h"

#if defined(DOLBYPLUS_HACODEC_SUPPORT)
#include "HA.AUDIO.DOLBYPLUS.decode.h"
#endif

#include "asf_parser.h"

#define AVPLAY_AUDIO_BUFF_SIZE (2 * 1024 * 1024)
#define AVPLAY_VIDEO_BUFF_SIZE (9 * 1024 * 1024)
#define HTTP_HEAD  "http://"
#define HTTPS_HEAD "https://"

#include "ModularDrmInterface.h"
#include "CryptoInterface.h"

enum
{
    PROTOCAL_HTTP_HEAD = 0,
    PROTOCAL_HTTPS_HEAD,
    PROTOCAL_OTHER_HEAD
} PLAYREADY_PROTOCAL_HEAD;

#ifdef DEBUG
#define HI_PLAYREADY_INFO(fmt, args...)    printf(fmt, ## args)
#else
#define HI_PLAYREADY_INFO(fmt, args...)
#endif
#define HI_PLAYREADY_ERR(fmt, args...)    printf("[err] %s(), %d: " fmt, __FUNCTION__, __LINE__, ## args)

FILE              *g_pASFFile = HI_NULL;
static pthread_t g_ASFThd;
static HI_BOOL g_StopThread = HI_FALSE;
HI_PLAYREADY_Handle g_WMDRMhandle = 0;
static HI_CHAR *ps8ServerIp = HI_NULL;
static HI_U32 u32ServerPort = 0;

static HI_U8 u8Url[255] = {0};

HI_BOOL isTvp = HI_FALSE;

typedef struct
{
    PLAYREADY_HTTP_HEADER_S *headers;
    HI_S32 sockfd;
    HI_U32 ResponseCode;
    HI_U8* DataBuffer;
    HI_U32 Datalength;
} PLAYREADY_HTTP_HANDLE;

static HI_S32 CopyFromBufferToFile(HI_U8 *pu8Input, HI_U32 u32Length, HI_CHAR *pFileName)
{
    FILE *phFdEn = HI_NULL;
    HI_S32 s32Ret = HI_SUCCESS;

    if ( (HI_NULL == pFileName) || (HI_NULL == pu8Input) )
    {
        HI_PLAYREADY_ERR("NULL pointer input ! error!\n\n\n");
        return  HI_FAILURE;
    }

    phFdEn = fopen(pFileName, "w+");
    if( HI_NULL == phFdEn )
    {
         HI_PLAYREADY_ERR("Failed to fopen file %s.\n", pFileName);
         return HI_FAILURE;
    }

    s32Ret = fwrite((HI_VOID *)pu8Input, (size_t)1, (size_t)u32Length, phFdEn);
    if( u32Length != (HI_U32)s32Ret)
    {
        HI_PLAYREADY_ERR("fwrite to encrypt file failed.\n\n\n");
        fclose(phFdEn);
        return HI_FAILURE;
    }

    fclose(phFdEn);
    return HI_SUCCESS;
}

static void ParseUrl(HI_PLAYREADY_URL *drm_url, HI_U8 *url)
{
    HI_U8 *pcolon   = HI_NULL;
    HI_U8 *findhost = HI_NULL;
    HI_U8 *s = HI_NULL;
    HI_U8 *find = HI_NULL;

    memset(drm_url, 0, sizeof(HI_PLAYREADY_URL));
    drm_url->url = url;
    s = drm_url->url;
    if (drm_url->url == HI_NULL)
    {
        HI_PLAYREADY_ERR("Url is NULL.\n");
        return;
    }

    //url should be "HTTP://WWW.xxx.com:80/asdd.jsp"
    if ((findhost = (HI_U8*)strstr((HI_CHAR *)s, (HI_CHAR *)"//")) != HI_NULL)
    {
        if ((findhost > s) && (*(findhost - 1) == ':'))
        {
            strncpy((HI_CHAR *)drm_url->protocol, (HI_CHAR *)s, (HI_U32)(findhost - s - 1)); //should be "HTTP"
        }

        findhost += 2; //jump "//"
        if ((find = (HI_U8*)strchr((HI_CHAR *)findhost, (HI_S32)'/')) != HI_NULL)
        {
            strncpy((HI_CHAR *)drm_url->host, (HI_CHAR *)findhost, (HI_U32)(find - findhost));
//            drm_url->query = find;
            strncpy((HI_CHAR *)drm_url->query, (HI_CHAR *)find, strlen((HI_CHAR *)find) + 1);
        }
        else
        {
            strncpy((HI_CHAR *)drm_url->host, (HI_CHAR *)findhost, strlen((HI_CHAR *)findhost) + 1);
//            drm_url->query = HI_NULL;
            memset(drm_url->query,0,sizeof(drm_url->query));
        }

        pcolon = (HI_U8 *)strchr((HI_CHAR *)drm_url->host, (HI_S32)':');
        if (pcolon != HI_NULL)
        {
            drm_url->port = (HI_U32)atoi((HI_CHAR *)(pcolon + 1)); //transfer port to numeric
            pcolon = '\0';                  //remove :port form host
        }
        else
        {
            struct servent * svt = HI_NULL;

            //svt=getservbyname( "http ", "tcp");
            svt = getservbyname((HI_CHAR *)drm_url->protocol, "tcp");
            if (svt != (struct servent*)HI_NULL)
            {
                drm_url->port = (HI_U32)ntohs((HI_U16)svt->s_port);
            }
            else
            {
                drm_url->port = 0;
            }
        }
    }
    else
    {
        drm_url->port  = 80;
//        drm_url->query = s;
        strncpy((HI_CHAR *)drm_url->query, (HI_CHAR *)s, strlen((HI_CHAR *)s) + 1);
    }

    if (drm_url->port == 0)
    {
        drm_url->port = 80;
    }

    HI_PLAYREADY_INFO("protocol:%s, host:%s, port:%d, query:%s\n", drm_url->protocol, drm_url->host, drm_url->port, drm_url->query);
    return;
}

static HI_S32 GetProtocalHead(HI_U8* url)
{
    HI_U8* urlHead;

    urlHead = (HI_U8 *)strstr((HI_CHAR *)url, (HI_CHAR *)HTTP_HEAD);
    if (NULL != urlHead)
    {
        return PROTOCAL_HTTP_HEAD;
    }

    urlHead = (HI_U8 *)strstr((HI_CHAR *)url, (HI_CHAR *)HTTPS_HEAD);
    if (NULL != urlHead)
    {
        return PROTOCAL_HTTPS_HEAD;
    }

    return PROTOCAL_OTHER_HEAD;
}

static HI_S32 HttpClientPlayInit(CURL **curl, HI_PLAYREADY_CHALLENGE_S *pChallenge, HI_PLAYREADY_URL *pstUrl)
{
    // use curl to process http&https request
    CURLcode return_code;
    HI_U8 u8Url[255];
    HI_U8 protocalHead;

    if ( (HI_NULL == curl)  || (HI_NULL == pChallenge) || (HI_NULL == pstUrl))
    {
        HI_PLAYREADY_ERR("invalid param, null pointer in httpclient init funcTion!\n");
        return HI_FAILURE;
    }

    // init libcurl
    return_code = curl_global_init(CURL_GLOBAL_ALL);
    if (CURLE_OK != return_code)
    {
        HI_PLAYREADY_ERR("init libcurl failed!\n");
        return HI_FAILURE;
    }

    // get easy handle
    *curl = curl_easy_init();
    HI_PLAYREADY_INFO("After curl init,curl addr:0x%x\n", *curl);
    if (HI_NULL == *curl)
    {
        HI_PLAYREADY_ERR("get a easy handle failed!\n");
        return HI_FAILURE;
    }

    memset(pstUrl, 0x00, sizeof(HI_PLAYREADY_URL));
    memcpy(u8Url, pChallenge->URL.pszString, pChallenge->URL.length);
    u8Url[pChallenge->URL.length] = '\0';
    HI_PLAYREADY_INFO("pChallenge->URL.length = %d\n", pChallenge->URL.length);
    HI_PLAYREADY_INFO("HTTP Post to : %s\n", u8Url);

    //check url is http or https
    protocalHead = GetProtocalHead(u8Url);

    // https ssl process
    if (PROTOCAL_HTTPS_HEAD == protocalHead)
    {
        HI_PLAYREADY_INFO("is https url\n");
        return_code = curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYPEER, 0);
        return_code = curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYHOST, 0);
    }
    // set url
    return_code = curl_easy_setopt(*curl, CURLOPT_URL, u8Url);

    ParseUrl(pstUrl, u8Url); //Get host, port of URL, query

    if ( HI_NULL != ps8ServerIp)
    {
        strncpy((HI_CHAR *)pstUrl->host, ps8ServerIp, strlen(ps8ServerIp) + 1);
        pstUrl->port = u32ServerPort;
        HI_PLAYREADY_INFO(" Mode 1 http client ps8ServerIp %s\n", pstUrl->host);
        HI_PLAYREADY_INFO("Mode 1 http server port : %d\n",pstUrl->port);
    }else
    {
        HI_PLAYREADY_INFO(" Mode 0 http client ps8ServerIp %s\n", pstUrl->host);
        HI_PLAYREADY_INFO("Mode 0 http server port : %d\n",pstUrl->port);
    }

    // set CURLOPT_POST 1 indicates this time is POST operation
    return_code = curl_easy_setopt(*curl, CURLOPT_POST, 1);

    return HI_SUCCESS;

}

static HI_S32 HttpClientDeInit(CURL *curl)
{
    if ( 0 == curl )
    {
        HI_PLAYREADY_ERR("invalid curl in http client deinit!\n");
        return HI_FAILURE;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return HI_SUCCESS;
}

static HI_VOID ASFThread(HI_VOID *arg)
{
    HI_HANDLE ASFHandle = 0;
    HI_U32 Readlen = 0;
    HI_S32 ret = 0;
    HI_U32 RequireSize = 0;
    HI_U32 u32MinHeaderLen = 64 * 1024;                //Minum Size of File is 64K.
    HI_U32 u32LenToPacket = 0;
    HI_U32 u32PacketSize = 0;
    HI_U32 u32Readlen = 0;
    HI_UNF_STREAM_BUF_S stASFData = {0};

    HI_U8 *asfHeaderBuffer = (HI_U8*)malloc(sizeof(HI_U8) * u32MinHeaderLen);
    if (HI_NULL == asfHeaderBuffer)
    {
        HI_PLAYREADY_ERR("Malloc asfHeaderBuffer failed!\n");
        return;
    }

    ASFHandle = *((HI_HANDLE *)arg);
    HI_PLAYREADY_INFO("args:0x%x, ASFHandle:0x%x\n", (HI_U32)arg, (HI_U32)ASFHandle);

    u32Readlen = fread(asfHeaderBuffer, sizeof(HI_S8), u32MinHeaderLen, g_pASFFile);
    ret = HI_ASF_Head_Parser(ASFHandle, &u32LenToPacket, &u32PacketSize, asfHeaderBuffer, u32Readlen);

    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("HI_ASF_Head_Parser fail!\n ");
        free(asfHeaderBuffer);
        return;
    }
    free(asfHeaderBuffer);

    ret = fseek(g_pASFFile, u32LenToPacket, SEEK_SET);
    if (ret != 0)
    {
        HI_PLAYREADY_ERR("fseek failed\n");
        return;
    }

    RequireSize = u32PacketSize * 100;

    HI_PLAYREADY_INFO("u32PacketSize:%d, RequireSize:%d\n", u32PacketSize, RequireSize);

    while (!g_StopThread)
    {
        HI_PLAYREADY_INFO("\nEnter the ASF thread! \n");
        ret = HI_ASF_GetBuffer(ASFHandle, RequireSize, &stASFData);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("HI_ASF_GetBuffer Return Failed!\n ");
            return;
        }

        Readlen = fread(stASFData.pu8Data, sizeof(HI_U8), RequireSize, g_pASFFile);

        //Judge and inject ASF Data
        if (Readlen > 0)
        {
            if (Readlen != RequireSize)
            {
                HI_PLAYREADY_INFO("Maybe come to end to Read ASF file 0x%x, 0x%x\n", Readlen, RequireSize);
            }

            ret = HI_ASF_PutBuffer(ASFHandle, Readlen);
            if (ret != HI_SUCCESS)
            {
                HI_PLAYREADY_ERR("call HI_UNF_ASF_PutBuffer failed.\n");
                return;
            }
        }
        else
        {
            HI_PLAYREADY_INFO("File Parse Over, Thanks for Watching~^-^~\n");

            //rewind(g_pASFFile);
            return;
        }
    }

    return;
}

HI_S32 TsPlayerEventHandler(HI_HANDLE handle, HI_UNF_AVPLAY_EVENT_E enEvent, HI_U32 para)
{
    return HI_SUCCESS;
}

HI_S32 HIADP_AVPlay_ASF_SetAdecAttr(HI_HANDLE hAvplay, HI_U32 enADecType, HI_HA_DECODEMODE_E enMode, HI_S32 isCoreOnly,
                                    ASF_WMA_FORMAT_S *pWMAPrivateData)
{
    HI_UNF_ACODEC_ATTR_S AdecAttr;
    WAV_FORMAT_S stWavFormat;

    HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, &AdecAttr);
    AdecAttr.enType = enADecType;

    if (HA_AUDIO_ID_PCM == AdecAttr.enType)
    {
        HI_BOOL isBigEndian;

        /* set pcm wav format here base on pcm file */
        stWavFormat.nChannels = 1;
        stWavFormat.nSamplesPerSec = 48000;
        stWavFormat.wBitsPerSample = 16;
        /* if big-endian pcm */
        isBigEndian = HI_FALSE;
        if (HI_TRUE == isBigEndian)
        {
            stWavFormat.cbSize = 4;
            stWavFormat.cbExtWord[0] = 1;
        }

        HA_PCM_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam), &stWavFormat);
        HI_PLAYREADY_INFO("please make sure the attributes of PCM stream is tme same as defined in function of \"HIADP_AVPlay_SetAdecAttr\"? \n");
        HI_PLAYREADY_INFO("(nChannels = 1, wBitsPerSample = 16, nSamplesPerSec = 48000, isBigEndian = HI_FALSE) \n");
    }
    else if (HA_AUDIO_ID_MP2 == AdecAttr.enType)
    {
        HA_MP2_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }
    else if (HA_AUDIO_ID_AAC == AdecAttr.enType)
    {
        HA_AAC_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }
    else if (HA_AUDIO_ID_MP3 == AdecAttr.enType)
    {
        HA_MP3_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }
    else if (HA_AUDIO_ID_WMA9STD == AdecAttr.enType)
    {
        HI_PLAYREADY_INFO("Use WMA9STD\n");
        HA_WMA_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam), pWMAPrivateData);
    }
#ifdef __FFMPEG_DECODE__
    else if (HA_AUDIO_ID_FFMPEG_DECODE == AdecAttr.enType)
    {
        AdecAttr.enFmt = HI_UNF_ADEC_STRAM_FMT_PACKET;

        if (HI_NULL != pWMAPrivateData)
        {
            HA_FFMPEGC_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam), pWMAPrivateData);
        }
    }
#endif
    else
    {
        HA_DRA_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }

    HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, &AdecAttr);

    return HI_SUCCESS;
}

HI_S32 HIADP_AVPlay_ASF_SetVdecAttr(HI_HANDLE hAvplay, HI_UNF_VCODEC_TYPE_E enType, HI_BOOL IsHighProfile,
                                    HI_UNF_VCODEC_MODE_E enMode)
{
    HI_S32 Ret;
    HI_UNF_VCODEC_ATTR_S VdecAttr;

    Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr);
    if (HI_SUCCESS != Ret)
    {
        HI_PLAYREADY_ERR("HI_UNF_AVPLAY_GetAttr failed:%#x\n", Ret);
        return Ret;
    }

    VdecAttr.enType = enType;
    VdecAttr.enMode = enMode;
    VdecAttr.u32ErrCover = 100;
    VdecAttr.u32Priority = 3;

    if (enType == HI_UNF_VCODEC_TYPE_VC1)
    {
        if (IsHighProfile == HI_TRUE)
        {
            VdecAttr.unExtAttr.stVC1Attr.bAdvancedProfile = HI_TRUE;
            VdecAttr.unExtAttr.stVC1Attr.u32CodecVersion = 8;
            HI_PLAYREADY_INFO("VC1 AP\n");
        }
        else
        {
            VdecAttr.unExtAttr.stVC1Attr.bAdvancedProfile = HI_FALSE;
            VdecAttr.unExtAttr.stVC1Attr.u32CodecVersion = 5;
            HI_PLAYREADY_INFO("VC1 SM\n");
        }
    }

    Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr);
    if (Ret != HI_SUCCESS)
    {
        HI_PLAYREADY_INFO("VdecAttr.enType:%d\n", VdecAttr.enType);
        HI_PLAYREADY_INFO("VdecAttr.enMode:%d\n", VdecAttr.enMode);
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_SetAttr failed, Ret:0X%X\n.\n", Ret);
        return Ret;
    }

    return Ret;
}

HI_U32 ASF_StartAVplay(HI_HANDLE AVPlayHandle, HI_U32 enVideoCodec, HI_BOOL IsHighProfile, HI_U32 u32AdecTypeCodec,
                       ASF_WMA_FORMAT_S  *pWMAPrivateData, HI_U32 *VideoEnable, HI_U32 *AudioEnable)
{
    HI_U32 ret = HI_SUCCESS;
    HI_HANDLE hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;

    *AudioEnable = HI_FALSE;
    *VideoEnable = HI_FALSE;

    if (u32AdecTypeCodec != 0 && HI_FALSE == isTvp )
    {
        // 5. Start Audio Play
        ret = HI_UNF_AVPLAY_ChnOpen(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_ChnOpen failed.\n");
            goto Exit;
        }

        ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
            goto AVPLAY_CHN_CLOSE;
        }
        ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&hTrack);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("call HI_UNF_SND_CreateTrack failed.\n");
            goto AVPLAY_CHN_CLOSE;
        }

        ret = HI_UNF_SND_Attach(hTrack, AVPlayHandle);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("call HI_UNF_SND_Attach failed.\n");
            goto SND_TRACK_DESTROY;
        }

        ret = HI_UNF_SND_SetTrackMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, HI_UNF_TRACK_MODE_DOUBLE_MONO);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("call HI_UNF_SND_SetTrackMode failed.\n");
            goto SND_TRACK_DESTROY;
        }

        ret = HIADP_AVPlay_ASF_SetAdecAttr(AVPlayHandle, u32AdecTypeCodec, HD_DEC_MODE_RAWPCM, 0, pWMAPrivateData);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("%s(), %d, call HIADP_AVPlay_ASF_SetAdecAttr failed.\n", __FUNCTION__,__LINE__);
            goto SND_TRACK_DESTROY;
        }

        ret = HI_UNF_AVPLAY_Start(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("%s(), %d, call HI_UNF_AVPLAY_Start failed.\n", __FUNCTION__,__LINE__);
            goto SND_TRACK_DESTROY;
        }

        *AudioEnable = HI_TRUE;
    }

    if (enVideoCodec < HI_UNF_VCODEC_TYPE_BUTT)
    {
        HI_PLAYREADY_INFO("enVideoCodec:%d, HI_UNF_VCODEC_TYPE_VC1:%d\n", enVideoCodec, HI_UNF_VCODEC_TYPE_VC1);
        ret = HIADP_AVPlay_ASF_SetVdecAttr(AVPlayHandle, enVideoCodec, IsHighProfile, HI_UNF_VCODEC_MODE_NORMAL);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("call HIADP_AVPlay_ASF_SetVdecAttr failed.\n");
            goto SND_TRACK_DESTROY;
        }

        ret = HI_UNF_AVPLAY_Start(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_Start failed.\n");
            goto SND_TRACK_DESTROY;
        }

        *VideoEnable = HI_TRUE;
    }
    return HI_SUCCESS;

SND_TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);
AVPLAY_CHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(AVPlayHandle,HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
Exit:
    return ret;
}

static HI_S32 Asf_Open(HI_HANDLE *ohAVHandle, HI_HANDLE *ohWin)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_AVPLAY_ATTR_S stAttr;
    HI_UNF_SYNC_ATTR_S SyncAttr;
    HI_UNF_AVPLAY_TVP_ATTR_S    stAvTVPAttr;

    HI_HANDLE AVPlayHandle;
    HI_HANDLE hWin;

    // 2. Create AVPlayer
    ret = HI_UNF_AVPLAY_GetDefaultConfig(&stAttr, HI_UNF_AVPLAY_STREAM_TYPE_ES);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_GetDefaultConfig failed.\n");
        return HI_FAILURE;
    }

    //Get Param from Hiplayer
    stAttr.stStreamAttr.u32AudBufSize = AVPLAY_AUDIO_BUFF_SIZE;
    stAttr.stStreamAttr.u32VidBufSize = AVPLAY_VIDEO_BUFF_SIZE;

    ret = HI_UNF_AVPLAY_Create(&stAttr, &AVPlayHandle);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_Create failed.\n");
        return HI_FAILURE;
    }

    // 3. Register Callback Func
    ret |= HI_UNF_AVPLAY_RegisterEvent(AVPlayHandle, HI_UNF_AVPLAY_EVENT_STOP, TsPlayerEventHandler);
    ret |= HI_UNF_AVPLAY_RegisterEvent(AVPlayHandle, HI_UNF_AVPLAY_EVENT_NEW_VID_FRAME, TsPlayerEventHandler);
    ret |= HI_UNF_AVPLAY_RegisterEvent(AVPlayHandle, HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME, TsPlayerEventHandler);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_RegisterEvent failed.\n");
        goto AVPLAY_DESTROY;
    }

    // 4. Set Sync mode
    ret = HI_UNF_AVPLAY_GetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_GetAttr failed.\n");
        goto AVPLAY_DESTROY;
    }

    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;

    //SyncAttr.enSyncRef = HI_UNF_SYNC_REF_NONE;
    ret = HI_UNF_AVPLAY_SetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto AVPLAY_DESTROY;
    }
    if(HI_TRUE == isTvp)
    {
        stAvTVPAttr.bEnable = HI_TRUE;
        ret = HI_UNF_AVPLAY_SetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_TVP, &stAvTVPAttr);
        if (ret != HI_SUCCESS)
        {
            HI_PLAYREADY_ERR("set tvp error\n");
            goto AVPLAY_DESTROY;
        }
    }
    // 6. VO window create
    ret = HIADP_VO_CreatWin(HI_NULL, &hWin);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HIADP_VO_CreatWin failed.\n");
        goto AVPLAY_DESTROY;
    }

    // 8. Start Video Play
    ret = HI_UNF_AVPLAY_ChnOpen(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto VO_DEINIT;
    }

    ret = HI_UNF_VO_AttachWindow(hWin, AVPlayHandle);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_VO_AttachWindow failed.\n");
        goto CHN_CLOSE;
    }

    ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }

    *ohAVHandle = AVPlayHandle;
    *ohWin = hWin;
    return HI_SUCCESS;

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(hWin,HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, AVPlayHandle);

CHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

VO_DEINIT:
    HI_UNF_VO_DestroyWindow(hWin);

AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(AVPlayHandle);

FAILED:
    return HI_FAILURE;
}

static HI_S32 Asf_Close(HI_HANDLE hAVHandle, HI_HANDLE hWin)
{
    HI_UNF_AVPLAY_STOP_OPT_S Stop;

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAVHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD | HI_UNF_AVPLAY_MEDIA_CHAN_VID, &Stop);

    HI_UNF_SND_Detach(HI_UNF_SND_0, hAVHandle);
    HI_UNF_AVPLAY_ChnClose(hAVHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

    HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, hAVHandle);
    HI_UNF_AVPLAY_ChnClose(hAVHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    HI_UNF_VO_DestroyWindow(hWin);

    HI_UNF_AVPLAY_Destroy(hAVHandle);

    return HI_SUCCESS;
}

static HI_S32 Asf_Pause(HI_HANDLE hAVHandle)
{
    HI_S32 ret = HI_SUCCESS;

    HI_PLAYREADY_INFO("Asf_Pause\n");

    ret = HI_UNF_AVPLAY_Pause(hAVHandle, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call Asf_Pause failed.\n");
        return HI_FAILURE;
    }

    return ret;
}

static HI_S32 Asf_Resume(HI_HANDLE hAVHandle)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_VCODEC_ATTR_S struVdecAttr;

    HI_PLAYREADY_INFO("Info: Asf_Resume\n");

    ret = HI_UNF_AVPLAY_GetAttr(hAVHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &struVdecAttr);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_GetAttr failed.\n");
        return HI_FAILURE;
    }

    struVdecAttr.enMode = HI_UNF_VCODEC_MODE_NORMAL;
    ret = HI_UNF_AVPLAY_SetAttr(hAVHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &struVdecAttr);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_SetAttr failed.\n");
        return HI_FAILURE;
    }

    ret = HI_UNF_AVPLAY_Resume(hAVHandle, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call Asf_Resume failed.\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 Ret;
    HI_CHAR InputCmd[32];
    HI_UNF_ENC_FMT_E enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_ASF_OPEN_S stOpenParam;
    HI_HANDLE ASFhandle = 0, hAVPlay = 0, hWin = 0;
    HI_UNF_DISP_BG_COLOR_S BgColor;
    HI_CHAR * pu8tmpStr = NULL;
    HI_U32 u32ASFVideoType = HI_UNF_ASF_STREAM_TYPE_VIDEO_UNKNOW;
    HI_U32 u32ASFAudioType = HI_UNF_ASF_STREAM_TYPE_AUDIO_UNKNOW;

    if (argc < 2)
    {
        HI_PLAYREADY_INFO(" usage1: test_playready_play asffile\n usage2: test_playready_play asffile TVP \n");
        return 0;
    }

    if( argv[2] != NULL && strncmp( argv[2], "tvp", 3) )
    {
        isTvp = HI_TRUE;
        HI_PLAYREADY_ERR("WARNNING WE CHOOOSE TVP VIDIO CHANNEL\n");
    }
    else
    {
        HI_PLAYREADY_ERR("WARNNING WE CHOOOSE NO_TVP VIDIO CHANNEL\n");
    }

    g_pASFFile = fopen(argv[1], "rb");
    if (!g_pASFFile)
    {
        HI_PLAYREADY_ERR("open file %s error!\n", argv[1]);
        return -1;
    }

    HI_PLAYREADY_INFO("Parse input param success!\n");

    HI_SYS_Init();
    Ret = HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_Init failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HIADP_Disp_Init(enFormat);
    if (Ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call DispInit failed.\n");
        goto AVPLAY_DEINIT;
    }

    BgColor.u8Red   = 0;
    BgColor.u8Green = 200;
    BgColor.u8Blue  = 200;
    HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY0, &BgColor);

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    if (Ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HIADP_VO_Init failed.\n");
        goto DISP_DEINIT;
    }

    Ret = HIADP_Snd_Init();
    if (Ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call SndInit failed.\n");
        goto VO_DEINIT;
    }

    Ret = HIADP_AVPlay_RegADecLib();
    if (Ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("call HI_UNF_AVPLAY_RegisterAcodecLib failed.\n");
        goto SND_DEINIT;
    }

    Asf_Open(&hAVPlay, &hWin);
    /* Open ASF handle */
    stOpenParam.hAVPlay = hAVPlay;
    stOpenParam.u32VdecType  = u32ASFVideoType;
    stOpenParam.u32AudioType = u32ASFAudioType;
    stOpenParam.u32ASFBufferSize = 3 * 1024 * 1024; // Allocate 2MBytes
    Ret = HI_ASF_Open(&stOpenParam, &ASFhandle);
    if (Ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("HI_ASF_Open Return Failed!\n");
        goto PLAYREADY_DEINIT;
    }

    HI_PLAYREADY_INFO("ASFhandle:0x%x\n", ASFhandle);

    g_StopThread = HI_FALSE;
    pthread_create(&g_ASFThd, HI_NULL, (HI_VOID *)ASFThread, (HI_VOID *)&ASFhandle);

    while (1)
    {
        HI_PLAYREADY_INFO("please input the q to quit!\n");
        fgets(InputCmd, 30, stdin);

        if ('q' == InputCmd[0])
        {
            HI_PLAYREADY_INFO("prepare to quit!\n");
            break;
        }

        if (('r' == InputCmd[0]) || ('R' == InputCmd[0]))
        {
            Asf_Resume(hAVPlay);
        }

        if (('p' == InputCmd[0]) || ('P' == InputCmd[0]))
        {
            Asf_Pause(hAVPlay);
        }
    }

    HI_PLAYREADY_INFO("come to asf close\n");

    g_StopThread = HI_TRUE;
    pthread_join(g_ASFThd, HI_NULL);
    HI_ASF_Close(ASFhandle);
    Asf_Close(hAVPlay, hWin);

PLAYREADY_DEINIT:

    ASF_Crypto_release();
    ASF_MediaDrm_Release();

SND_DEINIT:
    HIADP_Snd_DeInit();
VO_DEINIT:
    HIADP_VO_DeInit();
DISP_DEINIT:
    HIADP_Disp_DeInit();
AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();
SYS_DEINIT:
    HI_SYS_DeInit();
    fclose(g_pASFFile);
    g_pASFFile = HI_NULL;
    if (g_WMDRMhandle != 0)
    {
        HI_PLAYREADY_Close(g_WMDRMhandle);
    }

    return 0;
}

ModularDrmInterface *g_pDRMhandle = NULL;
CryptoInterface *g_pCryptoHandle = NULL;
Vector<HI_U8> g_keyID;
Vector<HI_U8> g_sessionId;

HI_VOID PRINT_VECTOR(Vector<HI_U8> &data,HI_CHAR *printinfo)
{
    HI_S32 i = 0;

    if(printinfo != NULL)
    {
        HI_PLAYREADY_INFO("********** the %s is: \n",printinfo);
    }

    for(i = 0;i< data.size();i++)
    {
        HI_PLAYREADY_INFO("0x%x ,",data[i]);
        if (i%8 == 7)
        {
            HI_PLAYREADY_INFO("\n");
        }
    }

    HI_PLAYREADY_INFO("\n");
}

HI_VOID PRINT_Array(HI_U8 *data,HI_S32 len,HI_CHAR *printinfo)
{
    HI_S32 i = 0;

    if(printinfo != NULL)
    {
        HI_PLAYREADY_INFO("********** the %s is: \n",printinfo);
    }

    for(i = 0;i< len;i++)
    {
        HI_PLAYREADY_INFO("0x%x ,",data[i]);
        if (i%8 == 7)
        {
            HI_PLAYREADY_INFO("\n");
        }
    }

    HI_PLAYREADY_INFO("\n");
}

HI_S32 ASF_Crypto_Prepare(const HI_U8 uuid[16],Vector<HI_U8> &initData)
{
    HI_S32 ret;
    CryptoInterface *pCryptoHandle;

    HI_PLAYREADY_INFO("[info]%s:enter func \n",__FUNCTION__);

    pCryptoHandle = CryptoInterface::Create(uuid,(HI_VOID*)(initData.editArray()),initData.size());

    if (pCryptoHandle == NULL)
    {
        printf("[error]%s,%d: CryptoInterface Create fail \n",__FUNCTION__,__LINE__);
        return -1;
    }

    g_pCryptoHandle = pCryptoHandle;
    //ret = pCryptoHandle->setMediaDrmSession(g_sessionId);
    //if (ret != HI_SUCCESS)
    //{
    //    printf("[error]%s,%d:setMediaDrmSession fail \n",__FUNCTION__,__LINE__);
    //    return ret;
    //}

    HI_PLAYREADY_INFO("[info]%s:exit func \n",__FUNCTION__);

    return ret;
}

HI_S32 ASF_Crypto_release()
{
    HI_S32 ret;
    CryptoInterface *pCryptoHandle = g_pCryptoHandle;

    HI_PLAYREADY_INFO("[info]%s:enter func \n",__FUNCTION__);

    ret = CryptoInterface::Destroy(pCryptoHandle);

    if (ret != HI_SUCCESS)
    {
        printf("[error]%s,%d:CryptoInterface Destroy fail \n",__FUNCTION__,__LINE__);
        return ret;
    }

    pCryptoHandle = NULL;
    g_pCryptoHandle = NULL;

    HI_PLAYREADY_INFO("[info]%s:exit func \n",__FUNCTION__);

    return ret;
}

HI_S32 get_response_from_server(Vector<HI_U8>& request,String8 &url,Vector<HI_U8>& outResponse)
{
    CURL *curl;
    HI_PLAYREADY_URL stUrl;
    HI_PLAYREADY_CHALLENGE_S Challenge;
    HI_S32 ret;
    HI_PLAYREADY_ASCII_STRING Response;

    memset(&Challenge,0,sizeof(HI_PLAYREADY_CHALLENGE_S));
    Challenge.ChallengeContent.length = request.size();
    Challenge.ChallengeContent.pszString = (HI_U8*)malloc(Challenge.ChallengeContent.length);
    memcpy(Challenge.ChallengeContent.pszString,request.array(), Challenge.ChallengeContent.length);

    Challenge.URL.length = url.size();
    Challenge.URL.pszString = (HI_U8*)malloc(Challenge.URL.length);
    memcpy(Challenge.URL.pszString,url.string(), Challenge.URL.length);

    ret = HttpClientPlayInit(&curl, &Challenge, &stUrl);
    if ( HI_SUCCESS != ret)
    {
        HI_PLAYREADY_ERR("HTTP Client init 1 failed.\n");
        return HI_FAILURE;
    }

    ret = HI_PLAYREADY_HTTP_FetchLicenseEx(curl, &stUrl, &Challenge, &Response, IS_PLAYREADY_ENCRYPT);
    if (ret != HI_SUCCESS)
    {
        HI_PLAYREADY_ERR("HI_PLAYREADY_HTTP_FetchLicenseEx Return:0x%x\n",
                ret);
        HI_PLAYREADY_ERR("~~~~~~~~~~~~HTTP and DRM Server Return Err : %s~~~~~~~~~~~~\n",
            HI_PLAYREADY_HTTP_GetReturnCodeString(ret));
        return ret;
    }

    outResponse.appendArray(Response.pszString,Response.length);

    ret = HttpClientDeInit(curl);
    if ( HI_SUCCESS != ret)
    {
        HI_PLAYREADY_ERR("@@@@@@@@@@@@http client deinit  1 failed!@@@@@@@@@@@@@@\n");
    }
    free(Challenge.ChallengeContent.pszString);
    free(Challenge.URL.pszString);
    HI_PLAYREADY_HTTP_Release_Response(&Response);

}

HI_CHAR xmlFilePath[] = "/usr/data/response.txt";
HI_VOID get_response_from_file(Vector<HI_U8> & response)
{
    FILE* pResponseFile = NULL;

    HI_S32 len;
    HI_U8* pszString = NULL;

    pResponseFile = fopen((char *)xmlFilePath, "rb");

    if (pResponseFile == NULL)
    {
        printf("open file %s fail \n",xmlFilePath);
        return;
    }

    fseek(pResponseFile, 0, SEEK_END);
    len = ftell(pResponseFile);
    HI_INFO_ASF("Response file fd:0x%x, size:0x%x\n", (HI_U32)pResponseFile, len);
    fseek(pResponseFile, 0, SEEK_SET);
    pszString = (HI_U8 *)malloc(sizeof(HI_U8) * (len));
    memset(pszString, 0, len);
    fread(pszString, 1, len, pResponseFile);

    response.appendArray(pszString,len);

    free(pszString);

    fclose(pResponseFile);
}

HI_S32 ASF_MediaDrm_Prepare(const HI_U8 uuid[16],Vector<HI_U8> &initData)
{
    HI_DRM_KEY_REQUEST keyRequest;
    Vector<HI_U8> response;
    KeyedVector<String8, String8> optionalParameters;

    HI_CHAR * mimetype;
    HI_S32 ret;

    ModularDrmInterface *pDRMhandle = NULL;

    HI_PLAYREADY_INFO("[info]%s:enter func \n",__FUNCTION__);

    /*step1: create drm,load drm engine*/
    pDRMhandle = ModularDrmInterface::Create(uuid);

    if (pDRMhandle == NULL)
    {
        printf("[error]%s,%d:create drm fail \n",__FUNCTION__,__LINE__);
    }

    g_pDRMhandle = pDRMhandle;

    /*step2: open session*/
    ret = pDRMhandle->openSession(g_sessionId);

    if (ret != HI_SUCCESS)
    {
        printf("[error]%s,%d:open session fail \n",__FUNCTION__,__LINE__);
        return ret;
    }

    PRINT_VECTOR(g_sessionId,"session id");

    /*step3: request key data from drm engine*/
    ret = pDRMhandle->getKeyRequest(g_sessionId, initData,"video/mp4",
                              HI_DRM_KEY_TYPE_STREAMING, optionalParameters, (HI_DRM_KEY_REQUEST*)&keyRequest);

    //PRINT_VECTOR(keyRequest.requetData,"request data");
    HI_PLAYREADY_INFO("%s:drm key request type(%d) \n",__FUNCTION__,keyRequest.eKeyRequestType);
    HI_PLAYREADY_INFO("%s:drm license url(%s) \n",__FUNCTION__,keyRequest.defaultUrl.string());

    if (ret != HI_SUCCESS)
    {
        printf("[error]%s,%d:getKeyRequest fail \n",__FUNCTION__,__LINE__);
        return ret;
    }

    /*for debug*/
    FILE *pFile;

    /*step4: request key from license server*/
    //if ((pFile=fopen(xmlFilePath,"r")) != NULL)
    //{
    //    fclose(pFile);
    //    pFile = NULL;
    //    get_response_from_file(response);
    //}
    //else
    //{
    //    get_response_from_server(keyRequest.requetData,keyRequest.defaultUrl,response);
    //}
    get_response_from_server(keyRequest.requestData,keyRequest.defaultUrl,response);

    if ((pFile=fopen(xmlFilePath,"r")) == NULL)
    {
        CopyFromBufferToFile(response.editArray(),response.size(),xmlFilePath);
    }
    else
    {
        fclose(pFile);
        pFile = NULL;
    }

    HI_PLAYREADY_INFO("\n %s \n",response.array());

    /*step5: add key to drm engine*/
    ret = pDRMhandle->provideKeyResponse(g_sessionId,response,g_keyID);

    PRINT_VECTOR(g_keyID,"key id");

    if (ret != HI_SUCCESS)
    {
        printf("[error]%s,%d:provideKeyResponse fail \n",__FUNCTION__,__LINE__);
        return ret;
    }

    HI_PLAYREADY_INFO("[info]%s,%d,result(%d):end func",__FUNCTION__,__LINE__,ret);

    ASF_Crypto_Prepare(uuid,g_sessionId);

    return ret;
}

HI_S32 ASF_MediaDrm_Release()
{
     HI_S32 ret;
     ModularDrmInterface *pDRMhandle = g_pDRMhandle;

     HI_PLAYREADY_INFO("[info]%s:enter func \n",__FUNCTION__);

     ret = pDRMhandle->closeSession(g_sessionId);

     if (ret != HI_SUCCESS)
     {
         printf("[error]%s,%d:closeSession fail \n",__FUNCTION__,__LINE__);
         return ret;
     }

     ret = ModularDrmInterface::Destroy(pDRMhandle);

     if (ret != HI_SUCCESS)
     {
         printf("[error]%s,%d:Destroy object fail \n",__FUNCTION__,__LINE__);
     }

     pDRMhandle = NULL;
     g_pDRMhandle = NULL;

     return ret;
}

/*kid capture from file: Bear_Video_OPLs0.pyv*/
HI_U8 kKeyid[16] =
{
    0x37 ,0x18 ,0xeb ,0xb6 ,0xa8 ,0x7b ,0x4f ,0x79 ,
    0xb3 ,0x2c ,0x5 ,0xc2 ,0x26 ,0xe1,0xd0,0xd3
};

HI_VOID convertToNativeKid(const HI_U8 kid[16], HI_U8 nativeKid[16]) {
    // swap 4 bytes
    nativeKid[0] = kid[3];
    nativeKid[1] = kid[2];
    nativeKid[2] = kid[1];
    nativeKid[3] = kid[0];
    // swap 2 bytes
    nativeKid[4] = kid[5];
    nativeKid[5] = kid[4];
    // swap 2 bytes
    nativeKid[6] = kid[7];
    nativeKid[7] = kid[6];
    memcpy(nativeKid + 8, kid + 8, 8);
}

HI_S32 ASF_MediaDrm_Decrypt(HI_U8* iv,HI_S32 ivLen,HI_CHAR* pSrc,HI_S32 s32srcSize,HI_VOID *pDst)
{
    CryptoInterface *pCryptoHandle;
    String8 errorDetailMsg;
    HI_S32 ret = HI_FAILURE;
    HI_U8 key[16];
    HI_U8 setIv[16];

    HI_PLAYREADY_INFO("[info]%s:enter func \n",__FUNCTION__);

    memset(key,0,16);
    if (g_keyID.size() > 0)
    {
        PRINT_VECTOR(g_keyID,"input key id");
        memcpy(key,g_keyID.editArray(),g_keyID.size());
    }
    else
    {
         HI_PLAYREADY_INFO("[info]%s: input key id is null \n",__FUNCTION__);
    }

    HI_PLAYREADY_INFO("[info]%s: check point 1 \n",__FUNCTION__);

    if (iv != NULL)
    {
        PRINT_Array(iv,ivLen,"input iv");
        memset(setIv,0,16);
        memcpy(setIv,iv,ivLen);
    }
    else
    {
         printf("[info]%s: input iv is null \n",__FUNCTION__);
    }
    HI_PLAYREADY_INFO("[info]%s: check point 2 \n",__FUNCTION__);

    HI_DRM_SUBSAMPLES subsamples[1];
    if( HI_TRUE == isTvp )
    {
        subsamples[0].u32numBytesOfClearData = 16;
        subsamples[0].u32numBytesOfEncryptedData = s32srcSize - 16;
    }
    else
    {
        subsamples[0].u32numBytesOfClearData = 0;
        subsamples[0].u32numBytesOfEncryptedData = s32srcSize;
    }

    HI_PLAYREADY_INFO("[info]%s: check point 3 :start decrypt,srcSize(%d)\n",__FUNCTION__,s32srcSize);

    pCryptoHandle = g_pCryptoHandle;

    if (pCryptoHandle == NULL)
    {
        printf("[info]%s:crypto handle is null \n",__FUNCTION__);
        return ret;
    }

    HI_U8 nativeKid[16];
    convertToNativeKid(key,nativeKid);
    PRINT_Array(nativeKid,16,"input key id");

    ret = pCryptoHandle->decrypt(isTvp,
                           nativeKid,
                           iv,
                           HI_CRYPTO_MODE_AES_CTR,
                           pSrc,
                           s32srcSize,
                           subsamples,
                           sizeof(subsamples)/sizeof(subsamples[0]),
                           pDst,
                           errorDetailMsg);

    HI_PLAYREADY_INFO("[info]%s:decrypt bytes:%d\n",__FUNCTION__, ret);

    return ret;
}
/*------------------------------------END---------------------------------------------*/
