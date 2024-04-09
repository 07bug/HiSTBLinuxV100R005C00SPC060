#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include "hi_transcoder.h"
#include "hi_muxer.h"
#include "hi_muxer_intf.h"
#include "linux_list.h"

#define LOG_TAG "tran_muxer"
#include "hi_trans_common.h"

static pthread_mutex_t s_stMuxerMutex;
static HI_BOOL bTranMuxerInitFlag = HI_FALSE;
static HI_S32 s_s32MuxerHandleNum;
static HI_S32 g_CodecNum = HI_NULL;
static struct list_head s_stMuxerListHead;
static HI_MuxerInfo_S* g_hFirstCodec = NULL;

#define MUXER_LOCK(pMutex) \
    do{\
        (HI_VOID)pthread_mutex_lock(pMutex);\
    }while(0)

#define MUXER_UNLOCK(pMutex) \
    do{\
        (HI_VOID)pthread_mutex_unlock(pMutex);\
    }while(0)
#define MUXER_MODULE_LOCK    MUXER_LOCK(&s_stMuxerMutex)
#define MUXER_MODULE_UNLOCK    MUXER_UNLOCK(&s_stMuxerMutex)

#define CHECK_MUXER_INIT \
    do{ \
        if(!bTranMuxerInitFlag) \
        { \
            MUXER_UNLOCK(&s_stMuxerMutex); \
            TRANS_LOGOUT("not init error\n"); \
            return HI_FAILURE; \
        } \
    }while(0)

typedef struct tagHI_MuxerItem_S
{
    struct list_head list;
    HI_MuxerInfo_S* pMuxerInfo;
    HI_ULONG MuxerHandle;
} HI_MuxerItem_S;

static HI_S32 MuxerCheckCtrlInfo(const HI_MuxerInfo_S* pstMuxerInfo)
{
    CHECK_NULL_PTR_RETURN(pstMuxerInfo->szName);
    CHECK_NULL_PTR_RETURN(pstMuxerInfo->DoMuxer);
    CHECK_NULL_PTR_RETURN(pstMuxerInfo->MuxerCreate);
    CHECK_NULL_PTR_RETURN(pstMuxerInfo->MuxerDestroy);
    CHECK_NULL_PTR_RETURN(pstMuxerInfo->MuxerGetHeader);
    CHECK_NULL_PTR_RETURN(pstMuxerInfo->pszDescription);
    TRANS_CHK_RETURN_NO_PRINT((0 == pstMuxerInfo->enMuxerType), HI_FAILURE);

    return HI_SUCCESS;
}

