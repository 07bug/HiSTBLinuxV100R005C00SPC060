/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: engine_sink.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "drv_ao_ioctl.h"
#include "hi_drv_ao.h"
#include "hi_error_mpi.h"
#include "hi_mpi_ao.h"
#include "mpi_mmz.h"

#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)

#define OUTPUT_TRACK_SLEEP_MS       (5 * 1000)
#define FIFO_BLOCK_MS               (32)
#define HBR_FRAME_LENGTH            (0x6000)
#define LBR_FRAME_LENGTH            (0x1800)
#define PCM_FRAME_LENGTH            (0x1800)
#define BITS_BYTE_PER_FRAME         (0x60001800)
#define PCM_SAMPLES_PER_FRAME       (0x600)

/*USECASE LOWLATENCY*/
#define TRACK_BUF_LOWLATENCY_MS               (65)
#define TRACK_BUF_LOWLATENCY_STARTTHRESHOLD   (30)
#define AIP_FIFO_BUFFER_LOW_LATENCY_MS     (12)
#define AOP_BUFFER_LOW_LATENCY_MS          (20)
/*USECASE NORMAL*/
#define TRACK_BUF_MS               (200)
#define TRACK_BUF_STARTTHRESHOLD   (50)
#define AIP_FIFO_BUFFER_MS         (40)
#define AOP_BUFFER_MS              (40)

#define TRACK_RESUME_THRESHOLD_RENDER_MS  (30)
#define TRACK_RESUME_THRESHOLD_NORMAL_MS  (50)

#define PAGE_SIZE_MASK     (0xfffff000)
#define MEM_PAGE_SIZE      (0x1000)

#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
#define HI_AUDIO_DSP_SUPPORT
#endif

extern HI_S32 g_s32AOFd;

typedef struct
{
    HI_HANDLE hSinkTrack;
    HI_HANDLE bExtTrackUsed;

    HI_U32    u32ExtTrackBufThreshold;
    HI_U32    u32ExtTrackBufLevel;

    HI_BOOL   bFifoValid;
    HI_BOOL   bContinuousOutputEnable;
    HI_BOOL   bOutputAtmosEnable;
    HI_BOOL   bTrackFadeEnable;
    HI_BOOL   bDeepContinuousEnable;
    HI_UNF_SND_OUTPUTLATENCY_E enOutLatencyMode;

    ENGINE_MANAGER_S* pstEngineManager;
    SOURCE_MANAGER_S* pstSourceManager;
} SINK_MANAGER_S;

static SINK_MANAGER_S* g_pstSinkManager = HI_NULL;

static const HI_U16 g_ddp_heard[] =
{
    0xF872, 0x4E1F, 0x0015, 0x0600, 0x0B77, 0x02FF, 0x3F87, 0xE021, 0x0620, 0x0000,
    0x0002, 0x0000, 0x0007, 0xF941, 0x013E, 0xD408, 0x0808, 0x0802, 0x0202, 0x0200,
    0x8080, 0x8080, 0x2020, 0x2020, 0x0808, 0x0808, 0x31F3, 0xE7CF, 0x9F3E, 0x7CF9,
    0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCFBF, 0xE757,
    0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3,
    0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCFBF, 0xF9D5, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3,
    0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9,
    0xF3EF, 0xFE75, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9,
    0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CFB, 0xFF9D, 0x5F3E, 0x7CF9,
    0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C,
    0xF9F3, 0xE7CF, 0x9F3E, 0xFFE7, 0x57CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C,
    0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0xBFF9,
    0xD729, 0xE892, 0x49C7, 0x005F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFF0,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0009, 0x148A, 0x4522, 0x9148, 0xA452, 0x2914,
    0x8A45, 0x22BF, 0xFFFF, 0xFFFF, 0xFFC0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0033, 0x3333, 0x3333, 0x3333, 0x3333, 0x3333, 0x332F, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFF8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0004,
    0x8A45, 0x2291, 0x48A4, 0x5229, 0x148A, 0x4522, 0x915F, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFF0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0009, 0x148A, 0x4522,
    0x9148, 0xA452, 0x2914, 0x8A45, 0x22BF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFE0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0012, 0x2914, 0x8A45, 0x2291, 0x48A4,
    0x5229, 0x148A, 0x457F, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFC0, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0024, 0x5229, 0x148A, 0x4522, 0x9148, 0xA452, 0x2914,
    0x8AFE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x4040, 0x5124, 0x9240, 0x4051, 0x2492, 0x4040,
    0x5124, 0x9240, 0x4051, 0x2492, 0x4040, 0x5124, 0x9200, 0x0000, 0x0000, 0x0000,
    0x5FD0, 0xFAC2,
};

