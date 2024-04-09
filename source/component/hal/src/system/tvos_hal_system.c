#define LOG_TAG "System"

/**
 * \file hal_system_implement.c
 * \brief hal system implement file.
*/
#include <pthread.h>
#include <unistd.h>

#include "hi_unf_pmoc.h"
#include "hi_common.h"
#include "hi_unf_i2c.h"
#include "hi_unf_advca.h"

#include "tvos_hal_common.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_system.h"

#define PTHREAD_MUTEX_T pthread_mutex_t

/* init flag */
static BOOL s_bSystemInited = FALSE;

#ifdef RM_SUPPORT
/* RM module init flag*/
static BOOL s_bRmInited = FALSE;
#endif

/* fake standby flag */
static BOOL s_bFakeStandbyStatus = FALSE;
static BOOL s_bWakeUpFakeStandby = FALSE;

/**< mutex of sytem*/
static PTHREAD_MUTEX_T s_SystemMutex;

#define PowerLowerValue          0x3FF
#define PowerUpperValue          0x00
#define SYS_HEADER_VERSION       1
#define SYS_DEVICE_API_VERSION_1_0 HARDWARE_DEVICE_API_VERSION_2(1, 0, SYS_HEADER_VERSION)

#define SYS_LOCK(mutex) \
    do \
    { \
        (VOID)pthread_mutex_lock((mutex)); \
    } while (0)

#define SYS_UNLOCK(mutex) \
    do \
    { \
        (VOID)pthread_mutex_unlock((mutex)); \
    } while (0)

static S32 system_init(SYSTEM_DEVICE_S* pstDev, const SYSTEM_INIT_PARAMS_S* const pstInitParams)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();

    /* Return success if already inited */
    HAL_CHK_RETURN((TRUE == s_bSystemInited), SUCCESS, "System already init.");

    /* init system, todo: move to system init */
    SYS_LOCK(&s_SystemMutex);
    s32Ret = HI_SYS_Init();
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("sys init error!!");
        SYS_UNLOCK(&s_SystemMutex);
        return ERROR_SYSTEM_INIT_FAILED;
    }

    s32Ret = HI_UNF_I2C_Init();
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "i2c init error!! ret(0x%08x)", s32Ret);

    s32Ret = HI_UNF_PMOC_Init();
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "pmoc init error!! ret(0x%08x)", s32Ret);

    s_bSystemInited = TRUE;
    SYS_UNLOCK(&s_SystemMutex);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 system_term(SYSTEM_DEVICE_S* pstDev, const SYSTEM_TERM_PARAMS_S* const pstTermParams)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((TRUE != s_bSystemInited), SUCCESS, "System already deinit.");

    /* PMOC deinit */
    s32Ret = HI_UNF_PMOC_DeInit();
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "pmoc deinit error!! ret(0x%08x)", s32Ret);

    /* i2c deinit */
    s32Ret = HI_UNF_I2C_DeInit();
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "i2c deinit error!! ret(0x%08x)", s32Ret);

    /* deinit system, todo: move to system deinit */
    s32Ret = HI_SYS_DeInit();
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "i2c deinit error!! ret(0x%08x)", s32Ret);

    SYS_LOCK(&s_SystemMutex);
    s_bSystemInited = FALSE;
    SYS_UNLOCK(&s_SystemMutex);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

