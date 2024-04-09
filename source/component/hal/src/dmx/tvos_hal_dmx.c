#define LOG_TAG "HALDMX"
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "tvos_hal_common.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_dmx.h"
#include "hi_unf_demux.h"
#include "hi_unf_descrambler.h"
#include "hi_unf_advca.h"
#include "hi_mpi_demux.h"
#include "pthread.h"

#define DMX_LOG_ERROR HAL_ERROR
#define DMX_LOG_INFO HAL_ERROR
#define DMX_MALLOC malloc
#define DMX_FREE free
#define DMX_CHANNEL_TOTAL   (96)
#define DMX_FILTER_TOTAL    (96)
#define DMX_MSG_BUF_NUM     (40)
#define DMX_AUD_BUF         (1 * 1024 * 1024)

/**origin is 4*1024*1024, modify 16 for promote play speed(from sxd) */
#define DMX_VID_BUF         (16 * 1024 * 1024)
#define DMX_CA_VID_LEN      (16)

#define INVALID_PID         (0x1FFF)
#define INVALID_HANDLE      (0)
#define INVALID_CHN_ID      (0x1fff)

//函数参数检查
#define HAL_DMX_CHK_PARA( val  ) \
    do                                                      \
    {                                                       \
        if (NULL == (val))                                  \
        {                                                   \
            DMX_LOG_ERROR("NULL PTR");                      \
            return ERROR_NULL_PTR;                          \
        };                                                  \
    } while (0)

#define HAL_DMX_CHK_INIT() \
    do                                                      \
    {                                                       \
        if (!s_bDmxInit)                                  \
        {                                                   \
            DMX_LOG_ERROR("Demux not init.");                      \
            return ERROR_NOT_INITED;                          \
        };                                                  \
    } while (0)

#define HAL_DMX_CHK_DMX_ID(dmxId) \
    do                                                      \
    {                                                       \
        if ((U32)dmxId >= s_u32DmxNum)                                  \
        {                                                   \
            DMX_LOG_ERROR("INVALID DMX ID %d, Total Dmx Num %d.", dmxId, s_u32DmxNum);  \
            return ERROR_DMX_INVALID_DMX_ID;                          \
        };                                                  \
    } while (0)

#define DMX_CHECK(pstChn) \
    if (NULL == pstChn)\
    {\
        DMX_LOG_ERROR("Invalid u32ChannelId"); \
        return ERROR_INVALID_PARAM; \
    }

/** dmx channel protect lock  */
#define DMX_LOCK() (VOID)pthread_mutex_lock( &s_DmxHandleMutex )
#define DMX_UNLOCK() (VOID)pthread_mutex_unlock( &s_DmxHandleMutex )

#define DMX_CHECK_AND_UNLOCK(pstChn) \
    if (NULL == pstChn)\
    {\
        DMX_UNLOCK(); \
        DMX_LOG_ERROR("Invalid u32ChannelId"); \
        return ERROR_INVALID_PARAM; \
    }

/** dmx descramble protect lock  */
#define DESCRAM_LOCK() (VOID)pthread_mutex_lock(&s_Descram_mutex);
#define DESCRAM_UNLOCK() (VOID)pthread_mutex_unlock(&s_Descram_mutex);

#define HAL_DMX_CHK_PARA_UNLOCK( val , unlock) \
    do \
    { \
        if (NULL == (val))  \
        { \
            DMX_LOG_ERROR("NULL PTR"); \
            unlock;\
            return ERROR_NULL_PTR; \
        }; \
    } while (0)

static pthread_mutex_t s_DmxHandleMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t s_Descram_mutex  = PTHREAD_MUTEX_INITIALIZER;

typedef struct  _DMX_CHN_S
{
    DMX_ID_E                  enDmxId;
    HI_HANDLE                 hChn;
    HI_HANDLE                 ahAttachedFilter[DMX_FILTER_TOTAL];
    DMX_NOTIFY_TYPE_E         enNotifyType;
    DMX_REG_CALLBACK_PARAMS_S pstFunc[DMX_CHANNEL_CALLBACK_MAX];
    struct  _DMX_CHN_S*       next;
} DMX_CHN_S;

typedef struct  _DMX_KEY_S
{
    DMX_ID_E                    enDmxId;
    HI_HANDLE                   hDesc;
    HI_HANDLE                   hChn;
    HI_BOOL                     bEnable;
    DMX_DESC_ASSOCIATE_MODE_E   enMode;
    DMX_DESC_ASSOCIATE_PARAMS_S stAssocviateInfo;
    struct  _DMX_KEY_S*         next;
} DMX_KEY_S;

static DMX_CHN_S* s_pstDmxChnListHead = NULL;
static DMX_KEY_S* s_pstDmxKeyListHead = NULL;
static pthread_t s_DmxThread;
static BOOL s_bDmxTaskRun = FALSE;
static BOOL s_bDmxInit = FALSE;
static U32 s_u32DmxNum = 0;

static DMX_CHANNEL_TYPE_E dmxConvert2HalChnType(HI_UNF_DMX_CHAN_TYPE_E enSdkChnType)
{
    DMX_CHANNEL_TYPE_E enHalChnType;

    switch (enSdkChnType)
    {
        case HI_UNF_DMX_CHAN_TYPE_SEC:
            enHalChnType = DMX_SECTION_CHANNEL;
            break;

        case HI_UNF_DMX_CHAN_TYPE_PES:
            enHalChnType = DMX_PES_CHANNEL;
            break;

        case HI_UNF_DMX_CHAN_TYPE_AUD:
            enHalChnType = DMX_AUDIO_CHANNEL;
            break;

        case HI_UNF_DMX_CHAN_TYPE_VID:
            enHalChnType = DMX_VIDEO_CHANNEL;
            break;

        case HI_UNF_DMX_CHAN_TYPE_POST:
            enHalChnType = DMX_POST_CHANNEL;
            break;

        case HI_UNF_DMX_CHAN_TYPE_ECM_EMM:
            enHalChnType = DMX_CHANNEL_BUTT;
            break;

        default:
            enHalChnType = DMX_CHANNEL_BUTT;
    }

    return enHalChnType;
}

static HI_UNF_DMX_CHAN_TYPE_E dmxConvert2SdkChnType(DMX_CHANNEL_TYPE_E enHalChnType)
{
    HI_UNF_DMX_CHAN_TYPE_E enSdkChnType;

    switch (enHalChnType)
    {
        case DMX_VIDEO_CHANNEL:
            enSdkChnType = HI_UNF_DMX_CHAN_TYPE_VID;
            break;

        case DMX_AUDIO_CHANNEL:
            enSdkChnType = HI_UNF_DMX_CHAN_TYPE_AUD;
            break;

        case DMX_PES_CHANNEL:
            enSdkChnType = HI_UNF_DMX_CHAN_TYPE_PES;
            break;

        case DMX_SECTION_CHANNEL:
            enSdkChnType = HI_UNF_DMX_CHAN_TYPE_SEC;
            break;

        case DMX_POST_CHANNEL:
            enSdkChnType = HI_UNF_DMX_CHAN_TYPE_POST;
            break;

        case DMX_PCR_CHANNEL:
            enSdkChnType = HI_UNF_DMX_CHAN_TYPE_BUTT;
            break;

        default:
            enSdkChnType = HI_UNF_DMX_CHAN_TYPE_BUTT;
    }

    return enSdkChnType;
}

static DMX_CHANNEL_DATA_TYPE_E dmxConvert2HalChnDataType(HI_UNF_DMX_DATA_TYPE_E enSdkChnDataType)
{
    DMX_CHANNEL_DATA_TYPE_E enHalChnDataType;

    switch (enSdkChnDataType)
    {
        case HI_UNF_DMX_DATA_TYPE_WHOLE:
            enHalChnDataType = DMX_DATA_TYPE_WHOLE;
            break;

        case HI_UNF_DMX_DATA_TYPE_HEAD:
            enHalChnDataType = DMX_DATA_TYPE_HEAD;
            break;

        case HI_UNF_DMX_DATA_TYPE_BODY:
            enHalChnDataType = DMX_DATA_TYPE_BODY;
            break;

        case HI_UNF_DMX_DATA_TYPE_TAIL:
            enHalChnDataType = DMX_DATA_TYPE_TAIL;
            break;

        default:
            enHalChnDataType = DMX_DATA_TYPE_BUTT;
    }

    return enHalChnDataType;
}

static HI_UNF_DMX_DATA_TYPE_E dmxConvert2SdkChnDataType(DMX_CHANNEL_DATA_TYPE_E enHalChnDataType)
{
    HI_UNF_DMX_DATA_TYPE_E enSdkChnDataType;

    switch (enHalChnDataType)
    {
        case DMX_DATA_TYPE_WHOLE:
            enSdkChnDataType = HI_UNF_DMX_DATA_TYPE_WHOLE;
            break;

        case DMX_DATA_TYPE_HEAD:
            enSdkChnDataType = HI_UNF_DMX_DATA_TYPE_HEAD;
            break;

        case DMX_DATA_TYPE_BODY:
            enSdkChnDataType = HI_UNF_DMX_DATA_TYPE_BODY;
            break;

        case DMX_DATA_TYPE_TAIL:
            enSdkChnDataType = HI_UNF_DMX_DATA_TYPE_TAIL;
            break;

        default:
            enSdkChnDataType = HI_UNF_DMX_DATA_TYPE_BUTT;
    }

    return enSdkChnDataType;
}

static DMX_CHANNEL_STATUS_E dmxConvert2HalChnStatus(HI_UNF_DMX_CHAN_STATUS_E enSdkChnStatus)
{
    DMX_CHANNEL_STATUS_E enHalChnStatus;

    switch (enSdkChnStatus)
    {
        case HI_UNF_DMX_CHAN_CLOSE:
            enHalChnStatus = DMX_CHANNEL_DISABLE;
            break;

        case HI_UNF_DMX_CHAN_PLAY_EN:
            enHalChnStatus = DMX_CHANNEL_ENABLE;
            break;

        case HI_UNF_DMX_CHAN_REC_EN:
            enHalChnStatus = DMX_CHANNEL_ENABLE;
            break;

        case HI_UNF_DMX_CHAN_PLAY_REC_EN:
            enHalChnStatus = DMX_CHANNEL_ENABLE;
            break;

        default:
            enHalChnStatus = DMX_CHANNEL_DISABLE;
    }

    return enHalChnStatus;
}

static HI_UNF_DMX_CHAN_CRC_MODE_E dmxConvert2SdkCrcMode(U32 u32IsCRC)
{
    if (0 == u32IsCRC)
    {
        return HI_UNF_DMX_CHAN_CRC_MODE_FORBID;
    }
    else
    {
        return HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_DISCARD;
    }
}

static U32 dmxConvert2HalCrcMode(HI_UNF_DMX_CHAN_CRC_MODE_E enSdkCrcMode)
{
    U32 u32HalIsCRC;

    switch (enSdkCrcMode)
    {
        case HI_UNF_DMX_CHAN_CRC_MODE_FORBID:
            u32HalIsCRC = 0;
            break;
        case HI_UNF_DMX_CHAN_CRC_MODE_FORCE_AND_DISCARD:
        case HI_UNF_DMX_CHAN_CRC_MODE_FORCE_AND_SEND:
        case HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_DISCARD:
        case HI_UNF_DMX_CHAN_CRC_MODE_BY_SYNTAX_AND_SEND:
            u32HalIsCRC = 1;
            break;

        default:
            u32HalIsCRC = 0;
    }

    return u32HalIsCRC;
}

static HI_UNF_DMX_DESCRAMBLER_TYPE_E dmxConvert2SdkDescramblerType(DMX_DESC_TYPE_E enHalDescType)
{
    HI_UNF_DMX_DESCRAMBLER_TYPE_E enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2;
    switch(enHalDescType)
    {
        case DMX_DESC_TYPE_CSA2:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2;
            break;
        case DMX_DESC_TYPE_CSA3:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3;
            break;
        case DMX_DESC_TYPE_DES_CI:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_DES_CI;
            break;
        case DMX_DESC_TYPE_DES_CBC:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_DES_CBC;
            break;
        case DMX_DESC_TYPE_DES_IPTV:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_DES_IPTV;
            break;
        case DMX_DESC_TYPE_TDES_ECB:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_TDES_ECB;
            break;
        case DMX_DESC_TYPE_TDES_CBC:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_TDES_CBC;
            break;
        case DMX_DESC_TYPE_TDES_IPTV:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_TDES_IPTV;
            break;
        case DMX_DESC_TYPE_AES_ECB:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_ECB;
            break;
        case DMX_DESC_TYPE_AES_CBC:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC;
            break;
        case DMX_DESC_TYPE_AES_IPTV:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_IPTV;
            break;
        case DMX_DESC_TYPE_AES_NS:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_NS;
            break;
        case DMX_DESC_TYPE_AES_CI:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CI;
            break;
        case DMX_DESC_TYPE_SMS4_ECB:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_ECB;
            break;
        case DMX_DESC_TYPE_SMS4_CBC:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_CBC;
            break;
        case DMX_DESC_TYPE_SMS4_IPTV:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_IPTV;
            break;
        case DMX_DESC_TYPE_SMS4_NS:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_NS;
            break;
        default:
            enSdkDescType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2;
            break;
    }
    return enSdkDescType;
}

