#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include "hi_muxer.h"
#include "hi_muxer_intf.h"

#define LOG_TAG "ts_intf"
#include "hi_trans_common.h"

#define PES_HEAD_LEN (20)
#define PES_AUDIO_HEAD_LEN (14)
#define PAT_BUF_LEN (21)
#define PMT_BUF_LEN (31)

#define PES_TO_TS_LEN(PES_LEN) (((PES_LEN) / 176 + 1) * 188)
#define VIDEO_PES_BUFF_LEN (512 * 1024)
#pragma pack(4)

typedef struct stMuxer_Ts_Info_S
{
    HI_U32 u32FirstVideoPTS;
    HI_U32 u32AudioCounter;
    HI_U32 u32VideoCounter;
    HI_BOOL bLostFlag;
    HI_U32 patTsCounter;
    HI_U32 pmtTsCounter;
    HI_U8*  pstPesBuffer;
    HI_U32 u32PesBufLen;
    HI_BOOL bpcrFlag;
    HI_U32 u32TSEncNum;
    HI_U8 pstVPSBuffer[MAX_SPS_PPS_BUF];
    HI_S32 s32VPSLen;
    HI_U8 pstSPSBuffer[MAX_SPS_PPS_BUF];
    HI_S32 s32SPSLen;
    HI_U8 pstPPSBuffer[MAX_SPS_PPS_BUF];
    HI_S32 s32PPSLen;
    Transcoder_MuxerAttr stMuxerAttr;
} Muxer_Ts_Info_S;

