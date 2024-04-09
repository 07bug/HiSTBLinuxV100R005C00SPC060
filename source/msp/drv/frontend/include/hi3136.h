#ifndef __HI3136_H__
#define __HI3136_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*
#define          POLAR_SWITCH                   0        0 level for 18V,1 level for 13V
Diseqc Command word
-----------------------------------
֡ͷ+��ַ+����+����
-----------------------------------
#define     HI3136_DISEQC_CMD1          0xE0  //��ͷ
#define     HI3136_DISEQC_CMD2          0x10  //��ַ
#define     HI3136_DISEQC_CMD3          0x38 //����committed
#define     HI3136_DISEQC_CMD3_1        0x39 //���� uncommitted

#define     HI3136_DISEQC_CMD4_LNB1     0xF0
#define     HI3136_DISEQC_CMD4_SW01     0xF0
#define     HI3136_DISEQC_CMD4_SW02     0xF1
#define     HI3136_DISEQC_CMD4_SW03     0xF2
#define     HI3136_DISEQC_CMD4_SW04     0xF3
#define     HI3136_DISEQC_CMD4_SW05     0xF4
#define     HI3136_DISEQC_CMD4_SW06     0xF5
#define     HI3136_DISEQC_CMD4_SW07     0xF6
#define     HI3136_DISEQC_CMD4_SW08     0xF7
#define     HI3136_DISEQC_CMD4_SW09     0xF8
#define     HI3136_DISEQC_CMD4_SW10     0xF9
#define     HI3136_DISEQC_CMD4_SW11     0xFA
#define     HI3136_DISEQC_CMD4_SW12     0xFB
#define     HI3136_DISEQC_CMD4_SW13     0xFC
#define     HI3136_DISEQC_CMD4_SW14     0xFD
#define     HI3136_DISEQC_CMD4_SW15     0xFE
#define     HI3136_DISEQC_CMD4_SW16     0xFF
*/

/*PLL module*/
#define     PLL_CTRL1                   0x00
#define     PLL_CTRL2                   0x01
#define     PLL_CTRL3                   0x02
#define     PLL_CTRL4                   0x03
#define     PLL_CTRL5                   0x04
#define     PLL_CTRL6                   0x05
#define     PLL_CTRL7                   0x06
#define     PLL_CTRL8                   0x07
#define     PLL_CTRL9                   0x08
#define     PLL_CTRL10                  0x09
#define     ADC_CTRL1                   0x0a
#define     TS_CTRL1                    0x0b
#define     ADC_CTRL2                   0x0c
#define     IO_CTRL1                    0x0d
#define     IO_CTRL2                    0x0e

#define     MAN_RST_CTRL0               0x20
#define     STATE_WAITS                 0x22
#define     CLK_DEMO_L                  0x23
#define     CLK_DEMO_M                  0x24
#define     CLK_DEMO_H                  0x25

#define     CLK_FEC_L                   0x26
#define     CLK_FEC_M                   0x27
#define     CLK_FEC_H                   0x28

/*MAN module*/
#define     LOCK_FLAG                   0x2c
#define     TUNER_SEL                   0x2d

/*IP_IO_CONFIG*/
#define     RSTN_CTRL                   0x2e
#define     ILA_SEL                     0x2f

/*AGC module*/
#define     AGC_SPEED_BOUND             0x30
#define     AGC_CTRL                    0x33
#define     AGC_CTRL_L                  0x37
#define     AGC_CTRL_H                  0x38

/*TR module*/
#define     FS_L                        0x46
#define     FS_H                        0x47
#define     CENT_FREQ_L                 0x48
#define     CENT_FREQ_H                 0x49
#define     FS_OFFSET_FC_L              0x4c
#define     FS_OFFSET_FC_H              0x4d
#define     FREQ_OFFSET_FC_L            0x4e
#define     FREQ_OFFSET_FC_H            0x4f

/*CR module*/
#define     CR_CTRL_SW                  0x52
#define     CR_BW_MAX                   0x58
#define     CR_CN                       0x5a
#define     CR_STATE                    0x5b
#define     CR_PLS_CODE                 0x5c

/*CR module*/
#define     TR_FREQ_FB_L                0x66
#define     TR_FREQ_FB_H                0x67

#define     XREG_INIT_LOW               0x7a
#define     XREG_INIT_MID               0x7b
#define     XREG_INIT_HI                0x7c
#define     NOISE_POW_CPU_L             0x7e
#define     NOISE_POW_CPU_H             0x7f

/*���ϼĴ�����3136��һ��*/

/*FEC module*/
#define     LDPC_ITER                   0x82    /*����3138����3136ûʹ��,Ӧʹ��HI3138_S_ITER_CTRL*/
#define     BER_CTRL                    0x83    /*����3138��Ӧʹ��HI3138_S_BER_CTRL*/

