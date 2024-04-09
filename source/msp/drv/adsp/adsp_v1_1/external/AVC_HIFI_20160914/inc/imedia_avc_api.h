//==============================================================================
//           Copyright (C), 2008-2015, Hisilicon Tech. Co., Ltd.
//==============================================================================
//  �ļ�����: imedia_avc_api.h
//  �ļ�����: ���ļ�����AVC/DRC�㷨��ĸ��ṹ�嶨����Ϣ�͹��ܺ�����������Ϣ
//            ��ʹ���㷨��ʱ��Ҫ�������ļ�
//
//  �ṹ���б�:
//      iMedia_AVC_STRU_MEM_CONFIG  -- �㷨�ڴ����ýṹ��
//      iMedia_AVC_STRU_MEM_SIZE    -- �㷨�ڴ��С�ṹ��
//      iMedia_AVC_STRU_VERSION     -- �㷨�汾��Ϣ�ṹ��
//      iMedia_AVC_STRU_PARAMS      -- AVC�㷨�������ýṹ��
//      iMedia_DRC_STRU_PARAMS      -- DRC�㷨�������ýṹ��
//      iMedia_AVC_DRC_STRU_PARAMS  -- �㷨�ܽӿڲ������ýṹ��
//
//  �����б�:
//      iMedia_AVC_GetSize()        -- ��ȡ�ڴ��С
//      iMedia_AVC_Init()           -- ��ʼ���㷨ʵ��(ͨ������)
//      iMedia_AVC_Apply()          -- �㷨����Ӧ��
//      iMedia_AVC_SetParams()      -- �����㷨��������
//      iMedia_AVC_GetParams()      -- ��ȡ�㷨��������
//      iMedia_AVC_GetVersion()     -- ��ȡ�㷨��汾��Ϣ���������ñ������汾��
//                                     ����ʱ��Ͱ汾��
//
//  �޸ļ�¼: ���ļ�β
//==============================================================================

#ifndef _IMEDIA_AVC_API_H_
#define _IMEDIA_AVC_API_H_

#include "imedia_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
//     ��������������Ϣ
//==============================================================================
#define    IMEDIA_AVC_CHAN_MSG_VERLEN   (64)    // �㷨��汾��Ϣ������ʱ���ַ�������
#define    IMEDIA_AVC_SAMPLE_RATE       (48000) // �㷨����Ĳ�����
#define    IMEDIA_AVC_CHAN_NUM          (2)     // �㷨�������ݵ�������
#define    IMEDIA_AVC_FRAME_PCMNUM_S    (256)   // �㷨����һ֡PCM���ݵ���������

//==============================================================================
//     �����붨����Ϣ
//==============================================================================
// BEGIN: modified by x00227689 20141120 ���ⵥ: DTS2014112004156
#define    IMEDIA_AVC_EOK                      (0)     // �����ɹ�������
#define    IMEDIA_AVC_INV_MEMSIZE_PST          (-1)    // ��Ч���ڴ��С�ṹ��ָ��
#define    IMEDIA_AVC_INV_MEMCFG_PST           (-2)    // ��Ч���ڴ����ýṹ��ָ��
#define    IMEDIA_AVC_INV_SAMPLE_RATE          (-3)    // ��Ч�Ĳ�����
#define    IMEDIA_AVC_INV_CHANNEL              (-4)    // ��Ч��������
#define    IMEDIA_AVC_INV_HANDLE               (-5)    // ��Ч�����ָ��Ϊ�գ�
#define    IMEDIA_AVC_INV_BASE                 (-6)    // ��Ч�Ļ���ַ
#define    IMEDIA_AVC_INV_MEM_SIZE             (-7)    // �ڴ��СС��Ҫ��ֵ
#define    IMEDIA_AVC_INV_PARAMS               (-8)    // ��Ч�����ýṹ��ָ��
#define    IMEDIA_AVC_INV_PARA_MODE            (-9)    // ��Ч�㷨����ģʽ
#define    IMEDIA_AVC_INV_PARA_ATTACK          (-10)   // ��ЧAttackTime
#define    IMEDIA_AVC_INV_PARA_RELEASE         (-11)   // ��ЧReleaseTime
#define    IMEDIA_AVC_INV_PARA_START_LEVEL     (-12)   // ��Ч�������ƽ
#define    IMEDIA_AVC_INV_PARA_CORNER_LEVEL    (-13)   // ��Ч��ת�۵�ƽ
#define    IMEDIA_AVC_INV_PARA_MAX_GAIN        (-14)   // ��Ч���������
#define    IMEDIA_AVC_INV_PARA_TARGET_LEVEL    (-15)   // ��Ч��Ŀ���ƽ
#define    IMEDIA_AVC_INV_PARA_CROSS_LEVEL     (-16)   // ת�۵�ƽС�ڵ��������ƽ
                                                       // ��ת�۵�ƽ�����������ڵ���Ŀ���ƽ
                                                       // ��DRCģʽ��Ŀ���ƽС�ڵ��������ƽ
