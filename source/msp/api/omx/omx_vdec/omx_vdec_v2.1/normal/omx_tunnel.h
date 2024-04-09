#ifndef __OMX_TUNNEL_H__
#define __OMX_TUNNEL_H__

#include "OMX_Types.h"
#include "OMX_VideoExt.h"

#ifdef ANDROID_O
#include <hardware/gralloc1.h>
#else
#include <hardware/gralloc.h>
#endif

#include "gralloc_priv.h"
#include "vfmw.h"
typedef struct
{
    HI_HANDLE client_player;
    HI_HANDLE play_handle;
    HI_HANDLE win_handle;
    ConfigureVideoTunnelModeParams config_param;
    native_handle_t native_handle;

} OMX_TUNNEL_INFO;


OMX_ERRORTYPE omx_tunnel_init(OMX_COMPONENTTYPE *pcomp, OMX_PTR pInitParam);
OMX_ERRORTYPE omx_tunnel_deinit(OMX_COMPONENTTYPE *pcomp);
OMX_ERRORTYPE omx_tunnel_enable(OMX_COMPONENTTYPE *pcomp);
OMX_ERRORTYPE omx_tunnel_disable(OMX_COMPONENTTYPE *pcomp);
OMX_ERRORTYPE omx_tunnel_start(OMX_COMPONENTTYPE *pcomp);
OMX_ERRORTYPE omx_tunnel_stop(OMX_COMPONENTTYPE *pcomp);
OMX_ERRORTYPE omx_tunnel_flush(OMX_COMPONENTTYPE *pcomp);
OMX_ERRORTYPE omx_tunnel_parse_csd(OMXVDEC_BUF_DESC *pBuffer, OMX_TUNNEL_CSD *csd);
OMX_ERRORTYPE omx_tunnel_config_avlay_dolbyhdr(OMX_COMPONENTTYPE *pcom_priv, OMXVDEC_BUF_DESC *pBuffer);
OMX_ERRORTYPE omx_tunnel_get_hdr_static_info(OMX_COMPONENTTYPE *pcomp, DescribeHDRStaticInfoParams *describe_hdr_static_info);
OMX_ERRORTYPE omx_tunnel_set_hdr_static_info(OMX_COMPONENTTYPE *pcomp, DescribeHDRStaticInfoParams *describe_hdr_static_info);
OMX_ERRORTYPE omx_tunnel_get_color_aspects(OMX_COMPONENTTYPE *pcomp, DescribeColorAspectsParams *describe_color_aspects_params);
OMX_ERRORTYPE omx_tunnel_set_color_aspects(OMX_COMPONENTTYPE *pcomp, DescribeColorAspectsParams *describe_color_aspects_params);

#ifdef HI_OMX_TEE_SUPPORT
OMX_ERRORTYPE omx_tunnel_secure_parse_csd(OMXVDEC_BUF_DESC *pBuffer, OMX_TUNNEL_CSD *pcsd);
#endif

#endif
