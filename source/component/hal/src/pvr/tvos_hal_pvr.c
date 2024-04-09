#define LOG_TAG "HALPVR"

#include "tvos_hal_common.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_pvr.h"
#include "hi_error_mpi.h"
#include "hi_unf_pvr.h"
#include "pthread.h"

/****************************************************************************************/
#define HAL_PVR_INVALID_HANDLE                  (0xFFFFFFFF)
#define HAL_PVR_MALLOC                          malloc
#define HAL_PVR_FREE                            free
#define HAL_PVR_ERROR                           HAL_ERROR
#define HAL_PVR_DEBUG                           HAL_DEBUG
#define HAL_PVR_GET_DEMUXID(dmxIdIn, dmxIdOut)  (dmxIdOut) = (dmxIdIn)
#define HAL_PVR_GET_TSBUFFER(tsBufIn, tsBufOut) (tsBufOut) = (tsBufIn)
#define HAL_PVR_INVALID_PID                     (0x1FFF)
#define HAL_PVR_MAX_REC_NUM                     (10)
#define HAL_PVR_MAX_PLAY_NUM                    (5)
#define HAL_PVR_MAGIC_NUM                       (0x5A5B5A5B)
#define HAL_PVR_EVENT_MAX                       (12)
#define HAL_PVR_INVALD_CHN_INDEX                (-1)

#define HAL_PVR_LOCK(mutex)\
    do{\
        (VOID)pthread_mutex_lock(&(mutex)); \
    }while(0)

#define HAL_PVR_UNLOCK(mutex)\
    do{\
        (VOID)pthread_mutex_unlock(&(mutex)); \
    }while(0)

#define HAL_PVR_CHECK_CHN(enHalType, s32ChnId)\
    do{\
        if ((0 > (s32ChnId))||((HAL_PVR_MAX_REC_NUM + HAL_PVR_MAX_PLAY_NUM) <= (s32ChnId)))\
        {\
            HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);\
            return ERROR_PVR_INVALID_CHN;\
        }\
        if (HI_NULL == s_stChnIndex[s32ChnId].pChnInfo)\
        {\
            HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);\
            return ERROR_PVR_INVALID_CHN;\
        }\
        if (HAL_PVR_MAGIC_NUM != s_stChnIndex[s32ChnId].pChnInfo->u32PvrMagicNum)\
        {\
            HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);\
            return ERROR_PVR_INVALID_CHN;\
        }\
        if (s_stChnIndex[s32ChnId].pChnInfo->enType != (enHalType))\
        {\
            HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);\
            return ERROR_PVR_INVALID_CHN;\
        }\
    }while(0)
#define HAL_PVR_ENTER()\
    do{\
        HAL_PVR_DEBUG("\t[%s_%d]ENTER>>>\n",__FILE__, __LINE__);\
    }while(0)
#define HAL_PVR_EXIT()\
    do{\
        HAL_PVR_DEBUG("\t[%s_%d]EXIT<<<<\n",__FILE__, __LINE__);\
    }while(0)

#define HAL_PVR_CHECK_NULL_POINTER_RETURN(val)\
    do{\
        if (NULL == (val))\
        {\
            HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);\
            HAL_PVR_ERROR("NULL PTR\n");\
            return ERROR_NULL_PTR;\
        }\
    }while(0)

#define HAL_PVR_SET_VALUE(s32Old, s32New)\
    do{\
        (s32Old) = (s32New);\
    }while(0)
#define HAL_PVR_GET_VALUE(s32SourceNum, s32DestNum)\
    do{\
        (s32DestNum) = (s32SourceNum);\
    }while(0)
#define HAL_PVR_ADD_VALUE(s32Base, s32Delta)\
    do{\
        (s32Base) += (s32Delta);\
    }while(0)
#define HAL_PVR_SUB_VALUE(s32Base, s32Delta)\
    do{\
        (s32Base) -= (s32Delta);\
    }while(0)
#define HAL_PVR_CHECK_INIT_RETURN(ret)\
    do{\
        if (FALSE == s_stPvrCtrl.bInitFlag)\
        {\
            HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);\
            return (ret);\
        }\
    }while(0)

#define HAL_PVR_GET_STATE_BY_SPEED(state, speed) \
    do {\
        switch (speed)\
        {\
            case HI_UNF_PVR_PLAY_SPEED_NORMAL           :\
                state = PVR_PLAY_STATE_PLAY;\
                break;\
            case HI_UNF_PVR_PLAY_SPEED_2X_FAST_FORWARD  :\
            case HI_UNF_PVR_PLAY_SPEED_4X_FAST_FORWARD  :\
            case HI_UNF_PVR_PLAY_SPEED_8X_FAST_FORWARD  :\
            case HI_UNF_PVR_PLAY_SPEED_16X_FAST_FORWARD :\
            case HI_UNF_PVR_PLAY_SPEED_32X_FAST_FORWARD :\
            case HI_UNF_PVR_PLAY_SPEED_64X_FAST_FORWARD :\
                state = PVR_PLAY_STATE_FF;\
                break;\
            case HI_UNF_PVR_PLAY_SPEED_1X_FAST_BACKWARD :\
            case HI_UNF_PVR_PLAY_SPEED_2X_FAST_BACKWARD :\
            case HI_UNF_PVR_PLAY_SPEED_4X_FAST_BACKWARD :\
            case HI_UNF_PVR_PLAY_SPEED_8X_FAST_BACKWARD :\
            case HI_UNF_PVR_PLAY_SPEED_16X_FAST_BACKWARD:\
            case HI_UNF_PVR_PLAY_SPEED_32X_FAST_BACKWARD:\
            case HI_UNF_PVR_PLAY_SPEED_64X_FAST_BACKWARD:\
                state = PVR_PLAY_STATE_FB;\
                break;\
            case HI_UNF_PVR_PLAY_SPEED_2X_SLOW_FORWARD  :\
            case HI_UNF_PVR_PLAY_SPEED_4X_SLOW_FORWARD  :\
            case HI_UNF_PVR_PLAY_SPEED_8X_SLOW_FORWARD  :\
            case HI_UNF_PVR_PLAY_SPEED_16X_SLOW_FORWARD :\
            case HI_UNF_PVR_PLAY_SPEED_32X_SLOW_FORWARD :\
            case HI_UNF_PVR_PLAY_SPEED_64X_SLOW_FORWARD :\
                state = PVR_PLAY_STATE_SF;\
                break;\
            case HI_UNF_PVR_PLAY_SPEED_2X_SLOW_BACKWARD :\
            case HI_UNF_PVR_PLAY_SPEED_4X_SLOW_BACKWARD :\
            case HI_UNF_PVR_PLAY_SPEED_8X_SLOW_BACKWARD :\
            case HI_UNF_PVR_PLAY_SPEED_16X_SLOW_BACKWARD:\
            case HI_UNF_PVR_PLAY_SPEED_32X_SLOW_BACKWARD:\
            case HI_UNF_PVR_PLAY_SPEED_64X_SLOW_BACKWARD:\
                state = PVR_PLAY_STATE_SB;\
                break;\
            default:\
                state = PVR_PLAY_STATE_INVALID;\
                break;\
        }\
    }while(0)
/****************************************************************************************/
/****************************************************************************************/

typedef enum halPVR_TYPE_E
{
    HAL_PVR_REC = 0,
    HAL_PVR_PLY = 1,
    HAL_PVR_BUTT
} HAL_PVR_TYPE_E;

typedef struct halPVR_CHAN_INFO_S
{
    U32 u32PvrMagicNum;/*Magic num, used to check the data valid*/
    U32 ChnId;/*channel num.*/
    HAL_PVR_TYPE_E enType;/*channel type, recording or playing*/
    union
    {
        PVR_REC_OPENPARAMS_S stRecCfg;
        PVR_PLAY_OPENPARAMS_S stPlyCfg;
    } stUserCfg;/*the user config. one channel can't support recording and playing at the same time*//*CNComment:*/
} HAL_PVR_CHAN_INFO_S;
typedef struct halPVR_CHAN_CTRL_S
{
    BOOL bUsed;/*TRUE-- the channel has been used, FALSE is not been used*/
    HAL_PVR_CHAN_INFO_S* pChnInfo;/*the channel pointer, it's not null if bUsed is TRUE*/
} HAL_PVR_CHAN_CTRL_S;
typedef struct halPVR_EVENT_CTRL_S
{
    BOOL bUsed;/*if the event type has been reg,the value is TRUE*/
    PVR_EVENT_E enHalEvent;/*event type, ref. PVR_EVENT_E */
    VOID* pArgs;/*argument for the pfnCallback registered by app*/
    pvr_eventCallBack pfnCallback;/*the callback registered by app, which is called while receive the event form sdk*/
} HAL_PVR_EVENT_CTRL_S;
typedef struct halPVR_CTRL_INFO_S
{
    S32 s32RecChnNum;/*the total recording channel*/
    S32 s32PlyChnNum;/*the total playing channel */
    pthread_mutex_t PvrHandleMutex;/*the mutex is used to protect to access the */
    BOOL bInitFlag;/**//*CNComment:*/
} HAL_PVR_CTRL_INFO_S;
/****************************************************************************************/
/****************************************************************************************/

static HAL_PVR_CTRL_INFO_S s_stPvrCtrl =
{
    .s32RecChnNum = 0,
    .s32PlyChnNum = 0,
    .PvrHandleMutex = PTHREAD_MUTEX_INITIALIZER,
    .bInitFlag = FALSE,
};