#define     FEC_BER_L                   0x84    /*����3138��Ӧʹ��HI3138_S_FEC_BER_L*/
#define     FEC_BER_H                   0x85    /*����3138��Ӧʹ��HI3138_S_FEC_BER_H*/
//#define     FEC_FER_L                 0x86    /*����3138����3136ûʹ��*/
//#define     FEC_FER_H                 0x87    /*����3138����3136ûʹ��*/
#define     FS_CTRL1                    0x8c    /*����3138����3138û�ҵ�*/
#define     FS_CTRL2                    0x8d    /*����3138����3138û�ҵ�*/
#define     SEAR_RESULT                 0x8e    /*����3138��Ӧʹ��HI3138_S_SEAR_RESULT*/

/*OUTP module*/
#define     TS_PARALL_CTRL              0x90    /*����3138��Ӧʹ��HI3138_S_TS_PARALL_CTRL*/
#define     TS_OUT10_SEL                0x91    /*����3138��Ӧʹ��HI3138_S_TS_10_SEL*/
#define     TS_OUT32_SEL                0x92    /*����3138��Ӧʹ��HI3138_S_TS_32_SEL*/
#define     TS_OUT54_SEL                0x93    /*����3138��Ӧʹ��HI3138_S_TS_54_SEL*/
#define     TS_OUT76_SEL                0x94    /*����3138��Ӧʹ��HI3138_S_TS_76_SEL*/
#define     TS_OUT98_SEL                0x95    /*����3138��Ӧʹ��HI3138_S_TS_98_SEL*/
#define     TS_CTRL0                    0x96    /*����3138��Ӧʹ��HI3138_S_TS_CTRL0*/
//#define     TS_CTRL1                  0x97    /*����3138��Ӧʹ��HI3138_S_TS_CTRL1*/
#define     TS_CTRL3                    0x97    /*����3138��Ӧʹ��HI3138_S_TS_CTRL3*/
#define     TS_CTRL4                    0x98    /*����3138��Ӧʹ��HI3138_S_TS_CTRL4*/

#define     TS_CLK_DIV_F_L              0x99    /*����3138��Ӧʹ��HI3138_S_TS_CLK_DIV_F_L*/
#define     TS_CLK_DIV_F_H              0x9a    /*����3138��Ӧʹ��HI3138_S_TS_CLK_DIV_F_H*/

#define     ISI_SEL                     0x9b    /*����3138��Ӧʹ��HI3138_S_ISI_SEL*/
#define     MATYPE_OUT                  0x9c    /*����3138��Ӧʹ��HI3138_S_MATTYPE*/
#define     ISI_NUM                     0x9d    /*����3138��Ӧʹ��Ӧʹ��HI3138_S_ISI_NUM*/

/*CBS module*/
#define     FC_MAX_RELIABLE             0xa0
#define     FS_SPAN                     0xa1
#define     CBS_TH1_COR_NO              0xa2    /*����3138����3136ûʹ��*/
#define     CBS_CTRL_RDADDR             0xa8
#define     CBS_FS_L                    0xa9
#define     CBS_FS_H                    0xaa
#define     CBS_FC_L                    0xab
#define     CBS_FC_H                    0xac
#define     CBS_FINISH                  0xad
#define     CBS_RELIABLITY              0xae
#define     CBS_R2_NUM                  0xaf

/*DISEQC module*/
#define     DSEC_ADDR                   0xb0
#define     DSEC_DATA                   0xb1
#define     DSEC_RATIO_L                0xb2
#define     DSEC_RATIO_H                0xb3
#define     TX_CTRL                     0xb4
#define     DSEC_EN                     0xb7
#define     RX_STATE                    0xb8
#define     INT_STATE                   0xb9