extern HI_MuxerInfo_S st_Muxer_TS;
HI_S32 HI_Muxer_RegistCtrl(const HI_CHAR* pszDecoderDllName)
{
    HI_MuxerInfo_S* pMuxerInfo = NULL;
    HI_MuxerInfo_S* pTmpInfo = NULL;
    HI_VOID* pDllModule = NULL;
    HI_S32 s32Ret = 0;

    CHECK_NULL_PTR_RETURN(pszDecoderDllName);
    TRANS_LOGOUT("HI_Muxer_RegistCtrl muxer name : %s\n", pszDecoderDllName);
    /*find if already been registed*/
    if (g_hFirstCodec != NULL)
    {
        pTmpInfo = g_hFirstCodec;
        while (pTmpInfo->next != NULL)
        {
            if (0 == strcmp(pTmpInfo->szDllName, pszDecoderDllName))
            {
                TRANS_LOGOUT("muxer name : %s registed already!!\n", pszDecoderDllName);
                return HI_SUCCESS;
            }
            pTmpInfo = pTmpInfo->next;
        }
    }

    if (!strcmp(pszDecoderDllName, TS_DEFAULT_MUXER))
    {
        pMuxerInfo = &st_Muxer_TS;
    }
    else
    {
        pDllModule = dlopen(pszDecoderDllName, RTLD_LAZY | RTLD_GLOBAL);
        TRANS_CHK_RETURN_PRINT((HI_NULL == pDllModule), HI_FAILURE, "dlopen fail\n");

        /* Get a entry pointer to the "hi_muxer_entry" .  If
         * there is an error, we can't go on, so set the error code and exit */
        pMuxerInfo = (HI_MuxerInfo_S*)dlsym(pDllModule, "hi_muxer_entry");
        if (pMuxerInfo == NULL)
        {
            s32Ret = dlclose(pDllModule);
            TRANS_CHK_PRINT((HI_SUCCESS != s32Ret), "dlclose fail,ret=0x%x\n", s32Ret);
            return HI_FAILURE;
        }

        if (HI_SUCCESS != MuxerCheckCtrlInfo(pMuxerInfo))
        {
            TRANS_LOGOUT(" Register %s Failed \n", pszDecoderDllName);
            s32Ret = dlclose(pDllModule);
            TRANS_CHK_PRINT((HI_SUCCESS != s32Ret), "dlclose fail,ret=0x%x\n", s32Ret);

            return HI_FAILURE;
        }
        pMuxerInfo->pDllModule = pDllModule;
    }

    strncpy(pMuxerInfo->szDllName, pszDecoderDllName, MAX_DLLNAME_LEN - 1);
    pMuxerInfo->szDllName[MAX_DLLNAME_LEN - 1] = 0;

    TRANS_LOGOUT("pszDescription %s!!!\n", pMuxerInfo->pszDescription);
    if (g_hFirstCodec == NULL)
    {
        g_hFirstCodec = pMuxerInfo;
        pMuxerInfo->next = NULL;
    }
    else
    {
        pTmpInfo = g_hFirstCodec;
        while (pTmpInfo->next != NULL)
        {
            pTmpInfo = pTmpInfo->next;
        }
        pTmpInfo->next = pMuxerInfo;
        pMuxerInfo->next = NULL;
    }

    g_CodecNum += 1;

    return HI_SUCCESS;
}

