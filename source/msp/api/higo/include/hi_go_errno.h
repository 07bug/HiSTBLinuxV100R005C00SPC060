#ifndef __HI_GO_ERRNO_H__
#define __HI_GO_ERRNO_H__

/* add include here */
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/***************************** Macro Definition ******************************/
/** \addtogroup      HIGO_ERRCODE */
/** @{ */  /** <!-- [HIGO_ERRCODE] */

/**Error IDs of HiGo projects*/
/** CNcomment:HiGo ��Ŀ����ID */
#define HIGO_ERR_APPID (0x80000000L + 0x30000000L)

typedef enum hiGOLOG_ERRLEVEL_E
{
    HIGO_LOG_LEVEL_DEBUG = 0,  /* debug-level                                  */
    HIGO_LOG_LEVEL_INFO,       /* informational                                */
    HIGO_LOG_LEVEL_NOTICE,     /* normal but significant condition             */
    HIGO_LOG_LEVEL_WARNING,    /* warning conditions                           */
    HIGO_LOG_LEVEL_ERROR,      /* error conditions                             */
    HIGO_LOG_LEVEL_CRIT,       /* critical conditions                          */
    HIGO_LOG_LEVEL_ALERT,      /* action must be taken immediately             */
    HIGO_LOG_LEVEL_FATAL,      /* just for compatibility with previous version */
    HIGO_LOG_LEVEL_BUTT
} HIGO_LOG_ERRLEVEL_E;

/**Macros for defining the error codes of the HiGo*/
/** CNcomment:HiGo �����붨��� */
#define HIGO_DEF_ERR( module, errid) \
    ((HI_S32)((HIGO_ERR_APPID) | (((HI_U32)module) << 16) | (((HI_U32)HIGO_LOG_LEVEL_ERROR) << 13) | ((HI_U32)errid)))

/**HiGo Module encoding*/
/** CNcomment:HiGo ģ����� */
typedef enum
{
    HIGO_MOD_COMM = 0,
    HIGO_MOD_SURFACE,
    HIGO_MOD_MEMSURFACE,
    HIGO_MOD_LAYER,
    HIGO_MOD_BLITER,
    HIGO_MOD_DEC,
    HIGO_MOD_TEXTOUT,
    HIGO_MOD_WINC,
    HIGO_MOD_CURSOR,
    HIGO_MOD_TEXT_LAYOUT,
    HIGO_MOD_BUTT
} HIGO_MOD_E;

/**Common error codes of the HiGo*/
/** CNcomment:HiGo ���������� */
typedef enum
{
    ERR_COMM_NOTINIT = 0,
    ERR_COMM_INITFAILED,
    ERR_COMM_DEINITFAILED,
    ERR_COMM_NULLPTR,
    ERR_COMM_INVHANDLE,
    ERR_COMM_NOMEM,
    ERR_COMM_INTERNAL,
    ERR_COMM_INVSRCTYPE,
    ERR_COMM_INVFILE,
    ERR_COMM_INVPARAM,
    ERR_COMM_INUSE,
    ERR_COMM_UNSUPPORTED,
    ERR_COMM_DEPENDTDE,
    ERR_COMM_DEPENDFB ,
    ERR_COMM_DEPENDMMZ,
    ERR_COMM_DEPENDJPEG,
    ERR_COMM_DEPENDPNG,
    ERR_COMM_DEPENDBMP,
    ERR_COMM_DEPENDGIF,
    ERR_COMM_DEPENDCURSOR,
    ERR_COMM_DEPENDJPGENC,
    ERR_COMM_BUTT
} HIGO_ERR_E;

/**The dependent module is not initialized (0xB0008000).*/
/** CNcomment:��������ģ��δ��ʼ�� 0xB0008000 */
#define HIGO_ERR_NOTINIT HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_NOTINIT)

/*The module fails to be initialized (0xB0008001).*/
/** CNcomment:ģ���ʼ��ʧ�� 0xB0008001 */
#define HIGO_ERR_DEINITFAILED HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_INITFAILED)

