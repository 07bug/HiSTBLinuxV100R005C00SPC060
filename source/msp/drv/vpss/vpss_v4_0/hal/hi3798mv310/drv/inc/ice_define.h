#ifndef __ICE_DEFINE_H__
#define __ICE_DEFINE_H__

#include "hi_type.h"

typedef enum
{
    ICE_BIT_DEPTH_8  = 0,
    ICE_BIT_DEPTH_10 = 1,
    ICE_BIT_DEPTH_12 = 2,
    ICE_BIT_DEPTH_14 = 3,
    ICE_BIT_DEPTH_BUTT
} ICE_BIT_DEPTH_E;

typedef enum
{
    ICE_REG_CFG_MODE_TYP    = 0 ,
    ICE_REG_CFG_MODE_RAND   = 1 ,
    ICE_REG_CFG_MODE_MAX    = 2 ,
    ICE_REG_CFG_MODE_MIN    = 3 ,
    ICE_REG_CFG_MODE_MINMAX = 4 ,
    ICE_REG_CFG_MODE_MANUAL = 5 ,
    ICE_REG_CFG_MODE_BUTT
} ICE_REG_CFG_MODE_E;

typedef enum
{
    ICE_DATA_FMT_YUV422  = 0,
    ICE_DATA_FMT_YUV420  = 1,
    ICE_DATA_FMT_YUV444  = 2,
    ICE_DATA_FMT_YUV400  = 3,
    ICE_DATA_FMT_BUTT

} ICE_DATA_FMT_E;

typedef enum
{
    ICE_DATA_TYPE_ARGB8888  = 0,
    ICE_DATA_TYPE_RGB888  = 1,
    ICE_DATA_TYPE_BUTT

} ICE_DATA_TYPE_E;

typedef enum
{
    ICE_BAYER_FMT_GRBG  = 0,
    ICE_BAYER_FMT_GBRG  = 1,
    ICE_BAYER_FMT_RGGB  = 2,
    ICE_BAYER_FMT_BGGR  = 3,
    ICE_BAYER_FMT_BUTT

} ICE_BAYER_FMT_E;

typedef enum
{
    ICE_ERROR_TYPE_NORMAL = 0,
    ICE_ERROR_TYPE_HEAD_ZERO,
    ICE_ERROR_TYPE_HEAD_RAND,
    ICE_ERROR_TYPE_HEAD_MAX ,
    ICE_ERROR_TYPE_DATA_ZERO,
    ICE_ERROR_TYPE_DATA_RAND,
    ICE_ERROR_TYPE_DATA_MAX ,
    ICE_ERROR_TYPE_FRAMESIZE_MAX ,
    ICE_ERROR_TYPE_FRAMESIZE_RAND,
    ICE_ERROR_TYPE_FRAMESIZE_ZERO,
    ICE_ERROR_TYPE_BUTT

} ICE_ERROR_TYPE_E;

typedef struct
{
    HI_BOOL bEn;
    HI_U32  u32StartPos ;
    HI_U32  u32EndPos   ;
    HI_U32  u32StartPosC;
    HI_U32  u32EndPosC  ;
} ICE_FRM_PART_MODE_S;

typedef struct
{
    HI_BOOL bEn;
    HI_U32  u32Index ;
} ICE_FRM_SLICE_MODE_S;

typedef struct
{
    /* input */
    HI_U32   enLayer                ;
    HI_U32   u32FrameWth            ;
    HI_U32   u32FrameHgt            ;
    HI_U32   u32TileHgt             ;
    HI_U32   u32CmpRatio            ;
    HI_BOOL  bIsLossy               ;
    HI_BOOL  bChmProcEn             ;
    HI_BOOL  bEslEn                 ;
    HI_BOOL  bBorderRawEn           ;
    ICE_BIT_DEPTH_E    enBitDepth   ;
    ICE_DATA_FMT_E     enDataFmt    ;
    ICE_BAYER_FMT_E    enBayerFmt   ;
    ICE_REG_CFG_MODE_E enCmpCfgMode ;
    /* file name */
    HI_S8 cCmpInfo[80]              ;
    HI_BOOL bLoadDdrMode            ;
    char **cCmpFileName            ;
    /* output */
    HI_U32 *u32CmpSize;
    /* debug */
    ICE_ERROR_TYPE_E enErrType  ;
} CMP_SEG_INFO_S;

typedef enum
{
    OSD_CMP_MODE_TYP  = 0,
    OSD_CMP_MODE_RAND,
    OSD_CMP_MODE_BUTT
} OSD_CMP_MODE_E;

typedef struct
{
    /* input */
    HI_U32   enLayer            ;
    OSD_CMP_MODE_E enCmpCfgMode ;
    HI_U32 u32CmpRatio          ;
    HI_BOOL bLoadDdrMode        ;
    /* file name */
    char   *cCmpInfo            ;
    HI_S8 cCmpDdrFile[4][80];
    char **cCmpFileName        ;
    char **cRegCfgFileName     ;
    /* output */
    HI_U32 *u32CmpSize         ;
    /* debug */
    ICE_ERROR_TYPE_E enErrType  ;
} CMP_FRM_INFO_S;

typedef struct
{
    HI_U32   enLayer                ;
    HI_U32   u32FrameWth            ;
    HI_U32   u32FrameHgt            ;
    HI_U32   u32TileHgt             ;
    HI_U32   u32CmpRatioY           ;
    HI_U32   u32CmpRatioC           ;
    HI_BOOL  bCmpEn                 ;
    HI_BOOL  bIsRawEn               ;
    HI_BOOL  bIsLossyY              ;
    HI_BOOL  bIsLossyC              ;
    HI_BOOL  bChmProcEn             ;
    HI_BOOL  bEslEn                 ;
    ICE_BIT_DEPTH_E    enBitDepth   ;
    ICE_DATA_FMT_E     enDataFmt    ;
    ICE_BAYER_FMT_E    enBayerFmt   ;
    ICE_REG_CFG_MODE_E enCmpCfgMode ;
    ICE_FRM_PART_MODE_S stPartModeCfg;
    ICE_FRM_SLICE_MODE_S stSliceModeCfg;
    /* file name */
    char **cCmpFileName            ;
    /* output */
    HI_U32 *u32CmpSize;
    /* debug */
    ICE_ERROR_TYPE_E enErrType  ;
} ICE_FRM_CFG_S;

typedef struct
{
    HI_U32   enLayer                ;
    HI_U32   u32FrameWth            ;
    HI_U32   u32FrameHgt            ;
    HI_U32   u32TileHgt             ;
    HI_U32   u32CmpRatioY           ;
    HI_U32   u32CmpRatioC           ;
    HI_BOOL  bCmpEn                 ;
    HI_BOOL  bIsRawEn               ;
    HI_BOOL  bIsLossyY              ;
    HI_BOOL  bIsLossyC              ;
    HI_BOOL  bChmProcEn             ;
    HI_BOOL  bEslEn                 ;
    HI_BOOL  bCscEn                 ;
    ICE_BIT_DEPTH_E    enBitDepth   ;
    ICE_DATA_FMT_E     enDataFmt    ;
    ICE_DATA_TYPE_E    enDataType   ;
    ICE_BAYER_FMT_E    enBayerFmt   ;
    ICE_REG_CFG_MODE_E enCmpCfgMode ;
    ICE_FRM_PART_MODE_S stPartModeCfg;
    /* file name */
    HI_S8 cCmpInfo[80]              ;
    char **cCmpFileName            ;
    /* output */
    HI_U32 *u32CmpSize;
    /* debug */
    ICE_ERROR_TYPE_E enErrType  ;
    HI_BOOL bLoadDdrMode        ;
    HI_S8 cCmpDdrFile[4][80];
} ICE_SEG_CFG_S;

#endif

