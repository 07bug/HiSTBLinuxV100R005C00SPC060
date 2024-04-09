
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "hi_debug.h"
#include "hi_common.h"
#include "hi_unf_so.h"
#include "hi_unf_subt.h"
#include "hi_unf_ttx.h"
#include "hi_unf_cc.h"
#include "caption_cc_xds.h"
#include "caption_subt_out.h"
#include "caption_ttx_out.h"
#include "caption_ttx_msg.h"
#include "caption_cc_out.h"

#include "tvos_hal_common.h"
#include "tvos_hal_type.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_caption.h"

#ifdef LINUX_OS
#include "hi_go.h"
#endif

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "CAPTION"

#define CAPTION_HEADER_VERSION          1
#define CAPTION_DEVICE_API_VERSION_1_0  HARDWARE_DEVICE_API_VERSION_2(1, 0, CAPTION_HEADER_VERSION)

/** Invalid vout handle */
#define INVALID_CAPTION_HANDLE       (0)

/*max interval, Unit: millisecond*/
#define CAPTION_MAX_INTERVAL         (10 * 1000)

/*ttx line data, row num*/
#define CAPTION_TTX_ROW_NUM         (32)

/*ttx line data, column num*/
#define CAPTION_TTX_COLUMN_NUM      (46)

#define CAPTION_UNUSED(_var) (HI_VOID)(_var)

#define CAPTION_CHK_SUBT_INIT() \
    do { \
        if (FALSE == s_stCaptionModule.bSubtInited) \
        { \
            HAL_ERROR("Subt Caption not inited ."); \
            return ERROR_NOT_INITED; \
        } \
    } while(0)

#define CAPTION_CHK_TTX_INIT() \
    do { \
        if (FALSE == s_stCaptionModule.bTtxInited) \
        { \
            HAL_ERROR("Teletext not inited ."); \
            return ERROR_NOT_INITED; \
        } \
    } while(0)

#define CAPTION_CHK_CC_INIT() \
    do { \
        if (FALSE == s_stCaptionModule.bCcInited) \
        { \
            HAL_ERROR("CC Caption not inited ."); \
            return ERROR_NOT_INITED; \
        } \
    } while(0)

#define CAPTION_CHK_PARA( val  ) \
    do \
    { \
        if ((val)) \
        { \
            HAL_ERROR("param is invalid ."); \
            return ERROR_INVALID_PARAM; \
        }; \
    } while (0)

/*lint -e607*/
#define CAPTION_CHK_PTR(ptr) \
    do { \
        if (NULL == ptr) \
        {\
            HAL_ERROR("ptr is null"); \
            return ERROR_NULL_PTR; \
        } \
    } while(0)

#define CAPTION_SLEEPMS(ms)  \
    do{\
        struct timespec  _ts;\
        _ts.tv_sec = (ms) >= 1000 ? (ms)/1000 : 0;\
        _ts.tv_nsec =  (_ts.tv_sec > 0) ? ((ms)%1000)*1000000LL : (ms) * 1000000LL;\
        (HI_VOID)nanosleep(&_ts, NULL);\
    }while (0)

/* init flag */
typedef struct _SUBT_MODULE_S
{
    HANDLE  hSo;    /**<Subtitle Output Handle*//**<CNcomment:Subt 输出模块句柄 */
    HANDLE  hSubt;  /**<Subtitle Handle*//**<CNcomment:Subt 模块句柄 */
    HANDLE  hOut;   /**<Subtitle OSD Output Handle*//**<CNcomment:Subt 图层输出模块句柄 */
    CAPTION_STATE_E     enStatus;         /**<Subtitle Running Status*//**<CNcomment:Subt 模块运行状态 */
    CAPTION_SUBT_DATA_E enSubtDataType;   /**<Subtitle Data Type*//**<CNcomment:Subt 数据类型 */
    U32                 u32SubtItemNum;    /**<Subtitle Item number*//**<CNcomment:已设置的Subt服务项数量 */
    CAPTION_SUBT_ITEM_S astSubtItems[SUBT_ITEM_MAX_NUM]; /**<The item of the subtitling content *//**<CNcomment:字幕内容 */
    CAPTION_SUBT_ITEM_S stSubtItem;       /**<Subtitle Item select by user*//**<CNcomment:用户选择的Subt服务项 */
    CAPTION_GETPTS_CALLBACK_PFN pfnGetPts; /**<get pts call bak function *//**<CNcomment:获取PTS 回调函数 */
} SUBT_MODULE_S;

typedef struct _TTX_MODULE_S
{
    HANDLE  hTTX;   /**<Teletext Handle*//**<CNcomment:TTX 模块句柄 */
    HANDLE  hOut;   /**<Teletext OSD Output Handle*//**<CNcomment:Teletext 图层输出模块句柄 */
    CAPTION_TTX_DATA_SOURCE_E enDataSource; /**<Teletext data source *//**<CNcomment:Teletext 数据来源 */
    CAPTION_TTX_OUTPUT_TYPE_E enOutputType; /**<out put type*//**<CNcomment: ttx 字幕输出类型 */
    CAPTION_STATE_E           enStatus;     /**<Teletext Running Status*//**<CNcomment:TTX 模块运行状态 */
    CAPTION_TTX_CONTENT_S     stTtxItem;    /**<Teletext Item*//**<CNcomment:TTX 服务项 */
    CAPTION_GETPTS_CALLBACK_PFN pfnGetPts;  /**<get pts call bak function *//**<CNcomment:获取PTS 回调函数 */
    pthread_t     pMsgTaskId;              /**<msg task id*//**<CNcomment: 消息处理任务ID */
} TTX_MODULE_S;

typedef struct _CC_MODULE_S
{
    HANDLE  hCC;     /**<ClosedCaption Handle*//**<CNcomment:CC 模块句柄 */
    HANDLE  hOut;    /**<ClosedCaption OSD Output Handle*//**<CNcomment:CC 图层输出模块句柄 */
    CAPTION_STATE_E    enStatus;         /**<ClosedCaption Running Status*//**<CNcomment:CC 模块运行状态 */
    CAPTION_CC_DATA_E  enCCType;         /**<ClosedCaption data type *//**<CNcomment:CC 数据类型 */
    CAPTION_GETPTS_CALLBACK_PFN pfnGetPts; /**<get pts call bak function *//**<CNcomment:获取PTS 回调函数 */
} CC_MODULE_S;

typedef struct _CAPTION_MODULE_INFO_S
{
    BOOL          bSubtInited;  /**<Subtitle Init Flag*//**<CNcomment:subtitle字幕初始化标识 */
    BOOL          bTtxInited;  /**<Teletext Init Flag*//**<CNcomment:teletext初始化标识 */
    BOOL          bCcInited;  /**<CC Init Flag*//**<CNcomment:CC字幕初始化标识 */
    SUBT_MODULE_S stSubtInfo;      /**<subtitle mode info*//**<CNcomment: subtitle 字幕模块信息 */
    TTX_MODULE_S  stTtxInfo;       /**<teletext mode info*//**<CNcomment: teletext 字幕模块信息 */
    CC_MODULE_S   stCCInfo;        /**<cc mode info*//**<CNcomment: cc 字幕模块信息 */
    HI_RECT_S     stDisplayRect;   /**<display info*//**<CNcomment: 显示位置信息 */
} CAPTION_MODULE_INFO_S;

typedef struct _CAPTION_TTX_KEY_MAP_S
{
    CAPTION_TTX_KEY_E enHalKey;    /**<Caption hal ttx key *//**<CNcomment:HAL 层TTX 字幕key 类型 */
    HI_UNF_TTX_KEY_E  enUnfKey;    /**<Caption unf ttx keyInit Flag*//**<CNcomment:UNF 层TTX 字幕key 类型 */
} CAPTION_TTX_KEY_MAP_S;

static CAPTION_MODULE_INFO_S s_stCaptionModule;

static CAPTION_TTX_KEY_MAP_S s_stTtxKeyMap[] =
{
    {CAPTION_TTX_KEY_0, HI_UNF_TTX_KEY_0},
    {CAPTION_TTX_KEY_1, HI_UNF_TTX_KEY_1},
    {CAPTION_TTX_KEY_2, HI_UNF_TTX_KEY_2},
    {CAPTION_TTX_KEY_3, HI_UNF_TTX_KEY_3},
    {CAPTION_TTX_KEY_4, HI_UNF_TTX_KEY_4},
    {CAPTION_TTX_KEY_5, HI_UNF_TTX_KEY_5},
    {CAPTION_TTX_KEY_6, HI_UNF_TTX_KEY_6},
    {CAPTION_TTX_KEY_7, HI_UNF_TTX_KEY_7},
    {CAPTION_TTX_KEY_8, HI_UNF_TTX_KEY_8},
    {CAPTION_TTX_KEY_9, HI_UNF_TTX_KEY_9},
    {CAPTION_TTX_KEY_PREVIOUS_PAGE, HI_UNF_TTX_KEY_PREVIOUS_PAGE},
    {CAPTION_TTX_KEY_NEXT_PAGE, HI_UNF_TTX_KEY_NEXT_PAGE},
    {CAPTION_TTX_KEY_PREVIOUS_SUBPAGE, HI_UNF_TTX_KEY_PREVIOUS_SUBPAGE},
    {CAPTION_TTX_KEY_NEXT_SUBPAGE, HI_UNF_TTX_KEY_NEXT_SUBPAGE},
    {CAPTION_TTX_KEY_PREVIOUS_MAGAZINE, HI_UNF_TTX_KEY_PREVIOUS_MAGAZINE},
    {CAPTION_TTX_KEY_NEXT_MAGAZINE, HI_UNF_TTX_KEY_NEXT_MAGAZINE},
    {CAPTION_TTX_KEY_RED, HI_UNF_TTX_KEY_RED},
    {CAPTION_TTX_KEY_GREEN, HI_UNF_TTX_KEY_GREEN},
    {CAPTION_TTX_KEY_YELLOW, HI_UNF_TTX_KEY_YELLOW},
    {CAPTION_TTX_KEY_CYAN, HI_UNF_TTX_KEY_CYAN},
    {CAPTION_TTX_KEY_INDEX, HI_UNF_TTX_KEY_INDEX},
    {CAPTION_TTX_KEY_REVEAL, HI_UNF_TTX_KEY_REVEAL},
    {CAPTION_TTX_KEY_HOLD, HI_UNF_TTX_KEY_HOLD},
    {CAPTION_TTX_KEY_MIX, HI_UNF_TTX_KEY_MIX},
    {CAPTION_TTX_KEY_UPDATE, HI_UNF_TTX_KEY_UPDATE},
};

#ifdef LINUX_OS
static BOOL s_bHigoInit = FALSE;
#endif

//hal BOOL -> unf HI_BOOL
static inline HI_BOOL caption_bool_hal_to_unf(BOOL bHalValue)
{
    return (HI_BOOL)((TRUE == bHalValue) ? HI_TRUE : HI_FALSE);
}

//unf  HI_BOOL  -> hal BOOL
static inline BOOL caption_bool_unf_to_hal(HI_BOOL bUnfValue)
{
    return (BOOL)((HI_TRUE == bUnfValue) ? TRUE : FALSE);
}

static S32 caption_subt_get_pts(U32 u32UserData, HI_S64* ps64CurrentPts)
{
    U32 u32CurrentPts = 0;

    CAPTION_CHK_PTR(ps64CurrentPts);

    if (CAPTION_SHOW != s_stCaptionModule.stSubtInfo.enStatus)
    {
        HAL_ERROR("status error!! subtitle status = 0x%08x", s_stCaptionModule.stSubtInfo.enStatus);
        return FAILURE;
    }

    s_stCaptionModule.stSubtInfo.pfnGetPts(&u32CurrentPts);

    *ps64CurrentPts = (HI_S64)u32CurrentPts;

    return HI_SUCCESS;
}

static S32 caption_subt_draw(U32 u32UserData, const HI_UNF_SO_SUBTITLE_INFO_S* pstInfo, HI_VOID* pvExtData)
{
    CAPTION_CHK_PTR(pstInfo);

    if (CAPTION_SHOW != s_stCaptionModule.stSubtInfo.enStatus)
    {
        HAL_ERROR("status error!! subtitle status = 0x%08x", s_stCaptionModule.stSubtInfo.enStatus);
        return FAILURE;
    }

    caption_subt_output_draw(u32UserData, pstInfo, pvExtData);

    return HI_SUCCESS;
}

static S32 caption_subt_clear(U32 u32UserData, HI_VOID* pvExtData)
{
    if (CAPTION_SHOW != s_stCaptionModule.stSubtInfo.enStatus)
    {
        HAL_ERROR("status error!! subtitle status = 0x%08x", s_stCaptionModule.stSubtInfo.enStatus);
        return FAILURE;
    }

    caption_subt_output_clear(u32UserData, pvExtData);

    return HI_SUCCESS;
}

static S32 caption_subt_get_so_data(HI_UNF_SUBT_DATA_S* pstSubtData, HI_UNF_SO_SUBTITLE_INFO_S* pstSubtitleOut)
{
    CAPTION_CHK_PTR(pstSubtData);
    CAPTION_CHK_PTR(pstSubtitleOut);

    if (HI_UNF_SUBT_PAGE_NORMAL_CASE == pstSubtData->enPageState)
    {
        pstSubtitleOut->unSubtitleParam.stGfx.enMsgType = HI_UNF_SO_DISP_MSG_NORM;
    }
    else
    {
        pstSubtitleOut->unSubtitleParam.stGfx.enMsgType = HI_UNF_SO_DISP_MSG_ERASE;
    }

    pstSubtitleOut->unSubtitleParam.stGfx.x = pstSubtData->u32x;
    pstSubtitleOut->unSubtitleParam.stGfx.y = pstSubtData->u32y;
    pstSubtitleOut->unSubtitleParam.stGfx.w = pstSubtData->u32w;
    pstSubtitleOut->unSubtitleParam.stGfx.h = pstSubtData->u32h;

    pstSubtitleOut->unSubtitleParam.stGfx.s32BitWidth = (S32)pstSubtData->u32BitWidth;
    memcpy(pstSubtitleOut->unSubtitleParam.stGfx.stPalette, pstSubtData->pvPalette, pstSubtData->u32PaletteItem);

    pstSubtitleOut->unSubtitleParam.stGfx.s64Pts = pstSubtData->u32PTS;
    pstSubtitleOut->unSubtitleParam.stGfx.u32Duration = pstSubtData->u32Duration;

    pstSubtitleOut->unSubtitleParam.stGfx.u32Len = pstSubtData->u32DataLen;
    pstSubtitleOut->unSubtitleParam.stGfx.pu8PixData = pstSubtData->pu8SubtData;

    pstSubtitleOut->unSubtitleParam.stGfx.u32CanvasWidth = pstSubtData->u32DisplayWidth;
    pstSubtitleOut->unSubtitleParam.stGfx.u32CanvasHeight = pstSubtData->u32DisplayHeight;

    return HI_SUCCESS;
}

static S32 caption_subt_callback(U32 u32UserData, HI_UNF_SUBT_DATA_S* pstSubtData)
{
    S32 s32Ret = SUCCESS;
    HANDLE hSO = INVALID_CAPTION_HANDLE;
    HI_UNF_SO_SUBTITLE_INFO_S stSubtitleOut;

    CAPTION_CHK_PTR(pstSubtData);

    memset(&stSubtitleOut, 0, sizeof(HI_UNF_SO_SUBTITLE_INFO_S));

    caption_subt_get_so_data(pstSubtData, &stSubtitleOut);

    hSO = s_stCaptionModule.stSubtInfo.hSo;

    if ((INVALID_CAPTION_HANDLE != hSO) && (CAPTION_SHOW == s_stCaptionModule.stSubtInfo.enStatus))
    {
        s32Ret = HI_UNF_SO_SendData(hSO, &stSubtitleOut, 1000);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    return HI_SUCCESS;
}

static S32 caption_subt_inject_data(U8* pu8Data, U32 u32DataSize)
{
    U32 u32SubtPID = 0;
    S32 s32Ret = SUCCESS;
    HANDLE hSubt = INVALID_CAPTION_HANDLE;

    if (CAPTION_SHOW != s_stCaptionModule.stSubtInfo.enStatus)
    {
        HAL_ERROR("status error!! subtitle status = 0x%08x", s_stCaptionModule.stSubtInfo.enStatus);
        return FAILURE;
    }

    hSubt = s_stCaptionModule.stSubtInfo.hSubt;
    u32SubtPID = s_stCaptionModule.stSubtInfo.stSubtItem.u32SubtPID;

    s32Ret = HI_UNF_SUBT_InjectData(hSubt, u32SubtPID, pu8Data, u32DataSize);

    //HAL_DEBUG("%s,%d  u32DataSize(%d)", __func__, __LINE__, u32DataSize);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return s32Ret;
}

static S32 caption_ttx_inject_data(U8* pu8Data, U32 u32DataSize)
{
    S32 s32Ret = SUCCESS;
    HANDLE hTTX = INVALID_CAPTION_HANDLE;

    hTTX = s_stCaptionModule.stTtxInfo.hTTX;

    if (CAPTION_SHOW != s_stCaptionModule.stTtxInfo.enStatus)
    {
        HAL_ERROR("status error!! ttx status = 0x%08x", s_stCaptionModule.stTtxInfo.enStatus);
        return FAILURE;
    }

    s32Ret = HI_UNF_TTX_InjectData(hTTX, pu8Data, u32DataSize);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return SUCCESS;
}

static S32 caption_cc_inject_data(U8* pu8Data, U32 u32DataSize)
{
    S32 s32Ret = SUCCESS;
    HANDLE hCC = INVALID_CAPTION_HANDLE;
    CAPTION_CC_DATA_E enCCDataType = CAPTION_CC_DATA_BUTT;

    if (CAPTION_SHOW != s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    hCC = s_stCaptionModule.stCCInfo.hCC;
    enCCDataType = s_stCaptionModule.stCCInfo.enCCType;

    switch (enCCDataType)
    {
        case CAPTION_CC_DATA_608:
        case CAPTION_CC_DATA_708:
        {
            HI_UNF_CC_USERDATA_S stUserData;

            stUserData.pu8userdata = pu8Data;
            stUserData.u32dataLen = u32DataSize;

            s32Ret = HI_UNF_CC_InjectUserData(hCC, &stUserData);

            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
                return FAILURE;
            }

            break;
        }

        case CAPTION_CC_DATA_ARIB:
        {
            s32Ret = HI_UNF_CC_InjectPESData(hCC, pu8Data, u32DataSize);

            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x), hCC = 0x%x", __func__, __LINE__, s32Ret, hCC);
                return FAILURE;
            }

            break;
        }

        default:
        {
            HAL_ERROR("%s,%d error!! type(0x%08x)", __func__, __LINE__, enCCDataType);
            return ERROR_INVALID_PARAM;
        }
    }

    return SUCCESS;
}

