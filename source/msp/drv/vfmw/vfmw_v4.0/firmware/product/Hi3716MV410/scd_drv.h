
#ifndef __SCD_DRV_H__
#define __SCD_DRV_H__


//#include "basedef.h"
#include "mem_manage.h"
#include "vfmw.h"
#include "sysconfig.h"

#define SCDDRV_OK       (0)
#define SCDDRV_ERR      (-1)

#define SCD_IDLE        (0)
#define SCD_BUSY        (1)

#define HEADER_BUFFER_SIZE         (128)

#ifdef CFG_SCD_TIME_OUT
#define SCD_TIMEOUT     (CFG_SCD_TIME_OUT)
#else
#define SCD_TIMEOUT     (2000)
#endif

#ifdef CFG_SCD_BUF
#define SCD_MSG_BUFFER  (CFG_SCD_BUF)
#else
#define SCD_MSG_BUFFER  (700*1024)  // ���ӳ����貿�ֿռ�������һ�����
#endif

#ifndef MUTI_SCD
#ifndef SM_RUN_ON_SOFTSCD

/* register operator */
#ifdef MULTI_VDH

#define  WR_SCDREG(reg, dat)   MEM_WritePhyWord((SCD_REG_PHY_ADDR + reg),(dat));
#define  WR_SCDREG_1(reg, dat) MEM_WritePhyWord((SCD_REG_PHY_ADDR_1 + reg),(dat));
#define  WR_SCDREG_2(reg, dat) MEM_WritePhyWord((SCD_REG_PHY_ADDR_2 + reg),(dat));
#define  RD_SCDREG(reg)        MEM_ReadPhyWord((SCD_REG_PHY_ADDR + reg))
#define  RD_SCDREG_1(reg)      MEM_ReadPhyWord((SCD_REG_PHY_ADDR_1 + reg))
#define  RD_SCDREG_2(reg)      MEM_ReadPhyWord((SCD_REG_PHY_ADDR_2 + reg))

#else

#define  WR_SCDREG(reg, dat)                          \
    do{                                       \
        MEM_WritePhyWord((s_RegPhyBaseAddr + reg),(dat));                   \
    }while(0)
#define  WR_SCDREG_1(reg, dat)                          \
    do{                                       \
        MEM_WritePhyWord((s_RegPhyBaseAddr_1 + reg),(dat));                   \
    }while(0)

#define  RD_SCDREG(reg)    MEM_ReadPhyWord((SCD_REG_PHY_ADDR + reg))
#define  RD_SCDREG_1(reg)    MEM_ReadPhyWord((SCD_REG_PHY_ADDR_1 + reg))

#endif
#endif

#else//for muti scd
extern UADDR  s_ScdRegPhyBaseAddr[MAX_SCD_NUM];
extern UADDR  s_ScdRegResetPhyAddr[MAX_SCD_NUM];
extern UADDR  s_ScdRegResetOKPhyAddr[MAX_SCD_NUM];

#define  WR_SCDREG(id,reg,dat)   MEM_WritePhyWord((s_ScdRegPhyBaseAddr[id] + reg),(dat))
#define  RD_SCDREG(id,reg)       MEM_ReadPhyWord((s_ScdRegPhyBaseAddr[id] + reg))

#endif


typedef enum
{
    FMW_OK          = 0,
    FMW_ERR_PARAM   = -1,
    FMW_ERR_NOMEM   = -2,
    FMW_ERR_NOTRDY  = -3,
    FMW_ERR_BUSY    = -4,
    FMW_ERR_RAWNULL = -5, // Number or Size is 0
    FMW_ERR_SEGFULL = -6, // Number or Size is 0
    FMW_ERR_SCD     = -7
} FMW_RETVAL_E;

typedef enum
{
    SCDDRV_SLEEP_STAGE_NONE = 0,      // δ����
    SCDDRV_SLEEP_STAGE_PREPARE,       // �յ������������δ�������
    SCDDRV_SLEEP_STAGE_SLEEP          // ������
} SCDDRV_SLEEP_STAGE_E;

/* control registers */
#if 1
#define  REG_SCD_START        0x800
#define  REG_LIST_ADDRESS     0x804
#define  REG_UP_ADDRESS       0x808
#define  REG_UP_LEN           0x80c
#define  REG_BUFFER_FIRST     0x810
#define  REG_BUFFER_LAST      0x814
#define  REG_BUFFER_INI       0x818
#define  REG_SCD_INT_MASK     0x81c
#define  REG_SCD_PROTOCOL     0x820
#define  REG_SCD_INI_CLR      0x824
/* state registers */
#define  REG_SCD_OVER         0x840
#define  REG_SCD_INT          0x844
#define  REG_SCD_NUM          0x84c
#define  REG_ROLL_ADDR        0x850
#define  REG_SRC_EATEN        0x854
#else
#define  REG_SCD_START        0x000
#define  REG_LIST_ADDRESS     0x004
#define  REG_UP_ADDRESS       0x008
#define  REG_UP_LEN           0x00c
#define  REG_BUFFER_FIRST     0x010
#define  REG_BUFFER_LAST      0x014
#define  REG_BUFFER_INI       0x018
#define  REG_SCD_INT_MASK     0x01c
#define  REG_SCD_PROTOCOL     0x020
#define  REG_SCD_INI_CLR      0x024
/* state registers */
#define  REG_SCD_OVER         0x040
#define  REG_SCD_INT          0x044
#define  REG_SCD_NUM          0x04c
#define  REG_ROLL_ADDR        0x050
#define  REG_SRC_EATEN        0x054
#endif
//add by sdk 2013-03-21 3716cv200
#define  REG_DSP_SPS_MSG_ADDRESS      0x828
#define  REG_DSP_PPS_MSG_ADDRESS      0x82c
#define  REG_DVM_MSG_ADDRESS           0x830
#define  REG_SED_TOP_ADDRESS           0x834
#define  REG_CA_MN_ADDRESS             0x838
//end add

#define  REG_AVS_FLAG       0x0000
#define  REG_EMAR_ID        0x0004
#define  REG_VDH_SELRST        0x0008
#define  REG_VDH_ARBIT_CTRL_STATE             0X0010
#define  REG_VDH_CK_GT       0x000c
#define  REG_DSP_WATCH_DOG             0X0018
/*######################################################
       macro & constants
 ######################################################*/
// ʵ��״̬
#define SM_INST_MODE_IDLE   0
#define SM_INST_MODE_WORK   1
#define SM_INST_MODE_WAIT   2


// ���޳���
#ifdef CFG_MAX_RAW_NUM
#define MAX_STREAM_RAW_NUM  CFG_MAX_RAW_NUM
#else
#define MAX_STREAM_RAW_NUM  (1024)   ///?????? for test
#endif
#ifdef CFG_MAX_SEG_NUM
#define MAX_STREAM_SEG_NUM  CFG_MAX_SEG_NUM
#else
#define MAX_STREAM_SEG_NUM  (1024 + 128)
#endif
#define MAX_STREAM_SEG_ALLOW    (100000)
#define MIN_STREAM_SEG_NUM      4//��С����SCD����Ϣ�صĸ���
#define SM_MAX_SMID             MAX_CHAN_NUM
#define SM_SCD_UP_INFO_NUM      2
#ifdef SCD_MP4_SLICE_ENABLE
#define MAX_SM_SCD_UP_INFO_NUM  3  //MPEG4������Ϣ��ʹ��3��word������Э��ʹ��2��word��ȡ����
#else
#define MAX_SM_SCD_UP_INFO_NUM  SM_SCD_UP_INFO_NUM
#endif
#define SM_MAX_DOWNMSG_SIZE     (3*MAX_STREAM_RAW_NUM*sizeof(SINT32))
#define SM_MAX_UPMSG_SIZE       (SM_SCD_UP_INFO_NUM*MAX_STREAM_SEG_NUM*sizeof(SINT32))

