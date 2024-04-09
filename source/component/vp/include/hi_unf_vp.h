/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_vp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/03/25
  Description   :
  History       :
  1.Date        : 2011/03/25
    Author      :
    Modification: Created file

 *******************************************************************************/

/**
 * \file
 * \brief Describes the information about the video phone (VP) engine. CNcomment: �ṩVP��Ƶ����������ϢCNend
 */
#ifndef __HI_UNF_VP_H__
#define __HI_UNF_VP_H__
#include <netinet/in.h>
#include "hi_common.h"
#include "hi_unf_common.h"
#include "hi_unf_venc.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      VP*/
/** @{ */  /** <!-- [VP] */

/** Video source mode */
/**CNcomment: ��ƵԴģʽ*/
typedef enum hiUNF_VP_SOURCE_MODE_E
{
    HI_UNF_VP_SRC_MODE_USBCAM = 0,   /**<USB camera source mode *//**<CNcomment: USB ����ͷԴģʽ*/
    HI_UNF_VP_SRC_MODE_VI,           /**<VI camera source mode *//**<CNcomment: VIԴģʽ*/
    HI_UNF_VP_SRC_MODE_BUTT,
} HI_UNF_VP_SOURCE_MODE_E;

/**Video source attribute*/
/**CNcomment: ��ƵԴ���� */
typedef struct hiUNF_VP_SOURCE_ATTR_S
{
    HI_HANDLE               hSrc;        /**<video source handle, can be set to VI handle or USB camera handle in v4l2*//**<CNcomment: ��Ƶ��������VI�������v4l2��USB����ͷ�ľ��*/
    HI_UNF_VP_SOURCE_MODE_E enSrcMode;   /**<Video source mode *//**<CNcomment: ��ƵԴģʽ*/
    HI_U32                  u32VIBufNum; /**<VI buffer number*//**<CNcomment:VI����������*/
} HI_UNF_VP_SOURCE_ATTR_S;

/**Network attribute*/
/**CNcomment: �������� */
typedef union hiUNF_VP_NET_ATTR_U
{
    struct sockaddr_in  stIpv4Attr;      /**<IPV4 attribute*//**<CNcomment:IPV4����*/
    struct sockaddr_in6 stIpv6Attr;      /**<IPV6 attribute*//**<CNcomment:IPV6����*/
} HI_UNF_VP_NET_ATTR_U;

/**RTP attribute*/
/**CNcomment: RTP����*/
typedef struct hiUNF_VP_RTP_ATTR_S
{
    HI_U32 u32SplitSize;                       /**< split size, should be less than MTU size*//**<CNcomment:��Ƭ��С*/
    HI_U32 u32PayLoadType;                     /**< pay load type *//**<CNcomment:��������*/
    HI_U32 u32SortDepth;                       /**< sort in order when receive RTP packets, this para indicates sort depth *//**<CNcomment:�������*/
    HI_U32 u32RecvBufSize;                     /**< buffer size, usually 1500 bytes , should be bigger than u32SplitSize*//**<CNcomment:����buf��Ӧ�ô��ڷ�Ƭ��С*/
    HI_U32 u32RecvBufNum;                      /**< buffer number (total_size = u32BufSize * u32BufNum) *//**<CNcomment:����buf����*/
} HI_UNF_VP_RTP_ATTR_S;

/**Video engine attribute*/
/**CNcomment: ��Ƶ�������� */
typedef struct hiUNF_VP_ATTR_S
{
    HI_UNF_VENC_CHN_ATTR_S stVencAttr;        /**<VENC attribute*//**<CNcomment: ��Ƶ����������*/
    HI_UNF_VCODEC_TYPE_E   enDecType;         /**<VDEC attribute*//**<CNcomment: ��Ƶ����������*/
    HI_BOOL                bIsIpv4;           /**<whether use IPV4 attribute, use 1 to demonstrate IPV4, use 0 to demonstrate IPV6 *//**<CNcomment: �Ƿ�ʹ��IPV4������1��ʾʹ��IPV4��0��ʾʹ��IPV6*/
    HI_UNF_VP_NET_ATTR_U   stLocalNetAttr;    /**<Local network attribute*//**<CNcomment: ������������*/
    HI_UNF_VP_NET_ATTR_U   stRemoteNetAttr;   /**<Remote network attribute*//**<CNcomment: Զ����������*/
    HI_UNF_VP_RTP_ATTR_S   stRtpAttr;         /**<RTP attribute. Generally, We highly recommend that you don't modify it.*//**<CNcomment: RTP���ԣ�һ�㲻�����޸�*/
} HI_UNF_VP_ATTR_S;

