/*********************************************************************************
*
*  Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
*  This program is confidential and proprietary to Hisilicon Technologies Co., Ltd.
*  (Hisilicon), and may not be copied, reproduced, modified, disclosed to
*  others, published or used, in whole or in part, without the express prior
*  written permission of Hisilicon.
*
***********************************************************************************/

/*******************************************************************************/

#ifndef __LOADERDB_H__
#define __LOADERDB_H__

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define STBINFO  "deviceinfo"

typedef unsigned short HI_U16;
typedef unsigned char  HI_U8;
typedef unsigned char  HI_UCHAR;
typedef unsigned int   HI_U32;

typedef short        HI_S16;
typedef char         HI_S8;
typedef char         HI_CHAR;
typedef int          HI_S32;
typedef void         HI_VOID;
typedef unsigned int HI_HANDLE;

typedef enum {
    HI_FALSE    = 0,
    HI_TRUE     = 1,
} HI_BOOL;

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2*/
/** @{ */  /** <!- [Data structure of loader upgrade parameter area] */

/**
 \brief attention \n
Serial number information includes the hardware version and vendor ID to be verified during the upgrade. Different service provider and vendors have different serial numbers for STBs.\n
CNcomment:���кź�������ʱ��Ҫ�Ƚϵ�Ӳ���汾��,���̱�š���ͬ����Ӫ�̺ͳ����в�ͬ�Ĺ������е����кš�\n CNend
A serial number contains the following information:\n
          External serial number, such as  00000003-00000001-1d000021      \n
          External serial number is in the following format:\n
          AAAAAAAA-BBBBBBBB-CCCCCCCC ....\n
          AAAAAAAA 	Terminal product vendor authentication number\n
          BBBBBBBB 	Hardware version\n
          CCCCCCCC 	Hareware serial number.\n

CNcomment:���кŵĸ�ʽ�������: \n
          �������к���:  00000003-00000001-1d000021�� \n
          �������кŸ�ʽ����: \n
          AAAAAAAA-BBBBBBBB-CCCCCCCC ....\n
          AAAAAAAA 	�ն˲�Ʒ����������֤��š� \n
          BBBBBBBB 	Ӳ���汾�š�\n
          CCCCCCCC 	Ӳ��ϵ�кš�\n CNend
 \param[out] pstStbinfo  STB serial number information. The memory is allocated externally.CNcomment:���������к���Ϣ.�ⲿ�����ڴ档 CNend
 \retval ::HI_SUCCESS Success. CNcomment:�ɹ��� CNend
 \retval ::HI_FAILURE  This API fails to be called. CNcomment:APIϵͳ����ʧ�ܡ� CNend
 \see ::HI_LOADER_STB_INFO_S \n
For details, see the definition in HI_LOADER_STB_INFO_S.
CNcomment:��ϸ��Ϣ,��ο�HI_LOADER_STB_INFO_S���塣 CNend
 */
/**STB infor */
typedef struct hiLOADER_STBINFO_S
{
    HI_U32 u32OUI; /**< Vendor ID *//**<CNcomment: ����id */
    HI_U32 u32AreaCode; /**< Region code *//**<CNcomment: ������*/
    HI_U32 u32HWVersion; /**< Hardware version *//**<CNcomment: Ӳ���汾�� */
    HI_U32 u32HWSerialNum; /**< Hardware serial number *//**<CNcomment: Ӳ��ϵ�к�*/
} HI_LOADER_STB_INFO_S;

#ifdef __cplusplus
 #if __cplusplus
}

 #endif
#endif

#endif