#ifdef HAL_HISI_EXTEND_H
static S32 system_evt_config(SYSTEM_DEVICE_S* pstDev, const SYS_EVT_CONFIG_PARAMS_S* pstCfg)
{

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((TRUE != s_bSystemInited), ERROR_NOT_INITED , "System not init.");
    HAL_CHK_RETURN(!pstCfg, ERROR_NULL_PTR, "null PTR");
    HAL_CHK_RETURN(!pstCfg->pfnCallback, ERROR_NULL_PTR, "null PTR");
    HAL_CHK_RETURN(SYS_RM_EVT_BUTT <= pstCfg->enEvt, ERROR_INVALID_PARAM, "parameter is invalid");

#ifdef RM_SUPPORT
    U32 u32EventID = 0;
    S32 s32Ret = SUCCESS;

    if (pstCfg->enEvt >= SYS_RM_EVT_WND_LACK && pstCfg->enEvt < SYS_RM_EVT_BUTT)
    {
        if (!s_bRmInited)
        {
            HAL_ERROR("RM not supported or has not been initialized, regitster event failed!");
            return ERROR_NOT_INITED;
        }

        if (SYS_RM_EVT_WND_LACK == pstCfg->enEvt)
        {
            u32EventID = HI_UNF_RM_EVENT_WND_LACK;
        }
        else if (SYS_RM_EVT_WND_CREATED == pstCfg->enEvt)
        {
            u32EventID = HI_UNF_RM_EVENT_WND_CREATED;
        }
        else
        {
            u32EventID = HI_UNF_RM_EVENT_WND_DESTROYED;
        }

        if (pstCfg->bEnable)
        {
            HAL_ERROR("Register RM callback, eventId = 0x%x", u32EventID);
            s32Ret = HI_UNF_RM_RegisterCallback(pstCfg->pClient, pstCfg->pfnCallback, u32EventID);
            HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "error!! ret(0x%08x)", s32Ret);
        }
        else
        {
            HAL_ERROR("Unregister RM callback, eventId = 0x%x", u32EventID);
            s32Ret = HI_UNF_RM_UnRegisterCallback(pstCfg->pClient, pstCfg->pfnCallback);
            HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "error!! ret(0x%08x)", s32Ret);
        }
    }

#endif

    HAL_DEBUG_EXIT();

    return SUCCESS;
}
#endif

static S32 enter_fake_standby(BOOL bFakeStandby)
{
    S32 s32Ret = FAILURE;

    if (TRUE == bFakeStandby && FALSE == s_bFakeStandbyStatus)
    {
        /* enter fake standby. only close Audio/HDMI/CVBS/YPbPr */
#ifdef HAL_HISI_EXTEND_H
        s_bWakeUpFakeStandby = FALSE;
        s32Ret = disable_audio_output();
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "error!! ret(0x%08x)", s32Ret);

        s32Ret |= disable_display_output();
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "error!! ret(0x%08x)", s32Ret);
#else
        s32Ret = HI_UNF_PMOC_EnterSmartStandby(0);
        if (SUCCESS == s32Ret)
        {
            s_bFakeStandbyStatus = TRUE;
        }
#endif
    }
    else if (FALSE == bFakeStandby && TRUE == s_bFakeStandbyStatus)
    {
        /* cancel fake standby */
#ifdef HAL_HISI_EXTEND_H
        s_bWakeUpFakeStandby = TRUE;
        s32Ret = enable_display_output();
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "error!! ret(0x%08x)", s32Ret);

        s32Ret |= restore_audio_output();
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "error!! ret(0x%08x)", s32Ret);
#else
        s32Ret = HI_UNF_PMOC_QuitSmartStandby();
        if (SUCCESS == s32Ret)
        {
            s_bFakeStandbyStatus = FALSE;
        }
#endif
    }
    else
    {
        /* the same status */
        s32Ret = SUCCESS;
    }

    return (SUCCESS == s32Ret) ? SUCCESS : FAILURE;
}

static S32 enter_true_standby(const SYSTEM_STANDBY_PARA_S* const pstPara,
                              SYSTEM_WAKEUPINFO_S* pstWakeupInfo)
{
    S32 s32Ret = FAILURE;
    S32 s32Ret1 = FAILURE;
    U32 u32Index         = 0;
    U32 u32StandbyTime   = 0;
    U32 u32PowerKeyIndex = 0;
    HI_UNF_PMOC_WKUP_S          stPmocWakeup;
    HI_UNF_PMOC_DEV_TYPE_S      stDevType;
    HI_UNF_PMOC_ACTUAL_WKUP_E   stWakeupStatus;
    HI_UNF_PMOC_WAKEUP_MODE_S   stWakeUpMode;

    if (TRUE == s_bFakeStandbyStatus)
    {
        //wakeup fakestandby.
        (VOID)enable_display_output();
        (VOID)restore_audio_output();
    }

    //set FAKE standby flag to false to avoid system problem when from FAKE->True standby->Wakeup->FAKE.
    s_bFakeStandbyStatus = FALSE;

    HAL_MEMSET_NO_VERIFY(&stDevType, 0x0, sizeof(HI_UNF_PMOC_DEV_TYPE_S));
    HAL_MEMSET_NO_VERIFY(&stPmocWakeup, 0x0, sizeof(HI_UNF_PMOC_WKUP_S));

    stDevType.irtype = HI_UNF_IR_CODE_RAW;
    s32Ret = HI_UNF_PMOC_SetDevType(&stDevType);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_SYSTEM_STANDBY_FAILED, "error!! ret(0x%08x)", s32Ret);

    /* set wakeup key */
    while (u32Index < SYSTEM_STANDBY_WKUP_KEY_MAXNUM)
    {
        if (TRUE == pstPara->astStandbyKey[u32Index].bExist)
        {
            if ((KEY_TYPE_IR == pstPara->astStandbyKey[u32Index].enType)
                && (u32PowerKeyIndex < PMOC_WKUP_IRKEY_MAXNUM))
            {
                stPmocWakeup.u32IrPowerKey0[u32PowerKeyIndex] =
                    pstPara->astStandbyKey[u32Index].stCode.u32KeyLowerValue;
                stPmocWakeup.u32IrPowerKey1[u32PowerKeyIndex] =
                    pstPara->astStandbyKey[u32Index].stCode.u32KeyUpperValue;
                stPmocWakeup.u32IrPmocNum++;
                u32PowerKeyIndex++; //increase index to avoid only record last key.
            }
            else if (KEY_TYPE_PANEL == pstPara->astStandbyKey[u32Index].enType)
            {
                stPmocWakeup.u32KeypadPowerKey =
                    pstPara->astStandbyKey[u32Index].stCode.u32KeyLowerValue;
            }
        }

        u32Index++;
    }

    /* set wakeup time */
    if (pstPara->stAlarmTime.u64TimeSec > pstPara->stCurrTime.u64TimeSec)
    {
        stPmocWakeup.u32WakeUpTime
            = (U32)(pstPara->stAlarmTime.u64TimeSec - pstPara->stCurrTime.u64TimeSec);
    }

#ifdef SYS_SECURITYOS_SUPPORT
    stPmocWakeup.bResumeResetEnable = TRUE;
#endif

    SYS_LOCK(&s_SystemMutex);

    if (TRUE == s_bWakeUpFakeStandby)
    {
        s_bWakeUpFakeStandby = FALSE;
        SYS_UNLOCK(&s_SystemMutex);
        HAL_ERROR("enter true standby error!!");
        return FAILURE;
    }

    SYS_UNLOCK(&s_SystemMutex);

    //u64TimeSec is relative time.
    stPmocWakeup.u32WakeUpTime = pstPara->stAlarmTime.u64TimeSec;
    s32Ret = HI_UNF_PMOC_SetWakeUpAttr(&stPmocWakeup);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_SYSTEM_STANDBY_FAILED, "error!! ret(0x%08x)", s32Ret);

    /* FIXME: set time display */

    /* enter standby */
    s32Ret = HI_UNF_PMOC_SwitchSystemMode(HI_UNF_PMOC_MODE_SLEEP, &stWakeupStatus);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_SYSTEM_STANDBY_FAILED, "error!! ret(0x%08x)", s32Ret);

    /* FIXME: set wake up key */
    if (pstWakeupInfo)
    {
        memset(&stWakeUpMode, 0, sizeof(stWakeUpMode));
        s32Ret1 = HI_UNF_PMOC_GetWakeUpMode(&stWakeUpMode);

        pstWakeupInfo->stWakeupKey.bExist = TRUE;
        pstWakeupInfo->stWakeupKey.enType = KEY_TYPE_IR;

        if (HI_SUCCESS == s32Ret1)
        {
            pstWakeupInfo->stWakeupKey.stCode.u32KeyLowerValue  = stWakeUpMode.u64IRPowerKey & (0xFFFFFFFF);
            pstWakeupInfo->stWakeupKey.stCode.u32KeyUpperValue  = stWakeUpMode.u64IRPowerKey >> 32;
        }
        else
        {
            pstWakeupInfo->stWakeupKey.stCode.u32KeyLowerValue  = PowerLowerValue;
            pstWakeupInfo->stWakeupKey.stCode.u32KeyUpperValue  = PowerUpperValue;
        }

        s32Ret = HI_UNF_PMOC_GetStandbyPeriod(&u32StandbyTime);

        if (SUCCESS == s32Ret)
        {
            pstWakeupInfo->stStandbyPeriodTime.u64TimeSec = (U64)u32StandbyTime;
        }
        else
        {
            HAL_ERROR("%s,%d error!! ret(0x%08x)", __func__, __LINE__, s32Ret);
        }
    }

    return SUCCESS;
}

