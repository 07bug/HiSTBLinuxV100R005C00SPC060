#ifndef __VPSS_ALG_BUF_H__
#define __VPSS_ALG_BUF_H__

#include "hi_type.h"
#include "vpss_common.h"
#include "hi_drv_vpss.h"
#include "vpss_osal.h"
#include "hi_drv_mmz.h"
#include "vpss_wbc.h"
#include "vpss_stt_mcdei.h"
#include "vpss_sttinf.h"
#include "hi_drv_video.h"
#include "vpss_wbc_mcdei.h"
#define VPSS_ALGBUF_DEG 0
#define VPSS_INSTANCE_ALGFIXSIZE_NUM 2 //申请算法SMMU个数
#define VPSS_ALG_INSTANCEID_CHECK(id, type) {\
        if (id >= VPSS_INSTANCE_ALGFIXSIZE_NUM) {\
            VPSS_FATAL("Invalid instanceid:%d algtype:%d\n", id, type);\
            return HI_FAILURE;}\
    }
#define WBC_BUFF_SIZE (12444*1024UL)
#define STTRGME_BUFF_SIZE (132*1024UL)
#define STTPRJH_BUFF_SIZE (1956*1024UL)
#define STTPRJV_BUFF_SIZE (492*1024UL)
#define BLEND_WBC_BUFF_SIZE (6224*1024UL)
#define RGME_WBC_BUFF_SIZE (5168*1024UL)
#define STTBLKMV_BUFF_SIZE (684*1024UL)
#ifdef VPSS_SUPPORT_BLKMT
#define STTBLKMT_BUFF_SIZE (200*1024UL)
#endif
#ifdef VPSS_SUPPORT_DICNT
#define STTDICNT_BUFF_SIZE (600*1024UL)
#endif
#define STTDIE_BUFF_SIZE (2040*1024UL)
#define STTNR_BUFF_SIZE (6800*1024UL)
#define STTWBC_BUFF_SIZE (160*1024UL)

typedef enum hiVPSS_ALG_BUF_TYPE_E
{
    VPSS_ALG_WBC = 0,
    VPSS_ALG_STTRGME,
    VPSS_ALG_STTPRJH,
    VPSS_ALG_STTPRJV,
    VPSS_ALG_BLEND_WBC,
    VPSS_ALG_RGME_WBC,
    VPSS_ALG_STTBLKMV,
#ifdef VPSS_SUPPORT_BLKMT
    VPSS_ALG_STTBLKMT,
#endif
#ifdef VPSS_SUPPORT_DICNT
    VPSS_ALG_STTDICNT,
#endif
    VPSS_ALG_STTDIE,
    VPSS_ALG_STTNR,
    VPSS_ALG_STTWBC,
    VPSS_ALG_BUTT
} VPSS_ALG_BUF_TYPE_E;


typedef struct hiALG_MEM_NODE
{
    VPSS_ALG_BUF_TYPE_E enType;
    HI_U32 u32MemSize;
    HI_U32 u32MemOffset;
    SMMU_BUFFER_S stMMUBuf;
    HI_BOOL bInUse;
    HI_BOOL bNeedMap;  //在初始化的时候，来区分哪些mem需要初始化，需要初始化的，把虚拟地址初始化为0
} ALG_MEM_NODE;

typedef struct hiVPSS_ALG_BUF
{
    ALG_MEM_NODE stMemPool[VPSS_ALG_BUTT];
    HI_U32 u32Index;
    HI_U32 u32TotalUseCount;
    HI_U32 u32TotalSize;
    SMMU_BUFFER_S stMMUBuf;
} VPSS_ALG_BUF;

HI_S32 VPSS_AlgBuf_Init (VPSS_ALG_BUF *pstBuf, HI_U32 u32Index);
#if defined(ALGBUF_MANAGE_MODE1)
extern VPSS_ALG_BUF g_VpssAlgBuf;
HI_S32 VPSS_AlgBuf_Malloc(VPSS_ALG_BUF *pstBuf, VPSS_ALG_BUF_TYPE_E enAlgType,
                          HI_CHAR *pAlgName, HI_U32 u32SizeNeed, HI_U32 u32Align, SMMU_BUFFER_S *pSmmuBuf);
HI_S32 VPSS_AlgBuf_Free(VPSS_ALG_BUF *pstBuf, SMMU_BUFFER_S *pstMMUBuf,
                        VPSS_ALG_BUF_TYPE_E enAlgType);
HI_VOID VPSS_AlgBuf_Print1(VPSS_ALG_BUF *pstBuf);
#elif defined(ALGBUF_MANAGE_MODE2)
extern VPSS_ALG_BUF g_VpssAlgBuf[];
HI_S32 VPSS_AlgBuf_Free(VPSS_ALG_BUF *pstBuf);
HI_S32 VPSS_AlgBuf_Malloc(VPSS_ALG_BUF *pstBuf);
HI_S32 VPSS_AlgBuf_Rel(VPSS_ALG_BUF *pstBuf, SMMU_BUFFER_S *pstMMUBuf, VPSS_ALG_BUF_TYPE_E enAlgType);
HI_S32 VPSS_AlgBuf_Get(VPSS_ALG_BUF *pstBuf, VPSS_ALG_BUF_TYPE_E enAlgType, HI_CHAR *pAlgName,
                       HI_U32 u32SizeNeed, HI_U32 u32Align, SMMU_BUFFER_S *pSmmuBuf);
HI_VOID VPSS_AlgBuf_Print1(VPSS_ALG_BUF *pstBuf);
#endif
#endif