//add by sdk 2013-03-22 3716cv200
#define DSP_SPS_MSG_SIZE    (32*8*4)
#define DSP_PPS_MSG_SIZE    (256*8*4)
#define DVM_SIZE             (2*64*4)
#define DSP_SED_TOP_SIZE    (64*4*1088)
#define CA_MN_SIZE           (64*4*1088)
//end add

#define SM_SEGWASTE_BUF_SIZE  64     //Segʣ��ռ��˷ѵĴ�С

//#define MIN_BTM_SEG_LEN  (2*1024)  // Ҫ��WORD������, �����������Ƶ�,������FPGA_SCD_SEG_BLANK_AHB_LEN
#define MIN_TOP_SEG_LEN  (1*1024)    // Ҫ��WORD�����������ܽ�ð��
#define SM_H263_THRESHOLD_NUM 12     //�������ٸ�H263ͷ���ֺ�����H263ģʽ

#define SM_RAW_DISCARD_SIZE    (1024*1024)

#define WAIT_SEG_REL_MAX_TIME   1000
#define WAIT_SCD_RDY_MAX_TIME   1000

#define SM_VIDOBJLAY_START_CODE        0x00000120
#define SM_VOP_START_CODE              0x000001b6
#define SM_SHORT_VIDEO_START_CODE      0x00008000



#define SMSEG_STATE_INVALID   0
#define SMSEG_STATE_FRESH     1
#define SMSEG_STATE_READOUT   2

#define SMSEG_IS_READ( seg )     (((seg).SegState == SMSEG_STATE_READOUT) ? 1 : 0)
#define SMSEG_IS_RELEASED( seg ) (((seg).SegState == SMSEG_STATE_INVALID) ? 1 : 0)
#define SMSEG_IS_FRESH( seg )    (((seg).SegState == SMSEG_STATE_FRESH) ? 1 : 0)

#define SMSEG_SET_ISREAD( seg )                       \
    do{                                     \
        (seg).SegState = SMSEG_STATE_READOUT;                             \
    } while (0)

#define SMSEG_SET_ISRELEASED( seg )                     \
    do{                                     \
        (seg).SegState = SMSEG_STATE_INVALID;                             \
    } while (0)

#define SMSEG_SET_ISFRESH( seg )                      \
    do{                                     \
        (seg).SegState = SMSEG_STATE_FRESH;                             \
    } while (0)



#define FMW_ASSERT( cond )                          \
    do{                                     \
        if( !(cond) )                             \
        {                                   \
            return;                               \
        }                                   \
    } while (0)

#define FMW_ASSERT_RET( cond, ret )                     \
    do{                                     \
        if( !(cond) )                             \
        {                                   \
            return (ret);                           \
        }                                   \
    } while (0)

#define SMSEG_PHY2VIR( SegArrayPtr, phy, vir )                \
    do{                                     \
        (vir) = SegArrayPtr->pSegBufVirAddr+((phy)-SegArrayPtr->SegBufPhyAddr); \
    } while (0)



/*Check Val is between MinValue and MaxValue*/
#define SM_CHECK_VALUE(Val,MinValue,MaxValue,RetAction) \
    do \
    {\
        if (((Val) < (MinValue)) || ((Val) > (MaxValue)))\
        {\
            RetAction;\
        }\
    }while(0)



/*######################################################
       struct defs.
 ######################################################*/
typedef struct
{
    STREAM_DATA_S RawPacket[MAX_STREAM_RAW_NUM];
    SINT32      Head;
    SINT32      Tail;
    SINT32      History;
    SINT32      FirstPacketOffset;
    SINT32      CurShowIndex;
    SINT32      RawTotalSize;
} RAW_ARRAY_S;

typedef struct
{
    SINT8    ScdIntMask;
    SINT8    SliceCheckFlag;
    SINT8    ScdStart;//�Ƿ�����Scd
    UADDR    DownMsgPhyAddr;//����������Ϣ�صĵ�ַ
    SINT32   *pDownMsgVirAddr;
    UADDR    UpMsgPhyAddr;
    SINT32   *pUpMsgVirAddr;
    SINT32   UpLen;
    UADDR    BufferFirst;
    UADDR    BufferLast;
    UADDR    BufferIni;
    SINT32   ScdProtocol;
    SINT32   ScdIniClr;

    //add by sdk 2013-04-15  3716cv200
    UADDR    DspSpsMsgMemAddr;
    SINT32   *pDspSpsMsgMemVirAddr;
    SINT32   DspSpsMsgMemSize;

    UADDR    DspPpsMsgMemAddr;
    SINT32   *pDspPpsMsgMemVirAddr;
    SINT32   DspPpsMsgMemSize;

    UADDR    DvmMemAddr;
    SINT32   *pDvmMemVirAddr;
    SINT32   DvmMemSize;

    UADDR    DspSedTopMemAddr;
    SINT32   *pDspSedTopMemVirAddr;
    SINT32   DspSedTopMemSize;

    UADDR    DspCaMnMemAddr;
    SINT32   *pDspCaMnMemVirAddr;
    SINT32   DspCaMnMemSize;

    SINT32   ScdLowdlyEnable;
    SINT32   reg_avs_flag;
    //end add
} SM_CTRLREG_S;
//add by sdk 3716cv200 2013-04-15
typedef struct
{
    SINT32  Avs_Flag;
    SINT32  EMAR_ID;
    SINT32  VDH_SEL_RST_EN;
} GLB_CTRLREG_S;
typedef struct
{
    SINT32  Scdover;
    SINT32  ScdInt;
    SINT32  ShortScdNum;
    SINT32  ScdNum;
    UADDR   ScdRollAddr;
    SINT32  SrcEaten;
} SM_STATEREG_S;

/* MEPG4 ���е���Ч������Ϣ */
typedef struct
{
    USIGN  IsShStreamFlag:        1;
    USIGN  SliceFlag:             1;
    USIGN  IsShortHeader:         1;
    USIGN  StartCodeBitOffset:    4;
    USIGN  StartCodeLength:       4;
    USIGN  Reserved:              21;
} MP4_SCD_UPMSG;

/********************************************************************************
PhyAddr   ����Ƭ�������ַ
VirAddr   ����Ƭ�������ַ
LenInByte ����Ƭ�ĳ��ȣ����ֽ�Ϊ��λ
StreamID  ����Ƭ��ID��ÿƬλ�ڻ���������������һ��Ψһ��ID��
SegState  ����Ƭ��״̬
        0��  ���У�������Ƭ��Ч
        1��  SCD�ѷָ��δ������
        2��  �Ѷ��ߣ���δ�ͷ�
        ������reserved
IsLastSeg ��ʶ��Ƭ�����Ƿ���һ�����뵥Ԫ�����һƬ����
        0��    ��Ƭ�����������һƬ
        1��    ��Ƭ���������һƬ
        other��reserved
        ע��һ�����뵥Ԫ��ָЭ���һ�ν�����������Ԫ������H.264Э����ԣ�
            ���뵥Ԫ��NAL��MPEGϵ��Э��Ľ��뵥Ԫ����picture
Pts         ������ʱ���
*********************************************************************************/
typedef struct
{
    UINT8     *VirAddr;
    SINT8     SegState;
    UINT8     IsLastSeg;
    UINT8     IsStreamEnd;
    UINT8     DspCheckPicOverFlag;
    UADDR     PhyAddr;
    SINT32    LenInByte;
    SINT32    StreamID;
    UINT64    Pts;
    UINT64    RawPts;
    UINT64    Usertag;
    UINT64    DispTime;
    UINT32    DispEnableFlag;
    UINT32    DispFrameDistance;
    UINT32    DistanceBeforeFirstFrame;
    UINT32    GopNum;
    /* MEPG4 ���е���Ч������Ϣ */
    MP4_SCD_UPMSG stMp4UpMsg;
} STREAM_SEG_S;


