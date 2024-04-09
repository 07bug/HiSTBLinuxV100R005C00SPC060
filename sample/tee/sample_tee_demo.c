#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "tee_client_api.h"

#define DEMO_DEBUG
#define LOG_PRINTF					printf
#define LOG_ERR(fmt, arg...)		LOG_PRINTF("[ERR][%s][%d] " fmt , __FUNCTION__, __LINE__, ## arg)

#ifdef  DEMO_DEBUG
#define LOG_DBG(fmt, arg...)		LOG_PRINTF("[DBG][%s][%d] " fmt , __FUNCTION__, __LINE__, ## arg)
#else
#define LOG_DBG(fmt, arg...)
#endif

int main(int argc, char* argv[])
{
	TEEC_Context context;
	TEEC_Session session;
	TEEC_Result result;
	TEEC_Operation operation;
	TEEC_Operation sess_op;
	uint32_t origin;
	unsigned int cmd = 0;

	/* uuid */
	TEEC_UUID svc_id = {0x8f194022, 0xc9a2, 0x11e6,
		{0x9d, 0x9d, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01}};

	if (1 >= argc)
	{
		printf("Usage: sample_tee_demo cmd \n"
		       "       cmd:  0--Hello Secure World Test\n"
		      );
		return 0;
	}
	cmd = strtoul(argv[1], NULL, 0);

	/* init context     */
	result = TEEC_InitializeContext(NULL, &context);
	if(result != TEEC_SUCCESS) {
		LOG_ERR("InitializeContext failed, ReturnCode=0x%x\n", result);
		goto cleanup_1;
	} else {
		LOG_DBG("InitializeContext success\n");
	}

	/* open session   */
	memset(&sess_op, 0, sizeof(TEEC_Operation));
	sess_op.started = 1;
	sess_op.paramTypes = TEEC_PARAM_TYPES(
					      TEEC_NONE,
					      TEEC_NONE,
					      TEEC_MEMREF_TEMP_INPUT,
					      TEEC_MEMREF_TEMP_INPUT);
	result = TEEC_OpenSession(&context, &session, &svc_id,
				  TEEC_LOGIN_IDENTIFY, NULL, &sess_op, &origin);
	if(result != TEEC_SUCCESS) {
		LOG_ERR("OpenSession failed, ReturnCode=0x%x, ReturnOrigin=0x%x\n", result, origin);
		goto cleanup_2;
	} else {
		LOG_DBG("OpenSession success\n");
	}

	/* invoke cmd    */
	memset(&operation, 0x0, sizeof(TEEC_Operation));
	operation.started = 1;
	operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE,
						TEEC_NONE,
						TEEC_NONE,
						TEEC_VALUE_INOUT);
	operation.params[3].value.a = 0x11111111;
	operation.params[3].value.b = 0x22222222;
	result = TEEC_InvokeCommand( &session, cmd, &operation, &origin);
	if (result != TEEC_SUCCESS) {
		LOG_ERR("InvokeCommand failed, ReturnCode=0x%x, ReturnOrigin=0x%x\n", result, origin);
		while(1);
		goto cleanup_3;
	} else {
		LOG_DBG("InvokeCommand success\n");
		LOG_DBG("value a=0x%x, b=0x%x\n", operation.params[3].value.a,
			   operation.params[3].value.b);
	}

cleanup_3:
	TEEC_CloseSession(&session);
cleanup_2:
	TEEC_FinalizeContext(&context);
cleanup_1:
	return 0;
}

