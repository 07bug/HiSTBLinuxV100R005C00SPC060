#ifdef HI_TEE_PVR_SUPPORT

#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/errno.h>
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_module.h"
#include "hi_drv_module.h"
#include "hi_drv_dev.h"
#include "hi_kernel_adapt.h"
#include "pvr_debug.h"
#include "hi_error_mpi.h"
#include "drv_pvr_tee_func.h"

static TEEC_UUID PVR_Task_Uuid =
{
    0x569985fe,
    0xbac0,
    0x11e6,
    {
        0xa4, 0xa6, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01
    }
};

static PVR_DRV_TEEC_INFO_S s_stTeecInfo =
{
    .s32InitCount = 0,
};

static PVR_TEE_REC_CHAN_INFO_S PvrTeeRecChan[PVR_TEE_REC_MAX_CHN_NUM];

HI_S32 PVR_TeecInit(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 u32RootId = 0;
    TEEC_Operation stOperation;
    HI_S32 s32Ret = HI_FAILURE;
    HI_CHAR szSessionName[] = "hisi_pvr_client";

    HI_PVR_DEBUG_ENTER();

    s_stTeecInfo.s32InitCount++;
    if (1 < s_stTeecInfo.s32InitCount)
    {
        HI_INFO_PVR("pvr tee has already initialized(%d)!\n", s_stTeecInfo.s32InitCount);
        return  HI_SUCCESS;
    }

    for (i = 0; i < PVR_TEE_REC_MAX_CHN_NUM; i++)
    {
        PvrTeeRecChan[i].bUsed = HI_FALSE;
        PvrTeeRecChan[i].owner = 0;
        PvrTeeRecChan[i].u32TeeId = 0xFFFF;
    }

    s32Ret = TEEK_InitializeContext(HI_NULL, &s_stTeecInfo.stContext);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Initialise pvr teec context failed(0x%x)", s32Ret);
        s_stTeecInfo.s32InitCount--;
        return s32Ret;
    }

    memset(&stOperation, 0x00, sizeof(TEEC_Operation));
    stOperation.started = 1;
    stOperation.cancel_flag = 0;
    stOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT);
    stOperation.params[2].tmpref.buffer = (void *)(&u32RootId);
    stOperation.params[2].tmpref.size = sizeof(u32RootId);
    stOperation.params[3].tmpref.buffer = (void *)(szSessionName);
    stOperation.params[3].tmpref.size = strlen(szSessionName) + 1;

    s32Ret = (HI_S32)TEEK_OpenSession(&s_stTeecInfo.stContext, &s_stTeecInfo.stSession, &PVR_Task_Uuid, TEEC_LOGIN_IDENTIFY, NULL, &stOperation, NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("open pvr teec session failed(0x%x)", s32Ret);
        s_stTeecInfo.s32InitCount--;
        TEEK_FinalizeContext(&s_stTeecInfo.stContext);
        return s32Ret;
    }

    HI_INFO_PVR("open pvr teec session success!\n");
    HI_PVR_DEBUG_EXIT();

    return HI_SUCCESS;

}

HI_S32 PVR_TeecDeInit(HI_VOID)
{
    HI_U32 i = 0;
    HI_PVR_DEBUG_ENTER();

    if (0 >= s_stTeecInfo.s32InitCount)
    {
        HI_INFO_PVR("Not Init the PVR Tee!\n");
        return HI_SUCCESS;
    }

    s_stTeecInfo.s32InitCount--;
    if (0 < s_stTeecInfo.s32InitCount)
    {
        HI_INFO_PVR("There is other instance running!\n");
        return HI_SUCCESS;
    }

    for (i = 0; i < PVR_TEE_REC_MAX_CHN_NUM; i++)
    {
        PvrTeeRecChan[i].bUsed = HI_FALSE;
        PvrTeeRecChan[i].owner = 0;
        PvrTeeRecChan[i].u32TeeId = 0xFFFF;
    }

    TEEK_CloseSession(&s_stTeecInfo.stSession);
    TEEK_FinalizeContext(&s_stTeecInfo.stContext);
    HI_INFO_PVR("TEEC deinit success!\n");

    HI_PVR_DEBUG_EXIT();

    return HI_SUCCESS;
}

