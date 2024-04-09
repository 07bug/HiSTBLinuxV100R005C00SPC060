/******************************************************************************
 Copyright (C), 2015-2021, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : ModularDrmInterface.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2017/07/05
Last Modified :
Description   : drm engine interface definition, C++ TO C.
CNcomment     : Drm接口头文件定义
Function List :
History       :
******************************************************************************/

#ifndef _DRM_ENGINE_H_
#define _DRM_ENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************************** Structure Definition ****************************/

#define HI_DRMENGINE_UUID_LEN (16)
#define HI_DRMENGINE_KEY_LEN (16)
#define HI_DRMENGINE_IV_LEN (16)

#define MAX_SESSIONID_LEN (16)
#define MAX_KEYSETID_LEN (16)
#define MAX_ERRORMSG_LEN (16)

#define MAX_REQUEST_DATA_SIZE (32768)
#define MAX_RESPONSE_DATA_SIZE (32768)
#define MAX_DEFAULT_URL_SIZE (8192)
#define MAX_TRANS_LENGTH (1024*1024)

#define MAX_DRM_HANDLE_COUNT (16)
#define MAX_CRYPTO_HANDLE_COUNT (16)
#define MAX_SESSION_COUNT (16)

#define MAX_SUBSAMPLE_NUM (1024)
#define MAX_SUBSAMPLE_LEN (1024*1024)

#define MAX_PROPERTY_NAME_LEN (16)
#define MAX_PROPERTY_VALUE_LEN (2048)

#define __in
#define __out
#define __inout

typedef enum hiDRMENGINE_KEY_TYPE
{
    HI_DRMENGINE_KEY_TYPE_OFFLINE,        /**<keys will be for offline use,they will be saved to the device for use when the device is not connected to a network */
    HI_DRMENGINE_KEY_TYPE_STREAMING,      /**<This key request type species that the keys will be for online use, they will not be saved to the device for subsequent use when the device is not connected to a network.*/
    HI_DRMENGINE_KEY_TYPE_RELEASE,        /**<This key request type specifies that previously saved offline keys should be released. */
    HI_DRMENGINE_KEY_TYPE_BUTT
} HI_DRMENGINE_KEY_TYPE;

typedef enum hiDRMENGINE_KEYREQUEST_TYPE
{
    HI_DRMENGINE_KEYRST_TYPE_UNKNOWN,    /**<UNKNOWN type */
    HI_DRMENGINE_KEYRST_TYPE_INITIAL,    /**<Key request type is initial license request */
    HI_DRMENGINE_KEYRST_TYPE_RENEWAL,    /**<Key request type is license renewal */
    HI_DRMENGINE_KEYRST_TYPE_RELEASE,    /**<Key request type is license release */
    HI_DRMENGINE_KEYRST_TYPE_BUTT
} HI_DRMENGINE_KEYREQUEST_TYPE;

typedef struct hiDRMENGINE_KEYREQUEST
{   HI_U8 requestData[MAX_REQUEST_DATA_SIZE]; /**< key request data delivered to license server*/
    HI_U32 requestDataLen;
    HI_DRMENGINE_KEYREQUEST_TYPE eKeyRequestType;   /**< key request type,refer to ::HI_DRM_KEYREQUEST_TYPE */
    HI_CHAR defaultUrl[MAX_DEFAULT_URL_SIZE]; /**< default url of license server */
} HI_DRMENGINE_KEY_REQUEST;

typedef enum hiDRMENGINE_CRYPTO_MODE
{
    HI_DRMENGINE_CRYPTO_MODE_UNENCRYPTED = 0,     /**< no encrypted,not support*/
    HI_DRMENGINE_CRYPTO_MODE_AES_CTR     = 1,      /**< AES CRT mode */
    HI_DRMENGINE_CRYPTO_MODE_AES_WV      = 2,      /**< AES WV */
    HI_DRMENGINE_CRYPTO_MODE_AES_CBC     = 3,      /**< AES CBC mode */
} HI_DRMENGINE_CRYPTO_MODE;

typedef struct hiDRMENGINE_PATTERN
{
    HI_U32 u32numEncryptBlocks;  /**< Number of blocks to be encrypted in the pattern.
                          If zero, pattern encryption is inoperative.*/
    HI_U32 u32numSkipBlocks;      /**<  Number of blocks to be skipped (left clear) in the pattern.
                           If zero,pattern encryption is inoperative.*/
} HI_DRMENGINE_PATTERN;

