/*******************************************************************************
*                       Include files
*******************************************************************************/

#include <string.h>
#include <stdio.h>

#include "hi_debug.h"
#include "caption_cc_xds.h"

#define HI_FATAL_CC(fmt...)      HI_FATAL_PRINT(HI_ID_CC, fmt)
#define HI_ERR_CC(fmt...)        HI_ERR_PRINT(HI_ID_CC, fmt)
#define HI_WARN_CC(fmt...)       HI_WARN_PRINT(HI_ID_CC, fmt)
#define HI_INFO_CC(fmt...)       HI_INFO_PRINT(HI_ID_CC, fmt)
#define XDS_TRACE(fmt,args...)   printf(fmt,##args)

/*****************************************************************************
*                    Macro Definitions
*****************************************************************************/

#define MAX_PROGRAM_NAME_BYTE       33
#define MAX_CAPTION_SERVICES_LEN    8
#define MAX_COMPOSITE_PACKET_LEN    32
#define MAX_PROGRAM_NUM             8
#define MAX_PROGRAM_DESCRIPTION_LEN 32
#define MAX_CALLLETTER_LEN          6
#define MAX_TSID_LEN                4
#define MAX_SUPPLEMT_DATA_LEN       32
#define MAX_CHANNELMAP_HEADER_LEN   4
#define MAX_CHANNELMAP_PACKET_LEN   10
#define MAX_NWS_CODE_LEN            11
#define MAX_NWS_DATA_LEN            32

#define MIN_CC608_PROGNAME_LEN          2
#define MAX_CC608_PROGNAME_LEN          32
#define MIN_CC608_PROGTYPE_LEN          2
#define MAX_CC608_PROGTYPE_LEN          32
#define MIN_CC608_CAPTSERV_LEN          2
#define MAX_CC608_CAPTSERV_LEN          8
#define MAX_CC608_PROG_NUM              8
#define MAX_CC608_PROGDESC_LEN          32
#define MIN_CC608_NETNAME_LEN           2
#define MAX_CC608_NETNAME_LEN           32
#define MIN_CC608_CALLLET_LEN           4
#define MAX_CC608_CALLLET_LEN           6
#define MIN_CC608_SUPPDATA_LEN          2
#define MAX_CC608_SUPPDATA_LEN          32
#define MAX_CC608_CHID_LEN              6
#define MAX_CC608_NWSCODE_LEN           32
#define MAX_CC608_NWSMSG_LEN            32

/*****************************************************************************
*                       Type Definitions
*****************************************************************************/

/**Class Definitions in XDS Packet*//** CNcomment:XDS�ķ��� */
typedef enum tagXDS_CLASS_E
{
    XDS_CLASS_CUR,       /**<Current class*//**<CNcomment:Current�� */
    XDS_CLASS_FUT,       /**<Future class*//**<CNcomment:Future�� */
    XDS_CLASS_CHAN,      /**<Channel Information class*//**<CNcomment:Channel�� */
    XDS_CLASS_MISC,      /**<Miscellaneous class*//**<CNcomment:Miscellaneous�� */
    XDS_CLASS_PUB,       /**<Public Service class*//**<CNcomment:Public Service�� */
    XDS_CLASS_RESV,      /**<Reserved class*//**<CNcomment:Ԥ�� */
    XDS_CLASS_PRIV,      /**<Private Data class*//**<CNcomment:Private Data�� */
    XDS_CLASS_BUTT
} XDS_CLASS_E;

