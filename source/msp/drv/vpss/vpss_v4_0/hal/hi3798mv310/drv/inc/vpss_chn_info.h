#ifndef __VDP_CHN_INFO_H__
#define __VDP_CHN_INFO_H__

#include "vpss_define.h"
#include "xdp_sti.h"

typedef struct
{
    HI_U32 u32Width         ;
    HI_U32 u32Height        ;
    HI_U32 u32Datawidth     ;
    HI_U32 u32Pro           ;
    HI_U32 u32Fmt           ;
    HI_S32 s32YConstValue   ;
    HI_S32 s32YSt           ;
    HI_S32 s32YStep         ;
    HI_S32 s32YMin          ;
    HI_S32 s32YMax          ;
    HI_S32 s32CConstValue   ;
    HI_S32 s32CSt           ;
    HI_S32 s32CStep         ;
    HI_S32 s32CMin          ;
    HI_S32 s32CMax          ;
    STI_GENMODE_E enGenMode ;
    char *pchFileName      ;
    HI_U32 u32YValid        ;
    HI_U32 u32CValid        ;
    HI_U32 u32YRdyNeedMin   ;
    HI_U32 u32YRdyNeedMax   ;
    HI_U32 u32YNoRdyNeedMin ;
    HI_U32 u32YNoRdyNeedMax ;
    HI_U32 u32CRdyNeedMin   ;
    HI_U32 u32CRdyNeedMax   ;
    HI_U32 u32CNoRdyNeedMin ;
    HI_U32 u32CNoRdyNeedMax ;
} U_COLOR_CHN_INFO_S;

typedef struct
{
    HI_U32 u32Width         ;
    HI_U32 u32Height        ;
    HI_U32 u32Datawidth     ;
    HI_U32 u32Pro           ;
    HI_U32 u32Fmt           ;
    HI_S32 s32ConstValue   ;
    HI_S32 s32St           ;
    HI_S32 s32Step         ;
    HI_S32 s32Min          ;
    HI_S32 s32Max          ;
    STI_GENMODE_E enGenMode ;
    char *pchFileName      ;
    HI_U32 u32Valid        ;
    HI_U32 u32RdyNeedMin   ;
    HI_U32 u32RdyNeedMax   ;
    HI_U32 u32NoRdyNeedMin ;
    HI_U32 u32NoRdyNeedMax ;
} U_SOLO_CHN_INFO_S;

#endif



