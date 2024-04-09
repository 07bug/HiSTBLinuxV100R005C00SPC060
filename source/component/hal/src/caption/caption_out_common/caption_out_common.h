#ifndef __CAPTION_OUTPUT_COMMON_H__
#define __CAPTION_OUTPUT_COMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_common.h"

#define HIGO_TRANSPARENT_COLOR_KEY          (0xF0EB68)

HI_S32 caption_output_init(HI_HANDLE* phOut);

HI_S32 caption_output_deinit();

HI_S32 caption_output_create_surface(HI_RECT_S stRect, HI_HANDLE* phSurface);

HI_S32 caption_output_destory_surface();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__HI_SVR_SUBTITLE_H__ */