static HI_U32  crc32_table[256] =
{
    0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9,
    0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
    0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
    0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
    0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9,
    0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
    0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011,
    0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
    0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
    0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
    0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81,
    0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
    0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49,
    0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
    0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
    0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
    0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae,
    0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
    0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16,
    0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
    0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
    0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
    0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066,
    0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
    0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e,
    0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
    0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
    0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
    0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e,
    0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
    0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686,
    0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
    0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
    0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
    0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f,
    0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
    0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47,
    0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
    0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
    0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
    0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7,
    0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
    0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f,
    0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
    0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
    0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
    0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f,
    0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
    0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640,
    0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
    0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
    0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
    0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30,
    0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
    0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088,
    0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
    0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
    0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
    0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18,
    0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
    0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0,
    0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
    0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
    0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

static HI_VOID SetPtsTimeStamp( HI_U8* buf, HI_U64 time_stemp);
static int VideoPesHeader(HI_U8* buf, HI_S32 PayLoadlen, HI_U32 TimeStamp);

HI_U32 Crc32Calculate(const HI_U8* buffer, HI_U32 size)
{
    HI_U32 crc32_reg = 0xFFFFFFFF;
    HI_U32 cntByte;/*,temp1,temp2,temp3;*/

    for (cntByte = 0; cntByte < size; cntByte++)
    {
        //temp1=(crc32_reg << 8 );
        //temp2=crc32_table[((crc32_reg >> 24) ^ *buffer) & 0xFF];
        //temp3=temp1^temp2;
        crc32_reg = (crc32_reg << 8 ) ^ crc32_table[((crc32_reg >> 24) ^ *buffer++) & 0xFF];
    }
    return crc32_reg;
}


/*给H264/H265 es前封PES packet header*/
static int VideoPesHeader(HI_U8* buf, HI_S32 PayLoadlen, HI_U32 TimeStamp)
{
    HI_S32 pes_packet_Lenghtgth = 0;
    HI_U8 pes_header[PES_HEAD_LEN];//header长度
    HI_U64 Pts = 0;

    memset(pes_header, 0, sizeof(pes_header));
    pes_packet_Lenghtgth = PayLoadlen + 14;
    if (pes_packet_Lenghtgth <= 65535)
    {
        pes_header[4] = (pes_packet_Lenghtgth & 0xff00) >> 8;
        pes_header[5] = pes_packet_Lenghtgth & 0x00ff;
    }
    else
    {
        pes_header[4] = 0x0;
        pes_header[5] = 0x0;
    }
    /*PES包头的相关数据*/
    pes_header[0] = 0;
    pes_header[1] = 0;
    pes_header[2] = 0x01;
    pes_header[3] = 0xE0;
    pes_header[6] = 0x80;
    pes_header[7] = 0x80;
    pes_header[8] = 0x05;

    Pts = (TimeStamp * 90ULL) & (0x00000001ffffffffULL);
    SetPtsTimeStamp(&pes_header[9], Pts);  //设置时间戳 PTS
    pes_header[14] = 0;
    pes_header[15] = 0;
    pes_header[16] = 0;
    pes_header[17] = 0x01;
    pes_header[18] = 0x09;
    pes_header[19] = 0xe0;
    memcpy(buf, pes_header, PES_HEAD_LEN);
    return 0;
}

// 设置Pts时间戳(90khz)
static HI_VOID SetPtsTimeStamp( HI_U8* buf, HI_U64 time_stemp)
{
    buf[0] = ((time_stemp >> 29) | 0x21 ) & 0x3f;
    buf[1] = (HI_U8)(time_stemp >> 22);
    buf[2] = (HI_U8)((time_stemp >> 14) | 0x01);
    buf[3] = (HI_U8)(time_stemp >> 7);
    buf[4] = (HI_U8)((time_stemp << 1) | 0x01);
    return;
}
static void tSSetPCR(HI_U8* pTSBuf, HI_U32 u32TimeStamp)
{
    HI_U64 pcr = 0;
    pcr = (u32TimeStamp * 90ULL) & 0x00000001ffffffffULL;
    pTSBuf[4] = 0x07;
    pTSBuf[5] = 0x10;
    pTSBuf[6]  = ((HI_U8)( pcr >> 25 )) & 0xff;
    pTSBuf[7]  = ((HI_U8)( pcr >> 17 )) & 0xff;
    pTSBuf[8]  = ((HI_U8)( pcr >> 9  )) & 0xff;
    pTSBuf[9]  = ((HI_U8)( pcr >> 1  )) & 0xff;
    pTSBuf[10] = ((HI_U8)( pcr << 7  )) & 0x80;
    pTSBuf[11] = 0x00;
}
static HI_VOID getDefaultPATPMTTsBuffer(Muxer_Ts_Info_S* pstMuxerTs, HI_U8* pTsBuf, int* pTsLen)
{
    /*PAT,PMT表写死*/
    HI_U8 PatTsBuf[PAT_BUF_LEN];
    HI_U8 PmtTsBuf[PMT_BUF_LEN];
    if (TRANSCODER_CODEC_ID_H264 == pstMuxerTs->stMuxerAttr.videoCodec)
    {
        HI_U8 PatTsBuf_H264[PAT_BUF_LEN] = {0x47, 0x40, 0x00, 0x10, 0x00, 0x00, 0xb0, 0x0d, 0x00, 0x01, 0xc1, 0x00, 0x00, 0x00,
                                            0x01, 0xef, 0xff, 0x36, 0x90, 0xe2, 0x3d
                                           };
        HI_U8 PmtTsBuf_H264[PMT_BUF_LEN] = {0x47, 0x4f, 0xff, 0x10, 0x00, 0x02, 0xb0, 0x17, 0x00, 0x01, 0xc1, 0x00, 0x00, 0xe1,
                                            0x00, 0xf0, 0x00, 0x1b, 0xe1, 0x00, 0xf0, 0x00, 0x0f, 0xe1, 0x01, 0xf0, 0x00, 0x2f, 0x44, 0xb9, 0x9b
                                           };
        memcpy(PatTsBuf, PatTsBuf_H264, PAT_BUF_LEN);
        memcpy(PmtTsBuf, PmtTsBuf_H264, PMT_BUF_LEN);
    }
    else if (TRANSCODER_CODEC_ID_H265 == pstMuxerTs->stMuxerAttr.videoCodec)
    {
        HI_U8 PatTsBuf_H265[PAT_BUF_LEN] = {0x47, 0x40, 0x00, 0x10, 0x00, 0x00, 0xb0, 0x0d, 0x00, 0x01, 0xc1, 0x00, 0x00, 0x00,
                                            0x01, 0xf0, 0x00, 0x2a, 0xb1, 0x04, 0xb2
                                           };

        HI_U8 PmtTsBuf_H265[PMT_BUF_LEN] = {0x47, 0x50, 0x00, 0x10, 0x00, 0x02, 0xb0, 0x17, 0x00, 0x01, 0xc1, 0x00, 0x00, 0xe1,
                                            0x00, 0xf0, 0x00, 0x24, 0xe1, 0x00, 0xf0, 0x00, 0x0f, 0xe1, 0x01, 0xf0, 0x00, 0xc7, 0x72, 0xb7, 0xcb
                                           };
        memcpy(PatTsBuf, PatTsBuf_H265, PAT_BUF_LEN);
        memcpy(PmtTsBuf, PmtTsBuf_H265, PMT_BUF_LEN);
    }
    memset(pTsBuf, 0xff, 2 * 188);
    *pTsLen = 188 * 2;
    pstMuxerTs->patTsCounter = (pstMuxerTs->patTsCounter + 1) % 0x10;
    pstMuxerTs->pmtTsCounter = (pstMuxerTs->pmtTsCounter + 1) % 0x10;

    PatTsBuf[3] = (HI_U8)pstMuxerTs->patTsCounter | 0x10;
    PmtTsBuf[3] = (HI_U8)pstMuxerTs->pmtTsCounter | 0x10;
    memcpy(pTsBuf, PatTsBuf, PAT_BUF_LEN);
    memcpy(pTsBuf + 188, PmtTsBuf, PMT_BUF_LEN);
    pstMuxerTs->u32TSEncNum++;
    pstMuxerTs->u32TSEncNum++;
    return;
}


/*PES打包成TS*/
static int VideopesTranTs(Muxer_Ts_Info_S* pstMuxerTsInfo, HI_U8* pPESBuf, HI_S32 pesLen, HI_U8* pTsBuf, HI_S32* pTsLen, const TRANSCODER_STRAM* pstTranFrame,
                          HI_U32 u32VideoPTS)
{
    HI_U8* pPesPoint = NULL;
    HI_U8* pTsPoint = NULL;
    HI_S32   bpesHeadFlag = 0;

    pPesPoint = pPESBuf;
    pTsPoint = pTsBuf;
    pTsPoint[3] = (HI_U8)pstMuxerTsInfo->u32VideoCounter;

    while (pPESBuf + pesLen - pPesPoint >= 184)
    {
        pTsPoint[0] = 0x47;
        pTsPoint[1] = 0x41;
        pTsPoint[2] = 0x00;
        pTsPoint[3] = (HI_U8)pstMuxerTsInfo->u32VideoCounter;
        if (1 != bpesHeadFlag)
        {
            pTsPoint[1] = pTsPoint[1] | 0x40;  //payload_unit_start_indicator置为1
            bpesHeadFlag = 1;
        }
        else
        {
            pTsPoint[1] = pTsPoint[1] & 0xBF;  //payload_unit_start_indicator置为0
        }
        /*根据PCR 定义27 MHZ同90MHZ的对应关系，在包中加入写死的PCR字段*/
        if (0 == pstMuxerTsInfo->u32TSEncNum % 1024)
        {
            pstMuxerTsInfo->bpcrFlag = HI_TRUE;
        }

        if ((PAYLOAD_VIDEO_KEY_FRAME == pstTranFrame->ePayloadType) && pstMuxerTsInfo->bpcrFlag == HI_TRUE)
        {
            pTsPoint[3] = (HI_U8)pstMuxerTsInfo->u32VideoCounter | 0x30;
            tSSetPCR(pTsPoint, u32VideoPTS);
            memcpy(pTsPoint + 12, pPesPoint, 176);
            pPesPoint += 176;
            pTsPoint += 188;
            pstMuxerTsInfo->bpcrFlag = HI_FALSE;
            pstMuxerTsInfo->u32TSEncNum++;
        }
        else
        {
            pTsPoint[3] = pTsPoint[3] & 0xDF;
            pTsPoint[3] = pTsPoint[3] | 0x10;
            memcpy(pTsPoint + 4, pPesPoint, 184);
            pPesPoint += 184;
            pTsPoint += 188;
            pstMuxerTsInfo->u32TSEncNum++;
        }
        pstMuxerTsInfo->u32VideoCounter = (pstMuxerTsInfo->u32VideoCounter + 1) % 0x10;
    }
    if (183 - (pPESBuf + pesLen - pPesPoint) < 0)
    {
        TRANS_LOGOUT("conflict now !!!!!");
        *pTsLen = pTsPoint - pPESBuf;
        return 0;
    }
    else
    {
        //TRANS_LOGOUT("last frame now !!!!!");
        pTsPoint[0] = 0x47;
        pTsPoint[1] = 0x41;
        pTsPoint[2] = 0x00;
        pTsPoint[3] = (HI_U8)pstMuxerTsInfo->u32VideoCounter;
        if (bpesHeadFlag == 0)
        {
            pTsPoint[1] = pTsPoint[1] | 0x40;  //payload_unit_start_indicator置为1
        }
        else
        {
            pTsPoint[1] = pTsPoint[1] & 0xBF;  //payload_unit_start_indicator置为0
        }
        pTsPoint[3] = pTsPoint[3] | 0x30;
        pTsPoint[4] = (HI_U8)(183 - (pPESBuf + pesLen - pPesPoint));
        pTsPoint[5] = 0x0;
        if (pTsPoint[4] != 0)
        {
            memset(&pTsPoint[6], 0xff, pTsPoint[4] - 1);
        }
        memcpy(&pTsPoint[4] + 1 + pTsPoint[4], pPesPoint, (HI_U32)(pPESBuf + pesLen - pPesPoint));
        pTsPoint += 188;
        pstMuxerTsInfo->u32VideoCounter = (pstMuxerTsInfo->u32VideoCounter + 1) % 0x10;
        pstMuxerTsInfo->u32TSEncNum++;
    }
    *pTsLen = pTsPoint - pTsBuf;
    return 0;
}


HI_S32 AudioPesHeader(char* pstPesAudioBuf, int* pesBuflen, const TRANSCODER_AENC_STREAM* pstAACEsBuf, HI_U32 u32TimeStamp)
{
    HI_U32 pes_packet_Lenghtgth = 0;
    unsigned char pes_header[PES_AUDIO_HEAD_LEN];//header长度
    HI_U64 Pts = 0;

    memset(pes_header, 0, sizeof(pes_header));
    pes_packet_Lenghtgth = pstAACEsBuf->u32BufLen + 8;
    if (pes_packet_Lenghtgth <= 65535)
    {
        pes_header[4] = (pes_packet_Lenghtgth & 0xff00) >> 8;
        pes_header[5] = pes_packet_Lenghtgth & 0x00ff;
    }
    else
    {
        pes_header[4] = 0x0;
        pes_header[5] = 0x0;
    }
    /*PES包头的相关数据*/
    pes_header[0] = 0;
    pes_header[1] = 0;
    pes_header[2] = 0x01;
    pes_header[3] = 0xC0;           //音频的数据
    pes_header[6] = 0x80;
    pes_header[7] = 0x80;
    pes_header[8] = 0x05;

    Pts = (u32TimeStamp * 90ULL) & (0x00000001ffffffffULL);
    SetPtsTimeStamp(&pes_header[9], Pts);  //设置时间戳 PTS
    *pesBuflen = PES_AUDIO_HEAD_LEN;
    memcpy(pstPesAudioBuf, pes_header, PES_AUDIO_HEAD_LEN);
    return HI_SUCCESS;
}

HI_S32 AudiopesTranTs(Muxer_Ts_Info_S* pstMuxerTsInfo, HI_U8* pstPesAudioBuf, int pesBuflen, HI_U8* pstTSBuf, int* ps32TsLen)
{
    HI_U8* pPesPoint = NULL;
    HI_U8* pTsPoint = NULL;
    int   bpesHeadFlag = 0;

    pPesPoint = pstPesAudioBuf;
    pTsPoint = pstTSBuf;
    pTsPoint[3] = (HI_U8)pstMuxerTsInfo->u32AudioCounter;

    while (pstPesAudioBuf + pesBuflen - pPesPoint >= 184)
    {
        pTsPoint[0] = 0x47;
        pTsPoint[1] = 0x41;
        pTsPoint[2] = 0x01;
        pTsPoint[3] = (HI_U8)pstMuxerTsInfo->u32AudioCounter;
        if (1 != bpesHeadFlag)
        {
            pTsPoint[1] = pTsPoint[1] | 0x40;  //payload_unit_start_indicator置为1
            bpesHeadFlag = 1;
        }
        else
        {
            pTsPoint[1] = pTsPoint[1] & 0xBF;  //payload_unit_start_indicator置为0
        }
        pTsPoint[3] = pTsPoint[3] & 0xDF;
        pTsPoint[3] = pTsPoint[3] | 0x10;
        memcpy(pTsPoint + 4, pPesPoint, 184);
        pPesPoint += 184;
        pTsPoint += 188;
        pstMuxerTsInfo->u32AudioCounter = (pstMuxerTsInfo->u32AudioCounter + 1) % 0x10;
        pstMuxerTsInfo->u32TSEncNum++;
    }
    if (183 - (pstPesAudioBuf + pesBuflen - pPesPoint) < 0)
    {
        TRANS_LOGOUT("conflict now !!!!!");
        *ps32TsLen = pTsPoint - pstPesAudioBuf;
        return HI_SUCCESS;
    }
    else
    {
        pTsPoint[0] = 0x47;
        pTsPoint[1] = 0x41;
        pTsPoint[2] = 0x01;
        pTsPoint[3] = (HI_U8)pstMuxerTsInfo->u32AudioCounter;
        if (bpesHeadFlag == 0)
        {
            pTsPoint[1] = pTsPoint[1] | 0x40;  //payload_unit_start_indicator置为1
        }
        else
        {
            pTsPoint[1] = pTsPoint[1] & 0xBF;  //payload_unit_start_indicator置为0
        }
        pTsPoint[3] = pTsPoint[3] | 0x30;
        pTsPoint[4] = (HI_U8)(183 - (pstPesAudioBuf + pesBuflen - pPesPoint));
        pTsPoint[5] = 0x0;
        if (pTsPoint[4] != 0)
        {
            memset(&pTsPoint[6], 0xff, pTsPoint[4] - 1);
        }
        memcpy(&pTsPoint[4] + 1 + pTsPoint[4], pPesPoint, (HI_U32)(pstPesAudioBuf + pesBuflen - pPesPoint));
        pTsPoint += 188;
        pstMuxerTsInfo->u32AudioCounter = (pstMuxerTsInfo->u32AudioCounter + 1) % 0x10;
        pstMuxerTsInfo->u32TSEncNum++;
    }
    *ps32TsLen = pTsPoint - pstTSBuf;

    return HI_SUCCESS;
}

HI_S32 TsMuxerCreate(HI_ULONG* hMuxerHandle, Transcoder_MuxerType muxerType, const Transcoder_MuxerAttr* muxerAttr)
{
    Muxer_Ts_Info_S* pstMuxerTsInfo = HI_NULL;

    CHECK_NULL_PTR_RETURN(muxerAttr);

    TRANS_CHK_RETURN_PRINT(TRANSCODER_MUTEX_TS != (Transcoder_MuxerType)muxerType , HI_FAILURE, "muxer type :%d not support in TS!!\n", muxerType);
    TRANS_CHK_RETURN_PRINT((TRANSCODER_CODEC_ID_H264 != muxerAttr->videoCodec) && (TRANSCODER_CODEC_ID_H265 != muxerAttr->videoCodec), HI_FAILURE, " video codec :%d not support in TS\n", muxerAttr->videoCodec);
    TRANS_CHK_RETURN_PRINT((TRANSCODER_CODEC_ID_AACLC != muxerAttr->audioCodec), HI_FAILURE, "audio codec :%d not support in TS\n", muxerAttr->audioCodec);


    pstMuxerTsInfo = (Muxer_Ts_Info_S*)malloc(sizeof(Muxer_Ts_Info_S));
    TRANS_CHK_RETURN_PRINT(HI_NULL == pstMuxerTsInfo, HI_FAILURE, "muxer ts Info alloc error!!!\n");

    memset(pstMuxerTsInfo, 0, sizeof(Muxer_Ts_Info_S));

    pstMuxerTsInfo->u32PesBufLen = VIDEO_PES_BUFF_LEN;
    pstMuxerTsInfo->pstPesBuffer = (HI_U8*)malloc(pstMuxerTsInfo->u32PesBufLen);
    if (HI_NULL == pstMuxerTsInfo->pstPesBuffer)
    {
        TRANS_LOGOUT("muxer ts pesBuffer alloc error!!!\n");
        POINTER_FREE(pstMuxerTsInfo);
        return HI_FAILURE;
    }

    memcpy(&pstMuxerTsInfo->stMuxerAttr, muxerAttr, sizeof(Transcoder_MuxerAttr));
    *hMuxerHandle = (HI_ULONG)pstMuxerTsInfo;
    return HI_SUCCESS;
}

HI_S32 TsMuxerDestroy(HI_ULONG phHandle)
{
    Muxer_Ts_Info_S* pstMuxerTsInfo = HI_NULL;

    CHECK_NULL_PTR_RETURN(phHandle);

    pstMuxerTsInfo = (Muxer_Ts_Info_S*)phHandle;
    POINTER_FREE(pstMuxerTsInfo->pstPesBuffer);
    POINTER_FREE(pstMuxerTsInfo);
    return HI_SUCCESS;
}

HI_S32 TsMuxerGetHeader(HI_ULONG hMuxerHandle, const HI_CHAR* pTAGFrame, HI_S32* ps32Len)
{

    CHECK_NULL_PTR_RETURN(hMuxerHandle);
    CHECK_NULL_PTR_RETURN(ps32Len);

    *ps32Len = 0;
    return HI_SUCCESS;
}

HI_S32 TSMuxerAudioStream(Muxer_Ts_Info_S* pstMuxerTsInfo, HI_CHAR* pTAGFrame, HI_S32* ps32Len, const TRANSCODER_AENC_STREAM* pstAencStream)
{

    CHECK_NULL_PTR_RETURN(ps32Len);

    HI_U32 AddrBufLen = (HI_U32) * ps32Len;
    HI_CHAR stTmpAudioBuf[4096] = {0};
    HI_S32 pesBuflen;
    HI_U32 u32AudioPTS;

    TRANS_CHK_RETURN_PRINT(((pstAencStream->u32BufLen + 1024) > AddrBufLen), HI_FAILURE, "parameter buffer too small\n");

    if (0 == pstMuxerTsInfo->u32FirstVideoPTS)
    {
        *ps32Len = 0;
        return HI_SUCCESS;
    }

    u32AudioPTS = pstAencStream->u32PtsMs - pstMuxerTsInfo->u32FirstVideoPTS;

    AudioPesHeader(stTmpAudioBuf, &pesBuflen, pstAencStream, u32AudioPTS); //no failure return
    memcpy(stTmpAudioBuf + pesBuflen, pstAencStream->pu8Buf, pstAencStream->u32BufLen);
    pesBuflen += (HI_S32)pstAencStream->u32BufLen;
    AudiopesTranTs(pstMuxerTsInfo, (HI_U8*)stTmpAudioBuf, pesBuflen, (HI_U8*)pTAGFrame, ps32Len); //no failure return

    return HI_SUCCESS;
}

HI_S32 TSMuxerVideoStream(Muxer_Ts_Info_S* pstMuxerTsInfo, HI_CHAR* pTAGFrame, HI_S32* ps32Len, const TRANSCODER_STRAM* pstTranFrame)
{

    HI_S32 s32muxTsLen = 0, s32pesheadlen = 0, s32TsBuflen;
    HI_U32 u32VideoPTS = 0;
    CHECK_NULL_PTR_RETURN(pstMuxerTsInfo);
    CHECK_NULL_PTR_RETURN(ps32Len);
    CHECK_NULL_PTR_RETURN(pstTranFrame);

    TRANSCODER_VENC_STREAM* pstVencStream = (TRANSCODER_VENC_STREAM*)&pstTranFrame->enDataStream.stVencStream;
    CHECK_NULL_PTR_RETURN(pstVencStream);

    if (pstMuxerTsInfo->u32FirstVideoPTS == 0)
    {
        if (PAYLOAD_VIDEO_NORMAL_FRAME == pstTranFrame->ePayloadType)
        {
            *ps32Len = 0;
            return HI_SUCCESS;
        }
        else
        {
            pstMuxerTsInfo->u32FirstVideoPTS = pstVencStream->u32PtsMs;
        }
    }

    if (HI_TRUE == pstMuxerTsInfo->bLostFlag)
    {
        if (PAYLOAD_VIDEO_NORMAL_FRAME == pstTranFrame->ePayloadType)
        {
            *ps32Len = 0;
            return HI_SUCCESS;
        }
        if (PAYLOAD_VIDEO_KEY_FRAME == pstTranFrame->ePayloadType)
        {
            pstMuxerTsInfo->bLostFlag = HI_FALSE;
        }
    }
    else if (pstVencStream->u32SlcLen + PES_HEAD_LEN > pstMuxerTsInfo->u32PesBufLen)
    {
        TRANS_LOGOUT("venc stream too big len : %d!!!\n", pstVencStream->u32SlcLen);
        *ps32Len = 0;
        pstMuxerTsInfo->bLostFlag = HI_TRUE;
        return HI_SUCCESS;
    }

    if (PAYLOAD_VIDEO_VPS_FRAME == pstTranFrame->ePayloadType)
    {
        memcpy(pstMuxerTsInfo->pstVPSBuffer, pstVencStream->pu8Addr, pstVencStream->u32SlcLen);
        pstMuxerTsInfo->s32VPSLen = (HI_S32)pstVencStream->u32SlcLen;
        *ps32Len = 0;
        return HI_SUCCESS;
    }
    if (PAYLOAD_VIDEO_PPS_FRAME == pstTranFrame->ePayloadType)
    {
        memcpy(pstMuxerTsInfo->pstPPSBuffer, pstVencStream->pu8Addr, pstVencStream->u32SlcLen);
        pstMuxerTsInfo->s32PPSLen = (HI_S32)pstVencStream->u32SlcLen;
        *ps32Len = 0;
        return HI_SUCCESS;
    }

    if (PAYLOAD_VIDEO_SPS_FRAME == pstTranFrame->ePayloadType)
    {
        memcpy(pstMuxerTsInfo->pstSPSBuffer, pstVencStream->pu8Addr, pstVencStream->u32SlcLen);
        pstMuxerTsInfo->s32SPSLen = (HI_S32)pstVencStream->u32SlcLen;

        CHECK_NULL_PTR_RETURN(pTAGFrame);
        getDefaultPATPMTTsBuffer(pstMuxerTsInfo, (HI_U8*)pTAGFrame, &s32muxTsLen);
        *ps32Len = s32muxTsLen;
        return HI_SUCCESS;
    }

    u32VideoPTS = pstVencStream->u32PtsMs - pstMuxerTsInfo->u32FirstVideoPTS;
    if (0 == u32VideoPTS)
    { u32VideoPTS = 20; }
    if (PAYLOAD_VIDEO_KEY_FRAME == pstTranFrame->ePayloadType)
    {
        HI_U8* pBuf = pstMuxerTsInfo->pstPesBuffer;
        pBuf += PES_HEAD_LEN;
        if (pstMuxerTsInfo->s32VPSLen > 0)
        {
            memcpy(pBuf, pstMuxerTsInfo->pstVPSBuffer, (HI_U32)pstMuxerTsInfo->s32VPSLen);
            s32pesheadlen += pstMuxerTsInfo->s32VPSLen;
            pBuf += pstMuxerTsInfo->s32VPSLen;
        }
        if (pstMuxerTsInfo->s32SPSLen > 0)
        {
            memcpy(pBuf, pstMuxerTsInfo->pstSPSBuffer, (HI_U32)pstMuxerTsInfo->s32SPSLen);
            s32pesheadlen += pstMuxerTsInfo->s32SPSLen;
            pBuf += pstMuxerTsInfo->s32SPSLen;
        }
        if (pstMuxerTsInfo->s32PPSLen > 0)
        {
            memcpy(pBuf, pstMuxerTsInfo->pstPPSBuffer, (HI_U32)pstMuxerTsInfo->s32PPSLen);
            s32pesheadlen += pstMuxerTsInfo->s32PPSLen;
            pBuf += pstMuxerTsInfo->s32PPSLen;
        }
        memcpy(pBuf, pstVencStream->pu8Addr, pstVencStream->u32SlcLen);
        s32pesheadlen += (HI_S32)pstVencStream->u32SlcLen;
        s32pesheadlen += PES_HEAD_LEN;
    }
    else
    {
        memcpy(pstMuxerTsInfo->pstPesBuffer + PES_HEAD_LEN, pstVencStream->pu8Addr, pstVencStream->u32SlcLen);
        s32pesheadlen = PES_HEAD_LEN + (HI_S32)pstVencStream->u32SlcLen;
    }

    VideoPesHeader((HI_U8*)pstMuxerTsInfo->pstPesBuffer, (HI_S32)(s32pesheadlen - PES_HEAD_LEN), u32VideoPTS); //no failure return
    if (PES_TO_TS_LEN(s32pesheadlen) > *ps32Len)
    {
        TRANS_LOGOUT("venc stream too big len : %d %d!!!\n", pstVencStream->u32SlcLen, *ps32Len);
        *ps32Len = 0;
        pstMuxerTsInfo->bLostFlag = HI_TRUE;
        return HI_SUCCESS;
    }

    CHECK_NULL_PTR_RETURN(pTAGFrame);
    VideopesTranTs(pstMuxerTsInfo, pstMuxerTsInfo->pstPesBuffer, s32pesheadlen, (HI_U8*)pTAGFrame + s32muxTsLen, &s32TsBuflen, pstTranFrame, u32VideoPTS); //no failure return

    if (s32TsBuflen % 188 != 0)
    {
        TRANS_LOGOUT("ts load error1!!\n");
        *ps32Len = 0;
        return HI_FAILURE;
    }
    *ps32Len = s32muxTsLen + s32TsBuflen;
    return HI_SUCCESS;
}

HI_S32 TsMuxerDomuxer(HI_ULONG hMuxerHandle, HI_CHAR* pTAGFrame, HI_S32* ps32Len, const TRANSCODER_STRAM* pstTranFrame)
{
    Muxer_Ts_Info_S* pstMuxerTsInfo = HI_NULL;

    CHECK_NULL_PTR_RETURN(hMuxerHandle);
    CHECK_NULL_PTR_RETURN(ps32Len);
    TRANS_CHK_RETURN_PRINT((PAYLOAD_AUDIO_FRAME < pstTranFrame->ePayloadType || PAYLOAD_VIDEO_NORMAL_FRAME > pstTranFrame->ePayloadType), HI_FAILURE, "PayLoadType : %d not support\n", pstTranFrame->ePayloadType);

    pstMuxerTsInfo = (Muxer_Ts_Info_S*)hMuxerHandle;

    if (PAYLOAD_AUDIO_FRAME == pstTranFrame->ePayloadType)
    {
        return TSMuxerAudioStream(pstMuxerTsInfo, pTAGFrame, ps32Len, &pstTranFrame->enDataStream.stAencStream);
    }
    else
    {
        return TSMuxerVideoStream(pstMuxerTsInfo, pTAGFrame, ps32Len, pstTranFrame);
    }
}

HI_S32 TsMuxerSetPrivate(HI_ULONG hMuxerHandle, const HI_VOID* stAttr, HI_S32 s32Len)
{
    TRANS_LOGOUT("Ts Muxer not support SetPrivate function!!\n");
    return HI_SUCCESS;
}

HI_MuxerInfo_S st_Muxer_TS =
{
    .szName = (const HI_PCHAR)"TS",
    .enMuxerType = TRANSCODER_MUTEX_TS,
    .pszDescription = (const HI_PCHAR)TS_DEFAULT_MUXER,
    .pDllModule = HI_NULL,
    .MuxerCreate = TsMuxerCreate,
    .MuxerDestroy = TsMuxerDestroy,
    .MuxerGetHeader = TsMuxerGetHeader,
    .DoMuxer = TsMuxerDomuxer,
    .setPrivate = TsMuxerSetPrivate,
    .next = HI_NULL
};