static DMX_DESC_TYPE_E dmxConvert2HalDescramblerType(HI_UNF_DMX_DESCRAMBLER_TYPE_E enSdkDescType)
{
    DMX_DESC_TYPE_E enHalDescType = DMX_DESC_TYPE_CSA2;
    switch(enSdkDescType)
    {
        case HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2:
            enHalDescType = DMX_DESC_TYPE_CSA2;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3:
            enHalDescType = DMX_DESC_TYPE_CSA3;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_DES_CI:
            enHalDescType = DMX_DESC_TYPE_DES_CI;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_DES_CBC:
            enHalDescType = DMX_DESC_TYPE_DES_CBC;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_DES_IPTV:
            enHalDescType = DMX_DESC_TYPE_DES_IPTV;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_TDES_ECB:
            enHalDescType = DMX_DESC_TYPE_TDES_ECB;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_TDES_CBC:
            enHalDescType = DMX_DESC_TYPE_TDES_CBC;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_TDES_IPTV:
            enHalDescType = DMX_DESC_TYPE_TDES_IPTV;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_ECB:
            enHalDescType = DMX_DESC_TYPE_AES_ECB;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC:
            enHalDescType = DMX_DESC_TYPE_AES_CBC;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_IPTV:
            enHalDescType = DMX_DESC_TYPE_AES_IPTV;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_NS:
            enHalDescType = DMX_DESC_TYPE_AES_NS;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CI:
            enHalDescType = DMX_DESC_TYPE_AES_CI;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_ECB:
            enHalDescType = DMX_DESC_TYPE_SMS4_ECB;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_CBC:
            enHalDescType = DMX_DESC_TYPE_SMS4_CBC;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_IPTV:
            enHalDescType = DMX_DESC_TYPE_SMS4_IPTV;
            break;
        case HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_NS:
            enHalDescType = DMX_DESC_TYPE_SMS4_NS;
            break;
        default:
            enHalDescType = DMX_DESC_TYPE_CSA2;
            break;
    }
    return enHalDescType;
}

static VOID dmxConvert2SdkFilterAttr(const DMX_FILTER_DATA_S* const pstHalFilterData, HI_UNF_DMX_FILTER_ATTR_S* const pstSdkFilterAttr)
{
    HI_U32 i;
    HI_U32 len    = pstHalFilterData->u32FilterSize;
    HI_U8* match  = pstHalFilterData->pu8Match;
    HI_U8* mask   = pstHalFilterData->pu8Mask;
    HI_U8* negate = pstHalFilterData->pu8Notmask;
    HI_UNF_DMX_FILTER_ATTR_S* attr = pstSdkFilterAttr;

    attr->u32FilterDepth = 0;
    memset(attr->au8Match, 0xff, sizeof(attr->au8Match));
    memset(attr->au8Mask, 0x00, sizeof(attr->au8Mask));
    memset(attr->au8Negate, 0x00, sizeof(attr->au8Negate));

    if (len > 0)
    {
        len = (len > DMX_FILTER_MAX_DEPTH) ? DMX_FILTER_MAX_DEPTH : len;

        if ((NULL == match) || (NULL == mask) || (NULL == negate))
        {
            return;
        }

        attr->au8Match[0] = match[0];
        attr->au8Mask[0]   = ~(mask[0]);
        attr->au8Negate[0] = negate[0];

        attr->u32FilterDepth = 1;

        if (len > 3)
        {
            memcpy(&attr->au8Match[1], match + 3, len - 3);

            for (i = 3; i < len; i++)
            {
                attr->au8Mask[i - 2] = ~mask[i];
            }

            memcpy(&attr->au8Negate[1], negate + 3, len - 3);

            attr->u32FilterDepth += (len - 3);
        }

        for (i = 0; i < len; i++)
        {
            if (attr->au8Negate[i] != 0)
            {
                attr->au8Negate[i] = 1;
            }
        }
    }
}

U8 s_au8Match[DMX_FILTER_MAX_DEPTH + 2];
U8 s_au8Mask[DMX_FILTER_MAX_DEPTH + 2];
U8 s_au8Notmask[DMX_FILTER_MAX_DEPTH + 2];
static VOID dmxConvert2HalFilterAttr(const HI_UNF_DMX_FILTER_ATTR_S* const pstSdkFilterAttr, DMX_FILTER_DATA_S* const pstHalFilterData)
{
    HI_U32 i;
    HI_U32 len = pstSdkFilterAttr->u32FilterDepth;

    pstHalFilterData->pu8Match = s_au8Match;
    pstHalFilterData->pu8Mask = s_au8Mask;
    pstHalFilterData->pu8Notmask = s_au8Notmask;
    memset(s_au8Match, 0, DMX_FILTER_MAX_DEPTH + 2);
    memset(s_au8Mask, 0, DMX_FILTER_MAX_DEPTH + 2);
    memset(s_au8Notmask, 0, DMX_FILTER_MAX_DEPTH + 2);

    if (len > 0)
    {
        s_au8Match[0] = pstSdkFilterAttr->au8Match[0];
        s_au8Mask[0] = ~pstSdkFilterAttr->au8Mask[0];
        s_au8Notmask[0] = pstSdkFilterAttr->au8Negate[0];
        pstHalFilterData->u32FilterSize = 1;

        if (len > 1)
        {
            /* 第一字节，第二字节无意义 */

            for (i = 1; i < len; i++)
            {
                s_au8Match[i + 2] = pstSdkFilterAttr->au8Match[i];
            }

            for (i = 1; i < len; i++)
            {
                s_au8Mask[i + 2] = ~pstSdkFilterAttr->au8Mask[i];
            }

            for (i = 1; i < len; i++)
            {
                s_au8Notmask[i + 2] = pstSdkFilterAttr->au8Negate[i];
            }

            pstHalFilterData->u32FilterSize = len + 2;
        }
    }
}

static VOID dmxConvert2SdkChnAttr(const DMX_CHANNEL_OPEN_PARAM_S* const pstHalChnAttr, HI_UNF_DMX_CHAN_ATTR_S* const pstSdkChnAttr)
{
    pstSdkChnAttr->enChannelType = dmxConvert2SdkChnType(pstHalChnAttr->enType);

    pstSdkChnAttr->u32BufSize = pstHalChnAttr->u32Len;
    pstSdkChnAttr->enCRCMode = dmxConvert2SdkCrcMode(pstHalChnAttr->stChannelSettings.u32IsCRC);
    pstSdkChnAttr->enOutputMode = HI_UNF_DMX_CHAN_OUTPUT_MODE_PLAY;
    pstSdkChnAttr->enSecureMode = pstHalChnAttr->enSecureMode;
}

DMX_CHN_S* dmxNewChnInfo(const DMX_ID_E enDmxId, const DMX_CHANNEL_OPEN_PARAM_S* const pstOpenParams, const HI_HANDLE hChn)
{
    DMX_CHN_S** p = &s_pstDmxChnListHead;
    DMX_CHN_S* q = NULL;
    int j = 0;

    q = (DMX_CHN_S*)DMX_MALLOC(sizeof(DMX_CHN_S));

    if (NULL == q)
    {
        return NULL;
    }

    memset(q, 0, sizeof(DMX_CHN_S));

    while (*p != NULL)
    {
        p = &((*p)->next);
    }

    *p = q;
    q->next = NULL;

    q->enDmxId = enDmxId;
    q->hChn = hChn;

    if(pstOpenParams!=NULL)
      q->enNotifyType = pstOpenParams->stChannelSettings.enNotifyType;

    for (j = 0; j < DMX_CHANNEL_CALLBACK_MAX; ++j)
    {
        q->pstFunc[j].pfnCallback = NULL;
    }

    return q;
}

VOID dmxDelChnInfo(HI_HANDLE hChn)
{
    DMX_CHN_S** p = &s_pstDmxChnListHead;
    DMX_CHN_S*  q = NULL;

    while (*p != NULL)
    {
        if ((*p)->hChn == hChn)
        {
            break;
        }

        p = &((*p)->next);
    }

    if (*p == NULL)
    {
        DMX_LOG_ERROR("*p == NULL \n");
        return;
    }

    q  = *p;
    *p = (*p)->next;

    DMX_FREE(q);
    q = NULL;

    return;
}

DMX_CHN_S* dmxGetChnInfo(HI_HANDLE hChn)
{
    DMX_CHN_S* p = s_pstDmxChnListHead;

    while (p != NULL)
    {
        if (p->hChn == hChn)
        {
            break;
        }

        p = p->next;
    }

    return p;
}

DMX_KEY_S*  dmxNewKeyInfo(const DMX_ID_E enDemuxId, const HI_HANDLE hKey, const DMX_DESC_ASSOCIATE_MODE_E enMode)
{
    DMX_KEY_S** p = &s_pstDmxKeyListHead;
    DMX_KEY_S* q = NULL;

    q = (DMX_KEY_S*)DMX_MALLOC(sizeof(DMX_KEY_S));

    if (NULL == q)
    {
        return NULL;
    }

    memset(q, 0x0, sizeof(DMX_KEY_S));

    while (*p != NULL)
    {
        p = &((*p)->next);
    }

    *p = q;
    q->enDmxId = enDemuxId;
    q->hDesc  = hKey;
    q->enMode = enMode;
    q->hChn = INVALID_HANDLE;
    q->bEnable = HI_FALSE;
    q->stAssocviateInfo.enMode = enMode;

    if (DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDS == enMode)
    {
        q->stAssocviateInfo.DMX_ASSOCIATE_U.u16Pid =  INVALID_PID;
    }
    else
    {
        q->stAssocviateInfo.DMX_ASSOCIATE_U.u32ChannelId =  INVALID_CHN_ID;
    }

    q->next = NULL;

    return q;
}

DMX_KEY_S* dmxGetKeyInfoByDesc(const HI_HANDLE hDesc)
{
    DMX_KEY_S* p = s_pstDmxKeyListHead;

    while (p != NULL)
    {
        if (p->hDesc == hDesc)
        {
            break;
        }

        p = p->next;
    }

    return p;
}

DMX_KEY_S* dmxGetKeyInfoByChn(const HI_HANDLE hChn)
{
    DMX_KEY_S* p = s_pstDmxKeyListHead;

    while (p != NULL)
    {
        if ((p->hChn == hChn) && (p->bEnable == HI_TRUE))
        {
            break;
        }

        p = p->next;
    }

    return p;
}

VOID dmxDelKeyInfo(const HI_HANDLE hDesc)
{
    DMX_KEY_S** p = &s_pstDmxKeyListHead;
    DMX_KEY_S*  q = NULL;

    while (*p != NULL)
    {
        if ((*p)->hDesc == hDesc)
        {
            break;
        }

        p = &((*p)->next);
    }

    if (*p == NULL)
    {
        DMX_LOG_ERROR("*p == NULL \n");
        return;
    }

    q  = *p;
    *p = (*p)->next;

    DMX_FREE(q);
    q = NULL;

    return;
}

