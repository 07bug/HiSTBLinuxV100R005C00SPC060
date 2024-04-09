#ifndef __DRV_VENC_H__
#define __DRV_VENC_H__

#include <linux/kthread.h>

#include "drv_venc_efl.h"
#include "drv_venc_ioctl.h"
#include "hi_error_mpi.h"
#include "hi_unf_venc.h"
#include "hi_drv_venc.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define VENC_FIRMWARE_VERSION "001.002.2018070900"

#define GET_VENC_CHHANDLE(u32ChanId) (u32ChanId | (HI_ID_VENC << 16))

#define D_VENC_CHECK_CHN(u32VeChn) \
    do {if (u32VeChn >= HI_VENC_MAX_CHN){    \
            return HI_ERR_VENC_CHN_NOT_EXIST;           \
        }                                          \
    } while (0)
enum

{
    VEDU_H264    = 0,
    VEDU_JPGE   = 1,
};

enum
{
    VEDU_H264_BASELINE_PROFILE    = 0,
    VEDU_H264_MAIN_PROFILE    = 1,
    VEDU_H264_EXTENDED_PROFILE = 2,
    VEDU_H264_HIGH_PROFILE  = 3,
    VEDU_H264_PROFILE_BUTT  = 4
};

enum
{
    VEDU_YUV420    = 0,
    VEDU_YUV422    = 1,
    VEDU_YUV444 = 2
};

enum
{
    VEDU_SEMIPLANNAR    = 0,
    VEDU_PLANNAR        = 1,
    VEDU_PACKAGE        = 2
};

enum
{
    VEDU_ROTATION_0     = 0,
    VEDU_ROTATION_90    = 1,
    VEDU_ROTATION_270   = 2,
    VEDU_ROTATION_180   = 3
};

typedef struct hiVENC_PROC_WRITE_S
{
    struct file *  fpSaveFile;    /* file pointer */
    HI_CHAR YUVFileName[64];
    HI_CHAR StreamFileName[64];
    HI_U32  u32FrameModeCount;    /* number of saved frame, used in frame mode */
    HI_BOOL bTimeModeRun;         /* run tag in time mode */
    HI_BOOL bFrameModeRun;        /* run tag in frame mode */
    HI_BOOL bSaveYUVFileRun;
} VENC_PROC_WRITE_S;

typedef enum hiVENC_CHN_STATE_E
{
    VEDU_STATE_CREATE      = 0,
    VEDU_STATE_START       = 1,
    VEDU_STATE_STOPPING    = 2,
    VEDU_STATE_STOP        = 3,
    VEDU_STATE_DESTORYING  = 4,
    VEDU_STATE_BUTT
} VENC_CHN_STATE_E;

typedef struct tagOPTM_VENC_CHN_S
{
    HI_U32                 u32UID;
    HI_BOOL                bEnable;
    HI_BOOL                bFrameBufMng;
    HI_BOOL                bOMXChn;
    HI_HANDLE              hSource;
    VeduEfl_EncPara_S*              hVEncHandle;
    HI_HANDLE              hUsrHandle;     //user handle will not change after pmoc
    HI_HANDLE              hJPGE;
    HI_MOD_ID_E            enSrcModId;
    HI_U32                 u32SrcUser;
    HI_U32                 StrmBufAddr;
    HI_U32                 StrmBufSize;
    HI_UNF_VENC_CHN_ATTR_S stChnUserCfg;
    HI_U32                 u32SliceSize;   /* use to record the slice size in unit of MB line*/
    VeduEfl_NALU_S         stChnPacket;    /* use to release the stream */
    struct timeval stTimeStart;
    HI_U32 u32FrameNumLastInput;           /* use as a static value, save last encoded frame number */
    HI_U32 u32FrameNumLastEncoded;         /* use as a static value, save last input frame number */
    HI_U32 u32TotalByteLastEncoded;        /* use as a static value, save last encoded total byte */
    HI_U32 u32LastSecInputFps;             /* input frame rate of last second, source may be VI or VO */
    HI_U32 u32LastSecEncodedFps;           /* encoded frame rate of last second by frame control */
    HI_U32 u32LastSecKbps;                 /* bit rate of last second, count as Kbps */
    HI_U32 u32LastSecTryNum;
    HI_U32 u32LastTryNumTotal;
    HI_U32 u32LastSecOKNum;
    HI_U32 u32LastOKNumTotal;
    HI_U32 u32LastSecPutNum;
    HI_U32 u32LastPutNumTotal;

    HI_U32 u32LastSecStrmGetTryNum;
    HI_U32 u32LastSecStrmGetOKNum;
    HI_U32 u32LastSecStrmRlsTryNum;
    HI_U32 u32LastSecStrmRlsOKNum;
    HI_U32 u32LastStrmGetTryNumTotal;
    HI_U32 u32LastStrmGetOKNumTotal;
    HI_U32 u32LastStrmRlsOKNumTotal;
    HI_U32 u32LastStrmRlsTryNumTotal;

    struct file *pWhichFile;

    VeduEfl_SrcInfo_S     stSrcInfo;
    VENC_PROC_WRITE_S     stProcWrite;

    VENC_CHN_STATE_E      enChanState;
} OPTM_VENC_CHN_S;

