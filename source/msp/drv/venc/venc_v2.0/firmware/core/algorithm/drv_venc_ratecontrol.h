#include "drv_venc_buf_mng.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define RC_RECODE_USE   1
#define RC_FIRST_I_RECODE 0

#define GOP_THRESHOLD 1000
#define MODIFY_MINQP_FRAMENUM 200
#define ENLARGEMENT_FACTOR 6
#define MAX_INTER_LOADSIZE 5
#define MAX_INTRA_LOADSIZE 2

#define VENC_RC_FATAL(fmt...) //HI_FATAL_PRINT(HI_ID_VENC, fmt)
#define VENC_RC_ERR(fmt...) //HI_ERR_PRINT(HI_ID_VENC, fmt)
#define VENC_RC_WARN(fmt...) //HI_WARN_PRINT(HI_ID_VENC, fmt)
#define VENC_RC_INFO(fmt...) //HI_INFO_PRINT(HI_ID_VENC, fmt)
#define VENC_RC_DBG(fmt...) //HI_DBG_PRINT(HI_ID_VENC, fmt)

#ifdef VENC_UT_ENABLE
#define RC_PRIVATE
#else
#define RC_PRIVATE static
#endif

typedef struct
{
    HI_U32 GetFrameNumTry;
    HI_U32 PutFrameNumTry;
    HI_U32 GetStreamNumTry;
    HI_U32 PutStreamNumTry;

    HI_U32 GetFrameNumOK;
    HI_U32 PutFrameNumOK;
    HI_U32 GetStreamNumOK;
    HI_U32 PutStreamNumOK;
    HI_U32 CheckBufSizeNumFail;
    HI_U32 StartOneFrameFail;

    HI_U32 BufFullNum;
    //HI_U32 SkipFrmNum;
    HI_U32 FrmRcCtrlSkip;
    HI_U32 SamePTSSkip;
    HI_U32 QuickEncodeSkip;
    HI_U32 TooFewBufferSkip;
    HI_U32 ErrCfgSkip;
    HI_U32 TooManyBitsSkip;

    HI_U32 QueueNum;
    HI_U32 DequeueNum;                  /*OMX Channel not use this data*/
    HI_U32 StreamQueueNum;              /*just OMX Channel use this data*/
    HI_U32 MsgQueueNum;
    HI_U32 EtbCnt;
    HI_U32 EbdCnt;
    HI_U32 FtbCnt;
    HI_U32 FbdCnt;

    HI_U32 UsedStreamBuf;

    HI_U32 StreamTotalByte;

    HI_U32 u32RealSendInputRrmRate;       /*use to record curent Input FrameRate in use*/
    HI_U32 u32RealSendOutputFrmRate;      /*use to record curent Output FrameRate in use*/
    HI_U32 u32FrameType;

    HI_U32 u32TotalPicBits;
    HI_U32 u32TotalEncodeNum;
    HI_U32 RateControlRatio;           /*use to know whether the current bit rate is controlled*/
    HI_U32 RecodeNum;
} VeduEfl_StatInfo_S;