static S32 s_enEvent[HAL_PVR_EVENT_MAX][2] =
{
    {PVR_EVENT_PLAY_EOF,        HI_UNF_PVR_EVENT_PLAY_EOF},
    {PVR_EVENT_PLAY_SOF,        HI_UNF_PVR_EVENT_PLAY_SOF},
    {PVR_EVENT_PLAY_ERROR,      HI_UNF_PVR_EVENT_PLAY_ERROR},
    {PVR_EVENT_PLAY_REACH_REC,  HI_UNF_PVR_EVENT_PLAY_REACH_REC},
    {PVR_EVENT_PLAY_RESV,       HI_UNF_PVR_EVENT_PLAY_RESV},
    {PVR_EVENT_REC_DISKFULL,    HI_UNF_PVR_EVENT_REC_DISKFULL},
    {PVR_EVENT_REC_ERROR,       HI_UNF_PVR_EVENT_REC_ERROR},
    {PVR_EVENT_REC_OVER_FIX,    HI_UNF_PVR_EVENT_REC_OVER_FIX},
    {PVR_EVENT_REC_REACH_PLAY,  HI_UNF_PVR_EVENT_REC_REACH_PLAY},
    {PVR_EVENT_REC_DISK_SLOW,   HI_UNF_PVR_EVENT_REC_DISK_SLOW},
    {PVR_EVENT_REC_RESV,        HI_UNF_PVR_EVENT_REC_RESV},
    {PVR_EVENT_BUTT,            HI_UNF_PVR_EVENT_BUTT}
};
static HAL_PVR_CHAN_CTRL_S s_stChnIndex[HAL_PVR_MAX_REC_NUM + HAL_PVR_MAX_PLAY_NUM];
static HAL_PVR_EVENT_CTRL_S s_stCallback[HAL_PVR_EVENT_MAX];
/****************************************************************************************/
/****************************************************************************************/

static VOID pvrEventCallback(HI_U32 u32ChnID, HI_UNF_PVR_EVENT_E EventType, HI_S32 s32EventValue, HI_VOID* args);
static S32 pvrErrCodeTransfer(S32 s32ErrCode);
static VOID pvrInitChanInfo();
static S32 pvrRequireChnId();
static VOID pvrReleaseChnId(S32 s32Index);
static S32 pvrPlayGetTrickInfo(BOOL* pbStepMode,
                               BOOL* pbBackWard,
                               HI_UNF_PVR_PLAY_SPEED_E* penSpeed,
                               const PVR_PLAY_TRICKPARAMS_S* pstPlayTrickMode);
static S32 pvrPlayGetSeekInfo(HI_UNF_PVR_PLAY_POSITION_S* pstPosition, const PVR_PLAY_SEEKPARAMS_S* pstPlaySeekParams);
static S32 pvrPlayTransStatus(PVR_PLAY_STATUS_S* const pstStatus, HI_UNF_PVR_PLAY_STATUS_S stStatus);
static S32 pvrRecTransAttr(const PVR_REC_OPENPARAMS_S* const pstRecParams, HI_UNF_PVR_REC_ATTR_S* pstRecAttr);
static S32  pvr_init(struct _PVR_DEVICE_S* pstDev, const PVR_RECINIT_PARAMS_S*   const  pstInitParams);
static S32  pvr_term(struct _PVR_DEVICE_S* pstDev, const PVR_TERM_PARAMS_S* const  pstTrmParams);
static S32  pvr_get_capability(struct _PVR_DEVICE_S* pstDev, PVR_CAPABILITY_S*  const  pstCapability);
static S32 pvr_rec_open(struct _PVR_DEVICE_S* pstDev, U32* const  pu32RecchnId, DMX_ID_E const enDmxId, const PVR_REC_OPENPARAMS_S* const pstRecParams);
static S32 pvr_rec_close(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId, const PVR_REC_CLOSECHNPARAMS_S*  pstReccloseParams);
static S32 pvr_rec_start(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId);
static S32 pvr_rec_stop(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId);
static S32  pvr_rec_pause(struct _PVR_DEVICE_S* pstDev, const U32  u32RecchnId);
static S32  pvr_rec_resume(struct _PVR_DEVICE_S* pstDev, const U32  u32RecchnId);
static S32  pvr_rec_getstatus(struct _PVR_DEVICE_S* pstDev, U32  u32RecchnId, PVR_REC_STATUS_S* pstRecStatus);
static S32  pvr_rec_addpid(struct _PVR_DEVICE_S* pstDev, DMX_ID_E  enDmxId,  U32  u32RecchnId, U32 u32Pid, DMX_CHANNEL_TYPE_E enType);
static S32  pvr_rec_delpid(struct _PVR_DEVICE_S* pstDev, DMX_ID_E  enDmxId,  U32  u32RecchnId, U32 u32Pid);
static S32  pvr_play_open(struct _PVR_DEVICE_S* pstDev, U32* const pu32PlaychnId, const PVR_PLAY_OPENPARAMS_S* const pstPlayParams, HANDLE hAV, U32 u32TsBufferId);
static S32  pvr_play_close(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);
static S32  pvr_play_start(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);
static S32  pvr_play_stop(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);
static S32  pvr_play_pause(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);
static S32  pvr_play_resume(struct _PVR_DEVICE_S* pstDev,  const U32  u32PlaychnId);
static S32  pvr_play_trick(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, const PVR_PLAY_TRICKPARAMS_S* pstPlayTrickMode);
static S32  pvr_play_seek(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, const PVR_PLAY_SEEKPARAMS_S* pstPlaySeekParams);
static S32  pvr_play_getstatus(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, PVR_PLAY_STATUS_S* const pstStatus);
static S32  pvr_play_getfileattrbychannel(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, PVR_FILE_ATTR_S* const pAttr);
static S32  pvr_play_getfileattrbyfilename(struct _PVR_DEVICE_S* pstDev, const  CHAR* pFileName, PVR_FILE_ATTR_S* const pAttr);
static S32  pvr_usrdata_setbyfilename(struct _PVR_DEVICE_S* pstDev, const  CHAR* pFileName, U8* pInfo,  U32 u32UsrDataLen);
static S32  pvr_usrdata_getbyfilename(struct _PVR_DEVICE_S* pstDev, const  CHAR* pFileName, U8* pInfo,  U32 u32BufLen, U32* pUsrDataLen);
static S32  pvr_event_register(struct _PVR_DEVICE_S* pstDev, PVR_EVENT_E enEvent, pvr_eventCallBack pCallBack, VOID* pArgs);
static S32  pvr_event_unregister(struct _PVR_DEVICE_S* pstDev, PVR_EVENT_E enEvent);
static S32  pvr_remove_file(struct _PVR_DEVICE_S* pstDev, const CHAR* pFileName);

