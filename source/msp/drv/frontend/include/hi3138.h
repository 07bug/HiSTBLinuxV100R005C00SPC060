#ifndef __HI3138_H__
#define __HI3138_H__

#include "hi3138_info.h"
#include "hi3138_ts.h"
#include "hi3138_dvbc.h"
#include "hi3138_dvbs2.h"
#include "hi3138_dvbt2.h"
#include "hi3138_isdbt.h"

#ifdef __cplusplus
 #if __cplusplus
    extern "C" {
 #endif
#endif /* __cplusplus */


#define HI3138_I2C_CHN_SEL          0x00    //I2C_BASE--I2Cͨ��ѡ��Ĵ���
#define HI3138_CHIP_ID0             0x02    //I2C_BASE--оƬID�Ĵ���
#define HI3138_CHIP_ID1             0x03    //I2C_BASE--оƬID�Ĵ���
#define HI3138_TEST_SEL             0x05    //I2C_BASE--����ѡ��Ĵ���
#define HI3138_COOL_RSTN            0x0F    //I2C_BASE--�临λ���ƼĴ���

#define HI3138_CHN_ON               0x10    //IPIO--ͨ��ģʽ���ƼĴ���
#define HI3138_CRG_CTRL0            0x11    //IPIO--SDRAMʱ����λ�Ĵ���
#define HI3138_CRG_CTRL1            0x12    //IPIO--ͨ��0����ʱ�����üĴ���
#define HI3138_CRG_CTRL2            0x13    //IPIO--ͨ��1����ʱ�����üĴ���
#define HI3138_ADI2C_SEL            0x14    //IPIO--I2Cת��ͨ�����üĴ���
#define HI3138_ADC0_CTRL0           0x15    //IPIO--ADC0���ƼĴ���
#define HI3138_ADC0_CTRL1           0x16    //IPIO--ADC0���ƼĴ���
#define HI3138_ADC1_CTRL0           0x18    //IPIO--ADC1���ƼĴ���
#define HI3138_ADC1_CTRL1           0x19    //IPIO--ADC1���ƼĴ���
#define HI3138_ADC1_CTRL2           0x1B    //IPIO--ADC0/ADC1���ƼĴ���
#define HI3138_PLL0_CTRL0           0x1C    //IPIO--PLL0С����Ƶϵ����λ�Ĵ���?
#define HI3138_PLL0_CTRL1           0x1D    //IPIO--PLL0���ƼĴ���
#define HI3138_PLL0_CTRL2           0x1E    //IPIO--PLL0�����Ƶϵ���Ĵ���
#define HI3138_PLL0_CTRL3           0x1F    //IPIO--PLL0������Ƶϵ���Ĵ���
#define HI3138_PLL0_CTRL4           0x20    //IPIO--PLL0�ο���Ƶϵ���Ĵ���
#define HI3138_PLL0_CTRL5           0x21    //IPIO--PLL0��λ�Ĵ���
#define HI3138_PLL1_CTRL0           0x23    //IPIO--PLL1С����Ƶϵ����λ�Ĵ���
#define HI3138_PLL1_CTRL1           0x24    //IPIO--PLL1���ƼĴ���
#define HI3138_PLL1_CTRL2           0x25    //IPIO--PLL1�����Ƶϵ���Ĵ���
#define HI3138_PLL1_CTRL3           0x26    //IPIO--PLL1������Ƶϵ���Ĵ���
#define HI3138_PLL1_CTRL4           0x27    //IPIO--PLL1�ο���Ƶϵ���Ĵ���
#define HI3138_PLL1_CTRL5           0x28    //IPIO--PLL1��λ�Ĵ���
#define HI3138_IO_CTRL0             0x29    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL1             0x2A    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL2             0x2B    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL3             0x2C    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL4             0x2D    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL5             0x2E    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL6             0x2F    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL7             0x30    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL8             0x31    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL9             0x32    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL10            0x33    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL11            0x34    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL12            0x35    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL13            0x36    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL14            0x37    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL15            0x38    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL16            0x39    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL17            0x3A    //IPIO--IO ���üĴ���
#define HI3138_IO_CTRL18            0x3B    //IPIO--IO ���üĴ���
#define HI3138_SDR_BIST_CTRL0       0x3C    //IPIO--SDRAM BIST���üĴ���
#define HI3138_SDR_BIST_CTRL1       0x3D    //IPIO--SDRAM BIST��ʼ��ַ��λ�Ĵ���
#define HI3138_SDR_BIST_CTRL2       0x3E    //IPIO--SDRAM BIST��ʼ��ַ��λ�Ĵ���
#define HI3138_SDR_BIST_CTRL3       0x3F    //IPIO--SDRAM BIST��ʼ��ַ��λ�Ĵ���
#define HI3138_SDR_BIST_CTRL4       0x40    //IPIO--SDRAM BIST���ȵ�λ�Ĵ���
#define HI3138_SDR_BIST_CTRL5       0x41    //IPIO--SDRAM BIST������λ�Ĵ���
#define HI3138_SDR_BIST_CTRL6       0x42    //IPIO--SDRAM BIST���ȸ�λ�Ĵ���
#define HI3138_MTS_CTRL0            0x43    //IPIO--MTS���üĴ���
#define HI3138_MTS_OUT_SEL10        0x44    //IPIO--MTS�ܽ�ӳ��Ĵ���
#define HI3138_MTS_OUT_SEL32        0x45    //IPIO--MTS�ܽ�ӳ��Ĵ���
#define HI3138_MTS_OUT_SEL54        0x46    //IPIO--MTS�ܽ�ӳ��Ĵ���
#define HI3138_MTS_OUT_SEL76        0x47    //IPIO--MTS�ܽ�ӳ��Ĵ���
#define HI3138_MTS_OUT_SEL98        0x48    //IPIO--MTS�ܽ�ӳ��Ĵ���
#define HI3138_MTS_OUT_SELA         0x49    //IPIO--MTS�ܽ�ӳ��Ĵ���
#define HI3138_MTS_CTRL1            0x4A    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL2            0x4B    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL3            0x4C    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL4            0x4D    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL5            0x4E    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL6            0x4F    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL7            0x50    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL8            0x51    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL9            0x52    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL10           0x53    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL11           0x54    //IPIO--MTS���üĴ���
#define HI3138_MTS_CTRL12           0x55    //IPIO--MTS���üĴ���
#define HI3138_TS_CLK_CTRL          0x56    //IPIO--TS_CLK���üĴ���
#define HI3138_ADC0_STATUS          0x57    //IPIO--ADC0״̬�Ĵ���
#define HI3138_ADC1_STATUS          0x58    //IPIO--ADC1״̬�Ĵ���
#define HI3138_PLL_STATUS           0x5C    //IPIO--PLL״̬�Ĵ���
#define HI3138_IO_CTRL19            0x5D    //IPIO--IO ���üĴ���

#define HI3138_RSTN_CTRL            0x2E

#define HI3138_T_MAN_RST_CTRL0      0x20    //T--��λ���ƼĴ���
#define HI3138_T_MAN_RST_CTRL1      0x21    //T--��λ����ʹ�ܼĴ���
#define HI3138_T_STATE_WAITS        0x22    //T--��ʱ��λ�Ĵ���
#define HI3138_T_CLK_DEMO_L         0x23    //T--���ʱ�ӵ�λ�Ĵ���
#define HI3138_T_CLK_DEMO_M         0x24    //T--���ʱ����λ�Ĵ���
#define HI3138_T_CLK_FEC_L          0x26    //T--FECʱ�ӵ�λ�Ĵ���
#define HI3138_T_CLK_FEC_M          0x27    //T--FECʱ����λ�Ĵ���
#define HI3138_T_CLK_SDC_L          0x29    //T--SDCʱ�ӵ�λ�Ĵ���
#define HI3138_T_CLK_SDC_M          0x2A    //T--SDCʱ����λ�Ĵ���
#define HI3138_T_SDC_CTRL           0x2B    //T--SDC���ƼĴ���
#define HI3138_T_LOCK_FLAG          0x2C    //T--����ָʾ�Ĵ���
#define HI3138_T_TUNER_SEL          0x2D    //T--tuner���ƼĴ���
#define HI3138_T_RSTN_CTRL          0x2E    //T--�߼���λ�Ĵ���
#define HI3138_T_ILA_SEL            0x2F    //T--��������ѡ��Ĵ���
#define HI3138_T_AGC_SPEED_BOUND    0x30    //T--agc�����Ĵ���
#define HI3138_T_AGC_GOAL           0x31    //T--agc���ʼĴ���
#define HI3138_T_AGCOK_WAIT         0x32    //T--agc�ȴ��Ĵ���
#define HI3138_T_AGC_CTRL           0x33    //T--agc���ƼĴ���
#define HI3138_T_AGC_DC_I           0x34    //T--I·ֱ���Ĵ���
#define HI3138_T_AGC_DC_Q           0x35    //T--Q·ֱ���Ĵ���
#define HI3138_T_DAGC_CTRL          0x36    //T--����agc���ƼĴ���
#define HI3138_T_AGC_CTRL_L         0x37    //T--agc���ʵ�λ�Ĵ���
#define HI3138_T_AGC_CTRL_H         0x38    //T--agc���ʸ�λ�Ĵ���
#define HI3138_T_AMP_ERR_IIR        0x39    //T--�������Ĵ���
#define HI3138_T_PDM_CTRL_L         0x3A    //T--�ֶ�agc�����ֵ�λ�Ĵ���
#define HI3138_T_PDM_CTRL_H         0x3B    //T--�ֶ�agc�����ָ�λ�Ĵ���
#define HI3138_T_USE_PWM            0x3C    //T--AGC�������ѡ��Ĵ���
#define HI3138_T_DAGC_INNER_CTRL    0x40    //T--����AGC���ƼĴ���
#define HI3138_T_SF_RMV             0x41    //T--խ���������ƿ��ƼĴ���
#define HI3138_T_DAGC_REF           0x42    //T--dagc���Ȳο�ֵ�Ĵ���
#define HI3138_T_DAGC_SPEED         0x43    //T--dagc����ѡ��Ĵ���
#define HI3138_T_IF_FREQ_L          0x4A    //T--�����ź���ƵƵ�ʵ�λ�Ĵ���
#define HI3138_T_IF_FREQ_H          0x4B    //T--�����ź���ƵƵ�ʸ�λ�Ĵ���
#define HI3138_T_BAND_WIDTH         0x4E    //T--�����źŴ���Ĵ���
#define HI3138_T_SYN_CTRL0          0x50    //T--ͬ�����ƼĴ���
#define HI3138_T_CORR_HIGH_TH       0x51    //T--P2��ؼ������޼Ĵ���
#define HI3138_T_CORR_LOW_TH        0x52    //T--P2��ؼ������޼Ĵ���
#define HI3138_T_P2_POS_MOD         0x53    //T--P2ͬ��λ�ü������Ĵ���
#define HI3138_T_P1_THRES           0x54    //T--P1ͬ�����ƼĴ���
#define HI3138_T_CHN_FFT_GI         0x55    //T--ͬ���������Ĵ���
#define HI3138_T_P1_SIGNAL          0x56    //T--P1�������Ĵ���
#define HI3138_T_TIM_OFFSET         0x57    //T--��ʱ���Ĵ���
#define HI3138_T_CAR_OFFSET_L       0x58    //T--�ز�����λ�Ĵ���
#define HI3138_T_CAR_OFFSET_H       0x59    //T--�ز�����λ�Ĵ���
#define HI3138_T_T2_CHK_CTRL        0x5D    //T--DVB-T2������üĴ���
#define HI3138_T_SOAC_TH            0x5E    //T--P1���������޼Ĵ���
#define HI3138_T_OUTP_RAND          0x5F    //T--�������üĴ���
#define HI3138_T_LOOP_BW            0x60    //T--��·����ѡ��Ĵ���
#define HI3138_T_FD_GRP             0x61    //T--ʱ���ֵ���ƼĴ���
#define HI3138_T_CPE                0x62
#define HI3138_T_NP_IIR_SFT         0x64    //T--CSI������ƼĴ���
#define HI3138_T_ECHO_ISI           0x65
#define HI3138_T_ECHO_THRES         0x67    //T--�ྶ������޼Ĵ���
#define HI3138_T_ECHO_THL           0x68
#define HI3138_T_MIN_THRES          0x69    //T--�ྶ���������Сֵ�Ĵ���
#define HI3138_T_NP_GRP             0x6A    //T--ʱ���ֵ���ƼĴ���
#define HI3138_T_TS_A9_SEL          0x6B    //T--ts������ƼĴ���
#define HI3138_T_TS_87_SEL          0x6C    //T--ts������ƼĴ���
#define HI3138_T_TS_65_SEL          0x6D    //T--ts������ƼĴ���
#define HI3138_T_TS_43_SEL          0x6E    //T--ts������ƼĴ���
#define HI3138_T_TS_21_SEL          0x6F    //T--ts������ƼĴ���
#define HI3138_T_TIM_LOOP_L         0x70    //T--��ʱ����λ�Ĵ���
#define HI3138_T_TIM_LOOP_H         0x71    //T--��ʱ����λ�Ĵ���
#define HI3138_T_MAX_TH             0x74
#define HI3138_T_TS_0_SEL           0x75    //T--ts������ƼĴ���
#define HI3138_T_CIR_DIST_0         0x76    //T--�ྶ�ֲ��Ĵ���
#define HI3138_T_CIR_DIST_1         0x77    //T--�ྶ�ֲ��Ĵ���
#define HI3138_T_CIR_DIST_2         0x78    //T--�ྶ�ֲ��Ĵ���
#define HI3138_T_CIR_DIST_3         0x79    //T--�ྶ�ֲ��Ĵ���
#define HI3138_T_SNR_L              0x7A    //T--�����ָʾ��λ�Ĵ���
#define HI3138_T_SNR_H              0x7B    //T--�����ָʾ��λ�Ĵ���
#define HI3138_T_DOPPLER            0x7C    //T--������ָʾ�Ĵ���
#define HI3138_T_CEQ_ADDR_1D        0x7D    //T--TS�������ѡ��Ĵ���(bit6)
#define HI3138_T_CW_FREQ_L          0x80    //T--��Ƶ����Ƶ���λ�Ĵ���
#define HI3138_T_CW_FREQ_H          0x81    //T--��Ƶ����Ƶ���λ�Ĵ���
#define HI3138_T_CLK_ADC_L          0x85    //T--ADCʱ�ӵ�λ�Ĵ���
#define HI3138_T_CLK_ADC_M          0x86    //T--ADCʱ����λ�Ĵ���
#define HI3138_T_CLK_ADC_H          0x87    //T--ADCʱ�Ӹ�λ�Ĵ���
#define HI3138_T_ATV_STATE          0x88    //T--ͬƵ���ű�־�Ĵ���
#define HI3138_T_SMP_CTRL           0x89    //T--��Ƶ�����ɼ��Ĵ���
#define HI3138_T_ITER_CTRL          0x91    //T--�������ƼĴ���
#define HI3138_T_BER_CTRL           0x92    //T--ber���ƼĴ���
#define HI3138_T_AUTO_DLY           0x93    //T--�����л��Ĵ���
#define HI3138_T_ITER_NUM           0x94    //T--PRE������������Ĵ���
#define HI3138_T_ITER_NUM_POST      0x95    //T--POST������������Ĵ���
#define HI3138_T_FEC_BER_L          0x96    //T--ber��λ�Ĵ���
#define HI3138_T_FEC_BER_H          0x97    //T--ber��λ�Ĵ���
#define HI3138_T_FEC_FER_L          0x98    //T--fer��λ�Ĵ���
#define HI3138_T_FEC_FER_H          0x99    //T--fer��λ�Ĵ���
#define HI3138_T_SWITCH_DLY         0x9C    //T--���������л�ʱ�ӼĴ���
#define HI3138_T_T2_SUCCESS         0x9E    //T--T2����ɹ��Ĵ���
#define HI3138_T_OUTP_ISSY          0xA0    //T--issy���ƼĴ���
#define HI3138_T_OUTP_DCAP_SET      0xA1    //T--DATA PLP�������üĴ���
#define HI3138_T_OUTP_CCAP_SET      0xA2    //T--COMMON PLP�������üĴ���
#define HI3138_T_OUTP_PLL0          0xA3    //T--PLL���ƼĴ���
#define HI3138_T_OUTP_PLL1          0xA4    //T--PLL���ƼĴ���
#define HI3138_T_OUTP_PLL2          0xA5    //T--PLL���ƼĴ���
#define HI3138_T_OUTP_PLL3          0xA6    //T--PLL���ƼĴ���
#define HI3138_T_OUTP_PLL4          0xA7    //T--PLL���ƼĴ���
#define HI3138_T_OUTP_CLK_SET       0xA8    //T--���ʱ�����üĴ���
#define HI3138_T_OUTP_CLK_SETH      0xA9    //T--I2Cʱ�����üĴ���
#define HI3138_T_OUTP_CLK_SETL      0xAA    //T--PLL��ʼֵ���üĴ���
#define HI3138_T_OUTP_MODE_SET      0xAB    //T--���ģʽ���üĴ���
#define HI3138_T_OUTP_TS_MODE       0xAC    //T--TS���ģʽ���üĴ���
#define HI3138_T_OUTP_PKT_STA       0xAE    //T--TSͳ�ư������üĴ���
#define HI3138_T_OUTP_LIMIT_EN      0xAF    //T--�޷���ʹ�ܼĴ���
#define HI3138_T_PLP_CTRL           0xB0    //T--PLP���ƼĴ���
#define HI3138_T_PLP_ID0            0xB1    //T--Dataplp��żĴ���
#define HI3138_T_PLP_ID1            0xB2    //T--Commonplp��żĴ���
#define HI3138_T_TPS                0xB3    //T--�źŲ����Ĵ���
#define HI3138_T_STREAM_TYPE        0xB4    //T--��������������ָʾ�Ĵ���
#define HI3138_T_CODE_RATE_DVBT     0xB4    //T--DVB-T�������ʼĴ���
#define HI3138_T_TPS_DVBT           0xB5    //T--DVB-T�źŲ����Ĵ���
#define HI3138_T_PAPR_L1MOD         0xB5    //T--DVB-T2�źŲ����Ĵ���
#define HI3138_T_PP_VERSION         0xB8    //T--DVB-T2 PRE����Ĵ���
#define HI3138_T_NUM_T2_FRM         0xB9    //T--DVB-T2 PRE����Ĵ���
#define HI3138_T_LDATA_L            0xBA    //T--DVB-T2 PRE����Ĵ���
#define HI3138_T_LDATA_H            0xBB    //T--DVB-T2 PRE����Ĵ���
#define HI3138_T_NUM_PLP            0xBF    //T--DVB-T2 PRE����Ĵ���
#define HI3138_T_TMCC1              0xC0    //T--ISDB-T TMCC�Ĵ���
#define HI3138_T_TMCC2              0xC1    //T--ISDB-T TMCC�Ĵ���
#define HI3138_T_TMCC3              0xC2    //T--ISDB-T TMCC�Ĵ���
#define HI3138_T_TMCC4              0xC3    //T--ISDB-T TMCC�Ĵ���
#define HI3138_T_TMCC5              0xC4    //T--ISDB-T TMCC�Ĵ���
#define HI3138_T_TMCC6              0xC5    //T--ISDB-T TMCC�Ĵ���
#define HI3138_T_TMCC7              0xC6    //T--ISDB-T TMCC�Ĵ���
#define HI3138_T_PLP_ID             0xC6    //T--DVB-T2 POST����Ĵ���
#define HI3138_T_PLP_TYPE           0xC7    //T--DVB-T2 POST����Ĵ���
#define HI3138_T_PLP_GRP_ID         0xC8    //T--DVB-T2 POST����Ĵ���
#define HI3138_T_PLP_PARAM          0xC9    //T--DVB-T2 POST����Ĵ���

#define HI3138_S_MAN_RST_CTRL0      0x20    //S--��λ���ƼĴ���
#define HI3138_S_MAN_RST_CTRL1      0x21    //S--��λ����ʹ�ܼĴ���
#define HI3138_S_STATE_WAITS        0x22    //S--��ʱ��λ�Ĵ���
#define HI3138_S_CLK_DEMO_L         0x23    //S--���ʱ�ӵ�λ�Ĵ���
#define HI3138_S_CLK_DEMO_M         0x24    //S--���ʱ����λ�Ĵ���
#define HI3138_S_CLK_DEMO_H         0x25    //S--���ʱ�Ӹ�λ�Ĵ���
#define HI3138_S_CLK_FEC_L          0x26    //S--����ʱ�ӵ�λ�Ĵ���
#define HI3138_S_CLK_FEC_M          0x27    //S--����ʱ����λ�Ĵ���
#define HI3138_S_CLK_FEC_H          0x28    //S--����ʱ�Ӹ�λ�Ĵ���
#define HI3138_S_LOCK_TIME_L        0x29    //S--����ʱ���λ�Ĵ���
#define HI3138_S_LOCK_TIME_M        0x2A    //S--����ʱ����λ�Ĵ���
#define HI3138_S_LOCK_TIME_H        0x2B    //S--����ʱ���λ�Ĵ���
//#define HI3138_S_LOCK_FLAG        0x2C    //S--����ָʾ�Ĵ���
//#define HI3138_S_TUNER_SEL        0x2D    //S--tuner���ƼĴ���
//#define HI3138_S_RSTN_CTRL        0x2E    //S--�߼���λ�Ĵ���
#define HI3138_S_ILA_SEL            0x2F    //S--��������ѡ��Ĵ���
#define HI3138_S_AGC_SPEED_BOUND    0x30    //S--agc�����Ĵ���
#define HI3138_S_AGC_GOAL           0x31    //S--agc���ʼĴ���
#define HI3138_S_AGCOK_WAIT         0x32    //S--agc�ȴ��Ĵ���
#define HI3138_S_AGC_CTRL           0x33    //S--agc���ƼĴ���
#define HI3138_S_AGC_DC_I           0x34    //S--I·ֱ���Ĵ���
#define HI3138_S_AGC_DC_Q           0x35    //S--Q·ֱ���Ĵ���
#define HI3138_S_DAGC_CTRL          0x36    //S--����agc���ƼĴ���
//#define HI3138_S_AGC_CTRL_L       0x37    //S--agc���ʵ�λ�Ĵ���
//#define HI3138_S_AGC_CTRL_H       0x38    //S--agc���ʸ�λ�Ĵ���
#define HI3138_S_AMP_ERR_IIR        0x39    //S--�������Ĵ���
#define HI3138_S_PDM_CTRL_L         0x3A    //S--�ֶ�agc�����ֵ�λ�Ĵ���
#define HI3138_S_PDM_CTRL_H         0x3B    //S--�ֶ�agc�����ָ�λ�Ĵ���
#define HI3138_S_TR_CTRL1           0x40    //S--tr���ƼĴ���
#define HI3138_S_DAGC_STD           0x41    //S--dagc���ƼĴ���
#define HI3138_S_TR_MONITOR         0x43    //S--tr��ؼĴ���
#define HI3138_S_CNT_THRESH         0x44    //S--tr�ȴ�ʱ��Ĵ���
//#define HI3138_S_FS_L             0x46    //S--�����ʵ�λ�Ĵ���
//#define HI3138_S_FS_H             0x47    //S--�����ʸ�λ�Ĵ���
//#define HI3138_S_CENT_FREQ_L      0x48    //S--�ز�Ƶ�ʵ�λ�Ĵ���
//#define HI3138_S_CENT_FREQ_H      0x49    //S--�ز�Ƶ�ʸ�λ�Ĵ���
//#define HI3138_S_FS_OFFSET_FC_L   0x4C    //S--������ƫ���λ�Ĵ���
//#define HI3138_S_FS_OFFSET_FC_H   0x4D    //S--������ƫ���λ�Ĵ���
//#define HI3138_S_FREQ_OFFSET_FC_L 0x4E    //S--Ƶ��ƫ���λ�Ĵ���
//#define HI3138_S_FREQ_OFFSET_FC_H 0x4F    //S--Ƶ��ƫ���λ�Ĵ���
#define HI3138_S_PLH_SYNC_1         0x50    //S--֡ͬ�����ƼĴ���
#define HI3138_S_PLH_SYNC_2         0x51    //S--֡ͬ�����ƼĴ���
#define HI3138_S_CR_CTRL_SW         0x52    //S--cr���ƼĴ���
#define HI3138_S_SCAN_STEP_L        0x53    //S--ɨƵ�ٶȼĴ���
#define HI3138_S_SCAN_STEP_FB       0x54    //S--ɨƵ���ƼĴ���
#define HI3138_S_SCAN_ADJUST        0x55    //S--�Զ�ɨƵ�ٶȼĴ���
#define HI3138_S_CR_ZUNI_WAIT       0x56    //S--�ز����ƼĴ���
#define HI3138_S_CR_BW_ADJUST       0x57    //S--�ز�������ƼĴ���
#define HI3138_S_CR_BW_MAX          0x58    //S--�ز���������ƼĴ���
#define HI3138_S_CR_BW_SET          0x59    //S--�ز�������ƼĴ���
#define HI3138_S_CR_CN              0x5A    //S--�ز�CNֵ�Ĵ���
#define HI3138_S_CR_STATE           0x5B    //S--�ز�״̬�Ĵ���
#define HI3138_S_PLS_CODE           0x5C    //S--pls_code�Ĵ���
#define HI3138_S_FREQ_INV           0x5D    //S--Ƶ�׷�ת�Ĵ���
#define HI3138_S_CR_ZUNI_BW_L       0x5E    //S--�ز�����Ĵ���
#define HI3138_S_CR_ZUNI_BW_H       0x5F    //S--�ز�����Ĵ���
#define HI3138_S_SYNC_FREQ_L        0x60    //S--֡ͬ��Ƶ�ʼĴ���
#define HI3138_S_SYNC_FREQ_H        0x61    //S--֡ͬ��Ƶ�ʼĴ���
#define HI3138_S_SCAN_FREQ_L        0x62    //S--ɨƵƵ�ʼĴ���
#define HI3138_S_SCAN_FREQ_H        0x63    //S--ɨƵƵ�ʼĴ���
#define HI3138_S_FREQ_ACC_L         0x64    //S--�ز�Ƶ���������Ĵ���
#define HI3138_S_FREQ_ACC_H         0x65    //S--�ز�Ƶ���������Ĵ���
#define HI3138_S_TR_FREQ_FB_L       0x66    //S--�ز�Ƶ��tr�����Ĵ���
#define HI3138_S_TR_FREQ_FB_H       0x67    //S--�ز�Ƶ��tr�����Ĵ���
#define HI3138_S_CR_LOOP_DC_L       0x68    //S--�ز�PLL�����ּĴ���
#define HI3138_S_CR_LOOP_DC_H       0x69    //S--�ز�PLL�����ּĴ���
#define HI3138_S_EQU_CTRL           0x70    //S--������ƼĴ���
#define HI3138_S_LMS_STEP           0x71    //S--���ⲽ�����ƼĴ���
#define HI3138_S_CN_CTRL            0x75    //S--��������ͳ�ƿ��ƼĴ���
#define HI3138_S_EQU_TAP_REAL       0x76    //S--�����ͷʵ���Ĵ���
#define HI3138_S_EQU_TAP_IMAG       0x77    //S--�����ͷ�鲿�Ĵ���
#define HI3138_S_EQU_TAP_SEL        0x78    //S--��ͷѡ��Ĵ���
#define HI3138_S_XREG_INIT_LOW      0x7A    //S--������ƼĴ���
#define HI3138_S_XREG_INIT_MID      0x7B    //S--������ƼĴ���
#define HI3138_S_XREG_INIT_HI       0x7C    //S--������ƼĴ���
#define HI3138_S_RD_WR_TAP          0x7D    //S--��ͷ���ƼĴ���
//#define HI3138_S_NOISE_POW_L      0x7E    //S--�������ʵ�λ�Ĵ���
//#define HI3138_S_NOISE_POW_H      0x7F    //S--�������ʸ�λ�Ĵ���
#define HI3138_S_TS_PARALL_CTRL     0x80    //S--ts���ѡ��Ĵ���
#define HI3138_S_TS_10_SEL          0x81    //S--ts������ƼĴ���
#define HI3138_S_TS_32_SEL          0x82    //S--ts������ƼĴ���
#define HI3138_S_TS_54_SEL          0x83    //S--ts������ƼĴ���
#define HI3138_S_TS_76_SEL          0x84    //S--ts������ƼĴ���
#define HI3138_S_TS_98_SEL          0x85    //S--ts������ƼĴ���
#define HI3138_S_TS_CTRL0           0x86    //S--ts���ƼĴ���
#define HI3138_S_TS_CTRL3           0x87    //S--ts���ƼĴ���
#define HI3138_S_TS_CTRL4           0x88    //S--ts���ƼĴ���
#define HI3138_S_TS_CLK_DIV_F_L     0x89    //S--tsʱ�ӵ�λ�Ĵ���
#define HI3138_S_TS_CLK_DIV_F_H     0x8A    //S--tsʱ�ӵ�λ�Ĵ���
#define HI3138_S_ISI_SEL            0x8B    //S--isiѡ��Ĵ���
#define HI3138_S_MATTYPE            0x8C    //S--��id�Ĵ���
#define HI3138_S_ISI_NUM            0x8D    //S--�����Ĵ���,ԭ��ROLL_OFF
#define HI3138_S_CRC_ERR            0x8E    //S--crcУ��Ĵ���
#define HI3138_S_RST_WAIT           0x8F    //S--��λ�ȴ��Ĵ���
#define HI3138_S_BER_CTRL           0x92    //S--ber���ƼĴ���
#define HI3138_S_ITER_CLK_CTRL      0x94    //S--LDPC����ʱ���ſؼĴ���
#define HI3138_S_FEC_BER_L          0x96    //S--ber��λ�Ĵ���
#define HI3138_S_FEC_BER_H          0x97    //S--ber��λ�Ĵ���
#define HI3138_S_FEC_FER_L          0x98    //S--fer��λ�Ĵ���
#define HI3138_S_FEC_FER_H          0x99    //S--fer��λ�Ĵ���
#define HI3138_S_FEC_STATUS         0x9E    //S--FEC״̬�Ĵ���
#define HI3138_S_FS_SPAN            0xA1    //S--äɨ�����ʷ�Χ�Ĵ���
#define HI3138_S_AMP_MIN_FS         0xA7    //S--äɨ��ͷ����ʼĴ���
#define HI3138_S_CBS_CTRL_RDADDR    0xA8    //S--äɨ���ƼĴ���
//#define HI3138_S_CBS_FS_L         0xA9    //S--äɨ�����ʵ�λ�Ĵ���
//#define HI3138_S_CBS_FS_H         0xAA    //S--äɨ�����ʸ�λ�Ĵ���
//#define HI3138_S_CBS_FC_L         0xAB    //S--äɨƵƫ��λ�Ĵ���
//#define HI3138_S_CBS_FC_H         0xAC    //S--äɨƵƫ��λ�Ĵ���
//#define HI3138_S_CBS_FINISH       0xAD    //S--äɨ�����Ĵ���
//#define HI3138_S_CBS_RELIABILITY1 0xAE    //S--äɨ�ɿ��ȼĴ���
//#define HI3138_S_CBS_R2_NUM       0xAF    //S--äɨ�źŸ����Ĵ���
//#define HI3138_S_DSEC_ADDR        0xB0    //S--dsec��ַ�Ĵ���
//#define HI3138_S_DSEC_DATA        0xB1    //S--dsec���ݼĴ���
//#define HI3138_S_DSEC_RATIO_L     0xB2    //S--dsec��λƵ�ʼĴ���
//#define HI3138_S_DSEC_RATIO_H     0xB3    //S--dsec��λƵ�ʼĴ���
//#define HI3138_S_TX_CTRL1         0xB4    //S--dsec���Ϳ��ƼĴ���
#define HI3138_S_RX_CTRL1           0xB5    //S--dsec���տ��ƼĴ���
//#define HI3138_S_DSEC_EN          0xB7    //S--dsecʹ�ܼĴ���
//#define HI3138_S_RX_STATE         0xB8    //S--dsec����״̬�Ĵ���
//#define HI3138_S_INT_STATE        0xB9    //S--dsec״̬�Ĵ���
#define HI3138_S_DPUNC_CTRL0        0xE0    //S--��ɾ����ƼĴ���
#define HI3138_S_DPUNC_CTRL1        0xE1    //S--��ɾ����ƼĴ���
#define HI3138_S_PKT_SYNC_CTRL      0xE2    //S--��ͬ�����ƼĴ���
#define HI3138_S_SEAR_RESULT        0xE3    //S--������������Ĵ���
#define HI3138_S_ITER_CTRL          0xE6    //S--�������ƼĴ���

#define HI3138_C_MAN_RST_CTRL0      0x20    //C--��λ���ƼĴ���
#define HI3138_C_MAN_RST_CTRL1      0x21    //C--��λ���ƼĴ���
#define HI3138_C_DEMO_FREQ_L        0x23    //C--demoʱ�ӵ�λ�Ĵ���
#define HI3138_C_DEMO_FREQ_M        0x24    //C--demoʱ����λ�Ĵ���
#define HI3138_C_LOCK_TIME          0x25    //C--ϵͳ����ʱ��Ĵ���
#define HI3138_C_FEC_FREQ_L         0x26    //C--fecʱ�ӵ�λ�Ĵ���
#define HI3138_C_FEC_FREQ_M         0x27    //C--fecʱ����λ�Ĵ���
#define HI3138_C_AUTO_RST_CNT       0x28    //C--�Ը�λͳ�ƼĴ���
#define HI3138_C_CATCH_CTRL         0x2A    //C--cacth���ƼĴ���
#define HI3138_C_TOUT_CTRL          0x2B    //C--��ʱ���ƼĴ���
#define HI3138_C_LOCK_FLAG          0x2C    //C--ָʾ�Ĵ���
#define HI3138_C_TUNER_SEL          0x2D    //C--TUNER_I2Cת�����üĴ���
#define HI3138_C_RSTN_CTRL          0x2E    //C--��λ���ƼĴ���
#define HI3138_C_ILA_SEL            0x2F    //C--��������ѡ��Ĵ���
#define HI3138_C_AGC_SPEED_BOUND    0x30    //C--��������ѡ��Ĵ���
#define HI3138_C_AGC_GOAL           0x31    //C--agc���ʼĴ���
#define HI3138_C_AGCOK_WAIT         0x32    //C--agc�ȴ��Ĵ���
#define HI3138_C_AGC_CTRL           0x33    //C--agc���ƼĴ���
#define HI3138_C_AGC_DC_I           0x34    //C--I·ֱ���Ĵ���
#define HI3138_C_AGC_DC_Q           0x35    //C--Q·ֱ���Ĵ���
#define HI3138_C_DAGC_CTRL          0x36    //C--����agc���ƼĴ���
#define HI3138_C_AGC_CTRL_H         0x37    //C--agc���ʸ�λ�Ĵ���
#define HI3138_C_AGC_CTRL_L         0x38    //C--agc���ʵ�λ�Ĵ���
#define HI3138_C_AMP_ERR_IIR        0x39    //C--�������Ĵ���
#define HI3138_C_PDM_CTRL_H         0x3A    //C--�ֶ�agc�����ָ�λ�Ĵ���
#define HI3138_C_PDM_CTRL_L         0x3B    //C--�ֶ�agc�����ֵ�λ�Ĵ���
#define HI3138_C_USE_PWM            0x3C    //C--pwm���ƼĴ���
#define HI3138_C_DAGC_JIT_THRESH    0x40    //C--���ȶ���������޼Ĵ���
#define HI3138_C_SF_RMV_CTRL        0x41    //C--��Ƶ�������ƼĴ���
#define HI3138_C_DAGC_REF           0x42    //C--����AGC�ο����ȼĴ���
#define HI3138_C_SCAN_WAIT          0x43    //C--������äɨ���ƼĴ���
#define HI3138_C_FREQ_DEV_L         0x44    //C--�ز�����Ƶ��_�ز�ƫ���λ�Ĵ���
#define HI3138_C_FREQ_DEV_H         0x45    //C--�ز�����Ƶ��_�ز�ƫ���λ�Ĵ���
#define HI3138_C_FS_L               0x46    //C--�����ʵ�λ�Ĵ���
#define HI3138_C_FS_H               0x47    //C--�����ʸ�λ�Ĵ���
#define HI3138_C_TR_CR_CTRL         0x48    //C--��ʱ�ز����ƼĴ���
#define HI3138_C_TR_SCAN_CTRL       0x4A    //C--������äɨ���ƼĴ���
#define HI3138_C_FREQ_ADC_L         0x4B    //C--ADCʱ�ӵ�λ�Ĵ���
#define HI3138_C_FREQ_ADC_M         0x4C    //C--ADCʱ����λ�Ĵ���
#define HI3138_C_TR_LOOP_CTRL       0x4D    //C--��ʱ��·���ƼĴ���
#define HI3138_C_SF_SCAN_CTRL       0x4E    //C--��Ƶɨ����ƼĴ���
#define HI3138_C_EQU_CTRL           0x63    //C--���������ƼĴ���
#define HI3138_C_EQU_STEP_WAIT      0x64    //C--������������ȴ�ʱ��Ĵ���
#define HI3138_C_EQU_STATUS         0x66    //C--������״̬�Ĵ���
#define HI3138_C_NOISE_POW_L        0x6C    //C--�������ʵ�λ�Ĵ���
#define HI3138_C_NOISE_POW_H        0x6D    //C--�������ʸ�λ�Ĵ���
#define HI3138_C_PT_CTRL            0x6E    //C--��λ���ٿ��ƼĴ���
#define HI3138_C_PT_CTRL1           0x6F    //C--��λ���ٿ��ƼĴ���
#define HI3138_C_PT2_CR_CTRL        0x70    //C--�ز���·���ƼĴ���
#define HI3138_C_PLS_CTRL1          0x77    //C--�����������ƼĴ���
#define HI3138_C_PLS_CTRL2          0x78    //C--�����������ƼĴ���
#define HI3138_C_PLS_CTRL3          0x79    //C--�����������ƼĴ���
#define HI3138_C_QLLR_CTRL          0x90    //C--����LLR���ƼĴ���
#define HI3138_C_DEMAP_LOW_CTRL     0x91    //C--�߽�����LLR���ƼĴ���
#define HI3138_C_SYNC_CTRL          0x92    //C--��ͬ�����ƼĴ���
#define HI3138_C_ITLV_CW            0x94    //C--J.83B��֯ģʽ�Ĵ���
#define HI3138_C_ITLV_AUTO          0x9C    //C--J.83B��֯ģʽ���üĴ���
#define HI3138_C_OUTP_PLL_INI       0xB0    //C--TS����ʼƵ�����üĴ���
#define HI3138_C_OUTP_CAP_SET       0xB1    //C--OUTP�������üĴ���
#define HI3138_C_OUTP_PLLUP_FRE     0xB2    //C--TS����·����Ƶ�����üĴ���
#define HI3138_C_OUTP_PLL0          0xB3    //C--PLL���ƼĴ���
#define HI3138_C_OUTP_PLL1          0xB4    //C--PLL���ƼĴ���
#define HI3138_C_OUTP_PLL2          0xB5    //C--PLL���ƼĴ���
#define HI3138_C_OUTP_PLL3          0xB6    //C--PLL���ƼĴ���
#define HI3138_C_OUTP_PLL4          0xB7    //C--PLL���ƼĴ���
#define HI3138_C_OUTP_I2C_CLK0      0xB8    //C--I2Cʱ�����üĴ���
#define HI3138_C_OUTP_I2C_CLK1      0xB9    //C--I2Cʱ�����üĴ���
#define HI3138_C_OUTP_I2C_CLK2      0xBA    //C--I2Cʱ�����üĴ���
#define HI3138_C_OUTP_RAM_THRE      0xBB    //C--������ֵ�Ĵ���
#define HI3138_C_OUTP_TS_MODE       0xBC    //C--���ģʽ���ƼĴ���
#define HI3138_C_OUTP_SYNC_BYTE     0xBD    //C--ͬ�������üĴ���
#define HI3138_C_OUTP_PKT_SET       0xBE    //C--ͳ�ư������üĴ���
#define HI3138_C_OUTP_RAND          0xBF    //C--TS������żĴ���
#define HI3138_C_OUTP_TS_10_SEL     0xC0    //C--TS�˿�ѡ��Ĵ���
#define HI3138_C_OUTP_TS_32_SEL     0xC1    //C--TS�˿�ѡ��Ĵ���
#define HI3138_C_OUTP_TS_54_SEL     0xC2    //C--TS�˿�ѡ��Ĵ���
#define HI3138_C_OUTP_TS_76_SEL     0xC3    //C--TS�˿�ѡ��Ĵ���
#define HI3138_C_OUTP_TS_98_SEL     0xC4    //C--TS�˿�ѡ��Ĵ���
#define HI3138_C_OUTP_BER           0xC5    //C--�������ͳ�ƼĴ���
#define HI3138_C_OUTP_PKT_MODE      0xC6    //C--TS�����ģʽ�Ĵ���
#define HI3138_C_OUTP_NEAR_FUL      0xC7    //C--OUTP�����ӽ������üĴ���
#define HI3138_C_OUTP_SYS_CLK0      0xC8    //C--ϵͳʱ�����üĴ���
#define HI3138_C_OUTP_SYS_CLK1      0xC9    //C--ϵͳʱ�����üĴ���
#define HI3138_C_OUTP_PLL_CTRL      0xCA    //C--PLL���������üĴ���
#define HI3138_C_OUTP_BER_RES0      0xCB    //C--�������ͳ�ƽ���Ĵ���
#define HI3138_C_OUTP_BER_RES1      0xCC    //C--�������ͳ�ƽ���Ĵ���
#define HI3138_C_ERR_LMT_SET        0xCD    //C--���ͳ�ƿ��ƼĴ���
#define HI3138_C_ERR_PKT_L          0xCE    //C--�������λ�Ĵ���
#define HI3138_C_ERR_PKT_H          0xCF    //C--�������λ�Ĵ���


#define HI3138_IPIO_CINFIG(u32TunerPort) do{  \
    HI_U8 u8Temp = 0;\
    qam_read_byte(u32TunerPort, HI3138_I2C_CHN_SEL, &u8Temp);   \
    u8Temp &= ~(0x0F << 0); \
    u8Temp |= 3;    \
    qam_write_byte(u32TunerPort, HI3138_I2C_CHN_SEL, u8Temp);   \
    }while(0)

