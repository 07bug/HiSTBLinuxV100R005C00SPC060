#include <errno.h>
#include <pthread.h>
#include "tvos_hal_common.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_vout.h"
#include "hi_unf_vo.h"
#include "hi_unf_disp.h"
#include "hi_unf_hdmi.h"
#include "hi_unf_pdm.h"
#include "hi_unf_mce.h"
#include "hi_unf_pq.h"
#include "hi_drv_win.h"
#include "hi_mpi_win.h"
#include "hi_mpi_vdec.h"


/*lint -e655*/
/******************************* API declaration *****************************/
extern S32 av_get_sdk_avplay_hdl(const HANDLE hAvHandle, HANDLE* phSdkAvPlayHdl);

/** \addtogroup      HAL_AV */
/** @{ */  /** <!-- [HAL_AV] */
#define VOUT_MODE_ID            (0x1f03)


#define DAC_YPBPR_Y             (0)
#define DAC_YPBPR_PR            (1)
#define DAC_YPBPR_PB            (2)
#define DAC_CVBS                (0)
#define MAX_USER_ASPECT_HEIGHT     (2160)
#define MAX_USER_ASPECT_WIDTH      (3840)
#define USER_ASPECT_HEIGHT_RATIO_3  (3)
#define USER_ASPECT_HEIGHT_RATIO_9  (9)
#define USER_ASPECT_WIDTH_RATIO_4   (4)
#define USER_ASPECT_WIDTH_RATIO_16  (16)
#define UNSIGNED_INT_MAX_VALUE     (0xFFFFFFFF)

#define VIDEO_HEIGHT_1080 1080
#define VIDEO_WIDTH_1920 1920

/* init flag */
static BOOL s_bVoutInited = FALSE;

/* used support multi handle in one proccess */
static S32  s_s32VoutInstCount = 0;
static pthread_mutex_t s_vout_mutex = PTHREAD_MUTEX_INITIALIZER;
static HI_HANDLE s_hVBI = 0xFFFFFFFF;
#define VOUT_LOCK()    pthread_mutex_lock(&s_vout_mutex)
#define VOUT_UNLOCK()  pthread_mutex_unlock(&s_vout_mutex)

static U32 s_u32QueueWidth = 0;
static U32 s_u32QueueHeight = 0;

// for 4k frc queue&dequeue
#define HI_4K_BYPASS
#define HI_4K_BYPASS_FRC
static pthread_mutex_t s_vout_frame_mutex = PTHREAD_MUTEX_INITIALIZER;
#define VOUT_FRAME_LOCK()    pthread_mutex_lock(&s_vout_frame_mutex)
#define VOUT_FRAME_UNLOCK()  pthread_mutex_unlock(&s_vout_frame_mutex)

#define VOUT_HEADER_VERSION          1
#define VOUT_DEVICE_API_VERSION_1_0  HARDWARE_DEVICE_API_VERSION_2(1, 0, VOUT_HEADER_VERSION)

#define IS_REGION_EQ(r1, r2)  ((r1.u32Left == r2.u32Left)   \
                               && (r1.u32Right == r2.u32Right)  \
                               && (r1.u32Top == r2.u32Top)     \
                               && (r1.u32Bottom == r2.u32Bottom))

#define VOUT_INSTANCE_MAX          (1)
#define INVALID_HANDLE             (0)


//#define DEBUG_V
#ifdef  DEBUG_V
#define LOG_NDEBUG 0
#define LOG_TAG "hal_vout"
#include <cutils/log.h>
#define trace()    HAL_DEBUG("%s called", __func__)
#define dbg HAL_DEBUG
#else
#define trace()
#define dbg(fmt, ...)
#endif

#if defined(CHIP_TYPE_hi3798mv310)
   #define HOMOLOGOUS_WIN_UNSPPORT
#endif

typedef struct hal_VOUT_DEV_INFO_S
{
    HANDLE                  hVoutHandle;
    VOUT_OPEN_PARAMS_S*     pstVoutOpenParams;
}VOUT_DEV_INFO_S;

static VOUT_DEV_INFO_S g_VoutInfo[VOUT_INSTANCE_MAX];

/* Begin:  CNcomment:自定义函数 */
//////////////////////////////////////HDMI  BEGIN//////////////////////////////////////////
/*!
*@brief HDMI
*/
typedef struct hiHDMI_ARGS_S
{
    HI_UNF_HDMI_ID_E  enHdmi;
} HDMI_ARGS_S;

static HDMI_ARGS_S g_stHdmiArgs;
/* CNcomment:优先判断HDMI  */
static HI_UNF_HDMI_DEFAULT_ACTION_E g_enDefaultMode = HI_UNF_HDMI_DEFAULT_ACTION_HDMI;
/* CNcomment:接口热插拔函数 */
static HI_UNF_HDMI_CALLBACK_FUNC_S g_stCallbackFunc;

struct _HI_DISPLAY_FORMAT
{
    HI_UNF_ENC_FMT_E      enUnfFmt;
    VOUT_FORMAT_E         enDispFmt;
    VOUT_VID_FRAME_RATE_E enFrameRate;
} g_stHiDispFormat[] =
{
    {HI_UNF_ENC_FMT_1080P_60,               VOUT_FORMAT_HD_1080P,      VOUT_VID_FRAME_RATE_60},
    {HI_UNF_ENC_FMT_1080P_50,               VOUT_FORMAT_HD_1080P,      VOUT_VID_FRAME_RATE_50},
    {HI_UNF_ENC_FMT_1080P_30,               VOUT_FORMAT_HD_1080P,      VOUT_VID_FRAME_RATE_30},
    {HI_UNF_ENC_FMT_1080P_25,               VOUT_FORMAT_HD_1080P,      VOUT_VID_FRAME_RATE_25},
    {HI_UNF_ENC_FMT_1080P_24,               VOUT_FORMAT_HD_1080P,      VOUT_VID_FRAME_RATE_24},
    {HI_UNF_ENC_FMT_1080i_60,               VOUT_FORMAT_HD_1080I,      VOUT_VID_FRAME_RATE_60},
    {HI_UNF_ENC_FMT_1080i_50,               VOUT_FORMAT_HD_1080I,      VOUT_VID_FRAME_RATE_50},
    {HI_UNF_ENC_FMT_720P_60,                VOUT_FORMAT_HD_720P,       VOUT_VID_FRAME_RATE_60},
    {HI_UNF_ENC_FMT_720P_50,                VOUT_FORMAT_HD_720P,       VOUT_VID_FRAME_RATE_50},
    {HI_UNF_ENC_FMT_576P_50,                VOUT_FORMAT_576P,          VOUT_VID_FRAME_RATE_50},
    {HI_UNF_ENC_FMT_480P_60,                VOUT_FORMAT_480P,          VOUT_VID_FRAME_RATE_60},
    {HI_UNF_ENC_FMT_1080P_24_FRAME_PACKING, VOUT_FORMAT_HD_1080P,      VOUT_VID_FRAME_RATE_24},
    {HI_UNF_ENC_FMT_720P_60_FRAME_PACKING,  VOUT_FORMAT_HD_720P,       VOUT_VID_FRAME_RATE_60},
    {HI_UNF_ENC_FMT_720P_50_FRAME_PACKING,  VOUT_FORMAT_HD_720P,       VOUT_VID_FRAME_RATE_50},
    {HI_UNF_ENC_FMT_3840X2160_24,           VOUT_FORMAT_HD_3840X2160,  VOUT_VID_FRAME_RATE_24},
    {HI_UNF_ENC_FMT_3840X2160_25,           VOUT_FORMAT_HD_3840X2160,  VOUT_VID_FRAME_RATE_25},
    {HI_UNF_ENC_FMT_3840X2160_30,           VOUT_FORMAT_HD_3840X2160,  VOUT_VID_FRAME_RATE_30},
    {HI_UNF_ENC_FMT_3840X2160_50,           VOUT_FORMAT_HD_3840X2160,  VOUT_VID_FRAME_RATE_50},
    {HI_UNF_ENC_FMT_3840X2160_60,           VOUT_FORMAT_HD_3840X2160,  VOUT_VID_FRAME_RATE_60},
    {HI_UNF_ENC_FMT_4096X2160_24,           VOUT_FORMAT_HD_4096X2160,  VOUT_VID_FRAME_RATE_24},
    {HI_UNF_ENC_FMT_4096X2160_25,           VOUT_FORMAT_HD_4096X2160,  VOUT_VID_FRAME_RATE_25},
    {HI_UNF_ENC_FMT_4096X2160_30,           VOUT_FORMAT_HD_4096X2160,  VOUT_VID_FRAME_RATE_30},
    {HI_UNF_ENC_FMT_4096X2160_50,           VOUT_FORMAT_HD_4096X2160,  VOUT_VID_FRAME_RATE_50},
    {HI_UNF_ENC_FMT_4096X2160_60,           VOUT_FORMAT_HD_4096X2160,  VOUT_VID_FRAME_RATE_60},
    {HI_UNF_ENC_FMT_PAL,                    VOUT_FORMAT_PAL,           VOUT_VID_FRAME_RATE_AUTO},
    {HI_UNF_ENC_FMT_NTSC_PAL_M,             VOUT_FORMAT_PALM,          VOUT_VID_FRAME_RATE_AUTO},
    {HI_UNF_ENC_FMT_PAL_N,                  VOUT_FORMAT_PALN,          VOUT_VID_FRAME_RATE_AUTO},
    {HI_UNF_ENC_FMT_PAL_Nc,                 VOUT_FORMAT_PALN,          VOUT_VID_FRAME_RATE_AUTO},
    {HI_UNF_ENC_FMT_NTSC,                   VOUT_FORMAT_NTSC,          VOUT_VID_FRAME_RATE_AUTO},
    {HI_UNF_ENC_FMT_NTSC_J,                 VOUT_FORMAT_NTSC,          VOUT_VID_FRAME_RATE_AUTO},
    {HI_UNF_ENC_FMT_SECAM_SIN,              VOUT_FORMAT_SECAM,         VOUT_VID_FRAME_RATE_AUTO},
    {HI_UNF_ENC_FMT_SECAM_COS,              VOUT_FORMAT_SECAM,         VOUT_VID_FRAME_RATE_AUTO},
};

static inline HI_BOOL hal_to_unf_for_bool(BOOL bHalValue)
{
    return (HI_BOOL)((TRUE == bHalValue) ? HI_TRUE : HI_FALSE);
}

static inline BOOL unf_to_hal_for_bool(HI_BOOL bUnfValue)
{
    return (BOOL)(HI_TRUE == bUnfValue) ? TRUE : FALSE;
}

S32 disable_display_output(VOID)
{
#ifndef HOMOLOGOUS_WIN_UNSPPORT
    S32 s32Ret = FAILURE;
    HI_UNF_DISP_INTF_S     stIntf[2];

    /* stop hdmi0 */
    s32Ret = HI_UNF_HDMI_Stop(HI_UNF_HDMI_ID_0);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_HDMI_Stop() failed!!. Ret=%#x.", s32Ret);
    }

    memset(stIntf, 0, sizeof(stIntf));
    stIntf[0].enIntfType                = HI_UNF_DISP_INTF_TYPE_YPBPR;
    stIntf[0].unIntf.stYPbPr.u8DacY     = DAC_YPBPR_Y;
    stIntf[0].unIntf.stYPbPr.u8DacPb    = DAC_YPBPR_PB;
    stIntf[0].unIntf.stYPbPr.u8DacPr    = DAC_YPBPR_PR;
    stIntf[1].enIntfType                = HI_UNF_DISP_INTF_TYPE_HDMI;
    stIntf[1].unIntf.enHdmi             = HI_UNF_HDMI_ID_0;
    s32Ret = HI_UNF_DISP_DetachIntf(HI_UNF_DISPLAY1, &stIntf[0], 2);

    if (SUCCESS != s32Ret)
    {
        s32Ret = ERROR_DISPLAY_ATTACH_INTF_FAILED;
        HAL_ERROR("vout_open display1 attachintf failed!!. Ret=%#x.", s32Ret);
    }

    stIntf[0].enIntfType            = HI_UNF_DISP_INTF_TYPE_CVBS;
    stIntf[0].unIntf.stCVBS.u8Dac   = DAC_CVBS;
    s32Ret = HI_UNF_DISP_DetachIntf(HI_UNF_DISPLAY0, &stIntf[0], 1);

    if (SUCCESS != s32Ret)
    {
        s32Ret = ERROR_DISPLAY_ATTACH_INTF_FAILED;
        HAL_ERROR("vout_open display0 attachintf failed!!. Ret=%#x.", s32Ret);
    }

    return s32Ret;
#else
    return SUCCESS;
#endif
}

S32 enable_display_output(VOID)
{
#ifndef HOMOLOGOUS_WIN_UNSPPORT
    S32 s32Ret = SUCCESS;
    HI_UNF_DISP_INTF_S     stIntf[2];

    memset(stIntf, 0, sizeof(stIntf));
    stIntf[0].enIntfType                = HI_UNF_DISP_INTF_TYPE_YPBPR;
    stIntf[0].unIntf.stYPbPr.u8DacY     = DAC_YPBPR_Y;
    stIntf[0].unIntf.stYPbPr.u8DacPb    = DAC_YPBPR_PB;
    stIntf[0].unIntf.stYPbPr.u8DacPr    = DAC_YPBPR_PR;

    stIntf[1].enIntfType                = HI_UNF_DISP_INTF_TYPE_HDMI;
    stIntf[1].unIntf.enHdmi             = HI_UNF_HDMI_ID_0;
    s32Ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY1, &stIntf[0], 2);

    if (SUCCESS != s32Ret)
    {
        s32Ret = FAILURE;
        HAL_ERROR("vout_open display1 attachintf failed!!. Ret=%#x.", s32Ret);
        return s32Ret;
    }

    /* start hdmi0 */
    s32Ret = HI_UNF_HDMI_Start(HI_UNF_HDMI_ID_0);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_HDMI_Start() failed!!. Ret=%#x.", s32Ret);
    }

    /* 2. set display0 bind intf for display */
    stIntf[0].enIntfType            = HI_UNF_DISP_INTF_TYPE_CVBS;
    stIntf[0].unIntf.stCVBS.u8Dac   = DAC_CVBS;
    s32Ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY0, &stIntf[0], 1);

    if (SUCCESS != s32Ret)
    {
        s32Ret = ERROR_DISPLAY_ATTACH_INTF_FAILED;
        HAL_ERROR("vout_open display0 attachintf failed!!. Ret=%#x.", s32Ret);
    }

    return s32Ret;
#else
    return SUCCESS;
#endif
}

static VOID HDMI_HotPlug_Proc(VOID* pPrivateData)
{
    HAL_DEBUG_ENTER();
    S32                s32Ret = SUCCESS;
    HDMI_ARGS_S*        pArgs = (HDMI_ARGS_S*)pPrivateData;
    HI_UNF_HDMI_ID_E   hHdmi  = pArgs->enHdmi;
    HI_UNF_HDMI_ATTR_S stHdmiAttr;
    HI_UNF_EDID_BASE_INFO_S stSinkCap;
    HI_UNF_HDMI_STATUS_S    stHdmiStatus;
#ifdef HI_HDCP_SUPPORT
    static U8 u8FirstTimeSetting = TRUE;
#endif

    // TODO: reference android code, should design first.

    HAL_DEBUG("\n --- Get HDMI event: HOTPLUG. --- \n");
    HI_UNF_HDMI_GetStatus(hHdmi, &stHdmiStatus);

    HAL_CHK_RETURN_VOID((FALSE == stHdmiStatus.bConnected), "No Connect\n");

    HI_UNF_HDMI_GetAttr(hHdmi, &stHdmiAttr);
    s32Ret = HI_UNF_HDMI_GetSinkCapability(hHdmi, &stSinkCap);

    if (HI_SUCCESS == s32Ret)
    {
        if (HI_TRUE == stSinkCap.bSupportHdmi)
        {
            stHdmiAttr.bEnableHdmi = HI_TRUE;

            if (TRUE != stSinkCap.stColorSpace.bYCbCr444)
            {
                stHdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
            }
            else
            {
                stHdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_YCBCR444;  /* user can choicen RGB/YUV*/
            }
        }
        else
        {
            stHdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
            //CNcomment:读取到了edid，并且不支持hdmi则进入dvi模式
            //read real edid ok && sink not support hdmi,then we run in dvi mode
            stHdmiAttr.bEnableHdmi = HI_FALSE;
            stHdmiAttr.enDeepColorMode = HI_UNF_HDMI_DEEP_COLOR_OFF;
        }
    }
    else
    {
        //when get capability fail,use default mode
        if (g_enDefaultMode != HI_UNF_HDMI_DEFAULT_ACTION_DVI)
        { stHdmiAttr.bEnableHdmi = HI_TRUE; }
        else
        { stHdmiAttr.bEnableHdmi = HI_FALSE; }
    }

    if (HI_TRUE == stHdmiAttr.bEnableHdmi)
    {
        stHdmiAttr.bEnableAudio = HI_TRUE;
        stHdmiAttr.bEnableVideo = HI_TRUE;
        stHdmiAttr.bEnableAudInfoFrame = HI_TRUE;
        stHdmiAttr.bEnableAviInfoFrame = HI_TRUE;
    }
    else
    {
        stHdmiAttr.bEnableAudio = HI_FALSE;
        stHdmiAttr.bEnableVideo = HI_TRUE;
        stHdmiAttr.bEnableAudInfoFrame = HI_FALSE;
        stHdmiAttr.bEnableAviInfoFrame = HI_FALSE;
        stHdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
    }

#ifdef HI_HDCP_SUPPORT

    if (u8FirstTimeSetting == HI_TRUE)
    {
        U32 u32HDCPFlag    = HI_FALSE;
        u8FirstTimeSetting = HI_FALSE;

        if (u32HDCPFlag == HI_TRUE)
        {
            stHdmiAttr.bHDCPEnable = HI_TRUE;//Enable HDCP
        }
        else
        {
            stHdmiAttr.bHDCPEnable = HI_FALSE;
        }
    }
    else
    {
        //HDCP Enable use default setting!!
    }

#endif
    s32Ret = HI_UNF_HDMI_SetAttr(hHdmi, &stHdmiAttr);
    if(SUCCESS != s32Ret)
    {
        HAL_ERROR("set HDMI attributes failed:%#x\n", s32Ret);
        return;
    }
    /* HI_UNF_HDMI_SetAttr must before HI_UNF_HDMI_Start! */
    s32Ret = HI_UNF_HDMI_Start(hHdmi);
    if(SUCCESS != s32Ret)
    {
        HAL_ERROR("HDMI start failed:%#x\n", s32Ret);
        return;
    }
    HAL_DEBUG_EXIT();

    return;
}