static S32 system_switch_standby(struct _SYSTEM_DEVICE_S* pstDev,
                                 const SYSTEM_STANDBY_PARA_S* const pstPara, SYSTEM_WAKEUPINFO_S* pstWakeupInfo)
{
    S32 s32Ret = FAILURE;

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((TRUE != s_bSystemInited), ERROR_NOT_INITED , "System not init.");
    HAL_CHK_RETURN((NULL == pstPara || NULL == pstWakeupInfo), ERROR_NULL_PTR, "error!! Null PTR error!!");

    SYS_LOCK(&s_SystemMutex);

    /* for HI3751V500,  cann't set bDispTimeEnable,  ignore */

    /* fake standby and true standby deal with */
    if (SYSTEM_SYSTEM_MODE_SLOW == pstPara->enSystemMode)
    {
        /* fake standby */
        HAL_DEBUG("SystemMode: SYSTEM_SYSTEM_MODE_SLOW!!");
        s32Ret = enter_fake_standby(TRUE);
    }
    else if (SYSTEM_SYSTEM_MODE_NORMAL == pstPara->enSystemMode)
    {
        /* cancel fake standby */
        HAL_DEBUG("SystemMode: SYSTEM_SYSTEM_MODE_NORMAL!!");
        s32Ret = enter_fake_standby(FALSE);
    }
    else if (SYSTEM_SYSTEM_MODE_STANDBY == pstPara->enSystemMode)
    {
        /* true standby */
        HAL_DEBUG("SystemMode: SYSTEM_SYSTEM_MODE_STANDBY!!");
        s_bWakeUpFakeStandby = FALSE;//reset wakeup from fake standby flag.
        s32Ret = enter_true_standby(pstPara, pstWakeupInfo);
    }
    else
    {
        HAL_ERROR("error!! Invalid Param!!");
        SYS_UNLOCK(&s_SystemMutex);
        return ERROR_INVALID_PARAM;
    }

    SYS_UNLOCK(&s_SystemMutex);
    HAL_DEBUG_EXIT();

    return (SUCCESS == s32Ret) ? SUCCESS : FAILURE;
}

// TODO: Add this three funs to Android
static S32 system_get_standby_period(U32* pu32Period)
{
    HI_UNF_PMOC_GetStandbyPeriod(pu32Period);
    return ERROR_NOT_SUPPORTED;
}

static S32 system_get_standby_param(SYSTEM_STANDBY_PARA_S* pstPara)
{
    HI_UNF_PMOC_WKUP_S stAttr;
    // TODO: get wakeup attr from PMOC

    HI_UNF_PMOC_GetWakeUpAttr(&stAttr);
    return ERROR_NOT_SUPPORTED;
}

