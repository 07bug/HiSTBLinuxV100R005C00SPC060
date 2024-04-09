//==============================================================================
//           Copyright (C), 2008-2014, Hisilicon Tech. Co., Ltd.
//==============================================================================
//  �ļ�����: imeida_peq_api.h
//  �ļ�����: ���ļ�����PEQ�㷨��ĸ��ṹ�嶨����Ϣ�͹��ܺ�����������Ϣ
//            ��ʹ���㷨��ʱ��Ҫ�������ļ�
//
//  �ṹ���б�:
//      iMedia_PEQ_STRU_MEM_CONFIG  -- PEQ�㷨�ڴ����ýṹ��
//      iMedia_PEQ_STRU_MEM_SIZE    -- PEQ�㷨�ڴ��С�ṹ��
//      iMedia_PEQ_STRU_VERSION     -- PEQ�㷨�汾��Ϣ�ṹ��
//      iMedia_PEQ_STRU_PARAMS      -- PEQ�㷨�������ýṹ��
//
//  �����б�:
//      iMedia_PEQ_GetSize()        -- ��ȡ�ڴ��С
//      iMedia_PEQ_Init()           -- ��ʼ���㷨ʵ��(ͨ������)
//      iMedia_PEQ_Apply()          -- �㷨����Ӧ��
//      iMedia_PEQ_SetParams()      -- �����㷨��������
//      iMedia_PEQ_GetParams()      -- ��ȡ�㷨��������
//      iMedia_PEQ_GetVersion()     -- ��ȡ�㷨��汾��Ϣ���������ñ������汾��
//                                     ����ʱ��Ͱ汾��
//
//  �޸ļ�¼: ���ļ�β
//==============================================================================
#ifndef _IMEDIA_PEQ_API_H_
#define _IMEDIA_PEQ_API_H_

#include "imedia_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif // __cplusplus

//==============================================================================
//     ���������궨��
//==============================================================================
#define    IMEDIA_PEQ_FRAME_LENGTH_S             (256)   // ������֡��
#define    IMEDIA_PEQ_SAMPLE_48K                 (48000) // ������
#define    IMEDIA_PEQ_BAND_NUM_MAX               (10)    // ���Ƶ����

//==============================================================================
//     �����붨����Ϣ
//==============================================================================
// BEGIN: modified by y00278990 20141120 ���ⵥ: DTS2014112004982
#define    IMEDIA_PEQ_EOK                        (0)     // �����ɹ�������
#define    IMEDIA_PEQ_INV_INIT_PPHANDLE          (-1)    // Init�ӿ�����Ч���
#define    IMEDIA_PEQ_INV_INIT_BASE              (-2)    // Init�ӿ�����Ч�Ĵ洢������
#define    IMEDIA_PEQ_INV_INIT_MEM_SIZE          (-3)    // Init�ӿ��д洢����������С��Ҫ��ĳ���
#define    IMEDIA_PEQ_INV_INIT_PST_PARAMS        (-4)    // Init�ӿ������ò����ṹ��ָ��Ϊ��
#define    IMEDIA_PEQ_INV_CHECK_BAND_NUM         (-5)    // ���õĶ���������Χ
#define    IMEDIA_PEQ_INV_CHECK_FILTERTYPE       (-6)    // ���õ��˲������ͳ�����Χ
#define    IMEDIA_PEQ_INV_CHECK_CUTOFF           (-7)    // ���õ�����Ƶ�����ô���
#define    IMEDIA_PEQ_INV_CHECK_Q                (-8)    // ���õ�Ʒ�����ӳ�����Χ
#define    IMEDIA_PEQ_INV_CHECK_GAIN             (-9)    // ���õ�����ֵ������Χ
#define    IMEDIA_PEQ_INV_APPLY_HANDLE           (-10)   // Apply�ӿ���ͨ������ָ��Ϊ��
#define    IMEDIA_PEQ_INV_APPLY_INBUF            (-11)   // Apply�ӿ����������ݵ�ַΪ��
#define    IMEDIA_PEQ_INV_APPLY_OUTBUF           (-12)   // Apply�ӿ���������ݵ�ַΪ��
#define    IMEDIA_PEQ_INV_APPLY_UNINITIED        (-13)   // Apply�ӿ���ͨ��δ��ʼ��
#define    IMEDIA_PEQ_INV_SETPARAMS_HANDLE       (-14)   // �������ýӿ��о��Ϊ��
#define    IMEDIA_PEQ_INV_SETPARAMS_PST_PARAMS   (-15)   // �������ýӿ��в����ṹ��ָ��Ϊ��
#define    IMEDIA_PEQ_INV_SETPARAMS_UNINITIED    (-16)   // ����SetParams�ӿ�ǰû��Init
#define    IMEDIA_PEQ_INV_GETPARAMS_HANDLE       (-17)   // ������ȡ�ӿ��о��Ϊ��
#define    IMEDIA_PEQ_INV_GETPARAMS_PST_PARAMS   (-18)   // ������ȡ�ӿ��н��ղ����ṹ��ָ��Ϊ��
#define    IMEDIA_PEQ_INV_GETPARAMS_UNINITIED    (-19)   // ����GetParams�ӿ�ǰû��Init
#define    IMEDIA_PEQ_INV_GETVERSION_PPVERSION   (-20)   // �汾��Ϣ�ӿ�������ָ��Ϊ��
#define    IMEDIA_PEQ_INV_GETSIZE_MEMSIZE_PST    (-21)   // ��Ч���ڴ��С�ṹ��ָ��
#define    IMEDIA_PEQ_INV_GETSIZE_MEMCFG_PST     (-22)   // ��Ч���ڴ����ýṹ��ָ��
#define    IMEDIA_PEQ_INV_GETSIZE_SAMPLE_RATE    (-23)   // ��Ч�Ĳ�����
// END: modified by y00278990 20141120 ���ⵥ: DTS2014112004982
//==============================================================================
//     �汾��Ϣ�ṹ��
//==============================================================================
// DSP����汾��Ϣ�ṹ��
typedef struct  tagPEQ_STRU_VERSION
{
    IMEDIA_INT8    ucCgtVersion[100];     // Code Generation Tools�汾��
    IMEDIA_INT8    ucReleaseVer[100];     // �㷨��汾��
    IMEDIA_INT8    ucReleaseTime[100];    // ��������
} iMedia_PEQ_STRU_VERSION, *iMedia_PEQ_PST_VERSION;