/********************************************************************************

RawPacket ԭʼ������Ϣ�ļ�¼�ռ䣬���ɼ�¼MAX_RAW_PACKET_NUM������������Ϣ��
Head    ��һ����Ч��¼��λ��
Tail    ���һ����Ч��¼��λ��
SegBufPhyAddr ����Ƭ�λ����������ַ
pSegBufVirAddr  ����Ƭ�λ����������ַ
SegBufSize    ����Ƭ�λ�������С����λ���ֽ�
SegBufReadAddr  ����Ƭ�λ������Ķ���ַ
SegBufWriteAddr ����Ƭ�λ�������д��ַ
*********************************************************************************/
typedef struct
{
    UINT8         *pSegBufVirAddr;
    STREAM_SEG_S  StreamSeg[ MAX_STREAM_SEG_NUM ];
    SINT32        Head;
    SINT32        Tail;
    SINT32        History;
    SINT32        Current;
    UADDR         SegBufPhyAddr;
    SINT32        SegBufSize;
    UADDR         SegBufReadAddr;
    UADDR         SegBufWriteAddr;

    SINT32        SegTotalSize;    /* SegTotalSize:  Insert��, Release�� */
    SINT32        SegFreshSize;    /* SegFreshSize:  Insert��, Read�� */
    SINT32        SegFreshNum;
} SEG_ARRAY_S;


/********************************************************************************
Mode  ָ�����ú�SMʵ���Ĺ���ģʽ��
        0���ǹ���ģʽ
        1������ģʽ
        ���Mode��0�����ⲿģ��ϣ�����SMʵ��ֹͣ���������������ֻ��رմ�ʵ����������Ա��ȡֵ�����ԡ�
Priority    ���ȼ�
            ���ȼ�ͨ����һ�����������������ֵԽ�����ȼ�Խ�ߡ�
            0����"��Ȩ��"���������ȼ����κ�ʱ�򶼲��ᱻ���ȡ�
VidStd  VID_STD_E ��ƵЭ�����͡�������ƵЭ��Ķ����ԣ��������зֺ͹����п��ܴ�����Э����صĲ������������ָ��Э�����͡�
DownMsgAddr ������Ϣ�����������������ַ
DownMsgSize ������Ϣ�Ĵ�С���ֽ�����
UpMsgAddr   ������Ϣ����ʼ���ַ�����������ַ
UpMsgSize   ������Ϣ�Ĵ�С���ֽ�����
SegBufAddr  �����������������ַ������������д�ŵ��Ǳ�SCD����������Чģ�飩�и�õ���������������ַ��Ϊ�����ַ�������ַ����Ϊ����ӦĳЩ����ϵͳ������Linux�����ص㣬����������ϵͳ�У������ַ�������ַ���ó�ͬһ��ֵ���ɡ�
SegBufSize  �������Ĵ�С�����ֽ�Ϊ��λ��
*********************************************************************************/
typedef struct
{
    //SINT32        Mode;
    UINT8        *pBufVirAddr;
    UINT8         Priority;
    VID_STD_E     VidStd;

    UADDR         BufPhyAddr;
    SINT32        BufSize;

    /*�Ĵ����������ַ*/
    UADDR         RegPhyBaseAddr;
    STD_EXTENSION_U    StdExt;              /* ��չ��Ϣ��VC1��ص��������Ƿ�ΪAP �Ͱ汾��Ϣ*/
    //UINT32        LastRawDisContinueCount;  /* �����ж��Ƿ���raw��DisContinueCount�仯 ����ʼ��Ϊ-1 */
    //SINT32        DisContinueRawPacketFlag; /* 0: δ������1: ������2: ���������¿�ʼ���豻�ٴλص�0״̬ */
    SINT32        ScdLowdlyEnable;          /* 0: ���ӳ�δʹ��; 1: ���ӳ�ʹ�� */
    SINT32        s32ChanLowlyEnable;
    SINT32        IsOmxPath;             /* 0: �ͻ���δʹ��; 1: �ͻ���ʹ�� */
    //STREAM_DATA_S DisContinueRawPacket;     /* ��¼����raw��discontinueʱ������һ�������Ժ����Ӵ˰���ʼ���� */

    SINT32        MaxRawPacketNum;
    SINT32        MaxRawPacketSize;
} SM_CFG_S;


typedef struct
{
    UINT8        *pSegBufVirAddr;
    UADDR         DownMsgPhyAddr;
    SINT32       *pDownMsgVirAddr;
    SINT32        DownMsgSize;

    UADDR         UpMsgPhyAddr;
    SINT32       *pUpMsgVirAddr;
    SINT32        UpMsgSize;
    SINT32        UpMsgNum;  // Num of UpMsg, Unit: 2 * WORD
    //add by sdk 2013-04-15 3716cv200
    UADDR         DspSpsMsgMemAddr;
    SINT32         *pDspSpsMsgMemVirAddr;
    SINT32         DspSpsMsgMemSize;

    UADDR         DspPpsMsgMemAddr;
    SINT32         *pDspPpsMsgMemVirAddr;
    SINT32         DspPpsMsgMemSize;

    UADDR         DvmMemAddr;
    SINT32         *pDvmMemVirAddr;
    SINT32         DvmMemSize;

    UADDR         DspSedTopMemAddr;
    SINT32         *pDspSedTopMemVirAddr;
    SINT32         DspSedTopMemSize;

    UADDR         DspCaMnMemAddr;
    SINT32         *pDspCaMnMemVirAddr;
    SINT32         DspCaMnMemSize;
    //end add
    UADDR         SegBufPhyAddr;
    SINT32        SegBufSize;
} SM_BUFFERCFG_S;


/********************************************************************************
 SMʵ������Ϣ�ṹ�����ڶ��⴫���ڲ���Ϣ����GetInfo()�ӿ���ʹ��
*********************************************************************************/
typedef struct
{
    SINT8         InstMode;      /* 0: �ǹ���ģʽ,  1: ����ģʽ   */
    SINT32        RawNum;        /* ԭʼ��������Ŀ                */
    SINT32        SegNum;        /* ԭʼ������������              */
    SINT32        TotalRawSize;  /* ���и������Ƭ����Ŀ          */
    SINT32        TotalSegSize;  /* ���и������Ƭ����������      */

    SINT32        numReadSegFail;  /* ����������seg�ļ��� */
} SM_INST_INFO_S;

/********************************************************************************
 ÿ������Scd��Raw���������ԣ���Ҫ����SegStream��Ptsʹ��
*********************************************************************************/
typedef struct
{
    UINT8    *pCurrStartVirAddr;
    UINT8    *pCurrEndVirAddr;
    UADDR     CurrStartPhyAddr;
    UADDR     CurrEndPhyAddr;
    SINT32    Length;
    SINT32    TotalLen;//�ӵ�0������ǰ�����ۼƳ���
    UINT64    Pts;
} SM_PUSHRAWPACKET_S;

typedef struct
{
    SINT32             PushRawNum;
    SINT32             PushRawTotalLen;
    SINT32             PushRawOver; // 0:��ʼ״̬��1:��������SCD����2:���SCD����3:������������seekPTS����Ϊ��Ч
} SM_PUSHRAW_S;

typedef enum
{
    SM_NOT_MPEG4 = 0,
    SM_MPEG4_NOTH263,
    SM_MPEG4_H263
} MPEG4_SUB_STD;

typedef struct
{
    UINT8    *pSegBufVirAddr;//Seg Buffer�������ַ,ȡ����ʱʹ��
    SINT32    *pScdUpMsg;      //�����˵�������Ϣ�ĵ�ַ
    SINT32    ProtocolType;
    SINT32    ModeFlag;       //0:�ڷ�Mpeg4ģʽ; 1:��һ�β���H263ģʽ, 2:��һ����H263ģʽ
    SINT32    LastH263Num;    //��һ�ν�������ΪH263ͷ������
    UADDR     SegBufPhyAddr;
    SINT32    SegBufSize;
    UADDR     SegBufRollAddr;
    SINT32    SegNum;         //�����˵�SegStream���ж��ٰ�
    SINT32    SMInstID;       // ��ǰ����ʵ��ID
} SM_SEGSTREAMFILTER_S;