static void* dmxRecvTask(void* ptr)
{
    HI_S32 s32Ret = SUCCESS;
    HI_HANDLE hChn[DMX_CHANNEL_TOTAL];
    HI_U32 u32ChnNum = 0;
    HI_U32 u32DataNum = 0;
    DMX_CHN_S* pstChnInfo = NULL;
    HI_UNF_DMX_DATA_S astSecDataBuf[DMX_MSG_BUF_NUM];
    HI_U32 i = 0;
    HI_U32 j = 0;
    HI_U32 k = 0;
    DMX_CALLBACK_DATA_S stDmxCallbackData;
    DMX_SECTION_DATA_S stSecData;

    while (s_bDmxTaskRun)
    {
        DMX_LOCK();

        u32ChnNum = sizeof(hChn) / sizeof(hChn[0]);

        /**origin timeout is 20, for promote play speed change to 0(from sxd) */
        s32Ret = HI_UNF_DMX_GetDataHandle(hChn, &u32ChnNum, 0);
        if (HI_SUCCESS != s32Ret)
        {
            DMX_UNLOCK();
            usleep(10 * 1000);
            continue;
        }

        for (i = 0; i < u32ChnNum; i++)
        {
            HI_HANDLE hChannel = hChn[i];
            pstChnInfo = dmxGetChnInfo(hChannel);

            if (NULL == pstChnInfo)
            {
                continue;
            }

            stDmxCallbackData.pstSectionData = NULL;
            stDmxCallbackData.u32ChannelId = hChannel;
            stDmxCallbackData.enEvt = DMX_ALL_EVT;
            stDmxCallbackData.enDemuxId   = pstChnInfo->enDmxId;
            stDmxCallbackData.u32FilterId = 0; // TODO:没用

            if ((DMX_NOTIFY_DATA != pstChnInfo->enNotifyType))
            {
                /* 没有回调。不上报数据，等待其主动获取  */
                for (k = 0; k < DMX_CHANNEL_CALLBACK_MAX; k++)
                {
                    if ((0 == pstChnInfo->pstFunc[k].u32IsDisable) && (NULL != pstChnInfo->pstFunc[k].pfnCallback))
                    {
                        DMX_UNLOCK();
                        pstChnInfo->pstFunc[k].pfnCallback(&stDmxCallbackData);
                        DMX_LOCK();
                    }
                }

                continue;
            }

            s32Ret = HI_UNF_DMX_AcquireBuf(hChannel, DMX_MSG_BUF_NUM, &u32DataNum, astSecDataBuf, 10);
            if (HI_SUCCESS != s32Ret)
            {
                continue;
            }

            stDmxCallbackData.pstSectionData = &stSecData;

            for (j = 0; j < u32DataNum; j++)
            {
                stSecData.pData = astSecDataBuf[j].pu8Data;
                stSecData.u32Length = astSecDataBuf[j].u32Size;

                for (k = 0; k < DMX_CHANNEL_CALLBACK_MAX; k++)
                {
                    if ((0 == pstChnInfo->pstFunc[k].u32IsDisable) && (NULL != pstChnInfo->pstFunc[k].pfnCallback))
                    {
                        DMX_UNLOCK();
                        pstChnInfo->pstFunc[k].pfnCallback(&stDmxCallbackData);
                        DMX_LOCK();
                    }
                }
            }

            HI_UNF_DMX_ReleaseBuf(hChannel, u32DataNum, astSecDataBuf);
        }

        DMX_UNLOCK();
        usleep(10 * 1000);
    }

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return NULL;
}

static S32 dmx_channel_close_ex(const U32 u32ChannelId, const DMX_CHANNEL_CLOSE_PARAMS_S* pstCloseParams);

S32 dmx_init(struct _DEMUX_DEVICE_S* pstDev, const DMX_INIT_PARAMS_S* const pstInitParams )
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_CAPABILITY_S stDmxCapability;

    memset(&stDmxCapability, 0, sizeof(HI_UNF_DMX_CAPABILITY_S));

    if (s_bDmxInit)
    {
        return SUCCESS;
    }

    DMX_LOCK();

    s32Ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_Init fail s32Ret=%#x \n", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    s32Ret = HI_UNF_DMX_GetCapability(&stDmxCapability);
    if (HI_SUCCESS == s32Ret)
    {
        s_u32DmxNum = stDmxCapability.u32DmxNum;
    }

    s_bDmxTaskRun = HI_TRUE;

    s32Ret = pthread_create(&s_DmxThread, NULL, dmxRecvTask, NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_UNF_DMX_DeInit();
        s_bDmxTaskRun = HI_FALSE;
        DMX_LOG_ERROR("pthread_create s32Ret=%#x \n", s32Ret);
        DMX_UNLOCK();
        return FAILURE;
    }

    s_bDmxInit = TRUE;
    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_term(struct _DEMUX_DEVICE_S* pstDev, const DMX_TERM_PARAM_S* const pstTermParams )
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );

    DMX_CHN_S* pChn = NULL;
    DMX_KEY_S* pKey = NULL;

    if (!s_bDmxInit)
    {
        return SUCCESS;
    }

    s_bDmxTaskRun = HI_FALSE;

    pthread_join(s_DmxThread, NULL);

    DMX_LOCK();

    pChn = s_pstDmxChnListHead;

    while (pChn != NULL)
    {
        dmx_channel_close_ex(pChn->hChn, NULL);
        pChn = pChn->next;
    }

    pKey = s_pstDmxKeyListHead;

    while (pKey != NULL)
    {
        HI_UNF_DMX_DestroyDescrambler(pKey->hDesc);
        pKey = pKey->next;
    }

    HI_UNF_DMX_DeInit();

    s_bDmxInit = FALSE;

    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_set_source_params(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, const DMX_SOURCE_PARAMS_S* pstSourceParams)
{
    S32 s32Ret = SUCCESS;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstSourceParams);
    HAL_DMX_CHK_DMX_ID(enDemuxId);

    // TODO:
    if (DMX_SOURCE_TUNER == pstSourceParams->enSourceType)
    {
        s32Ret = HI_UNF_DMX_AttachTSPort(enDemuxId, (HI_UNF_DMX_PORT_E)pstSourceParams->DMX_SOURCE_U.hSource);
        if (SUCCESS != s32Ret)
        {
            DMX_LOG_ERROR("demux attch port fail");
            return ERROR_DMX_OP_FAILED;
        }
    }
    else if (DMX_SOURCE_MEM == pstSourceParams->enSourceType)
    {
        s32Ret = HI_UNF_DMX_AttachTSPort(enDemuxId, (HI_UNF_DMX_PORT_E)pstSourceParams->DMX_SOURCE_U.hInjecter);
        if (SUCCESS != s32Ret)
        {
            DMX_LOG_ERROR("demux attch port fail");
            return ERROR_DMX_OP_FAILED;
        }
    }
    else if (DMX_SOURCE_NONE == pstSourceParams->enSourceType)
    {
        (VOID)HI_UNF_DMX_DetachTSPort(enDemuxId);
        return SUCCESS;
    }
    else
    {
        DMX_LOG_ERROR("invalid param enSourceType= %d", pstSourceParams->enSourceType);
        return ERROR_INVALID_PARAM;
    }

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_get_source_params(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, DMX_SOURCE_PARAMS_S* const pstSourceParams)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstSourceParams);
    HAL_DMX_CHK_DMX_ID(enDemuxId);

    // TODO:
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_PORT_E enPordId = HI_UNF_DMX_PORT_BUTT;

    s32Ret = HI_UNF_DMX_GetTSPortId(enDemuxId, &enPordId);

    if (HI_ERR_DMX_NOATTACH_PORT == s32Ret)
    {
        pstSourceParams->enSourceType = DMX_SOURCE_NONE;
        DMX_LOG_ERROR("Demux no attch source.");
        return ERROR_DMX_NOATTACH_SOURCE;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("get ts port fail.");
        return ERROR_DMX_OP_FAILED;
    }

    if ((enPordId >= HI_UNF_DMX_PORT_IF_0) && (enPordId <= HI_UNF_DMX_PORT_TSI_15))
    {
        pstSourceParams->enSourceType = DMX_SOURCE_TUNER;
        pstSourceParams->DMX_SOURCE_U.hSource = enPordId;
        pstSourceParams->DMX_SOURCE_U.hInjecter = enPordId;

    }
    else if ((enPordId >= HI_UNF_DMX_PORT_RAM_0) && (enPordId <= HI_UNF_DMX_PORT_RAM_15))
    {
        pstSourceParams->enSourceType = DMX_SOURCE_MEM;
        pstSourceParams->DMX_SOURCE_U.hSource = enPordId;
        pstSourceParams->DMX_SOURCE_U.hInjecter = enPordId;
    }

    DMX_LOG_INFO("[%s][%d] pstSourceParams->enSourceType = 0x%x\n",__FUNCTION__,__LINE__ ,pstSourceParams->enSourceType);
    return SUCCESS;
}

S32 dmx_disconnect(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = SUCCESS;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);

    s32Ret = HI_UNF_DMX_DetachTSPort(enDemuxId);
    if (HI_SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("Demux detach fail.");
        return ERROR_DMX_OP_FAILED;
    }

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_reconnect(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = SUCCESS;
    HI_UNF_DMX_PORT_E enPortId = HI_UNF_DMX_PORT_BUTT;

    s32Ret = HI_UNF_DMX_GetTSPortId(enDemuxId, &enPortId);
    s32Ret |= HI_UNF_DMX_AttachTSPort(enDemuxId, enPortId);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("attach ts port fail");
        return ERROR_DMX_OP_FAILED;
    }

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_get_capability(struct _DEMUX_DEVICE_S* pstDev, DMX_CAPABILITY_S* const pstCapability)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );

    // TODO:
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_CAPABILITY_S stCap;
    U32 u32Index;

    HAL_DMX_CHK_PARA(pstCapability);

    memset(&stCap, 0x0, sizeof(stCap));

    s32Ret = HI_UNF_DMX_GetCapability(&stCap);
    if (HI_SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("get demux capability fail");
        return ERROR_DMX_OP_FAILED;
    }

    pstCapability->u32DMXNum = stCap.u32DmxNum;

    for (u32Index = 0; u32Index < pstCapability->u32DMXNum;  u32Index++)
    {
        pstCapability->u32ChannelNumArr[u32Index] = stCap.u32ChannelNum;
        pstCapability->u32FilterNumArr[u32Index] = stCap.u32FilterNum;
    }

    DMX_LOG_INFO("[%s][%d] pstCapability->u32DMXNum = 0x%x\n",__FUNCTION__,__LINE__,pstCapability->u32DMXNum);
    return SUCCESS;
}

S32 dmx_get_status(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, DMX_STATUS_S* const pstStatus)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    HI_UNF_DMX_PORT_PACKETNUM_S stTSPortPacketNum;
    HI_U32 u32DmxId = enDemuxId;
    HI_S32 s32Ret = FAILURE;
    HI_U32 u32PortId = 0;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);
    HAL_DMX_CHK_PARA(pstStatus);

    s32Ret  = HI_UNF_DMX_GetFreeChannelCount(u32DmxId, &pstStatus->u32FreeChannelNum);
    s32Ret |= HI_UNF_DMX_GetFreeFilterCount (u32DmxId, &pstStatus->u32FreeFilterNum);
    s32Ret |= HI_UNF_DMX_GetFreeDescramblerKeyCount(u32DmxId, &pstStatus->u32FreeDescramblerNum);
    s32Ret |= HI_UNF_DMX_GetTSPortId( u32DmxId, (HI_UNF_DMX_PORT_E*)&u32PortId);
    s32Ret |= HI_UNF_DMX_GetTSPortPacketNum((HI_UNF_DMX_PORT_E)u32PortId, &stTSPortPacketNum);

    if (HI_SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("dmx_get_status s32Ret=%#x \n", s32Ret);
        return FAILURE;
    }

    pstStatus->u32TsPacketCount = stTSPortPacketNum.u32TsPackCnt;

    DMX_LOG_INFO("[%s][%d] pstStatus->u32FreeChannelNum = 0x%x, pstStatus->u32FreeDescramblerNum = 0x%x, pstStatus->u32FreeFilterNum = 0x%x,pstStatus->u32IsConnect = 0x%x,pstStatus->u32TsPacketCount = 0x%x\n",\
                  __FUNCTION__,__LINE__,pstStatus->u32FreeChannelNum, pstStatus->u32FreeDescramblerNum,pstStatus->u32FreeFilterNum,pstStatus->u32IsConnect,pstStatus->u32TsPacketCount);
    return SUCCESS;
}

