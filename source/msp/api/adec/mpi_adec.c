/*****************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: mpi_adec.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date           DefectNum    Description
* 0.01      2006-04-03     NULL         Create this file.
*
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hi_module.h"
#include "hi_error_mpi.h"
#include "hi_mpi_mem.h"
#include "hi_drv_adec.h"
#include "hi_mpi_adec_core.h"
#include "hi_mpi_adec.h"

#ifdef HI_ADEC_AUDSPECTRUM_SUPPORT
#include "mpi_adec_waveform.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define ADECGetRealChn(hAdec) do {hAdec = hAdec & 0xffff;} while (0)

static HI_U32 g_s32AdecInitCnt = 0;
static HI_U32 g_u32StreamCnt[ADEC_INSTANCE_MAXNUM];
static HI_VOID* g_pAdecArry[ADEC_INSTANCE_MAXNUM];
static HI_UNF_STREAM_BUF_S g_sStreamBackupArry[ADEC_INSTANCE_MAXNUM][3];

static pthread_mutex_t g_AdecMPIMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_AdecINSTMPIMutex[ADEC_INSTANCE_MAXNUM]  = {[0 ... (ADEC_INSTANCE_MAXNUM-1)] = PTHREAD_MUTEX_INITIALIZER};

#define ADEC_MPI_LOCK()    (void)pthread_mutex_lock(&g_AdecMPIMutex)
#define ADEC_MPI_UNLOCK()  (void)pthread_mutex_unlock(&g_AdecMPIMutex)
#define ADEC_INST_LOCK(AdecId)    (void)pthread_mutex_lock(&g_AdecINSTMPIMutex[AdecId])
#define ADEC_INST_UNLOCK(AdecId)  (void)pthread_mutex_unlock(&g_AdecINSTMPIMutex[AdecId])

//#define AUDIO_SAVE_ADECDATA 1

#ifdef AUDIO_SAVE_ADECDATA
static FILE* g_fStream = HI_NULL;
static FILE* g_fPcm = HI_NULL, *g_fLbr = HI_NULL, *g_fHbr = HI_NULL;

static HI_VOID AdecOpenSaveFile(HI_VOID)
{
    if (HI_NULL == g_fStream)
    {
        g_fStream = fopen("/mnt/adec_dump.es", "wb");
        if (HI_NULL == g_fStream)
        {
            HI_ERR_ADEC("Open /mnt/adec_dump.es fail\n");
        }
    }

    if (HI_NULL == g_fPcm)
    {
        g_fPcm = fopen("/mnt/adec_dump.pcm", "wb");
        if (!g_fPcm)
        {
            HI_ERR_ADEC("Open adec_dump.pcm fail\n");
        }
    }

    if (HI_NULL == g_fLbr)
    {
        g_fLbr = fopen("/mnt/adec_dump.lbr", "wb");
        if (!g_fLbr)
        {
            HI_ERR_ADEC("Open adec_dump.lbr fail\n");
        }
    }

    if (HI_NULL == g_fHbr)
    {
        g_fHbr = fopen("/mnt/adec_dump.hbr", "wb");
        if (!g_fHbr)
        {
            HI_ERR_ADEC("Open adec_dump.hbr fail\n");
        }
    }
}

static HI_VOID AdecCloseSaveFile(HI_VOID)
{
    if (g_fStream)
    {
        fclose(g_fStream);
        g_fStream = HI_NULL;
    }

    if (g_fPcm)
    {
        fclose(g_fPcm);
        g_fPcm = HI_NULL;
    }

    if (g_fLbr)
    {
        fclose(g_fLbr);
        g_fLbr = HI_NULL;
    }

    if (g_fHbr)
    {
        fclose(g_fHbr);
        g_fHbr = HI_NULL;
    }
}

static HI_VOID AdecSaveEsInStream(const HI_UNF_STREAM_BUF_S* pstStream)
{
    if (g_fStream)
    {
        fwrite(pstStream->pu8Data, 1, pstStream->u32Size, g_fStream);
        fflush(g_fStream);
    }
}

static HI_VOID AdecSaveOutputData(HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    if (g_fPcm)
    {
        if (pstAOFrame->s32BitPerSample == 16)
        {
            fwrite(pstAOFrame->ps32PcmBuffer, sizeof(HI_U16), pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels, g_fPcm);
        }
        else
        {
            fwrite(pstAOFrame->ps32PcmBuffer, sizeof(HI_U32), pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels, g_fPcm);
        }

        fflush(g_fPcm);
    }

    if (g_fLbr)
    {
        fwrite((HI_VOID*)pstAOFrame->ps32BitsBuffer, 1, pstAOFrame->u32BitsBytesPerFrame & 0xffff, g_fLbr);
        fflush(g_fLbr);
    }

    if (g_fHbr)
    {
        fwrite((HI_VOID*)((HI_U8*)pstAOFrame->ps32BitsBuffer + (pstAOFrame->u32BitsBytesPerFrame & 0xffff)), 1, ((pstAOFrame->u32BitsBytesPerFrame >> 16) & 0xffff), g_fHbr);
        fflush(g_fHbr);
    }
}
#endif

HI_S32 HI_MPI_ADEC_RegisterDeoderLib(const HI_CHAR* pszCodecDllName, HI_U32 u32Length)
{
    return ADEC_RegisterDecoder(pszCodecDllName);
}

HI_S32 HI_MPI_ADEC_FoundSupportDeoder(HA_FORMAT_E enFormat, HI_U32* penDstCodecID)
{
    return ADEC_FoundSupportDecoder(enFormat, penDstCodecID);
}

HI_S32 HI_MPI_ADEC_GetDecoderList(HI_HA_DECODE_LIB_S** ppHaLib)
{
    return ADEC_GetDecoderList(ppHaLib);
}

HI_S32 HI_MPI_ADEC_Init(const HI_CHAR* pszCodecNameTable[])
{
    HI_S32 s32Ret = HI_SUCCESS;

    ADEC_MPI_LOCK();

    if (0 == g_s32AdecInitCnt)
    {
        s32Ret = ADEC_Init();
        if (HI_SUCCESS != s32Ret)
        {
            ADEC_MPI_UNLOCK();
            return s32Ret;
        }
    }

    g_s32AdecInitCnt++;

    ADEC_MPI_UNLOCK();

    return s32Ret;
}

HI_S32 HI_MPI_ADEC_deInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    ADEC_MPI_LOCK();

    if (0 == g_s32AdecInitCnt)
    {
        ADEC_MPI_UNLOCK();
        return HI_SUCCESS;
    }

    g_s32AdecInitCnt--;

    if (0 == g_s32AdecInitCnt)
    {
        s32Ret = ADEC_DeInit();
    }

    ADEC_MPI_UNLOCK();

    return s32Ret;
}

HI_S32 HI_MPI_ADEC_Open(HI_HANDLE* phAdec)
{
    HI_S32 s32Ret;
    HI_U32 hRealAdec;
    HI_VOID* ptrmem = HI_NULL_PTR;

    ADEC_MPI_LOCK();
    if (0 == g_s32AdecInitCnt)
    {
        HI_ERR_ADEC("Adec not inited\n");
        ADEC_MPI_UNLOCK();
        return HI_FAILURE;
    }

    s32Ret = ADEC_Open(phAdec);
    if (HI_SUCCESS != s32Ret)
    {
        ADEC_MPI_UNLOCK();
        return s32Ret;
    }

    hRealAdec = (HI_U32)(*phAdec);

    if (ADEC_INSTANCE_MAXNUM <= hRealAdec)
    {
        (HI_VOID)ADEC_Close(hRealAdec);
        ADEC_MPI_UNLOCK();
        return HI_ERR_ADEC_INVALID_PARA;
    }

    ADEC_INST_LOCK(hRealAdec);

    ptrmem = HI_MALLOC(HI_ID_ADEC, ADEC_MAX_INPUT_BLOCK_SIZE);
    if (HI_NULL == ptrmem)
    {
        (HI_VOID)ADEC_Close(hRealAdec);
        ADEC_INST_UNLOCK(hRealAdec);
        ADEC_MPI_UNLOCK();
        return HI_ERR_ADEC_NULL_PTR;
    }

    memset(ptrmem, 0, ADEC_MAX_INPUT_BLOCK_SIZE);
    g_pAdecArry[hRealAdec] = ptrmem;
    memset(g_sStreamBackupArry[hRealAdec], 0, sizeof(HI_UNF_STREAM_BUF_S) * 3);
    g_u32StreamCnt[hRealAdec] = 0;

    *phAdec = hRealAdec | (HI_ID_ADEC << 16);

#ifdef AUDIO_SAVE_ADECDATA
    AdecOpenSaveFile();
#endif

    ADEC_INST_UNLOCK(hRealAdec);
    ADEC_MPI_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_ADEC_Close(HI_HANDLE hAdec)
{
    ADECGetRealChn(hAdec);
    CHECK_ADEC_HANDLE(hAdec);

    ADEC_INST_LOCK(hAdec);

    if (g_pAdecArry[hAdec])
    {
        HI_FREE(HI_ID_ADEC, g_pAdecArry[hAdec]);
        g_pAdecArry[hAdec] = HI_NULL;
    }

    ADEC_INST_UNLOCK(hAdec);

#ifdef AUDIO_SAVE_ADECDATA
    AdecCloseSaveFile();
#endif

    return ADEC_Close(hAdec);
}

HI_S32 HI_MPI_ADEC_Start(HI_HANDLE hAdec)
{
    HI_BOOL bWorkState = HI_TRUE;

    ADECGetRealChn(hAdec);
    return ADEC_SetAttr(hAdec, ADEC_ATTR_WORKSTATE, &bWorkState);
}

HI_S32 HI_MPI_ADEC_Stop(HI_HANDLE hAdec)
{
    HI_S32 s32Ret;
    HI_BOOL bWorkState = HI_FALSE;

    ADECGetRealChn(hAdec);
    s32Ret  = ADEC_SetAttr(hAdec, ADEC_ATTR_WORKSTATE, &bWorkState);
    s32Ret |= ADEC_SetAttr(hAdec, ADEC_ATTR_EosStateFlag, &bWorkState);
    return s32Ret;
}

HI_S32 HI_MPI_ADEC_SetAllAttr(HI_HANDLE hAdec, ADEC_ATTR_S* pstAllAttr)
{
    ADECGetRealChn(hAdec);
    return ADEC_SetAttr(hAdec, ADEC_ATTR_ALLATTR, pstAllAttr);
}

HI_S32 HI_MPI_ADEC_GetDelayMs(HI_HANDLE hAdec, HI_U32* pDelay)
{
    ADECGetRealChn(hAdec);
    return ADEC_GetDelayMs(hAdec, pDelay);
}

HI_S32 HI_MPI_ADEC_GetAllAttr(HI_HANDLE hAdec, ADEC_ATTR_S* pstAllAttr)
{
    ADECGetRealChn(hAdec);
    return ADEC_GetAttr(hAdec, ADEC_ATTR_ALLATTR, pstAllAttr);
}

HI_S32 HI_MPI_ADEC_SendStream(HI_HANDLE hAdec, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    HI_S32 s32Ret;

    ADECGetRealChn(hAdec);
    CHECK_ADEC_HANDLE(hAdec);

    ADEC_INST_LOCK(hAdec);
    ADEC_DbgCountTrySendStream(hAdec);
    ADEC_INST_UNLOCK(hAdec);

    s32Ret = ADEC_SendStream(hAdec, pstStream, u32PtsMs);
    if (HI_SUCCESS == s32Ret)
    {
        ADEC_INST_LOCK(hAdec);
        ADEC_DbgCountSendStream(hAdec);
        ADEC_INST_UNLOCK(hAdec);

#ifdef AUDIO_SAVE_ADECDATA
        AdecSaveEsInStream(pstStream);
#endif
    }

    return s32Ret;
}

HI_S32 HI_MPI_ADEC_GetBuffer(HI_HANDLE hAdec, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream)
{
    HI_S32 s32Ret;

    ADECGetRealChn(hAdec);
    CHECK_ADEC_HANDLE(hAdec);

    if (HI_NULL_PTR == pstStream)
    {
        HI_ERR_ADEC("invalid pstStream(0x%x) \n", pstStream);
        return HI_ERR_ADEC_NULL_PTR;
    }

    ADEC_INST_LOCK(hAdec);

    if (HI_NULL == g_pAdecArry[hAdec])
    {
        ADEC_INST_UNLOCK(hAdec);
        return HI_ERR_ADEC_NULL_PTR;
    }

    ADEC_DbgCountTryGetBuffer(hAdec);

    memset(g_sStreamBackupArry[hAdec], 0, sizeof(HI_UNF_STREAM_BUF_S) * 3);
    s32Ret = ADEC_GetBuffer(hAdec, u32RequestSize, &g_sStreamBackupArry[hAdec][1], &g_sStreamBackupArry[hAdec][2]);
    if (HI_SUCCESS != s32Ret)
    {
        ADEC_INST_UNLOCK(hAdec);
        return s32Ret;
    }

    if (g_sStreamBackupArry[hAdec][2].u32Size > 0)
    {
        g_sStreamBackupArry[hAdec][0].pu8Data = (HI_U8*)(g_pAdecArry[hAdec]);
        g_sStreamBackupArry[hAdec][0].u32Size = u32RequestSize;
        memcpy(pstStream, &g_sStreamBackupArry[hAdec][0], sizeof(HI_UNF_STREAM_BUF_S));
        g_u32StreamCnt[hAdec] = 2;

        ADEC_DbgCountGetBuffer(hAdec);
        ADEC_INST_UNLOCK(hAdec);
        return HI_SUCCESS;
    }

    memcpy(pstStream, &g_sStreamBackupArry[hAdec][1], sizeof(HI_UNF_STREAM_BUF_S));
    memset(&g_sStreamBackupArry[hAdec][2], 0, sizeof(HI_UNF_STREAM_BUF_S));
    g_u32StreamCnt[hAdec] = 1;

    ADEC_DbgCountGetBuffer(hAdec);

    ADEC_INST_UNLOCK(hAdec);

    return HI_SUCCESS;
}

HI_S32 HI_MPI_ADEC_PutBuffer(HI_HANDLE hAdec, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    HI_S32 s32Ret;

    ADECGetRealChn(hAdec);
    CHECK_ADEC_HANDLE(hAdec);

    if (HI_NULL_PTR == pstStream)
    {
        HI_ERR_ADEC("invalid pstStream(0x%x)\n", pstStream);
        return HI_ERR_ADEC_NULL_PTR;
    }

    ADEC_INST_LOCK(hAdec);

    if (HI_NULL == g_pAdecArry[hAdec])
    {
        ADEC_INST_UNLOCK(hAdec);
        return HI_FAILURE;
    }

    if ((1 != g_u32StreamCnt[hAdec]) && (2 != g_u32StreamCnt[hAdec]))
    {
        HI_ERR_ADEC("hAdec%d: invalid g_u32StreamCnt(0x%x)\n", hAdec, g_u32StreamCnt[hAdec]);
        ADEC_INST_UNLOCK(hAdec);
        return HI_ERR_ADEC_INVALID_PARA;
    }

    if (0 == pstStream->u32Size)
    {
        HI_ERR_ADEC("err u32Size=%d\n", pstStream->u32Size);
        ADEC_INST_UNLOCK(hAdec);
        return HI_SUCCESS;
    }

    ADEC_DbgCountTryPutBuffer(hAdec);
    if (1 == g_u32StreamCnt[hAdec])
    {
        if ((pstStream->pu8Data != g_sStreamBackupArry[hAdec][1].pu8Data)
            || (pstStream->u32Size > g_sStreamBackupArry[hAdec][1].u32Size))
        {
            HI_ERR_ADEC("invalid pstStream->pu8Data or  pstStream->u32Size\n");
            ADEC_INST_UNLOCK(hAdec);
            return HI_ERR_ADEC_INVALID_PARA;
        }

        if (pstStream->u32Size != g_sStreamBackupArry[hAdec][1].u32Size)
        {
            g_sStreamBackupArry[hAdec][1].u32Size = pstStream->u32Size;
        }
    }

    if (2 == g_u32StreamCnt[hAdec])
    {
        if ((pstStream->pu8Data != g_sStreamBackupArry[hAdec][0].pu8Data)
            || (pstStream->u32Size > g_sStreamBackupArry[hAdec][0].u32Size))
        {
            HI_ERR_ADEC("invalid pstStream->pu8Data or  pstStream->u32Size \n");
            ADEC_INST_UNLOCK(hAdec);
            return HI_ERR_ADEC_INVALID_PARA;
        }

        if (pstStream->u32Size <= g_sStreamBackupArry[hAdec][1].u32Size)
        {
            memcpy((HI_VOID*)g_sStreamBackupArry[hAdec][1].pu8Data, (HI_VOID*)pstStream->pu8Data, pstStream->u32Size);
            g_sStreamBackupArry[hAdec][1].u32Size = pstStream->u32Size;
            memset(&g_sStreamBackupArry[hAdec][2], 0, sizeof(HI_UNF_STREAM_BUF_S));
        }
        else
        {
            memcpy((HI_VOID*)g_sStreamBackupArry[hAdec][1].pu8Data, (HI_VOID*)pstStream->pu8Data, g_sStreamBackupArry[hAdec][1].u32Size);
            memcpy((HI_VOID*)g_sStreamBackupArry[hAdec][2].pu8Data, (HI_VOID*)(pstStream->pu8Data + g_sStreamBackupArry[hAdec][1].u32Size),
                   pstStream->u32Size - g_sStreamBackupArry[hAdec][1].u32Size);
            g_sStreamBackupArry[hAdec][2].u32Size = pstStream->u32Size - g_sStreamBackupArry[hAdec][1].u32Size;
        }
    }

    g_u32StreamCnt[hAdec] = 0;

    s32Ret = ADEC_PutBuffer(hAdec, &g_sStreamBackupArry[hAdec][1], &g_sStreamBackupArry[hAdec][2], u32PtsMs);
    if (HI_SUCCESS == s32Ret)
    {
        ADEC_DbgCountPutBuffer(hAdec);

#ifdef AUDIO_SAVE_ADECDATA
        AdecSaveEsInStream(pstStream);
#endif
    }

    ADEC_INST_UNLOCK(hAdec);

    return s32Ret;
}

HI_S32 HI_MPI_ADEC_ReceiveFrame(HI_HANDLE hAdec, HI_UNF_AO_FRAMEINFO_S* pstAOFrame, ADEC_EXTFRAMEINFO_S* pstExtInfo)
{
    HI_S32 s32Ret;

    ADECGetRealChn(hAdec);
    CHECK_ADEC_HANDLE(hAdec);

    ADEC_INST_LOCK(hAdec);
    ADEC_DbgCountTryReceiveFrame(hAdec);
    ADEC_INST_UNLOCK(hAdec);

    s32Ret = ADEC_ReceiveFrame(hAdec, pstAOFrame, pstExtInfo);
    if (HI_SUCCESS == s32Ret)
    {
        ADEC_INST_LOCK(hAdec);
        ADEC_DbgCountReceiveFrame(hAdec);
        ADEC_INST_UNLOCK(hAdec);

#ifdef AUDIO_SAVE_ADECDATA
        AdecSaveOutputData(pstAOFrame);
#endif
    }

    return s32Ret;
}

HI_S32 HI_MPI_ADEC_ReleaseFrame(HI_HANDLE hAdec, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    ADECGetRealChn(hAdec);
    return ADEC_ReleaseFrame(hAdec, pstAOFrame);
}

HI_S32 HI_MPI_ADEC_SetADMixAttr(HI_HANDLE hAdec, HI_BOOL bAdEnable, HI_BOOL bAdToSomePort)
{
    return HI_SUCCESS;
}

HI_S32 HI_MPI_ADEC_GetADMixAttr(HI_HANDLE hAdec, HI_BOOL* pbAdEnable, HI_BOOL* pbAdToSomePort)
{
    return HI_SUCCESS;
}

/*
 * Mixer balance - This parameter controls the mixer balance between the main and associated inputs.
 * The valid values are from -32 (mute associated) to 32 (mute main).
 * Values from -1 to -31 indicate associate program attenuation in steps of 1 dB.
 * Values 1 to 31 indicate attenuation of main program in steps of 1 dB.
 */
