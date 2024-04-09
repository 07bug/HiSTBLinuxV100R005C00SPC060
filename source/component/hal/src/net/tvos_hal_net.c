#define LOG_TAG "NetHal"

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <linux/ip.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <linux/route.h>
#include <linux/if_arp.h>
#include <linux/rtnetlink.h>

#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>

#include "tvos_hal_net.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_common.h"
#ifdef HI_WIFI_SUPPORT
#include "hi_wlan_sta.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define NETWORK_MAC_FILEDS_COUNT 6
#define NETWORK_MAC_ADDRESS_FIELD_LENGTH 2
#define NETWORK_IP_VALUE_LENGTH 4
#define NETWORK_SYSFS_CLASS_NET  "/sys/class/net"
#define NETWORK_ETH_PREFIX  "eth"
#define NETWORK_WLAN_PREFIX "wlan"
#define NETWORK_NET_DNSRESOLV_FILENAME   "/var/resolv.conf"
#define NETWORK_PPP_DNSRESOLV_FILENAME   "/etc/ppp/resolv.conf"
#define NETWORK_NET_DNSRESOLV_BAK_FILENAME   "/etc/resolv.conf"
#define NETWORK_NET_DNSRESOLV_BAK_SOFTLINK_FILENAME   "/tmp/ppp/resolv.conf"
#define NETWORK_NET_DNSRESOLV_BAK_SOFTLINK_DIR   "/tmp/ppp"
#define NETWORK_NET_ROUTE_FILENAME "/proc/net/route"
#define NETWORK_PPPOE_CONNECT_SCRIPT "/usr/data/pppoe/pppoe-connect.sh"
#define NETWORK_PPPOE_DISCONNECT_SCRIPT "/usr/data/pppoe/pppoe-disconnect.sh"
#define NETWORK_INTERFACE_NAME_LEN  16
#define NETWORK_MAX_INTERFACE_NUM  16
#define NETWORK_MAX_AP_COUNT 40
#define NETWORK_SSID_LENGTH 32
#define NETWORK_PASSWORD_LENGTH 64
#define NETWORK_SINGLE_DNS 1
#define NETWORK_DOUBLE_DNS 2
#define NETWORK_READ_DHCP_PID_TIMES 2

#define ERROR_WLAN_PREFIX  (ERROR_WLAN_FAILED&0XFFFFFF00)

#define NET_LOCK(mutex)                      \
    do                                                      \
    {                                                        \
        (VOID)pthread_mutex_lock((mutex)); \
    } while (0)

#define NET_UNLOCK(mutex)                    \
    do                                                         \
    {                                                           \
        (VOID)pthread_mutex_unlock((mutex)); \
    } while (0)

#define HI_LOG_CHK_PARA_NULL_PTR( val  ) \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            HAL_ERROR("Null PTR!!.");                 \
            return ERROR_NULL_PTR;                      \
        };                                                   \
    } while (0)

#define HI_LOG_CHK_PARA_VALID( val  ) \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            HAL_ERROR("Invalid PARAM!!.");          \
            return ERROR_INVALID_PARAM;                      \
        };                                                   \
    } while (0)

#define HI_STA_ASSERT_CALLBACK( val  ) \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            HAL_DEBUG("the callback is null");          \
            return;                      \
        };                                                   \
    } while (0)

#define HI_LOG_CHK_RETURN(val, ret, ...) \
    do \
    { \
        if ((val)) \
        { \
            HAL_ERROR(__VA_ARGS__); \
            return (ret); \
        } \
    } while (0)

static CHAR eth_name_array[NETWORK_MAX_INTERFACE_NUM][NETWORK_INTERFACE_NAME_LEN] =
{
    "eth0",
    "eth1",
    "eth2",
    "eth3",
    "eth4",
    "eth5",
    "eth6",
    "eth7",
    "wlan0",
    "wlan1",
    "wlan2",
    "wlan3",
    "wlan4",
    "wlan5",
    "wlan6",
    "wlan7"
};

typedef struct _NET_DHCP_ENTITY_S
{
    NET_CARD_E           enNetCardID;
    NET_DHCP_CONN_EVTCB pfnCallback;
    U32 u32DhcpThreadID;
    struct  _NET_DHCP_ENTITY_S*  pNext;
} NET_DHCP_ENTITY_S;

typedef struct _NET_PPPOE_ENTITY_S
{
    NET_PPPOE_INFO_S stPppoeInfo;
    NET_PPPOE_CONN_EVTCB pfnCallback;
    U32 u32PppoeThread;
    CHAR pppoeInterface[NET_PPPOE_INTERFACE_LEN + 1];
    struct  _NET_PPPOE_ENTITY_S*  pNext;
} NET_PPPOE_ENTITY_S;

typedef struct _NET_INTERFACE_CB_ENTITY_S
{
    NET_INTERFACE_EVTCB pfnCallback;
    U32 u32ObserverThread;
    struct  _NET_INTERFACE_CB_ENTITY_S*  pNext;
} NET_INTERFACE_CB_ENTITY_S;

typedef VOID (*sighandler_t)(S32);
static sighandler_t s_old_handler;
static pthread_mutex_t s_net_mutex;
static BOOL s_bNetInited = FALSE;

static pthread_mutex_t s_pppoeMutex;
static NET_PPPOE_ENTITY_S* s_pstPppoeHead = NULL;
static pthread_mutex_t s_dhcpMutex;
static NET_DHCP_ENTITY_S* s_pstDhcpHead = NULL;
static pthread_mutex_t s_observerMutex;
static NET_INTERFACE_CB_ENTITY_S* s_pstOberverCBHead = NULL;

#ifdef HI_WIFI_SUPPORT
static NET_WLAN_STA_SCAN_EVTCB s_pEventCallback = NULL;
static NET_WLAN_STA_LINKAP_EVTCB s_pApEventCallback = NULL;
static WLAN_STA_EVENT_E s_enEvent = WLAN_STA_EVENT_SCAN_IDLE;
static VOID net_wlan_callback(HI_WLAN_STA_EVENT_E event, VOID* pstPrivData);
#endif

static S32 HI_NET_CHECK_SUPPORT( NET_CARD_E enNetCard )
{
    if (NET_WLAN_0 > enNetCard )
    {
#ifndef HI_ETHERNET_SUPPORT
        return FAILURE;
#endif
    }
    else
    {
#ifndef HI_WIFI_SUPPORT
        return FAILURE;
#endif
    }

    return SUCCESS;
}

static S32 prase_mac(CHAR* pDst, const CHAR* pSrc)
{
    const CHAR* pTempSrc = pSrc;
    CHAR acTempField[NETWORK_MAC_ADDRESS_FIELD_LENGTH + 1];
    S32 s32ColonCnt = 0;
    S32 i = 0;

    if ((NULL == pSrc) || (NULL == pDst))
    {
        return FAILURE;
    }

    while ('\0' != *pTempSrc)
    {
        if (i >= NETWORK_MAC_ADDRESS_FIELD_LENGTH + 1)
        {
            HAL_ERROR("too many chars between ':' and ':'");
            return FAILURE;
        }

        if (':' == *pTempSrc)
        {
            if (s32ColonCnt >= NETWORK_MAC_FILEDS_COUNT - 1)
            {
                HAL_ERROR("too many ':'");
                return FAILURE;
            }

            acTempField[i] = '\0';
            pDst[s32ColonCnt++] = strtoul(acTempField, NULL, 16);
            i = 0;
        }
        else
        {
            acTempField[i] = *pTempSrc;
            i++;
        }

        pTempSrc++;
    }

    if (i >= NETWORK_MAC_ADDRESS_FIELD_LENGTH + 1)
    {
        HAL_ERROR("too many chars between ':' and '\0'");
        return FAILURE;
    }

    acTempField[i] = '\0';
    pDst[s32ColonCnt] = strtoul(acTempField, NULL, 16);

    if (NETWORK_MAC_FILEDS_COUNT - 1 != s32ColonCnt)
    {
        return FAILURE;
    }

    return SUCCESS;
}

static S32 prase_interface_order(NET_CARD_E enNetCardID)
{
    S32 s32Order = 0;
    U32 u32CardID = (U32)enNetCardID;

    while ((u32CardID & 0x01) != 0x01)
    {
        u32CardID >>= 1;
        s32Order++;
    }

    return s32Order;
}

static CHAR* skip_space(CHAR* pLine)
{
    CHAR* p = pLine;

    while ((*p == ' ') || (*p == '\t'))
    {
        p++;
    }

    return p;
}

static CHAR* skip_word(CHAR* pLine)
{
    CHAR* p = pLine;

    while ((*p != '\t') && (*p != ' ') && (*p != '\n') && (*p != 0))
    {
        p++;
    }

    return p;
}

static CHAR* get_word(CHAR* pLine, CHAR* pValue)
{
    CHAR* p = pLine;

    p = skip_space(p);

    while ((*p != '\t') && (*p != ' ') && (*p != '\n') && (*p != 0))
    {
        *pValue++ = *p++;
    }

    *pValue = 0;

    return p;
}

static S32 net_eth_ipaddressset (const CHAR* pIface, const CHAR* pIpAdd)
{
    S32 s32Sockfd;
    struct ifreq ifr;
    struct sockaddr_in* sin = NULL;

    if ((s32Sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        HAL_ERROR("socket create fail!");
        return FAILURE;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, pIface, sizeof(ifr.ifr_name) - 1);
    sin = (struct sockaddr_in*)&ifr.ifr_addr;
    sin->sin_family = AF_INET;

    if (inet_pton(AF_INET, pIpAdd, &sin->sin_addr) <= 0)  // fix: change from < to <= for invalid ipAddr input
    {
        HAL_ERROR("inet_pton fail!");
        close(s32Sockfd);
        return FAILURE;
    }

    if (ioctl(s32Sockfd, SIOCSIFADDR, &ifr) < 0)
    {
        HAL_ERROR("set ipaddr fail!");
        close(s32Sockfd);
        return FAILURE;
    }

    close(s32Sockfd);
    return SUCCESS;
}

static S32 net_eth_ipaddressget(const CHAR* pIface, CHAR* ipAdd)
{
    S32 s32Sockfd;
    struct ifreq ifr;
    struct sockaddr_in* s_in = NULL;

    s32Sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (s32Sockfd < 0)
    {
        HAL_DEBUG("socket create fail!");
        return FAILURE;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, pIface, NETWORK_INTERFACE_NAME_LEN - 1);

    if (ioctl(s32Sockfd, SIOCGIFADDR, &ifr) < 0)
    {
        HAL_DEBUG("ioctl fail!");
        close(s32Sockfd);
        return FAILURE;
    }

    s_in = (struct sockaddr_in*)(&ifr.ifr_addr);
    memcpy((VOID*)ipAdd, inet_ntoa(s_in->sin_addr), 15);
    close(s32Sockfd);
    return SUCCESS;
}

static S32 net_eth_subnetmaskset(const CHAR* pIface, const CHAR* subNetmask)
{
    S32 sockfd;
    struct ifreq ifr;
    struct sockaddr_in* sin;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        HAL_ERROR("socket create fail!");
        return FAILURE;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, pIface, sizeof(ifr.ifr_name) - 1);
    sin = (struct sockaddr_in*)&ifr.ifr_netmask;
    sin->sin_family = AF_INET;

    if (inet_pton(AF_INET, subNetmask, &sin->sin_addr) < 0)
    {
        HAL_ERROR("inet_pton  fail!");
        close(sockfd);
        return FAILURE;
    }

    if (ioctl(sockfd, SIOCSIFNETMASK, &ifr) < 0)
    {
        HAL_ERROR("set netmask fail!");
        close(sockfd);
        return FAILURE;
    }

    close(sockfd);
    return SUCCESS;
}