typedef struct
{
    SINT8          SegFullFlag;
    SINT8          IsCounting;
    SINT8          LastCfgAllRawFlag; // 1 : ��ʵ���ϴ�����SCDʱ�����е�RAW���������������ô����ñ�־λ��ÿ��SCD����ʱ�����жϸ�ֵ
    SINT8          InsertNewSegFlag; // 1 : ��ʵ��SCD��������µ�SEG�������ñ�־λ����ÿ��SCD�ж��н��и��£�SCD��������0
    SINT8          FillNewRawFlag; // 1 : ��ʵ���ϴ�SCD����������µ�RAW�������ñ�־λ����ÿ��SCD��������0

    SM_SEGSTREAMFILTER_S SegFilter;//ֻ��Mpeg4�������ʹ��
    SM_CFG_S       Config;
    RAW_ARRAY_S    RawPacketArray;
    SEG_ARRAY_S    StreamSegArray;
    SM_PUSHRAW_S   SmPushRaw;
    SM_BUFFERCFG_S BufAddrCfg;
    SINT32         InstID;
    SINT32         ScdID;         //��¼��ǰͨ���������SCD id�ţ�����SM_Stop�Ⱥ�����,������SCD�и�ǮҪ���¸�ֵ
    SINT32         CutingFlag;    //��¼��ǰͨ���Ƿ����ڱ�SCD�и��SM_SCDIntServeProc�жϴ���������0����CutStreamWithSCD����1
    SINT32         MatchScdIdPlus1;  //��¼��ǰͨ��ƥ���SCDid +1; -1->��ͨ��DSP������δ���������ܴ���0->���ʹ��SCD�и1->�̶�ѡ��SCD0�и2->�̶�ѡ��SCD1�и�...;
    SINT32         Mode;
    SINT32         TransFormSeg[MAX_STREAM_SEG_NUM *MAX_SM_SCD_UP_INFO_NUM];  //�任���SegƬ��,ֻ��Mpeg4������¿�����������Ϣ��һ��,����Э�鶼��һ����
    UINT32         BlockTimeInMs;  // ��������ʱ�䣬��λms
    UINT32         LastBlockTime;  // ��һ�α�������ʱ��(ϵͳʱ��)�����ں���ˢ������ʱ��
    UINT64         LastPts;//������ε�Pts���ϴ���ͬ�����-1
    SINT32         PrevCfgRawSize;
    SINT32         PrevCfgSegSize;

    /* ͳ������ */
    SINT32         TotalRawSize;
    UINT32         LastStatTime; //����ͳ�����ʵ�ʱ��
    UINT32         BitRate;  // ����, ��λKbps

    /* ����ͳ����Ϣ */
    SINT32         numReadSegFail;
    SINT32         LastSCDStartTime; //�ϴ�����SCD�����ʱ�䣬��λ ����

    UINT32         UpMsgStepNum;
    UINT32         u32RawSizeCount;
    UINT32         u32RawNumCount;
    SINT32         s32ChanLowlyEnable;    /* chan lowdly enable */

    UINT32         HeaderLen;
    UINT8          HeaderBuf[HEADER_BUFFER_SIZE];

} SM_INSTANCE_S;


typedef struct hiSCD_DRV_MEM_S
{
    UADDR          HwMemAddr;
    SINT32         HwMemSize;

    UADDR          DownMsgMemAddr;
    UINT32        *pDownMsgMemVirAddr;
    SINT32         DownMsgMemSize;

    UADDR          UpMsgMemAddr;
    SINT32        *pUpMsgMemVirAddr;
    SINT32         UpMsgMemSize;
    //add by sdk 2013-04-15  3716cv200
    //sps pps ��Ҫ��ͨ�����
    /*
    	SINT32         DspSpsMsgMemAddr;
    	SINT32         *pDspSpsMsgMemVirAddr;
    	SINT32         DspSpsMsgMemSize;

    	SINT32         DspPpsMsgMemAddr;
    	SINT32         *pDspPpsMsgMemVirAddr;
    	SINT32         DspPpsMsgMemSize;
    */
    UADDR          DvmMemAddr;
    SINT32         *pDvmMemVirAddr;
    SINT32         DvmMemSize;

    UADDR          DspSedTopMemAddr;
    SINT32         *pDspSedTopMemVirAddr;
    SINT32         DspSedTopMemSize;

    UADDR          DspCaMnMemAddr;
    SINT32         *pDspCaMnMemVirAddr;
    SINT32         DspCaMnMemSize;
    //end add
    UADDR          ScdRegAddr;
    UADDR          ScdResetRegAddr;
} SCD_DRV_MEM_S;

/*
    ���ӳ�����Ҫά��SPS,PPS��Ϣ��DDT MEM ����
*/
typedef struct
{
    MEM_RECORD_S   stBaseMemInfo;

    UADDR          DspSpsMsgMemAddr;
    SINT32         *pDspSpsMsgMemVirAddr;
    SINT32         DspSpsMsgMemSize;

    UADDR          DspPpsMsgMemAddr;
    SINT32         *pDspPpsMsgMemVirAddr;
    SINT32         DspPpsMsgMemSize;
} DSP_CTX_MEM_S;

/********************************************************************************
ThisInstID    ��ǰSCD���ڴ����ʵ�����
ScdState    SCD�Ĺ���״̬��
          0�����У�δ������
          1�����У����������У�
*********************************************************************************/
typedef struct
{
    SCD_DRV_MEM_S       ScdDrvMem;
    //    SM_INSTANCE_S       SmInstArray[MAX_CHAN_NUM];
    SINT32              IsScdDrvOpen;
    SINT32              ThisInstID;
    SINT32              SCDState;
    UINT32              LastProcessTime;
    SINT32              DspReloadFlag;
} SMDRV_PARAM_S;

/********************************************************************************
SmInstArray     SMʵ�����飬��¼SCDʵ������Ϣ��ָ��
DspCtxMem       SMʵ����Ӧ�����DSP��Դ������
SmInstPriority  SMʵ�������ȼ�
          0����������ȼ���1��֮����������
*********************************************************************************/
typedef struct
{
    DSP_CTX_MEM_S       DspCtxMem;
    SM_INSTANCE_S      *pSmInstArray;
    SINT32              SmInstPriority;
} SM_IIS_S;



/*######################################################
       interface functions.
 ######################################################*/
SINT32 SCDDRV_PrepareSleep(SINT32 ScdId);
SCDDRV_SLEEP_STAGE_E SCDDRV_GetSleepStage(SINT32 ScdId);
VOID SCDDRV_ForceSleep(SINT32 ScdId);
VOID SCDDRV_ExitSleep(SINT32 ScdId);


/*========================================================================
    part1.    raw stream management module
========================================================================*/
/*********************************************************************************
    ����ԭ��
      SINT32 ResetSCD(VOID)
    ��������
      ��λSCDӲ��
    ����˵��
      ��
    ����ֵ
      ��
    �㷨����
      ��
*********************************************************************************/
SINT32 ResetSCD(SINT32 ScdId);