//==============================================================================
//     �˲���ö������
//==============================================================================
typedef enum
{
    PEQ_HP_FILTER = 0,  // ��ͨ�˲��� HP
    PEQ_LS_FILTER = 1,  // ��Ƶ����˲��� LS
    PEQ_PK_FILTER = 2,  // ��ֵ�˲��� PK
    PEQ_HS_FILTER = 3,  // ��Ƶ����˲��� HS
    PEQ_LP_FILTER = 4   // ��ͨ�˲��� LP
} iMedia_PEQ_Filter_Type;

//==============================================================================
//     PEQ���ڴ����ýṹ��
//==============================================================================
typedef struct tagPEQ_STRU_MEM_CONFIG
{
    IMEDIA_INT32  iSampleRate;                                    // ���ݲ�����
    IMEDIA_INT8   cReserve[4];                                    // ������
} iMedia_PEQ_STRU_MEM_CONFIG, *iMedia_PEQ_PST_MEM_CONFIG;

//==============================================================================
//     PEQ���ڴ��С�ṹ��
//==============================================================================
typedef struct tagPEQ_STRU_MEM_SIZE
{
    IMEDIA_UINT32   uiStrSize;                                    // ͨ��������С, ��λΪ�ֽ�
    IMEDIA_INT32    iInSize;                                      // ��Ч����
    IMEDIA_INT32    iOutSize;                                     // ��Ч����
} iMedia_PEQ_STRU_MEM_SIZE, *iMedia_PEQ_PST_MEM_SIZE;

//==============================================================================
//     PEQ�����ò������������ɶ�̬����
//==============================================================================
typedef struct tagPEQ_STRU_PARAMS
{
    IMEDIA_UINT8  filtertype[IMEDIA_PEQ_BAND_NUM_MAX]; // �˲�������
                                                       // ��Χ: [0: HP, 1: LS, 2: PK, 3: HS 4: LP]
    IMEDIA_UINT16 cutoff[IMEDIA_PEQ_BAND_NUM_MAX];     // ����Ƶ�ʣ���λHz
                                                       // ��Χ: HP and LS[20, 4000], PK[20, 22000], HS and LP[4000, 22000]
    IMEDIA_UINT16 q[IMEDIA_PEQ_BAND_NUM_MAX];          // Qֵ��*10���㣬��Χ: HS and LS[7, 10], PK[5, 100], �ߵ�ͨΪ7
                                                       // modified by y00278990 20141120 ���ⵥ: DTS2014112005541
    IMEDIA_INT16  gain[IMEDIA_PEQ_BAND_NUM_MAX];       // Ƶ������, *1000���꣬�ߵ�ͨ�˲�������Ϊ0dB���������͵��˲������淶Χ[-15000, 15000]dB
                                                       // modified by y00278990 20141120 ���ⵥ: DTS2014112005541
    IMEDIA_UINT32 uiBandNum;                           // Ƶ��������Χ(0, 10]
} iMedia_PEQ_STRU_PARAMS, *iMedia_PEQ_PST_PARAMS;

