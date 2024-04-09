#ifndef __CAPTION_SUBT_OUTPUT_H__
#define __CAPTION_SUBT_OUTPUT_H__

#include  "hi_unf_so.h"

#ifdef __cplusplus
extern "C"{
#endif

HI_S32 caption_subt_output_init(HI_HANDLE* phOut);
HI_S32 caption_subt_output_deinit(HI_HANDLE hOut);

HI_S32 caption_subt_output_create_surface(HI_RECT_S stRect);
HI_S32 caption_subt_output_destory_surface();

HI_S32 caption_subt_output_draw(HI_U32 u32UserData, const HI_UNF_SO_SUBTITLE_INFO_S *pstInfo, HI_VOID *pArg);
HI_S32 caption_subt_output_clear(HI_U32 u32UserData, HI_VOID *pArg);

#ifdef __cplusplus
}
#endif

#endif
