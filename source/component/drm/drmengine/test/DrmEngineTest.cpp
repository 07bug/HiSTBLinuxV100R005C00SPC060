//
// Copyright 2013 Google Inc. All Rights Reserved.
//

#define LOG_NDEBUG 0
#define LOG_TAG "PluginTest"
#include <utils/Logger.h>

#include <DrmAPI.h>
#include <CryptoAPI.h>
#include <AString.h>
#include <DrmErrors.h>
#include <utils/String16.h>
#include <utils/String8.h>
#include <utils/Vector.h>
#include <dlfcn.h>
#include <ModularDrmInterface.h>
#include <ModularDrmInterfaceImpl.h>
#include <CryptoInterface.h>
#include <CryptoInterfaceImpl.h>
#include <string>
#include <stdlib.h>

#include "DrmEngine.h"
#include "HTTPUtil.h"
#include "PsshInitData.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TEST_INFO(fmt, args...) printf("%s(), %d: " fmt, __FUNCTION__,__LINE__, ## args)
#define TEST_FAIL    (1)
#define TEST_SUCCESS (0)

#define MAX_INITDATA_LEN (1000)
#define MAX_ERRORDETAILMSG_LEN (128)
#define MAX_LICENSERSP_LEN  (10000)

//set multi handle para
#define DRM_NUM (2)
#define SESSION_NUM (2)

#define PLAYREADY_DEFAULT_LICENSE_URL "http://playready.directtaps.net/pr/svc/rightsmanager.asmx"

#define ASSERT_TRUE(A) \
    if (false == (A)) \
    { \
    HI_LOGE("tested line not pass!\n"); \
    }

#define ASSERT_EQ(A, B) \
    if ((A) != (B)) \
    { \
    HI_LOGE("tested line not pass!\n"); \
    }

#define EXPECT_TRUE(A) \
    if (false == (A)) \
    { \
    HI_LOGE("tested line not pass!\n"); \
    return TEST_FAIL; \
    }

#define EXPECT_FALSE(A) \
    if (true == (A)) \
    { \
    HI_LOGE("tested line not pass!\n"); \
    return TEST_FAIL; \
    }

#define EXPECT_EQ(A, B) \
    if ((A) != (B)) \
    { \
    HI_LOGE("tested line not pass!\n"); \
    return TEST_FAIL; \
    }

#define EXPECT_NE(A, B) \
    if ((A) == (B)) \
    { \
    HI_LOGE("tested line not pass!\n"); \
    return TEST_FAIL; \
    }

#define EXPECT_GT(A, B) \
    if ((A) <= (B)) \
    { \
    HI_LOGE("tested line not pass!\n"); \
    return TEST_FAIL; \
    }

#define CHECK_NULLPTR(ptr) { \
    if (HI_NULL == (ptr)) \
    { \
    HI_LOGE("%s %d nullptr error!\n", __FUNCTION__, __LINE__); \
    return HI_FAILURE; \
    } \
}

namespace {

    using android::String8;
    using std::string;

    static HI_U32 drmclose_FLAG = 0;
    static HI_U32 decryptclose_FLAG = 0;

    static HI_S32 VectorToArray(const Vector<HI_U8> &vectorData,
        HI_U8* arrayData, HI_U32* arrayLen)
    {
        CHECK_NULLPTR(arrayData);
        CHECK_NULLPTR(arrayLen);

#if 1
        printf("------input vectorData------\n");
        for(HI_U32 i=0;i<vectorData.size();i++)
        {
            printf("%c",vectorData[i]);
        }
        printf("\n------length:%d------\n",vectorData.size());
#endif

        if(!vectorData.isEmpty())
        {
            *arrayLen = vectorData.size();
            memcpy(arrayData, &vectorData[0], *arrayLen + 1);
        }
#if 1
        printf("------VectorToArray result------\n");
        for(HI_U32 i=0;i<*arrayLen;i++)
        {
            printf("%c",arrayData[i]);
        }
        printf("\n------length:%d------\n",*arrayLen);
#endif
        return HI_SUCCESS;
    }

     static HI_S32 ArrayToVector(const HI_U8* arrayData, const HI_U32 arrayLen,
         Vector<HI_U8> &vectorData)
     {
         CHECK_NULLPTR(arrayData);
         vectorData.clear();
         vectorData.appendArray(arrayData, arrayLen);
         return HI_SUCCESS;
     }