static VOID HDMI_UnPlug_Proc(HI_VOID* pPrivateData)
{
    HAL_DEBUG_ENTER();
    HDMI_ARGS_S*      pArgs  = (HDMI_ARGS_S*)pPrivateData;
    HI_UNF_HDMI_ID_E hHdmi   =  pArgs->enHdmi;

    (VOID)HI_UNF_HDMI_Stop(hHdmi);
    HAL_DEBUG_EXIT();
    return;
}

static VOID HDMI_Event_Proc(HI_UNF_HDMI_EVENT_TYPE_E event, VOID* pPrivateData)
{
    HAL_DEBUG_ENTER();

    switch (event)
    {
        case HI_UNF_HDMI_EVENT_HOTPLUG:
            HDMI_HotPlug_Proc(pPrivateData);
            break;

        case HI_UNF_HDMI_EVENT_NO_PLUG:
            HDMI_UnPlug_Proc(pPrivateData);
            break;

        case HI_UNF_HDMI_EVENT_EDID_FAIL:
            HAL_DEBUG("HI_UNF_HDMI_EVENT_EDID_FAIL \n");
            break;

        case HI_UNF_HDMI_EVENT_HDCP_FAIL:
            HAL_DEBUG("HI_UNF_HDMI_EVENT_HDCP_FAIL \n");
            break;

        case HI_UNF_HDMI_EVENT_HDCP_SUCCESS:
            HAL_DEBUG("HI_UNF_HDMI_EVENT_HDCP_SUCCESS \n");
            break;

        case HI_UNF_HDMI_EVENT_RSEN_CONNECT:
            HAL_DEBUG("HI_UNF_HDMI_EVENT_RSEN_CONNECT \n");
            break;

        case HI_UNF_HDMI_EVENT_RSEN_DISCONNECT:
            HAL_DEBUG("HI_UNF_HDMI_EVENT_RSEN_DISCONNECT \n");
            break;

        default:
            break;
    }

    HAL_DEBUG_EXIT();
    return;
}

#ifdef HI_HDCP_SUPPORT
HI_S32 HIADP_HDMI_SetHDCPKey(HI_UNF_HDMI_ID_E enHDMIId)
{
    HI_UNF_HDMI_LOAD_KEY_S stLoadKey;
    FILE* pBinFile = NULL;
    HI_U32 u32Len;
    HI_U32 u32Ret;

    pBinFile = fopen("EncryptedKey_332bytes.bin", "rb");

    if (HI_NULL == pBinFile)
    {
        return HI_FAILURE;
    }

    fseek(pBinFile, 0, SEEK_END);
    u32Len = ftell(pBinFile);
    fseek(pBinFile, 0, SEEK_SET);

    stLoadKey.u32KeyLength = u32Len; //332
    stLoadKey.pu8InputEncryptedKey  = (HI_U8*)malloc(u32Len);

    if (HI_NULL == stLoadKey.pu8InputEncryptedKey)
    {
        fclose(pBinFile);
        return HI_FAILURE;
    }

    if (u32Len != fread(stLoadKey.pu8InputEncryptedKey, 1, u32Len, pBinFile))
    {
        fclose(pBinFile);
        free(stLoadKey.pu8InputEncryptedKey);
        return HI_FAILURE;
    }

    u32Ret = HI_UNF_HDMI_LoadHDCPKey(enHDMIId, &stLoadKey);
    free(stLoadKey.pu8InputEncryptedKey);
    fclose(pBinFile);
    return u32Ret;
}
#endif

static S32 HIADP_HDMI_Init(HI_UNF_HDMI_ID_E enHDMIId, HI_UNF_ENC_FMT_E enWantFmt)
{
    HAL_DEBUG_ENTER();
    S32 s32Ret = FAILURE;
    HI_UNF_HDMI_OPEN_PARA_S stOpenParam;
    HI_UNF_HDMI_DELAY_S  stDelay;

    g_stHdmiArgs.enHdmi = enHDMIId;
    s32Ret = HI_UNF_HDMI_Init();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_HDMI_Init failed:%#x\n", s32Ret);
        return HI_FAILURE;
    }

#ifdef HI_HDCP_SUPPORT
    s32Ret = HIADP_HDMI_SetHDCPKey(enHDMIId);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("Set hdcp erro:%#x\n", s32Ret);
    }

#endif
    HI_UNF_HDMI_GetDelay(HI_UNF_HDMI_ID_0, &stDelay);
    stDelay.bForceFmtDelay  = HI_TRUE;
    stDelay.bForceMuteDelay = HI_TRUE;
    stDelay.u32FmtDelay     = 500;
    stDelay.u32MuteDelay    = 120;
    HI_UNF_HDMI_SetDelay(HI_UNF_HDMI_ID_0, &stDelay);
    #ifdef LINUX_OS
    g_stCallbackFunc.pfnHdmiEventCallback = HDMI_Event_Proc;
    g_stCallbackFunc.pPrivateData = &g_stHdmiArgs;

    s32Ret = HI_UNF_HDMI_RegCallbackFunc(enHDMIId, &g_stCallbackFunc);

    if (s32Ret != SUCCESS)
    {
        HI_UNF_HDMI_DeInit();
        return FAILURE;
    }
    #endif
    stOpenParam.enDefaultMode = g_enDefaultMode;//HI_UNF_HDMI_FORCE_NULL;
    s32Ret = HI_UNF_HDMI_Open(enHDMIId, &stOpenParam);

    if (s32Ret != HI_SUCCESS)
    {
        HAL_ERROR("HI_UNF_HDMI_Open failed:%#x\n", s32Ret);
        #ifdef LINUX_OS
        HI_UNF_HDMI_UnRegCallbackFunc(enHDMIId, &g_stCallbackFunc);
        #endif
        HI_UNF_HDMI_DeInit();
        return HI_FAILURE;
    }

    HAL_DEBUG_EXIT();
    return s32Ret;
}
//////////////////////////////////////HDMI END//////////////////////////////////////////
/* CNcomment:OPEN的时候设置display的初始参数 */
S32 display_set_param()
{
    S32 s32Ret = SUCCESS;
    HI_UNF_DISP_BG_COLOR_S BgColor;
#ifndef ANDROID
    s32Ret = HI_UNF_DISP_SetVirtualScreen(HI_UNF_DISPLAY1, 1920, 1080);
    if (s32Ret != SUCCESS)
    {
        return s32Ret;
    }
#endif

    BgColor.u8Red   = 0;
    BgColor.u8Green = 0;
    BgColor.u8Blue  = 0;
    s32Ret = HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY1, &BgColor);

    if (s32Ret != SUCCESS)
    {
        return s32Ret;
    }

    return s32Ret;
}

/*CNcomment:unf制式类型转换为tvos制式*/
static S32 convert_unf_disp_format_to_hal(HI_UNF_ENC_FMT_E enUnfFmt,
        VOUT_FORMAT_E* penDispFmt,
        VOUT_VID_FRAME_RATE_E* penFrameRate)
{
    U32 i = 0;

    if ((NULL == penDispFmt) || (NULL == penFrameRate))
    {
        HAL_ERROR("convert_unf_disp_format_to_hal failed, null ptr.");
        return FAILURE;
    }

    *penDispFmt   = VOUT_FORMAT_UNKNOWN;
    *penFrameRate = VOUT_VID_FRAME_RATE_UNKNOWN;

    for (i = 0; i < (sizeof(g_stHiDispFormat) / sizeof(g_stHiDispFormat[0])); i++)
    {
        if (g_stHiDispFormat[i].enUnfFmt == enUnfFmt)
        {
            *penDispFmt   = g_stHiDispFormat[i].enDispFmt;
            *penFrameRate = g_stHiDispFormat[i].enFrameRate;
            return SUCCESS;
        }
    }

    return SUCCESS;
}

/* CNcomment:tvos宽高比类型 转化为unf制式 */
static HI_UNF_DISP_ASPECT_RATIO_E convert_tvos_disp_aspectrate_to_unf(VOUT_ASPECT_RATIO_E enTvosAspectRatio)
{
    HI_UNF_DISP_ASPECT_RATIO_E enUnfAspectRatio = HI_UNF_DISP_ASPECT_RATIO_16TO9;

    switch (enTvosAspectRatio)
    {
        case VOUT_ASPECT_RATIO_AUTO:
            enUnfAspectRatio = HI_UNF_DISP_ASPECT_RATIO_AUTO;
            break;

        case VOUT_ASPECT_RATIO_16TO9:
            enUnfAspectRatio = HI_UNF_DISP_ASPECT_RATIO_16TO9;
            break;

        case VOUT_ASPECT_RATIO_4TO3:
            enUnfAspectRatio = HI_UNF_DISP_ASPECT_RATIO_4TO3;
            break;

        default:
            enUnfAspectRatio = HI_UNF_DISP_ASPECT_RATIO_16TO9;
            break;
    }

    return enUnfAspectRatio;
}

/* CNcomment:unf宽高比类型 转化为tvos制式 */
static VOUT_ASPECT_RATIO_E convert_unf_disp_aspectrate_to_tvos(HI_UNF_DISP_ASPECT_RATIO_E enUnfAspectRatio)
{
    VOUT_ASPECT_RATIO_E enAspectRatio = VOUT_ASPECT_RATIO_16TO9;

    switch (enUnfAspectRatio)
    {
        case HI_UNF_DISP_ASPECT_RATIO_AUTO:
            enAspectRatio = VOUT_ASPECT_RATIO_AUTO;
            break;

        case HI_UNF_DISP_ASPECT_RATIO_16TO9:
            enAspectRatio = VOUT_ASPECT_RATIO_16TO9;
            break;

        case HI_UNF_DISP_ASPECT_RATIO_4TO3:
            enAspectRatio = VOUT_ASPECT_RATIO_4TO3;
            break;

        default:
            enAspectRatio = VOUT_ASPECT_RATIO_16TO9;
            break;
    }

    return enAspectRatio;
}

/* CNcomment:窗口的宽高转换方式 */
static HI_UNF_VO_ASPECT_CVRS_E convert_tvos_window_aspect_cvrs(VOUT_ASPECT_RATIO_CONVERSION_E enTvosRatioConv)
{
    /* Default value */
    HI_UNF_VO_ASPECT_CVRS_E enAspectRatioConv = HI_UNF_VO_ASPECT_CVRS_LETTERBOX;

    switch (enTvosRatioConv)
    {
        case VOUT_AR_CONVERSION_PAN_SCAN:
            enAspectRatioConv = HI_UNF_VO_ASPECT_CVRS_PAN_SCAN;
            break;

        case VOUT_AR_CONVERSION_LETTER_BOX:
            enAspectRatioConv = HI_UNF_VO_ASPECT_CVRS_LETTERBOX;
            break;

        case VOUT_AR_CONVERSION_COMBINED:
            enAspectRatioConv = HI_UNF_VO_ASPECT_CVRS_COMBINED;
            break;

        case VOUT_AR_CONVERSION_IGNORE:
            enAspectRatioConv = HI_UNF_VO_ASPECT_CVRS_IGNORE;
            break;

        default:
            enAspectRatioConv = HI_UNF_VO_ASPECT_CVRS_LETTERBOX;
            break;
    }

    return enAspectRatioConv;
}

static VOUT_ASPECT_RATIO_CONVERSION_E convert_unf_window_aspect_cvrs(HI_UNF_VO_ASPECT_CVRS_E enUNFRatioConv)
{
    /* Default value */
    VOUT_ASPECT_RATIO_CONVERSION_E enAspectRatioConv = VOUT_AR_CONVERSION_LETTER_BOX;

    switch (enUNFRatioConv)
    {
        case HI_UNF_VO_ASPECT_CVRS_PAN_SCAN:
            enAspectRatioConv = VOUT_AR_CONVERSION_PAN_SCAN;
            break;

        case HI_UNF_VO_ASPECT_CVRS_LETTERBOX:
            enAspectRatioConv = VOUT_AR_CONVERSION_LETTER_BOX;
            break;

        case HI_UNF_VO_ASPECT_CVRS_COMBINED:
            enAspectRatioConv = VOUT_AR_CONVERSION_COMBINED;
            break;

        case HI_UNF_VO_ASPECT_CVRS_IGNORE:
            enAspectRatioConv = VOUT_AR_CONVERSION_IGNORE;
            break;

        default:
            enAspectRatioConv = VOUT_AR_CONVERSION_LETTER_BOX;
            break;
    }

    return enAspectRatioConv;
}

S32 check_vout_init_param(HANDLE hVout)
{
    if (!s_bVoutInited)
    {
        HAL_ERROR("Not Inited!!.");
        return ERROR_VO_NOT_INITED;
    }

    if (INVALID_HANDLE == g_VoutInfo[0].hVoutHandle || g_VoutInfo[0].hVoutHandle != hVout)
    {
        HAL_ERROR("Invalid vout handle!!.");
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

/* End:  CNcomment:自定义函数 */

/*!
*@brief CNcomment:video out 初始化
*/
S32 vout_init(struct _VOUT_DEVICE_S* pstDev, const VOUT_INIT_PARAMS_S* const pstInitParams)
{
    U32 i = 0;
    S32 s32Ret = FAILURE;

    HAL_DEBUG_ENTER();

    if (s_bVoutInited)
    {
        HAL_DEBUG("vout already inited.");
        return SUCCESS;
    }

    /* 1.init display */
    s32Ret = HI_UNF_DISP_Init();
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_DISP_Init failed. ret(0x%08x)", s32Ret);
        return ERROR_DISPLAY_INIT_FAILED;
    }

    /* 2.init vo  */
    s32Ret = HI_UNF_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("call HI_UNF_VO_Init error!!.  ret(0x%08x)", s32Ret);
        (VOID)HI_UNF_DISP_DeInit();
        return ERROR_VO_INIT_FAILED;
    }

    /* 3.init PQ */
    if (SUCCESS != HI_UNF_PQ_Init())
    {
        HAL_ERROR("call HI_UNF_PQ_DeInit error!!, cann't set PQ value.");
    }

    if (SUCCESS != HI_UNF_MCE_Init(HI_NULL))
    {
        HAL_ERROR("call HI_UNF_MCE_Init error!!");
    }

    VOUT_LOCK();

    for (i = 0; i < VOUT_INSTANCE_MAX; i++)
    {
        g_VoutInfo[i].pstVoutOpenParams = NULL;
        g_VoutInfo[i].hVoutHandle = INVALID_HANDLE;
    }

    s_bVoutInited = TRUE;
    VOUT_UNLOCK();

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
 *   brief Open a video output instance.CNcomment:打开一个视频输出实例
 *  默认双通道高标清输出,只能open一次
 *  HD: display1 interface:YPBPR and HDMI  SOURCE
 *  SD: display0 interface:CVBS            DESTINATION
**/
S32 vout_open_channel(struct _VOUT_DEVICE_S* pstVoutDev,
                      HANDLE* const phVout,
                      const VOUT_OPEN_PARAMS_S* const pstOpenParams)
{
    S32                    s32Ret = FAILURE;
    VOUT_OPEN_PARAMS_S*    pstVoutOpenParams = NULL;
    HI_UNF_ENC_FMT_E       enFmt;

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((!s_bVoutInited), ERROR_VO_NOT_INITED, "Not Inited!!.");

    if (NULL == phVout)
    {
        HAL_ERROR("Param Point is NULL!!.");
        return ERROR_NULL_PTR;
    }

    VOUT_LOCK();

    if (INVALID_HANDLE != g_VoutInfo[0].hVoutHandle)
    {
        *phVout = g_VoutInfo[0].hVoutHandle;
        s_s32VoutInstCount++;
        HAL_ERROR("open new channle, instCout is %d ", s_s32VoutInstCount);
        VOUT_UNLOCK();
        return SUCCESS;
    }

    VOUT_UNLOCK();

    pstVoutOpenParams = (VOUT_OPEN_PARAMS_S*)HAL_MALLOC(sizeof(VOUT_OPEN_PARAMS_S));
    HAL_CHK_GOTO((!pstVoutOpenParams), VOUT_END, "vout_open memory malloc failed!!.");
    HAL_MEMSET((VOID*)pstVoutOpenParams, 0x0, sizeof(VOUT_OPEN_PARAMS_S));

    s32Ret = enable_display_output();
    if (FAILURE == s32Ret)
    {
        goto VOUT_DISP1_ATTACH_INTF_FAIL;
    }
    else if (ERROR_DISPLAY_ATTACH_INTF_FAILED == s32Ret)
    {
        goto VOUT_DISP_GET_FORMAT_FAIL;
    }
    else
    {
    }

    /* 3. set same source dst_display0 src_display1 */
    s32Ret = HI_UNF_DISP_Attach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
    HAL_CHK_GOTO((SUCCESS != s32Ret), VOUT_DISP_GET_FORMAT_FAIL, "vout_open display attach failed!!. Ret=%#x.", s32Ret);

#if 0
    enFmt = convert_tvos_disp_format_to_unf(pstOpenParams->enDispFmt);
    /* 4. set display1 format tvos制式转换unf */
    s32Ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, enFmt);

    if (s32Ret != SUCCESS)
    {
        HAL_ERROR("vout_open display1 setformat failed!!. Ret=%#x.", s32Ret);
        goto VOUT_DISP_SET_PARAM_FAIL;
    }

    /* 5. set display0 format */
    s32Ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, convert_display0_format(enFmt));

    if (s32Ret != SUCCESS)
    {
        HAL_ERROR("vout_open display1 setformat failed!!. Ret=%#x.", s32Ret);
        goto VOUT_DISP_SET_PARAM_FAIL;
    }

