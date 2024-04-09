/**
* \file
* \brief Describes the information about the system module.
*/

#ifndef __TVOS_HAL_SYSTEM_H__
#define __TVOS_HAL_SYSTEM_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "tvos_hal_type.h"
#ifdef ANDROID_HAL_MODULE_USED
#include <hardware/hardware.h>
#else
#include "tvos_hal_linux_adapter.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************** Macro Definition ****************************/
/** \addtogroup     HAL_SYSTEM */
/** @{ */  /** <!-- [HAL_SYSTEM] */

/**Module id define.*//** CNcomment:ģ��ID ���� */
#define SYSTEM_HARDWARE_MODULE_ID       "system"

/**Device name define .*//** CNcomment:�豸���ƶ��� */
#define SYSTEM_HARDWARE_SYSTEM0         "system0"

/**Chip ID max length.*//** CNcomment:оƬID ��󳤶� */
#define SYSTEM_CHIP_ID_LENGTH           (256)

/**Standby wakeup max key number.*//** CNcomment:�����õĴ������Ѽ������� */
#define SYSTEM_STANDBY_WKUP_KEY_MAXNUM  (8)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_SYSTEM */
/** @{ */  /** <!-- [HAL_SYSTEM] */

/**System init param *//** CNcomment:ϵͳ��ʼ������ */
typedef struct _SYSTEM_INIT_PARAMS_S
{
    U32      u32MemSize;                /**<System total memory size(BYTE), can be ignored(zero) *//**<CNcomment:ϵͳ�ܹ��ڴ��С(BYTE), ���Ժ���(0) */
    U32      u32SysMemSize;             /**<OS and driver total memory size(BYTE), can be ignored(zero) *//**<CNcomment: ����ϵͳ���豸�����ڴ��С (BYTE), ���Ժ���(0) */
    U32      u32DmxMemSize;             /**<Dmx driver memory size(BYTE), can be ignored(zero) *//**<CNcomment:Dmx �����ڴ��С(BYTE), ���Ժ���(0) */
    U32      u32AvMemSize;              /**<AV Memory size(BYTE), can be ignored(zero) *//**<CNcomment:AV�ڴ��С(BYTE), ���Ժ���(0) */
    U32      u32UsrShareMemSize;        /**<usr_share Memory size(BYTE), can be ignored(zero) *//**<CNcomment:usr_share�ڴ��С(BYTE), ���Ժ���(0) */
} SYSTEM_INIT_PARAMS_S;

/**System deinit param *//** CNcomment:ϵͳȥ��ʼ������ */
typedef struct _SYSTEM_TERM_PARAMS_S
{
    U32 u32Dummy;    /**<Reserve *//**<CNcomment:����*/
} SYSTEM_TERM_PARAMS_S;

#ifdef HAL_HISI_EXTEND_H
/**Defines of SYS event.*/
/**CNcomment: ����SYS�¼�*/
typedef enum _SYS_EVT_E
{
    SYS_RM_EVT_WND_LACK    = 0x1,  /**<Indicates the current available window, no parameter *//**<CNcomment:ָʾ��ǰû�п��õ�window, �޲���*/
    SYS_RM_EVT_WND_CREATED = 0x2,   /**<Indicates the window has been created, no parameter *//**<CNcomment:ָʾwindow�Ѿ�������, �޲���*/
    SYS_RM_EVT_WND_DESTROYED = 0x4, /**<Indicates the window has been destroyed, no parameter *//**<CNcomment:ָʾwindow�Ѿ�������, �޲���*/
    SYS_RM_EVT_BUTT
} SYS_EVT_E;

/**
\brief SYS event callback. CNcomment:sys �¼��ص������������� CNend
\attention \n
The function could call the api of sys module
\param[in] pClient sys client.CNcomment:sys client CNend
\param[in] enEvt sys event type.CNcomment:sys�¼����� CNend
\param[in] u32EventPara The data with event, see SYS_EVT_E.CNcomment:��ο� SYS_EVT_E ��˵�� CNend
\retval ::SUCCESS CNcomment:�ɹ� CNend
\retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ�� CNend
\retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
\see \n
::SYS_EVT_E
*/
typedef S32 (*SYS_CALLBACK_PFN_T)(VOID* pClient,  SYS_EVT_E enEvent, U32 u32EventPara);

/**Struct of sys event config parameter*/
/**CNcomment:ϵͳ�¼����ò���*/
typedef struct _SYS_EVT_CONFIG_PARAMS_S
{
    SYS_EVT_E           enEvt;                  /**<sys event*//**<CNcomment: sys�¼�,��ʾ�����ö��ĸ��¼���Ч*/
    BOOL                bEnable;                /**<enable*//**<CNcomment: ʹ�ܱ�־*/
    VOID*               pClient;                /**<fn client*//**<CNcomment: �ص�������client*/
    SYS_CALLBACK_PFN_T  pfnCallback;            /**<Callback*//**<CNcomment: �ص�����*/
} SYS_EVT_CONFIG_PARAMS_S;
#endif

/**System work mode *//** CNcomment:ϵͳ����ģʽ */
typedef enum _SYSTEN_SYSTEM_MODE_E
{
    SYSTEM_SYSTEM_MODE_NORMAL = 0,      /**<Normal work mode *//**<CNcomment:��������ģʽ*/
    SYSTEM_SYSTEM_MODE_SLOW,            /**<Low power mode, fake standby, front panel led can display time *//**<CNcomment:�͹��Ĺ���ģʽ, ��Ӧ�ٴ���,ǰ������ʾʱ��*/
    SYSTEM_SYSTEM_MODE_STANDBY,         /**<standby work mode, true standby, front panel led cann't display*//**<CNcomment:���������ģʽ, ǰ��岻����ʾ*/
    SYSTEM_SYSTEM_MODE_BUTT
} SYSTEN_SYSTEM_MODE_E;

/**Key code structure *//** CNcomment:����ֵ�ṹ */
typedef struct _SYSTEM_KEY_CODE_S
{
    U32     u32KeyLowerValue;            /**<Key code value low  *//**<CNcomment:����ֵ��λ*/
    U32     u32KeyUpperValue;            /**<Key code value high  *//**<CNcomment:����ֵ��λ*/
} SYSTEM_KEY_CODE_S;

/**Key type type *//** CNcomment:�������� */
typedef enum _SYSTEM_KEY_TYPE_E
{
    KEY_TYPE_IR = 0,                     /**<IR type *//**<CNcomment:����ң�ذ���*/
    KEY_TYPE_PANEL,                      /**<Front panel type *//**<CNcomment:ǰ��尴��*/
    KEY_TYPE_BUTT
} SYSTEM_KEY_TYPE_E;

/**Key info *//** CNcomment:������Ϣ*/
typedef struct _SYSTEM_KDB_KEY_DATA_S
{
    BOOL                  bExist;        /**<Whether valid *//**<CNcomment:�����Ƿ���Ч*/
    SYSTEM_KEY_TYPE_E     enType;        /**<Key type, IR or panel key *//**<CNcomment:�������ͣ�ң��������尴��*/
    SYSTEM_KEY_CODE_S     stCode;        /**<Key value *//**<CNcomment:���յ��İ�����ֵ*/
} SYSTEM_KDB_KEY_DATA_S;

/**Time info, UTC time *//** CNcomment:ʱ����Ϣ����UTCʱ����*/
typedef struct _SYSTEM_TIME_S
{
    U64   u64TimeSec;
} SYSTEM_TIME_S;

/**Time info, UTC time *//** CNcomment:ʱ����Ϣ����UTCʱ����*/
typedef struct _SYSTEM_WAKEUPINFO_S
{
    SYSTEM_KDB_KEY_DATA_S stWakeupKey;
    SYSTEM_TIME_S stStandbyPeriodTime;
} SYSTEM_WAKEUPINFO_S;