HI_S32 HI_MPI_ADEC_SetADBalance(HI_HANDLE hAdec, HI_S16 s16ADBalance)
{
    return HI_SUCCESS;
}

HI_S32 HI_MPI_ADEC_GetADBalance(HI_HANDLE hAdec, HI_S16* ps16ADBalance)
{
    return HI_SUCCESS;
}

HI_S32 HI_MPI_ADEC_SendADStream(HI_HANDLE hAdec, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    return HI_SUCCESS;
}

HI_S32 HI_MPI_ADEC_GetADBuffer(HI_HANDLE hAdec, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream)
{
    return HI_SUCCESS;
}

HI_S32 HI_MPI_ADEC_PutADBuffer(HI_HANDLE hAdec, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    return HI_SUCCESS;
}

HI_S32 HI_MPI_ADEC_GetADDelayMs(HI_HANDLE hAdec, HI_U32* pDelay)
{
    return HI_SUCCESS;
}

HI_S32 HI_MPI_ADEC_GetInfo(HI_HANDLE hAdec, HI_MPI_ADEC_INFO_E enAdecInfo, HI_VOID* pstAdecInfo)
{
    HI_S32 s32Ret;

    ADECGetRealChn(hAdec);

    switch (enAdecInfo)
    {
        case HI_MPI_ADEC_STATUSINFO:
            HI_INFO_ADEC("HI_MPI_ADEC_GetInfo CMD: ADEC_STATUSINFO\n");
            s32Ret = ADEC_GetStatusInfo(hAdec,  (ADEC_STATUSINFO_S*)pstAdecInfo);
            break;

        case HI_MPI_ADEC_STREAMINFO:
            HI_INFO_ADEC("HI_MPI_ADEC_GetInfo CMD: ADEC_STREAMINFO\n");
            s32Ret = ADEC_GetStreamInfo(hAdec, (ADEC_STREAMINFO_S*)pstAdecInfo);
            break;

        case HI_MPI_ADEC_BUFFERSTATUS:
            HI_INFO_ADEC("HI_MPI_ADEC_GetInfo CMD: ADEC_BUFFERSTATUS\n");
            s32Ret = ADEC_GetBufferStatus(hAdec, (ADEC_BUFSTATUS_S*)pstAdecInfo);
            break;

        case HI_MPI_ADEC_DEBUGINFO:
            HI_INFO_ADEC("HI_MPI_ADEC_GetInfo CMD: ADEC_DEBUGINFO\n");
            s32Ret = ADEC_GetDebugInfo(hAdec, (ADEC_DEBUGINFO_S*)pstAdecInfo);
            break;

        case HI_MPI_ADEC_HaSzNameInfo:
            HI_INFO_ADEC("HI_MPI_ADEC_GetInfo CMD: ADEC_HaSzNameInfo\n");
            s32Ret = ADEC_GetHaSzNameInfo(hAdec, (ADEC_SzNameINFO_S*)pstAdecInfo);
            break;

        default:
            HI_ERR_ADEC("HI_MPI_ADEC_GetAttrInfo fail: INVALID PARAM = 0x%x\n", enAdecInfo);
            s32Ret = HI_ERR_ADEC_INVALID_PARA;
            break;
    }

    return s32Ret;
}

