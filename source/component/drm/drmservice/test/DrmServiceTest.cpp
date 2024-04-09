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

#include "HTTPUtil.h"
#include "PsshInitData.h"
#define TEST_INFO(fmt, args...) printf("%s(), %d: " fmt, __FUNCTION__,__LINE__, ## args)
#define TEST_FAIL    1
#define TEST_SUCCESS 0

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

namespace {

using android::String8;

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

HI_U8 verifyLicenseRequest(HI_DRM_KEY_REQUEST* keyRequest, const Vector<uint8_t>& drmHeader)
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

const String8 kPluginPath("/vendor/lib/mediadrm/libplayreadypkdrmplugin.so");

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
    Vector<uint8_t> sessionId1, sessionId2, sessionId3, sessionId4, sessionId5;
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(sessionId1));

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(sessionId2));

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(sessionId3));

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(sessionId4));

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(sessionId5));

    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId1));
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId2));
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId3));
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId4));
    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId5));

//    Vector<uint8_t> anotherSessionId;
//    EXPECT_NE(OK, mModularDrmInterfaceOtherDrm->openSession(anotherSessionId));

//    EXPECT_FALSE(sessionId.size() == anotherSessionId.size() &&
//             memcmp(sessionId.array(), anotherSessionId.array(), sessionId.size()) == 0);

//    EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(sessionId));
//    EXPECT_NE(OK, mModularDrmInterfaceOtherDrm->closeSession(anotherSessionId));

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
    }

    HI_U8 Setup()
    {
        mModularDrmInterfacePlayready = ModularDrmInterface::Create(kPlayReadyUuid);
        mModularDrmInterfaceOtherDrm = ModularDrmInterface::Create(kRandomUuid);

        EXPECT_EQ(OK, mModularDrmInterfacePlayready->openSession(playreadySessionId));
        EXPECT_NE(OK, mModularDrmInterfaceOtherDrm->openSession(anotherSessionId));
#if 1
        EXPECT_EQ(OK, drmDecryptPrepare(mModularDrmInterfacePlayready, playreadySessionId));

        mCryptoInterfacePlayready = CryptoInterface::Create(kPlayReadyUuid,
            reinterpret_cast<const char*>(playreadySessionId.array()), playreadySessionId.size());
        mCryptoInterfaceOtherDrm = CryptoInterface::Create(kRandomUuid,
            reinterpret_cast<const char*>(anotherSessionId.array()), anotherSessionId.size());
#endif

        return TEST_SUCCESS;
    }

    HI_U8 TearDown()
    {
        EXPECT_EQ(OK, mModularDrmInterfacePlayready->closeSession(playreadySessionId));
        EXPECT_NE(OK, mModularDrmInterfaceOtherDrm->closeSession(anotherSessionId));

        CryptoInterface::Destroy(mCryptoInterfacePlayready);
        CryptoInterface::Destroy(mCryptoInterfaceOtherDrm);
        ModularDrmInterface::Destroy(mModularDrmInterfacePlayready);
        ModularDrmInterface::Destroy(mModularDrmInterfaceOtherDrm);
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
/*
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
    */
    HI_S32 ret = mCryptoInterfacePlayready->decrypt(HI_FALSE,
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
#if 1
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
#endif

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
#if 1
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
#endif
    if (cryptoInterfaceTest.TearDown())
    {
        TEST_INFO("[5] TearDown failed.\n");
    }
    else
    {
        TEST_INFO("[5] TearDown success.\n");
    }
}

}  // namespace android

int main(int argc, char** argv)
{
    testModularInterface();

    testCryptoInterface();
    return 0;
}