S32 dmx_channel_open(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32ChannelId, const DMX_CHANNEL_OPEN_PARAM_S* const pstOpenParams)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = FAILURE;
    HI_HANDLE hDmxChn = INVALID_HANDLE;
    HI_UNF_DMX_CHAN_ATTR_S stChAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);
    HAL_DMX_CHK_PARA(pu32ChannelId);
    HAL_DMX_CHK_PARA(pstOpenParams);

    // TODO: u32FirstIndex    u32AddData     u32Tag
    memset(&stChAttr, 0, sizeof(stChAttr));

    dmxConvert2SdkChnAttr(pstOpenParams, &stChAttr);

    s32Ret = HI_UNF_DMX_CreateChannel(enDemuxId, &stChAttr, &hDmxChn);
    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CreateChannel error ret = %#x \n ", s32Ret);
        return ERROR_INVALID_PARAM;
    }

    if (HI_ERR_DMX_NOFREE_CHAN == s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CreateChannel error ret = %#x \n ", s32Ret);
        return ERROR_DMX_NOFREE_CHAN;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CreateChannel error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    if (pstOpenParams->u32Pid < INVALID_PID)
    {
        s32Ret = HI_UNF_DMX_SetChannelPID(hDmxChn, pstOpenParams->u32Pid);
        if (SUCCESS != s32Ret)
        {
            DMX_LOG_ERROR("HI_UNF_DMX_SetChannelPID error ret = %#x \n ", s32Ret);
            s32Ret = HI_UNF_DMX_DestroyChannel(hDmxChn);
            if(SUCCESS != s32Ret)
            {
                 DMX_LOG_ERROR("HI_UNF_DMX_DestroyChannel error ret = %#x \n ", s32Ret);
            }

            return ERROR_DMX_OP_FAILED;
        }
    }

    *pu32ChannelId = hDmxChn;

    DMX_LOCK();
    dmxNewChnInfo(enDemuxId, pstOpenParams, hDmxChn);
    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] *pu32ChannelId = 0x%x\n",__FUNCTION__,__LINE__,*pu32ChannelId );
    return SUCCESS;
}

S32 dmx_channel_close_ex(const U32 u32ChannelId, const DMX_CHANNEL_CLOSE_PARAMS_S* pstCloseParams )
{
    DMX_LOG_INFO("[%s][%d] u32ChannelId = 0x%x\n",__FUNCTION__,__LINE__,u32ChannelId);
    S32 i = 0;
    S32 s32Ret = FAILURE;
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);

    DMX_CHECK(pstDmxInfo);

    for (i = 0; i < DMX_FILTER_TOTAL; i++)
    {
        if (0 != pstDmxInfo->ahAttachedFilter[i])
        {
            s32Ret = HI_UNF_DMX_DestroyFilter(pstDmxInfo->ahAttachedFilter[i]);
            if (SUCCESS != s32Ret)
            {
                DMX_LOG_ERROR("HI_UNF_DMX_DestroyFilter error, handle = %#x, ret = %#x \n ", pstDmxInfo->ahAttachedFilter[i], s32Ret);
            }

            pstDmxInfo->ahAttachedFilter[i] = 0;
        }
    }

    s32Ret = HI_UNF_DMX_DestroyChannel(u32ChannelId);
    if(HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        s32Ret = HI_MPI_DMX_DestroyPcrChannel(u32ChannelId);
        if (SUCCESS != s32Ret)
        {
            DMX_LOG_ERROR("INVALID PCR ID = %#x \n", u32ChannelId);
            return ERROR_DMX_OP_FAILED;
        }
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_DestroyChannel error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_channel_close(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_CHANNEL_CLOSE_PARAMS_S* pstCloseParams)
{
    DMX_LOG_INFO("[%s][%d] u32ChannelId = 0x%x\n",__FUNCTION__,__LINE__,u32ChannelId );
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    s32Ret = dmx_channel_close_ex(u32ChannelId, pstCloseParams);

    if (SUCCESS != s32Ret)
    {
        DMX_UNLOCK();
        return s32Ret;
    }

    dmxDelChnInfo(u32ChannelId);
    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_channel_set_pid(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U16 u16Pid)
{
    S32 s32Ret = FAILURE;
    U32 u32TempPid = 0;

    HAL_DMX_CHK_INIT();

    DMX_LOG_INFO("[%s][%d] u32ChannelId = 0x%x,u16Pid = 0x%x\n",__FUNCTION__,__LINE__ ,u32ChannelId,u16Pid);

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    if (u16Pid > INVALID_PID)
    {
        u32TempPid = INVALID_PID;
        s32Ret = HI_UNF_DMX_SetChannelPID((HI_HANDLE)u32ChannelId, u32TempPid);
    }
    else
    {
        s32Ret = HI_UNF_DMX_SetChannelPID((HI_HANDLE)u32ChannelId, (HI_U32)u16Pid);
    }

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("dmx_channel_set_pid param error, u32ChannelId = %#x, u16Pid = %#x", u32ChannelId, u16Pid);
        DMX_UNLOCK();
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_SetChannelPID error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }
    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_channel_query(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32ChannelId, const U16 u16Pid)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);
    HAL_DMX_CHK_PARA(pu32ChannelId);

    if (u16Pid >= INVALID_PID)
    {
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_UNF_DMX_GetChannelHandle(enDemuxId, (HI_U32)u16Pid, pu32ChannelId);
    if (HI_ERR_DMX_UNMATCH_CHAN == s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetChannelHandle error ret = %#x \n ", s32Ret);
        return ERROR_DMX_UNMATCH_CHAN;
    }

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_channel_enable(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    s32Ret = HI_UNF_DMX_OpenChannel(u32ChannelId);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_OpenChannel error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }
    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_channel_disable(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    s32Ret = HI_UNF_DMX_CloseChannel(u32ChannelId);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CloseChannel error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_channel_reset(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId )
{
    HAL_DMX_CHK_INIT();

    // TODO:
    return ERROR_NOT_SUPPORTED;
}

S32 dmx_channel_get_info(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, DMX_CHANNEL_INFO_S* const pstInfo)
{
    S32 s32Ret = FAILURE;
    HI_U32 u32PID = 0;
    HI_UNF_DMX_CHAN_ATTR_S stChnAttr;
    HI_UNF_DMX_CHAN_STATUS_S stStatus;

    HI_UNF_DMX_PORT_PACKETNUM_S stTSPortPacketNum;
    HI_U32 u32PortId = 0;
    S32 i = 0;
    S32 j = 0;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstInfo);

    DMX_LOCK();
    const DMX_CHN_S* const pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    pstInfo->enDemuxId = pstDmxInfo->enDmxId;

    for (i = 0; i < DMX_CHANNEL_CALLBACK_MAX; i++)
    {
        if (NULL != pstDmxInfo->pstFunc[i].pfnCallback)
        {
            j++;
        }
    }

    pstInfo->u32CallbackNum = j;

    s32Ret = HI_UNF_DMX_GetChannelAttr(u32ChannelId, &stChnAttr);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetChannelAttr error ret = %#x \n ", s32Ret);
    }
    else
    {
        pstInfo->enType = dmxConvert2HalChnType(stChnAttr.enChannelType);
        pstInfo->u32Len = stChnAttr.u32BufSize;
    }

    s32Ret = HI_UNF_DMX_GetChannelPID(u32ChannelId, &u32PID);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetChannelAttr error ret = %#x \n ", s32Ret);
    }
    else
    {
        pstInfo->u16Pid = u32PID;
    }

    s32Ret = HI_UNF_DMX_GetChannelStatus(u32ChannelId, &stStatus);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetChannelAttr error ret = %#x \n ", s32Ret);
    }
    else
    {
        pstInfo->enStatus = dmxConvert2HalChnStatus(stStatus.enChanStatus);
    }

    s32Ret = HI_UNF_DMX_GetTSPortId( pstInfo->enDemuxId, (HI_UNF_DMX_PORT_E*)&u32PortId);

    s32Ret |= HI_UNF_DMX_GetTSPortPacketNum((HI_UNF_DMX_PORT_E)u32PortId, &stTSPortPacketNum);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetTSPortPacketNum error ret = %#x \n ", s32Ret);
    }
    else
    {
        pstInfo->u32PacketCount = stTSPortPacketNum.u32TsPackCnt;
    }

    pstInfo->u32FilterNum = 0;

    for (i = 0; i < DMX_FILTER_TOTAL; i++)
    {
        if (0 != pstDmxInfo->ahAttachedFilter[i])
        {
            pstInfo->u32FilterNum++;
        }
    }

    DMX_UNLOCK();
    return SUCCESS;
}

S32 dmx_channel_set(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_CHANNEL_SETTING_S* const pstSettings)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    // TODO:   u32AddData     u32Tag

    S32 s32Ret = FAILURE;
    HI_UNF_DMX_CHAN_ATTR_S stChnAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstSettings);

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    pstDmxInfo->enNotifyType = pstSettings->enNotifyType;

    s32Ret = HI_UNF_DMX_GetChannelAttr(u32ChannelId, &stChnAttr);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetChannelAttr error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return FAILURE;
    }

    stChnAttr.enCRCMode = dmxConvert2SdkCrcMode(pstSettings->u32IsCRC);

    /* The CRC mode can be changed dynamically. */
    s32Ret = HI_UNF_DMX_SetChannelAttr(u32ChannelId, &stChnAttr);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_SetChannelAttr error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return FAILURE;
    }

    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_channel_get(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, DMX_CHANNEL_SETTING_S* const pstSettings)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    // TODO:   u32AddData     u32Tag
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_CHAN_ATTR_S stChAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstSettings);

    DMX_LOCK();
    const DMX_CHN_S* const pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    pstSettings->enNotifyType = pstDmxInfo->enNotifyType;

    s32Ret = HI_UNF_DMX_GetChannelAttr(u32ChannelId, &stChAttr);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetChannelAttr error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return FAILURE;
    }

    pstSettings->u32IsCRC = dmxConvert2HalCrcMode(stChAttr.enCRCMode);
    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

#ifdef HAL_HISI_EXTEND_H
S32 dmx_channel_get_data_handle(struct _DEMUX_DEVICE_S* pstDev, U32* pu32ChannelId, U32* pu32ChNum, const U32 u32TimeoutMs)
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pu32ChannelId);
    HAL_DMX_CHK_PARA(pu32ChNum);

    s32Ret = HI_UNF_DMX_GetDataHandle(pu32ChannelId, pu32ChNum, u32TimeoutMs);

    if (HI_ERR_DMX_NOAVAILABLE_DATA == s32Ret)
    {
        return ERROR_DMX_NOAVAILABLE_DATA;
    }

    if (HI_ERR_DMX_TIMEOUT == s32Ret)
    {
        return ERROR_DMX_TIMEOUT;
    }

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        return ERROR_INVALID_PARAM;
    }

    return SUCCESS;
}
#endif

S32 dmx_channel_get_buf(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32 u32AcquirePackageNum, U32* pu32AcquiredNum, DMX_CHANNEL_DATA_S* pstChannelData, const U32 u32TimeoutMs )
{
    U32 i = 0;
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pu32AcquiredNum);
    HAL_DMX_CHK_PARA(pstChannelData);

    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK(pstDmxInfo);

    DMX_LOCK();

    s32Ret = HI_UNF_DMX_AcquireBuf(u32ChannelId, u32AcquirePackageNum, pu32AcquiredNum, (HI_UNF_DMX_DATA_S*)pstChannelData, u32TimeoutMs);

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID param . \n ");
        DMX_UNLOCK();
        return ERROR_INVALID_PARAM;
    }
    else if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_AcquireBuf error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    for (i = 0; i < *pu32AcquiredNum; i++)
    {
        pstChannelData[i].enDataType = dmxConvert2HalChnDataType((HI_UNF_DMX_DATA_TYPE_E)pstChannelData[i].enDataType);
    }

    DMX_UNLOCK();
    return SUCCESS;
}

S32 dmx_channel_release_buf(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32 u32ReleaseNum, DMX_CHANNEL_DATA_S* pstChannelData)
{
    U32 i = 0;
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstChannelData);

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    for (i = 0; i < u32ReleaseNum; i++)
    {
        pstChannelData[i].enDataType = (DMX_CHANNEL_DATA_TYPE_E)dmxConvert2SdkChnDataType(pstChannelData[i].enDataType);
    }

    s32Ret = HI_UNF_DMX_ReleaseBuf(u32ChannelId, u32ReleaseNum, (HI_UNF_DMX_DATA_S*)pstChannelData);

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_AcquireBuf param error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_INVALID_PARAM;
    }
    else if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_ReleaseBuf error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    DMX_UNLOCK();
    return SUCCESS;
}

S32 dmx_channel_register_callback(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_REG_CALLBACK_PARAMS_S* const pstReg)
{
    S32 i = 0;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstReg);

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    for (i = 0; i < DMX_CHANNEL_CALLBACK_MAX; i++)
    {
        if (NULL == pstDmxInfo->pstFunc[i].pfnCallback)
        {
            pstDmxInfo->pstFunc[i] = *pstReg;
            break;
        }
    }

    if (DMX_CHANNEL_CALLBACK_MAX == i)
    {
        DMX_LOG_ERROR("Can not register more callback. \n ");
        DMX_UNLOCK();
        return FAILURE;
    }

    DMX_UNLOCK();

    return SUCCESS;
}

