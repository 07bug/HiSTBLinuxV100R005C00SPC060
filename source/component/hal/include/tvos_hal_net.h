#ifndef __HAL_NET_INTERFACE_H__
#define __HAL_NET_INTERFACE_H__

#include "tvos_hal_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/** CNcomment:IP��ַ���ȣ���IPV6����Ҫ�� CNend */
#define NET_IPV6_ADDR_LENGTH   23

/** CNcomment:IP��ַ���ȣ���IPV4����Ҫ�� CNend */
#define NET_IPV4_ADDR_LENGTH   15

/** CNcomment:IP��ַ���ȣ���IPV4����Ҫ�� CNend */
#define NET_MAC_ADDR_LENGTH    17

/** CNcomment:SSID��󳤶� CNend */
#define STA_MAX_SSID_LEN       256

/** CNcomment: STAɨ���AP mac��ַ��󳤶� CNend */
#define STA_AP_BSSID_LEN       17

/** max len of password *//** CNcomment:������󳤶� CNend */
#define MAX_PSSWD_LEN          64

/**max len of pppoe username*//**CNcomment:pppoe�û�����󳤶�CNend*/
#define NET_MAX_PPPOE_USERNAME_LEN 255

/**max len of pppoe password*//**CNcomment:pppoe������󳤶�CNend*/
#define NET_MAX_PPPOE_PASSWD_LEN 255

/**max len of pppoe device name*//**CNcomment:pppoe�豸�ڵ�����󳤶�CNend*/
#define NET_PPPOE_INTERFACE_LEN 4

/** CNcomment: �������� CNend */
typedef enum _NET_IPV_TYPE_E
{
    NET_IPV_TYPE_4  = 0,
    NET_IPV_TYPE_6,
    NET_IPV_TYPE_4_6,
    NET_IPV_TYPE_BUTT,
} NET_IPV_TYPE_E;

/** CNcomment: ����ID CNend */
typedef enum _NET_CARD_E
{
    NET_ETH_0    = 0x1 << 0,
    NET_ETH_1    = 0x1 << 1,
    NET_ETH_2    = 0x1 << 2,
    NET_ETH_3    = 0x1 << 3,
    NET_ETH_4    = 0x1 << 4,
    NET_ETH_5    = 0x1 << 5,
    NET_ETH_6    = 0x1 << 6,
    NET_ETH_7    = 0x1 << 7,
    NET_WLAN_0   = 0x1 << 8,
    NET_WLAN_1   = 0x1 << 9,
    NET_WLAN_2   = 0x1 << 10,
    NET_WLAN_3   = 0x1 << 11,
    NET_WLAN_4   = 0x1 << 12,
    NET_WLAN_5   = 0x1 << 13,
    NET_WLAN_6   = 0x1 << 14,
    NET_WLAN_7   = 0x1 << 15,
    NET_CARD_BUTT,
} NET_CARD_E;

/** CNcomment: ����ģ������ CNend */
typedef struct _NET_CAPBILITY_S
{
    U32   u32NetIdSet;
} NET_CAPBILITY_S;

/** CNcomment: ����������Ϣ CNend */
typedef struct _NET_CONFIG_S
{
    CHAR IpAddr[NET_IPV6_ADDR_LENGTH + 1];
    CHAR NetMask[NET_IPV4_ADDR_LENGTH + 1];
    CHAR GateWay[NET_IPV6_ADDR_LENGTH + 1];
    CHAR PrimaryDns[NET_IPV6_ADDR_LENGTH + 1];
    CHAR SecondDns[NET_IPV6_ADDR_LENGTH + 1];
} NET_CONFIG_S;

/** CNcomment: ����MAC��Ϣ CNend */
typedef struct _NET_MAC_S
{
    CHAR Mac[NET_MAC_ADDR_LENGTH + 1];
} NET_MAC_S;

/** CNcomment: ��������״̬ CNend */
typedef enum _NET_LINKSTATUS_E
{
    NET_LINK_STATUS_OFF = 0,
    NET_LINK_STATUS_ON,
    NET_LINK_STATUS_BUTT,
} NET_LINKSTATUS_E;

