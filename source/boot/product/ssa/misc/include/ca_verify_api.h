/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : ca_verify_api.h
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __CA_VERIFY_API_H__
#define __CA_VERIFY_API_H__

#include "hi_type.h"
#include "ca_verify_def.h"

#define ADVCA_MODE    0
#define COMMON_MODE     1


/**
\brief  Verify partition signature by partitionname, signature partitionname and its offset
CNcomment:����flash��������ǩ����������ƫ������У��flash����
\param[in] u32MemAddr   RAM address for image               CNcomment:pPartionName  ���image���ڴ��ַ
\param[in] pPartitionName    Flash partion name             CNcomment:pPartionName  flash ������
\param[in] PartitionSignName Flash signature partion name   CNcomment:PartitionSignName  ǩ��������
\param[in] offset            The offset of sign header      CNcomment:offset  ǩ��ͷ����ƫ����
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CA_Verify_Signature(HI_U32 u32MemAddr, HI_CHAR *pPartitionName, HI_CHAR *PartitionSignName, HI_U32 offset);

/*
    Choose randomly partial section to verify partition.
*/
HI_S32 HI_CA_Verify_Signature_Ex(HI_U32 u32MemAddr,HI_CHAR *PartitionImagenName, HI_CHAR *PartitionSignName, HI_U32 offset);



/**
\brief  verify bootargs parameter area
CNcomment:У��bootargs����flash����
\attention \n
\param[in] u32MemAddr         RAM address for image       CNcomment:pPartionName  ���image���ڴ��ַ
\param[in] u32ParaPartionAddr Bootargs partion address    CNcomment:u32ParaPartionAddr  bootargs������ַ
\param[in] u32ParaParitonSize Bootargs partion size       CNcomment:u32ParaParitonSize  bootargs������С
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CA_Verify_BootPara(HI_U32 u32MemAddr, HI_U32 u32ParaPartionAddr, HI_U32 u32ParaParitonSize);


/**
\brief  Get advaced CA image header structure by flash partition name
CNcomment:ͨ��flash���������ֻ�ȡ�߰�imageͷ����Ϣ
\attention \n
\param[in] pPartionName Flash partion name                CNcomment:pPartionName  flash ������
\param[in] pstAuthInfo  Authentication configure infor    CNcomment:pstAuthInfo  У��������Ϣ
\param[out] pstImgInfo  Image header info                 CNcomment:pstAuthInfo  ����ͷ����Ϣ
\param[out] pIsEncrypt  Is the image encrypted            CNcomment:ImgInDDRAddress �����Ƿ����
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CA_GetAdvcaImgInfoByPartName(HI_U8* pPartionName, HI_CA_AuthInfo_S *pstAuthInfo, HI_CAImgHead_S* pstImgInfo, HI_BOOL *pIsEncrypt);


/**
\brief  Get advaced CA image header structure by flash partition addr
CNcomment:ͨ��flash�����ĵ�ַ��ȡ�߰�imageͷ����Ϣ
\attention \n
\param[in] PartionAddr Flash partion address              CNcomment:pPartionName  flash ������ַ
\param[in] pstAuthInfo  Authentication configure infor    CNcomment:pstAuthInfo  У��������Ϣ
\param[out] pstImgInfo  Image header info                 CNcomment:pstAuthInfo  ����ͷ����Ϣ
\param[out] pIsEncrypt  Is the image encrypted            CNcomment:ImgInDDRAddress �����Ƿ����
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CA_GetAdvcaImgInfoByAddr(HI_U32 PartionAddr, HI_CA_AuthInfo_S *pstAuthInfo, HI_CAImgHead_S* pstImgInfo, HI_BOOL *pIsEncrypt);


/**
\brief  In advca mode, verify flash contents by partion name
CNcomment:�߰�ģʽ�¸���flash������У��flash����
\attention \n
����Ǽ��ܴ洢��flash�ľ��񣬻ᱻ�Ƚ��ܣ�Ȼ��У��ǩ������������ľ���ֱ��У��ǩ����
\param[in] pPartionName Flash partion name    CNcomment:pPartionName  flash ������
\param[in] u32RamAddr   RAM address for image CNcomment:pPartionName  ���image���ڴ��ַ
\param[in] pstAuthInfo  Authentication configure infor    CNcomment:pstAuthInfo  У��������Ϣ
\param[out] pu32CodeAddr After Authenticate finished ,image address in DDR CNcomment:ImgInDDRAddress У����ɺ󣬿��þ�����DDR�е�λ��
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CA_AdvcaVerifyByPartName(HI_U8* pPartionName,HI_U32 u32RamAddr, HI_CA_AuthInfo_S *pstAuthInfo, HI_U32 *pu32CodeAddr);


/**
\brief  In advca mode, verify flash contents by partion addr
CNcomment:�߰�ģʽ�¸���flash������ַУ��flash����
\attention \n
����Ǽ��ܴ洢��flash�ľ��񣬻ᱻ�Ƚ��ܣ�Ȼ��У��ǩ������������ľ���ֱ��У��ǩ����
\param[in] pPartionName Flash partion address CNcomment:pPartionName  flash ����addr
\param[in] u32RamAddr   RAM address for image CNcomment:pPartionName  ���image���ڴ��ַ
\param[in] pstAuthInfo  Authentication configure infor    CNcomment:pstAuthInfo  У��������Ϣ
\param[out] pu32CodeAddr After Authenticate finished ,image address in DDR CNcomment:ImgInDDRAddress У����ɺ󣬿��þ�����DDR�е�λ��
\retval ::0 Success CNcomment:0                  �ɹ�
\retval ::-1 Faliure CNcomment:-1                ʧ��
\see \n
None CNcomment:��
*/
HI_S32 HI_CA_AdvcaVerifyByPartAddr(HI_U32 PartitionAddr,HI_U32 u32RamAddr, HI_CA_AuthInfo_S *pstAuthInfo,HI_U32 *pu32CodeAddr);



#endif /*__CA_VERIFY_API_H__*/

