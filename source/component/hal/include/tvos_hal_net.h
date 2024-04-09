#ifndef __HAL_NET_INTERFACE_H__
#define __HAL_NET_INTERFACE_H__

#include "tvos_hal_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/** CNcomment:IP地址长度，按IPV6长度要求 CNend */
#define NET_IPV6_ADDR_LENGTH   23

/** CNcomment:IP地址长度，按IPV4长度要求 CNend */
#define NET_IPV4_ADDR_LENGTH   15

/** CNcomment:IP地址长度，按IPV4长度要求 CNend */
#define NET_MAC_ADDR_LENGTH    17

/** CNcomment:SSID最大长度 CNend */
#define STA_MAX_SSID_LEN       256

/** CNcomment: STA扫描的AP mac地址最大长度 CNend */
#define STA_AP_BSSID_LEN       17

/** max len of password *//** CNcomment:密码最大长度 CNend */
#define MAX_PSSWD_LEN          64

/**max len of pppoe username*//**CNcomment:pppoe用户名最大长度CNend*/
#define NET_MAX_PPPOE_USERNAME_LEN 255

/**max len of pppoe password*//**CNcomment:pppoe密码最大长度CNend*/
#define NET_MAX_PPPOE_PASSWD_LEN 255

/**max len of pppoe device name*//**CNcomment:pppoe设备节点名最大长度CNend*/
#define NET_PPPOE_INTERFACE_LEN 4

/** CNcomment: 网络类型 CNend */
typedef enum _NET_IPV_TYPE_E
{
    NET_IPV_TYPE_4  = 0,
    NET_IPV_TYPE_6,
    NET_IPV_TYPE_4_6,
    NET_IPV_TYPE_BUTT,
} NET_IPV_TYPE_E;

/** CNcomment: 网卡ID CNend */
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

/** CNcomment: 网络模块能力 CNend */
typedef struct _NET_CAPBILITY_S
{
    U32   u32NetIdSet;
} NET_CAPBILITY_S;

/** CNcomment: 网络设置信息 CNend */
typedef struct _NET_CONFIG_S
{
    CHAR IpAddr[NET_IPV6_ADDR_LENGTH + 1];
    CHAR NetMask[NET_IPV4_ADDR_LENGTH + 1];
    CHAR GateWay[NET_IPV6_ADDR_LENGTH + 1];
    CHAR PrimaryDns[NET_IPV6_ADDR_LENGTH + 1];
    CHAR SecondDns[NET_IPV6_ADDR_LENGTH + 1];
} NET_CONFIG_S;

/** CNcomment: 网络MAC信息 CNend */
typedef struct _NET_MAC_S
{
    CHAR Mac[NET_MAC_ADDR_LENGTH + 1];
} NET_MAC_S;

/** CNcomment: 网络连接状态 CNend */
typedef enum _NET_LINKSTATUS_E
{
    NET_LINK_STATUS_OFF = 0,
    NET_LINK_STATUS_ON,
    NET_LINK_STATUS_BUTT,
} NET_LINKSTATUS_E;

/** CNcomment:AP安全模式类型 CNend */
typedef enum _WLAN_SECURITY_E
{
    WLAN_SECURITY_OPEN = 0,               /**< CNcomment:OPEN模式 CNend */
    WLAN_SECURITY_WEP,                    /**< CNcomment:WEP模式 CNend */
    WLAN_SECURITY_WPA_WPA2_PSK,           /**< CNcomment:WPA-PSK或WPA2-PSK模式 CNend */
    WLAN_SECURITY_WPA_WPA2_EAP,           /**< CNcomment:WPA-EAP或WPA2-EAP模式 CNend */
    WLAN_SECURITY_WAPI_PSK,               /**< CNcomment:WAPI-PSK模式 CNend */
    WLAN_SECURITY_WAPI_CERT,              /**< CNcomment:WAPI-CERT模式 CNend */
    WLAN_SECURITY_BUTT,
} WLAN_SECURITY_E;

