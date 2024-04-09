#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "hi_audio_codec.h"
#include "sonic.h"
#include "HA.AUDIO.SONIC.h"

typedef struct
{
    HI_U32 u32SampleRate;
    HI_U32 u32Ch;
    HI_U32 u32BitPerSample;
    HI_U32 u32SpeedInt;
    HI_U32 u32SpeedDeci;
    sonicStream pstream;
} stSonicInstance;

static HI_HA_ERRORTYPE_E HA_CheckParameter(HI_VOID* pstConfigStructure)
{
    HA_CODEC_SPEED_SET_PARAM_S* pstConfig = HI_NULL;

    pstConfig = (HA_CODEC_SPEED_SET_PARAM_S*)pstConfigStructure;
    if (HI_ADEC_SPEED_INT_SLOW > pstConfig->u32SpeedInt || HI_ADEC_SPEED_INT_BUTT <= pstConfig->u32SpeedInt)
    {
        HA_ERR_PRINT("SpeedInt[%d] is out of rang[%d,%d)\n", pstConfig->u32SpeedInt, HI_ADEC_SPEED_INT_SLOW, HI_ADEC_SPEED_INT_BUTT);
        return HA_ErrorInvalidParameter;
    }

    if (HI_ADEC_SAMPLE_RATE_8K > pstConfig->u32Sample || HI_ADEC_SAMPLE_RATE_192K < pstConfig->u32Sample)
    {
        HA_ERR_PRINT("Invalid Sample parameter\n");
        return HA_ErrorInvalidParameter;
    }

    if (1 > pstConfig->u32Channel || 8 < pstConfig->u32Channel)
    {
        HA_ERR_PRINT("Channel[%d] is out of rang[1,8]\n", pstConfig->u32Channel);
        return HA_ErrorInvalidParameter;
    }

    if (16 != pstConfig->u32BitPerSample && 24 != pstConfig->u32BitPerSample)
    {
        HA_ERR_PRINT("only support 16 and 24 BitPerSmaple\n");
        return HA_ErrorInvalidParameter;
    }

    return HI_SUCCESS;
}

static HI_HA_ERRORTYPE_E HA_SetConfig(HI_VOID* phSonic, HI_VOID* pstConfigStructure)
{
    HI_S32 s32Ret = 0;
    HI_FLOAT speed = 1.0f;
    HA_CODEC_PARAMETER_QUERY_S* pstParam = HI_NULL;
    HA_CODEC_SPEED_SET_PARAM_S* pstConfig = HI_NULL;
    stSonicInstance* hDev = HI_NULL;

    if (!phSonic || !pstConfigStructure)
    {
        HA_ERR_PRINT("HA_SetConfig invalid param!\n");
        return HA_ErrorInvalidParameter;
    }

    hDev = (stSonicInstance*)phSonic;

    pstParam = (HA_CODEC_PARAMETER_QUERY_S*)pstConfigStructure;
    switch (pstParam->enCmd)
    {
        case HA_CODEC_SPEED_SET_CMD:
        {
            s32Ret = HA_CheckParameter(pstConfigStructure);
            if (HI_SUCCESS != s32Ret)
            {
                HA_ERR_PRINT("The input parameter is invalid\n");
                return HA_ErrorInvalidParameter;
            }

            pstConfig = (HA_CODEC_SPEED_SET_PARAM_S*)pstConfigStructure;
            hDev->u32BitPerSample = pstConfig->u32BitPerSample;
            if (pstConfig->u32Sample != hDev->u32SampleRate)
            {
                sonicSetSampleRate(hDev->pstream, pstConfig->u32Sample);
                hDev->u32SampleRate = pstConfig->u32Sample;
            }

            if (pstConfig->u32Channel != hDev->u32Ch)
            {
                sonicSetNumChannels(hDev->pstream, pstConfig->u32Channel);
                hDev->u32Ch = pstConfig->u32Channel;
            }

            if ((pstConfig->u32SpeedInt != hDev->u32SpeedInt) || (pstConfig->u32SpeedDeci != hDev->u32SpeedDeci))
            {
                speed = (float)pstConfig->u32SpeedInt + ((float)pstConfig->u32SpeedDeci) / 1000;
                sonicSetSpeed(hDev->pstream, speed);
                hDev->u32SpeedInt = pstConfig->u32SpeedInt;
                hDev->u32SpeedDeci = pstConfig->u32SpeedDeci;
            }
            break;
        }

        default:
        {
            HA_ERR_PRINT("Input Command error\n");
            return HA_ErrorInvalidParameter;
        }
    }
    return HA_ErrorNone;
}

