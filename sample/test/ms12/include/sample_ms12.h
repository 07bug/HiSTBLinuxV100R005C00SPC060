#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_unf_hdmi.h"
#include "hi_go.h"
#include "hi_unf_ecs.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "hi_adp.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_boardcfg.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "HA.AUDIO.DTSHD.decode.h"
#include "HA.AUDIO.DOLBYMS12.decode.h"
#ifdef DOLBYPLUS_HACODEC_SUPPORT
#include "HA.AUDIO.DOLBYPLUS.decode.h"
#endif
#include "HA.AUDIO.DOLBYTRUEHD.decode.h"
#include "HA.AUDIO.TRUEHDPASSTHROUGH.decode.h"

#ifndef __SAMPLE_MS12_H__
#define __SAMPLE_MS12_H__

#ifdef __cplusplus
extern "C" {
#endif
#define SAMPLE_MAX_PROG_NUM    ((HI_U32)32)
#define SAMPLE_MAX_AUDIO_NUM   ((HI_U32)32)

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf(fmt, args...)
#else
#define sample_printf(fmt, args...) \
    ({printf("[%s:%d]: " fmt "", __FUNCTION__, __LINE__, ## args);})
#endif
#define SAMPLE_DOFUNC_RETURN(func, ret)\
    do{\
        (ret)=func;\
        if (HI_SUCCESS != (ret))\
        {\
            sample_printf("calling %s failed! ret = 0x%08x\n", # func, (ret));\
            return ret;\
        }\
    }while(0)
#define SAMPLE_DOFUNC_NO_RETURN(func, ret)\
    do{\
        (ret)=func;\
        if (HI_SUCCESS != (ret))\
        {\
            sample_printf("calling %s failed! ret = 0x%08x\n", # func, (ret));\
        }\
    }while(0)
#define SAMPLE_DOFUNC_GOTO(func, ret, exit_label)\
    do{\
        (ret)=func;\
        if (HI_SUCCESS != (ret))\
        {\
            sample_printf("calling %s failed! ret = 0x%08x\n", # func, (ret));\
            goto exit_label;\
        }\
    }while(0)
#define SAMPLE_CHECK_POINTER_RETURN(pointer)\
    do{\
        if (HI_NULL == (pointer))\
        {\
            sample_printf("null pointer!\n");\
            return HI_FAILURE;\
        }\
    }while(0)
typedef struct tagSAMPLE_THREAD_INFO_S
{
    pthread_t threadID;
    HI_BOOL bExitFlag;
}SAMPLE_THREAD_INFO_S;

#ifdef __cplusplus
}
#endif

#endif
