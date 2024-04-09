/******************************************************************************

Copyright (C), 2009-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_drv_aiaov2.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/09/22
Last Modified :
Description   : aiao
Function List :
History       :
* main\1    2012-09-22   sdk     init.
******************************************************************************/
#ifndef __DRV_AIAO_IOCTL_VERI_H__
#define __DRV_AIAO_IOCTL_VERI_H__

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_module.h"
#include "hal_aiao_common.h"

#define  AIAO_VERI_PROC_NAME  "aiao_veri"

typedef struct hiAIAO_Sys_Crg_S
{
    HI_U32 u32CrgSkip;
} AIAO_Sys_Crg_S;

typedef struct
{
    HI_UNF_HDMI_ID_E enHdmi;
    HDMI_AUDIOINTERFACE_E   enSoundIntf;         /**<the origin of Sound,suggestion set HI_UNF_SND_INTERFACE_I2S,the parameter need consistent with Ao input *//**<CNcomment:HDMI��Ƶ��Դ, ����HI_UNF_SND_INTERFACE_I2S,�˲�����Ҫ��AO���뱣��һ�� */
    HI_U32                  u32Channels;         //��channel��multy channel���������������ں�̬�ɵ�multy channel
    HI_UNF_SAMPLE_RATE_E    enSampleRate;        /**<the samplerate of audio,this parameter consistent with AO config *//**<CNcomment:PCM��Ƶ������,�˲�����Ҫ��AO�����ñ���һ�� */
    HI_UNF_BIT_DEPTH_E      enBitDepth;  //ĿǰĬ����16bit    /**<the audio bit depth,defualt 16,this parameter consistent with AO config*//**<CNcomment:��Ƶλ��Ĭ��Ϊ16,�˲�����Ҫ��AO�����ñ���һ�� */
} AIAO_HDMI_AUDIO_ATRR_S;

#ifdef __aarch64__
#error "aiao veri only support 32bit driver!"
#endif

enum
{
    CMD_ID_AIAO_GET_CAPABILITY,
    CMD_ID_AIAO_SET_SYSCRG,
    CMD_ID_AIAO_RW_REGISTER,
    CMD_ID_AIAO_PORT_OPEN,
    CMD_ID_AIAO_PORT_CLOSE,
    CMD_ID_AIAO_PORT_START,
    CMD_ID_AIAO_PORT_STOP,
    CMD_ID_AIAO_PORT_MUTE,
    CMD_ID_AIAO_PORT_TRACKMODE,
    CMD_ID_AIAO_PORT_VOLUME,
    CMD_ID_AIAO_PORT_GET_USERCONFIG,
    CMD_ID_AIAO_PORT_GET_STATUS,
    CMD_ID_AIAO_PORT_SEL_SPDIFOUTSOURCE,
    CMD_ID_AIAO_PORT_SET_SPDIFOUTPORT,
    CMD_ID_AIAO_PORT_SET_I2SDATASEL,

    CMD_ID_AIAO_PORT_READ_DATA,
    CMD_ID_AIAO_PORT_WRITE_DATA,
    CMD_ID_AIAO_PORT_PREPARE_DATA,
    CMD_ID_AIAO_PORT_QUERY_BUF,
    CMD_ID_AIAO_PORT_UPDATE_RPTR,
    CMD_ID_AIAO_PORT_UPDATE_WPTR,

    CMD_ID_AIAO_HDMI_SETAUDIO_ATTR,

#ifdef HI_AIAO_TIMER_SUPPORT
    CMD_ID_AIAO_TIMER_CREATE,
    CMD_ID_AIAO_TIMER_DESTROY,
    CMD_ID_AIAO_TIMER_SETATTR,
    CMD_ID_AIAO_TIMER_SETENABLE,
    CMD_ID_AIAO_TIMER_GETSTATUS,
#endif

    CMD_ID_AIAO_TIANLAI_INIT,
    CMD_ID_AIAO_TIANLAI_DEINIT,
    CMD_ID_AIAO_TIANLAI_SETINSRC,

    CMD_ID_AIAO_BUTT
};

/*
 * AIAO command code definition
 */

/* global */
#define CMD_AIAO_GET_CAPABILITY                        _IOWR (HI_ID_AIAO, CMD_ID_AIAO_GET_CAPABILITY, AIAO_Port_GetCapability_S)
#define CMD_AIAO_SET_SYSCRG                            _IOWR (HI_ID_AIAO, CMD_ID_AIAO_SET_SYSCRG, AIAO_Sys_Crg_S)
/* global debug */
#define CMD_AIAO_RW_REGISTER                           _IOWR (HI_ID_AIAO, CMD_ID_AIAO_RW_REGISTER, AIAO_Dbg_Reg_S)