/**Remote mode*/
/**CNcomment: Զ��ģʽ*/
typedef enum hiUNF_VP_REMOTE_MODE_E
{
    HI_UNF_VP_RMT_MODE_SEND = 0x1,         /**<Send local video to remote mode*//**<CNcomment: ���ͱ�����Ƶ��Զ��ģʽ*/
    HI_UNF_VP_RMT_MODE_RECV = 0x2,         /**<Receive remote video mode*//**<CNcomment: ����Զ����Ƶģʽ*/
    HI_UNF_VP_RMT_MODE_BUTT = 0x4,
} HI_UNF_VP_REMOTE_MODE_E;

/**RTCP configure of video engine*/
/**CNcomment: ��Ƶ����RTCP������Ϣ */
typedef struct hiUNF_VP_RTCP_CFG_S
{
    HI_U32 u32EnableFlag;     /**<Enable RTCP function: 0--disable, 1--enable*//**<CNcomment: RTCPͳ��ʹ��: 0--��ʹ��, 1--ʹ��*/
    HI_U32 u32SendInterval;   /**<Send interval of RTCP report, [500, 65535]ms, must be integer of 500ms*//**<CNcomment: RTCP���淢�ͼ��, [500, 65535] ms , ����Ϊ500ms��������*/
} HI_UNF_VP_RTCP_CFG_S;

/**RTCP statistics information*/
/**CNcomment: RTCP ͳ����Ϣ*/
typedef struct hiUNF_VP_RTCP_STATIC_INFO_S
{
    HI_U32 u32TotalLostPacket;     /**<Total lost packet, this value may reset to 0 when network connection become abnormal *//**<CNcomment: ���ݶ���ͳ�ƣ����������쳣ʱ�������ݿ�������*/
    HI_U32 u32LossFraction;        /**<Lost rate(%)*//**<CNcomment: ������(%) */
    HI_U32 u32Jitter;              /**<Jitter(ms)*//**<CNcomment: ƽ������(ms) */
    HI_U32 u32Delay;               /**<Delay(ms)*//**<CNcomment: ƽ��ʱ��(ms) */
} HI_UNF_VP_RTCP_STATIC_S;

/**Statistic information of network*/
/**CNcomment: ��Ƶ��������ͳ����Ϣ */
typedef struct hiUNF_VP_NET_STA_S
{
    HI_U32                  u32SendPacketNum; /**<Total send packet number*//**<CNcomment: ���Ͱ�����*/
    HI_U32                  u32SendBytes;     /**<Total send bytes*//**<CNcomment: �����ֽ���*/
    HI_U32                  u32RecvPacketNum; /**<Total recv packet number*//**<CNcomment: ���հ�����*/
    HI_U32                  u32RecvBytes;      /**<Total recv bytes*//**<CNcomment: �����ֽ���*/
    HI_UNF_VP_RTCP_STATIC_S stSendInfo;       /**<Send information*//**<CNcomment: ����ͳ��*/
    HI_UNF_VP_RTCP_STATIC_S stRecvInfo;       /**<Reveive information*//**<CNcomment: ����ͳ��*/
} HI_UNF_VP_NET_STA_S;

/**Record stream format*/
/**CNcomment: ¼����������*/
typedef enum hiUNF_VP_RECORD_FORMAT_E
{
    HI_UNF_VP_RECORD_TS = 0x1,         /**<Record TS stream*//**<CNcomment: ¼��TS��*/
    HI_UNF_VP_RECORD_BUTT = 0x2,
} HI_UNF_VP_RECORD_FORMAT_E;

/**Statistic information of video*/
/**CNcomment: ��Ƶ����ͳ����Ϣ */
typedef struct hiUNF_VP_VIDEO_STATICS_S
{
    HI_U32                  u32CaptureFrmCnt;    /**<Total camera capture frame number*//**<CNcomment: ����ͷ�ɼ�֡����*/
    HI_U32                  u32EncoderOutFrmCnt; /**<Total encoder output frame number*//**<CNcomment: ���������֡��*/
    HI_U32                  u32EncoderOutBytes;  /**<Total encoder output bytes*//**<CNcomment: ����������ֽ�*/
    HI_U32                  u32DecoderInFrmCnt;  /**<Total decoder input frame number*//**<CNcomment: ����������֡��*/
    HI_U32                  u32DecoderInBytes;   /**<Total decoder input bytes*//**<CNcomment: �����������ֽ�*/
} HI_UNF_VP_VIDEO_STATICS_S;


/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      VP */
/** @{ */  /** <!-- ��VP�� */

/**
 \brief Initializes the VP module. CNcomment: ��ʼ��VPģ��CNend
 \attention \n
Call this application programming interface (API) before creating VP by calling ::HI_UNF_VP_Create.
CNcomment: �ڵ���::HI_UNF_VP_Create�ӿڴ�������֮ǰ�����ñ��ӿ�CNend
 \param N/A CNcomment: ��CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_DEV_NOT_EXIST The VP device does not exist. CNcomment: �豸������CNend
 \retval ::HI_ERR_VP_DEV_OPEN_ERR The VP device fails to be started. CNcomment: �豸�򿪴���CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_Init(HI_VOID);

/**
 \brief Deinitialize the VP module. CNcomment: ȥ��ʼ��VPģ��CNend
 \attention \n
Call this API after destroying all VPs by calling ::HI_UNF_VP_DestroyChannel.
CNcomment: �ڵ���::HI_UNF_VP_Destroy�ӿ�����VP�󣬵��ñ��ӿ�CNend
 \param N/A CNcomment: ��CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_NOT_INIT The VP is not initialized. CNcomment: VPδ��ʼ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_DeInit(HI_VOID);

/**
 \brief Obtain the default parameter values of VP. CNcomment: ��ȡVPȱʡ����CNend
 \attention \n
Call this API before creating VP by calling ::HI_UNF_VP_Create. This enables you to set parameters conveniently.
CNcomment: �ڵ���::HI_UNF_VP_Create�ӿڴ���VP֮ǰ�����ñ��ӿڣ�������д����CNend
 \param[in] N/A CNcomment: ��CNend
 \param[out] pstDefAttr Pointer to the default VP attributes. For details, see :HI_UNF_VP_ATTR_S. CNcomment: ָ�����ͣ�VPĬ�����ԣ��μ�:HI_UNF_VP_ATTR_S CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \see \n
N/A CNcomment: ��CNend
 */

HI_S32 HI_UNF_VP_GetDefaultAttr(HI_UNF_VP_ATTR_S *pstDefAttr);

/**
 \brief Create VP. CNcomment: ����VP  CNend
 \attention \n
N/A CNcomment: ��CNend
 \param[in]  pstAttr parameter CNcomment: VP����CNend
 \param[out] phVP Pointer to the VP handle. CNcomment: ָ�����ͣ�VP���CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval ::HI_ERR_VP_NOT_SUPPORT The input parameter is invalid. CNcomment: ��������Ƿ�CNend
 \retval ::HI_ERR_VP_NOT_SUPPORT The mode is not supported. CNcomment: ��֧��ģʽCNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_Create(const HI_UNF_VP_ATTR_S *pstAttr, HI_HANDLE *phVP);

/**
 \brief Destroy VP. CNcomment: ����VP  CNend
 \attention \n
N/A CNcomment: ��CNend
 \param[in] hVP VP handle CNcomment: VP���CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_NOT_INIT The VP module is not initialized. CNcomment: VPδ��ʼ��CNend
 \retval ::HI_ERR_VP_INVALID_HANDLE The VP handle is invalid. CNcomment: �Ƿ���VP���CNend
 \retval Other values: A fails to be destroyed. CNcomment: ���� ����ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_Destroy(HI_HANDLE hVP);

/**
 \brief Attach input source of VP. CNcomment: ����Ƶ����ԴCNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \param[in] stSrcAttr Video input attribute. CNcomment:��Ƶ����ͨ������CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval Other values: Failed to attach input source of VP. CNcomment: ����Ƶ����Դʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_AttachSource(HI_HANDLE hVP, HI_UNF_VP_SOURCE_ATTR_S *pstSrcAttr);

/**
 \brief Attach local window of VP. CNcomment: �󶨱�����Ƶ����CNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \param[in] hLocalWin Local window handle. CNcomment:������Ƶ���ھ��CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval Other values: Failed to attach local window of VP. CNcomment: �󶨱�����Ƶ����ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_AttachLocalWin(HI_HANDLE hVP, HI_HANDLE hLocalWin);

/**
 \brief Attach remote window of VP. CNcomment: ��Զ����Ƶ����CNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \param[in] hRemoteWin Remote window handle. CNcomment:Զ����Ƶ���ھ��CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval Other values: Failed to attach remote window of VP. CNcomment: ��Զ����Ƶ����ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_AttachRemoteWin(HI_HANDLE hVP, HI_HANDLE hRemoteWin);

/**
 \brief Detach input source of VP. CNcomment: ȥ����Ƶ����ԴCNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval Other values: Failed to detach input source of VP. CNcomment: ȥ����Ƶ����Դʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_DetachSource(HI_HANDLE hVP);

/**
 \brief Detach local window of VP. CNcomment: ȥ�󶨱�����Ƶ����CNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval Other values: Failed to detach local window of VP. CNcomment: ȥ�󶨱�����Ƶ����ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_DetachLocalWin(HI_HANDLE hVP);

/**
 \brief Detach remote window of VP. CNcomment: ȥ��Զ����Ƶ����CNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP���CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval Other values: Failed to detach remote window of VP. CNcomment: ȥ��Զ����Ƶ����ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_DetachRemoteWin(HI_HANDLE hVP);

/**
 \brief Obtains the configuration of VP. CNcomment: ��ȡVP ����CNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \param[out] pstAttr Pointer to VP attributes. For details, see :HI_UNF_VP_ATTR_S. CNcomment: ָ�����ͣ�VP ���ԣ��μ�:HI_UNF_VP_ATTR_S  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval Other values:Fail to obtain attributes. CNcomment: ��ȡͨ������ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */

HI_S32 HI_UNF_VP_GetAttr(HI_HANDLE hVP, HI_UNF_VP_ATTR_S *pstAttr);

/**
 \brief Modifies the configuration of VP. CNcomment: �޸�VP����CNend
 \attention \n
You are advised to obtain the current configuration by calling HI_UNF_VP_GetChAttr(), and modify parameter values as required.
CNcomment: �����ȵ���HI_UNF_VP_GetChAttr()��ȡ��ǰ���ã��ٶԲ�������Ҫ�޸�CNend
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \param[in] pstAttr Pointer to VP attributes. For details, see :HI_UNF_VP_ATTR_S. CNcomment: ָ�����ͣ�VP ���ԣ��μ�:HI_UNF_VP_ATTR_S  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval Other values: Fail to modify attributes . CNcomment: �޸�����ʧ��CNend
 \see \n
N/A CNcomment:��CNend
 */
HI_S32 HI_UNF_VP_SetAttr(HI_HANDLE hVP, const HI_UNF_VP_ATTR_S *pstAttr);

/**
 \brief Starts VP. CNcomment: VP��ʼ����CNend
 \attention \n
After setting parameters including the codec, video input (VI), and video output (VO) parameters, you can start the video engine by calling this API to transmit or receive data over the Internet and display the local or remote video output.
CNcomment: �ڲ���׼���ú󣬰������������VI/VO������ȷ�󣬵��ô˽ӿڿ���������Ƶ��������У�ʵ�������շ�����ʾ���ء�Զ����Ƶ���CNend
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval Other values: VP fails to be started. CNcomment:  VP��ʼ����ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_Start(HI_HANDLE hVP);

/**
 \brief Stops VP. CNcomment: VPֹͣ����CNend
 \attention \n
After VP is started successfully, you can stop it by calling this API to freeze the screen or stop transmitting or receiving data over Internet. You can resume the VP by calling HI_UNF_VP_Start.
CNcomment: ��VP�����������к󣬿���ͨ���˽ӿ���ͣ���У�ʹ���涳�ᡢ�����շ���ͣ�����Ե���HI_UNF_VP_Start�ָ�����CNend
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval Other values: VP fails to be started. CNcomment: VP��ʼ����ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_Stop(HI_HANDLE hVP);

/**
 \brief Previews the local video over VP. CNcomment: VP��ʼԤ��������ƵCNend
 \attention \n
After the VI and hLocalWin parameters are set, you can preview the local video by calling this API.
CNcomment: ��VI��hLocalWin׼����֮�󣬿�ʼԤ��������ƵCNend
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval Other values: VP fails to be started. CNcomment: VP��ʼ����ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_StartPreView(HI_HANDLE hVP);

/**
 \brief Stops previewing the local video over VP. CNcomment: VPԤ��������ƵCNend
 \attention \n
When a local video is previewed over VP, you can stop previewing the video by calling this API.
CNcomment: ��VPԤ��������Ƶ�󣬵���ֹͣԤ��CNend
 \param[in] hVP VP handle CNcomment: VP ���CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval Other values: VP fails to be started. CNcomment: ����  VP��ʼ����ʧ��CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_StopPreView(HI_HANDLE hVP);

/**
 \brief Starts remote VP. CNcomment: VP����Զ��  CNend
 \attention \n
Starts remote VP, this interface enables vp start sending local video to remote, or receiving remote video.
CNcomment: ����Զ�ˣ����Ե����������ͱ�����Ƶ��Զ�ˣ������Զ����Ƶ  CNend
 \param[in] hVP VP handle CNcomment: VP ���  CNend
 \param[in] enRmtMode remote mode CNcomment: Զ��ģʽ  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�  CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������  CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��  CNend
 \retval Other values: VP fails to be started. CNcomment: VP����ʧ��  CNend
 \see \n
N/A CNcomment: ��  CNend
 */
HI_S32 HI_UNF_VP_StartRemote(HI_HANDLE hVP, HI_UNF_VP_REMOTE_MODE_E enRmtMode);

/**
 \brief Stops remote VP. CNcomment: VPֹͣԶ��  CNend
 \attention \n
Stops remote VP, this interface enables vp stop sending local video to remote, or receiving remote video.
CNcomment: ֹͣԶ�ˣ����Ե���ֹͣ���ͱ�����Ƶ��Զ�ˣ���ֹͣ����Զ����Ƶ  CNend
 \param[in] hVP VP handle CNcomment: VP ���  CNend
 \param[in] enRmtMode remote mode CNcomment: Զ��ģʽ  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�  CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������  CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��  CNend
 \retval Other values: VP fails to be started. CNcomment: VPֹͣʧ��  CNend
 \see \n
N/A CNcomment: ��  CNend
 */
HI_S32 HI_UNF_VP_StopRemote(HI_HANDLE hVP, HI_UNF_VP_REMOTE_MODE_E enRmtMode);