#define HI3138_ARRARY_SIZE(arraryName) (sizeof(arraryName)/sizeof(arraryName[0]))

#define HI3138_SELECT_ALLOCATION_PORT(u32TunerPort, arraryName, allocationIndex) \
    do { \
        for(allocationIndex = 0; allocationIndex < (HI3138_ARRARY_SIZE(arraryName)); allocationIndex++) \
        { \
            if((u32TunerPort == arraryName[allocationIndex].u32TunerPort) \
                && (HI_UNF_TUNER_SIG_TYPE_BUTT != arraryName[i].enHi3138SigType)) \
            { \
                break; \
            } \
        } \
        if(allocationIndex >= (HI3138_ARRARY_SIZE(arraryName))) \
        { \
            HI_ERR_TUNER("allocation port is not match.\n"); \
            return HI_FAILURE; \
        } \
    } while(0)


typedef enum hi3138_INNER_DEMOD_NUMBER
{
    HI3138_INNER_DEMOD0 = 0,
    HI3138_INNER_DEMOD1,
    HI3138_INNER_DEMOD_BUTT
}Hi3138_INNER_DEMOD_NUMBER;

typedef enum hi3138_LNB_POWER_SOURCE
{
    HI3138_LNB_POWER_BY_ADDR0 = 0,
    HI3138_LNB_POWER_BY_ADDR1,
    HI3138_LNB_POWER_BY_ADDR_BUTT
}Hi3138_LNB_POWER_SOURCE;

