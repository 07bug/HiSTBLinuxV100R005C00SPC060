/*
 * Copyright (c) 2016, Hisilicon Limited.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
#include <linux/module.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/io.h>
#include <linux/vmalloc.h>
#include <linux/tee_drv.h>
#include <linux/mutex.h>
#include "teek_client_api.h"
#include "../tee_private.h"

static DEFINE_MUTEX(teec_mutex);

static int optee_match(struct tee_ioctl_version_data *vers, const void *data)
{
	struct tee_ioctl_version_data v = {
		.impl_id = TEE_IMPL_ID_OPTEE,
		.impl_caps = TEE_OPTEE_CAP_TZ,
		.gen_caps = TEE_GEN_CAP_GP,
	};
	char *name = "optee-tz";

	if (!vers)
		return 0;

	/* If data is not null, it must be the string optee-tz */
	if (data && strncmp(data, "optee-tz", strlen(name)))
		return 0;

	if (vers && memcmp(&v, vers, sizeof(v)))
		return 0;

	return 1;
}

TEEC_Result TEEK_InitializeContext(const char *name, TEEC_Context *context)
{
	struct tee_context *ctx;

	if (!context)
		return TEEC_ERROR_BAD_PARAMETERS;

	ctx = tee_client_open_context(NULL, optee_match, name, NULL);
	if (IS_ERR(ctx)) {
		pr_err("%s - can't get device [%s]\n", __func__, name);
		return TEEC_ERROR_BAD_PARAMETERS;
	}

	context->ctx = ctx;

	return TEEC_SUCCESS;
}
EXPORT_SYMBOL(TEEK_InitializeContext);

void TEEK_FinalizeContext(TEEC_Context *context)
{
	if (!context || !context->ctx) {
		pr_err("%s - can't release context %p\n", __func__,
		       context);
		return;
	}

	tee_client_close_context(context->ctx);

	return;
}
EXPORT_SYMBOL(TEEK_FinalizeContext);

static TEEC_Result teec_pre_process_tmpref(TEEC_Context *ctx,
			uint32_t param_type, TEEC_TempMemoryReference *tmpref,
			struct tee_param *param,
			TEEC_SharedMemory *shm)
{
	TEEC_Result res;

	switch (param_type) {
	case TEEC_MEMREF_TEMP_INPUT:
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT;
		shm->flags = TEEC_MEM_INPUT;
		break;
	case TEEC_MEMREF_TEMP_OUTPUT:
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT;
		shm->flags = TEEC_MEM_OUTPUT;
		break;
	case TEEC_MEMREF_TEMP_INOUT:
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
		shm->flags = TEEC_MEM_INPUT | TEEC_MEM_OUTPUT;
		break;
	default:
		return TEEC_ERROR_BAD_PARAMETERS;
	}
	shm->size = tmpref->size;

	res = TEEK_AllocateSharedMemory(ctx, shm);
	if (res != TEEC_SUCCESS)
		return res;

	memcpy(shm->buffer, tmpref->buffer, tmpref->size);
	param->u.memref.size = tmpref->size;
	param->u.memref.shm = tee_shm_get_from_id(ctx->ctx, shm->id);
	return TEEC_SUCCESS;
}

static TEEC_Result teec_pre_process_whole(TEEC_Context *ctx,
			TEEC_RegisteredMemoryReference *memref,
			struct tee_param *param)
{
	const uint32_t inout = TEEC_MEM_INPUT | TEEC_MEM_OUTPUT;
	uint32_t flags = memref->parent->flags & inout;
	TEEC_SharedMemory *shm;

	if (flags == inout)
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
	else if (flags & TEEC_MEM_INPUT)
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT;
	else if (flags & TEEC_MEM_OUTPUT)
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT;
	else
		return TEEC_ERROR_BAD_PARAMETERS;

	shm = memref->parent;
	/*
	 * We're using a shadow buffer in this reference, copy the real buffer
	 * into the shadow buffer if needed. We'll copy it back once we've
	 * returned from the call to secure world.
	 */
	if (shm->shadow_buffer && (flags & TEEC_MEM_INPUT))
		memcpy(shm->shadow_buffer, shm->buffer, shm->size);

