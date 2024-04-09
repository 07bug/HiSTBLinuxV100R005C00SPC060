/**
 * \file
 * \brief Describes the information about the smc module.
 */

#ifndef  __TVOS_HAL_SMC_H__
#define __TVOS_HAL_SMC_H__

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
#endif /* __cplusplus */

/*************************** Macro Definition ****************************/
/** \addtogroup     HAL_SMC */
/** @{ */  /** <!-- [HAL_SMC] */

/**Module id define.*//** CNcomment:ģ��ID ���� */
#define SMC_HARDWARE_MODULE_ID  "smc"

/**Device name define .*//** CNcomment:�豸���ƶ��� */
#define SMC_HARDWARE_SMC0       "smc0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_SMC */
/** @{ */  /** <!-- [HAL_SMC] */

/**SMC active level *//** CNcomment:SMC��Ч��ƽ */
typedef enum _SMC_POLARITY_E
{
    SMC_EN_LOW = 0,             /**<Active low*//**<CNcomment:�͵�ƽ��Ч */
    SMC_EN_HIGH,                /**<Active high*//**<CNcomment:�ߵ�ƽ��Ч */
    SMC_EN_BUTT
} SMC_POLARITY_E;

/**Status of the SMC *//** CNcomment:���ܿ�״̬  */
typedef enum _SMC_STATUS_E
{
    SMC_TERM = 0,               /**<The smc is not initialized.*//**<CNcomment: smcδ��ʼ�� */
    SMC_RESET,                  /**<The smc is resetting.*//**<CNcomment: smc���ڸ�λ */
    SMC_INSERTED,               /**<The smc is inserted.*//**<CNcomment: smc�Ѳ��� */
    SMC_REMOVED,                /**<The smc is removed.*//**<CNcomment: smc���γ� */
    SMC_RESET_COMPLETE,         /**<The smc is resetted completely.*//**<CNcomment: smc��λ��� */
    SMC_RESET_TIMEOUT,          /**<The smc reset timeout.*//**<CNcomment: smc��λ��ʱ */
    SMC_RW_COMPLETE,            /**<The smc read/write completely.*//**<CNcomment: smc��д��� */
    SMC_RW_TIMEOUT,             /**<The smc read/write timeout.*//**<CNcomment: smc��д��ʱ */
    SMC_POWER_DOWN_COMPLETE,    /**<The smc powerdown complete.*//**<CNcomment: smc�µ���� */
    SMC_POWER_DOWN_TIMEOUT,     /**<The smc powerdown timeout.*//**<CNcomment: smc�µ糬ʱ */
    SMC_UNKNOW_ERROR,           /**<The smc unkonwn error.*//**<CNcomment: smc���� */
    SMC_STATUS_BUTT
} SMC_STATUS_E;

/**smart card protocol *//** CNcomment:���ܿ�Э������  */
typedef enum _SMC_PROTOCOL_E
{
    SMC_PROTOCOL_T0 = 0,        /**<7816 T0 protocol*/   /**<CNcomment:7816 T0 Э�� */
    SMC_PROTOCOL_T1,            /**<7816 T1 protocol*/   /**<CNcomment:7816 T1 Э�� */
    SMC_PROTOCOL_T14 = 14,      /**<7816 T14 protocol*/  /**<CNcomment:7816 T14 Э�� */
    SMC_PROTOCOL_BUTT
} SMC_PROTOCOL_E;

/**smart card standard *//** CNcomment:���ܿ���׼ */
typedef enum _SMC_STANDARD_E
{
    SMC_ISO = 0,
    SMC_N,
    SMC_IRD,
    SMC_TF,
    SMC_DVN,
    SMC_SUV,
    SMC_STANDARD_BUTT
} SMC_STANDARD_E;