/****************************************************************************************/
/****************************************************************************************/
static VOID pvrEventCallback(HI_U32 u32ChnID, HI_UNF_PVR_EVENT_E EventType, HI_S32 s32EventValue, HI_VOID* args)
{
    HAL_PVR_EVENT_CTRL_S* pstCallback = NULL;
    U32 u32HalChnId = HAL_PVR_INVALD_CHN_INDEX;
    U32 i = 0;

    for (i = 0; i < HAL_PVR_EVENT_MAX; i++)
    {
        if (EventType == s_enEvent[i][1])
        {
            pstCallback = &(s_stCallback[i]);
            break;
        }
    }
    if (NULL == pstCallback)
    {
        HAL_PVR_ERROR("Invalid sdk pvr event(0x%08x)!\n", EventType);
        return;
    }
    if ((FALSE == pstCallback->bUsed) || (NULL == pstCallback->pfnCallback))
    {
        return;
    }
    for (i = 0; i < HAL_PVR_MAX_REC_NUM + HAL_PVR_MAX_PLAY_NUM; i++)
    {
        if ((TRUE == s_stChnIndex[i].bUsed)
            && (NULL != s_stChnIndex[i].pChnInfo))
        {
            if (u32ChnID == s_stChnIndex[i].pChnInfo->ChnId)
            {
                u32HalChnId = i;
                break;
            }
        }
    }
    if ((U32)HAL_PVR_INVALD_CHN_INDEX == u32HalChnId)
    {
        HAL_PVR_ERROR("Invalid chanid (%d)\n", u32ChnID);
        return;
    }
    pstCallback->pfnCallback(u32HalChnId, pstCallback->enHalEvent, s32EventValue, pstCallback->pArgs);
    return;
}
static S32 pvrErrCodeTransfer(S32 s32ErrCode)
{
    switch (s32ErrCode)
    {
        case HI_ERR_PVR_NOT_INIT:
            return ERROR_NOT_INITED;
        case HI_ERR_PVR_INVALID_PARA:
            return ERROR_INVALID_PARAM;
        case HI_ERR_PVR_NUL_PTR:
            return ERROR_NULL_PTR;
        case HI_ERR_PVR_CHN_NOT_INIT:
            return ERROR_PVR_INVALID_CHN;
        case HI_ERR_DMX_UNMATCH_CHAN:
            return ERROR_PVR_INVALID_CHN;
        case HI_ERR_PVR_INVALID_CHNID:
            return ERROR_PVR_INVALID_CHN;
        case HI_ERR_PVR_NO_CHN_LEFT:
            return ERROR_PVR_NO_CHN_LEFT;
        case HI_ERR_PVR_ALREADY:
            return ERROR_PVR_ALREADY;
        case HI_ERR_PVR_BUSY:
            return ERROR_PVR_CHANNEL_BUSY;
        case HI_ERR_PVR_NO_MEM:
            return ERROR_PVR_NO_MEM;
        case HI_ERR_PVR_NOT_SUPPORT:
            return ERROR_PVR_NOT_SUPPORT;
        case HI_ERR_PVR_RETRY:
            return ERROR_PVR_RETRY;
        case HI_ERR_PVR_FILE_EXIST:
            return ERROR_PVR_FILE_EXIST;
        case HI_ERR_PVR_FILE_NOT_EXIST:
            return ERROR_PVR_FILE_NO_EXIST;
        case HI_ERR_PVR_FILE_CANT_OPEN:
            return ERROR_PVR_FILE_CANT_OPEN;
        case HI_ERR_PVR_FILE_CANT_CLOSE:
            return ERROR_PVR_FILE_CANT_CLOSE;
        case HI_ERR_PVR_FILE_CANT_SEEK:
            return ERROR_PVR_FILE_CANT_SEEK;
        case HI_ERR_PVR_FILE_CANT_WRITE:
            return ERROR_PVR_FILE_CANT_SEEK;
        case HI_ERR_PVR_FILE_CANT_READ:
            return ERROR_PVR_FILE_CANT_READ;
        case HI_ERR_PVR_FILE_INVALID_FNAME:
            return ERROR_PVR_FILE_INVALID_FNAME;
        case HI_ERR_PVR_FILE_TILL_START:
            return ERROR_PVR_FILE_TILL_START;
        case HI_ERR_PVR_FILE_TILL_END:
            return ERROR_PVR_FILE_TILL_END;
        case HI_ERR_PVR_FILE_DISC_FULL:
            return ERROR_PVR_FILE_DISK_FULL;
        case HI_ERR_PVR_REC_INVALID_STATE:
            return ERROR_PVR_REC_INVALID_STATE;
        case HI_ERR_PVR_REC_INVALID_DMXID:
            return ERROR_PVR_REC_INVALID_DMXID;
        case HI_ERR_PVR_REC_INVALID_FSIZE:
            return ERROR_PVR_REC_INVALID_FSIZE;
        case HI_ERR_PVR_REC_INVALID_UDSIZE:
            return ERROR_PVR_REC_INVALID_UDSIZE;
        case HI_ERR_PVR_PLAY_INVALID_STATE:
            return ERROR_PVR_PLAY_INVALID_STATE;
        case HI_ERR_PVR_PLAY_INVALID_DMXID:
            return ERROR_PVR_PLAY_INVALID_DMXID;
        case HI_ERR_PVR_PLAY_INVALID_TSBUFFER:
            return ERROR_PVR_PLAY_INVALID_TSBUFFER;
        case HI_ERR_PVR_PLAY_INVALID_PACKETBUFFER:
            return ERROR_PVR_PLAY_INVALID_PACKETBUFFER;
        case HI_ERR_PVR_PLAY_INDEX_BEYOND_TS:
            return ERROR_PVR_PLAY_INDEX_BEYOND_TS;
        case HI_ERR_PVR_INDEX_CANT_MKIDX:
            return ERROR_PVR_INDEX_CANT_MKIDX;
        case HI_ERR_PVR_INDEX_FORMAT_ERR:
            return ERROR_PVR_INDEX_FORMAT_ERR;
        case HI_ERR_PVR_INDEX_DATA_ERR:
            return ERROR_PVR_INDEX_DATA_ERR;
        case HI_ERR_PVR_INDEX_INVALID_ENTRY:
            return ERROR_PVR_INDEX_INVALID_ENTRY;
        case HI_ERR_PVR_INTF_EVENT_INVAL:
            return ERROR_PVR_INTF_EVENT_INVAL;
        case HI_ERR_PVR_INTF_EVENT_NOREG:
            return ERROR_PVR_INTF_EVENT_NOREG;
        default:
            return s32ErrCode;
    }
    return SUCCESS;
}
static VOID pvrInitChanInfo()
{
    U32 i = 0;

    for (i = 0; i < (HAL_PVR_MAX_REC_NUM + HAL_PVR_MAX_PLAY_NUM); i++)
    {
        s_stChnIndex[i].pChnInfo = NULL;
        s_stChnIndex[i].bUsed = FALSE;
    }

    return;
}
static S32 pvrRequireChnId()
{
    U32 i = 0;

    for (i = 0; i < (HAL_PVR_MAX_REC_NUM + HAL_PVR_MAX_PLAY_NUM); i++)
    {
        if (FALSE == s_stChnIndex[i].bUsed)
        {
            s_stChnIndex[i].bUsed = TRUE;
            return i;
        }
    }
    return -1;
}

static VOID pvrReleaseChnId(S32 s32Index)
{
    if ((0 > s32Index) || ((HAL_PVR_MAX_REC_NUM + HAL_PVR_MAX_PLAY_NUM) <= s32Index))
    {
        HAL_PVR_ERROR("Invalid chan index(%d)!\n", s32Index);
        return;
    }
    s_stChnIndex[s32Index].bUsed = FALSE;
    return;
}

static S32 pvrPlayGetTrickInfo(BOOL* pbStepMode,
                               BOOL* pbBackWard,
                               HI_UNF_PVR_PLAY_SPEED_E* penSpeed,
                               const PVR_PLAY_TRICKPARAMS_S* pstPlayTrickMode)
{
    PVR_PLAY_TRICK_MODE_E       enMode = PVR_PLAY_TRICKMODE_NORMAL;
    PVR_PLAY_SPEEDMULTIPLE_E    enMultiple = PVR_PLAY_SPEED_1X;
    PVR_PLAY_SPEEDCHANGE_E      enChange = PVR_PLAY_SPEED_FAST;

    HAL_CHK_RETURN(((NULL == pbStepMode) || (NULL == penSpeed) || (NULL == pbBackWard) || (NULL == pstPlayTrickMode)),
                   ERROR_NULL_PTR, "null pointer for argument!\n");

    enMode = pstPlayTrickMode->enMode;
    if (PVR_PLAY_TRICKMODE_STEPFRAME == enMode)
    {
        *pbStepMode = TRUE;
        *penSpeed = HI_UNF_PVR_PLAY_SPEED_NORMAL;
        *pbBackWard = (PVR_PLAY_TRICK_BACK == pstPlayTrickMode->unData.enStep) ? TRUE : FALSE;
    }
    else if (PVR_PLAY_TRICKMODE_SPEED == enMode)
    {
        *pbStepMode = FALSE;
        *pbBackWard = (PVR_PLAY_TRICK_BACK == pstPlayTrickMode->unData.stSpeed.enDirection) ? TRUE : FALSE;
        enMultiple = pstPlayTrickMode->unData.stSpeed.enMultiple;
        enChange = pstPlayTrickMode->unData.stSpeed.enChange;

        HAL_CHK_RETURN(((PVR_PLAY_SPEED_FAST != enChange) && (PVR_PLAY_SPEED_SLOW != enChange)),
            ERROR_INVALID_PARAM, "Invalid speed param, enChange = %d!\n", enChange);
        HAL_CHK_RETURN((PVR_PLAY_SPEED_BUTT <= enMultiple),
            ERROR_INVALID_PARAM, "Invalid speed param, enMultiple = %d!\n", enMultiple);

        if (PVR_PLAY_SPEED_FAST == enChange)
        {
            *penSpeed = (HI_UNF_PVR_PLAY_SPEED_E)(HI_UNF_PVR_PLAY_SPEED_NORMAL * (1 << enMultiple));
        }
        else if (PVR_PLAY_SPEED_SLOW == enChange)
        {
            *penSpeed = (HI_UNF_PVR_PLAY_SPEED_E)(HI_UNF_PVR_PLAY_SPEED_NORMAL / (1 << enMultiple));
        }
    }
    else if (PVR_PLAY_TRICKMODE_NORMAL == enMode)
    {
        *pbStepMode = FALSE;
        *penSpeed = HI_UNF_PVR_PLAY_SPEED_NORMAL;
        *pbBackWard = FALSE;
    }
    else
    {
        HAL_PVR_ERROR("Invalid speed param, enMode = %d!\n", enMode);
        return ERROR_INVALID_PARAM;
    }
    return SUCCESS;
}

static S32 pvrPlayGetSeekInfo(HI_UNF_PVR_PLAY_POSITION_S* pstPosition, const PVR_PLAY_SEEKPARAMS_S* pstPlaySeekParams)
{
    PVR_PLAY_SEEKTYPE_E enType = PVR_PLAY_SEEKTYPE_UNKOWN;
    PVR_PLAY_SEEKMODE_E enSeekMode = PVR_PLAY_SEEKMODE_SET;
    S64 s64Offset = 0;

    if ((NULL == pstPosition) || (NULL == pstPlaySeekParams))
    {
        HAL_PVR_ERROR("null pointer for argument!\n");
        return ERROR_NULL_PTR;
    }

    enType = pstPlaySeekParams->enType;
    enSeekMode = pstPlaySeekParams->enSeekMode;
    s64Offset = pstPlaySeekParams->s64Offset;
    if (PVR_PLAY_SEEKTYPE_STAMPTIME != enType)
    {
        HAL_PVR_ERROR("Invalide seek params, enType = %d\n", enType);
        return ERROR_INVALID_PARAM;
    }
    if ((PVR_PLAY_SEEKMODE_SET != enSeekMode)
        && (PVR_PLAY_SEEKMODE_CUR != enSeekMode)
        && (PVR_PLAY_SEEKMODE_END != enSeekMode))
    {
        HAL_PVR_ERROR("Invalide seek params, enSeekMode = %d\n", enSeekMode);
        return ERROR_INVALID_PARAM;
    }
    if (((PVR_PLAY_SEEKMODE_SET == enSeekMode) && (0 > s64Offset))
        || ((PVR_PLAY_SEEKMODE_END == enSeekMode) && (0 < s64Offset)))
    {
        HAL_PVR_ERROR("Invalide seek params, enSeekMode = %d, s64Offset = %lld\n", enSeekMode, s64Offset);
        return ERROR_INVALID_PARAM;
    }
    pstPosition->enPositionType = HI_UNF_PVR_PLAY_POS_TYPE_TIME;
    pstPosition->s64Offset = s64Offset;
    if (PVR_PLAY_SEEKMODE_SET == enSeekMode)
    {
        pstPosition->s32Whence = SEEK_SET;
    }
    else if (PVR_PLAY_SEEKMODE_END == enSeekMode)
    {
        pstPosition->s32Whence = SEEK_END;
    }
    else
    {
        pstPosition->s32Whence = SEEK_CUR;
    }

    return SUCCESS;
}

