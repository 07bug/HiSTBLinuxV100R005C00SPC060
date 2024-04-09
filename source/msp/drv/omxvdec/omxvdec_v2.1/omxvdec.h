/*
 * Copyright (c) (2014 - ...) Device Chipset Source Algorithm and Chipset Platform Development Dept
 * Hisilicon. All rights reserved.
 *
 * File:    omxvdec.h
 *
 * Purpose: omxvdec main entry header file
 *
 * Author:  sdk
 *
 * Date:    26, 11, 2014
 *
 */

#ifndef __OMXVDEC_H__
#define __OMXVDEC_H__

#include <linux/cdev.h>
#include "hi_drv_mmz.h"
#include "hi_drv_sys.h"
#include "hi_drv_proc.h"
#include "drv_omxvdec.h"
#include "omxvdec_mem.h"
#include "drv_vdec_ext.h"
#include "hi_drv_module.h"

#ifdef VFMW_VPSS_BYPASS_EN
#include "hi_kernel_adapt.h"
#endif

#define MAX_OPEN_COUNT                    (32)
#define MAX_CHANNEL_NUM                   (MAX_OPEN_COUNT)

#define OMX_ALWS                          (0xFFFFFFFF)
#define OMX_FATAL                         (0)
#define OMX_ERR                           (1)
#define OMX_WARN                          (2)
#define OMX_INFO                          (3)
#define OMX_TRACE                         (4)
#define OMX_INBUF                         (5)
#define OMX_OUTBUF                        (6)
#define OMX_VPSS                          (7)
#define OMX_VER                           (8)
#define OMX_PTS                           (9)

#define OMX_LOWDELAY_REC_NODE_NUM           10
#define OMX_LOWDELAY_REC_ITEM               9
#define OMX_LOWDELAY_REC_USERTAG            0
#define OMX_LOWDELAY_REC_NODE_STATE         1
#define OMX_LOWDELAY_REC_ETB_TIME           2
#define OMX_LOWDELAY_REC_VFMW_RCV_STRM_TIME 3
#define OMX_LOWDELAY_REC_VFMW_RLS_STRM_TIME 4
#define OMX_LOWDELAY_REC_VFMW_RPO_IMG_TIME  5
#define OMX_LOWDELAY_REC_VPSS_RCV_IMG_TIME  6
#define OMX_LOWDELAY_REC_VPSS_RPO_IMG_TIME  7
#define OMX_LOWDELAY_REC_TOTAL_USED_TIME    8
#define OMX_LOWDELAY_REC_NODE_FREE          0
#define OMX_LOWDELAY_REC_NODE_WRITED        1

extern HI_U32 g_TraceOption;

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define OmxPrint(flag, format,arg...) \
    do { \
        if (OMX_ALWS == flag || (0 != (g_TraceOption & (1 << flag)))) \
            printk("<OMXVDEC:%d> " format, __LINE__, ## arg); \
    } while (0)
#else
#define OmxPrint(flag, format,arg...)    ({do{}while(0);0;})
#endif


#define OMXVDEC_ASSERT_RETURN(cond, else_print)                        \
    do {                                                            \
        if( !(cond) )                                               \
        {                                                           \
            OmxPrint(OMX_ALWS, "ASSERT: %s at L%d:%s\n", __func__, __LINE__, else_print); \
            return HI_FAILURE;                                       \
        }                                                           \
    }while(0)

#define OMXVDEC_ASSERT_RETURN_NULL(cond, else_print)                        \
    do {                                                            \
        if( !(cond) )                                               \
        {                                                           \
            OmxPrint(OMX_ALWS, "ASSERT: %s at L%d:%s\n", __func__, __LINE__, else_print); \
            return;                                       \
        }                                                           \
    }while(0)

#ifdef VFMW_VPSS_BYPASS_EN
#define D_OMXVDEC_CHECK_PTR_RET(ptr) \
    do {\
        if (HI_NULL == ptr)\
        { \
            OmxPrint(OMX_ERR, "PTR '%s' is NULL.\n", # ptr); \
            return HI_FAILURE;           \
        }  \
    } while (0)

#define D_OMXVDEC_CHECK_PTR(ptr) \
    do {\
        if (HI_NULL == ptr)\
        { \
            OmxPrint(OMX_ERR, "PTR '%s' is NULL.\n", # ptr); \
            return;           \
        }  \
    } while (0)
#endif

typedef enum
{
    TASK_STATE_INVALID = 0,
    TASK_STATE_SLEEPING,
    TASK_STATE_ONCALL,
    TASK_STATE_RUNNING,
} eTASK_STATE;

typedef enum
{
    ALLOC_INVALID = 0,
    ALLOC_BY_MMZ,
    ALLOC_BY_MMZ_UNMAP,
    ALLOC_BY_PRE,
    ALLOC_BY_SEC,
} eMEM_ALLOC;

typedef enum
{
    SAVE_FLIE_RAW = 0,
    SAVE_FLIE_IMG,
} eSAVE_FLIE;

typedef struct
{
    HI_U32              open_count;
    HI_U32              total_chan_num;
    unsigned long       chan_bitmap;
    struct list_head    chan_list;
    spinlock_t          lock;
    spinlock_t          channel_lock;
    spinlock_t          stream_lock;
    struct cdev         cdev;
    struct device      *device;
} OMXVDEC_ENTRY;

typedef struct
{
    VOID      *pDecoderFunc;        /*decoder external functions*/
    VOID      *pProcessorFunc;      /*processor external functions*/
    VOID      *pVdecFunc;
} OMXVDEC_FUNC;

typedef struct
{
    HI_U32 usrtag_start_time;
    HI_U32 interval;
    HI_U32 current_tag;
    HI_U32 time_record[OMX_LOWDELAY_REC_NODE_NUM + 1][OMX_LOWDELAY_REC_ITEM];
    HI_U32 time_cost_sum;
    HI_U32 average_time_cost;
    HI_U32 rec_index;
} OMXVDEC_LOWDELAY_PROC_RECORD;


HI_VOID omxvdec_release_mem(HI_VOID *pMMZ_Buf, eMEM_ALLOC eMemAlloc);

UINT32 OMX_GetTimeInMs(VOID);

#endif