	param->u.memref.shm = tee_shm_get_from_id(ctx->ctx, shm->id);
	param->u.memref.size = shm->size;
	return TEEC_SUCCESS;
}

static TEEC_Result teec_pre_process_partial(TEEC_Context *ctx,
			uint32_t param_type,
			TEEC_RegisteredMemoryReference *memref,
			struct tee_param *param)
{
	uint32_t req_shm_flags;
	TEEC_SharedMemory *shm;

	switch (param_type) {
	case TEEC_MEMREF_PARTIAL_INPUT:
		req_shm_flags = TEEC_MEM_INPUT;
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT;
		break;
	case TEEC_MEMREF_PARTIAL_OUTPUT:
		req_shm_flags = TEEC_MEM_OUTPUT;
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT;
		break;
	case TEEC_MEMREF_PARTIAL_INOUT:
		req_shm_flags = TEEC_MEM_OUTPUT | TEEC_MEM_INPUT;
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT;
		break;
	default:
		return TEEC_ERROR_BAD_PARAMETERS;
	}

	shm = memref->parent;

	if ((shm->flags & req_shm_flags) != req_shm_flags)
		return TEEC_ERROR_BAD_PARAMETERS;

	/*
	 * We're using a shadow buffer in this reference, copy the real buffer
	 * into the shadow buffer if needed. We'll copy it back once we've
	 * returned from the call to secure world.
	 */
	if (shm->shadow_buffer && param_type != TEEC_MEMREF_PARTIAL_OUTPUT)
		memcpy((char *)shm->shadow_buffer + memref->offset,
		       (char *)shm->buffer + memref->offset, memref->size);

	param->u.memref.shm = tee_shm_get_from_id(ctx->ctx, shm->id);
	param->u.memref.shm_offs = memref->offset;
	param->u.memref.size = memref->size;
	return TEEC_SUCCESS;
}

static TEEC_Result teec_pre_process_operation(TEEC_Context *ctx,
			TEEC_Operation *operation,
			struct tee_param *params,
			TEEC_SharedMemory *shms)
{
	TEEC_Result res;
	size_t n;

	memset(shms, 0, sizeof(TEEC_SharedMemory) *
			TEEC_CONFIG_PAYLOAD_REF_COUNT);
	if (!operation) {
		memset(params, 0, sizeof(struct tee_ioctl_param) *
				  TEEC_CONFIG_PAYLOAD_REF_COUNT);
		return TEEC_SUCCESS;
	}

	for (n = 0; n < TEEC_CONFIG_PAYLOAD_REF_COUNT; n++) {
		uint32_t param_type;

		param_type = TEEC_PARAM_TYPE_GET(operation->paramTypes, n);
		switch (param_type) {
		case TEEC_NONE:
			params[n].attr = param_type;
			break;
		case TEEC_VALUE_INPUT:
		case TEEC_VALUE_OUTPUT:
		case TEEC_VALUE_INOUT:
			params[n].attr = param_type;
			params[n].u.value.a = operation->params[n].value.a;
			params[n].u.value.b = operation->params[n].value.b;
			break;
		case TEEC_MEMREF_TEMP_INPUT:
		case TEEC_MEMREF_TEMP_OUTPUT:
		case TEEC_MEMREF_TEMP_INOUT:
			res = teec_pre_process_tmpref(ctx, param_type,
				&operation->params[n].tmpref, params + n,
				shms + n);
			if (res != TEEC_SUCCESS)
				return res;
			break;
		case TEEC_MEMREF_WHOLE:
			res = teec_pre_process_whole(ctx,
					&operation->params[n].memref,
					params + n);
			if (res != TEEC_SUCCESS)
				return res;
			break;
		case TEEC_MEMREF_PARTIAL_INPUT:
		case TEEC_MEMREF_PARTIAL_OUTPUT:
		case TEEC_MEMREF_PARTIAL_INOUT:
			res = teec_pre_process_partial(ctx, param_type,
				&operation->params[n].memref, params + n);
			if (res != TEEC_SUCCESS)
				return res;
			break;
		default:
			return TEEC_ERROR_BAD_PARAMETERS;
		}
	}

	return TEEC_SUCCESS;
}

