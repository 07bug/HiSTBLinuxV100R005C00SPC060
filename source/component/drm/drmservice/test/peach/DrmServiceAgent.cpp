
/* Copyright (c) Peach Fuzzer, LLC
 *
 * Example of a native Peach Agent using the Poco opensource C++ library.
 *
 * This example uses the REST Agent Channel.
 *
 * Authors:
 *   Michael Eddington <mike@dejavusecurity.com>
 *
 */

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/JSON/JSON.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Base64Decoder.h"
#include <iostream>

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <DrmAPI.h>
//#include <CryptoAPI.h>
#include <AString.h>
#include <DrmErrors.h>
#include <utils/String16.h>
#include <utils/String8.h>
#include <utils/Vector.h>
//#include <dlfcn.h>
#include <ModularDrmInterface.h>
#include <ModularDrmInterfaceImpl.h>
#include <CryptoInterface.h>
#include <CryptoInterfaceImpl.h>
#include "PlayReadyDrmPlugin.h"
#include "PlayReadySessionManager.h"
#include <dlfcn.h>
#include <utils/Logger.h>

//#include <common_log.h>
//#include "DrmSessionManager.h"
//#include "DrmService.h"
//#include <binder/ProcessState.h>
//#include <binder/IPCThreadState.h>
//#include <binder/IServiceManager.h>
//#include "DrmClient.h"
//#include "ICrypto.h"

using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using namespace Poco::JSON;
using namespace std;
int FaultNumber=0;

const String8 kPluginPath("/vendor/lib/mediadrm/libplayreadypkdrmplugin.so");
#define TEST_FAIL    1
#define TEST_SUCCESS 0
#define HI_LENGTH 500000
#define zero 0
#define sTime 500
//ModularDrmInterface *ModularDrmInfo = NULL;
//CryptoInterface *CryptoInfo = NULL;
//Vector < HI_U8 > sessionId;
ModularDrmInterface *ModularDrmInfo = NULL;

#define DEBUG_INFO_HEX(num)     printf("-----[%s, %d]%s= (0x%x)\n", __func__, __LINE__, #num, num);
#define DEBUG_INFO_DEC(num)     printf("-----[%s, %d]%s= (%d)\n", __func__, __LINE__, #num, num);
#define DEBUG_INFO_LLD(num)     printf("-----[%s, %d]%s= (%lld)\n", __func__, __LINE__, #num, num);
#define DEBUG_INFO_STR(str)     printf("-----[%s, %d]%s= (%s)\n", __func__, __LINE__, #str, str.c_str());
#define DEBUG_INFO_INFO(chars)  printf("-----[%s, %d]%s\n", __func__, __LINE__, chars);

#define CREATE_MODULARINTERFACE \
        sessionId.clear(); \
        ModularDrmInfo->openSession(sessionId);

#define CREATE_CRYPTOINTERFACE \
        CryptoInterface *CryptoInfo = NULL; \
        if (!sessionId.isEmpty()) \
            CryptoInfo = CryptoInterface::Create(kPlayReadyUuid,(HI_VOID*)(sessionId.editArray()),sessionId.size());

#define DESTROY_MODULARINTERFACE \
    ModularDrmInfo->closeSession(sessionId); \
    sessionId.clear();

#define DESTROY_CRYPTOINTERFACE \
    CryptoInterface::Destroy(CryptoInfo);

#define HIU8_TO_VECTOR(strTmp, cVector) \
        cVector.clear(); \
        if (!strTmp.size()) ; \
        else cVector.appendArray((const unsigned char *)strTmp.c_str(), strTmp.size()); \
        cVector.appendArray((const unsigned char*)"\0", 2);

#define STR_TO_STR8(str, str8) str8.setTo(str.c_str(), str.size())

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

Vector<uint8_t> getInitData(const String8& drmHeaderXml) {
    String16 drmHeader(drmHeaderXml);
    Vector<uint8_t> initData;
    initData.appendArray(reinterpret_cast<const uint8_t*>(drmHeader.string()),
                         drmHeader.size() * sizeof(drmHeader[0]));
    return initData;
}

