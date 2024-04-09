#ifndef __DRV_HDMI_TEE_H__
#define __DRV_HDMI_TEE_H__

#include "drv_hdmi_common.h"
#include "teek_client_api.h"    // tee

/* enhance key operation security */
#define HDMI_KEY_SUCC   0xAC145884
#define HDMI_KEY_FAIL   0xF2788541

#define HDMI_KEY_TRUE   0xAC145887
#define HDMI_KEY_FALSE  0xF278854A


#define HDMI_TEE_DATA_SIZE 1024
typedef enum {
    HI_HDMI_HDCP14_INIT = 0x100,    /* 0x100 enhance operation security */
    HI_HDMI_HDCP14_BKSV_SET,
    HI_HDMI_HDCP14_RPT_ENABLE,
    HI_HDMI_HDCP14_R0_VERIFY,
    HI_HDMI_HDCP14_KSVLIST_SET,
    HI_HDMI_HDCP14_VI_VERIFY,
    HI_HDMI_HDCP14_ENC_ENABLE,
    HI_HDMI_STATUS,
    HI_HDMI_HDCP14_EVENT,
    HI_HDMI_HDCP22_INIT,
    HI_HDMI_TEE_STATUS_VIEW,
    HI_HDMI_HDCP_CAPS,
    HI_HDMI_STOP,
    HI_HDMI_COMM_BUTT,
} HI_HDMI_COMMID_E;

enum TEE_Result_Value{
    TEE_SUCCESS = 0x0,                          /**< �ɹ�  */
    TEE_ERROR_INVALID_CMD,                      /**< �Ƿ����� */
    TEE_ERROR_SERVICE_NOT_EXIST,                /**< ���񲻴��� */
    TEE_ERROR_SESSION_NOT_EXIST,                /**< ���Ӳ����� */
    TEE_ERROR_SESSION_MAXIMUM,                  /**< ���������� */
    TEE_ERROR_REGISTER_EXIST_SERVICE,           /**< ע���Ѿ����ڵķ��� */
    TEE_ERROR_TARGET_DEAD_FATAL,                 /**< Global Task ����  */
    TEE_ERROR_READ_DATA,                        /**< ��ȡ�ļ�����  */
    TEE_ERROR_WRITE_DATA,                       /**< д���ļ�����  */
    TEE_ERROR_TRUNCATE_OBJECT,                  /**< �ض��ļ�����  */
    TEE_ERROR_SEEK_DATA,                        /**< �����ļ�����  */
    TEE_ERROR_SYNC_DATA,                        /**< ͬ���ļ�����  */
    TEE_ERROR_RENAME_OBJECT,                    /**< �������ļ�����  */
    TEE_ERROR_TRUSTED_APP_LOAD_ERROR,           /**< �򿪻Ựʱ�����ؿ���Ӧ�ó���ʧ��*/
#ifdef GP_V1_1_SUPPORTED
    TEE_ERROR_CORRUPT_OBJECT=0xF0100001,/**If the persistent object is corrupt. The object handle is closed.*/
    TEE_ERROR_CORRUPT_OBJECT_2=0xF0100002,/**If the persistent object is stored in a storage area which is currently inaccessible.*/
    TEE_ERROR_STORAGE_NOT_AVAILABLE=0xF0100003,
    TEE_ERROR_STORAGE_NOT_AVAILABLE_2=0xF0100004,
#endif
    TEE_ERROR_GENERIC = 0xFFFF0000,             /**< ͨ�ô���  */
    TEE_ERROR_ACCESS_DENIED = 0xFFFF0001 ,      /**< Ȩ��У��ʧ��  */
    TEE_ERROR_CANCEL = 0xFFFF0002 ,             /**< ������ȡ��  */
    TEE_ERROR_ACCESS_CONFLICT = 0xFFFF0003 ,    /**< �������ʵ��³�ͻ  */
    TEE_ERROR_EXCESS_DATA = 0xFFFF0004 ,        /**< ��������������̫��  */
    TEE_ERROR_BAD_FORMAT = 0xFFFF0005 ,         /**< ���ݸ�ʽ����ȷ  */
    TEE_ERROR_BAD_PARAMETERS = 0xFFFF0006 ,     /**< ������Ч  */
    TEE_ERROR_BAD_STATE = 0xFFFF0007,           /**< ��ǰ״̬�µĲ�����Ч  */
    TEE_ERROR_ITEM_NOT_FOUND = 0xFFFF0008,      /**< ���������δ�ҵ�  */
    TEE_ERROR_NOT_IMPLEMENTED = 0xFFFF0009,     /**< ����Ĳ������ڵ���δʵ��  */
    TEE_ERROR_NOT_SUPPORTED = 0xFFFF000A,       /**< ����Ĳ�����Ч��δ֧��  */
    TEE_ERROR_NO_DATA = 0xFFFF000B,             /**< ���ݴ���  */
    TEE_ERROR_OUT_OF_MEMORY = 0xFFFF000C,       /**< ϵͳû�п�����Դ  */
    TEE_ERROR_BUSY = 0xFFFF000D,                /**< ϵͳ��æ  */
    TEE_ERROR_COMMUNICATION = 0xFFFF000E,       /**< �������ͨ��ʧ��  */
    TEE_ERROR_SECURITY = 0xFFFF000F,            /**< ��⵽��ȫ����  */
    TEE_ERROR_SHORT_BUFFER = 0xFFFF0010,        /**< �ڴ����볤��С���������  */
    TEE_PENDING = 0xFFFF2000,                   /**< ���ŷ����ڵȴ�״̬(�첽����) */
    TEE_PENDING2 = 0xFFFF2001,                  /**< ���ŷ����ڵȴ�״̬2(����δ���) */
    TEE_PENDING3 = 0xFFFF2002,
    TEE_ERROR_TIMEOUT = 0xFFFF3001,             /**< ����ʱ */
    TEE_ERROR_OVERFLOW = 0xFFFF300f,            /**< ������� */
    TEE_ERROR_TARGET_DEAD = 0xFFFF3024,          /**< Trusted Application����  */
    TEE_ERROR_STORAGE_NO_SPACE = 0xFFFF3041,    /**< û���㹻��Flash�ռ����洢�ļ� */
    TEE_ERROR_FILE_CORRUPT = 0xFFFF3042,        /**< �洢���ļ����𻵣�������У��ʧ�� */
    TEE_ERROR_MAC_INVALID = 0xFFFF3071,         /**< MACֵУ�����  */
    TEE_ERROR_SIGNATURE_INVALID = 0xFFFF3072,   /**< У��ʧ�� */
    TEE_ERROR_TIME_NOT_SET = 0xFFFF5000,        /**< ʱ��δ���� */
    TEE_ERROR_TIME_NEEDS_RESET = 0xFFFF5001,    /**< ʱ����Ҫ���� */
    TEE_FAIL = 0xFFFF5002,    /**< ʱ����Ҫ���� */
    TEE_ERROR_TIMER = 0xFFFF6000,
    TEE_ERROR_TIMER_CREATE_FAILED,
    TEE_ERROR_TIMER_DESTORY_FAILED,
    TEE_ERROR_TIMER_NOT_FOUND,
    TEE_ERROR_RPMB_BASE = 0xFFFF7000,    /**< RPMB��ȫ�洢�������ַ */
    TEE_ERROR_RPMB_GENERIC = 0xFFFF7001,    /**< RPMB������ͨ�ô��� */
    TEE_ERROR_RPMB_MAC_FAIL,    /**< RPMB������MACУ����� */
    TEE_ERROR_RPMB_COUNTER_FAIL,    /**< RPMB������������У����� */
    TEE_ERROR_RPMB_ADDR_FAIL,    /**< RPMB��������ַУ����� */
    TEE_ERROR_RPMB_WRITE_FAIL,    /**< RPMB������д���� */
    TEE_ERROR_RPMB_READ_FAIL,    /**< RPMB������������ */
    TEE_ERROR_RPMB_KEY_NOT_PROGRAM,    /**< RPMB Keyδд�� */
    TEE_ERROR_RPMB_RESP_UNEXPECT_MSGTYPE = 0xFFFF7100,    /**< RPMBӦ�����ݵ���Ϣ����У����� */
    TEE_ERROR_RPMB_RESP_UNEXPECT_BLKCNT,    /**< RPMBӦ�����ݵ����ݿ�У����� */
    TEE_ERROR_RPMB_RESP_UNEXPECT_BLKIDX,    /**< RPMBӦ�����ݵ����ݵ�ַУ����� */
    TEE_ERROR_RPMB_RESP_UNEXPECT_WRCNT,    /**< RPMBӦ�����ݵļ�����У����� */
    TEE_ERROR_RPMB_RESP_UNEXPECT_NONCE,    /**< RPMBӦ�����ݵ������У����� */
    TEE_ERROR_RPMB_RESP_UNEXPECT_MAC,    /**< RPMBӦ�����ݵ�MACУ����� */
    TEE_ERROR_RPMB_FILE_NOT_FOUND,    /**< RPMB��ȫ�洢�ļ������� */
    TEE_ERROR_RPMB_NOSPC,    /**< RPMB��ȫ�洢���̿ռ䲻�� */
    TEE_ERROR_TUI_IN_USE = 0xFFFF7110,
    TEE_ERROR_TUI_SWITCH_CHANNAL,
    TEE_ERROR_TUI_CFG_DRIVER,
    TEE_ERROR_TUI_INVALID_EVENT,
    TEE_ERROR_TUI_POLL_EVENT,
    TEE_ERROR_TUI_CANCELED,
    TEE_FAIL2
};

