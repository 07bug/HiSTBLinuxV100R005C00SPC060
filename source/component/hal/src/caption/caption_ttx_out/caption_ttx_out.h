#ifndef  __CAPTION_TELETEXT_OUT_H__
#define __CAPTION_TELETEXT_OUT_H__

#include  "hi_unf_ttx.h"

#ifdef __cplusplus
extern "C" {
#endif

HI_S32 caption_ttx_output_init(HI_HANDLE* phOut);
HI_S32 caption_ttx_output_deinit(HI_HANDLE hOut);

HI_S32 caption_ttx_output_create_surface(HI_RECT_S stRect);
HI_S32 caption_ttx_output_destory_surface();

HI_S32 caption_ttx_output_callbak(HI_HANDLE hTTX, HI_UNF_TTX_CB_E enCB, HI_VOID *pvCBParam);

#ifdef __cplusplus
}
#endif
#endif