     static HI_S32 String8ToArray(const String8 &string8Data,
         HI_U8* arrayData, HI_U32* arrayDataLen )
     {
         const HI_U8 *charData  = reinterpret_cast<const uint8_t*>(string8Data.string());
         *arrayDataLen = string8Data.length();
         memcpy(arrayData, charData, *arrayDataLen + 1);
         arrayData[*arrayDataLen] = '\0';
         return HI_SUCCESS;
     }

     static HI_S32 ArrayToString8(const HI_U8 &arrayData, String8 *string8Data)
     {
         /*will  be implemented if necessary*/
         return HI_SUCCESS;
     }

    static void printVector(const Vector<HI_U8> &vectorData)
    {
        HI_U32 len= vectorData.size();
        printf("vector=");
        for(HI_U32 i=0;i<len;i++)
        {
            printf("%c",vectorData[i]);
        }
        printf("\nlenght=%d\n",len);
    }

    bool extractElement(const String8& xmlData, const String8& attribute, String8* element)
    {
        const static char* openFormat = "<%s>";
        const String8 openTag = String8::format(openFormat, attribute.string());
        ssize_t start = xmlData.find(openTag);
        if (start < 0) {
            HI_LOGE("Cannot find %s", openTag.string());
            return false;
        }
        start += openTag.size();

        const static char* closeFormat = "</%s>";
        const String8 closeTag = String8::format(closeFormat, attribute.string());
        ssize_t end = xmlData.find(closeTag, start);
        if (end < 0) {
            HI_LOGE("Cannot find %s", closeTag.string());
            return false;
        }

        element->setTo(&xmlData.string()[start], end - start);
        return true;
    }

    Vector<uint8_t> getInitData(const String8& drmHeaderXml)
    {
        String16 drmHeader(drmHeaderXml);
        Vector<uint8_t> initData;
        initData.appendArray(reinterpret_cast<const uint8_t*>(drmHeader.string()),
            drmHeader.size() * sizeof(drmHeader[0]));
        return initData;
    }

    inline String8 getString8FromUtf16String(const android::Vector<uint8_t>& utf16Array)
    {
        return String8(reinterpret_cast<const char16_t*>(utf16Array.array()),
            utf16Array.size() / sizeof(char16_t));
    }

    HI_U8 verifyLicenseRequest(HI_DRMENGINE_KEY_REQUEST* keyRequest, const Vector<uint8_t>& drmHeader)
    {
        HI_DRM_KEYREQUEST_TYPE eKeyRequestType =
            (HI_DRM_KEYREQUEST_TYPE)(keyRequest->eKeyRequestType);
        HI_LOGD("eKeyRequestType:%d", eKeyRequestType);
        EXPECT_EQ(eKeyRequestType, HI_DRM_KEYRST_TYPE_INITIAL);

        String8 defaultUrl(keyRequest->defaultUrl,strlen(keyRequest->defaultUrl));
        HI_LOGD("defaultUrl:%s", defaultUrl.string());
        String8 expectUrl(PLAYREADY_DEFAULT_LICENSE_URL);
        EXPECT_EQ(defaultUrl, expectUrl);

        const String8 requestXml(reinterpret_cast<const char*>(keyRequest->requestData),
                                   keyRequest->requestDataLen);
        String8 challenge;
        EXPECT_TRUE(extractElement(requestXml, String8("challenge"), &challenge));
        String8 contentHeader;
        EXPECT_TRUE(extractElement(challenge, String8("ContentHeader"), &contentHeader));

        const String8 drmHeaderXml(getString8FromUtf16String(drmHeader));
        EXPECT_TRUE(drmHeaderXml.find(contentHeader.string()) >= 0);

        return TEST_SUCCESS;
    }