/**Type of current Class*//** CNcomment:Current������ */
typedef enum tagXDS_CUR_TYPE_E
{
    XDS_CUR_PRG_ID        =   0x1,  /**<Program Identification Number*//**<CNcomment:��Ŀ�Ŀ�ʼʱ������� */
    XDS_CUR_TIMEINSHOW    =   0x2,  /**<Length/Time-in-Show*//**<CNcomment:��Ŀ����ʱ�� */
    XDS_CUR_PRG_NAME      =   0x3,  /**<Program Name*//**<CNcomment:��Ŀ���� */
    XDS_CUR_PRG_TYPE      =   0x4,  /**<Program Type*//**<CNcomment:��Ŀ���� */
    XDS_CUR_CONT_ADVSR    =   0x5,  /**<Content Advisory*//**<CNcomment:��Ŀ���ݵ����Ƽ��� */
    XDS_CUR_AUD_SERVC     =   0x6,  /**<Audio Services*//**<CNcomment:��Ƶ��Ŀ�����ݷ��� */
    XDS_CUR_CAP_SERVC     =   0x7,  /**<Caption Services*//**<CNcomment:��Ļ���� */
    XDS_CUR_CPY_REDIST    =   0x8,  /**<Copy and Redistribution Control Packet*//**<CNcomment:���ݿ����ͷ������� */
    XDS_CUR_COMP_1        =   0xC,  /**<Composite Packet-1*//**<CNcomment:�ۺ����ݰ� */
    XDS_CUR_COMP_2        =   0xD,  /**<Composite Packet-2*//**<CNcomment:�ۺ����ݰ� */
    XDS_CUR_PRG_DESC1     =   0x10, /**<Program Description Row 1*//**<CNcomment:��Ŀ���������� */
    XDS_CUR_PRG_DESC2     =   0x11, /**<Program Description Row 2*//**<CNcomment:��Ŀ���������� */
    XDS_CUR_PRG_DESC3     =   0x12, /**<Program Description Row 3*//**<CNcomment:��Ŀ���������� */
    XDS_CUR_PRG_DESC4     =   0x13, /**<Program Description Row 4*//**<CNcomment:��Ŀ���������� */
    XDS_CUR_PRG_DESC5     =   0x14, /**<Program Description Row 5*//**<CNcomment:��Ŀ���������� */
    XDS_CUR_PRG_DESC6     =   0x15, /**<Program Description Row 6*//**<CNcomment:��Ŀ���������� */
    XDS_CUR_PRG_DESC7     =   0x16, /**<Program Description Row 7*//**<CNcomment:��Ŀ���������� */
    XDS_CUR_PRG_DESC8     =   0x17, /**<Program Description Row 8*//**<CNcomment:��Ŀ���������� */
    XDS_CUR_TYPE_BUTT
} XDS_CUR_TYPE_E;

/**Type of Channel Information Class*//** CNcomment:Ƶ����Ϣ������ */
typedef enum tagXDS_CHAN_TYPE
{
    XDS_CHAN_NET_NAME      =   0x1,  /**<Network Name*//**<CNcomment:�������� */
    XDS_CHAN_CALL_LETTER   =   0x2,  /**<Call Letters (Station ID) and Native Channel*//**<CNcomment:Station ID����Native Channel */
    XDS_CHAN_TAPE_DELAY    =   0x3,  /**<Tape Delay*//**<CNcomment:Tape�ӳ� */
    XDS_CHAN_TRNS_SIGNID   =   0x4,  /**<Transmission Signal Identifier (TSID)*//**<CNcomment:�����źű�ʶ */
    XDS_CHAN_TYPE_BUTT
} XDS_CHAN_TYPE;

/**Type of Miscellaneous Class*//** CNcomment:Miscellaneous������ */
typedef enum tagXDS_MISC_TYPE
{
    XDS_MISC_TIMEOFDAY     =   0x1,  /**<Time of Day*//**<CNcomment:��ǰʱ�� */
    XDS_MISC_IMPL_CAPTID   =   0x2,  /**<Impulse Capture ID*//**<CNcomment:¼��ID */
    XDS_MISC_SUPL_DATALOC  =   0x3,  /**<Supplemental Data Location*//**<CNcomment:�������ݵ�λ�� */
    XDS_MISC_TIME_ZONE     =   0x4,  /**<Local Time Zone & DST Use*//**<CNcomment:��������ʱ��ʱ�� */
    XDS_MISC_OUTOFBAND     =   0x40, /**<Out-of-Band Channel Number*//**<CNcomment:����Ƶ����Ƶ���� */
    XDS_MISC_CHMAP_POINTER =   0x41, /**<Channel Map Pointer*//**<CNcomment:Ƶ��ӳ�����Ƶ������ */
    XDS_MISC_CHMAP_HEADER  =   0x42, /**<Channel Map Header Packet*//**<CNcomment:Ƶ��ӳ���ͷ */
    XDS_MISC_CHMAP_PAKT    =   0x43, /**<Channel Map Packet*//**<CNcomment:Ƶ��ӳ��� */
    XDS_MISC_TYPE_BUTT
} XDS_MISC_TYPE;

/**Type of Public Service Class*//** CNcomment:�������������� */
typedef enum hiUNF_CC_XDS_PUB_TYPE
{
    HI_UNF_CC_XDS_PUB_NWS_CODE      =   0x1,  /*National Weather Service Code (WRSAME)*//**<CNcomment:����������Ϣ�� */
    HI_UNF_CC_XDS_PUB_NWS_MSG       =   0x2,  /*National Weather Service Message*//**<CNcomment:����������Ϣ��Ϣ */
    HI_UNF_CC_XDS_PUB_TYPE_BUTT
} HI_UNF_CC_XDS_PUB_TYPE;

typedef struct _tagXDS_ProgramIDNum_S
{
    HI_U8 u8Minute;
    HI_U8 u8Hour;
    HI_U8 u8Data;
    HI_U8 u8Month;
} XDS_ProgramIDNum_S;

typedef struct _tagXDS_LenTimeInShow_S
{
    HI_U8 u8LengthMin;
    HI_U8 u8LengthHour;
    HI_U8 u8ElapsedMin;
    HI_U8 u8ElapsedHour;
    HI_U8 u8ElapsedSec;
} XDS_LenTimeInShow_S;

typedef struct _tagXDSProgName_S
{
    HI_U8 au8ProgName[MAX_CC608_PROGNAME_LEN];
    HI_U8 u8ProgNameLen;
} XDSProgName_S;

typedef struct _tagXDSProgType_S
{
    HI_U8 au8ProgType[MAX_CC608_PROGTYPE_LEN];
    HI_U8 u8ProgTypeLen;
} XDSProgType_S;

typedef struct _tagXDSContAdv_S
{
    HI_U8 u8Char1;
    HI_U8 u8Char2;
} XDSContAdv_S;

typedef struct _tagXDSAudioService_S
{
    HI_U8 u8Main;
    HI_U8 u8SAP;
} XDSAudioService_S;

typedef struct _tagXDSCaptService_S
{
    HI_U8 au8CaptServices[MAX_CC608_CAPTSERV_LEN];
    HI_U8 u8CaptServicesLen;
} XDSCaptService_S;

typedef struct _tagXDSCopyAndRedist_S
{
    HI_U8 u8Byte1;
    HI_U8 u8Byte2;
} XDSCopyAndRedist_S;

typedef struct _tagXDSCompPacket1_S
{
    HI_U8 au8ProgramType[5];
    HI_U8 u8ContAdv;
    HI_U8 u8LengthMin;
    HI_U8 u8LengthHour;
    HI_U8 u8ElapsedMin;
    HI_U8 u8ElapsedHour;
    HI_U8 au8Title[22];
    HI_U8 u8TitleLen;
} XDSCompPacket1_S;

typedef struct _tagXDSCompPacket2_S
{
    XDS_ProgramIDNum_S stPRGStartTime;
    XDSAudioService_S stAudioServices;
    HI_U8 au8CaptServices[2];
    HI_U8 au8CallLetter[4];
    HI_U8 au8NativeChan[2];
    HI_U8 au8NetworkName[18];
    HI_U8 au8NetworkNameLen;
} XDSCompPacket2_S;

typedef struct _tagXDSProgDesc_S
{
    HI_U8 au8ProgDesc[MAX_CC608_PROGDESC_LEN];
    HI_U8 u8ProgDescLen;
} XDSProgDesc_S;

typedef struct _tagXDSNetworkName_S
{
    HI_U8 au8NetName[MAX_CC608_NETNAME_LEN];
    HI_U8 u8NetNameLen;
} XDSNetworkName_S;

typedef struct _tagXDSCallLetNatvCh_S
{
    HI_U8 au8CallLetter[4];
    HI_U8 au8NativeChan[2];
    HI_U8 u8NativeChanLen;
} XDSCallLetNatvCh_S;

typedef struct _tagXDSTapeDelay_S
{
    HI_U8 u8Minute;
    HI_U8 u8Hour;
} XDSTapeDelay_S;

typedef struct _tagXDSTranSignID_S
{
    HI_U8 u8TSID3to0;
    HI_U8 u8TSID7to4;
    HI_U8 u8TSID11to8;
    HI_U8 u8TSID15to12;
} XDSTranSignID_S;

typedef struct _tagXDSTimeOfDay_S
{
    HI_U8 u8Minute;
    HI_U8 u8Hour;
    HI_U8 u8Date;
    HI_U8 u8Month;
    HI_U8 u8Day;
    HI_U8 u8Year;
} XDSTimeOfDay_S;

typedef struct _tagXDSImpCaptID_S
{
    HI_U8 u8Minute;
    HI_U8 u8Hour;
    HI_U8 u8Date;
    HI_U8 u8Month;
    HI_U8 u8LengthMin;
    HI_U8 u8LengthHour;
} XDSImpCaptID_S;

typedef struct  _tagXDSSupplDataLoc_S
{
    HI_U8 au8SupplDataLoc[MAX_CC608_SUPPDATA_LEN];
    HI_U8 u8SupplDataLocLen;
} XDSSupplDataLoc_S;

typedef struct _tagXDSLocTimeZone_S
{
    HI_U8 u8LocTimeZoneHour;
} XDSLocTimeZone_S;

typedef struct _tagXDSOutOfBand_S
{
    HI_U8 u8ChanLow;
    HI_U8 u8ChanHigh;
} XDSOutOfBand_S;

typedef struct _tagXDSChMapPointer_S
{
    HI_U8 u8TuneChanLow;
    HI_U8 u8TuneChanHigh;
} XDSChMapPointer_S;

typedef struct _tagXDSChMapHeader_S
{
    HI_U8 u8ChanLow;
    HI_U8 u8ChanHigh;
    HI_U8 u8Version;
} XDSChMapHeader_S;

typedef struct _tagXDSChMapPacket_S
{
    HI_U8 u8UserChanLow;
    HI_U8 u8UserChanHigh;
    HI_U8 u8TuneChanLow;
    HI_U8 u8TuneChanHigh;
    HI_U8 au8ChID[MAX_CC608_CHID_LEN];
    HI_U8 u8ChIDLen;
} XDSChMapPacket_S;

typedef struct _tagXDSNatWeaServcCode_S
{
    HI_U8 au8NatWeaServcCode[MAX_CC608_NWSCODE_LEN];
    HI_U8 u8NatWeaServcCodeLen;
} XDSNatWeaServcCode_S;

typedef struct _tagXDSNatWeaServcMsg_S
{
    HI_U8 u8NatWeaServcMsg[MAX_CC608_NWSMSG_LEN];
    HI_U8 u8NatWeaServcMsgLen;
} XDSNatWeaServcMsg_S;

typedef HI_S32 (*XDSPacketDecoder_FN)(HI_U8* pu8PacketData, HI_U8 u8PacketLen);

static XDSPacketDecoder_FN  pfnXDSPacketDecoder[XDS_CLASS_BUTT][XDS_MISC_TYPE_BUTT];

static XDS_ProgramIDNum_S stProgramIDNum;
static XDS_LenTimeInShow_S stLenTimeInShow;
static XDSProgName_S stProgName;
static XDSProgType_S stProgType;
static XDSContAdv_S stContAdv;
static XDSAudioService_S stAudioService;
static XDSCaptService_S stCaptService;
static XDSCopyAndRedist_S stCopyAndRedist;
static XDSCompPacket1_S stCompPacket1;
static XDSCompPacket2_S stCompPacket2;
static XDSProgDesc_S stXDSProgDesc;
static XDSNetworkName_S  stNetworkName;
static XDSCallLetNatvCh_S stCallLetNatvCh;
static XDSTapeDelay_S stTapeDelay;
static XDSTranSignID_S stTransSignID;
static XDSTimeOfDay_S stTimeOfDay;
static XDSImpCaptID_S stImpCaptID;
static XDSSupplDataLoc_S stSupplDataLoc;
static XDSLocTimeZone_S stLocTimeZone;
static XDSOutOfBand_S stOutOfBand;
static XDSChMapPointer_S stChMapPointer;
static XDSChMapHeader_S stChMapHeader;
static XDSChMapPacket_S stChMapPacket;
static XDSNatWeaServcCode_S stNatWeaServcCode;
static XDSNatWeaServcMsg_S stNatWeaServcMsg;

/*******************************************************************************
*                       Static Function Definition
*******************************************************************************/

