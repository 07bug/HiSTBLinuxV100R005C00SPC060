
#define LOG_TAG "DrmEngine"

#include <utils/Logger.h>
#include <stdlib.h>
#include <stdio.h>

#include "ModularDrmInterface.h"
#include "CryptoInterface.h"
#include "DrmEngine.h"
#include "pthread.h"
#include "hi_list.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace android;

/******************************* begin define *****************************/
#define DEBUG_FLAG (0)

#if DEBUG_FLAG
#define FUNC_ENTER_PRINT        HI_LOGI(">>>%s enter\n", __FUNCTION__);
#define FUNC_RETURN_PRINT       HI_LOGI("%s return success<<<\n", __FUNCTION__);
#define FUNC_TEST_PRINT         HI_LOGI("%s %d test\n", __FUNCTION__, __LINE__);
#define FUNC_RETURN_ERROR_PRINT HI_LOGE("%s return error\n", __FUNCTION__);
#else
#define FUNC_ENTER_PRINT
#define FUNC_RETURN_PRINT
#define FUNC_TEST_PRINT
#define FUNC_RETURN_ERROR_PRINT HI_LOGE("%s return error\n",__FUNCTION__);
#endif

#define PLAYREADY_DEFAULT_LICENSE_URL "http://playready.directtaps.net/pr/svc/rightsmanager.asmx"

#define MODULE_LOCK\
        do{\
            if(HI_FALSE == s_DrmEngineMutex_status)\
            {\
                if (0 != pthread_mutex_init(&s_DrmEngineMutex, HI_NULL))\
                {\
                    HI_LOGE("Mutex init error!!!\n");\
                }\
                s_DrmEngineMutex_status = HI_TRUE;\
            }\
            else\
            {\
                HI_LOGD("s_DrmEngineMutex = %p lock\n", &s_DrmEngineMutex);\
                (HI_VOID)pthread_mutex_lock(&s_DrmEngineMutex);\
                HI_LOGD("s_DrmEngineMutex = %p lock finish\n", &s_DrmEngineMutex);\
            }\
        }while(0)

#define MODULE_UNLOCK\
        do{\
            HI_LOGD("s_DrmEngineMutex = %p unlock\n", &s_DrmEngineMutex);\
            (HI_VOID)pthread_mutex_unlock(&s_DrmEngineMutex);\
            HI_LOGD("s_DrmEngineMutex = %p unlock finish\n", &s_DrmEngineMutex);\
        }while(0)

#define CHECK_NULLPTR(ptr) \
        do{\
            if (HI_NULL == ptr) \
            {\
                HI_LOGE("nullptr error!\n");\
                return HI_FAILURE;\
            }\
        }while(0)

#define CHECK_NULLPTR_BOOL(ptr)\
        do{\
            if (HI_NULL == ptr)\
            {\
                HI_LOGE("nullptr error!\n");\
                return HI_FALSE;\
            }\
        }while(0)

#define CHECK_ZEROLEN(len) \
        do{ \
            if (0 == len) \
            { \
                HI_LOGE("len = 0 error!\n"); \
                return HI_FAILURE; \
            } \
        }while(0)

#define CHECK_ZEROLEN_BOOL(len) \
        do{ \
            if (0 == len) \
            { \
                HI_LOGE("%s %d len = 0 error!\n", __FUNCTION__, __LINE__);\
                return HI_FALSE; \
            } \
        }while(0)

#define DRM_HANDLE_INFO_PRINT(pHandle)\
        do{\
            HI_LOGI("DRM_HANDLE_INFO_PRINT:");\
            HI_LOGI("pDrmHandle = %p", pHandle);\
            HI_LOGI("pDrm = %p", pHandle->pInterface);\
            HI_LOGI("count = %d\n", s_hiHandleInfo.drm.handle_count);\
        }while(0)

#define CRYPTO_HANDLE_INFO_PRINT(pHandle)\
        do{\
            HI_LOGI("CRYPTO_HANDLE_INFO_PRINT:");\
            HI_LOGI("CryptoHandle = %p", pHandle);\
            HI_LOGI("pCrypto = %p", pHandle->pInterface);\
            HI_LOGI("sessionId = %s", pHandle->session.sessionId);\
            HI_LOGI("sessionIdLen = %d",pHandle->session.sessionIdLen);\
            HI_LOGI("count = %d", s_hiHandleInfo.crypto.handle_count);\
        }while(0)

#define DRM_HANDLE_COUNT_CHECK\
        do{\
            if((0 == s_hiHandleInfo.drm.handle_count) \
              || (s_hiHandleInfo.drm.handle_count > MAX_DRM_HANDLE_COUNT))\
            {\
                 HI_LOGE("DrmHandleCount = %d error!\n", s_hiHandleInfo.drm.handle_count);\
                 return HI_FAILURE;\
            }\
        }while(0)

#define CRYPTO_HANDLE_COUNT_CHECK\
        do{\
            if((0 == s_hiHandleInfo.crypto.handle_count) \
              || (s_hiHandleInfo.crypto.handle_count > MAX_CRYPTO_HANDLE_COUNT))\
            {\
                 HI_LOGE("CryptoHandleCount = %d error!\n", s_hiHandleInfo.crypto.handle_count);\
                 return HI_FAILURE;\
            }\
        }while(0)

#define SESSION_COUNT_CHECK\
        do{\
            if((0 == s_hiHandleInfo.session_count) \
              || (s_hiHandleInfo.session_count > MAX_SESSION_COUNT))\
            {\
               HI_LOGE("SessionCount = %d error!\n", s_hiHandleInfo.session_count);\
               return HI_FAILURE;\
            }\
        }while(0)

#define DRM_HANDLE_VOID_TRANS(pDrmHandle, v_pDrmHandle)\
        do{\
            pDrmHandle = (HI_DRM_HANDLE*)(v_pDrmHandle);\
        }while(0)

#define CRYPTO_HANDLE_VOID_TRANS(pCryptoHandle, v_pCryptoHandle)\
        do{\
            pCryptoHandle = (HI_CRYPTO_HANDLE*)(v_pCryptoHandle);\
        }while(0)

#define DRM_HANDLE_EXIST_CHECK(pDrmHandle)\
        do{\
            if(HI_FALSE == Drm_Handle_isExist(pDrmHandle))\
            {\
                HI_LOGE("this handle is not exist!\n");\
                return HI_FAILURE;\
            }\
        }while(0)

#define CRYPTO_HANDLE_EXIST_CHECK(pDrmHandle, pCryptoHandle)\
        do{\
            if(HI_FALSE == Crypto_Handle_isExist(pDrmHandle, pCryptoHandle))\
            {\
                HI_LOGE("this handle is not exist!\n");\
                return HI_FAILURE;\
            }\
        }while(0)

/******************************* end define *****************************/

/************************* begin typedef struct *************************/
//--------handle struct---------------
typedef struct hiDrm_Handle
{
    ModularDrmInterface* pInterface;
    List_Head_S list;
}HI_DRM_HANDLE;

typedef struct hiCrypto_Handle
{
    HI_DRMENGINE_SESSION session;
    CryptoInterface* pInterface;
    List_Head_S list;
}HI_CRYPTO_HANDLE;

//--------handle info struct-----------
typedef struct hiDrm_Handle_Info
{
    HI_DRM_HANDLE handle_head;
    HI_U32 handle_count;
}HI_DRM_HANDLE_INFO;

