#include "sample_ms12.h"
#include "sample_ir.h"

static IR_KEY_INFO_S g_stIrKeyInfo[IR_KEY_type_BUTT] = 
{
    {0x35caff00, IR_KEY_type_UP},
    {0x2dd2ff00, IR_KEY_type_DOWN},
    {0x3ec1ff00, IR_KEY_type_RIGHT},
    {0x6699ff00, IR_KEY_type_LEFT},
    {0x31ceff00, IR_KEY_type_ENTER},
    {0x6f90ff00, IR_KEY_type_BACK},
    {0x629dff00, IR_KEY_type_EPG},
    {0x639cff00, IR_KEY_type_POWER},
    {0x34cbff00, IR_KEY_type_HOME},
    {0x7f80ff00, IR_KEY_type_VOLUMEUP},
    {0x7e81ff00, IR_KEY_type_VOLUMEDOWN},
    {0x22ddff00, IR_KEY_type_MUTE},
    {0x6d92ff00, IR_KEY_type_1},
    {0x6c93ff00, IR_KEY_type_2},
    {0x33ccff00, IR_KEY_type_3},
    {0x718eff00, IR_KEY_type_4},
    {0x708fff00, IR_KEY_type_5},
    {0x37c8ff00, IR_KEY_type_6},
    {0x758aff00, IR_KEY_type_7},
    {0x748bff00, IR_KEY_type_8},
    {0x3bc4ff00, IR_KEY_type_9},
    {0x7887ff00, IR_KEY_type_0},
    {0x7b84ff00, IR_KEY_type_F1},
    {0x7689ff00, IR_KEY_type_F2},
    {0x26d9ff00, IR_KEY_type_F3},
    {0x6996ff00, IR_KEY_type_F4},
    {0x6897ff00, IR_KEY_type_SEARCH},
    {0x25daff00, IR_KEY_type_REWIND},
    {0x29d6ff00, IR_KEY_type_FF},
    {0x2fd0ff00, IR_KEY_type_STOP},
    {0x6a95ff00, IR_KEY_type_SET},
    {0x38c7ff00, IR_KEY_type_INFO},
    {0x2ed1ff00, IR_KEY_type_AUDIO},
    {0x738cff00, IR_KEY_type_SUB},
    {0x7788ff00, IR_KEY_type_BACKSPACE},
    {0x3cc3ff00, IR_KEY_type_PLAYPAUSE},
    {0x6b94ff00, IR_KEY_type_FAVORITES},
    {0x7a85ff00, IR_KEY_type_CHANNELUP},
    {0x7986ff00, IR_KEY_type_CHANNELDOWN},
    {0x6798ff00, IR_KEY_type_PAGEDOWN},
    {0x30cfff00, IR_KEY_type_PAGEUP},
    {0x609fff00, IR_KEY_type_FN_1},
    {0x39c6ff00, IR_KEY_type_FN_2},
    {0x649bff00, IR_KEY_type_FN_D},
    {0x659aff00, IR_KEY_type_FN_E},
    {0x3fc0ff00, IR_KEY_type_FN_F},
    {0x3dc2ff00, IR_KEY_type_FN_S},
    {0x7d82ff00, IR_KEY_type_FN_B},
    {0x9a65ff00, IR_KEY_type_RECALL}
};
static Sample_Ir_ProcFn s_pKeyProcFn = HI_NULL;
static IR_KEY_TYPE_E IrSwitchKey(HI_U32 u32KeyValue)
{
    HI_U32 i = 0;
    for (i = 0; i < IR_KEY_type_BUTT; i++)
    {
        if (u32KeyValue == g_stIrKeyInfo[i].u32KeyValue)
            return g_stIrKeyInfo[i].enKeyType;
    }

    sample_printf("Not find the right key(0x%08x)\n", u32KeyValue);
    return IR_KEY_type_BUTT;
}

HI_S32 Sample_Ir_RegKeyProcessFn(Sample_Ir_ProcFn pKeyProcFn)
{
    SAMPLE_CHECK_POINTER_RETURN(pKeyProcFn);
    s_pKeyProcFn = pKeyProcFn;
    return HI_SUCCESS;
}

HI_S32 Sample_Ir_Init(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    SAMPLE_DOFUNC_RETURN(HI_UNF_IR_Init(), s32Ret);
    SAMPLE_DOFUNC_RETURN(HI_UNF_IR_EnableKeyUp(HI_TRUE), s32Ret);
    SAMPLE_DOFUNC_RETURN(HI_UNF_IR_SetRepKeyTimeoutAttr(300), s32Ret);
    SAMPLE_DOFUNC_RETURN(HI_UNF_IR_EnableRepKey(HI_TRUE), s32Ret);
    SAMPLE_DOFUNC_RETURN(HI_UNF_IR_Enable(HI_TRUE), s32Ret);

    return HI_SUCCESS;
}

HI_S32 Sample_Ir_DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    SAMPLE_DOFUNC_RETURN(HI_UNF_IR_Enable(HI_FALSE), s32Ret);
    SAMPLE_DOFUNC_RETURN(HI_UNF_IR_DeInit(), s32Ret);

    return HI_SUCCESS;
}

HI_VOID *Sample_Ir_ProcessRoutine(HI_VOID *pArgs)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U64 u64KeyId = 0;
    HI_UNF_KEY_STATUS_E PressStatus;
    IR_KEY_TYPE_E enKeyType;
    SAMPLE_THREAD_INFO_S *pstThreadInfo = (SAMPLE_THREAD_INFO_S *)pArgs;

    pthread_detach(pstThreadInfo->threadID);

    while (HI_FALSE == pstThreadInfo->bExitFlag)
    {
        /* get ir press codevalue & press status*/
        s32Ret = HI_UNF_IR_GetValue(&PressStatus, &u64KeyId, 0);
        if ((HI_SUCCESS != s32Ret) || (HI_UNF_KEY_STATUS_DOWN != PressStatus))
        {
            usleep(50000);
            continue;
        }

        enKeyType = IrSwitchKey((HI_U32)u64KeyId);
        if (IR_KEY_type_BUTT == enKeyType)
        {
            usleep(50000);
            continue;
        }

        if (HI_NULL != s_pKeyProcFn)
        {
            SAMPLE_DOFUNC_NO_RETURN(s_pKeyProcFn(enKeyType), s32Ret);
        }

        usleep(50000);
    }

    return HI_NULL;
}

