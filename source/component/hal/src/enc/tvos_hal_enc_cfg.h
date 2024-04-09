#include "tvos_hal_enc.h"
#include "hi_unf_disp.h"
#include "hi_unf_sound.h"

S32 cfg_enc_set_default_cast_attr(HI_UNF_DISP_CAST_ATTR_S* const pstCastAttr)
{
    pstCastAttr->u32Width  = 1280;
    pstCastAttr->u32Height = 720;
    pstCastAttr->bLowDelay = HI_TRUE;
    pstCastAttr->bCrop = HI_FALSE;

    return SUCCESS;
}

S32 cfg_enc_set_default_track_attr(HI_UNF_AUDIOTRACK_ATTR_S* const pstTrackAttr)
{
    pstTrackAttr->u32OutputBufSize = 256 * 1024;

    return SUCCESS;
}

S32 cfg_enc_get_capability(ENC_CAPABILITY_S* const pstCapability)
{
    U32 u32Count = 0;

    //ENC_OUTPUT_STREAM_FORMAT_E
    pstCapability->enOutputStreamFormat = ENC_OUTPUT_STREAM_FORMAT_ES;

    //ENC_AENC_CAPABILITY_S
    pstCapability->stAencArr.bExist = TRUE;

    //support AAC only
    for (u32Count = AV_AUD_STREAM_TYPE_MP2; u32Count < AV_AUD_STREAM_TYPE_BUTT; u32Count++)
    {
        pstCapability->stAencArr.astStreamTypeArr[u32Count].bSupportedDecType = FALSE;
    }

    pstCapability->stAencArr.astStreamTypeArr[AV_AUD_STREAM_TYPE_AAC].bSupportedDecType = TRUE;
    pstCapability->stAencArr.astStreamTypeArr[AV_AUD_STREAM_TYPE_AAC].u32Number = 1;

    //ENC_VENC_CAPABILITY_S
    pstCapability->stVencArr.bExist = TRUE;
    pstCapability->stVencArr.enType = ENC_ENCODE_VIDEO;

    //support H264 only
    for (u32Count = AV_VID_STREAM_TYPE_MPEG2; u32Count < AV_VID_STREAM_TYPE_BUTT; u32Count++)
    {
        pstCapability->stVencArr.astVencSupport[u32Count].bSupportedDecType = FALSE;
    }

    pstCapability->stVencArr.astVencSupport[AV_VID_STREAM_TYPE_H264].bSupportedDecType = TRUE;
    pstCapability->stVencArr.astVencSupport[AV_VID_STREAM_TYPE_H264].enDecCapLevel = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stVencArr.astVencSupport[AV_VID_STREAM_TYPE_H264].u32Number = 1;
    pstCapability->stVencArr.astVencSupport[AV_VID_STREAM_TYPE_H264].u32Fps = 30;

    return SUCCESS;
}