typedef struct hi3138_SIGNAL_INFO_ALLOCATION
{
    HI_U32 u32TunerPort;
    Hi3138_INNER_DEMOD_NUMBER enInnerDemodId;
    Hi3138_LNB_POWER_SOURCE enLNBSrc;
    HI_UNF_TUNER_SIG_TYPE_E enHi3138SigType;
    HI_UNF_TUNER_ADC_PORT_E enADCId;
    HI_UNF_TUNER_TS_OUTPUT_PORT_E enTSOutputId;
    HI_UNF_TUNER_IF_PATH_SEL_E enIFPath;
    HI_UNF_TUNER_I2C_TRANSMISSION_GATEWAY_E enI2CGateWaySel;
    HI_UNF_TUNER_SYNC_PIN_MUX_E               enSyncPin;
    HI_UNF_TUNER_OUPUT_MODE_E enTsType;
    HI_BOOL                     bTSCombFlag;
    HI_UNF_TUNER_TSOUT_SET_S stTSOut;
}Hi3138_SIGNAL_INFO_ALLOCATION;

typedef enum tagHI3138_C_LOCK_FLAG_E
{
    HI3138_C_AGC_LOCK_FLAG = 0,
    HI3138_C_TDP_LOCK_FLAG,
    HI3138_C_EQU_LOCK_FLAG,
    HI3138_C_SYNC_LOCK_FLAG,
    HI3138_C_FEC_LOCK_FLAG,
    HI3138_C_RESERVED_LOCK_1,
    HI3138_C_RESERVED_LOCK_2,
    HI3138_C_CR_SCAN_LOCK_FLAG
} HI3138_C_LOCK_FLAG_E;

