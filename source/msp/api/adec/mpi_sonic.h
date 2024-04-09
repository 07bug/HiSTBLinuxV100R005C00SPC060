#ifndef __HI_SONIC_H__
#define __HI_SONIC_H__

#include <stdio.h>
#include <pthread.h>

#include "hi_type.h"
#include "hi_unf_sound.h"
#include "hi_mpi_adec_core.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define ADEC_SONIC_CACHE_BUFFER_SIZE 6144*8*2 //Double the frame size

typedef struct
{
    HI_BOOL         bFristFrame;
    HI_U32          u32SonicInt;
    HI_U32          u32SonicDeci;
    HI_U32          u32BufSize;
    HI_U32          u32SampleRate;
    HI_U32          u32Ch;
    HI_U32          u32BitPerSample;
    HI_U32          u32CacheOffSet;
    HI_MMZ_BUF_S    stSonicMMzBuf;
    HI_U32*         pu32SonicAddr;
    HI_HA_DECODE_S* pEntry;
    HI_VOID*        pDllModule;
    HI_VOID*        phandle;
    HI_U8           ucPcmCache[ADEC_SONIC_CACHE_BUFFER_SIZE];
} ADEC_SONIC_S;

HI_S32 Sonic_Create(HI_VOID** phSonic, HI_U32 u32PcmSize, HI_U32 u32AdecChID);
HI_S32 Sonic_Destroy(HI_VOID* phSonic);
HI_S32 Sonic_Process(HI_VOID* phSonic, HI_UNF_AO_FRAMEINFO_S* pstAOFrame, HI_U32 u32NewSpeedInt, HI_U32 u32NewSpeedDeci);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
