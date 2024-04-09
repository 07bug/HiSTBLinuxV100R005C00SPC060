#include "vmm.h"
#include "vmm_osal.h"
#include "vmm_core.h"


SINT32 VMM_ModuleInit(PFN_VMM_CALLBACK pfVmmCallback)
{
    D_VMM_CHECK_PTR_RET(pfVmmCallback, ERR_VMM_NULL_PTR);

    return VMM_Core_Init(pfVmmCallback);
}

SINT32 VMM_ModuleDeInit(VOID)
{
    return VMM_Core_Deinit();
}

SINT32 VMM_SendCommand(VMM_CMD_TYPE_E CmdID, VMM_CMD_PRIO_E Proir, VOID *pParamIn)
{
    D_VMM_CHECK_PTR_RET(pParamIn, ERR_VMM_NULL_PTR);

    if (CmdID >= VMM_CMD_TYPE_BUTT)
    {
        PRINT(PRN_ERROR, "%s invalid command %d\n", __func__, CmdID);
        return ERR_VMM_INVALID_PARA;
    }

    return VMM_Core_AddMsg(CmdID, Proir, pParamIn);
}


SINT32 VMM_SendCommandBlock(VMM_CMD_BLK_TYPE_E CmdID, VOID *pParamInOut)
{
    D_VMM_CHECK_PTR_RET(pParamInOut, ERR_VMM_NULL_PTR);

    if (CmdID >= VMM_CMD_BLK_TYPE_BUTT)
    {
        PRINT(PRN_ERROR, "%s invalid command %d\n", __func__, CmdID);
        return ERR_VMM_INVALID_PARA;
    }

    return VMM_Core_SendCmdBlock(CmdID, pParamInOut);
}

#ifdef VCODEC_UT_ENABLE
EXPORT_SYMBOL(VMM_ModuleInit);
EXPORT_SYMBOL(VMM_ModuleDeInit);
EXPORT_SYMBOL(VMM_SendCommand);
EXPORT_SYMBOL(VMM_SendCommandBlock);
#endif