typedef struct hiCrypto_Handle_Info
{
    HI_CRYPTO_HANDLE handle_head;
    HI_U32 handle_count;
}HI_CRYPTO_HANDLE_INFO;

typedef struct hiHandle_Info
{
    HI_DRM_HANDLE_INFO drm;
    HI_CRYPTO_HANDLE_INFO crypto;
    HI_U32 session_count;
}HI_HANDLE_INFO;
/************************* end typedef struct *************************/

/************************ begin static implement **********************/
static HI_HANDLE_INFO s_hiHandleInfo;

static pthread_mutex_t s_DrmEngineMutex;
static HI_BOOL s_DrmEngineMutex_status = HI_FALSE;

static HI_BOOL Drm_Handle_isExist(const HI_DRM_HANDLE* pDrmHandle)
{
    FUNC_ENTER_PRINT;

    List_Head_S* pos = HI_NULL;
    List_Head_S* next = HI_NULL;
    HI_DRM_HANDLE* pDrmHandleInList = HI_NULL;

    HI_LOGD("drm handle target:%p\n", pDrmHandle);

    HI_List_For_Each_Safe(pos, next, &(s_hiHandleInfo.drm.handle_head.list))
    {
        pDrmHandleInList = HI_LIST_ENTRY(pos, HI_DRM_HANDLE, list);

        HI_LOGD("drm handle in pos:%p\n", pDrmHandleInList);

        if(pDrmHandleInList == pDrmHandle)
        {
            HI_LOGD("input drm handle %p exist\n", pDrmHandleInList);
            return HI_TRUE;
        }
    }

    HI_LOGI("input drm handle %p not exist!", pDrmHandle);
    return HI_FALSE;
}

#if defined(STREAM_DEBUG)
static FILE * stream_input_full;
static FILE * stream_input_secure;
static FILE * stream_input_notsecure;
static FILE * stream_output_notsecure;
#endif

static HI_VOID Drm_Init(HI_VOID)
{
    FUNC_ENTER_PRINT;

#if defined(STREAM_DEBUG)
    stream_input_full = fopen("/tmp/stream_input_full", "w");
    stream_input_secure = fopen("/tmp/stream_input_secure", "w");
    stream_input_notsecure = fopen("/tmp/stream_input_notsecure", "w");
    stream_output_notsecure = fopen("/tmp/stream_output_notsecure", "w");
#endif

    if(0 != pthread_mutex_init(&s_DrmEngineMutex, HI_NULL))
    {
         HI_LOGE("Mutex init error!!!\n");
         return;
    }

    s_DrmEngineMutex_status = HI_TRUE;

    memset(&s_hiHandleInfo, 0, sizeof(HI_HANDLE_INFO));

    HI_LIST_HEAD_INIT_PTR(&s_hiHandleInfo.drm.handle_head.list);

    FUNC_RETURN_PRINT;
    return;
}

static HI_VOID Drm_DeInit(HI_VOID)
{
    FUNC_ENTER_PRINT;

    (HI_VOID)pthread_mutex_destroy(&s_DrmEngineMutex);
    s_DrmEngineMutex_status = HI_FALSE;

    HI_List_Del_Init(&s_hiHandleInfo.drm.handle_head.list);

    memset(&s_hiHandleInfo, 0, sizeof(HI_HANDLE_INFO));

    FUNC_RETURN_PRINT;
    return;
}

static HI_VOID Crypto_Init(HI_VOID)
{
    FUNC_ENTER_PRINT;

    memset(&s_hiHandleInfo.crypto, 0, sizeof(HI_CRYPTO_HANDLE_INFO));

    HI_LIST_HEAD_INIT_PTR(&s_hiHandleInfo.crypto.handle_head.list);

    FUNC_RETURN_PRINT;
    return;
}

static HI_VOID Crypto_DeInit(HI_VOID)
{
    FUNC_ENTER_PRINT;

    HI_List_Del_Init(&s_hiHandleInfo.crypto.handle_head.list);

    memset(&s_hiHandleInfo.crypto, 0, sizeof(HI_CRYPTO_HANDLE_INFO));

    FUNC_RETURN_PRINT;
    return;
}

//transfer pDrmHandle from void type v_pDrmHandle, and
//check if pDrmHandle is exist in drm handle list
static HI_S32 getDrmHandle(__out HI_DRM_HANDLE* &pDrmHandle,
                           __in  const HI_VOID* &v_pDrmHandle)
{
    FUNC_ENTER_PRINT;

    pDrmHandle = (HI_DRM_HANDLE*)(v_pDrmHandle);

    if(HI_TRUE != Drm_Handle_isExist(pDrmHandle))
    {
        HI_LOGE("Drm Handle %p not exist in list, error!\n",pDrmHandle);
        return HI_FAILURE;
    }

    FUNC_RETURN_PRINT;
    return HI_SUCCESS;
}

//search session in crypto list, and get the pCryptoHandle in target Node
static HI_S32 getCryptoHandle(__out HI_CRYPTO_HANDLE* &pCryptoHandle,
                              __in  const HI_DRMENGINE_SESSION session)
{
    FUNC_ENTER_PRINT;

    List_Head_S* pos = HI_NULL;
    List_Head_S* next = HI_NULL;

    HI_CRYPTO_HANDLE* pCryptoHandleInList = HI_NULL;

    HI_U8 in_sessionId[MAX_SESSIONID_LEN] = {0};
    HI_U32 in_sessionIdLen = 0;

    in_sessionIdLen = session.sessionIdLen;
    memcpy(in_sessionId, session.sessionId, session.sessionIdLen);

//-------------------------search in list--------------------------------
#if DEBUG_FLAG
    HI_LOGD("--------------began search------------\n");
    HI_LOGD("pCryptoHandle:%p", pCryptoHandle);
    HI_LOGD("search target:\n");
    HI_LOGD("sessionId:%s\n", session.sessionId);
    HI_LOGD("sessionIdLen:%d\n", session.sessionIdLen);
#endif

    HI_List_For_Each_Safe(pos, next, &s_hiHandleInfo.crypto.handle_head.list)
    {
        pCryptoHandleInList = HI_LIST_ENTRY(pos, HI_CRYPTO_HANDLE, list);
#if DEBUG_FLAG
        HI_LOGD("---------------------------\n");
        HI_LOGD("Crypto sessionId = %s\n", pCryptoHandleInList->session.sessionId);
        HI_LOGD("Crypto sessionIdLen = %d\n", pCryptoHandleInList->session.sessionIdLen);
#endif
    //-----------------compare session info--------------------------
        //compare len and Id
        if((in_sessionIdLen == pCryptoHandleInList->session.sessionIdLen)
           && (0 == memcmp(in_sessionId, pCryptoHandleInList->session.sessionId, in_sessionIdLen)))
        {
            pCryptoHandle = pCryptoHandleInList;
            HI_LOGD("Found sessionId=%s, crypto handle=%p\n", session.sessionId, pCryptoHandle);
            FUNC_RETURN_PRINT;
            return HI_SUCCESS;
        }
    }

    HI_LOGD("crypto interface %p not found!\n", pCryptoHandle);
    FUNC_RETURN_PRINT;
    return HI_FAILURE;
}

