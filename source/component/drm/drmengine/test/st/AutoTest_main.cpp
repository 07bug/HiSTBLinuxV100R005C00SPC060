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
#include "HTTPSource.h"
#include "HTTPStream.h"
#include "HTTPUtil.h"
#include "PsshInitData.h"
#include <common_log.h>
#include "DrmSessionManager.h"
#include "DrmService.h"
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "DrmClient.h"
#include "ICrypto.h"
#include <dirent.h>

#define TEST_INFO(fmt, args...) printf("%s(), %d: " fmt, __FUNCTION__,__LINE__, ## args)
#define TEST_FAIL    1
#define TEST_SUCCESS 0
#define HI_LENGTH 500000
#define zero 0
#define sTime 500

ModularDrmInterface *ModularDrmInfo = HI_NULL;
ModularDrmInterface *ModularDrmInfo1 = HI_NULL;
ModularDrmInterface *ModularOtherDrmInfo = HI_NULL;
CryptoInterface *CryptoInfo = HI_NULL;
CryptoInterface *CryptoInfo1 = HI_NULL;
CryptoInterface *CryptoOtherInfo = HI_NULL;

HI_CHAR invalidXmlFilePath[] = "/mnt/bin/invalidResponse.txt";

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

HI_VOID Test_Destroy(HI_CHAR* pFunc,HI_S32 s32Line)
{
    if (HI_NULL != ModularDrmInfo)
    {
        ModularDrmInterface::Destroy(ModularDrmInfo);
        ModularDrmInfo = HI_NULL;
    }
    if (HI_NULL != ModularDrmInfo1)
    {
        ModularDrmInterface::Destroy(ModularDrmInfo1);
        ModularDrmInfo1 = HI_NULL;
    }
    if (HI_NULL != CryptoInfo)
    {
        CryptoInterface::Destroy(CryptoInfo);
        CryptoInfo = HI_NULL;
    }
    if (HI_NULL != CryptoInfo1)
    {
        CryptoInterface::Destroy(CryptoInfo1);
        CryptoInfo1 = HI_NULL;
    }
    if (HI_NULL != ModularOtherDrmInfo)
    {
        ModularDrmInterface::Destroy(ModularOtherDrmInfo);
        ModularOtherDrmInfo = HI_NULL;
    }
    if (HI_NULL != CryptoOtherInfo)
    {
        CryptoInterface::Destroy(CryptoOtherInfo);
        CryptoOtherInfo = HI_NULL;
    }
    HITEST_FinalResult(pFunc,s32Line);

    return;
}

namespace {

using android::String8;

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
//æ— æ•ˆivå‘é‡
const HI_U8 kInvalidTestIv[16] = {
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

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

Vector<HI_U8> getInitData(const String8& drmHeaderXml)
{
    String16 drmHeader(drmHeaderXml);
    Vector<HI_U8> initData;
    initData.appendArray(reinterpret_cast<const HI_U8*>(drmHeader.string()),drmHeader.size() * sizeof(drmHeader[0]));
    return initData;
}

 String8 getString8FromUtf16String(const android::Vector<HI_U8>& utf16Array)
{
    return String8(reinterpret_cast<const char16_t*>(utf16Array.array()),utf16Array.size() / sizeof(char16_t));
}

 HI_U8 verifyLicenseRequest(HI_DRM_KEY_REQUEST* keyRequest, const Vector<HI_U8>& drmHeader)
{
    HI_DRM_KEYREQUEST_TYPE eKeyRequestType = keyRequest->eKeyRequestType;
    HI_LOGD("eKeyRequestType:%d", eKeyRequestType);
    EXPECT_EQ(eKeyRequestType, HI_DRM_KEYRST_TYPE_INITIAL);

    String8 defaultUrl = keyRequest->defaultUrl;
    HI_LOGD("defaultUrl:%s", defaultUrl.string());
    String8 expectUrl("http://playready.directtaps.net/pr/svc/rightsmanager.asmx");
    EXPECT_EQ(defaultUrl, expectUrl);

    const String8 requestXml(reinterpret_cast<const char*>(keyRequest->requestData.array()),
                             keyRequest->requestData.size());
    String8 challenge;
    EXPECT_TRUE(extractElement(requestXml, String8("challenge"), &challenge));
    String8 contentHeader;
    EXPECT_TRUE(extractElement(challenge, String8("ContentHeader"), &contentHeader));

    const String8 drmHeaderXml(getString8FromUtf16String(drmHeader));
    EXPECT_TRUE(drmHeaderXml.find(contentHeader.string()) >= 0);

    return TEST_SUCCESS;
}

/*******************************************************************************
* FuncName     : get_response_from_file
* FuncItem    : ä»Žæ–‡ä»¶èŽ·å–response.
* InputParameters   : FilePath
* OutputParameters : FilePath
* retval                   :
*******************************************************************************/
HI_BOOL get_response_from_file(HI_CHAR* FilePath,Vector<HI_U8> & response)
{
    FILE* pResponseFile = NULL;
    HI_S32 len;
    HI_U8* pszString = NULL;
    pResponseFile = fopen((char *)FilePath, "rb");
    if (pResponseFile == NULL)
    {
        printf("open file %s fail \n",FilePath);
        return HI_FALSE;
    }
    fseek(pResponseFile, 0, SEEK_END);
    len = ftell(pResponseFile);
    fseek(pResponseFile, 0, SEEK_SET);
    pszString = (HI_U8 *)malloc(sizeof(HI_U8) * (len));
    memset(pszString, 0, len);
    fread(pszString, 1, len, pResponseFile);
    response.appendArray(pszString,len);
    free(pszString);
    fclose(pResponseFile);
    return HI_TRUE;
}

/*******************************************************************************
* FuncName     : decryptPrepare
* FuncItem    : èŽ·å–ä¸€äº›è§£å¯†å†…éƒ¨éœ€è¦çš„å˜é‡å€¼ï¼Œä¸ºè§£å¯†åšå‡†å¤‡.
* InputParameters   : ModularDrmInterface * sessionId
* OutputParameters :
* retval                   :
*******************************************************************************/
HI_U8 decryptPrepare(ModularDrmInterface *modularDrmInterface,Vector<HI_U8>& sessionId)
{
    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST keyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&keyRequest));
    Vector<HI_U8> licenseResponse;
    const String8 kSoapAction("http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");
    HITEST_ASSERT_EQUAL(DoSoapAction(keyRequest.defaultUrl, kSoapAction,String8(reinterpret_cast<const char*>(keyRequest.requestData.array()),keyRequest.requestData.size()),&licenseResponse),HI_TRUE);

    const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),licenseResponse.size());
    Vector<HI_U8> keySetId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->provideKeyResponse(sessionId, licenseResponse, keySetId));

    return HI_SUCCESS;
}

} // namespace anonymous

namespace android {
#if 1
class ModularInterfaceTest
{
    public:
    HI_U8 isCryptoSchemeSupported();
    HI_U8 OpenSession();
    HI_U8 GenerateKeyRequest();
    HI_U8 GenerateKeyRequestWithInvalidHeader();
    HI_U8 GenerateKeyRequestWithCustomData();
    HI_U8 CheckSecurityLevel();
    HI_U8 Decrypt();

    HI_U8 Setup()
    {
        mModularDrmInterfacePlayready = ModularDrmInterface::Create(kPlayReadyUuid);
        mModularDrmInterfaceOtherDrm = ModularDrmInterface::Create(kRandomUuid);
        return TEST_SUCCESS;
    }
    HI_U8 TearDown()
    {
        ModularDrmInterface::Destroy(mModularDrmInterfacePlayready);
        ModularDrmInterface::Destroy(mModularDrmInterfaceOtherDrm);
        return TEST_SUCCESS;
    }

private:
    ModularDrmInterface *mModularDrmInterfacePlayready;
    ModularDrmInterface *mModularDrmInterfaceOtherDrm;
};

HI_U8 ModularInterfaceTest::isCryptoSchemeSupported()
{
    EXPECT_TRUE(mModularDrmInterfacePlayready->isCryptoSchemeSupported(kPlayReadyUuid, "video/mp4"));

    EXPECT_FALSE(mModularDrmInterfaceOtherDrm->isCryptoSchemeSupported(kRandomUuid, "video/mp4"));

    return TEST_SUCCESS;
}

HI_U8 ModularInterfaceTest::OpenSession()
{
    Vector<uint8_t> sessionId;
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(sessionId));

    Vector<uint8_t> anotherSessionId;
    EXPECT_NE(OK, mModularDrmInterfaceOtherDrm->openSession(anotherSessionId));

    EXPECT_FALSE(sessionId.size() == anotherSessionId.size() &&
             memcmp(sessionId.array(), anotherSessionId.array(), sessionId.size()) == 0);

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId));
    EXPECT_NE(OK, mModularDrmInterfaceOtherDrm->closeSession(anotherSessionId));

    return TEST_SUCCESS;
}

HI_U8 ModularInterfaceTest::GenerateKeyRequest()
{
    Vector<HI_U8> sessionId;
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(sessionId));

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST keyRequest;

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->getKeyRequest(sessionId,
           initData,
           String8("video/mp4").string(),
                                           (HI_DRM_KEY_TYPE)DrmPlugin::kKeyType_Streaming,
                                           KeyedVector<String8, String8>(),
                                           &keyRequest));
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId));
    return verifyLicenseRequest(&keyRequest, initData);
}

HI_U8 ModularInterfaceTest::GenerateKeyRequestWithInvalidHeader()
{
    Vector<HI_U8> sessionId;
    EXPECT_TRUE(OK == mModularDrmInterfacePlayready->openSession(sessionId));

    Vector<HI_U8> invalidInitData = getInitData(kInvalidTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST keyRequest;

    HI_S32 ret = mModularDrmInterfacePlayready->getKeyRequest(sessionId,
                                                                invalidInitData,
                                                                String8("video/mp4"),
                                                                (HI_DRM_KEY_TYPE)DrmPlugin::kKeyType_Streaming,
                                                                KeyedVector<String8, String8>(),
                                                                &keyRequest);

    HI_LOGD("getKeyRequest ret in GenerateKeyRequestWithInvalidHeader:%d", ret);

    EXPECT_NE(OK, mModularDrmInterfacePlayready->getKeyRequest(sessionId,
                                                                invalidInitData,
                                                                String8("video/mp4"),
                                                                (HI_DRM_KEY_TYPE)DrmPlugin::kKeyType_Streaming,
                                                                KeyedVector<String8, String8>(),
                                                                &keyRequest));

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId));
    return TEST_SUCCESS;
}

HI_U8 ModularInterfaceTest::GenerateKeyRequestWithCustomData()
{
    Vector<HI_U8> sessionId;
    EXPECT_TRUE(OK == mModularDrmInterfacePlayready->openSession(sessionId));

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);

    const String8 kMockCustomData("This is test!");
    KeyedVector<String8, String8> optionalParameters;
    optionalParameters.add(String8("PRCustomData"), kMockCustomData);
    HI_DRM_KEY_REQUEST keyRequest;

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->getKeyRequest(sessionId, initData, String8("video/mp4"),
                                           (HI_DRM_KEY_TYPE)DrmPlugin::kKeyType_Streaming,
                                           optionalParameters,
                                           &keyRequest));
    verifyLicenseRequest(&keyRequest, initData);
    String8 customData;
    String8 keyRequestXml(reinterpret_cast<const char*>(keyRequest.requestData.array()), keyRequest.requestData.size());
    EXPECT_TRUE(extractElement(keyRequestXml, String8("CustomData"), &customData));
    EXPECT_TRUE(customData == kMockCustomData);
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId));
    return TEST_SUCCESS;
}

HI_U8 ModularInterfaceTest::CheckSecurityLevel()
{
    String8 securityLevel;
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->getPropertyString(String8("securityLevel"),
                                               securityLevel));
#ifdef USE_SW_DECRYPTION
    EXPECT_TRUE(securityLevel == "L3");
#else
    EXPECT_TRUE(securityLevel == "L1");
#endif

    return TEST_SUCCESS;
}

HI_U8 ModularInterfaceTest::Decrypt()
{
    Vector<HI_U8> sessionId;
    EXPECT_TRUE(OK == mModularDrmInterfacePlayready->openSession(sessionId));


    Vector<HI_U8> KeyIdDataBuffer;
    KeyIdDataBuffer.setCapacity(sizeof(kTestKeyId));

    Vector<HI_U8> encryptedDataBuffer;
    encryptedDataBuffer.setCapacity(sizeof(kTestData));

    Vector<HI_U8> IvDataBuffer;
    IvDataBuffer.setCapacity(sizeof(kTestIv));

    Vector<HI_U8> decryptedDataBuffer;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));

    EXPECT_EQ(HI_FAILURE,
              mModularDrmInterfacePlayready->decrypt(sessionId,
                                    KeyIdDataBuffer,
                                    encryptedDataBuffer,
                                    IvDataBuffer,
                                    decryptedDataBuffer));

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId));
    return TEST_SUCCESS;
}