S32 dmx_channel_config_callback(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_CALLBACK_PFN pfnCallback, const DMX_CFG_CALLBACK_E enCfg)
{
    S32 i = 0;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    for (i = 0; i < DMX_CHANNEL_CALLBACK_MAX; i++)
    {
        if (pfnCallback == pstDmxInfo->pstFunc[i].pfnCallback)
        {
            switch (enCfg)
            {
                case DMX_CALLBACK_ENABLE:
                    pstDmxInfo->pstFunc[i].u32IsDisable = 0;
                    break;

                case DMX_CALLBACK_DISABLE:
                    pstDmxInfo->pstFunc[i].u32IsDisable = 1;
                    break;

                case DMX_CALLBACK_REMOVE:
                    pstDmxInfo->pstFunc[i].pfnCallback = NULL;
                    break;

                default:
                    DMX_LOG_ERROR("enCfg error. enCfg = %d \n ", enCfg);
                    DMX_UNLOCK();
                    return FAILURE;
            }

            break;
        }
    }

    if (DMX_CHANNEL_CALLBACK_MAX == i)
    {
        DMX_LOG_ERROR("Can not find the callback. pfnCallback = %p. \n ", (void *)pfnCallback);
        DMX_UNLOCK();
        return FAILURE;
    }

    DMX_UNLOCK();

    return SUCCESS;
}

S32 dmx_channel_add_filter(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32* const pu32FilterId, const DMX_FILTER_DATA_S* const pstFilterData)
{
    // TODO: enFilterRepeatMode
    S32 s32Ret = FAILURE;
    S32 i = 0;
    HI_HANDLE hFilter = INVALID_HANDLE;
    HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pu32FilterId);
    HAL_DMX_CHK_PARA(pstFilterData);

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    dmxConvert2SdkFilterAttr(pstFilterData, &stFilterAttr);

    s32Ret = HI_UNF_DMX_CreateFilter(pstDmxInfo->enDmxId, &stFilterAttr, &hFilter);

    if (HI_ERR_DMX_NOFREE_FILTER == s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CreateFilter error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_NOFREE_FILTER;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CreateFilter error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    for (i = 0; i < DMX_FILTER_TOTAL; i++)
    {
        if (0 == pstDmxInfo->ahAttachedFilter[i])
        {
            pstDmxInfo->ahAttachedFilter[i] = hFilter;
            break;
        }
    }

    *pu32FilterId = hFilter;
    DMX_UNLOCK();
    return SUCCESS;
}

S32 dmx_channel_set_filter(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId, const DMX_FILTER_DATA_S* const pstFilterData)
{
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstFilterData);

    dmxConvert2SdkFilterAttr(pstFilterData, &stFilterAttr);

    s32Ret = HI_UNF_DMX_SetFilterAttr(u32FilterId, &stFilterAttr);

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_SetFilterAttr param invalid ret = %#x \n ", s32Ret);
        return ERROR_INVALID_PARAM;
    }
    else if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_SetFilterAttr error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_channel_get_filter(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId, DMX_FILTER_DATA_S* const pstFilterData)
{
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstFilterData);

    s32Ret = HI_UNF_DMX_GetFilterAttr(u32FilterId, &stFilterAttr);

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetFilterAttr param invalid ret = %#x \n ", s32Ret);
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetFilterAttr error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    dmxConvert2HalFilterAttr(&stFilterAttr, pstFilterData);

    return SUCCESS;
}

S32 dmx_channel_destroy_filter(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId)
{
    S32 s32Ret = FAILURE;
    S32 i = 0;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    for (i = 0; i < DMX_FILTER_TOTAL; i++)
    {
        if (u32FilterId == pstDmxInfo->ahAttachedFilter[i])
        {
            pstDmxInfo->ahAttachedFilter[i] = 0;
            break;
        }
    }

    DMX_UNLOCK();

    if (DMX_FILTER_TOTAL == i)
    {
        DMX_LOG_ERROR("filter id invalid %#x \n ", u32FilterId);
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_UNF_DMX_DestroyFilter(u32FilterId);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_DestroyFilter error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_channel_destroy_all_filter(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId)
{
    S32 s32Ret = FAILURE;
    S32 i = 0;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    for (i = 0; i < DMX_FILTER_TOTAL; i++)
    {
        if (0 != pstDmxInfo->ahAttachedFilter[i])
        {
            s32Ret = HI_UNF_DMX_DestroyFilter(pstDmxInfo->ahAttachedFilter[i]);

            if (SUCCESS != s32Ret)
            {
                DMX_LOG_ERROR("HI_UNF_DMX_DestroyFilter error, handle = %#x, ret = %#x \n ", pstDmxInfo->ahAttachedFilter[i], s32Ret);
            }

            pstDmxInfo->ahAttachedFilter[i] = 0;
        }
    }

    DMX_UNLOCK();
    return SUCCESS;
}

S32 dmx_channel_enable_filter(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId)
{
    S32 s32Ret = FAILURE;
    HI_HANDLE hAttachedChn = INVALID_HANDLE;

    HAL_DMX_CHK_INIT();

    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK(pstDmxInfo);

    s32Ret = HI_UNF_DMX_GetFilterChannelHandle(u32FilterId, &hAttachedChn);
    if ((SUCCESS == s32Ret) && (hAttachedChn == u32ChannelId))
    {
        return SUCCESS;
    }

    s32Ret = HI_UNF_DMX_AttachFilter(u32FilterId, u32ChannelId);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_AttachFilter error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_channel_disable_filter(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId)
{
    S32 s32Ret = FAILURE;
    HI_HANDLE hAttachedChn = HI_INVALID_HANDLE;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    s32Ret = HI_UNF_DMX_GetFilterChannelHandle(u32FilterId, &hAttachedChn);
    if (HI_ERR_DMX_NOATTACH_FILTER == s32Ret)
    {
        DMX_UNLOCK();
        return SUCCESS;
    }

    s32Ret = HI_UNF_DMX_DetachFilter(u32FilterId, u32ChannelId);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_DetachFilter error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }
    DMX_UNLOCK();

    return SUCCESS;
}

S32 dmx_channel_query_filter_by_table_id(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32* const pu32FilterId, const U8 u8TableId, const U16 u16ExtId)
{
    // TODO: u16ExtId
    S32 s32Ret = FAILURE;
    S32 i = 0;
    HI_UNF_DMX_FILTER_ATTR_S stFilterAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pu32FilterId);

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32ChannelId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    for (i = 0; i < DMX_FILTER_TOTAL; i++)
    {
        if (0 != pstDmxInfo->ahAttachedFilter[i])
        {
            s32Ret = HI_UNF_DMX_GetFilterAttr(pstDmxInfo->ahAttachedFilter[i], &stFilterAttr);

            if (SUCCESS != s32Ret)
            {
                continue;
            }

            if ((0 != stFilterAttr.u32FilterDepth) && (stFilterAttr.au8Match[0] == u8TableId))
            {
                *pu32FilterId = pstDmxInfo->ahAttachedFilter[i];
                DMX_UNLOCK();
                return SUCCESS;
            }
        }
    }

    DMX_UNLOCK();
    return FAILURE;
}

S32 dmx_channel_query_filter_by_filter_data(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32* const pu32FilterId, const DMX_FILTER_DATA_S* const pstFilterData)
{
    HAL_DMX_CHK_INIT();
    return ERROR_NOT_SUPPORTED;
}

S32 dmx_descrambler_open(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32DescId, const DMX_DESC_ASSOCIATE_MODE_E enMode)
{
    S32 s32Ret = FAILURE;
    HI_HANDLE hKey = INVALID_HANDLE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);
    HAL_DMX_CHK_PARA(pu32DescId);

    DESCRAM_LOCK();
    s32Ret = HI_UNF_DMX_CreateDescrambler(enDemuxId, &hKey);
    if (SUCCESS != s32Ret)
    {
        DESCRAM_UNLOCK();
        DMX_LOG_ERROR("HI_UNF_DMX_CreateDescrambler error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    *pu32DescId = hKey;
    dmxNewKeyInfo(enDemuxId, hKey, enMode);
    DESCRAM_UNLOCK();

    return SUCCESS;
}

S32 dmx_descrambler_open_ex(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32DescId, const DMX_DESCRAMBLER_ATTR_S* pstDesramblerAttr)
{
    // TODO:

    S32 s32Ret = SUCCESS;
    HI_UNF_DMX_DESCRAMBLER_ATTR_S stDesramblerAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);
    HAL_DMX_CHK_PARA(pu32DescId);
    HAL_DMX_CHK_PARA(pstDesramblerAttr);

    stDesramblerAttr.enCaType = (HI_UNF_DMX_CA_TYPE_E)pstDesramblerAttr->enCaType;
    stDesramblerAttr.enDescramblerType  = dmxConvert2SdkDescramblerType(pstDesramblerAttr->enDescramblerType);
    stDesramblerAttr.enEntropyReduction = (HI_UNF_DMX_CA_ENTROPY_E)pstDesramblerAttr->enEntropyReduction;

    DESCRAM_LOCK();
    s32Ret = HI_UNF_DMX_CreateDescramblerExt(enDemuxId, &stDesramblerAttr, pu32DescId);
    if (SUCCESS != s32Ret)
    {
        DESCRAM_UNLOCK();
        DMX_LOG_ERROR("HI_UNF_DMX_CreateDescramblerExt error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    dmxNewKeyInfo(enDemuxId, *pu32DescId, DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNEL);
    DESCRAM_UNLOCK();

    return SUCCESS;
}

S32 dmx_descrambler_enable(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId )
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    DESCRAM_LOCK();
    DMX_KEY_S* pstDmxKeyInfo = dmxGetKeyInfoByDesc(u32DescId);
    HAL_DMX_CHK_PARA_UNLOCK(pstDmxKeyInfo, DESCRAM_UNLOCK());

    s32Ret = HI_UNF_DMX_AttachDescrambler(u32DescId, pstDmxKeyInfo->hChn);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_AttachDescrambler error ret = %#x \n ", s32Ret);
        DESCRAM_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    DESCRAM_UNLOCK();
    return SUCCESS;
}

S32 dmx_descrambler_disable(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId )
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    DESCRAM_LOCK();
    DMX_KEY_S* pstDmxKeyInfo = dmxGetKeyInfoByDesc(u32DescId);

    HAL_DMX_CHK_PARA_UNLOCK(pstDmxKeyInfo, DESCRAM_UNLOCK());
    s32Ret = HI_UNF_DMX_DetachDescrambler(u32DescId, pstDmxKeyInfo->hChn);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_DetachDescrambler error ret = %#x \n ", s32Ret);
        DESCRAM_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    DESCRAM_UNLOCK();
    return SUCCESS;
}

S32 dmx_descrambler_close(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId)
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    DESCRAM_LOCK();

    s32Ret = HI_UNF_DMX_DestroyDescrambler(u32DescId);
    if (SUCCESS != s32Ret)
    {
        DESCRAM_UNLOCK();
        DMX_LOG_ERROR("HI_UNF_DMX_DestroyDescrambler error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    dmxDelKeyInfo(u32DescId);
    DESCRAM_UNLOCK();

    return SUCCESS;
}

S32 dmx_descrambler_associate(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DESC_ASSOCIATE_PARAMS_S* const pstParams )
{
    S32 s32Ret = FAILURE;
    HI_HANDLE hChn = INVALID_HANDLE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstParams);

    DESCRAM_LOCK();

    DMX_KEY_S *pstDmxKeyInfo = dmxGetKeyInfoByDesc(u32DescId);
    HAL_DMX_CHK_PARA_UNLOCK(pstDmxKeyInfo, DESCRAM_UNLOCK());

    switch (pstParams->enMode)
    {
        case DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDS:
            s32Ret = HI_UNF_DMX_GetChannelHandle(pstDmxKeyInfo->enDmxId, pstParams->DMX_ASSOCIATE_U.u16Pid, &hChn);

            if (SUCCESS != s32Ret)
            {
                DMX_LOG_ERROR("HI_UNF_DMX_GetChannelHandle error ret = %#x \n ", s32Ret);
            }
            else
            {
                pstDmxKeyInfo->hChn = hChn;
                pstDmxKeyInfo->stAssocviateInfo = *pstParams;
            }

            break;

        case DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNEL:
            pstDmxKeyInfo->hChn = pstParams->DMX_ASSOCIATE_U.u32ChannelId;
            pstDmxKeyInfo->stAssocviateInfo = *pstParams;
            break;

        default:
            DESCRAM_UNLOCK();
            return FAILURE;
    }

    DESCRAM_UNLOCK();

    return SUCCESS;
}

S32 dmx_descrambler_dissociate(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DESC_ASSOCIATE_PARAMS_S* const pstParams )
{
    S32 s32Ret = FAILURE;
    HI_HANDLE hChn = INVALID_HANDLE;
    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstParams);

    DESCRAM_LOCK();
    DMX_KEY_S* pstDmxKeyInfo = dmxGetKeyInfoByDesc(u32DescId);
    HAL_DMX_CHK_PARA_UNLOCK(pstDmxKeyInfo, DESCRAM_UNLOCK());

    switch (pstParams->enMode)
    {
        case DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDS:
            s32Ret = HI_UNF_DMX_GetChannelHandle(pstDmxKeyInfo->enDmxId, pstParams->DMX_ASSOCIATE_U.u16Pid, &hChn);

            if (SUCCESS != s32Ret)
            {
                DMX_LOG_ERROR("HI_UNF_DMX_GetChannelHandle error ret = %#x \n ", s32Ret);
            }
            else
            {
                pstDmxKeyInfo->hChn = hChn;
                pstDmxKeyInfo->stAssocviateInfo = *pstParams;
            }

            break;

        case DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNEL:
            pstDmxKeyInfo->hChn = pstParams->DMX_ASSOCIATE_U.u32ChannelId;
            pstDmxKeyInfo->stAssocviateInfo = *pstParams;
            break;

        default:
            DESCRAM_UNLOCK();
            return FAILURE;
    }

    DESCRAM_UNLOCK();

    return SUCCESS;
}