/**
 \brief Configs RTCP over VP. CNcomment: VP����RTCP  CNend
 \attention \n
When VP has been created, you can config RTCP to enable and config RTCP sending frequency by calling this API.
CNcomment: �ڴ���VP�󣬵��øýӿ�����RTCP������ʹ���Լ�����RTCP����Ƶ��CNend
 \param[in] hVP VP handle CNcomment: VP���CNend
 \param[out] pstRtcpCfg Pointer to config RTCP information, refer to HI_UNF_VP_RTCP_CFG_S. CNcomment: ָ�����ͣ�VP RTCP������Ϣ���μ�:HI_UNF_VP_RTCP_CFG_S  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval Other value CNcomment: ����CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_ConfigRtcp(HI_HANDLE hVP, HI_UNF_VP_RTCP_CFG_S *pstRtcpCfg);

/**
 \brief Gets network statistics information over VP. CNcomment: VP��ȡ����ͳ����ϢCNend
 \attention \n
When VP has been started, you can get network statistics information to config parameter of video encoder by calling this API.
CNcomment: ������VP�󣬵��øýӿڻ�ȡ����ͳ����Ϣ�Ե�������������CNend
 \param[in] hVP VP handle CNcomment: VP���CNend
 \param[out] pstNetStatics Pointer to network statistics information of VP, refer to HI_UNF_VP_NET_STA_S. CNcomment: ָ�����ͣ�VP����ͳ����Ϣ���μ�:HI_UNF_VP_NET_STA_S  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval Other value CNcomment: ����CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_GetNetStatics(HI_HANDLE hVP, HI_UNF_VP_NET_STA_S *pstNetStatics);

/**
 \brief Gets VENC handle. CNcomment: ��ȡVENC���  CNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP���  CNend
 \param[out] phVenc Pointer to VENC handle. CNcomment: ָ�����ͣ�VENC���  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�  CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������  CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��  CNend
 \retval Other value CNcomment: ����  CNend
 \see \n
N/A CNcomment: ��  CNend
 */
HI_S32 HI_UNF_VP_GetVencHandle(HI_HANDLE hVp, HI_HANDLE *phVenc);

/**
 \brief Gets AVPLAY handle that play remote video. CNcomment: ��ȡ����Զ����Ƶ��AVPLAY���  CNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP���  CNend
 \param[out] phAvplay Pointer to AVPLAY handle. CNcomment: ָ�����ͣ�AVPLAY���  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�  CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������  CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��  CNend
 \retval Other value CNcomment: ����  CNend
 \see \n
N/A CNcomment: ��  CNend
 */
HI_S32 HI_UNF_VP_GetAvplayHandle(HI_HANDLE hVp, HI_HANDLE *phAvplay);

/**
 \brief Start record stream. CNcomment: ��ʼ¼������  CNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP���  CNend
 \param[in] enRecordFmt Record stream format. CNcomment: ¼��������ʽ����  CNend
 \param[in] enRecordType Record type. CNcomment: ¼������  CNend
 \param[in] ucFullName Record stream full name, full directory included. CNcomment: ¼���������ƣ�������·��  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�  CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������  CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��  CNend
 \retval Other value CNcomment: ����  CNend
 \see \n
N/A CNcomment: ��  CNend
 */
HI_S32 HI_UNF_VP_StartRecord(HI_HANDLE hVP, HI_UNF_VP_REMOTE_MODE_E enRecordType,
                                 HI_UNF_VP_RECORD_FORMAT_E enRecordFmt, HI_CHAR * ucFullName);

/**
 \brief Stop record stream. CNcomment: ֹͣ¼������  CNend
 \attention \n
 \param[in] hVP VP handle CNcomment: VP���  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�  CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������  CNend
 \retval Other value CNcomment: ����  CNend
 \see \n
N/A CNcomment: ��  CNend
 */
HI_S32 HI_UNF_VP_StopRecord(HI_HANDLE hVP);


/**
 \brief Gets video statistics information over VP. CNcomment: VP��ȡ��Ƶͳ����ϢCNend
 \param[in] hVP VP handle CNcomment: VP���CNend
 \param[out] pstNetStatics Pointer to video statistics information of VP, refer to HI_UNF_VP_NET_STA_S. CNcomment: ָ�����ͣ�VP��Ƶͳ����Ϣ  CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ�CNend
 \retval ::HI_ERR_VP_INVALID_PARA The input parameter is invalid. CNcomment: ��Ч���������CNend
 \retval ::HI_ERR_VP_NULL_PTR The pointer is null. CNcomment: ��ָ��CNend
 \retval Other value CNcomment: ����CNend
 \see \n
N/A CNcomment: ��CNend
 */
HI_S32 HI_UNF_VP_GetVideoStatics(HI_HANDLE hVP, HI_UNF_VP_VIDEO_STATICS_S *pstVideoStatics);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif
