/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_common_ext.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2006/02/09
  Description   :
  History       :
  1.Date        : 2006/02/09
    Modification: Created file

  2.Date         : 2006/2/9
    Modification : Modified some macro for coherence
                   with mpi_struct.h

  3.Date         : 2010/1/25
    Modification : Modified for X5HD common module

******************************************************************************/
#include <linux/string.h>
#include <linux/kernel.h>
#include "hi_drv_dev.h"
#include "hi_drv_mmz.h"
#include "hi_osal.h"



#include "linux/mutex.h"

#include "hi_type.h"
#include "hi_module.h"
#include "hi_debug.h"
#include "hi_drv_sys.h"
#include "teek_client_api.h"

#ifdef COMMON_TEE_SUPPORT

#define TEEC_CMD_GET_VERSION           0

typedef struct hiCommon_Teec_S
{
    TEEC_Context context;
    TEEC_Session session;
    HI_BOOL  connected;
    struct mutex lock;
}Common_Teec_S;



HI_BOOL bCommonFlag = HI_FALSE;
typedef struct hiCOMMON_COMM_S
{
    Common_Teec_S    teec;
    HI_S32       (*SendCmdToTA)(HI_U32 CmdId, TEEC_Operation *Operation, HI_U32 *RetOrigin);
} COMMON_COMM_S;

static HI_S32 Common_SendCmdToTA(HI_U32 CmdId, TEEC_Operation *Operation, HI_U32 *RetOrigin);

static COMMON_COMM_S g_stCommonComm = {
      .SendCmdToTA     = Common_SendCmdToTA,
       };


static HI_S32 CommonInitTeec(COMMON_COMM_S *CommonCom)
{
    HI_S32 ret = HI_FAILURE;
    TEEC_UUID CommonTaskUUID =
    {\
        0x000ac3b0, \
        0xbf6f, \
        0x11e7, \
        {0x8f, 0x1a, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66}
    };
    TEEC_Operation Operation;
    HI_CHAR GeneralSessionName[] = "tee_common_session";
    HI_U32 RootId = 0;

    mutex_lock(&CommonCom->teec.lock);

     if (unlikely(HI_TRUE == CommonCom->teec.connected))
     {
        ret = HI_SUCCESS;
        goto out0;
     }

    ret = TEEK_InitializeContext(NULL, &CommonCom->teec.context);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("Initialise common teec context failed(0x%x)", ret);
        goto out1;
    }
    memset(&Operation, 0x0, sizeof(TEEC_Operation));
    Operation.started = 1;
    Operation.cancel_flag = 0;
    Operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT);
    Operation.params[2].tmpref.buffer = (void *)(&RootId);
    Operation.params[2].tmpref.size = sizeof(RootId);
    Operation.params[3].tmpref.buffer = (void *)(GeneralSessionName);
    Operation.params[3].tmpref.size = strlen(GeneralSessionName) + 1;

    ret = TEEK_OpenSession(&CommonCom->teec.context, &CommonCom->teec.session, &CommonTaskUUID, TEEC_LOGIN_IDENTIFY, NULL, &Operation, NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("open common teec session failed(0x%x)\n", ret);
        goto out2;
    }

    CommonCom->teec.connected = HI_TRUE;

    mutex_unlock(&CommonCom->teec.lock);

    return HI_SUCCESS;

out2:
    TEEK_FinalizeContext(&CommonCom->teec.context);
out1:
    CommonCom->teec.connected = HI_FALSE;
out0:
    mutex_unlock(&CommonCom->teec.lock);
    return ret;
}

static HI_VOID CommonDeinitTeec(COMMON_COMM_S *CommonCom)
{
    mutex_lock(&CommonCom->teec.lock);

    if (HI_TRUE == CommonCom->teec.connected)
    {
        CommonCom->teec.connected = HI_FALSE;

        TEEK_CloseSession(&CommonCom->teec.session);

        TEEK_FinalizeContext(&CommonCom->teec.context);
    }

    mutex_unlock(&CommonCom->teec.lock);
}

/*common SendCmdToTA*/
static HI_S32 Common_SendCmdToTA(HI_U32 CmdId, TEEC_Operation *Operation, HI_U32 *RetOrigin)
{
    HI_S32 ret = HI_FAILURE;
    COMMON_COMM_S *CommonCom = &g_stCommonComm;

    if (unlikely(HI_FALSE == CommonCom->teec.connected))
    {
        ret = CommonInitTeec(CommonCom);
        if (HI_SUCCESS != ret)
        {
            goto out;
        }
    }

    ret = TEEK_InvokeCommand(&CommonCom->teec.session, CmdId, Operation, RetOrigin);

out:
    return ret;
}

/*GetSecureOSImageVersion  Need first init COMMON TEE*/
/* The Secure OS Version format:HiSTBLinuxV100R005C00SPC050_MSID_0x02_VER_0x02_20171019_20:49:10 */
HI_S32 HI_DRV_SYS_GetSecureOSImageVersion(HI_CHAR *pVersion,HI_U32 u32VersionLen)
{
    HI_S32 ret = HI_FAILURE;
    TEEC_Operation operation;
    HI_SYS_MEM_CONFIG_S stConfig = {0};
    COMMON_COMM_S *CommonCom = &g_stCommonComm;

    ret = HI_DRV_SYS_GetMemConfig(&stConfig);
    if (HI_SUCCESS != ret)
    {
        goto out;
    }

    memset(pVersion, 0x00, u32VersionLen);

    operation.started = 1;
    operation.params[0].tmpref.buffer = (HI_VOID *)pVersion;
    operation.params[0].tmpref.size   = u32VersionLen;
    operation.params[1].value.a = stConfig.u32TotalSize;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE);

    ret = CommonCom->SendCmdToTA(TEEC_CMD_GET_VERSION, &operation, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("send TEEC_CMD_GET_VERSION to TA failed(0x%x).\n", ret);
        ret = HI_FAILURE;
        goto out;
    }

    ret = HI_SUCCESS;
out :
    return ret;
}

/*Init Tee common CA*/
HI_S32 HI_DRV_TEE_Common_Init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    if (HI_FALSE == bCommonFlag)
    {
        COMMON_COMM_S *CommonCom = &g_stCommonComm;
        mutex_init(&CommonCom->teec.lock);
        CommonInitTeec(CommonCom);
        bCommonFlag = HI_TRUE;
    }

    ret = HI_SUCCESS;

    return ret;
}

/*UnInit Tee common CA*/
HI_S32 HI_DRV_TEE_Common_UnInit(HI_VOID)
{
    if (HI_TRUE == bCommonFlag)
    {
        CommonDeinitTeec(&g_stCommonComm);
        bCommonFlag = HI_FALSE;
    }

    return HI_SUCCESS;
}
#else
HI_S32 HI_DRV_SYS_GetSecureOSImageVersion(HI_CHAR *pVersion, HI_U32 u32VersionLen)
{
    return HI_SUCCESS;
}

HI_S32 HI_DRV_TEE_Common_Init(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 HI_DRV_TEE_Common_UnInit(HI_VOID)
{
    return HI_SUCCESS;
}
#endif