static S32 TransSpeed2Hal(HI_UNF_PVR_PLAY_SPEED_E SdkSpeed, PVR_PLAY_SPEEDMULTIPLE_E *enMultiple, PVR_PLAY_SPEEDCHANGE_E entype)
{
    U32 Count = 0;
    S32 Tmp = 0;

    if (PVR_PLAY_SPEED_FAST == entype)
    {
        Tmp = SdkSpeed / HI_UNF_PVR_PLAY_SPEED_NORMAL;
    }
    else if (PVR_PLAY_SPEED_SLOW == entype)
    {
        Tmp = HI_UNF_PVR_PLAY_SPEED_NORMAL / SdkSpeed;
    }
    else
    {
        return FAILURE;
    }

    while(1)
    {
        if (abs(Tmp) > 1)
        {
            Tmp = Tmp/2;
            Count++;
        }
        else
        {
            break;
        }
    }

    *enMultiple = Count;

    return SUCCESS;
}

static S32 pvrPlayTransStatus(PVR_PLAY_STATUS_S* const pstStatus, HI_UNF_PVR_PLAY_STATUS_S stStatus)
{
    PVR_PLAY_SPEEDMULTIPLE_E enMultiple = 0;

    pstStatus->u32CurPlayTimeInMs = stStatus.u32CurPlayTimeInMs;
    switch (stStatus.enState)
    {
        case HI_UNF_PVR_PLAY_STATE_INVALID:
            pstStatus->enState = PVR_PLAY_STATE_INVALID;
            break;
        case HI_UNF_PVR_PLAY_STATE_INIT:
            pstStatus->enState = PVR_PLAY_STATE_INIT;
            break;
        case HI_UNF_PVR_PLAY_STATE_PLAY:
            pstStatus->enState = PVR_PLAY_STATE_PLAY;
            break;
        case HI_UNF_PVR_PLAY_STATE_PAUSE:
            pstStatus->enState = PVR_PLAY_STATE_PAUSE;
            break;
        case HI_UNF_PVR_PLAY_STATE_FF:
            pstStatus->enState = PVR_PLAY_STATE_FF;
            break;
        case HI_UNF_PVR_PLAY_STATE_FB:
            pstStatus->enState = PVR_PLAY_STATE_FB;
            break;
        case HI_UNF_PVR_PLAY_STATE_SF:
            pstStatus->enState = PVR_PLAY_STATE_SF;
            break;
        case HI_UNF_PVR_PLAY_STATE_SB:
            pstStatus->enState = PVR_PLAY_STATE_SB;
            break;
        case HI_UNF_PVR_PLAY_STATE_STEPF:
            pstStatus->enState = PVR_PLAY_STATE_STEPF;
            pstStatus->stTrickParam.enMode = PVR_PLAY_TRICKMODE_STEPFRAME;
            pstStatus->stTrickParam.unData.enStep = PVR_PLAY_TRICK_ONWARD;
            break;
        case HI_UNF_PVR_PLAY_STATE_STEPB:
            pstStatus->enState = PVR_PLAY_STATE_STEPB;
            pstStatus->stTrickParam.enMode = PVR_PLAY_TRICKMODE_STEPFRAME;
            pstStatus->stTrickParam.unData.enStep = PVR_PLAY_TRICK_BACK;
            break;
        case HI_UNF_PVR_PLAY_STATE_STOP:
            pstStatus->enState = PVR_PLAY_STATE_STOP;
            break;
        default:
            pstStatus->enState = PVR_PLAY_STATE_INVALID;
            break;
    }

    if ((HI_UNF_PVR_PLAY_STATE_STEPB != stStatus.enState)
        && (HI_UNF_PVR_PLAY_STATE_STEPF != stStatus.enState))
    {
        pstStatus->stTrickParam.enMode = PVR_PLAY_TRICKMODE_SPEED;
        pstStatus->stTrickParam.unData.stSpeed.enDirection = PVR_PLAY_TRICK_ONWARD;
        if (0 > stStatus.enSpeed)
        {
            pstStatus->stTrickParam.unData.stSpeed.enDirection = PVR_PLAY_TRICK_BACK;
            stStatus.enSpeed = (HI_UNF_PVR_PLAY_SPEED_E)(-1 * stStatus.enSpeed);
        }
        if (HI_UNF_PVR_PLAY_SPEED_NORMAL <= stStatus.enSpeed)
        {
            pstStatus->stTrickParam.unData.stSpeed.enChange = PVR_PLAY_SPEED_FAST;

            (VOID)TransSpeed2Hal(stStatus.enSpeed, &enMultiple, PVR_PLAY_SPEED_FAST);

            pstStatus->stTrickParam.unData.stSpeed.enMultiple = enMultiple;
        }
        else
        {
            pstStatus->stTrickParam.unData.stSpeed.enChange = PVR_PLAY_SPEED_SLOW;

            (VOID)TransSpeed2Hal(stStatus.enSpeed, &enMultiple, PVR_PLAY_SPEED_SLOW);

            pstStatus->stTrickParam.unData.stSpeed.enMultiple = enMultiple;
        }
    }
    return SUCCESS;
}

static S32 pvrRecTransAttr(const PVR_REC_OPENPARAMS_S* const pstRecParams, HI_UNF_PVR_REC_ATTR_S* pstRecAttr)
{
    //HAL_PVR_CHECK_NULL_POINTER_RETURN(pstRecParams);
    //HAL_PVR_CHECK_NULL_POINTER_RETURN(pstRecAttr);

    if (NULL == pstRecParams || NULL == pstRecAttr)
    {
        HAL_PVR_ERROR("NULL PTR\n");
        return ERROR_NULL_PTR;
    }

    pstRecAttr->u32IndexPid = pstRecParams->u32IndexPid;
    pstRecAttr->u32DavBufSize = pstRecParams->u32DavBufSize;
    pstRecAttr->u32ScdBufSize = pstRecParams->u32ScdBufSize;
    pstRecAttr->u32UsrDataInfoSize = pstRecParams->u32UsrDataInfoSize;
    pstRecAttr->bIsClearStream = HI_TRUE;
    if (PVR_STREAM_TS == pstRecParams->enStreamType)
    {
        pstRecAttr->enStreamType = HI_UNF_PVR_STREAM_TYPE_TS;
        if (PVR_REC_INDEX_TYPE_VIDEO == pstRecParams->enIndexType)
        {
            pstRecAttr->enIndexType = HI_UNF_PVR_REC_INDEX_TYPE_VIDEO;
            switch (pstRecParams->enVidType)
            {
                case AV_VID_STREAM_TYPE_MPEG2:
                    pstRecAttr->enIndexVidType = HI_UNF_VCODEC_TYPE_MPEG2;
                    break;
                case AV_VID_STREAM_TYPE_MPEG4:
                    pstRecAttr->enIndexVidType = HI_UNF_VCODEC_TYPE_MPEG4;
                    break;
                case AV_VID_STREAM_TYPE_AVS:
                    pstRecAttr->enIndexVidType = HI_UNF_VCODEC_TYPE_AVS;
                    break;
                case AV_VID_STREAM_TYPE_H264:
                    pstRecAttr->enIndexVidType = HI_UNF_VCODEC_TYPE_H264;
                    break;
                case AV_VID_STREAM_TYPE_HEVC:
                    pstRecAttr->enIndexVidType = HI_UNF_VCODEC_TYPE_HEVC;
                    break;
                default:
                {
                    HAL_PVR_ERROR("unsupport videotype %d\n", pstRecParams->enVidType);
                    return ERROR_INVALID_PARAM;
                }
            }
        }
        else if (PVR_REC_INDEX_TYPE_AUDIO == pstRecParams->enIndexType)
        {
            pstRecAttr->enIndexType = HI_UNF_PVR_REC_INDEX_TYPE_AUDIO;
        }
        else
        {
            HAL_PVR_ERROR("unsupport index type(%d) for ts recording!\n", pstRecParams->enIndexType);
            return ERROR_INVALID_PARAM;
        }
    }
    else if (PVR_STREAM_ALL_TS == pstRecParams->enStreamType)
    {
        pstRecAttr->enIndexType = HI_UNF_PVR_REC_INDEX_TYPE_NONE;
        pstRecAttr->enStreamType = HI_UNF_PVR_STREAM_TYPE_ALL_TS;
    }

    if (FALSE == pstRecParams->stEncryptCfg.bDoCipher)
    {
        pstRecAttr->stEncryptCfg.bDoCipher = HI_FALSE;
        pstRecAttr->stEncryptCfg.u32KeyLen = 0;
    }
    else
    {
        pstRecAttr->stEncryptCfg.bDoCipher = HI_TRUE;
        memcpy(&pstRecAttr->stEncryptCfg.au8Key, pstRecParams->stEncryptCfg.au8Key, PVR_HAL_MAX_CIPHER_KEY_LEN);
        pstRecAttr->stEncryptCfg.enType = (HI_UNF_CIPHER_ALG_E)pstRecParams->stEncryptCfg.enType;
        pstRecAttr->stEncryptCfg.u32KeyLen = pstRecParams->stEncryptCfg.u32KeyLen;
    }

    pstRecAttr->u64MaxFileSize = pstRecParams->u64MaxFileSize;
    pstRecAttr->u64MaxTimeInMs = pstRecParams->u64MaxTimeInMs;
    pstRecAttr->bRewind = (TRUE == pstRecParams->bRewind) ? HI_TRUE : HI_FALSE;
    memcpy(&pstRecAttr->szFileName, pstRecParams->szFileName, PVR_FILE_NAME_LENGTH);
    pstRecAttr->u32FileNameLen = pstRecParams->u32FileNameLen;
    return SUCCESS;
}