static HI_S32 _CC608_XDS_DecodeProgIDNum(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;
    HI_U8 Minute, Hour, Date, Month;

    if ( len != 4 )
    {
        HI_ERR_CC("Invalide length:%d for Data/Time Packet!\n", len);
        return HI_FAILURE;
    }

    Minute = (buf[0] & 0x3F);
    Hour = (buf[1] & 0x1F);
    Date = (buf[2] & 0x1F);
    Month = (buf[3] & 0x0F);

    if ( ( Minute > 59 ) || ( Hour > 23 ) || ( Date > 31 ) || ( Month > 12 ))
    {
        HI_ERR_CC("Invalide Time/Date Value:Minute=%d,Hour=%d,Date=%d,Month=%d\n", Minute, Hour, Date, Month);
        return HI_FAILURE;
    }

    stProgramIDNum.u8Minute =   buf[0];
    stProgramIDNum.u8Hour   =   buf[1];
    stProgramIDNum.u8Data   =   buf[2];
    stProgramIDNum.u8Month  =   buf[3];

    XDS_TRACE("Program Start Time: %.2d-%.2d %.2d:%.2d\n", Month, Date, Hour, Minute);
    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeLenAndTimeInShow(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;
    HI_U8 length[6];
    HI_U8 i;

    if ( len >  6 )
    {
        HI_ERR_CC("Invalide length:%d for length/Elapse Packet!\n", len);
        return HI_FAILURE;
    }

    memset(length, 0, 6);

    for ( i = 0; i < len; i++)
    {
        length[i] = (buf[i] & 0x3F);
    }

    if ( (length[0] > 59) || (length[2] > 59) || (length[4] > 59) )
    {
        HI_ERR_CC("Invalide Show length value:len(min)=%d,ET(min)=%d,ET(s)=%d\n", length[0], length[2], length[4]);
        return HI_FAILURE;
    }

    stLenTimeInShow.u8LengthMin     =   buf[0];
    stLenTimeInShow.u8LengthHour    =   buf[1];
    stLenTimeInShow.u8ElapsedMin    =   buf[2];
    stLenTimeInShow.u8ElapsedHour   =   buf[3];
    stLenTimeInShow.u8ElapsedSec    =   buf[4];

    XDS_TRACE("Program Length:%d:%d, Elapsed Time:%d:%d:%d\n", length[1], length[0], length[3], length[2], length[4]);

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeProgName(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;
    HI_U8 i;

    if ((len < MIN_CC608_PROGNAME_LEN) || (len > MAX_CC608_PROGNAME_LEN))
    {
        HI_ERR_CC("XDS program title overflow!\n");
        return HI_FAILURE;
    }

    for ( i = 0; i < len; i++)
    {
        if ( ((buf[i] < 0x20) && (buf[i] != 0)) || (buf[i] > 0x7f) )
        {
            HI_ERR_CC("Invalide Value for Program Title buf[%d]=%x\n", i, buf[i]);
            return HI_FAILURE;
        }
    }

    stProgName.u8ProgNameLen    =   len;
    memcpy(stProgName.au8ProgName, buf, len);

    XDS_TRACE("Program name:\n");

    for (i = 0; i < len; i++)
    {
        XDS_TRACE("%c ", stProgName.au8ProgName[i]);
    }

    XDS_TRACE("\n");

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeProgType(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;
    HI_U8 i;

    if ( len > MAX_CC608_PROGTYPE_LEN )
    {
        HI_ERR_CC("Invalide length:%d for program type packet\n", len);
        return HI_FAILURE;
    }

    for ( i = 0; i < len; i++)
    {
        if ( ((buf[i] < 0x20) && (buf[i] != 0)) || (buf[i] > 0x7f) )
        {
            HI_ERR_CC("Invalide value for program type:buf[%d]=%x\n", i, buf[i]);
            return HI_FAILURE;
        }
    }

    stProgType.u8ProgTypeLen = len;
    memcpy(stProgType.au8ProgType, buf, len);

    XDS_TRACE("Program type:\n");

    for (i = 0; i < len; i++)
    {
        XDS_TRACE("%c ", stProgType.au8ProgType[i]);
    }

    XDS_TRACE("\n");

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeContentAdvisory(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;

    stContAdv.u8Char1   =   buf[0];
    stContAdv.u8Char2   =   buf[1];

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeAudioService(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;

    stAudioService.u8Main   =   buf[0];
    stAudioService.u8SAP    =   buf[1];

    XDS_TRACE("Audio Service: 0x%x 0x%x\n", stAudioService.u8Main, stAudioService.u8SAP);
    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeCaptionService(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len < MIN_CC608_CAPTSERV_LEN || len > MAX_CC608_CAPTSERV_LEN )
    {
        HI_ERR_CC("Invalide len = %d for caption service packet!\n", len);
        return HI_FAILURE;
    }

    stCaptService.u8CaptServicesLen = len;
    memcpy(stCaptService.au8CaptServices, buf, len);

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeCopyAndRedist(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len != 2 )
    {
        HI_ERR_CC("Invalide len = %d for CGMSA packet!\n", len);
        return HI_FAILURE;
    }

    stCopyAndRedist.u8Byte1 =   buf[0];
    stCopyAndRedist.u8Byte2 =   buf[1];

    XDS_TRACE("Copy and Redistribution: 0x%x 0x%x\n", buf[0], buf[1]);

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeCompPacket1(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len < 10 || len > 32 )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    memcpy(stCompPacket1.au8ProgramType, buf, 5);

    stCompPacket1.u8ContAdv       =   buf[5];
    stCompPacket1.u8LengthMin     =   buf[6];
    stCompPacket1.u8LengthHour    =   buf[7];
    stCompPacket1.u8ElapsedMin    =   buf[8];
    stCompPacket1.u8ElapsedHour   =   buf[9];
    stCompPacket1.u8TitleLen      =   len - 10;

    memcpy(stCompPacket1.au8Title, &buf[10], len - 10);

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeCompPacket2(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len < 14 || len > 32 )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stCompPacket2.stPRGStartTime.u8Minute   =   buf[0];
    stCompPacket2.stPRGStartTime.u8Hour     =   buf[1];
    stCompPacket2.stPRGStartTime.u8Data     =   buf[2];
    stCompPacket2.stPRGStartTime.u8Month    =   buf[3];
    stCompPacket2.stAudioServices.u8Main    =   buf[4];
    stCompPacket2.stAudioServices.u8SAP     =   buf[5];

    memcpy(stCompPacket2.au8CaptServices, &buf[6], 2);
    memcpy(stCompPacket2.au8CallLetter, &buf[8], 4);
    memcpy(stCompPacket2.au8NativeChan, &buf[12], 2);

    stCompPacket2.au8NetworkNameLen   =   len - 14;

    memcpy(stCompPacket2.au8NetworkName, &buf[14], len - 14);

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeProgDescription(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len > MAX_CC608_PROGDESC_LEN )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stXDSProgDesc.u8ProgDescLen = len;
    memcpy(stXDSProgDesc.au8ProgDesc, buf, len);

    return 0;
}

static HI_S32 _CC608_XDS_DecodeNetworkName(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if (len < MIN_CC608_NETNAME_LEN)
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    if (len > MAX_CC608_NETNAME_LEN)
    {
        len = MAX_CC608_NETNAME_LEN;
    }

    stNetworkName.u8NetNameLen  =   len;
    memcpy(stNetworkName.au8NetName, buf, len);

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeCallLetter(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if (len > MAX_CC608_CALLLET_LEN)
    {
        HI_ERR_CC("Invalide len = %d for composite packet and reset to length=6\n", len);
        len = MAX_CC608_CALLLET_LEN;
    }

    if (len <= MIN_CC608_CALLLET_LEN)
    {
        XDS_TRACE("Call Letter: %c %c %c %c\n", buf[0], buf[1], buf[2], buf[3]);
    }
    else
    {
        XDS_TRACE("Call Letter: %c %c %c %c %c %c\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
    }

    memcpy(stCallLetNatvCh.au8CallLetter, buf, (len > 4) ? 4 : len);

    if (len < MIN_CC608_CALLLET_LEN)
    {
        len = MIN_CC608_CALLLET_LEN;
    }

    stCallLetNatvCh.u8NativeChanLen =   len - MIN_CC608_CALLLET_LEN;
    memcpy(stCallLetNatvCh.au8NativeChan, &buf[MIN_CC608_CALLLET_LEN], len - MIN_CC608_CALLLET_LEN);

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeTapeDelay(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len != 2 )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stTapeDelay.u8Minute    =   buf[0];
    stTapeDelay.u8Hour      =   buf[1];

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeTSID(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len != 4 )
    {
        HI_ERR_CC("Invalide len = %d for TSID packet!\n", len);
        return HI_FAILURE;
    }

    stTransSignID.u8TSID3to0    =   buf[0];
    stTransSignID.u8TSID7to4    =   buf[1];
    stTransSignID.u8TSID11to8   =   buf[2];
    stTransSignID.u8TSID15to12  =   buf[3];

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeTimeOfDay(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;
    HI_U8 Minute, Hour, Date, Month, Week, Year;

    if ( len != 6 )
    {
        HI_ERR_CC("Invalide length:%d for Data/Time Packet!\n", len);
        return HI_FAILURE;
    }

    Minute = (buf[0] & 0x3F);
    Hour = (buf[1] & 0x1F);
    Date = (buf[2] & 0x1F);
    Month = (buf[3] & 0x0F);
    Week = (buf[4] & 0x07 );
    Year = (buf[5] & 0x3f );

    if ( ( Minute > 59 ) || ( Hour > 23 ) || ( Date > 31 ) || ( Month > 12 ))
    {
        HI_ERR_CC("Invalide Time/Date Value:Minute=%d,Hour=%d,Date=%d,Month=%d\n", Minute, Hour, Date, Month);
        return HI_FAILURE;
    }

    stTimeOfDay.u8Minute    =   Minute;
    stTimeOfDay.u8Hour      =   Hour;
    stTimeOfDay.u8Date      =   Date;
    stTimeOfDay.u8Month     =   Month;
    stTimeOfDay.u8Day       =   Week;
    stTimeOfDay.u8Year      =   Year;

    XDS_TRACE("Time of Day: %.2d-%.2d %.2d:%.2d, Week:%d,Year:%d\n", Month, Date, Hour, Minute, Week, Year + 1990);
    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeImpCaptureID(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len != 6 )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stImpCaptID.u8Minute    =   buf[0];
    stImpCaptID.u8Hour      =   buf[1];
    stImpCaptID.u8Date      =   buf[2];
    stImpCaptID.u8Month     =   buf[3];
    stImpCaptID.u8LengthMin =   buf[4];
    stImpCaptID.u8LengthHour =   buf[5];

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeSuplDataLoc(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( (len < MIN_CC608_SUPPDATA_LEN) || (len > MAX_CC608_SUPPDATA_LEN) )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stSupplDataLoc.u8SupplDataLocLen    =   len;
    memcpy(&stSupplDataLoc, buf, len);

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeTimeZone(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len != 2 )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    if ( buf[1] != 0)
    {
        HI_WARN_CC("The second character of Local Time Zone & DST Use packet is not NULL!\n");
    }

    stLocTimeZone.u8LocTimeZoneHour =   buf[0];

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeOutOfBand(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len != 2 )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stOutOfBand.u8ChanLow   =   buf[0];
    stOutOfBand.u8ChanHigh  =   buf[1];

    return 0;
}

static HI_S32 _CC608_XDS_DecodeChMapPointer(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len != 2 )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stChMapPointer.u8TuneChanLow    =   buf[0];
    stChMapPointer.u8TuneChanHigh   =   buf[1];

    return 0;
}

static HI_S32 _CC608_XDS_DecodeChMapHeader(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len != 4 )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stChMapHeader.u8ChanLow =   buf[0];
    stChMapHeader.u8ChanHigh =  buf[1];
    stChMapHeader.u8Version =   buf[2];

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeChMapPacket(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( (len < 2) || (len > 10))
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stChMapPacket.u8UserChanLow = buf[0];
    stChMapPacket.u8UserChanHigh = buf[1];

    if (len > 2)
    {
        stChMapPacket.u8TuneChanLow = buf[2];
        stChMapPacket.u8TuneChanHigh = buf[3];

        if (len > 4)
        {
            stChMapPacket.u8ChIDLen = len - 4;
            memcpy(stChMapPacket.au8ChID, &buf[4], len - 4);
        }
    }

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeNWSCode(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len > MAX_CC608_NWSCODE_LEN )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stNatWeaServcCode.u8NatWeaServcCodeLen  =  len;
    memcpy(stNatWeaServcCode.au8NatWeaServcCode, buf, len);

    return HI_SUCCESS;
}

static HI_S32 _CC608_XDS_DecodeNWSData(HI_U8* pu8PacketData, HI_U8 u8PacketLen)
{
    HI_U8* buf = pu8PacketData;
    HI_U8 len  = u8PacketLen;

    if ( len > MAX_CC608_NWSMSG_LEN )
    {
        HI_ERR_CC("Invalide len = %d for composite packet-1!\n", len);
        return HI_FAILURE;
    }

    stNatWeaServcMsg.u8NatWeaServcMsgLen = len;
    memcpy(stNatWeaServcMsg.u8NatWeaServcMsg, buf, len);

    return HI_SUCCESS;
}

HI_VOID caption_cc_output_xds_init()
{
    HI_S32 j = 0;

    memset(pfnXDSPacketDecoder, 0, sizeof(pfnXDSPacketDecoder));

    // current class
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_PRG_ID]       =   _CC608_XDS_DecodeProgIDNum;
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_TIMEINSHOW]   =   _CC608_XDS_DecodeLenAndTimeInShow;
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_PRG_NAME]     =   _CC608_XDS_DecodeProgName;
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_PRG_TYPE]     =   _CC608_XDS_DecodeProgType;
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_CONT_ADVSR]   =   _CC608_XDS_DecodeContentAdvisory;
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_AUD_SERVC]    =   _CC608_XDS_DecodeAudioService;
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_CAP_SERVC]    =   _CC608_XDS_DecodeCaptionService;
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_CPY_REDIST]   =   _CC608_XDS_DecodeCopyAndRedist;
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_COMP_1]       =   _CC608_XDS_DecodeCompPacket1;
    pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_COMP_2]       =   _CC608_XDS_DecodeCompPacket2;

    for (j = 0; j < 8; j++)
    {
        pfnXDSPacketDecoder[XDS_CLASS_CUR][XDS_CUR_PRG_DESC1 + j]  =  _CC608_XDS_DecodeProgDescription;
    }

    // future class
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_PRG_ID]       =   _CC608_XDS_DecodeProgIDNum;
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_TIMEINSHOW]   =   _CC608_XDS_DecodeLenAndTimeInShow;
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_PRG_NAME]     =   _CC608_XDS_DecodeProgName;
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_PRG_TYPE]     =   _CC608_XDS_DecodeProgType;
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_CONT_ADVSR]   =   _CC608_XDS_DecodeContentAdvisory;
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_AUD_SERVC]    =   _CC608_XDS_DecodeAudioService;
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_CAP_SERVC]    =   _CC608_XDS_DecodeCaptionService;
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_CPY_REDIST]   =   _CC608_XDS_DecodeCopyAndRedist;
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_COMP_1]       =   _CC608_XDS_DecodeCompPacket1;
    pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_COMP_2]       =   _CC608_XDS_DecodeCompPacket2;

    for (j = 0; j < 8; j++)
    {
        pfnXDSPacketDecoder[XDS_CLASS_FUT][XDS_CUR_PRG_DESC1 + j]  =  _CC608_XDS_DecodeProgDescription;
    }

    // channel class
    pfnXDSPacketDecoder[XDS_CLASS_CHAN][XDS_CHAN_NET_NAME]    =   _CC608_XDS_DecodeNetworkName;
    pfnXDSPacketDecoder[XDS_CLASS_CHAN][XDS_CHAN_CALL_LETTER] =   _CC608_XDS_DecodeCallLetter;
    pfnXDSPacketDecoder[XDS_CLASS_CHAN][XDS_CHAN_TAPE_DELAY]  =   _CC608_XDS_DecodeTapeDelay;
    pfnXDSPacketDecoder[XDS_CLASS_CHAN][XDS_CHAN_TRNS_SIGNID] =   _CC608_XDS_DecodeTSID;

    // miscellaneous class
    pfnXDSPacketDecoder[XDS_CLASS_MISC][XDS_MISC_TIMEOFDAY]   =   _CC608_XDS_DecodeTimeOfDay;
    pfnXDSPacketDecoder[XDS_CLASS_MISC][XDS_MISC_IMPL_CAPTID] =   _CC608_XDS_DecodeImpCaptureID;
    pfnXDSPacketDecoder[XDS_CLASS_MISC][XDS_MISC_SUPL_DATALOC] =   _CC608_XDS_DecodeSuplDataLoc;
    pfnXDSPacketDecoder[XDS_CLASS_MISC][XDS_MISC_TIME_ZONE]   =   _CC608_XDS_DecodeTimeZone;
    pfnXDSPacketDecoder[XDS_CLASS_MISC][XDS_MISC_OUTOFBAND]   =   _CC608_XDS_DecodeOutOfBand;
    pfnXDSPacketDecoder[XDS_CLASS_MISC][XDS_MISC_CHMAP_POINTER] =  _CC608_XDS_DecodeChMapPointer;
    pfnXDSPacketDecoder[XDS_CLASS_MISC][XDS_MISC_CHMAP_HEADER] =   _CC608_XDS_DecodeChMapHeader;
    pfnXDSPacketDecoder[XDS_CLASS_MISC][XDS_MISC_CHMAP_PAKT] =   _CC608_XDS_DecodeChMapPacket;

    // public class
    pfnXDSPacketDecoder[XDS_CLASS_PUB][HI_UNF_CC_XDS_PUB_NWS_CODE] =   _CC608_XDS_DecodeNWSCode;
    pfnXDSPacketDecoder[XDS_CLASS_PUB][HI_UNF_CC_XDS_PUB_NWS_MSG] =   _CC608_XDS_DecodeNWSData;
}

HI_S32 caption_cc_output_xds(HI_U8 u8XDSClass, HI_U8 u8XDSType, HI_U8* pu8Data, HI_U8 u8DataLen)
{
    XDSPacketDecoder_FN pFnXDSPacketDecoder;

    XDS_TRACE("CC608_XDS_Decode, u8XDSClass=%d, u8XDSType=%d,u8DataLen=%d\n", u8XDSClass, u8XDSType, u8DataLen);

    if ((u8XDSClass >= XDS_CLASS_BUTT) || (u8XDSType >= XDS_MISC_TYPE_BUTT))
    {
        HI_ERR_CC("Invalid XDS packet class %d or type %d.\n", u8XDSClass, u8XDSType);
        return HI_FAILURE;
    }

    pFnXDSPacketDecoder = pfnXDSPacketDecoder[u8XDSClass][u8XDSType];

    if (pFnXDSPacketDecoder == HI_NULL)
    {
        return HI_FAILURE;
    }

    if ( pu8Data && u8DataLen )
    {
        (HI_VOID)pFnXDSPacketDecoder(pu8Data, u8DataLen);
    }

    return HI_SUCCESS;
}