static const HI_U16 g_dd_heard[] =
{
    0xF872, 0x4E1F, 0x0001, 0x5000, 0x0B77, 0x0BF5, 0x2430, 0xE1FC, 0x04C0, 0x3F01,
    0x955D, 0x1451, 0x451F, 0xF3AB, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C,
    0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E,
    0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xC99E,
    0xC373, 0xFFCE, 0xAF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F,
    0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF,
    0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F29, 0x86E9, 0x37FF,
    0x3ABE, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7,
    0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3,
    0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xA5F4, 0x373F, 0xFCEA, 0xF9F3,
    0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9,
    0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C,
    0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF267, 0x4A6B, 0x7FF3, 0xABE7, 0xCF9F, 0x3E7C,
    0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E,
    0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F,
    0x3E7C, 0xF9F3, 0xE7CA, 0x9325, 0x7DFF, 0xCEB9, 0x4F8E, 0x2448, 0x9122, 0x4400,
    0x0000, 0x0007, 0x78F1, 0xE3C7, 0x7777, 0x7777, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0EEE, 0xEEED,
    0xB6DB, 0x6DB6, 0xF9F3, 0x5AD6, 0xB5AD, 0x6BE7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF,
    0x9F3E, 0x7CF9, 0xF000, 0x0000, 0x00EF, 0x1E3C, 0x78EE, 0xEEEE, 0xEEE0, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0001, 0xDDDD, 0xDDB6, 0xDB6D, 0xB6DF, 0x3E6B, 0x5AD6, 0xB5AD, 0x7CF9, 0xF3E7,
    0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x0000, 0x0000, 0x1DE3, 0xC78F, 0x1DDD,
    0xDDDD, 0xDC00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x003B, 0xBBBB, 0xB6DB, 0x6DB6, 0xDBE7, 0xCD6B, 0x5AD6,
    0xB5AF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7C0, 0x0000, 0x0003,
    0xBC78, 0xF1E3, 0xBBBB, 0xBBBB, 0x8000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0777, 0x7776, 0xDB6D, 0xB6DB,
    0x7CF9, 0xAD6B, 0x5AD6, 0xB5F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C,
    0xF800, 0x0000, 0x0077, 0x8F1E, 0x3C77, 0x7777, 0x7770, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xEEEE,
    0xEEDB, 0x6DB6, 0xDB6F, 0x9F35, 0xAD6B, 0x5AD6, 0xBE7C, 0xF9F3, 0xE7CF, 0x9F3E,
    0x7CF9, 0xF3E7, 0xCF9F, 0x0000, 0x0000, 0x0EF0, 0x1F80, 0x8000, 0x0000, 0x0000,
    0x0EF1, 0xE3C7, 0x8EEE, 0xEEEE, 0xEE00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001D, 0xDDDD, 0xDB6D, 0xB6DB,
    0x6DF3, 0xE6B5, 0xAD6B, 0x5AD7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9,
    0xF3E0, 0x0000, 0x0001, 0xDE3C, 0x78F1, 0xDDDD, 0xDDDD, 0xC000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03BB,
    0xBBBB, 0x6DB6, 0xDB6D, 0xBE7C, 0xD6B5, 0xAD6B, 0x5AF9, 0xF3E7, 0xCF9F, 0x3E7C,
    0xF9F3, 0xE7CF, 0x9F3E, 0x7C00, 0x0000, 0x003B, 0xC78F, 0x1E3B, 0xBBBB, 0xBBB8,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x7777, 0x776D, 0xB6DB, 0x6DB7, 0xCF9A, 0xD6B5, 0xAD6B, 0x5F3E,
    0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x8000, 0x0000, 0x0778, 0xF1E3,
    0xC777, 0x7777, 0x7700, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x000E, 0xEEEE, 0xEDB6, 0xDB6D, 0xB6F9, 0xF35A,
    0xD6B5, 0xAD6B, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F0, 0x0000,
    0x0000, 0xEF1E, 0x3C78, 0xEEEE, 0xEEEE, 0xE000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01DD, 0xDDDD, 0xB6DB,
    0x6DB6, 0xDF3E, 0x6B5A, 0xD6B5, 0xAD7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7,
    0xCF9F, 0x3E00, 0x0000, 0x001D, 0xE03F, 0x0100, 0x0000, 0x0000, 0x001D, 0xE3C7,
    0x8F1D, 0xDDDD, 0xDDDC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3BBB, 0xBBB6, 0xDB6D, 0xB6DB, 0xE7CD,
    0x6B5A, 0xD6B5, 0xAF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xC000,
    0x0000, 0x03BC, 0x78F1, 0xE3BB, 0xBBBB, 0xBB80, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0007, 0x7777, 0x76DB,
    0x6DB6, 0xDB7C, 0xF9AD, 0x6B5A, 0xD6B5, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF,
    0x9F3E, 0x7CF8, 0x0000, 0x0000, 0x778F, 0x1E3C, 0x7777, 0x7777, 0x7000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x00EE, 0xEEEE, 0xDB6D, 0xB6DB, 0x6F9F, 0x35AD, 0x6B5A, 0xD6BE, 0x7CF9, 0xF3E7,
    0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F00, 0x0000, 0x000E, 0xF1E3, 0xC78E, 0xEEEE,
    0xEEEE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x1DDD, 0xDDDB, 0x6DB6, 0xDB6D, 0xF3E6, 0xB5AD, 0x6B5A,
    0xD7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE000, 0x0000, 0x01DE,
    0x3C78, 0xF1DD, 0xDDDD, 0xDDC0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0xBBBB, 0xBB6D, 0xB6DB, 0x6DBE,
    0x7CD6, 0xB5AD, 0x6B5A, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C,
    0x0000, 0x0000, 0x3BC0, 0x7E02, 0x0002, 0x3300, 0xBB23, 0x994F, 0xFC21, 0x1A47,
    0x7AFF, 0x7198, 0xA5EF, 0x8CF2, 0xED20, 0x5D05, 0xC2C1, 0xD282, 0x9404, 0xDC17,
    0xD318, 0x6C75, 0xEE2C, 0x704C, 0x5772, 0xDA4C, 0x7D19, 0x9826, 0xD051, 0x9C88,
    0xC049, 0x0000, 0x0000, 0x1DE3, 0xC78F, 0x1DDD, 0xDDDD, 0xDC00, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x003B,
    0xBBBB, 0xB6DB, 0x6DB6, 0xDBE7, 0xCD6B, 0x5AD6, 0xB5AF, 0x9F3E, 0x7CF9, 0xF3E7,
    0xCF9F, 0x3E7C, 0xF9F3, 0xE7C0, 0x0000, 0x0003, 0xBC78, 0xF1E3, 0xBBBB, 0xBBBB,
    0x8000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0777, 0x7776, 0xDB6D, 0xB6DB, 0x7CF9, 0xAD6B, 0x5AD6, 0xB5F3,
    0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF800, 0x0000, 0x0077, 0x8F1E,
    0x3C77, 0x7777, 0x7770, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xEEEE, 0xEEDB, 0x6DB6, 0xDB6F, 0x9F35,
    0xAD6B, 0x5AD6, 0xBE7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x0000,
    0x0000, 0x0EF1, 0xE3C7, 0x8EEE, 0xEEEE, 0xEE00, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001D, 0xDDDD, 0xDB6D,
    0xB6DB, 0x6DF3, 0xE6B5, 0xAD6B, 0x5AD7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E,
    0x7CF9, 0xF3E0, 0x0000, 0x0001, 0xDE3C, 0x78F1, 0xDDDD, 0xDDDD, 0xC000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x03BB, 0xBBBB, 0x6DB6, 0xDB6D, 0xBE7C, 0xD6B5, 0xAD6B, 0x5AF9, 0xF3E7, 0xCF9F,
    0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7C00, 0x0000, 0x003B, 0xC07E, 0x0200, 0x0258,
    0x00D4, 0x23BD, 0x3331, 0xA737, 0x3EA4, 0xC49E, 0x991B, 0x2B62, 0x7688, 0x8AF3,
    0x04D9, 0x92C1, 0x7200, 0xF33C, 0xF2EB, 0x5DD4, 0xB38C, 0x80F9, 0xE4D1, 0x0D1B,
    0xB7AB, 0xB2AA, 0x5B0B, 0x2015, 0xFFDF, 0x07CE, 0xD519, 0x1744, 0x0CA7, 0x01E7,
    0xD47B, 0x7327, 0x5C83, 0x1E74, 0xD6B0, 0xB23E, 0x71F3, 0xDFF5, 0x5C3A, 0x5609,
    0xC977, 0xC5EA, 0xE798, 0xDD08, 0x0000, 0x0000, 0x1DE3, 0xC78F, 0x1DDD, 0xDDDD,
    0xDC00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x003B, 0xBBBB, 0xB6DB, 0x6DB6, 0xDBE7, 0xCD6B, 0x5AD6, 0xB5AF,
    0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7C0, 0x0000, 0x0003, 0xBC78,
    0xF1E3, 0xBBBB, 0xBBBB, 0x8000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0777, 0x7776, 0xDB6D, 0xB6DB, 0x7CF9,
    0xAD6B, 0x5AD6, 0xB5F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF800,
    0x0000, 0x0077, 0x8F1E, 0x3C77, 0x7777, 0x7770, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xEEEE, 0xEEDB,
    0x6DB6, 0xDB6F, 0x9F35, 0xAD6B, 0x5AD6, 0xBE7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9,
    0xF3E7, 0xCF9F, 0x0000, 0x0000, 0x0EF1, 0xE3C7, 0x8EEE, 0xEEEE, 0xEE00, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x001D, 0xDDDD, 0xDB6D, 0xB6DB, 0x6DF3, 0xE6B5, 0xAD6B, 0x5AD7, 0xCF9F, 0x3E7C,
    0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E0, 0x0000, 0x0001, 0xDE3C, 0x78F1, 0xDDDD,
    0xDDDD, 0xC000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x03BB, 0xBBBB, 0x6DB6, 0xDB6D, 0xBE7C, 0xD6B5, 0xAD6B,
    0x5AF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7C00, 0x0000, 0x003B,
    0xC07E, 0x0200, 0x0257, 0x00E5, 0x8F4E, 0xD3F5, 0x4AC8, 0xBB46, 0xBBFB, 0x3007,
    0xD098, 0xA26A, 0x7A4D, 0x819E, 0xAACB, 0x3CD2, 0x4EC2, 0x4538, 0x58E2, 0x0BFF,
    0xB6DC, 0xFE57, 0x5A5E, 0x8E6F, 0x3219, 0x2B79, 0x2FBD, 0x45A4, 0x42FA, 0x4C1F,
    0x5981, 0xB01C, 0x6600, 0xE1CA, 0x5728, 0x4F58, 0x1EA9, 0x6AF8, 0xA933, 0xA2D9,
    0xEA76, 0x672A, 0xCF23, 0x291D, 0x49E8, 0x58E1, 0x4900, 0x0000, 0x001D, 0xE3C7,
    0x8F1D, 0xDDDD, 0xDDDC, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3BBB, 0xBBB6, 0xDB6D, 0xB6DB, 0xE7CD,
    0x6B5A, 0xD6B5, 0xAF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xC000,
    0x0000, 0x03BC, 0x78F1, 0xE3BB, 0xBBBB, 0xBB80, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0007, 0x7777, 0x76DB,
    0x6DB6, 0xDB7C, 0xF9AD, 0x6B5A, 0xD6B5, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF,
    0x9F3E, 0x7CF8, 0x0000, 0x0000, 0x778F, 0x1E3C, 0x7777, 0x7777, 0x7000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x00EE, 0xEEEE, 0xDB6D, 0xB6DB, 0x6F9F, 0x35AD, 0x6B5A, 0xD6BE, 0x7CF9, 0xF3E7,
    0xCF9F, 0x3E7C, 0xF9F3, 0xE7CF, 0x9F00, 0x0000, 0x000E, 0xF1E3, 0xC78E, 0xEEEE,
    0xEEEE, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x1DDD, 0xDDDB, 0x6DB6, 0xDB6D, 0xF3E6, 0xB5AD, 0x6B5A,
    0xD7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C, 0xF9F3, 0xE000, 0x0000, 0x01DE,
    0x3C78, 0xF1DD, 0xDDDD, 0xDDC0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0xBBBB, 0xBB6D, 0xB6DB, 0x6DBE,
    0x7CD6, 0xB5AD, 0x6B5A, 0xF9F3, 0xE7CF, 0x9F3E, 0x7CF9, 0xF3E7, 0xCF9F, 0x3E7C,
    0x0000, 0x0000, 0x3BC0, 0x7523,
};