static S32 system_set_standby_param(const SYSTEM_STANDBY_PARA_S* const pstPara)
{
    HI_UNF_PMOC_WKUP_S stAttr;
    // TODO: set wakeup attr to PMOC
    HAL_CHK_RETURN((NULL == pstPara), ERROR_NULL_PTR, "parameter is NULL.");
    HI_UNF_PMOC_GetWakeUpAttr(&stAttr);

    stAttr.u32WakeUpTime = (U32)pstPara->stAlarmTime.u64TimeSec;

    HI_UNF_PMOC_SetWakeUpAttr(&stAttr);
    return ERROR_NOT_SUPPORTED;
}

static S32 system_crypt_transfer(SYSTEM_DEVICE_S* pstDev, U32 u32SrcBuf, U32 u32DestBuf,
                                 U32 u32DataSize, SYSTEM_CRYPT_MODE_E enMode, BOOL bBlock)
{
    HAL_ERROR("error!! system_crypt_transfer not support!!");
    return ERROR_NOT_SUPPORTED;
}

static S32 system_get_chip_id(SYSTEM_DEVICE_S* pstDev, SYSTEM_CHIP_ID_S* const pstChipId)
{
    HAL_DEBUG_ENTER();

    U32 u32MSBID = 0;
    U32 u32LSBID = 0;
    CHAR pChipID[SYSTEM_CHIP_ID_LENGTH] = {0};

    HAL_CHK_RETURN((TRUE != s_bSystemInited), ERROR_NOT_INITED , "System not init.");
    HAL_CHK_RETURN((NULL == pstChipId), ERROR_NULL_PTR, "invalid parameter.");
    SYS_LOCK(&s_SystemMutex);

#if defined(CA_FRAMEWORK_V200_SUPPORT)

    HAL_DEBUG("CA FRAMWORK V200 NOT SUPPORT !\n");
#else
    if (FAILURE == HI_UNF_ADVCA_GetDCASChipId(&u32MSBID, &u32LSBID))
    {
        HAL_ERROR("error!! call HI_UNF_ADVCA_GetDCASChipId failed!!");
        return FAILURE;
    }
#endif

    HAL_DEBUG("u32MSBID = %d, u32LSBID = %d!!", u32MSBID, u32LSBID);
    HAL_MEMSET_NO_VERIFY(pChipID, 0, SYSTEM_CHIP_ID_LENGTH);

    snprintf(pChipID, SYSTEM_CHIP_ID_LENGTH - 1, "%d", u32LSBID);
    HAL_MEMSET_NO_VERIFY(pstChipId, 0, sizeof(SYSTEM_CHIP_ID_S));
    snprintf((CHAR*)pstChipId->au8ChipIdBuf, SYSTEM_CHIP_ID_LENGTH - 1, "%d", u32MSBID);
    strncat((CHAR*)pstChipId->au8ChipIdBuf, pChipID, strlen(pChipID));
    pstChipId->u32ActLen = strlen((CHAR*)pstChipId->au8ChipIdBuf);

    HAL_DEBUG("strChipId = %s, u32ActLen = %d!!", pstChipId->au8ChipIdBuf, pstChipId->u32ActLen);

    SYS_UNLOCK(&s_SystemMutex);
    HAL_DEBUG_ENTER();

    return SUCCESS;
}

static S32 system_sys_reboot(SYSTEM_DEVICE_S* pstDev, const U32 u32TimeMs)
{
    S32 s32Ret = FAILURE;
    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((TRUE != s_bSystemInited), ERROR_NOT_INITED , "System not init.");

    usleep(u32TimeMs * 1000);
    s32Ret = system("reboot");
    if(SUCCESS != s32Ret)
    {
        HAL_ERROR("error!! system reboot failed!!");
        return FAILURE;
    }
    return SUCCESS;
}

static S32 system_sys_halt(SYSTEM_DEVICE_S* pstDev, const U32 u32TimeMs)
{
    S32 s32Ret = FAILURE;
    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((TRUE != s_bSystemInited), ERROR_NOT_INITED , "System not init.");

    usleep(u32TimeMs * 1000);
    s32Ret = system("reboot -p");
    if(SUCCESS != s32Ret)
    {
        HAL_ERROR("error!! system halt failed!!");
        return FAILURE;
    }
    return SUCCESS;
}