typedef struct hiDRMENGINE_SUBSAMPLES
{
    HI_U32 u32numBytesOfClearData;      /**< number of clear data per sample,the unit is byte*/
    HI_U32 u32numBytesOfEncryptedData;  /**< number of encrypted data per sample,the unit is byte*/
} HI_DRMENGINE_SUBSAMPLES;

typedef struct hiDrm_SessionId
{
    HI_U8 sessionId[MAX_SESSIONID_LEN];
    HI_U32 sessionIdLen;
}HI_DRMENGINE_SESSION;

/******************************* API Declaration *****************************/
HI_S32 HI_DrmEngine_Create(__out HI_VOID** v_ppDrmHandle,
                           __in  const HI_U8 uuid[HI_DRMENGINE_UUID_LEN]);

HI_S32 HI_DrmEngine_Destroy(__in const HI_VOID* v_pDrmHandle);

HI_BOOL HI_DrmEngine_isCryptoSchemeSupported(__in const HI_VOID* v_pDrmHandle,
                                             __in const HI_U8 uuid[HI_DRMENGINE_KEY_LEN],
                                             __in const HI_CHAR* mimeType);

HI_S32 HI_DrmEngine_openSession(__in  const HI_VOID* v_pDrmHandle,
                                __out HI_DRMENGINE_SESSION* pSession);

HI_S32 HI_DrmEngine_closeSession(__in const HI_VOID* v_pDrmHandle,
                                 __in const HI_DRMENGINE_SESSION session);

HI_S32 HI_DrmEngine_getKeyRequest(__in  const HI_VOID* v_pDrmHandle,
                                  __in  const HI_DRMENGINE_SESSION session,
                                  __in  const HI_U8* initData,
                                  __in  const HI_U32 initDataLen,
                                  __in  HI_CHAR const* mimeType,
                                  __in  const HI_DRMENGINE_KEY_TYPE drmEngineKeyType,
                                  __out HI_DRMENGINE_KEY_REQUEST* pCTypeKeyRequest);

HI_S32 HI_DrmEngine_provideKeyResponse(__in  const HI_VOID* v_pDrmHandle,
                                       __in  const HI_DRMENGINE_SESSION session,
                                       __in  const HI_U8* response,
                                       __in  const HI_U32 responseLen,
                                       __out HI_U8* keySetId,
                                       __out HI_U32* pKeySetIdLen);

//20170925 x00418653
//VMX api add
HI_S32 HI_DrmEngine_getPropertyString(__in  const HI_VOID* v_pDrmHandle,
                                      __in  const HI_U8* name,
                                      __in  const HI_U32 nameLen,
                                      __out HI_U8* value,
                                      __out HI_U32* pValueLen);

HI_S32 HI_DrmEngine_setPropertyString(__in  const HI_VOID* v_pDrmHandle,
                                      __in  const HI_U8* name,
                                      __in  const HI_U32 nameLen,
                                      __in  const HI_U8* value,
                                      __in  const HI_U32 valueLen);
//END VMX add

HI_S32 HI_DrmEngine_cryptoCreate(__in const HI_DRMENGINE_SESSION session,
                                 __in const HI_U8 uuid[HI_DRMENGINE_UUID_LEN]);

HI_S32 HI_DrmEngine_cryptoDestroy(__in const HI_DRMENGINE_SESSION session);

HI_BOOL HI_DrmEngine_requiresSecureDecoderComponent(__in const HI_DRMENGINE_SESSION session,
                                                    __in const HI_CHAR* mime);

HI_S32  HI_DrmEngine_decrypt(__in  const HI_DRMENGINE_SESSION session,
                             __in  HI_BOOL secure,
                             __in  const HI_U8 key[HI_DRMENGINE_KEY_LEN],
                             __in  const HI_U8 iv[HI_DRMENGINE_IV_LEN],
                             __in  HI_DRMENGINE_CRYPTO_MODE drmEngineMode,
                             __in  const HI_DRMENGINE_PATTERN *drmEnginePattern,
                             __in  const HI_VOID* pSrc,
                             __in  HI_S32 s32srcSize,
                             __in  const HI_DRMENGINE_SUBSAMPLES* drmEngineSubSamples,
                             __in  HI_S32 numSubSamples,
                             __out HI_VOID* pDst,
                             __out HI_U8* errorDetailMsg,
                             __out HI_U32* pErrorDetailMsgLen);

#ifdef __cplusplus
}
#endif

#endif //HI_MODULAR_DRM_INTERFACE_H__