class CryptoInterfaceTest
{
public:
    HI_U8 isCryptoSchemeSupported();
    HI_U8 requiresSecureDecoderComponent();
    HI_U8 decrypt();
/*
    HI_U8 drmDecryptPrepare(ModularDrmInterface *modularDrmInterface,
                            Vector<uint8_t>& sessionId)
    {
        Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
        HI_DRM_KEY_REQUEST keyRequest;

        EXPECT_EQ(OK, modularDrmInterface->getKeyRequest(sessionId,
           initData,
           String8("video/mp4").string(),
                                           (HI_DRM_KEY_TYPE)DrmPlugin::kKeyType_Streaming,
                                           KeyedVector<String8, String8>(),
                                           &keyRequest));

        verifyLicenseRequest(&keyRequest, initData);

        Vector<uint8_t> licenseResponse;
        const String8 kSoapAction("http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");
        EXPECT_TRUE(DoSoapAction(keyRequest.defaultUrl, kSoapAction,
                                 String8(reinterpret_cast<const char*>(keyRequest.requestData.array()),
                                         keyRequest.requestData.size()),
                                 &licenseResponse));

        const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),
                                     licenseResponse.size());
        //printf("licenseResponse:%s", strLicenseResponse.string());

        Vector<uint8_t> keySetId;
        EXPECT_EQ(OK, modularDrmInterface->provideKeyResponse(sessionId, licenseResponse, keySetId));

        return TEST_SUCCESS;
    }*/
    //added by zhangpan for autotest 20160823
    HI_U8 Setup_AutoTest()
    {
        mModularDrmInterfacePlayready = ModularDrmInterface::Create(kPlayReadyUuid);
        mModularDrmInterfaceOtherDrm = ModularDrmInterface::Create(kRandomUuid);

        EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(playreadySessionId));
        EXPECT_NE(OK, mModularDrmInterfaceOtherDrm->openSession(anotherSessionId));

        //EXPECT_EQ(OK, drmDecryptPrepare(mModularDrmInterfacePlayready, playreadySessionId));

        mCryptoInterfacePlayready = CryptoInterface::Create(kPlayReadyUuid,
            reinterpret_cast<const char*>(playreadySessionId.array()), playreadySessionId.size());
        mCryptoInterfaceOtherDrm = CryptoInterface::Create(kRandomUuid,
            reinterpret_cast<const char*>(anotherSessionId.array()), anotherSessionId.size());

        return TEST_SUCCESS;
    }
/*
    HI_U8 Setup()
    {
        mModularDrmInterfacePlayready = ModularDrmInterface::Create(kPlayReadyUuid);
        mModularDrmInterfaceOtherDrm = ModularDrmInterface::Create(kRandomUuid);

        EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(playreadySessionId));
        EXPECT_NE(OK, mModularDrmInterfaceOtherDrm->openSession(anotherSessionId));

        EXPECT_EQ(OK, drmDecryptPrepare(mModularDrmInterfacePlayready, playreadySessionId));

        mCryptoInterfacePlayready = CryptoInterface::Create(kPlayReadyUuid,
            reinterpret_cast<const char*>(playreadySessionId.array()), playreadySessionId.size());
        mCryptoInterfaceOtherDrm = CryptoInterface::Create(kRandomUuid,
            reinterpret_cast<const char*>(anotherSessionId.array()), anotherSessionId.size());

        return TEST_SUCCESS;
    }
*/
    HI_U8 TearDown()
    {
        EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(playreadySessionId));
        EXPECT_NE(OK, mModularDrmInterfaceOtherDrm->closeSession(anotherSessionId));

        CryptoInterface::Destroy(mCryptoInterfacePlayready);
        CryptoInterface::Destroy(mCryptoInterfaceOtherDrm);
        return TEST_SUCCESS;
    }

private:
    CryptoInterface *mCryptoInterfacePlayready;
    CryptoInterface *mCryptoInterfaceOtherDrm;

    ModularDrmInterface *mModularDrmInterfacePlayready;
    ModularDrmInterface *mModularDrmInterfaceOtherDrm;


    Vector<uint8_t> playreadySessionId;
    Vector<uint8_t> anotherSessionId;
};

HI_U8 CryptoInterfaceTest::isCryptoSchemeSupported()
{
    EXPECT_EQ(HI_TRUE, mCryptoInterfacePlayready->isCryptoSchemeSupported(kPlayReadyUuid));

//    EXPECT_EQ(HI_FALSE, mCryptoInterfaceOtherDrm->isCryptoSchemeSupported(kRandomUuid));

    return TEST_SUCCESS;
}

HI_U8 CryptoInterfaceTest::requiresSecureDecoderComponent()
{
    EXPECT_EQ(HI_FALSE, mCryptoInterfacePlayready->requiresSecureDecoderComponent("video/mp4"));

    return TEST_SUCCESS;
}
#if 0
HI_U8 CryptoInterfaceTest::decrypt()
{
    HI_DRM_SUBSAMPLES subSamples;
    subSamples.u32numBytesOfClearData = 0;
    subSamples.u32numBytesOfEncryptedData = 10;

    HI_U8 decryptData[10];
    String8 errorDetailMsg;

/*    HI_S32 ret = mCryptoInterfacePlayready->decrypt(HI_TRUE,
                                       kTestKeyId,
                                       kTestIv,
                                       HI_CRYPTO_MODE_AES_CTR,
                                       kTestData,
                                       10,
                                       &subSamples,
                                       1,
                                       decryptData,
                                       errorDetailMsg);

    HI_LOGD("Return code of decrypt secure:%d", ret);
    EXPECT_NE(OK, ret);
*/
    HI_S32 ret = mCryptoInterfacePlayready->decrypt(HI_FALSE,
                                       kTestKeyId,
                                       kTestIv,
                                       HI_CRYPTO_MODE_AES_CTR,
                                       kTestData,
                                       10,
                                       &subSamples,
                                       -1,
                                       decryptData,
                                       errorDetailMsg);

    HI_LOGD("Return code of decrypt secure:%d", ret);
    EXPECT_NE(OK, ret);
    ret = mCryptoInterfacePlayready->decrypt(HI_FALSE,
                                       kTestKeyId,
                                       kTestIv,
                                       HI_CRYPTO_MODE_AES_CTR,
                                       kTestData,
                                       -1,
                                       &subSamples,
                                       1,
                                       decryptData,
                                       errorDetailMsg);

    HI_LOGD("Return code of decrypt secure:%d", ret);
    EXPECT_NE(OK, ret);
    ret = mCryptoInterfacePlayready->decrypt(HI_FALSE,
                                       kTestKeyId,
                                       kTestIv,
                                       HI_CRYPTO_MODE_AES_CTR,
                                       HI_NULL,
                                       10,
                                       &subSamples,
                                       1,
                                       decryptData,
                                       errorDetailMsg);

    HI_LOGD("Return code of decrypt secure:%d", ret);
    EXPECT_NE(OK, ret);
    ret = mCryptoInterfacePlayready->decrypt(HI_FALSE,
                                       kInvalidKeyId,
                                       kTestIv,
                                       HI_CRYPTO_MODE_AES_CTR,
                                       kTestData,
                                       10,
                                       &subSamples,
                                       1,
                                       decryptData,
                                       errorDetailMsg);

    HI_LOGD("Return code of decrypt secure:%d", ret);
    EXPECT_NE(OK, ret);
    ret = mCryptoInterfacePlayready->decrypt(HI_FALSE,
                                       kTestKeyId,
                                       kTestIv,
                                       HI_CRYPTO_MODE_AES_CTR,
                                       kTestData,
                                       10,
                                       &subSamples,
                                       1,
                                       decryptData,
                                       errorDetailMsg);

    HI_LOGD("Return code of decrypt non-secure:%d", ret);

    EXPECT_EQ(0, memcmp(decryptData, kTestResult, sizeof(kTestResult)));

    return TEST_SUCCESS;
}