    // Got license header xml from Microsoft Test server
    // $ curl -O http://playready.directtaps.net/smoothstreaming/SSWSS720H264PR/SuperSpeedway_720.ism/Manifest
    // $ xmlstarlet sel -t -m '//ProtectionHeader[1]' -v . -n < Manifest | base64 -d
    const String8 kTestDrmHeaderXml(
        "<WRMHEADER xmlns=\"http://schemas.microsoft.com/DRM/2007/03/PlayReadyHeader\" version=\"4.0.0.0\">"
        "<DATA><PROTECTINFO><KEYLEN>16</KEYLEN><ALGID>AESCTR</ALGID></PROTECTINFO>"
        "<KID>AmfjCTOPbEOl3WD/5mcecA==</KID><CHECKSUM>BGw1aYZ1YXM=</CHECKSUM>"
        "<CUSTOMATTRIBUTES><IIS_DRM_VERSION>7.1.1064.0</IIS_DRM_VERSION></CUSTOMATTRIBUTES>"
        "<LA_URL>http://playready.directtaps.net/pr/svc/rightsmanager.asmx</LA_URL>"
        "<DS_ID>AH+03juKbUGbHl1V/QIwRA==</DS_ID>"
        "</DATA></WRMHEADER>");

    const String8 kInvalidTestDrmHeaderXml(
        "<WRMHEADER xmlns=\"http://schemas.microsoft.com/DRM/2007/03/PlayReadyHeader\" version=\"4.0.0.0\">"
        "<DATA><PROTECTINFO><KEYLEN>16</KEYLEN><ALGID>AESCTR</ALGID></PROTECTINFO>"
        // remove KID to corrupt DrmHeader
        //"<KID>AmfjCTOPbEOl3WD/5mcecA==</KID><CHECKSUM>BGw1aYZ1YXM=</CHECKSUM>"
        "<CUSTOMATTRIBUTES><IIS_DRM_VERSION>7.1.1064.0</IIS_DRM_VERSION></CUSTOMATTRIBUTES>"
        "<LA_URL>http://playready.directtaps.net/pr/svc/rightsmanager.asmx</LA_URL>"
        "<DS_ID>AH+03juKbUGbHl1V/QIwRA==</DS_ID>"
        "</DATA></WRMHEADER>");

    const String8 kPluginPath("/vendor/lib/mediadrm/libplayreadydrmplugin.so");

    const HI_U8 kRandomUuid[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    };

    const HI_U8 kPlayReadyUuid[16] = {
        0x9a, 0x04, 0xF0, 0x79, 0x98, 0x40, 0x42, 0x86,
        0xAB, 0x92, 0xE6, 0x5B, 0xE0, 0x88, 0x5F, 0x95
    };

    const HI_U8 kTestKeyId[16] = {
        0x09, 0xe3, 0x67, 0x02, 0x8f, 0x33, 0x43, 0x6c,
        0xa5, 0xdd, 0x60, 0xff, 0xe6, 0x67, 0x1e, 0x70
    };

    const HI_U8 kTestIv[16] = {
        0xf4, 0xb3, 0x10, 0x77, 0x75, 0x3e, 0x8b, 0x90,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    const HI_U8 kTestData[10] = {
        0x06, 0xf5, 0xd0, 0xad, 0x80, 0x3d, 0x62, 0xc7, 0xbd, 0xf5
    };

    const HI_U8 kTestResult[10] = {
        0x21, 0x0a, 0x90, 0x28, 0x7d, 0x60, 0x14, 0x3e, 0xb1, 0xc0
    };

    const HI_U8 kInvalidKeyId[16] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };
} // namespace anonymous

namespace android {