#define    IMEDIA_AVC_INV_BIT_DEPTH            (-17)   // ��Ч������λ������
#define    IMEDIA_AVC_INV_INBUFF               (-18)   // ���뻺����Ϊ��
#define    IMEDIA_AVC_INV_MEM_ODD              (-19)   // ��Ч�����ַ
#define    IMEDIA_AVC_INV_OUTBUFF              (-20)   // ���������Ϊ��
#define    IMEDIA_AVC_INV_OUTBUFF_UNALIGNED    (-21)   // �����������ַû��4�ֽڶ���
#define    IMEDIA_AVC_UNINITIED                (-22)   // û����ɳ�ʼ��
#define    IMEDIA_AVC_INV_PARA_VERSION         (-23)   // ��Ч�汾��Ϣ�ṹ��ָ��

#define    IMEDIA_AVC_INV_REFMODE              (-24)   // ��Ч��RefMode����
#define    IMEDIA_AVC_INV_POWERCTRLSPEECHMODE  (-25)   // ��Ч��PowerCtrlSpeedMode����
// END: modified by x00227689 20141120 ���ⵥ: DTS2014112004156
//==============================================================================
//     ���ò���������Ϣ
//==============================================================================
typedef enum
{
    IMEDIA_AVC_MODE = 0,
    IMEDIA_DRC_MODE = 1
}IMEDIA_AVC_DRC_MODE;

typedef enum
{
    IMEDIA_AVC_BIT_DEPTH_16 = 0,
    IMEDIA_AVC_BIT_DEPTH_24 = 1
}IMEDIA_AVC_DRC_BIT_DEPTH;

//==============================================================================
//     �����������Ͷ�����Ϣ
//==============================================================================
// �ڴ����ýṹ��
typedef struct tagAVC_STRU_MEM_CONFIG
{
    IMEDIA_INT32  iSampleRate;                                    // ���ݲ����� 48000
    IMEDIA_INT32  iChannels;                                      // ������ 2
    IMEDIA_INT8   cReserve[8];                                    // ������
}iMedia_AVC_STRU_MEM_CONFIG, *iMedia_AVC_PST_MEM_CONFIG;

// �ڴ��С�ṹ��
typedef struct tagAVC_STRU_MEM_SIZE
{
    IMEDIA_UINT32   uiStrSize;                                    // ͨ��������С, ��λΪ�ֽ�
    IMEDIA_INT32    iInSize;                                      // ��������
    IMEDIA_INT32    iOutSize;                                     // ��������
}iMedia_AVC_STRU_MEM_SIZE, *iMedia_AVC_PST_MEM_SIZE;

// �汾��Ϣ�ṹ��
typedef struct  tagAVC_STRU_VERSION
{
    IMEDIA_UINT8    ucCgtVersion[IMEDIA_AVC_CHAN_MSG_VERLEN];     // Code Generation Tools�汾��
    IMEDIA_UINT8    ucReleaseVer[IMEDIA_AVC_CHAN_MSG_VERLEN];     // �㷨��汾��
    IMEDIA_UINT8    ucReleaseTime[IMEDIA_AVC_CHAN_MSG_VERLEN];    // ��������
} iMedia_AVC_STRU_VERSION, *iMedia_AVC_PST_VERSION;