static VOID caption_subt_maptype_tounf(CAPTION_SUBT_DATA_E enSubtDataType, HI_UNF_SUBT_DATA_TYPE_E* penUnfDataType)
{
    if (NULL == penUnfDataType)
    {
        return;
    }

    switch (enSubtDataType)
    {
        case CAPTION_SUBT_DATA_DVB:
        {
            *penUnfDataType = HI_UNF_SUBT_DVB;
            break;
        }

        case CAPTION_SUBT_DATA_SCTE:
        {
            *penUnfDataType = HI_UNF_SUBT_SCTE;
            break;
        }

        default:
        {
            *penUnfDataType = HI_UNF_SUBT_BUTT;
            break;
        }
    }

    return;
}

static S32 caption_subt_create_so(VOID)
{
    S32 s32Ret = FAILURE;
    HANDLE hSo = INVALID_CAPTION_HANDLE;

    s32Ret = HI_UNF_SO_Create(&hSo);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s32Ret = HI_UNF_SO_SetMaxInterval(hSo, CAPTION_MAX_INTERVAL);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s32Ret = HI_UNF_SO_RegGetPtsCb(hSo,(HI_UNF_SO_GETPTS_FN) caption_subt_get_pts, (U32)0);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s32Ret = HI_UNF_SO_RegOnDrawCb(hSo, (HI_UNF_SO_ONDRAW_FN)caption_subt_draw, (HI_UNF_SO_ONCLEAR_FN)caption_subt_clear, 0);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s_stCaptionModule.stSubtInfo.hSo = hSo;

    return SUCCESS;
}