    class ModularInterfaceTest
    {
    public:
        ModularInterfaceTest();
        HI_U8 isCryptoSchemeSupported();
        HI_U8 OpenSession();
        HI_U8 GenerateKeyRequest();
        HI_U8 GenerateKeyRequestWithInvalidHeader();
        HI_U8 GenerateKeyRequestWithCustomData();
        HI_U8 Decrypt();
        HI_U8 drmEngineDecryptPrepare(HI_VOID* v_pDrmHandle, HI_DRMENGINE_SESSION session)
        {
            HI_LOGD("ENTER\n");
            HI_LOGD("pDrmHandle = %p, sessionId = %s, Len = %d\n",v_pDrmHandle, session.sessionId,session.sessionIdLen);

            HI_U8 initData[MAX_INITDATA_LEN];
            HI_U32 initDataLen = 0;

            //HI_U8 licenseResponse[MAX_LICENSERSP_LEN];
            HI_U8* licenseResponse;
            HI_U32 licenseResponseLen = 0;

            HI_U8 keySetId[MAX_KEYSETID_LEN];
            HI_U32 keySetIdLen = 0;

            Vector<HI_U8> vInitData = getInitData(kTestDrmHeaderXml);

            VectorToArray(vInitData, initData, &initDataLen);

            HI_DRMENGINE_KEY_REQUEST keyRequest;
            HI_CHAR const* mimeType ="video/mp4";

            EXPECT_EQ(OK, HI_DrmEngine_getKeyRequest(v_pDrmHandle, session,
                initData, initDataLen,
                mimeType,
                (HI_DRMENGINE_KEY_TYPE)(DrmPlugin::kKeyType_Streaming),
                &keyRequest));

            verifyLicenseRequest(&keyRequest, vInitData);

            Vector<HI_U8> vLicenseResponse;
            const String8 kSoapAction("http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");

            EXPECT_TRUE(DoSoapAction(String8(keyRequest.defaultUrl, strlen(keyRequest.defaultUrl)),
                                     kSoapAction,
                                      String8(reinterpret_cast<const char*>(keyRequest.requestData), keyRequest.requestDataLen),
                                    &vLicenseResponse));

            licenseResponse = (HI_U8*)malloc(vLicenseResponse.size());
            VectorToArray(vLicenseResponse, licenseResponse, &licenseResponseLen);

            EXPECT_EQ(OK,HI_DrmEngine_provideKeyResponse(v_pDrmHandle,
                                                                 session,
                                                                 licenseResponse, licenseResponseLen,
                                                                 keySetId, &keySetIdLen));

            free(licenseResponse);

            return TEST_SUCCESS;
        }

        HI_U8 Setup()
        {
            HI_LOGD("ENTER\n");

            HI_LOGD("Set drmNum = %d, sessionNum = %d\n", drmNum, sessionNum);

            for(HI_U32 i=0;i<drmNum;i++)
            {
                pDrmHandleSet[i] = HI_NULL;
                HI_DrmEngine_Create(&pDrmHandleSet[i], kPlayReadyUuid);
            }

            return TEST_SUCCESS;
        }

        HI_U8 TearDown()
        {
            HI_LOGD("ENTER\n");

            for(HI_U32 i=0;i<drmNum;i++)
            {
                EXPECT_EQ(OK, HI_DrmEngine_Destroy(pDrmHandleSet[i]));
            }

           // EXPECT_NE(OK, HI_DrmEngine_Destroy(pDrmHandleSet[1]));

            return TEST_SUCCESS;
        }

        HI_U8 DecryptSetup()
        {
            HI_LOGD("ENTER\n");

            HI_LOGD("Set drmNum = %d, sessionNum = %d\n", drmNum, sessionNum);

            HI_U32 i = 0;
            HI_U32 j = 0;

            for(i = 0; i < drmNum; i++)
           {
                pDrmHandleSet[i] = HI_NULL;
                HI_DrmEngine_Create(&pDrmHandleSet[i], kPlayReadyUuid);
                for(j = 0; j < sessionNum; j++)
                {
                    EXPECT_EQ(OK, HI_DrmEngine_openSession(pDrmHandleSet[i],
                                &sessionDecrypt[0]));
                }
            }

           for(i = 0; i < drmNum; i++)
           {
               for(j = 0; j < sessionNum; j++)
               {
                        EXPECT_EQ(OK, drmEngineDecryptPrepare(pDrmHandleSet[i],
                               sessionDecrypt[i*drmNum + j]));
               }
           }

           for(i = 0; i < drmNum; i++)
           {
               for(j = 0; j < sessionNum; j++)
               {
                         EXPECT_EQ(OK, HI_DrmEngine_cryptoCreate(sessionDecrypt[i*drmNum + j],
                                kPlayReadyUuid));
               }
           }

            return TEST_SUCCESS;
        }
        HI_U8 DecryptTearDown()
        {
           HI_LOGD("ENTER\n");

           HI_U32 i = 0;
           HI_U32 j = 0;

           for(i = 0; i < drmNum; i++)
           {
               for(j = 0; j < sessionNum; j++)
               {
                   EXPECT_EQ(OK, HI_DrmEngine_cryptoDestroy(sessionDecrypt[i*drmNum + j]));
               }
           }

            for(i = 0; i < drmNum; i++)
            {
                for(j = 0; j < sessionNum; j++)
                {
                     EXPECT_EQ(OK, HI_DrmEngine_closeSession(pDrmHandleSet[i],
                                sessionDecrypt[i*drmNum + j]));
                }
                EXPECT_EQ(OK, HI_DrmEngine_Destroy(pDrmHandleSet[i]));

            }

            return TEST_SUCCESS;
        }