/************************************************************************
  ԭ��  SINT32 InsertRawPacket( RAW_ARRAY_S *pRawStreamArray, RAW_PACKET_S *pRawPacket )
  ����  ��һ��ԭʼ���������뵽ָ������������
  ����  pRawStreamArray ָ��ԭʼ��������
        pRawPacket  ָ��ԭʼ������
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 InsertRawPacket( RAW_ARRAY_S *pRawStreamArray, STREAM_DATA_S *pRawPacket );

/************************************************************************
  ԭ��  SINT32 GetRawIsFull(SINT32 SmID)
  ����  �õ�Raw Buffer�ܷ�����״̬
  ����  SmID  ��������ģ���ʵ���ı�ʶ
  ����ֵ  ���Բ���Raw Packet�ͷ���FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 GetRawState(SINT32 SmID);

/************************************************************************
  ԭ��  SINT32 SetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 Offset )
  ����  ���õ�һ������������Ч�ֽ�ƫ��
  ����  pRawStreamArray ָ��ԭʼ��������
    Offset  ��һ�����ݰ�����Ч�ֽ�ƫ����
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 SetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 Offset );

/************************************************************************
  ԭ��  SINT32 GetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 *pOffset )
  ����  ��ȡ��һ������������Ч�ֽ�ƫ��
  ����  pRawStreamArray ָ��ԭʼ��������
        pOffset ��һ�����ݰ�����Ч�ֽ�ƫ����
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 GetFirstOffset( RAW_ARRAY_S *pRawStreamArray, SINT32 *pOffset );

/************************************************************************
  ԭ��  SINT32 ShowFirstRawPacket( RAW_ARRAY_S *pRawStreamArray, RAW_PACKET_S *pRawPacket )
  ����  �鿴ָ�������������еĵ�һ����������Ϣ��
  ����  pRawStreamArray ָ��ԭʼ��������
        pRawPacket  ָ��ԭʼ�������Ľṹ�����ڽ�����������Ϣ
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 ShowFirstRawPacket( RAW_ARRAY_S *pRawStreamArray, STREAM_DATA_S *pRawPacket );

/************************************************************************
  ԭ��  SINT32 ShowNextRawPacket( RAW_ARRAY_S *pRawStreamArray, RAW_PACKET_S *pRawPacket )
  ����  "Next"���������һ�ε���Show���������Եġ���������ShowFirstRawPacket()��Ͽɲ鿴��������������Ϣ��
  ����  pRawStreamArray ָ��ԭʼ��������
        pRawPacket  ָ��ԭʼ�������Ľṹ�����ڽ�����������Ϣ
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 ShowNextRawPacket( RAW_ARRAY_S *pRawStreamArray, STREAM_DATA_S *pRawPacket );

/************************************************************************
  ԭ��  SINT32 DeleteRawPacket( RAW_ARRAY_S *pRawStreamArray, UINT32 DelNum )
  ����  �ӵ�һ��������ʼ������ɾ��DelNum����������
          ����������Ƭ�λ������Ĵ��ڣ�ԭʼ�������������ͷţ�����ԭʼ����
      ����ģ�����ֻ֧�ְ�����˳���ͷš���������ԭʼ��������ɾ����ͬʱ��
      Ҳ�����MPP�Ľӿ�֪ͨ�ⲿ�齨�ͷŶ�Ӧ�������ռ䡣
  ����  pRawStreamArray ָ��ԭʼ��������
        pRawPacket  ָ��ԭʼ�������Ľṹ�����ڽ�����������Ϣ
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 DeleteRawPacket( RAW_ARRAY_S *pRawStreamArray, UINT32 DelNum );

/************************************************************************
ԭ��    SINT32 DeleteRawPacketInBuffer(SINT32 SmID, SINT32 ResetFlag)
����    ��history��ʼ������ɾ����head
����    pRawStreamArray ָ��ԭʼ��������
����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 DeleteRawPacketInBuffer(SINT32 SmID, SINT32 ResetFlag);

/************************************************************************
  ԭ��  SINT32 GetRawNumOffsert( RAW_ARRAY_S *pRawStreamArray, SINT32 Len, SINT32 *pNum, SINT32 *pOffset, UINT64 *pPts, UINT64 *pUsertag, UINT64 *pDisptime, UINT32 *pDispEnableFlag, UINT32 *pDispFrameDistance, UINT32 *pDistanceBeforeFirstFrame, UINT32 *pGopNum, UINT64 *pRawPts);
  ����  �ӳ���Len����ӵ�һ��������ʼ��������Ҫ�ж�����������Ĵ�С����Len������а���򳤶�����ΪOffset��
  ����  pRawStreamArray ָ��ԭʼ��������
        Len             ����
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 GetRawNumOffsert( RAW_ARRAY_S *pRawStreamArray, SINT32 Len, SINT32 *pNum, SINT32 *pOffset, UINT64 *pPts, UINT64 *pUsertag, UINT64 *pDisptime, UINT32 *pDispEnableFlag, UINT32 *pDispFrameDistance, UINT32 *pDistanceBeforeFirstFrame, UINT32 *pGopNum, UINT64 *pRawPts);

/************************************************************************
  ԭ��  SINT32 DeleteRawLen( RAW_ARRAY_S *pRawStreamArray, SINT32 DelLen )
  ����  �ӵ�һ��������ʼ������ɾ��DelLen�����������ɾ���ĳ��Ȳ�������Ҫ��ƫ�ơ�
  ����  pRawStreamArray ָ��ԭʼ��������
        DelLen  �ܹ���Ҫɾ���ĳ���
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 DeleteRawLen( RAW_ARRAY_S *pRawStreamArray, SINT32 DelLen );

/************************************************************************
  ԭ��  SINT32 DeleteLastSendRaw( UINT32 SmID  )
  ����  ɾ��SmID��ָ���ͨ�����ϴ�������SCD������
  ����  SmIDͨ����
  ����ֵ  ��
************************************************************************/
VOID DeleteLastSendRaw( UINT32 SmID );

/************************************************************************
  ԭ��  SINT32 GetRawStreamSize( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamSize)
  ����  ��ԭʼ�������������а��ĳ����ۼ�������Ϊ����������Ŀ���ǻ��Ŀǰ������ռ�������
  ����  pRawStreamArray ָ��ԭʼ��������
  ����ֵ  �ɹ������������ȣ����򷵻ش����루��������
************************************************************************/
SINT32 GetRawStreamSize( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamSize);

/************************************************************************
    ԭ��  SINT32 GetRawStreamNum( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum )
    ����  ��ԭʼ�����������ѱ����͵���δ���и������������Ŀ���ǻ��Ŀǰ������ռ�������
    ����  pRawStreamArray ָ��ԭʼ��������
    ����ֵ  �ɹ�����pStreamNum����������������FMW_OK,ʧ���򷵻ش����루��������
************************************************************************/
SINT32 GetRawStreamNum( RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum );

/*========================================================================
    part2.    stream segment management module
========================================================================*/

/************************************************************************
  ԭ��  SINT32 ConfigStreamSegArray( SEG_ARRAY_S *pStreamSegArray, UINT32 BufPhyAddr, UINT8 *pBufVirAddr, UINT32 BufSize )
  ����  Ϊ����Ƭ�μ������ñ�Ҫ����Ϣ��������Ƭ�λ��������׵�ַ�����ȵȡ�
  ����  pStreamSegArray ָ���и�����Ƭ�μ���
        BufPhyAddr  ����Ƭ�λ����������ַ
        BufSize ����Ƭ�λ�������С����λ���ֽ�
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 ConfigStreamSegArray( SEG_ARRAY_S *pStreamSegArray, UADDR BufPhyAddr, UINT8 *pBufVirAddr, UINT32 BufSize );

/************************************************************************
  ԭ��  VOID ResetStreamSegArray( SEG_ARRAY_S *pStreamSegArray )
  ����  ��һ���и�����Ƭ�μ��ϸ�λ������������м�¼���ͷ�ȫ���и���������ռ䡣
  ����  pStreamSegArray ָ���и�����Ƭ�μ���
  ����ֵ  ��
************************************************************************/
VOID ResetStreamSegArray( SEG_ARRAY_S *pStreamSegArray );