//==============================================================================
// ��������: iMedia_PEQ_GetSize
// ��������: ��ȡͨ����С
// �������:
//     pstConf     -- �ڴ����ýṹ��
// �������:
//     pstMemSize  -- ͨ����С�ṹ��
// ���ز���:
//     ret         -- ����������IMEDIA_PEQ_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_GetSize(iMedia_PEQ_PST_MEM_SIZE pstMemSize, iMedia_PEQ_PST_MEM_CONFIG pstConf);

//==============================================================================
// // ��������: iMedia_PEQ_Init
// ��������: ��ʼ���㷨ʵ��(ͨ������)������������
// �������:
//     ppHandle    -- ������
//     pMemBase    -- ͨ��������ʼ��ַ
//     uiMemSize   -- ͨ�������ռ��С
//     pstParams   -- PEQ�������ýṹ��ָ��
// �������:
//     ppHandle    -- ������
// ���ز���:
//     ret         -- ���������� IMEDIA_PEQ_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_Init(IMEDIA_VOID** ppHandle,
                             const IMEDIA_VOID* pMemBase,
                             IMEDIA_UINT32 uiMemSize,
                             const iMedia_PEQ_PST_PARAMS pstParams);

//==============================================================================
// ��������: iMedia_PEQ_Apply
// ��������: �㷨����Ӧ��(����һ֡512�㣬Լ5.33ms)
// �������:
//     pHandle    -- ������
//     psIn       -- �������ݻ�����ָ��
// �������:
//     psOut      -- ������ݻ�����ָ��
// ���ز���:
//     ret        -- ���������� IMEDIA_PEQ_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_Apply(IMEDIA_VOID* pHandle, const IMEDIA_INT16* psIn, IMEDIA_INT16* psOut);

//==============================================================================
// ��������: iMedia_PEQ_SetParams
// ��������: ��̬�������ýӿڣ��л���������ʱʹ�á�
//           ע��: �ýӿڽ��ǵ��Խӿڣ�ֻ���ڵ��Խ׶�ʹ�ã�����������ʹ�á�
// �������:
//     pHandle    -- ������
//     pstParams  -- �㷨�������ýṹ��ָ��
// �������:
//     pHandle    -- ������
// ���ز���:
//     ret        -- ���������� IMEDIA_PEQ_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_SetParams(IMEDIA_VOID* pHandle, const iMedia_PEQ_PST_PARAMS pstParams);

//==============================================================================
// ��������: iMedia_PEQ_GetParams
// ��������: ��̬�������ýӿڣ��л���������ʱʹ�á�
//           ע��: �ýӿڽ��ǵ��Խӿڣ�ֻ���ڵ��Խ׶�ʹ�ã�����������ʹ�á�
// �������:
//     pHandle   -- ������
//     pstParams -- �㷨�������ýṹ��ָ��
// �������:
//     pHandle   -- ������
// ���ز���:
//     ret       -- ���������� IMEDIA_PEQ_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_GetParams(const IMEDIA_VOID* pHandle, iMedia_PEQ_PST_PARAMS pstParams);

//==============================================================================
// ��������: iMedia_PEQ_GetVersion
// ��������: ��ȡ�㷨��汾��Ϣ���������ñ������汾������ʱ��Ͱ汾��
// �������:
//     ppVersion  -- �汾��Ϣ�ṹ����
// �������:
//     ppVersion  -- �汾��Ϣ�ṹ����
// ���ز���:
//     ret        -- ���������� IMEDIA_PEQ_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
IMEDIA_INT32 iMedia_PEQ_GetVersion(iMedia_PEQ_PST_VERSION* ppVersion);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif // __cplusplus

#endif // __IMEDIA_PEQ_API_H__

//==============================================================================
// �޸ļ�¼:
//  2013-10-24 14:02:23    �����ļ�
//                         �����ˣ�����/h00207014
//  2014-08-21 15:33:25    �޸�PEQ�ӿ�
//                         �޸��ˣ��ܼ�/x00227689
//  2014-09-04 10:12:51    ���PEQ�������ܺͲ�����Χȷ��
//                         �޸��ˣ��ܼ�/x00227689
//  2014-10-28 14:00:00    ��ɽӿڵ��޸�
//                         �޸��ˣ�����ϼ/y00278990
//  2014-11-20 16:05:12    �޸����ⵥ��DTS2014112004982��DTS2014112005541
//                         �޸��ˣ�����ϼ/y00278990
//==============================================================================

