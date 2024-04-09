/*
 * Copyright:
 * ----------------------------------------------------------------------------
 * This confidential and proprietary software may be used only as authorized
 * by a licensing agreement from ARM Limited.
 *      (C) COPYRIGHT 2012-2014 ARM Limited, ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorized copies and
 * copies may only be made to the extent permitted by a licensing agreement
 * from ARM Limited.
 * ----------------------------------------------------------------------------
 */
#ifndef __AFBC_CONFIG_H__
#define __AFBC_CONFIG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct
{
    int     bitdepth;
    int     pix_format;
    int     frame_width;
    int     frame_height;
    int     cmp_mode;           // 0 --compress   1-- bypass raw
    int     yuv_transform_en;
    int     block_split;
    int     max_allowed_bctree;
} AFBC_CFG;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif
