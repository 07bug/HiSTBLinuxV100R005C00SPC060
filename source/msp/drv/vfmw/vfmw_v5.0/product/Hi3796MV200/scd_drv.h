#ifndef __SCD_DRV_H__
#define __SCD_DRV_H__

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
#define SCD_TIMEOUT     (20000)
#endif

#ifdef CFG_SCD_BUF
#define SCD_MSG_BUFFER  (CFG_SCD_BUF)
#else
#define SCD_MSG_BUFFER  (700*1024)  // ���ӳ����貿�ֿռ�������һ�����
#endif

extern UADDR  s_ScdRegPhyBaseAddr[MAX_SCD_NUM];
extern UADDR  s_ScdRegResetPhyAddr[MAX_SCD_NUM];
extern UADDR  s_ScdRegResetOKPhyAddr[MAX_SCD_NUM];

#define  WR_SCDREG(id,reg,dat)   MEM_WritePhyWord((s_ScdRegPhyBaseAddr[id] + reg),(dat))
#define  RD_SCDREG(id,reg)       MEM_ReadPhyWord((s_ScdRegPhyBaseAddr[id] + reg))

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
    SCDDRV_SLEEP_STAGE_SLEEP,         // ������
    SCDDRV_SLEEP_STAGE_BUTT
} SCDDRV_SLEEP_STAGE_E;

/* control registers */
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

#define REG_PREVIOUS_BYTE_LSB      0x83c
#define REG_PREVIOUS_BYTE_MSB     0x844

#define  REG_SCD_NUM          0x84c
#define  REG_ROLL_ADDR        0x850
#define  REG_SRC_EATEN        0x854

#define REG_SEG_BUFFER_OFFSET    0x858
#define REG_SEG_NEXT_ADDR     0x85c

#define  REG_DSP_SPS_MSG_ADDRESS      0x828
#define  REG_DSP_PPS_MSG_ADDRESS      0x82c
#define  REG_DVM_MSG_ADDRESS           0x830
#define  REG_SED_TOP_ADDRESS           0x834
#define  REG_CA_MN_ADDRESS             0x838

#define  REG_SCD_CLK_CFG      0x880

#define  REG_AVS_FLAG       0x0000
#define  REG_EMAR_ID        0x0004
#define  REG_VDH_SELRST        0x0008
#define  REG_VDH_ARBIT_CTRL_STATE             0X0010
#define  REG_VDH_CK_GT       0x000c
#define  REG_DSP_WATCH_DOG             0X0018

// ʵ��״̬
#define SM_INST_MODE_IDLE   0
#define SM_INST_MODE_WORK   1
#define SM_INST_MODE_WAIT   2

// ���޳���
#ifdef CFG_MAX_RAW_NUM
#define MAX_STREAM_RAW_NUM  CFG_MAX_RAW_NUM
#else
#define MAX_STREAM_RAW_NUM  (1024)
#endif

#ifdef CFG_MAX_SEG_NUM
#define MAX_STREAM_SEG_NUM  CFG_MAX_SEG_NUM
#else
#define MAX_STREAM_SEG_NUM  (4096)
#endif

#define MAX_STREAM_SEG_ALLOW    (100000)
#define MIN_STREAM_SEG_NUM      4  //��С����SCD����Ϣ�صĸ���
#define SM_SCD_UP_INFO_NUM      2
#ifdef SCD_MP4_SLICE_ENABLE
#define MAX_SM_SCD_UP_INFO_NUM  3  //MPEG4������Ϣ��ʹ��3��word������Э��ʹ��2��word��ȡ����
#else
#define MAX_SM_SCD_UP_INFO_NUM  SM_SCD_UP_INFO_NUM
#endif
#define SM_MAX_DOWNMSG_SIZE     (3*MAX_STREAM_RAW_NUM*sizeof(SINT32))
#define SM_MAX_UPMSG_SIZE       (SM_SCD_UP_INFO_NUM*MAX_STREAM_SEG_NUM*sizeof(SINT32))

#define DSP_SPS_MSG_SIZE        (32*8*4)
#define DSP_PPS_MSG_SIZE        (256*8*4)
#define DVM_SIZE                (2*64*4)
#define DSP_SED_TOP_SIZE        (64*4*1088)
#define CA_MN_SIZE              (64*4*1088)

#define SM_SEGWASTE_BUF_SIZE  64     //Segʣ��ռ��˷ѵĴ�С

