#ifndef __VFMV_CTRL_H__
#define __VFMV_CTRL_H__

#include "vfmw.h"
#include "fsp.h"
#include "sysconfig.h"
#include "syntax.h"
#ifdef ENV_SOS_KERNEL
#include "vfmw_tee_client.h"
#endif

/*======================================================================*/
/*  常数                                                                */
/*======================================================================*/
#define VCTRL_OK                (0)
#define VCTRL_ERR               (-1)
#define VCTRL_ERR_VDM_BUSY      (-2)
#define VCTRL_ERR_NO_FSTORE     (-3)
#define VCTRL_ERR_NO_STREAM     (-4)

#define MAX_FRAME_SIZE          (2048*2048)

#define VCTRL_FIND_PTS          (0)
#define VCTRL_PTS_ILLEAGLE      (-1)
#define VCTRL_SEEKING_PTS       (-2)

#define VCTRL_ADD_EXTRA         (1)
#define VCTRL_IGNOR_EXTRA       (2)

#define MAX_USRDEC_FRAME_NUM    (16)

// time record pos
#define THREAD_START            (0)
#define THREAD_END              (1)

#define SEGCOPY_START           (2)
#define SEGCOPY_END             (3)

#define MAP_START               (4)
#define MAP_END                 (5)

#define SYNTAX_START            (6)
#define SYNTAX_END              (7)

#define VDH_START               (8)
#define VDH_END                 (9)

#define ISR_START               (9)
#define ISR_END                 (10)

#define NEXT_THREAD_START       (11)

#define COPY_SIZE_DATA          (0)
#define VDH_DATA                (1)

#define MAX_RECORD_NUM          (15)

#define MAX_RECORD_POS          (12)   //TIME
#define MAX_RECORD_DATA         (2)    //DATA

/*======================================================================*/
/*  结构与枚举                                                          */
/*======================================================================*/
/* 通道相关的统计信息 */
typedef struct hiVFMW_CHAN_STAT
{
    UINT32        u32FrBeginTime;     /* 计算帧率的开始时间 */
    UINT32        u32FrImgNum;        /* 帧数 */
    UINT32        u32FrFrameRate;     /* 帧率 */

    /* 丢帧统计 */
    UINT32        u32SkipFind;        /* 解到的skip帧数目 */
    UINT32        u32SkipDiscard;     /* 丢弃不解的skip帧数目 */
    UINT32        u32IsFieldFlag;     /* 当前插入队列中的帧是场图标志，用于PVR快进快退获取码流帧场属性 */
} VFMW_CHAN_STAT_S;

typedef struct hiVFMW_GLOBAL_STAT
{
    /* VDM占用率统计 */
    UINT32        u32VdhStatisticStartTimeInMs; /* 统计VDM占用率的起始时间 */
    UINT32        u32VdhLastStartTimeInMs;      /* 上一次启动硬件的时间 */
    UINT32        u32VdhWorkTimeInMs;           /* VDM累计工作时间 */
    UINT32        u32VdhCycleTime;              /* 通过Cycle统计的VDM累计工作时间 */
    UINT32        u32VdhLoad;                   /* VDM占用率 */
    UINT32        u32VdhCycleLoad;              /* 通过Cycle统计的VDM占用率 */
    UINT32        u32VdhIrqPerSec;              /* VDM 每秒中断数 */

    /* VDM性能数据统计 */
    UINT32        u32PicNum;
    UINT32        u32AccountVdhKiloCycle;
    UINT32        u32VdhKiloCyclePerSecond;
    UINT32        u32Period;
    /* SCD占用率统计 */
    UINT32        u32ScdBeginTime;              /* 统计SCD占用率的起始时间 */
    UINT32        u32ScdLastStartTime;          /* 上一次启动硬件的时间 */
    UINT32        u32ScdWorkTime;               /* SCD累计工作时间 */
    UINT32        u32ScdLoad;                   /* SCD占用率 */

} VFMW_GLOBAL_STAT_S;