static S32 net_eth_subnetmaskget(const CHAR* pIface, CHAR* subNetmask)
{
    S32 s32Sockfd;
    struct ifreq ifr;
    struct sockaddr_in* s_in = NULL;

    s32Sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (s32Sockfd < 0)
    {
        HAL_DEBUG("socket create fail!");
        return FAILURE;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, pIface, NETWORK_INTERFACE_NAME_LEN - 1);

    if (ioctl(s32Sockfd, SIOCGIFNETMASK, &ifr) < 0)
    {
        HAL_DEBUG("ioctl fail!");
        close(s32Sockfd);
        return FAILURE;
    }

    s_in = (struct sockaddr_in*)(&ifr.ifr_netmask);

    memcpy((VOID*)subNetmask, inet_ntoa(s_in->sin_addr), NET_IPV4_ADDR_LENGTH + 1);
    close(s32Sockfd);
    return SUCCESS;
}

static S32 net_eth_gatewayset(const CHAR* pIface, const CHAR* gateway)
{
    S32 sockfd;
    struct rtentry rm;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        HAL_ERROR("socket create fail!");
        return FAILURE;
    }

    memset(&rm, 0, sizeof(struct rtentry));

    (( struct sockaddr_in*)&rm.rt_dst)->sin_family = AF_INET;
    (( struct sockaddr_in*)&rm.rt_dst)->sin_addr.s_addr = 0;
    (( struct sockaddr_in*)&rm.rt_dst)->sin_port = 0;

    (( struct sockaddr_in*)&rm.rt_genmask)->sin_family = AF_INET;
    (( struct sockaddr_in*)&rm.rt_genmask)->sin_addr.s_addr = 0;
    (( struct sockaddr_in*)&rm.rt_genmask)->sin_port = 0;

    (( struct sockaddr_in*)&rm.rt_gateway)->sin_family = AF_INET;
    (( struct sockaddr_in*)&rm.rt_gateway)->sin_addr.s_addr = inet_addr(gateway);
    (( struct sockaddr_in*)&rm.rt_gateway)->sin_port = 0;

    rm.rt_flags = RTF_UP | RTF_GATEWAY;

    if (( ioctl(sockfd, SIOCADDRT, &rm)) < 0)
    {
        HAL_ERROR("SIOCADDRT fail !");
        close(sockfd);
        return FAILURE;
    }

    close(sockfd);
    return SUCCESS;

}

static S32 gatewayaddress_parse(const CHAR* pchSrc, S32* ps32Out)
{
    S32 i = 0;
    S32 s32Arr[8];
    memset(s32Arr, 0 , sizeof(s32Arr));

    S32 s32Length = strlen(pchSrc);

    if (8 > s32Length)
    {
        HAL_ERROR("input str is invalid, str = %s", pchSrc);
        return FAILURE;
    }

    for (i = 0; i < 8; i++)
    {
        if (pchSrc[i] >= 'A' && pchSrc[i] <= 'F')
        {
            s32Arr[i] = pchSrc[i] - 'A' + 10;
        }
        else if (pchSrc[i] >= 'a' && pchSrc[i] <= 'f')
        {
            s32Arr[i] = pchSrc[i] - 'a' + 10;
        }
        else if (pchSrc[i] >= '0' && pchSrc[i] <= '9')
        {
            s32Arr[i] = pchSrc[i] - '0';
        }
        else
        {
            HAL_ERROR("input str has invalid character , str = %s", pchSrc);
            return FAILURE;
        }
    }

    ps32Out[0] = (s32Arr[0] << 4) | s32Arr[1];
    ps32Out[1] = (s32Arr[2] << 4) | s32Arr[3];
    ps32Out[2] = (s32Arr[4] << 4) | s32Arr[5];
    ps32Out[3] = (s32Arr[6] << 4) | s32Arr[7];

    return SUCCESS;
}

static S32 net_eth_gatewayget(const CHAR* pIface, CHAR* gateway)
{
    CHAR line[512];
    CHAR str[16];
    FILE* fp = NULL;
    memset(str, 0, sizeof(str));
    memset(line, 0, sizeof(line));

    fp = fopen(NETWORK_NET_ROUTE_FILENAME, "r");

    if (NULL == fp)
    {
        HAL_ERROR("no route file");
        return FAILURE;
    }

    while (fgets(line, sizeof(line), fp) != 0)
    {
        CHAR* p = line;
        p = strstr(p, pIface);

        if (p)
        {
            p = get_word(p, str);
            p = get_word(p, str);

            if (strncmp(str, "00000000", sizeof(str)) == 0)
            {
                get_word(p, str);

                if (strncmp(str, "00000000", sizeof(str)) != 0)
                {
                    S32 s32Arr[NETWORK_IP_VALUE_LENGTH];

                    if (SUCCESS == gatewayaddress_parse(str, s32Arr))
                    {
                        snprintf(gateway, NET_IPV6_ADDR_LENGTH + 1, "%d.%d.%d.%d", s32Arr[3], s32Arr[2], s32Arr[1],  s32Arr[0]);
                        fclose(fp);
                        return SUCCESS;
                    }
                }
            }
        }
    }

    fclose(fp);
    return FAILURE;
}

static S32 net_eth_dnsset(const CHAR* pIface, const CHAR* pDns1, const CHAR* pDns2)
{
    FILE* fp = NULL;
    S32 s32Ret = FAILURE;
    CHAR dnsFile[32];
    memset(dnsFile, 0x0, sizeof(dnsFile));

    if (NULL  != (fp = fopen(NETWORK_NET_DNSRESOLV_FILENAME, "r")))
    {
        strncpy(dnsFile, NETWORK_NET_DNSRESOLV_FILENAME, sizeof(NETWORK_NET_DNSRESOLV_FILENAME));
        fclose(fp);
        fp = NULL;
    }
    else
    {
        strncpy(dnsFile, NETWORK_NET_DNSRESOLV_BAK_SOFTLINK_FILENAME, sizeof(NETWORK_NET_DNSRESOLV_BAK_SOFTLINK_FILENAME));
    }

    if (NULL != (fp = fopen(NETWORK_NET_DNSRESOLV_BAK_SOFTLINK_DIR, "r")))
    {
        fclose(fp);
        fp = NULL;
    }
    else
    {
        s32Ret = mkdir(NETWORK_NET_DNSRESOLV_BAK_SOFTLINK_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        HI_LOG_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "mkdir failed");
    }

    fp = fopen(dnsFile, "w+");

    if (fp)
    {
        fprintf(fp, "nameserver %s\nnameserver %s", pDns1, pDns2);
        fclose(fp);
        return SUCCESS;
    }

    return FAILURE;
}

static S32 net_ppp_dnsget(const CHAR* pIface, CHAR dns[][32], S32* pDnsNumber)
{
    CHAR line[128];
    FILE* fp = NULL;
    CHAR* pStr = NULL;
    CHAR dnsFile[32];
    S32 s32DnsNum = 0;
    S32 i = 0;
    memset(dnsFile, 0x0, sizeof(dnsFile));
    memset(line, 0x0, sizeof(line));

    strncpy(dnsFile, NETWORK_PPP_DNSRESOLV_FILENAME, sizeof(NETWORK_PPP_DNSRESOLV_FILENAME));

    fp = fopen(dnsFile, "r");

    if (!fp)
    {
        HAL_DEBUG("no dns");
        return FAILURE;
    }

    while (fgets(line, 128, fp) != 0)
    {
        pStr = strstr(line, "nameserver");

        if (pStr)
        {
            pStr = skip_word(pStr);
            get_word(pStr, dns[i]);
            s32DnsNum++;

            if (strlen(dns[i]) == 0)
            {
                strncpy(dns[i], "0.0.0.0", NET_IPV6_ADDR_LENGTH + 1);
            }

            if (i == 1)
            { break; }

            i++;
        }
    }

    fclose(fp);

    if (0 == s32DnsNum)
    {
        return FAILURE;
    }
    else
    {
        *pDnsNumber = s32DnsNum;
        return SUCCESS;
    }
}

static S32 net_eth_dnsget(const CHAR* pIface, CHAR dns[][32], S32* pDnsNumber)
{
    CHAR line[128];
    FILE* fp = NULL;
    CHAR* pStr = NULL;
    CHAR dnsFile[32];
    S32 s32DnsNum = 0;
    S32 i = 0;
    memset(dnsFile, 0x0, sizeof(dnsFile));
    memset(line, 0x0, sizeof(line));

    if (NULL != (fp = fopen(NETWORK_NET_DNSRESOLV_FILENAME, "r")))
    {
        strncpy(dnsFile, NETWORK_NET_DNSRESOLV_FILENAME, sizeof(NETWORK_NET_DNSRESOLV_FILENAME));
        fclose(fp);
        fp = NULL;
    }
    else
    {
        strncpy(dnsFile, NETWORK_NET_DNSRESOLV_BAK_FILENAME, sizeof(NETWORK_NET_DNSRESOLV_BAK_FILENAME));
    }

    fp = fopen(dnsFile, "r");

    if (!fp)
    {
        HAL_DEBUG("no dns");
        return FAILURE;
    }

    while (fgets(line, 128, fp) != 0)
    {
        pStr = strstr(line, "nameserver");

        if (pStr)
        {
            pStr = skip_word(pStr);
            get_word(pStr, dns[i]);
            s32DnsNum++;

            if (strlen(dns[i]) == 0)
            {
                strncpy(dns[i], "0.0.0.0", NET_IPV6_ADDR_LENGTH + 1);
            }

            if (i == 1)
            { break; }

            i++;
        }
    }

    fclose(fp);

    if (0 == s32DnsNum)
    {
        return FAILURE;
    }
    else
    {
        *pDnsNumber = s32DnsNum;
        return SUCCESS;
    }
}

static S32 get_char_num(const CHAR* src, CHAR dstChar)
{
    S32 s32Num = 0;
    U32 i = 0;

    for (i = 0; i < strlen(src); i++)
    {
        if (src[i] == dstChar)
        {
            s32Num++;
        }
    }

    return s32Num;
}