HI_S32 HI_Muxer_DeRegistCtrl(const HI_CHAR* pszDecoderDllName)
{
    HI_MuxerInfo_S* pTmpInfo = g_hFirstCodec;
    HI_MuxerInfo_S* pPreInfo = pTmpInfo;
    HI_BOOL b_isFind = HI_FALSE;
    HI_S32 s32Ret;

    if (g_CodecNum == 1)
    {
        if (!strcmp(pszDecoderDllName, pTmpInfo->szDllName))
        {
            g_hFirstCodec = NULL;
            b_isFind  = HI_TRUE;
        }
        else
        {
            TRANS_LOGOUT("there some error happen, reg and unreg could not be correspond\n");
            return HI_FAILURE;
        }
    }
    else
    {
        while (pTmpInfo != NULL)
        {
            if (!strcmp(pszDecoderDllName, pTmpInfo->szDllName))
            {
                if (pTmpInfo == g_hFirstCodec)
                {
                    g_hFirstCodec = pTmpInfo->next;
                }
                else
                {
                    pPreInfo->next = pTmpInfo->next;
                    pTmpInfo->next = NULL;
                }
                if (HI_NULL != pTmpInfo->pDllModule)
                {
                    s32Ret = dlclose(pTmpInfo->pDllModule);
                    if (HI_SUCCESS != s32Ret)
                    {
                        TRANS_LOGOUT("dlclose error!!!\n");
                    }
                }
                b_isFind = HI_TRUE;
                break;
            }
            pPreInfo = pTmpInfo;
            pTmpInfo = pTmpInfo->next;
        }
    }

    if (b_isFind == HI_TRUE)
    {
        g_CodecNum--;
    }
    else
    {
        TRANS_LOGOUT("there some error happen, reg and unreg could not be correspond\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_S32 HI_Muxer_Init()
{

    TRANS_CHK_RETURN_PRINT((HI_TRUE == bTranMuxerInitFlag), HI_SUCCESS, "Muxer already init.\n");

    HI_S32 s32Ret = pthread_mutex_init(&s_stMuxerMutex, HI_NULL);
    TRANS_CHK_RETURN_PRINT((HI_SUCCESS != s32Ret), HI_FAILURE, "pthread_mutex_init error return : %d\n", s32Ret);

    INIT_LIST_HEAD(&s_stMuxerListHead);
    s32Ret = HI_Muxer_RegistCtrl(TS_DEFAULT_MUXER);
    if (HI_SUCCESS != s32Ret)
    {
        (HI_VOID)pthread_mutex_destroy(&s_stMuxerMutex);
        TRANS_LOGOUT("Muxer regist Default Ctrl error!!!\n");
        return HI_FAILURE;
    }

    bTranMuxerInitFlag = HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 HI_Muxer_DeInit()
{
    HI_S32 s32Ret;
    struct list_head* pMuxList = HI_NULL;
    HI_MuxerItem_S* pMuxItem = HI_NULL;

    TRANS_CHK_RETURN_PRINT((HI_FALSE == bTranMuxerInitFlag), HI_SUCCESS, "Muxer already deinit.\n");
    /*destroy all the muxer handle*/
    while (!list_empty(&s_stMuxerListHead))
    {
        pMuxList = s_stMuxerListHead.next;
        pMuxItem = list_entry(pMuxList, HI_MuxerItem_S, list);
        s32Ret = HI_Muxer_Destroy((HI_ULONG)pMuxItem);
        TRANS_CHK_PRINT((HI_SUCCESS != s32Ret), "HI_Muxer_Destroy fail,ret=0x%x\n", s32Ret);
    }

    (HI_VOID)pthread_mutex_unlock(&s_stMuxerMutex);
    s32Ret = pthread_mutex_destroy(&s_stMuxerMutex);
    if (HI_SUCCESS != s32Ret && EBUSY != s32Ret)
    {
        TRANS_LOGOUT("pthread_mutex_destroy error ret : %d\n", s32Ret);
        s32Ret =  HI_FAILURE;
    }
    else
    {
        s32Ret = HI_SUCCESS;
    }

    /*unreg all the muxer ctrl*/
    while (g_hFirstCodec != HI_NULL)
    {
        if (HI_NULL != g_hFirstCodec->pDllModule)
        {
            s32Ret = dlclose(g_hFirstCodec->pDllModule);
            if (HI_SUCCESS != s32Ret)
            {
                TRANS_LOGOUT("dlclose error!!!\n");
            }
        }
        g_hFirstCodec = g_hFirstCodec->next;
    }
    g_hFirstCodec = NULL;
    bTranMuxerInitFlag = HI_FALSE;
    return s32Ret;
}

HI_S32 HI_Muxer_FindCtrl(HI_MuxerInfo_S** MuxerInfo, Transcoder_MuxerType muxerType)
{
    HI_MuxerInfo_S* pTmpInfo = g_hFirstCodec;
    HI_BOOL b_isFind = HI_FALSE;

    MUXER_MODULE_LOCK;
    while (pTmpInfo != NULL)
    {
        TRANS_LOGOUT("dll name :%s \n", pTmpInfo->szDllName);
        TRANS_LOGOUT("dll description :%s \n", pTmpInfo->pszDescription);
        TRANS_LOGOUT("muxer type :%d \n", pTmpInfo->enMuxerType);
        if (pTmpInfo->enMuxerType == (Transcoder_MuxerType)muxerType)
        {
            b_isFind = HI_TRUE;
            break;
        }
        pTmpInfo = pTmpInfo->next;
    }

    if (b_isFind == HI_TRUE)
    {
        *MuxerInfo = pTmpInfo;
    }
    else
    {
        TRANS_LOGOUT("muxer created have not been registered Ctrl\n");
        MUXER_MODULE_UNLOCK;
        return HI_FAILURE;
    }
    MUXER_MODULE_UNLOCK;
    return HI_SUCCESS;
}

HI_S32 HI_Muxer_Create(HI_ULONG* phMuxerHandle, HI_U32 muxerType, Transcoder_MuxerAttr* muxerAttr)
{

    HI_MuxerInfo_S* pTmpInfo = NULL;
    HI_ULONG hMuxerFuncHandle = HI_NULL;
    CHECK_MUXER_INIT;
    CHECK_NULL_PTR_RETURN(phMuxerHandle);
    CHECK_NULL_PTR_RETURN(muxerAttr);

    TRANS_LOGOUT("muxerType : %d\n", muxerType);

    HI_S32 s32Ret = HI_Muxer_FindCtrl(&pTmpInfo, muxerType);
    TRANS_CHK_RETURN_PRINT((HI_SUCCESS != s32Ret), HI_FAILURE, "muxer Create error!!\n");

    s32Ret = pTmpInfo->MuxerCreate(&hMuxerFuncHandle, muxerType, muxerAttr);
    TRANS_CHK_RETURN_PRINT((HI_SUCCESS != s32Ret), HI_FAILURE, "ceate Muxer handle name : %s error!!\n", pTmpInfo->szName);

    MUXER_MODULE_LOCK;
    HI_MuxerItem_S* muxerItem = (HI_MuxerItem_S*)malloc(sizeof(HI_MuxerItem_S));
    if (HI_NULL == muxerItem)
    {
        TRANS_LOGOUT("muxerItem alloc memory error!!!\n");
        MUXER_MODULE_UNLOCK;
        return HI_FAILURE;
    }
    memset(muxerItem, 0, sizeof(HI_MuxerItem_S));
    muxerItem->MuxerHandle = hMuxerFuncHandle;
    muxerItem->pMuxerInfo = pTmpInfo;
    *phMuxerHandle = (HI_ULONG)muxerItem;
    list_add_tail(&muxerItem->list, &s_stMuxerListHead);
    s_s32MuxerHandleNum++;
    MUXER_MODULE_UNLOCK;

    return HI_SUCCESS;
}

static HI_BOOL HI_Muxer_IsMuxerHandleExist(HI_ULONG hMuxerHandle)
{
    struct list_head* pHandleList = HI_NULL;
    HI_MuxerItem_S* pMuxItem = NULL;
    HI_MuxerItem_S* pTmpInfo = NULL;
    HI_BOOL b_isFind = HI_FALSE;

    pMuxItem = (HI_MuxerItem_S*)hMuxerHandle;
    list_for_each(pHandleList, &s_stMuxerListHead)
    {
        pTmpInfo = list_entry(pHandleList, HI_MuxerItem_S, list);
        if (pTmpInfo == pMuxItem)
        {
            b_isFind = HI_TRUE;
            break;
        }
    }

    return b_isFind;
}

HI_S32 HI_Muxer_Destroy(HI_ULONG hMuxerHandle)
{
    HI_S32 s32Ret = HI_SUCCESS;
    struct list_head* listItem = NULL;
    HI_MuxerItem_S* pTmpInfo = NULL;

    CHECK_MUXER_INIT;
    CHECK_NULL_PTR_RETURN(hMuxerHandle);
    MUXER_MODULE_LOCK;
    if (HI_TRUE == HI_Muxer_IsMuxerHandleExist(hMuxerHandle))
    {
        pTmpInfo = (HI_MuxerItem_S*)hMuxerHandle;
        s32Ret = pTmpInfo->pMuxerInfo->MuxerDestroy(pTmpInfo->MuxerHandle);
        TRANS_CHK_PRINT((HI_SUCCESS != s32Ret), "destroy Muxer handle name : %s error,s32Ret = %d!!\n", pTmpInfo->pMuxerInfo->szName, s32Ret);

        listItem = &pTmpInfo->list;
        list_del(listItem);
        POINTER_FREE(pTmpInfo);
    }
    else
    {
        TRANS_LOGOUT("some error happen, could not find the muxer handle\n");
        s32Ret = HI_FAILURE;
    }
    s_s32MuxerHandleNum--;
    MUXER_MODULE_UNLOCK;
    return s32Ret;
}

HI_S32 HI_Muxer_GetHeader(HI_ULONG hMuxerHandle, HI_CHAR* pTAGFrame, HI_S32* ps32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32HeadLen = 0;
    HI_MuxerItem_S* pTmpInfo = NULL;

    CHECK_MUXER_INIT;
    CHECK_NULL_PTR_RETURN(hMuxerHandle);
    CHECK_NULL_PTR_RETURN(pTAGFrame);
    CHECK_NULL_PTR_RETURN(ps32Len);
    *ps32Len = 0;

    bRet = HI_Muxer_IsMuxerHandleExist(hMuxerHandle);
    TRANS_CHK_RETURN_PRINT((HI_FALSE == bRet), HI_FAILURE, "some error happen, could not find the muxer handle\n");

    pTmpInfo = (HI_MuxerItem_S*)hMuxerHandle;
    s32Ret = pTmpInfo->pMuxerInfo->MuxerGetHeader(pTmpInfo->MuxerHandle, pTAGFrame, &s32HeadLen);
    TRANS_CHK_RETURN_PRINT((HI_SUCCESS != s32Ret), HI_FAILURE, "DoMuxer fail, ret = 0x%x, name = %s error!!\n", s32Ret, pTmpInfo->pMuxerInfo->szName);

    *ps32Len = s32HeadLen;
    return HI_SUCCESS;
}

HI_S32 HI_Muxer_DoMuxer(HI_ULONG hMuxerHandle, HI_CHAR* pTAGFrame, HI_S32* ps32Len, TRANSCODER_STRAM* pstTranFrame)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bRet = HI_FALSE;
    HI_S32 s32MuxerLen = 0;
    HI_MuxerItem_S* pTmpInfo = NULL;

    CHECK_MUXER_INIT;

    CHECK_NULL_PTR_RETURN(hMuxerHandle);
    CHECK_NULL_PTR_RETURN(ps32Len);
    CHECK_NULL_PTR_RETURN(pTAGFrame);
    CHECK_NULL_PTR_RETURN(pstTranFrame);

    bRet = HI_Muxer_IsMuxerHandleExist(hMuxerHandle);
    TRANS_CHK_RETURN_PRINT((HI_FALSE == bRet), HI_FAILURE, "some error happen, could not find the muxer handle\n");

    s32MuxerLen = *ps32Len;
    pTmpInfo = (HI_MuxerItem_S*)hMuxerHandle;
    s32Ret = pTmpInfo->pMuxerInfo->DoMuxer(pTmpInfo->MuxerHandle, pTAGFrame, &s32MuxerLen, pstTranFrame);
    TRANS_CHK_RETURN_PRINT((HI_SUCCESS != s32Ret), HI_FAILURE, "DoMuxer fail, ret = 0x%x, name = %s error!!\n", s32Ret, pTmpInfo->pMuxerInfo->szName);

    *ps32Len = s32MuxerLen;
    return HI_SUCCESS;
}

HI_S32 HI_Muxer_SetPrivateData(HI_ULONG hMuxerHandle, HI_VOID* stAttr, HI_S32 s32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bRet = HI_FALSE;
    HI_MuxerItem_S* pTmpInfo = HI_NULL;

    CHECK_MUXER_INIT;
    CHECK_NULL_PTR_RETURN(hMuxerHandle);
    CHECK_NULL_PTR_RETURN(stAttr);
    CHECK_NULL_PTR_RETURN(s32Len);

    bRet = HI_Muxer_IsMuxerHandleExist(hMuxerHandle);
    TRANS_CHK_RETURN_PRINT((HI_FALSE == bRet), HI_FAILURE, "some error happen, could not find the muxer handle\n");

    pTmpInfo = (HI_MuxerItem_S*)hMuxerHandle;
    s32Ret = pTmpInfo->pMuxerInfo->setPrivate(pTmpInfo->MuxerHandle, stAttr, s32Len);
    TRANS_CHK_RETURN_PRINT((HI_SUCCESS != s32Ret), HI_FAILURE, "setPrivate fail, ret = 0x%x, name = %s error!!\n", s32Ret, pTmpInfo->pMuxerInfo->szName);

    return HI_SUCCESS;
}

HI_S32 HI_Muxer_RegistMuxer(const HI_CHAR* pLibMuxerName)
{
    CHECK_NULL_PTR_RETURN(pLibMuxerName);
    TRANS_CHK_RETURN_PRINT((HI_FALSE == bTranMuxerInitFlag), HI_FAILURE, "not init error\n");

    return HI_Muxer_RegistCtrl(pLibMuxerName);
}

HI_S32 HI_Muxer_DeRegistMuxer(const HI_CHAR* pLibMuxerName)
{
    CHECK_NULL_PTR_RETURN(pLibMuxerName);
    TRANS_CHK_RETURN_PRINT((HI_FALSE == bTranMuxerInitFlag), HI_FAILURE, "not init error\n");

    return HI_Muxer_DeRegistCtrl(pLibMuxerName);
}