/* ArrangeMem函数调用传递的指示符类型 */
typedef enum
{
    CAP_HEVC_SPECIFIC     = -2,
    INVALID_CHAN_ID       = -1,
    VALID_CHAN_ID_START   = 0,
} ARRANGE_FLAG_E;

typedef enum
{
    VDM_SUPPORT_VP6       = 1,  /* 1<<0 */
    VDM_SUPPORT_BPD       = 2,  /* 1<<1 */
    VDM_SUPPORT_VCMP      = 4,  /* 1<<2 */
    VDM_SUPPORT_GMC       = 8,  /* 1<<3 */
    VDM_SUPPORT_DNR       = 16  /* 1<<4 */
} VDM_CHARACTER_E;

/* 线程的状态 */
typedef enum hiTASKSTATE_E
{
    TASK_STATE_EXIT = 0,        /* 退出, 线程未创建或已销毁 */
    TASK_STATE_STOP,            /* 停止，线程已创建，但在空转，解码停止 */
    TASK_STATE_RUNNING,         /* 运行 */
    TASK_STATE_BUTT
} TASK_STATE_E;

/* 对线程发出的指令 */
typedef enum hiTASKCMD_E
{
    TASK_CMD_NONE = 0,          /* 无指令 */
    TASK_CMD_START,             /* 启动指令：启动处于停止状态的线程 */
    TASK_CMD_STOP,              /* 停止指令：停止处于运行状态的线程 */
    TASK_CMD_KILL,              /* 销毁指令：使处于运行或停止状态的线程自然退出 */
    TASK_CMD_BUTT
} TASK_CMD_E;

/* 通道的解码核心 */
typedef enum hiChanDecCore
{
    DEC_CORE_VDM,
    DEC_CORE_IMEDIA_H263,
    DEC_CORE_IMEDIA_SORENSON,
    DEC_CORE_BUTT
} CHAN_DEC_CORE_E;

/* 最后一帧状态跟踪 */
typedef enum hiLastFrameState
{
    LAST_FRAME_INIT = 0,
    LAST_FRAME_RECEIVE,
    LAST_FRAME_REPORT_SUCCESS,
    LAST_FRAME_REPORT_FAILURE,
    LAST_FRAME_REPORT_FRAMEID,
    LAST_FRAME_BUTT
} LAST_FRAME_STATE_E;

/*通道控制状态*/
typedef enum
{
    CHAN_NORMAL,
    CHAN_FRAME_STORE_ALLOC,
    CHAN_DESTORY,
} VFMW_CHANNEL_CONTROL_STATE_E;

typedef struct hiDRV_MEM_S
{
    MEM_RECORD_S  stVdmHalMem[MAX_VDH_NUM];      /* VDM HAL内存 */
    MEM_RECORD_S  stScdCmnMem[MAX_SCD_NUM];      /* SCD 公共内存 */
#ifdef VFMW_VP9_SUPPORT
//#ifndef ENV_SOS_KERNEL
    MEM_RECORD_S  stVp9ProbMem[MAX_VDH_NUM];     /* VP9 概率表内存 */
//#endif
#endif
    MEM_DESC_S    stExtHalMem;                   /* 支持外部配hal层内存*/
    MEM_RECORD_S  stVdmReg[MAX_VDH_NUM];
    MEM_RECORD_S  stFodReg;
    MEM_RECORD_S  stScdReg[MAX_SCD_NUM];
    MEM_RECORD_S  stBpdReg;
    MEM_RECORD_S  stSystemReg;                   /* 系统寄存器，比如复位FOD,VDM,SCD等 */
} DRV_MEM_S;

typedef struct hiDRV_IRQ_RECORD_S
{
    SINT32 VdhIrq[MAX_VDH_NUM];
    SINT32 ScdIrq[MAX_SCD_NUM];
    SINT32 vdh_mmu_irq[MAX_VDH_NUM];
} DRV_IRQ_RECORD_S;