void testModularInterface()
{
    TEST_INFO("Test modualr interface start!\n");

    ModularInterfaceTest modualrInterfaceTest;

    if(modualrInterfaceTest.Setup())
    {
        TEST_INFO("[1] SetUp failed.\n");
    }
    else
    {
        TEST_INFO("[1] SetUp success.\n");
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

    if(modualrInterfaceTest.GenerateKeyRequestWithCustomData())
    {
        TEST_INFO("[6] GenerateKeyRequestWithCustomData failed.\n");
    }
    else
    {
        TEST_INFO("[6] GenerateKeyRequestWithCustomData success.\n");
    }

    if(modualrInterfaceTest.CheckSecurityLevel())
    {
        TEST_INFO("[7] CheckSecurityLevel failed.\n");
    }
    else
    {
        TEST_INFO("[7] CheckSecurityLevel success.\n");
    }

    if(modualrInterfaceTest.Decrypt())
    {
        TEST_INFO("[8] Decrypt failed.\n");
    }
    else
    {
        TEST_INFO("[8] Decrypt success.\n");
    }

    if(modualrInterfaceTest.TearDown())
    {
        TEST_INFO("[9] TearDown failed.\n");
    }
    else
    {
        TEST_INFO("[9] TearDown success.\n");
    }
}

void testCryptoInterface()
{
    CryptoInterfaceTest cryptoInterfaceTest;

    if (cryptoInterfaceTest.Setup())
    {
        TEST_INFO("[1] Setup failed.\n");
    }
    else
    {
        TEST_INFO("[1] Setup success.\n");
    }

    if (cryptoInterfaceTest.isCryptoSchemeSupported())
    {
        TEST_INFO("[2] isCryptoSchemeSupported failed.\n");
    }
    else
    {
        TEST_INFO("[2] isCryptoSchemeSupported success.\n");
    }

    if (cryptoInterfaceTest.requiresSecureDecoderComponent())
    {
        TEST_INFO("[3] requiresSecureDecoderComponent failed.\n");
    }
    else
    {
        TEST_INFO("[3] requiresSecureDecoderComponent success.\n");
    }

    if (cryptoInterfaceTest.decrypt())
    {
        TEST_INFO("[4] decrypt failed.\n");
    }
    else
    {
        TEST_INFO("[4] decrypt success.\n");
    }

    if (cryptoInterfaceTest.TearDown())
    {
        TEST_INFO("[5] TearDown failed.\n");
    }
    else
    {
        TEST_INFO("[5] TearDown success.\n");
    }
}
#endif

/*for auto test 20160822 start*/
CryptoInterfaceTest cryptoInterfaceTest;
HI_S32 cryptoInterfaceTest_Setup()
{
    if (cryptoInterfaceTest.Setup_AutoTest())
    {
        TEST_INFO("[10] Setup failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[10] Setup success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    cryptoInterfaceTest.TearDown();
    return 0;
}

HI_S32 cryptoInterfaceTest_isCryptoSchemeSupported()
{
    cryptoInterfaceTest.Setup_AutoTest();
    if (cryptoInterfaceTest.isCryptoSchemeSupported())
    {
        TEST_INFO("[11] isCryptoSchemeSupported failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[11] isCryptoSchemeSupported success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    cryptoInterfaceTest.TearDown();
    return 0;
}

HI_S32 cryptoInterfaceTest_requiresSecureDecoderComponent()
{
    cryptoInterfaceTest.Setup_AutoTest();
    if (cryptoInterfaceTest.requiresSecureDecoderComponent())
    {
        TEST_INFO("[12] requiresSecureDecoderComponent failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[12] requiresSecureDecoderComponent success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    cryptoInterfaceTest.TearDown();
    return 0;
}
/*      ÐèÒªÍâÍø»·¾³
HI_S32 cryptoInterfaceTest_decrypt()
{
    cryptoInterfaceTest.Setup();
    if (cryptoInterfaceTest.decrypt())
    {
        TEST_INFO("[13] decrypt failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[13] decrypt success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    cryptoInterfaceTest.TearDown();
    return 0;
}
*/
HI_S32 cryptoInterfaceTest_TearDown()
{
    cryptoInterfaceTest.Setup_AutoTest();
    if (cryptoInterfaceTest.TearDown())
    {
        TEST_INFO("[14] TearDown failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[14] TearDown success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return 0;
}

ModularInterfaceTest modualrInterfaceTest;
HI_S32 modualrInterfaceTest_Setup()
{
    if(modualrInterfaceTest.Setup())
    {
      TEST_INFO("[1] SetUp failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[1] SetUp success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    modualrInterfaceTest.TearDown();
    return 0;
}

HI_S32 modualrInterfaceTest_isCryptoSchemeSupported()
{
    modualrInterfaceTest.Setup();
    if(modualrInterfaceTest.isCryptoSchemeSupported())
    {
        TEST_INFO("[2] isCryptoSchemeSupported failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[2] isCryptoSchemeSupported success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    modualrInterfaceTest.TearDown();
    return 0;
}

HI_S32 modualrInterfaceTest_OpenSession()
{
    modualrInterfaceTest.Setup();
    if(modualrInterfaceTest.OpenSession())
    {
        TEST_INFO("[3] OpenSession failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[3] OpenSession success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    modualrInterfaceTest.TearDown();
    return 0;
}

HI_S32 modualrInterfaceTest_GenerateKeyRequest()
{
    modualrInterfaceTest.Setup();
    if(modualrInterfaceTest.GenerateKeyRequest())
    {
        TEST_INFO("[4] GenerateKeyRequest failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[4] GenerateKeyRequest success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    modualrInterfaceTest.TearDown();
    return 0;
}

HI_S32 modualrInterfaceTest_GenerateKeyRequestWithInvalidHeader()
{
    modualrInterfaceTest.Setup();
    if(modualrInterfaceTest.GenerateKeyRequestWithInvalidHeader())
    {
        TEST_INFO("[5] GenerateKeyRequestWithInvalidHeader failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[5] GenerateKeyRequestWithInvalidHeader success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    modualrInterfaceTest.TearDown();
    return 0;
}

HI_S32 modualrInterfaceTest_GenerateKeyRequestWithCustomData()
{
    modualrInterfaceTest.Setup();
    if(modualrInterfaceTest.GenerateKeyRequestWithCustomData())
    {
        TEST_INFO("[6] GenerateKeyRequestWithCustomData failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[6] GenerateKeyRequestWithCustomData success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    modualrInterfaceTest.TearDown();
    return 0;
}

HI_S32 modualrInterfaceTest_CheckSecurityLevel()
{
    modualrInterfaceTest.Setup();
    if(modualrInterfaceTest.CheckSecurityLevel())
    {
        TEST_INFO("[7] CheckSecurityLevel failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[7] CheckSecurityLevel success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    modualrInterfaceTest.TearDown();
    return 0;
}

HI_S32 modualrInterfaceTest_Decrypt()
{
    modualrInterfaceTest.Setup();
    if(modualrInterfaceTest.Decrypt())
    {
        TEST_INFO("[8] Decrypt failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[8] Decrypt success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    modualrInterfaceTest.TearDown();
    return 0;
}

HI_S32 modualrInterfaceTest_TearDown()
{
    modualrInterfaceTest.Setup();
    if(modualrInterfaceTest.TearDown())
    {
        TEST_INFO("[9] TearDown failed.\n");
        HITEST_CHECK_SUCCESS(-1);
        return -1;
    }
    else
    {
        TEST_INFO("[9] TearDown success.\n");
        HITEST_CHECK_SUCCESS(0);
    }

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return 0;
}
/*for auto test 20160822 end*/
#endif

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Create_001
* Test Item        : å•æ¿ä¸Šç”µå¹¶åˆå§‹åŒ–æœåŠ¡åŽï¼Œå®‰è£…playready æ’ä»¶åŽï¼Œåˆ›å»ºdrmå¯¹è±¡æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Create_001(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Create_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–ç³»ç»ŸæœåŠ¡ï¼Œå®‰è£…äº†playreadyæ’ä»¶åŽï¼Œ
                              è¾“å…¥æ— æ•ˆçš„uuidï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸï¼Œåˆ›å»ºdrmå¯¹è±¡å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Create_002(HI_VOID)
{
    Vector<HI_U8> sessionId;
    Vector<HI_U8> sessionId2;
    HITEST_CHECK_NULL(ModularOtherDrmInfo = ModularDrmInterface::Create(kRandomUuid));
    HITEST_CHECK_FAIL(ModularOtherDrmInfo->openSession(sessionId));
    HITEST_CHECK_FAIL(ModularOtherDrmInfo->closeSession(sessionId2));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Create_003
* Test Item        : å•æ¿ä¸Šç”µå¹¶åˆå§‹åŒ–æœåŠ¡åŽï¼Œåœ¨å¤šè¿›ç¨‹ä¸‹ï¼Œåˆ›å»ºdrmå¯¹è±¡ï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Create_003(HI_VOID)
{
    pid_t forkId;
    forkId = fork();
    if(forkId < 0)
    {
        HITEST_FailPrint((HI_CHAR*)__FUNCTION__, HI_FAILURE, __LINE__);
    }
    else if(forkId == 0)
    {
        HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
        HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo));
        ModularDrmInfo = HI_NULL;
    }
    else
    {
        HITEST_CHECK_NULL(ModularDrmInfo1 = ModularDrmInterface::Create(kPlayReadyUuid));
        HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo1));
        ModularDrmInfo1 = HI_NULL;
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Create_004
* Test Item        : å•æ¿ä¸Šç”µå¹¶åˆå§‹åŒ–æœåŠ¡åŽï¼Œå®‰è£…playready æ’ä»¶åŽï¼Œuuidä¸ºç©ºæ—¶ï¼Œåˆ›å»ºdrmå¯¹è±¡ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Create_004(HI_VOID)
{
    ModularDrmInfo = ModularDrmInterface::Create(HI_NULL);
    if (NULL != ModularDrmInfo)
    {
        HITEST_FailPrint((HI_CHAR*)__FUNCTION__, HI_FAILURE, __LINE__);
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Destroy_001
* Test Item        : å•æ¿ä¸Šç”µå¹¶åˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºdrmå¯¹è±¡åŽï¼Œæ­£å¸¸é”€æ¯å¯¹è±¡æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Destroy_001(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo));
    ModularDrmInfo = HI_NULL;
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Destroy_002
* Test Item        :å•æ¿ä¸Šç”µå¹¶åˆå§‹åŒ–æœåŠ¡åŽï¼Œ è§£å¯†åŽï¼Œé”€æ¯å¯¹è±¡ï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Destroy_002(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    HI_S32 numSubSamples = 1;
    HI_U8 decryptData[10];
    String8 errorDetailMsg;
    HI_S32 ret;
    ret = CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,decryptData,errorDetailMsg);
    HITEST_ASSERT_EQUAL(10,ret);
    HITEST_ASSERT_EQUAL(0, memcmp(decryptData, kTestResult, sizeof(kTestResult)));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));

    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Destroy_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œé‡å¤é”€æ¯DRMå¯¹è±¡ï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Destroy_003(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo));
    ModularDrmInfo = HI_NULL;
    HITEST_CHECK_FAIL(ModularDrmInterface::Destroy(ModularDrmInfo));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Destroy_004
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œæœªåˆ›å»ºDRMå¯¹è±¡ï¼ŒåŽ»é”€æ¯å¯¹è±¡ï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Destroy_004(HI_VOID)
{
    HITEST_CHECK_FAIL(ModularDrmInterface::Destroy(ModularDrmInfo));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Destroy_005
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéžDRMå¯¹è±¡ï¼ŒåŽ»é”€æ¯å¯¹è±¡ï¼Œè°ƒç”¨æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Destroy_005(HI_VOID)
{
    HITEST_CHECK_NULL(ModularOtherDrmInfo = ModularDrmInterface::Create(kRandomUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularOtherDrmInfo));
    ModularOtherDrmInfo = HI_NULL;
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Destroy_006
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œæœªé”€æ¯è§£å¯†å¯¹è±¡ï¼Œå°±ç›´æŽ¥é”€æ¯drmå¯¹è±¡ï¼Œè°ƒç”¨æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Destroy_006(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo));
    ModularDrmInfo = HI_NULL;
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_Destroy_007
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåå¤åˆ›å»ºå…³é—­å¯¹è±¡10000æ¬¡ï¼Œæ¯æ¬¡æŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_Destroy_007(HI_VOID)
{
    ModularDrmInterface* ModularDrmInfo[HITEST_STRESS_TIMES] = {NULL};
    for (HI_U32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        HITEST_CHECK_NULL(ModularDrmInfo[i] = ModularDrmInterface::Create(kPlayReadyUuid));
    }
    for (HI_U32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo[i]));
        ModularDrmInfo[i] = HI_NULL;
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒæŸ¥è¯¢mp4è§†é¢‘æ ¼å¼çš„åª’ä½“æ–‡ä»¶ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_001(HI_VOID)
{
    const HI_CHAR* mimeType = "video/mp4";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kInvalidTestIv,mimeType),HI_FALSE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒæŸ¥è¯¢mp4éŸ³é¢‘æ ¼å¼çš„åª’ä½“æ–‡ä»¶ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_002(HI_VOID)
{
    const HI_CHAR* mimeType = "audio/mp4";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒæŸ¥è¯¢3gppè§†é¢‘æ ¼å¼çš„åª’ä½“æ–‡ä»¶ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_003(HI_VOID)
{
    const HI_CHAR* mimeType = "video/3gpp";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_005
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒæŸ¥è¯¢3gppéŸ³é¢‘æ ¼å¼çš„åª’ä½“æ–‡ä»¶ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_004(HI_VOID)
{
    const HI_CHAR* mimeType = "audio/3gpp";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_005
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒæŸ¥è¯¢3gpp2è§†é¢‘æ ¼å¼çš„åª’ä½“æ–‡ä»¶ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_005(HI_VOID)
{
    const HI_CHAR* mimeType = "video/3gpp2";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_006
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒæŸ¥è¯¢3gpp2éŸ³é¢‘æ ¼å¼çš„åª’ä½“æ–‡ä»¶ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_006(HI_VOID)
{
    const HI_CHAR* mimeType = "audio/3gpp2";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_007
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒæŸ¥è¯¢quicktimeæ ¼å¼çš„åª’ä½“æ–‡ä»¶ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_007(HI_VOID)
{
    const HI_CHAR* mimeType = "video/quicktime";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_008
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒæŸ¥è¯¢webmæ ¼å¼çš„åª’ä½“æ–‡ä»¶ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_008(HI_VOID)
{
    const HI_CHAR* mimeType = "audio/webm";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_009
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥éžplayreadyçš„uuidï¼Œè¿›è¡ŒæŸ¥è¯¢ï¼Œè¿”å›žHI_FALSEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_009(HI_VOID)
{
    const HI_CHAR* mimeType = "audio/3gpp";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kRandomUuid,mimeType),HI_FALSE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_010
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥ä¸æ”¯æŒçš„åª’ä½“æ ¼å¼ï¼Œè¿›è¡ŒæŸ¥è¯¢ï¼Œè¿”å›žHI_FALSEï¼ˆæš‚æ—¶ä¸æ‰©å±•ä¸ºHI_TRUEï¼‰ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_010(HI_VOID)
{
    const HI_CHAR* mimeType = "video/avi";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_011
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥åª’ä½“æ ¼å¼ä¸ºç©ºæŒ‡é’ˆï¼Œè¿›è¡ŒæŸ¥è¯¢ï¼Œè¿”å›žHI_FALSEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_011(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,HI_NULL),HI_FALSE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_012
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥åª’ä½“ä¸ºç©ºï¼Œè¿›è¡ŒæŸ¥è¯¢ï¼Œè¿”å›žHI_FALSEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_012(HI_VOID)
{
    const HI_CHAR* mimeType = HI_NULL;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_FALSE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_013
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥uuidä¸ºç©ºï¼Œè¿›è¡ŒæŸ¥è¯¢ï¼Œè¿”å›žHI_FALSEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_013(HI_VOID)
{
    const HI_CHAR* mimeType = "video/mp4";
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(HI_NULL,mimeType),HI_FALSE);
    if (ModularDrmInfo)
    {
        ModularDrmInterface::Destroy(ModularDrmInfo);
        ModularDrmInfo = HI_NULL;
    }

    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_014
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œå¤šè¿›ç¨‹ä¸‹ï¼ŒæŸ¥è¯¢åˆæ³•çš„åª’ä½“æ ¼å¼ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_014(HI_VOID)
{
    pid_t forkId;
    forkId = fork();
    const HI_CHAR* mimeType1 = "video/3pgg";
    const HI_CHAR* mimeType2 = "video/mp4";
    if(forkId <0)
    {
        HITEST_FailPrint((HI_CHAR*)__FUNCTION__, HI_FAILURE, __LINE__);
    }
    else if (forkId == 0)
    {
        HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
        HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType1),HI_TRUE);
        HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo));
        ModularDrmInfo = HI_NULL;
    }
    else
    {
        HITEST_CHECK_NULL(ModularDrmInfo1 = ModularDrmInterface::Create(kPlayReadyUuid));
        HITEST_ASSERT_EQUAL(ModularDrmInfo1->isCryptoSchemeSupported(kPlayReadyUuid,mimeType2),HI_TRUE);
        HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo1));
        ModularDrmInfo1 = HI_NULL;
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_015
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œå¤šè¿›ç¨‹ä¸‹ï¼ŒåŒæ—¶æŸ¥è¯¢
                              åˆæ³•å’Œéžæ³•çš„åª’ä½“æ ¼å¼ï¼Œåˆæ³•çš„è¿”å›žHI_TRUEï¼Œéžæ³•çš„è¿”å›žHI_FALSEï¼ˆæš‚æ—¶ä¸æ‰©å±•ä¸ºHI_TRUEï¼‰ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_015(HI_VOID)
{
    pid_t forkId;
    forkId = fork();
    const HI_CHAR* mimeType1 = "video/mp4";
    const HI_CHAR* mimeType2 = "video/invalid";
    if(forkId <0)
    {
        HITEST_FailPrint((HI_CHAR*)__FUNCTION__, HI_FAILURE, __LINE__);
    }
    else if (forkId == 0)
    {
        HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
        HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType1),HI_TRUE);
        HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo));
        ModularDrmInfo = HI_NULL;
    }
    else
    {
        HITEST_CHECK_NULL(ModularDrmInfo1 = ModularDrmInterface::Create(kPlayReadyUuid));
        HITEST_ASSERT_EQUAL(ModularDrmInfo1->isCryptoSchemeSupported(kPlayReadyUuid,mimeType2),HI_TRUE);
        HITEST_CHECK_SUCCESS(ModularDrmInterface::Destroy(ModularDrmInfo1));
        ModularDrmInfo1 = HI_NULL;
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_isCryptoSchemeSupported_016
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåå¤è°ƒç”¨æŽ¥å£10000æ¬¡è¿›è¡ŒæŸ¥è¯¢ï¼Œæ¯æ¬¡è¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_isCryptoSchemeSupported_016(HI_VOID)
{
    const HI_CHAR* mimeType = "video/mp4";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    for (HI_U32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
         HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_openSession_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œå…³é—­åŽå†æ‰“å¼€sessionï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_openSession_001(HI_VOID)
{
    Vector<HI_U8> sessionId;
    Vector<HI_U8> anotherSessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(anotherSessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(anotherSessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_openSession_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œæ‰“å¼€å¤šä¸ªsessionå¹¶å…³é—­æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_openSession_002(HI_VOID)
{
    Vector<HI_U8> sessionId;
    Vector<HI_U8> anotherSessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(anotherSessionId));
    HITEST_ASSERT_EQUAL((sessionId.size() == anotherSessionId.size() && memcmp(sessionId.array(), anotherSessionId.array(), sessionId.size()) == 0),HI_FALSE);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(anotherSessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_openSession_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéžDRMå¯¹è±¡ï¼Œæ‰“å¼€sessionï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_openSession_003(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularOtherDrmInfo = ModularDrmInterface::Create(kRandomUuid));
    HITEST_CHECK_FAIL(ModularOtherDrmInfo->openSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_openSession_004
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéžDRMå¯¹è±¡ä¸”æŸ¥è¯¢æ’ä»¶æ”¯æŒplayreadyè§£å¯†ï¼Œæ‰“å¼€sessionï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_openSession_004(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kRandomUuid));
    const HI_CHAR* mimeType = "video/mp4";
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    HITEST_CHECK_FAIL(ModularDrmInfo->openSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè§£å¯†åŽå…³é—­sessionã€‚æŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_001(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_S32 numSubSamples = 1;
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HI_S32 ret;
    ret = CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg);
    HITEST_ASSERT_EQUAL(10,ret);
    HITEST_ASSERT_EQUAL(0, memcmp(pDst, kTestResult, sizeof(kTestResult)));

    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));

    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;

}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œæ‰“å¼€ä¼šè¯åŽï¼Œè¿›è¡Œå…³é—­ï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_002(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥è¶…é•¿æœ€å¤§å€¼çš„sessionIdï¼Œè°ƒç”¨æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_003(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8>  sessionId;
    for(HI_U32 i = 0;i < HI_LENGTH;i++)
    {
        sessionId.push_back(255);
    }
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_004
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥è¶…é•¿æœ€å°å€¼çš„sessionIdï¼Œè°ƒç”¨æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_004(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8>  sessionId;
    for(HI_U32 i = 0;i < HI_LENGTH;i++)
    {
        sessionId.push_back(0);
    }
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_005
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºè§£å¯†å¯¹è±¡åŽå…³é—­sessionï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_005(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_006
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œé”€æ¯è§£å¯†å¯¹è±¡åŽå…³é—­sessionï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_006(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_CHECK_SUCCESS(CryptoInterface::Destroy(CryptoInfo));
    CryptoInfo = HI_NULL;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_007
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œæœªæ‰“å¼€ä¼šè¯è°ƒç”¨closeSessionåŽ»å…³é—­ï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_007(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_FAIL(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_008
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œé‡å¤å…³é—­sessionï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_008(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_009
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºdrmå¯¹è±¡ï¼Œå…³é—­sessionï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_009(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_010
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéždrmå¯¹è±¡ï¼Œå…³é—­sessionï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_010(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_NULL(ModularDrmInfo1 = ModularDrmInterface::Create(kRandomUuid));
    HITEST_CHECK_FAIL(ModularDrmInfo1->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_011
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œç›´æŽ¥åˆ›å»ºéždrmå¯¹è±¡ï¼Œå…³é—­sessionï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_011(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kRandomUuid));
    HITEST_CHECK_FAIL(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_closeSession_012
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåå¤æ‰“å¼€å…³é—­session (10000æ¬¡)ï¼Œæ¯æ¬¡è°ƒç”¨æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_closeSession_012(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8>  sessionId;
    for (HI_U32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
        HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè§£å¯†åŠ å¯†æµèŽ·å–keyç”³è¯·ä¿¡æ¯æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_001(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    Vector<HI_U8> sessionId2;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    HITEST_CHECK_SUCCESS(verifyLicenseRequest(&pKeyRequest,initData));
    HITEST_CHECK_FAIL(ModularDrmInfo->getKeyRequest(sessionId2,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè§£å¯†å¸¦å®¢æˆ·ä¿¡æ¯åŠ å¯†æµèŽ·å–keyç”³è¯·ä¿¡æ¯æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_002(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    const String8 kMockCustomData("This is test!");
    KeyedVector<String8, String8> optionalParameters;
    optionalParameters.add(String8("PRCustomData"), kMockCustomData);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,optionalParameters,&pKeyRequest));
    HITEST_CHECK_SUCCESS(verifyLicenseRequest(&pKeyRequest,initData));

    String8 customData;
    String8 keyRequestXml(reinterpret_cast<const char*>(pKeyRequest.requestData.array()), pKeyRequest.requestData.size());
    HITEST_ASSERT_EQUAL(extractElement(keyRequestXml, String8("CustomData"), &customData),HI_TRUE);
    HITEST_ASSERT_EQUAL((customData == kMockCustomData),HI_TRUE);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè§£å¯†éžæ³•åŠ å¯†æ–‡ä»¶ï¼ŒèŽ·å–keyç”³è¯·ä¿¡æ¯å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_003(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    Vector<HI_U8> initData = getInitData(kInvalidTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_FAIL(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_004
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥ä¸æ”¯æŒçš„åª’ä½“æ ¼å¼(playreadyåŠ å¯†çš„pyvè§†é¢‘æ ¼å¼)ï¼ŒèŽ·å–keyç”³è¯·ä¿¡æ¯å¤±è´¥ï¼ˆæš‚æ—¶ä¸æ‰©å±•ï¼Œä¸ºæˆåŠŸï¼‰ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_004(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/pyv").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_005
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè§£å¯†keyç±»åž‹éžæ³•æ—¶ï¼ŒèŽ·å–keyç”³è¯·ä¿¡æ¯ï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_005(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_BUTT;
    HITEST_CHECK_FAIL(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_006
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œä¼šè¯idè¶…é•¿ï¼ŒèŽ·å–keyç”³è¯·ä¿¡æ¯ï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_006(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    for(HI_U32 i = 0;i <= HI_LENGTH;i++)
    {
        sessionId.push_back(255);
    }

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_FAIL(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_007
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œå…¥å‚å‡ºå‚nullæŒ‡é’ˆï¼ŒèŽ·å–keyç”³è¯·ä¿¡æ¯ï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_007(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,HI_NULL,pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    HITEST_CHECK_FAIL(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),HI_NULL));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_008
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéždrmå¯¹è±¡ï¼Œä½¿ç”¨drmå¯¹è±¡çš„sessionåŽ»èŽ·å–keyè¯·æ±‚ä¿¡æ¯ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_008(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_NULL(ModularDrmInfo1 = ModularDrmInterface::Create(kRandomUuid));
    HITEST_CHECK_FAIL(ModularDrmInfo1->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_009
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéždrmå¯¹è±¡ï¼ŒèŽ·å–keyè¯·æ±‚ä¿¡æ¯ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_009(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kRandomUuid));
    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_FAIL(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_010
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéždrmå¯¹è±¡ä¸”æŸ¥è¯¢æ’ä»¶æ”¯æŒplayreadyè§£å¯†ï¼ŒèŽ·å–keyè¯·æ±‚ä¿¡æ¯ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_010(HI_VOID)
{
    Vector<HI_U8> sessionId;
    const HI_CHAR* mimeType = "video/mp4";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kRandomUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_FAIL(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_getKeyRequest_011
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåå¤è°ƒç”¨æŽ¥å£èŽ·å–keyç”³è¯·ä¿¡æ¯ï¼Œæ¯æ¬¡æŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_getKeyRequest_011(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;

    for (HI_S32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
        HITEST_CHECK_SUCCESS(verifyLicenseRequest(&pKeyRequest,initData));
    }
     HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_provideKeyResponse_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒæŽ¥æ”¶åˆ°åˆæ³•çš„keyè¯·æ±‚å›žåº”ï¼Œè°ƒç”¨æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_provideKeyResponse_001(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST keyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&keyRequest));
    Vector<HI_U8> licenseResponse;
    const String8 kSoapAction("http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");
    HITEST_ASSERT_EQUAL(DoSoapAction(keyRequest.defaultUrl, kSoapAction,String8(reinterpret_cast<const char*>(keyRequest.requestData.array()),keyRequest.requestData.size()),&licenseResponse),HI_TRUE);

    const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),licenseResponse.size());
    Vector<HI_U8> keySetId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->provideKeyResponse(sessionId, licenseResponse, keySetId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_provideKeyResponse_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œæ— æ•ˆçš„responseæ•°æ®è¾“å…¥ï¼ˆç©ºæˆ–è€…é”™è¯¯ï¼‰ï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_provideKeyResponse_002(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HI_BOOL pFlag;
    Vector<HI_U8> sessionId;
    Vector<HI_U8> sessionId2;
    FILE* pResponseFile = NULL;
    char response[] = "abcd1234";
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    Vector<HI_U8> invalidResponse;

    system("mkdir -p /mnt/bin/");
    pResponseFile = fopen((char *)invalidXmlFilePath, "w+");
    if (pResponseFile == NULL)
    {
        HITEST_FailPrint((HI_CHAR*)__FUNCTION__, HI_FAILURE, __LINE__);
        return -1;
    }
    fwrite(response, sizeof(response), 1, pResponseFile);
    fclose(pResponseFile);
    pFlag = get_response_from_file(invalidXmlFilePath,invalidResponse);
    if (pFlag == HI_FALSE)
    {
        HITEST_FailPrint((HI_CHAR*)__FUNCTION__, HI_FAILURE, __LINE__);
    }
    Vector<HI_U8> keySetId;
    HITEST_CHECK_FAIL(ModularDrmInfo->provideKeyResponse(sessionId,invalidResponse,keySetId));
    HITEST_CHECK_FAIL(ModularDrmInfo->provideKeyResponse(sessionId2,invalidResponse,keySetId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_provideKeyResponse_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéždrmå¯¹è±¡ï¼ŒèŽ·å–licenseå“åº”ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_provideKeyResponse_003(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST keyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&keyRequest));
    Vector<HI_U8> licenseResponse;
    const String8 kSoapAction("http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");
    HITEST_ASSERT_EQUAL(DoSoapAction(keyRequest.defaultUrl, kSoapAction,String8(reinterpret_cast<const char*>(keyRequest.requestData.array()),keyRequest.requestData.size()),&licenseResponse),HI_TRUE);

    const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),licenseResponse.size());
    Vector<HI_U8> keySetId;
    HITEST_CHECK_NULL(ModularDrmInfo1 = ModularDrmInterface::Create(kRandomUuid));
    HITEST_CHECK_FAIL(ModularDrmInfo1->provideKeyResponse(sessionId, licenseResponse, keySetId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_provideKeyResponse_004
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéždrmå¯¹è±¡ï¼Œç›´æŽ¥è°ƒç”¨æŽ¥å£èŽ·å–keyè¯·æ±‚å›žåº”ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_provideKeyResponse_004(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kRandomUuid));
    Vector<HI_U8> licenseResponse;
    for(HI_U32 j = 0;j < 16;j++)
    {
        licenseResponse.push_back(1);
    }
    const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),licenseResponse.size());
    Vector<HI_U8> keySetId;
    HITEST_CHECK_FAIL(ModularDrmInfo->provideKeyResponse(sessionId, licenseResponse, keySetId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_provideKeyResponse_005
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéždrmå¯¹è±¡ï¼Œä¸”æŸ¥è¯¢æ’ä»¶æ”¯æŒplayreadyè§£å¯†ï¼ŒèŽ·å–keyå“åº”ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_provideKeyResponse_005(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kRandomUuid));
    const HI_CHAR* mimeType = "video/mp4";
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Vector<HI_U8> licenseResponse;
    for(HI_U32 j = 0;j < 16;j++)
    {
        licenseResponse.push_back(1);
    }
    const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),licenseResponse.size());
    Vector<HI_U8> keySetId;
    HITEST_CHECK_FAIL(ModularDrmInfo->provideKeyResponse(sessionId, licenseResponse, keySetId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_provideKeyResponse_006
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºdrmå¯¹è±¡ï¼Œä¼ å…¥æ— æ•ˆsessionIdï¼ŒèŽ·å–keyå“åº”ã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_provideKeyResponse_006(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));

    Vector<HI_U8> sessionId;
    Vector<HI_U8> otherSessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        otherSessionId.push_back(1);
    }
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST keyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&keyRequest));
    Vector<HI_U8> licenseResponse;
    const String8 kSoapAction("http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");
    HITEST_ASSERT_EQUAL(DoSoapAction(keyRequest.defaultUrl, kSoapAction,String8(reinterpret_cast<const char*>(keyRequest.requestData.array()),keyRequest.requestData.size()),&licenseResponse),HI_TRUE);

    const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),licenseResponse.size());
    Vector<HI_U8> keySetId;
    HITEST_CHECK_FAIL(ModularDrmInfo->provideKeyResponse(otherSessionId, licenseResponse, keySetId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_provideKeyResponse_007
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œä¸åŒdrm headerè°ƒç”¨æŽ¥å£10000æ¬¡æ¯æ¬¡æŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_provideKeyResponse_007(HI_VOID)
{
    for (HI_S32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        Test_ModularDrm_provideKeyResponse_001();
    }
    return 0;
}

/*******************************************************************************
* Test Case ID    : Test_ModularDrm_provideKeyResponse_008
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒåŒä¸€drm headeråå¤è°ƒç”¨æŽ¥å£10000æ¬¡æ¯æ¬¡æŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_ModularDrm_provideKeyResponse_008(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST keyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    Vector<HI_U8> licenseResponse;
    Vector<HI_U8> keySetId;

    for (HI_S32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
        HITEST_CHECK_SUCCESS(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&keyRequest));
        licenseResponse.clear();
        const String8 kSoapAction("http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");
        HITEST_ASSERT_EQUAL(DoSoapAction(keyRequest.defaultUrl, kSoapAction,String8(reinterpret_cast<const char*>(keyRequest.requestData.array()),keyRequest.requestData.size()),&licenseResponse),HI_TRUE);
        const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),licenseResponse.size());
        HITEST_CHECK_SUCCESS(ModularDrmInfo->provideKeyResponse(sessionId, licenseResponse, keySetId));
    if (keySetId.size() == zero)
    {
        HITEST_FailPrint((HI_CHAR *)__FUNCTION__,HI_FAILURE, __LINE__);
    }
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iNorm_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥playreadyçš„uuidï¼Œåˆ›å»ºè§£å¯†å¯¹è±¡æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_001(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iNorm_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒèŽ·å–keyåŽï¼Œå¼€å§‹åˆ›å»ºå¯¹è±¡è¿›è¡Œè§£å¯†ï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_002(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iNorm_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œé”€æ¯å¯¹è±¡åŽï¼Œå†åˆ›å»ºè§£å¯†å¯¹è±¡ï¼Œè¿”å›žå¯¹è±¡handleã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_003(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_CHECK_SUCCESS(CryptoInterface::Destroy(CryptoInfo));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iNorm_004
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œæž„é€ åˆæ³•sessionå‚æ•°ï¼Œè°ƒç”¨createæŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_004(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iAbnm_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥éžplayreadyçš„uuidï¼Œæ‰§è¡ŒæˆåŠŸï¼Œåˆ›å»ºéžè§£å¯†å¯¹è±¡ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_005(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoOtherInfo = CryptoInterface::Create(kRandomUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_S32 numSubSamples = 1;
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoOtherInfo->decrypt(HI_FALSE,kInvalidKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iAbnm_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥è¶…é•¿åˆå§‹æ•°æ®ï¼Œåˆ›å»ºè§£å¯†å¯¹è±¡æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_006(HI_VOID)
{
    Vector<HI_U8> invalidInitData;
    for(HI_U32 i = 0;i < HI_LENGTH;i++)
    {
        invalidInitData.push_back(255);
    }
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(invalidInitData.editArray()),invalidInitData.size()));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iAbnm_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥åˆå§‹æ•°æ®å¤§å°ä¸ºè´Ÿæ•°ï¼Œåˆ›å»ºè§£å¯†å¯¹è±¡å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_007(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HI_S32 initSize =-1;
    CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),initSize);
    if (HI_NULL != CryptoInfo)
    {
        HITEST_FailPrint((HI_CHAR *)__FUNCTION__,HI_FAILURE, __LINE__);
    }
        HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iAbnm_004
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œuuidä¸ºç©ºï¼Œåˆ›å»ºè§£å¯†å¯¹è±¡å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_008(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    CryptoInfo = CryptoInterface::Create(HI_NULL,(HI_VOID*)(sessionId.editArray()),sessionId.size());
    if (NULL != CryptoInfo)
    {
        HITEST_FailPrint((HI_CHAR*)__FUNCTION__, HI_FAILURE, __LINE__);
    }
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iAbnm_005
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒinitDataå…¥å‚ç©ºæŒ‡é’ˆï¼Œåˆ›å»ºè§£å¯†å¯¹è±¡ï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_009(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,HI_NULL,sessionId.size());
    if (HI_NULL != CryptoInfo)
    {
        HITEST_FailPrint((HI_CHAR *)__FUNCTION__,HI_FAILURE, __LINE__);
    }
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iAbnm_007
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼ŒinitDataå…¥å‚ä¸ºç©ºï¼Œåˆ›å»ºè§£å¯†å¯¹è±¡ï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_010(HI_VOID)
{
    const HI_VOID* initData  = HI_NULL;
    CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,initData,zero);
    if (HI_NULL != CryptoInfo)
    {
        HITEST_FailPrint((HI_CHAR *)__FUNCTION__,HI_FAILURE, __LINE__);
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iAbnm_008
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œæœªæ‰“å¼€sessionï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_011(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size());
    if (HI_NULL != CryptoInfo)
    {
        HITEST_FailPrint((HI_CHAR *)__FUNCTION__,HI_FAILURE, __LINE__);
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iAbnm_009
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œå…³é—­session åŽï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸï¼Œä½†å¯¹è±¡è§£å¯†å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_012(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    HI_S32 numSubSamples = 1;
    HI_U8 decryptData[10];
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,decryptData,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Create_iStre_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåå¤è°ƒç”¨åˆ›å»ºè§£å¯†å¯¹è±¡æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Create_013(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    CryptoInterface* CryptoInfo[HITEST_STRESS_TIMES] = {NULL};

    for (HI_S32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        HITEST_CHECK_NULL(CryptoInfo[i] = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    }
        HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    for (HI_S32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        HITEST_CHECK_SUCCESS(CryptoInterface::Destroy(CryptoInfo[i]));
        CryptoInfo[i] = HI_NULL;
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Destroy_iNorm_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œæ­£å¸¸åˆ›å»ºè§£å¯†å¯¹è±¡åŽé”€æ¯ï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Destroy_001(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,reinterpret_cast<const char*>(sessionId.array()),sessionId.size()));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    HITEST_CHECK_SUCCESS(CryptoInterface::Destroy(CryptoInfo));
    CryptoInfo = HI_NULL;
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Destroy_iNorm_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè§£å¯†åŽé”€æ¯å¯¹è±¡ï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Destroy_002(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    HI_S32 numSubSamples = 1;
    HI_U8 decryptData[10];
    String8 errorDetailMsg;
    HI_S32 ret;
    ret = CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,decryptData,errorDetailMsg);
    HITEST_ASSERT_EQUAL(10,ret);
    HITEST_ASSERT_EQUAL(0, memcmp(decryptData, kTestResult, sizeof(kTestResult)));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    HITEST_CHECK_SUCCESS(CryptoInterface::Destroy(CryptoInfo));
    CryptoInfo = HI_NULL;
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Destroy_iAbnm_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œå¯¹è±¡ä¸ºç©ºï¼Œé”€æ¯å¯¹è±¡ï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Destroy_003(HI_VOID)
{
    HITEST_CHECK_FAIL(CryptoInterface::Destroy(CryptoInfo));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Destroy_iAbnm_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œé‡å¤é”€æ¯å¯¹è±¡ï¼ŒæŽ¥å£è°ƒç”¨å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Destroy_004(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    HITEST_CHECK_SUCCESS(CryptoInterface::Destroy(CryptoInfo));
    CryptoInfo = HI_NULL;
    HITEST_CHECK_FAIL(CryptoInterface::Destroy(CryptoInfo));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Destroy_iAbnm_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œå…¥å‚ç©ºæŒ‡é’ˆï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Destroy_005(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    HITEST_CHECK_FAIL(CryptoInterface::Destroy(CryptoOtherInfo));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_Destroy_iStre_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåå¤åˆ›å»ºé”€æ¯å¯¹è±¡ï¼Œæ¯æ¬¡è°ƒç”¨æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_Destroy_006(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    CryptoInterface* CryptoInfo[HITEST_STRESS_TIMES] = {NULL};
    for (HI_S32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        HITEST_CHECK_NULL(CryptoInfo[i] = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    }
     HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    for (HI_S32 i=0;i<HITEST_STRESS_TIMES;i++)
    {
        HITEST_CHECK_SUCCESS(CryptoInterface::Destroy(CryptoInfo[i]));
        CryptoInfo[i] = HI_NULL;
    }
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_isCryptoSchemeSupported_iNorm_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œå®‰è£…playreadyåŽï¼Œè¾“å…¥å¯¹åº”uuidè¿›è¡ŒæŸ¥è¯¢ï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_Crypto_isCryptoSchemeSupported_001(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_ASSERT_EQUAL(CryptoInfo->isCryptoSchemeSupported(kPlayReadyUuid),HI_TRUE);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_isCryptoSchemeSupported_iNorm_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œç›´æŽ¥åˆ›å»ºè§£å¯†å¯¹è±¡åŽï¼ŒæŸ¥è¯¢æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_isCryptoSchemeSupported_002(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_ASSERT_EQUAL(CryptoInfo->isCryptoSchemeSupported(kPlayReadyUuid),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_isCryptoSchemeSupported_iAbnm_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œè¾“å…¥éžæ³•uuidï¼Œè¿›è¡ŒæŸ¥è¯¢ï¼Œè¿”å›žHI_FALSEã€‚
*******************************************************************************/
HI_S32 Test_Crypto_isCryptoSchemeSupported_003(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_ASSERT_EQUAL((CryptoInfo->isCryptoSchemeSupported(kRandomUuid)),HI_FALSE);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_isCryptoSchemeSupported_iAbnm_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œç›´æŽ¥åˆ›å»ºéžè§£å¯†å¯¹è±¡ï¼Œè°ƒç”¨æŸ¥è¯¢æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_isCryptoSchemeSupported_004(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kRandomUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_ASSERT_EQUAL(CryptoInfo->isCryptoSchemeSupported(kPlayReadyUuid),HI_TRUE);

    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_isCryptoSchemeSupported_iAbnm_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œuuidä¸ºç©ºï¼Œè°ƒç”¨æŸ¥è¯¢æŽ¥å£æˆåŠŸï¼Œè¿”å›žHI_FALSEã€‚
*******************************************************************************/
HI_S32 Test_Crypto_isCryptoSchemeSupported_005(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_ASSERT_EQUAL(CryptoInfo->isCryptoSchemeSupported(HI_NULL),HI_FALSE);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_isCryptoSchemeSupported_iAbnm_004
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåˆ›å»ºéžæ³•çš„è§£å¯†å¯¹è±¡ï¼Œè°ƒç”¨æŸ¥è¯¢æŽ¥å£æˆåŠŸï¼Œè¿”å›žHI_FALSEã€‚
*******************************************************************************/
HI_S32 Test_Crypto_isCryptoSchemeSupported_006(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    CryptoInfo = CryptoInterface::Create(kRandomUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size());
    HITEST_ASSERT_EQUAL(CryptoInfo->isCryptoSchemeSupported(kPlayReadyUuid),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_isCryptoSchemeSupported_iStre_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡åŽï¼Œåå¤è°ƒç”¨æŽ¥å£è¿›è¡ŒæŸ¥è¯¢ï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸï¼Œè¿”å›žHI_TRUEã€‚
*******************************************************************************/
HI_S32 Test_Crypto_isCryptoSchemeSupported_007(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    for (HI_S32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        HITEST_ASSERT_EQUAL(CryptoInfo->isCryptoSchemeSupported(kPlayReadyUuid),HI_TRUE);
    }
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iNorm_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼Œè§£å¯†AES_CTRåŠ å¯†çš„æ•°æ®ï¼ŒæŽ¥å£è°ƒç”¨æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_001(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    HI_S32 numSubSamples = 1;
    HI_U8 decryptData[10];
    String8 errorDetailMsg;
    HI_S32 ret;
    ret = CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_WV,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,decryptData,errorDetailMsg);
    HITEST_ASSERT_EQUAL(ERROR_DRM_CANNOT_HANDLE,ret);
    ret = CryptoInfo->decrypt(HI_TRUE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,decryptData,errorDetailMsg);
    HITEST_ASSERT_EQUAL(ERROR_DRM_CANNOT_HANDLE,ret);
    //HITEST_ASSERT_EQUAL(0, memcmp(decryptData, kTestResult, sizeof(kTestResult)));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼Œè§£å¯†keyéžæ³•ï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_002(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_S32 numSubSamples = 1;
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kInvalidKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_002
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼ŒsrcSizeå¤§äºŽè§£å¯†æ•°æ®é•¿åº¦ï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_003(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_S32 numSubSamples = 1;
    HI_S32 srcSize = sizeof(kTestData)+1;
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,srcSize,&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_003
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼ŒsrcSizeå°äºŽè§£å¯†æ•°æ®é•¿åº¦ï¼Œè°ƒç”¨æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_004(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_S32 numSubSamples = 1;
    HI_S32 srcSize = sizeof(kTestData)-1;
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HI_S32 ret;
    ret = CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,srcSize,&SubSamples,numSubSamples,pDst,errorDetailMsg);
    HITEST_ASSERT_EQUAL(10,ret);
    HITEST_ASSERT_EQUAL(0, memcmp(pDst, kTestResult, sizeof(kTestResult)));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_004
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼Œå…¥å‚å‡ºå‚ä¸ºNULLï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_005(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_S32 numSubSamples = 1;
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg1;
    String8 errorDetailMsg2;
    String8 errorDetailMsg3;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,HI_NULL,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg1));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg1));

    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,HI_NULL,errorDetailMsg2));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg2));

    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),HI_NULL,numSubSamples,pDst,errorDetailMsg3));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg3));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_005
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼Œsecureè®¾ç½®ä¸ºHI_TRUEï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_006(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_S32 numSubSamples = 1;
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_TRUE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_006
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼Œs32srcSizeè®¾ç½®ä¸ºè´Ÿæ•°ï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_007(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    HI_S32 s32srcSize = -1;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_S32 numSubSamples = 1;
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,s32srcSize,&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_007
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼ŒnumSubSamplesè®¾ç½®ä¸ºè´Ÿæ•°ï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_008(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    HI_S32 numSubSamples = -1;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_008
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼Œivå‘é‡éžæ³•ï¼Œè°ƒç”¨æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_009(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    HI_S32 numSubSamples = 1;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kInvalidTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_009
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼Œåˆ›å»ºéžæ³•çš„è§£å¯†å¯¹è±¡ä¸”æ”¯æŒè§£å¯†ç­–ç•¥æ—¶ï¼Œè°ƒç”¨è§£å¯†æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_010(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    CryptoInfo = CryptoInterface::Create(kRandomUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size());
    HITEST_ASSERT_EQUAL(CryptoInfo->isCryptoSchemeSupported(kPlayReadyUuid),HI_TRUE);
    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    HI_S32 numSubSamples = 1;
    HI_U8 decryptData[10];
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,decryptData,errorDetailMsg));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iAbnm_010
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼Œç›´æŽ¥åˆ›å»ºå¯¹è±¡åŽï¼Œè°ƒç”¨è§£å¯†æŽ¥å£å¤±è´¥ã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_011(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    HI_S32 numSubSamples = 1;
    HI_U8 decryptData[10];
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,decryptData,errorDetailMsg));

    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*******************************************************************************
* Test Case ID    : HITEST_SECURITY_Crypto_decrypt_iStre_001
* Test Item        : å•æ¿ä¸Šç”µåˆå§‹åŒ–æœåŠ¡ï¼Œåå¤è°ƒç”¨æŽ¥å£æˆåŠŸã€‚
*******************************************************************************/
HI_S32 Test_Crypto_decrypt_012(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_SUCCESS(decryptPrepare(ModularDrmInfo,sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    HI_S32 numSubSamples = 1;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    HI_S32 ret;
    for (HI_S32 i = 0;i < HITEST_STRESS_TIMES;i++)
    {
        ret = CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg);
        HITEST_ASSERT_EQUAL(10,ret);
        HITEST_ASSERT_EQUAL(0, memcmp(pDst, kTestResult, sizeof(kTestResult)));
    }
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æ‰§è¡Œå‘½ä»¤å‰éœ€è¦å…ˆæ‰‹åŠ¨è®¾ç½®çŽ¯å¢ƒ*/
/*æœªå¯åŠ¨drmæœåŠ¡ï¼Œåˆ›å»ºdrmå¯¹è±¡å¤±è´¥*/

HI_S32 Test_ModularDrm_EnvironmentSetting_001(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æœªå¯åŠ¨drmæœåŠ¡ï¼Œå…³é—­session*/

HI_S32 Test_ModularDrm_EnvironmentSetting_002(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æœªå¯åŠ¨drmæœåŠ¡ï¼Œè°ƒç”¨getKeyRequestæŽ¥å£èŽ·å–keyè¯·æ±‚ä¿¡æ¯*/

HI_S32 Test_ModularDrm_EnvironmentSetting_003(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_FAIL(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æœªå¯åŠ¨drmæœåŠ¡ï¼Œè°ƒç”¨provideKeyRespondeæŽ¥å£èŽ·å–å“åº”*/

HI_S32 Test_ModularDrm_EnvironmentSetting_004(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }

    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> licenseResponse;
    for(HI_U32 j = 0;j < 16;j++)
    {
        licenseResponse.push_back(1);
    }
    const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),licenseResponse.size());
    Vector<HI_U8> keySetId;
    HITEST_CHECK_FAIL(ModularDrmInfo->provideKeyResponse(sessionId, licenseResponse, keySetId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æœªå¯åŠ¨drmæœåŠ¡ï¼Œè°ƒç”¨æŸ¥è¯¢æŽ¥å£*/

HI_S32 Test_ModularDrm_EnvironmentSetting_005(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HITEST_ASSERT_EQUAL(CryptoInfo->isCryptoSchemeSupported(kPlayReadyUuid),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æœªå¯åŠ¨drmæœåŠ¡ï¼Œè°ƒç”¨è§£å¯†æŽ¥å£è¿›è¡Œè§£å¯†*/

HI_S32 Test_ModularDrm_EnvironmentSetting_006(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    HI_S32 numSubSamples = 1;
    HI_U8 decryptData[10];
    String8 errorDetailMsg;

    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,decryptData,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æ²¡æœ‰å®‰è£…æ’ä»¶åº“ï¼Œåˆ›å»ºdrmå¯¹è±¡*/

HI_S32 Test_ModularDrm_EnvironmentSetting_007(HI_VOID)
{
    Vector<HI_U8> sessionId;
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_CHECK_FAIL(ModularDrmInfo->openSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*è·¯å¾„ä¸‹æ²¡æœ‰å®‰è£…æ’ä»¶åº“ï¼Œè¿›è¡ŒæŸ¥è¯¢*/

HI_S32 Test_ModularDrm_EnvironmentSetting_008(HI_VOID)
{
    const HI_CHAR* mimeType = "video/mp4";
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_ASSERT_EQUAL(ModularDrmInfo->isCryptoSchemeSupported(kPlayReadyUuid,mimeType),HI_TRUE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æ²¡æœ‰å®‰è£…æ’ä»¶åº“ï¼Œè°ƒç”¨getKeyRequestæŽ¥å£èŽ·å–keyè¯·æ±‚ä¿¡æ¯*/
HI_S32 Test_ModularDrm_EnvironmentSetting_009(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }

    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST pKeyRequest;
    HI_DRM_KEY_TYPE pKeyStatus = HI_DRM_KEY_TYPE_STREAMING;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_FAIL(ModularDrmInfo->getKeyRequest(sessionId,initData,String8("video/mp4").string(),pKeyStatus,KeyedVector<String8, String8>(),&pKeyRequest));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æ²¡æœ‰å®‰è£…æ’ä»¶åº“ï¼Œè°ƒç”¨provideKeyResponseæŽ¥å£èŽ·å–keyè¯·æ±‚å›žåº”*/
HI_S32 Test_ModularDrm_EnvironmentSetting_010(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }

    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> licenseResponse;
    for(HI_U32 j = 0;j < 16;j++)
    {
        licenseResponse.push_back(1);
    }
    const String8 strLicenseResponse(reinterpret_cast<const char*>(licenseResponse.array()),licenseResponse.size());
    Vector<HI_U8> keySetId;
    HITEST_CHECK_FAIL(ModularDrmInfo->provideKeyResponse(sessionId, licenseResponse, keySetId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æ²¡æœ‰åŠ è½½æ’ä»¶åº“ï¼Œè°ƒç”¨è§£å¯†æŽ¥å£*/
HI_S32 Test_ModularDrm_EnvironmentSetting_011(HI_VOID)
{
    Vector<HI_U8> sessionId;
    for(HI_U32 i = 0;i < 16;i++)
    {
        sessionId.push_back(1);
    }
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    HI_S32 numSubSamples = 1;
    HI_U8 decryptData[10];
    String8 errorDetailMsg;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kTestKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,decryptData,errorDetailMsg));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*ä¸å­˜åœ¨æ’ä»¶åº“å®‰è£…è·¯å¾„ï¼Œåˆ›å»ºdrmå¯¹è±¡å¤±è´¥*/

HI_S32 Test_ModularDrm_EnvironmentSetting_012(HI_VOID)
{
    Vector<HI_U8> sessionId;
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_CHECK_FAIL(ModularDrmInfo->openSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*æœªåŠ è½½playreadyå®‰å…¨è¯ä¹¦ï¼Œåˆ›å»ºdrmå¯¹è±¡å¤±è´¥*/

HI_S32 Test_ModularDrm_EnvironmentSetting_013(HI_VOID)
{
    Vector<HI_U8> sessionId;
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_CHECK_FAIL(ModularDrmInfo->openSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

/*å®‰è£…playreadyè¯ä¹¦è·¯å¾„é”™è¯¯æˆ–è€…ä¸å­˜åœ¨ï¼Œåˆ›å»ºdrmå¯¹è±¡å¤±è´¥*/

HI_S32 Test_ModularDrm_EnvironmentSetting_014(HI_VOID)
{
    Vector<HI_U8> sessionId;
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_CHECK_FAIL(ModularDrmInfo->openSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

HI_S32 Test_ModularDrm_otherOpera_001(HI_VOID)
{
    Vector<HI_U8> sessionId;
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    Vector<HI_U8> initData = getInitData(kTestDrmHeaderXml);
    HI_DRM_KEY_REQUEST keyRequest;
    EXPECT_NE(OK, ModularDrmInfo->getKeyRequest(sessionId,
                        initData,
                        String8("video/mp4").string(),
                        (HI_DRM_KEY_TYPE)DrmPlugin::kKeyType_Offline,
                        KeyedVector<String8, String8>(),
                        &keyRequest));
    EXPECT_NE(OK, ModularDrmInfo->getKeyRequest(sessionId,
                        initData,
                        String8("video/mp4").string(),
                        (HI_DRM_KEY_TYPE)DrmPlugin::kKeyType_Release,
                        KeyedVector<String8, String8>(),
                        &keyRequest));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

HI_S32 Test_ModularDrm_otherOpera_002(HI_VOID)
{
    Vector<HI_U8> sessionId;
    Vector<HI_U8> sessionId2;
    Vector<HI_U8> keySetId;
    KeyedVector<String8, String8> infoMap;
    HI_DRM_PROVITION_REQUEST request;
    String8 cert_type;
    String8 cert_authority;
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->restoreKeys(sessionId, keySetId));
    HITEST_CHECK_FAIL(ModularDrmInfo->restoreKeys(sessionId2, keySetId));
    HITEST_CHECK_FAIL(ModularDrmInfo->removeKeys(sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->removeKeys(sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->removeKeys(sessionId2));
    HITEST_CHECK_FAIL(ModularDrmInfo->queryKeyStatus(sessionId, infoMap));
    HITEST_CHECK_FAIL(ModularDrmInfo->queryKeyStatus(sessionId2, infoMap));
    HITEST_CHECK_FAIL(ModularDrmInfo->getProvisionRequest(cert_type, cert_authority, &request));
    HITEST_CHECK_FAIL(ModularDrmInfo->provideProvisionResponse(sessionId, sessionId, sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->provideProvisionResponse(sessionId2, sessionId, sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->unprovisionDevice());
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

HI_S32 Test_ModularDrm_otherOpera_003(HI_VOID)
{
    Vector<HI_U8> sessionId;
    Vector<HI_U8> sessionId2;
    Vector<HI_U8> keySetId;
    List<Vector<HI_U8> > secureStops;
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->getSecureStop(sessionId, sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->getSecureStop(sessionId2, sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->getSecureStops(secureStops));
    HITEST_CHECK_FAIL(ModularDrmInfo->releaseSecureStops(sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->releaseSecureStops(sessionId2));
    HITEST_CHECK_FAIL(ModularDrmInfo->releaseAllSecureStops());
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

HI_S32 Test_ModularDrm_otherOpera_004(HI_VOID)
{
    Vector<HI_U8> sessionId;
    Vector<HI_U8> sessionId2;
    Vector<HI_U8> value;
    String8 name;
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->getPropertyByteArray(name, value));
    HITEST_CHECK_FAIL(ModularDrmInfo->setPropertyString(name, name));
    HITEST_CHECK_FAIL(ModularDrmInfo->setPropertyByteArray(name, value));
    HITEST_CHECK_FAIL(ModularDrmInfo->setCipherAlgorithm(sessionId, name));
    HITEST_CHECK_FAIL(ModularDrmInfo->setMacAlgorithm(sessionId, name));
    HITEST_CHECK_FAIL(ModularDrmInfo->setCipherAlgorithm(sessionId2, name));
    HITEST_CHECK_FAIL(ModularDrmInfo->setMacAlgorithm(sessionId2, name));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

HI_S32 Test_ModularDrm_otherOpera_005(HI_VOID)
{
    Vector<HI_U8> sessionId;
    Vector<HI_U8> value;
    String8 name;
    HI_BOOL match;
    String8 algorithm;
    DrmListener* listener;
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->encrypt(sessionId, sessionId, sessionId, sessionId, sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->sign(sessionId, sessionId, sessionId, sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->verify(sessionId, sessionId, sessionId, sessionId, match));
    HITEST_CHECK_FAIL(ModularDrmInfo->signRSA(sessionId, algorithm, sessionId, sessionId, sessionId));
    HITEST_CHECK_FAIL(ModularDrmInfo->setListener(listener));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

HI_S32 Test_Crypto_otherOpera_001(HI_VOID)
{
    Vector<HI_U8> sessionId;
    HI_CHAR* mime = NULL;
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));

    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));
    //CryptoInfo = CryptoInterface::Create(kPlayReadyUuid, initData, initSize);
    HITEST_ASSERT_EQUAL(CryptoInfo->requiresSecureDecoderComponent(mime), HI_FALSE);
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

HI_S32 Test_Crypto_otherOpera_002(HI_VOID)
{
    HITEST_CHECK_NULL(ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    Vector<HI_U8> sessionId;
    HI_U8 * p_kid = NULL;
    HI_U8 * p_kiv = NULL;
    HITEST_CHECK_SUCCESS(ModularDrmInfo->openSession(sessionId));
    HITEST_CHECK_NULL(CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size()));

    HI_DRM_SUBSAMPLES SubSamples;
    SubSamples.u32numBytesOfClearData = 0;
    SubSamples.u32numBytesOfEncryptedData = sizeof(kTestData);
    Vector<HI_U8> decryptedDataBuffer;
    decryptedDataBuffer.setCapacity(sizeof(kTestData));
    HI_S32 numSubSamples = -1;
    HI_VOID* pDst = decryptedDataBuffer.editArray();
    String8 errorDetailMsg;
    //HI_CRYPTO_MODE mode = HI_CRYPTO_MODE_AES_WV+HI_CRYPTO_MODE_AES_CTR;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_TRUE,p_kid, p_kiv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_TRUE,kInvalidKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kInvalidKeyId, kTestIv,HI_CRYPTO_MODE_AES_CTR,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    numSubSamples = 1;
    //HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kInvalidKeyId, kTestIv,mode/*HI_CRYPTO_MODE_AES_CTR*/,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kInvalidKeyId, kTestIv,HI_CRYPTO_MODE_UNENCRYPTED,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kInvalidKeyId, kTestIv,HI_CRYPTO_MODE_AES_WV,kTestData,sizeof(kTestData),&SubSamples,numSubSamples,pDst,errorDetailMsg));
    HI_DRM_SUBSAMPLES *SubSamples1 = NULL;
    HITEST_CHECK_FAIL(CryptoInfo->decrypt(HI_FALSE,kInvalidKeyId, kTestIv,HI_CRYPTO_MODE_AES_WV,kTestData,sizeof(kTestData),SubSamples1,numSubSamples,pDst,errorDetailMsg));
    HITEST_ASSERT_CONDITION_ERR((HI_NULL != errorDetailMsg));
    HITEST_CHECK_FAIL(CryptoInfo->setMediaDrmSession(sessionId));
    HITEST_CHECK_SUCCESS(ModularDrmInfo->closeSession(sessionId));
    Test_Destroy((HI_CHAR *)__FUNCTION__,__LINE__);
    return 0;
}

class TestDrmClientInterface
{
public:
    HI_U8 TestsetListener();
    HI_U8 Testnotify();
    HI_U8 TestDrmClientInit(const HI_U8 uuid[16])
    {
        mDrmClient = new DrmClient(uuid);
        return HI_SUCCESS;
    }
    HI_U8 TestDrmClientRel()
    {
        HI_LOGD("%s", __FUNCTION__);

        if (mDrmClient != NULL)
        {
            delete mDrmClient;
            mDrmClient = NULL;
        }
        return HI_SUCCESS;
    }
private:
    DrmClient * mDrmClient;
};

HI_U8 TestDrmClientInterface::TestsetListener()
{
    DrmListener * listener;
    ASSERT_EQ(HI_SUCCESS, TestDrmClientInit(kPlayReadyUuid));
    ASSERT_EQ(HI_SUCCESS, mDrmClient->setListener(listener));

    return HI_SUCCESS;
}

HI_U8 TestDrmClientInterface::Testnotify()
{
    HI_S32 extra = 3;
    Parcel obj;
    EXPECT_EQ(HI_SUCCESS, TestDrmClientInit(kPlayReadyUuid));
    mDrmClient->notify(DrmPlugin::kDrmPluginEventProvisionRequired, extra, &obj);
    mDrmClient->notify(DrmPlugin::kDrmPluginEventKeyNeeded, extra, &obj);
    mDrmClient->notify(DrmPlugin::kDrmPluginEventKeyExpired, extra, &obj);
    mDrmClient->notify(DrmPlugin::kDrmPluginEventVendorDefined, extra, &obj);
    mDrmClient->notify(DrmPlugin::kDrmPluginEventSessionReclaimed, extra, &obj);
    mDrmClient->notify(DrmPlugin::kDrmPluginEventExpirationUpdate, extra, &obj);
    mDrmClient->notify(DrmPlugin::kDrmPluginEventKeysChange, extra, &obj);
    return HI_SUCCESS;
}

TestDrmClientInterface testDrmClient;
HI_S32 TestDrmClientInterface_TestsetListener()
{
    if (testDrmClient.TestsetListener())
    {
        TEST_INFO("TestsetListener failed.\n");
        HITEST_CHECK_SUCCESS(HI_FALSE);
        return HI_FALSE;
    }
    else
    {
        TEST_INFO("TestsetListener success.\n");
        HITEST_CHECK_SUCCESS(HI_SUCCESS);
    }
    testDrmClient.TestDrmClientRel();

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestDrmClientInterface_Testnotify()
{
    if (testDrmClient.Testnotify())
    {
        TEST_INFO("Testnotify failed.\n");
        HITEST_CHECK_SUCCESS(HI_FALSE);
        return HI_FALSE;
    }
    else
    {
        TEST_INFO("Testnotify success.\n");
        HITEST_CHECK_SUCCESS(HI_SUCCESS);
    }
    testDrmClient.TestDrmClientRel();

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

class TestCryptoClientInterface
{
public:
    HI_U8 TestnotifyResolution();
    HI_U8 TestCryptoClientInit(const HI_U8 uuid[16], const HI_VOID *initData, HI_S32 initSize)
    {
        mCryptoClient = new CryptoClient(uuid, initData, initSize);
        return HI_SUCCESS;
    }
    HI_U8 TestCryptoClientRel()
    {
        HI_LOGD("%s", __FUNCTION__);

        if (mCryptoClient != NULL)
        {
            delete mCryptoClient;
            mCryptoClient = NULL;
        }
        return HI_SUCCESS;
    }

private:
    CryptoClient * mCryptoClient;
};

HI_U8 TestCryptoClientInterface::TestnotifyResolution()
{
    Vector<HI_U8> sessionId;
    HI_U32 width = 1;
    HI_U32 height = 2;
    EXPECT_NE(HI_NULL, ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid));
    EXPECT_EQ(HI_SUCCESS, ModularDrmInfo->openSession(sessionId));
    EXPECT_EQ(HI_SUCCESS, TestCryptoClientInit(kPlayReadyUuid, (HI_VOID*)(sessionId.editArray()), sessionId.size()));
    mCryptoClient->notifyResolution(width, height);
    return HI_SUCCESS;
}

TestCryptoClientInterface testCryptoClient;
HI_S32 TestDrmClientInterface_TestnotifyResolution()
{
    if (testCryptoClient.TestnotifyResolution())
    {
        TEST_INFO("TestnotifyResolution failed.\n");
        HITEST_CHECK_SUCCESS(HI_FALSE);
        return HI_FALSE;
    }
    else
    {
        TEST_INFO("TestnotifyResolution success.\n");
        HITEST_CHECK_SUCCESS(0);
    }
    testCryptoClient.TestCryptoClientRel();

    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}








HI_S32 TestDrmService_TestDeleteDrmService()
{
    DrmService* drmService = new DrmService();
    delete drmService;

    HITEST_CHECK_SUCCESS(0);
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestDrmSessionManager_TestDeleteDrmSessionManager()
{
    sp<DrmSessionManager> drmSessionManager = new DrmSessionManager();

    HITEST_CHECK_SUCCESS(0);
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestDrmSessionManager_TestIsEqualSessionId()
{
    Vector<HI_U8> sessionid1;
    Vector<HI_U8> sessionid2;

    sessionid1.appendArray((const unsigned char*)"pr0", 4);
    sessionid2.appendArray((const unsigned char*)"pr1", 4);
    if (0 == isEqualSessionId(sessionid1, sessionid2))
    {
        TEST_INFO("TestIsEqualSessionId success.\n");
        HITEST_CHECK_SUCCESS(0);
    }
    else
    {
        TEST_INFO("TestIsEqualSessionId failed.\n");
        HITEST_CHECK_SUCCESS(HI_FALSE);
        return HI_FALSE;
    }
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestDrmSessionManager_TestremoveDrm()
{
    struct DrmSessionClient : public DrmSessionClientInterface
    {
        DrmSessionClient(Drm* drm) : mDrm(drm)
        {
        }

        virtual HI_BOOL reclaimSession(const Vector<HI_U8>& sessionId)
        {
            return HI_TRUE;
        }

    protected:
        virtual ~DrmSessionClient() {}

    private:
        wp<Drm> mDrm;
    };

    sp<DrmSessionClientInterface> mDrmSessionClient;
    mDrmSessionClient = new DrmSessionClient(NULL);
    DrmSessionManager* drmSessionManager = new DrmSessionManager();
    Vector<HI_U8> sessionid1;

    drmSessionManager->addSession(1111, mDrmSessionClient, sessionid1);

    sp<DrmSessionClientInterface> mDrmSessionClient2;
    mDrmSessionClient2 = new DrmSessionClient(NULL);
    drmSessionManager->removeDrm(mDrmSessionClient2);

    HITEST_CHECK_SUCCESS(0);
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestSharedLibrary_TestLookup()
{
    String8 path("");
    SharedLibrary sl(path);
    sl.lookup("");

    HITEST_CHECK_SUCCESS(0);
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

// TODO:
HI_S32 TestDrm_TestsetListener()
{
    Drm drm;
    drm.setListener(NULL);

    HITEST_CHECK_SUCCESS(0);
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestDrm_TestsendEvent()
{
    Drm drm;
    Vector<HI_U8> sessionid1;
    Vector<HI_U8> data;
    Parcel dataSource;
    sp<IDrmClient> listener = interface_cast<IDrmClient>(dataSource.readStrongBinder());
    drm.setListener(listener);
    drm.sendEvent( DrmPlugin::kDrmPluginEventProvisionRequired, 1, &sessionid1, &data);

    HITEST_CHECK_SUCCESS(0);
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestDrm_TestsendExpirationUpdate()
{
    Drm drm;
    Vector<HI_U8> sessionid1;
    Parcel dataSource;
    sp<IDrmClient> listener = interface_cast<IDrmClient>(dataSource.readStrongBinder());
    drm.setListener(listener);
    drm.sendExpirationUpdate( &sessionid1, 1111);

    HITEST_CHECK_SUCCESS(0);
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestDrm_TestsendKeysChange()
{
    Drm drm;
    Vector<HI_U8> sessionid1;
    Vector<DrmPlugin::KeyStatus> keyStatusList;
    Parcel dataSource;
    sp<IDrmClient> listener = interface_cast<IDrmClient>(dataSource.readStrongBinder());
    drm.setListener(listener);
    drm.sendKeysChange( &sessionid1, &keyStatusList, HI_FALSE);

    HITEST_CHECK_SUCCESS(0);
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestCrypto_TestfindFactoryForScheme()
{
    Crypto crypto;
    HI_U8 uuid[ HI_DRM_UUID_LEN ] = {0};
    HI_U8 uuid2[ HI_DRM_UUID_LEN ] = {1, 1, 1, 1,1, 1, 1, 1,1, 1, 1, 1,1, 1, 1, 1};

    crypto.isCryptoSchemeSupported(uuid);
    crypto.isCryptoSchemeSupported(uuid2);

    HITEST_CHECK_SUCCESS(0);
    HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
    return HI_SUCCESS;
}

HI_S32 TestCrypto_TestcreatePlugin()
{
    Crypto crypto;
    HI_U8 uuid[ HI_DRM_UUID_LEN ] = {0x9a, 0x04, 0xF0, 0x79, 0x98, 0x40, 0x42, 0x86,
    0xAB, 0x92, 0xE6, 0x5B, 0xE0, 0x88, 0x5F, 0x95};
    HI_CHAR* data = (HI_CHAR*)"abc";

    crypto.createPlugin(uuid, data, 4);

    if (HI_FAILURE == crypto.createPlugin(uuid, data, 4))
    {
        TEST_INFO("TestcreatePlugin success.\n");
        HITEST_CHECK_SUCCESS(0);
        HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
        return HI_SUCCESS;
    }
    else
    {
        TEST_INFO("TestcreatePlugin failed.\n");
        HITEST_CHECK_SUCCESS(HI_FALSE);
        return HI_FALSE;
    }
}

HI_S32 TestCrypto_TestdestroyPlugin()
{
    Crypto crypto;

    if (HI_FAILURE == crypto.destroyPlugin())
    {
        TEST_INFO("TestcreatePlugin success.\n");
        HITEST_CHECK_SUCCESS(0);
        HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
        return HI_SUCCESS;
    }
    else
    {
        TEST_INFO("TestcreatePlugin failed.\n");
        HITEST_CHECK_SUCCESS(HI_FALSE);
        return HI_FALSE;
    }
}

HI_S32 TestCrypto_TestrequiresSecureDecoderComponent()
{
    Crypto crypto;

    if (0 == crypto.requiresSecureDecoderComponent(NULL))
    {
        TEST_INFO("TestcreatePlugin success.\n");
        HITEST_CHECK_SUCCESS(0);
        HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
        return HI_SUCCESS;
    }
    else
    {
        TEST_INFO("TestcreatePlugin failed.\n");
        HITEST_CHECK_SUCCESS(HI_FALSE);
        return HI_FALSE;
    }
}

HI_S32 TestCrypto_Testdecrypt()
{
    Crypto crypto;

    if (HI_FAILURE == crypto.decrypt(HI_FALSE, NULL, NULL, CryptoPlugin::kMode_Unencrypted, NULL, 0, NULL, 0, NULL, NULL))
    {
        TEST_INFO("TestcreatePlugin success.\n");
        HITEST_CHECK_SUCCESS(0);
        HITEST_FinalResult((HI_CHAR*)__FUNCTION__, __LINE__);
        return HI_SUCCESS;
    }
    else
    {
        TEST_INFO("TestcreatePlugin failed.\n");
        HITEST_CHECK_SUCCESS(HI_FALSE);
        return HI_FALSE;
    }
}

HITEST_FUNC_S drmService_TESTList[] =
{
    HITEST_ADD_TESTCASE(TestCrypto_Testdecrypt),
    HITEST_ADD_TESTCASE(TestCrypto_TestrequiresSecureDecoderComponent),
    HITEST_ADD_TESTCASE(TestCrypto_TestdestroyPlugin),
    HITEST_ADD_TESTCASE(TestCrypto_TestcreatePlugin),
    HITEST_ADD_TESTCASE(TestCrypto_TestfindFactoryForScheme),
    //HITEST_ADD_TESTCASE(TestDrm_TestsendKeysChange),
    //HITEST_ADD_TESTCASE(TestDrm_TestsendExpirationUpdate),
    //HITEST_ADD_TESTCASE(TestDrm_TestsendEvent),
    //HITEST_ADD_TESTCASE(TestDrm_TestsetListener),
    HITEST_ADD_TESTCASE(TestSharedLibrary_TestLookup),
    HITEST_ADD_TESTCASE(TestDrmSessionManager_TestremoveDrm),
    HITEST_ADD_TESTCASE(TestDrmSessionManager_TestDeleteDrmSessionManager),
    HITEST_ADD_TESTCASE(TestDrmService_TestDeleteDrmService),
    HITEST_ADD_TESTCASE(TestDrmSessionManager_TestIsEqualSessionId),
    HITEST_ADD_TESTCASE(modualrInterfaceTest_Setup),
    HITEST_ADD_TESTCASE(modualrInterfaceTest_isCryptoSchemeSupported),
    HITEST_ADD_TESTCASE(modualrInterfaceTest_OpenSession),
    HITEST_ADD_TESTCASE(modualrInterfaceTest_GenerateKeyRequest),
    HITEST_ADD_TESTCASE(modualrInterfaceTest_GenerateKeyRequestWithInvalidHeader),
    HITEST_ADD_TESTCASE(modualrInterfaceTest_GenerateKeyRequestWithCustomData),
    HITEST_ADD_TESTCASE(modualrInterfaceTest_CheckSecurityLevel),
    HITEST_ADD_TESTCASE(modualrInterfaceTest_Decrypt),
    HITEST_ADD_TESTCASE(modualrInterfaceTest_TearDown),
    HITEST_ADD_TESTCASE(cryptoInterfaceTest_Setup),
    HITEST_ADD_TESTCASE(cryptoInterfaceTest_isCryptoSchemeSupported),
    HITEST_ADD_TESTCASE(cryptoInterfaceTest_requiresSecureDecoderComponent),
    HITEST_ADD_TESTCASE(cryptoInterfaceTest_TearDown),
    HITEST_ADD_TESTCASE(Test_ModularDrm_Create_001),
    HITEST_ADD_TESTCASE(Test_ModularDrm_Create_002),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_Create_003),
    HITEST_ADD_TESTCASE(Test_ModularDrm_Create_004),
    HITEST_ADD_TESTCASE(Test_ModularDrm_Destroy_001),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_Destroy_002),
    HITEST_ADD_TESTCASE(Test_ModularDrm_Destroy_003),
    HITEST_ADD_TESTCASE(Test_ModularDrm_Destroy_004),
    HITEST_ADD_TESTCASE(Test_ModularDrm_Destroy_005),
    HITEST_ADD_TESTCASE(Test_ModularDrm_Destroy_006),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_Destroy_007),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_001),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_002),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_003),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_004),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_005),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_006),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_007),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_008),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_009),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_010),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_011),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_012),
    HITEST_ADD_TESTCASE(Test_ModularDrm_isCryptoSchemeSupported_013),
    HITEST_ADD_TESTCASE(Test_ModularDrm_openSession_001),
    HITEST_ADD_TESTCASE(Test_ModularDrm_openSession_002),
    HITEST_ADD_TESTCASE(Test_ModularDrm_openSession_003),
    HITEST_ADD_TESTCASE(Test_ModularDrm_openSession_004),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_001),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_002),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_003),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_004),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_005),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_006),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_007),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_008),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_009),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_010),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_011),
    HITEST_ADD_TESTCASE(Test_ModularDrm_closeSession_012),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_001),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_002),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_003),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_004),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_005),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_006),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_007),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_008),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_009),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_010),
    HITEST_ADD_TESTCASE(Test_ModularDrm_getKeyRequest_011),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_provideKeyResponse_001),
    HITEST_ADD_TESTCASE(Test_ModularDrm_provideKeyResponse_002),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_provideKeyResponse_003),
    HITEST_ADD_TESTCASE(Test_ModularDrm_provideKeyResponse_004),
    HITEST_ADD_TESTCASE(Test_ModularDrm_provideKeyResponse_005),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_provideKeyResponse_006),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_provideKeyResponse_007),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_provideKeyResponse_008),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_001),
    //HITEST_ADD_TESTCASE(Test_Crypto_Create_002),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_003),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_004),
    //HITEST_ADD_TESTCASE(Test_Crypto_Create_005),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_006),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_007),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_008),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_009),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_010),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_011),
    //HITEST_ADD_TESTCASE(Test_Crypto_Create_012),
    HITEST_ADD_TESTCASE(Test_Crypto_Create_013),
    HITEST_ADD_TESTCASE(Test_Crypto_Destroy_001),
    //HITEST_ADD_TESTCASE(Test_Crypto_Destroy_002),
    HITEST_ADD_TESTCASE(Test_Crypto_Destroy_003),
    HITEST_ADD_TESTCASE(Test_Crypto_Destroy_004),
    HITEST_ADD_TESTCASE(Test_Crypto_Destroy_005),
    HITEST_ADD_TESTCASE(Test_Crypto_Destroy_006),
    HITEST_ADD_TESTCASE(Test_Crypto_isCryptoSchemeSupported_001),
    HITEST_ADD_TESTCASE(Test_Crypto_isCryptoSchemeSupported_002),
    //HITEST_ADD_TESTCASE(Test_Crypto_isCryptoSchemeSupported_003),
    HITEST_ADD_TESTCASE(Test_Crypto_isCryptoSchemeSupported_004),
    HITEST_ADD_TESTCASE(Test_Crypto_isCryptoSchemeSupported_005),
    HITEST_ADD_TESTCASE(Test_Crypto_isCryptoSchemeSupported_006),
    HITEST_ADD_TESTCASE(Test_Crypto_isCryptoSchemeSupported_007),
    //HITEST_ADD_TESTCASE(Test_Crypto_decrypt_001),
    //HITEST_ADD_TESTCASE(Test_Crypto_decrypt_002),
    /*HITEST_ADD_TESTCASE(Test_Crypto_decrypt_003),
    //HITEST_ADD_TESTCASE(Test_Crypto_decrypt_004),
    HITEST_ADD_TESTCASE(Test_Crypto_decrypt_005),
    HITEST_ADD_TESTCASE(Test_Crypto_decrypt_006),
    HITEST_ADD_TESTCASE(Test_Crypto_decrypt_007),
    HITEST_ADD_TESTCASE(Test_Crypto_decrypt_008),
    HITEST_ADD_TESTCASE(Test_Crypto_decrypt_009),
    HITEST_ADD_TESTCASE(Test_Crypto_decrypt_010),
    HITEST_ADD_TESTCASE(Test_Crypto_decrypt_011),*/
    //HITEST_ADD_TESTCASE(Test_Crypto_decrypt_012),
    HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_001),
    HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_002),
    HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_003),
    HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_004),
    HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_005),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_006),
    //HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_007),
    HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_008),
    HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_009),
    HITEST_ADD_TESTCASE(Test_ModularDrm_EnvironmentSetting_010),
    HITEST_ADD_TESTCASE(Test_ModularDrm_otherOpera_001),
    HITEST_ADD_TESTCASE(Test_ModularDrm_otherOpera_002),
    HITEST_ADD_TESTCASE(Test_ModularDrm_otherOpera_003),
    HITEST_ADD_TESTCASE(Test_ModularDrm_otherOpera_004),
    HITEST_ADD_TESTCASE(Test_ModularDrm_otherOpera_005),
    HITEST_ADD_TESTCASE(Test_Crypto_otherOpera_001),
    HITEST_ADD_TESTCASE(Test_Crypto_otherOpera_002),
    HITEST_ADD_TESTCASE(TestDrmClientInterface_TestsetListener),
    HITEST_ADD_TESTCASE(TestDrmClientInterface_Testnotify),
    HITEST_ADD_TESTCASE(TestDrmClientInterface_TestnotifyResolution),
};
}  // namespace android

//return pid(result > 0)
int setOomScoreAdjByName( char* ProcName)
{
    DIR             *dir;
    struct dirent   *d;
    int             pid;
    char            *s;
    FILE* file_fd;
    int pnlen;
    int Rslt_pid = 0;
    char filename[30] = {0};

    pnlen = strlen(ProcName);

    /* Open the /proc directory. */
    dir = opendir("/proc");
    if (!dir)
    {
        printf("cannot open /proc\n");
        return -1;
    }

    /* Walk through the directory. */
    while ((d = readdir(dir)) != NULL) {
        char exe [PATH_MAX+1];
        char path[PATH_MAX+1];
        int len;
        int namelen;

        /* See if this is a process */
        if ((pid = atoi(d->d_name)) == 0)
            continue;

        snprintf(exe, sizeof(exe), "/proc/%s/exe", d->d_name);
        if ((len = readlink(exe, path, PATH_MAX)) < 0)
                continue;
        path[len] = '\0';

        /* Find ProcName */
        s = strrchr(path, '/');
        if(s == NULL)
            continue;
        s++;

        /* we don't need small name len */
        namelen = strlen(s);
        if(namelen < pnlen)
            continue;

        if(!strncmp(ProcName, s, pnlen)) {
            /* to avoid subname like search proc tao but proc taolinke matched */
            if(s[pnlen] == ' ' || s[pnlen] == '\0') {
                Rslt_pid = pid;
                sprintf(filename, "/proc/%d/oom_score_adj", pid);
                file_fd = fopen(filename, "w+");
                fwrite("-500", 1, 5, file_fd);  //set service_drm not killed
                fclose(file_fd);
                break;
            }
        }
    }

    closedir(dir);

    return Rslt_pid;
}

int main(int argc, char** argv)
{
    HITEST_InitResultFlag();
    setOomScoreAdjByName((char*)"service_drm");
    TEST_Entry(argc, argv, drmService_TESTList, sizeof(drmService_TESTList)/sizeof(drmService_TESTList[0]));

    return 0;
}