static HI_HA_ERRORTYPE_E HA_SonicInit(HI_VOID** phSonic,
                                      const HI_HADECODE_OPENPARAM_S* pOpenParam)
{
    HI_U32 sampleRate = 0;
    HI_U32 numChannels = 0;
    HI_U32 bitperSample = 0;
    stSonicInstance* hDev = HI_NULL;
    sonicStream pstream = {0};

    if (!pOpenParam || !phSonic)
    {
        HA_ERR_PRINT("HA_SonicInit invalid param!\n");
        return HA_ErrorInvalidParameter;
    }

    hDev = (stSonicInstance*)malloc(sizeof(stSonicInstance));
    if (HI_NULL == hDev)
    {
        HA_ERR_PRINT("HA_SonicInit alloc mem failed!\n");
        return HA_ErrorInsufficientResources;
    }

    memset(hDev, 0, sizeof(stSonicInstance));

    numChannels  = pOpenParam->sPcmformat.u32DesiredOutChannels;
    sampleRate   = pOpenParam->sPcmformat.u32DesiredSampleRate;
    bitperSample = pOpenParam->sPcmformat.u32BitPerSample;

    pstream = sonicCreateStream(sampleRate, numChannels);
    if (HI_NULL == pstream)
    {
        free(hDev);
        hDev = HI_NULL;
        HA_ERR_PRINT("sonicCreateStream alloc sonic failed!\n");
        return HA_ErrorInsufficientResources;
    }

    sonicSetPitch(pstream, 1.0);
    sonicSetRate(pstream, 1.0);
    sonicSetVolume(pstream, 1.0);
    sonicSetChordPitch(pstream, 0);
    sonicSetQuality(pstream, 0);
    hDev->u32SampleRate = sampleRate;
    hDev->u32Ch = numChannels;
    hDev->u32BitPerSample = bitperSample;
    hDev->u32SpeedInt = 1;
    hDev->u32SpeedDeci = 0;
    hDev->pstream = pstream;
    *phSonic = (HI_VOID*)hDev;

    return HI_SUCCESS;
}

static HI_HA_ERRORTYPE_E HA_SonicDeInit(HI_VOID* pSonic)
{
    stSonicInstance* hDev;

    if (!pSonic)
    {
        HA_ERR_PRINT("SonicCreateStream invald param!\n");
        return HA_ErrorInvalidParameter;
    }

    hDev = (stSonicInstance*)pSonic;
    sonicDestroyStream(hDev->pstream);

    free(hDev);
    hDev = HI_NULL;

    return HA_ErrorNone;
}

static HI_VOID SonicUnifyBitDepthPcmData(HI_U8* pData, HI_U32 u32Samples)
{
    HI_U32 i = 0;
    HI_S16* ps16Dst = (HI_S16*)pData;
    HI_S32* ps32Src = (HI_S32*)pData;

    for (i = 0; i < u32Samples; i++)
    {
        *ps16Dst++ = (HI_S16)((*ps32Src++) >> 16);
    }
}

