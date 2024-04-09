
#ifndef __SYNTAX_COMMON_HEADER__
#define __SYNTAX_COMMON_HEADER__

//#include "basedef.h"
#include "vfmw.h"
#include "scd_drv.h"


/* ����ֵ�����������޸ģ������Ϊ��2�������ݣ�����С��64�������ܳ����� */
#define MAX_QUEUE_IMAGE_NUM    (64)

/* �����������ѡ��, ΪDecOrderOutput����ȡֵ */
#define NOT_DEC_ORDER          (0)
#define DEC_ORDER_NORMAL_DPB   (1)
#define DEC_ORDER_SIMPLE_DPB   (2)
#define DEC_ORDER_SKYPLAY      (3)

#define IMG_ID_MAGIC_STEP      (100)

/* MPEG2, MPEG4����ƴ����������ݽṹ */
typedef struct
{
    STREAM_SEG_S    StreamPack[2];  // for vfmw decode
} DEC_STREAM_PACKET_S;

typedef struct
{
    //     STREAM_SEG_S    StreamSeg[MAX_STREAM_SEG_NUM];
    //     UINT32          SegNum;
    UINT8           FoundPicFlag;
    UINT8           IsCurrSegWaitDec;
    UINT8           ConvolutionPacketNum;
    STREAM_SEG_S    CurrSeg;
    DEC_STREAM_PACKET_S    Pack;  // for vfmw decode
    DEC_STREAM_PACKET_S    LastPack;//sdk
    UINT8                  u32SCDWrapAround;//sdk
} STREAM_SEG_PACKET_S;

typedef struct hiIMAGE_SIDE_INFO_S
{
    UINT32     OldAspectRatio;
    UINT32     OldScanType;
    UINT32     OldSeqCnt;
    UINT32     OldFrameRate;
    UINT32     OldDispSize;
    UINT32     OldDispCenter;
    UINT32     LastImageIdPlus2;

    UINT32     ImageWidth;
    UINT32     ImageHeight;
    UINT32     VideoFormat;
    UINT32     ImageFormat;

    UINT32     SeqImgCnt;
    UINT32     SeqCnt;

    /* time stamp calculation */
    UINT32     PrevNumFramesBtwPTS;
    UINT64     PrevPts;
    UINT64     AveragePtsStep;  /* smoothed by a FIR filter */

} IMAGE_SIDE_INFO_S;

/* video output queue(VO queue)  */
typedef struct
{
    UINT16     max_queue_size;
    UINT16     queue_size;
    UINT16     history;
    UINT16     head;
    UINT16     tail;
    IMAGE      *image_ptr[MAX_QUEUE_IMAGE_NUM];
    IMAGE_SIDE_INFO_S  SideInfo;
    UINT32     ResetMagicWord;
} IMAGE_VO_QUEUE;


typedef struct hiSYNTAX_EXTRA_DATA_S
{
    SINT32     s32RefErrThr;
    SINT32     s32OutErrThr;
    SINT32     s32DecMode;   /* 0,1,2 = IPB,IP,I */
    SINT32     s32DecOrderOutput;  /* 0:display order, 1:decode order */
    SINT32     s32DnrTfEnable;
    UADDR      s32SyntaxMemAddr;
    SINT32     s32SyntaxMemSize;
    VDEC_CHAN_CAP_LEVEL_E eCapLevel;
    UADDR      s32BpdMemAddr;
    SINT32     s32BpdMemSize;
    UADDR      s32Vp8SegIdMemAddr;
    SINT32     s32Vp8SegIdMemSize;
    //VFMW_STATE stState;
    UINT64     pts;
    UINT64     NextPts;
    UINT64     Usertag;
    UINT64     NextUsertag;
    UINT64     DispTime;
    UINT64     NextDispTime;
    UINT32     DispEnableFlag;
    UINT32     DispFrameDistance;
    UINT32     DistanceBeforeFirstFrame;
    UINT32     NextDispEnableFlag;
    UINT32     NextDispFrameDistance;
    UINT32     NextDistanceBeforeFirstFrame;
    UINT32     GopNum;
    UINT32     NextGopNum;

    STREAM_SEG_PACKET_S  stSegPacket;
    SINT32     s32NewPicSegDetector;
    STD_EXTENSION_U    StdExt;
    VDEC_CHAN_STATE_S  stChanState;
    SINT32     s32BasicCtxSize;
    UADDR      s32ContextMemAddr;
    SINT32     s32ContextMemSize;
    SINT32     s32Compress_en;
    SINT32     s32MoreGapEnable;
    SINT32     s32FastForwardBackwardSpeed;
    SINT32     s32KeepSPSPPS;                      /* keep global info in ctx for seek reset */
    SINT32     s32SupportAllP;                     /* support stream of all p frames */
    SINT32     s32ModuleLowlyEnable;               /*ģ������ʱʹ�ܱ�־*/
    SINT32     s32LowdlyEnable;                    /*SCD֡�ڵ���ʱʹ�ܱ�־*/
    VFMW_CONTROLINFO_S stPvrInfo;
#if 0
    SINT32    s32SupportBFrame;  /* ͨ���Ƿ�֧��B֡�����Ƿ�֧��B֡���� 0: ��֧�� 1: ֧��*/
    SINT32    s32MaxRefFrameNum;  /*������֧�ֲο�֡���������ֵ,���ĳ�����ο�֡�������ڴ�ֵ������ܲ������
                                      0:   ��ָʾͨ���ο�֡ϸ�ں��Ƿ�֧��B֡�� s32SupportBFrame��s32MaxRefFrameNum����Ч����ȫ������ǰ�ӿ�����ͨ��
                                      ��0: ������֧�ֲο�֡���������ֵ��s32SupportBFrame��s32MaxRefFrameNum����Ч������ͨ��ʱ��ο�������Ԫ�ء�*/
#endif
    VDEC_CHAN_OPTION_S stChanOption;/*ͨ������ΪCAP_LEVEL_USER_DEFINE_WITH_OPTIONʱ���û�ָ��ѡ������*/


    //add by sdk, 2012.11.20
    VDEC_DISPIC_PARAM_S stDisParams;  //��֡����
    SINT32 s32WaitFsFlag;//�ȴ�����֡���־sdk

    //HEVC 10Bit
    SINT32 s32BitDepth;
    SINT32 s32BitDepthChanged;
    //add by sdk
    SINT32      s32Is4k60fps;      //1: ��ͨ�����ڲ��ŵ���4k60����
    SINT32      s32IsHevcMain10;   //1: ��ͨ����H265 main10 profileͨ�����п�����10bit����
} SYNTAX_EXTRA_DATA_S;



VOID ReleasePacket(VID_STD_E VidStd, VOID *pCtx);


SINT32 OpenUsdPool(SINT32 ChanID);
VOID CloseUsdPool(SINT32 ChanID);

SINT32  InitUsdPool(SINT32 ChanID);
VDEC_USRDAT_S *GetUsd(SINT32 ChanID);
VOID FreeUsdByDec(SINT32 ChanID, VDEC_USRDAT_S *pUsrdat );
VOID MarkUsdByDnr(SINT32 ChanID, VDEC_USRDAT_S *pUsrdat );
VOID UnMarkUsdByDnr(SINT32 ChanID, VDEC_USRDAT_S *pUsrdat );

#endif