static S32  pvr_init(struct _PVR_DEVICE_S* pstDev, const PVR_RECINIT_PARAMS_S*   const  pstInitParams)
{
    S32 s32Ret = SUCCESS;
    BOOL bInitFlag = 0;
    U32 i = 0;

    HAL_PVR_ENTER();

    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);
    HAL_PVR_GET_VALUE(s_stPvrCtrl.bInitFlag, bInitFlag);
    if (TRUE == bInitFlag)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_DEBUG("Already init, just return success!\n");
        return SUCCESS;
    }

    HAL_PVR_SET_VALUE(s_stPvrCtrl.bInitFlag, TRUE);
    pvrInitChanInfo();

    s32Ret = HI_UNF_PVR_RecInit();
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_ERROR("call rec init failed, ret = %#x\n", s32Ret);
        goto ERR1;
    }

    s32Ret = HI_UNF_PVR_PlayInit();
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_ERROR("call play init failed, ret = %#x\n", s32Ret);
        goto ERR2;
    }

    for (i = 0; i < HAL_PVR_EVENT_MAX; i++)
    {
        s_stCallback[i].bUsed = FALSE;
        s_stCallback[i].pArgs = NULL;
        s_stCallback[i].pfnCallback = NULL;
        s_stCallback[i].enHalEvent = (PVR_EVENT_E)s_enEvent[i][0];
    }

    HAL_PVR_SET_VALUE(s_stPvrCtrl.s32PlyChnNum, 0);
    HAL_PVR_SET_VALUE(s_stPvrCtrl.s32RecChnNum, 0);
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
ERR2:
    (VOID)HI_UNF_PVR_RecDeInit();
ERR1:
    HAL_PVR_SET_VALUE(s_stPvrCtrl.bInitFlag, FALSE);
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
    HAL_PVR_ERROR("init failed, ret = %#x\n", s32Ret);
    return pvrErrCodeTransfer(s32Ret);
}

static S32  pvr_term(struct _PVR_DEVICE_S* pstDev, const PVR_TERM_PARAMS_S* const  pstTrmParams)
{
    S32 s32Ret = SUCCESS;
    BOOL bInitFlag = 0;
    S32 i = 0;
    S32 s32RecChnNum = 0;
    S32 s32PlyChnNum = 0;

    HAL_PVR_ENTER();

    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);
    HAL_PVR_GET_VALUE(s_stPvrCtrl.bInitFlag, bInitFlag);
    if (FALSE == bInitFlag)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_DEBUG("not init the pvr module or already terminal!\n");
        return SUCCESS;
    }

    HAL_PVR_GET_VALUE(s_stPvrCtrl.s32RecChnNum, s32RecChnNum);
    HAL_PVR_GET_VALUE(s_stPvrCtrl.s32PlyChnNum, s32PlyChnNum);
    if (0 < (s32RecChnNum + s32PlyChnNum))
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("some instance is not closed!\n");
        return ERROR_PVR_MODULE_BUSY;
    }

    HAL_PVR_SET_VALUE(s_stPvrCtrl.bInitFlag, FALSE);

    s32Ret = HI_UNF_PVR_PlayDeInit();
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_ERROR("play deinit failed, ret = %#x\n", s32Ret);
        goto ERR1;
    }

    s32Ret = HI_UNF_PVR_RecDeInit();
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_ERROR("rec deinit failed, ret = %#x\n", s32Ret);
        goto ERR2;
    }

    pvrInitChanInfo();
    for (i = 0; i < HAL_PVR_EVENT_MAX; i++)
    {
        s_stCallback[i].bUsed = FALSE;
        s_stCallback[i].pArgs = NULL;
        s_stCallback[i].pfnCallback = NULL;
        s_stCallback[i].enHalEvent = (PVR_EVENT_E)s_enEvent[i][0];
    }

    HAL_PVR_SET_VALUE(s_stPvrCtrl.s32PlyChnNum, 0);
    HAL_PVR_SET_VALUE(s_stPvrCtrl.s32RecChnNum, 0);
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;

ERR2:
    (VOID)HI_UNF_PVR_PlayInit();
ERR1:
    HAL_PVR_SET_VALUE(s_stPvrCtrl.bInitFlag, TRUE);
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_ERROR("terminal failed, ret = %#x\n", s32Ret);
    return pvrErrCodeTransfer(s32Ret);
}

static S32  pvr_get_capability(struct _PVR_DEVICE_S* pstDev, PVR_CAPABILITY_S*  const  pstCapability)
{
    HAL_PVR_ENTER();

    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pstCapability);
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    pstCapability->bSupportTimeShift = TRUE;
    pstCapability->u32SupportRecNumber = HAL_PVR_MAX_REC_NUM;
    pstCapability->u32SupportPlayNumber = HAL_PVR_MAX_PLAY_NUM;
    pstCapability->enStreamType = (PVR_STREAM_TYPE_E)(PVR_STREAM_TS | PVR_STREAM_ALL_TS);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32 pvr_rec_open(struct _PVR_DEVICE_S* pstDev, U32* const  pu32RecchnId, DMX_ID_E const enDmxId, const PVR_REC_OPENPARAMS_S* const pstRecParams)
{
    S32 s32Ret = SUCCESS;
    S32 s32Index = HAL_PVR_INVALD_CHN_INDEX;
    HI_UNF_PVR_REC_ATTR_S stRecAttr;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    S32 s32RecChnNum = 0;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pstRecParams);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pu32RecchnId);

    HAL_PVR_GET_VALUE(s_stPvrCtrl.s32RecChnNum, s32RecChnNum);
    if (HAL_PVR_MAX_REC_NUM <= s32RecChnNum)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("No free Record channel left!\n");
        return ERROR_PVR_NO_CHN_LEFT;
    }

    s32Index = pvrRequireChnId();
    if (HAL_PVR_INVALD_CHN_INDEX == s32Index)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("No free Record channel left!\n");
        return ERROR_PVR_NO_CHN_LEFT;
    }

    pstChnInfo = (HAL_PVR_CHAN_INFO_S*)HAL_PVR_MALLOC(sizeof(HAL_PVR_CHAN_INFO_S));
    if (NULL == pstChnInfo)
    {
        pvrReleaseChnId(s32Index);
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("malloc failed!\n");
        return ERROR_PVR_NO_MEM;
    }

    memset(pstChnInfo, 0x00, sizeof(HAL_PVR_CHAN_INFO_S));
    memset(&stRecAttr, 0x00, sizeof(stRecAttr));

    HAL_PVR_GET_DEMUXID(enDmxId, stRecAttr.u32DemuxID);
    s32Ret = pvrRecTransAttr(pstRecParams, &stRecAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_ERROR("create rec channel failed, ret = %#x\n", s32Ret);
        goto ERR;
    }
    s32Ret = HI_UNF_PVR_RecCreateChn(&(pstChnInfo->ChnId), &stRecAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_ERROR("create rec channel failed, ret = %#x\n", s32Ret);
        goto ERR;
    }

    HAL_PVR_ADD_VALUE(s_stPvrCtrl.s32RecChnNum, 1);
    pstChnInfo->u32PvrMagicNum = HAL_PVR_MAGIC_NUM;
    pstChnInfo->enType = HAL_PVR_REC;
    memcpy(&pstChnInfo->stUserCfg.stRecCfg, pstRecParams, sizeof(PVR_REC_OPENPARAMS_S));
    s_stChnIndex[s32Index].pChnInfo = pstChnInfo;
    *pu32RecchnId = s32Index;

    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
    HAL_PVR_EXIT();
    return SUCCESS;

ERR:
    if (HAL_PVR_INVALD_CHN_INDEX != s32Index)
    {
        pvrReleaseChnId(s32Index);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
    if (NULL != pstChnInfo)
    {
        HAL_PVR_FREE(pstChnInfo);
        pstChnInfo = NULL;
    }
    return pvrErrCodeTransfer(s32Ret);
}

static S32 pvr_rec_close(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId, const PVR_REC_CLOSECHNPARAMS_S*  pstReccloseParams)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_REC, (S32)u32RecchnId);

    pstChnInfo = s_stChnIndex[u32RecchnId].pChnInfo;
    s32Ret = HI_UNF_PVR_RecDestroyChn(pstChnInfo->ChnId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_ERROR("destroy rec channel failed, ret = %#x\n", s32Ret);
        goto ERR;
    }

    s_stChnIndex[u32RecchnId].pChnInfo = NULL;
    HAL_PVR_FREE(pstChnInfo);

    pvrReleaseChnId((S32)u32RecchnId);
    HAL_PVR_SUB_VALUE(s_stPvrCtrl.s32RecChnNum, 1);
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;

ERR:
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
    HAL_PVR_ERROR("close the rec channel(%d) failed, ret = %#x\n", u32RecchnId, s32Ret);
    return pvrErrCodeTransfer(s32Ret);
}