#ifdef HI_AUDIO_DSP_SUPPORT
static HI_S32 SinkMmap(RENDER_MAP_ATTR_S* pstMapattr)
{
    HI_U32  u32SizeInPage;
    HI_U32  u32PageDiff;
    HI_U32  u32PhyAddrInPage;
    HI_VOID* pMapedAddr = HI_NULL;

    u32PhyAddrInPage = pstMapattr->u32PhyAddr & PAGE_SIZE_MASK;
    u32PageDiff = pstMapattr->u32PhyAddr - u32PhyAddrInPage;
    u32SizeInPage = ( ( 4 + u32PageDiff  - 1 ) & PAGE_SIZE_MASK ) + MEM_PAGE_SIZE;

    pMapedAddr = (HI_VOID*)mmap((HI_VOID*)0, u32SizeInPage, PROT_READ | PROT_WRITE, MAP_SHARED, g_s32AOFd, u32PhyAddrInPage);
    if (MAP_FAILED == pMapedAddr)
    {
        HI_ERR_AO("HIAOMmap mmap failed\n");
        return HI_FAILURE;
    }

    pstMapattr->pMapVirAddr = pMapedAddr;
    pstMapattr->pVirAddr = (HI_VOID*)(pMapedAddr + u32PageDiff);
    pstMapattr->u32MapSize = u32SizeInPage;

    return HI_SUCCESS;
}

