#include "hi_unf_pvr.h"
#include "hi_mpi_pvr.h"
#include "hi_drv_pvr.h"
#include "teek_client_api.h"

#ifndef __DRV_PVR_TEE_FUNC_H__
#define __DRV_PVR_TEE_FUNC_H__

#ifdef HI_TEE_PVR_SUPPORT
#define PVR_TEE_REC_MAX_CHN_NUM         PVR_REC_MAX_CHN_NUM
#define REE_PVR_BUFFER_MAX_LEN          (2*47*1024*1024)
#define REE_PVR_BUFFER_MIN_LEN          (4*188*256)
#define REE_PVR_BUFFER_ALIGN            (47*1024)

typedef enum
{
    TEE_PVR_CMD_REC_OPEN_CHANNEL    = 0,
    TEE_PVR_CMD_REC_CLOSE_CHANNEL   = 1,
    TEE_PVR_CMD_REC_PROCESS_DATA    = 2,
    TEE_PVR_CMD_REC_GET_TEE_STATE   = 4,
    TEE_PVR_CMD_REC_COPY_TO_REE     = 8,
    TEE_PVR_CMD_REC_GET_ADDRINFO    = 16,
    TEE_PVR_CMD_PLAY_COPY_FROM_REE  = 32,
    TEE_PVR_CMD_PLAY_PROCESS_DATA   = 64,
    TEE_PVR_CMD_TYPE_INVALID        = 0xffffffff,
}TEE_PVR_CMD_TYPE_E;

typedef struct tagPVR_DRV_TEEC_INFO_S
{
    HI_S32 s32InitCount;
    TEEC_Context stContext;
    TEEC_Session stSession;
} PVR_DRV_TEEC_INFO_S;

typedef struct tagPVR_TEE_REC_CHAN_INFO_S
{
    HI_BOOL bUsed;
    HI_U32 u32TeeId;
    pid_t owner;
}PVR_TEE_REC_CHAN_INFO_S;

#define TEE_PVR_CHECK_CHN_RETURN(u32ChnId, pstTeeChnInfo)\
    do{\
        HI_U32 idx = 0;\
        for(idx =0; idx < PVR_TEE_REC_MAX_CHN_NUM; idx++)\
        {\
            if ((HI_TRUE == PvrTeeRecChan[idx].bUsed) && (PvrTeeRecChan[idx].u32TeeId == (u32ChnId)))\
            {\
                (pstTeeChnInfo) = &PvrTeeRecChan[idx];\
                break;\
            }\
        }\
        if (idx >= PVR_TEE_REC_MAX_CHN_NUM)\
        {\
            HI_ERR_PVR("Invalid tee channel(%d)\n", u32ChnId);\
            return HI_ERR_PVR_INVALID_PARA;\
        }\
    }while(0)
HI_S32 PVR_TeecInit(HI_VOID);
HI_S32 PVR_TeecDeInit(HI_VOID);
HI_S32 PVR_TeeRelease(struct file *file);
HI_S32 PVR_TeeRecOpenChn(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs);
HI_S32 PVR_TeeRecCloseChn(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs);
HI_S32 PVR_TeeRecCopyToRee(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs);
HI_S32 PVR_TeeRecProcessData(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs);
HI_S32 PVR_TeeRecGetState(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs);
HI_S32 PVR_TeeRecGetAddrInfo(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs);
HI_S32 PVR_TeePlayCopyFromRee(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs);
HI_S32 PVR_TeePlayProcessData(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs);
HI_S32 PVR_TeecIoctl(struct inode *inode, struct file *file, HI_U32 cmd, HI_VOID *arg);
#endif
#endif