#endif

    /* 6. set display param */
    s32Ret = display_set_param();
    HAL_CHK_GOTO((SUCCESS != s32Ret), VOUT_DISP_GET_FORMAT_FAIL,
                 "vout_open display set parameter failed!!. Ret=%#x.", s32Ret);

    /* 7. first open display1 */
    s32Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY1);
    if (SUCCESS != s32Ret)
    {
        s32Ret = ERROR_DISPLAY_CHANNEL_OPEN_FAILED;
        HAL_ERROR("vout_open display1 open failed!!. Ret=%#x.", s32Ret);
        goto VOUT_DISP_GET_FORMAT_FAIL;
    }

    /* 8. open display0 */
    s32Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY0);
    if (SUCCESS != s32Ret)
    {
        s32Ret = ERROR_DISPLAY_CHANNEL_OPEN_FAILED;
        HAL_ERROR("vout_open display0 open failed!!. Ret=%#x.", s32Ret);
        goto VOUT_DISP_OPEN_FAIL;
    }

    /* 9. CNcomment:获取源的显示制式 */
    s32Ret = HI_UNF_DISP_GetFormat(HI_UNF_DISPLAY1, &enFmt);
    HAL_CHK_GOTO((SUCCESS != s32Ret), VOUT_DISP_GET_FORMAT_FAIL,
                 "vout_open HI_UNF_DISP_GetFormat failed!!. Ret=%#x.", s32Ret);

    /* 10. HDMI init */
    s32Ret = HIADP_HDMI_Init(HI_UNF_HDMI_ID_0, enFmt);
    HAL_CHK_GOTO((SUCCESS != s32Ret), VOUT_DISP_GET_FORMAT_FAIL,
                 "vout_open HDMI_Init failed!!. Ret=%#x.", s32Ret);

    /* Handle value *//** FIXME: hal record handle list */
    pstVoutOpenParams->enDispChan   = VOUT_DISPLAY_HD0 | VOUT_DISPLAY_SD0;
    pstVoutOpenParams->enOutputType = VOUT_OUTPUT_TYPE_YPBPR | VOUT_OUTPUT_TYPE_HDMI;

    VOUT_LOCK();
    g_VoutInfo[0].pstVoutOpenParams = pstVoutOpenParams;
    g_VoutInfo[0].hVoutHandle = ((VOUT_MODE_ID << 16) | s_s32VoutInstCount);
    *phVout = g_VoutInfo[0].hVoutHandle;
    s_s32VoutInstCount++;
    HAL_ERROR("open new channle, instCout is %d ", s_s32VoutInstCount);
    VOUT_UNLOCK();

    HAL_DEBUG_EXIT();
    return SUCCESS;

VOUT_DISP_GET_FORMAT_FAIL:
    HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
VOUT_DISP_OPEN_FAIL:
    HI_UNF_DISP_Close(HI_UNF_DISPLAY1);

    /* we should not call this function, it may cause black screen, because it will detach the real device. */
#if 0
VOUT_DISP_SET_PARAM_FAIL:
    HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
VOUT_DISP_ATTACH_FAIL:
    stIntf[0].enIntfType          = HI_UNF_DISP_INTF_TYPE_CVBS;
    stIntf[0].unIntf.stCVBS.u8Dac = DAC_CVBS;
    HI_UNF_DISP_DetachIntf(HI_UNF_DISPLAY0, &stIntf[0], 1);

VOUT_DISP0_ATTACH_INTF_FAIL:
    stIntf[0].enIntfType = HI_UNF_DISP_INTF_TYPE_YPBPR;
    stIntf[0].unIntf.stYPbPr.u8DacY     = DAC_YPBPR_Y;
    stIntf[0].unIntf.stYPbPr.u8DacPb    = DAC_YPBPR_PB;
    stIntf[0].unIntf.stYPbPr.u8DacPr    = DAC_YPBPR_PR;
    HI_UNF_DISP_DetachIntf(HI_UNF_DISPLAY1, &stIntf[0], 2);
#endif

VOUT_DISP1_ATTACH_INTF_FAIL:
    HAL_FREE((VOID*)pstVoutOpenParams);

VOUT_END:
    return s32Ret;
}

/**
 *  CNcomment:关闭打开的通道
**/
S32 vout_close_channel(struct _VOUT_DEVICE_S* pstVoutDev,
                       const HANDLE hVout,
                       const VOUT_CLOSE_PARAMS_S* const pstCloseParams)
{
    S32 s32Ret = SUCCESS;
    VOUT_OPEN_PARAMS_S* pstVoutOpenParams = NULL;

    HAL_DEBUG_ENTER();

    if (!s_bVoutInited)
    {
        HAL_ERROR("Not Inited!!.");
        return ERROR_NOT_INITED;
    }

    if (INVALID_HANDLE == g_VoutInfo[0].hVoutHandle)
    {
        HAL_ERROR("vout not open channel!!.");
        return ERROR_VO_PARAMETER_INVALID;
    }

    VOUT_LOCK();

    if ((--s_s32VoutInstCount) > 0)
    {
        HAL_ERROR("instant no empty, should not free this handle, instcount [%d] ",
                  s_s32VoutInstCount);
        VOUT_UNLOCK();
        return SUCCESS;
    }

    pstVoutOpenParams = g_VoutInfo[0].pstVoutOpenParams;
    HAL_FREE((VOID*)pstVoutOpenParams);

    g_VoutInfo[0].hVoutHandle = INVALID_HANDLE;
    g_VoutInfo[0].pstVoutOpenParams = NULL;

    HAL_ERROR("release channle, instCout is %d ", s_s32VoutInstCount);
    VOUT_UNLOCK();

    /* no need closd DISPLAY0,DISPLAY1 and HDMI */

    s32Ret = HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_DISP0_Close failed. ret(0x%08x)", s32Ret);
        return ERROR_DISPLAY_CHANNEL_CLOSE_FAILED;
    }

    s32Ret = HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_DISP1_Close failed. ret(0x%08x)", s32Ret);
        return ERROR_DISPLAY_CHANNEL_CLOSE_FAILED;
    }

    s32Ret = HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_DISP_Detach failed. ret(0x%08x)", s32Ret);
        return FAILURE;
    }

    //s32Ret = disable_display_output();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_DISP1_Detach failed. ret(0x%08x)", s32Ret);
        return ERROR_DISPLAY_DETACH_INTF_FAILED;
    }

    /* HDMI UnRegCallback */
    #ifdef LINUX_OS
    HI_UNF_HDMI_Stop(HI_UNF_HDMI_ID_0);
    HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_0);
    HI_UNF_HDMI_UnRegCallbackFunc(HI_UNF_HDMI_ID_0, &g_stCallbackFunc);

    HI_UNF_HDMI_OPEN_PARA_S stOpenParam;
    stOpenParam.enDefaultMode = g_enDefaultMode;
    HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0, &stOpenParam);
    HI_UNF_HDMI_Start(HI_UNF_HDMI_ID_0);
    #endif
    HAL_DEBUG_EXIT();

    return SUCCESS;
}
/**
 * CNcomment: 模块终止
**/
S32 vout_term(struct _VOUT_DEVICE_S* pstVoutDev, const VOUT_TERM_PARAM_S* const  pstTermParams)
{
    U32 i = 0;
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    if (!s_bVoutInited)
    {
        HAL_DEBUG("Not Inited!!.");
        return SUCCESS;
    }

    VOUT_LOCK();

    for (i = 0; i < VOUT_INSTANCE_MAX; i++)
    {
        if (NULL != g_VoutInfo[i].pstVoutOpenParams)
        {
            HAL_ERROR("please close channel first\n");
            VOUT_UNLOCK();
            return FAILURE;
        }
    }

    VOUT_UNLOCK();

    s32Ret = HI_UNF_VO_DeInit();
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_VO_DeInit failed. ret(0x%08x)", s32Ret);
        return ERROR_VO_DEINIT_FAILED;
    }

    s32Ret = HI_UNF_DISP_DeInit();
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_DISP_DeInit failed. ret(0x%08x)", s32Ret);
        return ERROR_DISPLAY_DEINIT_FAILED;
    }

    if (SUCCESS != HI_UNF_PQ_DeInit())
    {
        HAL_ERROR("call HI_UNF_PQ_DeInit error!!, cann't set PQ value.  ret(0x%08x)", s32Ret);
        return FAILURE;
    }

    HI_UNF_MCE_DeInit();

    VOUT_LOCK();
    s_bVoutInited = FALSE;
    VOUT_UNLOCK();

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/**
brief Set display param. CNcomment:设置显示参数
*/
S32 vout_get_capability(struct _VOUT_DEVICE_S* pstVoutDev, VOUT_CAPABILITY_S* const pstCapability)
{
    U32 u32IndexHD0 = 0;
    U32 u32IndexSD0 = 3;

    HAL_DEBUG_ENTER();

    if (!pstCapability)
    {
        HAL_ERROR("vout_get_capability Null PTR error!!.");
        return ERROR_NULL_PTR;
    }

    /* Default capability config */
    pstCapability->enDisplayChannel
        = (VOUT_DISPLAY_CHANNEL_E)((U32)VOUT_DISPLAY_HD0 | (U32)VOUT_DISPLAY_SD0);

    pstCapability->astDispCapabilityAttr[u32IndexHD0].enVoutType
        = (VOUT_OUTPUT_TYPE_E)((U32)VOUT_OUTPUT_TYPE_YPBPR | (U32)VOUT_OUTPUT_TYPE_HDMI);

    pstCapability->astDispCapabilityAttr[u32IndexHD0].au32VidFormat[0]
        = VOUT_VID_FRAME_RATE_AUTO;

    pstCapability->astDispCapabilityAttr[u32IndexHD0].u32WindowNum
        = 1;

    pstCapability->astDispCapabilityAttr[u32IndexSD0].enVoutType
        = (VOUT_OUTPUT_TYPE_E)((U32)VOUT_OUTPUT_TYPE_YCBCR);

    pstCapability->astDispCapabilityAttr[u32IndexSD0].au32VidFormat[0]
        = VOUT_VID_FRAME_RATE_AUTO;

    pstCapability->astDispCapabilityAttr[u32IndexSD0].u32WindowNum
        = 1;

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 vout_evt_config(struct _VOUT_DEVICE_S* pstVoutDev,
                    const HANDLE hVout,
                    const VOUT_EVT_CONFIG_PARAMS_S* const pstCfg)
{
    return ERROR_NOT_SUPPORTED;
}

S32 vout_get_evt_config(struct _VOUT_DEVICE_S* pstVoutDev,
                        const HANDLE hVout,
                        const VOUT_EVT_E enEvt,
                        VOUT_EVT_CONFIG_PARAMS_S* const pstCfg)
{
    return ERROR_NOT_SUPPORTED;
}

/*
 * CNcomment:关闭显示通道
 */
S32 vout_outputchannel_mute(struct _VOUT_DEVICE_S* pstVoutDev,
                            const HANDLE hVout,
                            const VOUT_OUTPUT_TYPE_E enOutChannel)
{
    /* 功能和vout_close_channel冲突 ? */
    return ERROR_NOT_SUPPORTED;
}

/*
 * CNcomment:打开显示通道
 */
S32 vout_outputchannel_unmute(struct _VOUT_DEVICE_S* pstVoutDev,
                              const HANDLE hVout,
                              const VOUT_OUTPUT_TYPE_E enOutChannel)
{
    return ERROR_NOT_SUPPORTED;
}

static S32 get_display_format(HI_UNF_DISP_E enDisp, VOUT_DISPSETTING_S* pstSettings)
{
    S32 s32Ret = FAILURE;
    HI_UNF_ENC_FMT_E enEncFmt = HI_UNF_ENC_FMT_BUTT;

    /* get sdk dispfmt and framerate */
    s32Ret = HI_UNF_DISP_GetFormat(enDisp, &enEncFmt);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_DISP_GetFormat failed. ret(0x%08x)", s32Ret);
        return ERROR_DISPLAY_OP_FAILED;
    }

    /* if get unknown format, use default format */
    if (HI_UNF_ENC_FMT_BUTT == enEncFmt)
    {
        enEncFmt = HI_UNF_ENC_FMT_1080P_60;
    }

    s32Ret = convert_unf_disp_format_to_hal(enEncFmt, &(pstSettings->enDispFmt), &(pstSettings->enFrameRate));
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("convert_unf_disp_format_to_hal failed. ret(0x%08x)", s32Ret);
        return ERROR_DISPLAY_OP_FAILED;
    }

    return SUCCESS;
}

/*
 *  CNcomment:hisi平台默认双通道高标清输出
 *  HD: display1 interface:YPBPR and HDMI  SOURCE
 *  SD: display0 interface:CVBS            DESTINATION
 *  set 宽高比类型
 *  set u8Bbrightness/u8Contrast/u8Saturation 范围 [0,100]
 */
S32 vout_display_get(struct _VOUT_DEVICE_S* pstVoutDev,
                     const HANDLE hVout,
                     VOUT_DISPSETTING_S* const pstSettings)
{
    S32 s32Ret = FAILURE;
    HI_UNF_DISP_ASPECT_RATIO_S stAspectRatio;
    HI_UNF_DISP_OFFSET_S  stOffset;
    HI_UNF_EDID_BASE_INFO_S stSinkCap;
    U32 u32Brightness = 0;
    U32 u32Contrast   = 0;
    U32 u32Saturation = 0;
    U32 u32Hue = 0;

    HAL_DEBUG_ENTER();

    memset(&stSinkCap, 0, sizeof(HI_UNF_EDID_BASE_INFO_S));
    s32Ret = check_vout_init_param(hVout);
    HAL_CHK_RETURN_NO_PRINT((SUCCESS != s32Ret), s32Ret);

    /* Param check */
    HAL_CHK_RETURN((NULL == pstSettings), ERROR_NULL_PTR, "Null PTR!!.");

    get_display_format(HI_UNF_DISPLAY1, pstSettings);

    pstSettings->enAspectRatioConv = VOUT_AR_CONVERSION_LETTER_BOX;
    pstSettings->enOutputType      = VOUT_OUTPUT_TYPE_YPBPR | VOUT_OUTPUT_TYPE_HDMI | VOUT_OUTPUT_TYPE_YCBCR;
    pstSettings->bOutputEnable     = TRUE;

    /* 获取宽高比类型 */
    s32Ret = HI_UNF_DISP_GetAspectRatio(HI_UNF_DISPLAY1, &stAspectRatio);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_DISP_SetAspectRatio failed. ret(0x%08x)", s32Ret);

    pstSettings->enAspectRatio = convert_unf_disp_aspectrate_to_tvos(stAspectRatio.enDispAspectRatio);

    /* 获取u8Bbrightness/u8Contrast/u8Saturation 范围 [0,100] */
    s32Ret = HI_UNF_PQ_GetBrightness(HI_UNF_DISPLAY1, &u32Brightness);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_GetBrightness failed. ret(0x%08x)", s32Ret);

    s32Ret = HI_UNF_PQ_GetContrast(HI_UNF_DISPLAY1, &u32Contrast);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_GetContrast failed. ret(0x%08x)", s32Ret);

    s32Ret = HI_UNF_PQ_GetSaturation(HI_UNF_DISPLAY1, &u32Saturation);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_GetSaturation failed. ret(0x%08x)", s32Ret);

    s32Ret = HI_UNF_PQ_GetHue(HI_UNF_DISPLAY1, &u32Hue);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_GetHue failed. ret(0x%08x)", s32Ret);

    pstSettings->u8Brightness = (U8)u32Brightness;
    pstSettings->u8Contrast   = (U8)u32Contrast;
    pstSettings->u8Saturation = (U8)u32Saturation;
    pstSettings->u8Hue        = (U8)u32Hue;

    s32Ret = HI_UNF_DISP_GetScreenOffset(HI_UNF_DISPLAY1, &stOffset);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_DISP_GetScreenOffset failed. ret(0x%08x)", s32Ret);

    pstSettings->stDispOutRegion.u32Left   = stOffset.u32Left;
    pstSettings->stDispOutRegion.u32Top    = stOffset.u32Top;
    pstSettings->stDispOutRegion.u32Right  = stOffset.u32Right;
    pstSettings->stDispOutRegion.u32Bottom = stOffset.u32Bottom;

    /* get native format*/
    s32Ret = HI_UNF_HDMI_GetSinkCapability(HI_UNF_HDMI_ID_0, &stSinkCap);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_HDMI_GetSinkCapability failed. ret(0x%08x)", s32Ret);

    s32Ret = convert_unf_disp_format_to_hal(stSinkCap.enNativeFormat,
             &(pstSettings->enAutoDispFmt), &(pstSettings->enAutoFrameRate));

    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "convert_unf_disp_format_to_hal failed. ret(0x%08x)", s32Ret);

    return SUCCESS;
}