static HI_VOID SinkUnmap(RENDER_MAP_ATTR_S* pstMapattr)
{
    (HI_VOID)munmap(pstMapattr->pMapVirAddr, pstMapattr->u32MapSize);
}

#endif

static HI_VOID SinkBuildFrame(HI_HADECODE_OUTPUT_S* pstPackOut, HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    pstAOFrame->s32BitPerSample = RENDER_OUT_FRAME_BITWIDTH;
    pstAOFrame->u32Channels   = RENDER_OUT_FRAME_CHANNEL;
    pstAOFrame->bInterleaved  = HI_TRUE;
    pstAOFrame->u32SampleRate = RENDER_OUT_FRAME_SAMPLERATE;
    pstAOFrame->u32PtsMs = 0xffffffff;
    pstAOFrame->u32BitsBytesPerFrame = pstPackOut->u32BitsOutBytesPerFrame;
    pstAOFrame->ps32BitsBuffer = pstPackOut->ps32BitsOutBuf;
    pstAOFrame->u32FrameIndex = 0;
    pstAOFrame->u32PcmSamplesPerFrame = pstPackOut->u32PcmOutSamplesPerFrame;
    pstAOFrame->ps32PcmBuffer = pstPackOut->ps32PcmOutBuf;
    pstAOFrame->u32IEC61937DataType = 0;
}

static HI_S32 SinkCreateTrack(HI_VOID)
{
    HI_S32 s32Ret;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr = {0};

    s32Ret = HI_MPI_RENDER_GetDefaultOpenAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("call HI_MPI_AO_Track_GetDefaultOpenAttr failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HI_MPI_RENDER_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &g_pstSinkManager->hSinkTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("call HI_MPI_AO_Track_Create failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HI_MPI_RENDER_GetTrackAttr(g_pstSinkManager->hSinkTrack, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("call HI_MPI_AO_Track_GetAttr failed(0x%x)\n", s32Ret);
    }

    stTrackAttr.u32StartThresholdMs = TRACK_BUF_STARTTHRESHOLD;
    stTrackAttr.u32BufLevelMs = TRACK_BUF_MS;

    s32Ret = HI_MPI_RENDER_SetTrackAttr(g_pstSinkManager->hSinkTrack, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("call HI_MPI_AO_Track_SetAttr failed(0x%x)\n", s32Ret);
    }

    s32Ret = HI_MPI_RENDER_StartTrack(g_pstSinkManager->hSinkTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("call HI_MPI_AO_Track_Start failed(0x%x)\n", s32Ret);
        goto ERR_CREATTRACK;
    }

    return HI_SUCCESS;

ERR_CREATTRACK:
    HI_MPI_RENDER_DestroyTrack(g_pstSinkManager->hSinkTrack);

    return s32Ret;
}

static HI_S32 SinkDestoryTrack(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = HI_MPI_RENDER_StopTrack(g_pstSinkManager->hSinkTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("call HI_MPI_AO_Track_Stop failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return HI_MPI_RENDER_DestroyTrack(g_pstSinkManager->hSinkTrack);
}

static HI_S32 SinkSetTrackOutLatency(HI_U32 u32AopDmaMS, HI_U32 u32AipFifoMs, HI_U32 u32ResumeThresholdMs)
{
    HI_S32 s32Ret;

    s32Ret = HI_MPI_AO_SND_SetLowLatency(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, u32AopDmaMS);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SND_SetLowLatency, s32Ret);
        return s32Ret;
    }

    s32Ret = HI_MPI_AO_SetTrackFifoLatency(g_pstSinkManager->hSinkTrack, u32AipFifoMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SetTrackFifoLatency, s32Ret);
        return s32Ret;
    }

    s32Ret = HI_MPI_AO_Track_SetResumeThresholdMs(g_pstSinkManager->hSinkTrack, u32ResumeThresholdMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_Track_SetResumeThresholdMs, s32Ret);
    }

    return s32Ret;
}

static HI_S32 SinkEnableTrackContinueOutput(HI_BOOL bContinueEnable)
{
    HI_S32 s32Ret;

    s32Ret = HI_MPI_AO_SetContinueOutputEnable(HI_UNF_SND_0, bContinueEnable);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SetContinueOutputEnable, s32Ret);
    }

    return s32Ret;
}

static HI_S32 SinkEnableTrackOutputAtmos(HI_BOOL bOutputAtmosEnable)
{
    HI_S32 s32Ret;

    s32Ret = HI_MPI_AO_SetOutputAtmosEnable(HI_UNF_SND_0, bOutputAtmosEnable);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SetOutputAtmosEnable, s32Ret);
    }

    return s32Ret;
}

static HI_S32 SinkCreate(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = SinkCreateTrack();
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SinkCreateTrack, s32Ret);
        return s32Ret;
    }

    s32Ret = SinkSetTrackOutLatency(AOP_BUFFER_MS, AIP_FIFO_BUFFER_MS, TRACK_RESUME_THRESHOLD_NORMAL_MS);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SinkSetTrackOutLatency, s32Ret);
    }

    return s32Ret;
}

static HI_S32 SinkDestory(HI_VOID)
{
    return SinkDestoryTrack();
}

