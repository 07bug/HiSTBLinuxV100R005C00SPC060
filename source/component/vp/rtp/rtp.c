#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "linux_list.h"
#include "hi_osal.h"
#include "rtp.h"
#include "rtp_priv.h"
#include "rtcp_priv.h"
#include "hi_common.h"
#include "hi_mpi_mem.h"
#include "hi_unf_common.h"

extern int  VP_DUMP(char* str, const unsigned char *buf, unsigned int len);

typedef struct hiRTCP_ATTR_S
{
    HI_VOID*          hRTCP;             /* RTCP handle */
    HI_BOOL           bStop;             /* tag to stop RTCP send & recv thread */
    pthread_t         pThreadRecv;       /* tag of thread */
    pthread_t         pThreadSend;       /* tag of thread */
    HI_S32            s32Socket;         /* RTCP session socket */
    RTP_RTCP_REPORT_S stReport;          /* user get network report from this struct */
    VP_RTP_INFO       stRtpInfo;         /* inner use */
    VP_RTCP_INFO      stRtcpInfo;        /* inner use */
} RTCP_ATTR_S;

typedef struct hiRTP_PRIV_ATTR_S
{
    HI_HANDLE       hRTP;                /* RTP handle */
    HI_S32          s32Socket;           /* RTP session socket */
    RTP_RECV_BUF_S* pstRecvBuf;          /* MMZ recv buffer, full & free list */
    HI_BOOL         bRecvStop;           /* tag of stop receving from network thread */
    HI_BOOL         bStartRev;           /* flag for receive fisrt rtp packet*/
    pthread_t       threadRecv;          /* tag of thread */
    RTP_ATTR_S      stRtpAttr;           /* save user config here */
    HI_U32          u32SeqNum;           /* tag of packet number, increase in internal */
    HI_U32          u32CurNum;           /* current process packet number */
    RTCP_ATTR_S     stRtcp;              /* RTCP params */
    RTP_RTCP_REPORT_S stReport;          /* user get network report from this struct */
} RTP_PRIV_ATTR_S;

static HI_BOOL g_bRtpInited = HI_FALSE;
#define HI_RTP_STAT_DELAY_INTERVAL 30

static RTP_PRIV_ATTR_S g_stRtpAttr[RTP_MAX_SESSION_NUM];
static pthread_mutex_t g_RtpMutex = PTHREAD_MUTEX_INITIALIZER;
#define HI_RTP_LOCK() (void)pthread_mutex_lock(&g_RtpMutex);
#define HI_RTP_UNLOCK() (void)pthread_mutex_unlock(&g_RtpMutex);

#define CHECK_RTP_INIT \
    do {\
        HI_RTP_LOCK(); \
        if (HI_FALSE == g_bRtpInited)\
        { \
            HI_RTP_UNLOCK(); \
            return HI_ERR_RTP_NOT_INIT; \
        } \
        HI_RTP_UNLOCK(); \
    } while (0)

#define CHECK_RTP_NULL_PTR(ptr) \
    do {\
        if (NULL == (ptr))\
        {\
            HI_ERR_RTP("PTR('%s') is NULL.\n", # ptr); \
            return HI_ERR_RTP_PTR_NULL; \
        } \
    } while (0)

#define CHECK_RTP_HANDLE(hRTP) \
    do {\
        HI_RTP_LOCK(); \
        if (HI_NULL == hRTP)\
        {\
            HI_RTP_UNLOCK(); \
            return HI_ERR_RTP_INVALID_HANDLE; \
        } \
        if (HI_INVALID_HANDLE == hRTP)\
        {\
            HI_RTP_UNLOCK(); \
            return HI_ERR_RTP_INVALID_HANDLE; \
        } \
        if (HI_ID_RTP != (HI_CHAR)(hRTP >> 24))\
        {\
            HI_RTP_UNLOCK(); \
            return HI_ERR_RTP_INVALID_HANDLE; \
        } \
        HI_RTP_UNLOCK(); \
    } while (0)

#ifndef TRANS_CHK_RETURN_NO_PRINT
#define TRANS_CHK_RETURN_NO_PRINT(val, s32Ret) \
do \
{ \
    if ((val)) \
    { \
        return (s32Ret); \
     } \
} while (0)
#endif

#ifndef TRANS_CHK_RETURN_PRINT
#define TRANS_CHK_RETURN_PRINT(val, s32Ret, ...) \
do \
{ \
    if ((val)) \
    { \
        HI_ERR_RTP(__VA_ARGS__); \
        return (s32Ret); \
     } \
} while (0)
#endif
HI_S32 RTCP_EnableNonblock(HI_S32 fd)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_S32 old_flags = fcntl(fd, F_GETFL, 0);
    HI_U32 flag = 0;

    if (-1 == old_flags)
    {
        return -errno;
    }

    flag = (HI_U32)old_flags;
    s32Ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
    if (-1 == s32Ret)
    {
        return -errno;
    }

    return HI_SUCCESS;
}

HI_S32 RTCP_Create(HI_U32 u32Chn)
{
    HI_S32 s32Ret = HI_FAILURE;
    struct sockaddr_in sktAddr;
    struct sockaddr_in6 sktIp6Addr;

    s32Ret = VP_RTCP_CreateSession(&g_stRtpAttr[u32Chn].stRtcp.hRTCP, g_stRtpAttr[u32Chn].hRTP);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_RTP("Cannot creat rtcp session, ret %x\n", s32Ret);
        return s32Ret;
    }

    /* create RTCP socket */
    if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bIsIpv4)
    {
        g_stRtpAttr[u32Chn].stRtcp.s32Socket = socket(AF_INET, SOCK_DGRAM, 0);
    }
    else
    {
        g_stRtpAttr[u32Chn].stRtcp.s32Socket = socket(AF_INET6, SOCK_DGRAM, 0);
    }

    if (g_stRtpAttr[u32Chn].stRtcp.s32Socket == -1)
    {
        HI_ERR_RTP("RTCP socket creates failed\n");
        s32Ret = VP_RTCP_DeleteSession(g_stRtpAttr[u32Chn].stRtcp.hRTCP);

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_RTP("VP_RTCP_DeleteSession failed\n");
        }

        return HI_ERR_RTP_NET_ERR;
    }

    /* set to non-block mode, in case RTCP session backups when disconnect */
    s32Ret = RTCP_EnableNonblock(g_stRtpAttr[u32Chn].stRtcp.s32Socket);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_RTP("RTP_EnableNonblock failed, ret = 0x%08x\n", s32Ret);
        s32Ret = VP_RTCP_DeleteSession(g_stRtpAttr[u32Chn].stRtcp.hRTCP);

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_RTP("VP_RTCP_DeleteSession failed\n");
        }

        return HI_ERR_RTP_NET_ERR;
    }

    /* bind local IP and port(RTP_port +1) to socket */
    if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bIsIpv4)
    {
        memcpy(&sktAddr, &g_stRtpAttr[u32Chn].stRtpAttr.stLocalNet.stIpv4Attr, sizeof(struct sockaddr_in));
        sktAddr.sin_port = htons(ntohs(sktAddr.sin_port) + 1);
        s32Ret = bind(g_stRtpAttr[u32Chn].stRtcp.s32Socket, (struct sockaddr*)&sktAddr, sizeof(struct sockaddr));
    }
    else
    {
        memcpy(&sktIp6Addr, &g_stRtpAttr[u32Chn].stRtpAttr.stLocalNet.stIpv6Attr, sizeof(struct sockaddr_in6));
        sktIp6Addr.sin6_port = htons(ntohs(sktIp6Addr.sin6_port) + 1);
        s32Ret = bind(g_stRtpAttr[u32Chn].stRtcp.s32Socket, (struct sockaddr*)&sktIp6Addr, sizeof(struct sockaddr_in6));
    }
    if (s32Ret == -1)
    {
        HI_ERR_RTP("RTCP bind socket failed\n");
        shutdown(g_stRtpAttr[u32Chn].stRtcp.s32Socket, 2);
        close(g_stRtpAttr[u32Chn].stRtcp.s32Socket);
        s32Ret = VP_RTCP_DeleteSession(g_stRtpAttr[u32Chn].stRtcp.hRTCP);

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_RTP("VP_RTCP_DeleteSession failed\n");
        }

        return HI_ERR_RTP_NET_ERR;
    }

    g_stRtpAttr[u32Chn].stRtcp.bStop = HI_FALSE;
    if (pthread_create(&g_stRtpAttr[u32Chn].stRtcp.pThreadRecv, HI_NULL, RTP_ScheduleRtcpRecv, (HI_VOID*)(HI_SIZE_T)u32Chn))
    {
        HI_ERR_RTP("pthread_create RTP_ScheduleRtcpRecv failed\n");
        shutdown(g_stRtpAttr[u32Chn].stRtcp.s32Socket, 2);
        close(g_stRtpAttr[u32Chn].stRtcp.s32Socket);
        s32Ret = VP_RTCP_DeleteSession(g_stRtpAttr[u32Chn].stRtcp.hRTCP);

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_RTP("VP_RTCP_DeleteSession failed\n");
        }

        return HI_FAILURE;
    }

    if (pthread_create(&g_stRtpAttr[u32Chn].stRtcp.pThreadSend, HI_NULL, RTP_ScheduleRtcpSend, (HI_VOID*)(HI_SIZE_T)u32Chn))
    {
        HI_ERR_RTP("pthread_create RTP_ScheduleRtcpSend failed\n");
        shutdown(g_stRtpAttr[u32Chn].stRtcp.s32Socket, 2);
        close(g_stRtpAttr[u32Chn].stRtcp.s32Socket);

        g_stRtpAttr[u32Chn].stRtcp.bStop = HI_TRUE;
        if (pthread_join(g_stRtpAttr[u32Chn].stRtcp.pThreadRecv, HI_NULL))
        {
            HI_ERR_RTP("pThreadRecv failed, line = %d\n", __LINE__);
        }

        s32Ret = VP_RTCP_DeleteSession(g_stRtpAttr[u32Chn].stRtcp.hRTCP);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_RTP("VP_RTCP_DeleteSession failed\n");
        }

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID RTCP_Destroy(HI_U32 u32Chn)
{
    HI_S32 s32Ret = HI_FAILURE;

    shutdown(g_stRtpAttr[u32Chn].stRtcp.s32Socket, 2);
    close(g_stRtpAttr[u32Chn].stRtcp.s32Socket);
    g_stRtpAttr[u32Chn].stRtcp.bStop = HI_TRUE;
    if (pthread_join(g_stRtpAttr[u32Chn].stRtcp.pThreadRecv, HI_NULL))
    {
        HI_ERR_RTP("pThreadRecv failed, line = %d\n", __LINE__);
    }

    if (pthread_join(g_stRtpAttr[u32Chn].stRtcp.pThreadSend, HI_NULL))
    {
        HI_ERR_RTP("pThreadSend failed, line = %d\n", __LINE__);
    }

    s32Ret = VP_RTCP_DeleteSession(g_stRtpAttr[u32Chn].stRtcp.hRTCP);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_RTP("VP_RTCP_DeleteSession failed\n");
    }
    return;
}

