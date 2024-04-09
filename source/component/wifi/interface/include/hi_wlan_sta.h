/******************************************************************************
  Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
  File Name     : hi_wlan_sta.h
  Version       : Initial Draft
  Author        : Hisilicon WiFi software group
  Created       :
  Last Modified :
  Description   : header file for Wi-Fi Station component
  Function List :
  History       :
  1.Date        :
  Author        :
  Modification  : Created file
******************************************************************************/

/**
 * \file
 * \brief describle the information about WiFi STA component. CNcomment:�ṩWiFi STA�����ؽӿڡ����ݽṹ��Ϣ��CNend
 */

#ifndef __HI_WLAN_STA_H__
#define __HI_WLAN_STA_H__

#include "hi_type.h"
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup     WLAN_STA */
/** @{ */  /** <!-- [WLAN_STA] */

#ifndef HI_WLAN_COMMON_DEF
#define HI_WLAN_COMMON_DEF

#define MAX_SSID_LEN    256    /** max len of AP's ssid *//** CNcomment:SSID��󳤶� */
#define BSSID_LEN       17     /** len of MAC address *//** CNcomment:MAC��ַ���� */
#define MAX_PSSWD_LEN   64     /** max len of password *//** CNcomment:������󳤶� */

/** invalid parameter */
/** CNcomment:��Ч�Ĳ��� -2 */
#define HI_WLAN_INVALID_PARAMETER           -2

/** no supported WiFi device found */
/** CNcomment:û���ҵ�WiFi�豸 -3 */
#define HI_WLAN_DEVICE_NOT_FOUND            -3

/** load driver fail */
/** CNcomment:��������ʧ�� -4 */
#define HI_WLAN_LOAD_DRIVER_FAIL            -4

/** run wpa_supplicant process fail */
/** CNcomment:����wpa_supplicantʧ�� -5 */
#define HI_WLAN_START_SUPPLICANT_FAIL       -5

/** cann't connect to wpa_supplicant */
/** CNcomment:����wpa_supplicantʧ�� -6 */
#define HI_WLAN_CONNECT_TO_SUPPLICANT_FAIL  -6

/** cann't send command to wpa_supplicant */
/** CNcomment:���������wpa_supplicantʧ�� -7 */
#define HI_WLAN_SEND_COMMAND_FAIL           -7

/** run hostapd process fail */
/** CNcomment:����hostapdʧ�� -8 */
#define HI_WLAN_START_HOSTAPD_FAIL          -8

/** network security mode type *//** CNcomment:AP��ȫģʽ���� */
typedef enum hiHI_WLAN_SECURITY_E
{
    HI_WLAN_SECURITY_OPEN,          /**< OPEN mode, not encrypted *//** CNcomment:OPENģʽ */
    HI_WLAN_SECURITY_WEP,           /**< WEP mode *//** CNcomment:WEPģʽ */
    HI_WLAN_SECURITY_WPA_WPA2_PSK,  /**< WPA-PSK/WPA2-PSK mode *//** CNcomment:WPA-PSK��WPA2-PSKģʽ */
    HI_WLAN_SECURITY_WPA_WPA2_EAP,  /**< WPA-EAP/WPA2-EAP mode *//** CNcomment:WPA-EAP��WPA2-EAPģʽ */
    HI_WLAN_SECURITY_WAPI_PSK,      /**< WAPI-PSK mode *//** CNcomment:WAPI-PSKģʽ */
    HI_WLAN_SECURITY_WAPI_CERT,     /**< WAPI-CERT mode *//** CNcomment:WAPI-CERTģʽ */
    HI_WLAN_SECURITY_BUTT,
} HI_WLAN_SECURITY_E;

#endif /* HI_WLAN_COMMON_DEF */

/** WiFi event type *//** CNcomment:WiFi�¼����� */
typedef enum hiHI_WLAN_STA_EVENT_E
{
    HI_WLAN_STA_EVENT_DISCONNECTED,    /**< network disconnected event *//** CNcomment:����Ͽ��¼� */
    HI_WLAN_STA_EVENT_SCAN_RESULTS_AVAILABLE,    /**< scan done event *//** CNcomment:ɨ������¼� */
    HI_WLAN_STA_EVENT_CONNECTING,      /**< try to connect to network event *//** CNcomment:��������AP�¼� */
    HI_WLAN_STA_EVENT_CONNECTED,       /**< network connected event *//** CNcomment:������AP�¼� */
    HI_WLAN_STA_EVENT_SUPP_STOPPED,    /**< supplicant abnormal event *//** CNcomment:wpa_supplicantֹͣ�¼� */
    HI_WLAN_STA_EVENT_DRIVER_STOPPED,  /**< driver abnormal event *//** CNcomment:�����˳��¼� */
    HI_WLAN_STA_EVENT_BUTT,
} HI_WLAN_STA_EVENT_E;