/* set display format */
static S32 set_display_format(HI_UNF_DISP_E enDisp,
                              const VOUT_DISPSETTING_S* const pstSettings)
{
    S32 s32Ret = FAILURE;
    BOOL bExistFormat = FALSE;
    HI_UNF_ENC_FMT_E enEncFmt = HI_UNF_ENC_FMT_1080P_60;
    HI_UNF_PDM_BASEPARAM_TYPE_E enType = HI_UNF_PDM_BASEPARAM_BUTT;
    HI_UNF_PDM_DISP_PARAM_S stDispParam;
    U32 i = 0;

    memset(&stDispParam, 0, sizeof(HI_UNF_PDM_DISP_PARAM_S));

    switch (enDisp)
    {
        case HI_UNF_DISPLAY0:
        {
            enType = HI_UNF_PDM_BASEPARAM_DISP0;
            break;
        }

        case HI_UNF_DISPLAY1:
        case HI_UNF_DISPLAY2:
        {
            enType = HI_UNF_PDM_BASEPARAM_DISP1;
            break;
        }

        default:
        {
            HAL_ERROR("Invalid enTrype!!");
            return FAILURE;
        }
    }

    for (i = 0; i < (sizeof(g_stHiDispFormat) / sizeof(g_stHiDispFormat[0])); i++)
    {
        if ((g_stHiDispFormat[i].enDispFmt   == pstSettings->enDispFmt)
            && (g_stHiDispFormat[i].enFrameRate == pstSettings->enFrameRate))
        {
            enEncFmt = g_stHiDispFormat[i].enUnfFmt;
            bExistFormat = TRUE;
            break;
        }
    }

    HAL_CHK_RETURN((FALSE == bExistFormat), FAILURE, "Invalid enDispFmt and enFrameRate!!.");

    if (pstSettings->bClearLogo)
    {
        HI_UNF_MCE_ClearLogo();
    }

    s32Ret = HI_UNF_DISP_SetFormat(enDisp, enEncFmt);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_DISP_SetFormat failed. ret(0x%08x)", s32Ret);

    s32Ret = HI_UNF_PDM_GetBaseParam(enType, &stDispParam);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "ERR: HI_UNF_PDM_GetBaseParam, Ret = %#x\n", s32Ret);

    stDispParam.enFormat = enEncFmt;
    s32Ret = HI_UNF_PDM_UpdateBaseParam(enType, &stDispParam);
    HAL_CHK_RETURN((HI_SUCCESS != s32Ret), s32Ret, "ERR: HI_UNF_PDM_UpdateBaseParam, Ret = %#x\n", s32Ret);

    return SUCCESS;
}

/*
 *  CNcomment:hisi平台默认双通道高标清输出
 *  HD: display1 interface:YPBPR and HDMI  SOURCE
 *  SD: display0 interface:CVBS            DESTINATION
 *  set 宽高比类型
 *  set u8Bbrightness/u8Contrast/u8Saturation 范围 [0,100]
 */
S32 vout_display_set(struct _VOUT_DEVICE_S* pstVoutDev,
                     const HANDLE hVout,
                     const VOUT_DISPSETTING_S* const pstSettings)
{
    S32 s32Ret = FAILURE;
    HI_UNF_DISP_ASPECT_RATIO_S stAspectRatio;
    HI_UNF_DISP_OFFSET_S stScnOffset;
    VOUT_DISPSETTING_S stOrgSettings;

    HAL_DEBUG_ENTER();

    s32Ret = check_vout_init_param(hVout);
    HAL_CHK_RETURN_NO_PRINT((SUCCESS != s32Ret), s32Ret);

    /* Param check */
    HAL_CHK_RETURN((NULL == pstSettings), ERROR_NULL_PTR, "Null PTR!!.");

    if ((pstSettings->u8Brightness > VOUT_BRIGHTNESS_MAX) || (pstSettings->u8Contrast > VOUT_CONTRAST_MAX)
        || (pstSettings->u8Saturation > VOUT_SATURATION_MAX))
    {
        HAL_ERROR("Invalid vout param!!.");
        return ERROR_VO_PARAMETER_INVALID;
    }

    s32Ret = vout_display_get(pstVoutDev, hVout, &stOrgSettings);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_DISP_SetAspectRatio failed. ret(0x%08x)", s32Ret);

    if ((stOrgSettings.enDispFmt != pstSettings->enDispFmt) || (stOrgSettings.enFrameRate != pstSettings->enFrameRate))
    {
        s32Ret = set_display_format(HI_UNF_DISPLAY1, pstSettings);
        HAL_CHK_RETURN((HI_SUCCESS != s32Ret), s32Ret, "HI_UNF_DISP_SetFormat failed. ret(0x%08x)", s32Ret);
    }

    /* CNcomment:设置宽高比类型 */
    if (stOrgSettings.enAspectRatio != pstSettings->enAspectRatio)
    {
        stAspectRatio.enDispAspectRatio = convert_tvos_disp_aspectrate_to_unf(pstSettings->enAspectRatio);

        s32Ret = HI_UNF_DISP_SetAspectRatio(HI_UNF_DISPLAY1, &stAspectRatio);
        HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_DISP_SetAspectRatio failed. ret(0x%08x)", s32Ret);
    }

    /* CNcomment:设置 u8Bbrightness/u8Contrast/u8Saturation/u8Hue 范围 [0,100] */
    s32Ret = HI_UNF_PQ_SetBrightness(HI_UNF_DISPLAY1, (U32)pstSettings->u8Brightness);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_SetBrightness failed. ret(0x%08x)", s32Ret);

    s32Ret = HI_UNF_PQ_SetContrast(HI_UNF_DISPLAY1, (U32)pstSettings->u8Contrast);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_SetBrightness failed. ret(0x%08x)", s32Ret);

    s32Ret = HI_UNF_PQ_SetSaturation(HI_UNF_DISPLAY1, (U32)pstSettings->u8Saturation);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_SetSaturation failed. ret(0x%08x)", s32Ret);

    s32Ret = HI_UNF_PQ_SetHue(HI_UNF_DISPLAY1, (U32)pstSettings->u8Hue);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_SetHue failed. ret(0x%08x)", s32Ret);

    HI_UNF_DISP_GetScreenOffset(HI_UNF_DISPLAY1, &stScnOffset);

    if (!IS_REGION_EQ(stScnOffset, pstSettings->stDispOutRegion))
    {
        stScnOffset.u32Left   = pstSettings->stDispOutRegion.u32Left;
        stScnOffset.u32Top    = pstSettings->stDispOutRegion.u32Top;
        stScnOffset.u32Bottom = pstSettings->stDispOutRegion.u32Bottom;
        stScnOffset.u32Right  = pstSettings->stDispOutRegion.u32Right;

        s32Ret = HI_UNF_DISP_SetScreenOffset(HI_UNF_DISPLAY1, &stScnOffset);
        HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_DISP_SetScreenOffset failed. ret(0x%08x)", s32Ret);
    }

    HAL_DEBUG_EXIT();

    return s32Ret;
}

/*
 * CNcomment:CGMS启动
 */