/**The module fails to be deinitialized (0xB0008002).*/
/** CNcomment:ģ��ȥ��ʼ��ʧ�� 0xB0008002 */
#define HIGO_ERR_INITFAILED HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEINITFAILED)

/**The input pointer is null (0xB0008003).*/
/** CNcomment:�������Ϊ��ָ�� 0xB0008003 */
#define HIGO_ERR_NULLPTR HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_NULLPTR)

/**The input handle is invalid (0xB0008004).*/
/** CNcomment:������Ч�ľ�� 0xB0008004 */
#define HIGO_ERR_INVHANDLE HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_INVHANDLE)

/**The memory is insufficient (0xB0008005).*/
/** CNcomment:�ڴ治�� 0xB0008005 */
#define HIGO_ERR_NOMEM HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_NOMEM)

/**An internal error occurs (0xB0008006).*/
/** CNcomment:�ڲ����� 0xB0008006 */
#define HIGO_ERR_INTERNAL HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_INTERNAL)

/**The I/O source is invalid (0xB0008007).*/
/** CNcomment:��Ч��IO��Դ 0xB0008007 */
#define HIGO_ERR_INVSRCTYPE HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_INVSRCTYPE)

/**The file operation fails because the file is invalid (0xB0008008).*/
/** CNcomment:��Ч���ļ����ļ�����ʧ�� 0xB0008008 */
#define HIGO_ERR_INVFILE HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_INVFILE)

/**The parameter is invalid (0xB0008009).*/
/** CNcomment:��Ч�Ĳ��� 0xB0008009*/
#define HIGO_ERR_INVPARAM HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_INVPARAM)

/**The handle is being used (0xB000800A).*/
/** CNcomment:�˾�����ڱ�ʹ�� 0xB000800A */
#define HIGO_ERR_INUSE HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_INUSE)

/**The operation is invalid (0xB000800B).*/
/** CNcomment:��Ч�Ĳ��� 0xB000800B */
#define HIGO_ERR_UNSUPPORTED HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_UNSUPPORTED)

/**An error occurs when the APIs related to the TDE are called (0xB000800C).*/
/** CNcomment:����TDE���� 0xB000800C*/
#define HIGO_ERR_DEPEND_TDE HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEPENDTDE)

/**An error occurs when the APIs related to the FB are called (0xB000800D).*/
/** CNcomment:����FB����  0xB000800D*/
#define HIGO_ERR_DEPEND_FB HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEPENDFB)

/**An error occurs when the APIs related to the MMZ are called (0xB000800E).*/
/** CNcomment:����MMZ���� 0xB000800E*/
#define HIGO_ERR_DEPEND_MMZ HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEPENDMMZ)

/**An error occurs when the APIs related to .jpeg decoding are called (0xB000800F).*/
/** CNcomment:����JPEG�������    0xB000800F*/
#define HIGO_ERR_DEPEND_JPEG HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEPENDJPEG)

/**An error occurs when the APIs related to .png decoding are called (0xB0008010).*/
/** CNcomment:����PNG������� 0xB0008010*/
#define HIGO_ERR_DEPEND_PNG HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEPENDPNG)

/**An error occurs when the APIs related to .bmp decoding are called (0xB0008011).*/
/** CNcomment:����BMP������� 0xB0008011*/
#define HIGO_ERR_DEPEND_BMP HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEPENDBMP)

/**An error occurs when the APIs related to .gif decoding are called (0xB0008012).*/
/** CNcomment:����GIF������� 0xB0008012*/
#define HIGO_ERR_DEPEND_GIF HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEPENDGIF)

/**An error occurs when the APIs related to the cursor are called (0xB0008013).*/
/** CNcomment:����CURSOR�������  0xB0008013*/
#define HIGO_ERR_DEPEND_CURSOR HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEPENDCURSOR)