/** network information *//** CNcomment:AP信息结构体 CNend */
typedef struct _WLAN_STA_AccessPoint_S
{
    CHAR ssid[STA_MAX_SSID_LEN + 1];      /**< CNcomment:AP的SSID CNend */
    CHAR bssid[STA_AP_BSSID_LEN + 1];     /**< CNcomment:AP的MAC地址 CNend */
    U32  level;                           /**< CNcomment:AP的信号强度，0 - 100 CNend */
    S32  rssi;                            /**< CNcomment:AP的信号强度，dBm值 CNend */
    U32  channel;                         /**< CNcomment:AP的信道 CNend */
    WLAN_SECURITY_E security;             /**< CNcomment:AP的安全模式 CNend */
} WLAN_STA_AccessPoint_S;

/** CNcomment:需要连接的AP配置 CNend */
typedef struct _WLAN_STA_Config_S
{
    CHAR   ssid[STA_MAX_SSID_LEN + 1];    /**< CNcomment:AP的SSID CNend */
    CHAR   bssid[STA_AP_BSSID_LEN + 1];   /**< CNcomment:AP的MAC地址 CNend */
    WLAN_SECURITY_E security;             /**< CNcomment:AP的安全模式 CNend */
    CHAR   psswd[MAX_PSSWD_LEN + 1];      /**< CNcomment:密码 CNend */
    BOOL   hidden_ssid;                   /**< CNcomment:AP是否是隐藏SSID CNend */
} WLAN_STA_Config_S;

/** CNcomment:网络连接状态类型 CNend */
typedef enum _WLAN_STA_CONN_STATE_E
{
    WLAN_STA_CONN_STATUS_DISCONNECTED = 0,  /**< CNcomment:网络断开状态 CNend */
    WLAN_STA_CONN_STATUS_CONNECTING,        /**< CNcomment:正在连接AP状态 CNend */
    WLAN_STA_CONN_STATUS_CONNECTED,         /**< CNcomment:连接上AP状态 CNend */
    WLAN_STA_CONN_STATUS_BUTT,
} WLAN_STA_CONN_STATE_E;

/** CNcomment:网络连接状态信息 CNend */
typedef struct _WLAN_STA_CONN_Status_S
{
    WLAN_STA_CONN_STATE_E state;            /**< CNcomment:网络的连接状态 CNend */
    WLAN_STA_AccessPoint_S ap;              /**< CNcomment:连接上或者正在连接的AP信息 CNend */
} WLAN_STA_CONN_Status_S;

/** CNcomment: STA扫描网络事件 CNend */
typedef enum _WLAN_STA_EVENT_E
{
    WLAN_STA_EVENT_SCAN_IDLE = 0,       /**wlan scan idle event*//**CNcomment:wlan 空闲事件CNend*/
    WLAN_STA_EVENT_SCAN_SCANNING,       /**wlan scanning event*//**CNcomment:wlan正在搜索事件CNend*/
    WLAN_STA_EVENT_SCAN_COMPLETE,       /**wlan scan complete event*//**CNcomment:wlan搜索完成事件CNend*/
    WLAN_STA_EVENT_SCAN_ERROR,          /**wlan scan error event*//**CNcomment:wlan搜索出现错误事件CNend*/
    WLAN_STA_EVENT_SCAN_BUTT,
} WLAN_STA_EVENT_E;

/**Interface  event type */
/**CNcomment:网口事件*/
typedef enum _NET_INTERFACE_EVENT_E
{
    NET_INTERFACE_UP = 0,                  /**iface link up*//**CNcomment:网口up事件CNend*/
    NET_INTERFACE_DOWN,                    /**iface link down*//**CNcomment:网口down事件CNend*/
    NET_INTERFACE_BUTT
} NET_INTERFACE_EVENT_E;