S32 dmx_descrambler_get_associate_info(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, DMX_DESC_ASSOCIATE_PARAMS_S* const pstParams)
{
    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstParams);

    DESCRAM_LOCK();
    DMX_KEY_S* pstDmxKeyInfo = dmxGetKeyInfoByDesc(u32DescId);
    HAL_DMX_CHK_PARA_UNLOCK(pstDmxKeyInfo, DESCRAM_UNLOCK());

    *pstParams = pstDmxKeyInfo->stAssocviateInfo;
    DESCRAM_UNLOCK();

    return SUCCESS;
}

S32 dmx_descrambler_set_even_key(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8Key, const U32 u32Len, const U32 u32Option )
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pu8Key);

    if  (0 == u32Len)
    {
        DMX_LOG_ERROR("Invalid u32Len:%d\n ", u32Len);
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_UNF_DMX_SetDescramblerEvenKey(u32DescId, pu8Key);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_SetDescramblerEvenKey error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_descrambler_set_odd_key(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8Key, const U32 u32Len, const U32 u32Option )
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pu8Key);

    if  (0 == u32Len)
    {
        DMX_LOG_ERROR("Invalid u32Len:%d\n ", u32Len);
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_UNF_DMX_SetDescramblerOddKey(u32DescId, pu8Key);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_SetDescramblerOddKey error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_set_descrambler_attribute(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, DMX_DESCRAMBLER_ATTR_S* pstAttr )
{
    // TODO:
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_DESCRAMBLER_ATTR_S stDesramblerAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstAttr);

    stDesramblerAttr.enCaType = (HI_UNF_DMX_CA_TYPE_E)pstAttr->enCaType;
    stDesramblerAttr.enDescramblerType  = dmxConvert2SdkDescramblerType(pstAttr->enDescramblerType);
    stDesramblerAttr.enEntropyReduction = (HI_UNF_DMX_CA_ENTROPY_E)pstAttr->enEntropyReduction;

    s32Ret = HI_UNF_DMX_SetDescramblerAttr(u32DescId, &stDesramblerAttr);
    if (HI_SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("set descrambler attr error ret = 0x%x", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_get_descrambler_attribute(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, DMX_DESCRAMBLER_ATTR_S* pstAttr )
{
    // TODO:
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_DESCRAMBLER_ATTR_S stDesramblerAttr;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstAttr);

    s32Ret = HI_UNF_DMX_GetDescramblerAttr(u32DescId, &stDesramblerAttr);
    if (HI_SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("set descrambler attr error ret = 0x%x", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    pstAttr->enCaType = (DMX_DESCRAMBLER_TYPE_E)stDesramblerAttr.enCaType;
    pstAttr->enDescramblerType  = dmxConvert2HalDescramblerType(stDesramblerAttr.enDescramblerType);
    pstAttr->enEntropyReduction = (DMX_CA_ENTROPY_E)stDesramblerAttr.enEntropyReduction;

    return SUCCESS;
}

//add by sdk
S32 dmx_dcas_keyladder_config(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DCAS_KEYLADDER_SETTING_S* pstDcasKLConfig)
{
#if defined(CA_FRAMEWORK_V200_SUPPORT)

    DMX_LOG_ERROR("CA FrameWork V200 not support!\n");
    return ERROR_NOT_SUPPORTED;

#else

    S32 s32Ret = FAILURE;
    U8 u8OutputBuf[DMX_CA_VID_LEN] = {0};
    U8 u8CAVid[DMX_CA_VID_LEN] = {0};
    HI_UNF_CIPHER_ALG_E enAlg;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstDcasKLConfig);

    if (DMX_KL_ALG_TDES == pstDcasKLConfig->enKLAlg)
    {
        enAlg = HI_UNF_CIPHER_ALG_3DES;
    }
    else if (DMX_KL_ALG_AES == pstDcasKLConfig->enKLAlg)
    {
        enAlg = HI_UNF_CIPHER_ALG_AES;
    }
    else
    {
        DMX_LOG_ERROR("Invalid Dcas KL alg 0x%x\n ", pstDcasKLConfig->enKLAlg);
        return FAILURE;
    }

    DESCRAM_LOCK();

    //Set the algorithm to TDES or AES
    s32Ret = HI_UNF_ADVCA_DCASOpen(enAlg);

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_DCASOpen error ret = %#x \n ", s32Ret);
        DESCRAM_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    //Set Vendor ID
    memset(u8CAVid, 0, DMX_CA_VID_LEN);
    u8CAVid[0] = (unsigned char)(pstDcasKLConfig->u32CAVid & 0xFF);
    u8CAVid[1] = (unsigned char)((pstDcasKLConfig->u32CAVid >> 16) & 0xFF);
    s32Ret = HI_UNF_ADVCA_SetDCASSessionKey(HI_UNF_ADVCA_DCAS_KEYLADDER_VENDORSYSID, u8CAVid, u8OutputBuf);

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_SetDCASSessionKey set vendor id error ret = %#x \n ", s32Ret);
        HI_UNF_ADVCA_DCASClose();
        DESCRAM_UNLOCK();
        return FAILURE;
    }

    //Set EK2
    s32Ret = HI_UNF_ADVCA_SetDCASSessionKey(HI_UNF_ADVCA_DCAS_KEYLADDER_EK2, pstDcasKLConfig->pu8EK2, u8OutputBuf);

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_SetDCASSessionKey set EK2 error ret = %#x \n ", s32Ret);
        HI_UNF_ADVCA_DCASClose();
        DESCRAM_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    //Set EK1
    s32Ret = HI_UNF_ADVCA_SetDCASSessionKey(HI_UNF_ADVCA_DCAS_KEYLADDER_EK1, pstDcasKLConfig->pu8EK1, u8OutputBuf);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_SetDCASSessionKey set EK1 error ret = %#x \n ", s32Ret);
        HI_UNF_ADVCA_DCASClose();
        DESCRAM_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    if(NULL != pstDcasKLConfig->pu8EvenKey)
    {
        s32Ret = HI_UNF_DMX_SetDescramblerEvenKey(u32DescId, pstDcasKLConfig->pu8EvenKey);
        if (SUCCESS != s32Ret)
        {
            DMX_LOG_ERROR("HI_UNF_DMX_SetDescramblerEvenKey error ret = %#x \n ", s32Ret);
            HI_UNF_ADVCA_DCASClose();
            DESCRAM_UNLOCK();
            return FAILURE;
        }
    }

    if(NULL != pstDcasKLConfig->pu8OddKey)
    {
        s32Ret = HI_UNF_DMX_SetDescramblerOddKey(u32DescId, pstDcasKLConfig->pu8OddKey);
        if (SUCCESS != s32Ret)
        {
            DMX_LOG_ERROR("HI_UNF_DMX_SetDescramblerOddKey error ret = %#x \n ", s32Ret);
            HI_UNF_ADVCA_DCASClose();
            DESCRAM_UNLOCK();
            return FAILURE;
        }
    }

    s32Ret = HI_UNF_ADVCA_DCASClose();
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_DCASClose error ret = %#x \n ", s32Ret);
        DESCRAM_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    DESCRAM_UNLOCK();
    return SUCCESS;
#endif

}

S32 dmx_dcas_get_nonce(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DCAS_NONCE_SETTING_S* pstDcasNonceConfig, U8* pu8DANonce)
{
#if defined(CA_FRAMEWORK_V200_SUPPORT)

    DMX_LOG_ERROR("CA FrameWork V200 not support!\n");
    return ERROR_NOT_SUPPORTED;

#else

    S32 s32Ret = FAILURE;
    U8 u8OutputBuf[DMX_CA_VID_LEN] = {0};
    U8 u8CAVid[DMX_CA_VID_LEN] = {0};
    HI_UNF_CIPHER_ALG_E enAlg = HI_UNF_CIPHER_ALG_BUTT;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstDcasNonceConfig);
    HAL_DMX_CHK_PARA(pu8DANonce);

    if (DMX_KL_ALG_TDES == pstDcasNonceConfig->enKLAlg)
    {
        enAlg = HI_UNF_CIPHER_ALG_3DES;
    }
    else if (DMX_KL_ALG_AES == pstDcasNonceConfig->enKLAlg)
    {
        enAlg = HI_UNF_CIPHER_ALG_AES;
    }
    else
    {
        DMX_LOG_ERROR("Invalid Dcas KL alg 0x%x\n ", pstDcasNonceConfig->enKLAlg);
        return ERROR_INVALID_PARAM;
    }

    //Set the algorithm to TDES or AES
    s32Ret = HI_UNF_ADVCA_DCASOpen(enAlg);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_DCASOpen error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    //Set Vendor ID
    memset(u8CAVid, 0, sizeof(u8CAVid));
    memcpy(u8CAVid, (HI_U8*)&pstDcasNonceConfig->u32CAVid, sizeof(U32));

    s32Ret = HI_UNF_ADVCA_SetDCASSessionKey(HI_UNF_ADVCA_DCAS_KEYLADDER_VENDORSYSID, u8CAVid, u8OutputBuf);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_SetDCASSessionKey set vendor id error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    //Set EK2
    s32Ret = HI_UNF_ADVCA_SetDCASSessionKey(HI_UNF_ADVCA_DCAS_KEYLADDER_EK2, pstDcasNonceConfig->pu8EK2, u8OutputBuf);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_SetDCASSessionKey set EK2 error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    //set nonce
    s32Ret = HI_UNF_ADVCA_SetDCASSessionKey(HI_UNF_ADVCA_DCAS_KEYLADDER_NONCE, pstDcasNonceConfig->pu8Nonce, pu8DANonce);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_SetDCASSessionKey set EK1 error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    s32Ret = HI_UNF_ADVCA_DCASClose();
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_DCASClose error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
#endif
}

S32 dmx_descrambler_set_even_iv(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8IV, const U32 u32Len)
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pu8IV);

    if  (0 == u32Len)
    {
        DMX_LOG_ERROR("Invalid u32Len:%d\n ", u32Len);
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_UNF_DMX_SetDescramblerEvenIVKey(u32DescId, pu8IV);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_SetDescramblerEvenIVKey error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_descrambler_set_odd_iv(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8IV, const U32 u32Len)
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pu8IV);

    if  (0 == u32Len)
    {
        DMX_LOG_ERROR("Invalid u32Len:%d\n ", u32Len);
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_UNF_DMX_SetDescramblerOddIVKey(u32DescId, pu8IV);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_SetDescramblerOddIVKey error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

//add end

S32 dmx_avfilter_open(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32AVFilterId, const DMX_PARSER_FILTER_OPEN_PARAM_S* const pstFilterOpenPara)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_CHAN_ATTR_S stChnAttr;
    HI_HANDLE hChn = INVALID_HANDLE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);
    HAL_DMX_CHK_PARA(pu32AVFilterId);
    HAL_DMX_CHK_PARA(pstFilterOpenPara);

    memset(&stChnAttr, 0x0, sizeof(HI_UNF_DMX_CHAN_ATTR_S));

    s32Ret = HI_UNF_DMX_GetChannelDefaultAttr(&stChnAttr);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetChannelDefaultAttr error ret = %#x \n ", s32Ret);
    }

    stChnAttr.enOutputMode = HI_UNF_DMX_CHAN_OUTPUT_MODE_PLAY;

    if (DMX_VIDEO_CHANNEL == pstFilterOpenPara->enType)
    {
        stChnAttr.enChannelType = HI_UNF_DMX_CHAN_TYPE_VID;
        stChnAttr.u32BufSize = DMX_VID_BUF;
    }
    else if (DMX_AUDIO_CHANNEL == pstFilterOpenPara->enType)
    {
        stChnAttr.enChannelType = HI_UNF_DMX_CHAN_TYPE_AUD;
        stChnAttr.u32BufSize = DMX_AUD_BUF;
    }
    else
    {
        DMX_LOG_ERROR("Param error.");
        return ERROR_INVALID_PARAM;
    }

    if (INVALID_PID == pstFilterOpenPara->u32Pid)
    {
        DMX_LOG_ERROR("pid invalid .");
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_UNF_DMX_CreateChannel(enDemuxId, &stChnAttr, &hChn);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CreateChannel error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    s32Ret = HI_UNF_DMX_SetChannelPID(hChn, pstFilterOpenPara->u32Pid);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_SetChannelPID error ret = %#x \n ", s32Ret);
        s32Ret = HI_UNF_DMX_DestroyChannel(hChn);
        if(SUCCESS != s32Ret)
        {
             DMX_LOG_ERROR("HI_UNF_DMX_DestroyChannel error ret = %#x \n ", s32Ret);
        }
        return ERROR_DMX_OP_FAILED;
    }

    *pu32AVFilterId = hChn;

    DMX_LOCK();
    dmxNewChnInfo(enDemuxId, NULL, hChn);
    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] *pu32AVFilterId = 0x%x\n",__FUNCTION__,__LINE__,*pu32AVFilterId );
    return SUCCESS;
}