/**An error occurs when the APIs related to .jpeg encoding are called (0xB0008014).*/
/** CNcomment:����jpeg����ʧ�� 0xB0008014*/
#define HIGO_ERR_DEPEND_JPGE HIGO_DEF_ERR(HIGO_MOD_COMM, ERR_COMM_DEPENDJPGENC)


/**Error codes of the HiGo surface module*/
/** CNcomment:HiGo surfaceģ������� */
typedef enum
{
    ERR_SURFACE_INVSURFACESIZE = 0,
    ERR_SURFACE_INVSURFACEPF,
    ERR_SURFACE_NOTLOCKED,
    ERR_SURFACE_LOCKED,
    ERR_SURFACE_NOCOLORKEY,
    ERR_SURFACE_BUTT
} HIGO_SURFACE_ERR_E;

#define SURFACE_DEF_ERR(err) HIGO_DEF_ERR(HIGO_MOD_SURFACE, err)

/**The surface size is incorrect (0xB0018000).*/
/** CNcomment:surface�ߴ粻��ȷ 0xB0018000 */
#define HIGO_ERR_INVSURFACESIZE SURFACE_DEF_ERR(ERR_SURFACE_INVSURFACESIZE)

/**The pixel format of the surface is incorrect (0xB0018001).*/
/** CNcomment:surface���ظ�ʽ����ȷ 0xB0018001 */
#define HIGO_ERR_INVSURFACEPF SURFACE_DEF_ERR(ERR_SURFACE_INVSURFACEPF)

/**The surface cannot be unlocked because it is not locked (0xB0018002).*/
/** CNcomment:surfaceδ���������ܽ���surface�������� 0xB0018002 */
#define HIGO_ERR_NOTLOCKED SURFACE_DEF_ERR(ERR_SURFACE_NOTLOCKED)

/**The surface cannot be written because it is locked (0xB0018003).*/
/** CNcomment:surface����������surface���е�д��������ֹ 0xB0018003 */
#define HIGO_ERR_LOCKED SURFACE_DEF_ERR(ERR_SURFACE_LOCKED)

/**The surface does not contain the colorkey value (0xB0018004).*/
/** CNcomment:surface������colorKeyֵ 0xB0018004 */
#define HIGO_ERR_NOCOLORKEY SURFACE_DEF_ERR(ERR_SURFACE_NOCOLORKEY)

/**Error codes of the HiGo Gdev module*/
/** CNcomment:HiGo gdevģ�������*/
typedef enum
{
    ERR_LAYER_INVSIZE = 0,
    ERR_LAYER_INVLAYERID,
    ERR_LAYER_INVPIXELFMT,
    ERR_LAYER_FLUSHTYPE,
    ERR_LAYER_FREEMEM,
    ERR_LAYER_CLOSELAYER,
    ERR_LAYER_CANNOTCHANGE,
    ERR_LAYER_INVORDERFLAG,
    ERR_LAYER_SETALPHA,
    ERR_LAYER_ALREADYSHOW,
    ERR_LAYER_ALREADYHIDE,
    ERR_LAYER_INVLAYERPOS,
    ERR_LAYER_INVSURFACE,
    ERR_LAYER_INVLAYERSIZE,
    ERR_LAYER_INVFLUSHTYPE,
    ERR_LAYER_INVANILEVEL,
    ERR_LAYER_NOTOPEN,
    ERR_LAYER_BUTT
} HIGO_LAYER_ERR_E;

#define LAYER_DEF_ERR(err) HIGO_DEF_ERR(HIGO_MOD_LAYER, err)

/**The layer size is invalid (0xB0038000).*/
/** CNcomment:��Ч��ͼ���С 0xB0038000 */
#define HIGO_ERR_INVSIZE LAYER_DEF_ERR(ERR_LAYER_INVSIZE)

/**The hardware layer ID is invalid (0xB0038001).*/
/** CNcomment:��Ч��Ӳ��ͼ��ID 0xB0038001 */
#define HIGO_ERR_INVLAYERID LAYER_DEF_ERR(ERR_LAYER_INVLAYERID)