S32 vout_vbi_cgms_start(struct _VOUT_DEVICE_S* pstVoutDev,
                        HANDLE hVout,
                        VOUT_VBI_CGMS_TYPE_E enCgmsType,
                        VOUT_VBI_CGMS_A_COPY_E enCopyRight)
{
    HI_UNF_DISP_CGMS_CFG_S stCgmsCfg;
    HI_UNF_DISP_CGMS_TYPE_E enType;
    HI_UNF_DISP_CGMS_MODE_E enMode;
    HI_UNF_DISP_VBI_CFG_S stVBICfg;

    HAL_DEBUG_ENTER();

    S32 s32Ret = check_vout_init_param(hVout);
    HAL_CHK_RETURN_NO_PRINT((SUCCESS != s32Ret), s32Ret);

    memset(&stVBICfg, 0, sizeof(stVBICfg));
    stVBICfg.enType =  HI_UNF_DISP_VBI_TYPE_CC;
    HI_UNF_DISP_CreateVBI(HI_UNF_DISPLAY0, &stVBICfg, &s_hVBI);

    if (enCgmsType == VOUT_VBI_CGMS_A)
    {
        enType = HI_UNF_DISP_CGMS_TYPE_A;
    }
    else if (enCgmsType == VOUT_VBI_CGMS_B)
    {
        enType = HI_UNF_DISP_CGMS_TYPE_B;
    }
    else
    {
        HAL_ERROR("Invalid param!!.");
        return ERROR_VO_PARAMETER_INVALID;
    }

    switch (enCopyRight)
    {
        case VOUT_VBI_CGMS_A_COPY_PERMITTED:
            enMode = HI_UNF_DISP_CGMS_MODE_COPY_FREELY;
            break;

        case VOUT_VBI_CGMS_A_COPY_ONE_TIME_BEEN_MADE:
            enMode = HI_UNF_DISP_CGMS_MODE_COPY_NO_MORE;
            break;

        case VOUT_VBI_CGMS_A_COPY_ONE_TIME:
            enMode = HI_UNF_DISP_CGMS_MODE_COPY_ONCE;
            break;

        case VOUT_VBI_CGMS_A_COPY_FORBIDDEN:
            enMode = HI_UNF_DISP_CGMS_MODE_COPY_NEVER;
            break;

        default:
            HAL_ERROR("Invalid param!!.");
            return ERROR_VO_PARAMETER_INVALID;
    }

    stCgmsCfg.bEnable = HI_TRUE;
    stCgmsCfg.enType = enType;
    stCgmsCfg.enMode = enMode;

    HI_UNF_DISP_SetCgms(HI_UNF_DISPLAY0, &stCgmsCfg);
    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 vout_vbi_cgms_stop(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout)
{
    HI_UNF_DISP_CGMS_CFG_S stCgmsCfg;

    S32 s32Ret = check_vout_init_param(hVout);
    HAL_CHK_RETURN_NO_PRINT((SUCCESS != s32Ret), s32Ret);

    if (UNSIGNED_INT_MAX_VALUE == s_hVBI)
    {
        HAL_ERROR("Invalid param cgms not start!!.");
        return ERROR_VO_PARAMETER_INVALID;
    }

    (VOID)HI_UNF_DISP_DestroyVBI(s_hVBI);

    stCgmsCfg.bEnable = HI_FALSE;
    HI_UNF_DISP_SetCgms(HI_UNF_DISPLAY0, &stCgmsCfg);
    s_hVBI = UNSIGNED_INT_MAX_VALUE;

    return SUCCESS;
}

S32 vout_get_bg_color(struct _VOUT_DEVICE_S* pstVoutDev,
                      HANDLE hVout,
                      VOUT_BG_COLOR_S* pstVoutBgColor)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_DISP_BG_COLOR_S stDispBgColor;

    HAL_DEBUG_ENTER();

    s32Ret = check_vout_init_param(hVout);
    if (SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (NULL == pstVoutBgColor)
    {
        HAL_ERROR("Null PTR!!.");
        return ERROR_NULL_PTR;
    }

    s32Ret = HI_UNF_DISP_GetBgColor(HI_UNF_DISPLAY1, &stDispBgColor);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("FAILURE!");
        return s32Ret;
    }

    pstVoutBgColor->u8Red   = stDispBgColor.u8Red;
    pstVoutBgColor->u8Green = stDispBgColor.u8Green;
    pstVoutBgColor->u8Blue  = stDispBgColor.u8Blue;

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 vout_set_bg_color(struct _VOUT_DEVICE_S* pstVoutDev,
                      HANDLE hVout,
                      VOUT_BG_COLOR_S* pstVoutBgColor)
{
    HI_UNF_DISP_BG_COLOR_S stColor;

    HAL_DEBUG_ENTER();

    S32 s32Ret = check_vout_init_param(hVout);
    if (SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (NULL == pstVoutBgColor)
    {
        HAL_ERROR("Null PTR!!.");
        return ERROR_NULL_PTR;
    }

    stColor.u8Blue  = pstVoutBgColor->u8Blue;
    stColor.u8Green = pstVoutBgColor->u8Green;
    stColor.u8Red   = pstVoutBgColor->u8Red;

    if (SUCCESS != HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY1, &stColor))
    {
        HAL_ERROR("Invalid PARAM!!.");
        return ERROR_VO_PARAMETER_INVALID;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 vout_get_3dmode(struct _VOUT_DEVICE_S* pstVoutDev,
                    HANDLE hVout,
                    VOUT_3D_MODE_E* pen3dMode)
{
    HI_UNF_DISP_3D_E en3D;
    HI_UNF_ENC_FMT_E enEncFormat;

    HAL_DEBUG_ENTER();

    S32 s32Ret = check_vout_init_param(hVout);
    if (SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (NULL == pen3dMode)
    {
        HAL_ERROR("Null PTR!!.");
        return ERROR_NULL_PTR;
    }

    /* 3D only support HDMI */
    if (SUCCESS != HI_UNF_DISP_Get3DMode(HI_UNF_DISPLAY1, &en3D, &enEncFormat))
    {
        return ERROR_VO_PARAMETER_INVALID;
    }

    /* default mode is 2D */
    *pen3dMode = VOUT_3D_MODE_2D;

    switch ((U32)en3D)
    {
        case HI_UNF_DISP_3D_NONE:
            *pen3dMode = VOUT_3D_MODE_2D;
            break;

        case HI_UNF_DISP_3D_FRAME_PACKING:
        case HI_UNF_DISP_3D_SIDE_BY_SIDE_HALF:
        case HI_UNF_DISP_3D_TOP_AND_BOTTOM:
        case HI_UNF_DISP_3D_FIELD_ALTERNATIVE:
        case HI_UNF_DISP_3D_LINE_ALTERNATIVE:
        case HI_UNF_DISP_3D_SIDE_BY_SIDE_FULL:
        case HI_UNF_DISP_3D_L_DEPTH:
        case HI_UNF_DISP_3D_L_DEPTH_GRAPHICS_GRAPHICS_DEPTH:
            *pen3dMode = VOUT_3D_MODE_3D;
            break;

        default:
            break;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 vout_set_3dmode(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, VOUT_3D_MODE_E en3dMode)
{
    VOUT_3D_MODE_E en3dOrgMode   = VOUT_3D_MODE_2D;
    HI_UNF_DISP_3D_E en3D        = HI_UNF_DISP_3D_NONE;
    HI_UNF_ENC_FMT_E enEncFormat = HI_UNF_ENC_FMT_1080P_60;

    HAL_DEBUG_ENTER();

    S32 s32Ret = check_vout_init_param(hVout);
    HAL_CHK_RETURN_NO_PRINT((SUCCESS != s32Ret), s32Ret);

    vout_get_3dmode(pstVoutDev, hVout, &en3dOrgMode);
    HAL_CHK_RETURN_NO_PRINT((en3dOrgMode == en3dMode), SUCCESS);

    if (VOUT_3D_MODE_2D == en3dMode)
    {
        en3D = HI_UNF_DISP_3D_NONE;
    }
    else if ((VOUT_3D_MODE_2DTO3D == en3dMode) || (VOUT_3D_MODE_3D == en3dMode))
    {
        en3D = HI_UNF_DISP_3D_FRAME_PACKING;
    }
    else
    {
        HAL_ERROR("Invalid param!!.");
        return ERROR_VO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_DISP_GetFormat(HI_UNF_DISPLAY1, &enEncFormat);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "Get display format fail!");

    if (enEncFormat == HI_UNF_ENC_FMT_1080P_60 ||
        enEncFormat == HI_UNF_ENC_FMT_1080P_50 ||
        enEncFormat == HI_UNF_ENC_FMT_1080P_30 ||
        enEncFormat == HI_UNF_ENC_FMT_1080P_25 ||
        enEncFormat == HI_UNF_ENC_FMT_1080P_24 ||
        enEncFormat == HI_UNF_ENC_FMT_1080i_60 ||
        enEncFormat == HI_UNF_ENC_FMT_1080i_50)
    {
        enEncFormat = HI_UNF_ENC_FMT_1080P_24_FRAME_PACKING;
    }
    else if (enEncFormat == HI_UNF_ENC_FMT_720P_60)
    {
        enEncFormat = HI_UNF_ENC_FMT_720P_60_FRAME_PACKING;
    }
    else if (enEncFormat == HI_UNF_ENC_FMT_720P_50)
    {
        enEncFormat = HI_UNF_ENC_FMT_720P_50_FRAME_PACKING;
    }

    s32Ret = HI_UNF_DISP_Set3DMode(HI_UNF_DISPLAY1, en3D, enEncFormat);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "Set 3D mode fail!");

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

/*
 *  CNcomment:创建一个显示窗口,返回phVoutWindow HANDLER
 */
S32 vout_window_create(struct _VOUT_DEVICE_S* pstVoutDev,
                       const HANDLE hVout,
                       HANDLE* const phVoutWindow,
                       const VOUT_WINDOW_CREATE_PARAMS_S* const pstCreateParams)
{
    S32 s32Ret = HI_FAILURE;
    HI_UNF_WINDOW_ATTR_S WinAttr;

    s32Ret = check_vout_init_param(hVout);
    if (SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    memset(&WinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));
    WinAttr.enDisp = HI_UNF_DISPLAY1;
    WinAttr.bVirtual = HI_FALSE;

    if (NULL != pstCreateParams)
    {
        WinAttr.bVirtual = hal_to_unf_for_bool(pstCreateParams->bVirtual);
        if (WinAttr.bVirtual)
        {
            WinAttr.enVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_420;
            WinAttr.stWinAspectAttr.enAspectCvrs = HI_UNF_VO_ASPECT_CVRS_IGNORE;
        }
    }

    WinAttr.stWinAspectAttr.enAspectCvrs = HI_UNF_VO_ASPECT_CVRS_IGNORE;
    WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    WinAttr.stWinAspectAttr.u32UserAspectWidth  = 0;
    WinAttr.stWinAspectAttr.u32UserAspectHeight = 0;
    WinAttr.bUseCropRect = HI_FALSE;
    WinAttr.stInputRect.s32X = 0;
    WinAttr.stInputRect.s32Y = 0;
    WinAttr.stInputRect.s32Width = 0;
    WinAttr.stInputRect.s32Height = 0;
    memset(&WinAttr.stOutputRect, 0x0, sizeof(HI_RECT_S));

    s32Ret = HI_UNF_VO_CreateWindow(&WinAttr, phVoutWindow);
    if (s32Ret != SUCCESS)
    {
        HAL_ERROR("vout HI_UNF_VO_CreateWindow fail:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

/*
 *  CNcomment:销毁一个显示窗口,返回phVoutWindow HANDLER
 *  CNcomment:如果已经绑定了源，请先调用vout_window_detach_input
 */
S32 vout_window_destroy(struct _VOUT_DEVICE_S* pstVoutDev,
                        const HANDLE hVout,
                        const HANDLE hVoutWindow,
                        const VOUT_WINDOW_DESTROY_PARAM_S* const pstDestroyParams)
{
    S32 s32Ret = SUCCESS;

    s32Ret = check_vout_init_param(hVout);
    if (SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = HI_UNF_VO_DestroyWindow(hVoutWindow);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_destroy HI_UNF_VO_DestroyWindow failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return s32Ret;
}

/*
 * CNcomment:设置window参数
 */
S32 vout_window_set(struct _VOUT_DEVICE_S* pstVoutDev,
                    const HANDLE hVoutWindow,
                    const VOUT_WINDOW_SETTINGS_S* const pstSettings)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_WINDOW_ATTR_S WinAttr;

    if (0 == hVoutWindow)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (NULL == pstSettings)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.");
        return ERROR_NULL_PTR;
    }

    if ((pstSettings->stWindowUserDefAspect.u32UserAspectHeight > MAX_USER_ASPECT_HEIGHT)
        || (pstSettings->stWindowUserDefAspect.u32UserAspectWidth > MAX_USER_ASPECT_WIDTH))
    {
        HAL_ERROR("vout_window_set PARAMETER_INVALID.\n");
        return ERROR_VO_PARAMETER_INVALID;
    }

    memset(&WinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));

    s32Ret = HI_UNF_VO_GetWindowAttr(hVoutWindow, &WinAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set HI_UNF_VO_GetWindowAttr failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    if (HI_TRUE == pstSettings->stWindowUserDefAspect.bUserDefAspectRatio)
    {
        WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_TRUE;
        WinAttr.stWinAspectAttr.u32UserAspectHeight = pstSettings->stWindowUserDefAspect.u32UserAspectHeight;
        WinAttr.stWinAspectAttr.u32UserAspectWidth  = pstSettings->stWindowUserDefAspect.u32UserAspectWidth;
    }
    else
    {
        if (VOUT_ASPECT_RATIO_AUTO == pstSettings->enAspectRatio)
        {
            WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
        }
        else if (VOUT_ASPECT_RATIO_16TO9 == pstSettings->enAspectRatio)
        {
            WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_TRUE;
            WinAttr.stWinAspectAttr.u32UserAspectHeight = USER_ASPECT_HEIGHT_RATIO_9;
            WinAttr.stWinAspectAttr.u32UserAspectWidth = USER_ASPECT_WIDTH_RATIO_16;
        }
        else if (VOUT_ASPECT_RATIO_4TO3 == pstSettings->enAspectRatio)
        {
            WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_TRUE;
            WinAttr.stWinAspectAttr.u32UserAspectHeight = USER_ASPECT_HEIGHT_RATIO_3;
            WinAttr.stWinAspectAttr.u32UserAspectWidth = USER_ASPECT_WIDTH_RATIO_4;
        }
    }

    WinAttr.stWinAspectAttr.enAspectCvrs = convert_tvos_window_aspect_cvrs(pstSettings->enAspectRatioConv);

    s32Ret = HI_UNF_VO_SetWindowAttr(hVoutWindow, &WinAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set HI_UNF_VO_SetWindowAttr failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return s32Ret;
}

/**
 * CNcomment:设置window参数
 */
S32 vout_window_get(struct _VOUT_DEVICE_S* pstVoutDev,
                    const HANDLE hVoutWindow,
                    VOUT_WINDOW_SETTINGS_S* const pstSettings)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_WINDOW_ATTR_S WinAttr;
    U32 u32Brightness = 0;
    U32 u32Contrast   = 0;
    U32 u32Saturation = 0;

    HAL_CHK_RETURN((0 == hVoutWindow), ERROR_VO_WIN_NOT_CREATED, "vout_window_set Invalid vout handle!!.");

    HAL_CHK_RETURN((NULL == pstSettings), ERROR_NULL_PTR, "vout_window_set Invalid vout handle!!.");

    memset(&WinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));
    s32Ret = HI_UNF_VO_GetWindowAttr(hVoutWindow, &WinAttr);

    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_VO_PARAMETER_INVALID, "vout_window_get HI_UNF_VO_GetWindowAttr failed:%#x.\n", s32Ret);

    if (WinAttr.stWinAspectAttr.bUserDefAspectRatio)
    {
        if ((WinAttr.stWinAspectAttr.u32UserAspectHeight == USER_ASPECT_HEIGHT_RATIO_3)
            && (WinAttr.stWinAspectAttr.u32UserAspectWidth == USER_ASPECT_WIDTH_RATIO_4))
        {
            pstSettings->enAspectRatio = VOUT_ASPECT_RATIO_4TO3;
        }
        else if ((WinAttr.stWinAspectAttr.u32UserAspectHeight == USER_ASPECT_HEIGHT_RATIO_9)
                 && (WinAttr.stWinAspectAttr.u32UserAspectWidth == USER_ASPECT_WIDTH_RATIO_16))
        {
            pstSettings->enAspectRatio = VOUT_ASPECT_RATIO_16TO9;
        }
    }
    else
    {
        pstSettings->enAspectRatio = VOUT_ASPECT_RATIO_AUTO;
    }

    pstSettings->stWindowUserDefAspect.bUserDefAspectRatio = WinAttr.stWinAspectAttr.bUserDefAspectRatio;
    pstSettings->stWindowUserDefAspect.u32UserAspectHeight = WinAttr.stWinAspectAttr.u32UserAspectHeight;
    pstSettings->stWindowUserDefAspect.u32UserAspectWidth  = WinAttr.stWinAspectAttr.u32UserAspectWidth;
    pstSettings->enAspectRatioConv = convert_unf_window_aspect_cvrs(WinAttr.stWinAspectAttr.enAspectCvrs);
    pstSettings->bVirtual = WinAttr.bVirtual;

    /* CNcomment:获取u8Bbrightness/u8Contrast/u8Saturation 范围 [0,100] */
    s32Ret = HI_UNF_PQ_GetBrightness(HI_UNF_DISPLAY1, &u32Brightness);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_GetBrightness failed. ret(0x%08x)", s32Ret);

    pstSettings->u8Brightness = (U8)u32Brightness;

    s32Ret = HI_UNF_PQ_GetContrast(HI_UNF_DISPLAY1, &u32Contrast);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_GetContrast failed. ret(0x%08x)", s32Ret);

    pstSettings->u8Contrast = (U8)u32Contrast;

    s32Ret = HI_UNF_PQ_GetSaturation(HI_UNF_DISPLAY1, &u32Saturation);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_DISPLAY_OP_FAILED, "HI_UNF_PQ_GetSaturation failed. ret(0x%08x)", s32Ret);

    pstSettings->u8Saturation = (U8)u32Saturation;

    return s32Ret;
}

/**
 * CNcomment:设置视频输入窗口的大小
 */
S32 vout_window_set_input_rect(struct _VOUT_DEVICE_S* pstVoutDev,
                               const HANDLE hVoutWindow,
                               AV_COORD_T u32Left,
                               AV_COORD_T u32Top,
                               U32 u32Width,
                               U32 u32Height)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_WINDOW_ATTR_S stWinAttr;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    memset(&stWinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));
    s32Ret = HI_UNF_VO_GetWindowAttr(hVoutWindow, &stWinAttr);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set HI_UNF_VO_GetWindowAttr failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    stWinAttr.bUseCropRect          = HI_FALSE;
    stWinAttr.stInputRect.s32X      = u32Left;
    stWinAttr.stInputRect.s32Y      = u32Top;
    stWinAttr.stInputRect.s32Width  = u32Width;
    stWinAttr.stInputRect.s32Height = u32Height;

    s32Ret = HI_UNF_VO_SetWindowAttr(hVoutWindow, &stWinAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set HI_UNF_VO_SetWindowAttr failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

/**
 * CNcomment:获取输入窗口的大小
 */
S32 vout_window_get_input_rect(struct _VOUT_DEVICE_S* pstVoutDev,
                               const HANDLE hVoutWindow,
                               AV_COORD_T* const pu32Left,
                               AV_COORD_T* const pu32Top,
                               U32* const pu32Width,
                               U32* const pu32Height)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_WINDOW_ATTR_S stWinAttr;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (   (NULL == pu32Left)
        || (NULL == pu32Top)
        || (NULL == pu32Width)
        || (NULL == pu32Height))
    {
        HAL_ERROR("prar is err ,ptr NULL!!\n");
        return ERROR_NULL_PTR;
    }

    memset(&stWinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));

    s32Ret = HI_UNF_VO_GetWindowAttr(hVoutWindow, &stWinAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set HI_UNF_VO_GetWindowAttr failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    *pu32Left   = stWinAttr.stInputRect.s32X;
    *pu32Top    = stWinAttr.stInputRect.s32Y;
    *pu32Width  = stWinAttr.stInputRect.s32Width;
    *pu32Height = stWinAttr.stInputRect.s32Height;

    return SUCCESS;
}

/**
 * CNcomment:设置输出窗口的大小
 */
S32 vout_window_set_output_rect(struct _VOUT_DEVICE_S* pstVoutDev,
                                const HANDLE hVoutWindow,
                                AV_COORD_T u32Left,
                                AV_COORD_T u32Top,
                                U32 u32Width,
                                U32 u32Height)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_WINDOW_ATTR_S stWinAttr;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    memset(&stWinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));
    s32Ret = HI_UNF_VO_GetWindowAttr(hVoutWindow, &stWinAttr);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set HI_UNF_VO_GetWindowAttr failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    stWinAttr.stOutputRect.s32X      = u32Left;
    stWinAttr.stOutputRect.s32Y      = u32Top;
    stWinAttr.stOutputRect.s32Width  = u32Width;
    stWinAttr.stOutputRect.s32Height = u32Height;
    s32Ret = HI_UNF_VO_SetWindowAttr(hVoutWindow, &stWinAttr);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set HI_UNF_VO_SetWindowAttr failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

/**
 * CNcomment:获取视频输出窗口的大小
 */
S32 vout_window_get_output_rect(struct _VOUT_DEVICE_S* pstVoutDev,
                                const HANDLE hVoutWindow,
                                AV_COORD_T* const pu32Left,
                                AV_COORD_T* const pu32Top,
                                U32* const pu32Width,
                                U32* const pu32Height)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_WINDOW_ATTR_S stWinAttr;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }


    if (   (NULL == pu32Left)
        || (NULL == pu32Top)
        || (NULL == pu32Width)
        || (NULL == pu32Height))
    {
        HAL_ERROR("prar is err ,ptr NULL!!\n");
        return ERROR_NULL_PTR;
    }

    memset(&stWinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));
    s32Ret = HI_UNF_VO_GetWindowAttr(hVoutWindow, &stWinAttr);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set HI_UNF_VO_GetWindowAttr failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    *pu32Left   = stWinAttr.stOutputRect.s32X;
    *pu32Top    = stWinAttr.stOutputRect.s32Y;
    *pu32Width  = stWinAttr.stOutputRect.s32Width;
    *pu32Height = stWinAttr.stOutputRect.s32Height;

    return SUCCESS;
}

/*
 * CNcomment:获取视频窗口状态
 */
S32 vout_window_get_status(struct _VOUT_DEVICE_S* pstVoutDev,
                           const HANDLE hVoutWindow,
                           VOUT_WINDOW_STATUS_S* const  pstStatus)
{
    S32  s32Ret = SUCCESS;
    U32  u32OrgZorder;
    HI_BOOL bEnable = HI_TRUE;

    if (!hVoutWindow)
    {
        HAL_ERROR(" vout_window_get_status Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (NULL == pstStatus)
    {
        HAL_ERROR("prar is err ,ptr NULL!!\n");
        return ERROR_NULL_PTR;
    }

    s32Ret = HI_UNF_VO_GetWindowEnable(hVoutWindow, &bEnable);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_VO_GetWindowEnable failed:%#x.\n", s32Ret);
        return FAILURE;
    }

    s32Ret = HI_UNF_VO_GetWindowZorder(hVoutWindow, &u32OrgZorder);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_VO_GetWindowZorder failed:%#x.\n", s32Ret);
        return FAILURE;
    }

    pstStatus->u8WinEnableStatus = bEnable;
    pstStatus->bWindowEnableMute = bEnable;
    pstStatus->u32ZOrderIndex = u32OrgZorder;

    /*not support get mute color/ color temperature /u8WindowConnected*/

    return SUCCESS;
}

/*
 * CNcomment:暂停视频
 */
S32 vout_window_freeze(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow)
{
    S32 s32Ret = SUCCESS;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    s32Ret = HI_UNF_VO_FreezeWindow(hVoutWindow, HI_TRUE, HI_UNF_WINDOW_FREEZE_MODE_LAST);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_freeze vout_window_freeze failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}
/*
 * CNcomment:恢复视频播放
 */
S32 vout_window_unfreeze(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow)
{
    S32 s32Ret = SUCCESS;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    s32Ret = HI_UNF_VO_FreezeWindow(hVoutWindow, HI_FALSE, HI_UNF_WINDOW_FREEZE_MODE_LAST);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_unfreeze HI_UNF_VO_FreezeWindow failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}
/*
 * CNcomment:关闭窗口输出
 */