static S32 netaddress_parse(const CHAR* srcAddress, S32* pS32Out)
{
    S32 s32NumCnt = 0;
    S32 s32Index = 0;
    S32 s32TmpValue = -1;
    CHAR chTmp = '\0';
    S32 s32DotCnt = get_char_num(srcAddress, '.');

    if ((NETWORK_IP_VALUE_LENGTH - 1) != s32DotCnt)
    {
        HAL_ERROR("src address error:%s", srcAddress);
        return FAILURE;
    }

    while (srcAddress[s32Index] != '\0')
    {
        chTmp = srcAddress[s32Index++];

        if ('.' == chTmp)
        {
            if (-1 == s32TmpValue)
            {
                HAL_ERROR("src address error:%s", srcAddress);
                return FAILURE;
            }

            pS32Out[s32NumCnt] = s32TmpValue;
            s32TmpValue = -1;
            s32NumCnt++;
        }
        else if (chTmp >= '0' && chTmp <= '9')
        {
            if (-1 == s32TmpValue)
            {
                s32TmpValue = 0;
            }

            s32TmpValue = s32TmpValue * 10 + (chTmp - '0');
        }
        else if (' ' == chTmp || '\t' == chTmp)
        {
            continue;
        }
        else
        {
            HAL_ERROR("src address error:%s", srcAddress);
            return FAILURE;
        }
    }

    if ((-1 == s32TmpValue) || ((NETWORK_IP_VALUE_LENGTH - 1) != s32NumCnt))
    {
        HAL_ERROR("src address error:%s", srcAddress);
        return FAILURE;
    }

    pS32Out[s32NumCnt] = s32TmpValue;

    return SUCCESS;
}

static S32 format_address(const CHAR* srcAddress, CHAR* dstAddress, U32 u32Size)
{
    S32 s32AddressValue[NETWORK_IP_VALUE_LENGTH];
    memset(s32AddressValue, 0x0, sizeof(s32AddressValue));
    CHAR acAddress[NET_IPV6_ADDR_LENGTH + 1];
    memset(acAddress, 0, sizeof(acAddress));

    if (u32Size > NET_IPV6_ADDR_LENGTH)
    {
        HAL_ERROR("srcAddress length is invalid,length = %u", u32Size);
        return FAILURE;
    }

    strncpy(acAddress, srcAddress, u32Size);

    S32 s32Ret = netaddress_parse(acAddress, s32AddressValue);

    if (s32Ret == SUCCESS)
    {
        snprintf(dstAddress, u32Size, "%d.%d.%d.%d", s32AddressValue[0], s32AddressValue[1],
                 s32AddressValue[2], s32AddressValue[3]);

        if (INADDR_NONE == inet_addr(dstAddress))
        {
            HAL_ERROR("incorrect ip address:%s", dstAddress);
            return FAILURE;
        }

        return SUCCESS;
    }
    else
    {
        HAL_ERROR("srcAddress is error!the address:%s", acAddress);
        return FAILURE;
    }
}

static BOOL compare_address(const NET_CONFIG_S* pSrcNetConfig, const NET_CONFIG_S* pDstNetConfig)
{
    return (BOOL)((strncmp(pSrcNetConfig->IpAddr, pDstNetConfig->IpAddr, sizeof(pDstNetConfig->IpAddr)) == 0)
                  && (strncmp(pSrcNetConfig->NetMask, pDstNetConfig->NetMask, sizeof(pDstNetConfig->NetMask)) == 0)
                  && (strncmp(pSrcNetConfig->GateWay, pDstNetConfig->GateWay, sizeof(pDstNetConfig->GateWay)) == 0));
}

static S32 check_ip_gateway_match(const NET_CONFIG_S* pNetConfig)
{
    U32 i = 0;
    S32 s32Ret = FAILURE;
    S32 s32IpValue[NETWORK_IP_VALUE_LENGTH];
    S32 s32NetMaskValue[NETWORK_IP_VALUE_LENGTH];
    S32 s32GatewayValue[NETWORK_IP_VALUE_LENGTH];
    memset(s32IpValue, 0x0, sizeof(s32IpValue));
    memset(s32NetMaskValue, 0x0, sizeof(s32NetMaskValue));
    memset(s32GatewayValue, 0x0, sizeof(s32GatewayValue));

    s32Ret = netaddress_parse(pNetConfig->IpAddr, s32IpValue);
    HI_LOG_CHK_RETURN((FAILURE == s32Ret), FAILURE,
                      "ipaddr error,the error code is 0x%x", s32Ret);

    s32Ret = netaddress_parse(pNetConfig->NetMask, s32NetMaskValue);
    HI_LOG_CHK_RETURN((FAILURE == s32Ret), FAILURE,
                      "netmask error,the error code is 0x%x", s32Ret);

    s32Ret = netaddress_parse(pNetConfig->GateWay, s32GatewayValue);

    HI_LOG_CHK_RETURN((FAILURE == s32Ret), FAILURE,
                      "gateway error,the error code is 0x%x", s32Ret);

    for (i = 0; i < NETWORK_IP_VALUE_LENGTH; i++)
    {
        if ((s32IpValue[i]&s32NetMaskValue[i]) != (s32GatewayValue[i]&s32NetMaskValue[i]))
        { return FAILURE; }
    }

    return SUCCESS;
}

S32 net_init(VOID)
{
#ifdef HI_WIFI_SUPPORT
    NET_LOCK(&s_net_mutex);

    if (s_bNetInited)
    {
        HAL_DEBUG("Net Already Inited");
        NET_UNLOCK(&s_net_mutex);
        return SUCCESS;
    }

    S32 s32Ret =  HI_WLAN_STA_Init();

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_WLAN_STA_Init error,the s32Ret is %d", s32Ret);
        NET_UNLOCK(&s_net_mutex);
        return ERROR_WLAN_FAILED;
    }

    s_bNetInited = TRUE;
    NET_UNLOCK(&s_net_mutex);
    return SUCCESS;
#elif defined HI_ETHERNET_SUPPORT
    return SUCCESS;
#else
    return FAILURE;
#endif
}

S32 net_deinit(VOID)
{
#ifdef HI_WIFI_SUPPORT
    NET_LOCK(&s_net_mutex);

    if (!s_bNetInited)
    {
        HAL_DEBUG("Net Not Inited Yet.");
        NET_UNLOCK(&s_net_mutex);
        return SUCCESS;
    }

    HI_WLAN_STA_DeInit();
    NET_UNLOCK(&s_net_mutex);
    return SUCCESS;
#elif defined HI_ETHERNET_SUPPORT
    return SUCCESS;
#else
    return FAILURE;
#endif
}

S32 net_open(NET_CARD_E enNetCardID)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    struct ifreq ifr;
    S32 s32Sockfd;
    CHAR interface[24];

    if (enNetCardID < NET_WLAN_0)
    {
#ifdef HI_ETHERNET_SUPPORT

        if ((s32Sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            HAL_ERROR("socket create fail!");
            return ERROR_NETWORK_OPEN_FAILED;
        }

        strncpy(ifr.ifr_name, eth_name_array[prase_interface_order(enNetCardID)], NETWORK_INTERFACE_NAME_LEN - 1);

        if ((ioctl(s32Sockfd, SIOCGIFFLAGS, (caddr_t)&ifr)) == -1)
        {
            HAL_ERROR("SIOCGIFFLAGS fail!");
            close(s32Sockfd);
            return ERROR_NETWORK_OPEN_FAILED;
        }

        ifr.ifr_flags |= IFF_UP;

        if ((ioctl(s32Sockfd, SIOCSIFFLAGS, (caddr_t)&ifr)) == -1)
        {
            HAL_ERROR("SIOCSIFFLAGS fail!");
            close(s32Sockfd);
            return ERROR_NETWORK_OPEN_FAILED;
        }

        close(s32Sockfd);
#else
        return FAILURE;
#endif
    }
    else
    {
#ifdef HI_WIFI_SUPPORT
        NET_LOCK(&s_net_mutex);
        s_old_handler = signal(SIGCHLD, SIG_DFL);  //fix wifi open  "no child processes" problem

        S32 s32Ret = HI_WLAN_STA_Open(interface);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_WLAN_STA_Open error,ret is %d", s32Ret);
            NET_UNLOCK(&s_net_mutex);

            if (FAILURE == s32Ret)
            {
                return FAILURE;
            }

            return ERROR_WLAN_PREFIX | (s32Ret * (-1));
        }

        NET_UNLOCK(&s_net_mutex);

        HAL_DEBUG("HI_WLAN_STA_Open success,the interface is %s\n", interface);
#else
        return FAILURE;
#endif
    }

    return SUCCESS;

}

S32 net_close(NET_CARD_E enNetCardID)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    struct ifreq ifr;
    S32 s32Sockfd;
    S32 s32Ret = FAILURE;

    if (enNetCardID < NET_WLAN_0)
    {
#ifdef HI_ETHERNET_SUPPORT

        if ((s32Sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            HAL_ERROR("socket create fail!");
            return ERROR_NETWORK_CLOSE_FAILED;
        }

        strncpy(ifr.ifr_name, eth_name_array[prase_interface_order(enNetCardID)], NETWORK_INTERFACE_NAME_LEN - 1);

        if ((ioctl(s32Sockfd, SIOCGIFFLAGS, (caddr_t)&ifr)) == -1)
        {
            HAL_ERROR("SIOCGIFFLAGS fail!");
            close(s32Sockfd);
            return ERROR_NETWORK_CLOSE_FAILED;
        }

        ifr.ifr_flags &= (~IFF_UP);

        if ((ioctl(s32Sockfd, SIOCSIFFLAGS, (caddr_t)&ifr)) == -1)
        {
            HAL_ERROR("SIOCSIFFLAGS fail!");
            close(s32Sockfd);
            return ERROR_NETWORK_CLOSE_FAILED;
        }

        close(s32Sockfd);
#else
        return FAILURE;
#endif
    }
    else
    {
#ifdef HI_WIFI_SUPPORT
        NET_LOCK(&s_net_mutex);
        s32Ret = HI_WLAN_STA_Close(eth_name_array[prase_interface_order(enNetCardID)]);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_WLAN_STA_Close error,ret is %d", s32Ret);
            NET_UNLOCK(&s_net_mutex);

            if (FAILURE == s32Ret)
            {
                return FAILURE;
            }

            return ERROR_WLAN_PREFIX | (s32Ret * (-1));
        }

        signal(SIGCHLD, s_old_handler);
        NET_UNLOCK(&s_net_mutex);
#else
        return FAILURE;
#endif
    }

    return SUCCESS;
}

//cannot get wlan0 when wifi is closed
S32 net_get_capability(NET_CAPBILITY_S* const pNetCapability)
{
    HI_LOG_CHK_PARA_NULL_PTR(pNetCapability == NULL);
    DIR* netdir = NULL;
    struct dirent* de = NULL;
    memset(pNetCapability, 0x0, sizeof(NET_CAPBILITY_S)); //reset to 0,in order to avoid the effect of the value

    if (!(netdir = opendir(NETWORK_SYSFS_CLASS_NET)))
    {
        HAL_ERROR("open dir  %s fail", NETWORK_SYSFS_CLASS_NET);
        return FAILURE;
    }

    while ((de = readdir(netdir)))
    {
        if (0 == strncmp(de->d_name, NETWORK_ETH_PREFIX, strlen(NETWORK_ETH_PREFIX)))
        {
            S32 eth_num = atoi(de->d_name + strlen(NETWORK_ETH_PREFIX));
            pNetCapability->u32NetIdSet += NET_ETH_0 << eth_num;
        }
        else if (0 == strncmp(de->d_name, NETWORK_WLAN_PREFIX, strlen(NETWORK_WLAN_PREFIX)))
        {
            S32 wlan_num = atoi(de->d_name + strlen(NETWORK_WLAN_PREFIX));
            pNetCapability->u32NetIdSet += NET_WLAN_0 << wlan_num;
        }
    }

    closedir(netdir);
    return SUCCESS;
}

