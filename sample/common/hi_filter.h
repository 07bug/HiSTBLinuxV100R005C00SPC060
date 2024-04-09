/**
 \file
 \brief dmx adaption
 \copyright Shenzhen Hisilicon Co., Ltd.
 \version draft
 \author  
 \date 2011-8-8
 */

#ifndef __HI_FILTER_H__
#define __HI_FILTER_H__

/* add include here */
#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DMX_FILTER_COUNT                96
#define DMX_CHANNEL_COUNT               96

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/
/*call back envent type*/ /*CNcomment:�ص������¼����� */
typedef enum hiFILTER_CALLBACK_TYPE_E
{
    HI_FILTER_CALLBACK_TYPE_DATA_COME,       /**< ���ݵ����ڲ�buffer    */
    HI_FILTER_CALLBACK_TYPE_DATA_IN_BUFFER,  /**< �����ѿ������ⲿbuffer   */
    HI_FILTER_CALLBACK_TYPE_TIMEOUT,         /**< �ȴ����ݳ�ʱ */
    HI_FILTER_CALLBACK_TYPE_BUTT
} HI_FILTER_CALLBACK_TYPE_E;

/*Transparent transmission mode, only the data to reach the internal buffer of events and timeout events, not a copy of the data does not appear to copy data to an external buffer event
    In copy mode, in addition to the data reaches the internal buffer of events and timeout events, there will be a copy of the data to the external buffer events.
      However, in the copy mode, when the reach the data of the external buffer event, the user via the callback function's return value to confirm whether to continue copying, in order to discard the unwanted duplicate data.
      At this point, the return value of 0 means copy a copy, and direct release.*/
/*CNcomment:
    ��͸��ģʽ�£�ֻ�����ݵ����ڲ�buffer���¼��ͳ�ʱ�¼�������������ݵĿ���Ҳ����������ݿ������ⲿbuffer���¼�
    �ڿ���ģʽ�£��������ݵ����ڲ�buffer���¼��ͳ�ʱ�¼��⣬������һ�����ݿ������ⲿbuffer���¼���
      �����ڿ���ģʽ�£����������ݵ����ⲿbuffer�¼�ʱ���û�����ͨ���ص������ķ���ֵȷ���Ƿ�������п������Ա�ֱ�Ӷ�������Ҫ���ظ����ݡ�
      ��ʱ������ֵΪ0��ʾ���п�����Ϊ1��ʾ��������ֱ���ͷš�

 */
typedef HI_S32 (*HI_FILTER_CALLBACK)(HI_S32 s32Filterid, HI_FILTER_CALLBACK_TYPE_E enCallbackType,
                                     HI_UNF_DMX_DATA_TYPE_E eDataType, HI_U8 *pu8Buffer, HI_U32 u32BufferLength);

typedef struct  hiFILTER_ATTR_S
{
    HI_U32  u32DMXID;              /* DMX ID ,0-4*/
    HI_U32  u32PID;                 /* TS PID */
    HI_U8  *pu8BufAddr;             /*Transparent transmission mode set to NULL,otherwise you need to get a buffer and record here*//*CNcomment:�ڷ�͸��ģʽ�£�����������ݵ�buffer��ַ����Ҫ������һ���ڴ棬Ȼ����ָ��,͸��ģʽ����ΪNULL */
    HI_U32  u32BufSize;             /* buffer size,Transparent transmission mode set to 0 */

    HI_U32 u32DirTransFlag;        /* if Transparent transmission mode��0 -Not Transparent transmission mode 1 - Transparent transmission mode */
    HI_U32 u32FilterType;          /* section type 0 - SECTION  1- PES */
    HI_U32 u32CrcFlag;             /* crc check flag,0 - close crc check 1-force crc check 2-crc check by sytax*/
    HI_U32 u32TimeOutMs;           /*time out in ms,0 stand for not timeout,otherwise when timeout,the user can receive the envent*//*CNcomment: ��ʱʱ��(ms)��������ʱ��filter��Ȼû�����ݣ�������¼��ص� ���Ϊ0���ʾ����Ҫ��ʱ�¼�*/

    HI_U32 u32FilterDepth;          /*Filter Depth*/
    HI_U8  u8Match[DMX_FILTER_MAX_DEPTH];
    HI_U8  u8Mask[DMX_FILTER_MAX_DEPTH];
    HI_U8  u8Negate[DMX_FILTER_MAX_DEPTH];

    HI_FILTER_CALLBACK funCallback;         /* data comes callback */
} HI_FILTER_ATTR_S;

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
HI_S32   HI_FILTER_Init(HI_VOID);
HI_S32   HI_FILTER_DeInit(HI_VOID);
HI_S32   HI_FILTER_Creat(HI_FILTER_ATTR_S *pstFilterAttr, HI_S32 *ps32FilterID);
HI_S32   HI_FILTER_Destroy(HI_S32 s32FilterID);
HI_S32   HI_FILTER_SetAttr(HI_S32 s32FilterID, HI_FILTER_ATTR_S *pstFilterAttr);
HI_S32   HI_FILTER_GetAttr (HI_S32 s32FilterID, HI_FILTER_ATTR_S *pstFilterAttr);
HI_S32   HI_FILTER_Start(HI_S32 s32FilterID);
HI_S32   HI_FILTER_Stop(HI_S32 s32FilterID);

#ifdef __cplusplus
}
#endif
#endif /* __HI_FILTER_H__ */