static S32 caption_subt_destory_so(VOID)
{
    S32 s32Ret = FAILURE;
    HANDLE hSo = INVALID_CAPTION_HANDLE;

    hSo = s_stCaptionModule.stSubtInfo.hSo;

    if (INVALID_CAPTION_HANDLE != hSo)
    {
        s32Ret = HI_UNF_SO_Destroy(hSo);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s_stCaptionModule.stSubtInfo.hSo = INVALID_CAPTION_HANDLE;

    return SUCCESS;
}

static S32 caption_subt_create_dvbsubt(HANDLE* phSubt)
{
    S32 s32Ret = FAILURE;
    HANDLE hSubt = INVALID_CAPTION_HANDLE;
    HI_UNF_SUBT_PARAM_S stUnfSubtParam;

    HAL_DEBUG("%s, %d\n", __func__, __LINE__);

    memset(&stUnfSubtParam, 0, sizeof(HI_UNF_SUBT_PARAM_S));

    stUnfSubtParam.enDataType = HI_UNF_SUBT_DVB;
    stUnfSubtParam.pfnCallback = (HI_UNF_SUBT_CALLBACK_FN)caption_subt_callback;
    stUnfSubtParam.u8SubtItemNum = 0;
    stUnfSubtParam.pUserData = HI_NULL;

    s32Ret = HI_UNF_SUBT_Create(&stUnfSubtParam, &hSubt);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    *phSubt = hSubt;

    HAL_DEBUG("%s, %d, hSubt(0x%08x)\n", __func__, __LINE__, hSubt);

    return HI_SUCCESS;
}

static S32 caption_subt_create_sctesubt(HANDLE* phSubt)
{
    S32 s32Ret = FAILURE;
    HI_UNF_SUBT_PARAM_S stUnfSubtParam;
    HANDLE hSubt = INVALID_CAPTION_HANDLE;

    HAL_DEBUG("%s, %d\n", __func__, __LINE__);

    memset(&stUnfSubtParam, 0, sizeof(HI_UNF_SUBT_PARAM_S));

    stUnfSubtParam.enDataType = HI_UNF_SUBT_SCTE;
    stUnfSubtParam.pfnCallback = (HI_UNF_SUBT_CALLBACK_FN)caption_subt_callback;
    stUnfSubtParam.u8SubtItemNum = 0;
    stUnfSubtParam.pUserData = HI_NULL;

    s32Ret = HI_UNF_SUBT_Create(&stUnfSubtParam, &hSubt);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s32Ret = HI_UNF_SUBT_RegGetPtsCb(hSubt, (HI_UNF_SUBT_GETPTS_FN)caption_subt_get_pts, 0);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    *phSubt = hSubt;
    HAL_DEBUG("%s, %d, hSubt(0x%08x)\n", __func__, __LINE__, hSubt);

    return HI_SUCCESS;
}

static S32 caption_subt_destory(VOID)
{
    S32 s32Ret = FAILURE;
    HI_HANDLE hSubt = INVALID_CAPTION_HANDLE;

    hSubt = s_stCaptionModule.stSubtInfo.hSubt;

    if (INVALID_CAPTION_HANDLE != hSubt)
    {
        s32Ret = HI_UNF_SUBT_Destroy(hSubt);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s_stCaptionModule.stSubtInfo.hSubt = INVALID_CAPTION_HANDLE;

    return SUCCESS;
}

static S32 caption_subt_reset(VOID)
{
    S32 s32Ret = FAILURE;
    HANDLE hSo = INVALID_CAPTION_HANDLE;
    HANDLE hSubt = INVALID_CAPTION_HANDLE;

    hSo = s_stCaptionModule.stSubtInfo.hSo;
    hSubt = s_stCaptionModule.stSubtInfo.hSubt;

    s32Ret = HI_UNF_SUBT_Reset(hSubt);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s32Ret = HI_UNF_SO_ResetSubBuf(hSo);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return HI_SUCCESS;
}

static S32 caption_subt_start(CAPTION_SUBT_PARAM_S* pstSubtParam)
{
    S32 s32Ret = SUCCESS;
    HANDLE hSubt = INVALID_CAPTION_HANDLE;

    HAL_DEBUG_ENTER();

    s32Ret = caption_subt_create_so();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    if (CAPTION_SUBT_DATA_DVB == pstSubtParam->enSubtDataType)
    {
        s32Ret = caption_subt_create_dvbsubt(&hSubt);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }
    else if (CAPTION_SUBT_DATA_SCTE == pstSubtParam->enSubtDataType)
    {
        s32Ret = caption_subt_create_sctesubt(&hSubt);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }
    else
    {
        HAL_ERROR("%s,%d error!! enSubtDataType(0x%08x)", __func__, __LINE__, pstSubtParam->enSubtDataType);
        return ERROR_INVALID_PARAM;
    }

    s_stCaptionModule.stSubtInfo.enSubtDataType = pstSubtParam->enSubtDataType;
    s_stCaptionModule.stSubtInfo.hSubt = hSubt;
    s_stCaptionModule.stSubtInfo.enStatus = CAPTION_RUNNING;
    s_stCaptionModule.stSubtInfo.pfnGetPts = pstSubtParam->pfnGetPts;
    s_stCaptionModule.stSubtInfo.u32SubtItemNum = 0;

    if (INVALID_CAPTION_HANDLE == s_stCaptionModule.stSubtInfo.hOut)
    {
        s32Ret = caption_subt_output_init(&(s_stCaptionModule.stSubtInfo.hOut));

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)\n", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    return SUCCESS;
}

static S32 caption_subt_switch(CAPTION_SUBT_ITEM_S* pstSubtItem)
{
    S32 s32Ret = SUCCESS;
    SUBT_MODULE_S* pstSubtInfo = NULL;
    HANDLE hSubt = INVALID_CAPTION_HANDLE;
    HI_UNF_SUBT_ITEM_S stUnfSubtItem = {0};
    U32 i = 0;
    BOOL bFind = FALSE;

    if ((CAPTION_BUTT == s_stCaptionModule.stSubtInfo.enStatus) ||
        (CAPTION_STOPPED == s_stCaptionModule.stSubtInfo.enStatus))
    {
        HAL_ERROR("status error!! subtitle status = 0x%08x", s_stCaptionModule.stSubtInfo.enStatus);
        return FAILURE;
    }

    memset(&stUnfSubtItem, 0x0, sizeof(HI_UNF_SUBT_ITEM_S));

    pstSubtInfo = &(s_stCaptionModule.stSubtInfo);

    //4 check same as now
    if ((pstSubtInfo->stSubtItem.u32SubtPID == pstSubtItem->u32SubtPID)
        &&(pstSubtInfo->stSubtItem.u16PageID == pstSubtItem->u16PageID)
        &&(pstSubtInfo->stSubtItem.u16AncillaryID == pstSubtItem->u16AncillaryID))
    {
        HAL_DEBUG("same subt as now, so return success");
        return SUCCESS;
    }

    //4 may this subt alread set to unf, but not current one, so find this subt.

    for (i = 0; i < pstSubtInfo->u32SubtItemNum; i++)
    {
        if ((pstSubtInfo->astSubtItems[i].u32SubtPID == pstSubtItem->u32SubtPID)
            &&(pstSubtInfo->astSubtItems[i].u16PageID == pstSubtItem->u16PageID)
            &&(pstSubtInfo->astSubtItems[i].u16AncillaryID == pstSubtItem->u16AncillaryID))
        {
            bFind = HI_TRUE;
            break;
        }
    }

    hSubt = pstSubtInfo->hSubt;

    stUnfSubtItem.u32SubtPID = pstSubtItem->u32SubtPID;
    stUnfSubtItem.u16PageID = pstSubtItem->u16PageID;
    stUnfSubtItem.u16AncillaryID = pstSubtItem->u16AncillaryID;

    //4 not in current list, so update first, then switch
    if (!bFind)
    {
        HI_UNF_SUBT_PARAM_S stUpdateParam;
        stUpdateParam.astItems[0].u32SubtPID = pstSubtItem->u32SubtPID;
        stUpdateParam.astItems[0].u16PageID = pstSubtItem->u16PageID;
        stUpdateParam.astItems[0].u16AncillaryID = pstSubtItem->u16AncillaryID;
        stUpdateParam.pfnCallback = (HI_UNF_SUBT_CALLBACK_FN)caption_subt_callback;
        stUpdateParam.pUserData = HI_NULL;
        stUpdateParam.u8SubtItemNum = 1;

        caption_subt_maptype_tounf(pstSubtInfo->enSubtDataType, &(stUpdateParam.enDataType));

        s32Ret = HI_UNF_SUBT_Update(hSubt, &stUpdateParam);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        }
        pstSubtInfo->u32SubtItemNum = 1;
    }

    s32Ret = HI_UNF_SUBT_SwitchContent(hSubt, &stUnfSubtItem);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    pstSubtInfo->stSubtItem.u32SubtPID = pstSubtItem->u32SubtPID;
    pstSubtInfo->stSubtItem.u16PageID = pstSubtItem->u16PageID;
    pstSubtInfo->stSubtItem.u16AncillaryID = pstSubtItem->u16AncillaryID;

    return SUCCESS;
}

static S32 caption_subt_hide(VOID)
{
    S32 s32Ret = SUCCESS;

    if (CAPTION_BUTT == s_stCaptionModule.stSubtInfo.enStatus)
    {
        HAL_ERROR("status error!! subtitle status = 0x%08x", s_stCaptionModule.stSubtInfo.enStatus);
        return FAILURE;
    }

    if ((CAPTION_STOPPED == s_stCaptionModule.stSubtInfo.enStatus) ||
        (CAPTION_HIDE == s_stCaptionModule.stSubtInfo.enStatus))
    {
        HAL_DEBUG("already hide", __func__, __LINE__);
        return SUCCESS;
    }

    s32Ret = caption_subt_reset();
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HI_UNF_SO_CLEAR_PARAM_S stClear;
    stClear.x = 0;
    stClear.y = 0;
    stClear.w = 0;
    stClear.h = 0;

    s32Ret = caption_subt_clear(0, (VOID*)&stClear);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s_stCaptionModule.stSubtInfo.enStatus = CAPTION_HIDE;

    return SUCCESS;
}

static S32 caption_subt_stop()
{
    S32 s32Ret = SUCCESS;

    if (CAPTION_STOPPED == s_stCaptionModule.stSubtInfo.enStatus)
    {
        HAL_DEBUG("%s,%d subt has stooped!! ", __func__, __LINE__);
        return SUCCESS;
    }

    if (CAPTION_SHOW == s_stCaptionModule.stSubtInfo.enStatus)
    {
        s32Ret = caption_subt_hide();

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s32Ret = caption_subt_destory_so();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s32Ret = caption_subt_destory();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s_stCaptionModule.stSubtInfo.enStatus = CAPTION_STOPPED;
    s_stCaptionModule.stSubtInfo.enSubtDataType = CAPTION_SUBT_DATA_BUTT;
    s_stCaptionModule.stSubtInfo.u32SubtItemNum = 0;
    memset(&(s_stCaptionModule.stSubtInfo.stSubtItem), 0x0, sizeof(CAPTION_SUBT_ITEM_S));

    if (INVALID_CAPTION_HANDLE != s_stCaptionModule.stSubtInfo.hOut)
    {
        s32Ret = caption_subt_output_deinit(s_stCaptionModule.stSubtInfo.hOut);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }

        s_stCaptionModule.stSubtInfo.hOut = INVALID_CAPTION_HANDLE;
    }

    return SUCCESS;
}

static S32 caption_ttx_callback(HI_HANDLE hTTX, HI_UNF_TTX_CB_E enCB, HI_VOID* pvCBParam)
{
    if ((HI_UNF_TTX_CB_CREATE_BUFF != enCB) && (HI_UNF_TTX_CB_DESTROY_BUFF != enCB))
    {
        if (CAPTION_STOPPED == s_stCaptionModule.stTtxInfo.enStatus)
        {
            return HI_SUCCESS;
        }
    }

    if (HI_UNF_TTX_CB_GETPTS == enCB)
    {
        U32 u32CurrentPts = 0;

        s_stCaptionModule.stTtxInfo.pfnGetPts(&u32CurrentPts);

        *(HI_S64*)pvCBParam = (HI_S64)u32CurrentPts;
    }
    else
    {
        caption_ttx_output_callbak(hTTX, enCB, pvCBParam);
    }

    return HI_SUCCESS;
}

VOID  caption_ttx_handle_msg(VOID* args)
{
    HANDLE hDispalyHandle = INVALID_CAPTION_HANDLE;
    MESSAGE_S stMsg;
    TTX_MODULE_S* pstTtxInfo;

    pstTtxInfo = (TTX_MODULE_S*) args;

    if (NULL == pstTtxInfo)
    {
        HAL_ERROR("%s,%d error!!  args null ", __func__, __LINE__);
        return;
    }

    while (CAPTION_STOPPED != pstTtxInfo->enStatus)
    {
        if (HI_FAILURE == MsgQueue_De(&stMsg))
        {
            //lint -e506
            CAPTION_SLEEPMS(20);
            //lint +e506
            continue;
        }

        hDispalyHandle = *(HI_HANDLE* )stMsg.pu8MsgData;

        if (HI_SUCCESS != HI_UNF_TTX_Display(pstTtxInfo->hTTX, hDispalyHandle))
        {
            HAL_ERROR("%s,%d error!! ", __func__, __LINE__);
        }
    }
}

static S32 caption_ttx_create(HANDLE* phTTX)
{
    S32 s32Ret = FAILURE;
    HANDLE hTTX = INVALID_CAPTION_HANDLE;
    HI_UNF_TTX_INIT_PARA_S stUnfTtxInitParam = {0};

    memset(&stUnfTtxInitParam, 0, sizeof(HI_UNF_TTX_INIT_PARA_S));

    stUnfTtxInitParam.pu8MemAddr = HI_NULL;
    stUnfTtxInitParam.u32MemSize = 0;
    stUnfTtxInitParam.pfnCB = (HI_UNF_TTX_CB_FN)caption_ttx_callback;
    stUnfTtxInitParam.bFlash = HI_TRUE;
    stUnfTtxInitParam.bNavigation = HI_TRUE;

    s32Ret = HI_UNF_TTX_Create(&stUnfTtxInitParam, &hTTX);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s32Ret = HI_UNF_TTX_SetMaxInterval(hTTX, CAPTION_MAX_INTERVAL);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    *phTTX = hTTX;

    return HI_SUCCESS;
}

static S32 caption_ttx_destory()
{
    S32 s32Ret = FAILURE;
    HANDLE hTTX = INVALID_CAPTION_HANDLE;

    hTTX = s_stCaptionModule.stTtxInfo.hTTX;

    if (INVALID_CAPTION_HANDLE != hTTX)
    {
        s32Ret = HI_UNF_TTX_Destroy(hTTX);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s_stCaptionModule.stTtxInfo.hTTX = INVALID_CAPTION_HANDLE;

    return SUCCESS;
}

static S32 caption_ttx_reset()
{
    S32 s32Ret = FAILURE;
    HANDLE hTTX = INVALID_CAPTION_HANDLE;

    hTTX = s_stCaptionModule.stTtxInfo.hTTX;

    if (INVALID_CAPTION_HANDLE != hTTX)
    {
        s32Ret = HI_UNF_TTX_ResetData(hTTX);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    return SUCCESS;
}

static VOID caption_ttx_map_type_tounf(CAPTION_TTX_DATA_TYPE_E enHalTtxType, HI_UNF_TTX_TYPE_E* penUnfTtxType)
{
    HI_UNF_TTX_TYPE_E enUnfTtxType = HI_UNF_TTX_TTXSUBT_BUTT;

    if (NULL == penUnfTtxType)
    {
        return;
    }

    switch (enHalTtxType)
    {
        case CAPTION_TTX_DATA_INITTTX:
        {
            enUnfTtxType = HI_UNF_TTX_INITTTX;
            break;
        }

        case CAPTION_TTX_DATA_TTXSUBT:
        {
            enUnfTtxType = HI_UNF_TTX_TTXSUBT;
            break;
        }

        default:
        {
            enUnfTtxType = HI_UNF_TTX_TTXSUBT_BUTT;
            break;
        }
    }

    *penUnfTtxType = enUnfTtxType;

}

static VOID caption_ttx_map_outtype_tounf(CAPTION_TTX_OUTPUT_TYPE_E enOutputType, HI_UNF_TTX_OUTPUT_E* penUnfOutputType)
{
    HI_UNF_TTX_OUTPUT_E enOutput = HI_UNF_TTX_BUTT;

    if (NULL == penUnfOutputType)
    {
        return;
    }

    if (CAPTION_TTX_OUTPUT_VBI == enOutputType)
    {
        enOutput = HI_UNF_TTX_VBI_OUTPUT;
    }
    else if (CAPTION_TTX_OUTPUT_OSD == enOutputType)
    {
        enOutput = HI_UNF_TTX_OSD_OUTPUT;
    }
    else if (CAPTION_TTX_OUTPUT_VBI_OSD == enOutputType)
    {
        enOutput = HI_UNF_TTX_DUAL_OUTPUT;
    }
    else
    {
        enOutput = HI_UNF_TTX_BUTT;
    }

    *penUnfOutputType = enOutput;

    HAL_DEBUG("%s,%d!! outtype(0x%08x)", __func__, __LINE__, enOutput);

}

static VOID caption_ttx_map_pagetype_tounf(CAPTION_TTX_PAGE_TYPE_E enPageType, HI_UNF_TTX_PAGE_TYPE_E* penUnfPageType)
{
    HI_UNF_TTX_PAGE_TYPE_E enUnfPageType = HI_UNF_TTX_PAGE_BUTT;

    if (NULL == penUnfPageType)
    {
        return;
    }

    switch (enPageType)
    {
        case CAPTION_TTX_PAGE_CUR:
        {
            enUnfPageType = HI_UNF_TTX_PAGE_CUR;
            break;
        }

        case CAPTION_TTX_PAGE_INDEX:
        {
            enUnfPageType = HI_UNF_TTX_PAGE_INDEX;
            break;
        }

        case CAPTION_TTX_PAGE_LINK1:
        {
            enUnfPageType = HI_UNF_TTX_PAGE_LINK1;
            break;
        }

        case CAPTION_TTX_PAGE_LINK2:
        {
            enUnfPageType = HI_UNF_TTX_PAGE_LINK2;
            break;
        }

        case CAPTION_TTX_PAGE_LINK3:
        {
            enUnfPageType = HI_UNF_TTX_PAGE_LINK3;
            break;
        }

        case CAPTION_TTX_PAGE_LINK4:
        {
            enUnfPageType = HI_UNF_TTX_PAGE_LINK4;
            break;
        }

        case CAPTION_TTX_PAGE_LINK5:
        {
            enUnfPageType = HI_UNF_TTX_PAGE_LINK5;
            break;
        }

        case CAPTION_TTX_PAGE_LINK6:
        {
            enUnfPageType = HI_UNF_TTX_PAGE_LINK6;
            break;
        }

        default:
        {
            enUnfPageType = HI_UNF_TTX_PAGE_BUTT;
            break;
        }
    }

    *penUnfPageType = enUnfPageType;
}

static S32 caption_ttx_map_key_tounf(CAPTION_TTX_KEY_E enKey, HI_UNF_TTX_KEY_E* penUnfKey)
{
    U32 i = 0;
    U32 u32MapSize = 0;
    S32 s32Ret = SUCCESS;
    HI_UNF_TTX_KEY_E enUnfKey = HI_UNF_TTX_KEY_BUTT;

    if ((NULL == penUnfKey) || (CAPTION_TTX_KEY_BUTT <= enKey))
    {
        return FAILURE;
    }

    u32MapSize = sizeof(s_stTtxKeyMap) / sizeof(CAPTION_TTX_KEY_MAP_S);

    for (i = 0; i < u32MapSize; i++)
    {
        if (enKey == s_stTtxKeyMap[i].enHalKey)
        {
            enUnfKey = s_stTtxKeyMap[i].enUnfKey;
        }
    }

    if (HI_UNF_TTX_KEY_BUTT == enUnfKey)
    {
        s32Ret = FAILURE;
    }

    *penUnfKey = enUnfKey;

    return s32Ret;
}

static S32 caption_ttx_execmd_key(HANDLE hTTX, VOID* pvCMDParam)
{
    S32 s32Ret = FAILURE;
    CAPTION_TTX_KEY_E enKey = CAPTION_TTX_KEY_BUTT;
    HI_UNF_TTX_KEY_E  enUnfKey = HI_UNF_TTX_KEY_BUTT;

    enKey = *(CAPTION_TTX_KEY_E*)pvCMDParam;

    s32Ret = caption_ttx_map_key_tounf(enKey, &enUnfKey);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_UNF_TTX_ExecCmd(hTTX, HI_UNF_TTX_CMD_KEY, (VOID*)&enUnfKey);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return SUCCESS;
}

static S32 caption_ttx_execmd_open_page(HANDLE hTTX, VOID* pvCMDParam)
{
    S32 s32Ret = FAILURE;
    CAPTION_TTX_PAGE_ITEM_S stPageItem;
    HI_UNF_TTX_PAGE_ADDR_S  stUnfPageItem;

    stPageItem = *(CAPTION_TTX_PAGE_ITEM_S*)pvCMDParam;

    stUnfPageItem.u8MagazineNum = stPageItem.u8MagazineNum;
    stUnfPageItem.u8PageNum = stPageItem.u8PageNum;
    stUnfPageItem.u16PageSubCode = stPageItem.u16PageSubCode;

    s32Ret = HI_UNF_TTX_ExecCmd(hTTX, HI_UNF_TTX_CMD_OPENPAGE, (VOID*)&stUnfPageItem);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return SUCCESS;
}

static S32 caption_ttx_execmd_get_pageaddr(HANDLE hTTX, VOID* pvCMDParam)
{
    S32 s32Ret = FAILURE;
    CAPTION_TTX_GETPAGEADDR_S* pstPageInfo = NULL;
    HI_UNF_TTX_GETPAGEADDR_S   stUnfPageInfo;

    pstPageInfo = (CAPTION_TTX_GETPAGEADDR_S*)pvCMDParam;

    caption_ttx_map_pagetype_tounf(pstPageInfo->enPageType, &(stUnfPageInfo.enPageType));

    s32Ret = HI_UNF_TTX_ExecCmd(hTTX, HI_UNF_TTX_CMD_GETPAGEADDR, (VOID*)&stUnfPageInfo);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    pstPageInfo->stPageInfo.u8MagazineNum = stUnfPageInfo.stPageAddr.u8MagazineNum;
    pstPageInfo->stPageInfo.u8PageNum = stUnfPageInfo.stPageAddr.u8PageNum;
    pstPageInfo->stPageInfo.u16PageSubCode = stUnfPageInfo.stPageAddr.u16PageSubCode;

    return SUCCESS;
}

static S32 caption_ttx_execmd_check_page(HANDLE hTTX, VOID* pvCMDParam)
{
    S32 s32Ret = FAILURE;
    CAPTION_TTX_CHECK_PARAM_S* pstCheckParam;
    HI_UNF_TTX_CHECK_PARAM_S  stUnfCheckParam;

    pstCheckParam = (CAPTION_TTX_CHECK_PARAM_S*)pvCMDParam;

    stUnfCheckParam.stPageAddr.u8MagazineNum = pstCheckParam->stPageInfo.u8MagazineNum;
    stUnfCheckParam.stPageAddr.u8PageNum = pstCheckParam->stPageInfo.u8PageNum;;
    stUnfCheckParam.stPageAddr.u16PageSubCode = pstCheckParam->stPageInfo.u16PageSubCode;;

    s32Ret = HI_UNF_TTX_ExecCmd(hTTX, HI_UNF_TTX_CMD_CHECKPAGE, (VOID*)&stUnfCheckParam);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    pstCheckParam->bSucceed = stUnfCheckParam.bSucceed;

    return SUCCESS;
}

static S32 caption_ttx_execmd_set_request(HANDLE hTTX, VOID* pvCMDParam)
{
    S32 s32Ret = FAILURE;
    U16 u16DataSize = CAPTION_TTX_ROW_NUM * CAPTION_TTX_COLUMN_NUM;
    CAPTION_TTX_REQUESET_RAWDATA_S stRequestParam;
    HI_UNF_TTX_REQUEST_RAWDATA_S stUnfRequestParam;
    HI_UNF_TTX_RAWDATA_S stRawData;

    stRequestParam = *(CAPTION_TTX_REQUESET_RAWDATA_S*)pvCMDParam;

    CAPTION_CHK_PTR(stRequestParam.pstRawData);
    CAPTION_CHK_PTR(stRequestParam.pfnRequestCallback);

    memset(&stUnfRequestParam, 0x0, sizeof(HI_UNF_TTX_REQUEST_RAWDATA_S));
    memset(&stRawData, 0x0, sizeof(HI_UNF_TTX_RAWDATA_S));

    stUnfRequestParam.pstRawData = &stRawData;

    stUnfRequestParam.pstRawData->u32ValidLines = stRequestParam.pstRawData->u32ValidLines;

    memcpy(stUnfRequestParam.pstRawData->au8Lines, stRequestParam.pstRawData->au8Lines, u16DataSize);

    stUnfRequestParam.pfnRequestCallback = (HI_UNF_TTX_REQUEST_CALLBACK_FN)stRequestParam.pfnRequestCallback;

    s32Ret = HI_UNF_TTX_ExecCmd(hTTX, HI_UNF_TTX_CMD_SETREQUEST, (VOID*)&stUnfRequestParam);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return SUCCESS;
}

static S32 caption_ttx_execmd_clear_request(HANDLE hTTX, VOID* pvCMDParam)
{
    S32 s32Ret = FAILURE;
    U16 u16DataSize = CAPTION_TTX_ROW_NUM * CAPTION_TTX_COLUMN_NUM;
    CAPTION_TTX_REQUESET_RAWDATA_S stRequestParam;
    HI_UNF_TTX_REQUEST_RAWDATA_S stUnfRequestParam;
    HI_UNF_TTX_RAWDATA_S stRawData;

    stRequestParam = *(CAPTION_TTX_REQUESET_RAWDATA_S*)pvCMDParam;

    CAPTION_CHK_PTR(stRequestParam.pstRawData);
    CAPTION_CHK_PTR(stRequestParam.pfnRequestCallback);

    memset(&stUnfRequestParam, 0x0, sizeof(HI_UNF_TTX_REQUEST_RAWDATA_S));
    memset(&stRawData, 0x0, sizeof(HI_UNF_TTX_RAWDATA_S));

    stUnfRequestParam.pstRawData = &stRawData;

    stUnfRequestParam.pstRawData->u32ValidLines = stRequestParam.pstRawData->u32ValidLines;

    memcpy(stUnfRequestParam.pstRawData->au8Lines, stRequestParam.pstRawData->au8Lines, u16DataSize);

    stUnfRequestParam.pfnRequestCallback = (HI_UNF_TTX_REQUEST_CALLBACK_FN)stRequestParam.pfnRequestCallback;

    s32Ret = HI_UNF_TTX_ExecCmd(hTTX, HI_UNF_TTX_CMD_CLEARREQUEST, (VOID*)&stUnfRequestParam);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return SUCCESS;
}

static S32 caption_ttx_start(CAPTION_TTX_PARAM_S* pstTTXParam)
{
    S32 s32Ret = SUCCESS;
    HANDLE hTTX = INVALID_CAPTION_HANDLE;
    HI_UNF_TTX_PACKET_TYPE_E enPacketType;
    VOID* pVoid = HI_NULL;
    pthread_t pMsgId = 0;

    s32Ret = MsgQueue_Init();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    if (INVALID_CAPTION_HANDLE == s_stCaptionModule.stTtxInfo.hOut)
    {
        s32Ret = caption_ttx_output_init(&(s_stCaptionModule.stTtxInfo.hOut));

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s32Ret = caption_ttx_create(&hTTX);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    if (CAPTION_TTX_DATA_SOURCE_PES == pstTTXParam->enDataSource)
    {
        enPacketType = HI_UNF_TTX_PACKET_TYPE_PES;
    }
    else if (CAPTION_TTX_DATA_SOURCE_RAW == pstTTXParam->enDataSource)
    {
        enPacketType = HI_UNF_TTX_PACKET_TYPE_RAW;
    }
    else
    {
        HAL_ERROR("%s,%d error!! enDataSource(0x%08x)", __func__, __LINE__,  pstTTXParam->enDataSource);
        return FAILURE;
    }

    s32Ret = HI_UNF_TTX_SetPacketType(hTTX, enPacketType);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    /*create msg handle task*/
    pVoid = (VOID*) & (s_stCaptionModule.stTtxInfo);

    s_stCaptionModule.stTtxInfo.enStatus = CAPTION_STOPPED;

    if (0 != s_stCaptionModule.stTtxInfo.pMsgTaskId)
    {
        if (0 != pthread_join(s_stCaptionModule.stTtxInfo.pMsgTaskId, HI_NULL))
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s32Ret = pthread_create(&pMsgId, NULL, (VOID * (*)(VOID*))caption_ttx_handle_msg, (HI_VOID*)pVoid);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s_stCaptionModule.stTtxInfo.enDataSource = pstTTXParam->enDataSource;
    s_stCaptionModule.stTtxInfo.hTTX = hTTX;
    s_stCaptionModule.stTtxInfo.enStatus = CAPTION_RUNNING;
    s_stCaptionModule.stTtxInfo.pMsgTaskId = pMsgId;
    s_stCaptionModule.stTtxInfo.pfnGetPts = pstTTXParam->pfnGetPts;

    return SUCCESS;
}

static S32 caption_ttx_switch(CAPTION_TTX_CONTENT_S* pstTTXContentParam)
{
    S32 s32Ret = SUCCESS;
    TTX_MODULE_S* pstTtxInfo = NULL;
    HANDLE hTTX = INVALID_CAPTION_HANDLE;
    HI_UNF_TTX_CONTENT_PARA_S stUnfContent;

    if ((CAPTION_BUTT == s_stCaptionModule.stTtxInfo.enStatus) ||
        (CAPTION_STOPPED == s_stCaptionModule.stTtxInfo.enStatus))
    {
        HAL_ERROR("status error!! ttx status = 0x%08x", s_stCaptionModule.stTtxInfo.enStatus);
        return FAILURE;
    }

    pstTtxInfo = &(s_stCaptionModule.stTtxInfo);

    memset(&stUnfContent, 0x0, sizeof(HI_UNF_TTX_CONTENT_PARA_S));
    memcpy(&(pstTtxInfo->stTtxItem), pstTTXContentParam, sizeof(CAPTION_TTX_CONTENT_S));

    caption_ttx_map_type_tounf(pstTTXContentParam->enType, &stUnfContent.enType);
    stUnfContent.stInitPgAddr.u8MagazineNum = pstTTXContentParam->stInitPagInfo.u8MagazineNum;
    stUnfContent.stInitPgAddr.u8PageNum = pstTTXContentParam->stInitPagInfo.u8PageNum;
    stUnfContent.stInitPgAddr.u16PageSubCode = pstTTXContentParam->stInitPagInfo.u16PageSubCode;
    stUnfContent.u32ISO639LanCode = pstTTXContentParam->u32ISO639LanCode;

    hTTX = pstTtxInfo->hTTX;

    s32Ret = HI_UNF_TTX_SwitchContent(hTTX, &stUnfContent);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return SUCCESS;
}

static S32 caption_ttx_hide(CAPTION_TTX_OUTPUT_TYPE_E enOutputType)
{
    S32 s32Ret = SUCCESS;
    HANDLE hTTX = INVALID_CAPTION_HANDLE;
    HI_UNF_TTX_OUTPUT_E enOutput = HI_UNF_TTX_BUTT;

    CAPTION_CHK_PARA(CAPTION_TTX_OUTPUT_BUTT == enOutputType);

    if ((CAPTION_BUTT == s_stCaptionModule.stTtxInfo.enStatus) ||
        (CAPTION_STOPPED == s_stCaptionModule.stTtxInfo.enStatus))
    {
        HAL_ERROR("status error!! ttx status = 0x%08x", s_stCaptionModule.stTtxInfo.enStatus);
        return FAILURE;
    }

    caption_ttx_map_outtype_tounf(enOutputType, &enOutput);

    hTTX = s_stCaptionModule.stTtxInfo.hTTX;

    s32Ret = HI_UNF_TTX_Output(hTTX, enOutput, HI_FALSE);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error false!! s32Ret(0x%08x),hTTX(0x%08x), enOutput(0x%08x)", __func__, __LINE__, hTTX, s32Ret, enOutput);
        return FAILURE;
    }

    s_stCaptionModule.stTtxInfo.enStatus = CAPTION_HIDE;

    return SUCCESS;
}

static S32 caption_ttx_stop(VOID)
{
    S32 s32Ret = SUCCESS;

    if (CAPTION_STOPPED == s_stCaptionModule.stTtxInfo.enStatus)
    {
        HAL_ERROR("%s,%d error!!", __func__, __LINE__);
        return SUCCESS;
    }

    if (CAPTION_SHOW == s_stCaptionModule.stTtxInfo.enStatus)
    {
        s32Ret = caption_ttx_hide(s_stCaptionModule.stTtxInfo.enOutputType);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s32Ret = caption_ttx_destory();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s_stCaptionModule.stTtxInfo.enStatus = CAPTION_STOPPED;
    s_stCaptionModule.stTtxInfo.enDataSource = CAPTION_TTX_DATA_SOURCE_BUTT;

    memset(&(s_stCaptionModule.stTtxInfo.stTtxItem), 0x0, sizeof(CAPTION_TTX_CONTENT_S));

    if (INVALID_CAPTION_HANDLE != s_stCaptionModule.stTtxInfo.hOut)
    {
        s32Ret = caption_ttx_output_deinit(s_stCaptionModule.stTtxInfo.hOut);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }

        s_stCaptionModule.stTtxInfo.hOut = INVALID_CAPTION_HANDLE;
    }

    if (HI_NULL != s_stCaptionModule.stTtxInfo.pMsgTaskId)
    {
        pthread_join(s_stCaptionModule.stTtxInfo.pMsgTaskId, NULL);
        s_stCaptionModule.stTtxInfo.pMsgTaskId = HI_NULL;
    }

    s32Ret = MsgQueue_DeInit();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return SUCCESS;
}

static S32 caption_cc_map_type_tounf(CAPTION_CC_DATA_E enCCType, HI_UNF_CC_DATA_TYPE_E* penUnfCCType)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_CC_DATA_TYPE_E enUnfCCType = HI_UNF_CC_DATA_TYPE_BUTT;

    if (NULL == penUnfCCType)
    {
        return FAILURE;
    }

    switch (enCCType)
    {
        case CAPTION_CC_DATA_608:
        {
            enUnfCCType = HI_UNF_CC_DATA_TYPE_608;
            break;
        }

        case CAPTION_CC_DATA_708:
        {
            enUnfCCType = HI_UNF_CC_DATA_TYPE_708;
            break;
        }

        case CAPTION_CC_DATA_ARIB:
        {
            enUnfCCType = HI_UNF_CC_DATA_TYPE_ARIB;
            break;
        }

        default:
        {
            enUnfCCType = HI_UNF_CC_DATA_TYPE_BUTT;
            break;
        }
    }

    *penUnfCCType = enUnfCCType;

    if (HI_UNF_CC_DATA_TYPE_BUTT == enUnfCCType)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}

static S32 caption_cc_map_608type_tounf(CAPTION_CC608_DATATYPE_E en608Type, HI_UNF_CC_608_DATATYPE_E* penUnf608Type)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_CC_608_DATATYPE_E enUnf608Type = HI_UNF_CC_608_DATATYPE_BUTT;

    if (NULL == penUnf608Type)
    {
        return FAILURE;
    }

    switch (en608Type)
    {
        case CAPTION_CC_608_DATATYPE_CC1:
        {
            enUnf608Type = HI_UNF_CC_608_DATATYPE_CC1;
            break;
        }

        case CAPTION_CC_608_DATATYPE_CC2:
        {
            enUnf608Type = HI_UNF_CC_608_DATATYPE_CC2;
            break;
        }

        case CAPTION_CC_608_DATATYPE_CC3:
        {
            enUnf608Type = HI_UNF_CC_608_DATATYPE_CC3;
            break;
        }

        case CAPTION_CC_608_DATATYPE_CC4:
        {
            enUnf608Type = HI_UNF_CC_608_DATATYPE_CC4;
            break;
        }

        case CAPTION_CC_608_DATATYPE_TEXT1:
        {
            enUnf608Type = HI_UNF_CC_608_DATATYPE_TEXT1;
            break;
        }

        case CAPTION_CC_608_DATATYPE_TEXT2:
        {
            enUnf608Type = HI_UNF_CC_608_DATATYPE_TEXT2;
            break;
        }

        case CAPTION_CC_608_DATATYPE_TEXT3:
        {
            enUnf608Type = HI_UNF_CC_608_DATATYPE_TEXT3;
            break;
        }

        case CAPTION_CC_608_DATATYPE_TEXT4:
        {
            enUnf608Type = HI_UNF_CC_608_DATATYPE_TEXT4;
            break;
        }

        default:
        {
            enUnf608Type = HI_UNF_CC_608_DATATYPE_BUTT;
            break;
        }
    }

    *penUnf608Type = enUnf608Type;

    if (HI_UNF_CC_608_DATATYPE_BUTT == enUnf608Type)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;

}
static S32 caption_cc_map_opacity_tounf(CAPTION_CC_OPACITY_E enCCOpac, HI_UNF_CC_OPACITY_E* penUnfOpac)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_CC_OPACITY_E enUnfOpac = HI_UNF_CC_OPACITY_BUTT;

    if (NULL == penUnfOpac)
    {
        return FAILURE;
    }

    switch (enCCOpac)
    {
        case CAPTION_CC_OPACITY_DEFAULT:
        {
            enUnfOpac = HI_UNF_CC_OPACITY_DEFAULT;
            break;
        }

        case CAPTION_CC_OPACITY_SOLID:
        {
            enUnfOpac = HI_UNF_CC_OPACITY_SOLID;
            break;
        }

        case CAPTION_CC_OPACITY_FLASH:
        {
            enUnfOpac = HI_UNF_CC_OPACITY_FLASH;
            break;
        }

        case CAPTION_CC_OPACITY_TRANSLUCENT:
        {
            enUnfOpac = HI_UNF_CC_OPACITY_TRANSLUCENT;
            break;
        }

        case CAPTION_CC_OPACITY_TRANSPARENT:
        {
            enUnfOpac = HI_UNF_CC_OPACITY_TRANSPARENT;
            break;
        }

        default:
        {
            enUnfOpac = HI_UNF_CC_OPACITY_BUTT;
            break;
        }
    }

    *penUnfOpac = enUnfOpac;

    if (HI_UNF_CC_OPACITY_BUTT == enUnfOpac)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;

}

static S32 caption_cc_map_fontstyle_tounf(CAPTION_CC_FONTSTYLE_E enFontStyle, HI_UNF_CC_FONTSTYLE_E* penUnfFontStyle)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_CC_FONTSTYLE_E enUnfFontStyle = HI_UNF_CC_FONTSTYLE_BUTT;

    if (NULL == penUnfFontStyle)
    {
        return FAILURE;
    }

    switch (enFontStyle)
    {
        case CAPTION_CC_FONTSTYLE_DEFAULT:
        {
            enUnfFontStyle = HI_UNF_CC_FONTSTYLE_DEFAULT;
            break;
        }

        case CAPTION_CC_FONTSTYLE_NORMAL:
        {
            enUnfFontStyle = HI_UNF_CC_FONTSTYLE_NORMAL;
            break;
        }

        case CAPTION_CC_FONTSTYLE_ITALIC:
        {
            enUnfFontStyle = HI_UNF_CC_FONTSTYLE_ITALIC;
            break;
        }

        case CAPTION_CC_FONTSTYLE_UNDERLINE:
        {
            enUnfFontStyle = HI_UNF_CC_FONTSTYLE_UNDERLINE;
            break;
        }

        case CAPTION_CC_FONTSTYLE_ITALIC_UNDERLINE:
        {
            enUnfFontStyle = HI_UNF_CC_FONTSTYLE_ITALIC_UNDERLINE;
            break;
        }

        default:
        {
            enUnfFontStyle = HI_UNF_CC_FONTSTYLE_BUTT;
            break;
        }
    }

    *penUnfFontStyle = enUnfFontStyle;

    if (HI_UNF_CC_FONTSTYLE_BUTT == enUnfFontStyle)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;

}
static S32 caption_cc_map_dispfmt_tounf(CAPTION_CC_DF_E enDispFmt, HI_UNF_CC_DF_E* penUnfDispFmt)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_CC_DF_E enUnfDispFmt = HI_UNF_CC_DF_BUTT;

    if (NULL == penUnfDispFmt)
    {
        return FAILURE;
    }

    switch (enDispFmt)
    {
        case CAPTION_CC_DF_720X480:
        {
            enUnfDispFmt = HI_UNF_CC_DF_720X480;
            break;
        }

        case CAPTION_CC_DF_720X576:
        {
            enUnfDispFmt = HI_UNF_CC_DF_720X576;
            break;
        }

        case CAPTION_CC_DF_960X540:
        {
            enUnfDispFmt = HI_UNF_CC_DF_960X540;
            break;
        }

        case CAPTION_CC_DF_1280X720:
        {
            enUnfDispFmt = HI_UNF_CC_DF_1280X720;
            break;
        }

        case CAPTION_CC_DF_1920X1080:
        {
            enUnfDispFmt = HI_UNF_CC_DF_1920X1080;
            break;
        }

        default:
        {
            enUnfDispFmt = HI_UNF_CC_DF_BUTT;
            break;
        }
    }

    *penUnfDispFmt = enUnfDispFmt;

    if (HI_UNF_CC_DF_BUTT == enUnfDispFmt)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}