S32 net_set_ipv_type(NET_CARD_E enNetCardID, NET_IPV_TYPE_E eIpvType)
{
    return ERROR_NOT_SUPPORTED;
}

S32 net_get_openstatus(NET_CARD_E enNetCardID, BOOL* pbOpen)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pbOpen);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));
    S32 s32Sockfd;
    struct ifreq ifr;

    if ((s32Sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        HAL_ERROR("socket create fail!");
        return FAILURE;
    }

    bzero((CHAR*)&ifr, sizeof(ifr));
    strncpy(ifr.ifr_name, eth_name_array[prase_interface_order(enNetCardID)], NETWORK_INTERFACE_NAME_LEN - 1);

    if (ioctl(s32Sockfd, SIOCGIFFLAGS, (char*)&ifr) < 0)
    {
        HAL_ERROR("socket create fail!");
        close(s32Sockfd);
        return FAILURE;
    }

    if ((ifr.ifr_flags & IFF_RUNNING) == 0)
    {
        *pbOpen = (BOOL) NET_LINK_STATUS_OFF;
    }
    else
    {
        *pbOpen = (BOOL) NET_LINK_STATUS_ON;
    }

    close(s32Sockfd);

    return SUCCESS;
}

S32 net_get_linkstatus(NET_CARD_E enNetCardID,  NET_LINKSTATUS_E* pLinkStatus)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pLinkStatus);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));
    NET_CONFIG_S stConfig;
    S32 s32Ret = FAILURE;
    BOOL bOpen = FALSE;
    memset(&stConfig, 0x0, sizeof(stConfig));

    s32Ret = net_get_openstatus(enNetCardID, &bOpen);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("net_get_openstatus fail");
        return s32Ret;
    }

    if (TRUE != bOpen)
    {
        *pLinkStatus = NET_LINK_STATUS_OFF;
        return SUCCESS;
    }

    s32Ret = net_get_config(enNetCardID, &stConfig);

    if (SUCCESS != s32Ret)
    {
        *pLinkStatus = NET_LINK_STATUS_OFF;
    }
    else
    {
        *pLinkStatus = NET_LINK_STATUS_ON;
    }

    return SUCCESS;
}

static VOID sendInterfaceEvent(NET_INTERFACE_CB_ENTITY_S* pstInterfaceCB, NET_INTERFACE_EVENT_E enEvent, CHAR* pMessage)
{
    NET_INTERFACE_CB_ENTITY_S* pstTmpEntity = pstInterfaceCB;

    while (NULL != pstTmpEntity)
    {
        (pstTmpEntity->pfnCallback)(enEvent, pMessage);
        pstTmpEntity = pstTmpEntity->pNext;
    }

    return;
}

static VOID prase_netlink_message(CHAR* pBuf, S32 s32Size, NET_INTERFACE_CB_ENTITY_S* pstInterfaceCB)
{
    struct nlmsghdr* nh = NULL;
    struct ifinfomsg* ifinfo = NULL;
    struct rtattr* attr = NULL;
    S32 s32Len = 0;
    NET_INTERFACE_EVENT_E enEvent =  NET_INTERFACE_BUTT;

    for (nh = (struct nlmsghdr*)pBuf; NLMSG_OK(nh, s32Size); nh = NLMSG_NEXT(nh, s32Size))
    {
        if (NLMSG_DONE == nh->nlmsg_type)
        {
            break;
        }
        else if (RTM_NEWLINK != nh->nlmsg_type)
        {
            continue;
        }
        else
        {
            ifinfo = NLMSG_DATA(nh);

            if (ifinfo->ifi_flags & IFF_LOWER_UP)
            {
                enEvent = NET_INTERFACE_UP;
            }
            else
            {
                enEvent = NET_INTERFACE_DOWN;
            }

            attr = (struct rtattr*)(((CHAR*)nh) + NLMSG_SPACE(sizeof(*ifinfo)));
            s32Len = nh->nlmsg_len - NLMSG_SPACE(sizeof(*ifinfo));

            for (; RTA_OK(attr, s32Len); attr = RTA_NEXT(attr, s32Len))
            {
                if (IFLA_IFNAME == attr->rta_type)
                {
                    sendInterfaceEvent(pstInterfaceCB, enEvent, (CHAR*)RTA_DATA(attr));
                    break;
                }
            }
        }
    }
}

static VOID* interface_observer_thread(VOID* pvParams)
{
    NET_INTERFACE_CB_ENTITY_S* pstInterfaceCB = (NET_INTERFACE_CB_ENTITY_S* )pvParams;

    S32 s32fd = -1;
    S32 s32RetVal = 0;

    struct sockaddr_nl addr;
    S32 s32BufLen = 20 * 1024;
    CHAR* pcBuf = NULL;

    memset(&addr, 0, sizeof(struct sockaddr_nl));

    s32fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);

    if (s32fd < 0)
    {
        HAL_ERROR("create socket error");
        return NULL;
    }

    if ( 0 != setsockopt(s32fd, SOL_SOCKET, SO_RCVBUF, &s32BufLen, s32BufLen))
    {
        HAL_ERROR("setsockopt error");
        close(s32fd);
        return NULL;
    }

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_pid = getpid();
    addr.nl_groups = RTNLGRP_LINK;

    if (bind(s32fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        HAL_ERROR("bind error");
        close(s32fd);
        return NULL;
    }

    pcBuf = (CHAR*)malloc(s32BufLen);

    if (NULL == pcBuf)
    {
        HAL_ERROR("malloc failed");
        close(s32fd);
        return NULL;
    }

    memset(pcBuf, 0, s32BufLen);

    while ((s32RetVal = read(s32fd, pcBuf, s32BufLen)) > 0)
    {
        NET_LOCK(&s_observerMutex);

        if (NULL == s_pstOberverCBHead)
        {
            NET_UNLOCK(&s_observerMutex);
            break;
        }

        NET_UNLOCK(&s_observerMutex);
        prase_netlink_message(pcBuf, s32RetVal, pstInterfaceCB);
    }

    free(pcBuf);
    pcBuf = NULL;
    close(s32fd);
    return NULL;
}

S32 net_start_interface_observer(NET_INTERFACE_EVTCB interfaceCB)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == interfaceCB);

    NET_INTERFACE_CB_ENTITY_S* pstTmpEntity = NULL;
    NET_INTERFACE_CB_ENTITY_S* pstCbEntity = NULL;
    pstCbEntity = (NET_INTERFACE_CB_ENTITY_S*)malloc(sizeof(NET_INTERFACE_CB_ENTITY_S));

    if ( NULL == pstCbEntity)
    {
        HAL_ERROR("malloc error");
        return FAILURE;
    }

    pstCbEntity->pfnCallback = interfaceCB;
    NET_LOCK(&s_observerMutex);

    if (NULL == s_pstOberverCBHead)
    {
        s_pstOberverCBHead = pstCbEntity;
        s_pstOberverCBHead->pNext = NULL;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create((pthread_t*) & (s_pstOberverCBHead->u32ObserverThread), &attr, interface_observer_thread, s_pstOberverCBHead);
        pthread_attr_destroy(&attr);
    }
    else
    {
        pstTmpEntity = s_pstOberverCBHead;

        while (NULL != pstTmpEntity->pNext)
        {
            if (pstTmpEntity->pfnCallback == pstCbEntity->pfnCallback)
            {
                HAL_ERROR("alreay in observer");
                free(pstCbEntity);
                pstCbEntity = NULL;
                NET_UNLOCK(&s_observerMutex);
                return FAILURE;
            }

            pstTmpEntity = pstTmpEntity->pNext;
        }

        pstTmpEntity->pNext = pstCbEntity;
        pstCbEntity->u32ObserverThread = pstTmpEntity->u32ObserverThread;
        pstCbEntity->pNext = NULL;
    }

    NET_UNLOCK(&s_observerMutex);

    return SUCCESS;
}

S32 net_stop_interface_observer(NET_INTERFACE_EVTCB interfaceCB)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == interfaceCB);

    NET_INTERFACE_CB_ENTITY_S* pstTmpEntity = NULL;
    NET_INTERFACE_CB_ENTITY_S* pstPrivEntity = NULL;

    NET_LOCK(&s_observerMutex);

    pstTmpEntity = s_pstOberverCBHead;

    while (NULL != pstTmpEntity)
    {
        if (interfaceCB != pstTmpEntity->pfnCallback)
        {
            pstPrivEntity = pstTmpEntity;
            pstTmpEntity = pstTmpEntity->pNext;
            continue;
        }

        if (pstTmpEntity == s_pstOberverCBHead)
        {
            s_pstOberverCBHead = pstTmpEntity->pNext;
        }
        else if (NULL != pstPrivEntity)
        {
            pstPrivEntity->pNext = pstTmpEntity->pNext;
        }

        free(pstTmpEntity);
        pstTmpEntity = NULL;
        break;
    }

    NET_UNLOCK(&s_observerMutex);
    return SUCCESS;
}