    private:
        HI_U32 drmNum = DRM_NUM;
        HI_U32 sessionNum = SESSION_NUM;

        HI_VOID* pDrmHandleSet[DRM_NUM];

        HI_DRMENGINE_SESSION sessionDecrypt[DRM_NUM*SESSION_NUM];
    };

    ModularInterfaceTest::ModularInterfaceTest()
    {
        char *drm_num = HI_NULL;
        char *session_num = HI_NULL;

        char *drm_close = HI_NULL;
        char *decrypt_close = HI_NULL;

        if(drm_num = getenv("DRM_NUM"))
        {
            drmNum =  atoi(getenv("DRM_NUM"));
            printf("set drmNum = %d\n", drmNum);
        }

        if(drm_num = getenv("SESSION_NUM"))
        {
            sessionNum =  atoi(getenv("SESSION_NUM"));
            printf("set drmNum = %d\n", sessionNum);
        }

        if(drm_close = getenv("DRM_CLOSE"))
        {
            drmclose_FLAG =  atoi(getenv("DRM_CLOSE"));
            printf("set drmclose_FLAG = %d\n", drmclose_FLAG);
        }

        if(decrypt_close = getenv("DECRYPT_CLOSE"))
        {
            decryptclose_FLAG = atoi(getenv("DECRYPT_CLOSE"));
            printf("set decryptclose_FLAG = %d\n", decryptclose_FLAG);
        }
    }

    HI_U8 ModularInterfaceTest::isCryptoSchemeSupported()
    {
        HI_LOGD("ENTER\n");

        const HI_CHAR* mimeType = "video/mp4";

        for(HI_U32 i=0; i<drmNum; i++)
        {
            EXPECT_TRUE(HI_DrmEngine_isCryptoSchemeSupported(pDrmHandleSet[i], kPlayReadyUuid, mimeType));
            EXPECT_FALSE(HI_DrmEngine_isCryptoSchemeSupported(pDrmHandleSet[i], kRandomUuid, mimeType));
        }

        return TEST_SUCCESS;
    }

    HI_U8 ModularInterfaceTest::OpenSession()
    {
        HI_LOGD("ENTER\n");

        HI_DRMENGINE_SESSION session[DRM_NUM*SESSION_NUM];

        for(HI_U32 i = 0; i < drmNum; i++)
        {
            for(HI_U32 j = 0; j < sessionNum; j++)
            {
                EXPECT_EQ(OK, HI_DrmEngine_openSession(pDrmHandleSet[i],
                    &session[i*sessionNum + j]));

            }
        }

        for(HI_U32 i = 0; i < drmNum; i++)
        {
            for(HI_U32 j = 0; j < sessionNum; j++)
            {
               EXPECT_EQ(OK, HI_DrmEngine_closeSession(pDrmHandleSet[i],
                       session[i*sessionNum + j]));
            }
        }

        return TEST_SUCCESS;
    }

    HI_U8 ModularInterfaceTest::GenerateKeyRequest()
    {
       HI_LOGD("ENTER\n");

       HI_DRMENGINE_SESSION session[DRM_NUM*SESSION_NUM];

       HI_U8 initData[MAX_INITDATA_LEN];
       HI_U32 initDataLen = 0;
       HI_U32* pInitDataLen = &initDataLen;

        EXPECT_EQ(OK, HI_DrmEngine_openSession(pDrmHandleSet[0], &session[0]));

        Vector<HI_U8> vInitData = getInitData(kTestDrmHeaderXml);
        VectorToArray(vInitData, initData, pInitDataLen);

        HI_DRMENGINE_KEY_REQUEST keyRequest;
        HI_CHAR const* mimeType ="video/mp4";

        EXPECT_EQ(OK, HI_DrmEngine_getKeyRequest(pDrmHandleSet[0], session[0],
            initData, initDataLen,
            mimeType,
            (HI_DRMENGINE_KEY_TYPE)(DrmPlugin::kKeyType_Streaming),
            &keyRequest));

        EXPECT_EQ(OK, HI_DrmEngine_closeSession(pDrmHandleSet[0], session[0]));

        return verifyLicenseRequest(&keyRequest, vInitData);
    }

