#ifndef __HI_GO_DECODE_H__
#define __HI_GO_DECODE_H__

#include "hi_type.h"
#include "hi_go_comm.h"
#include "hi_go_surface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/*************************** Structure Definition ****************************/
/** \addtogroup      HIGO_DEC */
/** @{ */  /** <!-- [HIGO_DEC] */

/** Decoding type of the decoding instance*//** CNcomment: ����ʵ���Ľ������� */
typedef enum
{
    HIGO_DEC_IMGTYPE_JPEG = HIGO_IMGTYPE_JPEG, /**<.jpeg picture*//**<CNcomment: JPEG��ʽͼƬ*/
    HIGO_DEC_IMGTYPE_GIF  = HIGO_IMGTYPE_GIF,  /**<.gif picture*//**<CNcomment: GIF��ʽͼƬ*/
    HIGO_DEC_IMGTYPE_BMP  = HIGO_IMGTYPE_BMP, /**<.bmp picture*//**<CNcomment: BMP��ʽͼƬ */
    HIGO_DEC_IMGTYPE_PNG  = HIGO_IMGTYPE_PNG,  /**<.png picture*//**<CNcomment: PNG��ʽͼƬ */
    HIGO_DEC_IMGTYPE_RLE  = HIGO_IMGTYPE_RLE,  /**<.rle picture*//**<CNcomment: RLE��ʽͼƬ */
    HIGO_DEC_IMGTPYE_BUTT
} HIGO_DEC_IMGTYPE_E;

/**Stream source*//** CNcomment: ��������Դ */
typedef enum
{
    HIGO_DEC_SRCTYPE_FILE = 0, /**<Streams are derived from files.*//**<CNcomment: ������Դ���ļ�*/
    HIGO_DEC_SRCTYPE_MEM,      /**<Streams are derived from the memory.*//**<CNcomment: ������Դ���ڴ�*/
    HIGO_DEC_SRCTYPE_STREAM,   /**<Streams are derived from stream data.*/  /**<CNcomment: ������Դ����ʽ����*/
    HIGO_DEC_SRCTYPE_BUTT
} HIGO_DEC_SRCTYPE_E;

typedef enum
{
    HIGO_DEC_POSITION_SET = 0,   /*Start position*//** CNcomment:��ʼλ��*/
    HIGO_DEC_POSITION_CUR,       /*From the current position*//** CNcomment:�ӵ�ǰλ��*/
    HIGO_DEC_POSITION_END,       /*From the end position*//** CNcomment:�ӽ���λ��*/
    HIGO_DEC_POSITION_BUTT
}HIGO_DEC_POSITION_E;

typedef struct
{
	HIGO_MEMTYPE_E MemType;
	HI_BOOL IsPubPalette;  /*Decoder uses common Palette or not*//** CNcomment:����ͼƬ�Ƿ�ʹ�ù�����ɫ��,ֻ�������ʽ��Ч*/
}HIGO_DEC_SURINFO_S;


typedef HI_S32 (*PTR_Dec_WriteStreamCB_FN)(HIGO_DEC_POSITION_E Position,  HI_S32 Offset);


/**Detailed information about the stream source*//** CNcomment:������Դ����ϸ��Ϣ*/
typedef union
{
    /*The following information is required if the input source is the memory.*//** CNcomment:����ԴΪ�ڴ��ʱ��Ҫ����Ϣ*/
    struct
    {
        HI_CHAR* pAddr;      /**<Memory pointer address*//**<CNcomment: �ڴ�ָ���ַ*/
        HI_U32 Length;       /**<Length*//**<CNcomment: ����*/
    } MemInfo;

    /*Picture name*//** CNcomment:ͼƬ�ļ���*/
    const HI_CHAR *pFileName;
    PTR_Dec_WriteStreamCB_FN pWriteCB;
} HIGO_DEC_SRCINFO_U;