static void teec_post_process_tmpref(uint32_t param_type,
			TEEC_TempMemoryReference *tmpref,
			struct tee_param *param,
			TEEC_SharedMemory *shm)
{
	if (param_type != TEEC_MEMREF_TEMP_INPUT) {
		if (param->u.memref.size <= tmpref->size && tmpref->buffer)
			memcpy(tmpref->buffer, shm->buffer,
			       param->u.memref.size);

		tmpref->size = param->u.memref.size;
	}
}

static void teec_post_process_whole(TEEC_RegisteredMemoryReference *memref,
			struct tee_param *param)
{
	TEEC_SharedMemory *shm = memref->parent;

	if (shm->flags & TEEC_MEM_OUTPUT) {

		/*
		 * We're using a shadow buffer in this reference, copy back
		 * the shadow buffer into the real buffer now that we've
		 * returned from secure world.
		 */
		if (shm->shadow_buffer && param->u.memref.size <= memref->size)
			memcpy(shm->buffer, shm->shadow_buffer,
			       param->u.memref.size);

		memref->size = param->u.memref.size;
	}
}

static void teec_post_process_partial(uint32_t param_type,
			TEEC_RegisteredMemoryReference *memref,
			struct tee_param *param)
{
	if (param_type != TEEC_MEMREF_PARTIAL_INPUT) {
		TEEC_SharedMemory *shm = memref->parent;

		/*
		 * We're using a shadow buffer in this reference, copy back
		 * the shadow buffer into the real buffer now that we've
		 * returned from secure world.
		 */
		if (shm->shadow_buffer && param->u.memref.size <= memref->size)
			memcpy((char *)shm->buffer + memref->offset,
			       (char *)shm->shadow_buffer + memref->offset,
			       param->u.memref.size);

		memref->size = param->u.memref.size;
	}
}

static void teec_post_process_operation(TEEC_Operation *operation,
			struct tee_param *params,
			TEEC_SharedMemory *shms)
{
	size_t n;

	if (!operation)
		return;

	for (n = 0; n < TEEC_CONFIG_PAYLOAD_REF_COUNT; n++) {
		uint32_t param_type;

		param_type = TEEC_PARAM_TYPE_GET(operation->paramTypes, n);
		switch (param_type) {
		case TEEC_VALUE_INPUT:
			break;
		case TEEC_VALUE_OUTPUT:
		case TEEC_VALUE_INOUT:
			operation->params[n].value.a = params[n].u.value.a;
			operation->params[n].value.b = params[n].u.value.b;
			break;
		case TEEC_MEMREF_TEMP_INPUT:
		case TEEC_MEMREF_TEMP_OUTPUT:
		case TEEC_MEMREF_TEMP_INOUT:
			teec_post_process_tmpref(param_type,
				&operation->params[n].tmpref, params + n,
				shms + n);
			break;
		case TEEC_MEMREF_WHOLE:
			teec_post_process_whole(&operation->params[n].memref,
						params + n);
			break;
		case TEEC_MEMREF_PARTIAL_INPUT:
		case TEEC_MEMREF_PARTIAL_OUTPUT:
		case TEEC_MEMREF_PARTIAL_INOUT:
			teec_post_process_partial(param_type,
				&operation->params[n].memref, params + n);
		default:
			break;
		}
	}
}

static void teec_free_temp_refs(TEEC_Operation *operation,
			TEEC_SharedMemory *shms)
{
	size_t n;

	if (!operation)
		return;

	for (n = 0; n < TEEC_CONFIG_PAYLOAD_REF_COUNT; n++) {
		switch (TEEC_PARAM_TYPE_GET(operation->paramTypes, n)) {
		case TEEC_MEMREF_TEMP_INPUT:
		case TEEC_MEMREF_TEMP_OUTPUT:
		case TEEC_MEMREF_TEMP_INOUT:
			TEEK_ReleaseSharedMemory(shms + n);
			break;
		default:
			break;
		}
	}
}

static TEEC_Result linux_errno_to_res(int err)
{
	switch (err) {
	case -ENOMEM:
		return TEEC_ERROR_OUT_OF_MEMORY;
	default:
		return TEEC_ERROR_GENERIC;
	}
}