/** CNcomment:AP��ȫģʽ���� CNend */
typedef enum _WLAN_SECURITY_E
{
    WLAN_SECURITY_OPEN = 0,               /**< CNcomment:OPENģʽ CNend */
    WLAN_SECURITY_WEP,                    /**< CNcomment:WEPģʽ CNend */
    WLAN_SECURITY_WPA_WPA2_PSK,           /**< CNcomment:WPA-PSK��WPA2-PSKģʽ CNend */
    WLAN_SECURITY_WPA_WPA2_EAP,           /**< CNcomment:WPA-EAP��WPA2-EAPģʽ CNend */
    WLAN_SECURITY_WAPI_PSK,               /**< CNcomment:WAPI-PSKģʽ CNend */
    WLAN_SECURITY_WAPI_CERT,              /**< CNcomment:WAPI-CERTģʽ CNend */
    WLAN_SECURITY_BUTT,
} WLAN_SECURITY_E;

/** network information *//** CNcomment:AP��Ϣ�ṹ�� CNend */
typedef struct _WLAN_STA_AccessPoint_S
{
    CHAR ssid[STA_MAX_SSID_LEN + 1];      /**< CNcomment:AP��SSID CNend */
    CHAR bssid[STA_AP_BSSID_LEN + 1];     /**< CNcomment:AP��MAC��ַ CNend */
    U32  level;                           /**< CNcomment:AP���ź�ǿ�ȣ�0 - 100 CNend */
    S32  rssi;                            /**< CNcomment:AP���ź�ǿ�ȣ�dBmֵ CNend */
    U32  channel;                         /**< CNcomment:AP���ŵ� CNend */
    WLAN_SECURITY_E security;             /**< CNcomment:AP�İ�ȫģʽ CNend */
} WLAN_STA_AccessPoint_S;

/** CNcomment:��Ҫ���ӵ�AP���� CNend */
typedef struct _WLAN_STA_Config_S
{
    CHAR   ssid[STA_MAX_SSID_LEN + 1];    /**< CNcomment:AP��SSID CNend */
    CHAR   bssid[STA_AP_BSSID_LEN + 1];   /**< CNcomment:AP��MAC��ַ CNend */
    WLAN_SECURITY_E security;             /**< CNcomment:AP�İ�ȫģʽ CNend */
    CHAR   psswd[MAX_PSSWD_LEN + 1];      /**< CNcomment:���� CNend */
    BOOL   hidden_ssid;                   /**< CNcomment:AP�Ƿ�������SSID CNend */
} WLAN_STA_Config_S;

/** CNcomment:��������״̬���� CNend */
typedef enum _WLAN_STA_CONN_STATE_E
{
    WLAN_STA_CONN_STATUS_DISCONNECTED = 0,  /**< CNcomment:����Ͽ�״̬ CNend */
    WLAN_STA_CONN_STATUS_CONNECTING,        /**< CNcomment:��������AP״̬ CNend */
    WLAN_STA_CONN_STATUS_CONNECTED,         /**< CNcomment:������AP״̬ CNend */
    WLAN_STA_CONN_STATUS_BUTT,
} WLAN_STA_CONN_STATE_E;

/** CNcomment:��������״̬��Ϣ CNend */
typedef struct _WLAN_STA_CONN_Status_S
{
    WLAN_STA_CONN_STATE_E state;            /**< CNcomment:���������״̬ CNend */
    WLAN_STA_AccessPoint_S ap;              /**< CNcomment:�����ϻ����������ӵ�AP��Ϣ CNend */
} WLAN_STA_CONN_Status_S;

/** CNcomment: STAɨ�������¼� CNend */
typedef enum _WLAN_STA_EVENT_E
{
    WLAN_STA_EVENT_SCAN_IDLE = 0,       /**wlan scan idle event*//**CNcomment:wlan �����¼�CNend*/
    WLAN_STA_EVENT_SCAN_SCANNING,       /**wlan scanning event*//**CNcomment:wlan���������¼�CNend*/
    WLAN_STA_EVENT_SCAN_COMPLETE,       /**wlan scan complete event*//**CNcomment:wlan��������¼�CNend*/
    WLAN_STA_EVENT_SCAN_ERROR,          /**wlan scan error event*//**CNcomment:wlan�������ִ����¼�CNend*/
    WLAN_STA_EVENT_SCAN_BUTT,
} WLAN_STA_EVENT_E;

/**Interface  event type */
/**CNcomment:�����¼�*/
typedef enum _NET_INTERFACE_EVENT_E
{
    NET_INTERFACE_UP = 0,                  /**iface link up*//**CNcomment:����up�¼�CNend*/
    NET_INTERFACE_DOWN,                    /**iface link down*//**CNcomment:����down�¼�CNend*/
    NET_INTERFACE_BUTT
} NET_INTERFACE_EVENT_E;

