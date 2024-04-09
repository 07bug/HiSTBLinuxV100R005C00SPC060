
#ifndef __IMG_QUE_HEADER__
#define  __IMG_QUE_HEADER__

#include "basedef.h"
#include "vfmw.h"


#define IMGQUE_MAX_IMAGE_NUM    64
#define IMGQUE_MAX_NAME_LEN     16

typedef struct hiImageQueue
{
    SINT8      queue_name[IMGQUE_MAX_NAME_LEN];    //��������˶��ʵ�������������ʶ
    SINT8      ImageValid[IMGQUE_MAX_IMAGE_NUM];   // 0(00b): ����Ч,
    // 1(01b): ������Ч,
    // 2(10b): �׳���Ч��
    // 3(11b): ����Ч
    IMAGE      *image_ptr[IMGQUE_MAX_IMAGE_NUM];
    SINT32     max_queue_size;
    SINT32     queue_size;
    SINT32     history;
    SINT32     head;
    SINT32     tail;
    SINT32     ResetCount;
    UINT32     queue_mutex;
    UINT32     last_image_id_plus2;
    SINT32     (*DelImageProc)(struct hiImageQueue *pImageQueue, SINT32 ImageID);
} IMAGE_QUEUE;


/*********************************************************************************
    ����ԭ��
        SINT32 IMGQUE_InitQueue( IMAGE_QUEUE *pImageQueue )
    ��������
        ��ʼ��ͼ�����
    ����˵��
        pImageQueue: ͼ�����ָ��
		QueueName:   ͼ����е����֣�16���ַ�����
    ����ֵ
        �����ʼ���ɹ�����VF_OK�����򷵻ش�����
 *********************************************************************************/
SINT32 IMGQUE_InitQueue( IMAGE_QUEUE *pImageQueue, SINT8 *QueueName,
                         SINT32 (*DelImageProc)(struct hiImageQueue *pImageQueue, SINT32 ImageID) );

/*********************************************************************************
    ����ԭ��
        SINT32 IMGQUE_ResetQueue( IMAGE_QUEUE *pImageQueue )
    ��������
        ��ʼ��ͼ�����
    ����˵��
        pImageQueue: ͼ�����ָ��
    ����ֵ
        �����ʼ���ɹ�����VF_OK�����򷵻ش�����
 *********************************************************************************/
SINT32 IMGQUE_ResetQueue( IMAGE_QUEUE *pImageQueue );

/*********************************************************************************
    ����ԭ��
        SINT32 IMGQUE_InsertImage(IMAGE_QUEUE *pImageQueue, IMAGE *p_image)
    ��������
        ��ָ����ͼ����뵽ͼ�������
    ����˵��
        pImageQueue: ͼ�����ָ��
        p_image����������е�ͼ������
    ����ֵ
        �������ɹ��򷵻�VF_OK�����򷵻ش�����
    �㷨����
 *********************************************************************************/
SINT32 IMGQUE_InsertImage(IMAGE_QUEUE *pImageQueue, IMAGE *p_image);

/*********************************************************************************
    ����ԭ��
        VOID IMGQUE_GetImageNum(IMAGE_QUEUE *pImageQueue, SINT32 *pReadImgNum, SINT32 *pNewImgNum)
    ��������
        ��ȡ�����е�ͼ����Ŀ
    ����˵��
        pImageQueue: ͼ�����ָ��
        pReadImgNum: �ѱ����ߣ�����δ�ͷŵ�ͼ�����( history ~ head )
        pNewImgNum:  �Ѳ�����л�û�б����ߵ�ͼ�����( head ~ tail )
    ����ֵ
        ��
    �㷨����
 *********************************************************************************/
VOID IMGQUE_GetImageNum(IMAGE_QUEUE *pImageQueue, SINT32 *pReadImgNum, SINT32 *pNewImgNum);

SINT32 IMGQUE_ReturnImage(IMAGE_QUEUE *pImageQueue);

/*********************************************************************************
    ����ԭ��
        SINT32 IMGQUE_GetImage(IMAGE_QUEUE *pImageQueue, IMAGE *p_image)
    ��������
        ��VO�����л�ȡһ��ͼ��
    ����˵��
        pImageQueue: ͼ�����ָ��
        p_image:     IMAGE���͵�ָ�룬���ջ�ȡ����ͼ�����Ϣ
    ����ֵ
        �����ȡ�ɹ��򷵻�VF_OK�����򷵻ش�����
    �㷨����
 *********************************************************************************/
SINT32 IMGQUE_GetImage(IMAGE_QUEUE *pImageQueue, IMAGE *p_image);

/*********************************************************************************
    ����ԭ��
        SINT32 IMGQUE_DeleteImage(IMAGE_QUEUE *pImageQueue, SINT32 ImageID, SINT32 *pDelTopAddr, SINT32 *pDelBtmAddr)
    ��������
        �ͷ�һ��ͼ��ϵͳ������ô˺�������p_image��������ͼ���Ѿ�ʹ�ã�������
        Ҫ���棬��洢�ռ���Ա���������������·���
    ����˵��
        pImageQueue: ͼ�����ָ��
        p_image��IMAGE���͵�ָ�룬ָʾҪ�ͷŵ�ͼ�����Ϣ
    ����ֵ
        ����ͷųɹ��򷵻�VF_OK�����򷵻ش�����
    �㷨����
 *********************************************************************************/
SINT32 IMGQUE_DeleteImage(IMAGE_QUEUE *pImageQueue, SINT32 ImageID, SINT32 *pDelTopAddr, SINT32 *pDelBtmAddr);

VOID print_que(IMAGE_QUEUE *pImageQueue);

SINT32 IMGQUE_GetLastImageID(IMAGE_QUEUE *pImageQueue);

#endif