static S32 pvr_rec_start(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_REC, (S32)u32RecchnId);

    pstChnInfo = s_stChnIndex[u32RecchnId].pChnInfo;
    s32Ret = HI_UNF_PVR_RecStartChn(pstChnInfo->ChnId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("start record channel(%d) failed, ret = %#x\n", u32RecchnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();

    return SUCCESS;
}

static S32 pvr_rec_stop(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_REC, (S32)u32RecchnId);
    pstChnInfo = s_stChnIndex[u32RecchnId].pChnInfo;

    s32Ret = HI_UNF_PVR_RecStopChn(pstChnInfo->ChnId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("stop record channel(%d) failed, ret = %#x\n", u32RecchnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_rec_pause(struct _PVR_DEVICE_S* pstDev, const U32  u32RecchnId)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_REC, (S32)u32RecchnId);

    pstChnInfo = s_stChnIndex[u32RecchnId].pChnInfo;
    s32Ret = HI_UNF_PVR_RecPauseChn(pstChnInfo->ChnId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("pause record channel(%d) failed, ret = %#x\n", u32RecchnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_rec_resume(struct _PVR_DEVICE_S* pstDev, const U32  u32RecchnId)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_REC, (S32)u32RecchnId);

    pstChnInfo = s_stChnIndex[u32RecchnId].pChnInfo;
    s32Ret = HI_UNF_PVR_RecResumeChn(pstChnInfo->ChnId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("pause record channel(%d) failed, ret = %#x\n", u32RecchnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return s32Ret;
}

static S32  pvr_rec_getstatus(struct _PVR_DEVICE_S* pstDev, U32  u32RecchnId, PVR_REC_STATUS_S* pstRecStatus)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    HI_UNF_PVR_REC_STATUS_S stStatus;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pstRecStatus);
    HAL_PVR_CHECK_CHN(HAL_PVR_REC, (S32)u32RecchnId);

    memset(&stStatus, 0x00, sizeof(stStatus));
    pstChnInfo = s_stChnIndex[u32RecchnId].pChnInfo;
    s32Ret = HI_UNF_PVR_RecGetStatus(pstChnInfo->ChnId, &stStatus);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("get record channel(%d)'s status failed, ret = %#x\n", u32RecchnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }

    switch (stStatus.enState)
    {
        case HI_UNF_PVR_REC_STATE_INIT:
            pstRecStatus->enState = PVR_REC_STATE_INIT;
            break;
        case HI_UNF_PVR_REC_STATE_RUNNING:
            pstRecStatus->enState = PVR_REC_STATE_RUNNING;
            break;
        case HI_UNF_PVR_REC_STATE_PAUSE:
            pstRecStatus->enState = PVR_REC_STATE_PAUSE;
            break;
        case HI_UNF_PVR_REC_STATE_STOPPING:
            pstRecStatus->enState = PVR_REC_STATE_STOPPING;
            break;
        case HI_UNF_PVR_REC_STATE_STOP:
            pstRecStatus->enState = PVR_REC_STATE_STOP;
            break;
        default:
            pstRecStatus->enState = PVR_REC_STATE_INVALID;
            break;
    }
    pstRecStatus->u64CurWritePos = stStatus.u64CurWritePos;
    pstRecStatus->u32CurWriteFrame = stStatus.u32CurWriteFrame;
    pstRecStatus->u32CurTimeInMs = stStatus.u32CurTimeInMs;
    pstRecStatus->u32StartTimeInMs = stStatus.u32StartTimeInMs;
    pstRecStatus->u32EndTimeInMs = stStatus.u32EndTimeInMs;
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_rec_addpid(struct _PVR_DEVICE_S* pstDev, DMX_ID_E  enDmxId,  U32  u32RecchnId, U32 u32Pid, DMX_CHANNEL_TYPE_E enType)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    HI_UNF_PVR_REC_STATUS_S stStatus;

    HAL_PVR_ENTER();

    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);
    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_REC, (S32)u32RecchnId);
    if (HAL_PVR_INVALID_PID == u32Pid)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("invalid pid(%#x\n", u32Pid);
        return ERROR_INVALID_PARAM;
    }

    memset(&stStatus, 0x00, sizeof(stStatus));
    pstChnInfo = s_stChnIndex[u32RecchnId].pChnInfo;
    s32Ret = HI_UNF_PVR_RecGetStatus(pstChnInfo->ChnId, &stStatus);
    if (HI_UNF_PVR_REC_STATE_RUNNING == stStatus.enState)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("the channel has started, not support add pid!\n");
        return ERROR_PVR_REC_INVALID_STATE;
    }
    s32Ret = HI_UNF_PVR_RecAddPID(pstChnInfo->ChnId, u32Pid);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("add pid(%#x) to record channel(%d) failed, ret = %#x\n", u32Pid, u32RecchnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_rec_delpid(struct _PVR_DEVICE_S* pstDev, DMX_ID_E  enDmxId,  U32  u32RecchnId, U32 u32Pid)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    HI_UNF_PVR_REC_STATUS_S stStatus;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_REC, (S32)u32RecchnId);
    if (HAL_PVR_INVALID_PID == u32Pid)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("invalid pid(%#x\n", u32Pid);
        return ERROR_INVALID_PARAM;
    }

    memset(&stStatus, 0x00, sizeof(stStatus));
    pstChnInfo = s_stChnIndex[u32RecchnId].pChnInfo;
    s32Ret = HI_UNF_PVR_RecGetStatus(pstChnInfo->ChnId, &stStatus);
    if (HI_UNF_PVR_REC_STATE_RUNNING == stStatus.enState)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("the channel has started, not support add pid!\n");
        return ERROR_PVR_REC_INVALID_STATE;
    }

    s32Ret = HI_UNF_PVR_RecDelPID(pstChnInfo->ChnId, u32Pid);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("add pid(%#x) to record channel(%d) failed, ret = %#x\n", u32Pid, u32RecchnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_open(struct _PVR_DEVICE_S* pstDev,
                          U32* const pu32PlaychnId,
                          const PVR_PLAY_OPENPARAMS_S* const pstPlayParams,
                          HANDLE hAvPlay,
                          U32 u32TsBufferId)
{
    S32 s32Ret = SUCCESS;
    S32 s32Index = HAL_PVR_INVALD_CHN_INDEX;
    S32 s32PlyChnNum = 0;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    HI_UNF_PVR_PLAY_ATTR_S stPlayAttr;
    HI_HANDLE hTsBuffer = HAL_PVR_INVALID_HANDLE;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pu32PlaychnId);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pstPlayParams);
    HAL_PVR_GET_VALUE(s_stPvrCtrl.s32PlyChnNum, s32PlyChnNum);
    if (HAL_PVR_MAX_PLAY_NUM <= s32PlyChnNum)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("No free play channel left!\n");
        return ERROR_PVR_NO_CHN_LEFT;
    }

    HAL_PVR_GET_TSBUFFER(u32TsBufferId, hTsBuffer);
    if (HAL_PVR_INVALID_HANDLE == hAvPlay)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("Invalid avplay handle!\n");
        return ERROR_INVALID_PARAM;
    }

    if (PVR_STREAM_TS != pstPlayParams->enStreamType)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("only support ts playback(%d)\n", pstPlayParams->enStreamType);
        return ERROR_PVR_NOT_SUPPORT;
    }

    if ((0 == strlen(pstPlayParams->szFileName))
        || (PVR_MAX_FILENAME_LEN <= strlen(pstPlayParams->szFileName)))
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("Invalid filename length(0x%x)\n", (U32)strlen(pstPlayParams->szFileName));
        return ERROR_INVALID_PARAM;
    }

    s32Index = pvrRequireChnId();
    if (HAL_PVR_INVALD_CHN_INDEX == s32Index)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("No free play channel left!\n");
        return ERROR_PVR_NO_CHN_LEFT;
    }

    pstChnInfo = (HAL_PVR_CHAN_INFO_S*)HAL_PVR_MALLOC(sizeof(HAL_PVR_CHAN_INFO_S));
    if (NULL == pstChnInfo)
    {
        pvrReleaseChnId(s32Index);
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("malloc failed!\n");
        return ERROR_PVR_NO_MEM;
    }

    memset(pstChnInfo, 0x00, sizeof(HAL_PVR_CHAN_INFO_S));
    memset(&stPlayAttr, 0x00, sizeof(stPlayAttr));
    stPlayAttr.bIsClearStream = HI_TRUE;
    stPlayAttr.enStreamType = HI_UNF_PVR_STREAM_TYPE_TS;
    stPlayAttr.u32FileNameLen = strlen(pstPlayParams->szFileName);

    if (PVR_MAX_FILENAME_LEN < stPlayAttr.u32FileNameLen)
    {
        HAL_PVR_ERROR("u32FileNameLen err\n");
        goto ERR;
    }

    memcpy(stPlayAttr.szFileName, pstPlayParams->szFileName, stPlayAttr.u32FileNameLen);

    if (FALSE != pstPlayParams->stDecryptCfg.bDoCipher)
    {
        stPlayAttr.stDecryptCfg.bDoCipher = HI_TRUE;
        stPlayAttr.stDecryptCfg.enType = (HI_UNF_CIPHER_ALG_E)pstPlayParams->stDecryptCfg.enType;
        stPlayAttr.stDecryptCfg.u32KeyLen = pstPlayParams->stDecryptCfg.u32KeyLen;

        if (PVR_MAX_CIPHER_KEY_LEN < stPlayAttr.stDecryptCfg.u32KeyLen)
        {
            HAL_PVR_ERROR("u32KeyLen err\n");
            goto ERR;
        }

        memcpy(stPlayAttr.stDecryptCfg.au8Key,
               pstPlayParams->stDecryptCfg.au8Key,
               stPlayAttr.stDecryptCfg.u32KeyLen);
    }
    else
    {
        stPlayAttr.stDecryptCfg.bDoCipher = HI_FALSE;
        stPlayAttr.stDecryptCfg.u32KeyLen = 0;
    }

    s32Ret = HI_UNF_PVR_PlayCreateChn(&(pstChnInfo->ChnId), &stPlayAttr, hAvPlay, hTsBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_ERROR("create play channel failed, ret = %#x\n", s32Ret);
        goto ERR;
    }

    HAL_PVR_ADD_VALUE(s_stPvrCtrl.s32PlyChnNum, 1);
    pstChnInfo->u32PvrMagicNum = HAL_PVR_MAGIC_NUM;
    pstChnInfo->enType = HAL_PVR_PLY;
    memcpy(&pstChnInfo->stUserCfg.stPlyCfg, pstPlayParams, sizeof(PVR_PLAY_OPENPARAMS_S));
    s_stChnIndex[s32Index].pChnInfo = pstChnInfo;
    *pu32PlaychnId = s32Index;

    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
    HAL_PVR_EXIT();
    return SUCCESS;

ERR:
    pvrReleaseChnId(s32Index);
    if (NULL != pstChnInfo)
    {
        HAL_PVR_FREE(pstChnInfo);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
    return pvrErrCodeTransfer(s32Ret);
}