inline String8 getString8FromUtf16String(const android::Vector<uint8_t>& utf16Array) {
    return String8(reinterpret_cast<const char16_t*>(utf16Array.array()),
                   utf16Array.size() / sizeof(char16_t));
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

static int s_intServicePid = 0;
//static MountServiceInterface* s_mount = NULL;

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

/* get pid by service name. And there is only one pid for a service. */
int get_pid_by_name( char* ProcName, int* foundpid)
{
        //DEBUG_INFO_INFO("get_pid_by_name");
        DIR             *dir;
        struct dirent   *d;
        int             pid, i;
        char            *s;
        int pnlen;
        FILE* file_fd;
        int Rslt_pid = 0;
        char filename[30] = {0};

        i = 0;
        *foundpid = 0;//foundpid[0] = 0;
        pnlen = strlen(ProcName);

        /* Open the /proc directory. */
        dir = opendir("/proc");
        if (!dir)
        {
                printf("cannot open /proc");
                return -1;
        }

        /* Walk through the directory. */
        while ((d = readdir(dir)) != NULL) {

                char exe [PATH_MAX+1];
                char path[PATH_MAX+1];
                int len;
                int namelen;

                /* See if this is a process */
                if ((pid = atoi(d->d_name)) == 0)       continue;

                snprintf(exe, sizeof(exe), "/proc/%s/exe", d->d_name);
                if ((len = readlink(exe, path, PATH_MAX)) < 0)
                        continue;
                path[len] = '\0';

                /* Find ProcName */
                s = strrchr(path, '/');
                if(s == NULL) continue;
                s++;

                /* we don't need small name len */
                namelen = strlen(s);
                if(namelen < pnlen)     continue;

                if(!strncmp(ProcName, s, pnlen)) {
                        /* to avoid subname like search proc tao but proc taolinke matched */
                        if(s[pnlen] == ' ' || s[pnlen] == '\0') {
                                if (!s_intServicePid)
                                {
                                    Rslt_pid = pid;
                                    printf("Enter set oom_score_adj\n");
                                    /*sprintf(filename, "/proc/%d/oom_score_adj", pid);
                                    file_fd = fopen(filename, "w+");
                                    fwrite("-500", 1, 5, file_fd);  //set service_drm not killed
                                    fclose(file_fd);*/
                                }
                                *foundpid = pid;//foundpid[i] = pid;
                        }
                }
        }

        //foundpid[i] = 0;
        closedir(dir);
        //DEBUG_INFO_INFO("get_pid_by_name");

        return  0;

}

static int Detected_fault(void)
{
    //在这里判断是否出现fault, 然后设置FaultNumber

    //FaultNumber=1;
    int intPid = 0;
    if (0 != get_pid_by_name("service_drm", &intPid))
    {
        DEBUG_INFO_INFO("get service_drm pid by name failed");
    }

    if (s_intServicePid != intPid)
    {
        FaultNumber = 1;
        DEBUG_INFO_INFO("pid not matched");

        /* set current pid as s_intServicePid */
        s_intServicePid = intPid;
    }
}

class PublisherRequestHandler: public HTTPRequestHandler
{
public:
    std::stringstream data1;
    PublisherRequestHandler()
    {
        _urlPrefix = "/Agent/Publisher/";
        _cmdCreatePublisher =    _urlPrefix + "CreatePublisher";
        _cmdSetIteration = _urlPrefix + "Set_Iteration";
        _cmdSetIsControlIteration = _urlPrefix + "Set_IsControlIteration";
        _cmdGetResult = _urlPrefix + "Get_Result";
        _cmdSetResult = _urlPrefix + "Set_Result";
        _cmdStart = _urlPrefix + "start";
        _cmdOpen = _urlPrefix + "open";
        _cmdClose = _urlPrefix + "close";
        _cmdAccept = _urlPrefix + "accept";
        _cmdCall = _urlPrefix + "call";
        _cmdSetProperty = _urlPrefix + "setProperty";
        _cmdGetProperty = _urlPrefix + "getProperty";
        _cmdOutput = _urlPrefix + "output";
        _cmdInput = _urlPrefix + "input";
        _cmdWantBytes = _urlPrefix + "WantBytes";
        _cmdReadBytes = _urlPrefix + "ReadBytes";
        _cmdReadAllBytes = _urlPrefix + "ReadAllBytes";
    }

    void handleRequest(HTTPServerRequest& request,
                       HTTPServerResponse& response)
    {
        Object::Ptr jsonObject;

        Application& app = Application::instance();
            /*app.logger().information("Request from "
                + request.clientAddress().toString() + " " + request.getURI());*/

        response.setChunkedTransferEncoding(true);
        response.setContentType("application/json");

        std::string uri = request.getURI();
        std::ostream& ostr = response.send();

        if(request.getMethod() == "POST")
        {
            std::string json( (std::istreambuf_iterator<char>( request.stream() )),
               (std::istreambuf_iterator<char>()) );

            //app.logger().information(json);

            // Parse the JSON and get the Results
            //
            Poco::Dynamic::Var parsedJson;
            Poco::Dynamic::Var parsedJsonResult;
            Parser parser;
            parsedJson = parser.parse(json);
            parsedJsonResult = parser.result();

            // Get the JSON Object
            //
            jsonObject = parsedJsonResult.extract<Object::Ptr>();
        }

        if(uri.compare(0, _cmdCreatePublisher.length(), _cmdCreatePublisher) == 0)
        {
            // A Peach instance is connecting to us. We should disconnect any
            // existing connections.

            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdSetIteration.length(), _cmdSetIteration) == 0)
        {
            string iteration = GetJsonValue(jsonObject, "iteration");

            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdSetIsControlIteration.length(), _cmdSetIsControlIteration) == 0)
        {
            string isControlIteration = GetJsonValue(jsonObject, "isControlIteration");

            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdGetResult.length(), _cmdGetResult) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdSetResult.length(), _cmdSetResult) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdStart.length(), _cmdStart) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdOpen.length(), _cmdOpen) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdClose.length(), _cmdClose) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdAccept.length(), _cmdAccept) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdCall.length(), _cmdCall) == 0)
        {
                // name of method from call action
                string method = GetJsonValue(jsonObject, "method");
                if(method== "call_ModularDrmInterfaceCreate")
                {
                    fuzzing_ModularDrmInterfaceCreate(jsonObject);
                }
                else if(method== "call_isCryptoSchemeSupported")
                {
                    fuzzing_isCryptoSchemeSupported(jsonObject);
                }
                else if (method == "call_getKeyRequest")
                {
                    fuzzing_getKeyRequest(jsonObject);
                }
                else if (method == "call_provideKeyResponse")
                {
                    fuzzing_provideKeyResponse(jsonObject);
                }
                else if (method == "call_removeKeys")
                {
                    fuzzing_removeKeys(jsonObject);
                }
                else if (method == "call_restoreKeys")
                {
                    fuzzing_restoreKeys(jsonObject);
                }
                else if (method == "call_queryKeyStatus")
                {
                    fuzzing_queryKeyStatus(jsonObject);
                }
                else if (method == "call_getProvisionRequest")
                {
                    fuzzing_getProvisionRequest(jsonObject);
                }
                else if (method == "call_provideProvisionResponse")
                {
                    fuzzing_provideProvisionResponse(jsonObject);
                }
                else if (method == "call_getSecureStop")
                {
                    fuzzing_getSecureStop(jsonObject);
                }
                else if (method == "call_releaseSecureStops")
                {
                    fuzzing_releaseSecureStops(jsonObject);
                }
                else if (method == "call_getPropertyString")
                {
                    fuzzing_getPropertyString(jsonObject);
                }
                else if (method == "call_getPropertyByteArray")
                {
                    fuzzing_getPropertyByteArray(jsonObject);
                }
                else if (method == "call_setPropertyString")
                {
                    fuzzing_setPropertyString(jsonObject);
                }
                else if (method == "call_setPropertyByteArray")
                {
                    fuzzing_setPropertyByteArray(jsonObject);
                }
                else if (method == "call_setCipherAlgorithm")
                {
                    fuzzing_setCipherAlgorithm(jsonObject);
                }
                else if (method == "call_setMacAlgorithm")
                {
                    fuzzing_setMacAlgorithm(jsonObject);
                }
                else if (method == "call_encrypt")
                {
                    fuzzing_encrypt(jsonObject);
                }
                else if (method == "call_decrypt")
                {
                    fuzzing_decrypt(jsonObject);
                }
                else if (method == "call_sign")
                {
                    fuzzing_sign(jsonObject);
                }
                else if (method == "call_verify")
                {
                    fuzzing_verify(jsonObject);
                }
                else if (method == "call_signRSA")
                {
                    fuzzing_signRSA(jsonObject);
                }
                else if (method == "call_setListener")
                {
                    fuzzing_setListener(jsonObject);
                }
                else if (method == "call_CryptoInterfaceCreate")
                {
                    fuzzing_CryptoInterfaceCreate(jsonObject);
                }
                else if (method == "call_Crypto_isCryptoSchemeSupported")
                {
                    fuzzing_Crypto_isCryptoSchemeSupported(jsonObject);
                }
                else if (method == "call_Crypto_decrypt")
                {
                    fuzzing_Crypto_decrypt(jsonObject);
                }
                else
                {
                    cout << "no function matching \n";
                }
                Detected_fault();

                ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdSetProperty.length(), _cmdSetProperty) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdGetProperty.length(), _cmdGetProperty) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdOutput.length(), _cmdOutput) == 0)
        {
            istringstream ifs(GetJsonValue(jsonObject, "data"));
            Poco::Base64Decoder b64in(ifs);
            std::stringstream data;

            copy(istreambuf_iterator<char>(b64in),
                istreambuf_iterator<char>(),
                ostreambuf_iterator<char>(data));

            // data now contains the raw binary data

            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdInput.length(), _cmdInput) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdWantBytes.length(), _cmdWantBytes) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdReadBytes.length(), _cmdReadBytes) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else if(uri.compare(0, _cmdReadAllBytes.length(), _cmdReadAllBytes) == 0)
        {
            ostr << "{ \"error\":\"false\", \"errorString\":null }";
        }
        else
        {
            ostr << "{\"Error\":\"Error, unknown command.\"}";
        }
    }

    int get_data_string(Object::Ptr jsonObject, const char* keyword, string& outString)
    {
        std::stringstream data1;
        istringstream ifs1(GetdataValue(jsonObject, keyword));
        Poco::Base64Decoder b64in1(ifs1);

        copy(istreambuf_iterator<char>(b64in1),
             istreambuf_iterator<char>(),
             ostreambuf_iterator<char>(data1));

        outString =data1.str();
        HI_LOGD("get_data_string---%s",outString.c_str());
        //cout << "print_string  =" << print_string << ".\n";

        return 0;
    }

    int str2arr_16(string pStr, HI_U8 uuid[32])
    {
        int pStrSize = pStr.size();

        if (pStrSize > 16){
            memcpy(uuid, pStr.c_str(), 16);
        }
        else if (pStrSize > 0){
            memcpy(uuid, pStr.c_str(), pStrSize);
        }
        else{
            HI_LOGE("Input error!");
            return -1;
        }

        return 0;
    }

    //ModularDrmInterface
    int fuzzing_ModularDrmInterfaceCreate(Object::Ptr jsonObject)
    {
        ModularDrmInterface *TestDrmInfo = NULL;
        HI_U8 uuid[32] = {0};
        string strTmp_puuid = "\0";

        get_data_string(jsonObject, "func_str_ModularDrmInterfaceCreate_uuidArr", strTmp_puuid);
        if (strTmp_puuid.c_str())
            str2arr_16(strTmp_puuid, uuid);
        TestDrmInfo = ModularDrmInterface::Create(uuid);
        if (TestDrmInfo)
            ModularDrmInterface::Destroy(TestDrmInfo);

        return 0;
    }

    int fuzzing_isCryptoSchemeSupported(Object::Ptr jsonObject)
    {
        string strTmp_puuid = "\0";
        string strTmp_mimeType = "\0";
        char* mimeType = NULL;
        HI_U8 uuid[32] = {0};
        Vector < HI_U8 > sessionId;
        int CountSize = 0;

        get_data_string(jsonObject, "func_str_isCryptoSchemeSupported_uuidArr", strTmp_puuid);
        if (strTmp_puuid.c_str())
            str2arr_16(strTmp_puuid.c_str(), uuid);

        get_data_string(jsonObject, "func_str_isCryptoSchemeSupported_mimeType", strTmp_mimeType);

        CountSize = strTmp_mimeType.size();
        if (CountSize)
        {
            if (mimeType = (char *)malloc(CountSize))
            {
                memset(mimeType, 0x00, CountSize);
                memcpy(mimeType, strTmp_mimeType.c_str(), CountSize);
            }
            else
            {
                HI_LOGE("[%s] : malloc fail", __func__);
            }
        }
        else
        {
            HI_LOGE("[%s] : strTmp_mimeType.c_str() is NULL", __func__);
        }

        ModularDrmInfo->isCryptoSchemeSupported(uuid, (const char*)mimeType);

        if (mimeType)
        {
            free(mimeType);
            mimeType = NULL;
        }

        return 0;
    }

    int fuzzing_getKeyRequest(Object::Ptr jsonObject)
    {
        string strTmp_scope = "\0";
        string strTmp_initData = "\0";
        string strTmp_mimeType = "\0";
        string strTmp_keyType = "\0";
        string strTmp_optionalParameters = "\0";
        string strTmp_optionalParameters2 = "\0";
        string strTmp_optionalParameters3 = "\0";
        string strTmp_optionalParameters4 = "\0";
        string strTmp = "\0";
        KeyedVector<String8, String8> optionalParameters;
        char* mimeType = NULL;
        HI_U8 *scope_u8 = NULL;
        Vector<HI_U8> scope;
        Vector<HI_U8> initData;
        String8 key_str("");
        String8 val_str("");
        String8 temp_val("ABCDabcd1234ABCDabcd1234ABCDabcd1234ABCDabcd1234ABCDabcd1234ABCDabcd1234ABCDabcd1234ABCDabcd1234");
        int CountSize = 0;
        int PairNum = 0;
        HI_DRM_KEY_REQUEST pKeyRequest;
        Vector < HI_U8 > sessionId;
        HI_LOGD("[%s] : Enter", __func__);
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_getKeyRequest_scope", strTmp_scope);
        HIU8_TO_VECTOR(strTmp_scope, scope);

        get_data_string(jsonObject, "func_str_getKeyRequest_initData", strTmp_initData);
        HIU8_TO_VECTOR(strTmp_initData, initData);

        get_data_string(jsonObject, "func_str_getKeyRequest_mimeType", strTmp_mimeType);
        CountSize = strTmp_mimeType.size();
        if (CountSize)
        {
            if (mimeType = (char *)malloc(CountSize))
            {
                memset(mimeType, 0x00, CountSize);
                memcpy(mimeType, strTmp_mimeType.c_str(), CountSize);
            }
            else
            {
                HI_LOGE("[%s] : malloc fail", __func__);
            }
        }
        else
        {
            HI_LOGE("[%s] : strTmp_mimeType.c_str() is NULL", __func__);
        }

        get_data_string(jsonObject, "func_str_getKeyRequest_keyType", strTmp_keyType);
        HI_DRM_KEY_TYPE keyType = *((HI_DRM_KEY_TYPE *)strTmp_keyType.c_str());

        get_data_string(jsonObject, "func_str_getKeyRequest_optionalParameters", strTmp_optionalParameters);
        STR_TO_STR8(strTmp_optionalParameters, key_str);
        get_data_string(jsonObject, "func_str_getKeyRequest_optionalParameters2", strTmp_optionalParameters2);
        STR_TO_STR8(strTmp_optionalParameters2, val_str);
        optionalParameters.add(key_str, val_str);
        key_str.clear();
        val_str.clear();

        get_data_string(jsonObject, "func_str_getKeyRequest_optionalParameters3", strTmp);
        STR_TO_STR8(strTmp, key_str);
        get_data_string(jsonObject, "func_str_getKeyRequest_optionalParameters4", strTmp);
        STR_TO_STR8(strTmp, val_str);
        optionalParameters.add(key_str, val_str);

        strTmp.clear();
        get_data_string(jsonObject, "func_enum_getKeyRequest_num", strTmp);
        PairNum = *((int *)strTmp.c_str());
        if (PairNum)
        {
            for (int i = 0; i < PairNum; i++)
            {
                optionalParameters.add(temp_val, temp_val);
            }
        }

        ModularDrmInfo->getKeyRequest(
                                                scope,
                                                initData,
                                                (const char*)mimeType,
                                                keyType,
                                                optionalParameters,
                                                &pKeyRequest);//需要打印具体内容

        if (mimeType)
        {
            free(mimeType);
            mimeType = NULL;
        }

        DESTROY_MODULARINTERFACE
            HI_LOGD("[%s] : Leave", __func__);
        return 0;
    }

    int fuzzing_provideKeyResponse(Object::Ptr jsonObject)
    {
        string strTmp_scope = "\0";
        string strTmp_response = "\0";
        Vector<HI_U8> scope;
        Vector<HI_U8> response;
        Vector<HI_U8> keySetId;
        Vector < HI_U8 > sessionId;
        HI_LOGD("[%s] : Enter", __func__);
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_provideKeyResponse_scope", strTmp_scope);
        HIU8_TO_VECTOR(strTmp_scope, scope);

        get_data_string(jsonObject, "func_str_provideKeyResponse_response", strTmp_response);
        HIU8_TO_VECTOR(strTmp_response, response);

        //DEBUG_INFO_DEC(
        ModularDrmInfo->provideKeyResponse(scope, response, keySetId);//);
        DESTROY_MODULARINTERFACE
            HI_LOGD("[%s] : Leave", __func__);
        return 0;
    }

    int fuzzing_removeKeys(Object::Ptr jsonObject)
    {
        string strTmp_scope = "\0";
        Vector < HI_U8 > scope;
        Vector < HI_U8 > sessionId;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_removeKeys_scope", strTmp_scope);
        HIU8_TO_VECTOR(strTmp_scope, scope);

        ModularDrmInfo->removeKeys(scope);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_restoreKeys(Object::Ptr jsonObject)
    {
        string strTmp_scope = "\0";
        string strTmp_keySetId = "\0";
        Vector<HI_U8> scope;
        Vector<HI_U8> keySetId;
        Vector < HI_U8 > sessionId;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_restoreKeys_scope", strTmp_scope);
        HIU8_TO_VECTOR(strTmp_scope, scope);

        get_data_string(jsonObject, "func_str_restoreKeys_keySetId", strTmp_keySetId);
        HIU8_TO_VECTOR(strTmp_keySetId, keySetId);

        ModularDrmInfo->restoreKeys(scope, keySetId);
        ModularDrmInfo->removeKeys(sessionId);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_queryKeyStatus(Object::Ptr jsonObject)
    {
        string strTmp_scope = "\0";
        Vector<HI_U8> scope;
        Vector < HI_U8 > sessionId;
        KeyedVector<String8, String8> infoMap;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_queryKeyStatus_scope", strTmp_scope);
        HIU8_TO_VECTOR(strTmp_scope, scope);

        ModularDrmInfo->queryKeyStatus(scope, infoMap);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_getProvisionRequest(Object::Ptr jsonObject)
    {
        string strTmp_certType = "\0";
        string strTmp_certAuthority = "\0";
        String8 certType("");
        String8 certAuthority("");
        Vector < HI_U8 > sessionId;
        HI_DRM_PROVITION_REQUEST request;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_getProvisionRequest_certType", strTmp_certType);
        STR_TO_STR8(strTmp_certType, certType);

        get_data_string(jsonObject, "func_str_getProvisionRequest_certAuthority", strTmp_certAuthority);
        STR_TO_STR8(strTmp_certAuthority, certAuthority);

        ModularDrmInfo->getProvisionRequest(certType, certAuthority, &request);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_provideProvisionResponse(Object::Ptr jsonObject)
    {
        string strTmp_response = "\0";
        Vector<HI_U8> response;
        Vector<HI_U8> certificate;
        Vector<HI_U8> wrappedKey;
        Vector < HI_U8 > sessionId;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_provideProvisionResponse_response", strTmp_response);
        HIU8_TO_VECTOR(strTmp_response, response);

        ModularDrmInfo->provideProvisionResponse(response, certificate, wrappedKey);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_getSecureStop(Object::Ptr jsonObject)
    {
        string strTmp_ssid = "\0";
        Vector < HI_U8 > sessionId;
        Vector<HI_U8> ssid;
        Vector<HI_U8> secureStop;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_getSecureStop_ssid", strTmp_ssid);
        HIU8_TO_VECTOR(strTmp_ssid, ssid);

        ModularDrmInfo->getSecureStop(ssid, secureStop);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_releaseSecureStops(Object::Ptr jsonObject)
    {
        string strTmp_ssRelease = "\0";
        Vector < HI_U8 > sessionId;
        Vector<HI_U8> ssRelease;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_releaseSecureStops_ssRelease", strTmp_ssRelease);
        HIU8_TO_VECTOR(strTmp_ssRelease, ssRelease);

        ModularDrmInfo->releaseSecureStops(ssRelease);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_getPropertyString(Object::Ptr jsonObject)
    {
        string strTmp_name = "\0";
        Vector < HI_U8 > sessionId;
        String8 name;
        String8 value;
        CREATE_MODULARINTERFACE
        ModularDrmInfo->setPropertyString(String8("securityLevel"), String8("L1"));

        get_data_string(jsonObject, "func_str_getPropertyString_name", strTmp_name);
        STR_TO_STR8(strTmp_name, name);

        ModularDrmInfo->getPropertyString(name, value);
        DESTROY_MODULARINTERFACE
        return 0;
    }

    int fuzzing_getPropertyByteArray(Object::Ptr jsonObject)
    {
        string strTmp_name = "\0";
        Vector < HI_U8 > sessionId;
        String8 name;
        Vector<HI_U8> value;
        Vector<HI_U8> s_value;
        CREATE_MODULARINTERFACE
        s_value.appendArray((HI_U8 *)"L1", 2);
        ModularDrmInfo->setPropertyByteArray(String8("securityLevel"), s_value);

        get_data_string(jsonObject, "func_str_getPropertyByteArray_name", strTmp_name);
        STR_TO_STR8(strTmp_name, name);

        ModularDrmInfo->getPropertyByteArray(name, value);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_setPropertyString(Object::Ptr jsonObject)
    {
        string strTmp_name = "\0";
        string strTmp_value = "\0";
        Vector < HI_U8 > sessionId;
        String8 name;
        String8 value;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_setPropertyString_name", strTmp_name);
        STR_TO_STR8(strTmp_name, name);

        get_data_string(jsonObject, "func_str_setPropertyString_value", strTmp_value);
        STR_TO_STR8(strTmp_value, value);

        ModularDrmInfo->setPropertyString(name, value);
        DESTROY_MODULARINTERFACE
        return 0;
    }

    int fuzzing_setPropertyByteArray(Object::Ptr jsonObject)
    {
        string strTmp_name = "\0";
        string strTmp_value = "\0";
        Vector < HI_U8 > sessionId;
        String8 name;
        Vector < HI_U8 > value;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_setPropertyByteArray_name", strTmp_name);
        STR_TO_STR8(strTmp_name, name);

        get_data_string(jsonObject, "func_str_setPropertyByteArray_value", strTmp_value);
        HIU8_TO_VECTOR(strTmp_value, value);

        ModularDrmInfo->setPropertyByteArray(name, value);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_setCipherAlgorithm(Object::Ptr jsonObject)
    {
        string strTmp_algorithm = "\0";
        string strTmp_name = "\0";
        Vector < HI_U8 > sessionId;
        String8 algorithm;
        Vector < HI_U8 > name;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_setCipherAlgorithm_algorithm", strTmp_algorithm);
        STR_TO_STR8(strTmp_algorithm, algorithm);

        get_data_string(jsonObject, "func_str_setCipherAlgorithm_name", strTmp_name);
        HIU8_TO_VECTOR(strTmp_name, name);

        ModularDrmInfo->setCipherAlgorithm(name, algorithm);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_setMacAlgorithm(Object::Ptr jsonObject)
    {
        string strTmp_algorithm = "\0";
        string strTmp_name = "\0";
        Vector < HI_U8 > sessionId;
        String8 algorithm;
        Vector < HI_U8 > name;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_setMacAlgorithm_algorithm", strTmp_algorithm);
        STR_TO_STR8(strTmp_algorithm, algorithm);

        get_data_string(jsonObject, "func_str_setMacAlgorithm_name", strTmp_name);
        HIU8_TO_VECTOR(strTmp_name, name);

        ModularDrmInfo->setMacAlgorithm(name, algorithm);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_encrypt(Object::Ptr jsonObject)
    {
        string strTmp_sessionId1 = "\0";
        string strTmp_keyId = "\0";
        string strTmp_input = "\0";
        string strTmp_iv = "\0";
        Vector < HI_U8 > sessionId;
        Vector < HI_U8 > sessionId1;
        Vector < HI_U8 > keyId;
        Vector < HI_U8 > input;
        Vector < HI_U8 > iv;
        Vector < HI_U8 > output;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_encrypt_sessionId1", strTmp_sessionId1);
        HIU8_TO_VECTOR(strTmp_sessionId1, sessionId1);

        get_data_string(jsonObject, "func_str_encrypt_keyId", strTmp_keyId);
        HIU8_TO_VECTOR(strTmp_keyId, keyId);

        get_data_string(jsonObject, "func_str_encrypt_input", strTmp_input);
        HIU8_TO_VECTOR(strTmp_input, input);

        get_data_string(jsonObject, "func_str_encrypt_iv", strTmp_iv);
        HIU8_TO_VECTOR(strTmp_iv, iv);

        ModularDrmInfo->encrypt( sessionId1,
                            keyId,
                            input,
                            iv,
                            output);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_decrypt(Object::Ptr jsonObject)
    {
        string strTmp_sessionId1 = "\0";
        string strTmp_keyId = "\0";
        string strTmp_input = "\0";
        string strTmp_iv = "\0";
        Vector < HI_U8 > sessionId;
        Vector < HI_U8 > sessionId1;
        Vector < HI_U8 > keyId;
        Vector < HI_U8 > input;
        Vector < HI_U8 > iv;
        Vector < HI_U8 > output;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_decrypt_sessionId1", strTmp_sessionId1);
        HIU8_TO_VECTOR(strTmp_sessionId1, sessionId1);

        get_data_string(jsonObject, "func_str_decrypt_keyId", strTmp_keyId);
        HIU8_TO_VECTOR(strTmp_keyId, keyId);

        get_data_string(jsonObject, "func_str_decrypt_input", strTmp_input);
        HIU8_TO_VECTOR(strTmp_input, input);

        get_data_string(jsonObject, "func_str_decrypt_iv", strTmp_iv);
        HIU8_TO_VECTOR(strTmp_iv, iv);

        ModularDrmInfo->decrypt( sessionId1,
                            keyId,
                            input,
                            iv,
                            output);
        DESTROY_MODULARINTERFACE
        return 0;
    }

    int fuzzing_sign(Object::Ptr jsonObject)
    {
        string strTmp_sessionId1 = "\0";
        string strTmp_keyId = "\0";
        string strTmp_message = "\0";
        Vector < HI_U8 > sessionId1;
        Vector < HI_U8 > sessionId;
        Vector < HI_U8 > keyId;
        Vector < HI_U8 > message;
        Vector < HI_U8 > signature;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_sign_sessionId1", strTmp_sessionId1);
        HIU8_TO_VECTOR(strTmp_sessionId1, sessionId1);

        get_data_string(jsonObject, "func_str_sign_keyId", strTmp_keyId);
        HIU8_TO_VECTOR(strTmp_keyId, keyId);

        get_data_string(jsonObject, "func_str_sign_message", strTmp_message);
        //DEBUG_INFO_STR(strTmp_message);
        //DEBUG_INFO_DEC(strTmp_message.size());
        HIU8_TO_VECTOR(strTmp_message, message);

        ModularDrmInfo->sign( sessionId1,
                            keyId,
                            message,
                            signature);
        DESTROY_MODULARINTERFACE
        return 0;
    }

    int fuzzing_verify(Object::Ptr jsonObject)
    {
        string strTmp_sessionId1 = "\0";
        string strTmp_keyId = "\0";
        string strTmp_message = "\0";
        string strTmp_signature = "\0";
        Vector < HI_U8 > sessionId;
        Vector < HI_U8 > sessionId1;
        Vector < HI_U8 > keyId;
        Vector < HI_U8 > message;
        Vector < HI_U8 > signature;
        HI_BOOL match = (HI_BOOL)0;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_verify_sessionId1", strTmp_sessionId1);
        HIU8_TO_VECTOR(strTmp_sessionId1, sessionId1);

        get_data_string(jsonObject, "func_str_verify_keyId", strTmp_keyId);
        HIU8_TO_VECTOR(strTmp_keyId, keyId);

        get_data_string(jsonObject, "func_str_verify_message", strTmp_message);
        HIU8_TO_VECTOR(strTmp_message, message);

        get_data_string(jsonObject, "func_str_verify_signature", strTmp_signature);
        HIU8_TO_VECTOR(strTmp_signature, signature);

        ModularDrmInfo->verify( sessionId1,
                            keyId,
                            message,
                            signature,
                            match);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_signRSA(Object::Ptr jsonObject)
    {
        string strTmp_sessionId1 = "\0";
        string strTmp_algorithm = "\0";
        string strTmp_message = "\0";
        string strTmp_wrappedKey = "\0";
        Vector < HI_U8 > sessionId;
        Vector < HI_U8 > sessionId1;
        String8 algorithm;
        Vector < HI_U8 > message;
        Vector < HI_U8 > wrappedKey;
        Vector<HI_U8> signature;
        HI_BOOL match = (HI_BOOL)0;
        CREATE_MODULARINTERFACE

        get_data_string(jsonObject, "func_str_signRSA_sessionId1", strTmp_sessionId1);
        HIU8_TO_VECTOR(strTmp_sessionId1, sessionId1);

        get_data_string(jsonObject, "func_str_signRSA_algorithm", strTmp_algorithm);
        STR_TO_STR8(strTmp_algorithm, algorithm);

        get_data_string(jsonObject, "func_str_signRSA_message", strTmp_message);
        HIU8_TO_VECTOR(strTmp_message, message);

        get_data_string(jsonObject, "func_str_signRSA_wrappedKey", strTmp_wrappedKey);
        HIU8_TO_VECTOR(strTmp_wrappedKey, wrappedKey);

        ModularDrmInfo->signRSA( sessionId1,
                            algorithm,
                            message,
                            wrappedKey,
                            signature);
        DESTROY_MODULARINTERFACE

        return 0;
    }

    //数据模型未构建
    int fuzzing_setListener(Object::Ptr jsonObject)
    {
        Vector < HI_U8 > sessionId;
        CREATE_MODULARINTERFACE

        DrmListener *listener = NULL;

        ModularDrmInfo->setListener(listener);

        DESTROY_MODULARINTERFACE
        return 0;
    }

    //CryptoInterface
    int fuzzing_CryptoInterfaceCreate(Object::Ptr jsonObject)
    {
        CryptoInterface *TesyCryptoInfo = NULL;
        HI_U8 uuid[32] = {0};
        char * initData = NULL;
        HI_S32 initSize = 0;
        string strTmp_puuid = "\0";
        string strTmp_initData = "\0";

        get_data_string(jsonObject, "func_str_CryptoInterfaceCreate_uuidArr", strTmp_puuid);

         int pStrSize =  strTmp_puuid.size();
        if (pStrSize > 16){
            memcpy(uuid, strTmp_puuid.c_str(), 16);
        }
        else if (pStrSize > 0){
            memcpy(uuid, strTmp_puuid.c_str(), pStrSize);
        }
        else{
            HI_LOGE("Input error!");
            return -1;
        }
 
        get_data_string(jsonObject, "func_str_CryptoInterfaceCreate_initData", strTmp_initData);
        initSize = strTmp_initData.size();
        if (initSize)
        {
            if (initData = (char *)malloc(initSize + 1))
            {
                memset(initData, 0x00, initSize);
                memcpy(initData, strTmp_initData.c_str(), initSize);
                initData[initSize] = '\0';
            }
            else
            {
                HI_LOGE("[%s] : malloc fail", __func__);
            }
        }
 
        TesyCryptoInfo = CryptoInterface::Create(uuid, initData, initSize);
        if (TesyCryptoInfo)
            CryptoInterface::Destroy(TesyCryptoInfo);

        if (initData)
        {
            free(initData);
            initData = NULL;
        }

        return 0;
    }

    int fuzzing_Crypto_isCryptoSchemeSupported(Object::Ptr jsonObject)
    {
        string strTmp_puuid = "\0";
        string strTmp_mimeType = "\0";
        const char * puuid = NULL;
        HI_U8 uuid[32] = {0};
        Vector < HI_U8 > sessionId;
        CREATE_MODULARINTERFACE
        CREATE_CRYPTOINTERFACE

        get_data_string(jsonObject, "func_str_Crypto_isCryptoSchemeSupported_uuidArr", strTmp_puuid);
        if (strTmp_puuid.c_str())
            str2arr_16(strTmp_puuid.c_str(), uuid);

        //DEBUG_INFO_INFO(uuid);
        if (CryptoInfo){
            CryptoInfo->isCryptoSchemeSupported(uuid);
        }

        DESTROY_CRYPTOINTERFACE
        DESTROY_MODULARINTERFACE

        return 0;
    }

    int fuzzing_Crypto_decrypt(Object::Ptr jsonObject)
    {
        string strTmp_secure = "\0";
        string strTmp_key = "\0";
        string strTmp_iv = "\0";
        string strTmp_mode = "\0";
        string strTmp_pSrc = "\0";
        string strTmp_clear = "\0";
        string strTmp_encypto = "\0";
        string strTmp_numSubSamples = "\0";
        Vector < HI_U8 > sessionId;
        Vector<HI_U8> decryptedDataBuffer;
        HI_U8 key[32] = {0};
        HI_U8 iv[32] = {0};
        HI_U8 *pSrc = NULL;
        //HI_U8 pDst[10] = {0};
        HI_VOID* pDst = decryptedDataBuffer.editArray();
        HI_DRM_SUBSAMPLES subSamples;
        HI_S32 numSubSamples;
        HI_S32 s32srcSize = 0;
        //HI_VOID* pSrc;
        String8 errorDetailMsg;
        CREATE_MODULARINTERFACE
        CREATE_CRYPTOINTERFACE

        get_data_string(jsonObject, "func_num_Crypto_decrypt_secure", strTmp_secure);
        HI_BOOL secure = *((HI_BOOL *)strTmp_secure.c_str());
        //printf("secure = %d\n", secure);

        get_data_string(jsonObject, "func_str_Crypto_decrypt_key", strTmp_key);
        if (strTmp_key.c_str())
            str2arr_16(strTmp_key.c_str(), key);

        get_data_string(jsonObject, "func_str_Crypto_decrypt_iv", strTmp_iv);
        if (strTmp_iv.c_str())
            str2arr_16(strTmp_iv.c_str(), iv);

        get_data_string(jsonObject, "func_enum_Crypto_decrypt_mode", strTmp_mode);
        HI_CRYPTO_MODE mode = *((HI_CRYPTO_MODE *)strTmp_mode.c_str());

        get_data_string(jsonObject, "func_str_Crypto_decrypt_pSrc", strTmp_pSrc);
        s32srcSize = strTmp_pSrc.size();
        if (s32srcSize)
        {
            if (pSrc = (HI_U8 *)malloc(s32srcSize))
            {
                memset(pSrc, 0x00, s32srcSize);
                memcpy(pSrc, strTmp_pSrc.c_str(), s32srcSize);
            }
            else
            {
                HI_LOGE("[%s] : malloc fail", __func__);
            }
        }
        else
        {
            HI_LOGE("[%s] : strTmp_pSrc.c_str() is NULL", __func__);
        }

        get_data_string(jsonObject, "func_num_Crypto_decrypt_clear", strTmp_clear);
        subSamples.u32numBytesOfClearData = *((HI_U32 *)strTmp_clear.c_str());
        //printf("subSamples.u32numBytesOfClearData = %d\n", subSamples.u32numBytesOfClearData);
        get_data_string(jsonObject, "func_num_Crypto_decrypt_encypto", strTmp_encypto);
        subSamples.u32numBytesOfEncryptedData = *((HI_U32 *)strTmp_encypto.c_str());
        //printf("subSamples.u32numBytesOfEncryptedData = %d\n", subSamples.u32numBytesOfEncryptedData);

        get_data_string(jsonObject, "func_num_Crypto_decrypt_numSubSamples", strTmp_numSubSamples);
        numSubSamples = *((HI_S32 *)strTmp_numSubSamples.c_str());
        //printf("numSubSamples = %d\n", numSubSamples);
        if (CryptoInfo){
            CryptoInfo->decrypt( secure,
                    key,    //16
                    iv,     //16
                    mode,
                    pSrc,
                    s32srcSize,
                    &subSamples,
                    numSubSamples,
                    pDst,
                    errorDetailMsg);
        }

        if (pSrc)
        {
            free(pSrc);
            pSrc = NULL;
        }

        DESTROY_CRYPTOINTERFACE
        DESTROY_MODULARINTERFACE

        return 0;
    }

    string GetdataValue(Object::Ptr jsonObject, std::string aszKey)
    {
        vector<stringstream> args;

        Array::Ptr jsonArgs = jsonObject->getArray("args");

        for(int cnt = 0; cnt < jsonArgs->size(); ++cnt)
        {
            Object::Ptr arg = (jsonArgs->get(cnt)).extract<Object::Ptr>();

            // Name of argument/parameter
            std::string name = GetJsonValue(arg, "name");
            // Type of parameter
            string type = GetJsonValue(arg, "type");
            // Binary data from Peach

            istringstream ifs(GetJsonValue(arg, "data"));
            Poco::Base64Decoder b64in(ifs);

            copy(istreambuf_iterator<char>(b64in),
                istreambuf_iterator<char>(),
                ostreambuf_iterator<char>(data1));

            if(name ==  aszKey)
            {
                return GetJsonValue(arg, "data");
            }

        }

        return "None";
    }

    // Helper method for getting std::string value back
    string GetJsonValue(Object::Ptr aoJsonObject, const char *aszKey)
    {
        Poco::Dynamic::Var loVariable;
        string lsReturn;
        string lsKey(aszKey);

        // Get the member Variable
        //
        loVariable = aoJsonObject->get(lsKey);

        // Get the Value from the Variable
        //
        lsReturn = loVariable.convert<std::string>();

        return lsReturn;
    }

private:
    string _urlPrefix;
    string _cmdCreatePublisher;
    string _cmdSetIteration;
    string _cmdSetIsControlIteration;
    string _cmdGetResult;
    string _cmdSetResult;
    string _cmdStart;
    string _cmdOpen;
    string _cmdClose;
    string _cmdAccept;
    string _cmdCall;
    string _cmdSetProperty;
    string _cmdGetProperty;
    string _cmdOutput;
    string _cmdInput;
    string _cmdWantBytes;
    string _cmdReadBytes;
    string _cmdReadAllBytes;
};

class PeachRequestHandler: public HTTPRequestHandler
{
public:
    PeachRequestHandler()
    {
        _urlPrefix = "/Agent/";
        _cmdAgentConnect =    _urlPrefix + "AgentConnect";
        _cmdAgentDisconnect = _urlPrefix + "AgentDisconnect";
        _cmdCreatePublisher = _urlPrefix + "CreatePublisher";
        _cmdStartMonitor = _urlPrefix + "StartMonitor";
        _cmdStopMonitor = _urlPrefix + "StopMonitor";
        _cmdStopAllMonitors = _urlPrefix + "StopAllMonitors";
        _cmdSessionStarting = _urlPrefix + "SessionStarting";
        _cmdSessionFinished = _urlPrefix + "SessionFinished";
        _cmdIterationStarting = _urlPrefix + "IterationStarting";
        _cmdIterationFinished = _urlPrefix + "IterationFinished";
        _cmdDetectedFault = _urlPrefix + "DetectedFault";
        _cmdGetMonitorData = _urlPrefix + "GetMonitorData";
        _cmdMustStop = _urlPrefix + "MustStop";
    }

    void handleRequest(HTTPServerRequest& request,
                       HTTPServerResponse& response)
    {
        Object::Ptr jsonObject;

        Application& app = Application::instance();

        /*app.logger().information(string("Request from ")
            + request.clientAddress().toString() + " " + request.getURI());*/

        response.setChunkedTransferEncoding(true);
        response.setContentType("application/json");

        std::string uri = request.getURI();
        std::ostream& ostr = response.send();

        if(request.getMethod() == "POST")
        {
            std::string json( (std::istreambuf_iterator<char>( request.stream() )),
               (std::istreambuf_iterator<char>()) );

            //app.logger().information(json);

            // Parse the JSON and get the Results
            //
            Poco::Dynamic::Var parsedJson;
            Poco::Dynamic::Var parsedJsonResult;
            Parser parser;
            parsedJson = parser.parse(json);
            parsedJsonResult = parser.result();

            // Get the JSON Object
            //
            jsonObject = parsedJsonResult.extract<Object::Ptr>();
        }

        if(uri.compare(0, _cmdAgentConnect.length(), _cmdAgentConnect) == 0)
        {
            // A Peach instance is connecting to us. We should disconnect any
            // existing connections.

            ostr << "{ \"Status\":\"true\" }";
        }
        else if(uri.compare(0, _cmdAgentDisconnect.length(), _cmdAgentDisconnect) == 0)
        {
            // Peach instance is disconnecting from us

            ostr << "{ \"Status\":\"true\" }";
        }
        else if(uri.compare(0, _cmdCreatePublisher.length(), _cmdCreatePublisher) == 0)
        {
            // Indicates an I/O instance should be created to send/receive data via
            // our agent instance.

            ostr << "{ \"Status\":\"true\" }";
        }
        else if(uri.compare(0, _cmdStartMonitor.length(), _cmdStartMonitor) == 0)
        {
            // Start a monitor

            HTMLForm form(request);

            string name = form["name"];
            string cls = form["cls"];

            //app.logger().information(name + ":" + cls);

            /* Example of arguments json:

            {
                "args":{
                    "CommandLine":"mspaint.exe fuzzed.png",
                    "WinDbgPath":"C:\\Program Files (x86)\\Debugging Tools for Windows (x86)",
                    "StartOnCall":"ScoobySnacks"
                    }
            }

            */

            // Get arguments from json
            std::vector<std::string> argumentNames;
            Object::Ptr jsonArgsObject = jsonObject->getObject("args");
            jsonArgsObject->getNames(argumentNames);

            for(std::vector<std::string>::iterator it = argumentNames.begin(); it != argumentNames.end(); ++it)
            {
                std::string argName = *it;
                std::string argValue = GetJsonValue(jsonArgsObject, argName.c_str());

                // TODO - Use argument!
                //app.logger().information(argName + ": " + argValue);
            }

            ostr << "{ \"Status\":\"true\" }";
        }
        else if(uri.compare(0, _cmdStopMonitor.length(), _cmdStopMonitor) == 0)
        {
            // stop a started monitor

            ostr << "{ \"Status\":\"true\" }";
        }
        else if(uri.compare(0, _cmdStopAllMonitors.length(), _cmdStopAllMonitors) == 0)
        {
            // stop all started monitors

            ostr << "{ \"Status\":\"true\" }";
        }
        else if(uri.compare(0, _cmdSessionStarting.length(), _cmdSessionStarting) == 0)
        {
            // starting our fuzzing run

            ostr << "{ \"Status\":\"true\" }";
        }
        else if(uri.compare(0, _cmdSessionFinished.length(), _cmdSessionFinished) == 0)
        {
            // finished our fuzzing run

            ostr << "{ \"Status\":\"true\" }";
        }
        else if(uri.compare(0, _cmdIterationStarting.length(), _cmdIterationStarting) == 0)
        {
            // starting a fuzzing iteration
            HTMLForm form(request);

            unsigned int iterationCount;
            istringstream ( form["iterationCount"] ) >> iterationCount;

            string isReproduction = form["isReproduction"]; // "true" or "false"

            // TODO - Implement me!
        }
        else if(uri.compare(0, _cmdIterationFinished.length(), _cmdIterationFinished) == 0)
        {
            // finished our fuzzing iteration

            ostr << "{ \"Status\":\"false\" }";
        }
        else if(uri.compare(0, _cmdDetectedFault.length(), _cmdDetectedFault) == 0)
        {
            // did one of our monitors detect a fault?

            // did not detect fault
            //ostr << " { \"Status\":\"false\" }";

            // did detect fault

            if(FaultNumber)
                ostr << "{ \"Status\":\"true\" }";
            else
                ostr << "{ \"Status\":\"false\" }";
            FaultNumber=0;

        }
        else if(uri.compare(0, _cmdGetMonitorData.length(), _cmdGetMonitorData) == 0)
        {
            // TODO - Implement me!

            /*
            {
                "Results":[
                    {
                        "iteration":0,
                        "controlIteration":false,
                        "controlRecordingIteration":false,
                        "type":0,  (0 unknown, 1 Fault, 2 Data)
                        "detectionSource":null,
                        "title":null,
                        "description":null,
                        "majorHash":null,
                        "minorHash":null,
                        "exploitability":null,
                        "folderName":null,
                        "collectedData":[
                            {"Key":"data1","Value":"AA=="}
                        ]
                    }
                ]
            }
            */

            ostr << "{\"Results\":[{\"iteration\":0,\"controlIteration\":false,\"controlRecordingIteration\":false,\"type\":1,\"detectionSource\":\"Native Agent\",\"title\":\"Test Fault\",\"description\":\"Test fault from native agent.\",\"majorHash\":null,\"minorHash\":null,\"exploitability\":\"CRITICAL\",\"folderName\":\"CRITICAL-1-1\",\"collectedData\":[{\"Key\":\"collected-data.bin\",\"Value\":\"AA==\"}]}]}";
        }
        else if(uri.compare(0, _cmdMustStop.length(), _cmdMustStop) == 0)
        {
            // should we stop all fuzzing?

            ostr << "{ \"Status\":\"false\" }";
        }
        else
        {
            ostr << "{\"Error\":\"Error, unknown command.\"}";
        }
    }

    // Helper method for getting std::string value back
    string GetJsonValue(Object::Ptr aoJsonObject, const char *aszKey)
    {
        Poco::Dynamic::Var loVariable;
        string lsReturn;
        string lsKey(aszKey);

        // Get the member Variable
        //
        loVariable = aoJsonObject->get(lsKey);

        // Get the Value from the Variable
        //
        lsReturn = loVariable.convert<std::string>();

        return lsReturn;
    }

private:
    string _urlPrefix;
    string _cmdAgentConnect;
    string _cmdAgentDisconnect;
    string _cmdCreatePublisher;
    string _cmdStartMonitor;
    string _cmdStopMonitor;
    string _cmdStopAllMonitors;
    string _cmdSessionStarting;
    string _cmdSessionFinished;
    string _cmdIterationStarting;
    string _cmdIterationFinished;
    string _cmdDetectedFault;
    string _cmdGetMonitorData;
    string _cmdMustStop;
};

class ErrorRequestHandler: public HTTPRequestHandler
{
public:
    ErrorRequestHandler()
    {
    }

    void handleRequest(HTTPServerRequest& request,
                       HTTPServerResponse& response)
    {
        Application& app = Application::instance();
        /*app.logger().information("Request from "
            + request.clientAddress().toString());*/

        response.setChunkedTransferEncoding(true);
        response.setContentType("text/html");

        std::ostream& ostr = response.send();
        ostr << "<html><head><title>Peach Native Agent</title></head>";
        ostr << "<body><p style=\"text-align: center; "
                "font-size: 48px;\">";
        ostr << "Error, only Peach Fuzzer via Rest Agent Channel is expected.";
        ostr << "</p></body></html>";
    }
};

class PeachRequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
    PeachRequestHandlerFactory()
    {
        _urlPrefixAgent = "/Agent/";
        _urlPrefixPublisher = "/Agent/Publisher/";
    }

    HTTPRequestHandler* createRequestHandler(
        const HTTPServerRequest& request)
    {
        if(request.getURI().compare(0, _urlPrefixPublisher.length(),  _urlPrefixPublisher) == 0)
            return new PublisherRequestHandler();

        if (request.getURI().compare(0, _urlPrefixAgent.length(), _urlPrefixAgent) == 0)
            return new PeachRequestHandler();

        if (request.getURI() == "/")
        {
            return new ErrorRequestHandler();
        }
        else
            return 0;
    }

private:
    string _urlPrefixAgent;
    string _urlPrefixPublisher;
};

class HTTPPeachServer: public Poco::Util::ServerApplication
{
public:
    HTTPPeachServer(): _helpRequested(false)
    {
    }

    ~HTTPPeachServer()
    {
    }

protected:
    void initialize(Application& self)
    {
        loadConfiguration();
        ServerApplication::initialize(self);
    }

    void uninitialize()
    {
        ServerApplication::uninitialize();
    }

    void defineOptions(OptionSet& options)
    {
        ServerApplication::defineOptions(options);

        options.addOption(
        Option("help", "h", "display argument help information")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<HTTPPeachServer>(
                this, &HTTPPeachServer::handleHelp)));
    }

    void handleHelp(const std::string& name,
                    const std::string& value)
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader(
            "A web server that serves the current date and time.");
        helpFormatter.format(std::cout);
        stopOptionsProcessing();
        _helpRequested = true;
    }

    int main(const std::vector<std::string>& args)
    {
        if (!_helpRequested)
        {
            unsigned short port = (unsigned short)
                config().getInt("HTTPPeachServer.port", 9980);

            cout << "Listening on port " << port << ".\n";

            ServerSocket svs(port);
            HTTPServer srv(new PeachRequestHandlerFactory(),
                svs, new HTTPServerParams);

            srv.start();
            waitForTerminationRequest();
            srv.stop();
        }

        return Application::EXIT_OK;
    }

private:
    bool _helpRequested;
};

typedef union {
    int i;
    char c;
}my_union;

//判断大小端
int checkSystem1(void)
{
    my_union u;
    u.i = 1;
    return (u.i == u.c);
}

int arr2str() // 这里为了方便直接用main函数
{
    //char array[] = { 'h', 'e', 'l', 'l', 'o' };
    /* 需要注意的是，这里没有终结符，故需要知道数组的 */
    /* 大小（数组的大小是编译时常量）*/
    char *dest_str; // 目标字符串

    dest_str = (char *)malloc(sizeof(char) * (sizeof(kPlayReadyUuid) + 1));
    /* 为字符串分配堆空间 */

    strncpy(dest_str, (char *)kPlayReadyUuid, sizeof(kPlayReadyUuid));
    // 用C标准库函数strncpy拷贝字符
    printf("\n");
    printf("zhangpan : kPlayReadyUuid is [%s]\n", kPlayReadyUuid);
     printf("zhangpan : dest_str is [%s]\n", dest_str);
     printf("kPlayReadyUuid is : \n");
     for (int i = 0; i < sizeof(kPlayReadyUuid); i++)
    {
        printf("[%d] ", kPlayReadyUuid[i]);
    }
     printf("\n");

     for (int i = 0; i < sizeof(kPlayReadyUuid); i++)
    {
        printf("[0x%x] ", kPlayReadyUuid[i]);
    }
     printf("\n");
    return 0;
}

int main(int argc, char** argv)
{
    cout << "\n";
    cout << ">> Peach Native Agent Sample\n";
    cout << ">> Copyright (c) Peach Fuzzer, LLC\n";
    cout << "\n";
    s_intServicePid = 0;

    //int check = checkSystem1();
    //printf(">>>>The system is %s <<<<\n", check ? "[Small end]":"[Big end]");

    //arr2str();

    if (0 != get_pid_by_name("service_drm", &s_intServicePid))
    {
        return -1;
    }

    DEBUG_INFO_INFO("main");

    DEBUG_INFO_DEC(s_intServicePid);
    ModularDrmInfo = ModularDrmInterface::Create(kPlayReadyUuid);
    HTTPPeachServer app;
    app.run(argc, argv);
    ModularDrmInterface::Destroy(ModularDrmInfo);

    return 1;
}

// end
