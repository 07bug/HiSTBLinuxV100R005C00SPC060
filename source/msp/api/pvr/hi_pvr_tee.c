#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include "hi_type.h"
#include "hi_debug.h"
#include "pvr_debug.h"
#include "hi_pvr_debug.h"
#include "hi_pvr_tee.h"
#include "hi_drv_pvr.h"
#include "hi_drv_struct.h"
//#include "hi_mpi_mem.h"

#define HI_TEE_PVR_USE_SMMU

/************************************************************************/
typedef struct hiPVR_TEE_REC_DARA_S
{
    HI_U32  u32VirtulAddr;  //reserved, no use;
    HI_U32  u32PhyAddr;
    HI_U32  u32Len;
} PVR_TEE_REC_DARA_S;

typedef struct hiPVR_TEE_INDEX_INFO_S
{
    HI_U32 u32OptimizeFlag;
    HI_S32 s32IndexNum;
    HI_S32 s32TsDataNum;
    HI_U64 u64DropLength;
    HI_U64 u64GlobalOffset[REE_PVR_MAX_INDEX_NUM];
    HI_U32 u32FrameSize[REE_PVR_MAX_INDEX_NUM];
    PVR_TEE_REC_DARA_S stRecData[2];
} PVR_TEE_INDEX_INFO_S;

/************************************************************************/
static HI_S32 PVR_TeeMallocSmmuBuffer(HI_U32* pu32SmmuAddr, HI_S32 s32Length, HI_CHAR* pchName);
static HI_S32 PVR_TeeFreeSmmuBuffer(HI_U32 u32SmmuAddr);
/*************************************************************************/
extern HI_S32   g_s32PvrFd;      /*PVR module file description */