static HI_S32 SinkAddMuteData(HI_VOID)
{
    HI_S32 s32Ret;
    HI_U8* pu8Buf;
    HI_UNF_AO_FRAMEINFO_S stAOFrame;

    pu8Buf = (HI_U8*)malloc(PCM_FRAME_LENGTH + LBR_FRAME_LENGTH + HBR_FRAME_LENGTH);
    if (HI_NULL == pu8Buf)
    {
        HI_ERR_AO("ao frame buffer malloc failed!\n");
        return HI_FAILURE;
    }

    if (sizeof(g_dd_heard) > LBR_FRAME_LENGTH || sizeof(g_ddp_heard) > HBR_FRAME_LENGTH)
    {
        HI_ERR_AO("Invalid IEC61937 Dolby frame!\n");
        return HI_FAILURE;
    }

    memset(pu8Buf, 0, PCM_FRAME_LENGTH + LBR_FRAME_LENGTH + HBR_FRAME_LENGTH);
    memcpy(pu8Buf + PCM_FRAME_LENGTH, g_dd_heard, sizeof(g_dd_heard));
    memcpy(pu8Buf + PCM_FRAME_LENGTH + LBR_FRAME_LENGTH, g_ddp_heard, sizeof(g_ddp_heard));

    stAOFrame.s32BitPerSample = RENDER_OUT_FRAME_BITWIDTH;
    stAOFrame.u32Channels   = RENDER_OUT_FRAME_CHANNEL;
    stAOFrame.bInterleaved  = HI_TRUE;
    stAOFrame.u32SampleRate = RENDER_OUT_FRAME_SAMPLERATE;
    stAOFrame.u32PtsMs = HI_INVALID_PTS;
    stAOFrame.u32BitsBytesPerFrame = BITS_BYTE_PER_FRAME;
    stAOFrame.ps32BitsBuffer = (HI_S32*)(pu8Buf + PCM_FRAME_LENGTH);
    stAOFrame.u32FrameIndex = 0;
    stAOFrame.u32PcmSamplesPerFrame = PCM_SAMPLES_PER_FRAME;
    stAOFrame.ps32PcmBuffer = (HI_S32*)pu8Buf;
    stAOFrame.u32IEC61937DataType = 0;

    s32Ret = HI_MPI_AO_Track_SendData(g_pstSinkManager->hSinkTrack, &stAOFrame);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_Track_SendData, s32Ret);
    }

    free(pu8Buf);

    return s32Ret;
}

static HI_S32 SinkSetTrackAttr(HI_BOOL bContinueEnable)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32AopLatencyMs = AOP_BUFFER_MS;
    HI_U32 u32FIFOLatencyMs = AIP_FIFO_BUFFER_MS;
    HI_U32 u32ThresholdMs = TRACK_RESUME_THRESHOLD_NORMAL_MS;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr = {0};

    s32Ret = HI_MPI_RENDER_GetTrackAttr(g_pstSinkManager->hSinkTrack, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_RENDER_GetTrackAttr, s32Ret);
        return s32Ret;
    }

    if (HI_TRUE == bContinueEnable)
    {
        u32AopLatencyMs  = AOP_BUFFER_LOW_LATENCY_MS;
        u32FIFOLatencyMs = AIP_FIFO_BUFFER_LOW_LATENCY_MS;
        u32ThresholdMs   = TRACK_RESUME_THRESHOLD_RENDER_MS;
        stTrackAttr.u32StartThresholdMs = TRACK_BUF_LOWLATENCY_STARTTHRESHOLD;
        stTrackAttr.u32BufLevelMs = TRACK_BUF_LOWLATENCY_MS;
    }
    else
    {
        stTrackAttr.u32StartThresholdMs = TRACK_BUF_STARTTHRESHOLD;
        stTrackAttr.u32BufLevelMs = TRACK_BUF_MS;
    }

    s32Ret = SinkSetTrackOutLatency(u32AopLatencyMs, u32FIFOLatencyMs, u32ThresholdMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SinkSetTrackOutLatency, s32Ret);
        return s32Ret;
    }

    s32Ret = HI_MPI_RENDER_SetTrackAttr(g_pstSinkManager->hSinkTrack, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_RENDER_SetTrackAttr, s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32  Sink_Init(RENDER_MANAGER_S* pstRender)
{
    HI_S32 s32Ret;
    HI_PHYS_ADDR_T tPhyAddr = 0;
    HI_VIRT_ADDR_T tVirAddr = 0;

    g_pstSinkManager = (SINK_MANAGER_S*)malloc(sizeof(SINK_MANAGER_S));
    if (HI_NULL == g_pstSinkManager)
    {
        HI_ERR_AO("Sink manager malloc failed!\n");
        return HI_FAILURE;
    }

    memset(g_pstSinkManager, 0, sizeof(SINK_MANAGER_S));

    g_pstSinkManager->pstEngineManager = pstRender->pstEngineManger;
    g_pstSinkManager->pstSourceManager = pstRender->pstSourceManager;

    s32Ret = SinkCreate();
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SinkCreate, s32Ret);
        free(g_pstSinkManager);
        g_pstSinkManager = HI_NULL;
        return s32Ret;
    }

    s32Ret = HI_MPI_AO_GetTrackDelayPhy(g_pstSinkManager->hSinkTrack, (HI_VOID*)(&tPhyAddr), (HI_VOID*)(&tVirAddr));
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_GetTrackDelayPhy, s32Ret);
        (HI_VOID)SinkDestory();
        free(g_pstSinkManager);
        g_pstSinkManager = HI_NULL;
        return s32Ret;
    }

    g_pstSinkManager->pstEngineManager->stDelayMapAttr.u32PhyAddr = (HI_U32)tPhyAddr;
#ifdef HI_AUDIO_DSP_SUPPORT
    s32Ret = SinkMmap(&(g_pstSinkManager->pstEngineManager->stDelayMapAttr));
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SinkMmap, s32Ret);
        return s32Ret;
    }
#else
    g_pstSinkManager->pstEngineManager->stDelayMapAttr.pVirAddr =
        HI_MPI_MMZ_Map((HI_U32)tPhyAddr, HI_FALSE);
    if (HI_NULL == g_pstSinkManager->pstEngineManager->stDelayMapAttr.pVirAddr)
    {
        HI_LOG_PrintFuncErr(HI_MPI_MMZ_Map, s32Ret);
        return HI_FAILURE;
    }