static S32 caption_cc_map_608attr_tounf(CAPTION_CC608_ATTR_S st608Attr, HI_UNF_CC_608_CONFIGPARAM_S* pstUnf608Attr)
{
    S32 s32Ret = SUCCESS;

    if (NULL == pstUnf608Attr)
    {
        return ERROR_NULL_PTR;
    }

    //cc data type
    s32Ret = caption_cc_map_608type_tounf(st608Attr.enCC608DataType, &(pstUnf608Attr->enCC608DataType));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC608DataType(0x%08x)", __func__, __LINE__, st608Attr.enCC608DataType);
        return ERROR_INVALID_PARAM;
    }

    //text color
    pstUnf608Attr->u32CC608TextColor = st608Attr.u32CC608TextColor;

    //text opacity
    s32Ret = caption_cc_map_opacity_tounf(st608Attr.enCC608TextOpac, &(pstUnf608Attr->enCC608TextOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC608TextOpac(0x%08x)", __func__, __LINE__, st608Attr.enCC608TextOpac);
        return ERROR_INVALID_PARAM;
    }

    //background color
    pstUnf608Attr->u32CC608BgColor = st608Attr.u32CC608BgColor;

    //background opacity
    s32Ret = caption_cc_map_opacity_tounf(st608Attr.enCC608BgOpac, &(pstUnf608Attr->enCC608BgOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC608BgOpac(0x%08x)", __func__, __LINE__, st608Attr.enCC608BgOpac);
        return ERROR_INVALID_PARAM;
    }

    //font style
    s32Ret = caption_cc_map_fontstyle_tounf(st608Attr.enCC608FontStyle, &(pstUnf608Attr->enCC608FontStyle));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC608FontStyle(0x%08x)", __func__, __LINE__, st608Attr.enCC608FontStyle);
        return ERROR_INVALID_PARAM;
    }

    //disp format
    s32Ret = caption_cc_map_dispfmt_tounf(st608Attr.enCC608DispFormat, &(pstUnf608Attr->enCC608DispFormat));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC608DispFormat(0x%08x)", __func__, __LINE__, st608Attr.enCC608DispFormat);
        return ERROR_INVALID_PARAM;
    }

    //Leading TailingSpace flag
    pstUnf608Attr->bLeadingTailingSpace = caption_bool_hal_to_unf(st608Attr.bLeadingTailingSpace);

    return SUCCESS;
}

static S32 caption_cc_map_708type_tounf(CAPTION_CC708_SERVICE_NUM_E enServNum, HI_UNF_CC_708_SERVICE_NUM_E* penUnfServNum)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_CC_708_SERVICE_NUM_E enUnfServNum = HI_UNF_CC_708_SERVICE_BUTT;

    if (NULL == penUnfServNum)
    {
        return FAILURE;
    }

    switch (enServNum)
    {
        case CAPTION_CC_708_SERVICE1:
        {
            enUnfServNum = HI_UNF_CC_708_SERVICE1;
            break;
        }

        case CAPTION_CC_708_SERVICE2:
        {
            enUnfServNum = HI_UNF_CC_708_SERVICE2;
            break;
        }

        case CAPTION_CC_708_SERVICE3:
        {
            enUnfServNum = HI_UNF_CC_708_SERVICE3;
            break;
        }

        case CAPTION_CC_708_SERVICE4:
        {
            enUnfServNum = HI_UNF_CC_708_SERVICE4;
            break;
        }

        case CAPTION_CC_708_SERVICE5:
        {
            enUnfServNum = HI_UNF_CC_708_SERVICE5;
            break;
        }

        case CAPTION_CC_708_SERVICE6:
        {
            enUnfServNum = HI_UNF_CC_708_SERVICE6;
            break;
        }

        default:
        {
            enUnfServNum = HI_UNF_CC_708_SERVICE_BUTT;
            break;
        }
    }

    *penUnfServNum = enUnfServNum;

    if (HI_UNF_CC_708_SERVICE_BUTT == enUnfServNum)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}

static S32 caption_cc_map_fontname_tounf(CAPTION_CC_FONTNAME_E enFontName, HI_UNF_CC_FONTNAME_E* penUnfFontName)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_CC_FONTNAME_E enUnfFontName = HI_UNF_CC_FN_BUTT;

    if (NULL == penUnfFontName)
    {
        return FAILURE;
    }

    switch (enFontName)
    {
        case CAPTION_CC_FN_DEFAULT:
        {
            enUnfFontName = HI_UNF_CC_FN_DEFAULT;
            break;
        }

        case CAPTION_CC_FN_MONOSPACED:
        {
            enUnfFontName = HI_UNF_CC_FN_MONOSPACED;
            break;
        }

        case CAPTION_CC_FN_PROPORT:
        {
            enUnfFontName = HI_UNF_CC_FN_PROPORT;
            break;
        }

        case CAPTION_CC_FN_MONOSPACED_NO_SERIAFS:
        {
            enUnfFontName = HI_UNF_CC_FN_MONOSPACED_NO_SERIAFS;
            break;
        }

        case CAPTION_CC_FN_PROPORT_NO_SERIAFS:
        {
            enUnfFontName = HI_UNF_CC_FN_PROPORT_NO_SERIAFS;
            break;
        }

        case CAPTION_CC_FN_CASUAL:
        {
            enUnfFontName = HI_UNF_CC_FN_CASUAL;
            break;
        }

        case CAPTION_CC_FN_CURSIVE:
        {
            enUnfFontName = HI_UNF_CC_FN_CURSIVE;
            break;
        }

        case CAPTION_CC_FN_SMALL_CAPITALS:
        {
            enUnfFontName = HI_UNF_CC_FN_SMALL_CAPITALS;
            break;
        }

        default:
        {
            enUnfFontName = HI_UNF_CC_FN_BUTT;
            break;
        }
    }

    *penUnfFontName = enUnfFontName;

    if (HI_UNF_CC_FN_BUTT == enUnfFontName)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}
static S32 caption_cc_map_fontsize_tounf(CAPTION_CC_FONTSIZE_E enFontSize, HI_UNF_CC_FONTSIZE_E* penUnfFontSize)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_CC_FONTSIZE_E enUnfFontSize = HI_UNF_CC_FONTSIZE_BUTT;

    if (NULL == penUnfFontSize)
    {
        return FAILURE;
    }

    switch (enFontSize)
    {
        case CAPTION_CC_FONTSIZE_DEFAULT:
        {
            enUnfFontSize = HI_UNF_CC_FONTSIZE_DEFAULT;
            break;
        }

        case CAPTION_CC_FONTSIZE_SMALL:
        {
            enUnfFontSize = HI_UNF_CC_FONTSIZE_SMALL;
            break;
        }

        case CAPTION_CC_FONTSIZE_STANDARD:
        {
            enUnfFontSize = HI_UNF_CC_FONTSIZE_STANDARD;
            break;
        }

        case CAPTION_CC_FONTSIZE_LARGE:
        {
            enUnfFontSize = HI_UNF_CC_FONTSIZE_LARGE;
            break;
        }

        default:
        {
            enUnfFontSize = HI_UNF_CC_FONTSIZE_BUTT;
            break;
        }
    }

    *penUnfFontSize = enUnfFontSize;

    if (HI_UNF_CC_FONTSIZE_BUTT == enUnfFontSize)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}