/** connection state type *//** CNcomment:��������״̬���� */
typedef enum hiHI_WLAN_STA_CONN_STATE_E
{
    HI_WLAN_STA_CONN_STATUS_DISCONNECTED,  /**< not connected to any network *//** CNcomment:����Ͽ�״̬ */
    HI_WLAN_STA_CONN_STATUS_CONNECTING,    /**< connecting to a network *//** CNcomment:��������AP״̬ */
    HI_WLAN_STA_CONN_STATUS_CONNECTED,     /**< connected to a network *//** CNcomment:������AP״̬ */
    HI_WLAN_STA_CONN_STATUS_BUTT,
} HI_WLAN_STA_CONN_STATE_E;

/** network information *//** CNcomment:AP��Ϣ�ṹ�� */
typedef struct hiHI_WLAN_STA_ACCESSPOINT_S
{
    HI_CHAR ssid[MAX_SSID_LEN+1];      /**< AP's SSID *//** CNcomment:AP��SSID */
    HI_CHAR bssid[BSSID_LEN+1];        /**< AP's MAC address *//** CNcomment:AP��MAC��ַ */
    HI_U32  level;                     /**< AP's signal level, 0 - 100 *//** CNcomment:AP���ź�ǿ�ȣ�0 - 100 */
    HI_U32  channel;                   /**< AP's channel number *//** CNcomment:AP���ŵ� */
    HI_WLAN_SECURITY_E security;       /**< AP's security mode *//** CNcomment:AP�İ�ȫģʽ */
} HI_WLAN_STA_ACCESSPOINT_S;

/** network configuration *//** CNcomment:��Ҫ���ӵ�AP���� */
typedef struct hiHI_WLAN_STA_CONFIG_S
{
    HI_CHAR   ssid[MAX_SSID_LEN+1];      /**< network's SSID *//** CNcomment:AP��SSID */
    HI_CHAR   bssid[BSSID_LEN+1];        /**< network's MAC address *//** CNcomment:AP��MAC��ַ */
    HI_WLAN_SECURITY_E security;         /**< network's security mode *//** CNcomment:AP�İ�ȫģʽ */
    HI_CHAR   psswd[MAX_PSSWD_LEN+1];    /**< network's password, if not OPEN mode *//** CNcomment:���� */
    HI_BOOL   hidden_ssid;               /**< whether network hiddens it's SSID *//** CNcomment:AP�Ƿ�������SSID */
} HI_WLAN_STA_CONFIG_S;

/** network status information *//** CNcomment:��������״̬��Ϣ */
typedef struct hiHI_WLAN_STA_CONN_STATUS_S
{
    HI_WLAN_STA_CONN_STATE_E state;    /**< connection state *//** CNcomment:���������״̬ */
    HI_WLAN_STA_ACCESSPOINT_S ap;      /**< network information which connected or connecting *//** CNcomment:�����ϻ����������ӵ�AP��Ϣ */
} HI_WLAN_STA_CONN_STATUS_S;


/** Callback function of receiving WiFi events *//** CNcomment:����WiFi�¼��Ļص����� */
typedef HI_VOID (*HI_WLAN_STA_Event_CallBack)(HI_WLAN_STA_EVENT_E event, HI_VOID *pstPrivData);

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup     WLAN_STA*/
/** @{*/  /** <!-- [WLAN_STA]*/

/**
\brief: Initialize STA.CNcomment:��ʼ��STA CNend
\attention \n
\param    N/A.CNcomment:�� CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\see \n
::HI_WLAN_STA_DeInit
*/
HI_S32 HI_WLAN_STA_Init(HI_VOID);

/**
\brief: Deintialize STA.CNcomment:ȥ��ʼ��STA CNend
\attention \n
\param  N/A.CNcomment:�� CNend
\retval N/A.CNcomment:�� CNend
\see \n
::HI_WLAN_STA_Init
*/
HI_VOID HI_WLAN_STA_DeInit(HI_VOID);