//TODO :will modify for ipv6
S32 net_set_config(NET_CARD_E enNetCardID, const NET_CONFIG_S* pNetConfig)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pNetConfig);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));
    S32 s32Ret;
    NET_CONFIG_S ipConfig;
    NET_CONFIG_S currentIpconfig;
    CHAR acIface[NETWORK_INTERFACE_NAME_LEN];
    memset(&ipConfig, 0x0, sizeof(NET_CONFIG_S));
    memset(&currentIpconfig, 0x0, sizeof(NET_CONFIG_S));
    memset(acIface, 0x0, sizeof(acIface));

    memcpy(acIface, eth_name_array[prase_interface_order(enNetCardID)], NETWORK_INTERFACE_NAME_LEN - 1);
    s32Ret = format_address(pNetConfig->IpAddr, ipConfig.IpAddr, NET_IPV6_ADDR_LENGTH);
    s32Ret |= format_address(pNetConfig->NetMask, ipConfig.NetMask, NET_IPV4_ADDR_LENGTH);
    s32Ret |= format_address(pNetConfig->GateWay, ipConfig.GateWay, NET_IPV6_ADDR_LENGTH);
    s32Ret |= format_address(pNetConfig->PrimaryDns, ipConfig.PrimaryDns, NET_IPV6_ADDR_LENGTH);
    s32Ret |= format_address(pNetConfig->SecondDns, ipConfig.SecondDns, NET_IPV6_ADDR_LENGTH);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("address error!");
        return ERROR_NETWORK_INVALID_ADDRESS;
    }

    s32Ret = check_ip_gateway_match(pNetConfig);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("ip and gateway not in a local net");
        return ERROR_NETWORK_IP_GATEWAY_NOCOMPATIBLE;
    }

    s32Ret = net_get_config(enNetCardID, &currentIpconfig);

    if (SUCCESS != s32Ret)
    {
        s32Ret = net_eth_ipaddressset(acIface, ipConfig.IpAddr);
        s32Ret |= net_eth_subnetmaskset(acIface, ipConfig.NetMask);
        s32Ret |= net_eth_gatewayset(acIface, ipConfig.GateWay);
        s32Ret |= net_eth_dnsset(acIface, ipConfig.PrimaryDns, ipConfig.SecondDns);
        return s32Ret;
    }
    else
    {
        s32Ret = SUCCESS;
        BOOL bSame = compare_address(&ipConfig, &currentIpconfig);

        if (!bSame)
        {
            s32Ret = net_eth_ipaddressset(acIface, ipConfig.IpAddr);
            s32Ret |= net_eth_subnetmaskset(acIface, ipConfig.NetMask);
            s32Ret |= net_eth_gatewayset(acIface, ipConfig.GateWay);
        }

        S32 s32PriDnsCmp = strncmp(currentIpconfig.PrimaryDns, ipConfig.IpAddr, sizeof(ipConfig.IpAddr));
        S32 s32SecDnsCmp = strncmp(currentIpconfig.SecondDns, ipConfig.SecondDns, sizeof(ipConfig.SecondDns));

        if ((s32PriDnsCmp != 0) && (s32SecDnsCmp != 0))
        {
            s32Ret |= net_eth_dnsset(acIface, ipConfig.PrimaryDns, ipConfig.SecondDns);
        }
        else if (s32PriDnsCmp != 0)
        {
            s32Ret |= net_eth_dnsset(acIface, ipConfig.PrimaryDns, currentIpconfig.SecondDns);
        }
        else if (s32SecDnsCmp != 0)
        {
            s32Ret |= net_eth_dnsset(acIface, currentIpconfig.PrimaryDns, ipConfig.SecondDns);
        }

        return s32Ret;
    }

}

S32 net_get_config(NET_CARD_E enNetCardID,  NET_CONFIG_S* const pNetConfig)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pNetConfig);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));
    CHAR acDns[2][32];
    S32 s32DnsNumber;
    CHAR acIface[NETWORK_INTERFACE_NAME_LEN];
    memset(acIface, 0x0, sizeof(acIface));
    memcpy(acIface, eth_name_array[prase_interface_order(enNetCardID)], NETWORK_INTERFACE_NAME_LEN - 1);

    S32 s32Ret = net_eth_ipaddressget(acIface, pNetConfig->IpAddr);
    s32Ret |= net_eth_subnetmaskget(acIface, pNetConfig->NetMask);
    s32Ret |= net_eth_gatewayget(acIface, pNetConfig->GateWay);
    s32Ret |= net_eth_dnsget(acIface, acDns, &s32DnsNumber);

    if (SUCCESS != s32Ret)
    {
        HAL_DEBUG("net_get_config fail");
        return s32Ret;
    }

    if (NETWORK_SINGLE_DNS == s32DnsNumber)
    {
        strncpy(pNetConfig->PrimaryDns, acDns[0], NET_IPV6_ADDR_LENGTH + 1);
        strncpy(pNetConfig->SecondDns, "0.0.0.0", NET_IPV6_ADDR_LENGTH + 1);
    }
    else if (NETWORK_DOUBLE_DNS == s32DnsNumber)
    {
        strncpy(pNetConfig->PrimaryDns, acDns[0], NET_IPV6_ADDR_LENGTH + 1);
        strncpy(pNetConfig->SecondDns, acDns[1], NET_IPV6_ADDR_LENGTH + 1);
    }

    return SUCCESS;
}

S32 net_set_mac(NET_CARD_E enNetCardID, const NET_MAC_S* pNetConfig)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pNetConfig);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));
    S32 s32Sockfd;
    struct ifreq ifr;
    CHAR acMacReal[NETWORK_MAC_FILEDS_COUNT];
    memset(acMacReal, 0x0, sizeof(acMacReal));

    if (SUCCESS != prase_mac(acMacReal, pNetConfig->Mac))
    {
        HAL_ERROR("invalid parameter:%s", pNetConfig->Mac);
        return ERROR_NETWORK_INVALID_MAC;
    }

    if ((s32Sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        HAL_ERROR("socket create fail!");
        return ERROR_NETWORK_SET_MAC_FAILED;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, eth_name_array[prase_interface_order(enNetCardID)], NETWORK_INTERFACE_NAME_LEN - 1);
    ifr.ifr_hwaddr.sa_family = ARPHRD_ETHER;
    memcpy(ifr.ifr_hwaddr.sa_data, acMacReal, NETWORK_MAC_FILEDS_COUNT);

    if (ioctl(s32Sockfd, SIOCSIFHWADDR, &ifr) < 0)
    {
        close(s32Sockfd);
        return ERROR_NETWORK_SET_MAC_FAILED;
    }

    close(s32Sockfd);
    return SUCCESS;
}

S32 net_get_mac(NET_CARD_E enNetCardID,  NET_MAC_S* const pNetConfig)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pNetConfig);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));

    S32 s32Sockfd;
    struct ifreq ifr;

    s32Sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (s32Sockfd < 0)
    {
        HAL_ERROR("socket create fail!");
        return ERROR_NETWORK_GET_MAC_FAILED;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, eth_name_array[prase_interface_order(enNetCardID)], NETWORK_INTERFACE_NAME_LEN - 1);

    if (ioctl(s32Sockfd, SIOCGIFHWADDR, &ifr) < 0)
    {
        HAL_ERROR("SIOCGIFHWADDR fail!");
        close(s32Sockfd);
        return ERROR_NETWORK_GET_MAC_FAILED;
    }

    snprintf(pNetConfig->Mac, NET_MAC_ADDR_LENGTH + 1, "%02x:%02x:%02x:%02x:%02x:%02x",
             (U8)ifr.ifr_hwaddr.sa_data[0],
             (U8)ifr.ifr_hwaddr.sa_data[1],
             (U8)ifr.ifr_hwaddr.sa_data[2],
             (U8)ifr.ifr_hwaddr.sa_data[3],
             (U8)ifr.ifr_hwaddr.sa_data[4],
             (U8)ifr.ifr_hwaddr.sa_data[5]);
    close(s32Sockfd);
    return SUCCESS;
}

static S32 net_get_dhcppid(NET_CARD_E enNetCardID, U32* pPID)
{
    CHAR cmd[128];
    CHAR buff[512];
    CHAR name[32] = "udhcpc -i ";
    FILE* pFile = NULL;
    CHAR* pPidStr = NULL;
    CHAR* pRet = NULL;
    S32 s32Loop = 0;

    memset(cmd, 0, sizeof(cmd));
    memset(buff, 0, sizeof(buff));

    strncat(name, eth_name_array[prase_interface_order(enNetCardID)], NETWORK_INTERFACE_NAME_LEN);
    snprintf(cmd, sizeof(cmd), "busybox ps | grep \"%s\"", name);
    pFile = popen(cmd, "r");

    if (NULL == pFile)
    {
        return FAILURE;
    }

    for (s32Loop = 0; s32Loop < NETWORK_READ_DHCP_PID_TIMES; s32Loop++)
    {
        pRet = fgets(buff, sizeof(buff), pFile);

        if (NULL == pRet)
        {
            pclose(pFile);
            return FAILURE;
        }
    }

    pPidStr = strtok(buff, " ");

    if (NULL == pPidStr || strlen(pPidStr) == 0 )
    {
        pclose(pFile);
        return FAILURE;
    }

    if ((*pPID = atoi(pPidStr)) == 0)
    {
        pclose(pFile);
        return FAILURE;
    }

    pclose(pFile);
    return SUCCESS;
}

static BOOL is_dhcp_exist(NET_CARD_E enNetCard)
{
    NET_DHCP_ENTITY_S* pstTmpEntity = s_pstDhcpHead;

    while (NULL != pstTmpEntity)
    {
        if (pstTmpEntity->enNetCardID == enNetCard)
        {
            return TRUE;
        }

        pstTmpEntity = pstTmpEntity->pNext;
    }

    return FALSE;
}

static BOOL is_pppoe_exist(NET_CARD_E enNetCard)
{
    NET_PPPOE_ENTITY_S* pstTmpEntity = s_pstPppoeHead;

    while (NULL != pstTmpEntity)
    {
        if ((pstTmpEntity->stPppoeInfo).enNetCardID == enNetCard)
        {
            return TRUE;
        }

        pstTmpEntity = pstTmpEntity->pNext;
    }

    return FALSE;
}

static VOID* dhcpconn_thread(VOID* pvParams)
{
    NET_DHCP_ENTITY_S* pThreadDhcpEntity = NULL;
    FILE* pFile = NULL;
    CHAR* pRet = NULL;
    CHAR acBuff[256];
    CHAR acCommandLine[64];
    NET_CARD_E enNetCardID = NET_CARD_BUTT;

    memset(acBuff, 0, sizeof(acBuff));
    memset(acCommandLine, 0, sizeof(acCommandLine));

    NET_LOCK(&s_dhcpMutex);

    if (NULL == pvParams)
    {
        HAL_ERROR("the pvParams is NULL");
        NET_UNLOCK(&s_dhcpMutex);
        return NULL;
    }

    pThreadDhcpEntity = (NET_DHCP_ENTITY_S* )pvParams;
    enNetCardID = pThreadDhcpEntity->enNetCardID;

    if (NET_WLAN_0 <= enNetCardID)
    {
        (VOID)snprintf(acCommandLine, sizeof(acCommandLine), "udhcpc -i %s -q -n -t 10",
                       eth_name_array[prase_interface_order(enNetCardID)]);
    }
    else
    {
        (VOID)snprintf(acCommandLine, sizeof(acCommandLine), "udhcpc -i %s -q -n -t 5",
                       eth_name_array[prase_interface_order(enNetCardID)]);
    }

    pFile = popen(acCommandLine, "r");

    if (NULL == pFile)
    {
        HAL_ERROR("popen %s fail", acCommandLine);
        NET_UNLOCK(&s_dhcpMutex);
        return NULL;
    }

    if (NULL != pThreadDhcpEntity->pfnCallback)
    {
        pThreadDhcpEntity->pfnCallback(NET_DHCP_CONN_EVENT_CONNECTTING,
                                       eth_name_array[prase_interface_order(pThreadDhcpEntity->enNetCardID)]);
    }

    NET_UNLOCK(&s_dhcpMutex);

    while (TRUE)
    {
        pRet = fgets(acBuff, sizeof(acBuff), pFile);
        NET_LOCK(&s_dhcpMutex);

        if (!is_dhcp_exist(enNetCardID))
        {
            goto CLOSE_LABLE;
        }

        if (NULL == pRet)
        {
            if (NULL != pThreadDhcpEntity->pfnCallback)
            {
                pThreadDhcpEntity->pfnCallback(NET_DHCP_CONN_EVENT_CONNECT_FAIL,
                                               eth_name_array[prase_interface_order(pThreadDhcpEntity->enNetCardID)]);
            }

            NET_UNLOCK(&s_dhcpMutex);
            pclose(pFile);
            net_close_dhcp(enNetCardID);
            return NULL;

        }

        if (((pThreadDhcpEntity->enNetCardID < NET_WLAN_0) && (NULL != strstr(acBuff, "Received 0 reply")))
            || ((pThreadDhcpEntity->enNetCardID >= NET_WLAN_0) && (NULL != strstr(acBuff, "adding dns"))))
        {
            if (NULL != pThreadDhcpEntity->pfnCallback)
            {
                pThreadDhcpEntity->pfnCallback(NET_DHCP_CONN_EVENT_CONNECTED,
                                               eth_name_array[prase_interface_order(pThreadDhcpEntity->enNetCardID)]);
            }

            goto CLOSE_LABLE;
        }

        NET_UNLOCK(&s_dhcpMutex);
    }

CLOSE_LABLE:
    NET_UNLOCK(&s_dhcpMutex);
    pclose(pFile);
    return NULL;
}