/**System standby  config param *//** CNcomment:ϵͳ�������ò��� */
typedef struct _SYSTEM_STANDBY_PARA_S
{
    SYSTEN_SYSTEM_MODE_E    enSystemMode;       /**<System work mode *//**<CNcomment:ϵͳ����ģʽ*/
    SYSTEM_KDB_KEY_DATA_S   astStandbyKey[SYSTEM_STANDBY_WKUP_KEY_MAXNUM]; /**<Standby wakeup key config *//**<CNcomment:�������Ѽ�����*/
    BOOL                    bAutoWakeup;        /**<Whether auto wakeup *//**<CNcomment: �Ƿ��Զ�����*/
    BOOL                    bDispTimeEnable;    /**<Whether display time when standby *//**<CNcomment: ����ʱǰ����Ƿ���ʾʱ��*/
    SYSTEM_TIME_S           stCurrTime;         /**<System current time *//**<CNcomment:ϵͳ��ǰʱ��*/
    SYSTEM_TIME_S           stAlarmTime;        /**<System wakeup time *//**<CNcomment:ϵͳ�Զ�����ʱ��*/
    BOOL                    bWifiPowerOn;       /**<Whether Wifi power supply when standby   *//**<CNcomment:����ʱwifi�Ƿ񹩵�*/
    BOOL                    bCmPowerOn;         /**<Whether cable moderm power supply when standby   *//**<CNcomment:����ʱcable moderm�Ƿ񹩵�*/
    U32                     u32Dummy;           /**<Reserve *//**<CNcomment:����*/
} SYSTEM_STANDBY_PARA_S;

/**System crypt mode *//** CNcomment:ϵͳ�ӽ���ģʽ */
typedef enum _SYSTEM_CRYPT_MODE_E
{
    SYSTEM_CRYPT_MODE_PLAIN,        /**<Plain mode *//**<CNcomment:Plainģʽ*/
    SYSTEM_CRYPT_MODE_ENCRYPT,      /**<Encrypt mode *//**<CNcomment:Encryptģʽ*/
    SYSTEM_CRYPT_MODE_DECRYPT,      /**<Decrypt mode *//**<CNcomment:Decryptģʽ*/
    SYSTEM_CRYPT_MODE_BYTT
} SYSTEM_CRYPT_MODE_E;

/**chip desc info *//** CNcomment:оƬ������Ϣ */
typedef struct _SYSTEM_CHIP_ID_S
{
    U32     u32ActLen;                             /**<chip id length *//**<CNcomment:оƬID ʵ�ʳ���*/
    U8      au8ChipIdBuf[SYSTEM_CHIP_ID_LENGTH];   /**<chip id info buf *//**<CNcomment:оƬID buffer*/
} SYSTEM_CHIP_ID_S;

#ifdef ANDROID_HAL_MODULE_USED
/**System module structure(Android require) */
/**CNcomment:ϵͳģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _SYSTEM_MODULE_S
{
    struct hw_module_t stCommon;                   /**<Module common structure(Android require) *//**<CNcomment:ģ��ͨ�ýṹ(Android�Խ�Ҫ�� ) */
} SYSTEM_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup     HAL_SYSTEM */
/** @{ */  /** <!-- [HAL_SYSTEM] */