/**Parameters for creating a decoding instance.*//** CNcomment: ��������ʵ����Ҫ�Ĳ��� */
typedef struct
{
    HIGO_DEC_SRCTYPE_E SrcType; /**<Type of the input stream.*//**<CNcomment: ��������������*/
    HIGO_DEC_SRCINFO_U SrcInfo; /**<Information about the input source.*//**<CNcomment: ����Դ��ϸ��Ϣ*/
} HIGO_DEC_ATTR_S;

/** Major information after decoding*//** CNcomment: ���������Ϣ */
typedef struct
{
    HI_U32             Count;           /**<Number of pictures*//**<CNcomment: ͼƬ�ĸ��� */
    HIGO_DEC_IMGTYPE_E ImgType;         /**<Type of the input source.*//**<CNcomment: ����Դ���� */
    HI_U32             ScrWidth;        /**<Screen width. The screen refers to that of the picture. The value 0 indicates "invalid".*//**<CNcomment: ��Ļ��ȣ��˴���Ļ��ʾͼƬ�ļ���Ļ��0��ʾ��Ч */
    HI_U32             ScrHeight;       /**<Screen height. The screen refers to that of the picture. The value 0 indicates "invalid".*//**<CNcomment: ��Ļ�߶ȣ��˴���Ļ��ʾͼƬ�ļ���Ļ��0��ʾ��Ч */
    HI_BOOL            IsHaveBGColor;   /**<Whether there is any background color.*//**<CNcomment: �Ƿ��б���ɫ */
    HI_COLOR           BGColor;         /**<Background color*//**<CNcomment: ������ɫ */
} HIGO_DEC_PRIMARYINFO_S;

/** Index picture format*//** CNcomment: ����ͼƬ��ʽ */
typedef struct
{
    HI_U32    OffSetX;                /**<X offset value on the screen. The screen mentioned in this document refers to that of the picture.*//**<CNcomment: ����Ļ�ϵ�Xƫ�������˴���Ļ��ʾͼƬ�ļ���Ļ����ͬ */
    HI_U32    OffSetY;                /**<Y offset value on the screen.*//**<CNcomment: ����Ļ�ϵ�Yƫ����*/
    HI_U32    Width;                  /**<Width of the original picture*//**<CNcomment: ԭʼͼƬ�Ŀ�� */
    HI_U32    Height;                  /**<Height of the original picture*//**<CNcomment: ԭʼͼƬ�ĸ߶� */
    HI_U8     Alpha;                  /**<Information about channel alpha used for overlaying pictures. The alpha value ranges from 0 to 255.*//**<CNcomment: ����ͼƬ���е��ӵ�ͨ��alpha��Ϣ����Χ��0-255 */
    HI_BOOL   IsHaveKey;              /**<Key enable. HI_FALSE: disabled; HI_TRUE: enabled*//**<CNcomment: �Ƿ���KEY�� HI_FALSE: KEY��ʹ�ܣ�HI_TRUE: KEYʹ�� */
    HI_COLOR  Key;                    /**<Information about colorkey used for overlaying pictures*//**<CNcomment: ����ͼƬ���е��ӵ�colorkey��Ϣ */
    HIGO_PF_E Format;                 /**<Pixel format of the picture source*//**<CNcomment: ͼƬԴ���ظ�ʽ */
    HI_U32    DelayTime;              /**<Time interval between this picture and the previous one (10 ms). The value 0 indicates that the parameter is invalid.*//**<CNcomment: ����һ��ͼƬ��ʱ����(10ms)��0��ʾ�ò�����Ч */
    HI_U32    DisposalMethod;         /**<Processing method of the current frame. This application programming interface (API) is valid for only GIF pictures. 0: customized processing method; 1: no processing method; 2: use the background color.*/    /**<CNcomment: ��ǰ֡���������˽ӿ�ֻ��GIF��Ч��0:�û���������ʽ��1:��������2:ʹ�ñ���ɫ��*/
} HIGO_DEC_IMGINFO_S;

