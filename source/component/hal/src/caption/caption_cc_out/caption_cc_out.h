#ifndef __CAPTION_CC_OUT_H__
#define __CAPTION_CC_OUT_H__

#include "hi_unf_cc.h"
#ifdef __cplusplus
extern "C"{
#endif

HI_S32 caption_cc_output_init(HI_HANDLE* phOut);
HI_S32 caption_cc_output_deinit(HI_HANDLE hOut);

HI_S32 caption_cc_output_create_surface(HI_RECT_S stRect);
HI_S32 caption_cc_output_destory_surface();

HI_S32 caption_cc_output_draw(HI_U32 u32UserData, HI_UNF_CC_DISPLAY_PARAM_S *pstDisplayParam);

HI_S32 caption_cc_output_get_textsize(HI_U32 u32Userdata, HI_U16 *u16Str, HI_S32 s32StrNum, HI_S32 *ps32Width, HI_S32 *ps32Heigth);
HI_S32 caption_cc_output_blit(HI_U32 u32UserPrivatData, HI_UNF_CC_RECT_S *pstSrcRect, HI_UNF_CC_RECT_S *pstDestRect);
HI_S32 caption_cc_output_vbi(HI_U32 u32UserData, HI_UNF_CC_VBI_DADA_S *pstVBIDataField1, HI_UNF_CC_VBI_DADA_S *pstVBIDataField2);

#ifdef __cplusplus
}
#endif

#endif