/**
\brief: Open WiFi STA device.CNcomment:��WiFi STA�豸 CNend
\attention \n
\param[out] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\retval  ::HI_WLAN_DEVICE_NOT_FOUND
\retval  ::HI_WLAN_LOAD_DRIVER_FAIL
\see \n
::HI_WLAN_STA_Close
*/
HI_S32 HI_WLAN_STA_Open(HI_CHAR *ifname);

/**
\brief: Close WiFi STA device.CNcomment:�ر�WiFi STA�豸 CNend
\attention \n
\param[in] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\see \n
::HI_WLAN_STA_Open
*/
HI_S32 HI_WLAN_STA_Close(HI_CHAR *ifname);

/**
\brief: Start WiFi STA.CNcomment:����WiFi STA CNend
\attention \n
\param[in] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\param[in] pfnEventCb  call back function that receives events.CNcomment:�����¼��Ļص����� CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\retval  ::HI_WLAN_START_SUPPLICANT_FAIL
\retval  ::HI_WLAN_CONNECT_TO_SUPPLICANT_FAIL
\see \n
::HI_WLAN_STA_Stop
*/
HI_S32 HI_WLAN_STA_Start(HI_CHAR *ifname, HI_WLAN_STA_Event_CallBack pfnEventCb);

/**
\brief: Stop WiFi STA.CNcomment:ͣ��WiFi STA CNend
\attention \n
\param[in] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\see \n
::HI_WLAN_STA_Start
*/
HI_S32 HI_WLAN_STA_Stop(HI_CHAR *ifname);

/**
\brief: Start to scan.CNcomment:��ʼɨ�� CNend
\attention \n
\param[in] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\retval  ::HI_WLAN_SEND_COMMAND_FAIL
\see \n
*/
HI_S32 HI_WLAN_STA_StartScan(HI_CHAR *ifname);

/**
\brief: Get scan results.CNcomment:��ȡɨ�赽��AP CNend
\attention \n
\param[in] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\param[out] pstApList AP list.CNcomment: ����ɨ�赽��AP�б� CNend
\param[inout] pstApNum  number of APs.CNcomment: AP�б���AP������ CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\retval  ::HI_WLAN_SEND_COMMAND_FAIL
\see \n
*/
HI_S32 HI_WLAN_STA_GetScanResults(HI_CHAR *ifname, HI_WLAN_STA_ACCESSPOINT_S *pstApList,
                                    HI_U32 *pstApNum);

/**
\brief: Connect to AP.CNcomment:��ʼ����AP CNend
\attention \n
\param[in] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\param[in] pstStaCfg  AP configuration try to connect.CNcomment:��Ҫ���ӵ�AP����Ϣ CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\retval  ::HI_WLAN_SEND_COMMAND_FAIL
\see \n
::HI_WLAN_STA_Disconnect
*/
HI_S32 HI_WLAN_STA_Connect(HI_CHAR *ifname, HI_WLAN_STA_CONFIG_S *pstStaCfg);

/**
\brief: Disconnect to AP.CNcomment:�Ͽ����� CNend
\attention \n
\param[in] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\retval  ::HI_WLAN_SEND_COMMAND_FAIL
\see \n
::HI_WLAN_STA_Connect
*/
HI_S32 HI_WLAN_STA_Disconnect(HI_CHAR *ifname);

/**
\brief: Get current network connection status.CNcomment:��õ�ǰ������״̬��Ϣ CNend
\attention \n
\param[in] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\param[out] pstConnStatus network connection status.CNcomment:��������״̬��Ϣ CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\retval  ::HI_WLAN_SEND_COMMAND_FAIL
\see \n
*/
HI_S32 HI_WLAN_STA_GetConnectionStatus(HI_CHAR *ifname, HI_WLAN_STA_CONN_STATUS_S *pstConnStatus);

/**
\brief: Get local WiFi MAC address.CNcomment:��ȡ����WiFi MAC��ַ CNend
\attention \n
\param[in] ifname  WiFi network interface name.CNcomment:WiFi����ӿ���, ��: wlan0 CNend
\param[out] pstMac  MAC address of local WiFi.CNcomment:���汾��WiFi MAC��ַ CNend
\retval  ::HI_SUCCESS
\retval  ::HI_FAILURE
\retval  ::HI_WLAN_INVALID_PARAMETER
\see \n
*/
HI_S32 HI_WLAN_STA_GetMacAddress(HI_CHAR *ifname, HI_CHAR *pstMac);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
#endif /* __HI_WLAN_STA_H__ */