#define MOVE_JUDGE_SIZE     8
#define MOVE_JUDGE_INTRA    2
typedef struct
{
    HI_U32 skipFrame;
    HI_U32 MinQp;
    HI_U32 MaxQp;
    HI_U32 PicWidth;           /* done for 16 aligned @ venc */
    HI_U32 PicHeight;          /* done for 16 aligned @ venc */
    HI_U32 RcStart;

    HI_U32 CheckBufSize;
    HI_U32 PicBits;

    HI_U32 MeanQP;
    HI_U32 MhbBits;
    HI_U32 TxtBits;
    HI_U32 MadiVal;
    HI_U32 MadpVal;
    HI_U32 MinStillPercent;

    HI_U32 VoFrmRate;
    HI_U32 ViFrmRate;
    HI_U32 BitRate;
    HI_U32 Gop;
    HI_U32 IsIntraPic;
    HI_U32 RcnIdx;
    HI_U32 PmeInfoIdx;
    HI_U32 H264FrmNum;
    HI_U32 VencBufFull;
    HI_U32 VencPbitOverflow;
    HI_S32 LowDlyMod;
    HI_U32 bFrmRateSataError;
    HI_U32 IFrmInsertFlag;

    HI_U32 FrmNumInGop; //frame number in gop minus 1
    HI_U32 FrmNumSeq;//frame number in sequence

    /*******bits***********/
    HI_U64 GopBits;//bits in gop
    HI_U32 AverageFrameBits;//average bits of one frame

    // 统计前面若干帧  
    HI_BOOL IsAVBR;
    HI_U32 TarBitRate;
    HI_U32 TarGopBits;
    HI_U32 KBitsPerGop;
    HI_U32 MaxStillQP;

    HI_U32 u32MovementJudge[2][MOVE_JUDGE_SIZE];   // 0:  Intra;   1: Inter
    HI_S32 s32MovementJudgeQP[MOVE_JUDGE_SIZE];
    HI_U32 u32MovementJudgeMbh[MOVE_JUDGE_SIZE];
    HI_U32 u32MovementJudgeRes[MOVE_JUDGE_SIZE];
    HI_U32 u32ResPercent;
    HI_S32 s32LastPercent; // in [1, 255]

    HI_U32 u32MovementJudgeMadp[MOVE_JUDGE_SIZE];
    HI_U32 u32MovementJudgeMadi[MOVE_JUDGE_SIZE];
    
    HI_S32 s32GopPointer;
    HI_S32 s32GopSize;
    HI_U64 u64GopTotal;         // GOP based bitrate
    HI_U64 u64SecondTotal;    // frame based bitrate

    HI_S32 s32InstBitrate;   // 按整个gop计算的瞬时码率
    HI_S32 s32InstBitrate2;  // 按最近5帧计算的瞬时码率    

    // only for debug
    HI_S32 s32QPDelta0;
    HI_S32 s32QPDelta1;    
    HI_S32 s32QPDelta3;
    HI_S32 s32QPDelta4;
    HI_S32 s32QPDelta5;
    HI_U32 u32TarPercen3;
    HI_U32 u32TarPercen2;
    HI_U32 u32TarPercen;
    
    // every picure
    HI_U32 u32BitsStaticsGop[GOP_THRESHOLD];   // 存一个gop

    HI_U32 IPreQp;//Qp of previous six I frames
    HI_U32 PPreQP;
    HI_U32 PreTargetBits;
    HI_U32 PrePicBits;

    /*********IMB***********/
    HI_S32 NumIMBCurFrm;//number of I MB in current  frame
    HI_S32 NumIMB[6];//number of I MB of previous six frames
    HI_S32 AveOfIMB;//average number of I MB of previous six frames

    /**********scence change detect *************/
    HI_U32 IMBRatioCurScen[6];//number of I MB of previous six frames just for scence change judge

    /************RC Out**************/
    HI_U32 CurQp;
    HI_U32 TargetBits;
    HI_U32 StartQP;
    HI_U32 InitialQp;

    /**********parameter set************/
    HI_S32 MinTimeOfP;
    HI_S32 MaxTimeOfP;
    HI_S32 DeltaTimeOfP;
    HI_S32 IQpDelta;
    HI_S32 PQpDelta;

    HI_S32 CurTimeOfP[2];    //0:Intra    1:Inter
    HI_S32 IPQPDelta;
    HI_U32 WaterlineInit;
    HI_U32 Waterline;
    HI_U32 LastFrameTypeIsIntra;
    /**********I/P bits set************/
    HI_U32 IPicBits[2];
    HI_U32 PPicBits[5];
    HI_U32 IPicBitsHead;
    HI_U32 PPicBitsHead;

    HI_U32 RecodeCnt;         //1~n: frame need to be recoded(RecodeTime)   0: not need;
    HI_U32 ReStartQP;
    /**********instant bits set************/
    HI_U32 InstBits[65];     //the instant bitrate of last frame
    HI_U32 InstBitsLen;
    HI_U32 InstBitsSum;
    HI_U32 InstBitsHead;
    HI_U32 PreInstBitsSum;
    HI_U32 LastLen;
    HI_U32 LastGop;
    HI_U32 LastBitRate;
    /**********VBR set************/
    HI_BOOL IsVBRMode;
    HI_U32 VBR_SumOfQP;
    HI_S32 VBR_SumOfDeltaPicBits;
    HI_S32 LastSumOfDeltaPicBits;
    HI_U32 VBR_MinQP;
    HI_U32 VBR_MaxBitRate;

    HI_U32 LastSecFrameCnt;
    HI_U32 LastSecFrameCntForUsr;

} VeduEfl_Rc_S;

HI_S32 VENC_DRV_RcOpenOneFrm(VeduEfl_Rc_S *pstRc);
HI_S32 VENC_DRV_RcCloseOneFrm(VeduEfl_Rc_S *pstRc, VALG_FIFO_S *pstBitsFifo, HI_U32 *TrCount , HI_U32 *InterFrmCnt);
HI_S32 VENC_DRV_EflRcAverage(HI_S32* pData, HI_S32 n);
HI_VOID VEDU_DRV_RCUpdateInfo(VeduEfl_Rc_S* pstRc);
HI_S32 VEDU_DRV_RCIsNeedRecoding(VeduEfl_Rc_S* pstRc);
HI_S32 VEDU_DRV_RCStartQPChange(VeduEfl_Rc_S* pstRc);
HI_S32 VENC_DRV_CalRCRatio(HI_U32 CurInstBits, HI_U32 BitRate);

#ifdef VENC_UT_ENABLE
HI_VOID VEDU_DRV_RCofFirstFrame(VeduEfl_Rc_S* pstRc);
HI_U32  VEDU_DRV_EflRcInitQp(HI_U32 bits, HI_U32 w, HI_U32 h);
HI_S32 VEDU_DRV_RcModifyQPForLargeFrmBits(VeduEfl_Rc_S* pstRc);
HI_S32 VEDU_DRV_RCCalcQPDeltaByFrameBits(VeduEfl_Rc_S* pstRc);
HI_S32 VEDU_DRV_RCCalcQPDeltaByInstantBits(VeduEfl_Rc_S* pstRc);
HI_S32 VEDU_DRV_RCCalcQPDeltaByBitRate(HI_U32 u32CurInstBits, HI_U32 BitRate);
HI_S32 VEDU_DRV_RCCalcQPDeltaByWaterline(VeduEfl_Rc_S* pstRc);
HI_VOID VEDU_DRV_RCCalculateCurQP(VeduEfl_Rc_S* pstRc);
HI_S32 VEDU_DRV_RCUpdateFrameBits(VeduEfl_Rc_S* pstRc);
HI_S32 VEDU_DRV_RCCalcTimeOfP(VeduEfl_Rc_S* pstRc);
HI_VOID ModifyInfoForFrmRateChange(VeduEfl_Rc_S* pstRc);
HI_VOID VEDU_DRV_RCUpdateInstantBits(VeduEfl_Rc_S* pstRc);
HI_VOID VEDU_DRV_RCGetTargetFrameBits(VeduEfl_Rc_S* pstRc);
#endif