static HI_VOID VectorToArray(__in  const Vector<HI_U8> &vectorData,
                             __out HI_U8* arrayData,
                             __out HI_U32* pArrayDataLen)
{
    FUNC_ENTER_PRINT;

    if(!vectorData.isEmpty())
    {
        *pArrayDataLen = vectorData.size();
        memcpy(arrayData, &vectorData[0], *pArrayDataLen);

#if DEBUG_FLAG
        printf("VectorToArray Len =%d\n", *pArrayDataLen);
        for(HI_U32 i=0; i< *pArrayDataLen; i++)
        {
            printf("%c", arrayData[i]);
        }
        printf("\nEND\n");

        HI_LOGD("\nVectorToArray Result:\n%s\n", arrayData);
        HI_LOGD("Len=%d\n", *pArrayDataLen);
#endif

    }
    else
    {
        HI_LOGD("input Vector is empty!");
    }

    FUNC_RETURN_PRINT;
    return;
}

static HI_VOID ArrayToVector(__in  const HI_U8* arrayData,
                             __in  const HI_U32 arrayDataLen,
                             __out Vector<HI_U8> &vectorData)
{
    FUNC_ENTER_PRINT;

#if DEBUG_FLAG
    HI_LOGD("\nArrayToVector input: %s\n", arrayData);
    HI_LOGD("\nLen=%d\n", arrayDataLen);

    printf("================================\n");
    printf("ArrayToVector Len=%d\n", arrayDataLen);
    printf("================================\n");
    for(HI_U32 i=0; i< arrayDataLen; i++)
    {
        printf("%c", arrayData[i]);
    }
    printf("\nEND\n");
    printf("================================\n");
    printf("ArrayToVector input: %s\n", arrayData);
    printf("================================\n");
#endif

    vectorData.clear();
    vectorData.appendArray(arrayData, arrayDataLen);

    FUNC_RETURN_PRINT;
    return;
}

static HI_VOID String8ToArray(__in  const String8 &string8Data,
                              __out HI_U8* arrayData,
                              __out HI_U32* pArrayDataLen)
{
    FUNC_ENTER_PRINT;

    if(!string8Data.empty())
    {
#if DEBUG_FLAG
        HI_LOGD("string8Data input:\n%s\n", string8Data.string());
        HI_LOGD("string8Data len=%d\n", string8Data.length());
        printf("string8Data input:\n%s\n", string8Data.string());
        printf("string8Data len=%d\n", string8Data.length());
#endif

        const HI_U8 *charData = reinterpret_cast<const uint8_t*>(string8Data.string());
        *pArrayDataLen = string8Data.length();

        memcpy(arrayData, charData, *pArrayDataLen);

#if DEBUG_FLAG
        printf("================================\n");
        printf("*pArrayDataLen=%d\n", *pArrayDataLen);
        for(HI_U32 i=0; i< *pArrayDataLen; i++)
        {
            printf("%c", arrayData[i]);
        }
        printf("\n================================\n");
        HI_LOGD("================================\n");
        HI_LOGD("Len=%d\n", *pArrayDataLen);
        HI_LOGD("String8ToArray Result:\n%s\n", arrayData);
        HI_LOGD("================================\n");
#endif

    }
    else
    {
        HI_LOGD("input String8 is empty");
    }

    FUNC_RETURN_PRINT;
    return;
}

static HI_VOID ArrayToString8(__in const HI_U8* arrayData,
                              __in const HI_U32 arrayDataLen,
                              __out String8 &string8Data)
{
    HI_LOGD("input arrayData = %s, len = %d\n", arrayData, arrayDataLen);
    string8Data = String8(arrayData, arrayDataLen);
    return;
}
/************************* end static implement *********************/

/*************************** begin implement ************************/
HI_S32 HI_DrmEngine_Create(__out HI_VOID** v_ppDrmHandle,
                           __in  const HI_U8 uuid[HI_DRMENGINE_UUID_LEN])

