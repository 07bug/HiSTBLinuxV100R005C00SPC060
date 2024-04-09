/**
 * @file tee_client_storage_api.h
 *
 * Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ���������尲ȫ�洢�ӿ�\n
 */

/** @defgroup TEEC_StorageAPI ��ȫ�洢����ӿ�
 *@ingroup TEEC_API
 */

#ifndef _TEE_CLIENT_STORAGE_API_H_
#define _TEE_CLIENT_STORAGE_API_H_

#include "tee_client_type.h"

#define SFS_PROPERTY "trustedcore_sfs_property"
#define SFS_PROPERTY_VALUE "1"
/**
 * @ingroup  TEEC_StorageAPI
 *
 * ���ļ���ģʽ
 */
enum Data_Flag_Constants {
	TEE_DATA_FLAG_ACCESS_READ = 0x00000001,  /**< ֻ��ģʽ */
	TEE_DATA_FLAG_ACCESS_WRITE = 0x00000002,  /**< ֻдģʽ */
	TEE_DATA_FLAG_ACCESS_WRITE_META = 0x00000004,  /**< ������ļ�����ɾ�������������
    ����ʹ�ô�ģʽ�ȴ��ļ� */
	TEE_DATA_FLAG_SHARE_READ = 0x00000010,  /**< �����ģʽ ��
    ֻ���ڴ�ģʽ�£��ſ����Զ���ʽͬʱ��ͬһ���ļ� */
	TEE_DATA_FLAG_SHARE_WRITE = 0x00000020,  /**< ����дģʽ��
    ֻ���ڴ�ģʽ�£��ſ�����д��ʽͬʱ��ͬһ���ļ� */
	TEE_DATA_FLAG_CREATE = 0x00000200,  /**< �����ļ��������
    ���������ļ����������򸲸�ԭ���ļ� */
	TEE_DATA_FLAG_EXCLUSIVE = 0x00000400,  /**< ����ļ������ڣ��򴴽��ļ������򱨴� */
	TEE_DATA_FLAG_OVERWRITE = 0x00000400,
};

/**
 * @ingroup  TEEC_StorageAPI
 * @brief �򿪰�ȫ�洢����
 *
 * @par ����:
 * �򿪰�ȫ�洢����ɹ����Ƕ��ļ�������ǰ��
 *
 * @attention ��
 * @param ��
 *
 * @retval #TEEC_SUCCESS �򿪰�ȫ�洢����ɹ�
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_UninitStorageService
 * @since V100R002C00B302
 */
TEEC_Result TEEC_InitStorageService();

/**
 * @ingroup  TEEC_StorageAPI
 * @brief �رհ�ȫ�洢����
 *
 * @par ����:
 * �رհ�ȫ�洢����
 *
 * @attention ��
 * @param ��
 *
 * @retval #TEEC_SUCCESS �رհ�ȫ�洢����ɹ�
 * @retval #TEEC_ERROR_BAD_STATE ��ȫ�洢�����δ��
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_InitStorageService
 * @since V100R002C00B302
 */
TEEC_Result TEEC_UninitStorageService();

/**
 * @ingroup  TEEC_StorageAPI
 * @brief ���ļ�
 *
 * @par ����:
 * ��·��Ϊpath���ļ�����ģʽ��mode��ȡֵ��ΧΪ#Data_Flag_Constants
 *
 * @attention ��
 * @param path [IN] �ļ�·��
 * @param mode [IN] ���ļ��ķ�ʽ��ȡֵ��ΧΪ#Data_Flag_Constants
 *
 * @retval -1 ���ļ�ʧ�ܣ�û�г�ʼ����ȫ�洢���񡢻��ļ������ڡ�
 * �򲢷������ļ�ʱȨ��У��ʧ�ܣ���ͨ��#TEEC_GetFErr��ȡ������
 * @retval >=0 ���ļ��ɹ��������ļ�������
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FClose
 * @since V100R002C00B302
 */
int32_t TEEC_FOpen(char *path, uint32_t mode);

/**
 * @ingroup  TEEC_StorageAPI
 * @brief �ر��ļ�
 *
 * @par ����:
 * �ر�fd��ָ����ļ�
 *
 * @attention ��
 * @param fd [IN] �ļ�������
 *
 * @retval -1 �ر��ļ�ʧ�ܣ�û�г�ʼ����ȫ�洢���񡢻����fd��Ч��
 * ��ͨ��#TEEC_GetFErr��ȡ������
 * @retval 0 �ر��ļ��ɹ�
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FOpen
 * @since V100R002C00B302
 */
int32_t TEEC_FClose(int32_t fd);

/**
 * @ingroup  TEEC_StorageAPI
 * @brief ��ȡ�ļ�
 *
 * @par ����:
 * �Ӳ���fd��ָ���ļ���ȡ���ݵ�buf�У�����ȡsize���ֽ�
 *
 * @attention ��
 * @param fd [IN] �ļ�������
 * @param buf [IN] �ļ���ȡ���ݻ�����
 * @param size [IN] ��Ҫ��ȡ�Ĵ�С�����ֽ�Ϊ��λ�����ܴ���bufָ��Ļ�����
 *
 * @retval С��size ʵ�ʶ�ȡ���Ĵ�С����ȡ�ļ�ʱ��������������ļ�β��
 * ��ͨ������#TEEC_GetFErr��ȡ������
 * @retval ����size ��ȡ�ɹ�
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FOpen | TEEC_FClose | TEEC_GetFErr
 * @since V100R002C00B302
 */
size_t TEEC_FRead(int32_t fd, uint8_t *buf, size_t size);

/**
 * @ingroup  TEEC_StorageAPI
 * @brief д���ļ�
 *
 * @par ����:
 * �����fd��ָ���ļ�д������buf�����д��size���ֽ�
 *
 * @attention ��
 * @param fd [IN] �ļ�������
 * @param buf [IN] �ļ�д�����ݻ�����
 * @param size [IN] ��Ҫд��Ĵ�С�����ֽ�Ϊ��λ�����ܴ���bufָ��Ļ�����
 *
 * @retval С��size ʵ��д��Ĵ�С��д���ļ�ʱ��������������ļ�β��
 * ��ͨ������#TEEC_GetFErr��ȡ������
 * @retval ����size д��ɹ�
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FOpen | TEEC_FClose | TEEC_GetFErr
 * @since V100R002C00B302
 */
size_t TEEC_FWrite(int32_t fd, uint8_t *buf, size_t size);
/**
 * @ingroup  TEEC_StorageAPI
 * @brief �ض�λ�ļ�
 *
 * @par ����:
 * �ض�λ�ļ�
 *
 * @attention ��
 * @param ��
 *
 * @retval #TEEC_SUCCESS ��ȡ�ɹ�
 * @retval
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FOpen
 * @since V100R003C00B061
 */
int32_t TEEC_FSeek(int32_t fd, int32_t offset, int32_t fromwhere);
/**
 * @ingroup  TEEC_StorageAPI
 * @brief ��ȡ�ļ���Ϣ
 *
 * @par ����:
 * ��ȡ��ǰ�ļ�λ���Լ��ļ�����
 *
 * @attention ��
 * @param ��
 *
 * @retval #TEEC_SUCCESS ��ȡ�ɹ�
 * @retval
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FOpen
 * @since V100R003C00B061
 */
size_t TEEC_FInfo(int32_t fd, uint32_t *pos, uint32_t *len);
/**
 * @ingroup  TEEC_StorageAPI
 * @brief �رղ�ɾ���ļ�
 *
 * @par ����:
 * �رղ�ɾ����Ӧ�ļ�
 *
 * @attention ��
 * @param ��
 *
 * @retval #TEEC_SUCCESS ɾ���ɹ�
 * @retval
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FOpen
 * @since V100R003C00B061
 */
int32_t TEEC_FCloseAndDelete(int32_t fd);

/**
 * @ingroup  TEEC_StorageAPI
 * @brief sync�ļ���flash
 *
 * @par ����:
 * sync�ļ���flash
 *
 * @attention ��
 * @param ��
 *
 * @retval #TEEC_SUCCESS ɾ���ɹ�
 * @retval
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FOpen
 * @since V100R003C00B061
 */
int32_t TEEC_FSync(int32_t fd);

/**
 * @ingroup  TEEC_StorageAPI
 * @brief ��ȡ������
 *
 * @par ����:
 * ��ȡ��ȫ�洢����Ĵ�����
 *
 * @attention ��
 * @param ��
 *
 * @retval #TEEC_SUCCESS û�д������
 * @retval #TEEC_ERROR_BAD_STATE ��ȫ�洢�����δ��
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_storage_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_FRead | TEEC_FWrite
 * @since V100R002C00B302
 */
TEEC_Result TEEC_GetFErr();

#endif
/**
 * History: \n
 * 2013-4-12 sdk: Create this file\n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/
