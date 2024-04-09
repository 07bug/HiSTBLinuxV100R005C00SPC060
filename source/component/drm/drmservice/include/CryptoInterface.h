/******************************************************************************
 Copyright (C), 2015-2021, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name    : CryptoInterface.h
Version        : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2016/02
Last Modified :
Description   : modular drm crypto interface api definition.
                CNcomment: Modular Drm Crypto接口头文件定义CNend
Function List :
History       :
******************************************************************************/

#ifndef CRYPTO_INTERFACE_H__
#define CRYPTO_INTERFACE_H__

#include "DrmDefines.h"

/******************************* API Declaration *****************************/
/** \addtogroup      DrmService_API */
/** @{ */

/** Modular Drm interface api */
class CryptoInterface
{
public:
    virtual ~CryptoInterface() {};

    /**
    \brief create and instance the drm crypto object.
    \attention \n
    if want to access the crypto function, this must be call first.

    \param [in] uuid The UUID of the crypto scheme
    \param [in] initData session id which from ModularDrmInterface by ::openSessioin()
    \param [in] initSize sizeof initData

    \retval ::CryptoInterface*  drm crypto object access handle.
    \retval ::NULL  create crypto handle fail.
    \see \n
    None
    */
    static CryptoInterface* Create(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* initData, HI_S32 initSize);

    /**
    \brief Destroy drm crypto instance.
    \attention \n
    None.

    \param [in] object the instance handle that will be destroy.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    static HI_S32 Destroy(CryptoInterface* &object);

    /**
    \brief Query if the given scheme identified by its UUID is supported on device

    \attention \n
    None

    \param [in] uuid The UUID of the crypto scheme.

    \retval ::HI_TRUE scheme is supported.
    \retval ::HI_FALSE scheme is not supported.

    \see \n
    None
    */
    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_UUID_LEN]) = 0;

    /**
    \brief Query if the crypto scheme requires the use of a secure decoder
           to decode data of the given mime type

    \attention \n
     Not support now in drm plugin.(either playready or widevine)

     If this method returns false, a non-secure decoder will be used to
     decode the data after decryption. The decrypt API below will have
     to support insecure decryption of the data (secure = false) for
     media data of the given mime type.


    \param [in] mime The mime type of the media data.

    \retval ::HI_TRUE secure
    \retval ::HI_FALSE no secure

    \see \n
    None
    */
    virtual HI_BOOL requiresSecureDecoderComponent(const HI_CHAR* mime) = 0;

    /**
    \brief set media drm sessioin

    \attention \n
     Not support now in drm plugin.(either playready or widevine)

     A Drm session may be associated with a Crypto session.  The
     associated Drm session is used to load decryption keys
     into the crypto/drm plugin.  The keys are then referenced by key-id
     in the 'key' parameter to the decrypt() method.

    \param [in] sessionId the Drm sessionId to associate with this Crypto instance

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 setMediaDrmSession(const Vector<HI_U8>& sessionId) = 0;

    /**
    \brief Decrypt the provided input data

    \attention \n

    This a synchronous interface.

    Returns a non-negative result to indicate the number of bytes written
    to the dstPtr, or a negative result to indicate an error.

    \param [in] secure should be HI_TRUE or HI_FALSE
    \param [in] key Specifies which key to use
    \param [in] iv The initialization vector to use for the cipher
    \param [in] mode Encryption mode of the data,usually mode is ::HI_CRYPTO_MODE_AES_CTR
    \param [in] pSrc Source data willed be decrypted
    \param [in] s32srcSize Size of pSrc data
    \param [in] subSamples Sample description of source data,refer to::HI_DRM_SUBSAMPLES
    \param [in] numSubSamples number of samples
    \param [out] dstPtr pointer to output clear data
    \param [out] errorDetailMsg if call fail,may have a error msg data.

    \retval ::HI_S32 result to indicate the number of bytes written to pDst.
    \retval ::HI_FAILURE result to indicate an error

    \see \n
    None
    */
    virtual HI_S32 decrypt(
        HI_BOOL secure,
        const HI_U8 key[HI_DRM_KEY_LEN],
        const HI_U8 iv[HI_DRM_IV_LEN],
        HI_CRYPTO_MODE mode,
        const HI_VOID* pSrc, HI_S32 s32srcSize,
        const HI_DRM_SUBSAMPLES* subSamples, HI_S32 numSubSamples,
        HI_VOID* pDst,
        String8 &errorDetailMsg) = 0;

};

/** @}*/  /** <!-- ==== API Declaration End ====*/
#endif //CRYPTO_INTERFACE_H__