/**
\brief smc status calback function.CNcomment:���ܿ�״̬�ص����� CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in] handle handle.CNcomment:�����CNend
\param[in] status smc status.CNcomment:���ܿ�״̬��CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
 typedef void (*smc_status_callback_pfn)(const HANDLE   smc_handle,
                                            const SMC_STATUS_E status);

/**smc module init param *//** CNcomment:���ܿ�ģ���ʼ������ */
typedef struct _SMC_INIT_PARA_S
{
    U32 u32SmcBaud;                   /**< smc baud*//**<CNcomment:smc������*/
    U32 u32SmcEtu;                    /**< smc etu*//**<CNcomment:smc etu*/
    U32 u32SmcClk;                    /**< smc clock*//**<CNcomment:smc ʱ��*/

    SMC_STANDARD_E  enStandard;       /**< smc standard*//**<CNcomment:smc ��׼*/
    SMC_PROTOCOL_E  enProtocol;       /**< smc protocol*//**<CNcomment:smc Э��*/

    SMC_POLARITY_E  enSmcVcc;         /**< active level of the VCCEN signal*//**<CNcomment:VCCEN�ź��ߵ���Ч��ƽ*/
    SMC_POLARITY_E  enSmcDetect;      /**< active level of the DETECT signal*//**<CNcomment:DETECT�ź��ߵ���Ч��ƽ*/
    SMC_POLARITY_E  enSmcRst;         /**< active level of the RESET signal*//**<CNcomment:RESET�ߵ���Ч��ƽ*/
} SMC_INIT_PARA_S;

/**smc port *//** CNcomment:smc�˿� */
typedef enum _SMC_PORT_E
{
    SMC_PORT0 = 0,          /**< smc port 0*//**<CNcomment:smc�˿�0*/
    SMC_PORT1               /**< smc port 1*//**<CNcomment:smc�˿�1*/
} SMC_PORT_E;

/**smc open param *//** CNcomment:���ܿ���ʵ������ */
typedef struct _SMC_OPEN_PARA_S
{
    SMC_PORT_E enSmcPort;   /**<smc port*//**<CNcomment:smc �˿� */
} SMC_OPEN_PARA_S;

/**smc module term param *//** CNcomment:���ܿ�ģ����ֹ���� */
typedef struct _SMC_TERM_PARAMS_S
{
    U32  u32Dummy;          /**<Later extended*//**<CNcomment:�Ժ���չ��*/
} SMC_TERM_PARAMS_S;

/**smc open info *//** CNcomment:���ܿ���Ϣ */
typedef struct _SMC_INFO_S
{
    SMC_STANDARD_E  enStandard;        /**< smc standard*//**<CNcomment:smc ��׼*/
    SMC_PROTOCOL_E  enProtocol;        /**< smc protocol*//**<CNcomment:smc Э��*/
    SMC_STATUS_E    enStatus;          /**< smc status*//**<CNcomment:smc ״̬*/
    U32             u32SmcBaud;        /**< smc baud*//**<CNcomment:smc������*/
    U32             u32SmcEtu;         /**< smc etu*//**<CNcomment:smc etu*/
    U32             u32SmcClk;         /**< smc clock*//**<CNcomment:smc ʱ��*/
} SMC_INFO_S;

#ifdef ANDROID_HAL_MODULE_USED
/**smc module structure (Android require)*/
/**CNcomment:smcģ��ṹ(Android�Խ�Ҫ��)*/
typedef struct _SMC_MODULE_S
{
    struct hw_module_t common; /**<Module common structure(Android require) *//**<CNcomment:ģ��ͨ�ýṹ(Android�Խ�Ҫ�� ) */
} SMC_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_SMC*/
/** @{*/  /** <!-- -[HAL_SMC]=*/