typedef struct hiHDMI_TEE_INFO_S
{
    HI_BOOL         bTeeOpen;
    TEEC_Context    stTeecContext;
    TEEC_Operation  stTeecOperation;
    TEEC_Session    stTeecSession;
    HI_U8           au8TeeDataBuf[HDMI_TEE_DATA_SIZE];
    HI_U32          u32DataSize;
}HDMI_TEE_INFO_S;

typedef struct hiHDMI_TEE_HDCP_CAPS_S
{
    HI_BOOL         bHdcp14Support;
    HI_BOOL         bHdcp22Support;
}HDMI_TEE_HDCP_CAPS_S;

typedef struct hiHDMI_TEE_PARAM_S
{
    HI_HDMI_COMMID_E        enTeeCmd;
    HDMI_TEE_HDCP_CAPS_S    seHdcpCaps;
    HI_U32                  u32TestParam;
    HI_U32                  *pvData;
    HI_U32                  u32Size;
}HDMI_TEE_PARAM_S;

extern TEEC_UUID HdmiTaskUUID;
HI_S32 DRV_HDMI_TeeOpen(HDMI_DEVICE_ID_E enHdmiId);
HI_S32 DRV_HDMI_TeeCmdSend(HDMI_DEVICE_ID_E enHdmiId, HDMI_TEE_PARAM_S *pstParam);
HI_S32 DRV_HDMI_TeeClose(HDMI_DEVICE_ID_E enHdmiId);


#endif