/* AIAO PORT */
#define CMD_AIAO_PORT_OPEN                             _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_OPEN, AIAO_Port_Open_S)
#define CMD_AIAO_PORT_CLOSE                            _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_CLOSE, AIAO_Port_Close_S)
#define CMD_AIAO_PORT_START                            _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_START, AIAO_Port_Start_S)
#define CMD_AIAO_PORT_STOP                             _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_STOP, AIAO_Port_Stop_S)
#define CMD_AIAO_PORT_MUTE                             _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_MUTE, AIAO_Port_Mute_S)
#define CMD_AIAO_PORT_TRACKMODE                        _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_TRACKMODE, AIAO_Port_TrackMode_S)
#define CMD_AIAO_PORT_VOLUME                           _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_VOLUME, AIAO_Port_Volume_S)
#define CMD_AIAO_PORT_GET_USERCONFIG                   _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_GET_USERCONFIG, AIAO_Port_GetUserConfig_S)
#define CMD_AIAO_PORT_GET_STATUS                       _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_GET_STATUS, AIAO_Port_GetSTATUS_S)
#define CMD_AIAO_PORT_SEL_SPDIFOUTSOURCE               _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_SEL_SPDIFOUTSOURCE, AIAO_Port_SelectSpdifSource_S)
#define CMD_AIAO_PORT_SET_SPDIFOUTPORT                 _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_SET_SPDIFOUTPORT, AIAO_Port_SetSpdifOutPort_S)
#define CMD_AIAO_PORT_SET_I2SDATASEL                   _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_SET_I2SDATASEL, AIAO_Port_I2SDataSel_S)

#define CMD_AIAO_PORT_READ_DATA                        _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_READ_DATA, AIAO_Port_ReadData_S)        /* get port data */
#define CMD_AIAO_PORT_WRITE_DATA                       _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_WRITE_DATA, AIAO_Port_WriteData_S)       /* write port data */
#define CMD_AIAO_PORT_PREPARE_DATA                     _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_PREPARE_DATA, AIAO_Port_WriteData_S)       /* prepare port data */
#define CMD_AIAO_PORT_QUERY_BUF                        _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_QUERY_BUF, AIAO_Port_BufStatus_S)       /* get port status */

#define CMD_AIAO_PORT_UPDATE_RPTR                      _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_UPDATE_RPTR, AIAO_Port_ReadData_S)        /* get port data */
#define CMD_AIAO_PORT_UPDATE_WPTR                      _IOWR (HI_ID_AIAO, CMD_ID_AIAO_PORT_UPDATE_WPTR, AIAO_Port_WriteData_S)       /* write port data */

/* HDMI TX */
#define CMD_AIAO_HDMI_SETAUDIO_ATTR                    _IOWR (HI_ID_AIAO, CMD_ID_AIAO_HDMI_SETAUDIO_ATTR, AIAO_HDMI_AUDIO_ATRR_S)        /* get port data */

#ifdef HI_AIAO_TIMER_SUPPORT
#define CMD_AIAO_TIMER_CREATE                          _IOWR (HI_ID_AIAO, CMD_ID_AIAO_TIMER_CREATE, AIAO_Timer_Create_S)
#define CMD_AIAO_TIMER_DESTROY                         _IOWR (HI_ID_AIAO, CMD_ID_AIAO_TIMER_DESTROY, AIAO_Timer_Destroy_S)
#define CMD_AIAO_TIMER_SETATTR                         _IOW  (HI_ID_AIAO, CMD_ID_AIAO_TIMER_SETATTR, AIAO_TIMER_Attr_S)
#define CMD_AIAO_TIMER_SETENABLE                       _IOW  (HI_ID_AIAO, CMD_ID_AIAO_TIMER_SETENABLE, AIAO_TIMER_Enable_S)
#define CMD_AIAO_TIMER_GETSTATUS                       _IOWR (HI_ID_AIAO, CMD_ID_AIAO_TIMER_GETSTATUS, AIAO_TIMER_Status_S)
#endif
/*TianLai*/
#define CMD_AIAO_TIANLAI_INIT                          _IOW  (HI_ID_AIAO, CMD_ID_AIAO_TIANLAI_INIT, S5_TIANLAI_SAMPLERATE_E)
#define CMD_AIAO_TIANLAI_DEINIT                        _IOW  (HI_ID_AIAO, CMD_ID_AIAO_TIANLAI_DEINIT, HI_U32)
#define CMD_AIAO_TIANLAI_SETINSRC                      _IOW  (HI_ID_AIAO, CMD_ID_AIAO_TIANLAI_SETINSRC, S5_TIANLAI_LINEIN_SEL_E)

#endif  // __DRV_AIAO_IOCTL_VERI_H__