/**SMC device structure*//** CNcomment:���ܿ��豸�ṹ*/
typedef struct _SMC_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:ģ��ͨ�ýṹ(Android�Խ�Ҫ�� ) */
#endif
    /**
    \brief smc module init.CNcomment:���ܿ�ģ���ʼ�� CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] pstInitPara smart card module init param.CNcomment:��ʼ��ģ����� CNend
    \retval ::SUCCESS  success.CNcomment:��ʼ���ɹ���CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_INIT_FAILED  failure.CNcomment:��ʼ��ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*sk_hdi_smc_init)(struct _SMC_DEVICE_S* pstDev, const SMC_INIT_PARA_S* const pstInitPara);

    /**
    \brief open an smc instance.CNcomment:�����ܿ�ʵ�� CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] pstOpenPara smart card module open param.CNcomment:��smcģ��Ĳ����� CNend
    \param[out] pHandle handle.CNcomment:����� CNend
    \retval ::SUCCESS  success.CNcomment:��ʵ���ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_SMC_ALREADY_OPENED  invalid param.CNcomment:��ʵ���Ѿ��򿪡�CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_open)(struct _SMC_DEVICE_S* pstDev, HANDLE* const  pHandle,
                     const SMC_OPEN_PARA_S* const pstOpenPara);

    /**
    \brief close an smc instance.CNcomment:�ر����ܿ�ʵ�� CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:ʵ������� CNend
    \retval ::SUCCESS  success.CNcomment:�ر�ʵ���ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч�����CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_close)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle);

    /**
    \brief term smc module.CNcomment:��ֹ���ܿ�ģ�� CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] pTermParams handle.CNcomment:��ֹ������CNend
    \retval ::SUCCESS  success.CNcomment:��ֹʵ���ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_SMC_DEINIT_FAILED  failure.CNcomment:ģ����ֹʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_term)(struct _SMC_DEVICE_S* pstDev, const SMC_TERM_PARAMS_S* const  pstTermParams);

    /**
    \brief get the status of smart card. CNcomment: ��ȡ���ܿ�״̬��CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:�����CNend
    \param[out] pstSmcInfo handle.CNcomment:smc������Ϣ��CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч�����CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_get_info)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, SMC_INFO_S* pstSmcInfo);

    /**
    \brief  register callback function of smc status. CNcomment:ע�Ῠ״̬�ص�����CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:�����CNend
    \param[in]  pfnCallBack  Callback function  CNcomment: �ص�����ָ�롣CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч�����CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*smc_status_register_callback)(struct _SMC_DEVICE_S* pstDev, const HANDLE   handle,
                                        const smc_status_callback_pfn pfnCallBack);

    /**
    \brief reset smartcard. CNcomment: ��λ���ܿ���CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:�����CNend
    \param[in]  enProtocol  protocol  CNcomment: ��λ���õ�Э������CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч�����CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_reset_card)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, const SMC_PROTOCOL_E enProtocol);

    /**
    \brief transmits data to smart card. CNcomment: �����ܿ��������ݡ�CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:�����CNend
    \param[in]  u32len  length  CNcomment: �������ݵĳ���CNend
    \param[in]  pu8Buf  data buffer  CNcomment: �����͵�����CNend
    \param[out]  pu32SendLen  length of send success  CNcomment: �ɹ��������ݵĳ���CNend
    \param[in]  u32Timeout  wait timeout(in ms)  CNcomment:��ʱʱ��, ��λ�Ǻ���CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч�����CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*smc_send)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U32 u32len, U8* pu8Buf,
                    U32* pu32SendLen, U32 u32Timeout);

    /**
    \brief Receives data from smart card. CNcomment: �����ܿ��������ݡ�CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:�����CNend
    \param[in]  u32len  length  CNcomment: ׼���������ݵĳ���CNend
    \param[in]  pu8Buf  data buffer  CNcomment: ���յ�������CNend
    \param[out]  pu32ReceiveLen  length of receive success  CNcomment: ʵ�ʽ��յ����ݳ���CNend
    \param[in]  u32Timeout  wait timeout(in ms)  CNcomment:��ʱʱ��, ��λ�Ǻ���CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч�����CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_receive)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U32 u32Len, U8* pu8Buf,
                        U32* pu32ReceiveLen, U32 u32Timeout);

    /**
    \brief send command to smart card and reciver response. CNcomment: ���Ӧ�Ŀ���������ͽ���Ӧ��CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:�����CNend
    \param[in]  u32SendLen  length  CNcomment:  �������ݵĳ���CNend
    \param[in]  pu8SendBuf  send data buffer  CNcomment:  �����͵�����CNend
    \param[out]  pu32ReceiveLen  send data buffer  CNcomment:  ׼���������ݵĳ���CNend
    \param[out]  pu8ReceiveBuf  data buffer  CNcomment: ���յ�������CNend
    \param[in]  u32Timeout  wait timeout(in ms)  CNcomment:��ʱʱ��, ��λ�Ǻ���CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч�����CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_transfer)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U32 u32SendLen, U8* pu8SendBuf,
                         U32* pu32ReceiveLen, U8* pu8ReceiveBuf, U32 u32Timeout);

    /**
    \brief Obtains the ATR data of an SCI card. CNcomment: ��ȡSCI��ATR����CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:�����CNend
    \param[out]  pu8Len  length  CNcomment:  ��ȡATR �ĳ���CNend
    \param[out]  pu8Buf   data buffer  CNcomment:  ATR ����CNend
    \param[in]  u32Timeout  wait timeout(in ms)  CNcomment:��ʱʱ��, ��λ�Ǻ���CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч�����CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_get_atr)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U8* pu8Len, U8* pu8Buf, U32 u32Timeout);

    /**
    \brief adjust the communication parameters according to ATR. CNcomment:����ATR ����ͨѶ����CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:�����CNend
    \param[in]  pu8Buf   data buffer  CNcomment:  ATR ����CNend
    \param[in]  pu8Len  length  CNcomment:  ATR �ĳ���CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч�����CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_set_para_from_atr)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U8* pu8Buf, U32 u32Len);

    /**
    \brief get handle of an card. CNcomment:��ȡ���ܿ����.CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[out] handle handle.CNcomment:�����CNend
    \param[in]  enSmcPort  port  CNcomment:  �˿�CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_NOT_OPEN  invalid param.CNcomment:ʵ��û�д򿪡�CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:��������CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_get_active)(struct _SMC_DEVICE_S* pstDev, HANDLE* const pHandle, SMC_PORT_E enSmcPort);

    /**
    \brief remove the residual data. CNcomment: ����ײ�BUFF�еĲ�������.CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in] handle handle.CNcomment:�����CNend
    \retval ::SUCCESS  success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:û�г�ʼ����CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:��Ч����� CNend
    \retval ::FAILURE  failure.CNcomment:ʧ�ܡ� CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32  (*smc_flush)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle);

} SMC_DEVICE_S;

/**
 \brief direct get smc device api, for linux and android.CNcomment:��ȡ���ܿ��豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
 \attention \n
get smc device api, for linux and andorid.
CNcomment:��ȡ���ܿ��豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
 \retval  smc device pointer when success.CNcomment:�ɹ�����smc�豸ָ�롣CNend
 \retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
 \see \n
::SMC_DEVICE_S

 \par example
 */
SMC_DEVICE_S* getSmcDevice();

/**
\brief  Open HAL smc module device.CNcomment: ��HAL smcϵͳģ���豸 CNend
\attention \n
Open HAL smc module device(for compatible Android HAL).
CNcomment:��HAL smcϵͳģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice smc device structure.CNcomment:ϵͳsmc�豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::SMC_DEVICE_S

\par example
*/
static inline int smc_open(const struct hw_module_t* pstModule, SMC_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, SMC_HARDWARE_SMC0, (hw_device_t**)ppstDevice);
#else
    *ppstDevice = getSmcDevice();
    return SUCCESS;
#endif
}

/**
\brief  Close HAL smc module device.CNcomment:�ر�HAL smcģ���豸��CNend
\attention \n
Close HAL smc module device(for compatible Android HAL).
CNcomment:�ر�HAL smcģ���豸 (Ϊ����Android HAL�ṹ)��CNend
\param[in] pstDevice smc device structure.CNcomment:ϵͳsmc�豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� ��CNend
\see \n
::SMC_DEVICE_S

\par example
*/
static inline int smc_close(SMC_DEVICE_S* pstDevice)
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
#endif /* __cplusplus */

#endif /* __TVOS_HAL_SMC_H__ */
