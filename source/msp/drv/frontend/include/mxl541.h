#ifndef __MXL541_H__
#define __MXL541_H__

//#include "MxLWare_HYDRA_CommonApi.h"
//#include "MaxLinearDataTypes.h"



extern HI_U32  u32ResetGpioNo;



HI_S32 mxl541_init(HI_U32 u32TunerPort);
HI_S32 mxl541_set_sat_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_SAT_ATTR_S *pstSatTunerAttr);
HI_S32 mxl541_set_ts_out(HI_U32 u32TunerPort, HI_UNF_TUNER_TSOUT_SET_S *pstTSOut);
HI_S32 mxl541_set_ts_type(HI_U32 u32TunerPort, HI_UNF_TUNER_OUPUT_MODE_E enTsType);
HI_S32 mxl541_set_lnb_out(HI_U32 u32TunerPort, TUNER_LNB_OUT_E enOut);
HI_S32 mxl541_connect(HI_U32 u32TunerPort, TUNER_ACC_QAM_PARAMS_S *pstChannel);
HI_VOID mxl541_connect_timeout(HI_U32 u32ConnectTimeout);
HI_S32 mxl541_set_funcmode(HI_U32 u32TunerPort, TUNER_FUNC_MODE_E enFuncMode);
HI_S32 mxl541_send_continuous_22K(HI_U32 u32TunerPort, HI_U32 u32Continuous22K);
HI_S32 mxl541_send_tone(HI_U32 u32TunerPort, HI_U32 u32Tone);
HI_S32 mxl541_DiSEqC_send_msg(HI_U32 u32TunerPort, HI_UNF_TUNER_DISEQC_SENDMSG_S *pstSendMsg);
HI_S32 mxl541_DiSEqC_recv_msg(HI_U32 u32TunerPort, HI_UNF_TUNER_DISEQC_RECVMSG_S *pstRecvMsg);
HI_S32 mxl541_get_status(HI_U32 u32TunerPort, HI_UNF_TUNER_LOCK_STATUS_E * penTunerStatus);
HI_S32 mxl541_get_ber(HI_U32 u32TunerPort, HI_U32 * pu32BERa);
HI_S32 mxl541_get_snr(HI_U32 u32TunerPort, HI_U32* pu32SNR);
HI_S32 mxl541_get_signal_strength(HI_U32 u32TunerPort, HI_U32 * pu32strength);
HI_S32 mxl541_get_signal_info(HI_U32 u32TunerPort, HI_UNF_TUNER_SIGNALINFO_S *pstInfo);
HI_S32 mxl541_get_powerspecdata(HI_U32 u32TunerPort, HI_U32 u32freqStartInHz,HI_U32 u32freqStepInHz,HI_U32 u32numOfFreqSteps,HI_S16 *ps16powerData);
HI_S32 mxl541_get_freq_symb_offset(HI_U32 u32TunerPort, HI_U32 * pu32Freq, HI_U32 * pu32Symb);
HI_S32 mxl541_standby(HI_U32 u32TunerPort, HI_U32 u32Standby);
HI_S32 mxl541_deinit(HI_VOID);



#endif