    HI_U8 ModularInterfaceTest::GenerateKeyRequestWithInvalidHeader()
    {
        HI_LOGD("ENTER\n");

        HI_DRMENGINE_SESSION session[DRM_NUM*SESSION_NUM];

        HI_U8 invalidInitData[MAX_INITDATA_LEN];
        HI_U32 invalidInitDataLen = 0;
        HI_U32* pInvalidInitDataLen = &invalidInitDataLen;

        EXPECT_EQ(OK, HI_DrmEngine_openSession(pDrmHandleSet[0], &session[0]));

        Vector<HI_U8> vInvalidInitData = getInitData(kInvalidTestDrmHeaderXml);
        VectorToArray(vInvalidInitData, invalidInitData, pInvalidInitDataLen);

        HI_DRMENGINE_KEY_REQUEST keyRequest;

        HI_CHAR const* mimeType ="video/mp4";

        HI_S32 ret = HI_DrmEngine_getKeyRequest(pDrmHandleSet[0], session[0],
                invalidInitData, invalidInitDataLen,
                mimeType,
                (HI_DRMENGINE_KEY_TYPE)(DrmPlugin::kKeyType_Streaming),
                &keyRequest);

        printf("getKeyRequest ret in GenerateKeyRequestWithInvalidHeader:%d\n", ret);

        EXPECT_NE(OK, ret);

        EXPECT_EQ(OK, HI_DrmEngine_closeSession(pDrmHandleSet[0], session[0]));

        return TEST_SUCCESS;
    }

    HI_U8 ModularInterfaceTest::Decrypt()
    {
        HI_LOGD("ENTER\n");

        HI_DRMENGINE_SUBSAMPLES subSamples;
        subSamples.u32numBytesOfClearData = 0;
        subSamples.u32numBytesOfEncryptedData = 10;

        HI_U8 decryptData[10];
        memset(decryptData,0,sizeof(kTestResult));

        HI_U8 errorDetailMsg[MAX_ERRORDETAILMSG_LEN];
        HI_U32 errorDetailMsgLen = 0;
        HI_U32* pErrorDetailMsgLen;
        pErrorDetailMsgLen = &errorDetailMsgLen;

        HI_S32 ret = HI_FAILURE;

        HI_U32 count = 0;

        for(HI_U32 i = 0;i < drmNum * sessionNum; i++)
        {
//00
            count = 0;
            HI_LOGD("[session:%d]-----decrypt test %d------\n",i,count++);
            ret = HI_DrmEngine_decrypt(sessionDecrypt[i],
                                    HI_TRUE,
                                    kTestKeyId,
                                    kTestIv,
                                    HI_DRMENGINE_CRYPTO_MODE_AES_CTR,
                                    kTestData,
                                    10,
                                    &subSamples,
                                    1,
                                    decryptData,
                                    errorDetailMsg,
                                    pErrorDetailMsgLen);

            HI_LOGD("Return code of decrypt secure:%d", ret);
            EXPECT_NE(OK, ret);
            memset(decryptData,0,sizeof(kTestResult));

//01
            HI_LOGD("[session:%d]-----decrypt test %d------\n",i,count++);
            ret = HI_DrmEngine_decrypt(sessionDecrypt[i],
                HI_FALSE,
                kTestKeyId,
                kTestIv,
                HI_DRMENGINE_CRYPTO_MODE_AES_CTR,
                kTestData,
                10,
                &subSamples,
                -1,
                decryptData,
                errorDetailMsg,
                pErrorDetailMsgLen);

            HI_LOGD("Return code of decrypt secure:%d", ret);
            EXPECT_NE(OK, ret);
            memset(decryptData,0,sizeof(kTestResult));

//02
            HI_LOGD("[session:%d]-----decrypt test %d------\n",i,count++);
            ret = HI_DrmEngine_decrypt(sessionDecrypt[i],
                HI_FALSE,
                kTestKeyId,
                kTestIv,
                HI_DRMENGINE_CRYPTO_MODE_AES_CTR,
                kTestData,
                -1,
                &subSamples,
                1,
                decryptData,
                errorDetailMsg,
                pErrorDetailMsgLen);

            HI_LOGD("Return code of decrypt secure:%d", ret);
            EXPECT_NE(OK, ret);
            memset(decryptData,0,sizeof(kTestResult));

//03
            HI_LOGD("[session:%d]-----decrypt test %d------\n",i,count++);
            ret = HI_DrmEngine_decrypt(sessionDecrypt[i],
                HI_FALSE,
                kTestKeyId,
                kTestIv,
                HI_DRMENGINE_CRYPTO_MODE_AES_CTR,
                HI_NULL,
                10,
                &subSamples,
                1,
                decryptData,
                errorDetailMsg,
                pErrorDetailMsgLen);

            HI_LOGD("Return code of decrypt secure:%d", ret);
            EXPECT_NE(OK, ret);
            memset(decryptData,0,sizeof(kTestResult));

//04
            HI_LOGD("[session:%d]-----decrypt test %d------\n",i,count++);
            ret = HI_DrmEngine_decrypt(sessionDecrypt[i],
                HI_FALSE,
                kInvalidKeyId,
                kTestIv,
                HI_DRMENGINE_CRYPTO_MODE_AES_CTR,
                kTestData,
                10,
                &subSamples,
                1,
                decryptData,
                errorDetailMsg,
                pErrorDetailMsgLen);

            HI_LOGD("Return code of decrypt secure:%d", ret);
            EXPECT_NE(OK, ret);
            memset(decryptData,0,sizeof(kTestResult));

 //05
            HI_LOGD("[session:%d]-----decrypt test %d------\n",i,count++);
            ret = HI_DrmEngine_decrypt(sessionDecrypt[i],
                                        HI_FALSE,
                                        kTestKeyId,
                                        kTestIv,
                                        HI_DRMENGINE_CRYPTO_MODE_AES_CTR,
                                        kTestData,
                                        10,
                                        &subSamples,
                                        1,
                                        decryptData,
                                        errorDetailMsg,
                                        pErrorDetailMsgLen);

            HI_LOGD("Return code of decrypt non-secure:%d", ret);

            EXPECT_EQ(0, memcmp(decryptData, kTestResult, sizeof(kTestResult)));

            memset(decryptData,0,sizeof(kTestResult));
       }

        return TEST_SUCCESS;
    }