//#define MIN_BTM_SEG_LEN  (2*1024)  // Ҫ��WORD������, �����������Ƶ�,������FPGA_SCD_SEG_BLANK_AHB_LEN
#define MIN_TOP_SEG_LEN  (1*1024)    // Ҫ��WORD�����������ܽ�ð��
#define SM_H263_THRESHOLD_NUM 30     //�������ٸ�H263ͷ���ֺ�����H263ģʽ

#define SM_RAW_DISCARD_SIZE    (1024*1024)

#define WAIT_SEG_REL_MAX_TIME   1000
#define WAIT_SCD_RDY_MAX_TIME   1000

#define SM_VIDOBJLAY_START_CODE        0x00000120
#define SM_VOP_START_CODE              0x000001b6
#define SM_SHORT_VIDEO_START_CODE      0x00008000

#define SEG_CUT_NORMAL   0
#define SEG_CUT_REPEAT   1
#define SEG_CUT_HALF     2

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

#define FMW_ASSERT_RET(cond, ret)                     \
    do{                                     \
        if (!(cond))                             \
        {                                   \
            return (ret);                           \
        }                                   \
    } while (0)

#define SMSEG_PHY2VIR(SegArrayPtr, phy, vir)                \
    do{                                     \
        (vir) = SegArrayPtr->pSegBufVirAddr + ((phy) - SegArrayPtr->SegBufPhyAddr); \
    } while (0)


typedef enum
{
    INITIALISE = 0,
    WRITE_DOWN_MSG = 1,
    IN_ISR = 2,
    SEEK_PTS = 3
} PUSH_RAW_OVER_STATE;

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
    UINT8    SliceCheckFlag;
    SINT8    ScdStart;
    UADDR    DownMsgPhyAddr;
    SINT32   *pDownMsgVirAddr;
    SINT32   *pUpMsgVirAddr;
    UADDR    UpMsgPhyAddr;
    SINT32   UpLen;
    UADDR    BufferFirst;
    UADDR    BufferLast;
    UADDR    BufferIni;
    UINT32   ScdProtocol;
    SINT32   ScdIniClr;
    UINT32   ScdLowdlyEnable;
    UINT32   ScdMmuEn;
    UINT32   VdhMmuEn;
    UINT32   ScdInputMmuEn;
    SINT32   reg_avs_flag;
} SM_CTRLREG_S;

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
    UINT32  StartCodeNum;
    UADDR   ScdRollAddr;
    SINT32  SrcEaten;
    UINT32  UpMsgLenInWord;
    UADDR  seg_next_addr;
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

typedef struct
{
    UINT8     *VirAddr;
    SINT8     SegState;
    SINT8     CutResult;
    UINT8     IsLastSeg;
    UINT8     IsStreamEnd;
    UINT8     DVDualLayer;
    UINT8     DspCheckPicOverFlag;
    UADDR     PhyAddr;
    UINT32    LenInByte;
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
    STREAM_SEG_S  StreamSeg[MAX_STREAM_SEG_NUM];
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
    UINT8        *pBufVirAddr;
    UINT8         Priority;
    VID_STD_E     VidStd;

    UADDR         BufPhyAddr;
    SINT32        BufSize;
    UADDR         RegPhyBaseAddr;
    STD_EXTENSION_U    StdExt;              /* ��չ��Ϣ��VC1��ص��������Ƿ�ΪAP �Ͱ汾��Ϣ*/
    SINT32        ScdLowdlyEnable;          /* 0: ���ӳ�δʹ��; 1: ���ӳ�ʹ�� */
    SINT32        SedOnlyEnable;
    SINT32        s32ChanLowlyEnable;
    SINT32        IsOmxPath;                /* 0: �ͻ���δʹ��; 1: �ͻ���ʹ�� */
    SINT32        IsTunneledPath;
    SINT32        MaxRawPacketNum;
    SINT32        MaxRawPacketSize;
    SINT32        s32ScdMmuEn;
    SINT32        s32VdhMmuEn;
} SM_CFG_S;

typedef struct
{
    UINT8        *pSegBufVirAddr;
    UINT32       *pDownMsgVirAddr;
    SINT32        DownMsgSize;
    UADDR         DownMsgPhyAddr;
    UINT32        *pUpMsgVirAddr;
    UADDR         UpMsgPhyAddr;
    SINT32        UpMsgSize;
    SINT32        UpMsgNum;
    UADDR         SegBufPhyAddr;
    SINT32        SegBufSize;
} SM_BUFFERCFG_S;

typedef struct
{
    SINT8         InstMode;        /* 0: �ǹ���ģʽ,  1: ����ģʽ   */
    SINT32        RawNum;          /* ԭʼ��������Ŀ                */
    SINT32        SegNum;          /* ԭʼ������������              */
    SINT32        TotalRawSize;    /* ���и������Ƭ����Ŀ          */
    SINT32        TotalSegSize;    /* ���и������Ƭ����������      */
    SINT32        numReadSegFail;  /* ����������seg�ļ���           */
} SM_INST_INFO_S;

typedef struct
{
    UINT8    *pCurrStartVirAddr;
    UINT8    *pCurrEndVirAddr;
    UADDR     CurrStartPhyAddr;
    UADDR     CurrEndPhyAddr;
    SINT32    Length;
    SINT32    TotalLen;
    UINT64    Pts;
} SM_PUSHRAWPACKET_S;

typedef struct
{
    SINT32  PushRawNum;
    SINT32  PushRawTotalLen;
    PUSH_RAW_OVER_STATE PushRawOverState;
} SM_PUSHRAW_S;

typedef enum
{
    SM_NOT_MPEG4 = 0,
    SM_MPEG4_NOTH263,
    SM_MPEG4_H263
} MPEG4_SUB_STD;

typedef struct
{
    UINT8    *pSegBufVirAddr; //Seg Buffer�������ַ,ȡ����ʱʹ��
    UINT32   *pScdUpMsg;      //�����˵�������Ϣ�ĵ�ַ
    SINT32    ProtocolType;
    SINT32    ModeFlag;       //0:�ڷ�Mpeg4ģʽ; 1:��һ�β���H263ģʽ, 2:��һ����H263ģʽ
    SINT32    LastH263Num;    //��һ�ν�������ΪH263ͷ������
    UADDR     SegBufPhyAddr;
    SINT32    SegBufSize;
    UADDR     SegBufRollAddr;
    SINT32    SegNum;         //�����˵�SegStream���ж��ٰ�
    SINT32    SMInstID;       //��ǰ����ʵ��ID
} SM_SEGSTREAMFILTER_S;

typedef struct
{
    SINT8          SegFullFlag;
    SINT8          IsCounting;
    SINT8          LastCfgAllRawFlag; // 1 : ��ʵ���ϴ�����SCDʱ�����е�RAW���������������ô����ñ�־λ��ÿ��SCD����ʱ�����жϸ�ֵ
    SINT8          FillNewRawFlag;    // 1 : ��ʵ���ϴ�SCD����������µ�RAW�������ñ�־λ����ÿ��SCD��������0
    VBOOL          IsSegBypass;
    SM_CFG_S       Config;
    RAW_ARRAY_S    RawPacketArray;
    SEG_ARRAY_S    StreamSegArray;
    SM_PUSHRAW_S   SmPushRaw;
    SM_BUFFERCFG_S BufAddrCfg;
    SINT32         InstID;
    SINT32         ScdID;            //��¼��ǰͨ���������SCD id�ţ�����SM_Stop�Ⱥ�����,������SCD�и�ǮҪ���¸�ֵ
    SINT32         CutingFlag;       //��¼��ǰͨ���Ƿ����ڱ�SCD�и��SM_SCDIntServeProc�жϴ���������0����CutStreamWithSCD����1
    SINT32         MatchScdIdPlus1;  //��¼��ǰͨ��ƥ���SCDid +1; -1->��ͨ��DSP������δ���������ܴ���0->���ʹ��SCD�и1->�̶�ѡ��SCD0�и2->�̶�ѡ��SCD1�и�...;
    SINT32         Mode;
    UINT32         Mpeg4ModeFlag;
    UINT32         LastH263Num;
    UINT32         BlockTimeInMs;    //��������ʱ�䣬��λms
    UINT32         LastBlockTime;    //��һ�α�������ʱ��(ϵͳʱ��)�����ں���ˢ������ʱ��
    UINT64         LastPts;          //������ε�Pts���ϴ���ͬ�����-1
    SINT32         PrevCfgRawSize;
    SINT32         PrevCfgSegSize;

    /* ͳ������ */
    SINT32         TotalRawSize;
    UINT32         LastStatTime;     //����ͳ�����ʵ�ʱ��
    UINT32         BitRate;          //����, ��λKbps

    /* ����ͳ����Ϣ */
    SINT32         numReadSegFail;
    SINT32         LastSCDStartTime; //�ϴ�����SCD�����ʱ�䣬��λ ����

    UINT32         UpMsgStepInWord;
    UINT32         u32RawSizeCount;
    UINT32         u32RawNumCount;
    SINT32         s32ChanLowlyEnable;

    UINT32         HeaderLen;
    UINT8          HeaderBuf[HEADER_BUFFER_SIZE];
    SINT32         s32ScdInputMmuEn;

    UINT16         pre_scd_previous_byte_msb;
    UINT32         pre_scd_previous_byte_lsb;

    UINT16         scd_previous_byte_msb;
    UINT32         scd_previous_byte_lsb; // near to the next seg

    UADDR         seg_next_addr;

    UINT32         first_start_scd_flag;

    UADDR          last_start_code_addr;
    UINT32         last_unfinished_seg_size;

    UINT32         roll_flag;
    UADDR          roll_addr;

    STREAM_SEG_S   last_unfinished_seg;
    UINT64         raw_msg_arr[MAX_STREAM_RAW_NUM][2];
} SM_INSTANCE_S;