static S32 caption_cc_map_edgetype_tounf(CAPTION_CC_EDGETYPE_E enEdgeType, HI_UNF_CC_EdgeType_E* penUnfEdgeType)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_CC_EdgeType_E enUnfEdgeType = HI_UNF_CC_EDGETYPE_BUTT;

    if (NULL == penUnfEdgeType)
    {
        return FAILURE;
    }

    switch (enEdgeType)
    {
        case CAPTION_CC_EDGETYPE_DEFAULT:
        {
            enUnfEdgeType = HI_UNF_CC_EDGETYPE_DEFAULT;
            break;
        }

        case CAPTION_CC_EDGETYPE_NONE:
        {
            enUnfEdgeType = HI_UNF_CC_EDGETYPE_NONE;
            break;
        }

        case CAPTION_CC_EDGETYPE_RAISED:
        {
            enUnfEdgeType = HI_UNF_CC_EDGETYPE_RAISED;
            break;
        }

        case CAPTION_CC_EDGETYPE_DEPRESSED:
        {
            enUnfEdgeType = HI_UNF_CC_EDGETYPE_DEPRESSED;
            break;
        }

        case CAPTION_CC_EDGETYPE_UNIFORM:
        {
            enUnfEdgeType = HI_UNF_CC_EDGETYPE_UNIFORM;
            break;
        }

        case CAPTION_CC_EDGETYPE_LEFT_DROP_SHADOW:
        {
            enUnfEdgeType = HI_UNF_CC_EDGETYPE_LEFT_DROP_SHADOW;
            break;
        }

        case CAPTION_CC_EDGETYPE_RIGHT_DROP_SHADOW:
        {
            enUnfEdgeType = HI_UNF_CC_EDGETYPE_RIGHT_DROP_SHADOW;
            break;
        }

        default:
        {
            enUnfEdgeType = HI_UNF_CC_EDGETYPE_BUTT;
            break;
        }
    }

    *penUnfEdgeType = enUnfEdgeType;

    if (HI_UNF_CC_EDGETYPE_BUTT == enUnfEdgeType)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;

}

static S32 caption_cc_map_708attr_tounf(CAPTION_CC708_ATTR_S st708Attr, HI_UNF_CC_708_CONFIGPARAM_S* pstUnf708Attr)
{
    S32 s32Ret = SUCCESS;

    if (NULL == pstUnf708Attr)
    {
        return ERROR_NULL_PTR;
    }

    //CC708 service channel
    s32Ret = caption_cc_map_708type_tounf(st708Attr.enCC708ServiceNum, &(pstUnf708Attr->enCC708ServiceNum));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708ServiceNum(0x%08x)", __func__, __LINE__, st708Attr.enCC708ServiceNum);
        return ERROR_INVALID_PARAM;
    }

    //font name
    s32Ret = caption_cc_map_fontname_tounf(st708Attr.enCC708FontName, &(pstUnf708Attr->enCC708FontName));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708FontName(0x%08x)", __func__, __LINE__, st708Attr.enCC708FontName);
        return ERROR_INVALID_PARAM;
    }

    //font style
    s32Ret = caption_cc_map_fontstyle_tounf(st708Attr.enCC708FontStyle, &(pstUnf708Attr->enCC708FontStyle));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("caption_cc_map_fontstyle_tounf failed. enCC708FontStyle(0x%08x)", st708Attr.enCC708FontStyle);
        return ERROR_INVALID_PARAM;
    }

    //font size
    s32Ret = caption_cc_map_fontsize_tounf(st708Attr.enCC708FontSize, &(pstUnf708Attr->enCC708FontSize));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708FontSize(0x%08x)", __func__, __LINE__, st708Attr.enCC708FontSize);
        return ERROR_INVALID_PARAM;
    }

    //text color
    pstUnf708Attr->u32CC708TextColor = st708Attr.u32CC708TextColor;

    //text opacity
    s32Ret = caption_cc_map_opacity_tounf(st708Attr.enCC708TextOpac, &(pstUnf708Attr->enCC708TextOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708TextOpac(0x%08x)", __func__, __LINE__, st708Attr.enCC708TextOpac);
        return ERROR_INVALID_PARAM;
    }

    //backgrount color
    pstUnf708Attr->u32CC708BgColor = st708Attr.u32CC708BgColor;

    //backgrount opacity
    s32Ret = caption_cc_map_opacity_tounf(st708Attr.enCC708BgOpac, &(pstUnf708Attr->enCC708BgOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708BgOpac(0x%08x)", __func__, __LINE__, st708Attr.enCC708BgOpac);
        return ERROR_INVALID_PARAM;
    }

    //win color
    pstUnf708Attr->u32CC708WinColor = st708Attr.u32CC708WinColor;

    //win opacity
    s32Ret = caption_cc_map_opacity_tounf(st708Attr.enCC708WinOpac, &(pstUnf708Attr->enCC708WinOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708WinOpac(0x%08x)", __func__, __LINE__, st708Attr.enCC708WinOpac);
        return ERROR_INVALID_PARAM;
    }

    //edge type
    s32Ret = caption_cc_map_edgetype_tounf(st708Attr.enCC708TextEdgeType, &(pstUnf708Attr->enCC708TextEdgeType));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708TextEdgeType(0x%08x)", __func__, __LINE__, st708Attr.enCC708TextEdgeType);
        return ERROR_INVALID_PARAM;
    }

    return SUCCESS;
}

static S32 caption_cc_map_aribattr_tounf(CAPTION_ARIBCC_ATTR_S stAribAttr, HI_UNF_CC_ARIB_CONFIGPARAM_S* pstUnfAribAttr)
{
    if (NULL == pstUnfAribAttr)
    {
        return ERROR_NULL_PTR;
    }

    pstUnfAribAttr->u32BufferSize = stAribAttr.u32BufferSize;

    return SUCCESS;
}

static S32 caption_cc_map_type_tohal(HI_UNF_CC_DATA_TYPE_E enUnfCCType, CAPTION_CC_DATA_E* penCCType)
{
    S32 s32Ret = SUCCESS;
    CAPTION_CC_DATA_E enCCType = CAPTION_CC_DATA_BUTT;

    if (NULL == penCCType)
    {
        return FAILURE;
    }

    switch (enUnfCCType)
    {
        case HI_UNF_CC_DATA_TYPE_608:
        {
            enCCType = CAPTION_CC_DATA_608;
            break;
        }

        case HI_UNF_CC_DATA_TYPE_708:
        {
            enCCType = CAPTION_CC_DATA_708;
            break;
        }

        case HI_UNF_CC_DATA_TYPE_ARIB:
        {
            enCCType = CAPTION_CC_DATA_ARIB;
            break;
        }

        default:
        {
            enCCType = CAPTION_CC_DATA_BUTT;
            break;
        }
    }

    *penCCType = enCCType;

    if (CAPTION_CC_DATA_BUTT == enCCType)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}

static S32 caption_cc_map_opacity_tohal(HI_UNF_CC_OPACITY_E enUnfOpac, CAPTION_CC_OPACITY_E* penCCOpac)
{
    S32 s32Ret = SUCCESS;
    CAPTION_CC_OPACITY_E enCCOpac = CAPTION_CC_OPACITY_BUTT;

    if (NULL == penCCOpac)
    {
        return FAILURE;
    }

    switch (enUnfOpac)
    {
        case HI_UNF_CC_OPACITY_DEFAULT:
        {
            enCCOpac = CAPTION_CC_OPACITY_DEFAULT;
            break;
        }

        case HI_UNF_CC_OPACITY_SOLID:
        {
            enCCOpac = CAPTION_CC_OPACITY_SOLID;
            break;
        }

        case HI_UNF_CC_OPACITY_FLASH:
        {
            enCCOpac = CAPTION_CC_OPACITY_FLASH;
            break;
        }

        case HI_UNF_CC_OPACITY_TRANSLUCENT:
        {
            enCCOpac = CAPTION_CC_OPACITY_TRANSLUCENT;
            break;
        }

        case HI_UNF_CC_OPACITY_TRANSPARENT:
        {
            enCCOpac = CAPTION_CC_OPACITY_TRANSPARENT;
            break;
        }

        default:
        {
            enCCOpac = CAPTION_CC_OPACITY_BUTT;
            break;
        }
    }

    *penCCOpac = enCCOpac;

    if (CAPTION_CC_OPACITY_BUTT == enCCOpac)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}

static S32 caption_cc_map_fontstyle_tohal(HI_UNF_CC_FONTSTYLE_E enUnfFontStyle, CAPTION_CC_FONTSTYLE_E* penFontStyle)
{
    S32 s32Ret = SUCCESS;
    CAPTION_CC_FONTSTYLE_E enFontStyle = CAPTION_CC_FONTSTYLE_BUTT;

    if (NULL == penFontStyle)
    {
        return FAILURE;
    }

    switch (enUnfFontStyle)
    {
        case HI_UNF_CC_FONTSTYLE_DEFAULT:
        {
            enFontStyle = CAPTION_CC_FONTSTYLE_DEFAULT;
            break;
        }

        case HI_UNF_CC_FONTSTYLE_NORMAL:
        {
            enFontStyle = CAPTION_CC_FONTSTYLE_NORMAL;
            break;
        }

        case HI_UNF_CC_FONTSTYLE_ITALIC:
        {
            enFontStyle = CAPTION_CC_FONTSTYLE_ITALIC;
            break;
        }

        case HI_UNF_CC_FONTSTYLE_UNDERLINE:
        {
            enFontStyle = CAPTION_CC_FONTSTYLE_UNDERLINE;
            break;
        }

        case HI_UNF_CC_FONTSTYLE_ITALIC_UNDERLINE:
        {
            enFontStyle = CAPTION_CC_FONTSTYLE_ITALIC_UNDERLINE;
            break;
        }

        default:
        {
            enFontStyle = CAPTION_CC_FONTSTYLE_BUTT;
            break;
        }
    }

    *penFontStyle = enFontStyle;

    if (CAPTION_CC_FONTSTYLE_BUTT == enFontStyle)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;

}
static S32 caption_cc_map_dispfmt_tohal(HI_UNF_CC_DF_E enUnfDispFmt, CAPTION_CC_DF_E* penDispFmt)
{
    S32 s32Ret = SUCCESS;
    CAPTION_CC_DF_E enDispFmt = CAPTION_CC_DF_BUTT;

    if (NULL == penDispFmt)
    {
        return FAILURE;
    }

    switch (enUnfDispFmt)
    {
        case HI_UNF_CC_DF_720X480:
        {
            enDispFmt = CAPTION_CC_DF_720X480;
            break;
        }

        case HI_UNF_CC_DF_720X576:
        {
            enDispFmt = CAPTION_CC_DF_720X576;
            break;
        }

        case HI_UNF_CC_DF_960X540:
        {
            enDispFmt = CAPTION_CC_DF_960X540;
            break;
        }

        case HI_UNF_CC_DF_1280X720:
        {
            enDispFmt = CAPTION_CC_DF_1280X720;
            break;
        }

        case HI_UNF_CC_DF_1920X1080:
        {
            enDispFmt = CAPTION_CC_DF_1920X1080;
            break;
        }

        default:
        {
            enDispFmt = CAPTION_CC_DF_BUTT;
            break;
        }
    }

    *penDispFmt = enDispFmt;

    if (CAPTION_CC_DF_BUTT == enDispFmt)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}

static S32 caption_cc_map_608attr_tohal(HI_UNF_CC_608_CONFIGPARAM_S stUnf608Attr, CAPTION_CC608_ATTR_S* pst608Attr)
{
    S32 s32Ret = SUCCESS;

    if (NULL == pst608Attr)
    {
        return ERROR_NULL_PTR;
    }

    //text color
    pst608Attr->u32CC608TextColor = stUnf608Attr.u32CC608TextColor;

    //text opacity
    s32Ret = caption_cc_map_opacity_tohal(stUnf608Attr.enCC608TextOpac, &(pst608Attr->enCC608TextOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC608TextOpac(0x%08x)", __func__, __LINE__, stUnf608Attr.enCC608TextOpac);
        return ERROR_INVALID_PARAM;
    }

    //background color
    pst608Attr->u32CC608BgColor = stUnf608Attr.u32CC608BgColor;

    //background opacity
    s32Ret = caption_cc_map_opacity_tohal(stUnf608Attr.enCC608BgOpac, &(pst608Attr->enCC608BgOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC608BgOpac(0x%08x)", __func__, __LINE__, stUnf608Attr.enCC608BgOpac);
        return ERROR_INVALID_PARAM;
    }

    //font style
    s32Ret = caption_cc_map_fontstyle_tohal(stUnf608Attr.enCC608FontStyle, &(pst608Attr->enCC608FontStyle));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC608FontStyle(0x%08x)", __func__, __LINE__, stUnf608Attr.enCC608FontStyle);
        return ERROR_INVALID_PARAM;
    }

    //disp format
    s32Ret = caption_cc_map_dispfmt_tohal(stUnf608Attr.enCC608DispFormat, &(pst608Attr->enCC608DispFormat));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC608DispFormat(0x%08x)", __func__, __LINE__, stUnf608Attr.enCC608DispFormat);
        return ERROR_INVALID_PARAM;
    }

    //Leading TailingSpace flag
    pst608Attr->bLeadingTailingSpace = caption_bool_unf_to_hal(stUnf608Attr.bLeadingTailingSpace);

    return SUCCESS;
}

static S32 caption_cc_map_708type_tohal(HI_UNF_CC_708_SERVICE_NUM_E enUnfServNum, CAPTION_CC708_SERVICE_NUM_E* penServNum)
{
    S32 s32Ret = SUCCESS;
    CAPTION_CC708_SERVICE_NUM_E enServNum = CAPTION_CC_708_SERVICE_BUTT;

    if (NULL == penServNum)
    {
        return FAILURE;
    }

    switch (enUnfServNum)
    {
        case HI_UNF_CC_708_SERVICE1:
        {
            enServNum = CAPTION_CC_708_SERVICE1;
            break;
        }

        case HI_UNF_CC_708_SERVICE2:
        {
            enServNum = CAPTION_CC_708_SERVICE2;
            break;
        }

        case HI_UNF_CC_708_SERVICE3:
        {
            enServNum = CAPTION_CC_708_SERVICE3;
            break;
        }

        case HI_UNF_CC_708_SERVICE4:
        {
            enServNum = CAPTION_CC_708_SERVICE4;
            break;
        }

        case HI_UNF_CC_708_SERVICE5:
        {
            enServNum = CAPTION_CC_708_SERVICE5;
            break;
        }

        case HI_UNF_CC_708_SERVICE6:
        {
            enServNum = CAPTION_CC_708_SERVICE6;
            break;
        }

        default:
        {
            enServNum = CAPTION_CC_708_SERVICE_BUTT;
            break;
        }
    }

    *penServNum = enServNum;

    if (CAPTION_CC_708_SERVICE_BUTT == enServNum)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}

static S32 caption_cc_map_fontname_tohal(HI_UNF_CC_FONTNAME_E enUnfFontName, CAPTION_CC_FONTNAME_E* penFontName)
{
    S32 s32Ret = SUCCESS;
    CAPTION_CC_FONTNAME_E enFontName = CAPTION_CC_FN_BUTT;

    if (NULL == penFontName)
    {
        return FAILURE;
    }

    switch (enUnfFontName)
    {
        case HI_UNF_CC_FN_DEFAULT:
        {
            enFontName = CAPTION_CC_FN_DEFAULT;
            break;
        }

        case HI_UNF_CC_FN_MONOSPACED:
        {
            enFontName = CAPTION_CC_FN_DEFAULT;
            break;
        }

        case HI_UNF_CC_FN_PROPORT:
        {
            enFontName = CAPTION_CC_FN_PROPORT;
            break;
        }

        case HI_UNF_CC_FN_MONOSPACED_NO_SERIAFS:
        {
            enFontName = CAPTION_CC_FN_PROPORT;
            break;
        }

        case HI_UNF_CC_FN_PROPORT_NO_SERIAFS:
        {
            enFontName = CAPTION_CC_FN_PROPORT_NO_SERIAFS;
            break;
        }

        case HI_UNF_CC_FN_CASUAL:
        {
            enFontName = CAPTION_CC_FN_CASUAL;
            break;
        }

        case HI_UNF_CC_FN_CURSIVE:
        {
            enFontName = CAPTION_CC_FN_CURSIVE;
            break;
        }

        case HI_UNF_CC_FN_SMALL_CAPITALS:
        {
            enFontName = CAPTION_CC_FN_SMALL_CAPITALS;
            break;
        }

        default:
        {
            enFontName = CAPTION_CC_FN_BUTT;
            break;
        }
    }

    *penFontName = enFontName;

    if (CAPTION_CC_FN_BUTT == enFontName)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}
static S32 caption_cc_map_fontsize_tohal(HI_UNF_CC_FONTSIZE_E enUnfFontSize, CAPTION_CC_FONTSIZE_E* penFontSize)
{
    S32 s32Ret = SUCCESS;
    CAPTION_CC_FONTSIZE_E enFontSize = CAPTION_CC_FONTSIZE_BUTT;

    if (NULL == penFontSize)
    {
        return FAILURE;
    }

    switch (enUnfFontSize)
    {
        case HI_UNF_CC_FONTSIZE_DEFAULT:
        {
            enFontSize = CAPTION_CC_FONTSIZE_DEFAULT;
            break;
        }

        case HI_UNF_CC_FONTSIZE_SMALL:
        {
            enFontSize = CAPTION_CC_FONTSIZE_SMALL;
            break;
        }

        case HI_UNF_CC_FONTSIZE_STANDARD:
        {
            enFontSize = CAPTION_CC_FONTSIZE_STANDARD;
            break;
        }

        case HI_UNF_CC_FONTSIZE_LARGE:
        {
            enFontSize = CAPTION_CC_FONTSIZE_LARGE;
            break;
        }

        default:
        {
            enFontSize = CAPTION_CC_FONTSIZE_BUTT;
            break;
        }
    }

    *penFontSize = enFontSize;

    if (CAPTION_CC_FONTSIZE_BUTT == enFontSize)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;
}

static S32 caption_cc_map_edgetype_tohal(HI_UNF_CC_EdgeType_E enUnfEdgeType, CAPTION_CC_EDGETYPE_E* penEdgeType)
{
    S32 s32Ret = SUCCESS;
    CAPTION_CC_EDGETYPE_E enEdgeType = CAPTION_CC_EDGETYPE_BUTT;

    if (NULL == penEdgeType)
    {
        return FAILURE;
    }

    switch (enUnfEdgeType)
    {
        case HI_UNF_CC_EDGETYPE_DEFAULT:
        {
            enEdgeType = CAPTION_CC_EDGETYPE_DEFAULT;
            break;
        }

        case HI_UNF_CC_EDGETYPE_NONE:
        {
            enEdgeType = CAPTION_CC_EDGETYPE_NONE;
            break;
        }

        case HI_UNF_CC_EDGETYPE_RAISED:
        {
            enEdgeType = CAPTION_CC_EDGETYPE_RAISED;
            break;
        }

        case HI_UNF_CC_EDGETYPE_DEPRESSED:
        {
            enEdgeType = CAPTION_CC_EDGETYPE_DEPRESSED;
            break;
        }

        case HI_UNF_CC_EDGETYPE_UNIFORM:
        {
            enEdgeType = CAPTION_CC_EDGETYPE_UNIFORM;
            break;
        }

        case HI_UNF_CC_EDGETYPE_LEFT_DROP_SHADOW:
        {
            enEdgeType = CAPTION_CC_EDGETYPE_LEFT_DROP_SHADOW;
            break;
        }

        case HI_UNF_CC_EDGETYPE_RIGHT_DROP_SHADOW:
        {
            enEdgeType = CAPTION_CC_EDGETYPE_RIGHT_DROP_SHADOW;
            break;
        }

        default:
        {
            enEdgeType = CAPTION_CC_EDGETYPE_BUTT;
            break;
        }
    }

    *penEdgeType = enEdgeType;

    if (CAPTION_CC_EDGETYPE_BUTT == enEdgeType)
    {
        s32Ret = FAILURE;
    }

    return s32Ret;

}

static S32 caption_cc_map_708attr_tohal(HI_UNF_CC_708_CONFIGPARAM_S stUnf708Attr, CAPTION_CC708_ATTR_S* pst708Attr)
{
    S32 s32Ret = SUCCESS;

    if (NULL == pst708Attr)
    {
        return ERROR_NULL_PTR;
    }

    //CC708 service channel
    s32Ret = caption_cc_map_708type_tohal(stUnf708Attr.enCC708ServiceNum, &(pst708Attr->enCC708ServiceNum));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708ServiceNum(0x%08x)", __func__, __LINE__, stUnf708Attr.enCC708ServiceNum);
        return ERROR_INVALID_PARAM;
    }

    //font name
    s32Ret = caption_cc_map_fontname_tohal(stUnf708Attr.enCC708FontName, &(pst708Attr->enCC708FontName));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708FontName(0x%08x)", __func__, __LINE__, stUnf708Attr.enCC708FontName);
        return ERROR_INVALID_PARAM;
    }

    //font style
    s32Ret = caption_cc_map_fontstyle_tohal(stUnf708Attr.enCC708FontStyle, &(pst708Attr->enCC708FontStyle));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708FontStyle(0x%08x)", __func__, __LINE__, stUnf708Attr.enCC708FontStyle);
        return ERROR_INVALID_PARAM;
    }

    //font size
    s32Ret = caption_cc_map_fontsize_tohal(stUnf708Attr.enCC708FontSize, &(pst708Attr->enCC708FontSize));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708FontSize(0x%08x)", __func__, __LINE__, stUnf708Attr.enCC708FontSize);
        return ERROR_INVALID_PARAM;
    }

    //text color
    pst708Attr->u32CC708TextColor = stUnf708Attr.u32CC708TextColor;

    //text opacity
    s32Ret = caption_cc_map_opacity_tohal(stUnf708Attr.enCC708TextOpac, &(pst708Attr->enCC708TextOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708TextOpac(0x%08x)", __func__, __LINE__, stUnf708Attr.enCC708TextOpac);
        return ERROR_INVALID_PARAM;
    }

    //backgrount color
    pst708Attr->u32CC708BgColor = stUnf708Attr.u32CC708BgColor;

    //backgrount opacity
    s32Ret = caption_cc_map_opacity_tohal(stUnf708Attr.enCC708BgOpac, &(pst708Attr->enCC708BgOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708BgOpac(0x%08x)", __func__, __LINE__, stUnf708Attr.enCC708BgOpac);
        return ERROR_INVALID_PARAM;
    }

    //win color
    pst708Attr->u32CC708WinColor = stUnf708Attr.u32CC708WinColor;

    //win opacity
    s32Ret = caption_cc_map_opacity_tohal(stUnf708Attr.enCC708WinOpac, &(pst708Attr->enCC708WinOpac));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708WinOpac(0x%08x)", __func__, __LINE__, stUnf708Attr.enCC708WinOpac);
        return ERROR_INVALID_PARAM;
    }

    //edge type
    s32Ret = caption_cc_map_edgetype_tohal(stUnf708Attr.enCC708TextEdgeType, &(pst708Attr->enCC708TextEdgeType));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCC708TextEdgeType(0x%08x)", __func__, __LINE__, stUnf708Attr.enCC708TextEdgeType);
        return ERROR_INVALID_PARAM;
    }

    return SUCCESS;

}