static S32  pvr_play_close(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_PLY, (S32)u32PlaychnId);
    pstChnInfo = s_stChnIndex[u32PlaychnId].pChnInfo;

    s32Ret = HI_UNF_PVR_PlayDestroyChn(pstChnInfo->ChnId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("stop play channel(%d) failed, ret = %#x\n", u32PlaychnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }

    s_stChnIndex[u32PlaychnId].pChnInfo = NULL;
    HAL_PVR_FREE(pstChnInfo);
    pvrReleaseChnId((S32)u32PlaychnId);
    HAL_PVR_SUB_VALUE(s_stPvrCtrl.s32PlyChnNum, 1);
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_start(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_PLY, (S32)u32PlaychnId);

    pstChnInfo = s_stChnIndex[u32PlaychnId].pChnInfo;
    s32Ret = HI_UNF_PVR_PlayStartChn(pstChnInfo->ChnId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("start play channel(%d) failed, ret = %#x\n", u32PlaychnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_stop(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    HI_UNF_AVPLAY_STOP_OPT_S stStop;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_PLY, (S32)u32PlaychnId);

    memset(&stStop, 0x00, sizeof(stStop));
    stStop.enMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
    stStop.u32TimeoutMs = 0;

    pstChnInfo = s_stChnIndex[u32PlaychnId].pChnInfo;
    s32Ret = HI_UNF_PVR_PlayStopChn(pstChnInfo->ChnId, &stStop);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("stop play channel(%d) failed, ret = %#x\n", u32PlaychnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_pause(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_PLY, (S32)u32PlaychnId);

    pstChnInfo = s_stChnIndex[u32PlaychnId].pChnInfo;
    s32Ret = HI_UNF_PVR_PlayPauseChn(pstChnInfo->ChnId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("stop play channel(%d) failed, ret = %#x\n", u32PlaychnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_resume(struct _PVR_DEVICE_S* pstDev,  const U32  u32PlaychnId)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_PLY, (S32)u32PlaychnId);

    pstChnInfo = s_stChnIndex[u32PlaychnId].pChnInfo;
    s32Ret = HI_UNF_PVR_PlayResumeChn(pstChnInfo->ChnId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("stop play channel(%d) failed, ret = %#x\n", u32PlaychnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_trick(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, const PVR_PLAY_TRICKPARAMS_S* pstPlayTrickMode)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    HI_UNF_PVR_PLAY_MODE_S stTrickMode;
    BOOL bStepMode = FALSE;
    BOOL bonBack = FALSE;
    HI_UNF_PVR_PLAY_SPEED_E enSpeed = HI_UNF_PVR_PLAY_SPEED_NORMAL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_PLY, (S32)u32PlaychnId);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pstPlayTrickMode);

    pstChnInfo = s_stChnIndex[u32PlaychnId].pChnInfo;
    s32Ret = pvrPlayGetTrickInfo(&bStepMode, &bonBack, &enSpeed, pstPlayTrickMode);
    if (SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        return s32Ret;
    }

    if (TRUE == bStepMode)
    {
        if (TRUE == bonBack)
        {
            HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
            HAL_PVR_ERROR("Not support step play for backward!\n");
            return ERROR_PVR_NOT_SUPPORT;
        }
        s32Ret = HI_UNF_PVR_PlayStep(pstChnInfo->ChnId, 1);
    }
    else
    {
        enSpeed = (TRUE == bonBack) ? (-1 * enSpeed) : enSpeed;
        memset(&stTrickMode, 0x00, sizeof(stTrickMode));
        stTrickMode.enSpeed = enSpeed;
        s32Ret = HI_UNF_PVR_PlayTPlay(pstChnInfo->ChnId, &stTrickMode);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("stop play channel(%d) failed, ret = %#x\n", u32PlaychnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_seek(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, const PVR_PLAY_SEEKPARAMS_S* pstPlaySeekParams)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    HI_UNF_PVR_PLAY_POSITION_S stPosition;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN((HAL_PVR_TYPE_E)HAL_PVR_PLY, (S32)u32PlaychnId);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pstPlaySeekParams);

    pstChnInfo = s_stChnIndex[u32PlaychnId].pChnInfo;
    memset(&stPosition, 0x00, sizeof(stPosition));
    s32Ret = pvrPlayGetSeekInfo(&stPosition, pstPlaySeekParams);
    if (SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        return s32Ret;
    }

    s32Ret = HI_UNF_PVR_PlaySeek(pstChnInfo->ChnId, &stPosition);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("seek play channel(%d) failed, ret = %#x\n", u32PlaychnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_getstatus(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, PVR_PLAY_STATUS_S* const pstStatus)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    HI_UNF_PVR_PLAY_STATUS_S stStatus;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_PLY, (S32)u32PlaychnId);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pstStatus);

    pstChnInfo = s_stChnIndex[u32PlaychnId].pChnInfo;
    memset(&stStatus, 0x00, sizeof(stStatus));
    s32Ret = HI_UNF_PVR_PlayGetStatus(pstChnInfo->ChnId, &stStatus);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("get play channel(%d) status failed, ret = %#x\n", u32PlaychnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
    (VOID)pvrPlayTransStatus(pstStatus, stStatus);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_getfileattrbychannel(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, PVR_FILE_ATTR_S* const pAttr)
{
    S32 s32Ret = SUCCESS;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;
    HI_UNF_PVR_FILE_ATTR_S stFileAttr;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_CHN(HAL_PVR_PLY, (S32)u32PlaychnId);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pAttr);

    pstChnInfo = s_stChnIndex[u32PlaychnId].pChnInfo;
    memset(&stFileAttr, 0x00, sizeof(stFileAttr));
    s32Ret = HI_UNF_PVR_PlayGetFileAttr(pstChnInfo->ChnId, &stFileAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("get play channel(%d) file attr failed, ret = %#x\n", u32PlaychnId, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }

    switch (stFileAttr.enIdxType)
    {
        case HI_UNF_PVR_REC_INDEX_TYPE_NONE:
            pAttr->enIdxType = PVR_REC_INDEX_TYPE_NONE;
            break;
        case HI_UNF_PVR_REC_INDEX_TYPE_VIDEO:
            pAttr->enIdxType = PVR_REC_INDEX_TYPE_VIDEO;
            break;
        case HI_UNF_PVR_REC_INDEX_TYPE_AUDIO:
            pAttr->enIdxType = PVR_REC_INDEX_TYPE_AUDIO;
            break;
        default:
            pAttr->enIdxType = PVR_REC_INDEX_TYPE_BUTT;
            break;
    }

    pAttr->u32FrameNum = stFileAttr.u32FrameNum;
    pAttr->u32StartTimeInMs = stFileAttr.u32StartTimeInMs;
    pAttr->u32EndTimeInMs = stFileAttr.u32EndTimeInMs;
    pAttr->u64ValidSizeInByte = stFileAttr.u64ValidSizeInByte;
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_play_getfileattrbyfilename(struct _PVR_DEVICE_S* pstDev, const  CHAR* pFileName, PVR_FILE_ATTR_S* const pAttr)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_PVR_FILE_ATTR_S stFileAttr;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pFileName);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pAttr);

    memset(&stFileAttr, 0x00, sizeof(stFileAttr));
    s32Ret = HI_UNF_PVR_GetFileAttrByFileName(pFileName, &stFileAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("get file attr failed, ret = %#x\n", s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }

    switch (stFileAttr.enIdxType)
    {
        case HI_UNF_PVR_REC_INDEX_TYPE_NONE:
            pAttr->enIdxType = PVR_REC_INDEX_TYPE_NONE;
            break;
        case HI_UNF_PVR_REC_INDEX_TYPE_VIDEO:
            pAttr->enIdxType = PVR_REC_INDEX_TYPE_VIDEO;
            break;
        case HI_UNF_PVR_REC_INDEX_TYPE_AUDIO:
            pAttr->enIdxType = PVR_REC_INDEX_TYPE_AUDIO;
            break;
        default:
            pAttr->enIdxType = PVR_REC_INDEX_TYPE_BUTT;
            break;
    }

    pAttr->u32FrameNum = stFileAttr.u32FrameNum;
    pAttr->u32StartTimeInMs = stFileAttr.u32StartTimeInMs;
    pAttr->u32EndTimeInMs = stFileAttr.u32EndTimeInMs;
    pAttr->u64ValidSizeInByte = stFileAttr.u64ValidSizeInByte;
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_usrdata_setbyfilename(struct _PVR_DEVICE_S* pstDev, const  CHAR* pFileName,  U8* pInfo,  U32 u32UsrDataLen)
{
    U32 i = 0;
    S32 s32Ret = SUCCESS;
    BOOL bRecFlag = FALSE;
    HAL_PVR_CHAN_INFO_S* pstChnInfo = NULL;

    HAL_PVR_ENTER();

    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);
    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pFileName);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pInfo);

    for (i = 0; i < HAL_PVR_MAX_REC_NUM + HAL_PVR_MAX_PLAY_NUM; i++)
    {
        if (FALSE == s_stChnIndex[i].bUsed)
        {
            continue;
        }
        pstChnInfo = s_stChnIndex[i].pChnInfo;
        if ((NULL != pstChnInfo)
            && (HAL_PVR_REC == pstChnInfo->enType)
            && (0 == strncmp(pstChnInfo->stUserCfg.stRecCfg.szFileName, pFileName,
                             pstChnInfo->stUserCfg.stRecCfg.u32FileNameLen)))
        {
            bRecFlag = TRUE;
        }
    }

    if (FALSE == bRecFlag)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("set userdata only support recording!\n");
        return ERROR_PVR_NOT_SUPPORT;
    }

    s32Ret = HI_UNF_PVR_SetUsrDataInfoByFileName(pFileName, pInfo, u32UsrDataLen);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("set userdata failed, ret = %#x\n", s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_usrdata_getbyfilename(struct _PVR_DEVICE_S* pstDev, const  CHAR* pFileName,  U8* pInfo,  U32 u32BufLen,  U32* pUsrDataLen)
{
    S32 s32Ret = SUCCESS;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pFileName);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pUsrDataLen);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pInfo);

    s32Ret = HI_UNF_PVR_GetUsrDataInfoByFileName(pFileName, pInfo, u32BufLen, pUsrDataLen);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("get userdata failed, ret = %#x\n", s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();

    return s32Ret;
}
static S32  pvr_event_register(struct _PVR_DEVICE_S* pstDev, PVR_EVENT_E enEvent, pvr_eventCallBack pCallBack, VOID* pArgs)
{
    U32 i = 0;
    S32 s32Ret = SUCCESS;
    HI_UNF_PVR_EVENT_E enSdkEvent = HI_UNF_PVR_EVENT_BUTT;
    HAL_PVR_EVENT_CTRL_S* pstCallback = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pCallBack);
    for (i = 0; i < HAL_PVR_EVENT_MAX; i++)
    {
        if (enEvent == s_stCallback[i].enHalEvent)
        {
            pstCallback = &(s_stCallback[i]);
            enSdkEvent = (HI_UNF_PVR_EVENT_E)s_enEvent[i][1];
            break;
        }
    }

    if (NULL == pstCallback)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("Invalid event:0x%08x\n", enEvent);
        return ERROR_PVR_INTF_EVENT_INVAL;
    }

    if (TRUE == pstCallback->bUsed)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("event:0x%08x has already registered\n", enEvent);
        return ERROR_PVR_ALREADY;
    }

    pstCallback->bUsed = TRUE;
    pstCallback->pfnCallback = pCallBack;
    pstCallback->pArgs = pArgs;
    s32Ret = HI_UNF_PVR_RegisterEvent(enSdkEvent, pvrEventCallback, pArgs);
    if (HI_SUCCESS != s32Ret)
    {
        pstCallback->bUsed = FALSE;
        pstCallback->pfnCallback = NULL;
        pstCallback->pArgs = NULL;
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("register event(0x%08x) failed, ret = %#x\n", enEvent, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_event_unregister(struct _PVR_DEVICE_S* pstDev, PVR_EVENT_E enEvent)
{
    U32 i = 0;
    S32 s32Ret = SUCCESS;
    HI_UNF_PVR_EVENT_E enSdkEvent = HI_UNF_PVR_EVENT_BUTT;
    HAL_PVR_EVENT_CTRL_S* pstCallback = NULL;

    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);

    for (i = 0; i < HAL_PVR_EVENT_MAX; i++)
    {
        if (enEvent == s_stCallback[i].enHalEvent)
        {
            pstCallback = &(s_stCallback[i]);
            enSdkEvent = (HI_UNF_PVR_EVENT_E)s_enEvent[i][1];
            break;
        }
    }

    if (NULL == pstCallback)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("Invalid event:0x%08x\n", enEvent);
        return ERROR_PVR_INTF_EVENT_INVAL;
    }

    if (FALSE == pstCallback->bUsed)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("event:0x%08x has already unregistered\n", enEvent);
        return ERROR_PVR_ALREADY;
    }

    s32Ret = HI_UNF_PVR_UnRegisterEvent(enSdkEvent);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);
        HAL_PVR_ERROR("unregister event(0x%08x) failed, ret = %#x\n", enEvent, s32Ret);
        return pvrErrCodeTransfer(s32Ret);
    }

    pstCallback->bUsed = FALSE;
    pstCallback->pfnCallback = NULL;
    pstCallback->pArgs = NULL;
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_EXIT();
    return SUCCESS;
}

