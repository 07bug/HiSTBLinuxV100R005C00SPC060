#ifndef __XDP_DRV_IP_MMU_H__
#define __XDP_DRV_IP_MMU_H__

#include "vdp_define.h"

typedef enum
{
    XDP_MMU_INT_MODE_RD_INVLD = 0 ,
    XDP_MMU_INT_MODE_WR_INVLD     ,
    XDP_MMU_INT_MODE_PRE_ERR      ,
    XDP_MMU_INT_MODE_PAGE_MISS    ,
    XDP_MMU_INT_MODE_BUTT
} XDP_MMU_INT_MODE_E;

typedef enum
{
    XDP_MMU_SECURE_MODE_SAFE = 0,
    XDP_MMU_SECURE_MODE_UNSAFE ,
    XDP_MMU_SECURE_MODE_BUTT
} XDP_MMU_MODE_E;

typedef struct
{
    HI_U64 u64PageAddr  ;
    HI_U64 u64RdErrAddr ;
    HI_U64 u64WrErrAddr ;
} XDP_MMU_ADDR_S;

typedef struct
{
    HI_BOOL bIntMsk[XDP_MMU_INT_MODE_BUTT];
    HI_BOOL bClrInt[XDP_MMU_INT_MODE_BUTT];
} XDP_MMU_INT_S;

typedef struct
{
    HI_BOOL bSmmuEn;
    HI_BOOL bCkGtEn;
    HI_BOOL bIntEn ;
    HI_U32  u32PtwOutstd;
    XDP_MMU_ADDR_S stAddr[XDP_MMU_SECURE_MODE_BUTT];
    XDP_MMU_INT_S  stInt [XDP_MMU_SECURE_MODE_BUTT];
} XDP_MMU_CFG_S;

#endif