/*for hi3136*/
extern HI_S32 hi3136_init(HI_U32 u32TunerPort, HI_U8 enI2cChannel, HI_UNF_TUNER_DEV_TYPE_E enTunerDevType);
extern HI_S32 hi3136_set_sat_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_SAT_ATTR_S *pstSatTunerAttr);
extern HI_S32 hi3136_deInit(HI_U32 u32TunerPort);
extern HI_S32 hi3136_connect(HI_U32 u32TunerPort, TUNER_ACC_QAM_PARAMS_S * pstChannel);
extern HI_S32 hi3136_get_status (HI_U32 u32TunerPort, HI_UNF_TUNER_LOCK_STATUS_E  *penTunerStatus);
extern HI_S32 hi3136_get_ber(HI_U32 u32TunerPort, HI_U32* pu32ber);
extern HI_S32 hi3136_get_snr(HI_U32 u32TunerPort, HI_U32* pu32SNR);
extern HI_S32 hi3136_get_signal_strength(HI_U32 u32TunerPort, HI_U32* pu32SignalStrength);
extern HI_S32 hi3136_get_freq_symb_offset(HI_U32 u32TunerPort, HI_U32 * pu32Freq, HI_U32 * pu32Symb);
extern HI_S32 hi3136_get_signal_info(HI_U32 u32TunerPort, HI_UNF_TUNER_SIGNALINFO_S *pstInfo);
extern HI_S32 hi3136_set_ts_type(HI_U32 u32TunerPort, HI_UNF_TUNER_OUPUT_MODE_E enTsType);
extern HI_S32 hi3136_blindscan_init(HI_U32 u32TunerPort, TUNER_BLINDSCAN_INITPARA_S *pstPara);
extern HI_S32 hi3136_blindscan_action(HI_U32 u32TunerPort, TUNER_BLINDSCAN_PARA_S *pstPara);
extern HI_S32 hi3136_lnbctrl_power(HI_U32 u32TunerPort, HI_U8 u8Power);
extern HI_S32 hi3136_set_lnb_out(HI_U32 u32TunerPort, TUNER_LNB_OUT_E enOut);
extern HI_S32 hi3136_send_continuous_22K(HI_U32 u32TunerPort, HI_U32 u32Continuous22K);
extern HI_S32 hi3136_send_tone(HI_U32 u32TunerPort, HI_U32 u32Tone);
extern HI_S32 hi3136_DiSEqC_send_msg(HI_U32 u32TunerPort, HI_UNF_TUNER_DISEQC_SENDMSG_S *pstSendMsg);
extern HI_S32 hi3136_DiSEqC_recv_msg(HI_U32 u32TunerPort, HI_UNF_TUNER_DISEQC_RECVMSG_S *pstRecvMsg);
extern HI_S32 hi3136_standby(HI_U32 u32TunerPort, HI_U32 u32Standby);
extern HI_S32 hi3136_disable(HI_U32 u32TunerPort, HI_U32 u32Disable);
extern HI_S32 hi3136_set_funcmode(HI_U32 u32TunerPort, TUNER_FUNC_MODE_E enFuncMode);
extern HI_S32 hi3136_tp_verify(HI_U32 u32TunerPort, TUNER_TP_VERIFY_PARAMS_S *pstChannel);
extern HI_S32 hi3136_set_ts_out(HI_U32 u32TunerPort, HI_UNF_TUNER_TSOUT_SET_S *pstTSOut);
extern HI_S32 hi3136_get_data_sample(HI_U32 u32TunerPort, TUNER_DATA_SRC_E enDataSrc, HI_U32 u32DataLen, HI_UNF_TUNER_SAMPLE_DATA_S *pstData);
extern HI_S32 hi3136_set_isi_id(HI_U32 u32TunerPort, HI_U8 u8IsiId);
extern HI_S32 hi3136_get_total_isi_number(HI_U32 u32TunerPort, HI_U32 *pu32TotalStream);
extern HI_S32 hi3136_get_isi_id(HI_U32 u32TunerPort, HI_U8 u8Stream, HI_U8 *pu8IsiId);
extern HI_S32 hi3136_get_agc(HI_U32 u32TunerPort, HI_U32 Fcenter, HI_U32 *pu32Agc);
extern HI_S32 hi3136_set_scramble(HI_U32 u32TunerPort, HI_U32 u32Value);
extern HI_VOID hi3136_read_registers(HI_U32 u32TunerPort, void *p);

typedef enum tagHI3136_LOCK_STATUS_E
{
    UNLOCKED = 0,
    AGC_LOCKED,
    CBS_LOCKED,
    TR_LOCKED,
    SYNC_LOCKED,
    CR_LOCKED,
    FEC_LOCKED
} HI3136_LOCK_STATUS_E;

#define         BW_MAX_SET              0x12
#define         CN_TH                   230
typedef struct TP_VERIFY_INFO_st
{
    HI_U8 average_num;

    HI_U32 if_kHz;
    HI_U32 fs_Hz;
    HI_S32 mean_fc;
    HI_S32 mean_fs;
    HI_S32 mean_reliable;

    HI_U32 tim_ok_wait;
    HI_U8 s2_sync_bit;
    HI_U8 scan_ok_bit;
    HI_U8 low_cn;

    HI_U32 fec_num;
    HI_U32 scan_wait_s2_q;
    HI_U32 scan_wait_s2_8;
    HI_U32 scan_wait_s1;
    HI_U32 fec_num_all;
    HI_U32 fec_wait_s1;
    HI_S16 cn_drop;
    HI_U8 ScanNum;
    HI_U8 old_bw_max;
    HI_U8 fec_ok_bit;
    HI_U8 s1_high_cn;
    HI_U8 try_enough;
    HI_U8 cr_ok_err;
}TP_VERIFY_INFO_ST;

typedef struct TP_VERIFY_INIT_PARAM_st
{
    HI_U32 fs_grade;
    HI_U32 scan_wait_s2_q;
    HI_U32 scan_wait_s2_8;
    HI_U32 tim_ok_wait;
    HI_U32 fec_wait_s1;
    HI_U32 scan_wait_s1;

    HI_U32 hist_is_ok;
    HI_U32 eq_fs_no_cnt;
    HI_U32 eq_fs_no_cnt2;
    HI_U32 fec_ok_cnt;
    HI_U32 tp_all;
    HI_U32 pre_reliablity;

    HI_U8 average_num;
}TP_VERIFY_INIT_PARAM_ST;

#ifdef __cplusplus
}
#endif

#endif