/************************************************************************
  ԭ��  VOID GetSegBuf( SEG_ARRAY_S *pStreamSegArray, UINT32 *pBufAddr, UINT32 *pBufLength )
  ����  ��ȡ����Ƭ�λ������ĵ�ַ�ͳ��ȡ�
          SCD�и�����ʱ��Ҫ���û������Ķ��׵�ַ��
  ����  pStreamSegArray ָ���и�����Ƭ�μ���
        pAddr ��������Ƭ�λ������׵�ַ�������ַ��������ָ��
        pLength ��������Ƭ�λ��������ȱ�����ָ��
  ����ֵ  ��
************************************************************************/
VOID GetSegBuf( SEG_ARRAY_S *pStreamSegArray, UADDR *pBufAddr, UINT32 *pBufLength );

/************************************************************************
  ԭ��  VOID GetFreeSegBuf( SEG_ARRAY_S *pStreamSegArray, UINT32 *pAddr, UINT32 *pLength )
  ����  ��ȡ���е�����Ƭ�λ���ռ䣬���н���д��ַ�Ͷ���ַֻ���Ŀռ䶼����Ϊ���пռ䡣
          ��������Ƭ�λ�������һ��ѭ��buffer�����Կ���������ܾ��ƣ��Ӷ�ʹ�õ�ַ��������
      �жϵ�ַ�Ƿ���Ƶ�������pAddr+pLength>buffer�ײ���
  ����  pStreamSegArray ָ���и�����Ƭ�μ���
        pAddr ���տ��пռ��׵�ַ�������ַ��������ָ��
        pLength ���տ��пռ䳤�ȱ�����ָ��
  ����ֵ  ��
************************************************************************/
VOID GetFreeSegBuf( SEG_ARRAY_S *pStreamSegArray, SINT32 *pAddr, SINT32 *pLength );

/************************************************************************
  ԭ��  SINT32 InsertStreamSeg( SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg )
  ����  ���ض�������Ƭ�μ��в���һ������Ƭ�Ρ�
      ����������������������һ�ǽ�����������Ƭ�ε�������Ϣ���뵽�����У��ڶ��Ǹ�������Ƭ�λ�������д��ַ��
  ����  pStreamSegArray ָ���и�����Ƭ�μ���
      pStreamSeg  ����������Ƭ�ε�������Ϣ
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 InsertStreamSeg( SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg , SINT32 InstID);

/************************************************************************
  ԭ��  SINT32 GetStreamSeg( SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg )
  ����  ���ض�������Ƭ�μ���ȡ��һ������Ƭ�Σ������ڶ���ͷ������Ƭ����Ϣȡ����
  ����  pStreamSegArray ָ����Ƭ�μ���
        pStreamSeg  �洢����Ƭ�ε�������Ϣ�Ľṹָ��
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 GetStreamSeg( SEG_ARRAY_S *pStreamSegArray, STREAM_SEG_S *pStreamSeg );

/************************************************************************
  ԭ��  SINT32 ReleaseStreamSeg( SEG_ ARRAY_S *pStreamSegArray, UINT32 StreamID)
  ����  ��IDΪStreamID������Ƭ���ͷţ�����������Ƭ������ʷ���Ѷ�ȡ��δ�ͷŵĵ�һ����������ͬ����������Ƭ�λ������Ķ���ַ��
  ����  pStreamSegArray ָ����Ƭ�μ���
      StreamID  ���ͷ�����Ƭ�ε�ID
        ���StreamIDȡֵ��0~ MAX_STREAM_SEG_NUM-1֮�����ʾҪ�ͷ�������ΪStreamID������Ƭ�Σ�
        ���StreamID = 0xffffffff�����ʾ�ͷŵ�һ������Ƭ�Ρ����������ʹ�ó����ǣ��������
      ����ģ�鳤ʱ�䲻�ͷ��������������ݴ���SMģ����Ҫǿ���ͷŵ�һ�������ڳ��ռ��������и�������
      ������������������£����۵�һ������Ƭ���Ƿ񱻶��ߣ���ǿ���ͷš�
  ����ֵ  �ɹ�����FMW_OK�����򷵻ش�����
************************************************************************/
SINT32 ReleaseStreamSeg( SEG_ARRAY_S *pStreamSegArray, UINT32 StreamID );

/************************************************************************
    ԭ��  SINT32 GetSegStreamSize( SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamSize)
    ����  ������Ƭ�ϼ��������а��ĳ����ۼ�������Ϊ����������Ŀ���ǻ��Ŀǰ������ռ�������
    ����  pSegStreamArray ָ������Ƭ�ϼ���
    ����ֵ  �ɹ������������ȣ����򷵻ش����루��������
************************************************************************/
SINT32 GetSegStreamSize( SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamSize);

/************************************************************************
    ԭ��  GetSegStreamNum(SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamNum);
    ����  ������Ƭ�ϼ������ѱ����͵���δ���и������������Ŀ���ǻ��Ŀǰ������ռ�������
    ����  pSegStreamArray ָ������Ƭ�ϼ���
    ����ֵ  �ɹ������������������򷵻ش����루��������
************************************************************************/
SINT32 GetSegStreamNum(SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamNum);

VOID GetFreshSegStream( SEG_ARRAY_S *pSegStreamArray, SINT32 *pFreshNum, SINT32 *pFreshSize);


/*========================================================================
    part3.    top level
========================================================================*/
SINT32 SM_OpenSCDDrv(UADDR MemAddr, SINT32 MemSize, SINT32 ScdId);
SINT32 SM_CloseSCDDrv(SINT32 ScdId);
VOID SM_GiveThreadEvent(SINT32 SmID);
VOID SCDDRV_MaskInt(SINT32 ScdId);
VOID SCDDRV_EnableInt(SINT32 ScdId);
//SINT32 SM_GetInstanceRawDiscontinue(SINT32 InstID);
//SINT32 SM_SetRawDiscontinueFlag(SINT32 InstID, SINT32 Flag);
//SINT32 SM_GetInstanceStreamEmptyFlag(SINT32 InstID);
VOID SM_InstInit(VOID);
VOID SCDDRV_ResetSCD(SINT32 ChanID);

/************************************************************************
  ԭ��  SINT32 SM_Reset ( SINT32 SmID )
  ����  ���������Ը�λһ����������ģ���ʵ����
      ������ʹ��ID��ΪSmID����������ģ��ʵ��������״̬���ص���ʼֵ��
  ����  SmID  ��ʶ��������ģ�����������Ϣ���ڶ�·�����У�ÿһ·����������һ����������ģ���
      ʵ����SmIDָ��ĳ���ض���ʵ����
  ����ֵ  �ɹ�����FMW_OK�����򷵻��ض��Ĵ�����
************************************************************************/
SINT32 SM_ClearInst (SINT32 SmID);
SINT32 SM_Reset ( SINT32 SmID );
SINT32 SM_Start (SINT32 SmID);
SINT32 SM_Stop (SINT32 SmID);

/************************************************************************
  ԭ��  SINT32 SM_Config ( SINT32 SmID, SM_CFG_S *pSmCfg )
  ����  ��������������һ����������ģ���ʵ���������ʵ����ʼ����֮ǰ��������ô˺����������ñ�Ҫ����Ϣ��
  ����  SmID  ��ʶ��������ģ�����������Ϣ���ڶ�·�����У�ÿһ·����������һ����������ģ���ʵ����
      SmIDָ��ĳ���ض���ʵ����
      pSmCfg  SMʵ����������Ϣ
  ����ֵ  �ɹ�����FMW_OK�����򷵻��ض��Ĵ�����
************************************************************************/
SINT32 SM_Config ( SINT32 SmID, SM_CFG_S *pSmCfg );
SINT32 SM_CfgBuf ( SINT32 SmID, SINT32 ScdId );