static HI_HA_ERRORTYPE_E HA_SonicProc(HI_VOID* pSonic,
                                      HI_HADECODE_INPACKET_S* pApkt,
                                      HI_HADECODE_OUTPUT_S*   pAOut)
{
    HI_U32 samplesWritten = 0;
    HI_U32 u32OutSize = 0;
    HI_U32 u32WriteSize = 0;
    HI_U32 u32FrameSize = 0;
    HI_U32 u32Samples = 0;
    HI_U8* pTmpBuf = HI_NULL;
    float speed = 0;
    float TmpSize = 0;
    stSonicInstance* hDev = HI_NULL;

    if ((!pSonic) || (!pApkt) || (!pAOut))
    {
        HA_ERR_PRINT("Process NULL PTR!\n");
        return HA_ErrorInvalidParameter;
    }

    hDev = (stSonicInstance*)pSonic;
    if (0 == hDev->u32Ch)
    {
        HA_ERR_PRINT("Invald ch param!\n");
        return HA_ErrorInvalidParameter;
    }

    u32FrameSize = hDev->u32Ch * (hDev->u32BitPerSample / 8);
    if (0 == u32FrameSize)
    {
        HA_ERR_PRINT("Invald frame param!\n");
        return HA_ErrorInvalidParameter;
    }

    u32Samples = pApkt->s32Size / u32FrameSize;
    //convert to 16bit
    if (16 != hDev->u32BitPerSample)
    {
        SonicUnifyBitDepthPcmData(pApkt->pu8Data, u32Samples * hDev->u32Ch);
    }

    pTmpBuf = (HI_U8*)pAOut->ps32PcmOutBuf;
    if (HI_NULL == pTmpBuf)
    {
        HA_ERR_PRINT("NULL Pointer!\n");
        return HA_ErrorInvalidParameter;
    }

    if ((hDev->u32SpeedInt > 2) || (2 == hDev->u32SpeedInt && hDev->u32SpeedDeci != 0)
        || (0 == hDev->u32SpeedInt && 0 == hDev->u32SpeedDeci))
    {
        if (0 == hDev->u32SpeedInt && 0 == hDev->u32SpeedDeci )
        {
            TmpSize = (float)u32Samples * hDev->u32Ch * sizeof(HI_U16);
            u32OutSize = (HI_U32)TmpSize;
            memset((void *)pAOut->ps32PcmOutBuf, 0, u32OutSize);
        }
        else
        {
            speed = (float)hDev->u32SpeedInt + (float)hDev->u32SpeedDeci / 1000;
            TmpSize = (float)u32Samples * hDev->u32Ch * sizeof(HI_U16) / speed;
            u32OutSize = (HI_U32)TmpSize;
            memset((void *)pAOut->ps32PcmOutBuf, 0, u32OutSize);
        }
    }
    else
    {
        sonicWriteShortToStream(hDev->pstream, (HI_S16*)pApkt->pu8Data, u32Samples);
        do
        {
            samplesWritten = sonicReadShortFromStream(hDev->pstream, (HI_S16*)pTmpBuf, u32Samples);
            if (samplesWritten > 0)
            {
                u32WriteSize = samplesWritten * hDev->u32Ch * sizeof(HI_U16);
                u32OutSize += u32WriteSize;
                if (u32OutSize > (HI_U32)(pApkt->s32Size * ADEC_SONIC_BUFFER_NUM))
                {
                    break;
                }

                pTmpBuf = (HI_U8*)pTmpBuf + u32WriteSize;
            }
        }
        while (samplesWritten > 0);
    }

    pAOut->u32PcmOutBufSize = u32OutSize;
    pAOut->u32BitPerSample = 16;
    pApkt->s32Size = 0;
    pAOut->u32OutChannels = hDev->u32Ch;
    pAOut->u32OutSampleRate = hDev->u32SampleRate;
    return HA_ErrorNone;
}

#ifdef HA_AUDIO_STATIC_LINK_MODE
HI_HA_DECODE_S g_ha_audio_aac_decode_entry =
{
#else
HI_HA_DECODE_S ha_audio_decode_entry =
{
#endif
    .szName               = (const HI_PCHAR) "sonic effect",
    .enCodecID            = 0x1005,
    .uVersion.u32Version  = 0x10000001,
    .pszDescription       = (const HI_PCHAR) "Sonic effect",
    .DecInit              = HA_SonicInit,
    .DecDeInit            = HA_SonicDeInit,
    .DecSetConfig         = HA_SetConfig,
    .DecDecodeFrame       = HA_SonicProc,
};