HI_VOID* RTP_ScheduleRtcpSend(HI_VOID* args)
{
    HI_S32 s32Ret;
    HI_U32 u32Chn = (HI_U32)(HI_SIZE_T)args;
    HI_U32 u32SendLen;
    HI_U8* pu8SendAddr = HI_NULL;
    VP_PACKET_STRU* pRtcpPack = HI_NULL;
    VP_PACKET_STRU* pRtcpPackAddrBak = HI_NULL;
    //socklen_t sktLen;
    struct sockaddr_in stIpv4Remote  = {0};
    struct sockaddr_in6 stIpv6Remote = {0};

    pRtcpPack = (VP_PACKET_STRU*)HI_MALLOC(HI_ID_USR_START, sizeof(VP_PACKET_STRU));
    if (HI_NULL == pRtcpPack)
    {
        HI_ERR_RTP("RTCP Pack malloc failed.\n");
        return HI_NULL;
    }

    pRtcpPackAddrBak = pRtcpPack;
    memset(pRtcpPack, 0, sizeof(VP_PACKET_STRU));
    if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bIsIpv4)
    {
        memcpy(&stIpv4Remote, &g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv4Attr, sizeof(struct sockaddr_in));
        stIpv4Remote.sin_port =  htons(ntohs(stIpv4Remote.sin_port) + 1);
        //sktLen = sizeof(struct sockaddr_in);
    }
    else
    {
        memcpy(&stIpv6Remote, &g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv6Attr, sizeof(struct sockaddr_in6));
        stIpv6Remote.sin6_port = htons(ntohs(stIpv6Remote.sin6_port) + 1);
        //sktLen = sizeof(struct sockaddr_in6);
    }

    while (HI_FALSE == g_stRtpAttr[u32Chn].stRtcp.bStop)
    {

        s32Ret = VP_RTCP_SendCtrl(g_stRtpAttr[u32Chn].stRtcp.hRTCP, pRtcpPack);
        if (HI_SUCCESS == s32Ret)
        {
            pu8SendAddr = pRtcpPack->u.stRtpPack.data;
            u32SendLen = pRtcpPack->u.stRtpPack.ulLen;

            if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bIsIpv4)
            {
                s32Ret = sendto(g_stRtpAttr[u32Chn].stRtcp.s32Socket, pu8SendAddr, u32SendLen, 0,
                                (struct sockaddr*)&stIpv4Remote, sizeof(struct sockaddr_in));
            }
            else
            {
                s32Ret = sendto(g_stRtpAttr[u32Chn].stRtcp.s32Socket, pu8SendAddr, u32SendLen, 0,
                                (struct sockaddr*)&stIpv6Remote, sizeof(struct sockaddr_in6));
            }
            if (s32Ret == -1)
            {
                HI_ERR_RTP("RTCP send packets failed %s.\n", strerror(errno));
            }
        }

        vp_usleep(100 * 1000);
    }
    HI_FREE(HI_ID_USR_START, pRtcpPackAddrBak);
    pRtcpPackAddrBak = HI_NULL;

    return HI_NULL;
}

HI_VOID* RTP_ScheduleRtcpRecv(HI_VOID* args)
{
    HI_S32 s32Ret;
    HI_U32 u32Chn = (HI_U32)(HI_SIZE_T)args;
    RTP_RTCP_REPORT_S* pstReport  = HI_NULL;
    VP_RTCP_SESSION*   pstSession = HI_NULL;
    VP_RTPPACKET_STRU stPacket;
    struct sockaddr_in stIpv4Remote  = {0};
    struct sockaddr_in6 stIpv6Remote = {0};
    struct sockaddr_in stIpv4AttrReceived = {0};
    struct sockaddr_in6 stIpv6AttrReceived = {0};
    socklen_t sktLen;

    if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bIsIpv4)
    {
        memcpy(&stIpv4Remote, &g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv4Attr, sizeof(struct sockaddr_in));
        stIpv4Remote.sin_port =  htons(ntohs(stIpv4Remote.sin_port) + 1);
        sktLen = sizeof(struct sockaddr_in);
    }
    else
    {
        memcpy(&stIpv6Remote, &g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv6Attr, sizeof(struct sockaddr_in6));
        stIpv6Remote.sin6_port = htons(ntohs(stIpv6Remote.sin6_port) + 1);
        sktLen = sizeof(struct sockaddr_in6);
    }

    memset(&stPacket, 0, sizeof(stPacket));
    stPacket.ulLen = RTCP_PACKET_DATA_MAX_LEN;
    while (HI_FALSE == g_stRtpAttr[u32Chn].stRtcp.bStop)
    {
        if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bIsIpv4)
        {
            s32Ret = recvfrom(g_stRtpAttr[u32Chn].stRtcp.s32Socket, stPacket.data, RTCP_PACKET_DATA_MAX_LEN, 0,
                              (struct sockaddr*)&stIpv4AttrReceived, &sktLen);
        }
        else
        {
            s32Ret = recvfrom(g_stRtpAttr[u32Chn].stRtcp.s32Socket, stPacket.data, RTCP_PACKET_DATA_MAX_LEN, 0,
                              (struct sockaddr*)&stIpv6AttrReceived, &sktLen);
        }
        if (0 >= s32Ret)
        {
            vp_usleep(10 * 1000);
            continue;
        }

        if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bIsIpv4)
        {
            if ((0 != memcmp((const char*)(&stIpv4Remote.sin_addr),
                             (const char*)&stIpv4AttrReceived.sin_addr, sizeof(struct in_addr)))
                || (stIpv4AttrReceived.sin_port != stIpv4Remote.sin_port)
               )
            {
                HI_INFO_RTP("Rtcp the ip or port is not right\n");
                continue;
            }
        }
        else
        {
            if ((0 != memcmp((const char*)(&stIpv6Remote.sin6_addr),
                             (const char*)&stIpv6AttrReceived.sin6_addr, sizeof(struct in6_addr)))
                || (stIpv6AttrReceived.sin6_port != stIpv6Remote.sin6_port)
               )
            {
                HI_INFO_RTP("Rtcp the ip or port is not right\n");
                continue;
            }
        }

        stPacket.ulLen = (HI_U32)s32Ret;
        s32Ret = VP_RTCP_ParsePacket(g_stRtpAttr[u32Chn].stRtcp.hRTCP, &stPacket,
                                     &g_stRtpAttr[u32Chn].stRtcp.stRtcpInfo);

        memset(&stPacket, 0, stPacket.ulLen );
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_RTP("RTCP parse packets failed.\n");
            continue;
        }

        pstSession = (VP_RTCP_SESSION*)g_stRtpAttr[u32Chn].stRtcp.hRTCP;
        pstReport = &g_stRtpAttr[u32Chn].stRtcp.stReport;

        pstReport->stRecvInfo.u32Delay  = pstSession->stRtcpStatisticInfo.stRecvInfo.uiDelay;
        pstReport->stRecvInfo.u32Jitter = pstSession->stRtcpStatisticInfo.stRecvInfo.uiJitter;
        pstReport->stRecvInfo.u32LostPackets = pstSession->stRtcpStatisticInfo.stRecvInfo.uiTotalLostPacket;
        pstReport->stRecvInfo.u32LossPercent = pstSession->stRtcpStatisticInfo.stRecvInfo.uiLossFraction;

    }

    return HI_NULL;
}