HI_S32 hi3138_i2c_chn_sel(HI_U32 u32TunerPort);
HI_S32 hi3138_init(HI_U32 u32TunerPort, HI_U8 enI2cChannel, HI_UNF_TUNER_DEV_TYPE_E enTunerDevType);
HI_S32 hi3138_set_sat_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_SAT_ATTR_S *pstSatTunerAttr);
HI_S32 hi3138_set_ter_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_TER_ATTR_S *pstTerTunerAttr);
HI_S32 hi3138_set_cab_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_CAB_ATTR_S *pstCabTunerAttr);
HI_S32 hi3138_set_multi_mode_chip_attr(HI_U32 u32TunerPort,HI_UNF_TUNER_MULTI_MODE_CHIP_ATTR_S *enPortAttr);
HI_S32 hi3138_connect(HI_U32 u32TunerPort, TUNER_ACC_QAM_PARAMS_S *pstChannel);
HI_S32 hi3138_deinit(HI_VOID);
HI_VOID hi3138_connect_timeout(HI_U32 u32ConnectTimeout);
HI_S32 hi3138_set_funcmode(HI_U32 u32TunerPort, TUNER_FUNC_MODE_E enFuncMode);
HI_S32 hi3138_standby(HI_U32 u32TunerPort, HI_U32 u32Status);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif
