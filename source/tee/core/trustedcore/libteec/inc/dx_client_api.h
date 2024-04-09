/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : dx_client_api.h
* Description :
* Platform    :
* Author      : qiqingchao
* Version     : V1.0
* Date        : 2013.5.29
* Notes       :
*
*------------------------------------------------------------------------------
* Modifications:
*   Date        Author          Modifications
*******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/
/**
 * @file dx_client_api.h
 *
 * Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������������DX content path�ͻ��˽ӿ�\n
 */

/**@defgroup dx_client_api ������DX�ͻ��˽ӿ�
 *@ingroup TEEC_API
*/

#ifndef _DX_CLIENT_API_H_
#define _DX_CLIENT_API_H_

#include "tee_client_type.h"
/**
 * @ingroup dx_client_api
 * ��ȫ�ڴ����ݶ��볤�ȶ���
 */
#define ALIGN_SIZE 0x8000 //32KB
/**
 * @ingroup dx_client_api
 * ���ؽ������
 */
typedef TEEC_Result    DxStatus;
/**
 * @ingroup dx_client_api
 * DX�ͻ��˻Ự���ݽṹ
 */
typedef struct {
	bool cp_init_flag;      /**< ���ð�ȫ�ڴ�ı�־λ 0:����ȫ����;1:��ȫ�ͷǰ�ȫ���ܷ���*/
	TEEC_Session *session;  /**< ����DX�ӿڵĻỰ���� */
	uint32_t size;          /**< ����buffer��С */
	uint8_t *base_addr;     /**< ����buffer��ַ */
	uint8_t *virtual_addr;  /**< ����buffer�����ַ */
	TEEC_SharedMemory *sharedMem;   /**< �����ڴ汸�� */
} *Dx_Client_Tz_Session, Dx_Client_Tz_Session_val;
/**
 * @ingroup  dx_client_api
 * @brief DX�ͻ������ð�ȫ�ڴ�
 *
 * @par ����:
 * DX�ͻ�������һ���ڴ棬��֪ͨ��ȫ�ཫ������Ϊ����ȫ����
 *
 * @attention ��
 * @param pSession [IN] DX�ͻ��˻Ự���ݽṹ #Dx_Client_Tz_Session
 *
 * @retval #TEEC_SUCCESS ���ð�ȫ�ڴ�ɹ�
 * @retval #TEEC_ERROR_BAD_PARAMETERS �����������
 * @retval #TEEC_ReturnCode ͨ�ÿͻ���API����ֵ
 *
 * @par ����:
 * @li DX�ͻ��˽ӿ�
 * @li tee_client_type.h �����������ͺ����ݽṹ
 * @see DxTzClient_TerminateSecureContentPath
 * @since V100R002C00B302
*/
DxStatus DxTzClient_InitSecureContentPath(Dx_Client_Tz_Session pSession);
/**
 * @ingroup  dx_client_api
 * @brief DX�ͻ��˽����ȫ�ڴ�
 *
 * @par ����:
 * DX�ͻ��˽����ȫ�ڴ�����ƣ����ӷǰ�ȫ���ͷ��ڴ�
 *
 * @attention ��
 * @param pSession [IN] DX�ͻ��˻Ự���ݽṹ #Dx_Client_Tz_Session
 *
 * @retval TEEC_SUCCESS �ͷŰ�ȫ�ڴ�ɹ�
 * @retval TEEC_ERROR_BAD_PARAMETERS �ͷŰ�ȫ�ڴ�ʧ��
 * @retval #TEEC_ReturnCode ͨ�ÿͻ���API����ֵ
 *
 * @par ����:
 * @li DX�ͻ��˽ӿ�
 * @li tee_client_type.h �����������ͺ����ݽṹ
 * @see DxTzClient_InitSecureContentPath
 * @since V100R002C00B302
*/
DxStatus DxTzClient_TerminateSecureContentPath(Dx_Client_Tz_Session pSession);

#endif