HI_S32 HI_MPI_ADEC_GetAudSpectrum(HI_HANDLE hAdec, HI_U16* pSpectrum, HI_U32 u32BandNum)
{
#ifdef HI_ADEC_AUDSPECTRUM_SUPPORT
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_NULL == pSpectrum)
    {
        HI_ERR_ADEC("para pSpectrum is null.\n");
        return HI_FAILURE;
    }

    if ((u32BandNum != 20)
        && (u32BandNum != 80)
        && (u32BandNum != 512))
    {
        HI_ERR_ADEC("para u32BandNum is invalid.\n");
        return HI_FAILURE;
    }

    ADECGetRealChn(hAdec);

    s32Ret = ADEC_GetAnalysisPcmData(hAdec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_ADEC("call ADEC_AudGetAnalysisPcmData failed.\n");
        return s32Ret;
    }

    s32Ret = ADEC_GetAudSpectrum(pSpectrum, u32BandNum);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_ADEC("call ADEC_Mp3DecGetSpectrum failed.\n");
    }

    return s32Ret;
#else
    HI_ERR_ADEC("don't support AUDSPECTRUM!\n");
    return HI_SUCCESS;
#endif
}

HI_S32 HI_MPI_ADEC_SetConfigDeoder(const HI_U32 enDstCodecID, HI_VOID* pstConfigStructure)
{
    return ADEC_SetConfigDecoder(enDstCodecID, pstConfigStructure);
}

HI_S32 HI_MPI_ADEC_SetEosFlag(HI_HANDLE hAdec)
{
    ADECGetRealChn(hAdec);
    return ADEC_SetEosFlag(hAdec);
}

HI_S32 HI_MPI_ADEC_DropStream(HI_HANDLE hAdec, HI_U32 u32SeekPts)
{
    ADECGetRealChn(hAdec);
    return ADEC_DropStream(hAdec, u32SeekPts);
}

HI_S32 HI_MPI_ADEC_SetCodecCmd(HI_HANDLE hAdec, HI_VOID* pstCodecCmd)
{
    ADECGetRealChn(hAdec);
    return ADEC_SetCodecCmd(hAdec, pstCodecCmd);
}

HI_S32 HI_MPI_ADEC_CheckNewEvent(HI_HANDLE hAdec, ADEC_EVENT_S* pstNewEvent)
{
    ADECGetRealChn(hAdec);
    return ADEC_CheckNewEvent(hAdec, pstNewEvent);
}

HI_S32 HI_MPI_ADEC_SetTplay(HI_HANDLE hAdec, ADEC_TPLAY_S* pstTplayParam)
{
    ADECGetRealChn(hAdec);
    return ADEC_SetTplay(hAdec, pstTplayParam);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