static S32  pvr_remove_file(struct _PVR_DEVICE_S* pstDev, const  CHAR* pFileName)
{
    HAL_PVR_ENTER();
    HAL_PVR_LOCK(s_stPvrCtrl.PvrHandleMutex);

    HAL_PVR_CHECK_INIT_RETURN(ERROR_NOT_INITED);
    HAL_PVR_CHECK_NULL_POINTER_RETURN(pFileName);
    HAL_PVR_UNLOCK(s_stPvrCtrl.PvrHandleMutex);

    HI_UNF_PVR_RemoveFile(pFileName);

    HAL_PVR_EXIT();
    return SUCCESS;
}

#ifdef TVOS_PLATFORM
static int pvr_device_close(struct hw_device_t* pstDev)
{
    struct _PVR_DEVICE_S* pCtx = (struct _PVR_DEVICE_S*)pstDev;

    if (pCtx)
    {
        Hal_Free(pCtx);
        pCtx = NULL;
    }

    return 0;
}

static int pvr_device_open(const struct hw_module_t* module, const char* name,
                           struct hw_device_t** device)
{
    if (strcmp(name, DEMUX_HARDWARE_DEMUX0) != 0)
    {
        return -EINVAL;
    }

    if (NULL == device)
    {
        return HI_FAILURE;
    }

    PVR_DEVICE_S* pstDev = (PVR_DEVICE_S*)Hal_Malloc(sizeof(PVR_DEVICE_S));

    if (NULL == pstDev)
    {
        HAL_ERROR("malloc memory failed! ");
        return -ENOMEM;
    }


    HI_UNF_ADVCA_Init();

    /* initialize our state here */
    memset(pstDev, 0, sizeof(PVR_DEVICE_S));

    /* initialize the procs */
    pstDev->stCommon.tag = HARDWARE_DEVICE_TAG;
    pstDev->stCommon.version = PVR_DEVICE_API_VERSION_1_0;
    pstDev->stCommon.module = (hw_module_t*)module;
    pstDev->stCommon.close = pvr_device_close;

    /* register the callbacks */
    pstDev->pvr_init                        = pvr_init;
    pstDev->pvr_term                        = pvr_term;
    pstDev->pvr_get_capability              = pvr_get_capability;
    pstDev->pvr_rec_open                    = pvr_rec_open;
    pstDev->pvr_rec_close                   = pvr_rec_close;
    pstDev->pvr_rec_start                   = pvr_rec_start;
    pstDev->pvr_rec_stop                    = pvr_rec_stop;
    pstDev->pvr_rec_pause                   = pvr_rec_pause;
    pstDev->pvr_rec_resume                  = pvr_rec_resume;
    pstDev->pvr_rec_getstatus               = pvr_rec_getstatus;
    pstDev->pvr_rec_addpid                  = pvr_rec_addpid;
    pstDev->pvr_rec_delpid                  = pvr_rec_delpid;
    pstDev->pvr_play_open                   = pvr_play_open;
    pstDev->pvr_play_close                  = pvr_play_close;
    pstDev->pvr_play_start                  = pvr_play_start;
    pstDev->pvr_play_stop                   = pvr_play_stop;
    pstDev->pvr_play_pause                  = pvr_play_pause;
    pstDev->pvr_play_resume                 = pvr_play_resume;
    pstDev->pvr_play_trick                  = pvr_play_trick;
    pstDev->pvr_play_seek                   = pvr_play_seek;
    pstDev->pvr_play_getstatus              = pvr_play_getstatus;
    pstDev->pvr_play_getfileattrbychannel   = pvr_play_getfileattrbychannel;
    pstDev->pvr_play_getfileattrbyfilename  = pvr_play_getfileattrbyfilename;
    pstDev->pvr_usrdata_setbyfilename       = pvr_usrdata_setbyfilename;
    pstDev->pvr_usrdata_getbyfilename       = pvr_usrdata_getbyfilename;
    pstDev->pvr_event_register              = pvr_event_register;
    pstDev->pvr_event_unregister            = pvr_event_unregister;
    pstDev->pvr_remove_file                 = pvr_remove_file;

    *device = &(pstDev->stCommon);

    return SUCCESS;
}

static struct hw_module_methods_t pvr_module_methods =
{
open:
    pvr_device_open,
};
PVR_MODULE_S HAL_MODULE_INFO_SYM =
{
stCommon:
    {
    tag:
        HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
    id:
        PVR_HARDWARE_MODULE_ID,
    name:          "Sample hwcomposer module"
        ,
    author:        "The Android Open Source Project"
        ,
    methods:
        &pvr_module_methods,
    dso:
        NULL,
    reserved:
        {0},
    }
};
#else

static PVR_DEVICE_S s_stDevice_pvr =
{
    /* register the callbacks */
    .pvr_init                        = pvr_init,
    .pvr_term                        = pvr_term,
    .pvr_get_capability              = pvr_get_capability,
    .pvr_rec_open                    = pvr_rec_open,
    .pvr_rec_close                   = pvr_rec_close,
    .pvr_rec_start                   = pvr_rec_start,
    .pvr_rec_stop                    = pvr_rec_stop,
    .pvr_rec_pause                   = pvr_rec_pause,
    .pvr_rec_resume                  = pvr_rec_resume,
    .pvr_rec_getstatus               = pvr_rec_getstatus,
    .pvr_rec_addpid                  = pvr_rec_addpid,
    .pvr_rec_delpid                  = pvr_rec_delpid,
    .pvr_play_open                   = pvr_play_open,
    .pvr_play_close                  = pvr_play_close,
    .pvr_play_start                  = pvr_play_start,
    .pvr_play_stop                   = pvr_play_stop,
    .pvr_play_pause                  = pvr_play_pause,
    .pvr_play_resume                 = pvr_play_resume,
    .pvr_play_trick                  = pvr_play_trick,
    .pvr_play_seek                   = pvr_play_seek,
    .pvr_play_getstatus              = pvr_play_getstatus,
    .pvr_play_getfileattrbychannel   = pvr_play_getfileattrbychannel,
    .pvr_play_getfileattrbyfilename  = pvr_play_getfileattrbyfilename,
    .pvr_usrdata_setbyfilename       = pvr_usrdata_setbyfilename,
    .pvr_usrdata_getbyfilename       = pvr_usrdata_getbyfilename,
    .pvr_event_register              = pvr_event_register,
    .pvr_event_unregister            = pvr_event_unregister,
    .pvr_remove_file                 = pvr_remove_file,
};

PVR_DEVICE_S* getPVRDevice()
{
    return &s_stDevice_pvr;
}

#endif