#endif


    g_pstSinkManager->bTrackFadeEnable = HI_TRUE;

    return s32Ret;
}

HI_S32  Sink_Deinit(HI_VOID)
{
    HI_S32 s32Ret;
    HI_VOID* pDelayMsVirAddr = (HI_VOID*)(g_pstSinkManager->pstEngineManager->stDelayMapAttr.pVirAddr);

    if (HI_NULL != pDelayMsVirAddr)
    {
#ifdef HI_AUDIO_DSP_SUPPORT
        SinkUnmap(&(g_pstSinkManager->pstEngineManager->stDelayMapAttr));
#else
        HI_MPI_MMZ_Unmap(g_pstSinkManager->pstEngineManager->stDelayMapAttr.u32PhyAddr);
#endif
    }

    s32Ret = SinkDestory();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("call SinkDestory failed(0x%x)\n", s32Ret);
    }

    if (HI_NULL != g_pstSinkManager)
    {
        free(g_pstSinkManager);
        g_pstSinkManager = HI_NULL;
    }

    return s32Ret;
}

static HI_VOID SinkUpdate(HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_U32 u32TrackDelayMs;
    HI_U32 u32StaticDelay;
    HI_U32 u32CurPcmTotalDelay;
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource = HI_NULL;

    for(enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_EXTDEC; enSourceID++)
    {
        if (SOURCE_ID_ASSOC == enSourceID)
        {
            continue;
        }

        SOURCE_INST2_LOCK(enSourceID);

        pstSource = g_pstSinkManager->pstSourceManager->pstSource[enSourceID];

        if (HI_NULL == pstSource)
        {
            SOURCE_INST2_UNLOCK(enSourceID);
            continue;
        }

        if (pstSource->bWorking && ((SOURCE_STATE_RUNNING == pstSource->enState) || (SOURCE_STATE_PAUSE == pstSource->enState)))
        {
            pstSource->u32DecoderPcmDelay = pstMS12DecodeStream->stOutput.u32PcmDelayMs[SOURCE_ID_MAIN];

            pstSource->u32SinkPts = pstSource->u32CurStreamPts;
            pstSource->bSinkStarted = HI_TRUE;
            HI_INFO_AO("Update Source(%d) SinkPts: %d -> %d\n", pstSource->enSourceID, pstSource->u32SinkPts, pstSource->u32CurStreamPts);
        }

        pstSource->u32AddMediaMixerMuteMs = pstMS12DecodeStream->stOutput.u32AddMediaMixerMuteMs;

        if (pstSource->u32AddMediaMixerMuteMs > 32)
        {
            pstSource->u32AddMediaMixerMuteMs -= 32;
        }
        else
        {
            pstSource->u32AddMediaMixerMuteMs = 0;
        }

        pstMS12DecodeStream->stOutput.u32AddMediaMixerMuteMs = pstSource->u32AddMediaMixerMuteMs;
        pstSource->u32DecoderPcmDelay = pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID];

        if (SOURCE_STATE_RUNNING == pstSource->enState)
        {
            pstSource->u32AddMediaPauseMuteMs = 0;
            SOURCE_INST2_UNLOCK(enSourceID);
            continue;
        }

        if (SOURCE_STATE_PAUSE != pstSource->enState)
        {
            pstSource->u32AddMediaPauseMuteMs = 0;
            SOURCE_INST2_UNLOCK(enSourceID);
            continue;
        }

        u32TrackDelayMs = *((HI_U32*)g_pstSinkManager->pstEngineManager->stDelayMapAttr.pVirAddr) >> 16;
        u32StaticDelay = pstSource->u32DecoderStaticDelay;
        u32CurPcmTotalDelay = pstSource->u32DecoderPcmDelay + u32TrackDelayMs + u32StaticDelay;
        if (SOURCE_ID_MAIN  == enSourceID)
        {
            if (pstSource->u32SinkPts > (u32CurPcmTotalDelay + pstSource->u32PausePts))
            {
                pstSource->u32AddMediaPauseMuteMs = pstSource->u32SinkPts - u32CurPcmTotalDelay - pstSource->u32PausePts;
            }
            else
            {
                pstSource->u32AddMediaPauseMuteMs = 0;
            }
        }
        else
        {
            if (pstSource->u32PauseDelay > u32CurPcmTotalDelay)
            {
                pstSource->u32AddMediaPauseMuteMs = pstSource->u32PauseDelay - u32CurPcmTotalDelay;
            }
            else
            {
                pstSource->u32AddMediaPauseMuteMs = 0;
            }
        }

        HI_WARN_AO("enSourceID = %d\n", enSourceID);
        HI_WARN_AO("u32DecoderPcmDelay = %d, u32TrackDelayMs = %d, u32StaticDelay = %d, u32CurPcmTotalDelay = %d, u32PauseDelay = %d\n",
            pstSource->u32DecoderPcmDelay, u32TrackDelayMs, u32StaticDelay, u32CurPcmTotalDelay, pstSource->u32PauseDelay);

        HI_WARN_AO("pstSource->u32SinkPts = %d\n", pstSource->u32SinkPts);
        HI_WARN_AO("u32AddMediaPauseMuteMs = %d, Cur pts = %d\n", pstSource->u32AddMediaPauseMuteMs, pstSource->u32SinkPts - u32CurPcmTotalDelay - pstSource->u32AddMediaPauseMuteMs);
        HI_WARN_AO("u32AddMediaMixerMuteMs = %d\n", pstSource->u32AddMediaMixerMuteMs);
        SOURCE_INST2_UNLOCK(enSourceID);
    }
}

