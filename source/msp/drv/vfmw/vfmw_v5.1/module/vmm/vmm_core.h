#ifndef __VMM_CORE_H__
#define __VMM_CORE_H__

#include "vmm.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef SINT32(*FN_VMM_CMD_HANDLER)(VOID *pParamIn);

typedef struct
{
    UINT32 CmdID;
    FN_VMM_CMD_HANDLER pHandler;
} VMM_CMD_NODE;

SINT32 VMM_Core_Alloc(VOID *pParamIn);
SINT32 VMM_Core_Release(VOID *pParamIn);
SINT32 VMM_Core_Map(VOID *pParamIn);
SINT32 VMM_Core_Unmap(VOID *pParamIn);
SINT32 VMM_Core_ConfigMemBlock(VOID *pParamIn);
SINT32 VMM_Core_ConfigMemNode(VOID *pParamIn);
SINT32 VMM_Core_SetLocation(VOID *pParamIn);
SINT32 VMM_Core_ReleaseBurst(VOID *pParamIn);
SINT32 VMM_Core_CancleCmd(VOID *pParamIn);

SINT32 VMM_Core_SetPriorityPolicy(VOID *pParamIn);
SINT32 VMM_Core_GetMemNodeInfo(VOID *pParamIn);

SINT32 VMM_Core_AddMsg(const VMM_CMD_TYPE_E CmdID, VMM_CMD_PRIO_E Proir, VOID *pArgs);
SINT32 VMM_Core_SendCmdBlock(VMM_CMD_BLK_TYPE_E CmdID, VOID *pParamInOut);

SINT32 VMM_Core_Init(PFN_VMM_CALLBACK pfCallback);
SINT32 VMM_Core_Deinit(VOID);

VOID *VMM_Core_GetCallBackFunc(VOID);

#ifdef __cplusplus
}
#endif

#endif