HI_S32 VENC_DRV_Init(HI_VOID);
HI_VOID VENC_DRV_Exit(HI_VOID);
HI_VOID VENC_DRV_BoardInit(HI_VOID);
HI_VOID VENC_DRV_BoardDeinit(HI_VOID);
HI_VOID VENC_DRV_InitEvent(HI_VOID);
HI_BOOL VENC_DRV_CheckChnStateSafe(HI_U32 ChanId);

HI_S32 VENC_DRV_CreateChn(VeduEfl_EncPara_S** phVencChn, venc_chan_cfg *pstAttr,VENC_CHN_INFO_S* pstVeInfo, HI_BOOL bOMXChn,
                            struct file* pfile);
HI_S32 VENC_DRV_DestroyChn( VeduEfl_EncPara_S* hVencChn);

HI_S32 VENC_DRV_AttachInput(VeduEfl_EncPara_S* hVencChn, HI_HANDLE hSrc, HI_MOD_ID_E enModId );
HI_S32 VENC_DRV_DetachInput(VeduEfl_EncPara_S* hVencChn, HI_HANDLE hSrc, HI_MOD_ID_E enModId );

HI_S32 VENC_DRV_AcquireStream(VeduEfl_EncPara_S* hVencChn, VENC_STREAM_S* pstStream, HI_U32 u32TimeoutMs,
                               VENC_BUF_OFFSET_S* pstBufOffSet);
HI_S32 VENC_DRV_ReleaseStream(VeduEfl_EncPara_S* hVencChn, VENC_INFO_ACQUIRE_STREAM_S* pstStream);

HI_S32 VENC_DRV_StartReceivePic(VeduEfl_EncPara_S* EncHandle);
HI_S32 VENC_DRV_StopReceivePic(VeduEfl_EncPara_S* EncHandle);

HI_S32 VENC_DRV_SetAttr(VeduEfl_EncPara_S* EncHandle, HI_UNF_VENC_CHN_ATTR_S* pstAttr, VENC_CHN_INFO_S* pstVeInfo);
HI_S32 VENC_DRV_GetAttr(VeduEfl_EncPara_S* EncHandle, HI_UNF_VENC_CHN_ATTR_S* pstAttr);

HI_S32 VENC_DRV_RequestIFrame(VeduEfl_EncPara_S* EncHandle);

HI_S32 VENC_DRV_QueueFrame(VeduEfl_EncPara_S* hVencChn, HI_UNF_VIDEO_FRAME_INFO_S* pstFrameInfo );
HI_S32 VENC_DRV_DequeueFrame(VeduEfl_EncPara_S* hVencChn, HI_UNF_VIDEO_FRAME_INFO_S* pstFrameInfo );

HI_S32 VENC_DRV_GetCapability(HI_UNF_VENC_CAP_S *pstCapability);
HI_S32 VENC_DRV_SetSrcInfo(VeduEfl_EncPara_S *hVencChn, HI_DRV_VENC_SRC_HANDLE_S *pstSrc);

HI_S32 VENC_DRV_ProcAdd(VeduEfl_EncPara_S* hVenc, HI_U32 u32ChnID);  /**/
HI_VOID VENC_DRV_ProcDel(VeduEfl_EncPara_S* hVenc, HI_U32 u32ChnID);

HI_S32 VENC_DRV_DbgWriteYUV(HI_DRV_VIDEO_FRAME_S* pstFrame, HI_CHAR* pFileName);
HI_S32 VENC_DRV_DbgWriteYUV_OMX(venc_user_buf *pstFrameOmx, HI_CHAR* pFileName);
HI_S32 VENC_DRV_DbgSaveStream(VeduEfl_NALU_S* pNalu, VeduEfl_EncPara_S* phVencChn);


HI_S32 VENC_DRV_SetRateControlType(VeduEfl_EncPara_S* EncHandle, VENC_DRV_CONTROLRATETYPE_E enRCType);
HI_S32 VENC_DRV_GetRateControlType(VeduEfl_EncPara_S* EncHandle, VENC_DRV_CONTROLRATETYPE_E *penRCType);

HI_S32 VENC_DRV_SetInFrmRateType(VeduEfl_EncPara_S* EncHandle, VENC_DRV_FRMRATETYPE_E enInFrmRateType);
HI_S32 VENC_DRV_GetInFrmRateType(VeduEfl_EncPara_S* EncHandle, VENC_DRV_FRMRATETYPE_E *penInFrmRateType);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif //__DRV_VENC_H__
