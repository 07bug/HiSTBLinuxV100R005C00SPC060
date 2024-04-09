/**
 * @file tee_client_random_api.h
 *
 * Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ��������������������ӿ�\n
 */

/** @defgroup TEEC_RandomAPI ���������
 *@ingroup TEEC_API
 */

#ifndef _TEE_CLIENT_RANDOM_API_H_
#define _TEE_CLIENT_RANDOM_API_H_

/**
 * @ingroup  TEEC_RandomAPI
 * @brief �򿪰�ȫ�ӽ��ܷ���
 *
 * @par ����:
 * �򿪰�ȫ�ӽ��ܷ���ɹ����ǶԲ����������ǰ��
 *
 * @attention ��
 * @param ��
 *
 * @retval #TEEC_SUCCESS �򿪰�ȫ�ӽ��ܷ���ɹ�
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_random_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_UninitCryptoService
 * @since V100R002C00B302
 */
TEEC_Result TEEC_InitCryptoService();

/**
 * @ingroup  TEEC_RandomAPI
 * @brief �رհ�ȫ�ӽ��ܷ���
 *
 * @par ����:
 * �رհ�ȫ�ӽ��ܷ���
 *
 * @attention ��
 * @param ��
 *
 * @retval #TEEC_SUCCESS �رհ�ȫ�ӽ��ܷ���ɹ�
 * @retval #TEEC_ERROR_BAD_STATE �ӽ��ܷ����δ��
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_random_api.h���ýӿ���������ͷ�ļ�
 * @see TEEC_InitCryptoService
 * @since V100R002C00B302
 */
TEEC_Result TEEC_UninitCryptoService();

/**
 * @ingroup  TEEC_RandomAPI
 * @brief ���������
 *
 * @par ����:
 * ���ɴ�СΪoutsize����������������������ɹ����������outputΪ���������
 *
 * @attention ��
 * @param output [OUT] �����������
 * @param outsize [IN] ��������ȣ����ֽ�Ϊ��λ�����ֵΪ63KBytes
 *
 * @retval #TEEC_SUCCESS ����������ɹ�
 * @retval #TEEC_ERROR_BAD_PARAMETERS ����outputΪ�ջ�outsizeΪ��
 * @retval #TEEC_ERROR_BAD_STATE �ӽ��ܷ���δ��
 * @retval ��������ֵ�ο� #TEEC_ReturnCode
 *
 * @par ����:
 * @li libteec���ýӿ������Ĺ����
 * @li tee_client_random_api.h���ýӿ���������ͷ�ļ�
 * @since V100R002C00B306
 */
TEEC_Result TEEC_Random(uint8_t *output, uint32_t outsize);

#endif
/**
 * History: \n
 * 2013-6-14 sdk: Create this file\n
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/