/*压缩参数*/
typedef struct hi_VFMW_CHAN_CMP_PARA
{
    UINT32 VCmpEnable;
    UINT32 LossCmpEnable;
    UINT32 YCmpRatio;
    UINT32 UVCmpRatio;
} VFMW_CHAN_CMP_PARA_S;

/* 解码器控制数据集 */
typedef struct hiVFMW_CTRL_DATA_S
{
    SINT32        s32IsVCTRLOpen;        /* 标志VCTRL是否被全局打开 */
    TASK_STATE_E  eTaskState;            /* 线程状态 */
    TASK_CMD_E    eTaskCommand;          /* 线程指令 */
    VOID *hThread;                       /* 线程句柄 */
    SINT32        s32ThreadPos;          /* 线程位置 */
    SINT32        s32ThisChanIDPlus1;    /* 当前正在进行语法解码的通道号 */
    DRV_MEM_S     stDrvMem;
    SINT32        (*event_report_vdec)(SINT32 ChanID, SINT32 type, VOID *p_args );
    SINT32        (*event_report_omxvdec)(SINT32 ChanID, SINT32 type, VOID *p_args );
    DRV_IRQ_RECORD_S stIrqRecord;
} VFMW_CTRL_DATA_S;

typedef struct hiVFMW_CHAN_FRM_BUF_S
{
    MEM_RECORD_S stFrameBuffer;
    UINT8 u8BufferNodeState; //0:预分配得到的节点, 1:动态分配得到的节点,0xFF:空闲节点
} VFMW_CHAN_FRM_BUF_S;
/* 解码通道内存记录 */
typedef struct hiVFMW_CHAN_MEM_S
{
    MEM_RECORD_S        *pChanMem_vdh;             /* 指向该通道的帧存存储资源 */
    MEM_RECORD_S        *pChanMem_scd;             /* 指向该通道的SCD存储资源 */
    MEM_RECORD_S        *pChanMem_ctx;             /* 指向该通道的上下文存储资源 */
    FRAME_BUF_S         *pChanMem_frm;             /* 指向该通道帧存存储资源*/
    MEM_RECORD_S        *pChanMem_es;

    UINT32               u32DynamicAllocEn;        /* 是否为动态帧存方式l00273086*/
    SINT32               s32SelfAllocChanMem_vdh;  /* 标识通道 vdh 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32               s32SelfAllocChanMem_scd;  /* 标识通道 scd 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32               s32SelfAllocChanMem_ctx;  /* 标识通道 ctx 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32               s32SelfAllocChanMem_rpu;  /* 标识通道 HDR metadata 是否是自己分配的，1: 自己分配, 0: 外部分配 */
} VFMW_CHAN_MEM_S;
typedef struct hiVFMW_MEM_ARRANGE_INFO_S
{
    VDMHAL_MEM_ARRANGE_S stMemArrange;
    SINT32 ImgSlotLen;
    SINT32 PmvSlotLen;
    SINT32 ExpectImgLen;
    SINT32 HdrMetadataLen;
} VFMW_MEM_ARRANGE_INFO_S;

typedef struct hiVFMW_DYNAMIC_FS_TIMESTAMP_S
{
    UINT32 u32StartTime;
    UINT32 u32PreEndTime;
    UINT32 u32MMZEndTime;
    UINT32 u32PreAllocTime;
    UINT32 u32MMZAllocTime;
    UINT32 u32AllTime;
} VFMW_DYNAMIC_FS_TIMESTAMP_S;