HI_S32 Sink_SendData(HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_S32 s32Ret;
    AO_TRACK_FADE_S stTrackFade = {0};
    HI_UNF_AO_FRAMEINFO_S stAOFrame;
    HI_HADECODE_OUTPUT_S* pstPackOut = pstMS12DecodeStream->stOutput.pstOutput;
    struct timespec stSlpTm;

    CHANNEL_TRACE();

    HI_INFO_AO("AtmosOutActive new:%d old:%d\n", pstMS12DecodeStream->stOutput.bAtmosOutActive, g_pstSinkManager->bOutputAtmosEnable);

    if (pstMS12DecodeStream->stOutput.bAtmosOutActive != g_pstSinkManager->bOutputAtmosEnable)
    {
        g_pstSinkManager->bOutputAtmosEnable = pstMS12DecodeStream->stOutput.bAtmosOutActive;
        SinkEnableTrackOutputAtmos(g_pstSinkManager->bOutputAtmosEnable);
    }

    if (0 == pstPackOut->u32PcmOutSamplesPerFrame)
    {
        SINK_LOCK();
        SinkUpdate(pstMS12DecodeStream);
        SINK_UNLOCK();

        return HI_SUCCESS;
    }

    SINK_LOCK();

    if (USECASE_LOW_LATENCY == g_pstSinkManager->pstEngineManager->enUseCase)
    {
        stTrackFade.bEnable = (0 != pstMS12DecodeStream->stOutput.u32OutFrameMs[SOURCE_ID_OTTSOUND]) ? HI_FALSE : HI_TRUE;
    }
    else
    {
        if (0 != pstMS12DecodeStream->stOutput.u32OutFrameMs[SOURCE_ID_APP] ||
            0 != pstMS12DecodeStream->stOutput.u32OutFrameMs[SOURCE_ID_OTTSOUND])
        {
            stTrackFade.bEnable = HI_FALSE;
        }
        else
        {
            stTrackFade.bEnable = HI_TRUE;
        }
    }

    SINK_UNLOCK();

    if (g_pstSinkManager->bTrackFadeEnable != stTrackFade.bEnable)
    {
        HI_WARN_AO("Call HI_MPI_AO_Track_SetFadeAttr enalbe:%d\n", stTrackFade.bEnable);
        s32Ret = HI_MPI_AO_Track_SetFadeAttr(g_pstSinkManager->hSinkTrack, &stTrackFade);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(HI_MPI_AO_Track_SetFadeAttr, s32Ret);
        }

        g_pstSinkManager->bTrackFadeEnable = stTrackFade.bEnable;
    }

    HI_WARN_AO("PcmOutSamplesPerFrame is %d, BitsOutBytesPerFrame=0x%x\n", pstPackOut->u32PcmOutSamplesPerFrame, pstPackOut->u32BitsOutBytesPerFrame);

    SinkBuildFrame(pstPackOut, &stAOFrame);

    HI_INFO_AO("Track_SendData in\n");

    while (1)
    {
        SINK_LOCK();

        s32Ret = HI_MPI_AO_Track_SendData(g_pstSinkManager->hSinkTrack, &stAOFrame);
        if (HI_ERR_AO_OUT_BUF_FULL == s32Ret)
        {
            SINK_UNLOCK();
            stSlpTm.tv_sec = 0;
            stSlpTm.tv_nsec = OUTPUT_TRACK_SLEEP_MS * 1000;
            if(0 != nanosleep(&stSlpTm, NULL))
            {
                HI_ERR_AO("nanosleep err.\n");
            }
            continue;
        }
        else
        {
            SinkUpdate(pstMS12DecodeStream);
            SINK_UNLOCK();
            break;
        }
    }

    HI_INFO_AO("Track_SendData out\n");

    return s32Ret;
}

HI_S32 Sink_GetPreDecoderPts(SOURCE_S* pstSource, HI_U32* pu32Pts)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32DelayMs = 0;

    CHANNEL_TRACE();

    SINK_LOCK();

    if (HI_TRUE == pstSource->bSinkStarted)
    {
        SINK_UNLOCK();
        return HI_FAILURE;
    }

    if (g_pstSinkManager)
    {
        s32Ret = HI_MPI_AO_Track_GetDelayMs(g_pstSinkManager->hSinkTrack, &u32DelayMs);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("call HI_MPI_AO_Track_GetDelayMs failed(0x%x)\n", s32Ret);
        }
    }

    *pu32Pts = (pstSource->u32PreDecodePts > (u32DelayMs + pstSource->u32DecoderStaticDelay)) ?
               (pstSource->u32PreDecodePts - (u32DelayMs + pstSource->u32DecoderStaticDelay)) : 0;

    PTS_PRINTF("Source(%d) PreDecode Pts:%d PreDec:%d Track/Static DelayMS:%d/%d\n",
               pstSource->enSourceID, *pu32Pts, pstSource->u32PreDecodePts, u32DelayMs, pstSource->u32DecoderStaticDelay);

    SINK_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 Sink_GetTrackDelayMs(HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret = HI_SUCCESS;

    CHANNEL_TRACE();

    *pu32DelayMs = 0;

    if (g_pstSinkManager)
    {
        SINK_LOCK();

        s32Ret = HI_MPI_AO_Track_GetDelayMs(g_pstSinkManager->hSinkTrack, pu32DelayMs);
        if (HI_SUCCESS != s32Ret)
        {
            SINK_UNLOCK();
            HI_ERR_AO("call HI_MPI_AO_Track_GetDelayMs failed(0x%x)\n", s32Ret);
            return s32Ret;
        }

        SINK_UNLOCK();
        HI_WARN_AO("drv Track_GetDelayMs(%d)\n", *pu32DelayMs);
    }
    return HI_SUCCESS;
}

HI_S32 Sink_GetDelayMs(HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret = HI_SUCCESS;

    CHANNEL_TRACE();

    *pu32DelayMs = 0;

    if (g_pstSinkManager)
    {
        SINK_LOCK();

        s32Ret = HI_MPI_AO_Track_GetDelayMs(g_pstSinkManager->hSinkTrack, pu32DelayMs);
        if (HI_SUCCESS != s32Ret)
        {
            SINK_UNLOCK();
            HI_LOG_PrintFuncErr(HI_MPI_AO_Track_GetDelayMs, s32Ret);
            return s32Ret;
        }

        if (HI_TRUE == g_pstSinkManager->bFifoValid)
        {
            *pu32DelayMs += FIFO_BLOCK_MS;
        }

        SINK_UNLOCK();

        HI_WARN_AO("drv Track_GetDelayMs(%d)\n", *pu32DelayMs);
    }

    return HI_SUCCESS;
}

