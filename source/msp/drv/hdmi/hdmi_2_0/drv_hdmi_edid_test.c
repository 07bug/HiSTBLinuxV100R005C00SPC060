/******************************************************************************

  Copyright (C), 2014-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_hdmi_edid_test.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2014/12/10
  Description   :
  History       :
  Date          : 2014/12/10
  Author        : sdk
  Modification  :
*******************************************************************************/
#include "drv_hdmi_common.h"
#include "drv_hdmi_platform.h"
#include "drv_hdmi_edid_test.h"

#if HDMI_EDID_RAW_TEST


/**
\   sony hdmi2.0
*/
static HI_U8 s_g_au8EdidRawTest0[] =
{
    0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x4d, 0xd9, 0x03, 0x42, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x18, 0x01, 0x03, 0x80, 0x7a, 0x44, 0x78, 0x0a, 0x0d, 0xc9, 0xa0, 0x57, 0x47, 0x98, 0x27,
    0x12, 0x48, 0x4c, 0x21, 0x08, 0x00, 0x81, 0x80, 0xa9, 0xc0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3a, 0x80, 0x18, 0x71, 0x38, 0x2d, 0x40, 0x58, 0x2c,
    0x45, 0x00, 0xc2, 0xad, 0x42, 0x00, 0x00, 0x1e, 0x01, 0x1d, 0x00, 0x72, 0x51, 0xd0, 0x1e, 0x20,
    0x6e, 0x28, 0x55, 0x00, 0xc2, 0xad, 0x42, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x53,
    0x4f, 0x4e, 0x59, 0x20, 0x54, 0x56, 0x20, 0x20, 0x2a, 0x30, 0x37, 0x0a, 0x00, 0x00, 0x00, 0xfd,
    0x00, 0x30, 0x3e, 0x0e, 0x46, 0x0f, 0x00, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0xf4,
};

typedef struct{
    HI_U8       *pu8Addr;
    HI_S32      s32Size;
}EDID_TEST_RAW_S;

static EDID_TEST_RAW_S s_g_stEdidTestTable[] = {
        { s_g_au8EdidRawTest0,  sizeof(s_g_au8EdidRawTest0)  },
        {NULL,0}
};

#define EDID_TEST_TABLE_SIZE (sizeof(s_g_stEdidTestTable)/sizeof(s_g_stEdidTestTable[0]))

HI_S32 DRV_HDMI_EdidTestRawRead(HDMI_EDID_UPDATE_MODE_E enMode,
                                            HI_U8 *pau8Data,
                                            HI_U32 u32Len)
{
    EDID_TEST_RAW_S *pstEdidTest = HI_NULL;

    if (   ( HDMI_EDID_UPDATE_TEST0 > enMode )
        || ( HDMI_EDID_UPDATE_BUTT <= enMode )
        || ( EDID_TEST_TABLE_SIZE  < (enMode-HDMI_EDID_UPDATE_TEST0))
        || (HI_NULL == pau8Data)
        || (u32Len > HDMI_EDID_TOTAL_SIZE)    )
    {
        return HI_FAILURE;
    }

    pstEdidTest = &s_g_stEdidTestTable[enMode-HDMI_EDID_UPDATE_TEST0] ;

    HDMI_MEMCPY(pau8Data,pstEdidTest->pu8Addr,pstEdidTest->s32Size);
    return pstEdidTest->s32Size;
}


#endif /* HDMI_EDID_RAW_TEST */