{
    FUNC_ENTER_PRINT;

    HI_DRM_HANDLE* pDrmHandle = HI_NULL;
    ModularDrmInterface* pDrm = HI_NULL;

    CHECK_NULLPTR(v_ppDrmHandle);
    CHECK_NULLPTR(uuid);

//-----------------drm handle count check-----------------------
    if(s_hiHandleInfo.drm.handle_count > MAX_DRM_HANDLE_COUNT)
    {
         HI_LOGE("Drm Handle Count = %d error!\n", s_hiHandleInfo.drm.handle_count);
         return HI_FAILURE;
    }

    MODULE_LOCK;
//-------------------drm init check-------------------
    if(0 == s_hiHandleInfo.drm.handle_count)
    {
        HI_LOGD("begin Drm_Init\n");
        Drm_Init();
    }

//---------------------new drm handle------------------------
    HI_LOGD("begin create drm handle\n");

    pDrmHandle = new HI_DRM_HANDLE;

    if(HI_NULL == pDrmHandle)
    {
        HI_LOGE("new Drm Handle Count error!\n");
        goto errorRet;
    }

    memset(pDrmHandle, 0, sizeof(HI_DRM_HANDLE));

//----------------do drm create,and get interface addr------
    HI_LOGD("begin ModularDrmInterface::Create\n");

    pDrm = ModularDrmInterface::Create(uuid);

    if(HI_NULL == pDrm)
    {
        HI_LOGE("pDrm = ModularDrmInterface::Create nullptr!\n");
        delete pDrmHandle;
        pDrmHandle = HI_NULL;
        goto errorRet;
    }

//-----------add drm interface to Handle struct------------
    pDrmHandle->pInterface = pDrm;

//--------add Drm handle to list, and add count------------
    HI_LOGD("add drm handle list Node\n");

    HI_List_Add(&(pDrmHandle->list), &(s_hiHandleInfo.drm.handle_head.list));
    s_hiHandleInfo.drm.handle_count++;

    DRM_HANDLE_INFO_PRINT(pDrmHandle);

    HI_LOGD("drm handle has been created\n");

//-----------------output handle pointer-------------------
    *v_ppDrmHandle = (HI_DRM_HANDLE*)(pDrmHandle);

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT
    return HI_SUCCESS;

errorRet:
    HI_LOGE("ERROR\n");

    if(0 == s_hiHandleInfo.drm.handle_count)
    {
        HI_LOGD("begin drm list deInit\n");
        Drm_DeInit();
    }

    HI_LOGE("v_ppDrmHandle=%p\n", v_ppDrmHandle);

    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_S32 HI_DrmEngine_Destroy(__in const HI_VOID* v_pDrmHandle)
{
    FUNC_ENTER_PRINT;

    HI_DRM_HANDLE* pDrmHandle = HI_NULL;
    ModularDrmInterface* pDrm = HI_NULL;
    HI_S32 ret = HI_FAILURE;

    CHECK_NULLPTR(v_pDrmHandle);

    DRM_HANDLE_COUNT_CHECK;

    MODULE_LOCK;
//-----------------get Drm Handle---------------------
    HI_LOGI("begin getDrmHandle\n");

    if(HI_SUCCESS != getDrmHandle(pDrmHandle, v_pDrmHandle))
    {
        HI_LOGE("getDrmHandle error");
        goto errorRet;
    }

    if(HI_NULL ==  pDrmHandle->pInterface)
    {
        HI_LOGE("pDrmHandle->pInterface nullptr error");
        goto errorRet;
    }

    pDrm = pDrmHandle->pInterface;

    DRM_HANDLE_INFO_PRINT(pDrmHandle);

//----------------- drm destroy-----------------------
    HI_LOGI("begin ModularDrmInterface::Destroy\n");

    ret = ModularDrmInterface::Destroy(pDrm);

    if(HI_SUCCESS != ret)
    {
        HI_LOGE("ModularDrmInterface::Destroy error = %d\n", ret);
        goto errorRet;
    }

//------------delete drm handle Node in list---------
    HI_LOGI("delete drm handle list Node\n");

    HI_List_Del(&pDrmHandle->list);
    s_hiHandleInfo.drm.handle_count--;

    memset(pDrmHandle, 0, sizeof(HI_DRM_HANDLE));
    delete pDrmHandle;
    pDrmHandle = HI_NULL;

//------------drm handle list deinit----------------
    if(0 == s_hiHandleInfo.drm.handle_count)
    {
        HI_LOGI("begin drm list deInit\n");
        Drm_DeInit();
    }

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return HI_SUCCESS;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_BOOL HI_DrmEngine_isCryptoSchemeSupported(__in const HI_VOID* v_pDrmHandle,
                                             __in const HI_U8 uuid[HI_DRMENGINE_KEY_LEN],
                                             __in const HI_CHAR* mimeType)
{
    FUNC_ENTER_PRINT;

    HI_DRM_HANDLE* pDrmHandle = HI_NULL;
    ModularDrmInterface* pDrm = HI_NULL;
    HI_BOOL ret = HI_FALSE;

    CHECK_NULLPTR_BOOL(v_pDrmHandle);
    CHECK_NULLPTR_BOOL(uuid);
    CHECK_NULLPTR_BOOL(mimeType);

//-----------------drm handle count check-----------------------
    if((0 == s_hiHandleInfo.drm.handle_count)
       || (s_hiHandleInfo.drm.handle_count > MAX_DRM_HANDLE_COUNT))
    {
         HI_LOGE("DrmHandleCount = %d error!\n", s_hiHandleInfo.drm.handle_count);
         return HI_FALSE;
    }

    MODULE_LOCK;
//-----------------get drm handle-----------------------
    HI_LOGD("begin getDrmHandle\n");

    if(HI_SUCCESS != getDrmHandle(pDrmHandle, v_pDrmHandle))
    {
        HI_LOGE("getDrmHandle error");
        goto errorRet;
    }

    if(HI_NULL == pDrmHandle->pInterface)
    {
        HI_LOGE("pDrmHandle->pInterface nullptr error");
        goto errorRet;
    }

    pDrm = pDrmHandle->pInterface;

    DRM_HANDLE_INFO_PRINT(pDrmHandle);

//-----------------begin do isCryptoSchemeSupported-----------------------
    HI_LOGI("begin do isCryptoSchemeSupported\n");

    ret = pDrm->isCryptoSchemeSupported(uuid, mimeType);

    HI_LOGD("isCryptoSchemeSupported ret = %d",ret);

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return ret;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FALSE;
}

HI_S32 HI_DrmEngine_openSession(__in  const HI_VOID* v_pDrmHandle,
                                __out HI_DRMENGINE_SESSION* pSession)
{
    FUNC_ENTER_PRINT;

    HI_DRM_HANDLE* pDrmHandle = HI_NULL;
    ModularDrmInterface* pDrm = HI_NULL;

    Vector<HI_U8> vSessionId;

    CHECK_NULLPTR(v_pDrmHandle);

#if DEBUG_FLAG
    printf("v_pDrmHandle=%p\n", v_pDrmHandle);
#endif
    HI_LOGD("v_pDrmHandle=%p\n", v_pDrmHandle);

    CHECK_NULLPTR(pSession);

    DRM_HANDLE_COUNT_CHECK;

    if(s_hiHandleInfo.session_count > MAX_SESSION_COUNT)
    {
         HI_LOGE("session_count = %d > max error!\n",s_hiHandleInfo.session_count);
         FUNC_RETURN_ERROR_PRINT;
         return HI_FAILURE;
    }

    MODULE_LOCK;
//--------------------get drm handle--------------------------------
    HI_LOGI("begin getDrmHandle\n");

    if(HI_SUCCESS != getDrmHandle(pDrmHandle, v_pDrmHandle))
    {
        HI_LOGE("getDrmHandle error");
        goto errorRet;
    }

    if(HI_NULL ==  pDrmHandle->pInterface)
    {
        HI_LOGE("pDrmHandle->pInterface nullptr error");
        goto errorRet;
    }

    pDrm = pDrmHandle->pInterface;

    DRM_HANDLE_INFO_PRINT(pDrmHandle);

//--------------------openSession--------------------------------
    HI_LOGI("begin openSession\n");

    if(HI_SUCCESS != pDrm->openSession(vSessionId))
    {
        HI_LOGE("openSession error");
        goto errorRet;
    }

    memset(pSession->sessionId, 0, MAX_SESSIONID_LEN);
    pSession->sessionIdLen = 0;

    VectorToArray(vSessionId, pSession->sessionId, &pSession->sessionIdLen);

    if(0 == pSession->sessionIdLen || pSession->sessionIdLen > MAX_SESSIONID_LEN)
    {
        HI_LOGE("sessionId Len = %d error!\n", pSession->sessionIdLen);
        pDrm->closeSession(vSessionId);
        goto errorRet;
    }

    HI_LOGD("openSession success\n");

    s_hiHandleInfo.session_count++;

    HI_LOGD("openSession Id = %s, Len = %d\n", pSession->sessionId, pSession->sessionIdLen);

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return HI_SUCCESS;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_S32 HI_DrmEngine_closeSession(__in const HI_VOID* v_pDrmHandle,
                                 __in const HI_DRMENGINE_SESSION session)
{
    FUNC_ENTER_PRINT;

    HI_DRM_HANDLE* pDrmHandle = HI_NULL;
    ModularDrmInterface* pDrm = HI_NULL;

    Vector<HI_U8> vSessionId;

    CHECK_NULLPTR(v_pDrmHandle);
    CHECK_NULLPTR(session.sessionId);

    CHECK_ZEROLEN(session.sessionIdLen);

    HI_LOGD("closeSession input Id = %s, Len = %d\n", session.sessionId, session.sessionIdLen);

    DRM_HANDLE_COUNT_CHECK;
    SESSION_COUNT_CHECK;

    ArrayToVector(session.sessionId, session.sessionIdLen, vSessionId);

    MODULE_LOCK;
//--------------------get drm handle--------------------------------
    HI_LOGI("begin getDrmHandle\n");

    if(HI_SUCCESS != getDrmHandle(pDrmHandle, v_pDrmHandle))
    {
        HI_LOGE("getDrmHandle error");
        goto errorRet;
    }

    if(HI_NULL ==  pDrmHandle->pInterface)
    {
        HI_LOGE("pDrmHandle->pInterface nullptr error");
        goto errorRet;
    }

    pDrm = pDrmHandle->pInterface;

    DRM_HANDLE_INFO_PRINT(pDrmHandle);

//------------------ close session-----------------------------
    HI_LOGI("begin close session\n");

    //now closeSession for playready always return HI_SUCCESS
    if(HI_SUCCESS != pDrm->closeSession(vSessionId))
    {
        HI_LOGE("closeSession error");
        goto errorRet;
    }

    s_hiHandleInfo.session_count--;

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return HI_SUCCESS;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_S32 HI_DrmEngine_getKeyRequest(__in  const HI_VOID* v_pDrmHandle,
                                  __in  const HI_DRMENGINE_SESSION session,
                                  __in  const HI_U8* initData,
                                  __in  const HI_U32 initDataLen,
                                  __in  HI_CHAR const* mimeType,
                                  __in  HI_DRMENGINE_KEY_TYPE drmEngineKeyType,
                                  __out HI_DRMENGINE_KEY_REQUEST* pCTypeKeyRequest)
{
    FUNC_ENTER_PRINT;

    Vector<HI_U8> vSessionId;
    Vector<HI_U8> vInitData;
    KeyedVector<String8, String8> optionalParameters;
    //TODO:KeyedVector<String8, String8> optionalParameters will be implemented if necessary.

    HI_DRM_KEY_TYPE keyType = (HI_DRM_KEY_TYPE)(drmEngineKeyType);
    HI_DRM_KEY_REQUEST keyRequest;

    HI_DRM_HANDLE* pDrmHandle = HI_NULL;
    ModularDrmInterface* pDrm = HI_NULL;

    HI_S32 ret = HI_FAILURE;

    CHECK_NULLPTR(v_pDrmHandle);
    CHECK_NULLPTR(session.sessionId);
    CHECK_NULLPTR(initData);
    CHECK_NULLPTR(mimeType);
    CHECK_NULLPTR(pCTypeKeyRequest);

    CHECK_ZEROLEN(session.sessionIdLen);
    CHECK_ZEROLEN(initDataLen);

    DRM_HANDLE_COUNT_CHECK;
    SESSION_COUNT_CHECK;

    ArrayToVector(session.sessionId, session.sessionIdLen, vSessionId);
    ArrayToVector(initData, initDataLen, vInitData);

    MODULE_LOCK;
//--------------------get drm handle--------------------------------
    HI_LOGI("begin getDrmHandle\n");

    if(HI_SUCCESS != getDrmHandle(pDrmHandle, v_pDrmHandle))
    {
        HI_LOGE("getDrmHandle error");
        goto errorRet;
    }

    if(HI_NULL ==  pDrmHandle->pInterface)
    {
        HI_LOGE("pDrmHandle->pInterface nullptr error");
        goto errorRet;
    }

    pDrm = pDrmHandle->pInterface;

    DRM_HANDLE_INFO_PRINT(pDrmHandle);

//--------------------getKeyRequest--------------------------------
    HI_LOGI("begin getKeyRequest\n");

    //getKeyRequest has different return type;
    ret = pDrm->getKeyRequest(vSessionId, vInitData,
                              mimeType, keyType,
                              optionalParameters,
                              &keyRequest);

    if (HI_SUCCESS != ret)
    {
        HI_LOGE("getKeyRequest error! ret = %d\n", ret);
        MODULE_UNLOCK;
        return ret;
    }

//--------------------get pCTypeKeyRequest from keyRequest--------------------------------
//**************begin default Url**************
#if DEBUG_FLAG
    printf("====================\n");
    printf("keyRequest.defaultUrl.size()=%d\n", keyRequest.defaultUrl.size());
    printf("====================\n");
    printf("keyRequest.defaultUrl.string()=%s\n", keyRequest.defaultUrl.string());

    for(HI_U32 i=0; i<keyRequest.defaultUrl.size(); i++)
    {
        printf("%c", keyRequest.defaultUrl[i]);
    }
    printf("\n====================\n");
#endif

    //check keyRequest.defaultUrl info
    if(HI_NULL == keyRequest.defaultUrl.string())
    {
        HI_LOGE("keyRequest.defaultUrl.string() == nullptr\n");
        goto errorRet;
    }

    if(keyRequest.defaultUrl.length() + 1 > MAX_DEFAULT_URL_SIZE)
    {
        HI_LOGE("keyRequest.defaultUrl.length() =%d error!\n", keyRequest.defaultUrl.length());
        goto errorRet;
    }

    //keyRequest.defaultUrl begin copy
    memset(pCTypeKeyRequest->defaultUrl, 0, MAX_DEFAULT_URL_SIZE);

    HI_LOGD("keyRequest.defaultUrl.length() = %d\n", keyRequest.defaultUrl.length());
    HI_LOGD("keyRequest.defaultUrl.string() = %s\n", keyRequest.defaultUrl.string());

    if (0 == memcmp(keyRequest.defaultUrl.string(), PLAYREADY_DEFAULT_LICENSE_URL,
            strlen(PLAYREADY_DEFAULT_LICENSE_URL)))
    {
        HI_LOGD("license url = %s\n", PLAYREADY_DEFAULT_LICENSE_URL);
        memcpy(pCTypeKeyRequest->defaultUrl, PLAYREADY_DEFAULT_LICENSE_URL,
                                      strlen(PLAYREADY_DEFAULT_LICENSE_URL));
    }
    else
    {
        memcpy(pCTypeKeyRequest->defaultUrl, keyRequest.defaultUrl.string(),
                                             keyRequest.defaultUrl.length());
    }

    HI_LOGD("pCTypeKeyRequest->defaultUrl len = %d\n",strlen(pCTypeKeyRequest->defaultUrl));
    HI_LOGD("pCTypeKeyRequest->defaultUrl = %s\n", pCTypeKeyRequest->defaultUrl);
//**************end default Url**************

//**************begin eKeyRequestType**************
    pCTypeKeyRequest->eKeyRequestType = (HI_DRMENGINE_KEYREQUEST_TYPE)(keyRequest.eKeyRequestType);
    HI_LOGD("keyRequest.eKeyRequestType = %d\n", keyRequest.eKeyRequestType);
    HI_LOGD("pCTypeKeyRequest->eKeyRequestType = %d\n", pCTypeKeyRequest->eKeyRequestType);
//**************end eKeyRequestType**************

//**************begin requestData**************
    //check keyRequest.requestData info
    if (HI_NULL == keyRequest.requestData.array())
    {
        HI_LOGE("keyRequest.requestData.array() == nullptr\n");
        goto errorRet;
    }

    if (0 == keyRequest.requestData.size() || keyRequest.requestData.size() > MAX_REQUEST_DATA_SIZE)
    {
        HI_LOGE("keyRequest.requestData.size() = %d error\n", keyRequest.requestData.size());
        goto errorRet;
    }

    HI_LOGD("keyRequest.requestData.size() = %d\n", keyRequest.requestData.size());
    HI_LOGD("keyRequest.requestData.array() = %s\n", keyRequest.requestData.array());

    //keyRequest.requestData begin copy
    memcpy(pCTypeKeyRequest->requestData, keyRequest.requestData.array(),
        keyRequest.requestData.size());

    pCTypeKeyRequest->requestDataLen = keyRequest.requestData.size();

    HI_LOGD("pCTypeKeyRequest->requestDataLen = %d\n", pCTypeKeyRequest->requestDataLen);
    HI_LOGD("pCTypeKeyRequest->requestData = %s\n", pCTypeKeyRequest->requestData);
//**************end requestData**************

#if DEBUG_FLAG
    printf("keyRequest.defaultUrl.length() = %d\n", keyRequest.defaultUrl.length());
    printf("keyRequest.defaultUrl.string() = %s\n", keyRequest.defaultUrl.string());

    printf("pCTypeKeyRequest->defaultUrl len = %d\n",strlen(pCTypeKeyRequest->defaultUrl));
    printf("pCTypeKeyRequest->defaultUrl = %s\n", pCTypeKeyRequest->defaultUrl);

    printf("keyRequest.eKeyRequestType = %d\n", keyRequest.eKeyRequestType);
    printf("pCTypeKeyRequest->eKeyRequestType = %d\n", pCTypeKeyRequest->eKeyRequestType);

    printf("keyRequest.requestData.size() = %d\n", keyRequest.requestData.size());
    printf("keyRequest.requestData.array() = %s\n", keyRequest.requestData.array());

    printf("pCTypeKeyRequest->requestDataLen = %d\n", pCTypeKeyRequest->requestDataLen);
    printf("pCTypeKeyRequest->requestData = %s\n", pCTypeKeyRequest->requestData);
#endif

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return ret;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_S32 HI_DrmEngine_provideKeyResponse(__in  const HI_VOID* v_pDrmHandle,
                                       __in  const HI_DRMENGINE_SESSION session,
                                       __in  const HI_U8* response,
                                       __in  const HI_U32 responseLen,
                                       __out HI_U8* keySetId,
                                       __out HI_U32* pKeySetIdLen)
{
    FUNC_ENTER_PRINT;

    HI_S32 ret = HI_FAILURE;

    Vector<HI_U8> vSessionId;
    Vector<HI_U8> vResponse;
    Vector<HI_U8> vKeySetId;

    HI_DRM_HANDLE* pDrmHandle = HI_NULL;
    ModularDrmInterface* pDrm = HI_NULL;

    CHECK_NULLPTR(v_pDrmHandle);
    CHECK_NULLPTR(session.sessionId);
    CHECK_NULLPTR(response);
    CHECK_NULLPTR(keySetId);
    CHECK_NULLPTR(pKeySetIdLen);

    CHECK_ZEROLEN(session.sessionIdLen);
    CHECK_ZEROLEN(responseLen);

#if DEBUG_FLAG
    HI_LOGD("============================");
    HI_LOGD("response input:\n%s\n", response);
    HI_LOGD("Len = %d\n", responseLen);
    HI_LOGD("============================");

    printf("============================\n");
    printf("HI_DrmEngine_provideKeyResponse Len=%d\n", responseLen);
    for(HI_U32 i=0; i< responseLen; i++)
    {
        printf("%c", response[i]);
    }
    printf("\n============================\n");
#endif

    DRM_HANDLE_COUNT_CHECK;
    SESSION_COUNT_CHECK;

    ArrayToVector(session.sessionId, session.sessionIdLen, vSessionId) ;
    ArrayToVector(response, responseLen, vResponse);

    MODULE_LOCK;
//--------------------get drm handle--------------------------------
    HI_LOGI("begin getDrmHandle\n");

    if(HI_SUCCESS != getDrmHandle(pDrmHandle, v_pDrmHandle))
    {
        HI_LOGE("getDrmHandle error");
        goto errorRet;
    }

    if(HI_NULL == pDrmHandle->pInterface)
    {
        HI_LOGE("pDrmHandle->pInterface nullptr error");
        goto errorRet;
    }

    pDrm = pDrmHandle->pInterface;

    DRM_HANDLE_INFO_PRINT(pDrmHandle);

//--------------------provideKeyResponse--------------------------------
    HI_LOGI("begin provideKeyResponse\n");

    //provideKeyResponse has different return type;
    ret = pDrm->provideKeyResponse(vSessionId, vResponse, vKeySetId);

    if (HI_SUCCESS != ret)
    {
        HI_LOGE("provideKeyResponse error return = %d\n",ret);
        MODULE_UNLOCK;
        return ret;
    }

    if(vKeySetId.size() > MAX_KEYSETID_LEN)
    {
        HI_LOGE("vKeySetId.size() = %d Too Long!\n", vKeySetId.size());
        goto errorRet;
    }

    memset(keySetId, 0, HI_DRMENGINE_KEY_LEN);
    *pKeySetIdLen = 0;

    VectorToArray(vKeySetId, keySetId, pKeySetIdLen);

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return ret;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_S32 HI_DrmEngine_getPropertyString(__in  const HI_VOID* v_pDrmHandle,
                                      __in  const HI_U8* name,
                                      __in  const HI_U32 nameLen,
                                      __out HI_U8* value,
                                      __out HI_U32* pValueLen)
{
    FUNC_ENTER_PRINT;
    HI_S32 ret = HI_FAILURE;

    String8 str8_name;
    String8 str8_value;

    HI_DRM_HANDLE* pDrmHandle = HI_NULL;
    ModularDrmInterface* pDrm = HI_NULL;

    CHECK_NULLPTR(v_pDrmHandle);
    CHECK_NULLPTR(name);

    if (0 == nameLen || nameLen > MAX_PROPERTY_NAME_LEN)
    {
        HI_LOGE("%s name len = %d is invalid\n", nameLen);
        return HI_FAILURE;
    }

    DRM_HANDLE_COUNT_CHECK;

    ArrayToString8(name, nameLen, str8_name);

    MODULE_LOCK;

    HI_LOGI("begin getDrmHandle\n");
    if(HI_SUCCESS != getDrmHandle(pDrmHandle, v_pDrmHandle))
    {
        HI_LOGE("getDrmHandle error\n");
        goto errorRet;
    }

    if(HI_NULL == pDrmHandle->pInterface)
    {
        HI_LOGE("pDrmHandle->pInterface nullptr error\n");
        goto errorRet;
    }

    pDrm = pDrmHandle->pInterface;

    DRM_HANDLE_INFO_PRINT(pDrmHandle);

    HI_LOGI("begin getPropertyString\n");

    ret = pDrm->getPropertyString(str8_name, str8_value);
    if (HI_SUCCESS != ret)
    {
        HI_LOGE("getPropertyString error return = %d\n",ret);
        MODULE_UNLOCK;
        return ret;
    }

    if (str8_value.isEmpty() || str8_value.size() > MAX_PROPERTY_VALUE_LEN)
    {
        HI_LOGE("%s: value len = %d is invalid", str8_value.size());
        goto errorRet;
    }

    String8ToArray(str8_value, value, pValueLen);

    HI_LOGD("getPropertyString, value = %s, len = %d\n", value, *pValueLen);

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return ret;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_S32 HI_DrmEngine_setPropertyString(__in  const HI_VOID* v_pDrmHandle,
                                      __in  const HI_U8* name,
                                      __in  const HI_U32 nameLen,
                                      __in  const HI_U8* value,
                                      __in  const HI_U32 valueLen)
{
    FUNC_ENTER_PRINT;
    HI_S32 ret = HI_FAILURE;

    String8 str8_name;
    String8 str8_value;

    HI_DRM_HANDLE* pDrmHandle = HI_NULL;
    ModularDrmInterface* pDrm = HI_NULL;

    CHECK_NULLPTR(v_pDrmHandle);
    CHECK_NULLPTR(name);
    CHECK_NULLPTR(value);

    if (0 == nameLen || nameLen > MAX_PROPERTY_NAME_LEN)
    {
        HI_LOGE("%s name len = %d is invalid", nameLen);
        return HI_FAILURE;
    }

    if (0 == valueLen || valueLen > MAX_PROPERTY_VALUE_LEN)
    {
        HI_LOGE("%s value len = %d is invalid", valueLen);
        return HI_FAILURE;
    }

    DRM_HANDLE_COUNT_CHECK;

    ArrayToString8(name, nameLen, str8_name);
    ArrayToString8(value, valueLen, str8_value);

    MODULE_LOCK;

    HI_LOGI("begin getDrmHandle\n");
    if(HI_SUCCESS != getDrmHandle(pDrmHandle, v_pDrmHandle))
    {
        HI_LOGE("getDrmHandle error");
        goto errorRet;
    }

    if(HI_NULL == pDrmHandle->pInterface)
    {
        HI_LOGE("pDrmHandle->pInterface nullptr error");
        goto errorRet;
    }

    pDrm = pDrmHandle->pInterface;

    DRM_HANDLE_INFO_PRINT(pDrmHandle);

    HI_LOGI("begin setPropertyString\n");

    ret = pDrm->setPropertyString(str8_name, str8_value);
    if (HI_SUCCESS != ret)
    {
        HI_LOGE("setPropertyString error return = %d\n",ret);
        MODULE_UNLOCK;
        return ret;
    }

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return ret;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_S32 HI_DrmEngine_cryptoCreate(__in  const HI_DRMENGINE_SESSION session,
                                 __in  const HI_U8 uuid[HI_DRMENGINE_UUID_LEN])
{
    FUNC_ENTER_PRINT

    HI_CRYPTO_HANDLE* pCryptoHandle = HI_NULL;
    CryptoInterface* pCrypto = HI_NULL;

    CHECK_NULLPTR(uuid);
    CHECK_NULLPTR(session.sessionId);

    CHECK_ZEROLEN(session.sessionIdLen);

//----------- crypto list init check---------------
    SESSION_COUNT_CHECK;

    if(s_hiHandleInfo.crypto.handle_count > MAX_CRYPTO_HANDLE_COUNT)
    {
         HI_LOGE("crypto Handle Count = %d error!\n", s_hiHandleInfo.crypto.handle_count);
         return HI_FAILURE;
    }

    if(0 == s_hiHandleInfo.crypto.handle_count)
    {
        HI_LOGD("begin Crypto_Init\n");
        Crypto_Init();
    }

    MODULE_LOCK;
//--------------------get crypto handle-----------------------------
    //ensure sessionId is not exist in crypto list
    //cryptoInterface and sessionId are add/delete in crypto list at same time
    if(HI_SUCCESS == getCryptoHandle(pCryptoHandle, session))
    {
        HI_LOGE("session exist in crypto list, error!\n");
        goto errorRet;
    }

//-------------------create crypto handle--------------------------
    HI_LOGI("begin create cypto handle\n");

    pCryptoHandle = new HI_CRYPTO_HANDLE;

    if(HI_NULL == pCryptoHandle)
    {
        HI_LOGE("pCryptoHandle nullptr error!\n");
        goto errorRet;
    }

    memset(pCryptoHandle, 0, sizeof(HI_CRYPTO_HANDLE));

//-------------------begin CryptoInterface::Create-----------------
    HI_LOGI("begin CryptoInterface::Create\n");

    pCrypto = CryptoInterface::Create(uuid, session.sessionId, session.sessionIdLen);
    if(HI_NULL == pCrypto)
    {
        HI_LOGE("pCrypto = CryptoInterface::Create nullprt! pCrypto = %p\n", pCrypto);
        delete pCryptoHandle;
        pCryptoHandle = HI_NULL;
        goto errorRet;
    }

//---------------------update crypto handle------------------------
    pCryptoHandle->session.sessionIdLen = session.sessionIdLen;
    memcpy(pCryptoHandle->session.sessionId, session.sessionId, session.sessionIdLen);
    //memcpy(&(pCryptoHandle->session), &session, sizeof(HI_DRMENGINE_SESSION));

    pCryptoHandle->pInterface = pCrypto;

//-------------------add to crypto list, add count-----------------
    HI_List_Add(&(pCryptoHandle->list),&(s_hiHandleInfo.crypto.handle_head.list));
    s_hiHandleInfo.crypto.handle_count++;

    CRYPTO_HANDLE_INFO_PRINT(pCryptoHandle);

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return HI_SUCCESS;

errorRet:
    if(0 == s_hiHandleInfo.crypto.handle_count)
    {
        HI_LOGD("begin crypto list deInit\n");
        Crypto_DeInit();
    }

    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_S32 HI_DrmEngine_cryptoDestroy(__in const HI_DRMENGINE_SESSION session)

{
    FUNC_ENTER_PRINT;

    HI_CRYPTO_HANDLE* pCryptoHandle = HI_NULL;
    CryptoInterface* pCrypto = HI_NULL;
    HI_S32 ret = HI_FAILURE;

    CHECK_NULLPTR(session.sessionId);

    CHECK_ZEROLEN(session.sessionIdLen);

    SESSION_COUNT_CHECK;
    CRYPTO_HANDLE_COUNT_CHECK;

    MODULE_LOCK;
//-------------------- get crypto handle-------------------
    HI_LOGI("begin get cryptoHandle\n");

    if(HI_SUCCESS != getCryptoHandle(pCryptoHandle, session))
    {
        HI_LOGE("session not exist in crypto list, error!\n");
        goto errorRet;
    }

    if(HI_NULL == pCryptoHandle->pInterface)
    {
        HI_LOGE("pCryptoHandle->pInterface nullptr error!\n");
        goto errorRet;
    }

    pCrypto = pCryptoHandle->pInterface;

    CRYPTO_HANDLE_INFO_PRINT(pCryptoHandle);

//--------------------begin Crypto Destroy-----------------
    HI_LOGI("begin CryptoInterface::Destroy\n");

    ret = CryptoInterface::Destroy(pCrypto);

    if(HI_SUCCESS != ret)
    {
        HI_LOGE("CryptoInterface::Destroy error = %d\n", ret);
        goto errorRet;
    }

//---------------delete drm handle Node in list------------
    HI_List_Del(&pCryptoHandle->list);
    s_hiHandleInfo.crypto.handle_count--;

    memset(pCryptoHandle, 0 , sizeof(HI_CRYPTO_HANDLE));
    delete pCryptoHandle;
    pCryptoHandle = HI_NULL;

    if(0 == s_hiHandleInfo.crypto.handle_count)
    {
        HI_LOGI("begin crypto list deInit\n");
        Crypto_DeInit();
    }

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return HI_SUCCESS;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

HI_BOOL HI_DrmEngine_requiresSecureDecoderComponent(__in const HI_DRMENGINE_SESSION session,
                                                    __in const HI_CHAR* mime)
{
    FUNC_ENTER_PRINT;

    HI_CRYPTO_HANDLE* pCryptoHandle = HI_NULL;
    CryptoInterface* pCrypto = HI_NULL;
    HI_BOOL ret = HI_FALSE;

    CHECK_NULLPTR_BOOL(session.sessionId);
    CHECK_NULLPTR_BOOL(mime);

    CHECK_ZEROLEN_BOOL(session.sessionIdLen);

//SESSION_COUNT_CHECK
   if((0 == s_hiHandleInfo.session_count)
      || (s_hiHandleInfo.session_count > MAX_SESSION_COUNT))
    {
        HI_LOGE("SessionCount = %d error!\n", s_hiHandleInfo.session_count);
        return HI_FALSE;
    }

//CRYPTO_HANDLE_COUNT_CHECK;
    if((0 == s_hiHandleInfo.crypto.handle_count)
       || (s_hiHandleInfo.crypto.handle_count > MAX_CRYPTO_HANDLE_COUNT))
    {
         HI_LOGE("CryptoHandleCount = %d error!\n",s_hiHandleInfo.crypto.handle_count);
         return HI_FALSE;
    }

    MODULE_LOCK;
//-------------------- get crypto handle-------------------
    HI_LOGI("begin get cryptoHandle\n");

    if(HI_SUCCESS != getCryptoHandle(pCryptoHandle, session))
    {
        HI_LOGE("session not exist in crypto list, error!\n");
        goto errorRet;
    }

    if(HI_NULL == pCryptoHandle->pInterface)
    {
        HI_LOGE("pCryptoHandle->pInterface nullptr error!\n");
        goto errorRet;
    }

    pCrypto = pCryptoHandle->pInterface;

    CRYPTO_HANDLE_INFO_PRINT(pCryptoHandle);

//-------------------- do requiresSecureDecoderComponent-------------------
    HI_LOGD("begin requires Secure Decoder Component\n");

    ret = pCrypto->requiresSecureDecoderComponent(mime);
    if(HI_TRUE != ret)
    {
        HI_LOGE("requiresSecureDecoderComponent ret=%d false!\n");
        goto errorRet;
    }

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return HI_TRUE;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FALSE;
}

HI_S32  HI_DrmEngine_decrypt(__in  const HI_DRMENGINE_SESSION session,
                             __in  HI_BOOL secure,
                             __in  const HI_U8 key[HI_DRMENGINE_KEY_LEN],
                             __in  const HI_U8 iv[HI_DRMENGINE_IV_LEN],
                             __in  HI_DRMENGINE_CRYPTO_MODE drmEngineMode,
                             __in  const HI_DRMENGINE_PATTERN* drmEnginePattern,
                             __in  const HI_VOID* pSrc,
                             __in  HI_S32 s32srcSize,
                             __in  const HI_DRMENGINE_SUBSAMPLES* drmEngineSubSamples,
                             __in  HI_S32 numSubSamples,
                             __out HI_VOID* pDst,
                             __out HI_U8* errorDetailMsg,
                             __out HI_U32* pErrorDetailMsgLen)
{
    FUNC_ENTER_PRINT;

    HI_S32 ret = HI_FAILURE;
    String8 str8ErrorDetailMsg;

    HI_CRYPTO_HANDLE* pCryptoHandle = HI_NULL;
    CryptoInterface* pCrypto = HI_NULL;

    CHECK_NULLPTR(session.sessionId);
    CHECK_NULLPTR(key);
    CHECK_NULLPTR(iv);
    CHECK_NULLPTR(pSrc);
    CHECK_NULLPTR(drmEngineSubSamples);
    CHECK_NULLPTR(pDst);
    CHECK_NULLPTR(errorDetailMsg);
    CHECK_NULLPTR(pErrorDetailMsgLen);

    CHECK_ZEROLEN(session.sessionIdLen);

    HI_CRYPTO_MODE mode = (HI_CRYPTO_MODE)(drmEngineMode);
    HI_DRM_SUBSAMPLES* subSamples = (HI_DRM_SUBSAMPLES*)(drmEngineSubSamples);

//input numSubSamples len check, S32
    if(numSubSamples <= 0 || numSubSamples > MAX_SUBSAMPLE_NUM)
    {
        HI_LOGE("numSubSamples = %d err!\n", numSubSamples);
        return HI_FAILURE;
    }

    HI_U32 sum_SubSamples_count = 0;
    HI_U32 sum_SubSamples_clear_count = 0;
    HI_U32 sum_SubSamples_encrypt_count = 0;
    HI_U32 U32_numSubSamples = (HI_U32)numSubSamples;

//input subsample info check
    for(HI_U32 i=0; i < U32_numSubSamples; i++)
    {
        if(subSamples[i].u32numBytesOfClearData > MAX_SUBSAMPLE_LEN
           || subSamples[i].u32numBytesOfEncryptedData > MAX_SUBSAMPLE_LEN)
        {
            HI_LOGE("clear:%d, encrypt:%d over MAX len check\n",
                        subSamples[i].u32numBytesOfClearData,
                        subSamples[i].u32numBytesOfEncryptedData);
            return HI_FAILURE;
        }

        //input subsample all zero len check
        if(0 == subSamples[i].u32numBytesOfClearData
           && 0 == subSamples[i].u32numBytesOfEncryptedData)
        {
            HI_LOGE("clear:%d, encrypt:%d all zero LEN\n",
                        subSamples[i].u32numBytesOfClearData,
                        subSamples[i].u32numBytesOfEncryptedData);
            return HI_FAILURE;
        }
        //clear, encrypt, and total len sum up
        sum_SubSamples_count += subSamples[i].u32numBytesOfClearData;
        sum_SubSamples_clear_count += subSamples[i].u32numBytesOfClearData;

        sum_SubSamples_count += subSamples[i].u32numBytesOfEncryptedData;
        sum_SubSamples_encrypt_count += subSamples[i].u32numBytesOfEncryptedData;

        HI_LOGI("clear:%d, encrypt:%d\n",
                    subSamples[i].u32numBytesOfClearData,
                    subSamples[i].u32numBytesOfEncryptedData);

    }

    HI_LOGD("secure = %d, mode = %d\n", secure, mode);
    HI_LOGD("clear_count = %d, encrypt_count = %d, sum_SubSamples_count = %d\n",
                sum_SubSamples_clear_count,
                sum_SubSamples_encrypt_count,
                sum_SubSamples_count);

    SESSION_COUNT_CHECK;
    CRYPTO_HANDLE_COUNT_CHECK;

#if defined(STREAM_DEBUG)
    fwrite(pSrc, s32srcSize, 1, stream_input_full);
    if(HI_TRUE == secure)
    {
        fwrite(pSrc, s32srcSize, 1, stream_input_secure);
    }
    else if(HI_FALSE == secure)
    {
        fwrite(pSrc, s32srcSize, 1, stream_input_notsecure);
    }
#endif

    MODULE_LOCK;
//-------------------- get crypto handle-------------------
    HI_LOGI("begin get cryptoHandle\n");

    if(HI_SUCCESS != getCryptoHandle(pCryptoHandle, session))
    {
        HI_LOGE("session not exist in crypto list, error!\n");
        goto errorRet;
    }

    if(HI_NULL == pCryptoHandle->pInterface)
    {
        HI_LOGE("pCryptoHandle->pInterface nullptr error!\n");
        goto errorRet;
    }

    pCrypto = pCryptoHandle->pInterface;

    CRYPTO_HANDLE_INFO_PRINT(pCryptoHandle);

//--------------------begin decrypt--------------------------------
    HI_LOGI("begin decrypt\n");

    //the ret of decrypt is the totally processed size
    ret = pCrypto->decrypt(secure, key, iv, mode, pSrc, s32srcSize,
                                     subSamples, numSubSamples, pDst,
                                     str8ErrorDetailMsg);

#if defined(STREAM_DEBUG)
    if(HI_FALSE == secure)
    {
        fwrite(pDst, s32srcSize, 1, stream_output_notsecure);
    }
#endif
    //decrypt error result ret < 0
    if (ret < 0)
    {
        HI_LOGE("%s %d decrypt ret = %d\n", __FUNCTION__, __LINE__, ret);
        MODULE_UNLOCK;
        return ret;
    }

    memset(errorDetailMsg, 0, MAX_ERRORMSG_LEN);
    *pErrorDetailMsgLen = 0;
    String8ToArray(str8ErrorDetailMsg, errorDetailMsg, pErrorDetailMsgLen);

    MODULE_UNLOCK;
    FUNC_RETURN_PRINT;
    return ret;

errorRet:
    MODULE_UNLOCK;
    FUNC_RETURN_ERROR_PRINT;
    return HI_FAILURE;
}

/*************************** end implement ************************/

#ifdef __cplusplus
}
#endif
