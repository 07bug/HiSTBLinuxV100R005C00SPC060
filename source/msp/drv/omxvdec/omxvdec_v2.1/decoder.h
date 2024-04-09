#ifndef __DECODER_H__
#define __DECODER_H__

#include "channel.h"

#define LAST_FRAME_BUF_ID           (0xFFFFFFEE)
#define LAST_FRAME_BUF_SIZE         (20)

typedef enum
{
    DEC_CMD_CLEAR_STREAM,
    DEC_CMD_ALLOC_MEM,
    DEC_CMD_BIND_MEM,
    DEC_CMD_ACTIVATE_INST,
    DEC_CMD_CONFIG_MEM,
    DEC_CMD_BUTT,
} DECODER_CMD_E;

HI_S32 decoder_init(HI_VOID);
HI_S32 decoder_exit(HI_VOID);
HI_S32 decoder_create_inst(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_DRV_CFG *pdrv_cfg);
HI_S32 decoder_release_inst(OMXVDEC_CHAN_CTX *pchan);
HI_S32 decoder_start_inst(OMXVDEC_CHAN_CTX *pchan);
HI_S32 decoder_stop_inst(OMXVDEC_CHAN_CTX *pchan);
HI_S32 decoder_reset_inst(OMXVDEC_CHAN_CTX *pchan);
HI_S32 decoder_reset_inst_with_option(OMXVDEC_CHAN_CTX *pchan);
HI_S32 decoder_command_handler(OMXVDEC_CHAN_CTX *pchan, DECODER_CMD_E eCmd, HI_VOID *pArgs, UINT32 ParamLength);
HI_S32 decoder_get_stream_ex(HI_S32 chan_id, HI_VOID *stream_data);
HI_S32 decoder_release_stream_ex(HI_S32 chan_id, HI_VOID *stream_data);

#endif