/**DHCP  Connection event type */
/**CNcomment:DHCP ��Ϣ�¼�*/
typedef enum _NET_DHCP_CONN_EVENT_E
{
    NET_DHCP_CONN_EVENT_CONNECTTING = 0,        /**< Connecting to dhcp server*//**< CNcomment:��������dhcp������CNend */
    NET_DHCP_CONN_EVENT_CONNECTED,              /**< Connected to dhcp server *//**< CNcomment:������dhcp������CNend */
    NET_DHCP_CONN_EVENT_CONNECT_FAIL,           /**< Fail to Connect dhcp server *//**< CNcomment:����dhcp������ʧ��CNend */
    NET_DHCP_CONN_EVENT_BUTT
} NET_DHCP_CONN_EVENT_E;

/**PPPOE  Connection event type */
/**CNcomment:PPPoE ��Ϣ�¼�*/
typedef enum _NET_PPPOE_CONN_EVENT_E
{
    NET_PPPOE_CONN_EVENT_CONNECTTING = 0,      /**< Connecting to pppoe server*//**< CNcomment:��������pppoe ������CNend */
    NET_PPPOE_CONN_EVENT_CONNECTED,            /**< Connected to pppoe server *//**< CNcomment:������pppoe������CNend */
    NET_PPPOE_CONN_EVENT_AUTH_FAIL,            /**< auth fail to connect to pppoe server*//**< CNcomment:����pppoe ������,�û����������CNend */
    NET_PPPOE_CONN_EVENT_CONNECT_FAIL,         /**< Fail to Connect pppoe server *//**< CNcomment:����pppoe������ʧ��CNend */
    NET_PPPOE_CONN_EVENT_BUTT
} NET_PPPOE_CONN_EVENT_E;

/** PPPoE information *//** CNcomment:PPPoE ��ϢCNend */
typedef struct _NET_PPPOE_INFO_S
{
    NET_CARD_E    enNetCardID;                                            /**< Net type *//**< CNcomment:net ����CNend */
    CHAR          acUser[NET_MAX_PPPOE_USERNAME_LEN + 1];   /**< User name */ /**< CNcomment:�û���CNend */
    CHAR          acPw[NET_MAX_PPPOE_PASSWD_LEN + 1];        /**< Password */ /**< CNcomment:����CNend */
} NET_PPPOE_INFO_S;

/** HalNetinterface api */
/** CNcomment:wifiɨ���¼� CNend */
typedef VOID (*NET_WLAN_STA_SCAN_EVTCB)(WLAN_STA_EVENT_E enEvent, VOID* pPrivData);

/** CNcomment:wifi����ap�¼� CNend */
typedef VOID (*NET_WLAN_STA_LINKAP_EVTCB)(WLAN_STA_CONN_STATE_E enEvent, VOID* pPrivData);

/**CNcomment:�����¼�*/
typedef VOID (*NET_INTERFACE_EVTCB)(NET_INTERFACE_EVENT_E enEvent,VOID *pPrivData);

/**CNcomment:dhcp �����¼�*/
typedef VOID (*NET_DHCP_CONN_EVTCB)(NET_DHCP_CONN_EVENT_E enEvent, VOID* pPrivData);

/**CNcomment:pppoe �����¼�*/
typedef VOID (*NET_PPPOE_CONN_EVTCB)(NET_PPPOE_CONN_EVENT_E enEvent, VOID* pPrivData);

/** CNcomment: �����ʼ��CNend */
S32 net_init(VOID);

/** CNcomment: ����ȥ��ʼ�� CNend */
S32 net_deinit(VOID);

/** CNcomment: ��ȡ�������� CNend */
S32 net_get_capability(NET_CAPBILITY_S* const pNetCapability);

/** CNcomment: ����ָ������ CNend */
S32 net_open(NET_CARD_E enNetCardID);

/** CNcomment: �ر�ָ������ CNend */
S32 net_close(NET_CARD_E enNetCardID);

/** CNcomment: ����IPV���ͣ�IPV4����IPV6 CNend */
S32 net_set_ipv_type(NET_CARD_E enNetCardID, NET_IPV_TYPE_E eIpvType);