// AVC�㷨���ò����ṹ��
typedef struct tagAVC_STRU_PARAMS
{
    IMEDIA_INT32  sStartLevel;   // �����ƽ����Χ[-40, -20]dB *1000
    IMEDIA_INT32  sCornerLevel;  // �ﵽ���̧�������ת�۵�ƽ����Χ(-40, -16)dB *1000����Ҫ���������ƽ
    IMEDIA_INT32  sMaxGain;      // ���̧�����棬��Χ[0, 8]dB *1000
    IMEDIA_INT32  sTargetLevel;  // Ŀ���ƽ����Χ[-40, 0]dB *1000��ת�۵�ƽ�����������С��Ŀ���ƽ
}iMedia_AVC_STRU_PARAMS, *iMedia_AVC_PST_PARAMS;

// DRC�㷨���ò����ṹ��
typedef struct tagDRC_STRU_PARAMS
{
    IMEDIA_INT32  sStartLevel;   // �����ƽ��[-80, -1]*1000
    IMEDIA_INT32  sTargetLevel;  // Ŀ���ƽ��[-80, -1]*1000�������ƽ��С��Ŀ���ƽ
}iMedia_DRC_STRU_PARAMS, *iMedia_DRC_PST_PARAMS;

// �㷨���ò����ṹ��  32
typedef struct tagAVC_DRC_STRU_PARAMS
{
    IMEDIA_INT16  sMode;         // �㷨ѡ�����: 0 ��ʾѡ��AVC�㷨��1 ��ʾѡ��DRC�㷨������������Ч
    IMEDIA_INT16  sAttackTime;   // attackʱ�䣬��Χ[20, 2000]ms
    IMEDIA_INT16  sReleaseTime;  // releaseʱ�䣬��Χ[20, 2000]ms
    IMEDIA_INT16  sBitDepth;     // ����λ��0��ʾ16bit��1��ʾ24bit������������Ч���ݽ�֧��DRC�㷨
    iMedia_AVC_STRU_PARAMS  stAVCParams; // AVC�㷨���ò����ṹ��
    iMedia_DRC_STRU_PARAMS  stDRCParams; // DRC�㷨���ò����ṹ��
    IMEDIA_INT8 cRefMode;                // 0: ԭʼ�汾Ч���� 1������������ ����������Ч
    IMEDIA_INT8 cPowerCtrlSpeedMode;     // 0: ԭʼ�汾Ч���� 1: �Ͽ��ٿ��ƣ� ����������Ч
    IMEDIA_INT8 cReserve[2];
}iMedia_AVC_DRC_STRU_PARAMS, *iMedia_AVC_DRC_PST_PARAMS;


//==============================================================================
//     ����������Ϣ
//==============================================================================

//==============================================================================
// ��������: iMedia_AVC_GetSize
// ��������: ��ȡͨ����С
// �������:
//     pstConf    -- �ڴ����ýṹ��
// �������:
//     pstMemSize -- ͨ����С�ṹ��
// ���ز���:
//     ret        -- ����������IMEDIA_AVC_EOK��ʾ�ɹ��������������ʾʧ��
//==============================================================================
extern IMEDIA_INT32 iMedia_AVC_GetSize(iMedia_AVC_PST_MEM_SIZE pstMemSize,
                                       iMedia_AVC_PST_MEM_CONFIG pstConf);

//==============================================================================
// ��������: iMedia_AVC_Init
// ��������: ��ʼ���㷨ʵ��(ͨ������)������������
// �������:
//     pMemBase   -- ͨ��������ʼ��ַ
//     uiMemSize  -- ͨ�������ռ��С
//     pParams    -- �㷨�������ýṹ��ָ��
// �������:
//     ppHandle   -- ������
// ���ز���:
//     ret        -- ���������� IMEDIA_AVC_EOK ��ʾ�ɹ��������������ʾʧ��
//==============================================================================
extern IMEDIA_INT32 iMedia_AVC_Init(IMEDIA_VOID **ppHandle,
                                    const IMEDIA_VOID *pMemBase,
                                    IMEDIA_UINT32 uiMemSize,
                                    const iMedia_AVC_DRC_PST_PARAMS pParams);