HI_S32 Sink_GetSyncDelayMs(SOURCE_S* pstSource, HI_U32* pu32Pts, HI_U32* pu32OrgPtsMs)
{
    CHANNEL_TRACE();

    if (g_pstSinkManager)
    {
        HI_S32 s32Ret = HI_SUCCESS;
        HI_U32 u32PreDecodePts = 0;
        SINK_LOCK();

        s32Ret = HI_MPI_AO_Track_GetDelayMs(g_pstSinkManager->hSinkTrack, &pstSource->u32DelayMs);
        if (HI_SUCCESS != s32Ret)
        {
            SINK_UNLOCK();
            HI_LOG_PrintFuncErr(HI_MPI_AO_Track_GetDelayMs, s32Ret);
            return s32Ret;
        }

        *pu32OrgPtsMs = pstSource->u32SinkPts;

        u32PreDecodePts = (pstSource->u32PreDecodePts > pstSource->u32ExtraTargetPtsMs) ?
                          (pstSource->u32PreDecodePts - pstSource->u32ExtraTargetPtsMs) : pstSource->u32PreDecodePts;

        *pu32Pts = (pstSource->u32SinkPts > (pstSource->u32DelayMs + pstSource->u32DecoderStaticDelay + pstSource->u32DecoderPcmDelay + pstSource->u32AddMediaPauseMuteMs +u32PreDecodePts)) ?
                   (pstSource->u32SinkPts - (pstSource->u32DelayMs + pstSource->u32DecoderStaticDelay + pstSource->u32DecoderPcmDelay + pstSource->u32AddMediaPauseMuteMs)) : u32PreDecodePts;

        pstSource->u32PausePts = *pu32Pts;

        SINK_UNLOCK();

        //for pts trace avoid async case
        HI_WARN_AO("Source(%d) Pts:%d (SinkPts:%d TrackDelayMs:%d DecStaticDelay:%d DecPcmDelay:%d CurPts:%d PreDecodePts:%d RealPrePts:%d ExtraMs:%d)\n",
                   pstSource->enSourceID, *pu32Pts, pstSource->u32SinkPts, pstSource->u32DelayMs, pstSource->u32DecoderStaticDelay, pstSource->u32DecoderPcmDelay,
                   pstSource->u32CurStreamPts, pstSource->u32PreDecodePts, u32PreDecodePts, pstSource->u32ExtraTargetPtsMs);
    }

    return HI_SUCCESS;
}

HI_S32 Sink_SetFifoBufValid(HI_BOOL bValid)
{
    CHANNEL_TRACE();

    if (g_pstSinkManager)
    {
        g_pstSinkManager->bFifoValid = bValid;
    }

    return HI_SUCCESS;
}

HI_S32 Sink_SetContinueOutputStatus(HI_BOOL bEnable)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Sink_SetContinueOutputStatus %d\n", bEnable);

    if ((HI_FALSE == g_pstSinkManager->bContinuousOutputEnable) && (HI_TRUE == bEnable))
    {
        s32Ret = SinkEnableTrackContinueOutput(HI_TRUE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(SinkEnableTrackContinueOutput, s32Ret);
            return s32Ret;
        }

        HI_WARN_AO("Aplly SinkAddMuteData\n");

        s32Ret = SinkAddMuteData();
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(SinkAddMuteData, s32Ret);
            // not return
        }
    }

    if ((HI_TRUE == g_pstSinkManager->bContinuousOutputEnable) && (HI_FALSE == bEnable))
    {
        s32Ret = SinkEnableTrackContinueOutput(HI_FALSE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(SinkEnableTrackContinueOutput, s32Ret);
            return s32Ret;
        }
    }

    g_pstSinkManager->bContinuousOutputEnable = bEnable;

    return HI_SUCCESS;
}

HI_S32 Sink_SetOutputLatencyMode(HI_UNF_SND_OUTPUTLATENCY_E enMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (enMode >= HI_UNF_SND_OUTPUTLATENCY_BUTT)
    {
        HI_ERR_AO("Invalid enOutputMode(%d)!\n", enMode);
        return HI_ERR_AO_INVALID_PARA;
    }

    HI_WARN_AO("Sink_SetOutputLatencyMode %d\n", enMode);

    if ((HI_UNF_SND_OUTPUTLATENCY_NORMAL != g_pstSinkManager->enOutLatencyMode) && (HI_UNF_SND_OUTPUTLATENCY_NORMAL == enMode))
    {
        s32Ret = SinkSetTrackAttr(HI_FALSE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(SinkSetTrackAttr, s32Ret);
            return s32Ret;
        }
    }

    if ((HI_UNF_SND_OUTPUTLATENCY_LOW != g_pstSinkManager->enOutLatencyMode) && (HI_UNF_SND_OUTPUTLATENCY_LOW == enMode))
    {
        s32Ret = SinkSetTrackAttr(HI_TRUE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(SinkSetTrackAttr, s32Ret);
            return s32Ret;
        }
    }

    g_pstSinkManager->enOutLatencyMode = enMode;

    return HI_SUCCESS;
}

HI_S32 Sink_UpdateRenderParam(AO_RENDER_ATTR_S* pstRenderParam)
{
    HI_S32 s32Ret = HI_FAILURE;

    CHANNEL_TRACE();

    if (g_pstSinkManager)
    {
        s32Ret = HI_MPI_AO_SND_GetRenderParam(HI_UNF_SND_0, pstRenderParam);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(HI_MPI_AO_SND_GetRenderParam, s32Ret);
            return s32Ret;
        }

        HI_WARN_AO("GetRender passthru:%d Support:%d Cap:%d ConStatus:%d ConMode:%d\n", pstRenderParam->bPassthruBypass,
                   pstRenderParam->bSupport, pstRenderParam->u32Capability, pstRenderParam->bContinueStatus, pstRenderParam->enOutputMode);
    }

    return s32Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
