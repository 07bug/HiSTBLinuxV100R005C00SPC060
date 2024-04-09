#ifndef __VDEC_PRODUCT_H__
#define __VDEC_PRODUCT_H__

#include "vfmw.h"
#include "vdm_hal.h"

#define PDT_OK   0
#define PDT_ERR  -1

typedef struct
{
    VBOOL  AndroidTest;
    SINT32 Width;
    SINT32 Height;
    VID_STD_E eVidStd;
    VDEC_CHAN_CAP_LEVEL_E eCapLevel;
} PDT_OCCUPIED_S;

typedef enum
{
    ATTR_VDEC_CAP,
    ATTR_OUT_FMT,
    ATTR_OCCUPIED_NUM,
    ATTR_IS_SOFT_DEC,
    ATTR_BUTT,
} ATTR_ID;

SINT32 PDT_GetAttribute(ATTR_ID eAttrID, VOID *pArgs);
SINT32 PDT_Init(VDMHAL_FUN_PTR_S *pFuncPtr);
SINT32 PDT_Deinit(VOID);

#endif