/**System device structure*//** CNcomment:ϵͳ�豸�ṹ */
typedef struct _SYSTEM_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:ģ��ͨ�ýṹ(Android�Խ�Ҫ�� ) */
#endif

    /**
    \brief System  init.CNcomment:ϵͳ��ʼ�� CNend
    \attention \n
    Soc development kit init and alloc necessary resource, should be called before other module, repeat call return success.
    CNcomment:�弶��������ʼ���������Ҫ����Դ, Ӧ��������ģ���ʼ��ǰ������,�������ظ����÷��سɹ�. CNend
    \param[in] pstInitParams system module init param.CNcomment:��ʼ������ CNend

    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SYSTEM_INIT_FAILED  Soc development kit init error.CNcomment:�弶��������ʼ������CNend
    \retval ::ERROR_NO_MEMORY not enough memory .CNcomment:�ڴ治�㡣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SYSTEM_INIT_PARAMS_S

    \par example
    \code
    SYSTEM_INIT_PARAMS_S stInitParam;
    memset(&stInitParam, 0x0, sizeof(SYSTEM_INIT_PARAMS_S));
    stInitParam.u32Memsize=256*1024*1024;
    if (SUCCESS != system_init(pstDev, (const SYSTEM_INIT_PARAMS_S * const)&stInitParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_init)(struct _SYSTEM_DEVICE_S* pstDev, const SYSTEM_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief System  deinit.CNcomment:ϵͳȥ��ʼ�� CNend
    \attention \n
    Soc development kit deinit and release occupied resource, should be called after other module deinit, repeat call return success.
    CNcomment:�弶������ȥ��ʼ�����ͷ�ռ�õ���Դ, Ӧ��������ģ��ȥ��ʼ�������,�������ظ����÷��سɹ�. CNend
    \param[in] pstTermParams system module term param.CNcomment:��ʼ��ģ��ȥ��ʼ������ CNend

    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SYSTEM_DEINIT_FAILED  Soc development kit deinit error.CNcomment:�弶������ȥ��ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SYSTEM_TERM_PARAMS_S

    \par example
    \code
    SYSTEM_TERM_PARAMS_S stDeInitParam;
    stDeInitParam.u32Dummy = 0;
    if (SUCCESS != system_term(pstDev, (const SYSTEM_TERM_PARAMS_S * const)&stDeInitParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_term)(struct _SYSTEM_DEVICE_S* pstDev, const SYSTEM_TERM_PARAMS_S* const pstTermParams);

#ifdef HAL_HISI_EXTEND_H
    /**
    \brief Config the callback attribute of SYS event. CNcomment:����ĳһSYS�¼��Ĳ��� CNend
    \attention \n
    The function can execute regist/unregist
    1.Each event can register callback function and set it's config independently.
    2.Only one callback function can be registered for a SYS event, so the callback function will be recovered.
    CNcomment: ͨ������������ִ�еĲ�����regist/remove/disable/enable
    1. ÿ���¼������Զ���ע��/��ע���Լ��Ļص�����.
    3. ͬһ���¼�ֻ��ע��һ���ص�����,��:����ע��Ļص������Ḳ��ԭ�еĻص�����.
    CNend
    \param[in] pstCfg Config param.CNcomment:�¼����ò��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SYS_EVT_CONFIG_PARAMS_S
    */
    S32 (*system_evt_config)(struct _SYSTEM_DEVICE_S* pstDev, const SYS_EVT_CONFIG_PARAMS_S* pstCfg);