S32 dmx_avfilter_enable(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId)
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32AVFilterId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    s32Ret = HI_UNF_DMX_OpenChannel(u32AVFilterId);
    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID AVFilterId = %#x \n", u32AVFilterId);
        DMX_UNLOCK();
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_OpenChannel error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    DMX_UNLOCK();
    return SUCCESS;
}

S32 dmx_avfilter_get_esframe(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId, DMX_ESFRAME_INFO_S* pstFrameInfo)
{
    S32 s32Ret = FAILURE;
    HI_UNF_ES_BUF_S stEsBuf;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstFrameInfo);

    // TODO:需要SDK提供接口
    s32Ret = HI_UNF_DMX_AcquireEs(u32AVFilterId, &stEsBuf);
    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID AVFilterId = %#x \n", u32AVFilterId);
        return ERROR_INVALID_PARAM;
    }

    if (HI_ERR_DMX_NOT_SUPPORT == s32Ret)
    {
        DMX_LOG_ERROR("not support = %#x \n", s32Ret);
        return ERROR_NOT_SUPPORTED;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_AcquireEs error ret = %#x \n", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    pstFrameInfo->u64BufferAddr = (U64)((size_t)stEsBuf.pu8Buf);
    pstFrameInfo->u32Lenght = stEsBuf.u32BufLen;
    pstFrameInfo->u64Timestamp = stEsBuf.u32PtsMs;

    return SUCCESS;
}

S32 dmx_avfilter_release_esframe(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId, DMX_ESFRAME_INFO_S* pstFrameInfo)
{
    S32 s32Ret = FAILURE;
    HI_UNF_ES_BUF_S stEsBuf;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstFrameInfo);

    memset(&stEsBuf, 0x0, sizeof(HI_UNF_ES_BUF_S));

    stEsBuf.pu8Buf = (HI_U8*)((size_t)pstFrameInfo->u64BufferAddr);
    stEsBuf.u32BufLen = pstFrameInfo->u32Lenght;
    stEsBuf.u32PtsMs = pstFrameInfo->u64Timestamp;

    // TODO:需要SDK提供接口
    s32Ret = HI_UNF_DMX_ReleaseEs(u32AVFilterId, &stEsBuf);

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID AVFilterId = %#x \n", u32AVFilterId);
        return ERROR_INVALID_PARAM;
    }

    if (HI_ERR_DMX_NOT_SUPPORT == s32Ret)
    {
        DMX_LOG_ERROR("not support = %#x \n", s32Ret);
        return ERROR_NOT_SUPPORTED;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_ReleaseEs error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_avfilter_disable(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId)
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32AVFilterId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    s32Ret = HI_UNF_DMX_CloseChannel(u32AVFilterId);
    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID AVFilterId = %#x \n", u32AVFilterId);
        DMX_UNLOCK();
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CloseChannel error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    DMX_UNLOCK();
    return SUCCESS;
}

S32 dmx_avfilter_close(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId)
{
    DMX_LOG_ERROR("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();
    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32AVFilterId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    s32Ret = HI_UNF_DMX_DestroyChannel(u32AVFilterId);
    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID AVFilterId = %#x \n", u32AVFilterId);
        DMX_UNLOCK();
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_DestroyChannel error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    dmxDelChnInfo(u32AVFilterId);
    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}


S32 dmx_pcr_open(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32PcrId, const U32 u32Pid)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = FAILURE;
    HI_HANDLE hChn = INVALID_HANDLE;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);
    HAL_DMX_CHK_PARA(pu32PcrId);

    if (u32Pid >= INVALID_PID)
    {
        DMX_LOG_ERROR("INVALID PID = %#x \n ", u32Pid);
        return ERROR_INVALID_PARAM;
    }

    s32Ret = HI_MPI_DMX_CreatePcrChannel((HI_U32)enDemuxId, &hChn);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_MPI_DMX_CreatePcrChannel error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    s32Ret = HI_MPI_DMX_PcrPidSet(hChn, u32Pid);
    if (SUCCESS != s32Ret)
    {
        HI_MPI_DMX_DestroyPcrChannel(hChn);
        DMX_LOG_ERROR("HI_MPI_DMX_PcrPidSet error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    *pu32PcrId = hChn;

     DMX_LOCK();
     dmxNewChnInfo(enDemuxId, NULL, hChn);
     DMX_UNLOCK();

     DMX_LOG_INFO("[%s][%d] *pu32PcrId = 0x%x\n",__FUNCTION__,__LINE__ ,*pu32PcrId);
     return SUCCESS;
}

S32 dmx_pcr_close(struct _DEMUX_DEVICE_S* pstDev, const U32 u32PcrId)
{
    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32PcrId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    // TODO: SDK需要提供接口
    s32Ret = HI_MPI_DMX_DestroyPcrChannel(u32PcrId);
    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID PCR ID = %#x \n", u32PcrId);
        DMX_UNLOCK();
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_MPI_DMX_DestroyPcrChannel error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    dmxDelChnInfo(u32PcrId);
    DMX_UNLOCK();

    DMX_LOG_INFO("[%s][%d] \n",__FUNCTION__,__LINE__ );
    return SUCCESS;
}

S32 dmx_pcr_get(struct _DEMUX_DEVICE_S* pstDev, const U32 u32PcrId, U64* pu64StcTime)
{
    S32 s32Ret = FAILURE;
    HI_U64 u64ScrMs;

    HAL_DMX_CHK_INIT();

    HAL_DMX_CHK_PARA(pu64StcTime);
    DMX_LOCK();
    DMX_CHN_S* pstDmxInfo = dmxGetChnInfo(u32PcrId);
    DMX_CHECK_AND_UNLOCK(pstDmxInfo);

    // TODO: SDK需要提供接口
    s32Ret = HI_MPI_DMX_PcrScrGet(u32PcrId, pu64StcTime, &u64ScrMs);
    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID PCR ID = %#x \n", u32PcrId);
        DMX_UNLOCK();
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_MPI_DMX_PcrScrGet error ret = %#x \n ", s32Ret);
        DMX_UNLOCK();
        return ERROR_DMX_OP_FAILED;
    }

    DMX_UNLOCK();
    return SUCCESS;
}

S32 dmx_tsbuffer_create(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32TsBufferId)
{
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_PORT_E enPort;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);
    HAL_DMX_CHK_PARA(pu32TsBufferId);

    s32Ret = HI_UNF_DMX_GetTSPortId(enDemuxId, &enPort);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetTSPortId error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    s32Ret = HI_UNF_DMX_CreateTSBuffer(enPort, 0x200000, pu32TsBufferId);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CreateTSBuffer error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_tsbuffer_get(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId, U32 u32Size, U32 u32TimeoutMs, DMX_STREAM_DATA_S* pstStreamData)
{
    S32 s32Ret = FAILURE;
    HI_UNF_STREAM_BUF_S stStreamBuf;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstStreamData);

    s32Ret = HI_UNF_DMX_GetTSBuffer(u32TsBufferId, u32Size, &stStreamBuf, u32TimeoutMs);

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID TsBufferId = %#x\n", u32TsBufferId);
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetTSBuffer error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    pstStreamData->pu8Data   = stStreamBuf.pu8Data;
    pstStreamData->u32Length = stStreamBuf.u32Size;

    return SUCCESS;
}

S32 dmx_tsbuffer_put(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId, U32 u32ValidDataLen)
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    s32Ret = HI_UNF_DMX_PutTSBuffer(u32TsBufferId, u32ValidDataLen);

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID TsBufferId = %#x\n", u32TsBufferId);
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_PutTSBuffer error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_tsbuffer_destroy(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId)
{
    S32 s32Ret = FAILURE;

    HAL_DMX_CHK_INIT();

    s32Ret = HI_UNF_DMX_DestroyTSBuffer(u32TsBufferId);

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID TsBufferId = %#x\n", u32TsBufferId);
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_DestroyTSBuffer error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;
}

S32 dmx_tsbuffer_create_ex(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, DMX_TSBUF_ATTR_S* pstBufAttr, U32* const pu32TsBufferId)
{
    S32 s32Ret = FAILURE;
    HI_UNF_DMX_PORT_E enPort;
    HI_UNF_DMX_TSBUF_ATTR_S stTsBufAttr = {0};

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_DMX_ID(enDemuxId);
    HAL_DMX_CHK_PARA(pstBufAttr);
    HAL_DMX_CHK_PARA(pu32TsBufferId);

    memset(&stTsBufAttr, 0x0, sizeof(stTsBufAttr));

    s32Ret = HI_UNF_DMX_GetTSPortId(enDemuxId, &enPort);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetTSPortId error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    if (DMX_SECURE_MODE_NONE == pstBufAttr->enSecureMode)
    {
        stTsBufAttr.enSecureMode = HI_UNF_DMX_SECURE_MODE_NONE;
    }
    else if (DMX_SECURE_MODE_TEE == pstBufAttr->enSecureMode)
    {
        stTsBufAttr.enSecureMode = HI_UNF_DMX_SECURE_MODE_TEE;
    }
    else
    {
        return ERROR_INVALID_PARAM;
    }

    stTsBufAttr.u32BufSize = pstBufAttr->u32BufSize;

    s32Ret = HI_UNF_DMX_CreateTSBufferExt(enPort, &stTsBufAttr, pu32TsBufferId);
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_CreateTSBuffer error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    return SUCCESS;

}

S32 dmx_tsbuffer_get_ex(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId, U32 u32Size, U32 u32TimeoutMs, DMX_STREAM_DATA_S* pstStreamData, U32 *pu32PhyAddr)
{
    S32 s32Ret = FAILURE;
    HI_UNF_STREAM_BUF_S stStreamBuf;

    HAL_DMX_CHK_INIT();
    HAL_DMX_CHK_PARA(pstStreamData);
    HAL_DMX_CHK_PARA(pu32PhyAddr);

    s32Ret = HI_UNF_DMX_GetTSBufferEx(u32TsBufferId, u32Size, &stStreamBuf, pu32PhyAddr, u32TimeoutMs);

    if (HI_ERR_DMX_INVALID_PARA == s32Ret)
    {
        DMX_LOG_ERROR("INVALID TsBufferId = %#x\n", u32TsBufferId);
        return ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_DMX_GetTSBuffer error ret = %#x \n ", s32Ret);
        return ERROR_DMX_OP_FAILED;
    }

    pstStreamData->pu8Data   = stStreamBuf.pu8Data;
    pstStreamData->u32Length = stStreamBuf.u32Size;

    return SUCCESS;
}