typedef struct hiSCD_DRV_MEM_S
{
    UADDR          HwMemAddr;
    SINT32         HwMemSize;
    UINT32        *pDownMsgMemVirAddr;
    UADDR          DownMsgMemAddr;
    SINT32         DownMsgMemSize;
    SINT32        *pUpMsgMemVirAddr;
    UADDR          UpMsgMemAddr;
    SINT32         UpMsgMemSize;
    UADDR          ScdRegAddr;
    UADDR          ScdResetRegAddr;
} SCD_DRV_MEM_S;

typedef struct
{
    SCD_DRV_MEM_S       ScdDrvMem;
    SINT32              IsScdDrvOpen;
    SINT32              ThisInstID;
    SINT32              SCDState;
    UINT32              LastProcessTime;
    SINT32              DspReloadFlag;
} SMDRV_PARAM_S;

typedef struct
{
    SM_INSTANCE_S      *pSmInstArray;
    SINT32              SmInstPriority;
} SM_IIS_S;


SINT32 ResetSCD(SINT32 ScdId);
SINT32 DeleteRawPacketInBuffer(SINT32 SmID, SINT32 ResetFlag);
SINT32 GetRawStreamSize(RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamSize);
SINT32 GetRawStreamNum(RAW_ARRAY_S *pRawStreamArray, SINT32 *pStreamNum);
SINT32 GetSegStreamSize(SEG_ARRAY_S *pSegStreamArray, SINT32 *pStreamSize);
UINT32 GetSegStreamNum(SEG_ARRAY_S *pSegStreamArray);
VOID   GetFreshSegStream(SEG_ARRAY_S *pSegStreamArray, SINT32 *pFreshNum, SINT32 *pFreshSize);
SINT32 SM_OpenSCDDrv(UADDR MemAddr, SINT32 MemSize, SINT32 ScdId);
SINT32 SM_CloseSCDDrv(SINT32 ScdId);
VOID   SM_InstInit(VOID);
VOID   SCDDRV_ResetSCD(SINT32 ChanID);
SINT32 SM_ClearInst(SINT32 SmID);
SINT32 SM_Reset(SINT32 SmID);
SINT32 SM_Start(SINT32 SmID);
SINT32 SM_Stop(SINT32 SmID);
SINT32 SM_Config(SINT32 SmID, SM_CFG_S *pSmCfg);
SINT32 SM_GetInfo(SINT32 SmID, SM_INST_INFO_S *pSmInstInfo);
SINT32 SM_ReadSegStream(SINT32 SmID, STREAM_SEG_S *pStreamSeg);
SINT32 SM_ReleaseStreamSeg(SINT32 SmID, SINT32 StreamID);
VOID   SM_SCDIntServeProc(SINT32 ScdId);
VOID   SM_Wakeup(VOID);
VOID   PrintScdRawState(SINT32 SmID, SINT32 PrintDetail);
VOID   PrintScdSegState(SINT32 SmID, SINT32 PrintDetail);
SINT32 SM_SeekPts(SINT32 ChanID, UINT64 *pArgs);
VOID   SCDDRV_LoadDspCode(SINT32 ScdId, DSP_REQUIRE_E Require);
VOID   SCDDRV_SetStateIdle(SINT32 ScdId);
SINT32 SCDDRV_IsChanDec(SINT32 SmID);
VOID   SCD_ConfigReg(UINT32 Reg, UINT32 Data, SINT32 Id, VOID *pTask);
SINT32 SCDDRV_PrepareSleep(SINT32 ScdId);
VOID   SCDDRV_ForceSleep(SINT32 ScdId);
VOID   SCDDRV_ExitSleep(SINT32 ScdId);
SCDDRV_SLEEP_STAGE_E SCDDRV_GetSleepStage(SINT32 ScdId);

#endif  // __SCD_DRV_H__