/* Picture attributes after decoding*//** CNcomment: �����ͼƬ���� */
typedef struct
{
    HI_U32    Width;                  /**<Expected width after decoding*//**<CNcomment: ����������� */
    HI_U32    Height;                 /**<Expected height after decoding*//**<CNcomment: ���������߶�*/
    HIGO_PF_E Format;                 /**<Expected pixel format after decoding*//**<CNcomment: ������������ظ�ʽ*/
} HIGO_DEC_IMGATTR_S;

/** Extended data format type*//** CNcomment: ��չ���ݸ�ʽ���� */
typedef enum
{
    HIGO_DEC_EXTEND_EXIF = 0,          /**<Extended-data in EXIF format*//**<CNcomment: EXIF��ʽ����չ���� */
    HIGO_DEC_EXTEND_EXIF_BUTT
} HIGO_DEC_EXTENDTYPE_E;

/** Basic picture information*//** CNcomment: ͼƬ������Ϣ */
typedef struct
{
    HI_U32    Width;                /**<Picture width*//**<CNcomment: ͼƬ�Ŀ�� */
    HI_U32    Height;               /**<Picture height*//**<CNcomment: ͼƬ�ĸ߶� */
    HIGO_PF_E PixelFormat;          /**<Pixel format*//**<CNcomment: ���ظ�ʽ */
    HI_U32    VirAddr[3];           /**<Virtual address. If the address is in RGB format, only the first VirAddr[0] is the start address,
                                                and VirAddr[1] and VirAddr[2] are invalid. If the address is in YC format,
                                                VirAddr[0] indicates the start address of the Y component, VirAddr[1] indicates the start address of the C component,
                                                and VirAddr[2] is invalid.*/
                                                /**<CNcomment: �����ַ�������RGB��ʽ��ֻ�е�һ��VirAddr[0]Ϊ��ʼ��ַ��
                                                VirAddr[1]��VirAddr[2]��Ч�������YC��ʽ��
                                                VirAddr[0]��ʾY������ʼ��ַ��VirAddr[1]��ʾC������ʼ��ַ��
                                                VirAddr[2]��Ч */
    HI_U32    PhyAddr[3];           /**<Physical address. The usage principles are the same as previous ones.*//**<CNcomment: �����ַ��ʹ��ԭ��ͬ�� */
    HI_U32    Pitch[3];             /**<Pitch. The usage principles are the same as previous ones.*//**<CNcomment: �м�࣬ʹ��ԭ��ͬ�� */
    HI_U32    Palate[256];         /**<Palette*//**<CNcomment: ��ɫ�� */
} HIGO_DEC_IMGDATA_S;

/** Information about input streams*//** CNcomment: ��������Ϣ*/
typedef struct
{
    HI_VOID *pStreamAddr;    /**<Virtual start address of streams*//**<CNcomment: ��������ʼ��ַ*/
    HI_U32   StreamLen;      /**<Stream length*//**<CNcomment: ������*/
    HI_BOOL  EndFlag;        /**<Stream end flag*//**<CNcomment: �����������*/
    HI_U32   CopyLen;         /**<Actual length of the copied data*//**<CNcomment: ʵ�ʿ��������ݳ���*/
}HIGO_DEC_WRITESTREAM_S;


/** @} */  /*! <!-- Structure Definition end */
/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      HIGO_DEC */
/** @{ */  /** <!-- [HIGO_DEC] */


 /**
\brief Initializes the decoder.CNcomment: ��������ʼ�� CNend
\attention \n
::HI_GO_Init already calls the interfaceCNcomment: ::HI_GO_Init���Ѱ����Ըýӿڵĵ��� CNend
\param  N/ACNcomment: �� CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
::HI_GO_Init \n
::HI_GO_DeinitDecoder
*/

HI_S32 HI_GO_InitDecoder(HI_VOID);

/**
\brief Deinitializes the decoder.CNcomment: ������ȥ��ʼ�� CNend
\attention \n
When ::HI_GO_Deinit is called, this API is also called.CNcomment: ::HI_GO_Deinit���Ѱ����Ըýӿڵĵ��� CNend
\param  N/A.CNcomment: �� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_Deinit \n
::HI_GO_InitDecoder
*/

HI_S32 HI_GO_DeinitDecoder(HI_VOID);

 /**
 \brief Creates a decoding handle.CNcomment: ���������� CNend
 \attention \n
 Currently, the formats of .bmp, .png, .jpeg, and .gif are supported. The picture input source can be the memory, files
, and streams. The picture input source of streams is only applicable to the .jpeg format.
CNcomment: Ŀǰ֧��BMP��PNG��JPEG��GIF��ʽ��ͼƬ����Դֻ����Ϊ�ڴ桢�ļ��Լ���ʽ����ʽĿǰֻ��JPEG��ʽ��Ч��CNend

 \param[in] pSrcDesc Information about the input source. This parameter cannot be empty.
                The type of the input stream must match the information about the input source. For example,
corresponding file names must be entered for the file stream, and the memory address and memory size must be entered
for the memory stream.CNcomment: ����Դ��Ϣ������Ϊ��\n
                ��������������Ҫ������Դ��ϸ��Ϣһһƥ�䣬��FILE��������Ҫ������Ӧ���ļ���\n
                ��Memory��������Ҫ����memory�ĵ�ַ�Լ����� CNend
 \param[out] pDecoder Pointer of the decoding instance handle. This parameter cannot be empty.CNcomment: ����ʵ�����ָ�룬����Ϊ�� CNend

 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_NOTINIT
 \retval ::HIGO_ERR_NOMEM
 \retval ::HIGO_ERR_INVHANDLE
 \retval ::HIGO_ERR_INVFILE
 \retval ::HIGO_ERR_INVSRCTYPE
 \retval ::HIGO_ERR_INVIMAGETYPE
 \retval ::HIGO_ERR_INVIMGDATA

\see \n
::HI_GO_DestroyDecoder
*/
HI_S32 HI_GO_CreateDecoder(const HIGO_DEC_ATTR_S* pSrcDesc, HI_HANDLE* pDecoder);

 /**
 \brief Destroys a decoding handle.CNcomment:���ٽ����� CNend
 \attention \n
 N/A.CNcomment:�� CNend
 \param[in] Decoder Handle of the decoding instance.CNcomment:����ʵ����� CNend

 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_CreateDecoder
*/
HI_S32 HI_GO_DestroyDecoder(HI_HANDLE Decoder);

/**
 \brief Stream APICNcomment: ��ʽ�����ӿ� CNend
 \attention \n
 N/A.CNcomment:�� CNend
 \param[in] Decoder Handle of the decoding instance.CNcomment: ����ʵ����� CNend
 \param[in] pStream Pointer to the stream information. This parameter cannot be empty.CNcomment: ������Ϣָ�� ������Ϊ�� CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_INVHANDLE
 \retval ::HIGO_ERR_UNSUPPORTED

\see \n
::HI_GO_CreateDecoder
*/
HI_S32 HI_GO_DecWriteStream(HI_HANDLE Decoder, HIGO_DEC_WRITESTREAM_S *pStream);

/**
 \brief Resets the decoder when you need to terminate the decoding.CNcomment:��λ������������Ҫ��ֹ�����ʱ��ͽ��н�������λ CNend
 \attention \n
  N/A.CNcomment:�� CNend
 \param[in] Decoder Handle of the decoding instance.CNcomment:����ʵ����� CNend
 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE
 \retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_CreateDecoder \n
::HI_GO_DestroyDecoder
*/
HI_S32 HI_GO_ResetDecoder(HI_HANDLE Decoder);

 /**
 \brief Obtains the major information about pictures.CNcomment:��ȡͼƬ�ļ�����Ҫ��Ϣ CNend
 \attention
 N/A.CNcomment:�� CNend
\param[in] Decoder Handle of the decoding instance.CNcomment:����ʵ����� CNend
\param[out] pPrimaryInfo  Pointer to the major information about the decoded picture. This parameter cannot be empty.CNcomment:����ͼƬ����Ϣָ�룬����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR
\retval ::HI_NULL_PTR
\retval ::HIGO_ERR_INVIMGDATA

\see \n
::HI_GO_DecImgInfo
*/
HI_S32 HI_GO_DecCommInfo(HI_HANDLE Decoder, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo);

/**
 \brief Obtains the information about the specified picture. You can customize the picture format.CNcomment: ��ȡָ��ͼƬ����Ϣ����ͬʱ�û���������������ͼ���ʽ CNend
 \attention \n
  N/A.CNcomment: �� CNend
 \param[in] Decoder Handle of the decoding instance.CNcomment: ����ʵ����� CNend
 \param[in] Index
 Picture index number. For .jpeg pictures, the index number of the main picture is 0, and index
numbers of thumbnails start from 1.
                   The index numbers of GIF pictures start from 0 and increase by 1 according to the sequence of the
pictures stored in a file.
CNcomment: ͼƬ�����š�JPEG��ʽͼƬ����ͼ����������0������ͼ��������1��ʼ��\n
                   GIF��ʽͼƬ�������ļ��еĴ洢˳����������0��ʼ�ݼ� CNend
 \param[out] pImgInfo Picture information. This parameter cannot be empty.CNcomment: ͼƬ��Ϣ������Ϊ�� CNend

 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_INVHANDLE
 \retval ::HIGO_ERR_INVINDEX
 \retval ::HI_FAILURE
 \retval ::HI_NULL_PTR
 \retval ::HIGO_ERR_INVIMGDATA

\see \n
::HI_GO_DecCommInfo
*/
HI_S32 HI_GO_DecImgInfo(HI_HANDLE Decoder, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo);

 /**
 \brief Obtains the data of a picture.CNcomment:��ȡ����ͼƬ������ CNend
 \attention \n
 The format in the destination picture attributes does not support the macro block format.CNcomment:Ŀ��ͼƬ�����е�ͼ���ʽ��֧�ֺ���ʽ CNend

\param[in] Decoder Handle of the decoding instance.CNcomment:����ʵ����� CNend
\param[in] Index Index number of a picture, starting from 0.CNcomment:ͼƬ�����ţ������Ŵ�0��ʼ CNend
\param[in] pImgAttr Attribute of the destination picture. If the value is empty, it indicates that the original
picture attributes are retained.CNcomment:Ŀ��ͼƬ���ԣ�Ϊ�ձ�ʾ����ԭͼƬ���� CNend
\param[out] pSurface Handle of the surface where the decoded data is stored.CNcomment:��������ݴ�ŵ�surface�ľ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVINDEX
\retval ::HI_FAILURE
\retval ::HI_NULL_PTR
\retval ::HIGO_ERR_INVIMGDATA
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
::HI_GO_DecCommInfo
*/
HI_S32 HI_GO_DecImgData(HI_HANDLE Decoder, HI_U32 Index, const HIGO_DEC_IMGATTR_S *pImgAttr, HI_HANDLE *pSurface);