static void uuid_to_octets(uint8_t d[TEE_IOCTL_UUID_LEN], const TEEC_UUID *s)
{
	d[0] = s->timeLow >> 24;
	d[1] = s->timeLow >> 16;
	d[2] = s->timeLow >> 8;
	d[3] = s->timeLow;
	d[4] = s->timeMid >> 8;
	d[5] = s->timeMid;
	d[6] = s->timeHiAndVersion >> 8;
	d[7] = s->timeHiAndVersion;
	memcpy(d + 8, s->clockSeqAndNode, sizeof(s->clockSeqAndNode));
}


TEEC_Result TEEK_OpenSession(TEEC_Context *context,
			     TEEC_Session *session,
			     const TEEC_UUID *destination,
			     uint32_t connection_method,
			     const void *connectionData,
			     TEEC_Operation *operation,
			     uint32_t *ret_origin)
{
	uint64_t buf[(sizeof(struct tee_ioctl_open_session_arg) +
			TEEC_CONFIG_PAYLOAD_REF_COUNT *
				sizeof(struct tee_param))/
				sizeof(uint64_t)] = { 0 };
	struct tee_context *ctx;
	struct tee_ioctl_open_session_arg *arg;
	struct tee_param *params;
	TEEC_SharedMemory shm[TEEC_CONFIG_PAYLOAD_REF_COUNT];
	TEEC_Result res;
	uint32_t eorig;
	int rc;

	if (!context || !context->ctx || !session ||
			!destination)
		return TEEC_ERROR_BAD_PARAMETERS;

	arg = (struct tee_ioctl_open_session_arg *)buf;
	arg->num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;
	params = (struct tee_param *)(arg + 1);

	uuid_to_octets(arg->uuid, destination);
	arg->clnt_login = connection_method;

	ctx = (struct tee_context *)context->ctx;

	res = teec_pre_process_operation(context, operation, params, shm);
	if (res != TEEC_SUCCESS) {
		eorig = TEEC_ORIGIN_API;
		goto out_free_temp_refs;
	}

	rc = tee_client_open_session(ctx, arg, params);
	if (rc) {
		pr_err("%s failed rc:%d\n", __func__, rc);
		res = linux_errno_to_res(rc);
		eorig = TEEC_ORIGIN_COMMS;
		goto out_free_temp_refs;
	}

	res = arg->ret;
	eorig = arg->ret_origin;
	if (res == TEEC_SUCCESS) {
		session->ctx = context;
		session->session_id = arg->session;
	}
	teec_post_process_operation(operation, params, shm);

out_free_temp_refs:
	teec_free_temp_refs(operation, shm);

	if (ret_origin)
		*ret_origin = eorig;
	return res;
}
EXPORT_SYMBOL(TEEK_OpenSession);

void TEEK_CloseSession(TEEC_Session *session)
{
	if (session && session->ctx && session->ctx->ctx)
		tee_client_close_session(session->ctx->ctx,
					session->session_id);
}
EXPORT_SYMBOL(TEEK_CloseSession);

TEEC_Result TEEK_InvokeCommand(TEEC_Session *session,
			       uint32_t cmd_id,
			       TEEC_Operation *operation,
			       uint32_t *ret_origin)
{
	uint64_t buf[(sizeof(struct tee_ioctl_invoke_arg) +
			TEEC_CONFIG_PAYLOAD_REF_COUNT *
				sizeof(struct tee_ioctl_param)) /
			sizeof(uint64_t)] = { 0 };
	struct tee_ioctl_invoke_arg *arg;
	struct tee_param *params;
	struct tee_context *ctx;
	TEEC_Result res;
	uint32_t eorig;
	TEEC_SharedMemory shm[TEEC_CONFIG_PAYLOAD_REF_COUNT];
	int rc;

	if (!session)
		return TEEC_ERROR_BAD_PARAMETERS;

	arg = (struct tee_ioctl_invoke_arg *)buf;
	arg->num_params = TEEC_CONFIG_PAYLOAD_REF_COUNT;
	params = (struct tee_param *)(arg + 1);

	arg->session = session->session_id;
	arg->func = cmd_id;

	ctx = (struct tee_context *)session->ctx->ctx;

	if (operation) {
		mutex_lock(&teec_mutex);
		operation->session = session;
		mutex_unlock(&teec_mutex);
	}

	res = teec_pre_process_operation(session->ctx, operation, params, shm);
	if (res != TEEC_SUCCESS) {
		eorig = TEEC_ORIGIN_API;
		goto out_free_temp_refs;
	}

	rc = tee_client_invoke_func(ctx, arg, params);
	if (rc) {
		pr_err("%s failed rc:%d\n", __func__, rc);
		res = linux_errno_to_res(rc);
		eorig = TEEC_ORIGIN_COMMS;
		goto out_free_temp_refs;
	}

	res = arg->ret;
	eorig = arg->ret_origin;
	teec_post_process_operation(operation, params, shm);

out_free_temp_refs:
	teec_free_temp_refs(operation, shm);

	if (ret_origin)
		*ret_origin = eorig;
	return res;

}
EXPORT_SYMBOL(TEEK_InvokeCommand);

