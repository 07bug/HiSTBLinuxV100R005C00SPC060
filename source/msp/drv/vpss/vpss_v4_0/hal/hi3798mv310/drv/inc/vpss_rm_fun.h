#ifndef __XDP_RM_FUN_H__
#define __XDP_RM_FUN_H__

#include "hi_type.h"
#include "alg_comm.h"
#include "alg_lib.h"
#include "xdp_img.h"
#include "xdp_solo.h"

typedef struct
{
    VIDEO_FRAME_S pVideoData[16];
    HI_BOOL bSignedFlag[16] ;
    HI_U32  u32StWidth[16] ;
} VIDEO_FRAMES_S;

PIXEL_FORMAT_E eXdpFormatToPixFormat(HI_U32 InFormat);
HI_VOID vXdpImgToVideoFrameS(cImgData *pSrcData, VIDEO_FRAME_S *pDstData) ;
HI_VOID vVideoFrameSToXdpImg(VIDEO_FRAME_S *pSrcData, cImgData *pDstData) ;
HI_VOID vSoloDataToVideoFrameS(cSoloData *pSrcData, VIDEO_FRAMES_S *pDstData)  ;
HI_VOID vVideoFrameSToSoloData(VIDEO_FRAMES_S *pSrcData, cSoloData *pDstData)  ;
#endif