S32 net_open_dhcp(NET_CARD_E enNetCardID, NET_DHCP_CONN_EVTCB dhcpCB)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));

    NET_DHCP_ENTITY_S* pstTmpEntity = NULL;
    NET_DHCP_ENTITY_S* pstDhcpEntity = NULL;
    pstDhcpEntity = (NET_DHCP_ENTITY_S*)malloc(sizeof(NET_DHCP_ENTITY_S));

    if ( NULL == pstDhcpEntity)
    {
        HAL_ERROR("malloc error");
        return FAILURE;
    }

    memset(pstDhcpEntity, 0, sizeof(NET_DHCP_ENTITY_S));

    pstDhcpEntity->enNetCardID = enNetCardID;
    pstDhcpEntity->pfnCallback = dhcpCB;
    NET_LOCK(&s_dhcpMutex);

    if (NULL == s_pstDhcpHead)
    {
        s_pstDhcpHead = pstDhcpEntity;
        s_pstDhcpHead->pNext = NULL;
    }
    else
    {
        pstTmpEntity = s_pstDhcpHead;

        while (NULL != pstTmpEntity->pNext)
        {
            if (pstTmpEntity->enNetCardID == enNetCardID)
            {
                HAL_ERROR("alreay in connecting or connected");
                free(pstDhcpEntity);
                pstDhcpEntity = NULL;
                NET_UNLOCK(&s_dhcpMutex);
                return FAILURE;
            }

            pstTmpEntity = pstTmpEntity->pNext;
        }

        pstTmpEntity->pNext = pstDhcpEntity;
        pstDhcpEntity->pNext = NULL;
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create((pthread_t*) & (pstDhcpEntity->u32DhcpThreadID), &attr, dhcpconn_thread, pstDhcpEntity);
    pthread_attr_destroy(&attr);
    NET_UNLOCK(&s_dhcpMutex);
    return SUCCESS;
}

S32 net_close_dhcp(NET_CARD_E enNetCardID)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));
    S32 s32Ret = FAILURE;
    U32 u32Pid = 0;
    NET_DHCP_ENTITY_S* pstTmpEntity = NULL;
    NET_DHCP_ENTITY_S* pstPrivEntity = NULL;
    CHAR acPidCmd[32];
    memset(acPidCmd, 0, sizeof(acPidCmd));

    NET_LOCK(&s_dhcpMutex);

    pstTmpEntity = s_pstDhcpHead;

    while (NULL != pstTmpEntity)
    {
        if (enNetCardID != pstTmpEntity->enNetCardID)
        {
            pstPrivEntity = pstTmpEntity;
            pstTmpEntity = pstTmpEntity->pNext;
            continue;
        }

        if (pstTmpEntity == s_pstDhcpHead)
        {
            s_pstDhcpHead = pstTmpEntity->pNext;
        }
        else if (NULL != pstPrivEntity)
        {
            pstPrivEntity->pNext = pstTmpEntity->pNext;
        }

        free(pstTmpEntity);
        pstTmpEntity = NULL;
        break;
    }

    s32Ret = net_get_dhcppid(enNetCardID, &u32Pid);

    if (SUCCESS == s32Ret)
    {
        snprintf(acPidCmd, sizeof(acPidCmd), "kill -9 %d ", u32Pid);
        system(acPidCmd);
    }

    NET_UNLOCK(&s_dhcpMutex);
    return SUCCESS;

}

static VOID* pppoeconn_thread(VOID* pvParams)
{
    NET_PPPOE_ENTITY_S* pThreadPppoeEntity = NULL;
    FILE* pFile = NULL;
    CHAR* pRet = NULL;
    CHAR acBuff[256];
    CHAR acCmd[768];  //if length of pppoe username and password is 256 ,it will exceed 512
    CHAR acRouteCmd[64];
    CHAR acTmp[NET_IPV6_ADDR_LENGTH + 1];
    S32 s32AddressValue[NETWORK_IP_VALUE_LENGTH];
    NET_CARD_E enNetCardID = NET_CARD_BUTT;

    memset(acBuff, 0, sizeof(acBuff));
    memset(acCmd, 0, sizeof(acCmd));
    memset(acRouteCmd, 0, sizeof(acRouteCmd));
    memset(acTmp, 0 , sizeof(acTmp));
    memset(s32AddressValue, 0, sizeof(s32AddressValue));

    NET_LOCK(&s_pppoeMutex);

    if (NULL == pvParams)
    {
        HAL_ERROR("the pvParams is NULL");
        NET_UNLOCK(&s_pppoeMutex);
        return NULL;
    }

    pThreadPppoeEntity = (NET_PPPOE_ENTITY_S* )pvParams;
    enNetCardID = (pThreadPppoeEntity->stPppoeInfo).enNetCardID;

    strncpy(acCmd, NETWORK_PPPOE_CONNECT_SCRIPT, strlen(NETWORK_PPPOE_CONNECT_SCRIPT));
    strncat(acCmd, " ", sizeof(" "));
    strncat(acCmd, eth_name_array[prase_interface_order((pThreadPppoeEntity->stPppoeInfo).enNetCardID)],
            strlen(eth_name_array[prase_interface_order((pThreadPppoeEntity->stPppoeInfo).enNetCardID)]));
    strncat(acCmd, " ", strlen(" "));
    strncat(acCmd, "\'", strlen("\'"));
    strncat(acCmd, (pThreadPppoeEntity->stPppoeInfo).acUser, strlen((pThreadPppoeEntity->stPppoeInfo).acUser));
    strncat(acCmd, "\'", strlen("\'"));
    strncat(acCmd, " ", strlen(" "));
    strncat(acCmd, "\'", strlen("\'"));
    strncat(acCmd, (pThreadPppoeEntity->stPppoeInfo).acPw, strlen((pThreadPppoeEntity->stPppoeInfo).acPw));
    strncat(acCmd, "\'", strlen("\'"));

    pFile = popen(acCmd, "r");

    if (NULL == pFile)
    {
        HAL_ERROR("popen %s fail", acCmd);
        NET_UNLOCK(&s_pppoeMutex);
        return NULL;
    }

    if (NULL != pThreadPppoeEntity->pfnCallback)
    {
        pThreadPppoeEntity->pfnCallback(NET_PPPOE_CONN_EVENT_CONNECTTING,
                                        eth_name_array[prase_interface_order((pThreadPppoeEntity->stPppoeInfo).enNetCardID)]);
    }

    NET_UNLOCK(&s_pppoeMutex);

    while (TRUE)
    {
        pRet = fgets(acBuff, sizeof(acBuff), pFile);
        NET_LOCK(&s_pppoeMutex);

        if (!is_pppoe_exist(enNetCardID))
        {
            goto CLOSE_LABLE;
        }

        if (NULL == pRet)
        {

            if (NULL != pThreadPppoeEntity->pfnCallback)
            {
                pThreadPppoeEntity->pfnCallback(NET_PPPOE_CONN_EVENT_CONNECT_FAIL,
                                                eth_name_array[prase_interface_order((pThreadPppoeEntity->stPppoeInfo).enNetCardID)]);
            }

            goto CLOSE_CARD_LABLE;
        }

        if (NULL != strstr(acBuff, "Using interface "))
        {
            strncpy(pThreadPppoeEntity->pppoeInterface, acBuff + strlen("Using interface "), NET_PPPOE_INTERFACE_LEN);
            (pThreadPppoeEntity->pppoeInterface)[NET_PPPOE_INTERFACE_LEN] = '\0';
            NET_UNLOCK(&s_pppoeMutex);
            continue;
        }

        if (NULL != strstr(acBuff, "remote IP address "))
        {
            strncpy(acTmp, acBuff + strlen("remote IP address "), NET_IPV6_ADDR_LENGTH);
            acTmp[strlen(acTmp) - 1] = '\0';//remove the '\n'

            if (FAILURE == netaddress_parse(acTmp, s32AddressValue))
            {
                HAL_ERROR("remote IP address is error, address = %s", acTmp);

                if (NULL != pThreadPppoeEntity->pfnCallback)
                {
                    pThreadPppoeEntity->pfnCallback(NET_PPPOE_CONN_EVENT_CONNECT_FAIL,
                                                    eth_name_array[prase_interface_order((pThreadPppoeEntity->stPppoeInfo).enNetCardID)]);
                }

                goto CLOSE_CARD_LABLE;
            }

            strncpy(acRouteCmd, "route add default gw ", sizeof("route add default gw "));
            strncat(acRouteCmd, acTmp, NET_IPV6_ADDR_LENGTH);

            system(acRouteCmd);

            if (NULL != pThreadPppoeEntity->pfnCallback)
            {
                pThreadPppoeEntity->pfnCallback(NET_PPPOE_CONN_EVENT_CONNECTED,
                                                eth_name_array[prase_interface_order((pThreadPppoeEntity->stPppoeInfo).enNetCardID)]);
            }

            goto CLOSE_LABLE;
        }

        if (NULL != strstr(acBuff, "authentication failed"))
        {
            if (NULL != pThreadPppoeEntity->pfnCallback)
            {
                pThreadPppoeEntity->pfnCallback(NET_PPPOE_CONN_EVENT_AUTH_FAIL,
                                                eth_name_array[prase_interface_order((pThreadPppoeEntity->stPppoeInfo).enNetCardID)]);
            }

            goto CLOSE_CARD_LABLE;
        }

        NET_UNLOCK(&s_pppoeMutex);
    }

CLOSE_CARD_LABLE:
    NET_UNLOCK(&s_pppoeMutex);
    pclose(pFile);
    net_close_pppoe(enNetCardID);
    return NULL;

CLOSE_LABLE:
    NET_UNLOCK(&s_pppoeMutex);
    pclose(pFile);
    return NULL;
}