static S32 caption_cc_map_aribattr_tohal(HI_UNF_CC_ARIB_CONFIGPARAM_S stUnfAribAttr, CAPTION_ARIBCC_ATTR_S* pstAribAttr)
{
    if (NULL == pstAribAttr)
    {
        return ERROR_NULL_PTR;
    }

    pstAribAttr->u32BufferSize = stUnfAribAttr.u32BufferSize;

    return SUCCESS;

}

static S32 caption_cc_get_pts(U32 u32UserData, HI_S64* ps64CurrentPts)
{
    if (CAPTION_SHOW != s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    return SUCCESS;
}

static S32 caption_cc_draw(U32 u32UserData, HI_UNF_CC_DISPLAY_PARAM_S* pstDisplayParam)
{
    S32 s32Ret = SUCCESS;

    if (CAPTION_SHOW != s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    s32Ret = caption_cc_output_draw(u32UserData, pstDisplayParam);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return ERROR_INVALID_PARAM;
    }

    return SUCCESS;
}

static S32 caption_cc_get_textsize(U32 u32Userdata, HI_U16* u16Str, S32 s32StrNum, S32* ps32Width, S32* ps32Heigth)
{
    S32 s32Ret = SUCCESS;

    if (CAPTION_SHOW != s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    s32Ret = caption_cc_output_get_textsize(u32Userdata, u16Str, s32StrNum, ps32Width, ps32Heigth);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return ERROR_INVALID_PARAM;
    }

    return SUCCESS;
}

static S32 caption_cc_blit(U32 u32UserPrivatData, HI_UNF_CC_RECT_S* pstSrcRect, HI_UNF_CC_RECT_S* pstDestRect)
{
    S32 s32Ret = SUCCESS;

    if (CAPTION_SHOW != s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    s32Ret = caption_cc_output_blit(u32UserPrivatData, pstSrcRect, pstDestRect);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return ERROR_INVALID_PARAM;
    }

    return SUCCESS;
}

static S32 caption_cc_vbi(U32 u32UserData, HI_UNF_CC_VBI_DADA_S* pstVBIOddDataField1, HI_UNF_CC_VBI_DADA_S* pstVBIEvenDataField2)
{
    S32 s32Ret = SUCCESS;

    if (CAPTION_SHOW != s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    s32Ret = caption_cc_output_vbi(u32UserData, pstVBIOddDataField1, pstVBIEvenDataField2);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return ERROR_INVALID_PARAM;
    }

    return SUCCESS;
}

static S32 caption_cc_xds_decode(HI_U8 u8XDSClass, HI_U8 u8XDSType, HI_U8* pu8Data, HI_U8 u8DataLen)
{
    S32 s32Ret = SUCCESS;

    if (CAPTION_SHOW != s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    s32Ret = caption_cc_output_xds(u8XDSClass, u8XDSType, pu8Data, u8DataLen);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return ERROR_INVALID_PARAM;
    }

    return SUCCESS;
}

static S32 caption_cc_stop(VOID)
{
    S32 s32Ret = FAILURE;
    HANDLE hCC = INVALID_CAPTION_HANDLE;

    if (CAPTION_STOPPED == s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_DEBUG("%s,%d error!! cc already stopped", __func__, __LINE__);
        return SUCCESS;
    }

    hCC = s_stCaptionModule.stCCInfo.hCC;

    if (INVALID_CAPTION_HANDLE != hCC)
    {
        s32Ret = HI_UNF_CC_Stop(hCC);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s_stCaptionModule.stCCInfo.enStatus = CAPTION_STOPPED;

    return SUCCESS;
}


static S32 caption_cc_destroy(VOID)
{
    S32 s32Ret = FAILURE;
    HANDLE hCC = INVALID_CAPTION_HANDLE;

    hCC = s_stCaptionModule.stCCInfo.hCC;

    (VOID)caption_cc_stop();

    s32Ret = HI_UNF_CC_Destroy(hCC);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    if (INVALID_CAPTION_HANDLE != s_stCaptionModule.stCCInfo.hOut)
    {
        s32Ret = caption_cc_output_deinit(s_stCaptionModule.stCCInfo.hOut);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }

        s_stCaptionModule.stCCInfo.hOut = INVALID_CAPTION_HANDLE;
    }

    s_stCaptionModule.stCCInfo.hCC = INVALID_CAPTION_HANDLE;
    return SUCCESS;
}

/******************************* API Declaration *****************************/

/**
\brief Caption init.CNcomment:字幕初始化 CNend
\attention \n
repeat call return success.
CNcomment:本函数重复调用返回成功. CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_CAPTION_INIT_FAILED  Caption init error.CNcomment:字幕初始化错误。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
none. CNcomment: 无。CNend
*/
static S32 caption_init(CAPTION_DEVICE_S* pstDev, const CAPTION_INIT_PARAMS_S* const pstInitParams)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_PTR(pstInitParams);

#ifdef LINUX_OS
    if (FALSE == s_bHigoInit)
    {
        s32Ret = HI_GO_Init();
        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("failed to init higo! ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }
        s_bHigoInit = TRUE;
    }
#endif

    switch (pstInitParams->enCaptionType)
    {
        case CAPTION_TYPE_SUBT:
        {
            /* Return success if already inited */
            if (s_stCaptionModule.bSubtInited)
            {
                HAL_DEBUG("%s,%d Already Inited.!!", __func__, __LINE__);
                return SUCCESS;
            }
            s32Ret = HI_UNF_SUBT_Init();

            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
                return ERROR_CAPTION_INIT_FAILED;
            }

            s32Ret = HI_UNF_SO_Init();

            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
                return ERROR_CAPTION_INIT_FAILED;
            }

            memset(&s_stCaptionModule.stSubtInfo, 0, sizeof(SUBT_MODULE_S));
            s_stCaptionModule.bSubtInited = TRUE;
            break;
        }
        case CAPTION_TYPE_TTX:
        {
            if (s_stCaptionModule.bTtxInited)
            {
                HAL_DEBUG("%s,%d Already Inited.!!", __func__, __LINE__);
                return SUCCESS;
            }

            s32Ret = HI_UNF_TTX_Init();
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
                return ERROR_CAPTION_INIT_FAILED;
            }

            memset(&s_stCaptionModule.stTtxInfo, 0, sizeof(TTX_MODULE_S));
            s_stCaptionModule.bTtxInited = TRUE;
            break;
        }
        case CAPTION_TYPE_CC:
        {
            if (s_stCaptionModule.bCcInited)
            {
                HAL_DEBUG("%s,%d Already Inited.!!", __func__, __LINE__);
                return SUCCESS;
            }

            s32Ret = HI_UNF_CC_Init();
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
                return ERROR_CAPTION_INIT_FAILED;
            }

            memset(&s_stCaptionModule.stCCInfo, 0, sizeof(CC_MODULE_S));
            s_stCaptionModule.bCcInited = TRUE;
            break;
        }
        default:
            break;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Caption term.CNcomment:字幕终止 CNend
\attention \n
repeat call return success.
CNcomment:本函数重复调用返回成功. CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_CAPTION_INIT_FAILED  Caption init error.CNcomment:字幕去初始化错误。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
none. CNcomment: 无。CNend
*/
static S32 caption_term(CAPTION_DEVICE_S* pstDev, const CAPTION_TERM_PARAM_S* const pstTermParams)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_PTR(pstTermParams);

    switch (pstTermParams->enCaptionType)
    {
        case CAPTION_TYPE_SUBT:
        {
            if (!s_stCaptionModule.bSubtInited)
            {
                HAL_DEBUG("%s,%d Not Inited!! ", __func__, __LINE__);
                return SUCCESS;
            }

            //stop
            s32Ret = caption_subt_stop();
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            }

            //deinit
            s32Ret = HI_UNF_SO_DeInit();
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            }

            s32Ret = HI_UNF_SUBT_DeInit();
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            }

            memset(&s_stCaptionModule.stSubtInfo, 0, sizeof(SUBT_MODULE_S));
            s_stCaptionModule.bSubtInited = FALSE;
            break;
        }
        case CAPTION_TYPE_TTX:
        {
            if (!s_stCaptionModule.bTtxInited)
            {
                HAL_DEBUG("%s,%d Not Inited!! ", __func__, __LINE__);
                return SUCCESS;
            }

            s32Ret = caption_ttx_stop();
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            }

            s32Ret = HI_UNF_TTX_DeInit();
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            }
            memset(&s_stCaptionModule.stTtxInfo, 0, sizeof(TTX_MODULE_S));
            s_stCaptionModule.bTtxInited = FALSE;
            break;
        }
        case CAPTION_TYPE_CC:
        {
            if (!s_stCaptionModule.bCcInited)
            {
                HAL_DEBUG("%s,%d Not Inited!! ", __func__, __LINE__);
                return SUCCESS;
            }

            s32Ret = caption_cc_destroy();
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            }

            s32Ret = HI_UNF_CC_DeInit();
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            }

            memset(&s_stCaptionModule.stCCInfo, 0, sizeof(CC_MODULE_S));
            s_stCaptionModule.bCcInited = FALSE;
            break;
        }
        default:
            break;
    }

#ifdef LINUX_OS
    if (TRUE == s_bHigoInit)
    {
        s32Ret = HI_GO_Deinit();
        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_Deinit failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }
        s_bHigoInit = FALSE;
    }
#endif

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Caption data inject.CNcomment:字幕解析数据注入处理 CNend
\attention \n
repeat call return success.
本函数重复调用返回成功. CNend
\param[in] enCaptionType caption type param.CNcomment:字幕类型 CNend
\param[in] pu8Data caption data param.CNcomment:字幕数据 CNend
\param[in] u32DataSize caption data size param. CNcomment:字幕数据大小 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
\retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::CAPTION_TYPE_E

\par example
\code
CAPTION_TYPE_E enCaptionType;
enCaptionType = CAPTION_TYPE_SUBT;
if (SUCCESS != caption_common_injectData(pstDev, enCaptionType, pu8Data, u32DataSize))
{
return FAILUE;
}

\endcode
*/
static S32 caption_common_injectData(CAPTION_DEVICE_S* pstDev, CAPTION_TYPE_E enCaptionType, U8* pu8Data, U32 u32DataSize)
{
    S32 s32Ret = SUCCESS;

    CAPTION_CHK_PTR(pu8Data);
    CAPTION_CHK_PARA(0 == u32DataSize);

    switch (enCaptionType)
    {
        case CAPTION_TYPE_SUBT:
        {
            CAPTION_CHK_SUBT_INIT();
            s32Ret = caption_subt_inject_data(pu8Data, u32DataSize);
            break;
        }

        case CAPTION_TYPE_TTX:
        {
            CAPTION_CHK_TTX_INIT();
            s32Ret = caption_ttx_inject_data(pu8Data, u32DataSize);
            break;
        }

        case CAPTION_TYPE_CC:
        {
            CAPTION_CHK_CC_INIT();
            s32Ret = caption_cc_inject_data(pu8Data, u32DataSize);
            break;
        }

        default:
        {
            HAL_ERROR("%s,%d error!! enCaptionType(0x%08x)", __func__, __LINE__, enCaptionType);
            return ERROR_INVALID_PARAM;
        }
    }

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return SUCCESS;
}