/************************************************************************
    ԭ��    SINT32 SM_GetInfo( SINT32 SmID, SM_INST_INFO_S *pSmInstInfo )
    ����  ��������ѯ��������ģ����ԭʼ�������ۼ��˶��ٰ������и������������ж��ٶΡ��ڶ�·���뻷���£��ϲ���ȳ��������Ҫ����ÿһ·����Щ��Ϣ��������SCD�������һ·ȥ�и�������
    ����  SmID  ��������ģ���ʵ���ı�ʶ
            pSmInstInfo  ���ʵ����Ϣ�Ľṹ
    ����ֵ  FMW_ERR_PARAM or FMW_OK
************************************************************************/
SINT32 SM_GetInfo( SINT32 SmID, SM_INST_INFO_S *pSmInstInfo );

/************************************************************************
  ԭ��  SINT32 SM_PushRaw(SINT32 SmID, RAW_PACKET_S *pRawPacket)
  ����  �ⲿ������ñ���������������ģ������һ�����������͹���ֻ�ǽ������������Ϣ��¼��SMģ����ڲ��ṹ�У�����һ������ִ���������зֹ�����
  ����  SmID  ��������ģ���ʵ���ı�ʶ
    PhyAddr ԭʼ�����������ַ
    VirAddr ԭʼ�����������ַ
    Length  ԭʼ�����ĳ��ȣ����ֽ�Ϊ��λ
    Pts ԭʼ�����Ľ�Ŀʱ���(PTS)
  ����ֵ  �ɹ�����FMW_OK�����򷵻��ض��Ĵ�����
************************************************************************/
SINT32 SM_PushRaw(SINT32 SmID, STREAM_DATA_S *pRawPacket);

/************************************************************************
ԭ��  SINT32 SM_ReadStreamSeg(SINT32 SmID, STREAM_SEG_S *pStreamSeg )
����  ����������������ģ���ȡһ���ѷָ���ϵ�����
����  SmID  ��������ģ���ʵ���ı�ʶ
      pStreamSeg  ������������Ϣ�Ľṹָ��
����ֵ  �����ȡ�ɹ�����FMW_OK�����򷵻���Ӧ�Ĵ�����
************************************************************************/
SINT32 SM_ReadStreamSeg(SINT32 SmID, STREAM_SEG_S *pStreamSeg);

/************************************************************************
  ԭ��  SINT32 SM_ReleaseStreamSeg( SINT32 SmID, SINT32 StreamID )
  ����  ��������Э����Ѿ�������ϵ�����Ƭ�黹����������ģ��
  ����  SmID  ��������ģ���ʵ���ı�ʶ
        StreamID  ����Ƭ��ID
  ����ֵ  ��
************************************************************************/
SINT32 SM_ReleaseStreamSeg( SINT32 SmID, SINT32 StreamID );

/************************************************************************
  ԭ��  SINT32 CalcInstBlockTime( SINT32 SmID )
  ����  ����ָ��ʵ����������ʱ�䣬���ϴ�����ʱ���뵱ǰʱ��֮���ۼӵ�
          ������ʱ����ȥ�����Ҹ���"�ϴ�����ʱ��"
  ����  SmID  ��������ģ���ʵ���ı�ʶ
          FirstCalc  1: ��һ�μ��㣬����¼"�ϴ�����ʱ��"
                     0: �ۼƼ��㣬����������֮�⻹Ҫ�ۼ�����ʱ��
  ����ֵ  �ۼ�����ʱ��
************************************************************************/
SINT32 CalcInstBlockTime( SINT32 SmID, SINT32 FirstCalc );

/************************************************************************
  ԭ��  SINT32 SetInstMode( SINT32 SmID, SINT32 Mode )
  ����  ����ָ��ʵ����������ʱ�䣬���ϴ�����ʱ���뵱ǰʱ��֮���ۼӵ�
          ������ʱ����ȥ�����Ҹ���"�ϴ�����ʱ��"
  ����  SmID  ��������ģ���ʵ���ı�ʶ
          Mode    SM_INST_MODE_WORK  ����ģʽ
                  SM_INST_MODE_WAIT  ����ģʽ
  ����ֵ  �ɹ�����FMW_OK�� ���򷵻ش�����
************************************************************************/
SINT32 SetInstMode( SINT32 SmID, SINT32 Mode );


/*========================================================================
    part4.   SCD level �����и�Ϳ�����ģ��
========================================================================*/

/************************************************************************
  ԭ��  SINT32 CutStreamWithSCD(RAW_ARRAY_S *pRawStreamArray, SEG_ARRAY_S *pStreamSegArray, UINT32 StdType, SINT32 *pCutRawNum)
    ����  ����SCD�и�������
            ��������ԭʼ��������ȡ�����ɸ����������ø�SCD��Ȼ������SCD�иһ���и��ԭʼ����������ȡ��������������
            1.  ����Ƭ�λ������Ŀ��пռ�
            2.  ԭʼ������PTS�ֲ�
            �༴�����и���������ܳ��Ȳ��ô�������Ƭ�λ������Ŀ��пռ�������һ���и��������PTS���ܱ仯������MPEGϵ�п��������ܴ����ƣ���
            ����������ԭʼ����������ģ���ShowFirstRawPacket() / ShowNextRawPacket()����������ɨ��ԭʼ�������õ����и������������
    ����  pRawStreamArray ԭʼ������
          pStreamSegArray �и�����Ƭ�μ�
          StdType ������Э�����͡�
            SCDͬ��ͷ���������Э�����͡�
            pCutRawNum ���и����������Ŀ������0��������
    ����ֵ  FMW_OK�������
************************************************************************/
SINT32 CutStreamWithSCD(SM_INSTANCE_S *pScdInstance, SINT32 ScdId);

/************************************************************************
  ԭ��  VOID ScdDriver(SM_CTRLREG_S *pSmCtrlReg, UINT32 *pRegUpAddress)
    ����  ���üĴ�������
    ����
    ����ֵ
************************************************************************/
SINT32 ScdDriver(SM_CTRLREG_S *pSmCtrlReg, SM_PUSHRAW_S *pSmPushRaw, SINT32 SegStreamSize, RAW_ARRAY_S *pRawStreamArray,
            SINT32 *pDownMsgVirAddr, UADDR DownMsgPhyAddr,SINT32 ScdId);

/************************************************************************
  ԭ��  VOID WriteScdVtrlReg()
    ����  ����Scd״̬�Ĵ�������
    ����
    ����ֵ
************************************************************************/
VOID WriteScdVtrlReg(SM_CTRLREG_S *pSmCtrlReg, SINT32 ScdId);

/************************************************************************
  ԭ��  SINT32 WriteScdMsg(SM_PUSHRAW_S *pSmPushRaw, SINT32 *pDownMsgVirAddr, SINT32 DownMsgPhyAddr)
    ����  ����Scd������Ϣ��
    ����
    ����ֵ
************************************************************************/
SINT32 WriteScdMsg(SM_PUSHRAW_S *pSmPushRaw, SINT32 SegStreamSize, RAW_ARRAY_S *pRawStreamArray,
           SINT32 *pDownMsgVirAddr, UADDR DownMsgPhyAddr, SINT32 LowdlyFlag,SINT32 ScdId);

/************************************************************************
  ԭ��  VOID ReadScdStateReg(SM_STATEREG_S *pSmStateReg)
    ����  ��ȡScd״̬�Ĵ�������
    ����
    ����ֵ
************************************************************************/
VOID ReadScdStateReg(SM_STATEREG_S *pSmStateReg, SINT32 ScdId);

/************************************************************************
  ԭ��  SINT32 CheckScdStateReg(SM_STATEREG_S *pSmStateReg, SINT32 StdType)
    ����  ���Scd״̬�Ĵ�������
    ����
    ����ֵ
************************************************************************/
SINT32 CheckScdStateReg(SM_STATEREG_S *pSmStateReg, SINT32 StdType);