S32 net_open_pppoe(const NET_PPPOE_INFO_S* pPppoeConfig, NET_PPPOE_CONN_EVTCB pppoeCB)
{
#ifdef HI_PPPOE_SUPPORT
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pPppoeConfig);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= pPppoeConfig->enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(pPppoeConfig->enNetCardID));
    NET_PPPOE_ENTITY_S* pstTmpEntity = NULL;
    NET_PPPOE_ENTITY_S* pstPppoeEntity = NULL;
    BOOL bOpen = FALSE;

    if ('\0' == pPppoeConfig->acUser[0] || '\0' == pPppoeConfig->acPw[0])
    {
        HAL_ERROR("username and password cannot be empty");
        return FAILURE;
    }

    net_get_openstatus(pPppoeConfig->enNetCardID, &bOpen);

    if (!bOpen)
    {
        HAL_ERROR("the device is not open,please enable it first");
        return FAILURE;
    }

    pstPppoeEntity = (NET_PPPOE_ENTITY_S*)malloc(sizeof(NET_PPPOE_ENTITY_S));

    if ( NULL == pstPppoeEntity)
    {
        HAL_ERROR("malloc error");
        return FAILURE;
    }

    memset(pstPppoeEntity, 0, sizeof(NET_PPPOE_ENTITY_S));

    memcpy(&(pstPppoeEntity->stPppoeInfo), pPppoeConfig, sizeof(NET_PPPOE_INFO_S));
    (pstPppoeEntity->stPppoeInfo).acUser[NET_MAX_PPPOE_USERNAME_LEN] = '\0';
    (pstPppoeEntity->stPppoeInfo).acPw[NET_MAX_PPPOE_PASSWD_LEN] = '\0';
    pstPppoeEntity->pfnCallback = pppoeCB;
    NET_LOCK(&s_pppoeMutex);

    if (NULL == s_pstPppoeHead)
    {
        s_pstPppoeHead = pstPppoeEntity;
        s_pstPppoeHead->pNext = NULL;
    }
    else
    {
        pstTmpEntity = s_pstPppoeHead;

        while (NULL != pstTmpEntity->pNext)
        {
            if (pstTmpEntity->stPppoeInfo.enNetCardID == pPppoeConfig->enNetCardID)
            {
                HAL_ERROR("alreay in connecting or connected");
                free(pstPppoeEntity);
                pstPppoeEntity = NULL;
                NET_UNLOCK(&s_pppoeMutex);
                return FAILURE;
            }

            pstTmpEntity = pstTmpEntity->pNext;
        }

        pstTmpEntity->pNext = pstPppoeEntity;
        pstPppoeEntity->pNext = NULL;
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create((pthread_t*) & (pstPppoeEntity->u32PppoeThread), &attr, pppoeconn_thread, pstPppoeEntity);
    pthread_attr_destroy(&attr);
    NET_UNLOCK(&s_pppoeMutex);
    return SUCCESS;
#else
    return FAILURE;
#endif
}

S32 net_close_pppoe(NET_CARD_E enNetCardID)
{
#ifdef HI_PPPOE_SUPPORT
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));

    NET_PPPOE_ENTITY_S* pstTmpEntity = NULL;
    NET_PPPOE_ENTITY_S* pstPrivEntity = NULL;

    NET_LOCK(&s_pppoeMutex);

    pstTmpEntity = s_pstPppoeHead;

    while (NULL != pstTmpEntity)
    {
        if (enNetCardID != (pstTmpEntity->stPppoeInfo).enNetCardID)
        {
            pstPrivEntity = pstTmpEntity;
            pstTmpEntity = pstTmpEntity->pNext;
            continue;
        }

        if (pstTmpEntity == s_pstPppoeHead)
        {
            s_pstPppoeHead = pstTmpEntity->pNext;
        }
        else if (NULL != pstPrivEntity)
        {
            pstPrivEntity->pNext = pstTmpEntity->pNext;
        }

        system(NETWORK_PPPOE_DISCONNECT_SCRIPT);
        free(pstTmpEntity);
        pstTmpEntity = NULL;
        break;
    }

    NET_UNLOCK(&s_pppoeMutex);
    return SUCCESS;
#else
    return FAILURE;
#endif
}

S32 net_get_pppoe_address(NET_CARD_E enNetCardID, NET_CONFIG_S* const pNetConfig)
{
#ifdef HI_PPPOE_SUPPORT
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pNetConfig);
    S32 s32Ret = FAILURE;
    NET_PPPOE_ENTITY_S* pstTmpEntity = NULL;
    NET_PPPOE_ENTITY_S* pstDstEntity = NULL;
    CHAR acDns[2][32];
    S32 s32DnsNumber = 0;

    NET_LOCK(&s_pppoeMutex);

    pstTmpEntity = s_pstPppoeHead;

    while (NULL != pstTmpEntity)
    {
        if (enNetCardID != (pstTmpEntity->stPppoeInfo).enNetCardID)
        {
            pstTmpEntity = pstTmpEntity->pNext;
            continue;
        }

        pstDstEntity = pstTmpEntity;
        break;
    }

    if (NULL == pstDstEntity)
    {
        HAL_ERROR("no connect pppoe");
        NET_UNLOCK(&s_pppoeMutex);
        return FAILURE;
    }

    s32Ret = net_eth_ipaddressget(pstDstEntity->pppoeInterface, pNetConfig->IpAddr);
    s32Ret |= net_eth_subnetmaskget(pstDstEntity->pppoeInterface, pNetConfig->NetMask);
    s32Ret |= net_eth_gatewayget(pstDstEntity->pppoeInterface, pNetConfig->GateWay);
    s32Ret |= net_ppp_dnsget(pstDstEntity->pppoeInterface, acDns, &s32DnsNumber);

    if (SUCCESS != s32Ret)
    {
        HAL_DEBUG("net_get_pppoe_address fail");
        NET_UNLOCK(&s_pppoeMutex);
        return s32Ret;
    }

    if (NETWORK_SINGLE_DNS == s32DnsNumber)
    {
        strncpy(pNetConfig->PrimaryDns, acDns[0], NET_IPV6_ADDR_LENGTH + 1);
        strncpy(pNetConfig->SecondDns, "0.0.0.0", NET_IPV6_ADDR_LENGTH + 1);
    }
    else if (NETWORK_DOUBLE_DNS == s32DnsNumber)
    {
        strncpy(pNetConfig->PrimaryDns, acDns[0], NET_IPV6_ADDR_LENGTH + 1);
        strncpy(pNetConfig->SecondDns, acDns[1], NET_IPV6_ADDR_LENGTH + 1);
    }

    NET_UNLOCK(&s_pppoeMutex);
    return SUCCESS;
#else
    return FAILURE;
#endif
}

S32 net_clear_address(NET_CARD_E enNetCardID)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID);
    HI_LOG_CHK_PARA_VALID(HI_NET_CHECK_SUPPORT(enNetCardID));
    struct ifreq ifr;
    struct sockaddr_in* sin;
    S32 s32Sockfd;

    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, eth_name_array[prase_interface_order(enNetCardID)], IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
    sin = (struct sockaddr_in*) (&ifr.ifr_addr);
    sin->sin_family = AF_INET;
    sin->sin_port = 0;
    sin->sin_addr.s_addr = 0;

    s32Sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (s32Sockfd < 0)
    {
        HAL_ERROR("socket create fail!");
        return FAILURE;
    }

    if (ioctl(s32Sockfd, SIOCSIFADDR, &ifr) < 0)
    {
        close(s32Sockfd);
        return FAILURE;
    }

    close(s32Sockfd);
    return SUCCESS;
}

#ifdef HI_WIFI_SUPPORT
static VOID net_wlan_callback(HI_WLAN_STA_EVENT_E event, VOID* pstPrivData)
{
    HAL_DEBUG("the event type is:%d\n", event);
    WLAN_STA_CONN_STATE_E enApConnState = WLAN_STA_CONN_STATUS_BUTT;

    switch (event)
    {
        case HI_WLAN_STA_EVENT_DISCONNECTED:
        {
            HI_STA_ASSERT_CALLBACK(s_pApEventCallback == NULL);
            enApConnState = WLAN_STA_CONN_STATUS_DISCONNECTED;
            s_pApEventCallback(enApConnState, pstPrivData);
            break;
        }

        case HI_WLAN_STA_EVENT_CONNECTING:
        {
            HI_STA_ASSERT_CALLBACK(s_pApEventCallback == NULL);
            enApConnState = WLAN_STA_CONN_STATUS_CONNECTING;
            s_pApEventCallback(enApConnState, pstPrivData);
            break;
        }

        case HI_WLAN_STA_EVENT_CONNECTED:
        {
            HI_STA_ASSERT_CALLBACK(s_pApEventCallback == NULL);
            enApConnState = WLAN_STA_CONN_STATUS_CONNECTED;
            s_pApEventCallback(enApConnState, pstPrivData);
            break;
        }

        case HI_WLAN_STA_EVENT_SCAN_RESULTS_AVAILABLE:
        {
            HI_STA_ASSERT_CALLBACK(s_pEventCallback == NULL);
            s_enEvent = WLAN_STA_EVENT_SCAN_COMPLETE;
            s_pEventCallback(s_enEvent, pstPrivData);
            break;
        }

        case HI_WLAN_STA_EVENT_SUPP_STOPPED:
        case HI_WLAN_STA_EVENT_DRIVER_STOPPED:
        {
            HI_STA_ASSERT_CALLBACK(s_pEventCallback == NULL);
            s_enEvent = WLAN_STA_EVENT_SCAN_ERROR;
            s_pEventCallback(s_enEvent, pstPrivData);
            break;
        }

        default:
            break;
    }
}
#endif

S32 net_sta_start(NET_CARD_E enNetCardID, NET_WLAN_STA_SCAN_EVTCB pEventCallback, NET_WLAN_STA_LINKAP_EVTCB pApEventCallback)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID || NET_WLAN_0 > enNetCardID);
#ifdef HI_WIFI_SUPPORT
    S32 s32Ret = FAILURE;
    s_pEventCallback = pEventCallback;
    s_pApEventCallback = pApEventCallback;

    NET_LOCK(&s_net_mutex);
    s32Ret = HI_WLAN_STA_Start(eth_name_array[prase_interface_order(enNetCardID)], net_wlan_callback);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_WLAN_STA_Start error,the s32Ret is :%d", s32Ret);
        HI_WLAN_STA_Stop(eth_name_array[prase_interface_order(enNetCardID)]);
        NET_UNLOCK(&s_net_mutex);

        if (FAILURE == s32Ret)
        {
            return FAILURE;
        }

        return ERROR_WLAN_PREFIX | (s32Ret * (-1));
    }

    NET_UNLOCK(&s_net_mutex);
#else
    return FAILURE;
#endif
    return SUCCESS;
}

