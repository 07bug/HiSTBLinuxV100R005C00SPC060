//==============================================================================
//           Copyright (C), 2008-2013, Hisilicon Tech. Co., Ltd.
//==============================================================================
//  �ļ�����: imedia_typedef.h
//  �ļ�����: ���ļ�����iMedia�������㷨����������͵��ض�����Ϣ��
//            Ϊ�˸�������Ŀ�顢��Ʒ�ߵĶ��岻��ͻ��ͳһ���ṩ����Ƶķ�ʽ����
//            �ض������ݽ��м��أ��������TI��LSI��ARM��HiFiƽ̨ʹ��
//  �޸ļ�¼: ���ļ�β
//==============================================================================

#ifndef _IMEDIA_TYPEDEF_
#define _IMEDIA_TYPEDEF_

#ifdef __cplusplus
extern "C" {
#endif

// ʹ��uniDSP�궨���ֹ�ظ���������ı��뱨��
#ifndef UNI_TYPE_DEF
#define UNI_TYPE_DEF

// 8λ���������ض���
typedef unsigned char         IMEDIA_UINT8;
typedef signed char           IMEDIA_INT8;
typedef char                  IMEDIA_CHAR;   // 8λ���������ض���,��uniDSPͷ�ļ�����

// 16λ���������ض���
typedef unsigned short        IMEDIA_UINT16;
typedef signed short          IMEDIA_INT16;

// 32λ���������ض���
typedef unsigned int          IMEDIA_UINT32;
typedef signed int            IMEDIA_INT32;
typedef unsigned int          IMEDIA_BOOL;  // 32λ���������ض���,��uniDSPͷ�ļ�����

// 32λ���������ض���, ��uniDSPƽ̨ͷ�ļ�����
typedef unsigned int          IMEDIA_UINTPTR;
typedef signed int            IMEDIA_INTPTR;

// �������������ض���: ��uniDSPƽ̨ͷ�ļ�����
typedef float                 IMEDIA_FLOAT;
typedef double                IMEDIA_DOUBLE;

// �������������ض���: ��VTC��VQE�㷨���ڶ���һ��
typedef float                 IMEDIA_FLOAT32;
typedef double                IMEDIA_FLOAT64;

// VOID�ض��壬��uniDSPƽ̨ͷ�ļ�����
#ifndef     IMEDIA_VOID
#define     IMEDIA_VOID              void
#endif

//==============================================================================
// ARMƽ̨64λ���������ض���
//==============================================================================
#ifdef __arm__
typedef unsigned long long    IMEDIA_UINT64;
typedef long long             IMEDIA_INT64;
#endif

//==============================================================================
// MSVCƽ̨64λ���������ض���
//==============================================================================
#if defined(_MSC_VER)
typedef __int64               IMEDIA_INT64;
#endif

#if defined(_MSC_VER)
typedef unsigned __int64      IMEDIA_UINT64;
#endif

//==============================================================================
// TIƽ̨40λ��64λ���������ض���
//==============================================================================
#ifdef __COMPILER_VERSION__
// 40λ���������ض���
#ifdef __TI_40BIT_LONG__               // COFF ��ʽ��long ��λ����40λ, ELF ��ʽ��
                                       // long ��λ����32λ 
typedef unsigned long         IMEDIA_UINT40;
typedef long                  IMEDIA_INT40;
#else                                  // ELF ��ʽ��40λ����
typedef unsigned __int40_t    IMEDIA_UINT40;
typedef  __int40_t            IMEDIA_INT40;
#endif

#if (__COMPILER_VERSION__ < 5000000)
// CBSC TIƽ̨�Ͱ汾������(4.32,����5.0�汾)��֧��long long����
#else
typedef unsigned long long    IMEDIA_UINT64;
typedef long long             IMEDIA_INT64;
#endif
#endif

//==============================================================================
// HiFiƽ̨64λ���������ض���
//==============================================================================
#ifdef __XTENSA__
typedef unsigned long long    IMEDIA_UINT64;
typedef long long             IMEDIA_INT64;
#endif

#endif    // end of #ifndef UNI_TYPE_DEF

#ifndef     IMEDIA_NULL
#define     IMEDIA_NULL              ((IMEDIA_VOID *)0)
#endif

#ifdef __cplusplus
}
#endif

#endif    // end of #ifndef _IMEDIA_TYPEDEF_

//==============================================================================
// �޸ļ�¼:
// 2011-5-13 11:45:34   �����ļ�
//                      �޸���: �����ģ�����
// 2011-5-30 14:58:18   �޸ĺ�__TI_COMPILER_VERSION__Ϊ__COMPILER_VERSION__,���
//                      4.32��������INT40�޶���Ĵ���
//                      �޸���: ��ܣ�����
// 2012-4-20 16:50:06   C6000 �� ELF��ʽ��long��Ϊ32λ�������ͣ�������ELF��ʽ��
//                      �޸�Ϊ __int40_t
//                      �޸���: ������
// 2013-6-24 13:54:41   ���vc��XTENSA�汾long long����  
//                      �޸���: ʩ��
// 2013-7-18 16:05:02   ����TIƽCOFF ��ʽ��long ��λ����40λ, ELF ��ʽ��long ��
//                      λ����32λͬ���޸�
//                      �޸���: ʩ��
// 2013-7-19 10:20:40   ͳһARM��HiFiƽ̨���ļ���ʽ
//                      �޸���: ����
// 2014-4-29 10:20:40   ���IMEDIA_ǰ׺������ڸ�ƽ̨����ʱ���벻ͨ������
//                      �޸���: �ܺ�ΰ
//==============================================================================
