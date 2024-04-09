#ifndef __HI_GO_ENCODER_H__
#define __HI_GO_ENCODER_H__

#include "hi_go_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/*************************** Structure Definition ****************************/
/** \addtogroup      HIGO_ENC */
/** @{ */  /** <!-- [HIGO_ENC] */

/**Encoder attributes*/
/** CNcomment:����������*/
typedef struct
{
   HIGO_IMGTYPE_E ExpectType;   /**<Type of the encoded picture*//**<CNcomment:����ͼƬ����*/
   HI_U32 QualityLevel;        /**<The quality level ranges from 1 to 99. The higher the level, the better the quality, and the greater the encoded picture or occupied memory. The QualityLevel parameter is valid for .jpeg pictures only.*//**<CNcomment:1-99��, ����Խ�ߣ�����Խ�ã��������ͼ���ļ����ڴ�ҲԽ��ֻ��JPEG��Ч*/
}HIGO_ENC_ATTR_S;
/** @} */  /*! <!-- Structure Definition end */

/******************************* API declaration *****************************/
/** \addtogroup      HIGO_ENC */
/** @{ */  /** <!-- [HIGO_ENC] */
 /**
\brief Initializes the encoder. CNcomment:��������ʼ�� CNend
\attention \n
When ::HI_GO_Init is called, this application programming interface (API) is also called.
CNcomment: ::HI_GO_Init���Ѱ����Ըýӿڵĵ��� CNend
\param  N/A

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
::HI_GO_Init \n
::HI_GO_DeinitDecoder
*/

HI_S32 HI_GO_InitEncoder(HI_VOID);


/**
\brief Deinitializes the encoder. CNcomment:������ȥ��ʼ�� CNend
\attention \n
When ::HI_GO_Deinit is called, this API is also called.
CNcomment: ::HI_GO_Deinit���Ѱ����Ըýӿڵĵ��� CNend
\param  N/A

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_Deinit \n
::HI_GO_InitDecoder
*/

HI_S32 HI_GO_DeinitEncoder(HI_VOID);

/**
\brief Encodes a surface in a specified format, and saves the encoded surface in a file.
CNcomment:��һ��surface���뵽ָ��ͼ���ʽ�����浽�ļ��� CNend
\attention \n
The .bmp encoding format is supported.
The hardware platform determines whether the .jpeg encoding foramt is supported.
CNcomment:֧�ֱ����bmp��ʽ�ļ� \n
(�Ƿ�֧�ֱ����JPEG,ȡ����Ӳ��ƽ̨) CNend

\param[in] hSurface  Surface to be encoded. CNcomment:��Ҫ�����surface, CNend
\param[in] pFile    Name of the encoded file. This parameter can be empty. If this parameter is not set, the encoded file is named [year]-[month]-[date]-[hour]-[minute]-[second].
                        CNcomment:�������ļ���������Ϊ�գ�Ϊ�����õ�ǰʱ��[��]-[��]-[��]-[ʱ]-[��]-[��]������ CNend
\param[in] pAttr    Encoding attributes. This parameter cannot be empty. CNcomment:�������õ����ԣ�����Ϊ�� CNend

\retval ::HI_SUCCESS Success.
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVSRCTYPE
\retval ::HIGO_ERR_INVIMAGETYPE
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVMIRRORTYPE
\retval ::HIGO_ERR_INVROTATETYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_NOCOLORKEY
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_DEPEND_JPGE

\see \n
*/
HI_S32 HI_GO_EncodeToFile(HI_HANDLE hSurface, const HI_CHAR* pFile, const HIGO_ENC_ATTR_S* pAttr);

/**
\brief Encodes a surface in a specified picture format and saves it in a memory. Ensure that the memory is sufficient.
CNcomment:��һ��surface���뵽ָ��ͼ���ʽ�����浽�ڴ��У������б�ָ֤���ڴ���㹻�� CNend
\attention \n
The data can be encoded as .bmp data, and saved in a specified memory.
The hardware platform determines whether the .jpeg encoding format is supported.
CNcomment:֧�ֱ����bmp��ʽ���ݴ�ŵ�ָ�����ڴ���
(�Ƿ�֧�ֱ����JPEG,ȡ����Ӳ��ƽ̨) CNend

\param[in] hSurface     Surface to be encoded. CNcomment:��Ҫ�����surface, CNend
\param[in] pMem         Start address of the memory for storing the encoded pictures. CNcomment:���������ͼ�������ڴ�����ʼ��ַ CNend
\param[in] MemLen       Size of a specified memory. CNcomment:ָ���ڴ�Ĵ�С CNend
\param[out] pOutLen     Actual size of the used memory, indicating the length of encoded data. Ensure that the value of pOutLen is smaller than or equal to the value of MemLen.
                                CNcomment:ʵ��ʹ�õ��ڴ��С����������ݳ���(����ȷ��pOutLen <= MemLen) CNend
\param[in] pAttr        Encoding attributes. This parameter cannot be empty. CNcomment:�������õ����ԣ�����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVSRCTYPE
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVIMAGETY
\retval ::HIGO_ERR_INVIMAGETYPE
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVMIRRORTYPE
\retval ::HIGO_ERR_INVROTATETYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_NOCOLORKEY
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_DEPEND_JPGE

\see \n
*/

HI_S32 HI_GO_EncodeToMem(HI_HANDLE hSurface, HI_U8* pMem, HI_U32 MemLen, HI_U32* pOutLen, const HIGO_ENC_ATTR_S* pAttr);

/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif /* __HI_TYPE_H__ */