//==============================================================================
// ��������: iMedia_AVC_Apply
// ��������: �㷨����Ӧ��(����һ֡˫����512�㣬Լ5.333ms)
// �������:
//     pHandle    -- ������
//     PcmIn     -- �������ݻ�����ָ��
// �������:
//     PcmOut    -- ������ݻ�����ָ��
// ���ز���:
//     ret        -- ���������� IMEDIA_AVC_EOK ��ʾ�ɹ��������������ʾʧ��
//==============================================================================
extern IMEDIA_INT32 iMedia_AVC_Apply(IMEDIA_VOID *pHandle,
                                     const IMEDIA_VOID *PcmIn,
                                     IMEDIA_VOID *PcmOut);

//==============================================================================
// ��������: iMedia_AVC_SetParams
// ��������: ��̬�������ýӿڣ��л���������ʱʹ�á�
//           ע��: �ýӿڽ��ǵ��Խӿڣ�ֻ���ڵ��Խ׶�ʹ�ã�����������ʹ�á�
// �������:
//     pHandle    -- ������
//     pParams    -- �㷨�������ýṹ��ָ��
// �������:
//     pHandle    -- ������
// ���ز���:
//     ret        -- ���������� IMEDIA_AVC_EOK ��ʾ�ɹ��������������ʾʧ��
//==============================================================================
extern IMEDIA_INT32 iMedia_AVC_SetParams(IMEDIA_VOID* pHandle,
                                         const iMedia_AVC_DRC_PST_PARAMS pParams);

//==============================================================================
// ��������: iMedia_AVC_GetParams
// ��������: ��ȡ��ǰ�㷨�Ĳ�������
// �������:
//     pHandle    -- ������
// �������:
//     pParams    -- �㷨�������ýṹ��ָ��
// ���ز���:
//     ret        -- ���������� IMEDIA_AVC_EOK ��ʾ�ɹ��������������ʾʧ��
//==============================================================================
extern IMEDIA_INT32 iMedia_AVC_GetParams(IMEDIA_VOID *pHandle,
                                         iMedia_AVC_DRC_PST_PARAMS pParams);

//==============================================================================
// ��������: iMedia_AVC_GetVersion
// ��������: ��ȡ�㷨��汾��Ϣ���������ñ������汾������ʱ��Ͱ汾��
// �������:
//     ppVersion    -- �汾��Ϣ�ṹ����
// �������:
//     ppVersion    -- �汾��Ϣ�ṹ����
// ���ز���:
//     ret          -- ���������� IMEDIA_AVC_EOK ��ʾ�ɹ��������������ʾʧ��
//==============================================================================
extern IMEDIA_INT32 iMedia_AVC_GetVersion(iMedia_AVC_PST_VERSION *ppVersion);

#ifdef __cplusplus
}
#endif

#endif


//==============================================================================
// �޸ļ�¼:
//  2013-6-4 14:02:23    �����ļ�
//                       �����ˣ����ޱ�
//  2013-7-2 15:32:13    �޸��ļ���HiFi2���ݽṹ�޸ģ������˲�������flag
//                       �޸��ˣ�����/h00207014
//  2013-8-12 15:32:13   �޸��ļ����޸����ò����ṹ������������ע��
//                       �޸��ˣ�����/h00207014
//  2013-11-05 14:25:13  �޸���������,����ͨ������,���ò��������ӱ���iRmsThreshold
//                       ���ⵥ�ţ�DTS2013112101855
//                       �޸��ˣ�����/h00207014
//  2013-11-15 09:45:23  �޸�ջʹ�ù�������,��ջ����ͨ��
//                       ���ⵥ�ţ�DTS2013112101619
//                       �޸��ˣ�����/h00207014
//  2014-01-07 09:45:23  K3V3_HiFi3��ֲ,ɾ��HighQFiag
//                       �޸��ˣ�����/h00207014
//  2014-09-17 15:05:33  �޸�֡��Ϊ˫����512�㣬�ڲ�������һ���Ӵ�
//                       �޸��ˣ��ܼ�/x00227689
//  2014-10-27 12:05:33  ����㷨�ӿ��޸ģ����������ɵ��ļ���ʽ��Ϊ�ṹ�帳ֵ��ʽ
//                       �޸��ˣ��ܼ�/x00227689
//  2014-11-20 14:58:30  �޸����ⵥ: DTS2014112004156
//                       �޸��ˣ��ܼ�/x00227689
//  2015-06-27 17:20:30  ���24bitDRC����16bit�޸�
//                       �޸��ˣ��ܼ�/x00227689
//==============================================================================