    void testModularInterface()
    {
        TEST_INFO("Test modualr interface start!\n");

        ModularInterfaceTest modualrInterfaceTest;

if(!drmclose_FLAG)
{
        if(modualrInterfaceTest.Setup())
        {
            TEST_INFO("[1] Setup failed.\n");
        }
        else
        {
            TEST_INFO("[1] Setup success.\n");
        }
        if(modualrInterfaceTest.isCryptoSchemeSupported())
        {
            TEST_INFO("[2] isCryptoSchemeSupported failed.\n");
        }
        else
        {
            TEST_INFO("[2] isCryptoSchemeSupported success.\n");
        }
        if(modualrInterfaceTest.OpenSession())
        {
            TEST_INFO("[3] OpenSession failed.\n");
        }
        else
        {
            TEST_INFO("[3] OpenSession success.\n");
        }
        if(modualrInterfaceTest.GenerateKeyRequest())
        {
            TEST_INFO("[4] GenerateKeyRequest failed.\n");
        }
        else
        {
            TEST_INFO("[4] GenerateKeyRequest success.\n");
        }
        if(modualrInterfaceTest.GenerateKeyRequestWithInvalidHeader())
        {
            TEST_INFO("[5] GenerateKeyRequestWithInvalidHeader failed.\n");
        }
        else
        {
            TEST_INFO("[5] GenerateKeyRequestWithInvalidHeader success.\n");
        }
        if(modualrInterfaceTest.TearDown())
        {
            TEST_INFO("[6] TearDown failed.\n");
        }
        else
        {
            TEST_INFO("[6] TearDown success.\n");
        }
}

//decrypt
if(!decryptclose_FLAG)
{
        if(modualrInterfaceTest.DecryptSetup())
        {
            TEST_INFO("[7] DecryptSetup failed.\n");
        }
        else
        {
            TEST_INFO("[7] DecryptSetup success.\n");
        }
        if(modualrInterfaceTest.Decrypt())
        {
            TEST_INFO("[8] Decrypt failed.\n");
        }
        else
        {
            TEST_INFO("[8] Decrypt success.\n");
        }
        if(modualrInterfaceTest.DecryptTearDown())
        {
            TEST_INFO("[9] DecryptTearDown failed.\n");
        }
        else
        {
            TEST_INFO("[9] DecryptTearDown success.\n");
        }
}

    }

}  // namespace android

int main(int argc, char** argv)
{
    testModularInterface();
    return 0;
}

#ifdef __cplusplus
}
#endif