#ifdef TVOS_PLATFORM
static int sys_device_close(struct hw_device_t *pstDev)
{
    SYSTEM_DEVICE_S *pCtx = (SYSTEM_DEVICE_S *)pstDev;
    if (pCtx)
    {
        free(pCtx);
        pCtx = NULL;
    }
    return 0;
}

static int sys_device_open(const struct hw_module_t* module, const char* name,
                           struct hw_device_t** device)
{
    #define INIT_ZERO(obj) (memset(&(obj), 0, sizeof((obj))))

    S32 s32Ret = FAILURE;
    if (!strcmp(name, SYSTEM_HARDWARE_SYSTEM0))
    {
        if (NULL == device)
        {
            HAL_ERROR("ptr is NULL\n");
            return FAILURE;
        }

        SYSTEM_DEVICE_S *pstSysDev = (SYSTEM_DEVICE_S*)malloc(sizeof(SYSTEM_DEVICE_S));
        if (NULL ==  pstSysDev)
        {
            HAL_ERROR("malloc memory failed!\n",);
            return FAILURE;
        }

        /* initialize our state here */
        memset(pstSysDev, 0, sizeof(SYSTEM_DEVICE_S));
        INIT_ZERO(pstSysDev->stCommon.reserved);

        /* initialize the procs */
        pstSysDev->stCommon.tag = HARDWARE_DEVICE_TAG;
        pstSysDev->stCommon.version = SYS_DEVICE_API_VERSION_1_0;
        pstSysDev->stCommon.module = (hw_module_t*)module;
        pstSysDev->stCommon.close = sys_device_close;

        /* register the callbacks */
        pstSysDev->system_init = system_init;
        pstSysDev->system_term = system_term;
        pstSysDev->system_switch_standby = system_switch_standby;
        pstSysDev->system_get_standby_period  = system_get_standby_period,
        pstSysDev->system_get_standby_param   = system_get_standby_param,
        pstSysDev->system_set_standby_param   = system_set_standby_param,
        pstSysDev->system_crypt_transfer = system_crypt_transfer;
        pstSysDev->system_get_chip_id = system_get_chip_id;
        pstSysDev->system_sys_reboot = system_sys_reboot;
        pstSysDev->system_sys_halt = system_sys_halt;
#ifdef HAL_HISI_EXTEND_H
     pstSysDev->system_evt_config          = system_evt_config,
#endif
        *device = &(pstSysDev->stCommon);

        s32Ret = SUCCESS;
    }
    return s32Ret;
}

static struct hw_module_methods_t sys_module_methods = {
    open: sys_device_open
};

SYSTEM_MODULE_S HAL_MODULE_INFO_SYM = {
    stCommon: {
        tag: HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
        id: SYSTEM_HARDWARE_MODULE_ID,
        name: "Sample halsys module",
        author: "The Android Open Source Project",
        methods: &sys_module_methods,
        dso: NULL,
        reserved: {0},
    }
};
#endif

static SYSTEM_DEVICE_S s_stDevice_system =
{
    /* register the callbacks */
    .system_init                = system_init,
    .system_term                = system_term,
    .system_switch_standby      = system_switch_standby,
    .system_get_standby_period  = system_get_standby_period,
    .system_get_standby_param   = system_get_standby_param,
    .system_set_standby_param   = system_set_standby_param,
    .system_crypt_transfer      = system_crypt_transfer,
    .system_get_chip_id         = system_get_chip_id,
    .system_sys_reboot          = system_sys_reboot,
    .system_sys_halt            = system_sys_halt,
#ifdef HAL_HISI_EXTEND_H
    .system_evt_config          = system_evt_config,
#endif
};

SYSTEM_DEVICE_S* getSystemDevice()
{
    return &s_stDevice_system;
}