/**The pixel format is invalid (0xB0038002).*/
/** CNcomment:��Ч�����ظ�ʽ 0xB0038002 */
#define HIGO_ERR_INVPIXELFMT LAYER_DEF_ERR(ERR_LAYER_INVPIXELFMT)

/**The layer refresh mode is incorrect (0xB0038003).*/
/** CNcomment:ͼ��ˢ��ģʽ���� 0xB0038003 */
#define HIGO_ERR_INVFLUSHTYPE LAYER_DEF_ERR(ERR_LAYER_FLUSHTYPE)

/**The display buffer fails to be released (0xB0038004).*/
/** CNcomment:�ͷ��Դ�ʧ�� 0xB0038004 */
#define HIGO_ERR_FREEMEM LAYER_DEF_ERR(ERR_LAYER_FREEMEM)

/**The layer device fails to be stopped (0xB0038005).*/
/** CNcomment:�ر�ͼ���豸ʧ�� 0xB0038005 */
#define HIGO_ERR_CLOSELAYERFAILED LAYER_DEF_ERR(ERR_LAYER_CLOSELAYER)

/**The z-order of the graphics layer cannot be changed (0xB0038006).*/
/** CNcomment:ͼ��Z�򲻿ɸı� 0xB0038006 */
#define HIGO_ERR_CANNOTCHANGE LAYER_DEF_ERR(ERR_LAYER_CANNOTCHANGE)

/**The z-order change flag is invalid (0xB0038007).*/
/** CNcomment:��Ч��Z���޸ı�־ 0xB0038007 */
#define HIGO_ERR_INVORDERFLAG LAYER_DEF_ERR(ERR_LAYER_INVORDERFLAG)

/**The surface alpha value fails to be set (0xB0038008).*/
/** CNcomment:����surface alphaʧ�� 0xB0038008 */
#define HIGO_ERR_SETALPHAFAILED LAYER_DEF_ERR(ERR_LAYER_SETALPHA)

/**The graphics layer has been displayed (0xB0038009).*/
/** CNcomment:ͼ���Ѿ���ʾ 0xB0038009 */
#define HIGO_ERR_ALREADYSHOW LAYER_DEF_ERR(ERR_LAYER_ALREADYSHOW)

/**The graphics layer has been hidden (0xB003800A).*/
/** CNcomment:ͼ���Ѿ����� 0xB003800A */
#define HIGO_ERR_ALREADYHIDE LAYER_DEF_ERR(ERR_LAYER_ALREADYHIDE)

/**The start position of the graphics layer is invalid (0xB003800B).*/
/** CNcomment:��Ч��ͼ����ʼλ�� 0xB003800B*/
#define HIGO_ERR_INVLAYERPOS LAYER_DEF_ERR(ERR_LAYER_INVLAYERPOS)

/**Alignment fails because the surface is invalid (0xB003800C).*/
/** CNcomment:��Ч��surface����ʾ����ʧ�� 0xB003800C*/
#define HIGO_ERR_INVLAYERSURFACE LAYER_DEF_ERR(ERR_LAYER_INVSURFACE)

/**The anti-flicker level of the graphics layer is invalid (0xB003800F).*/
/** CNcomment:��Ч��ͼ�㿹��˸���� 0xB003800F*/
#define HIGO_ERR_INVANILEVEL LAYER_DEF_ERR(ERR_LAYER_INVANILEVEL)

/**The graphics layer is not started (0xB0038010).*/
/** CNcomment:ͼ��û�д� 0xB0038010*/
#define HIGO_ERR_NOTOPEN LAYER_DEF_ERR(ERR_LAYER_NOTOPEN)