HI_S32 RTP_CheckUserConfig(const RTP_ATTR_S* pstRtpAttr)
{
    CHECK_RTP_NULL_PTR(pstRtpAttr);

    if ((0 != pstRtpAttr->bIsIpv4) && (1 != pstRtpAttr->bIsIpv4))
    {
        HI_ERR_RTP("wrong af inet, value %d!\n", pstRtpAttr->bIsIpv4);
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    if (pstRtpAttr->enCtrlMod > RTP_SEND_AND_RECV)
    {
        HI_ERR_RTP("RTP send and receive mode is invalid(%d)\n", pstRtpAttr->enCtrlMod);
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    if (pstRtpAttr->u32SortDepth > RTP_MAX_SORT_DEPTH)
    {
        HI_ERR_RTP("RTP sort depth is invalid(%d)\n", pstRtpAttr->u32SortDepth);
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    if ((pstRtpAttr->u32RecvBufNum <= 0) || (pstRtpAttr->u32RecvBufNum > RTP_MAX_REORDER_BUF_NUM))
    {
        HI_ERR_RTP("RTP buffer num is invalid(%d)\n", pstRtpAttr->u32RecvBufNum);
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    if ((pstRtpAttr->u32RecvBufSize <= 0) || (pstRtpAttr->u32RecvBufSize > RTP_MAX_REORDER_BUF_SIZE))
    {
        HI_ERR_RTP("RTP buffer size is invalid(%d)\n", pstRtpAttr->u32RecvBufSize);
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    if ((pstRtpAttr->u32SplitSize <= 0) || (pstRtpAttr->u32SplitSize > RTP_MAX_SPLIT_SIZE))
    {
        HI_ERR_RTP("RTP split size is invalid(%d)\n", pstRtpAttr->u32SplitSize);
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    if (pstRtpAttr->u32SplitSize > pstRtpAttr->u32RecvBufSize)
    {
        HI_ERR_RTP("RTP split size(%d) is bigger than bufsize(%d)\n", pstRtpAttr->u32SplitSize, pstRtpAttr->u32RecvBufSize);
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    if (pstRtpAttr->u32PayLoadType >= RTP_MAX_PAYLOADS)
    {
        HI_ERR_RTP("RTP PayLoadType is invalid(%d)\n", pstRtpAttr->u32PayLoadType);
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    return HI_SUCCESS;
}

HI_S32 RTP_FindValidChannel(const HI_HANDLE* phRTP, HI_U32* hId)
{
    HI_U32 i;

    for (i = 0; i < RTP_MAX_SESSION_NUM; i++)
    {
        if (g_stRtpAttr[i].hRTP == *phRTP)
        {
            break;
        }
    }

    if (i == RTP_MAX_SESSION_NUM)
    {
        return HI_ERR_RTP_INVALID_HANDLE;
    }

    *hId = i;
    return HI_SUCCESS;
}

HI_VOID RTP_HeaderPacket(HI_U8* pPackAddr, HI_U32 u32TimeStamp, HI_U32 u32Marker,
                         RTP_PAYLOAD_TYPE_E enPayload, HI_U32 u32Ssrc, HI_U16 u16LastSn)
{
    RTP_HDR_S* pRtpHdr = (RTP_HDR_S*)pPackAddr;

    /* no padding, no header extension, no CSRC */
    RTP_SET_VERSION(pRtpHdr, RTP_VERSION);
    RTP_SET_PADDING(pRtpHdr, 0);
    RTP_SET_HDREXT(pRtpHdr, 0);
    RTP_SET_CSRCCNT(pRtpHdr, 0);
    RTP_SET_MARKER((RTP_HDR_S*)pRtpHdr, u32Marker);
    RTP_SET_PAYLOAD(pRtpHdr, enPayload);
    RTP_SET_SEQNUM((RTP_HDR_S*)pRtpHdr, htons(u16LastSn));
    RTP_SET_PTS((RTP_HDR_S*)pRtpHdr, htonl(u32TimeStamp));
    RTP_SET_SSRC(pRtpHdr, htonl(u32Ssrc));

    return;
}

HI_S32 RTP_RecvBufInit(HI_U32 u32Chn)
{
    HI_U32 i;
    HI_U8*   pu8BufPool = HI_NULL;
    HI_U32  u32Size = 0;

    if (HI_NULL != g_stRtpAttr[u32Chn].pstRecvBuf)
    {
        HI_ERR_RTP("RtpRevBufferPoolInit init error!\n");
        return HI_FAILURE;
    }

    g_stRtpAttr[u32Chn].pstRecvBuf = (RTP_RECV_BUF_S*)HI_MALLOC(HI_ID_USR_START, sizeof(RTP_RECV_BUF_S));

    if (HI_NULL == g_stRtpAttr[u32Chn].pstRecvBuf)
    {
        HI_ERR_RTP("RTP_RecvBufInit malloc failed.\n");
        return HI_FAILURE;
    }

    memset(g_stRtpAttr[u32Chn].pstRecvBuf, 0, sizeof(RTP_RECV_BUF_S));

    u32Size = g_stRtpAttr[u32Chn].stRtpAttr.u32RecvBufNum * g_stRtpAttr[u32Chn].stRtpAttr.u32RecvBufSize;
    pu8BufPool = (HI_U8*)HI_MALLOC(HI_ID_USR_START, u32Size);

    if (HI_NULL == pu8BufPool)
    {
        HI_ERR_RTP("RTP_RecvBufInit malloc failed.\n");
        HI_FREE(HI_ID_USR_START, g_stRtpAttr[u32Chn].pstRecvBuf);
        return HI_FAILURE;
    }

    memset(pu8BufPool, 0, u32Size);
    g_stRtpAttr[u32Chn].pstRecvBuf->pu8BufPool = pu8BufPool;

    INIT_LIST_HEAD(&g_stRtpAttr[u32Chn].pstRecvBuf->RtpEmptyList);
    INIT_LIST_HEAD(&g_stRtpAttr[u32Chn].pstRecvBuf->RtpFullList);

    for (i = 0; i < g_stRtpAttr[u32Chn].stRtpAttr.u32RecvBufNum; i++)
    {
        g_stRtpAttr[u32Chn].pstRecvBuf->stRtpBufNode[i].pBlockAddr = (HI_U8*)(pu8BufPool + i * g_stRtpAttr[u32Chn].stRtpAttr.u32RecvBufSize);
        g_stRtpAttr[u32Chn].pstRecvBuf->stRtpBufNode[i].u32BlockSize = g_stRtpAttr[u32Chn].stRtpAttr.u32RecvBufSize;
        g_stRtpAttr[u32Chn].pstRecvBuf->stRtpBufNode[i].u32SeqNumber = 0;
        INIT_LIST_HEAD(&g_stRtpAttr[u32Chn].pstRecvBuf->stRtpBufNode[i].listhead);
        list_add_tail(&g_stRtpAttr[u32Chn].pstRecvBuf->stRtpBufNode[i].listhead,
                      &g_stRtpAttr[u32Chn].pstRecvBuf->RtpEmptyList);
    }

    return HI_SUCCESS;
}

HI_VOID RTP_RecvBufDeInit(HI_U32 u32Chn)
{
    if (HI_NULL == g_stRtpAttr[u32Chn].pstRecvBuf)
    {
        HI_ERR_RTP("g_stRtpAttr[u32Chn].pstRecvBuf is NULL!\n");
        return;
    }

    if (HI_NULL != g_stRtpAttr[u32Chn].pstRecvBuf->pu8BufPool)
    {
        HI_FREE(HI_ID_USR_START, g_stRtpAttr[u32Chn].pstRecvBuf->pu8BufPool);
        g_stRtpAttr[u32Chn].pstRecvBuf->pu8BufPool = HI_NULL;
    }

    HI_FREE(HI_ID_USR_START, g_stRtpAttr[u32Chn].pstRecvBuf);
    g_stRtpAttr[u32Chn].pstRecvBuf = HI_NULL;

    return;
}

HI_S32 RTP_JudgeSeqNum(HI_U16 u16RefNum, HI_U16 u16JudgeNum)
{
    HI_S16 s16TmpNum1, s16TmpNum2;

    s16TmpNum1 = (HI_S16)u16RefNum;
    s16TmpNum2 = (HI_S16)u16JudgeNum;

    if (u16RefNum < u16JudgeNum)
    {
        return 0;
    }
    else
    {
        if ((s16TmpNum1 < 0) && (s16TmpNum2 >= 0))
        {
            return 0;
        }
        else
        {
            return u16RefNum - u16JudgeNum;
        }
    }
}

HI_S32 RTP_RecvBufQueueES(HI_U32 u32Chn, HI_U32 u32SeqNum, RTP_RECV_BUF_NODE_S* pstTmpBufNode)
{
    HI_S32 nRet;
    HI_LIST* ptr_buf;
    HI_LIST* ptr_buf_n;
    RTP_RECV_BUF_NODE_S* pstNxtBufNode;
    RTP_RECV_BUF_S* pstRecvBuf;

    CHECK_RTP_NULL_PTR(pstTmpBufNode);

    if (g_stRtpAttr[u32Chn].pstRecvBuf)
    {
        pstRecvBuf = g_stRtpAttr[u32Chn].pstRecvBuf;
    }
    else
    {
        return HI_FAILURE;
    }

    /* get a free block, copy data into it */

    /* Most cases is in order, first to determine whether this situation */
    if (list_empty(&pstRecvBuf->RtpFullList))
    {
        HI_RTP_LOCK();
        list_move_tail(&pstTmpBufNode->listhead, &pstRecvBuf->RtpFullList);
        HI_RTP_UNLOCK();
        return HI_SUCCESS;
    }

    pstNxtBufNode = list_entry(pstRecvBuf->RtpFullList.prev, RTP_RECV_BUF_NODE_S, listhead);
    nRet = RTP_JudgeSeqNum((HI_U16)pstNxtBufNode->u32SeqNumber, (HI_U16)u32SeqNum);

    if (HI_SUCCESS == nRet)
    {
        HI_RTP_LOCK();
        list_move_tail(&pstTmpBufNode->listhead, &pstRecvBuf->RtpFullList);
        HI_RTP_UNLOCK();
        return HI_SUCCESS;
    }

    /* If receive a very old, no need to rearrange */

    nRet = RTP_JudgeSeqNum((HI_U16)pstRecvBuf->u32LastOutSeq, (HI_U16)u32SeqNum);

    if (nRet > 1)
    {
        HI_WARN_RTP("RTP Can't Reorder,lost Buffer!\n");
        return HI_FAILURE;
    }

    HI_RTP_LOCK();

    list_for_each_safe (ptr_buf, ptr_buf_n, &pstRecvBuf->RtpFullList)
    {
        pstNxtBufNode = list_entry(ptr_buf, RTP_RECV_BUF_NODE_S, listhead);
        nRet = RTP_JudgeSeqNum((HI_U16)pstNxtBufNode->u32SeqNumber, (HI_U16)u32SeqNum);

        if (nRet >= (HI_S32)g_stRtpAttr[u32Chn].stRtpAttr.u32RecvBufNum)
        {
            HI_WARN_RTP("RTP Can't Reorder,lost Buffer!\n");
            HI_RTP_UNLOCK();
            return HI_FAILURE;
        }

        if (HI_SUCCESS != nRet)
        {
            list_del(&pstTmpBufNode->listhead);
            list_add(&pstTmpBufNode->listhead, pstNxtBufNode->listhead.prev);
            HI_RTP_UNLOCK();
            return HI_SUCCESS;
        }
    }
    HI_RTP_UNLOCK();

    HI_ERR_RTP("RTP Internal error!lost Buffer!\n");
    return HI_FAILURE;
}

HI_S32 RTP_RecvFrom(HI_U32 u32Chn, HI_U8* pu8RecvBuf, HI_U32 u32BlockSize, HI_U32* pu32RecvBytes)
{
    socklen_t sktLen;
    struct sockaddr_in stIpv4AttrReceived = {0};
    struct sockaddr_in6 stIpv6AttrReceived = {0};
    HI_S32 revBytes = 0;

    CHECK_RTP_NULL_PTR(pu8RecvBuf);
    CHECK_RTP_NULL_PTR(pu32RecvBytes);

    if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bIsIpv4)
    {
        sktLen = sizeof(struct sockaddr_in);
        revBytes = recvfrom(g_stRtpAttr[u32Chn].s32Socket, pu8RecvBuf, u32BlockSize, 0,
                            (struct sockaddr*)&stIpv4AttrReceived, &sktLen);
        if (revBytes <= 0)
        {
            return HI_FAILURE;
        }

        if ((0 != memcmp((const char*)(&g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv4Attr.sin_addr),
                         (const char*)&stIpv4AttrReceived.sin_addr, sizeof(struct in_addr)))
            || (stIpv4AttrReceived.sin_port != g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv4Attr.sin_port))
        {
            HI_INFO_RTP("the ip or port is not right\n");
            return HI_FAILURE;
        }
    }
    else
    {
        sktLen = sizeof(struct sockaddr_in6);
        revBytes = recvfrom(g_stRtpAttr[u32Chn].s32Socket, pu8RecvBuf, u32BlockSize, 0,
                            (struct sockaddr*)&stIpv6AttrReceived, &sktLen);
        if (revBytes <= 0)
        {
            return HI_FAILURE;
        }

        if ((0 != memcmp((const char*)(&g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv6Attr.sin6_addr),
                         (const char*)&stIpv6AttrReceived.sin6_addr, sizeof(struct in6_addr)))
            || (stIpv6AttrReceived.sin6_port != g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv6Attr.sin6_port))
        {
            HI_INFO_RTP("the ip or port is not right\n");
            return HI_FAILURE;
        }
    }

    *pu32RecvBytes = (HI_U32)revBytes;
    return HI_SUCCESS;
}

HI_S32 RTP_PraseHeadH264(HI_U8** ppu8RecvBuf, HI_U32* pu32RecvLen, HI_BOOL *bFirstFU)
{
    HI_U8* paddr = *ppu8RecvBuf;
    HI_U8  u8NalHead[4] = {0x0, 0x0, 0x0, 0x1};

    CHECK_RTP_NULL_PTR(pu32RecvLen);
    CHECK_RTP_NULL_PTR(*ppu8RecvBuf);

    /* FU-A Fragmentation unit */
    if (RTP_NAL_TYPE_FUA == (paddr[0] & 0x1f))
    {
        /* first piece */
        if (paddr[1] & 0x80)
        {
            paddr[1] &= 0x1f;
            paddr[1] |= (paddr[0] & 0xe0);
            memcpy(&paddr[-3], u8NalHead, 4);
            (*ppu8RecvBuf) -= 3;
            (*pu32RecvLen) += 3;
            *bFirstFU = HI_TRUE;
        }
        else
        {
            (*ppu8RecvBuf) += 2;
            (*pu32RecvLen) -= 2;
            *bFirstFU = HI_FALSE;
        }
    }
    else
    {
        memcpy(&paddr[-4], u8NalHead, 4);
        (*ppu8RecvBuf) -= 4;
        (*pu32RecvLen) += 4;
        *bFirstFU = HI_TRUE;
    }
    return 0;
}

HI_S32 RTP_PraseHeadH265(HI_U8** ppu8RecvBuf, HI_U32* pu32RecvLen, HI_BOOL *bFirstFU)
{
    HI_U8* paddr = *ppu8RecvBuf;
    HI_U8 u8NALType;
    HI_U8  u8NalHead[4] = {0x0, 0x0, 0x0, 0x1};

    CHECK_RTP_NULL_PTR(pu32RecvLen);
    CHECK_RTP_NULL_PTR(*ppu8RecvBuf);

    /* FU-A Fragmentation unit */
    if (49 == ((paddr[0] & 0x7e) >> 1))
    {
        /* first piece */
        if (paddr[2] & 0x80)
        {
            u8NALType = paddr[2] & 0x3f;
            paddr[2] = paddr[1];
            paddr[1] = (paddr[0] & 0x81) | ((u8NALType << 1) & 0x7e);
            memcpy(&paddr[-3], u8NalHead, 4);
            (*ppu8RecvBuf) -= 3;
            (*pu32RecvLen) += 3;
            *bFirstFU = HI_TRUE;
        }
        else
        {
            (*ppu8RecvBuf) += 3;
            (*pu32RecvLen) -= 3;
            *bFirstFU = HI_FALSE;
        }
    }
    else
    {
        memcpy(&paddr[-4], u8NalHead, 4);
        (*ppu8RecvBuf) -= 4;
        (*pu32RecvLen) += 4;
        *bFirstFU = HI_TRUE;
    }
    return 0;
}


HI_S32 RTP_RecvBufPrase(HI_U32 u32Chn, RTP_RECV_BUF_NODE_S*  pstTmpBufNode,
                        HI_U8* pu8RecvBuf, HI_U32 u32RecvBytes, HI_U16* pu16LastSeqNum)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U8*  pu8StartAddr = pu8RecvBuf;
    HI_U16 u16LastSeqNum = *pu16LastSeqNum;
    HI_U32 FUA_BuffLen   = 0;
    RTP_HDR_S* pPackAddr = HI_NULL;
    HI_U16 u16SeqNum;
    HI_U32 u32PtsMs;
    HI_BOOL bFirstFU = HI_FALSE;

    pPackAddr = (RTP_HDR_S*)pu8RecvBuf;
    u32PtsMs  = RTP_PTS_90MS_TO_MS(ntohl(pPackAddr->u32PtsMs));
    u16SeqNum = ntohs(pPackAddr->u32SeqNum);

    if ((u16SeqNum != (u16LastSeqNum + 1)) && g_stRtpAttr[u32Chn].bStartRev)
    {
        if ((0 == u16SeqNum) && (0xFFFF == u16LastSeqNum))
        {
            HI_INFO_RTP("round rtp: CurSeqNo:%u, LastSeqNo=%u \n", u16SeqNum, u16LastSeqNum);
        }
        else
        {
            HI_INFO_RTP("Lost rtp: CurSeqNo:%u, LastSeqNo=%u \n", u16SeqNum, u16LastSeqNum);
        }
    }

    *pu16LastSeqNum = u16SeqNum;
    g_stRtpAttr[u32Chn].bStartRev = HI_TRUE;
    g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.usSequenceNumber = u16SeqNum;
    g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.ulTimestamp = ntohl(pPackAddr->u32PtsMs);
    g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.ulSSRC = ntohl(pPackAddr->u32Ssrc);
    g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.ucCSRCcount = 0;

    FUA_BuffLen = u32RecvBytes - RTP_HDR_LEN;
    pu8StartAddr += sizeof(RTP_HDR_S);
    if((RTP_PAYLOAD_TYPE_E)g_stRtpAttr[u32Chn].stRtpAttr.u32PayLoadType == RTP_PT_H265)
    {
        RTP_PraseHeadH265(&pu8StartAddr, &FUA_BuffLen, &bFirstFU);
    }
    else
    {
        RTP_PraseHeadH264(&pu8StartAddr, &FUA_BuffLen, &bFirstFU);
    }
    pstTmpBufNode->bFirstFU = bFirstFU;
    pstTmpBufNode->u32Pts = u32PtsMs;
    pstTmpBufNode->u32BlockSize = FUA_BuffLen;
    pstTmpBufNode->u32Offset = pu8StartAddr - pstTmpBufNode->pBlockAddr;
    if (pstTmpBufNode->u32BlockSize)
    {
        s32Ret = RTP_RecvBufQueueES(u32Chn, u16SeqNum, pstTmpBufNode);
        if (HI_SUCCESS != s32Ret)
        {
            HI_WARN_RTP("RTP_RecvBufQueueES failed\n");
            return HI_FAILURE;
        }
        else
        {
            return HI_SUCCESS;
        }
    }

    return HI_FAILURE;
}

HI_VOID* RTP_ScheduleRecv(HI_VOID* args)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Chn = (HI_U32)(HI_SIZE_T)args;
    HI_U32 u32RecvBytes = 0;
    HI_U32 u32BlockSize = 0;
    RTP_RECV_BUF_S* pstRecvBuf = HI_NULL;
    RTP_RECV_BUF_NODE_S*  pstTmpBufNode = HI_NULL;
    HI_U8* u8RecvBuf = HI_NULL;
    HI_U32 u32PtsMsPrev = 0;
    VP_RTCP_SESSION* pstSession = HI_NULL;
    HI_U16 u16LastSeqNum = 0xFFFF;

    if (u32Chn >= RTP_MAX_SESSION_NUM || g_stRtpAttr[u32Chn].pstRecvBuf == HI_NULL)
    {
        return HI_NULL;
    }

    pstRecvBuf = g_stRtpAttr[u32Chn].pstRecvBuf;
    while (HI_FALSE == g_stRtpAttr[u32Chn].bRecvStop)
    {
        /* get a free block, copy data into it */
        if (((HI_NULL == u8RecvBuf)) && (!list_empty(&pstRecvBuf->RtpEmptyList)))
        {
            pstTmpBufNode = list_entry(pstRecvBuf->RtpEmptyList.next, RTP_RECV_BUF_NODE_S, listhead);
            if (HI_NULL != pstTmpBufNode)
            {
                u8RecvBuf = pstTmpBufNode->pBlockAddr;
                u32BlockSize = pstTmpBufNode->u32BlockSize;
            }
        }

        if (u8RecvBuf == HI_NULL || pstTmpBufNode == HI_NULL)
        {
            vp_usleep(1000);
            continue;
        }

        s32Ret = RTP_RecvFrom(u32Chn, u8RecvBuf, u32BlockSize, &u32RecvBytes);
        if (HI_SUCCESS != s32Ret)
        {
            vp_usleep(10 * 1000);
            continue;
        }

        if (u32RecvBytes <= RTP_HDR_LEN)
        {
            return HI_NULL;
        }

        s32Ret = RTP_RecvBufPrase(u32Chn, pstTmpBufNode, u8RecvBuf, u32RecvBytes, &u16LastSeqNum);
        if (HI_SUCCESS == s32Ret)
        {
            u8RecvBuf = HI_NULL;
        }

        pstSession = (VP_RTCP_SESSION*)g_stRtpAttr[u32Chn].stRtcp.hRTCP;
        if ((0 == (g_stRtpAttr[u32Chn].stReport.u32RecvPacketNum % HI_RTP_STAT_DELAY_INTERVAL))\
            && (u32PtsMsPrev != g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.ulTimestamp))
        {
            u32PtsMsPrev = g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.ulTimestamp;
            VP_RTCP_RecvCalculateDelayAndJitter(pstSession, g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.ulSSRC, u32PtsMsPrev);
        }

        g_stRtpAttr[u32Chn].stReport.u32RecvPacketNum++;
        g_stRtpAttr[u32Chn].stReport.u32RecvBytes += u32RecvBytes;

        if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bEnableRtcp)
        {
            pstSession->stRecvInfo.ulTimestamp = g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.ulTimestamp;
            pstSession->stRecvInfo.ulSequence = g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.usSequenceNumber;
            pstSession->stRecvInfo.ulPackets += 1;
            pstSession->stRecvInfo.ulBytes += u32RecvBytes;//g_stRtpAttr[u32Chn].stRtcp.stRtpInfo.ulPaloadLength;
            VP_RTCP_ParseRtpUpdateSource(pstSession, u32RecvBytes, &g_stRtpAttr[u32Chn].stRtcp.stRtpInfo);
        }
    }

    return HI_NULL;
}

static HI_S32 RTP_Recv_Enable(HI_U32 u32Chn)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i = u32Chn;

    s32Ret = RTP_RecvBufInit(i);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    g_stRtpAttr[i].bRecvStop = HI_FALSE;
    if (pthread_create(&g_stRtpAttr[i].threadRecv, HI_NULL, RTP_ScheduleRecv, (HI_VOID*)(HI_SIZE_T)i))
    {
        HI_ERR_RTP("pthread_create RTP_ScheduleRecv failed\n");
        g_stRtpAttr[i].bRecvStop = HI_TRUE;
        RTP_RecvBufDeInit(i);
        return HI_ERR_RTP_CREATE_ERR;
    }

    return HI_SUCCESS;
}

static HI_VOID RTP_Recv_DisEnable(HI_U32 u32Chn)
{
    HI_U32 i = u32Chn;

    if (HI_FALSE == g_stRtpAttr[i].bRecvStop)
    {
        g_stRtpAttr[i].bRecvStop = HI_TRUE;
        if (pthread_join(g_stRtpAttr[i].threadRecv, HI_NULL))
        {
            HI_ERR_RTP("pthread_join failed, line = %d\n", __LINE__);
        }
    }

    RTP_RecvBufDeInit(i);
    g_stRtpAttr[i].bStartRev = HI_FALSE;

    return;
}

HI_S32 RTP_Init(HI_VOID)
{
    HI_U32 i;

    for (i = 0; i < RTP_MAX_SESSION_NUM; i++)
    {
        g_stRtpAttr[i].hRTP = HI_INVALID_HANDLE;
    }

    g_bRtpInited = HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 RTP_DeInit(HI_VOID)
{
    g_bRtpInited = HI_FALSE;
    return HI_SUCCESS;
}

HI_S32 RTP_GetDefaultAttr(RTP_ATTR_S* pstRtpAttr)
{
    CHECK_RTP_NULL_PTR(pstRtpAttr);
    pstRtpAttr->bEnableRtcp = HI_TRUE;
    pstRtpAttr->bIsIpv4   = HI_TRUE;
    pstRtpAttr->enCtrlMod = RTP_SEND_AND_RECV;
    memset(&pstRtpAttr->stLocalNet, 0, sizeof(struct sockaddr_in));
    pstRtpAttr->stLocalNet.stIpv4Attr.sin_family = AF_INET;
    pstRtpAttr->stLocalNet.stIpv4Attr.sin_port = htons(16384);
    memset(&pstRtpAttr->stRemoteNet, 0, sizeof(struct sockaddr_in));
    pstRtpAttr->stRemoteNet.stIpv4Attr.sin_family = AF_INET;
    pstRtpAttr->stRemoteNet.stIpv4Attr.sin_port = htons(16384);
    pstRtpAttr->u32PayLoadType = RTP_PT_H264; // todo, add if-else
    pstRtpAttr->u32SplitSize   = RTP_DEFAULT_SPLIT_SIZE;
    pstRtpAttr->u32RecvBufSize = RTP_MAX_UDP_LEN;
    pstRtpAttr->u32RecvBufNum  = RTP_DEFAULT_REORDER_BUF_NUM;
    pstRtpAttr->u32SortDepth = RTP_DEFAULT_SORT_DEPTH;

    return HI_SUCCESS;
}

HI_S32 RTP_Create(const RTP_ATTR_S* pstRtpAttr, HI_HANDLE* phRTP)
{
    HI_U32 i;
    HI_S32 s32Ret = HI_FAILURE;

    CHECK_RTP_NULL_PTR(pstRtpAttr);
    CHECK_RTP_NULL_PTR(phRTP);
    CHECK_RTP_INIT;

    s32Ret = RTP_CheckUserConfig(pstRtpAttr);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    /* get a valid handle to create session */
    for (i = 0; i < RTP_MAX_SESSION_NUM; i++)
    {
        if (g_stRtpAttr[i].hRTP == HI_INVALID_HANDLE)
        {
            break;
        }
    }

    if (RTP_MAX_SESSION_NUM == i)
    {
        HI_ERR_RTP("RTP_Create failed\n");
        return HI_ERR_RTP_CREATE_ERR;
    }

    memset(&g_stRtpAttr[i], 0, sizeof(RTP_PRIV_ATTR_S));
    memcpy(&g_stRtpAttr[i].stRtpAttr, pstRtpAttr, sizeof(RTP_ATTR_S));
    /* alloc recv buffer */
    if ((RTP_ONLY_RECV == pstRtpAttr->enCtrlMod) || (RTP_SEND_AND_RECV == pstRtpAttr->enCtrlMod))
    {
        s32Ret = RTP_Recv_Enable(i);

        if (HI_SUCCESS != s32Ret)
        {
            memset(&g_stRtpAttr[i].stRtpAttr, 0, sizeof(RTP_ATTR_S));
            return s32Ret;
        }
    }

    /* create RTP socket */
    if (HI_TRUE == pstRtpAttr->bIsIpv4)
    {
        g_stRtpAttr[i].s32Socket = socket(AF_INET, SOCK_DGRAM, 0);
    }
    else
    {
        g_stRtpAttr[i].s32Socket = socket(AF_INET6, SOCK_DGRAM, 0);
    }

    if (g_stRtpAttr[i].s32Socket == -1)
    {
        HI_ERR_RTP("create socket failed %s\n", strerror(errno));
        goto ERR0;
    }

#if 1
    /*set recvfrom timeout to solve this sence, that User A and User B call each other with send and receive.
        If User A shutdown, then User B do not recevice, but User B send data continuelly, result in the programe of User B
        hanging up. */
    struct timeval tv;
    tv.tv_sec = SOCKET_RCVTIMEO / 1000 ;
    tv.tv_usec = (SOCKET_RCVTIMEO % 1000) * 1000;
    if (setsockopt(g_stRtpAttr[i].s32Socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    {
        HI_ERR_RTP("socket option SO_RCVTIMEO not support %s\n", strerror(errno));
    }

#endif

    /* bind socket to local IP and port */
    if (HI_TRUE == pstRtpAttr->bIsIpv4)
    {
        s32Ret = bind(g_stRtpAttr[i].s32Socket, (struct sockaddr*)&pstRtpAttr->stLocalNet.stIpv4Attr,
                      sizeof(struct sockaddr));
    }
    else
    {
        s32Ret = bind(g_stRtpAttr[i].s32Socket, (struct sockaddr*)&pstRtpAttr->stLocalNet.stIpv6Attr,
                      sizeof(struct sockaddr_in6));
    }
    if (s32Ret == -1)
    {
        HI_ERR_RTP("bind socket failed %s\n", strerror(errno) );
        goto ERR1;
    }

    /* generate handle value */
    *phRTP = (HI_ID_RTP << 24) + i;
    g_stRtpAttr[i].hRTP = *phRTP;
    g_stRtpAttr[i].bStartRev = HI_FALSE;
    /* enable RTCP session */
    if (HI_TRUE == pstRtpAttr->bEnableRtcp)
    {
        s32Ret = RTCP_Create(i);

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_RTP("RTCP_Create failed\n");
            goto ERR1;
        }
    }

    return HI_SUCCESS;

ERR1:
    shutdown(g_stRtpAttr[i].s32Socket, 2);
    close(g_stRtpAttr[i].s32Socket);
ERR0:
    if ((RTP_ONLY_RECV == pstRtpAttr->enCtrlMod) || (RTP_SEND_AND_RECV == pstRtpAttr->enCtrlMod))
    {
        RTP_Recv_DisEnable(i);
    }
    memset(&g_stRtpAttr[i].stRtpAttr, 0, sizeof(RTP_ATTR_S));
    return HI_ERR_RTP_NET_ERR;
}

HI_S32 RTP_Destroy(HI_HANDLE hRTP)
{
    HI_U32 i;
    HI_S32 s32Ret = HI_FAILURE;

    CHECK_RTP_HANDLE(hRTP);
    CHECK_RTP_INIT;

    s32Ret = RTP_FindValidChannel(&hRTP, &i);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }
    if (HI_TRUE == g_stRtpAttr[i].stRtpAttr.bEnableRtcp)
    {
        RTCP_Destroy(i);
    }

    shutdown(g_stRtpAttr[i].s32Socket, 2);
    close(g_stRtpAttr[i].s32Socket);
    if ((RTP_ONLY_RECV == g_stRtpAttr[i].stRtpAttr.enCtrlMod)
        || (RTP_SEND_AND_RECV == g_stRtpAttr[i].stRtpAttr.enCtrlMod))
    {
        RTP_Recv_DisEnable(i);
    }

    memset(&g_stRtpAttr[i], 0, sizeof(RTP_PRIV_ATTR_S));
    g_stRtpAttr[i].hRTP = HI_INVALID_HANDLE;

    return s32Ret;
}

HI_S32 RTP_GetAttr(HI_HANDLE hRTP, RTP_ATTR_S* pstRtpAttr)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i;

    CHECK_RTP_INIT;
    CHECK_RTP_HANDLE(hRTP);
    CHECK_RTP_NULL_PTR(pstRtpAttr);

    s32Ret = RTP_FindValidChannel(&hRTP, &i);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    memcpy(pstRtpAttr, &g_stRtpAttr[i].stRtpAttr, sizeof(RTP_ATTR_S));
    return HI_SUCCESS;
}

HI_S32 RTP_SetAttr(HI_HANDLE hRTP, const RTP_ATTR_S* pstRtpAttr)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i;

    CHECK_RTP_INIT;
    CHECK_RTP_HANDLE(hRTP);
    CHECK_RTP_NULL_PTR(pstRtpAttr);

    s32Ret = RTP_FindValidChannel(&hRTP, &i);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = RTP_CheckUserConfig(pstRtpAttr);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    //ctrl mod swith
    if (g_stRtpAttr[i].stRtpAttr.enCtrlMod != pstRtpAttr->enCtrlMod)
    {
        if (RTP_ONLY_SEND == pstRtpAttr->enCtrlMod)
        {
            RTP_Recv_DisEnable(i);
        }
        else if (RTP_ONLY_SEND == g_stRtpAttr[i].stRtpAttr.enCtrlMod)
        {
            s32Ret = RTP_Recv_Enable(i);
            if (HI_SUCCESS != s32Ret)
            {
                return s32Ret;
            }
        }

        g_stRtpAttr[i].stRtpAttr.enCtrlMod = pstRtpAttr->enCtrlMod;
    }

    //compare
    if (0 != memcmp((const char*)(&g_stRtpAttr[i].stRtpAttr), (const char*)pstRtpAttr, sizeof(RTP_ATTR_S)))
    {
        HI_ERR_RTP("do not support set this attr now\n");
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    return HI_SUCCESS;
}

/*
     FU indicator :
      +---------------+
       |0|1|2|3|4|5|6|7|
      +-+-+-+-+-+-+-+
      |F|NRI|  Type   |
      +---------------+

      FU header:
      +---------------+
      |0|1|2|3|4|5|6|7|
     +-+-+-+-+-+-+-+
      |S|E|R|  Type   |
      +---------------+
*/
static HI_S32 RTP_PackageHeader_H264(HI_U8* pHeader,const HI_U8 *pMessage,HI_BOOL bstart,HI_BOOL bend)
{
    HI_U8                               u8NALType;
    HI_U8                       u8start = 0;
    HI_U8                       u8end = 0;
    CHECK_RTP_NULL_PTR(pHeader);
    CHECK_RTP_NULL_PTR(pMessage);
    TRANS_CHK_RETURN_PRINT((HI_TRUE == bstart && HI_TRUE == bend), HI_FAILURE, "start & end can't be 1 at same time\n");

    if(*pMessage != 0 ||*(pMessage+1) != 0 || *(pMessage + 2) != 0 ||  *(pMessage + 3) != 1)
    {
        HI_ERR_RTP("[%s,%d]this package is not have NALU\n",__FUNCTION__,__LINE__);
        HI_ERR_RTP("flag : %x %x %x %x\n",*pMessage,*(pMessage+1),*(pMessage + 2),*(pMessage + 3));
        return HI_FAILURE;
    }

    if(HI_TRUE == bstart)
    {
        u8start = 1;
    }else
    {
        u8start = 0;
    }
    if(HI_TRUE == bend)
    {
        u8end = 1;
    }else
    {
        u8end = 0;
    }

    u8NALType = *(pMessage + 4) & 0x1F;
    *pHeader = 0x1c | (*(pMessage + 4) & 0xe0);
    *(pHeader + 1) = 0;
    *(pHeader + 1) = ((HI_U8)(u8start << 7)) | ((HI_U8)(u8end << 6)) | u8NALType;
    return HI_SUCCESS;
}


/*
    create the HEVC payload header and transmit the buffer as fragmentation units (FU)

    0                   1
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |F|   Type    |  LayerId  | TID |
   +-------------+-----------------+
     F       = 0
     Type    = 49 (fragmentation unit (FU))
     LayerId = 0
     TID     = 1


     create the FU header

     0 1 2 3 4 5 6 7
    +-+-+-+-+-+-+-+-+
     |S|E|  FuType   |
    +---------------+

       S       = variable
       E       = variable
       FuType  = NAL unit type


*/
static HI_S32 RTP_PackageHeader_H265(HI_U8* pHeader,const HI_U8 *pMessage,HI_BOOL bstart,HI_BOOL bend)
{
    HI_U8                       u8NALType;
    HI_U8                       u8start = 0;
    HI_U8                       u8end = 0;

    CHECK_RTP_NULL_PTR(pHeader);
    CHECK_RTP_NULL_PTR(pMessage);
    TRANS_CHK_RETURN_PRINT((HI_TRUE == bstart && HI_TRUE == bend), HI_FAILURE, "start & end can't be 1 at same time\n");

    /*Guaranteed is the start code of a slice*/
    if(*pMessage != 0 ||*(pMessage+1) != 0 || *(pMessage + 2) != 0 ||  *(pMessage + 3) != 1)
    {
        HI_ERR_RTP("[%s,%d]this package is not have NALU\n",__FUNCTION__,__LINE__);
        HI_ERR_RTP("flag : %x %x %x %x\n",*pMessage,*(pMessage+1),*(pMessage + 2),*(pMessage + 3));
        return HI_FAILURE;
    }

    if(HI_TRUE == bstart)
    {
        u8start = 1;
    }else
    {
        u8start = 0;
    }
    if(HI_TRUE == bend)
    {
        u8end = 1;
    }else
    {
        u8end = 0;
    }

    /*get the type of slice*/
    u8NALType = (*(pMessage + 4) >> 1)& 0x3F;

    /*set the FU type is 49 and structure the FU payload header*/
    *pHeader = (*(pMessage + 4) &0x81) | (49<<1);
    *(pHeader+1) =*(pMessage + 5) ;

    /*structure the FU header*/
    *(pHeader + 2) = ((HI_U8)(u8start << 7)) | ((HI_U8)(u8end << 6)) | u8NALType;
    return HI_SUCCESS;
}


HI_S32 RTP_UpdateRTCP(HI_U32 u32Chn, HI_U32 u3SndLen, HI_U32 u32PtsMs)
{
    VP_RTCP_SESSION* pstSession = HI_NULL;

    CHECK_RTP_INIT;
    TRANS_CHK_RETURN_NO_PRINT((RTP_MAX_SESSION_NUM <= u32Chn), HI_FAILURE);

    g_stRtpAttr[u32Chn].u32SeqNum++;
    g_stRtpAttr[u32Chn].stReport.u32SendPackets++;
    g_stRtpAttr[u32Chn].stReport.u32SendBytes += u3SndLen;

    if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bEnableRtcp)
    {
        pstSession = (VP_RTCP_SESSION*)g_stRtpAttr[u32Chn].stRtcp.hRTCP;
        pstSession->LOCAL->ulRTPTimestamp = u32PtsMs;
        pstSession->LOCAL->ulRTPSequence = g_stRtpAttr[u32Chn].u32SeqNum;
        /* may be used as sender information when send SR packet */
        pstSession->LOCAL->ulRTPPackets++;
        /* may be used as sender information when send SR packet */
        pstSession->LOCAL->ulRTPBytes += u3SndLen;
        pstSession->LOCAL->ulRTPLastPackTime = u32PtsMs;
        pstSession->ulSenders = 1;
        pstSession->LOCAL->bIsSender   = HI_TRUE;
        pstSession->LOCAL->bRTPHasSent = HI_TRUE;
        pstSession->stRtcpStatisticInfo.uiSendPacketNum = pstSession->LOCAL->ulRTPPackets;
        pstSession->stRtcpStatisticInfo.uiSendBytes = pstSession->LOCAL->ulRTPBytes;

    }
    return HI_SUCCESS;
}

HI_S32 RTP_SendMsg(HI_U32 u32Chn, HI_U8* pu8SendAddr, HI_U32 u32SendLen, HI_U32 u32PtsMs)
{
    HI_S32 s32Ret  = HI_FAILURE;

    CHECK_RTP_INIT;
    CHECK_RTP_NULL_PTR(pu8SendAddr);
    TRANS_CHK_RETURN_NO_PRINT((RTP_MAX_SESSION_NUM <= u32Chn), HI_FAILURE);

    /* send packets to remote IP & port */
    if (HI_TRUE == g_stRtpAttr[u32Chn].stRtpAttr.bIsIpv4)
    {
        s32Ret = sendto(g_stRtpAttr[u32Chn].s32Socket, pu8SendAddr, u32SendLen, 0,
                        (struct sockaddr*)&g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv4Attr,
                        sizeof(struct sockaddr_in));
    }
    else
    {
        s32Ret = sendto(g_stRtpAttr[u32Chn].s32Socket, pu8SendAddr, u32SendLen, 0,
                        (struct sockaddr*)&g_stRtpAttr[u32Chn].stRtpAttr.stRemoteNet.stIpv6Attr,
                        sizeof(struct sockaddr_in6));
    }
    if (s32Ret == -1)
    {
        HI_ERR_RTP("send packets failed. %s\n", strerror(errno));
        return HI_ERR_RTP_NET_ERR;
    }

    if ((HI_U32)s32Ret != u32SendLen)
    {
        HI_ERR_RTP("send packets failed, send bytes = %d(%d)\n", s32Ret, u32SendLen);
        return HI_ERR_RTP_NET_ERR;
    }
    RTP_UpdateRTCP(u32Chn, u32SendLen, u32PtsMs);
    return HI_SUCCESS;
}

static HI_S32 HI_RTP_VideoStream_H264(HI_U32 uChn, HI_U8* pu8BufAddr, HI_U32 u32Len, HI_U32 u32PtsMs)
{
    HI_U32         u32PackageLen =0;
    HI_U8          u8Marker = 0;
    HI_U8*         pRtpHdr = pu8BufAddr;
    HI_S32         s32Sendlen = 0;

    HI_U32         u32RTPSendLen = 0;
    HI_U8*         pRTPSendMsg = NULL;
    HI_U32        pRTPMsgLen = u32Len;
    HI_U8         u8RtpHdr[RTP_HDR_LEN] = {0};
    HI_U8         u8H264Head[H264_HEAD_LEN] = {0};
    HI_U8         u8H264FuHdr[H264_FU_HEAD_LEN] = {0};
    HI_S32        s32Ret;
    HI_BOOL       bStartFlag;
    HI_BOOL       bEndFlag;
    HI_U32        u32TimeStamp = RTP_PTS_MS_TO_90MS(u32PtsMs);
    VP_RTCP_SESSION* pstSession = HI_NULL;

    CHECK_RTP_INIT;
    CHECK_RTP_NULL_PTR(pu8BufAddr);
    TRANS_CHK_RETURN_NO_PRINT((RTP_MAX_SESSION_NUM <= uChn), HI_FAILURE);

    pstSession = (VP_RTCP_SESSION*)g_stRtpAttr[uChn].stRtcp.hRTCP;
    if(pRTPMsgLen <= g_stRtpAttr[uChn].stRtpAttr.u32SplitSize)
    {
        pRtpHdr += RTP_NAL_HEADER_SIZE;
        pRTPMsgLen -= RTP_NAL_HEADER_SIZE;

        RTP_HeaderPacket(u8RtpHdr, u32TimeStamp, 0, (RTP_PAYLOAD_TYPE_E)g_stRtpAttr[uChn].stRtpAttr.u32PayLoadType, \
                     pstSession->LOCAL->ulSSRC, g_stRtpAttr[uChn].u32SeqNum);
        memcpy(pRtpHdr - RTP_HDR_LEN, u8RtpHdr, RTP_HDR_LEN);
        u32RTPSendLen = pRTPMsgLen + RTP_HDR_LEN;
        pRTPSendMsg = pRtpHdr - RTP_HDR_LEN;
        s32Ret = RTP_SendMsg(uChn, pRTPSendMsg, u32RTPSendLen, u32TimeStamp);
        TRANS_CHK_RETURN_PRINT((s32Ret < 0), HI_FAILURE, "RTP video send error\n");
        return HI_SUCCESS;
    }

    memcpy(u8H264Head, pRtpHdr, H264_HEAD_LEN);
    while(u32PackageLen < pRTPMsgLen)
    {
        if(pRTPMsgLen - u32PackageLen  <= g_stRtpAttr[uChn].stRtpAttr.u32SplitSize)
        {
            u8Marker = 1;
            s32Sendlen = (HI_S32)pRTPMsgLen - (HI_S32)u32PackageLen;
        }
        else
        {
            s32Sendlen =  g_stRtpAttr[uChn].stRtpAttr.u32SplitSize;
            u8Marker = 0;
        }
        u32RTPSendLen = (HI_U32)s32Sendlen + RTP_HDR_LEN + H264_FU_HEAD_LEN;
        if(u32PackageLen == 0)    //the first package
        {
            bStartFlag = HI_TRUE;
            bEndFlag = HI_FALSE;
            u32PackageLen += H264_HEAD_LEN;
            pRtpHdr += H264_HEAD_LEN;
        }
        else if((g_stRtpAttr[uChn].stRtpAttr.u32SplitSize == (HI_U32)s32Sendlen) &&
                    (u32PackageLen + (HI_U32)s32Sendlen != pRTPMsgLen))  // in the middle packages
        {
            bEndFlag = HI_FALSE;
            bStartFlag = HI_FALSE;
        }
        else //the last package
        {
            bEndFlag = HI_TRUE;
            bStartFlag = HI_FALSE;
        }
        RTP_HeaderPacket(u8RtpHdr, u32TimeStamp, u8Marker, (RTP_PAYLOAD_TYPE_E)g_stRtpAttr[uChn].stRtpAttr.u32PayLoadType, \
                     pstSession->LOCAL->ulSSRC, g_stRtpAttr[uChn].u32SeqNum);

        s32Ret = RTP_PackageHeader_H264(u8H264FuHdr,u8H264Head, bStartFlag, bEndFlag);
        TRANS_CHK_RETURN_NO_PRINT((HI_SUCCESS != s32Ret), HI_FAILURE);

        memcpy(pRtpHdr - H264_FU_HEAD_LEN - RTP_HDR_LEN, u8RtpHdr, RTP_HDR_LEN);
        memcpy(pRtpHdr - H264_FU_HEAD_LEN, u8H264FuHdr, H264_FU_HEAD_LEN);

        pRTPSendMsg = pRtpHdr - H264_FU_HEAD_LEN - RTP_HDR_LEN;
        s32Ret = RTP_SendMsg(uChn,pRTPSendMsg, u32RTPSendLen, u32TimeStamp);
        TRANS_CHK_RETURN_PRINT((s32Ret < 0), HI_FAILURE, "RTP video send error\n");

        pRtpHdr +=  s32Sendlen;
        u32PackageLen += (HI_U32)s32Sendlen;
    }
    return HI_SUCCESS;
}


/*
 *     Reference documentation : RFC 7798
 *     url:https://datatracker.ietf.org/doc/rfc7798/?include_text=1
 */
static HI_S32 HI_RTP_VideoStream_H265(HI_U32 uChn, HI_U8* pu8BufAddr, HI_U32 u32Len, HI_U32 u32PtsMs)
{
    HI_U32         u32PackageLen =0;
    HI_U8          u8Marker = 0;
    HI_U8*         pRtpHdr = pu8BufAddr;
    HI_S32         s32Sendlen = 0;

    HI_U32         u32RTPSendLen = 0;
    HI_U8*         pRTPSendMsg = NULL;
    HI_U32        pRTPMsgLen = u32Len;
    HI_U8         u8RtpHdr[RTP_HDR_LEN] = {0};
    HI_U8         u8H265Head[H265_HEAD_LEN] = {0};
    HI_U8         u8H265FuHdr[H265_FU_HEAD_LEN] = {0};
    HI_S32        s32Ret;
    HI_BOOL       bStartFlag;
    HI_BOOL       bEndFlag;
    HI_U32        u32TimeStamp = RTP_PTS_MS_TO_90MS(u32PtsMs);
    VP_RTCP_SESSION* pstSession = HI_NULL;

    CHECK_RTP_INIT;
    CHECK_RTP_NULL_PTR(pu8BufAddr);
    TRANS_CHK_RETURN_NO_PRINT((RTP_MAX_SESSION_NUM <= uChn), HI_FAILURE);

    pstSession = (VP_RTCP_SESSION*)g_stRtpAttr[uChn].stRtcp.hRTCP;
    if(pRTPMsgLen <= g_stRtpAttr[uChn].stRtpAttr.u32SplitSize)
    {
        pRtpHdr += RTP_NAL_HEADER_SIZE;
        pRTPMsgLen -= RTP_NAL_HEADER_SIZE;

        RTP_HeaderPacket(u8RtpHdr, u32TimeStamp, 0, (RTP_PAYLOAD_TYPE_E)g_stRtpAttr[uChn].stRtpAttr.u32PayLoadType, \
                     pstSession->LOCAL->ulSSRC, g_stRtpAttr[uChn].u32SeqNum);
        memcpy(pRtpHdr - RTP_HDR_LEN, u8RtpHdr, RTP_HDR_LEN);
        u32RTPSendLen = pRTPMsgLen + RTP_HDR_LEN;
        pRTPSendMsg = pRtpHdr - RTP_HDR_LEN;
        s32Ret = RTP_SendMsg(uChn, pRTPSendMsg, u32RTPSendLen, u32TimeStamp);
        TRANS_CHK_RETURN_PRINT((s32Ret < 0), HI_FAILURE, "RTP video send error\n");
        return HI_SUCCESS;
    }

    memcpy(u8H265Head, pRtpHdr, H265_HEAD_LEN);
    while(u32PackageLen < pRTPMsgLen)
    {
        if(pRTPMsgLen - u32PackageLen  <= g_stRtpAttr[uChn].stRtpAttr.u32SplitSize)
        {
            u8Marker = 1;
            s32Sendlen = (HI_S32)pRTPMsgLen - (HI_S32)u32PackageLen;
        }
        else
        {
            s32Sendlen =  g_stRtpAttr[uChn].stRtpAttr.u32SplitSize;
            u8Marker = 0;
        }
        u32RTPSendLen = (HI_U32)s32Sendlen + RTP_HDR_LEN + H265_FU_HEAD_LEN;
        if(u32PackageLen == 0)    //the first package
        {
            bStartFlag = HI_TRUE;
            bEndFlag = HI_FALSE;
            u32PackageLen += H265_HEAD_LEN;
            pRtpHdr += H265_HEAD_LEN;
        }
        else if(g_stRtpAttr[uChn].stRtpAttr.u32SplitSize == (HI_U32)s32Sendlen)  // in the middle packages
        {
            bEndFlag = HI_FALSE;
            bStartFlag = HI_FALSE;
        }
        else //the last package
        {
            bEndFlag = HI_TRUE;
            bStartFlag = HI_FALSE;
        }
        RTP_HeaderPacket(u8RtpHdr, u32TimeStamp, u8Marker, (RTP_PAYLOAD_TYPE_E)g_stRtpAttr[uChn].stRtpAttr.u32PayLoadType, \
                     pstSession->LOCAL->ulSSRC, g_stRtpAttr[uChn].u32SeqNum);

        s32Ret = RTP_PackageHeader_H265(u8H265FuHdr, u8H265Head, bStartFlag, bEndFlag);
        TRANS_CHK_RETURN_NO_PRINT((HI_SUCCESS != s32Ret), HI_FAILURE);

        memcpy(pRtpHdr - H265_FU_HEAD_LEN - RTP_HDR_LEN, u8RtpHdr, RTP_HDR_LEN);
        memcpy(pRtpHdr - H265_FU_HEAD_LEN, u8H265FuHdr, H265_FU_HEAD_LEN);

        pRTPSendMsg = pRtpHdr - H265_FU_HEAD_LEN - RTP_HDR_LEN;
        s32Ret = RTP_SendMsg(uChn, pRTPSendMsg, u32RTPSendLen, u32TimeStamp);
        TRANS_CHK_RETURN_PRINT((s32Ret < 0), HI_FAILURE, "RTP video send error\n");

        pRtpHdr +=  s32Sendlen;
        u32PackageLen += (HI_U32)s32Sendlen;
    }
    return HI_SUCCESS;
}


HI_S32 RTP_Send(HI_HANDLE hRTP, HI_U8* pu8BufAddr, HI_U32 u32Len, HI_U32 u32PtsMs)
{
    HI_U32 i;
    HI_S32 s32Ret  = HI_FAILURE;

    CHECK_RTP_INIT;
    CHECK_RTP_NULL_PTR(pu8BufAddr);
    CHECK_RTP_HANDLE(hRTP);

    s32Ret = RTP_FindValidChannel(&hRTP, &i);
    TRANS_CHK_RETURN_NO_PRINT((HI_SUCCESS != s32Ret), s32Ret);

    if((RTP_PAYLOAD_TYPE_E)g_stRtpAttr[i].stRtpAttr.u32PayLoadType == RTP_PT_H265)
    {
        s32Ret = HI_RTP_VideoStream_H265(i, pu8BufAddr, u32Len, u32PtsMs);
    }
    else
    {
        s32Ret = HI_RTP_VideoStream_H264(i, pu8BufAddr, u32Len, u32PtsMs);
    }
    TRANS_CHK_RETURN_NO_PRINT((HI_SUCCESS != s32Ret), s32Ret);

    if (0 == (g_stRtpAttr[i].u32SeqNum % HI_RTP_STAT_DELAY_INTERVAL))
    {
        VP_RTCP_SendCalculateDelayAndJitter((VP_RTCP_SESSION*)g_stRtpAttr[i].stRtcp.hRTCP, u32PtsMs);
    }

    return HI_SUCCESS;
}

HI_S32 RTP_AcquireES(HI_HANDLE hRTP, size_t* u32BufAddr, HI_U32* u32Len, HI_U32* u32PtsMs, HI_BOOL *bFirstFU)
{
    HI_S32 s32Ret;
    HI_U32 i;
    RTP_RECV_BUF_NODE_S* pstTmpBufNode;
    HI_LIST* ptr_buf;
    HI_LIST* ptr_buf_n;
    HI_U32 depth = 0;
    RTP_RECV_BUF_S* pstRecvBuf = HI_NULL;

    CHECK_RTP_NULL_PTR(u32BufAddr);
    CHECK_RTP_NULL_PTR(u32Len);
    CHECK_RTP_NULL_PTR(u32PtsMs);
    CHECK_RTP_HANDLE(hRTP);
    CHECK_RTP_INIT;

    s32Ret = RTP_FindValidChannel(&hRTP, &i);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (g_stRtpAttr[i].pstRecvBuf)
    {
        pstRecvBuf = g_stRtpAttr[i].pstRecvBuf;
    }
    else
    {
        return HI_FAILURE;
    }

    /* find node in full list */
    if (!list_empty(&pstRecvBuf->RtpFullList))
    {
        pstTmpBufNode = list_entry(pstRecvBuf->RtpFullList.next, RTP_RECV_BUF_NODE_S, listhead);

        if (pstTmpBufNode->u32SeqNumber != (pstRecvBuf->u32LastOutSeq + 1))
        {
            if ((pstTmpBufNode->u32SeqNumber != 0) && (pstRecvBuf->u32LastOutSeq))
            {
                HI_RTP_LOCK();
                list_for_each_safe (ptr_buf, ptr_buf_n, &pstRecvBuf->RtpFullList)
                {
                    depth++;
                }
                HI_RTP_UNLOCK();

                /* still in reordering */
                if (depth <= g_stRtpAttr[i].stRtpAttr.u32SortDepth)
                {
                    HI_ERR_RTP("still in reordering,new %d ,last %d,Depth:%d <= %d\n", pstTmpBufNode->u32SeqNumber,
                               pstRecvBuf->u32LastOutSeq, depth, g_stRtpAttr[i].stRtpAttr.u32SortDepth);
                    return HI_FAILURE;
                }
            }
        }

        g_stRtpAttr[i].u32CurNum = pstTmpBufNode->u32SeqNumber;
        *u32BufAddr = (HI_SIZE_T)(pstTmpBufNode->pBlockAddr + pstTmpBufNode->u32Offset);
        *u32Len   = pstTmpBufNode->u32BlockSize;
        *u32PtsMs = pstTmpBufNode->u32Pts;
        *bFirstFU = pstTmpBufNode->bFirstFU;
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 RTP_ReleaseES(HI_HANDLE hRTP)
{
    HI_U32 i;
    HI_S32 s32Ret = HI_FAILURE;
    RTP_RECV_BUF_S* pstRecvBuf = HI_NULL;
    RTP_RECV_BUF_NODE_S* pstTmpBufNode = HI_NULL;
    HI_BOOL bFindNode = HI_FALSE;
    HI_LIST* ptr_buf;
    HI_LIST* ptr_buf_n;

    CHECK_RTP_HANDLE(hRTP);
    CHECK_RTP_INIT;

    s32Ret = RTP_FindValidChannel(&hRTP, &i);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (g_stRtpAttr[i].pstRecvBuf)
    {
        pstRecvBuf = g_stRtpAttr[i].pstRecvBuf;
    }
    else
    {
        return HI_FAILURE;
    }

    HI_RTP_LOCK();
    list_for_each_safe (ptr_buf, ptr_buf_n, &pstRecvBuf->RtpFullList)
    {
        pstTmpBufNode = list_entry(ptr_buf, RTP_RECV_BUF_NODE_S, listhead);
        if (pstTmpBufNode->u32SeqNumber == g_stRtpAttr[i].u32CurNum)
        {
            bFindNode = HI_TRUE;
            break;
        }
    }
    HI_RTP_UNLOCK();

    if (HI_TRUE == bFindNode && HI_NULL != pstTmpBufNode)
    {
        pstRecvBuf->u32LastOutSeq   = g_stRtpAttr[i].u32CurNum;
        pstTmpBufNode->u32BlockSize = g_stRtpAttr[i].stRtpAttr.u32RecvBufSize;
        HI_RTP_LOCK();
        list_move_tail(&pstTmpBufNode->listhead, &pstRecvBuf->RtpEmptyList);
        HI_RTP_UNLOCK();
    }
    else
    {
        HI_ERR_RTP("RTP_ReleaseES failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 RTP_GetRtcpReport(HI_HANDLE hRTP, RTP_RTCP_REPORT_S* pstReport)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i;
    VP_RTCP_SESSION* pstSession = HI_NULL;

    CHECK_RTP_NULL_PTR(pstReport);
    CHECK_RTP_HANDLE(hRTP);
    CHECK_RTP_INIT;

    s32Ret = RTP_FindValidChannel(&hRTP, &i);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (HI_FALSE == g_stRtpAttr[i].stRtpAttr.bEnableRtcp)
    {
        memcpy(pstReport, &g_stRtpAttr[i].stReport, sizeof(RTP_RTCP_REPORT_S));
        HI_INFO_RTP("NO RTCP, can not obtain Delay Jitter,and so on\n");
        return HI_SUCCESS;
    }

    pstSession = (VP_RTCP_SESSION*)g_stRtpAttr[i].stRtcp.hRTCP;
    if (HI_NULL == pstSession)
    {
        return HI_ERR_RTP_NOT_SUPPORT;
    }
    else
    {
        pstReport->u32RecvBytes = pstSession->stRecvInfo.ulBytes;
        pstReport->u32RecvPacketNum = pstSession->stRecvInfo.ulPackets;

        if (pstSession->bRtcpEnable)
        {
            pstReport->u32SendBytes   = pstSession->stRtcpStatisticInfo.uiSendBytes;
            pstReport->u32SendPackets = pstSession->stRtcpStatisticInfo.uiSendPacketNum;
        }
        else
        {
            pstReport->u32SendBytes   = g_stRtpAttr[i].stReport.u32SendBytes;
            pstReport->u32SendPackets = g_stRtpAttr[i].stReport.u32SendPackets;
        }

        pstReport->stSendInfo.u32Delay  = pstSession->stRtcpStatisticInfo.stSendInfo.uiDelay;
        pstReport->stSendInfo.u32Jitter = pstSession->stRtcpStatisticInfo.stSendInfo.uiJitter;
        pstReport->stSendInfo.u32LossPercent = pstSession->stRtcpStatisticInfo.stSendInfo.uiLossFraction;
        pstReport->stSendInfo.u32LostPackets = pstSession->stRtcpStatisticInfo.stSendInfo.uiTotalLostPacket;
        pstReport->stRecvInfo.u32Delay  = pstSession->stRtcpStatisticInfo.stRecvInfo.uiDelay;
        pstReport->stRecvInfo.u32Jitter = pstSession->stRtcpStatisticInfo.stRecvInfo.uiJitter;
        pstReport->stRecvInfo.u32LossPercent = pstSession->stRtcpStatisticInfo.stRecvInfo.uiLossFraction;
        pstReport->stRecvInfo.u32LostPackets = pstSession->stRtcpStatisticInfo.stRecvInfo.uiTotalLostPacket;

    }

    return HI_SUCCESS;
}

HI_S32 RTP_SetRtcpAttr(HI_HANDLE hRTP, HI_BOOL bEnable, HI_U32 u32SendTime)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i;

    CHECK_RTP_HANDLE(hRTP);
    CHECK_RTP_INIT;

    s32Ret = RTP_FindValidChannel(&hRTP, &i);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (HI_FALSE == g_stRtpAttr[i].stRtpAttr.bEnableRtcp)
    {
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    if ((u32SendTime < 500) || (u32SendTime > 65535) || (u32SendTime % 500))
    {
        HI_ERR_RTP("RTCP send interval(%d) is invalid.\n", u32SendTime);
        return HI_ERR_RTP_NOT_SUPPORT;
    }

    s32Ret = VP_RTCP_EnableRtcp(g_stRtpAttr[i].stRtcp.hRTCP, bEnable);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = VP_RTCP_CfgRtcpSendInterval(g_stRtpAttr[i].stRtcp.hRTCP, u32SendTime);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
