/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : mpi_adec.c
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#include <dlfcn.h>
#include <string.h>

#include "hi_drv_adec.h"
#include "hi_error_mpi.h"
#include "hi_drv_adec.h"
#include "mpi_mmz.h"
#include "mpi_sonic.h"
#include "HA.AUDIO.SONIC.h"

static const HI_CHAR* g_szHA_SONIC = "libHA.AUDIO.SONIC.so";

static HI_VOID SonicDelMMz(ADEC_SONIC_S* pstSonic)
{
    (HI_VOID)HI_MPI_MMZ_Unmap(pstSonic->stSonicMMzBuf.phyaddr);
    (HI_VOID)HI_MPI_MMZ_Delete(pstSonic->stSonicMMzBuf.phyaddr);

    pstSonic->pu32SonicAddr = HI_NULL;
}

static HI_S32 SonicAllocMMz(ADEC_SONIC_S* pstSonic, HI_U32 u32AdecChID, HI_U32 u32PcmSize)
{
    snprintf(pstSonic->stSonicMMzBuf.bufname, sizeof(pstSonic->stSonicMMzBuf.bufname), "ADEC_Sonic%d", u32AdecChID);

    pstSonic->stSonicMMzBuf.bufsize = u32PcmSize;
    pstSonic->stSonicMMzBuf.phyaddr = HI_MPI_MMZ_New(pstSonic->stSonicMMzBuf.bufsize, 0x32, HI_NULL, \
                                    pstSonic->stSonicMMzBuf.bufname);
    if (pstSonic->stSonicMMzBuf.phyaddr)
    {
        pstSonic->pu32SonicAddr = (HI_U32*)HI_MPI_MMZ_Map(pstSonic->stSonicMMzBuf.phyaddr, 1);
        pstSonic->u32BufSize = u32PcmSize;
        pstSonic->stSonicMMzBuf.user_viraddr = (HI_U8*)pstSonic->pu32SonicAddr;
    }
    else
    {
        pstSonic->pu32SonicAddr = HI_NULL;
        HI_ERR_ADEC("Sonic MMz Buffer Alloc Failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_BOOL SonicDetectParamChanged(ADEC_SONIC_S* pstSonic,
                                       HI_U32        u32NewSpeedInt,
                                       HI_U32        u32NewSpeedDeci,
                                       HI_U32        u32NewSample,
                                       HI_U32        u32NewCh,
                                       HI_U32        u32NewBitDepth)
{
    HI_U32 u32SonicSpeedInt;
    HI_U32 u32SonicSpeedDeci;
    HI_U32 u32Sample, u32Ch, u32BitDepth;

    u32SonicSpeedInt  = pstSonic->u32SonicInt;
    u32SonicSpeedDeci = pstSonic->u32SonicDeci;
    u32Sample         = pstSonic->u32SampleRate;
    u32Ch             = pstSonic->u32Ch;
    u32BitDepth       = pstSonic->u32BitPerSample;

    if ((u32NewSpeedInt  != u32SonicSpeedInt)  ||
        (u32NewSpeedDeci != u32SonicSpeedDeci) ||
        (u32NewSample    != u32Sample)         ||
        (u32NewCh        != u32Ch)             ||
        (u32NewBitDepth  != u32BitDepth))
    {
        pstSonic->u32SonicInt = u32NewSpeedInt;
        pstSonic->u32SonicDeci = u32NewSpeedDeci;
        pstSonic->u32SampleRate = u32NewSample;
        pstSonic->u32Ch = u32NewCh;
        pstSonic->u32BitPerSample = u32NewBitDepth;
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_S32 SonicSetParam(ADEC_SONIC_S* pstSonic, HI_U32 u32SampleRate, HI_U32 u32Channel, HI_U32 u32BitPerSample)
{
    HI_S32 s32Ret;
    HI_HA_DECODE_S* pEntry;
    HA_CODEC_SPEED_SET_PARAM_S stSpeedMode;

    pEntry = pstSonic->pEntry;
    memset(&stSpeedMode, 0, sizeof(HA_CODEC_SPEED_SET_PARAM_S));
    stSpeedMode.u32SpeedInt = pstSonic->u32SonicInt;
    stSpeedMode.u32SpeedDeci = pstSonic->u32SonicDeci;
    stSpeedMode.u32Sample = u32SampleRate;
    stSpeedMode.u32Channel = u32Channel;
    stSpeedMode.u32BitPerSample = u32BitPerSample;
    stSpeedMode.enCmd = HA_CODEC_SPEED_SET_CMD;

    s32Ret = (HI_S32)pEntry->DecSetConfig(pstSonic->phandle, &stSpeedMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_ADEC("Sonic Set Config Failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 Sonic_Create(HI_VOID** phandle, HI_U32 u32PcmSize, HI_U32 u32AdecChID)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_VOID* pDllModule;
    ADEC_SONIC_S* pstSonic;
    HI_HA_DECODE_S* pEntry;
    HI_HADECODE_OPENPARAM_S sOpenPram;

    pstSonic = (ADEC_SONIC_S*)HI_MALLOC(HI_ID_ADEC, sizeof(ADEC_SONIC_S));
    if (HI_NULL == pstSonic)
    {
        HI_ERR_ADEC("ADEC SONIC Malloc Failed!\n");
        return HI_FAILURE;
    }

    memset(pstSonic, 0 , sizeof(ADEC_SONIC_S));
    pDllModule = dlopen(g_szHA_SONIC, RTLD_LAZY | RTLD_GLOBAL);
    if (HI_NULL == pDllModule)
    {
        HI_WARN_ADEC("Register %s Failed because dlopen fail %s!\n", g_szHA_SONIC, dlerror());
        goto ERR_DLOPEN;
    }

    pEntry = (HI_HA_DECODE_S*)dlsym(pDllModule, "ha_audio_decode_entry");
    if (HI_NULL == pEntry)
    {
        dlerror();
        HI_ERR_ADEC("Sonic dlsm Failed!\n");
        goto ERR_DLSYM;
    }

    s32Ret = SonicAllocMMz(pstSonic, u32AdecChID, u32PcmSize * ADEC_SONIC_BUFFER_NUM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_ADEC("SonicAllocMMz Failed \n");
        goto ERR_DLSYM;
    }

    HA_SONIC_DecGetDefalutOpenParam(&sOpenPram);

    pEntry->DecInit(&pstSonic->phandle, &sOpenPram);
    if (HI_NULL == pstSonic->phandle)
    {
        HI_ERR_ADEC("Sonic DecInit Failed \n");
        goto ERR_INIT;
    }
    pstSonic->pEntry = pEntry;
    pstSonic->pDllModule = pDllModule;
    *phandle = (HI_VOID*)pstSonic;

    return HI_SUCCESS;

ERR_INIT:
    SonicDelMMz(pstSonic);
ERR_DLSYM:
    dlclose(pDllModule);
ERR_DLOPEN:
    if (HI_NULL != pstSonic)
    {
        HI_FREE(HI_ID_ADEC, pstSonic);
    }
    return s32Ret;
}

HI_S32 Sonic_Destroy(HI_VOID* handle)
{
    ADEC_SONIC_S*        pstSonic;
    HI_HA_DECODE_S* pEntry;

    if (HI_NULL == handle)
    {
        return HI_FAILURE;
    }

    pstSonic = (ADEC_SONIC_S*)handle;
    pEntry = pstSonic->pEntry;

    pEntry->DecDeInit(pstSonic->phandle);
    SonicDelMMz(pstSonic);

    dlclose(pstSonic->pDllModule);

    if (HI_NULL != pstSonic)
    {
        HI_FREE(HI_ID_ADEC, pstSonic);
    }

    return HI_SUCCESS;
}

HI_S32 Sonic_Process(HI_VOID* handle, HI_UNF_AO_FRAMEINFO_S* pstAOFrame, HI_U32 u32NewSpeedInt, HI_U32 u32NewSpeedDeci)
{
    HI_S32          s32Ret;
    HI_BOOL         bChanged;
    HI_U32          u32Sample;
    HI_U32          u32Ch;
    HI_U32          u32BitPerSample;
    HI_U32          u32frameSize;
    HI_U32          u32OutFrameDataSize = 0;
    HI_U32          u32LeftByte = 0;
    HI_HADECODE_INPACKET_S stInPkt;
    HI_HADECODE_OUTPUT_S sOut;
    HI_HA_DECODE_S*      pEntry;
    ADEC_SONIC_S*        pstSonic;

    if (HI_NULL == handle)
    {
        return HI_FAILURE;
    }

    pstSonic = (ADEC_SONIC_S*)handle;
    pEntry = pstSonic->pEntry;
    //disable multi ch passthrough
    if (pstAOFrame->u32Channels > HI_UNF_I2S_CHNUM_2)
    {
        pstAOFrame->u32Channels = HI_UNF_I2S_CHNUM_2;
    }

    u32Ch = pstAOFrame->u32Channels;
    u32Sample = pstAOFrame->u32SampleRate;
    u32BitPerSample = pstAOFrame->s32BitPerSample;
    bChanged = SonicDetectParamChanged(pstSonic, u32NewSpeedInt, u32NewSpeedDeci, u32Sample, u32Ch, u32BitPerSample);
    if (HI_TRUE == bChanged)
    {
        s32Ret = SonicSetParam(pstSonic, u32Sample, u32Ch, u32BitPerSample);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_ADEC("SonicSetParam Failed %d!\n", s32Ret);
            return s32Ret;
        }
    }

    u32frameSize =  u32Ch * u32BitPerSample / 8;
    stInPkt.pu8Data = (HI_U8*)pstAOFrame->ps32PcmBuffer;
    stInPkt.s32Size = pstAOFrame->u32PcmSamplesPerFrame * u32frameSize;
    if (0 != (u32NewSpeedInt + u32NewSpeedDeci))
    {
        u32OutFrameDataSize = stInPkt.s32Size * 1000 / (u32NewSpeedInt * 1000 + u32NewSpeedDeci);
    }
    u32LeftByte = u32OutFrameDataSize % (2 * u32frameSize);// sampling points ouptut must be even
    sOut.ps32PcmOutBuf = (HI_S32*)pstSonic->pu32SonicAddr;
    sOut.u32PcmOutBufSize = pstSonic->u32BufSize;

    s32Ret = pEntry->DecDecodeFrame(pstSonic->phandle, &stInPkt, &sOut);
    if (HA_ErrorNone != s32Ret)
    {
        HI_ERR_ADEC("Sonic Process failed\n");
        return s32Ret;
    }

    /*save to cache*/
    if ((pstSonic->u32CacheOffSet + sOut.u32PcmOutBufSize) < ADEC_SONIC_CACHE_BUFFER_SIZE)
    {
        memcpy(pstSonic->ucPcmCache + pstSonic->u32CacheOffSet, sOut.ps32PcmOutBuf, sOut.u32PcmOutBufSize);
        pstSonic->u32CacheOffSet +=sOut.u32PcmOutBufSize;
        memset(sOut.ps32PcmOutBuf, 0x0, u32OutFrameDataSize);
    }
    else
    {
        HI_ERR_ADEC("OutPut Data is bigger Than Cache Buffer\n");
    }

    if (HI_FALSE == pstSonic->bFristFrame)
    {
        /*out mute.*/
        pstSonic->bFristFrame = HI_TRUE;
    }
    else
    {
        /*get frame from cache.*/

        if (pstSonic->u32CacheOffSet < u32OutFrameDataSize)
        {
            HI_WARN_ADEC("data is not enough \n");
            u32OutFrameDataSize = 0;
        }
        else
        {
            if (u32LeftByte > 0)
            {
                if (pstSonic->u32CacheOffSet >= u32OutFrameDataSize - u32LeftByte + (2 * u32frameSize))
                {
                u32OutFrameDataSize = u32OutFrameDataSize + ((2 * u32frameSize) - u32LeftByte);
                }
                else
                {
                u32OutFrameDataSize = u32OutFrameDataSize - u32LeftByte;
                }
            }
            memcpy(sOut.ps32PcmOutBuf, pstSonic->ucPcmCache, u32OutFrameDataSize);
            pstSonic->u32CacheOffSet -= u32OutFrameDataSize;
            memmove(pstSonic->ucPcmCache, pstSonic->ucPcmCache+ u32OutFrameDataSize, pstSonic->u32CacheOffSet);
        }
    }
    pstAOFrame->u32PcmSamplesPerFrame = u32OutFrameDataSize / u32frameSize;
    pstAOFrame->ps32PcmBuffer = sOut.ps32PcmOutBuf;
    pstAOFrame->s32BitPerSample = HI_UNF_BIT_DEPTH_16;

    //no passthought when tplay mode
    pstAOFrame->u32BitsBytesPerFrame = 0;
    pstAOFrame->ps32BitsBuffer = HI_NULL_PTR;
    pstAOFrame->u32Channels = u32Ch;
    pstAOFrame->u32SampleRate = u32Sample;

    return HI_SUCCESS;
}