static HI_S32 PVR_TeeMallocSmmuBuffer(HI_U32* pu32SmmuAddr, HI_S32 s32Length, HI_CHAR* pchName)
{
    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pu32SmmuAddr)
    {
        HI_ERR_PVR("null pointer for pstSecBuf!\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    *pu32SmmuAddr = HI_MPI_SMMU_New(pchName, s32Length);
    if (0 == *pu32SmmuAddr)
    {
        HI_ERR_PVR("calling HI_MPI_SMMU_New failed!!\n");
        return HI_ERR_PVR_NO_MEM;
    }

    HI_INFO_PVR("success to malloc mem(0x%08x, %d)", *pu32SmmuAddr, s32Length);

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}
static HI_S32 PVR_TeeFreeSmmuBuffer(HI_U32 u32SmmuAddr)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_PVR_DEBUG_ENTER();

    if (0 == u32SmmuAddr)
    {
        HI_WARN_PVR("null pointer for input argument!\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    s32Ret = HI_MPI_SMMU_Delete(u32SmmuAddr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("failed to calling HI_MPI_SMMU_Delete(0x%08x)!\n", u32SmmuAddr);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_PVR_TeeOpenTeeChn(HI_U32* pu32ChnId, HI_S32 s32Length)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PVR_TEE_GEN_VALUE_ARGS_S stArgs;

    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pu32ChnId)
    {
        HI_ERR_PVR("null pointer for input argument!\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    memset(&stArgs, 0x00, sizeof(stArgs));
    stArgs.u32Args[0] = s32Length;

    s32Ret = ioctl(g_s32PvrFd, CMD_PVR_TEE_REC_OPEN, &stArgs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("CMD_PVR_TEE_REC_OPEN failed, ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    *pu32ChnId = stArgs.u32Args[7];

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}
HI_S32 HI_PVR_TeeCloseTeeChn(HI_U32 u32TeeChnId)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PVR_TEE_GEN_VALUE_ARGS_S stArgs;

    HI_PVR_DEBUG_ENTER();

    memset(&stArgs, 0x00, sizeof(stArgs));
    stArgs.u32Args[0] = u32TeeChnId;

    s32Ret = ioctl(g_s32PvrFd, CMD_PVR_TEE_REC_CLOSE, &stArgs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("CMD_PVR_TEE_REC_OPEN failed, ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}
HI_S32 HI_PVR_TeeCopyToREE_Test(PVR_REE_BUFFER_INFO_S* pstReeBuf, HI_U32 u32TeeChnId)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PVR_TEE_GEN_VALUE_ARGS_S stArgs;

    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pstReeBuf)
    {
        HI_ERR_PVR("null pointer for input argument!\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    pstReeBuf->u32Used = 0;
    memset(&stArgs, 0x00, sizeof(stArgs));
    stArgs.u32Args[0] = u32TeeChnId;
    stArgs.u32Args[1] = pstReeBuf->u32SmmuAddr;
    stArgs.u32Args[2] = pstReeBuf->u32Size;

    s32Ret = ioctl(g_s32PvrFd, CMD_PVR_TEE_REC_COPY_REE_TEST, &stArgs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("CMD_PVR_TEE_REC_COPY_REE_TEST failed:ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    pstReeBuf->u32Used = stArgs.u32Args[7];

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_PVR_TeeGetReeBuffInfo(PVR_REE_BUFFER_INFO_S* pstReeBuf,
                                HI_U8** ppu8DataAddr, HI_U32* pu32DataPhyAddr, HI_U32* pu32Len)
{
    HI_PVR_DEBUG_ENTER();

    if ((HI_NULL == pstReeBuf)
        || (HI_NULL == ppu8DataAddr)
        || (HI_NULL == pu32Len)
        || (HI_NULL == pu32DataPhyAddr))
    {
        HI_ERR_PVR("null pointer for input argument!\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    if (0 == pstReeBuf->u32Used)
    {
        return HI_TEE_ERROR_PVR_NO_ENOUGH_DATA;
    }

    *ppu8DataAddr = pstReeBuf->pUserAddr;
    *pu32DataPhyAddr = pstReeBuf->u32SmmuAddr;
    *pu32Len = pstReeBuf->u32Used;

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

/*填充一帧数据起始位置，保证188对齐，同步修改ts数据和index数据*/
HI_S32 HI_PVR_TeeAdjustTsData(HI_U32 u32TeeChnId, PVR_TEE_REC_PROCESS_INFO_S *pstRecInfo)
{
    HI_S32 i = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    PVR_TEE_GEN_VALUE_ARGS_S stArgs;
    PVR_TEE_INDEX_INFO_S* pstIndexInfo = HI_NULL;

    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pstRecInfo)
    {
        HI_ERR_PVR("null pointer for input argument!\n");
        return HI_ERR_PVR_NUL_PTR;
    }
    if ((HI_NULL == pstRecInfo->pstDmxRecData)
        || (HI_NULL == pstRecInfo->pstReeBuff)
        || (HI_NULL == pstRecInfo->pstTeeBuff))
    {
        HI_ERR_PVR("null pointer for input argument!\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    pstIndexInfo = (PVR_TEE_INDEX_INFO_S*)pstRecInfo->pstReeBuff->pUserAddr;
    if (HI_NULL == pstIndexInfo)
    {
        HI_ERR_PVR("no malloc/map the SMMU buffer!\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    memset(pstIndexInfo, 0x00, sizeof(PVR_TEE_INDEX_INFO_S));
    pstIndexInfo->s32IndexNum = (HI_S32)pstRecInfo->pstDmxRecData->u32IdxNum;
    pstIndexInfo->s32TsDataNum = (HI_S32)pstRecInfo->pstDmxRecData->u32RecDataCnt;
    pstIndexInfo->u64DropLength = pstRecInfo->u64DropLength;

    if ((REE_PVR_MAX_INDEX_NUM < pstIndexInfo->s32IndexNum)
        || (2 < pstIndexInfo->s32TsDataNum))
    {
        HI_ERR_PVR("Invalid index num(%d) or ts data num(%d)!\n",
                   pstIndexInfo->s32IndexNum, pstIndexInfo->s32TsDataNum);
        return HI_FAILURE;
    }

    for (i = 0; i < pstIndexInfo->s32TsDataNum; i++)
    {
        pstIndexInfo->stRecData[i].u32VirtulAddr = 0;//pstDmxRecData->stRecData[i].pDataAddr;
        pstIndexInfo->stRecData[i].u32PhyAddr = pstRecInfo->pstDmxRecData->stRecData[i].u32DataPhyAddr;
        pstIndexInfo->stRecData[i].u32Len = pstRecInfo->pstDmxRecData->stRecData[i].u32Len;
    }

    for (i = 0; i < pstIndexInfo->s32IndexNum; i++)
    {
        pstIndexInfo->u64GlobalOffset[i] = pstRecInfo->pstDmxRecData->stIndex[i].u64GlobalOffset;
        pstIndexInfo->u32FrameSize[i] = pstRecInfo->pstDmxRecData->stIndex[i].u32FrameSize;
    }

    pstRecInfo->pstTeeBuff->u32SmmuAddr = 0;
    pstRecInfo->pstTeeBuff->u32Used = 0;
    pstIndexInfo->u32OptimizeFlag = 1;

    memset(&stArgs, 0x00, sizeof(stArgs));
    stArgs.u32Args[0] = u32TeeChnId;
    stArgs.u32Args[1] = pstRecInfo->pstReeBuff->u32SmmuAddr;
    stArgs.u32Args[2] = (HI_U32)pstRecInfo->hDemuxHandle;

    s32Ret = ioctl(g_s32PvrFd, CMD_PVR_TEE_REC_PROCESS_TS_DATA, &stArgs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("CMD_PVR_TEE_REC_PROCESS_TS_DATA failed:ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    for (i = 0; i < pstIndexInfo->s32IndexNum; i++)
    {
        pstRecInfo->pstDmxRecData->stIndex[i].u64GlobalOffset = pstIndexInfo->u64GlobalOffset[i];
        pstRecInfo->pstDmxRecData->stIndex[i].u32FrameSize = pstIndexInfo->u32FrameSize[i];
    }

    pstRecInfo->pstTeeBuff->u32SmmuAddr = pstIndexInfo->stRecData[0].u32PhyAddr;
    pstRecInfo->pstTeeBuff->u32Used = pstIndexInfo->stRecData[0].u32Len;

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}
HI_S32 HI_PVR_TeeCopyDataFromRee(HI_HANDLE hTsBuf, PVR_REE_BUFFER_INFO_S* pstReeBuf, HI_U32 u32PhyAddr, HI_S32 s32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PVR_TEE_GEN_VALUE_ARGS_S stArgs;

    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pstReeBuf)
    {
        HI_ERR_PVR("null pointer for input argument!\n");
        return HI_ERR_PVR_NUL_PTR;
    }
    if (0 >= s32Len)
    {
        HI_ERR_PVR("Invalid data length(%d) for copy\n", s32Len);
        return HI_ERR_PVR_INVALID_PARA;
    }

    memset(&stArgs, 0x00, sizeof(stArgs));
    stArgs.u32Args[0] = pstReeBuf->u32SmmuAddr;
    stArgs.u32Args[1] = u32PhyAddr;
    stArgs.u32Args[2] = s32Len;
    stArgs.u32Args[3] = (HI_U32)hTsBuf;

    s32Ret = ioctl(g_s32PvrFd, CMD_PVR_TEE_PLAY_COPY_FROM_REE, &stArgs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("CMD_PVR_TEE_PLAY_COPY_FROM_REE failed:ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_PVR_TeePlayProcTsData(HI_U32 u32PhyAddr, HI_U32 u32HeadOffset, HI_U32 u32HeadToAdd, HI_U32 u32EndOffset, HI_U32 u32EndToAdd)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PVR_TEE_GEN_VALUE_ARGS_S stArgs;

    HI_PVR_DEBUG_ENTER();

    if (0 == u32PhyAddr)
    {
        HI_ERR_PVR("null address!\n");
        return HI_ERR_PVR_INVALID_PARA;
    }

    memset(&stArgs, 0x00, sizeof(stArgs));
    stArgs.u32Args[0] = u32PhyAddr;
    stArgs.u32Args[1] = u32HeadOffset;
    stArgs.u32Args[2] = u32EndOffset;
    stArgs.u32Args[3] = u32HeadToAdd;
    stArgs.u32Args[4] = u32EndToAdd;

    s32Ret = ioctl(g_s32PvrFd, CMD_PVR_TEE_PLAY_PROCESS_DATA, &stArgs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("CMD_PVR_TEE_PLAY_PROCESS_DATA failed:ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_PVR_TeeGetTeeState(HI_U32 u32TeeChnId, PVR_REE_BUFFER_INFO_S* pstTeeState)
{
#if 0
    HI_S32 s32Ret = HI_SUCCESS;
    PVR_TEE_GEN_VALUE_ARGS_S stArgs;

    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pstTeeState)
    {
        HI_ERR_PVR("null pointer for input argument!\n");
        return HI_ERR_PVR_NUL_PTR;
    }


    memset(&stArgs, 0x00, sizeof(stArgs));
    stArgs.u32Args[0] = u32TeeChnId;
    stArgs.u32Args[1] = pstTeeState->u32SmmuAddr;

    s32Ret = ioctl(g_s32PvrFd, CMD_PVR_TEE_REC_GET_STATE, &stArgs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("CMD_PVR_TEE_REC_GET_STATE failed:ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    HI_PVR_DEBUG_EXIT();
#endif

    return HI_SUCCESS;
}

HI_S32 HI_PVR_TeeMallocReeBuffer(PVR_REE_BUFFER_INFO_S* pstReeBuf, HI_S32 s32Length, HI_BOOL bShare, HI_CHAR* pchName)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pstReeBuf)
    {
        HI_ERR_PVR("null pointer for input argument!\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    pstReeBuf->pUserAddr = HI_NULL;
    s32Ret = PVR_TeeMallocSmmuBuffer(&pstReeBuf->u32SmmuAddr, s32Length, pchName);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("failed to calling PVR_TeeMallocSmmuBuffer!ret = 0x%08x!\n", s32Ret);
        return s32Ret;
    }

    pstReeBuf->pUserAddr = HI_MPI_SMMU_Map(pstReeBuf->u32SmmuAddr, HI_FALSE);
    HI_INFO_PVR("(smmu_addr, pUserAddr) = (0x%08x, %p)!\n",
                pstReeBuf->u32SmmuAddr, pstReeBuf->pUserAddr);
    pstReeBuf->u32Size = s32Length;
    pstReeBuf->u32Used = 0;

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_PVR_TeeFreeReeBuffer(PVR_REE_BUFFER_INFO_S* pstReeBuf, HI_BOOL bShare)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pstReeBuf)
    {
        HI_WARN_PVR("null pointer for input argument!\n");
        return HI_SUCCESS;
    }

    s32Ret = HI_MPI_SMMU_Unmap(pstReeBuf->u32SmmuAddr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("failed to calling HI_MPI_SMMU_Unmap!ret = 0x%08x!\n", s32Ret);
    }

    s32Ret = PVR_TeeFreeSmmuBuffer(pstReeBuf->u32SmmuAddr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("failed to calling PVR_TeeFreeSmmuBuffer!ret = 0x%08x!\n", s32Ret);
        return s32Ret;
    }

    pstReeBuf->u32SmmuAddr = HI_NULL;
    pstReeBuf->pUserAddr = HI_NULL;
    pstReeBuf->u32Size = 0;
    pstReeBuf->u32Used = 0;

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_PVR_TeeGetRecTeeBuf(HI_U32 u32TeeChnId, HI_U8** ppu8VirAddr, HI_U32* pu32PhyAddr, HI_U32* pu32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PVR_TEE_GEN_VALUE_ARGS_S stArgs;

    HI_PVR_DEBUG_ENTER();

    if ((HI_NULL == ppu8VirAddr) || (HI_NULL == pu32PhyAddr) || (HI_NULL == pu32Len))
    {
        HI_ERR_PVR("null pointer for input argument\n");
        return HI_ERR_PVR_NUL_PTR;
    }

    *ppu8VirAddr = HI_NULL;
    *pu32PhyAddr = HI_NULL;

    memset(&stArgs, 0x00, sizeof(stArgs));
    stArgs.u32Args[0] = u32TeeChnId;
    stArgs.u32Args[1] = *pu32Len;
    *pu32Len = 0;

    s32Ret = ioctl(g_s32PvrFd, CMD_PVR_TEE_REC_GET_ADDRINFO, &stArgs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("CMD_PVR_TEE_REC_GET_ADDRINFO failed:ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    *pu32PhyAddr = stArgs.u32Args[7];
    *pu32Len = stArgs.u32Args[6];

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