TEEC_Result TEEK_RegisterSharedMemory(TEEC_Context *context,
				      TEEC_SharedMemory *shared_memory)
{
	struct tee_shm *shm;

	if (!context || !context->ctx || !shared_memory)
		return TEEC_ERROR_BAD_PARAMETERS;

	if (!shared_memory->flags ||
	    (shared_memory->flags & ~(TEEC_MEM_INPUT | TEEC_MEM_OUTPUT)))
		return TEEC_ERROR_BAD_PARAMETERS;

	shared_memory->id = -1;
	shm = tee_shm_alloc(context->ctx, shared_memory->size,
				TEE_SHM_MAPPED);
	if (IS_ERR(shm)) {
		pr_err("%s: tee_shm_alloc(%zd) failed\n", __func__,
		       shared_memory->size);
		return TEEC_ERROR_OUT_OF_MEMORY;
	}
	shared_memory->id = shm->id;
	shared_memory->size = shm->size;

	shared_memory->shadow_buffer = shm->kaddr;
	shared_memory->ctx = context->ctx;

	shared_memory->alloced_size = shm->size;
	return TEEC_SUCCESS;
}
EXPORT_SYMBOL(TEEK_RegisterSharedMemory);

TEEC_Result TEEK_AllocateSharedMemory(TEEC_Context *context,
				      TEEC_SharedMemory *shared_memory)
{
	struct tee_shm *shm;

	if (!context || !context->ctx || !shared_memory)
		return TEEC_ERROR_BAD_PARAMETERS;

	if (!shared_memory->flags ||
	    (shared_memory->flags & ~(TEEC_MEM_INPUT | TEEC_MEM_OUTPUT)))
		return TEEC_ERROR_BAD_PARAMETERS;

	shared_memory->id = -1;

	shm = tee_shm_alloc(context->ctx, shared_memory->size,
				TEE_SHM_MAPPED);
	if (IS_ERR(shm)) {
		pr_err("%s: tee_shm_alloc(%zu) failed\n", __func__,
		       shared_memory->size);
		return TEEC_ERROR_OUT_OF_MEMORY;
	}
	shared_memory->id = shm->id;
	shared_memory->size = shm->size;
	shared_memory->buffer = shm->kaddr;

	shared_memory->shadow_buffer = NULL;
	shared_memory->alloced_size = shm->size;
	shared_memory->ctx = context->ctx;

	return TEEC_SUCCESS;
}
EXPORT_SYMBOL(TEEK_AllocateSharedMemory);

void TEEK_ReleaseSharedMemory(TEEC_SharedMemory *shared_memory)
{
	struct tee_shm *shm;

	if (!shared_memory || !shared_memory->ctx || shared_memory->id == -1)
		return;

	shm = tee_shm_get_from_id(shared_memory->ctx, shared_memory->id);
	if (IS_ERR(shm)) {
		pr_err("tee_shm_get_from_id failed %s fd=%d ctx=%p\n", __func__,
			shared_memory->id, shared_memory->ctx);
		return;
	}

	tee_shm_free(shm);

	shared_memory->buffer = NULL;
	shared_memory->id = -1;

	shared_memory->ctx = NULL;
	shared_memory->shadow_buffer = NULL;
}
EXPORT_SYMBOL(TEEK_ReleaseSharedMemory);