/**Error codes of the HiGo Bliter module*/
/** CNcomment:HiGo bliterģ������� */
typedef enum
{
    ERR_BLITER_INVCOMPTYPE = 0,
    ERR_BLITER_INVCKEYTYPE,
    ERR_BLITER_INVMIRRORTYPE,
    ERR_BLITER_INVROTATETYPE,
    ERR_BLITER_INVROPTYPE,
    ERR_BLITER_INVSCALING,
    ERR_BLITER_OUTOFBOUNDS,
    ERR_BLITER_EMPTYRECT,
    ERR_BLITER_OUTOFPAL,
    ERR_BLITER_NOP,
    ERR_BLITER_BUTT
} HIGO_BLITER_ERR_S;

/**The blending mode is incorrect (0xB0048000).*/
/** CNcomment:����Ļ��ģʽ  0xB0048000 */
#define HIGO_ERR_INVCOMPTYPE HIGO_DEF_ERR(HIGO_MOD_BLITER, ERR_BLITER_INVCOMPTYPE)

/**The colorkey operation is invalid (0xB0048001).*/
/** CNcomment:��Ч��colorKey���� 0xB0048001 */
#define HIGO_ERR_INVCKEYTYPE HIGO_DEF_ERR(HIGO_MOD_BLITER, ERR_BLITER_INVCKEYTYPE)

/**The mirror operation is invalid (0xB0048002).*/
/** CNcomment:��Ч�ľ������ 0xB0048002 */
#define HIGO_ERR_INVMIRRORTYPE HIGO_DEF_ERR(HIGO_MOD_BLITER, ERR_BLITER_INVMIRRORTYPE)

/**The rotation operation is invalid (0xB0048003).*/
/** CNcomment:��Ч����ת���� 0xB0048003 */
#define HIGO_ERR_INVROTATETYPE HIGO_DEF_ERR(HIGO_MOD_BLITER, ERR_BLITER_INVROTATETYPE)

/**The ROP operation is invalid (0xB0048004).*/
/** CNcomment:��Ч��ROP���� 0xB0048004 */
#define HIGO_ERR_INVROPTYPE HIGO_DEF_ERR(HIGO_MOD_BLITER, ERR_BLITER_INVROPTYPE)

/**The scaling is abnormal (0xB0048005).*/
/** CNcomment:���ű����쳣 0xB0048005 */
#define HIGO_ERR_INVSCALING HIGO_DEF_ERR(HIGO_MOD_BLITER, ERR_BLITER_INVSCALING)

/**The rectangle exceeds the boundary (0xB0048006).*/
/** CNcomment:���γ����߽� 0xB0048006*/
#define HIGO_ERR_OUTOFBOUNDS HIGO_DEF_ERR(HIGO_MOD_BLITER, ERR_BLITER_OUTOFBOUNDS)

/**The rectangle is empty (0xB0048007).*/
/** CNcomment:�վ��� 0xB0048007*/
#define HIGO_ERR_EMPTYRECT HIGO_DEF_ERR(HIGO_MOD_BLITER, ERR_BLITER_EMPTYRECT)

/**The palette does not contain this color (0xB0048008).*/
/** CNcomment:��ɫ���ڵ�ɫ���� 0xB0048008*/
#define HIGO_ERR_OUTOFPAL HIGO_DEF_ERR(HIGO_MOD_BLITER, ERR_BLITER_OUTOFPAL)

/**Error codes of the HiGo decoder*/
/** CNcomment:HiGo decodeģ�������*/
typedef enum
{
    ERR_DEC_INVIMAGETYPE = 0,
    ERR_DEC_INVINDEX,
    ERR_DEC_INVIMGDATA,
    ERR_DEC_BUTT
} HIGO_ERR_DEC_E;

/**<The picture format is invalid (0xB0058000).*/
/**<CNcomment:��Ч��ͼƬ���� 0xB0058000 */
#define HIGO_ERR_INVIMAGETYPE HIGO_DEF_ERR(HIGO_MOD_DEC, ERR_DEC_INVIMAGETYPE)