/**DHCP  Connection event type */
/**CNcomment:DHCP 消息事件*/
typedef enum _NET_DHCP_CONN_EVENT_E
{
    NET_DHCP_CONN_EVENT_CONNECTTING = 0,        /**< Connecting to dhcp server*//**< CNcomment:正在连接dhcp服务器CNend */
    NET_DHCP_CONN_EVENT_CONNECTED,              /**< Connected to dhcp server *//**< CNcomment:连接上dhcp服务器CNend */
    NET_DHCP_CONN_EVENT_CONNECT_FAIL,           /**< Fail to Connect dhcp server *//**< CNcomment:连接dhcp服务器失败CNend */
    NET_DHCP_CONN_EVENT_BUTT
} NET_DHCP_CONN_EVENT_E;

/**PPPOE  Connection event type */
/**CNcomment:PPPoE 消息事件*/
typedef enum _NET_PPPOE_CONN_EVENT_E
{
    NET_PPPOE_CONN_EVENT_CONNECTTING = 0,      /**< Connecting to pppoe server*//**< CNcomment:正在连接pppoe 服务器CNend */
    NET_PPPOE_CONN_EVENT_CONNECTED,            /**< Connected to pppoe server *//**< CNcomment:连接上pppoe服务器CNend */
    NET_PPPOE_CONN_EVENT_AUTH_FAIL,            /**< auth fail to connect to pppoe server*//**< CNcomment:连接pppoe 服务器,用户名密码错误CNend */
    NET_PPPOE_CONN_EVENT_CONNECT_FAIL,         /**< Fail to Connect pppoe server *//**< CNcomment:连接pppoe服务器失败CNend */
    NET_PPPOE_CONN_EVENT_BUTT
} NET_PPPOE_CONN_EVENT_E;

/** PPPoE information *//** CNcomment:PPPoE 信息CNend */
typedef struct _NET_PPPOE_INFO_S
{
    NET_CARD_E    enNetCardID;                                            /**< Net type *//**< CNcomment:net 类型CNend */
    CHAR          acUser[NET_MAX_PPPOE_USERNAME_LEN + 1];   /**< User name */ /**< CNcomment:用户名CNend */
    CHAR          acPw[NET_MAX_PPPOE_PASSWD_LEN + 1];        /**< Password */ /**< CNcomment:密码CNend */
} NET_PPPOE_INFO_S;

/** HalNetinterface api */
/** CNcomment:wifi扫描事件 CNend */
typedef VOID (*NET_WLAN_STA_SCAN_EVTCB)(WLAN_STA_EVENT_E enEvent, VOID* pPrivData);

/** CNcomment:wifi连接ap事件 CNend */
typedef VOID (*NET_WLAN_STA_LINKAP_EVTCB)(WLAN_STA_CONN_STATE_E enEvent, VOID* pPrivData);

/**CNcomment:网口事件*/
typedef VOID (*NET_INTERFACE_EVTCB)(NET_INTERFACE_EVENT_E enEvent,VOID *pPrivData);

/**CNcomment:dhcp 连接事件*/
typedef VOID (*NET_DHCP_CONN_EVTCB)(NET_DHCP_CONN_EVENT_E enEvent, VOID* pPrivData);

/**CNcomment:pppoe 连接事件*/
typedef VOID (*NET_PPPOE_CONN_EVTCB)(NET_PPPOE_CONN_EVENT_E enEvent, VOID* pPrivData);

/** CNcomment: 网络初始化CNend */
S32 net_init(VOID);

/** CNcomment: 网络去初始化 CNend */
S32 net_deinit(VOID);

/** CNcomment: 获取网络能力 CNend */
S32 net_get_capability(NET_CAPBILITY_S* const pNetCapability);

/** CNcomment: 开启指定网口 CNend */
S32 net_open(NET_CARD_E enNetCardID);

/** CNcomment: 关闭指定网口 CNend */
S32 net_close(NET_CARD_E enNetCardID);

/** CNcomment: 设置IPV类型，IPV4或者IPV6 CNend */
S32 net_set_ipv_type(NET_CARD_E enNetCardID, NET_IPV_TYPE_E eIpvType);

/** CNcomment: 获取网口开启状态 CNend */
S32 net_get_openstatus(NET_CARD_E enNetCardID, BOOL* pbOpen);