/************************************************************************
ԭ��  SINT32 ScdReturnSegFilter(SM_SEGSTREAMFILTER_S *pSegStreamFilter, SINT32 *pTransFormSeg, SINT32 *pSegNum, UINT32 UpMsgStepNum)
����
����    pSegNum(����/���)
����ֵ  FMW_OK�������
************************************************************************/
SINT32 ScdReturnSegFilter(SM_SEGSTREAMFILTER_S *pSegStreamFilter, SINT32 *pTransFormSeg, SINT32 *pExtraSrcBack, SINT32 *pSegNum, UINT32 UpMsgStepNum);

/************************************************************************
ԭ��  SINT32 CheckSegValid(STREAM_SEG_S *pSegPacket, SINT32 SendSegTotalSize, SINT32 SegFreeBufLen)
����
        PreSegTotalSize:����֮ǰ��������ܳ���
        SegFreeBufLen:Seg Stream Buffer�л�ʣ����ٳ���
����ֵ  FMW_OK�������

************************************************************************/
SINT32 CheckSegValid(STREAM_SEG_S *pSegPacket, SINT32 SegFreeBufLen);

/************************************************************************
ԭ��  SM_PUSHRAW_S *pPushRaw, SINT32 CurrSegTotalSize, SINT32 *pCurrRawId,UINT32 *pPts)
����
����
����ֵ  Pts
************************************************************************/
//VOID GetSegPts(SM_PUSHRAW_S *pPushRaw, SINT32 CurrSegTotalSize, SINT32 *pCurrRawId, SINT64 *pLastPts, SINT64 *pPts);
//  VOID GetSegPts(RAW_ARRAY_S *pRawStreamArray, SINT32 Len, UINT64 *pLastPts, UINT64 *pPts, UINT64 *pUsertag, UINT64 *pDisptime);
VOID GetSegPts(RAW_ARRAY_S *pRawStreamArray, SINT32 Len, UINT64 *pLastPts, STREAM_SEG_S *pSegPacket);

/************************************************************************
ԭ��  SINT32 ProcessSCDReturn(RAW_ ARRAY_S *pRawStreamArray, SEG_ARRAY_S *pStreamSegArray, SINT32 *pCutRawNum)
����  ����SCD�ķ�����Ϣ��
        ��������SCD�ļĴ������ϡ�������Ϣ���ж�ȡ��һ�ε������и���Ϣ������������ֲ�����
        1.  ����������Ϣ����֡����NAL��������STREAM_SEG_S��ʽ��֯���Ҳ��뵽����Ƭ�μ�pStreamSegArray�й�������
        2.  �����˴��и������˶���ԭʼ��������������Щ�������ͷš�
        ����
        pRawStreamArray ԭʼ������
        pStreamSegArray �и�����Ƭ�μ�
����ֵ  FMW_OK�������
************************************************************************/
SINT32 ProcessScdReturn(SM_INSTANCE_S *pScdInstance, SINT32 ScdId);

/************************************************************************
  ԭ��  VOID SM_SCDIntServeProc ( VOID )
  ����  ������ΪSCD���жϷ��������ӦSCD���ж��źŲ������䷵�ص���Ϣ��
  ����  ��
  ����ֵ  ��
************************************************************************/
VOID SM_SCDIntServeProc ( SINT32 ScdId);

/************************************************************************
  ԭ��  VOID SM_Wakeup ( VOID )
  ����  ���������ڻ���SMģ�飬����SMͣ�����޷��ָ����С�
      ��������̼߳��SCD��������߳���ÿ����һ֡���ô˺�����
      ������ö�ʱ�жϼ��SCD�����ڶ�ʱ�ж��е��ô˺�����
  ����  ��
  ����ֵ  ��
************************************************************************/
VOID SM_Wakeup ( VOID );
VOID  SM_SimpleEntry(VOID);

/************************************************************************
  ԭ��  VOID SM_GetBasePhyVir(SINT32 SmID, SINT32 *pBasePhyAddr, UINT8 **pBaseVirAddr)
  ����  ���Ի������ַ��������ַ
  ����  ��
  ����ֵ  ����������ַ
************************************************************************/
VOID SM_GetBasePhyVir(SINT32 SmID, SINT32 *pBasePhyAddr, UINT8 **pBaseVirAddr);

/************************************************************************
  ԭ��  UINT8 *SM_PhyToVir(SINT32 BasePhyAddr, UINT8 *pBaseVirAddr, SINT32 PhyAddr)
  ����  �����ַת�������ַ
  ����  ��
  ����ֵ  ����������ַ
************************************************************************/
UINT8 *SM_PhyToVir(UADDR PhyAddr);

/************************************************************************
ԭ��  UINT8 *SM_ScdPhyToVir(SINT32 BasePhyAddr, UINT8 *pBaseVirAddr, SINT32 PhyAddr)
����  �����ַת�������ַ
����  ��
����ֵ  ����������ַ
************************************************************************/
UINT8 *SM_ScdPhyToVir(UADDR BasePhyAddr, UINT8 *pBaseVirAddr, UADDR PhyAddr);

/************************************************************************
ԭ��  VOID PrintScdRawState()
����  ��ӡRaw���е���ϸ���
����
����ֵ  ��
************************************************************************/
VOID PrintScdRawState(SINT32 SmID, SINT32 PrintDetail);

/************************************************************************
ԭ��  VOID PrintScdSegState()
����  ��ӡSeg���е���ϸ���
����
����ֵ  ��
************************************************************************/
VOID PrintScdSegState(SINT32 SmID, SINT32 PrintDetail);
/************************************************************************
ԭ��  VOID PrintScdVtrlReg()
����  ��ӡScd���ƼĴ�������
����
����ֵ  ��
************************************************************************/
VOID PrintScdVtrlReg(SINT32 ScdId);

/************************************************************************
ԭ��  VOID PrintScdVtrlReg()
����  ��ӡ������Ϣ��
����
����ֵ  ��
************************************************************************/
VOID PrintDownMsg(UADDR DownMsgPhyAddr, SINT32 * pDownMsgVirAddr, SINT32 PushRawNum,SINT32 ScdId);

/************************************************************************
ԭ��  VOID PrintScdStateReg()
����  ��ӡScd״̬�Ĵ�������
����
����ֵ  ��
************************************************************************/
VOID PrintScdStateReg(SM_STATEREG_S *pSmStateReg, SINT32 ScdId);

/************************************************************************
ԭ��  VOID PrintScdInputRaw()
����  ��ӡRaw����
����
����ֵ  ��
************************************************************************/
VOID PrintScdInputRawAfterStart(UINT8 *pDownMsgVirBaseAddr, UADDR DownMsgPhyBaseAddr,
                                UINT8 *pRawBufVirBaseAddr,  UADDR RawBufPhyBaseAddr,
                                VOID *fpStream);
SINT32 SM_SeekPts(SINT32 ChanID, UINT64 *pArgs);
SINT32 SM_AllocDSPCtxMem(SINT32 SmID);
VOID SM_DeletDSPCtxMem(MEM_RECORD_S *pstDSPMem);
VOID WriteHexFile(SINT32 eVidStd, SINT32 ScdId);

/***********************************************************************
SCDDRV_MarkReloadDsp: �ú������Ա�ǵ�ǰDSP������Ҫ���أ�
                      ������ʱ��SCD�ж�
SmID : 1)����=-1ʱ����ʾ�����ʵ����صı������б�ʶ
��ע:��Ҫ��SCD�ж�����DSP���룬��Դ�ڵ�ǰDSP�м��ص���Lowdelay������룬
     ��Ҫ��SCD��ʱ�������أ�������������
     add by sdk
 ***********************************************************************/
VOID SCDDRV_MarkReloadDsp(SINT32 ScdId, SINT32 SmID);

VOID SM_UpdateMatchMode(SINT32 ScdId, SINT32 SmID);

UINT32 get_scd_msg_size(VOID);

#endif  // __SCD_DRV_H__
