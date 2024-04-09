//==============================================================================
//           Copyright (C), 2008-2014, Hisilicon Tech. Co., Ltd.
//==============================================================================
//  �ļ�����: imedia_asrc_api.h
//  �ļ�����: ����ӿ�ͷ�ļ�
//
//  �ṹ���б�:
//      iMedia_ASRC_STRU_MEM_CONFIG  -- �ڴ����ýṹ��
//      iMedia_ASRC_STRU_PARAMS      -- �������ýṹ��
//      iMedia_ASRC_STRU_MEM_SIZE    -- �ڴ��С�ṹ��
//      iMedia_ASRC_STRU_Version     -- �汾��Ϣ�ṹ��
//      iMedia_ASRC_STRU_DATA        -- I/O���ݽṹ��
//
//  �����б�:
//      iMedia_ASRC_GetSize()        -- ��ȡͨ��������С
//      iMedia_ASRC_Init()           -- ��ʼ���㷨ʵ��
//      iMedia_ASRC_Flush()          -- ���ͨ����ʷֵ
//      iMedia_ASRC_Apply()          -- �㷨����Ӧ��
//      iMedia_ASRC_GetParams()      -- ��ȡ�㷨��������
//      iMedia_ASRC_GetVersion()     -- ��ȡ�㷨��汾��Ϣ��
//                                      �������ñ������汾����ʱ��Ͱ汾��
//
//  �޸ļ�¼: ���ļ�β
//==============================================================================
#ifndef _IMEDIA_ASRC_API_H_
#define _IMEDIA_ASRC_API_H_

#include "imedia_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
//     �����붨����Ϣ
//==============================================================================
#define IMEDIA_ASRC_EOK                     (0)          //�����ɹ�
#define IMEDIA_ASRC_INV_HANDLE              (-1)         //��Ч������㷨���ΪNULL
#define IMEDIA_ASRC_INV_BASE                (-2)         //��Ч�Ļ���ַ������ַΪNULL
#define IMEDIA_ASRC_INV_MEM_SIZE            (-3)         //�洢������С��Ҫ�󳤶�
#define IMEDIA_ASRC_INV_MEMSIZE_PST         (-4)         //�ڴ�ߴ�ṹ��ָ��Ϊ��
#define IMEDIA_ASRC_INV_MEMCFG_PST          (-5)         //�������ýṹ��ָ��Ϊ��
#define IMEDIA_ASRC_INV_PARAMS              (-6)         //���ýṹ��ָ��ΪNULL
#define IMEDIA_ASRC_INV_SAMPLERATE          (-7)         //��Ч�Ĳ�����
#define IMEDIA_ASRC_INV_CHANNELS            (-8)         //��Ч��������
#define IMEDIA_ASRC_INV_INBITS              (-9)         //��Ч������λ��
#define IMEDIA_ASRC_INV_DATASIZE_IN         (-10)        //��Ч���������ݳ���
#define IMEDIA_ASRC_INV_DATA                (-11)        //���ݽṹ��ָ��Ϊ��
#define IMEDIA_ASRC_INV_UNINITIED           (-12)        //ͨ������δ��ʼ��
#define IMEDIA_ASRC_INV_INBUFF              (-13)        //���뻺����Ϊ��
#define IMEDIA_ASRC_INV_OUTBUFF             (-14)        //���������Ϊ��
#define IMEDIA_ASRC_INV_INBUFF_ADDRESS      (-15)        //��Ч�����뻺������ַ
#define IMEDIA_ASRC_INV_OUTBUFF_ADDRESS     (-16)        //��Ч�������������ַ
#define IMEDIA_ASRC_INV_VERSION             (-17)        //��Ч�汾��Ϣ�ṹ��ָ��

//==============================================================================
//     ö�����Ͷ���
//==============================================================================
//��������Χ
typedef enum
{
    IMEDIA_ASRC_MONO    = 1,                             //������
    IMEDIA_ASRC_STEREO  = 2                              //˫����,�����������ݽ�����
}iMedia_ASRC_CHANNELS;

//�������λ��Χ
typedef enum
{
    IMEDIA_ASRC_16BITS  = 16                             //λ��16bit
}iMedia_ASRC_INBITS;

//�����ʷ�Χ
typedef enum
{
    IMEDIA_ASRC_44100HZ = 44100,                         //������44100Hz
    IMEDIA_ASRC_48000HZ = 48000                          //������48000Hz
}iMedia_ASRC_SAMPLERATE;

//==============================================================================
//     �����������Ͷ�����Ϣ
//==============================================================================

//�ڴ����ýṹ��
typedef struct tagiMedia_ASRC_STRU_MEM_CONFIG
{
    IMEDIA_INT32 iInSampleRate;                                 //�������ݲ�����
    IMEDIA_INT32 iOutSampleRate;                                //������ݲ�����
    IMEDIA_INT32 iInBits;                                       //����λ��
    IMEDIA_INT32 iChannels;                                     //������
}iMedia_ASRC_STRU_MEM_CONFIG, *iMedia_ASRC_PST_MEM_CONFIG;

//�������ýṹ��
typedef struct tagiMedia_ASRC_STRU_PARAMS
{
    IMEDIA_INT32 iInSampleRate;                                 //�������ݲ�����
    IMEDIA_INT32 iOutSampleRate;                                //������ݲ�����
    IMEDIA_INT32 iInBits;                                       //����λ��
    IMEDIA_INT32 iChannels;                                     //������
    IMEDIA_INT32 iReserve[4];                                   //������
}iMedia_ASRC_STRU_PARAMS, *iMedia_ASRC_PST_PARAMS;

