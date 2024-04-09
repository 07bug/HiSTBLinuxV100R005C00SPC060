/******************************************************************************
*             Copyright 2009 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
******************************************************************************
* FileName: hi_ref_errno.h
* Description:ϵͳ���õĴ����붨��
*
* History:
* Version  Date        Author                               DefectNum  Description
* 1.0      2009/03/19  Hisilicon STB  software group  NULL       Create this file.
******************************************************************************/

#ifndef __HI_REF_ERRNO_H__
#define __HI_REF_ERRNO_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/***************************** Type Definition *******************************/
typedef HI_S32                  HI_ERRNO;

/***************************** Macro Definition ******************************/

/*************************************************************************
  ����������
*************************************************************************/

#define HI_ERRNO_COMMON_BASE    0
#define HI_ERRNO_COMMON_COUNT   0x100

//#define HI_FAILURE              (HI_ERRNO)(-1L)                       /* ��������ʧ�� */
//#define HI_SUCCESS              (HI_ERRNO)0                           /* �����ɹ���� */
#define HI_EUNKNOWN             (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 1)  /* ����ԭ��δ֪��ȷ���Ѿ������ǲ����ж������ԭ�� */
#define HI_EOTHER               (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 2)  /* ��������֪������ԭ�������Թ��� */
#define HI_EINTER               (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 3)  /* �ڲ����������ڲ��������Դ���ĳЩ�ڴ������CPU�Բ��I/O����ѧ����������ȵ� */
#define HI_EVERSION             (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 4)  /* �汾���� */
#define HI_EPAERM               (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 5)  /* ��֧�ֵĲ���/����/���ԣ����������汾����δ���İ汾����������Ʒ����֧�� */
#define HI_EINVAL               (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 6)  /* �������󣬰������������������ò����������ò�����һ�»��г�ͻ�����ʵ��ı�š�ͨ���š��豸�š���ָ�롢��ַ��������ȵ� */
#define HI_ENOTINIT             (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 7)  /* û�г�ʼ����ĳЩ�����������Ƚ��г�ʼ������ܽ��У�����δ���� */
#define HI_ENOTREADY            (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 8)  /* û��׼���ã�ĳЩ���������ھ߱�һ����������ܽ��У�������Ҫ�Ļ�������ȷ������ȱ���������Դ */
#define HI_ENORES               (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 9)  /* û����Դ�����������ڴ�ʧ�ܡ�û�п��л�������û�п��ж˿ڡ�û�п���ͨ���� */
#define HI_EEXIST               (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0xA)/* ��Դ�Ѵ��ڣ���������½�����Դ�Ѿ����ڣ������������� */
#define HI_ELOST                (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0xB) /* ��Դ�����ڣ�������ĳ����Դ����ַ���Ự������ */
#define HI_ENOOP                (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0xC) /* ��Դ���ɲ������������𻵲���ʹ�á�У�����δ����Ԥ�ڵ����á��豸�����ݵȵ� */
#define HI_EBUSY                (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0xD) /* ��Դ��æµ�����类���� */
#define HI_EIDLE                (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0xE) /* ��Դ������ */
#define HI_EFULL                (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0xF) /* ����ĳ���������Ѿ������� */
#define HI_EEMPTY               (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0x10) /* �գ�ĳ���������ǿյ� */
#define HI_EUNDERFLOW           (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0x11) /* ���磬ĳ�������е������Ѿ��½�������ˮ��֮�� */
#define HI_EOVERFLOW            (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0x12) /* ���磬ĳ�������е���������������ˮ��֮�� */
#define HI_EACCES               (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0x13) /* Ȩ�޴�������û��Ȩ�ޡ��������ȵ� */
#define HI_EINTR                (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0x14) /* ����δ��ɣ��Ѿ��ж� */
#define HI_ECONTINUE            (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0x15) /* ����δ��ɣ����ڼ��� */
#define HI_EOVER                (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0x16) /* ������ɣ���û�к����Ĳ������� */
#define HI_ERRNO_COMMON_BUTTOM  (HI_ERRNO)(HI_ERRNO_COMMON_BASE + 0x17) /* �Ѷ���Ĵ���Ÿ��� */

/*************************************************************************
  ģ���Զ���������
*************************************************************************/
#define HI_ERRNO_BASE           (HI_ERRNO)(HI_ERRNO_COMMON_BASE + HI_ERRNO_COMMON_COUNT)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_REF_ERRNO_H__ */