/** CNcomment: 设置网口基本信息 CNend */
S32 net_set_config(NET_CARD_E enNetCardID, const NET_CONFIG_S* pNetConfig);

/** CNcomment: 获取网口基本信息 CNend */
S32 net_get_config(NET_CARD_E enNetCardID,  NET_CONFIG_S* const pNetConfig);

/** CNcomment:设置网口Mac 地址信息 CNend */
S32 net_set_mac(NET_CARD_E enNetCardID, const NET_MAC_S* pNetConfig);

/** CNcomment:获取网口Mac 地址信息 CNend */
S32 net_get_mac(NET_CARD_E enNetCardID,  NET_MAC_S* const pNetConfig);

/** CNcomment:获取网口连接状态 CNend */
S32 net_get_linkstatus(NET_CARD_E enNetCardID,  NET_LINKSTATUS_E* pLinkStatus);

/**CNcomment:启动网口up/down事件监控*/
S32 net_start_interface_observer(NET_INTERFACE_EVTCB interfaceCB);

/**CNcomment:停止网口监控*/
S32 net_stop_interface_observer(NET_INTERFACE_EVTCB interfaceCB);

/** CNcomment:为对应网口开启DHCP功能 CNend */
S32 net_open_dhcp(NET_CARD_E enNetCardID, NET_DHCP_CONN_EVTCB dhcpCB);

/** CNcomment:为对应网口关闭DHCP功能 CNend */
S32 net_close_dhcp(NET_CARD_E enNetCardID);

/** CNcomment:为对应网口开启pppoe功能  */
S32 net_open_pppoe(const NET_PPPOE_INFO_S* pPppoeConfig, NET_PPPOE_CONN_EVTCB pppoeCB);

/** CNcomment:为对应网口关闭pppoe功能 CNend */
S32 net_close_pppoe(NET_CARD_E enNetCardID);

/** CNcomment:获取网卡对应的pppoe地址信息CNend */
S32 net_get_pppoe_address(NET_CARD_E enNetCardID,NET_CONFIG_S* const pNetConfig);

/** CNcomment:清除ip地址信息 CNend */
S32 net_clear_address(NET_CARD_E enNetCardID);

/** CNcomment:为对应wlan网口启动sta模式 CNend */
S32 net_sta_start(NET_CARD_E enNetCardID, NET_WLAN_STA_SCAN_EVTCB pEventCallback, NET_WLAN_STA_LINKAP_EVTCB pApEventCallback);

/** CNcomment:为对应wlan网口启动scan扫描 CNend */
S32 net_sta_startscan(NET_CARD_E enNetCardID);

/** CNcomment:为对应wlan网口停止sta模式 CNend */
S32 net_sta_stop(NET_CARD_E enNetCardID);

/** CNcomment:对应wlan网口获取scan状态 CNend */
S32 net_sta_getscanstatus(NET_CARD_E enNetCardID, WLAN_STA_EVENT_E* pScanStatus);

/** CNcomment:获取对应wlan网口扫描到的ap个数 CNend */
S32 net_sta_getresultnum(NET_CARD_E enNetCardID, U32* pNumber);

/** CNcomment:获取对应wlan网口扫描到的AP列表信息 CNend */
S32 net_sta_getresult(NET_CARD_E enNetCardID,  WLAN_STA_AccessPoint_S* pAPList, U32 ListNodeNumber, U32* pGettedNumber);

/** CNcomment:对应wlan网口连接AP CNend */
S32 net_sta_connect(NET_CARD_E enNetCardID, const WLAN_STA_Config_S* pConfig);

/** CNcomment:对应wlan网口断开AP CNend */
S32 net_sta_disconnect(NET_CARD_E enNetCardID);

/** CNcomment:wlan口的连接状态 CNend */
S32 net_sta_getconnectstatus(NET_CARD_E enNetCardID, WLAN_STA_CONN_Status_S* pStatus);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*__HAL_NET_INTERFACE_H__*/