#endif
    /**
    \brief System standby mode switch.CNcomment:����ģʽ�л� CNend
    \attention \n
    This interface is the last step of the standby operation, before call, should stop related system operation, such as close AV/DMX , three cases:
    1. lower layer part standby operate, this interface normal return, system is still normal running, apps need to recognize waking signal and deal with the signal
    2. lower layer standby, system blocks in this interface, lower layer needs to recognize waking signal and notify apps
    3. lower layer enters true standby by MCU, equivalent to hardware turnoff, wake up signal received by MCU
    CNcomment:�˽ӿ�Ϊ���������һ�����������ýӿ�ǰ��Ӧ��ֹͣ��Ӧ��ϵͳ����������ر�AV��DMX��
    ���ô˽ӿ�ʱ,�����ܳ����������:
    1. ���ú󣬵ײ����˲��ִ��������󣬺����������أ�ϵͳʵ�ʻ������У���Ӧ�ó����Լ�ʶ�����źţ�
        ������Ӧ�Ĳ���;
    2. �������ú󣬵ײ���������������ڴ����������棬ֱ���ײ��Լ�ʶ�𵽻��Ѱ������������أ�
        ���ں�������ͬʱ��Ӧ�ó���ģ�ⷢ��һ�λ����źţ�֮��Ӧ�ó����ٽ��п�AV���ŵȲ���
    3. �������ú�ֱ����MCU���������ʱ�൱��Ӳ���ػ�, ��MCU ���ջ����ź�    CNend
    \param[in] standby standy config.CNcomment: �������� CNend
    \param[out] pstWakeupInfo wake up information.CNcomment: �������Ѳ��� CNend

    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED system don't init.CNcomment:ϵͳδ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param.CNcomment:��������CNend
    \retval ::ERROR_SYSTEM_STANDBY_FAILED lower layer standby failed.CNcomment:�ײ��������ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SYSTEM_STANDBY_PARA_S

    \par example
    \code
    SYSTEM_STANDBY_PARA_S stStandbyPara;

    memset(&stStandbyPara, 0x0, sizeof(SYSTEM_STANDBY_PARA_S));
    stStandbyPara.enSystemMode = SYSTEM_SYSTEM_MODE_STANDBY;
    if (SUCCESS != system_switch_standby((const SYSTEM_STANDBY_PARA_S*const)&stStandbyPara))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_switch_standby)(struct _SYSTEM_DEVICE_S* pstDev, const SYSTEM_STANDBY_PARA_S* const pstPara, SYSTEM_WAKEUPINFO_S* pstWakeupInfo);

    /**
    \brief Get the period during standby status.
    CNcomment:\brief ��ȡ�Ӵ��������ѳ�����ʱ�䡣CNend

    \attention \n

    \param[out] pu32Period  The period of standby. CNcomment:����������ʱ�� CNend
    \retval ::ERROR_NOT_INITED  The PMoC device is not started.            CNcomment:PMoC�豸δ�� CNend
    \retval ::ERROR_NULL_PTR  The pointer is invalid.               CNcomment:�Ƿ�ָ�� CNend
    \retval ::FAILURE  It fails to get standby period.    CNcomment:��ȡ����ʱ��ʧ�� CNend
    \see \n
    N/A
    */
    S32 (*system_get_standby_period)(U32 *pu32Period);

    /**
    \brief Gets the wake-up mode of the ARM.
    CNcomment:\brief ��ȡ��ǰ������ʽ��CNend

    \attention \n

    \param[out] pstPara  Wake-up mode of the ARM                            CNcomment:ARM���ѷ�ʽ��CNend
    \retval HI_SUCCESS Success                                              CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  The PMoC device is not started.         CNcomment:PMoC�豸δ�� CNend
    \retval ::ERROR_NULL_PTR  The pointer is invalid.            CNcomment:�Ƿ�ָ�� CNend
    \retval ::ERROR_INVALID_PARAM  The parameter is invalid.           CNcomment:�Ƿ����� CNend
    \retval ::FAILURE It fails to set power val.    CNcomment:��ȡ���ѷ�ʽʧ�� CNend
    \see \n
    N/A
    */
    S32 (*system_get_standby_param)(SYSTEM_STANDBY_PARA_S* pstPara);

    /**
    \brief Sets the wake-up mode of the ARM.
    CNcomment:\brief ���õ�ǰ������ʽ��CNend

    \attention \n
    You can query the original IR code values by referring to IR remote manuals.\n
    In addition, you can query the relationships between the keys and key IDs by checking the connection between hardware and chips.\n
    CNcomment:IRԭʼ��ֵ����ͨ��ң������ʹ���ֲ�õ�\n
    �������ֵ�Ķ�Ӧ��ϵ����ͨ��Ӳ����оƬ�����ӹ�ϵ�õ���CNend

    \param[in] pstPara  Wake-up mode of the ARM                             CNcomment:ARM���ѷ�ʽ��CNend
    \retval HI_SUCCESS Success                                              CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  The PMoC device is not started.         CNcomment:PMoC�豸δ�� CNend
    \retval ::ERROR_NULL_PTR  The pointer is invalid.            CNcomment:�Ƿ�ָ�� CNend
    \retval ::ERROR_INVALID_PARAM  The parameter is invalid.           CNcomment:�Ƿ����� CNend
    \retval ::FAILURE It fails to set power val.    CNcomment:���û��ѷ�ʽʧ�� CNend
    \see \n
    N/A
    */
    S32 (*system_set_standby_param)(const SYSTEM_STANDBY_PARA_S* const pstPara);

    /**
    \brief Perform a generic transfer with the cryptocore.CNcomment:�ӽ�������ת�� CNend
    \attention \n
    Implementation is related with platform, maybe need ncache memory or dma  .
    CNcomment:����ʵ��ƽ̨���,�����õ�ncache�ڴ��dma. CNend
    \param[in] u32SrcBuf source buffer addr.CNcomment:Դ��ַ CNend
    \param[in] u32DestBuf dest buffer addr buffer.CNcomment:Ŀ�ĵ�ַ CNend
    \param[in] u32DataSize data size.CNcomment: ���ݴ�С CNend
    \param[in] enMode operate mode.CNcomment: ����ģʽ CNend
    \param[in] bBlock block flag.CNcomment: �Ƿ������ı�־ CNend

    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_SUPPORTED not supported.CNcomment:��֧�֡�CNend
    \retval ::ERROR_INVALID_PARAM invalid param.CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SYSTEM_CRYPT_MODE_E

    \par example
    */
    S32 (*system_crypt_transfer)(struct _SYSTEM_DEVICE_S* pstDev, U32 u32SrcBuf, U32 u32DestBuf, U32 u32DataSize, SYSTEM_CRYPT_MODE_E enMode, BOOL bBlock);

    /**
    \brief get chip id info.CNcomment:��ȡоƬID��Ϣ CNend
    \attention \n
    None.
    \param[out] pstChipId chip id info.CNcomment:оƬID��Ϣ CNend

    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_SUPPORTED not supported.CNcomment:��֧�֡�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SYSTEM_CHIP_ID_S

    \par example
    \code
    SYSTEM_CHIP_ID_S stSystemChipInfo;
    memset(&stSystemChipInfo, 0x0, sizeof(SYSTEM_CHIP_ID_S));
    if (SUCCESS != system_get_chip_id(pstDev, (SYSTEM_CHIP_ID_S * const)&stSystemChipInfo))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_get_chip_id)(struct _SYSTEM_DEVICE_S* pstDev, SYSTEM_CHIP_ID_S* const pstChipId);

    /**
    \brief system reboot.CNcomment:ϵͳ���� CNend
    \attention \n
    if success, cann't return.
    \param[in] u32TimeMs system reboot time(ms).CNcomment:ϵͳ����ʱ��(ms) CNend

    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_SUPPORTED not supported.CNcomment:��֧�֡�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    if (SUCCESS != system_sys_reboot(pstDev, 0))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_sys_reboot)(struct _SYSTEM_DEVICE_S* pstDev, const U32 u32TimeMs);

    /**
    \brief system halt.CNcomment:ϵͳ�ػ� CNend
    \attention \n
    if success, cann't return.
    \param[in] u32TimeMs system halt time(ms).CNcomment:ϵͳ�ػ�ʱ��(ms) CNend

    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_SUPPORTED not supported.CNcomment:��֧�֡�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    if (SUCCESS != system_sys_halt(pstDev, 0))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_sys_halt)(struct _SYSTEM_DEVICE_S* pstDev, const U32 u32TimeMs);
} SYSTEM_DEVICE_S ;

/**
\brief direct get system device api, for linux and android.CNcomment:��ȡϵͳ�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get system device api��for linux and andorid.
CNcomment:��ȡϵͳ�豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
\retval  system device pointer when success.CNcomment:�ɹ�����system�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::SYSTEM_DEVICE_S

\par example
*/
SYSTEM_DEVICE_S *getSystemDevice();

/**
\brief Open HAL System module device.CNcomment:��HALϵͳģ���豸 CNend
\attention \n
Open HAL System module device(for compatible Android HAL).
CNcomment:��HALϵͳģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice system device structure.CNcomment:ϵͳ�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::SYSTEM_DEVICE_S

\par example
*/
static inline int system_open(const struct hw_module_t* pstModule, SYSTEM_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, SYSTEM_HARDWARE_SYSTEM0, (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getSystemDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL System module device.CNcomment:�ر�HALϵͳģ���豸 CNend
\attention \n
Close HAL System module device(for compatible Android HAL).
CNcomment:�ر�HALϵͳģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice system device structure.CNcomment:ϵͳ�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::SYSTEM_DEVICE_S

\par example
*/
static inline int system_close(SYSTEM_DEVICE_S* pstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstDevice->stCommon.close(&pstDevice->stCommon);
#else
    return SUCCESS;
#endif
}

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*__TVOS_HAL_SYSTEM_H__*/

