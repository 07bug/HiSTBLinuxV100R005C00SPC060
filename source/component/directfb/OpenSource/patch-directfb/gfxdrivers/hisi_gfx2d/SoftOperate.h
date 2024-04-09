
#ifndef SGO_SOFTOPERATE_H
#define SGO_SOFTOPERATE_H


#include "hi_type.h"
#include "hi_tde_type.h"
#include "hi_tde_api.h"

typedef enum _SGO_RETVAL_TYPE_E
{

	SGO_SUCCESS = 0,                                     
	SGO_NULLADDR_SURFACE,                         
	SGO_NOTSUPPORT_COLORFORMAT,       
	SGO_NULLADDR_SURBUFFER ,                
	SGO_TOOLARGE_REGION,
	SGO_ERR_ALUCMD,                 
	SGO_ERR_COLORKEYMODE	,
	SGO_ERR_REGION,
	SGO_NOTSUPPORT_OPERATION
}SGO_RETVAL_TYPE_E;




/** 
\brief Fill rectangle CNcomment:�������
\attention \n
Support colorkey,alpha,ROP,Colorkey+ROP operation
CNcomment:����֧�ֲ�������colorkey��alpha��ROP��colorkey+ROP����ϲ���\

\param[in] pDstSurface  Dst surface     CNcomment:Ŀ��surface
\param[in] pRect  Fill region   CNcomment:�������
\param[in] u32FillColor  Fill color value   CNcomment:�����ɫ
\param[in] pBlitOpt operation config    CNcomment:��Ϸ�ʽ

\retval ::SGO_SUCCESS 
\retval ::
\see \n
none
CNcomment:��
*/
HI_S32 Hi_Soft_FillRect(TDE2_SURFACE_S* pDstSurface,  TDE2_RECT_S* pRect, HI_U32  u32FillColor, TDE2_OPT_S* pBlitOpt);



/** 
\brief 
Surface blit,support CSC(Color space change)
CNcomment:λ����ƣ��ڰ��ƹ����У�����ʵ��ɫ�ʿռ�ת����
\attention \n
CSC only supports YUV to RGB
Support colorkey,alpha,ROP,colorkey+ROP opreation
CNcomment:ɫ�ʿռ�ת����֧��YUV��RGBת�� \n
����֧�ֲ�������colorkey��alpha��ROP��colorkey+ROP����ϲ���\


\param[in] pSrcSurface  Src surface CNcomment:Դsurface
\param[in] pSrcRect Dst region,NULL specify surface size
                            CNcomment:���Ƶ�Դ����Ϊ�ձ�ʾ����Դsurface����
\param[in] pDstSurface  Dst surface     CNcomment:Ŀ��surface
\param[in] pDstRect Dst region,NULL specify surface size
                            CNcomment:���Ƶ�Ŀ������Ϊ�ձ�ʾ����Ŀ��surface����
\param[in]  pBlitOpt Operation config       CNcomment:��Ϸ�ʽ

\retval ::SGO_SUCCESS 
\retval ::
\see \n
none
CNcomment:��
*/
HI_S32 Hi_Soft_Blit( TDE2_SURFACE_S* pSrcSurface,  TDE2_RECT_S *pSrcRect,  TDE2_SURFACE_S* pDstSurface,  TDE2_RECT_S *pDstRect,  TDE2_OPT_S* pBlitOpt);


/** 
\brief 
Surface blit,support CSC(Color space change) and scale
CNcomment:λ����ƣ��ڰ��ƹ����У�����ʵ��ɫ�ʿռ�ת��,����
\attention \n
CSC only supports YUV to RGB
Support colorkey,alpha,ROP,colorkey+ROP opreation
CNcomment:ɫ�ʿռ�ת����֧��YUV��RGBת�� \n
����֧�ֲ�������colorkey��alpha��ROP��colorkey+ROP����ϲ���\


\param[in] pSrcSurface  Src surface CNcomment:Դsurface
\param[in] pSrcRect Dst region,NULL specify surface size
                            CNcomment:���Ƶ�Դ����Ϊ�ձ�ʾ����Դsurface����
\param[in] pDstSurface  Dst surface     CNcomment:Ŀ��surface
\param[in] pDstRect Dst region,NULL specify surface size
                            CNcomment:���Ƶ�Ŀ������Ϊ�ձ�ʾ����Ŀ��surface����
\param[in]  pBlitOpt Operation config       CNcomment:��Ϸ�ʽ

\retval ::SGO_SUCCESS 
\retval ::
\see \n
none
CNcomment:��
*/
HI_S32 Hi_Soft_StretchBlit( TDE2_SURFACE_S* pSrcSurface,  TDE2_RECT_S *pSrcRect,  TDE2_SURFACE_S* pDstSurface,  TDE2_RECT_S *pDstRect,   TDE2_OPT_S* pBlitOpt);


#endif