HI_S32 PVR_TeeRelease(struct file *file)
{
    HI_U32 i = 0;
    PVR_TEE_GEN_VALUE_ARGS_S stArgs;
    pid_t cPid = (pid_t)(unsigned long)file->private_data;

    HI_PVR_DEBUG_ENTER();

    for (i = 0; i < PVR_TEE_REC_MAX_CHN_NUM; i++)
    {
        if ((HI_TRUE == PvrTeeRecChan[i].bUsed) && (cPid == PvrTeeRecChan[i].owner))
        {
            memset(&stArgs, 0x00, sizeof(stArgs));
            stArgs.u32Args[0] = PvrTeeRecChan[i].u32TeeId;
            (HI_VOID)PVR_TeeRecCloseChn(file, &stArgs);
        }
    }

    HI_PVR_DEBUG_EXIT();

    return HI_SUCCESS;
}

/*
*  Input: pstArgs->u32Args[0] -- the buffer length of the buffer which will be allocated on the TEE
* Output:pstArgs->u32Args[7] -- tee channel id
*/
HI_S32 PVR_TeeRecOpenChn(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs)
{
    HI_U32 i = 0;
    HI_S32 s32Ret = HI_FAILURE;
    TEEC_Operation stOperation;
    HI_U32 u32Origin = 0;
    PVR_TEE_REC_CHAN_INFO_S *pstTeeChnInfo = HI_NULL;
    HI_U32 u32Length = pstArgs->u32Args[0];

    HI_PVR_DEBUG_ENTER();

    for (i = 0; i < PVR_TEE_REC_MAX_CHN_NUM; i++)
    {
        if (HI_TRUE != PvrTeeRecChan[i].bUsed)
        {
            pstTeeChnInfo = &PvrTeeRecChan[i];
            break;
        }
    }

    if (HI_NULL == pstTeeChnInfo)
    {
        HI_ERR_PVR("no tee channel left!\n");
        return HI_ERR_PVR_NO_CHN_LEFT;
    }

    if (0 != (u32Length % REE_PVR_BUFFER_ALIGN))
    {
        HI_WARN_PVR("buffer length(%u) is not aligned by %u\n", u32Length, (HI_U32)REE_PVR_BUFFER_ALIGN);
        u32Length = (u32Length % REE_PVR_BUFFER_ALIGN) * REE_PVR_BUFFER_ALIGN + REE_PVR_BUFFER_ALIGN;
    }

    if ((REE_PVR_BUFFER_MIN_LEN > u32Length) || (REE_PVR_BUFFER_MAX_LEN < u32Length))
    {
        HI_ERR_PVR("buffer length(%u) is too short(%u) or too long(%u)", u32Length, REE_PVR_BUFFER_MIN_LEN, REE_PVR_BUFFER_MAX_LEN);
        return HI_ERR_PVR_INVALID_PARA;
    }

    memset(&stOperation, 0x00, sizeof(stOperation));
    stOperation.started = 1;
    stOperation.params[0].value.a = 0;
    stOperation.params[0].value.b = u32Length;
    stOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    s32Ret = (HI_S32)TEEK_InvokeCommand(&s_stTeecInfo.stSession, (HI_U32)TEE_PVR_CMD_REC_OPEN_CHANNEL, &stOperation, &u32Origin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("open tee rec channel faild:ret=0x%x, u32Origin:%d\n", s32Ret, u32Origin);
        return s32Ret;
    }

    pstTeeChnInfo->bUsed = HI_TRUE;
    pstTeeChnInfo->owner = task_tgid_nr(current);
    pstTeeChnInfo->u32TeeId = stOperation.params[0].value.a;
    pstArgs->u32Args[7] = stOperation.params[0].value.a;

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

/*
* input: pstArgs->u32Args[0] -- the tee channel id.
* output: none
*/
HI_S32 PVR_TeeRecCloseChn(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs)
{
    HI_U32 u32Origin = 0;
    TEEC_Operation stOperation;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TeeChnId = pstArgs->u32Args[0];
    PVR_TEE_REC_CHAN_INFO_S *pstTeeChnInfo = HI_NULL;

    HI_PVR_DEBUG_ENTER();

    TEE_PVR_CHECK_CHN_RETURN(u32TeeChnId, pstTeeChnInfo);

    memset(&stOperation, 0x00, sizeof(stOperation));
    stOperation.started = 1;
    stOperation.params[0].value.a = u32TeeChnId;
    stOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    s32Ret = (HI_S32)TEEK_InvokeCommand(&s_stTeecInfo.stSession, (HI_U32)TEE_PVR_CMD_REC_CLOSE_CHANNEL, &stOperation, &u32Origin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("close tee rec channel faild:ret=0x%x, u32Origin:%d\n", s32Ret, u32Origin);
        return s32Ret;
    }

    pstTeeChnInfo->bUsed = HI_FALSE;
    pstTeeChnInfo->owner = 0;
    pstTeeChnInfo->u32TeeId = 0xFFFF;

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

/*
*input:       pstArgs->u32Args[0] -- the tee channel id.
*               pstArgs->u32Args[1] -- smmu addr of ree buffer.
*               pstArgs->u32Args[2] -- the size of ree buffer.
*output:     pstArgs->u32Args[7] -- the valid length of ree buffer.
*/
HI_S32 PVR_TeeRecCopyToRee(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs)
{
    HI_U32 u32Origin = 0;
    TEEC_Operation stOperation;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TeeChnId = pstArgs->u32Args[0];
    PVR_TEE_REC_CHAN_INFO_S *pstTeeChnInfo = HI_NULL;

    HI_PVR_DEBUG_ENTER();

    TEE_PVR_CHECK_CHN_RETURN(u32TeeChnId, pstTeeChnInfo);

    memset(&stOperation, 0x00, sizeof(stOperation));
    stOperation.started = 1;
    stOperation.params[0].value.a = u32TeeChnId;
    stOperation.params[1].value.a = pstArgs->u32Args[1];
    stOperation.params[1].value.b = pstArgs->u32Args[2];
    stOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE);

    s32Ret = (HI_S32)TEEK_InvokeCommand(&s_stTeecInfo.stSession, (HI_U32)TEE_PVR_CMD_REC_COPY_TO_REE, &stOperation, &u32Origin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("copy to ree faild:ret=0x%x, u32Origin:%d\n", s32Ret, u32Origin);
        return s32Ret;
    }

    pstArgs->u32Args[7] = stOperation.params[1].value.b;

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

/*
* input: pstArgs->u32Args[0] -- tee channel id
*          pstArgs->u32Args[1] -- smmu address pf ree
*output: none
*/
HI_S32 PVR_TeeRecProcessData(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs)
{
    HI_U32 u32Origin = 0;
    TEEC_Operation stOperation;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TeeChnId = pstArgs->u32Args[0];
    PVR_TEE_REC_CHAN_INFO_S *pstTeeChnInfo = HI_NULL;

    HI_PVR_DEBUG_ENTER();

    TEE_PVR_CHECK_CHN_RETURN(u32TeeChnId, pstTeeChnInfo);

    memset(&stOperation, 0x00, sizeof(stOperation));
    stOperation.started = 1;
    stOperation.params[0].value.a = u32TeeChnId;
    stOperation.params[0].value.b = pstArgs->u32Args[1];
    stOperation.params[1].value.a = pstArgs->u32Args[2];
    stOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE);

    s32Ret = (HI_S32)TEEK_InvokeCommand(&s_stTeecInfo.stSession, (HI_U32)TEE_PVR_CMD_REC_PROCESS_DATA, &stOperation, &u32Origin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("process ts data faild:ret=0x%x, u32Origin:%d\n", s32Ret, u32Origin);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}


HI_S32 PVR_TeeRecGetState(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs)
{
#if 0
    HI_U32 u32Origin = 0;
    TEEC_Operation stOperation;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TeeChnId = pstArgs->u32Args[0];
    PVR_TEE_REC_CHAN_INFO_S *pstTeeChnInfo = HI_NULL;

    HI_PVR_DEBUG_ENTER();

    TEE_PVR_CHECK_CHN_RETURN(u32TeeChnId, pstTeeChnInfo);

    memset(&stOperation, 0x00, sizeof(stOperation));
    stOperation.started = 1;
    stOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE);

    s32Ret = (HI_S32)TEEK_InvokeCommand(&s_stTeecInfo.stSession, (HI_U32)TEE_PVR_CMD_REC_GET_TEE_STATE, &stOperation, &u32Origin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("close tee rec channel faild:ret=0x%x, u32Origin:%d\n", s32Ret, u32Origin);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
#endif
    return HI_SUCCESS;
}

/*
* input: pstArgs->u32Args[0] -- tee channel id
* input:  pstArgs->u32Args[1] --the max expected length
*ouput:  pstArgs->u32Args[7] --the address of buffer
*ouput:  pstArgs->u32Args[6] --the valided length
*/
HI_S32 PVR_TeeRecGetAddrInfo(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs)
{
    HI_U32 u32Origin = 0;
    TEEC_Operation stOperation;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TeeChnId = pstArgs->u32Args[0];
    PVR_TEE_REC_CHAN_INFO_S *pstTeeChnInfo = HI_NULL;

    HI_PVR_DEBUG_ENTER();

    TEE_PVR_CHECK_CHN_RETURN(u32TeeChnId, pstTeeChnInfo);

    memset(&stOperation, 0x00, sizeof(stOperation));
    stOperation.started = 1;
    stOperation.params[0].value.a = u32TeeChnId;
    stOperation.params[0].value.b = pstArgs->u32Args[1];
    stOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_INOUT, TEEC_VALUE_INOUT, TEEC_NONE);

#if defined(CHIP_TYPE_hi3798mv200) && defined(HI_ADVCA_TYPE_VERIMATRIX_ULTRA)
    s32Ret = (HI_S32)TEEK_InvokeCommand(&s_stTeecInfo.stSession, (HI_U32)TEE_PVR_CMD_REC_GET_ADDRINFO, &stOperation, &u32Origin);
#else
    s32Ret = HI_SUCCESS;
#endif
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("get tee data info faild:ret=0x%x, u32Origin:%d\n", s32Ret, u32Origin);
        return s32Ret;
    }

	/* fix the compilation error:unused variable u32Origin */
	u32Origin = u32Origin;

    pstArgs->u32Args[7] = stOperation.params[1].value.a;
    pstArgs->u32Args[6] = stOperation.params[1].value.b;
    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

/*
* input: pstArgs->u32Args[0] -- SMMU address of REE buffer
*          pstArgs->u32Args[1] -- SMMU address of TEE buffer
*          pstArgs->u32Args[2] -- the length of data
*/
HI_S32 PVR_TeePlayCopyFromRee(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs)
{
    HI_U32 u32Origin = 0;
    TEEC_Operation stOperation;
    HI_S32 s32Ret = HI_SUCCESS;

    HI_PVR_DEBUG_ENTER();

    memset(&stOperation, 0x00, sizeof(stOperation));
    stOperation.started = 1;
    stOperation.params[0].value.a = pstArgs->u32Args[0];
    stOperation.params[0].value.b = pstArgs->u32Args[1];
    stOperation.params[1].value.a = pstArgs->u32Args[2];
    stOperation.params[1].value.b = pstArgs->u32Args[3];
    stOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE);

    s32Ret = (HI_S32)TEEK_InvokeCommand(&s_stTeecInfo.stSession, (HI_U32)TEE_PVR_CMD_PLAY_COPY_FROM_REE, &stOperation, &u32Origin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("copy play data to tee faild:ret=0x%x, u32Origin:%d\n", s32Ret, u32Origin);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

/*
* input: pstArgs->u32Args[0] -- SMMU address of data buffer
*          pstArgs->u32Args[1] -- u32HeadOffset
*          pstArgs->u32Args[2] -- u32EndOffset
*          pstArgs->u32Args[3] -- u32HeadToAdd
*          pstArgs->u32Args[4] -- u32EndToAdd
*/
HI_S32 PVR_TeePlayProcessData(struct file *file, PVR_TEE_GEN_VALUE_ARGS_S *pstArgs)
{
    HI_U32 u32Origin = 0;
    TEEC_Operation stOperation;
    HI_S32 s32Ret = HI_SUCCESS;

    HI_PVR_DEBUG_ENTER();

    memset(&stOperation, 0x00, sizeof(stOperation));
    stOperation.started = 1;
    stOperation.params[0].value.a = pstArgs->u32Args[0];
    stOperation.params[0].value.b = pstArgs->u32Args[1];
    stOperation.params[1].value.a = pstArgs->u32Args[2];
    stOperation.params[1].value.b = pstArgs->u32Args[3];
    stOperation.params[2].value.a = pstArgs->u32Args[4];
    stOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_INPUT, TEEC_VALUE_INPUT, TEEC_NONE);

    s32Ret = (HI_S32)TEEK_InvokeCommand(&s_stTeecInfo.stSession, (HI_U32)TEE_PVR_CMD_PLAY_PROCESS_DATA, &stOperation, &u32Origin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("process play ts data faild:ret=0x%x, u32Origin:%d\n", s32Ret, u32Origin);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

HI_S32 PVR_TeecIoctl(struct inode *inode, struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 s32Ret = HI_FAILURE;

    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == arg)
    {
        HI_ERR_PVR("null pinter for input!\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    switch(cmd)
    {
        case CMD_PVR_TEE_REC_OPEN:
            s32Ret = PVR_TeeRecOpenChn(file, arg);
            break;
        case CMD_PVR_TEE_REC_CLOSE:
            s32Ret = PVR_TeeRecCloseChn(file, arg);
            break;
        case CMD_PVR_TEE_REC_COPY_REE_TEST:
            s32Ret = PVR_TeeRecCopyToRee(file, arg);
            break;
        case CMD_PVR_TEE_REC_PROCESS_TS_DATA:
            s32Ret = PVR_TeeRecProcessData(file, arg);
            break;
        case CMD_PVR_TEE_REC_GET_STATE:
            s32Ret = PVR_TeeRecGetState(file, arg);
            break;
        case CMD_PVR_TEE_REC_GET_ADDRINFO:
            s32Ret = PVR_TeeRecGetAddrInfo(file, arg);
            break;
        case CMD_PVR_TEE_PLAY_COPY_FROM_REE:
            s32Ret = PVR_TeePlayCopyFromRee(file, arg);
            break;
        case CMD_PVR_TEE_PLAY_PROCESS_DATA:
            s32Ret = PVR_TeePlayProcessData(file, arg);
            break;
        default:
            s32Ret = HI_ERR_PVR_INVALID_PARA;
            HI_ERR_PVR("invalid cmd id(%d)\n", cmd);
            break;
    }
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("process failed,cmd id is:0x%08x, ret = 0x%08x\n", cmd, s32Ret);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}
#endif