/**<The picture index number is invalid (0xB0058001).*/
/**<CNcomment:��ЧͼƬ������ 0xB0058001 */
#define HIGO_ERR_INVINDEX HIGO_DEF_ERR(HIGO_MOD_DEC, ERR_DEC_INVINDEX)

/**<The picture data is invalid (0xB0058002).*/
/**<CNcomment:��ЧͼƬ���� 0xB0058002 */
#define HIGO_ERR_INVIMGDATA HIGO_DEF_ERR(HIGO_MOD_DEC, ERR_DEC_INVIMGDATA)

/**Error codes of the HiGo textout module*/
/** CNcomment:HiGo textoutģ������� */
typedef enum
{
    ERR_TEXTOUT_INVRECT = 0,
    ERR_TEXTOUT_UNSUPPORT_CHARSET,
    ERR_TEXTOUT_ISUSING,
    ERR_TEXTOUT_NOIMPLEMENT,
    ERR_TEXTOUT_SHAPE,
    ERR_TEXTOUT_MAX_CHAR,
    ERR_TEXTOUT_CHAR_SET,
    ERR_TEXTOUT_BIDI,
    ERR_TEXTOUT_ERRCODE_MAX = 0x1F,
    ERR_TEXTOUT_INTERNAL = 0,
    ERR_TEXTOUT_BUTT
} HIGO_TEXTOUT_ERR_S;

/**The rectangle region is invalid (0xB0068000).*/
/** CNcomment:��Ч�ľ������� 0xB0068000 */
#define HIGO_ERR_INVRECT HIGO_DEF_ERR(HIGO_MOD_TEXTOUT,ERR_TEXTOUT_INVRECT)

/**The character set is not supported (0xB0068001).*/
/** CNcomment:��֧�ֵ��ַ��� 0xB0068001*/
#define HIGO_ERR_UNSUPPORT_CHARSET HIGO_DEF_ERR(HIGO_MOD_TEXTOUT,ERR_TEXTOUT_UNSUPPORT_CHARSET)

/**The character set is not supported (0xB0068002).*/
/** CNcomment:��֧�ֵ��ַ��� 0xB0068002*/
#define HIGO_ERR_ISUSING HIGO_DEF_ERR(HIGO_MOD_TEXTOUT,ERR_TEXTOUT_ISUSING)
/**The function not implement yet (0xB0068003) */
/** CNcomment:�ú�����δʵ�� 0xB0068003 */
#define HIGO_ERR_NOIMPLEMENT  HIGO_DEF_ERR(HIGO_MOD_TEXTOUT, ERR_TEXTOUT_NOIMPLEMENT);
/**Shape Failed (0xB0068004) */
/** CNcomment:����ʧ�� 0xB0068004 */
#define HIGO_ERR_SHAPEFAILED HIGO_DEF_ERR(HIGO_MOD_TEXTOUT, ERR_TEXTOUT_SHAPE);

/**Number of characters greater than limit (0xB0068005) */
/** CNcomment:�ַ��������� 0xB0068005 */
#define HIGO_ERR_MAX_CHAR HIGO_DEF_ERR(HIGO_MOD_TEXTOUT, ERR_TEXTOUT_MAX_CHAR);

/**Char set error (0xB0068006) */
/** CNcomment:�ַ���������� 0xB0068006 */
#define HIGO_ERR_CHAR_SET HIGO_DEF_ERR(HIGO_MOD_TEXTOUT, ERR_TEXTOUT_CHAR_SET);

/**bi-directional process erro(0xB)068007) */
/** CNcomment:˫������� 0xB0068006 */
#define HIGO_ERROR_BIDI HIGO_DEF_ERR(HIGO_MOD_TEXTOUT, ERR_TEXTOUT_BIDI);

/**Internal error (0xB006801F) */
/** CNcomment:�ڲ����� 0xB006801F */
#define HIGO_ERR_TEXTINTERNAL HIGO_DEF_ERR(HIGO_MOD_TEXTOUT, ERR_TEXTOUT_INTERNAL)

/**Error codes of the HiGo Winc module*/
/** CNcomment:HiGo Wincģ������� */
typedef enum
{
    ERR_WINC_ALREADYBIND = 0, /**<The Winc module has been attached.*//**<CNcomment:�Ѿ����� */
    ERR_WINC_INVZORDERTYPE,   /**<The z-order adjustment mode is invalid.*//**<CNcomment:��Ч��Z�������ʽ */
    ERR_WINC_NOUPDATE,        /**<The desktop is not refreshed.*//**<CNcomment:�����޸��� */
    ERR_WINC_INVPF,           /**<The pixel format is invalid.*//**<CNcomment:��Ч�����ظ�ʽ */
    ERR_WINC_INVTREE,           /**<The window tree is invalid.*//**<CNcomment:��Ч�Ĵ����� */
    ERR_WINC_ALREADYSETMODE,    /**<The window already be set mode.*//**<CNcomment:�Ѿ��趨�����ڴ�ģʽ*/
    ERR_WINC_BUTT
} HIGO_ERR_WINC_E;

/**The desktop has been attached to a graphics layer (0xB0078000).*/
/** CNcomment:������ͼ���Ѿ��� 0xB0078000 */
#define HIGO_ERR_ALREADYBIND HIGO_DEF_ERR(HIGO_MOD_WINC, ERR_WINC_ALREADYBIND)

/**The z-order adjustment mode is invalid (0xB0078001).*/
/** CNcomment:��Ч��Z�������ʽ 0xB0078001 */
#define HIGO_ERR_INVZORDERTYPE HIGO_DEF_ERR(HIGO_MOD_WINC, ERR_WINC_INVZORDERTYPE)

/**The desktop is not refreshed (0xB0078002).*/
/** CNcomment:�����޸��� 0xB0078002 */
#define HIGO_ERR_NOUPDATE HIGO_DEF_ERR(HIGO_MOD_WINC, ERR_WINC_NOUPDATE)

/**The desktop is not refreshed (0xB0078003).*/
/** CNcomment:�����޸��� 0xB0078003 */
#define HIGO_ERR_INVPF HIGO_DEF_ERR(HIGO_MOD_WINC, ERR_WINC_INVPF)

/**The desktop is not refreshed (0xB0078004).*/
/** CNcomment:�����޸��� 0xB0078004 */
#define HIGO_ERR_INVTREE HIGO_DEF_ERR(HIGO_MOD_WINC, ERR_WINC_INVTREE)

/**The window already be set mode (0xB0078005).*/
/** CNcomment:�Ѿ��趨�����ڴ�ģʽ 0xB0078005 */
#define HIGO_ERR_ALREADYSETMODE HIGO_DEF_ERR(HIGO_MOD_WINC, ERR_WINC_ALREADYSETMODE)

/**Error codes of the HiGo surface module*/
/** CNcomment:HiGo Cursorģ������� */
typedef enum
{
    ERR_CURSOR_INVHOTSPOT = 0,
    ERR_CURSOR_NOCURSORINFO,
    ERR_CURSOR_BUTT
} HIGO_CURSOR_ERR_E;

/**The hot spot coordinate of the cursor is invalid (0xB0088000).*/
/** CNcomment:��Ч��cursor�ȵ����� 0xB0088000 */
#define HIGO_ERR_INVHOTSPOT  HIGO_DEF_ERR(HIGO_MOD_CURSOR, ERR_CURSOR_INVHOTSPOT)

/**The cursor information is not set (0xB0088001).*/
/** CNcomment:û������cursor��Ϣ 0xB0088001 */
#define HIGO_ERR_NOCURSORINF HIGO_DEF_ERR(HIGO_MOD_CURSOR, ERR_CURSOR_NOCURSORINFO)

/** @} */  /*! <!-- Macro Definition end */



/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif /* __HI_GO_ERRNO_H__ */