S32 vout_window_mute(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow)
{
    if (!hVoutWindow)
    {
        HAL_ERROR("Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (SUCCESS != HI_UNF_VO_SetWindowEnable(hVoutWindow, HI_FALSE))
    {
        HAL_ERROR("vout_window_mute failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}
/*
 * CNcomment:打开窗口输出
 */
S32 vout_window_unmute(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow)
{
    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_attach_input Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (SUCCESS != HI_UNF_VO_SetWindowEnable(hVoutWindow, HI_TRUE))
    {
        HAL_ERROR("vout_window_unmute failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

/*
 * CNcomment:将窗口与视频源绑定
 */
S32 vout_window_attach_input(struct _VOUT_DEVICE_S* pstVoutDev,
                             const HANDLE hVoutWindow,
                             const HANDLE hSource)
{
    HANDLE hAvPlayer;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_attach_input Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (SUCCESS != av_get_sdk_avplay_hdl(hSource, &hAvPlayer))
    {
        return ERROR_VO_PARAMETER_INVALID;
    }

    /* attach window fail not return failure for DPT and STB will use same process */
    if (SUCCESS != HI_UNF_VO_AttachWindow(hVoutWindow, hAvPlayer))
    {
        HAL_ERROR("vout_window_attach_input HI_UNF_VO_AttachWindow failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);
        return FAILURE;
    }

    return SUCCESS;
}

/*
 *CNcomment: 将窗口与视频源解绑定
 */
S32 vout_window_detach_input(struct _VOUT_DEVICE_S* pstVoutDev,
                             const HANDLE hVoutWindow,
                             const HANDLE hSource)
{
    HANDLE hAvPlayer;

    if (!hVoutWindow)
    {
        HAL_ERROR("Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (SUCCESS != av_get_sdk_avplay_hdl(hSource, &hAvPlayer))
    {
        return ERROR_VO_PARAMETER_INVALID;
    }

    /* detach window fail not return failure for DPT and STB will use same process */
    if (SUCCESS != HI_UNF_VO_DetachWindow(hVoutWindow, hAvPlayer))
    {
        HAL_ERROR("vout_window_detach_input HI_UNF_VO_DetachWindow failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);
        return FAILURE;
    }

    return SUCCESS;
}

/*
 * CNcomment:设置窗口的色温
 */
S32 vout_window_set_colortemperature(struct _VOUT_DEVICE_S* pstVoutDev,
                                     const HANDLE hVoutWindow,
                                     VOUT_WINDOW_COLOR_TEMPERATURE_S* pstColorTemperature)
{
    return ERROR_NOT_SUPPORTED;
}

/*
 * CNcomment:设置窗口的上下顺序
 */
S32 vout_window_set_zorder(struct _VOUT_DEVICE_S* pstVoutDev,
                           const HANDLE hVoutWindow,
                           U32 u32ZOrderIndex)
{
    S32 s32Ret = SUCCESS;
    U32 u32OrgZorder = 0;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set_zorder Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    s32Ret = HI_UNF_VO_GetWindowZorder(hVoutWindow, &u32OrgZorder);
    if (u32OrgZorder == u32ZOrderIndex)
    {
        return s32Ret;
    }

    s32Ret = HI_UNF_VO_SetWindowZorder(hVoutWindow, (HI_LAYER_ZORDER_E)u32ZOrderIndex);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set_zorder HI_UNF_VO_SetWindowZorder failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return s32Ret;
}

struct _VIDEO_FORMAT
{
    VOUT_VIDEO_FORMAT_E   enVoutVideoFormat;
    HI_UNF_VIDEO_FORMAT_E enHiVideoFormat;
} g_stVideoFormat[] =
{
    {VOUT_FORMAT_YUV_SEMIPLANAR_422,     HI_UNF_FORMAT_YUV_SEMIPLANAR_422},
    {VOUT_FORMAT_YUV_SEMIPLANAR_420,     HI_UNF_FORMAT_YUV_SEMIPLANAR_420},
    {VOUT_FORMAT_YUV_SEMIPLANAR_400,     HI_UNF_FORMAT_YUV_SEMIPLANAR_400},
    {VOUT_FORMAT_YUV_SEMIPLANAR_411,     HI_UNF_FORMAT_YUV_SEMIPLANAR_411},
    {VOUT_FORMAT_YUV_SEMIPLANAR_422_1X2, HI_UNF_FORMAT_YUV_SEMIPLANAR_422_1X2},
    {VOUT_FORMAT_YUV_SEMIPLANAR_444,     HI_UNF_FORMAT_YUV_SEMIPLANAR_444},
    {VOUT_FORMAT_YUV_SEMIPLANAR_420_UV,  HI_UNF_FORMAT_YUV_SEMIPLANAR_420_UV},
    {VOUT_FORMAT_YUV_PACKAGE_UYVY,       HI_UNF_FORMAT_YUV_PACKAGE_UYVY},
    {VOUT_FORMAT_YUV_PACKAGE_YUYV,       HI_UNF_FORMAT_YUV_PACKAGE_YUYV},
    {VOUT_FORMAT_YUV_PACKAGE_YVYU,       HI_UNF_FORMAT_YUV_PACKAGE_YVYU},
    {VOUT_FORMAT_YUV_PLANAR_400,         HI_UNF_FORMAT_YUV_PLANAR_400},
    {VOUT_FORMAT_YUV_PLANAR_411,         HI_UNF_FORMAT_YUV_PLANAR_411},
    {VOUT_FORMAT_YUV_PLANAR_420,         HI_UNF_FORMAT_YUV_PLANAR_420},
    {VOUT_FORMAT_YUV_PLANAR_422_1X2,     HI_UNF_FORMAT_YUV_PLANAR_422_1X2},
    {VOUT_FORMAT_YUV_PLANAR_422_2X1,     HI_UNF_FORMAT_YUV_PLANAR_422_2X1},
    {VOUT_FORMAT_YUV_PLANAR_444,         HI_UNF_FORMAT_YUV_PLANAR_444},
    {VOUT_FORMAT_YUV_PLANAR_410,         HI_UNF_FORMAT_YUV_PLANAR_410},
    {VOUT_FORMAT_YUV_BUTT,               HI_UNF_FORMAT_YUV_BUTT},
    {VOUT_FORMAT_RGB_SEMIPLANAR_444,     HI_UNF_FORMAT_RGB_SEMIPLANAR_444},
    {VOUT_FORMAT_RGB_BUTT,               HI_UNF_FORMAT_RGB_BUTT},
};

HI_UNF_VIDEO_FORMAT_E convert_vout_video_format_to_unf(VOUT_VIDEO_FORMAT_E enVideoFormat)
{
    U32 i = 0;

    for (i = 0; i < (sizeof(g_stVideoFormat) / sizeof(g_stVideoFormat[0])); i++)
    {
        if (g_stVideoFormat[i].enVoutVideoFormat == enVideoFormat )
        {
            return g_stVideoFormat[i].enHiVideoFormat;
        }
    }

    HAL_ERROR("convert_vout_videoformat_to_unf failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);

    return HI_UNF_FORMAT_YUV_SEMIPLANAR_420;
}

VOUT_VIDEO_FORMAT_E convert_unf_video_format_to_vout(HI_UNF_VIDEO_FORMAT_E enVideoFormat)
{
    U32 i = 0;

    for (i = 0; i < (sizeof(g_stVideoFormat) / sizeof(g_stVideoFormat[0])); i++)
    {
        if (g_stVideoFormat[i].enHiVideoFormat == enVideoFormat )
        {
            return g_stVideoFormat[i].enVoutVideoFormat;
        }
    }

    HAL_ERROR("convert_unf_videoformat_to_vout failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);

    return VOUT_FORMAT_YUV_SEMIPLANAR_420;
}

struct _VIDEO_FIELD_MODE
{
    VOUT_VIDEO_FIELD_MODE_E   enVoutVideoFieldMode;
    HI_UNF_VIDEO_FIELD_MODE_E enHiVideoFieldMode;
} g_stVideoFieldMode[] = {{VOUT_VIDEO_FIELD_ALL, HI_UNF_VIDEO_FIELD_ALL},
    {VOUT_VIDEO_FIELD_TOP,    HI_UNF_VIDEO_FIELD_TOP},
    {VOUT_VIDEO_FIELD_BOTTOM, HI_UNF_VIDEO_FIELD_BOTTOM},
    {VOUT_VIDEO_FIELD_BUTT,   HI_UNF_VIDEO_FIELD_BUTT},
};

HI_UNF_VIDEO_FIELD_MODE_E convert_vout_video_mode_to_unf(VOUT_VIDEO_FIELD_MODE_E enVideoMode)
{
    U32 i = 0;

    for (i = 0; i < (sizeof(g_stVideoFieldMode) / sizeof(g_stVideoFieldMode[0])); i++)
    {
        if (g_stVideoFieldMode[i].enVoutVideoFieldMode == enVideoMode )
        {
            return g_stVideoFieldMode[i].enHiVideoFieldMode;
        }
    }

    HAL_ERROR("convert_vout_video_mode_to_unf failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);

    return HI_UNF_VIDEO_FIELD_ALL;
}

VOUT_VIDEO_FIELD_MODE_E convert_unf_video_mode_to_vout(HI_UNF_VIDEO_FIELD_MODE_E enVideoMode)
{
    U32 i = 0;

    for (i = 0; i < (sizeof(g_stVideoFieldMode) / sizeof(g_stVideoFieldMode[0])); i++)
    {
        if (g_stVideoFieldMode[i].enHiVideoFieldMode == enVideoMode )
        {
            return g_stVideoFieldMode[i].enVoutVideoFieldMode;
        }
    }

    HAL_ERROR("convert_unf_video_fmode_to_vout failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);

    return VOUT_VIDEO_FIELD_ALL;
}

struct _VIDEO_FRAME_PACKING_TYPE
{
    VOUT_VIDEO_FRAME_PACKING_TYPE_E   enVoutVideoFramePackingType;
    HI_UNF_VIDEO_FRAME_PACKING_TYPE_E enHiVideoFramePackingType;
} g_stVideoFramePackingType[] =
{
    {VOUT_FRAME_PACKING_TYPE_NONE,            HI_UNF_FRAME_PACKING_TYPE_NONE},
    {VOUT_FRAME_PACKING_TYPE_SIDE_BY_SIDE,    HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE},
    {VOUT_FRAME_PACKING_TYPE_TOP_AND_BOTTOM,  HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM},
    {VOUT_FRAME_PACKING_TYPE_TIME_INTERLACED, HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED},
    {VOUT_FRAME_PACKING_TYPE_FRAME_PACKING,   HI_UNF_FRAME_PACKING_TYPE_FRAME_PACKING},
    {VOUT_FRAME_PACKING_TYPE_3D_TILE,         HI_UNF_FRAME_PACKING_TYPE_3D_TILE},
    {VOUT_FRAME_PACKING_TYPE_BUTT,            HI_UNF_FRAME_PACKING_TYPE_BUTT},
};

HI_UNF_VIDEO_FRAME_PACKING_TYPE_E convert_vout_video_frame_to_unf(VOUT_VIDEO_FRAME_PACKING_TYPE_E enVideoFramePackingType)
{
    U32 i = 0;

    for (i = 0; i < (sizeof(g_stVideoFramePackingType) / sizeof(g_stVideoFramePackingType[0])); i++)
    {
        if (g_stVideoFramePackingType[i].enVoutVideoFramePackingType == enVideoFramePackingType)
        {
            return g_stVideoFramePackingType[i].enHiVideoFramePackingType;
        }
    }

    HAL_ERROR("convert_vout_video_frame_to_unf failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);

    return HI_UNF_FRAME_PACKING_TYPE_NONE;
}

VOUT_VIDEO_FRAME_PACKING_TYPE_E convert_unf_video_frame_to_vout(HI_UNF_VIDEO_FRAME_PACKING_TYPE_E enVideoFramePackingType)
{
    U32 i = 0;

    for (i = 0; i < (sizeof(g_stVideoFramePackingType) / sizeof(g_stVideoFramePackingType[0])); i++)
    {
        if (g_stVideoFramePackingType[i].enHiVideoFramePackingType == enVideoFramePackingType)
        {
            return g_stVideoFramePackingType[i].enVoutVideoFramePackingType;
        }
    }

    HAL_ERROR("convert_unf_video_frame_to_vout failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);

    return VOUT_FRAME_PACKING_TYPE_NONE;
}

/* 1080p video process data to vo */
void vout_normal_queue_frame(HI_UNF_VIDEO_FRAME_INFO_S* stFrameinfo, VOUT_FRAME_INFO_S *pstFrameInfo)
{
    stFrameinfo->u32FrameIndex = pstFrameInfo->u32FrameIndex;
    memcpy(&stFrameinfo->stVideoFrameAddr[0], &pstFrameInfo->stVideoFrameAddr[0], sizeof(VOUT_FRAME_ADDR_S));
    memcpy(&stFrameinfo->stVideoFrameAddr[1], &pstFrameInfo->stVideoFrameAddr[1], sizeof(VOUT_FRAME_ADDR_S));

    stFrameinfo->u32Width                    = pstFrameInfo->u32Width;
    stFrameinfo->u32Height                   = pstFrameInfo->u32Height;
    stFrameinfo->u32SrcPts                   = (U32)pstFrameInfo->s64SrcPts;
    stFrameinfo->u32Pts                      = (U32)pstFrameInfo->s64Pts;
    stFrameinfo->u32AspectWidth              = pstFrameInfo->u32AspectWidth;
    stFrameinfo->u32AspectHeight             = pstFrameInfo->u32AspectHeight;
    stFrameinfo->stFrameRate.u32fpsDecimal   = pstFrameInfo->stFrameRate.u32fpsDecimal;
    stFrameinfo->stFrameRate.u32fpsInteger   = pstFrameInfo->stFrameRate.u32fpsInteger;
    stFrameinfo->enVideoFormat               = convert_vout_video_format_to_unf(pstFrameInfo->enVideoFormat);
    stFrameinfo->bProgressive                = (HI_BOOL)pstFrameInfo->bProgressive;
    stFrameinfo->enFieldMode                 = convert_vout_video_mode_to_unf(pstFrameInfo->enFieldMode);
    stFrameinfo->bTopFieldFirst              = (HI_BOOL)pstFrameInfo->bTopFieldFirst;
    stFrameinfo->enFramePackingType          = convert_vout_video_frame_to_unf(pstFrameInfo->enFramePackingType);
    stFrameinfo->u32Circumrotate             = pstFrameInfo->u32Circumrotate;
    stFrameinfo->bVerticalMirror             = (HI_BOOL)pstFrameInfo->bVerticalMirror;
    stFrameinfo->bHorizontalMirror           = (HI_BOOL)pstFrameInfo->bHorizontalMirror;
    stFrameinfo->u32DisplayWidth             = pstFrameInfo->u32DisplayWidth;
    stFrameinfo->u32DisplayHeight            = pstFrameInfo->u32DisplayHeight;
    stFrameinfo->u32DisplayCenterX           = pstFrameInfo->u32DisplayCenterX;
    stFrameinfo->u32DisplayCenterY           = pstFrameInfo->u32DisplayCenterY;
    stFrameinfo->u32ErrorLevel               = pstFrameInfo->u32ErrorLevel;
    memcpy(&stFrameinfo->u32Private, &pstFrameInfo->u32Private, (sizeof(U32) * 32));

    /* securty flag, if u32Private[0] == 1, this is a secure frame */
    stFrameinfo->u32Private[0] = (HI_U32)pstFrameInfo->bSecurityFrame;

    return;
}

#ifdef HI_4K_BYPASS
HI_VOID* vout_trans_phy_to_virtual(HI_U32 u32PhysAddr)
{
    HI_VOID *VirAddr = NULL;

    if (0 == u32PhysAddr)
    {
        HAL_ERROR("vout vout_trans_phy_to_virtual have wrong phyAddr 0");
        return NULL;
    }

    VirAddr = HI_MMZ_Map(u32PhysAddr, 0);

    return VirAddr;
}
HI_U32 vout_trans_virtual_to_phy(HI_VOID* VirAddr)
{
    HI_U32 u32PhyAddr = 0;
    HI_U32 u32Size = 0;
    HI_S32 s32Ret = SUCCESS;

    if (NULL == VirAddr)
    {
        HAL_ERROR("vout vout_trans_virtual_to_phy have wrong u32VirAddr NULL");
        return 0;
    }

    s32Ret = HI_MMZ_GetPhyaddr(VirAddr, &u32PhyAddr, &u32Size);
    if (s32Ret != HI_SUCCESS)
    {
        HAL_ERROR("vout vout_trans_virtual_to_phy fail u32VirAddr=0x%p,u32PhyAddr:%#x, u32Size:%#x", VirAddr, u32PhyAddr, u32Size);
        return 0;
    }

    return u32PhyAddr;
}

/* global array ro remember queue phyaddr for 4k_vidoe */
#define MAX_4K_PHY_ADDR 10

struct SHi4kPhyAddr
{
    U32 u32PhyAddr;
    U32 u32PhyAddr_Y;
    U32 isGlobalFree;//0 :need not to GlobalFree; 1 :should GlobalFree
};

static struct SHi4kPhyAddr gs_Queue4kPhyAddr[MAX_4K_PHY_ADDR]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

/**need global free flag, when 4K->1080P, or H264 4K<-> H265 4K  */
static void vout_4k_mark_global_free_flag()
{
    int i = 0;
    VOUT_FRAME_LOCK();
    for(i = 0 ; i < MAX_4K_PHY_ADDR ; i++)
    {
        if ((0 != gs_Queue4kPhyAddr[i].u32PhyAddr) && (0 != gs_Queue4kPhyAddr[i].u32PhyAddr_Y))
        {
            gs_Queue4kPhyAddr[i].isGlobalFree = 1;
        }
    }
    VOUT_FRAME_UNLOCK();
}

#if 0
/* 4K->1080p stage free not dequeue frame */
static U32 vout_4k_dequeue_free_frame(U32 u32PhyAddr_Y)
{
    S32 s32Ret = HI_FAILURE;
    U32 i = 0;
    for (i = 0; i < MAX_4K_PHY_ADDR; i++)
    {
        if (0 != gs_Queue4kPhyAddr[i].u32PhyAddr&&gs_Queue4kPhyAddr[i].u32PhyAddr_Y==u32PhyAddr_Y)
        {
            s32Ret = HI_MPI_VDEC_GlobalRelFrm((HI_DRV_VIDEO_FRAME_S *)vout_trans_phy_to_virtual(gs_Queue4kPhyAddr[i].u32PhyAddr));
            if (HI_SUCCESS != s32Ret)
            {
                HAL_ERROR("vout_4k_dequeue_free_frame failed index=%d s32Ret=%d ", i, s32Ret);
                continue;
            }
            HAL_ERROR("vout_4k_dequeue_free_frame success u32PhyAddr_Y=0x%x u32PhyAddr=%d ", u32PhyAddr_Y, gs_Queue4kPhyAddr[i].u32PhyAddr);
            /* free virtual address */
            HI_MMZ_Unmap(gs_Queue4kPhyAddr[i].u32PhyAddr);
            gs_Queue4kPhyAddr[i].u32PhyAddr=0;
            gs_Queue4kPhyAddr[i].u32PhyAddr_Y=0;
           return u32PhyAddr_Y;
        }
    }
    return 0;
}
#endif

/* drv frame_type to vo frame type */
HI_UNF_VIDEO_FRAME_PACKING_TYPE_E vout_trans_frm_type(HI_DRV_FRAME_TYPE_E eFrmType)
{
    HI_UNF_VIDEO_FRAME_PACKING_TYPE_E unfVideoFramePT = HI_UNF_FRAME_PACKING_TYPE_NONE;

    switch (eFrmType)
    {
        case HI_DRV_FT_NOT_STEREO:
            unfVideoFramePT = HI_UNF_FRAME_PACKING_TYPE_NONE;
        break;
        case HI_DRV_FT_SBS:
            unfVideoFramePT = HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE;
        break;
        case HI_DRV_FT_TAB:
            unfVideoFramePT = HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM;
        break;
        case HI_DRV_FT_FPK:
            unfVideoFramePT = HI_UNF_FRAME_PACKING_TYPE_FRAME_PACKING;
        break;
        case HI_DRV_FT_TILE:
            unfVideoFramePT = HI_UNF_FRAME_PACKING_TYPE_3D_TILE;
        break;
        case HI_DRV_FT_BUTT:
            unfVideoFramePT = HI_UNF_FRAME_PACKING_TYPE_BUTT;
        break;
        default:
            HAL_ERROR("vout_trans_frm_type have wrong unfVideoFramePT=%d ", unfVideoFramePT);
    }

    return unfVideoFramePT;
}

HI_UNF_VIDEO_FIELD_MODE_E vout_trans_fieldmode_type(HI_DRV_FIELD_MODE_E eFileMode)
{
    HI_UNF_VIDEO_FIELD_MODE_E unfFileMode = HI_UNF_VIDEO_FIELD_BUTT;
    switch (eFileMode)
    {
        case HI_DRV_FIELD_TOP:
            unfFileMode = HI_UNF_VIDEO_FIELD_TOP;
        break;
        case HI_DRV_FIELD_BOTTOM:
            unfFileMode = HI_UNF_VIDEO_FIELD_BOTTOM;
        break;
        case HI_DRV_FIELD_ALL:
            unfFileMode = HI_UNF_VIDEO_FIELD_ALL;
        break;
        default:
            HAL_ERROR("vout_trans_fieldmode_type have wrong unfFileMode=%d ", unfFileMode);
    }
    return unfFileMode;
}

/* when 4K video process DRV_VIDEO_FRAME to vo */
void vout_4k_queue_frame(HI_UNF_VIDEO_FRAME_INFO_S* pstFrameinfo, HI_DRV_VIDEO_FRAME_S *pstVideoFrame)
{
    pstFrameinfo->stVideoFrameAddr[0].u32YAddr     = pstVideoFrame->stBufAddr[0].u32PhyAddr_Y;
    pstFrameinfo->stVideoFrameAddr[0].u32CAddr     = pstVideoFrame->stBufAddr[0].u32PhyAddr_C;
    pstFrameinfo->stVideoFrameAddr[0].u32CrAddr    = pstVideoFrame->stBufAddr[0].u32PhyAddr_Cr;
    pstFrameinfo->stVideoFrameAddr[0].u32YStride   = pstVideoFrame->stBufAddr[0].u32Stride_Y;
    pstFrameinfo->stVideoFrameAddr[0].u32CStride   = pstVideoFrame->stBufAddr[0].u32Stride_C;
    pstFrameinfo->stVideoFrameAddr[0].u32CrStride  = pstVideoFrame->stBufAddr[0].u32Stride_Cr;

    pstFrameinfo->stVideoFrameAddr[1].u32YAddr     = pstVideoFrame->stBufAddr[1].u32PhyAddr_Y;
    pstFrameinfo->stVideoFrameAddr[1].u32CAddr     = pstVideoFrame->stBufAddr[1].u32PhyAddr_C;
    pstFrameinfo->stVideoFrameAddr[1].u32CrAddr    = pstVideoFrame->stBufAddr[1].u32PhyAddr_Cr;
    pstFrameinfo->stVideoFrameAddr[1].u32YStride   = pstVideoFrame->stBufAddr[1].u32Stride_Y;
    pstFrameinfo->stVideoFrameAddr[1].u32CStride   = pstVideoFrame->stBufAddr[1].u32Stride_C;
    pstFrameinfo->stVideoFrameAddr[1].u32CrStride  = pstVideoFrame->stBufAddr[1].u32Stride_Cr;


    pstFrameinfo->u32Width  = pstVideoFrame->u32Width;
    pstFrameinfo->u32Height = pstVideoFrame->u32Height;
    pstFrameinfo->u32SrcPts = pstVideoFrame->u32SrcPts;
    pstFrameinfo->u32Pts    = pstVideoFrame->u32Pts;
    pstFrameinfo->u32AspectWidth            = pstVideoFrame->u32AspectWidth;
    pstFrameinfo->u32AspectHeight           = pstVideoFrame->u32AspectHeight;
    pstFrameinfo->stFrameRate.u32fpsDecimal    = pstVideoFrame->u32FrameRate % 1000;
    pstFrameinfo->stFrameRate.u32fpsInteger    = pstVideoFrame->u32FrameRate / 1000;
    pstFrameinfo->u32FrameIndex = pstVideoFrame->u32FrameIndex;
    //pstFrameinfo->enVideoFormat = HI_UNF_FORMAT_YUV_TILE_420_CMP;
    /*  HI_DRV_PIX_FMT_NV12 Y/CbCr 4:2:0  */
    /*  HI_DRV_PIX_FMT_NV21 Y/CrCb 4:2:0  */
    if (HI_DRV_PIX_FMT_NV21_TILE == pstVideoFrame->ePixFormat)
    {
        pstFrameinfo->enVideoFormat = HI_UNF_FORMAT_YUV_TILE_420;
    }
    else if (HI_DRV_PIX_FMT_NV12_TILE == pstVideoFrame->ePixFormat)
    {
        pstFrameinfo->enVideoFormat = HI_UNF_FORMAT_YUV_TILE_420_UV;
    }
    else if (HI_DRV_PIX_FMT_YUV410p == pstVideoFrame->ePixFormat)
    {
        pstFrameinfo->enVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_410;
    }
    else if (HI_DRV_PIX_FMT_NV21_TILE_CMP == pstVideoFrame->ePixFormat)
    {
        //pstFrameinfo->enVideoFormat = HI_UNF_FORMAT_YUV_TILE_420_CMP;
    }
    else if (HI_DRV_PIX_FMT_NV12_TILE_CMP == pstVideoFrame->ePixFormat)
    {
         //pstFrameinfo->enVideoFormat = HI_UNF_FORMAT_YUV_TILE_420_UV_CMP;
    }
    else
    {
        HAL_ERROR("vout_4k_queue_frame have wrong enVideoFormat=%d ", pstVideoFrame->ePixFormat);
    }

    pstFrameinfo->bProgressive              = pstVideoFrame->bProgressive;
    pstFrameinfo->enFieldMode               = vout_trans_fieldmode_type(pstVideoFrame->enFieldMode);
    pstFrameinfo->bTopFieldFirst            = pstVideoFrame->bTopFieldFirst;
    pstFrameinfo->enFramePackingType        = vout_trans_frm_type(pstVideoFrame->eFrmType);
    pstFrameinfo->u32Circumrotate           = pstVideoFrame->u32Circumrotate;
    pstFrameinfo->bVerticalMirror           = pstVideoFrame->bToFlip_V;
    pstFrameinfo->bHorizontalMirror         = pstVideoFrame->bToFlip_H;
    pstFrameinfo->u32DisplayWidth           = pstVideoFrame->u32Width;
    pstFrameinfo->u32DisplayHeight          = pstVideoFrame->u32Height;
    pstFrameinfo->u32DisplayCenterX         = 0;
    pstFrameinfo->u32DisplayCenterY         = 0;
    pstFrameinfo->u32ErrorLevel             = pstVideoFrame->u32ErrorLevel;
    memcpy(&pstFrameinfo->u32Private, &pstVideoFrame->u32Priv, (sizeof(U32) * 64));
    /* securty flag, if u32Private[0] == 1, this is a secure frame */
    pstFrameinfo->u32Private[0] = (HI_U32)pstVideoFrame->bSecure;

    return;
}

static S32 vout_queue_4kframe_address(U32 u32PhyAddr_Y,U32 u32FrameIndex ,U32 u32PhyAddr)
{
    int i=0;
    VOUT_FRAME_LOCK();

    for(i = 0 ; i < MAX_4K_PHY_ADDR ; i++)
    {
        if ((0 == gs_Queue4kPhyAddr[i].u32PhyAddr)&&(gs_Queue4kPhyAddr[i].u32PhyAddr_Y==0))
        {
            gs_Queue4kPhyAddr[i].u32PhyAddr = u32PhyAddr;
            gs_Queue4kPhyAddr[i].u32PhyAddr_Y = u32PhyAddr_Y;

            VOUT_FRAME_UNLOCK();
            return 0;
        }
    }

    if(i>=MAX_4K_PHY_ADDR)
    {
        HAL_ERROR("vout_window_queue_frame have not array u32FrameIndex=%d phyAddr=0x%x\n",u32FrameIndex,u32PhyAddr);
        VOUT_FRAME_UNLOCK();
        return ERROR_VO_WIN_BUFQUE_FULL;
    }

    VOUT_FRAME_UNLOCK();
    return -1;
}

static U32 vout_dequeue_4kframe_address(U32 u32PhyAddr_Y,U32 u32FrameIndex, U32* pIsGlobalFree)
{
    S32 i = 0;
    U32 u32PhyAddr = 0;

    VOUT_FRAME_LOCK();

    for(i = 0 ; i < MAX_4K_PHY_ADDR ; i++)
    {
        if ((0 != gs_Queue4kPhyAddr[i].u32PhyAddr) && (gs_Queue4kPhyAddr[i].u32PhyAddr_Y ==u32PhyAddr_Y) )
        {
            u32PhyAddr = gs_Queue4kPhyAddr[i].u32PhyAddr;

            gs_Queue4kPhyAddr[i].u32PhyAddr_Y = 0;
            gs_Queue4kPhyAddr[i].u32PhyAddr   = 0;
            *pIsGlobalFree = gs_Queue4kPhyAddr[i].isGlobalFree;
            gs_Queue4kPhyAddr[i].isGlobalFree = 0;

            VOUT_FRAME_UNLOCK();
            return u32PhyAddr;
        }
    }

    if(i>=MAX_4K_PHY_ADDR)
    {
        HAL_ERROR("vout_dequeue_4kframe_address have not array u32FrameIndex=%d phyAddr=0x%x\n",u32FrameIndex,u32PhyAddr);
    }

    VOUT_FRAME_UNLOCK();
    return u32PhyAddr;
}
#endif

/* CNcomment:视频帧送显示 */
S32 vout_window_queue_frame(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_FRAME_INFO_S* pstFrameInfo)
{
    S32 s32Ret = SUCCESS;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_queue_frame Invalid vout handle!!\n");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (NULL == pstFrameInfo)
    {
        HAL_ERROR("vout_window_queue_frame Invalid pstFrameInfo!!\n");
        return ERROR_NULL_PTR;
    }

    if (0 == pstFrameInfo->stVideoFrameAddr[0].u32YAddr)
    {
        HAL_ERROR("vout_window_queue_frame u32YAddr is NULL!!\n");
        return ERROR_NULL_PTR;
    }

    HI_UNF_VIDEO_FRAME_INFO_S stFrameinfo = {0};

    VOUT_FRAME_LOCK();
    s_u32QueueWidth  = pstFrameInfo->u32Width;
    s_u32QueueHeight = pstFrameInfo->u32Height;
    VOUT_FRAME_UNLOCK();

    /* TVOS_FRAME_INFO to UNF_FRAME_INFO */
#ifdef HI_4K_BYPASS
    if ((pstFrameInfo->u32Width > VIDEO_WIDTH_1920) && (pstFrameInfo->u32Height > VIDEO_HEIGHT_1080))
    {
        HI_DRV_VIDEO_FRAME_S *pstDrvFrame = NULL;
        pstDrvFrame = (HI_DRV_VIDEO_FRAME_S*)vout_trans_phy_to_virtual(pstFrameInfo->stVideoFrameAddr[0].u32YAddr);
        if (NULL == pstDrvFrame)
        {
            HAL_ERROR("vout_window_queue_frame 4k have wrong virtual address 0\n");
            return FAILURE;
        }

        #ifdef HI_4K_BYPASS_FRC
        vout_queue_4kframe_address(pstDrvFrame->stBufAddr[0].u32PhyAddr_Y,pstDrvFrame->u32FrameIndex, pstFrameInfo->stVideoFrameAddr[0].u32YAddr);
        #endif

        /* free virtual address */
        HI_MMZ_Unmap(pstFrameInfo->stVideoFrameAddr[0].u32YAddr);

        s32Ret = HI_MPI_WIN_QueueFrame(hVoutWindow, pstDrvFrame);
        if(SUCCESS != s32Ret)
        {
            HAL_ERROR("VOUT HI_MPI_WIN_QueueFrame =====failed:%#x.\n", s32Ret);
            return s32Ret;
        }

        return s32Ret;
    }
    else
    {
        vout_normal_queue_frame(&stFrameinfo, pstFrameInfo);
    }
#else
    vout_normal_queue_frame(&stFrameinfo, pstFrameInfo);
#endif

    s32Ret = HI_UNF_VO_QueueFrame(hVoutWindow, &stFrameinfo);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_queue_frame failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

/* CNcomment:回收视频显示帧 */
S32 vout_window_dequeue_frame(struct _VOUT_DEVICE_S* pstVoutDev,
                              const HANDLE hVoutWindow,
                              VOUT_FRAME_INFO_S* pstFrameInfo,
                              U32 u32TimeOut)
{
    S32 s32Ret = SUCCESS;
#ifdef HI_4K_BYPASS
    U32 u32PhyAddr = 0;
    VOID *VirAddr = NULL;
    U32 IsGlobalFree = 0;
#endif
    HI_UNF_VIDEO_FRAME_INFO_S stFrameinfo = {0};

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_dequeue_frame Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (NULL == pstFrameInfo)
    {
        HAL_ERROR("vout_window_dequeue_frame Invalid pstFrameInfo!!.");
        return ERROR_NULL_PTR;
    }

    s32Ret = HI_UNF_VO_DeQueueFrame(hVoutWindow, &stFrameinfo, u32TimeOut);
    if(SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    /* UNF_FRAME_INFO to TVOS_FRAME_INFO */
    pstFrameInfo->u32FrameIndex = stFrameinfo.u32FrameIndex;
    memcpy(&pstFrameInfo->stVideoFrameAddr[0], &stFrameinfo.stVideoFrameAddr[0], sizeof(VOUT_FRAME_ADDR_S));
    memcpy(&pstFrameInfo->stVideoFrameAddr[1], &stFrameinfo.stVideoFrameAddr[1], sizeof(VOUT_FRAME_ADDR_S));

#ifdef HI_4K_BYPASS
    if ((stFrameinfo.u32Width > VIDEO_WIDTH_1920) && (stFrameinfo.u32Height > VIDEO_HEIGHT_1080))
    {
#ifdef HI_4K_BYPASS_FRC
        /*  gsm get dequeue phyaddress to free */
        u32PhyAddr = vout_dequeue_4kframe_address(pstFrameInfo->stVideoFrameAddr[0].u32YAddr,
                         pstFrameInfo->u32FrameIndex, &IsGlobalFree);
        if(u32PhyAddr != 0)
        {
            pstFrameInfo->stVideoFrameAddr[0].u32YAddr =u32PhyAddr;
        }
        else
        {
            return -1;
        }

        //  4k-> no-4k : global free last frame
        VOUT_FRAME_LOCK();
        if(!(stFrameinfo.u32Width == s_u32QueueWidth
            && stFrameinfo.u32Height == s_u32QueueHeight))
        {
            IsGlobalFree = 1;
        }
        //do global_free when resoulution_changed or detach be called
        if(IsGlobalFree)
        {
            VirAddr = vout_trans_phy_to_virtual(u32PhyAddr);
            if(NULL == VirAddr)
            {
                HAL_ERROR("vout_trans_phy_to_virtual failed, u32PhyAddr is %u", u32PhyAddr);
                VOUT_FRAME_UNLOCK();
                return -1;
            }

            s32Ret = HI_MPI_VDEC_GlobalRelFrm((HI_DRV_VIDEO_FRAME_S *)VirAddr);
            if (HI_SUCCESS != s32Ret)
            {
                HI_MMZ_Unmap(u32PhyAddr);
                HAL_ERROR("HI_MPI_VDEC_GlobalRelFrm failed s32Ret=%d phyaddr : 0x%x", s32Ret ,u32PhyAddr);
                VOUT_FRAME_UNLOCK();
                return -1;
            }

            HI_MMZ_Unmap(u32PhyAddr);
        }
        VOUT_FRAME_UNLOCK();
    #endif
    }
#endif

    pstFrameInfo->u32Width                  = stFrameinfo.u32Width;
    pstFrameInfo->u32Height                 = stFrameinfo.u32Height;
    pstFrameInfo->s64SrcPts                 = stFrameinfo.u32SrcPts;
    pstFrameInfo->s64Pts                    = stFrameinfo.u32Pts;
    pstFrameInfo->u32AspectWidth            = stFrameinfo.u32AspectWidth;
    pstFrameInfo->u32AspectHeight           = stFrameinfo.u32AspectHeight;
    pstFrameInfo->stFrameRate.u32fpsDecimal = stFrameinfo.stFrameRate.u32fpsDecimal;
    pstFrameInfo->stFrameRate.u32fpsInteger = stFrameinfo.stFrameRate.u32fpsInteger;
    pstFrameInfo->enVideoFormat             = convert_unf_video_format_to_vout(stFrameinfo.enVideoFormat);
    pstFrameInfo->bProgressive              = stFrameinfo.bProgressive;
    pstFrameInfo->enFieldMode               = convert_unf_video_mode_to_vout(stFrameinfo.enFieldMode);
    pstFrameInfo->bTopFieldFirst            = stFrameinfo.bTopFieldFirst;
    pstFrameInfo->enFramePackingType        = convert_unf_video_frame_to_vout(stFrameinfo.enFramePackingType);
    pstFrameInfo->u32Circumrotate           = stFrameinfo.u32Circumrotate;
    pstFrameInfo->bVerticalMirror           = stFrameinfo.bVerticalMirror;
    pstFrameInfo->bHorizontalMirror         = stFrameinfo.bHorizontalMirror;
    pstFrameInfo->u32DisplayWidth           = stFrameinfo.u32DisplayWidth;
    pstFrameInfo->u32DisplayHeight          = stFrameinfo.u32DisplayHeight;
    pstFrameInfo->u32DisplayCenterX         = stFrameinfo.u32DisplayCenterX;
    pstFrameInfo->u32DisplayCenterY         = stFrameinfo.u32DisplayCenterY;
    pstFrameInfo->u32ErrorLevel             = stFrameinfo.u32ErrorLevel;
    memcpy(&pstFrameInfo->u32Private, &stFrameinfo.u32Private, (sizeof(U32) * 32));

    return SUCCESS;
}

/* CNcomment:清空window中的缓冲，根据参数显示黑帧或最后一帧 */
S32 vout_window_reset(struct _VOUT_DEVICE_S* pstVoutDev,
                      const HANDLE hVoutWindow,
                      VOUT_WINDOW_SWITCH_MODE_E enWindowSwitchMode)
{
    HI_UNF_WINDOW_FREEZE_MODE_E enWinFreezeMode = (HI_UNF_WINDOW_FREEZE_MODE_E)enWindowSwitchMode;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set_zorder Invalid vout handle!!.");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (SUCCESS != HI_UNF_VO_ResetWindow(hVoutWindow, enWinFreezeMode))
    {
        HAL_ERROR("vout_window_reset failed:%#x.\n", ERROR_VO_PARAMETER_INVALID);
        return ERROR_VO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

/* CNcomment:获取窗口虚拟屏幕的宽高 */
S32 vout_window_get_virtual_size(struct _VOUT_DEVICE_S* pstVoutDev,
                                 const HANDLE hVoutWindow,
                                 U32* const uVirtualScreenW,
                                 U32* const uVirtualScreenH)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_WINDOW_ATTR_S WinAttr;
    U32 u32VirScrW = 0;
    U32 u32VirScrH = 0;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.\n");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if ((NULL == uVirtualScreenW) || (NULL == uVirtualScreenH))
    {
        HAL_ERROR("vout_window_get_virtual_size null param!!.\n");
        return ERROR_NULL_PTR;
    }

    memset(&WinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));

    s32Ret = HI_UNF_VO_GetWindowAttr(hVoutWindow, &WinAttr);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_set HI_UNF_VO_GetWindowAttr failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_DISP_GetVirtualScreen(WinAttr.enDisp, &u32VirScrW, &u32VirScrH);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("Get Virtual Screen W&H is %d, %d, failed:%#x.\n", u32VirScrW, u32VirScrH, s32Ret);
        return ERROR_VO_PARAMETER_INVALID;;
    }

    *uVirtualScreenW = u32VirScrW;
    *uVirtualScreenH = u32VirScrH;

    return SUCCESS;
}
/* CNcomment:获取窗口信息                                    */
/* CNcomment: u32DelayTime        当前最新一帧还有多久会显示 */
/* CNcomment: u32DispRate         显示帧率                   */
/* CNcomment: u32FrameNumInBufQn  window队列里有几帧         */
S32 vout_window_get_playinfo(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                             U32* const u32DelayTime, U32* const u32DispRate, U32* const u32FrameNumInBufQn)
{
    S32 s32Ret = SUCCESS;
    HI_DRV_WIN_PLAY_INFO_S stInfo;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_set Invalid vout handle!!.\n");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if ((NULL == u32DelayTime) || (NULL == u32DispRate) || (NULL == u32FrameNumInBufQn))
    {
        HAL_ERROR("vout_window_get_playinfo null param!!.\n");
        return ERROR_NULL_PTR;
    }

    memset(&stInfo, 0, sizeof(HI_DRV_WIN_PLAY_INFO_S));

    s32Ret = HI_MPI_WIN_GetPlayInfo(hVoutWindow, &stInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("vout_window_get_playinfo failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;;
    }

    *u32DelayTime       = stInfo.u32DelayTime;
    *u32DispRate        = stInfo.u32DispRate;
    *u32FrameNumInBufQn = stInfo.u32FrameNumInBufQn;

    return SUCCESS;

}

S32 vout_window_set_quick_output_mode(struct _VOUT_DEVICE_S* pstVoutDev,
                             const HANDLE hVoutWindow,
                             BOOL bQuickOutputEnable)
{
    HI_S32 s32Ret = FAILURE;

    if (!hVoutWindow)
    {
        HAL_ERROR("Invalid vout handle!");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    s32Ret = HI_UNF_VO_SetQuickOutputEnable(hVoutWindow, bQuickOutputEnable);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_VO_SetQuickOutputEnable failed:%#x.\n", s32Ret);
        return HI_FAILURE;
    }

    return SUCCESS;
}

S32 vout_window_get_quick_output_mode(struct _VOUT_DEVICE_S* pstVoutDev,
                                                       const HANDLE hVoutWindow,
                                                       BOOL* pbQuickOutputEnable)
{
    S32 s32Ret = FAILURE;

    if (!hVoutWindow)
    {
        HAL_ERROR("Invalid vout handle!\n");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (NULL == pbQuickOutputEnable)
    {
        HAL_ERROR("pbQuickOutputEnable is NULL\n!");
        return ERROR_NULL_PTR;
    }

    s32Ret = HI_UNF_VO_GetQuickOutputStatus(hVoutWindow, (HI_BOOL *)pbQuickOutputEnable);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_VO_SetQuickOutputEnable failed:%#x.\n", s32Ret);
        return HI_FAILURE;
    }

    return SUCCESS;
}


S32 vout_window_get_latency(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, U32* pu32Latency)
{
    S32 s32Ret = SUCCESS;
    HI_DRV_WIN_PLAY_INFO_S stInfo;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_get_lantency Invalid vout handle!!.\n");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    if (NULL == pu32Latency)
    {
        HAL_ERROR("vout_window_get_lantency null param!!.\n");
        return ERROR_NULL_PTR;
    }

    memset(&stInfo, 0, sizeof(HI_DRV_WIN_PLAY_INFO_S));

    s32Ret = HI_MPI_WIN_GetPlayInfo(hVoutWindow, &stInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_MPI_WIN_GetPlayInfo failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;
    }

    *pu32Latency = stInfo.u32DelayTime;

    return SUCCESS;
}

#ifdef HAL_HISI_EXTEND_H
/* CNcomment:关闭HDR通路 */
S32 vout_window_close_hdr_path(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                             BOOL bCloseHdrPath)
{
    S32 s32Ret = SUCCESS;

    if (!hVoutWindow)
    {
        HAL_ERROR("vout_window_close_hdr_path Invalid vout handle!!.\n");
        return ERROR_VO_WIN_NOT_CREATED;
    }

    s32Ret = HI_MPI_WIN_CloseHdrPath(hVoutWindow, bCloseHdrPath);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_MPI_WIN_CloseHdrPath failed:%#x.\n", s32Ret);
        return ERROR_VO_PARAMETER_INVALID;;
    }

    return SUCCESS;

}
#endif

#ifdef TVOS_PLATFORM
static int vout_device_close(struct hw_device_t *pstDev)
{
    struct _VOUT_DEVICE_S* pCtx = (struct _VOUT_DEVICE_S*)pstDev;
    if (pCtx) {
        free(pCtx);
        pCtx = NULL;
    }
    return 0;
}

static int vout_device_open(const struct hw_module_t* module, const char* name,
                            struct hw_device_t** device)
{
    HAL_DEBUG_ENTER();

    if (strcmp(name, VOUT_HARDWARE_VOUT0) != 0)
    {
        return -EINVAL;
    }

    if (NULL == device)
    {
        return FAILURE;
    }

    VOUT_DEVICE_S *stVOUTdev = (VOUT_DEVICE_S*)malloc(sizeof(VOUT_DEVICE_S));
    if (NULL == stVOUTdev)
    {
        HAL_ERROR("malloc memory failed! ");
        return -ENOMEM;
    }

    /* initialize our state here */
    memset(stVOUTdev, 0, sizeof(VOUT_DEVICE_S));

    /* initialize the procs */
    stVOUTdev->stCommon.tag     = HARDWARE_DEVICE_TAG;
    stVOUTdev->stCommon.version = VOUT_DEVICE_API_VERSION_1_0;
    stVOUTdev->stCommon.module  = (hw_module_t*)module;
    stVOUTdev->stCommon.close   = vout_device_close;

    /* register the callbacks */
    /* 1. 显示通道 */
    stVOUTdev->vout_init                 = vout_init;
    stVOUTdev->vout_term                 = vout_term;
    stVOUTdev->vout_open_channel         = vout_open_channel;
    stVOUTdev->vout_close_channel        = vout_close_channel;
    stVOUTdev->vout_get_capability       = vout_get_capability;
    stVOUTdev->vout_evt_config           = vout_evt_config;
    stVOUTdev->vout_get_evt_config       = vout_get_evt_config;
    stVOUTdev->vout_outputchannel_mute   = vout_outputchannel_mute;
    stVOUTdev->vout_outputchannel_unmute = vout_outputchannel_unmute;
    stVOUTdev->vout_display_set          = vout_display_set;
    stVOUTdev->vout_display_get          = vout_display_get;
    stVOUTdev->vout_vbi_cgms_start       = vout_vbi_cgms_start;
    stVOUTdev->vout_vbi_cgms_stop        = vout_vbi_cgms_stop;
    stVOUTdev->vout_set_bg_color         = vout_set_bg_color;
    stVOUTdev->vout_get_bg_color         = vout_get_bg_color;
    stVOUTdev->vout_get_3dmode           = vout_get_3dmode,
    stVOUTdev->vout_set_3dmode           = vout_set_3dmode,

    /* 2. 视频窗口 */
    stVOUTdev->vout_window_create               = vout_window_create;
    stVOUTdev->vout_window_destroy              = vout_window_destroy;
    stVOUTdev->vout_window_set                  = vout_window_set;
    stVOUTdev->vout_window_get                  = vout_window_get;
    stVOUTdev->vout_window_set_input_rect       = vout_window_set_input_rect;
    stVOUTdev->vout_window_get_input_rect       = vout_window_get_input_rect;
    stVOUTdev->vout_window_set_output_rect      = vout_window_set_output_rect;
    stVOUTdev->vout_window_get_output_rect      = vout_window_get_output_rect;
    stVOUTdev->vout_window_get_status           = vout_window_get_status;
    stVOUTdev->vout_window_freeze               = vout_window_freeze;
    stVOUTdev->vout_window_unfreeze             = vout_window_unfreeze;
    stVOUTdev->vout_window_mute                 = vout_window_mute;
    stVOUTdev->vout_window_unmute               = vout_window_unmute;
    stVOUTdev->vout_window_attach_input         = vout_window_attach_input;
    stVOUTdev->vout_window_detach_input         = vout_window_detach_input;
    stVOUTdev->vout_window_set_colortemperature = vout_window_set_colortemperature;
    stVOUTdev->vout_window_set_zorder           = vout_window_set_zorder;
    stVOUTdev->vout_window_queue_frame          = vout_window_queue_frame;
    stVOUTdev->vout_window_dequeue_frame        = vout_window_dequeue_frame;
    stVOUTdev->vout_window_reset                = vout_window_reset;
    stVOUTdev->vout_window_get_virtual_size     = vout_window_get_virtual_size;
    stVOUTdev->vout_window_get_playinfo         = vout_window_get_playinfo;
    stVOUTdev->vout_window_get_latency          = vout_window_get_latency;
    stVOUTdev->vout_window_set_quick_output_mode = vout_window_set_quick_output_mode;
    stVOUTdev->vout_window_get_quick_output_mode = vout_window_get_quick_output_mode;

#ifdef HAL_HISI_EXTEND_H
    stVOUTdev->vout_window_close_hdr_path       = vout_window_close_hdr_path;
#endif
    *device = &(stVOUTdev->stCommon);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static struct hw_module_methods_t vout_module_methods = {
    open: vout_device_open,
};

VOUT_MODULE_S HAL_MODULE_INFO_SYM = {
    stCommon: {
        tag:           HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
        id:            VOUT_HARDWARE_MODULE_ID,
        name:          "Sample hwcomposer module",
        author:        "The Android Open Source Project",
        methods:       &vout_module_methods,
        dso:           NULL,
        reserved:      {0},
    }
};
#endif

static  VOUT_DEVICE_S s_stVoutDev=
{
    /* register the callbacks */
    /* 1. CNcomment:显示通道 */
    .vout_init                 = vout_init,
    .vout_term                 = vout_term,
    .vout_open_channel         = vout_open_channel,
    .vout_close_channel        = vout_close_channel,
    .vout_get_capability       = vout_get_capability,
    .vout_evt_config           = vout_evt_config,
    .vout_get_evt_config       = vout_get_evt_config,
    .vout_outputchannel_mute   = vout_outputchannel_mute,
    .vout_outputchannel_unmute = vout_outputchannel_unmute,
    .vout_display_set          = vout_display_set,
    .vout_display_get          = vout_display_get,
    .vout_vbi_cgms_start       = vout_vbi_cgms_start,
    .vout_vbi_cgms_stop        = vout_vbi_cgms_stop,
    .vout_set_bg_color         = vout_set_bg_color,
    .vout_get_bg_color         = vout_get_bg_color,
    .vout_set_3dmode           = vout_set_3dmode,
    .vout_get_3dmode           = vout_get_3dmode,

    /* 2. CNcomment:视频窗口 */
    .vout_window_create               = vout_window_create,
    .vout_window_destroy              = vout_window_destroy,
    .vout_window_set                  = vout_window_set,
    .vout_window_get                  = vout_window_get,
    .vout_window_set_input_rect       = vout_window_set_input_rect,
    .vout_window_get_input_rect       = vout_window_get_input_rect,
    .vout_window_set_output_rect      = vout_window_set_output_rect,
    .vout_window_get_output_rect      = vout_window_get_output_rect,
    .vout_window_set_video_rect       = vout_window_set_output_rect,
    .vout_window_get_video_rect       = vout_window_get_output_rect,
    .vout_window_get_status           = vout_window_get_status,
    .vout_window_freeze               = vout_window_freeze,
    .vout_window_unfreeze             = vout_window_unfreeze,
    .vout_window_mute                 = vout_window_mute,
    .vout_window_unmute               = vout_window_unmute,
    .vout_window_attach_input         = vout_window_attach_input,
    .vout_window_detach_input         = vout_window_detach_input,
    .vout_window_set_colortemperature = vout_window_set_colortemperature,
    .vout_window_set_zorder           = vout_window_set_zorder,
    .vout_window_queue_frame          = vout_window_queue_frame,
    .vout_window_dequeue_frame        = vout_window_dequeue_frame,
    .vout_window_reset                = vout_window_reset,
    .vout_window_get_virtual_size     = vout_window_get_virtual_size,
    .vout_window_get_playinfo         = vout_window_get_playinfo,
    .vout_window_get_latency          = vout_window_get_latency,
    .vout_window_set_quick_output_mode = vout_window_set_quick_output_mode,
    .vout_window_get_quick_output_mode = vout_window_get_quick_output_mode,
#ifdef HAL_HISI_EXTEND_H
    .vout_window_close_hdr_path       = vout_window_close_hdr_path,
#endif
};

VOUT_DEVICE_S* getVoutDevice()
{
    return &s_stVoutDev;
}

