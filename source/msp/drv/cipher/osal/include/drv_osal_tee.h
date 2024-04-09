#ifndef __DRV_OSAL_TEE_H__
#define __DRV_OSAL_TEE_H__

#include "drv_osal_lib.h"

#define TEEC_CMD_GET_TRNG             0

s32 drv_osal_tee_open_session(void);
s32 drv_osal_tee_command(u32 command, void *params, u32 paramsize);
s32 drv_osal_tee_close_session(void);

#endif