//�ڴ��С�ṹ��
typedef struct tagiMedia_ASRC_STRU_MEM_SIZE
{
    IMEDIA_UINT32 uiStrSize;                                    //ͨ��������С����λΪ�ֽ�
}iMedia_ASRC_STRU_MEM_SIZE, *iMedia_ASRC_PST_MEM_SIZE;

//�汾��Ϣ�ṹ��
#define IMEDIA_ASRC_VERSION_MSG_VERLEN        (64)              //�㷨��汾��Ϣ�ַ�������
typedef struct tagASRC_STRU_VERSION
{
    IMEDIA_UINT8 ucCgtVersion[IMEDIA_ASRC_VERSION_MSG_VERLEN];  //�������汾��
    IMEDIA_UINT8 ucReleaseVer[IMEDIA_ASRC_VERSION_MSG_VERLEN];  //�㷨��汾��
    IMEDIA_UINT8 ucReleaseTime[IMEDIA_ASRC_VERSION_MSG_VERLEN]; //��������
}iMedia_ASRC_STRU_VERSION, *iMedia_ASRC_PST_VERSION;

//I/O���ݽṹ��
typedef struct tagASRC_STRU_DATA
{
    IMEDIA_VOID  *piInData;                                     //�������ݵ�ַ��������λ���ֽ�������
    IMEDIA_VOID  *piOutData;                                    //������ݵ�ַ��������λ���ֽ�������
    IMEDIA_INT32 iInSize;                                       //��������������ȡʵʱÿ֡����������������������Χ(0,1024]��˫������Χ(0,2048]
    IMEDIA_INT32 iOutSize;                                      //�������������ȡʵʱÿ֡����������������������(0,1120),˫�������(0,2240)
}iMedia_ASRC_STRU_DATA, *iMedia_ASRC_PST_DATA;

//==============================================================================
//     ��������
//==============================================================================

//==============================================================================
// ��������: iMedia_ASRC_GetSize
// ��������: ��ȡͨ����С
// �������:
//     pstConf     -- �ڴ����ýṹ��
// �������:
//     pstMemSize  -- ͨ����С�ṹ��
// ���ز���:
//     ret         -- ���������� IMEDIA_ASRC_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_ASRC_GetSize(iMedia_ASRC_PST_MEM_SIZE pstMemSize, iMedia_ASRC_PST_MEM_CONFIG pstConf);

//==============================================================================
// ��������: iMedia_ASRC_Init
// ��������: ��ʼ���㷨ʵ��(ͨ������)������������
// �������:
//     ppHandle    -- ������
//     pMemBase    -- ͨ��������ʼ��ַ
//     uiMemSize   -- ͨ�������ռ��С
//     pstParams   -- �������ýṹ��
// �������:
//     ppHandle    -- ������
// ���ز���:
//     ret         -- ���������� IMEDIA_ASRC_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_ASRC_Init(IMEDIA_VOID **ppHandle,  const IMEDIA_VOID *pMemBase, IMEDIA_UINT32 uiMemSize, iMedia_ASRC_PST_PARAMS pstParams);

//==============================================================================
// ��������: iMedia_ASRC_Flush
// ��������: ����ͨ����ʼ�����������ͨ����ʷֵ
// �������:
//     pHandle   -- ������
// �������:
//     pHandle   -- ������
// ���ز���:
//     ret       -- ���������� IMEDIA_ASRC_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_ASRC_Flush(IMEDIA_VOID *pHandle);

//==============================================================================
// ��������: iMedia_ASRC_Apply
// ��������: �㷨����Ӧ��
// �������:
//     pHandle   -- ������
//     pstDatas  -- I/0���ݽṹ��ָ��
// �������:
//     pstDatas
// ���ز���:
//     ret       -- ���������� IMEDIA_ASRC_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_ASRC_Apply(IMEDIA_VOID *pHandle, iMedia_ASRC_PST_DATA pstDatas);

//==============================================================================
// ��������: iMedia_ASRC_GetParams
// ��������: ��ȡ����
// �������:
//     pHandle     -- ������
// �������:
//     pstParams   -- �������ýṹ��
// ���ز���:
//     ret         -- ���������� IMEDIA_ASRC_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_ASRC_GetParams(IMEDIA_VOID *pHandle,  iMedia_ASRC_PST_PARAMS pstParams);

//==============================================================================
// ��������: iMedia_ASRC_GetVersion
// ��������: ��ȡ�㷨��汾��Ϣ���������ñ������汾������ʱ��Ͱ汾��
// �������:
//     ppVersion    -- �汾��Ϣ�ṹ����
// �������:
//     ppVersion    -- �汾��Ϣ�ṹ����
// ���ز���:
//     ret          -- ���������� IMEDIA_ASRC_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_ASRC_GetVersion(iMedia_ASRC_PST_VERSION *ppVersion);

#ifdef __cplusplus
}
#endif

#endif


//==============================================================================
// �޸ļ�¼:
// 2014-1-29 11:45:34   �����ļ�
//                      �޸���: ����/sdk
// 2014-12-19 14:10:11  �޸��ļ�
//                      �޸��ˣ�����ϼ/sdk
//==============================================================================