S32 dmx_get_streampath_param(struct _DEMUX_DEVICE_S *pstDev, DMX_ID_E enDemuxId, UCHAR  *pStreamPath, S32 *pStreamPathLength)
{
        return ERROR_NOT_SUPPORTED;
}

#ifdef TVOS_PLATFORM
static int dmx_device_close(struct hw_device_t *pstDev)
{
    struct _DEMUX_DEVICE_S* pCtx = (struct _DEMUX_DEVICE_S*)pstDev;

    if (pCtx)
    {
        free(pCtx);
        pCtx = NULL;
    }

    return 0;
}

static int dmx_device_open(const struct hw_module_t* module, const char* name,
                           struct hw_device_t** device)
{
    S32 s32Ret = FAILURE;

    if (strcmp(name, DEMUX_HARDWARE_DEMUX0) != 0)
    {
        return -EINVAL;
    }

    if (NULL == device)
    {
        return -EINVAL;
    }

    DEMUX_DEVICE_S *pstDev = (DEMUX_DEVICE_S*)malloc(sizeof(DEMUX_DEVICE_S));
    if (NULL == pstDev)
    {
        HAL_ERROR("malloc memory failed! ");
        return -ENOMEM;
    }

    s32Ret = HI_UNF_ADVCA_Init();
    if (SUCCESS != s32Ret)
    {
        DMX_LOG_ERROR("HI_UNF_ADVCA_Init error ret = %#x \n ", s32Ret);
    }

    /* initialize our state here */
    memset(pstDev, 0, sizeof(DEMUX_DEVICE_S));

    /* initialize the procs */
    pstDev->stCommon.tag = HARDWARE_DEVICE_TAG;
    pstDev->stCommon.version = DEMUX_DEVICE_API_VERSION_1_0;
    pstDev->stCommon.module = (hw_module_t*)module;
    pstDev->stCommon.close = dmx_device_close;

    /* register the callbacks */
    pstDev->dmx_init = dmx_init;
    pstDev->dmx_term = dmx_term;
    pstDev->dmx_set_source_params = dmx_set_source_params;
    pstDev->dmx_get_source_params = dmx_get_source_params;
    pstDev->dmx_disconnect = dmx_disconnect;
    pstDev->dmx_reconnect = dmx_reconnect;
    pstDev->dmx_get_capability = dmx_get_capability;
    pstDev->dmx_get_status       = dmx_get_status;
    pstDev->dmx_channel_open     = dmx_channel_open;
    pstDev->dmx_channel_close    = dmx_channel_close;
    pstDev->dmx_channel_set_pid  = dmx_channel_set_pid;
    pstDev->dmx_channel_query    = dmx_channel_query;
    pstDev->dmx_channel_enable   = dmx_channel_enable;
    pstDev->dmx_channel_disable  = dmx_channel_disable;
    pstDev->dmx_channel_reset    = dmx_channel_reset;
    pstDev->dmx_channel_get_info = dmx_channel_get_info;
    pstDev->dmx_channel_set      = dmx_channel_set;
    pstDev->dmx_channel_get      = dmx_channel_get;
    pstDev->dmx_channel_get_buf  = dmx_channel_get_buf;
    pstDev->dmx_channel_release_buf = dmx_channel_release_buf;
    pstDev->dmx_channel_register_callback = dmx_channel_register_callback;
    pstDev->dmx_channel_config_callback = dmx_channel_config_callback;
    pstDev->dmx_channel_add_filter = dmx_channel_add_filter;
    pstDev->dmx_channel_set_filter = dmx_channel_set_filter;
    pstDev->dmx_channel_get_filter = dmx_channel_get_filter;
    pstDev->dmx_channel_destroy_filter = dmx_channel_destroy_filter;
    pstDev->dmx_channel_destroy_all_filter = dmx_channel_destroy_all_filter;
    pstDev->dmx_channel_enable_filter  = dmx_channel_enable_filter;
    pstDev->dmx_channel_disable_filter = dmx_channel_disable_filter;
    pstDev->dmx_channel_query_filter_by_table_id = dmx_channel_query_filter_by_table_id;
    pstDev->dmx_channel_query_filter_by_filter_data = dmx_channel_query_filter_by_filter_data;
    pstDev->dmx_descrambler_open = dmx_descrambler_open;
    pstDev->dmx_descrambler_open_ex = dmx_descrambler_open_ex;
    pstDev->dmx_descrambler_enable  = dmx_descrambler_enable;
    pstDev->dmx_descrambler_disable = dmx_descrambler_disable;
    pstDev->dmx_descrambler_close = dmx_descrambler_close;
    pstDev->dmx_descrambler_associate = dmx_descrambler_associate;
    pstDev->dmx_descrambler_get_associate_info = dmx_descrambler_get_associate_info;
    pstDev->dmx_descrambler_set_even_key = dmx_descrambler_set_even_key;
    pstDev->dmx_descrambler_set_odd_key = dmx_descrambler_set_odd_key;
    pstDev->dmx_set_descrambler_attribute = dmx_set_descrambler_attribute;
    pstDev->dmx_get_descrambler_attribute = dmx_get_descrambler_attribute;
    pstDev->dmx_dcas_keyladder_config = dmx_dcas_keyladder_config;
    pstDev->dmx_dcas_get_nonce = dmx_dcas_get_nonce;
    pstDev->dmx_descrambler_set_even_iv = dmx_descrambler_set_even_iv;
    pstDev->dmx_descrambler_set_odd_iv = dmx_descrambler_set_odd_iv;
    pstDev->dmx_avfilter_open = dmx_avfilter_open;
    pstDev->dmx_avfilter_enable = dmx_avfilter_enable;
    pstDev->dmx_avfilter_get_esframe = dmx_avfilter_get_esframe;
    pstDev->dmx_avfilter_release_esframe = dmx_avfilter_release_esframe;
    pstDev->dmx_avfilter_disable = dmx_avfilter_disable;
    pstDev->dmx_avfilter_close = dmx_avfilter_close;
    pstDev->dmx_pcr_open = dmx_pcr_open;
    pstDev->dmx_pcr_close = dmx_pcr_close;
    pstDev->dmx_pcr_get = dmx_pcr_get;
    pstDev->dmx_tsbuffer_create = dmx_tsbuffer_create;
    pstDev->dmx_tsbuffer_get = dmx_tsbuffer_get;
    pstDev->dmx_tsbuffer_put = dmx_tsbuffer_put;
    pstDev->dmx_tsbuffer_destroy = dmx_tsbuffer_destroy;
    pstDev->dmx_get_streampath_param  = dmx_get_streampath_param;
#ifdef HAL_HISI_EXTEND_H
    pstDev->dmx_channel_get_data_handle  = dmx_channel_get_data_handle;
    pstDev->dmx_tsbuffer_create_ex       = dmx_tsbuffer_create_ex;
    pstDev->dmx_tsbuffer_get_ex          = dmx_tsbuffer_get_ex;
#endif

    *device = &(pstDev->stCommon);

    return SUCCESS;
}

static struct hw_module_methods_t dmx_module_methods =
{
open: dmx_device_open,
};

DMX_MODULE_S HAL_MODULE_INFO_SYM = {
stCommon:      {
tag:           HARDWARE_MODULE_TAG,
version_major: 1,
version_minor: 0,
id:            DEMUX_HARDWARE_MODULE_ID,
name:          "Sample hwcomposer module",
author:        "The Android Open Source Project",
methods:       &dmx_module_methods,
dso:           NULL,
reserved:      {0},
    }
};
#endif

static DEMUX_DEVICE_S s_stDmxDev=
{
    /* register the callbacks */
    .dmx_init                                = dmx_init,
    .dmx_term                                = dmx_term,
    .dmx_set_source_params                   = dmx_set_source_params,
    .dmx_get_source_params                   = dmx_get_source_params,
    .dmx_disconnect                          = dmx_disconnect,
    .dmx_reconnect                           = dmx_reconnect,
    .dmx_get_capability                      = dmx_get_capability,
    .dmx_get_status                          = dmx_get_status,
    .dmx_channel_open                        = dmx_channel_open,
    .dmx_channel_close                       = dmx_channel_close,
    .dmx_channel_set_pid                     = dmx_channel_set_pid,
    .dmx_channel_query                       = dmx_channel_query,
    .dmx_channel_enable                      = dmx_channel_enable,
    .dmx_channel_disable                     = dmx_channel_disable,
    .dmx_channel_reset                       = dmx_channel_reset,
    .dmx_channel_get_info                    = dmx_channel_get_info,
    .dmx_channel_set                         = dmx_channel_set,
    .dmx_channel_get                         = dmx_channel_get,
#ifdef HAL_HISI_EXTEND_H
    .dmx_channel_get_data_handle             = dmx_channel_get_data_handle,
    .dmx_tsbuffer_create_ex                  = dmx_tsbuffer_create_ex,
    .dmx_tsbuffer_get_ex                     = dmx_tsbuffer_get_ex,
#endif
    .dmx_channel_get_buf                     = dmx_channel_get_buf,
    .dmx_channel_release_buf                 = dmx_channel_release_buf,
    .dmx_channel_register_callback           = dmx_channel_register_callback,
    .dmx_channel_config_callback             = dmx_channel_config_callback,
    .dmx_channel_add_filter                  = dmx_channel_add_filter,
    .dmx_channel_set_filter                  = dmx_channel_set_filter,
    .dmx_channel_get_filter                  = dmx_channel_get_filter,
    .dmx_channel_destroy_filter              = dmx_channel_destroy_filter,
    .dmx_channel_destroy_all_filter          = dmx_channel_destroy_all_filter,
    .dmx_channel_enable_filter               = dmx_channel_enable_filter,
    .dmx_channel_disable_filter              = dmx_channel_disable_filter,
    .dmx_channel_query_filter_by_table_id    = dmx_channel_query_filter_by_table_id,
    .dmx_channel_query_filter_by_filter_data = dmx_channel_query_filter_by_filter_data,
    .dmx_descrambler_open                    = dmx_descrambler_open,
    .dmx_descrambler_open_ex                 = dmx_descrambler_open_ex,
    .dmx_descrambler_enable                  = dmx_descrambler_enable,
    .dmx_descrambler_disable                 = dmx_descrambler_disable,
    .dmx_descrambler_close                   = dmx_descrambler_close,
    .dmx_descrambler_associate               = dmx_descrambler_associate,
    .dmx_descrambler_get_associate_info      = dmx_descrambler_get_associate_info,
    .dmx_descrambler_set_even_key            = dmx_descrambler_set_even_key,
    .dmx_descrambler_set_odd_key             = dmx_descrambler_set_odd_key,
    .dmx_set_descrambler_attribute           = dmx_set_descrambler_attribute,
    .dmx_get_descrambler_attribute           = dmx_get_descrambler_attribute,
    .dmx_dcas_keyladder_config               = dmx_dcas_keyladder_config,
    .dmx_dcas_get_nonce                      = dmx_dcas_get_nonce,
    .dmx_descrambler_set_even_iv             = dmx_descrambler_set_even_iv,
    .dmx_descrambler_set_odd_iv              = dmx_descrambler_set_odd_iv,
    .dmx_avfilter_open                       = dmx_avfilter_open,
    .dmx_avfilter_enable                     = dmx_avfilter_enable,
    .dmx_avfilter_get_esframe                = dmx_avfilter_get_esframe,
    .dmx_avfilter_release_esframe            = dmx_avfilter_release_esframe,
    .dmx_avfilter_disable                    = dmx_avfilter_disable,
    .dmx_avfilter_close                      = dmx_avfilter_close,
    .dmx_pcr_open                            = dmx_pcr_open,
    .dmx_pcr_close                           = dmx_pcr_close,
    .dmx_pcr_get                             = dmx_pcr_get,
    .dmx_tsbuffer_create                     = dmx_tsbuffer_create,
    .dmx_tsbuffer_get                        = dmx_tsbuffer_get,
    .dmx_tsbuffer_put                        = dmx_tsbuffer_put,
    .dmx_tsbuffer_destroy                    = dmx_tsbuffer_destroy,
    .dmx_get_streampath_param  = dmx_get_streampath_param
};

DEMUX_DEVICE_S* getDemuxDevice()
{
    return &s_stDmxDev;
}

/************
1. dmx_set_source_params dmx_get_source_params dmx_disconnect dmx_reconnect dmx_channel_reset dmx_get_capability
2. u32FirstIndex u32AddData u32Tag未使用
3. enFilterRepeatMode有问题
4. dmx_channel_query_filter_by_filter_data
5. dmx_descrambler_open_ex dmx_set_descrambler_type dmx_get_descrambler_type
************/