/**
\brief Caption position of display.CNcomment:字幕显示区域 CNend
\attention \n
repeat call return success.
本函数重复调用返回成功. CNend
\param[in] u32PosX position x.CNcomment:显示位置x CNend
\param[in] u32PosY position y.CNcomment:显示位置y CNend
\param[in] u32PosWidth the width of position. CNcomment:显示宽度 CNend
\param[in] u32PosHeight the height of position . CNcomment:显示高 度CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
none. CNcomment: 无。CNend
*/
static S32 caption_set_window(CAPTION_DEVICE_S* pstDev, U32 u32PosX, U32 u32PosY, U32 u32PosWidth, U32 u32PosHeight)
{
    S32 s32Ret = SUCCESS;
    HI_RECT_S stWinRect = {0, 0, 0, 0};

    HAL_DEBUG_ENTER();

    CAPTION_CHK_PARA(0 == u32PosWidth);
    CAPTION_CHK_PARA(0 == u32PosHeight);
    if (FALSE == s_stCaptionModule.bSubtInited
        && FALSE == s_stCaptionModule.bTtxInited
        && FALSE == s_stCaptionModule.bCcInited )
    {
        return ERROR_NOT_INITED;
    }

    stWinRect.s32X = u32PosX;
    stWinRect.s32Y = u32PosY;
    stWinRect.s32Width = u32PosWidth;
    stWinRect.s32Height = u32PosHeight;

    if ((CAPTION_RUNNING == s_stCaptionModule.stSubtInfo.enStatus) ||
        (CAPTION_SHOW == s_stCaptionModule.stSubtInfo.enStatus) ||
        (CAPTION_HIDE == s_stCaptionModule.stSubtInfo.enStatus))
    {
        s32Ret = caption_subt_output_create_surface(stWinRect);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    if ((CAPTION_RUNNING == s_stCaptionModule.stTtxInfo.enStatus) ||
        (CAPTION_SHOW == s_stCaptionModule.stTtxInfo.enStatus) ||
        (CAPTION_HIDE == s_stCaptionModule.stTtxInfo.enStatus))
    {
        s32Ret = caption_ttx_output_create_surface(stWinRect);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    if ((CAPTION_RUNNING == s_stCaptionModule.stCCInfo.enStatus) ||
        (CAPTION_SHOW == s_stCaptionModule.stCCInfo.enStatus) ||
        (CAPTION_HIDE == s_stCaptionModule.stCCInfo.enStatus))
    {
        s32Ret = caption_cc_output_create_surface(stWinRect);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/*****************Subtitle相关函数*******************************/
/**
\brief Subtitle start.CNcomment:Subtitle 字幕启动 。CNend
\attention \n
call flow:start->setWindow->switch->inject->show->hide->stop.
调用流程:start->setWindow->switch->inject->show->hide->stop。CNend
\param[in] stSubtParam start param.CNcomment:启动参数 。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
::CAPTION_SUBT_PARAM_S

\par example
\code
CAPTION_SUBT_PARAM_S stSubtParam;
memset(&stSubtParam, 0x0, sizeof(CAPTION_SUBT_PARAM_S));
stSubtParam.enSubtDataType = CAPTION_SUBT_DATA_DVB;
if (SUCCESS != subt_start(pstDev, stSubtParam))
{
return FAILUE;
}

\endcode
*/
static S32 subt_start(CAPTION_DEVICE_S* pstDev, CAPTION_SUBT_PARAM_S* pstSubtParam)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_SUBT_INIT();
    CAPTION_CHK_PTR(pstSubtParam);
    CAPTION_CHK_PTR(pstSubtParam->pfnGetPts);
    CAPTION_CHK_PARA(CAPTION_SUBT_DATA_BUTT <= pstSubtParam->enSubtDataType);

    if (INVALID_CAPTION_HANDLE != s_stCaptionModule.stSubtInfo.hSo)
    {
        s32Ret = caption_subt_stop();

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s32Ret = caption_subt_start(pstSubtParam);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Subtitle switch.CNcomment:Subtitle 字幕切换 。CNend
\attention \n
none.CNcomment: 无。CNend
\param[in] stSubtItem subt item to dispaly.CNcomment:字幕显示项 。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
::CAPTION_SUBT_ITEM_S

\par example
\code
CAPTION_SUBT_ITEM_S stSubtItem;
memset(&stSubtItem, 0x0, sizeof(CAPTION_SUBT_ITEM_S));
stSubtItem.u32SubtPID = 0x1ff;
stSubtItem.u16PageID = 0x01;
stSubtItem.u16AncillaryID = 0x02;
if (SUCCESS != subt_switch(pstDev, stSubtItem))
{
return FAILUE;
}

\endcode
*/
static S32 subt_switch(CAPTION_DEVICE_S* pstDev, CAPTION_SUBT_ITEM_S* pstSubtItem)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_SUBT_INIT();
    CAPTION_CHK_PTR(pstSubtItem);

    //switch subt content
    s32Ret = caption_subt_switch(pstSubtItem);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Subtitle show.CNcomment:Subtitle 字幕显示 。CNend
\attention \n
none.CNcomment: 无。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
none. CNcomment: 无。CNend
*/
static S32 subt_show(CAPTION_DEVICE_S* pstDev)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_SUBT_INIT();

    if ((CAPTION_BUTT == s_stCaptionModule.stSubtInfo.enStatus) ||
        (CAPTION_STOPPED == s_stCaptionModule.stSubtInfo.enStatus))
    {
        HAL_ERROR("status error!! subtitle status = 0x%08x", s_stCaptionModule.stSubtInfo.enStatus);
        return FAILURE;
    }

    s32Ret = caption_subt_reset();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s_stCaptionModule.stSubtInfo.enStatus = CAPTION_SHOW;

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Subtitle hide.CNcomment:Subtitle 字幕隐藏 。CNend
\attention \n
none.CNcomment: 无。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
none. CNcomment: 无。CNend
*/
static S32 subt_hide(CAPTION_DEVICE_S* pstDev)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_SUBT_INIT();

    s32Ret = caption_subt_hide();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Subtitle stop.CNcomment:Subtitle 字幕停止 。CNend
\attention \n
clear all display, stop all subt work no matter subt show or hide.
清空所有的字幕显示及工作, 不管是在Show 还是Hide 状态。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
none. CNcomment: 无。CNend
*/
S32 subt_stop(CAPTION_DEVICE_S* pstDev)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_SUBT_INIT();

    s32Ret = caption_subt_stop();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief set Subtitle Items.CNcomment:设置多个字幕项，可以用来事先将多个字幕项设置给字幕模块，以提高切换字幕时的速度 。CNend
\attention \n
none.CNcomment: 无。CNend
\param[in] pstSubtItem the number of subt items .CNcomment:字幕项个数 。CNend
\param[in] pstSubtItem subt items.CNcomment:要设置的字幕项 。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
none. CNcomment: 无。CNend
*/
S32 subt_setItems(struct _CAPTION_DEVICE_S* pstDev, U32 u32ItemNum, CAPTION_SUBT_ITEM_S *pstSubtItem)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_SUBT_INIT();
    CAPTION_CHK_PTR(pstSubtItem);
    CAPTION_CHK_PARA(0 >= u32ItemNum);

    SUBT_MODULE_S* pstSubtInfo = NULL;
    HANDLE hSubt = INVALID_CAPTION_HANDLE;
    U32 i = 0;
    U32 u32ItemCount = 0;

    pstSubtInfo = &(s_stCaptionModule.stSubtInfo);
    hSubt = pstSubtInfo->hSubt;

    //update subt item
    HI_UNF_SUBT_PARAM_S stUpdateParam;
    memset(&stUpdateParam, 0, sizeof(HI_UNF_SUBT_PARAM_S));

    for (i = 0; (i < u32ItemNum) && (i < SUBT_ITEM_MAX_NUM); i++)
    {
        stUpdateParam.astItems[i].u32SubtPID = pstSubtItem[i].u32SubtPID;
        stUpdateParam.astItems[i].u16PageID = pstSubtItem[i].u16PageID;
        stUpdateParam.astItems[i].u16AncillaryID = pstSubtItem[i].u16AncillaryID;
        pstSubtInfo->astSubtItems[i].u32SubtPID = pstSubtItem[i].u32SubtPID;
        pstSubtInfo->astSubtItems[i].u16PageID = pstSubtItem[i].u16PageID;
        pstSubtInfo->astSubtItems[i].u16AncillaryID = pstSubtItem[i].u16AncillaryID;
        u32ItemCount++;
    }

    stUpdateParam.u8SubtItemNum = u32ItemCount;
    stUpdateParam.pfnCallback = (HI_UNF_SUBT_CALLBACK_FN)caption_subt_callback;
    stUpdateParam.pUserData = HI_NULL;

    pstSubtInfo->u32SubtItemNum = u32ItemCount;

    caption_subt_maptype_tounf(pstSubtInfo->enSubtDataType, &(stUpdateParam.enDataType));

    s32Ret = HI_UNF_SUBT_Update(hSubt, &stUpdateParam);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }
    HAL_DEBUG_EXIT();
    return SUCCESS;
}


/**
\brief Subtitle get running status.CNcomment:Subtitle 获取当前运行状态 。CNend
\attention \n
none.CNcomment: 无。CNend
\param[out] penStatus subt status.CNcomment:Subtitle 字幕运行状态 。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
::CAPTION_STATE_E

\par example
\code
CAPTION_STATE_E enStatus;
enStatus = CAPTION_BUTT;
if (SUCCESS != subt_get_status(pstDev, &enStatus))
{
return FAILUE;
}

\endcode
*/
static S32 subt_get_status(CAPTION_DEVICE_S* pstDev, CAPTION_STATE_E* penStatus)
{
    CAPTION_CHK_SUBT_INIT();
    CAPTION_CHK_PTR(penStatus);

    *penStatus = s_stCaptionModule.stSubtInfo.enStatus;

    return SUCCESS;
}

/****************teletext相关函数************************************/
/**
\brief Teletext start.CNcomment:Teletext 字幕启动。CNend
\attention \n
call flow:start->setWindow->switch->inject->show->hide->stop.
调用流程:start->setWindow->switch->inject->show->hide->stop 。CNend
\param[in] stTTXParam start param.CNcomment:启动参数。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
::CAPTION_TTX_PARAM_S

\par example
\code
CAPTION_TTX_PARAM_S stTTXParam;
stTTXParam.enDataSource = CAPTION_TTX_DATA_SOURCE_PES;
if (SUCCESS != ttx_start(pstDev, stTTXParam))
{
return FAILUE;
}

\endcode
*/
static S32 ttx_start(CAPTION_DEVICE_S* pstDev, CAPTION_TTX_PARAM_S* pstTTXParam)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_TTX_INIT();
    CAPTION_CHK_PTR(pstTTXParam);
    CAPTION_CHK_PTR(pstTTXParam->pfnGetPts);
    CAPTION_CHK_PARA(CAPTION_TTX_DATA_SOURCE_BUTT <= pstTTXParam->enDataSource);

    if (INVALID_CAPTION_HANDLE != s_stCaptionModule.stTtxInfo.hTTX)
    {
        s32Ret = caption_ttx_stop();

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    s32Ret = caption_ttx_start(pstTTXParam);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Teletext switch.CNcomment:Teletext 字幕切换 。CNend
\attention \n
stTTXContentParam.u32ISO639LanCode = pu8ISO639[2] + (pu8ISO639[1] << 8) + (pu8ISO639[0] << 16).
stTTXContentParam.u32ISO639LanCode 与ISO 639的映射关系:u32ISO639LanCode = pu8ISO639[2] + (pu8ISO639[1] << 8) + (pu8ISO639[0] << 16) 。CNend
\param[in] stTTXContentParam teletext content to dispaly.CNcomment:Teletext字幕显示内容。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
::CAPTION_TTX_CONTENT_S

\par example
\code
CAPTION_TTX_CONTENT_S stTTXContentParam;
memset(&stTTXContentParam, 0x0, sizeof(CAPTION_TTX_CONTENT_S));
stTTXContentParam.enType = CAPTION_TTX_DATA_TTXSUBT;
stTTXContentParam.u32ISO639LanCode = 0x656E67; //eng
stTTXContentParam.stInitPagInfo.u8MagazineNum = 0x0;
stTTXContentParam.stInitPagInfo.u8PageNum = 0x89;
stTTXContentParam.stInitPagInfo.u16PageSubCode = 0x0;
if (SUCCESS != ttx_switch(pstDev, stSubtItem))
{
return FAILUE;
}

\endcode
*/
static S32 ttx_switch(CAPTION_DEVICE_S* pstDev, CAPTION_TTX_CONTENT_S* pstTTXContentParam)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_TTX_INIT();
    CAPTION_CHK_PTR(pstTTXContentParam);

    s32Ret = caption_ttx_switch(pstTTXContentParam);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief reset teletext buffer.CNcomment:重置 Teletext buffer 。CNend
\attention \n
重置teletext buffer,当切台或者检测到teletext的数据来源有变化时，应重置teletext buffer以防止新旧teletext数据混合显示
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
*/
S32 ttx_resetBuffer(struct _CAPTION_DEVICE_S* pstDev)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_TTX_INIT();

    s32Ret = caption_ttx_reset();
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}


/**
\brief Teletext stop.CNcomment:Teletext 字幕停止 。CNend
\attention \n
clear all display, stop all ttx work no matter ttx show or hide.
清空所有的Teletext 字幕显示及工作, 不管是在Show 还是Hide 状态。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
*/
S32 ttx_stop(CAPTION_DEVICE_S* pstDev)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_TTX_INIT();

    s32Ret = caption_ttx_stop();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Teletext show.CNcomment:Teletext 字幕显示。CNend
\attention \n
none.CNcomment: 无。CNend
\param[in] enOutputType output type.CNcomment:Teletext 字幕输出类型。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
::CAPTION_TTX_OUTPUT_TYPE_E

\par example
\code
CAPTION_TTX_OUTPUT_TYPE_E enOutputType;
enOutputType = CAPTION_TTX_OUTPUT_OSD;
if (SUCCESS != ttx_show(pstDev, enOutputType))
{
return FAILUE;
}

\endcode
*/
static S32 ttx_show(CAPTION_DEVICE_S* pstDev, CAPTION_TTX_OUTPUT_TYPE_E enOutputType)
{
    S32 s32Ret = SUCCESS;
    HANDLE hTTX = INVALID_CAPTION_HANDLE;
    HI_UNF_TTX_OUTPUT_E enOutput = HI_UNF_TTX_BUTT;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_TTX_INIT();
    CAPTION_CHK_PARA(CAPTION_TTX_OUTPUT_BUTT == enOutputType);

    if ((CAPTION_BUTT == s_stCaptionModule.stTtxInfo.enStatus) ||
        (CAPTION_STOPPED == s_stCaptionModule.stTtxInfo.enStatus))
    {
        HAL_ERROR("status error!! ttx status = 0x%08x", s_stCaptionModule.stTtxInfo.enStatus);
        return FAILURE;
    }

    hTTX = s_stCaptionModule.stTtxInfo.hTTX;

    caption_ttx_map_outtype_tounf(enOutputType, &enOutput);

    s32Ret = HI_UNF_TTX_Output(hTTX, enOutput, HI_TRUE);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x),hTTX(0x%08x), enOutput(0x%08x)", __func__, __LINE__, s32Ret, hTTX, enOutput);
        return FAILURE;
    }

    s_stCaptionModule.stTtxInfo.enStatus = CAPTION_SHOW;
    s_stCaptionModule.stTtxInfo.enOutputType = enOutputType;

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Teletext hide.CNcomment:Teletext 字幕隐藏。CNend
\attention \n
none.CNcomment: 无。CNend
\param[in] enOutputType output type.CNcomment:Teletext 字幕输出类型。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
::CAPTION_TTX_OUTPUT_TYPE_E

\par example
\code
CAPTION_TTX_OUTPUT_TYPE_E enOutputType;
enOutputType = CAPTION_TTX_OUTPUT_OSD;
if (SUCCESS != ttx_hide(pstDev, enOutputType))
{
return FAILUE;
}

\endcode
*/
S32 ttx_hide(CAPTION_DEVICE_S* pstDev, CAPTION_TTX_OUTPUT_TYPE_E enOutputType)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_TTX_INIT();
    CAPTION_CHK_PARA(enOutputType >= CAPTION_TTX_OUTPUT_BUTT);

    s32Ret = caption_ttx_hide(enOutputType);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief  Handle user's operation.  CNcomment:TTX 用户操作处理函数。CNend
\attention \n
none.CNcomment: 无。CNend
\param[in] enCMD Type of command.   CNcomment:命令类型。CNend
\param[in] pvCMDParam Parameter of  command(The parameter must be  conveted to appropriate  type at every
specifical application), when the command is UPDATE or EXIT, the command can be NULL.
CNcomment:命令参数(具体应用需要强制转换)，UPDATE/EXIT时可为NULL。CNend
\param[out] pvCMDParam    Parameter of command , when the command is  GETPAGEADDR, it points to the address of specifical  pages.
CNcomment:命令参数，GETPAGEADDR时输出页地址。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
none. CNcomment: 无。CNend
*/
static S32 ttx_execCmd(CAPTION_DEVICE_S* pstDev, CAPTION_TTX_CMD_E enCMD, VOID* pvCMDParam)
{
    S32 s32Ret = FAILURE;
    HANDLE hTTX = INVALID_CAPTION_HANDLE;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_TTX_INIT();
    CAPTION_CHK_PTR(pvCMDParam);
    CAPTION_CHK_PARA(enCMD >= CAPTION_TTX_CMD_BUTT);

    if (CAPTION_SHOW != s_stCaptionModule.stTtxInfo.enStatus)
    {
        HAL_ERROR("status error!! ttx status = 0x%08x", s_stCaptionModule.stTtxInfo.enStatus);
        return FAILURE;
    }

    hTTX = s_stCaptionModule.stTtxInfo.hTTX;

    if (INVALID_CAPTION_HANDLE == hTTX)
    {
        HAL_ERROR("%s,%d error!! ", __func__, __LINE__);
        return FAILURE;
    }

    switch (enCMD)
    {
        case CAPTION_TTX_CMD_KEY:
        {
            s32Ret = caption_ttx_execmd_key(hTTX, pvCMDParam);
            break;
        }

        case CAPTION_TTX_CMD_OPENPAGE:
        {
            s32Ret = caption_ttx_execmd_open_page(hTTX, pvCMDParam);
            break;
        }

        case CAPTION_TTX_CMD_GETPAGEADDR:
        {
            s32Ret = caption_ttx_execmd_get_pageaddr(hTTX, pvCMDParam);
            break;
        }

        case CAPTION_TTX_CMD_CHECKPAGE:
        {
            s32Ret = caption_ttx_execmd_check_page(hTTX, pvCMDParam);
            break;
        }

        case CAPTION_TTX_CMD_SETREQUEST:
        {
            s32Ret = caption_ttx_execmd_set_request(hTTX, pvCMDParam);
            break;
        }

        case CAPTION_TTX_CMD_CLEARREQUEST:
        {
            s32Ret = caption_ttx_execmd_clear_request(hTTX, pvCMDParam);
            break;
        }

        default:
            break;
    }

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Teletext get running status.CNcomment:Teletext 获取当前运行状态 。CNend
\attention \n
none.CNcomment: 无。CNend
\param[out] penStatus subt status.CNcomment:Teletext 字幕运行状态 。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
::CAPTION_STATE_E

\par example
\code
CAPTION_STATE_E enStatus;
enStatus = CAPTION_BUTT;
if (SUCCESS != ttx_get_status(pstDev, &enStatus))
{
return FAILUE;
}

\endcode
*/
static S32 ttx_get_status(CAPTION_DEVICE_S* pstDev, CAPTION_STATE_E* penStatus)
{
    CAPTION_CHK_TTX_INIT();
    CAPTION_CHK_PTR(penStatus);

    *penStatus = s_stCaptionModule.stTtxInfo.enStatus;

    return SUCCESS;
}

/****************CC相关函数************************************/

/**
\brief Closed Caption create.CNcomment:Closed Caption 字幕创建 。CNend
\attention \n
call flow:creat->setWindow->start->inject->getAttr(setAttr)->stop.
调用流程:creat->setWindow->start->inject->getAttr(setAttr)->stop。CNend
\param[in] stCCParam create param.CNcomment:创建参数 。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
::CAPTION_CC_PARAM_S

\par example
\code
CAPTION_CC_PARAM_S stCCParam;
memset(&stCCParam, 0x0, sizeof(CAPTION_CC_PARAM_S));
stCCParam.enCCDataType = CAPTION_CC_DATA_608;
if (SUCCESS != cc_creat(pstDev, stCCParam))
{
return FAILUE;
}

\endcode
*/
static S32 cc_creat(CAPTION_DEVICE_S* pstDev, CAPTION_CC_PARAM_S* pstCCParam)
{
    S32 s32Ret = FAILURE;
    HI_UNF_CC_PARAM_S stUnfCCParam;
    HANDLE hCC = INVALID_CAPTION_HANDLE;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_CC_INIT();
    CAPTION_CHK_PTR(pstCCParam);
    CAPTION_CHK_PTR(pstCCParam->pfnGetPts);
    CAPTION_CHK_PARA(CAPTION_CC_DATA_BUTT <= pstCCParam->enCCDataType);

    if (INVALID_CAPTION_HANDLE != s_stCaptionModule.stCCInfo.hCC)
    {
        s32Ret = caption_cc_destroy();
        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    memset(&stUnfCCParam, 0, sizeof(HI_UNF_CC_PARAM_S));

    s_stCaptionModule.stCCInfo.pfnGetPts = pstCCParam->pfnGetPts;

    s32Ret = caption_cc_map_type_tounf(pstCCParam->enCCDataType, &(stUnfCCParam.stCCAttr.enCCDataType));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x), enCCDataType(0x%08x)", __func__, __LINE__, s32Ret, pstCCParam->enCCDataType);
        return FAILURE;
    }

    s32Ret = HI_UNF_CC_GetDefaultAttr(&(stUnfCCParam.stCCAttr));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    stUnfCCParam.pfnCCGetPts = (HI_UNF_CC_GETPTS_CB_FN)caption_cc_get_pts;
    stUnfCCParam.pfnCCDisplay = (HI_UNF_CC_DISPLAY_CB_FN)caption_cc_draw;
    stUnfCCParam.pfnCCGetTextSize = (HI_UNF_CC_GETTEXTSIZE_CB_FN)caption_cc_get_textsize;
    stUnfCCParam.pfnBlit = (HI_UNF_CC_BLIT_CB_FN)caption_cc_blit;
    stUnfCCParam.pfnVBIOutput = (HI_UNF_CC_VBI_CB_FN)caption_cc_vbi;
    stUnfCCParam.pfnXDSOutput = (HI_UNF_CC_XDS_CB_FN)caption_cc_xds_decode;
    stUnfCCParam.pUserData = HI_NULL;

    s32Ret = HI_UNF_CC_Create(&stUnfCCParam, &hCC);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s_stCaptionModule.stCCInfo.enCCType = pstCCParam->enCCDataType;
    s_stCaptionModule.stCCInfo.hCC = hCC;
    s_stCaptionModule.stCCInfo.enStatus = CAPTION_RUNNING;

    if (INVALID_CAPTION_HANDLE == s_stCaptionModule.stCCInfo.hOut)
    {
        s32Ret = caption_cc_output_init(&(s_stCaptionModule.stCCInfo.hOut));

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
            return FAILURE;
        }
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Closed Caption destroy.CNcomment:Closed Caption 字幕销毁 。CNend
\attention \n
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
*/
S32 cc_destroy(struct _CAPTION_DEVICE_S* pstDev)
{
    S32 s32Ret = FAILURE;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_CC_INIT();

    s32Ret = caption_cc_destroy();
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Closed Caption start.CNcomment:Closed Caption 字幕启动 。CNend
start cc data recv and display.
启动cc 数据的接收和显示。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
none. CNcomment: 无。CNend
*/
static S32 cc_start(CAPTION_DEVICE_S* pstDev)
{
    S32 s32Ret = FAILURE;
    HANDLE hCC = INVALID_CAPTION_HANDLE;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_CC_INIT();

    if (CAPTION_BUTT == s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    hCC = s_stCaptionModule.stCCInfo.hCC;

    if (INVALID_CAPTION_HANDLE == hCC)
    {
        HAL_ERROR("%s,%d error!! cc is not create.", __func__, __LINE__);
        return FAILURE;
    }

    s32Ret = HI_UNF_CC_Start(hCC);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s_stCaptionModule.stCCInfo.enStatus = CAPTION_SHOW;

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Closed Caption stop.CNcomment:Closed Caption 字幕停止 。CNend
\attention \n
stop cc data recv and display.
停止cc 数据的接收和显示。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
none. CNcomment: 无。CNend
*/
S32 cc_stop(CAPTION_DEVICE_S* pstDev)
{
    S32 s32Ret = FAILURE;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_CC_INIT();

    s32Ret = caption_cc_stop();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Closed Caption get attribution.CNcomment:Closed Caption 获取字幕属性信息 。CNend
\attention \n
none. CNcomment: 无。CNend
\param[out]  pstCCAttr  cc attribution structure. CNcomment: CC 属性信息结构体。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
::CAPTION_CC_ATTR_S

\par example
\code
CAPTION_CC_ATTR_S stCCAttr;
memset(&stCCAttr, 0x0, sizeof(CAPTION_CC_PARAM_S));
stCCAttr.enCCDataType = CAPTION_CC_DATA_608;
if (SUCCESS != cc_getAttr(pstDev, &stCCParam))
{
return FAILUE;
}

\endcode
*/
static S32 cc_getAttr(CAPTION_DEVICE_S* pstDev, CAPTION_CC_ATTR_S* pstCCAttr)
{
    S32 s32Ret = FAILURE;
    HANDLE hCC = INVALID_CAPTION_HANDLE;
    HI_UNF_CC_ATTR_S sUnftCCAttr;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_CC_INIT();
    CAPTION_CHK_PTR(pstCCAttr);

    if (CAPTION_SHOW != s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    hCC = s_stCaptionModule.stCCInfo.hCC;

    if (INVALID_CAPTION_HANDLE == hCC)
    {
        HAL_ERROR("cc is not create.");
        return FAILURE;
    }

    s32Ret = HI_UNF_CC_GetAttr(hCC, &sUnftCCAttr);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    s32Ret = caption_cc_map_type_tohal(sUnftCCAttr.enCCDataType, &(pstCCAttr->enCCDataType));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCCDataType(0x%08x)", __func__, __LINE__, pstCCAttr->enCCDataType);
        return FAILURE;
    }

    switch (pstCCAttr->enCCDataType)
    {
        case CAPTION_CC_DATA_608:
        {
            s32Ret = caption_cc_map_608attr_tohal(sUnftCCAttr.unCCConfig.stCC608ConfigParam, &(pstCCAttr->unCCConfig.stCC608ConfigParam));
            break;
        }

        case CAPTION_CC_DATA_708:
        {
            s32Ret = caption_cc_map_708attr_tohal(sUnftCCAttr.unCCConfig.stCC708ConfigParam, &(pstCCAttr->unCCConfig.stCC708ConfigParam));
            break;
        }

        case CAPTION_CC_DATA_ARIB:
        {
            s32Ret = caption_cc_map_aribattr_tohal(sUnftCCAttr.unCCConfig.stCCARIBConfigParam, &(pstCCAttr->unCCConfig.stAribCCConfigParam));
            break;
        }

        default:
        {
            s32Ret = FAILURE;
            break;
        }
    }

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCCDataType(0x%08x)", __func__, __LINE__, pstCCAttr->enCCDataType);
        return ERROR_INVALID_PARAM;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief Closed Caption set display attribution. CNcomment: Closed Caption 设置字幕显示属性信息。CNend
\attention \n
none. CNcomment: 无。CNend
\param[in]  stCCAttr  cc attribution structure. CNcomment:属性信息结构体。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
::CAPTION_CC_ATTR_S

\par example
\code
CAPTION_CC_ATTR_S stCCAttr;
memset(&stCCAttr, 0x0, sizeof(CAPTION_CC_PARAM_S));
stCCAttr.enCCDataType = CAPTION_CC_DATA_608;

if (SUCCESS == cc_getAttr(pstDev, &stCCParam))
{
stCCAttr.unCCConfig.stCC608ConfigParam.enCC608DataType = CAPTION_CC_608_DATATYPE_CC1;
if (SUCCESS != cc_setAttr(pstDev, stCCParam))
{
return FAILUE;
}
}

\endcode
*/
static S32 cc_setAttr(CAPTION_DEVICE_S* pstDev, CAPTION_CC_ATTR_S* pstCCAttr)
{
    S32 s32Ret = FAILURE;
    HANDLE hCC = INVALID_CAPTION_HANDLE;
    HI_UNF_CC_ATTR_S sUnftCCAttr;

    HAL_DEBUG_ENTER();

    CAPTION_CHK_CC_INIT();
    CAPTION_CHK_PTR(pstCCAttr);
    CAPTION_CHK_PARA(pstCCAttr->enCCDataType >= CAPTION_CC_DATA_BUTT);

    if (CAPTION_SHOW != s_stCaptionModule.stCCInfo.enStatus)
    {
        HAL_ERROR("status error!! cc status = 0x%08x", s_stCaptionModule.stCCInfo.enStatus);
        return FAILURE;
    }

    hCC = s_stCaptionModule.stCCInfo.hCC;

    if (INVALID_CAPTION_HANDLE == hCC)
    {
        HAL_ERROR("%s,%d error!! cc is not create.", __func__, __LINE__);
        return FAILURE;
    }

    s32Ret = caption_cc_map_type_tounf(pstCCAttr->enCCDataType, &(sUnftCCAttr.enCCDataType));

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCCDataType(0x%08x)", __func__, __LINE__, pstCCAttr->enCCDataType);
        return FAILURE;
    }

    switch (pstCCAttr->enCCDataType)
    {
        case CAPTION_CC_DATA_608:
        {
            s32Ret = caption_cc_map_608attr_tounf(pstCCAttr->unCCConfig.stCC608ConfigParam, &(sUnftCCAttr.unCCConfig.stCC608ConfigParam));
            break;
        }

        case CAPTION_CC_DATA_708:
        {
            s32Ret = caption_cc_map_708attr_tounf(pstCCAttr->unCCConfig.stCC708ConfigParam, &(sUnftCCAttr.unCCConfig.stCC708ConfigParam));
            break;
        }

        case CAPTION_CC_DATA_ARIB:
        {
            s32Ret = caption_cc_map_aribattr_tounf(pstCCAttr->unCCConfig.stAribCCConfigParam, &(sUnftCCAttr.unCCConfig.stCCARIBConfigParam));
            break;
        }

        default:
        {
            s32Ret = FAILURE;
            break;
        }

    }

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! enCCDataType(0x%08x)", __func__, __LINE__, pstCCAttr->enCCDataType);
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_UNF_CC_SetAttr(hCC, &sUnftCCAttr);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s,%d error!! s32Ret(0x%08x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
\brief cc get running status.CNcomment:cc 获取当前运行状态 。CNend
\attention \n
none.CNcomment: 无。CNend
\param[out] penStatus cc status.CNcomment:cc 字幕运行状态 。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
\retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
\retval ::FAILURE  other error.CNcomment:其它错误。CNend
\see \n
::CAPTION_STATE_E

\par example
\code
CAPTION_STATE_E enStatus;
enStatus = CAPTION_BUTT;
if (SUCCESS != cc_get_status(pstDev, &enStatus))
{
return FAILUE;
}

\endcode
*/
static S32 cc_get_status(CAPTION_DEVICE_S* pstDev, CAPTION_STATE_E* penStatus)
{
    CAPTION_CHK_CC_INIT();
    CAPTION_CHK_PTR(penStatus);

    *penStatus = s_stCaptionModule.stCCInfo.enStatus;

    return SUCCESS;
}

#ifdef TVOS_PLATFORM
static int caption_device_close(struct hw_device_t *pstDev)
{
    struct CAPTION_DEVICE_S* pCtx = (struct CAPTION_DEVICE_S*)pstDev;

    if (pCtx)
    {
        free(pCtx);
        pCtx = NULL;
    }
    return 0;
}

static int caption_device_open(const struct hw_module_t* module, const char* name,
                          struct hw_device_t** device)
{
    HAL_DEBUG_ENTER();

    if (strcmp(name, CAPTION_HARDWARE_CAPTION0) != 0)
    {
        return -EINVAL;
    }

    if (NULL == device)
    {
        return -EINVAL;
    }

    CAPTION_DEVICE_S *pstCaptionDev = (CAPTION_DEVICE_S*)malloc(sizeof(CAPTION_DEVICE_S));
    if (NULL == pstCaptionDev)
    {
        HAL_ERROR("%s,%d malloc memory failed!\n", __func__, __LINE__);
        return -ENOMEM;
    }

    /* initialize our state here */
    memset(pstCaptionDev, 0, sizeof(*pstCaptionDev));

    /* initialize the procs */
    pstCaptionDev->stCommon.tag = HARDWARE_DEVICE_TAG;
    pstCaptionDev->stCommon.version = CAPTION_DEVICE_API_VERSION_1_0;
    pstCaptionDev->stCommon.module = (hw_module_t*)module;
    pstCaptionDev->stCommon.close = caption_device_close;

    /* register the callbacks */
    pstCaptionDev->caption_init = caption_init;
    pstCaptionDev->caption_term = caption_term;
    pstCaptionDev->caption_common_injectData = caption_common_injectData;
    pstCaptionDev->caption_set_window = caption_set_window;


    /*register subtitle callbacks*/
    pstCaptionDev->subt_start = subt_start;
    pstCaptionDev->subt_switch = subt_switch;
    pstCaptionDev->subt_show = subt_show;
    pstCaptionDev->subt_hide = subt_hide;
    pstCaptionDev->subt_stop = subt_stop;
    pstCaptionDev->subt_get_status = subt_get_status;


    /*register teletext callbacks*/
    pstCaptionDev->ttx_start = ttx_start;
    pstCaptionDev->ttx_switch = ttx_switch;
    pstCaptionDev->ttx_stop = ttx_stop;
    pstCaptionDev->ttx_show = ttx_show;
    pstCaptionDev->ttx_hide = ttx_hide;
    pstCaptionDev->ttx_execCmd = ttx_execCmd;
    pstCaptionDev->ttx_get_status = ttx_get_status;

    /*register cc callbacks*/
    pstCaptionDev->cc_creat = cc_creat;
    pstCaptionDev->cc_start = cc_start;
    pstCaptionDev->cc_stop = cc_stop;
    pstCaptionDev->cc_getAttr = cc_getAttr;
    pstCaptionDev->cc_setAttr = cc_setAttr;
    pstCaptionDev->cc_get_status = cc_get_status;

    *device = &(pstCaptionDev->stCommon);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}


static struct hw_module_methods_t caption_module_methods = {
    open: caption_device_open,
};

CAPTION_MODULE_S HAL_MODULE_INFO_SYM = {
    stCommon: {
        tag:           HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
        id:            CAPTION_HARDWARE_MODULE_ID,
        name:          "Sample hwcomposer module",
        author:        "The Android Open Source Project",
        methods:       &caption_module_methods,
        dso:           NULL,
        reserved:      {0},
    }
};
#endif
static CAPTION_DEVICE_S s_stDevice_capion =
{
    /* register the callbacks */
    .caption_init = caption_init,
    .caption_term = caption_term,
    .caption_common_injectData = caption_common_injectData,
    .caption_set_window = caption_set_window,

    /*register subtitle callbacks*/
    .subt_start = subt_start,
    .subt_switch = subt_switch,
    .subt_show = subt_show,
    .subt_hide = subt_hide,
    .subt_stop = subt_stop,
    .subt_get_status = subt_get_status,

    /*register teletext callbacks*/
    .ttx_start = ttx_start,
    .ttx_switch = ttx_switch,
    .ttx_resetBuffer = ttx_resetBuffer,
    .ttx_stop = ttx_stop,
    .ttx_show = ttx_show,
    .ttx_hide = ttx_hide,
    .ttx_execCmd = ttx_execCmd,
    .ttx_get_status = ttx_get_status,

    /*register cc callbacks*/
    .cc_creat = cc_creat,
    .cc_destroy = cc_destroy,
    .cc_start = cc_start,
    .cc_stop = cc_stop,
    .cc_getAttr = cc_getAttr,
    .cc_setAttr = cc_setAttr,
    .cc_get_status = cc_get_status,
};

CAPTION_DEVICE_S* getCaptionDevice()
{
    return &s_stDevice_capion;
}

/** @}*/  /** <!-- ==== API Declaration End ====*/