/* 解码通道 */
typedef struct hiVFMW_CHAN_S
{
    SINT32         s32ChanID;       /* 通道ID */
    SINT32         s32IsOpen;       /* 0: 未打开，1: 打开 */
    SINT32         s32IsRun;        /* 0: 不被调度, 1: 运行，可被调度  */
#ifdef VFMW_VPSS_BYPASS_EN
    SINT32         s32IsImgOutputEn; /*0: Image 输出不使能，1:Image 输出使能*/
#endif
    SINT32         s32IsInit;       /* 0: 正常解码状态, 1: 刚初始化，未解码*/
    SINT32         s32Priority;     /* 优先级，0：最低优先级(从不调度) ~ 255(最高优先级，最优先调度) */
    SINT32         s32StopSyntax;   /* 停掉syntax解码，用于在stop通道的时候先停上游，让下游自由运行，把已生成
                                        的DecParam消耗干净，从而实现安全的通道stop和reset操作 */
    SINT32         MatchVdhIdPlus1;  //记录当前通道匹配的Vdhid +1; -1->该通道DSP处理部分未就绪，不能处理；0->随机使用VDH解码；1->固定选用VDH0解码；2->固定选用VDH1解码...;
    VDEC_ADAPTER_TYPE_E   eAdapterType;   /* 指示该通道是由vdec/omxvdec创建 */
    VDEC_CHAN_CAP_LEVEL_E eChanCapLevel;  /* 通道的能力级别 */
    UINT32         u32timeLastDecParamReady;

    VDEC_CHAN_CFG_S stChanCfg;       /* 保存用户配置，便于查询接口实现 */
    STREAM_INTF_S  stStreamIntf;     /* 码流接口 */
    IMAGE_INTF_S   stImageIntf;      /* 图象接口 */
    FRAME_INTF_S   stFrameIntf;

    SINT32         s32SCDInstID;     /* 该通道对应的SCD实例ID */
    SINT32         s32VDMInstID;     /* 该通道对应的VDM实例ID */
    MEM_RECORD_S   stChanMem_vdh;    /* 该通道的帧存存储资源 */
    MEM_RECORD_S   stChanMem_scd;    /* 该通道的SCD存储资源 */
    MEM_RECORD_S   stChanMem_ctx;    /* 该通道的上下文存储资源 */
    MEM_RECORD_S   stChanMem_es;     /* recorde es buf */

    SINT32         s32SelfAllocChanMem_vdh;  /* 标识通道 vdh 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32         s32SelfAllocChanMem_scd;  /* 标识通道 scd 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32         s32SelfAllocChanMem_ctx;  /* 标识通道 ctx 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32         s32SelfAllocChanMem_rpu;  /* 标识通道 HDR metadata 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    UADDR          s32VdmChanMemAddr;
    SINT32         s32VdmChanMemSize;    /* VDM通道所占据的存储空间大小 */
    UADDR          s32ScdChanMemAddr;
    UADDR          s32SdecMemAddr;       /* 软解码所使用的存储空间，为DNR+VDM的空间 */
    SINT32         s32SdecMemSize;
    SINT32         s32ScdChanMemSize;    /* SCD通道所占据的存储空间大小 */

    UADDR          s32BpdChanMemAddr;
    SINT32         s32BpdChanMemSize;    /* BPD通道所占据的存储空间大小 */

    UADDR          s32Vp8SegIdChanMemAddr;
    SINT32         s32Vp8SegIdChanMemSize;    /* SegId通道所占据的存储空间大小 */

    UADDR          s32Vp9SegIdChanMemAddr;
    SINT32         s32Vp9SegIdChanMemSize;    /* SegId通道所占据的存储空间大小 */

    IMAGE_FORMAT   stRecentImgformat;
    FRAME_PACKING_TYPE_E  stRecentImgPackingType;

    SINT32         s32NoStreamFlag;        /* 由于该通道没有足够码流导致未能生成解码参数decparam */
    LAST_FRAME_STATE_E eLastFrameState;    /* 描述最后一帧标记的状态 */

    SINT32         s32CountNoDecparamFlag; /* 发现没有解码参数后开始计时标志 */
    UINT32         u32NoDecparamStartTime;

    /* 用户态解码需要把VDM memory按帧映射上去. 创建时形成分割，以下信息记录帧存的分割和使用状况 */
    UADDR          s32UsrdecFramePhyAddr[MAX_USRDEC_FRAME_NUM];
    SINT32         s32UsrdecFrameSize;
    SINT32         s32UsrdecFrameNum;
    USRDEC_FRAME_DESC_S  stRecentUsrdecFrame;

    VID_STD_E      eVidStd;

    SYNTAX_EXTRA_DATA_S stSynExtraData;
    SINT32   s32FrameRate;
    CHAN_DEC_CORE_E eDecCore;
    SM_INSTANCE_S   SmInstArray;
    FSP_INST_S      FspInst;
    SINT32 AllocFrameOnly;

    SINT32 s32CurFsSize;
    SINT32 s32RefNum;
    SINT32 s32NeededFrameNum;//记录vdec配置给vfmw的总共的帧存个数
    SINT32 s32PreAllocFrmNum;
    SINT32 s32MMZFrmNum;
    SINT32 s32RefNumChanged;
    SINT32 s32SendStreamAgainFlag;
    FRAME_BUF_S stFrmBuf[MAX_FRAME_NUM];
    VFMW_MEM_ARRANGE_INFO_S stMemArrangeInfo;
    VFMW_DYNAMIC_FS_TIMESTAMP_S stDynamicFSTimestamp;

    UINT32 CfgFrameNum;
    UINT32 isFilledMemArrnageInfo;

#ifdef VFMW_VPSS_BYPASS_EN
    VFMW_SPECIAL_FRAME_REC_S specialFrmRec[VFMW_MAX_RESERVE_NUM + 1];
    UINT32 specialFrameNum;
#else
    UADDR  specialFramePhyAddr;
    UINT64 specialFrameVirAddr;
    UINT8  specialFrameNodeStatus;
    UINT32 specialFrameSize;
    UINT32 specialFrameExist;
#endif

    SINT32 resolutionChanged;
    SINT8  isMiracastChan;
    UINT32 u32DynamicFrameStoreAllocEn;
    UINT32 u32CurSavePicBitDepth;
    UADDR  ChanUniquelyID;
    SINT32 s32H264Score;
    SINT32 s32Mpeg2Score;
    SINT32 s32FindStartCodeCnt;
    SINT32 s32LastTwoStartCode;
    SINT32 s32LastOneStartCode;
    SINT32 s32CurrentStartCode;
    SINT32 s32ScdInputMmuEn;
    UINT32 DecodeFrameNumber;
    UINT32 OutputFrameNumber;
    VBOOL  AndroidTest;
    SINT32 IsNVRMode;
    VBOOL  bWakeUpDecThread;
    SYNTAX_CTX_S   stSynCtx;//此成员必须放在最后一个定义,创建通道时即使mvc support，但是配置的能力集不是mvc相关的，该结构体内存也只分配次大的CTX所需，以达到内存裁剪目的。

} VFMW_CHAN_S;

/* 线程的状态 */
typedef enum hiDSPSTATE_E
{
    DSP_STATE_NORMAL = 0,      /* DSP 还没有加载任何代码  */
    DSP_STATE_SCDLOWDLY,       /* DSP 已经加载了SCD低延的代码，说明已有一个通道处于低延迟模式 */
    DSP_STATE_AVS,             /* DSP 已经加载了AVS+的代码，说明已有一个通道正在跑AVS协议 */
    DSP_STATE_BUTT
} DSP_STATE_E;

/*======================================================================*/
/*  全局变量                                                            */
/*======================================================================*/
extern VFMW_CHAN_STAT_S g_VfmwChanStat[MAX_CHAN_NUM];
extern VFMW_GLOBAL_STAT_S g_VfmwGlobalStat[MAX_VDH_NUM];
extern SINT32 g_VdmCharacter;
extern VDM_VERSION_E g_eVdmVersion;
extern SINT32  (*AcceleratorCharacter)(DECPARAM_INF_S *pDecParamInfo);

/*======================================================================*/
/*  函数申明                                                            */
/*======================================================================*/
SINT32 VCTRL_OpenVfmw(VDEC_OPERATION_S *pArgs);
SINT32 VCTRL_SetCallBack(VDEC_ADAPTER_TYPE_E eType, SINT32 (*event_report)(SINT32 ChanID, SINT32 type, VOID *p_args));
SINT32 VCTRL_StopTask(VOID);
SINT32 VCTRL_StartTask(VOID);
SINT32 VCTRL_CloseVfmw(VOID);
VOID   VCTRL_Suspend(VOID);
VOID   VCTRL_Resume(VOID);
SINT32 VCTRL_CreateChan(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, SINT32 flag, SINT32 OneChanMemFlag);
SINT32 VCTRL_DestroyChan(SINT32 ChanID);
SINT32 VCTRL_StartChan(SINT32 ChanID);
SINT32 VCTRL_StopChan(SINT32 ChanID);
SINT32 VCTRL_StopChanWithCheck(SINT32 ChanID);
SINT32 VCTRL_GetChanCfg(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_ConfigChan(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_ResetChanWithOption(SINT32 ChanID, VDEC_CHAN_RESET_OPTION_S *pOption);
SINT32 VCTRL_ReleaseStream(SINT32 ChanID);
SINT32 VCTRL_ResetChan(SINT32 ChanID);
VOID   VCTRL_GetChanState(SINT32 ChanID, VDEC_CHAN_STATE_S *pstChanState);
SINT32 VCTRL_SetSendStreamAgainFlag(SINT32 ChanID, SINT32 flag);
SINT32 VCTRL_GetSendStreamAgainFlag(SINT32 ChanID);
SINT32 VCTRL_SetStreamInterface(SINT32 ChanID, VOID *pstStreamIntf);
STREAM_INTF_S* VCTRL_GetStreamInterface(SINT32 ChanID);
SINT32 VCTRL_GetChanMemSize(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, DETAIL_MEM_SIZE *pDetailMemSize, SINT32 flag);
SINT32 VCTRL_GetStreamSize(SINT32 ChanID, SINT32 *pArgs);
SINT32 VCTRL_SetDiscardPicParam(SINT32 ChanID, VDEC_DISPIC_PARAM_S *pArgs);
VID_STD_E VCTRL_GetVidStd(SINT32 ChanId);
VOID   VCTRL_GetHDRConfigInfo(SINT32 ChanId, HDR_INPUT_S *pstHDRInput);
VOID*  VCTRL_GetDecParam(SINT32 ChanId);
VOID   VCTRL_VdmPostProc(SINT32 ChanId, SINT32 ErrRatio, LUMA_INFO_S *pLumaInfo, SINT32 VdhId);
SINT32 VCTRL_GetChanImage(SINT32 ChanID, IMAGE *pImage);
SINT32 VCTRL_ReleaseChanImage(SINT32 ChanID, IMAGE *pImage);
SINT32 VCTRL_RunProcess(VOID);
VOID   VCTRL_ExtraWakeUpThread(VOID);
SINT32 VCTRL_GetImageBuffer(SINT32 ChanId);
SINT32 VCTRL_GetChanIDByCtx(VOID *pCtx);
SINT32 VCTRL_GetChanIDByMemAddr(UADDR PhyAddr);
SINT32 VCTRL_IsChanActive(SINT32 ChanID);
VOID   VCTRL_GetChanImgNum(SINT32 ChanID, SINT32 *pRefImgNum, SINT32 *pReadImgNum, SINT32 *pNewImgNum);
VDEC_CHAN_CAP_LEVEL_E VCTRL_GetChanCapLevel(SINT32 ChanID);
SINT32 VCTRL_SetMoreGapEnable(SINT32 ChanID, SINT32 MoreGapEnable);
SINT32 VCTRL_SeekPts(SINT32 ChanID, UINT64 *pArgs);
SINT32 VCTRL_ConfigFFFBSpeed(SINT32 ChanID, SINT32 *pArgs);
SINT32 VCTRL_ConfigPVRInfo(SINT32 ChanID, VFMW_CONTROLINFO_S *pArgs);
SINT32 VCTRL_SetDbgOption (UINT32 opt, UINT8 *p_args);
SINT32 VCTRL_GetChanWidth(SINT32 ChanID);
SINT32 VCTRL_GetChanHeight(SINT32 ChanID);
VOID   VCTRL_SetVdecExtra(SINT32 new_extra_ref, SINT32 new_extra_disp);
VOID   VCTRL_SetLastFrameState(SINT32 ChanID, LAST_FRAME_STATE_E eState);
SINT32 VCTRL_OutputLastFrame(SINT32 ChanId);
VOID   VCTRL_SvdecLastFrame(SINT32 ChanId, UINT32 LastFrameID);
SINT32 VCTRT_SetChanCtrlState(SINT32 ChanID, VFMW_CHANNEL_CONTROL_STATE_E ChanCtrlState);
SINT32 VCTRL_AllocMemToDecoder(SINT32 ChanID, FRAME_BUF_S *FrameBuf);
VOID   VCTRL_ResetHardware(SINT32 ChanID);
VOID   VCTRL_OpenHardware(SINT32 ChanID);
VOID   VCTRL_CloseHardware(SINT32 CurChanID);
SINT32 DelAllFrameMemRecord(SINT32 ChanID, FRAME_BUF_S *pFrmBuf);
IMAGE_VO_QUEUE* VCTRL_GetChanVoQue(SINT32 ChanID);
UINT32 VCTRL_GetFsSize(SINT32 ChanId, SINT32 Width, SINT32 Height);
VOID   VCTRL_EnableEsBuf(SINT32 ChanID);
VOID   VCTRL_DisableEsBuf(SINT32 ChanID);
SINT32 VCTRL_IfEsBufEnable(SINT32 ChanID);
VOID   VCTRL_ClearDecparam(SINT32 ChanId);
VOID   VCTRL_RecordPosTime(UINT32 pos);
VOID   VCTRL_RecordData(UINT32 pos, UINT32 Data);
VOID   VCTRL_InformVdmFree(SINT32 ChanID);

#ifdef VFMW_USER_SUPPORT
SINT32 VCTRL_GetUsrdecFrame(SINT32 ChanID, USRDEC_FRAME_DESC_S *pUsrdecFrame);
SINT32 VCTRL_PutUsrdecFrame(SINT32 ChanID, USRDEC_FRAME_DESC_S *pUsrdecFrame);
SINT32 USERDEC_RecycleImage(USER_CTX_S *pCtx, UINT32 ImgID);
#endif

#if defined(VFMW_H264_SED_ONLY_SUPPORT) || defined(VFMW_HEVC_SED_ONLY_SUPPORT)
SINT32 VCTRL_CheckFreshRaw(SINT32 ChanID);
SINT32 VCTRL_CheckFreshSeg(SINT32 ChanID);
VOID   VCTRL_VdmProcSedOnly(SINT32 ChanId, SINT32 VdhId);
UINT8  VCTRL_IsSedOnlyMode(VID_STD_E VidStd, VOID *pDecParam);
#endif

#if defined(VFMW_AVSPLUS_SUPPORT)
SINT32 VCTRL_LoadDspCode(SINT32 ChanID);
#endif

#ifdef ENV_SOS_KERNEL
SINT32 VCTRL_ParseCSD(OMX_TUNNEL_CSD *pcsd);
#endif

#ifdef VFMW_VPSS_BYPASS_EN
SINT32 VCTRL_ReportOccupiedFrame(SINT32 chanID, VDEC_SPECIAL_FRM_S *pSpecialFrmInfo);
SINT32 VCTRL_ImageOutputEnable(SINT32 chanID, SINT32 *pImgOutputEn);
SINT32 VCTRL_FindOccupiedFrame(SINT32 chanID);
#endif

#endif