S32 net_sta_startscan(NET_CARD_E enNetCardID)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID || NET_WLAN_0 > enNetCardID);
#ifdef HI_WIFI_SUPPORT
    S32 s32Ret = FAILURE;
    NET_LOCK(&s_net_mutex);
    s32Ret = HI_WLAN_STA_StartScan(eth_name_array[prase_interface_order(enNetCardID)]);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_WLAN_STA_StartScan error,the s32Ret is :%d", s32Ret);
        NET_UNLOCK(&s_net_mutex);

        if (FAILURE == s32Ret)
        {
            return FAILURE;
        }

        return ERROR_WLAN_PREFIX | (s32Ret * (-1));
    }

    NET_UNLOCK(&s_net_mutex);
    HAL_DEBUG("HI_WLAN_STA_StartScan success,the s32Ret is :%d", s32Ret);

    if (NULL != s_pEventCallback)
    {
        s_pEventCallback(WLAN_STA_EVENT_SCAN_SCANNING, NULL);
    }

    s_enEvent = WLAN_STA_EVENT_SCAN_SCANNING;
#else
    return FAILURE;
#endif
    return SUCCESS;
}

S32 net_sta_stop(NET_CARD_E enNetCardID)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID || NET_WLAN_0 > enNetCardID);
#ifdef HI_WIFI_SUPPORT
    S32 s32Ret = FAILURE;
    NET_LOCK(&s_net_mutex);
    s32Ret = HI_WLAN_STA_Stop(eth_name_array[prase_interface_order(enNetCardID)]);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_WLAN_STA_Stop error,the s32Ret is :%d", s32Ret);
        NET_UNLOCK(&s_net_mutex);

        if (FAILURE == s32Ret)
        {
            return FAILURE;
        }

        return ERROR_WLAN_PREFIX | (s32Ret * (-1));
    }

    NET_UNLOCK(&s_net_mutex);
    s_enEvent = WLAN_STA_EVENT_SCAN_IDLE;
#else
    return FAILURE;
#endif
    return SUCCESS;
}

S32 net_sta_getscanstatus(NET_CARD_E enNetCardID, WLAN_STA_EVENT_E* pScanStatus)
{
#ifdef HI_WIFI_SUPPORT
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pScanStatus);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID || NET_WLAN_0 > enNetCardID);
    *pScanStatus = s_enEvent;
#else
    return FAILURE;
#endif
    return SUCCESS;
}

S32 net_sta_getresultnum(NET_CARD_E enNetCardID, U32* pNumber)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pNumber);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID || NET_WLAN_0 > enNetCardID);
#ifdef HI_WIFI_SUPPORT
    S32 s32Ret = FAILURE;
    U32 u32TotalNumber = NETWORK_MAX_AP_COUNT;
    HI_WLAN_STA_ACCESSPOINT_S* pstApList = (HI_WLAN_STA_ACCESSPOINT_S*)
                                           malloc(sizeof(HI_WLAN_STA_ACCESSPOINT_S) * NETWORK_MAX_AP_COUNT);
    HI_LOG_CHK_RETURN((NULL == pstApList), FAILURE, "net_sta_getresultnum malloc error");
    memset(pstApList, 0, sizeof(HI_WLAN_STA_ACCESSPOINT_S) * NETWORK_MAX_AP_COUNT);
    NET_LOCK(&s_net_mutex);
    s32Ret = HI_WLAN_STA_GetScanResults(eth_name_array[prase_interface_order(enNetCardID)], pstApList, &u32TotalNumber);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("Call HI_WLAN_STA_GetScanResults error.");
        NET_UNLOCK(&s_net_mutex);
        free(pstApList);
        pstApList = NULL;

        if (FAILURE == s32Ret)
        {
            return FAILURE;
        }

        return ERROR_WLAN_PREFIX | (s32Ret * (-1));
    }

    *pNumber = u32TotalNumber;
    NET_UNLOCK(&s_net_mutex);
    free(pstApList);
    pstApList = NULL;
#else
    return FAILURE;
#endif
    return SUCCESS;
}

S32 net_sta_getresult(NET_CARD_E enNetCardID,  WLAN_STA_AccessPoint_S* pAPList, U32 ListNodeNumber, U32* pGettedNumber)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pAPList);
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pGettedNumber);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID || NET_WLAN_0 > enNetCardID);
#ifdef HI_WIFI_SUPPORT
    U32 u32TotalNumber = NETWORK_MAX_AP_COUNT;
    U32 i = 0;
    S32 s32Ret = FAILURE;

    HI_WLAN_STA_ACCESSPOINT_S* pstApList = (HI_WLAN_STA_ACCESSPOINT_S*)
                                           malloc(sizeof(HI_WLAN_STA_ACCESSPOINT_S) * NETWORK_MAX_AP_COUNT);
    HI_LOG_CHK_RETURN((NULL == pstApList), FAILURE, "net_sta_getresult malloc error");
    memset(pstApList, 0, sizeof(HI_WLAN_STA_ACCESSPOINT_S) * NETWORK_MAX_AP_COUNT);

    NET_LOCK(&s_net_mutex);
    s32Ret = HI_WLAN_STA_GetScanResults(eth_name_array[prase_interface_order(enNetCardID)], pstApList, &u32TotalNumber);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_WLAN_STA_GetScanResults error.");
        NET_UNLOCK(&s_net_mutex);
        free(pstApList);
        pstApList = NULL;

        if (FAILURE == s32Ret)
        {
            return FAILURE;
        }

        return ERROR_WLAN_PREFIX | (s32Ret * (-1));
    }

    for (i = 0; i < u32TotalNumber && i < ListNodeNumber; i++)
    {
        strncpy(pAPList[i].ssid, pstApList[i].ssid, STA_MAX_SSID_LEN + 1);

        switch (pstApList[i].security)
        {
            case HI_WLAN_SECURITY_OPEN:
                pAPList[i].security = WLAN_SECURITY_OPEN;
                break;

            case HI_WLAN_SECURITY_WEP:
                pAPList[i].security = WLAN_SECURITY_WEP;
                break;

            case HI_WLAN_SECURITY_WPA_WPA2_PSK:
                pAPList[i].security = WLAN_SECURITY_WPA_WPA2_PSK;
                break;

            case HI_WLAN_SECURITY_WPA_WPA2_EAP:
                pAPList[i].security = WLAN_SECURITY_WPA_WPA2_EAP;
                break;

            case HI_WLAN_SECURITY_WAPI_PSK:
                pAPList[i].security = WLAN_SECURITY_WAPI_PSK;
                break;

            case HI_WLAN_SECURITY_WAPI_CERT:
                pAPList[i].security = WLAN_SECURITY_WAPI_CERT;
                break;

            default:
                HAL_ERROR("Invalid para stLinkInfo.security.");
                pAPList[i].security = WLAN_SECURITY_WPA_WPA2_PSK;
                break;
        }

        pAPList[i].level = pstApList[i].level;
        pAPList[i].channel = pstApList[i].channel;
    }

    *pGettedNumber = i;
    NET_UNLOCK(&s_net_mutex);
    free(pstApList);
    pstApList = NULL;
#else
    return FAILURE;
#endif
    return SUCCESS;
}

S32 net_sta_connect(NET_CARD_E enNetCardID, const WLAN_STA_Config_S* pConfig)
{
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pConfig);
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID || NET_WLAN_0 > enNetCardID);
#ifdef HI_WIFI_SUPPORT
    S32 s32Ret = FAILURE;
    HI_WLAN_STA_CONFIG_S stWlanStaConfig;
    memset(&stWlanStaConfig, 0x0, sizeof(HI_WLAN_STA_CONFIG_S));
    strncpy(stWlanStaConfig.ssid, pConfig->ssid, STA_MAX_SSID_LEN);
    stWlanStaConfig.security = (HI_WLAN_SECURITY_E)pConfig->security;
    strncpy(stWlanStaConfig.psswd, pConfig->psswd, MAX_PSSWD_LEN);
    stWlanStaConfig.hidden_ssid = (HI_BOOL) pConfig->hidden_ssid;
    NET_LOCK(&s_net_mutex);
    s32Ret =  HI_WLAN_STA_Connect(eth_name_array[prase_interface_order(enNetCardID)], &stWlanStaConfig);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_WLAN_STA_Connect error.the s32Ret is :%d", s32Ret);
        NET_UNLOCK(&s_net_mutex);

        if (FAILURE == s32Ret)
        {
            return FAILURE;
        }

        return ERROR_WLAN_PREFIX | (s32Ret * (-1));
    }

    NET_UNLOCK(&s_net_mutex);
#else
    return FAILURE;
#endif
    return SUCCESS;
}

S32 net_sta_disconnect(NET_CARD_E enNetCardID)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID || NET_WLAN_0 > enNetCardID);
#ifdef HI_WIFI_SUPPORT
    S32 s32Ret = FAILURE;
    NET_LOCK(&s_net_mutex);
    s32Ret = HI_WLAN_STA_Disconnect(eth_name_array[prase_interface_order(enNetCardID)]);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_WLAN_STA_Disconnect error.the s32Ret is :%d", s32Ret);
        NET_UNLOCK(&s_net_mutex);

        if (FAILURE == s32Ret)
        {
            return FAILURE;
        }

        return ERROR_WLAN_PREFIX | (s32Ret * (-1));
    }

    NET_UNLOCK(&s_net_mutex);
#else
    return FAILURE;
#endif
    return SUCCESS;
}

S32 net_sta_getconnectstatus(NET_CARD_E enNetCardID, WLAN_STA_CONN_Status_S* pStatus)
{
    HI_LOG_CHK_PARA_VALID(NET_CARD_BUTT <= enNetCardID || NET_WLAN_0 > enNetCardID);
    HI_LOG_CHK_PARA_NULL_PTR(NULL == pStatus);
#ifdef HI_WIFI_SUPPORT
    S32 s32Ret = FAILURE;
    HI_WLAN_STA_CONN_STATUS_S stConnStatus;
    memset(&stConnStatus, 0, sizeof(HI_WLAN_STA_CONN_STATUS_S));
    NET_LOCK(&s_net_mutex);
    s32Ret = HI_WLAN_STA_GetConnectionStatus(eth_name_array[prase_interface_order(enNetCardID)], &stConnStatus);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_WLAN_STA_GetConnectionStatus error,s32Ret is %d", s32Ret);
        NET_UNLOCK(&s_net_mutex);

        if (FAILURE == s32Ret)
        {
            return FAILURE;
        }

        return ERROR_WLAN_PREFIX | (s32Ret * (-1));
    }

    if (stConnStatus.state != HI_WLAN_STA_CONN_STATUS_DISCONNECTED)
    {
        pStatus->state = (WLAN_STA_CONN_STATE_E)stConnStatus.state;
        strncpy((pStatus->ap).ssid, stConnStatus.ap.ssid, STA_MAX_SSID_LEN + 1);
        strncpy((pStatus->ap).bssid, stConnStatus.ap.bssid, BSSID_LEN + 1);
        (pStatus->ap).level = stConnStatus.ap.level;
        (pStatus->ap).channel = stConnStatus.ap.channel;
        (pStatus->ap).security = (WLAN_SECURITY_E)stConnStatus.ap.security;
    }
    else
    {
        pStatus->state = WLAN_STA_CONN_STATUS_DISCONNECTED;
    }

    NET_UNLOCK(&s_net_mutex);
#else
    return FAILURE;
#endif
    return SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