/**
 \brief Obtains the extended data.CNcomment: ��ȡ��չ���� CNend
 \attention \n
 Hi3110E does not support the API.CNcomment: Hi3110E��֧�ִ˺����� CNend
 \param[in] Decoder Handle of the decoding instance.CNcomment: ����ʵ����� CNend
 \param[in] DecExtendType
 Type of the obtained extended data. Currently, only the EXIF information in .jpeg format is available.
 CNcomment: ��ȡ��չ���ݵ����ͣ�Ŀǰ��Ҫֻ��JPEG��EXIF��Ϣ CNend
 \param[out] ppData Pointer to the extended data pointer.CNcomment: ָ����չ����ָ���ָ�� CNend
 \param[out] pLength ppData Length.CNcomment: ppData���� CNend
 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_INVHANDLE
 \retval ::HIGO_ERR_UNSUPPORTED

\see \n
::HI_GO_ReleaseDecExtendData
*/
HI_S32 HI_GO_DecExtendData(HI_HANDLE Decoder, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID **ppData, HI_U32 *pLength);

 /**
 \brief Releases extended data.CNcomment:�ͷ���չ���� CNend
 \attention \n
 Hi3110E does not support the API.CNcomment:Hi3110E��֧�ִ˺�����CNend
 \param[in] Decoder Decoder handle.CNcomment:Decoder��� CNend
 \param[in] DecExtendType Type of the obtained extended data. Currently, only the EXIF information in .jpeg format is
available.CNcomment:��ȡ��չ���ݵ����ͣ�Ŀǰ��Ҫֻ��JPEG��EXIF��Ϣ CNend
 \param[in] pData Pointer to the extended data.CNcomment:ָ����չ����ָ�� CNend
 \retval ::HI_SUCCESS
 \retval ::HIGO_ERR_NULLPTR
 \retval ::HIGO_ERR_UNSUPPORTED

\see \n
::HI_GO_DecExtendData
*/
HI_S32 HI_GO_ReleaseDecExtendData(HI_HANDLE Decoder, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID *pData);

/**
\brief Decodes a picture to a specified surface.CNcomment:��ͼ����뵽ָ����surface CNend
\attention \n
The decoded surface is scaled automatically based on the size of the target surface. In addition, the decoded surface
modifies the attributes of the target surface, such as colorkey, alpha value, and palette.
CNcomment:������Surface���Զ�����Ŀ��surface�Ĵ�С�������ţ����һ�ı�Ŀ��surface��COLORKEY��ALPHA�Լ���ɫ������ CNend
\param[in] Decoder Handle of the decoding instance.CNcomment: ����ʵ����� CNend
\param[in] Index   Index number of a decoded picture.CNcomment:����ͼƬ���� CNend
\param[out] Surface Decoded target surface.CNcomment:�����Ŀ��surface CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVINDEX
\retval ::HIGO_ERR_NULLPTR
\retval ::HI_FAILURE
\retval ::HI_NULL_PTR
\retval ::HIGO_ERR_INVIMGDATA
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_UNSUPPORTED

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_DecImgToSurface(HI_HANDLE Decoder, HI_U32 Index, HI_HANDLE Surface);

/**
\brief Decodes a specified file, and generates a new surface.CNcomment:����ָ�����ļ���������һ���µ�surface CNend
\attention \n
    If there are multiple pictures in the file (such as .gif animation, .jpeg main picture, and .jpeg thumbnail),
    only the .jpeg main picture and the first picture of the .gif animation are decoded.
    In addition, the surface size is the same as the picture size.
    CNcomment:����ļ����ж���ͼƬ������:gif������JPEG����ͼ������ͼ��
    JPEGֻ����ͼ��GIF��������һ��ͼƬsurface�Ĵ�С��ͼƬ�Ĵ�Сһ�� CNend
\param[in] pszFile Picture name. The picture can be in the format of .gif, .png, .jpg, or .bmp.CNcomment:ͼƬ�ļ�����������GIF, PNG, JPG, BMP CNend
\param[out] pSurface, Surface for storing decoded pictures.CNcomment:��������ͼ�� CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVINDEX
\retval ::HIGO_ERR_NULLPTR
\retval ::HI_NULL_PTR
\retval ::HIGO_ERR_INVIMGDATA
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVSRCTYPE
\retval ::HIGO_ERR_INVIMAGETYPE

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_DecodeFile(const HI_CHAR* pszFile, HI_HANDLE* pSurface);

/**
\brief Set the attribute of Decoder out Surface memrory.  CNcomment:���ý������Surface���ڴ����� CNend
\attention \n
N/A.CNcomment: �� CNend
\param[in] Decoder handle. CNcomment:����ʵ����� CNend
\param[in] pSurfInfo.  CNcomment:Surface���ڴ����� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_SetDecSurfInfo(HI_HANDLE Decoder, HIGO_DEC_SURINFO_S  *pSurfInfo);

/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif /* __HI_GO_DECODE_H__ */