/** CNcomment: ��ȡ���ڿ���״̬ CNend */
S32 net_get_openstatus(NET_CARD_E enNetCardID, BOOL* pbOpen);

/** CNcomment: �������ڻ�����Ϣ CNend */
S32 net_set_config(NET_CARD_E enNetCardID, const NET_CONFIG_S* pNetConfig);

/** CNcomment: ��ȡ���ڻ�����Ϣ CNend */
S32 net_get_config(NET_CARD_E enNetCardID,  NET_CONFIG_S* const pNetConfig);

/** CNcomment:��������Mac ��ַ��Ϣ CNend */
S32 net_set_mac(NET_CARD_E enNetCardID, const NET_MAC_S* pNetConfig);

/** CNcomment:��ȡ����Mac ��ַ��Ϣ CNend */
S32 net_get_mac(NET_CARD_E enNetCardID,  NET_MAC_S* const pNetConfig);

/** CNcomment:��ȡ��������״̬ CNend */
S32 net_get_linkstatus(NET_CARD_E enNetCardID,  NET_LINKSTATUS_E* pLinkStatus);

/**CNcomment:��������up/down�¼����*/
S32 net_start_interface_observer(NET_INTERFACE_EVTCB interfaceCB);

/**CNcomment:ֹͣ���ڼ��*/
S32 net_stop_interface_observer(NET_INTERFACE_EVTCB interfaceCB);

/** CNcomment:Ϊ��Ӧ���ڿ���DHCP���� CNend */
S32 net_open_dhcp(NET_CARD_E enNetCardID, NET_DHCP_CONN_EVTCB dhcpCB);

/** CNcomment:Ϊ��Ӧ���ڹر�DHCP���� CNend */
S32 net_close_dhcp(NET_CARD_E enNetCardID);

/** CNcomment:Ϊ��Ӧ���ڿ���pppoe����  */
S32 net_open_pppoe(const NET_PPPOE_INFO_S* pPppoeConfig, NET_PPPOE_CONN_EVTCB pppoeCB);

/** CNcomment:Ϊ��Ӧ���ڹر�pppoe���� CNend */
S32 net_close_pppoe(NET_CARD_E enNetCardID);

/** CNcomment:��ȡ������Ӧ��pppoe��ַ��ϢCNend */
S32 net_get_pppoe_address(NET_CARD_E enNetCardID,NET_CONFIG_S* const pNetConfig);

/** CNcomment:���ip��ַ��Ϣ CNend */
S32 net_clear_address(NET_CARD_E enNetCardID);

/** CNcomment:Ϊ��Ӧwlan��������staģʽ CNend */
S32 net_sta_start(NET_CARD_E enNetCardID, NET_WLAN_STA_SCAN_EVTCB pEventCallback, NET_WLAN_STA_LINKAP_EVTCB pApEventCallback);

/** CNcomment:Ϊ��Ӧwlan��������scanɨ�� CNend */
S32 net_sta_startscan(NET_CARD_E enNetCardID);

/** CNcomment:Ϊ��Ӧwlan����ֹͣstaģʽ CNend */
S32 net_sta_stop(NET_CARD_E enNetCardID);

/** CNcomment:��Ӧwlan���ڻ�ȡscan״̬ CNend */
S32 net_sta_getscanstatus(NET_CARD_E enNetCardID, WLAN_STA_EVENT_E* pScanStatus);

/** CNcomment:��ȡ��Ӧwlan����ɨ�赽��ap���� CNend */
S32 net_sta_getresultnum(NET_CARD_E enNetCardID, U32* pNumber);

/** CNcomment:��ȡ��Ӧwlan����ɨ�赽��AP�б���Ϣ CNend */
S32 net_sta_getresult(NET_CARD_E enNetCardID,  WLAN_STA_AccessPoint_S* pAPList, U32 ListNodeNumber, U32* pGettedNumber);

/** CNcomment:��Ӧwlan��������AP CNend */
S32 net_sta_connect(NET_CARD_E enNetCardID, const WLAN_STA_Config_S* pConfig);

/** CNcomment:��Ӧwlan���ڶϿ�AP CNend */
S32 net_sta_disconnect(NET_CARD_E enNetCardID);

/** CNcomment:wlan�ڵ�����״̬ CNend */
S32 net_sta_getconnectstatus(NET_CARD_E enNetCardID, WLAN_STA_CONN_Status_S* pStatus);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*__HAL_NET_INTERFACE_H__*/
