//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <semaphore.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <linux/miscdevice.h>
#include <asm/io.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <linux/module.h>
#include <linux/semaphore.h>

#include "hi_type.h"

#include "drv_i2c_ext.h"
#include "drv_gpioi2c_ext.h"
#include "drv_gpio_ext.h"
#include "hi_drv_gpioi2c.h"
#include "hi_debug.h"

#include "hi_drv_stat.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_proc.h"

#include "drv_tuner_ext.h"
#include "drv_tuner_ioctl.h"
#include "hi_drv_diseqc.h"
#include "drv_demod.h"

#include "hi_drv_i2c.h"
#include "hi_drv_gpio.h"
#include "hi_error_mpi.h"

#include "hi_type.h"
#include "drv_i2c_ext.h"
#include "hi_debug.h"
#include "hi_error_mpi.h"
#include "hi_drv_proc.h"
#include "hi_drv_sys.h"

#include "hi_type.h"
#include "hi_unf_i2c.h"
#include "drv_tuner_ext.h"
#include "drv_demod.h"

#include "MxLWare_HYDRA_CommonApi.h"
#include "MxLWare_HYDRA_OEM_Drv.h"
#include "MaxLinearDataTypes.h"
#include "MxLWare_FW_Download.h"
#include "MxLWare_HYDRA_DemodTunerApi.h"
#include "MxLWare_HYDRA_DeviceApi.h"
#include "MxLWare_HYDRA_TsMuxCtrlApi.h"
#include "MxLWare_HYDRA_OEM_Defines.h"

#define HYDRA_DEVICE_ID (0)



static oem_data_t stMXLOemData;
static HI_BOOL  s_Mxl541InitFlag = HI_FALSE;

HI_S32 mxl541_init(HI_U32 u32TunerPort)
{
    MXL_STATUS_E status;
    MXL_HYDRA_DEV_XTAL_T xtalParamPtr;
    MXL_HYDRA_VER_INFO_T  MXL541_DEVVERSION_INFO;
    MXL_BOOL_E tuner_status;
    HI_S32 wait_time = 10000;
    //HI_U8 enI2cChannel;
    struct timeval stStartTime, stEndTime,stDrvInit,stOverwriteDef,stXtal,stVerInfo,stPwrMode,stFWDL,stTunerEnable,stFreqOffset;
    long u64Total,u64DrvInit,u64OverWriteDef,u64Xtal,u64VerInfo,u64PwrMode,u64FWDL,u64TunerEnable,u64FreqOffset;

    if (s_Mxl541InitFlag)
    {
        HI_INFO_TUNER("\n\nMxl541 already inited!!!\n");
        return HI_SUCCESS;
    }
    do_gettimeofday(&stStartTime );

    //Init driver
    stMXLOemData.drvIndex = 0;
    stMXLOemData.channel = g_stTunerOps[u32TunerPort].enI2cChannel;
    stMXLOemData.i2cAddress = g_stTunerOps[u32TunerPort].u32DemodAddress;
    status = MxLWare_HYDRA_API_CfgDrvInit(HYDRA_DEVICE_ID, (void *)&stMXLOemData, MXL_HYDRA_DEVICE_541C);
    if (status == MXL_ALREADY_INITIALIZED)
    {
        //printk("\n\n\n\nEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n\n\n\n");
    }
    else if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Driver initialization FAILED\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }
    do_gettimeofday(&stDrvInit );

    //Overwrite default
    status = MxLWare_HYDRA_API_CfgDevOverwriteDefault(HYDRA_DEVICE_ID);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Overwrite default FAILED\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }
    do_gettimeofday(&stOverwriteDef );

    //Xtal
    xtalParamPtr.xtalFreq = MXL_HYDRA_XTAL_24_MHz;
    xtalParamPtr.xtalCap = 12;
    status = MxLWare_HYDRA_API_CfgDevXtal(HYDRA_DEVICE_ID, &xtalParamPtr, MXL_DISABLE);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Xtal FAILED\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }
    do_gettimeofday(&stXtal );

    //Dev version
    status = MxLWare_HYDRA_API_ReqDevVersionInfo(HYDRA_DEVICE_ID, &MXL541_DEVVERSION_INFO);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Req Dev Version FAILED\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }
    do_gettimeofday(&stVerInfo );
    //printk("chipId(mxl541c=%d):  %d\n", MXL_HYDRA_DEVICE_541C, MXL541_DEVVERSION_INFO.chipId);
    //printk("chipVer(mxl541c=%d):0x%x\n", MXL_HYDRA_DEVICE_541C, MXL541_DEVVERSION_INFO.chipVer);

    status = MxLWare_HYDRA_API_CfgDevPowerMode(HYDRA_DEVICE_ID, MXL_HYDRA_PWR_MODE_ACTIVE);
    if(MXL_SUCCESS!=status)
    {
        HI_ERR_TUNER("MxL_HYDRA_Lib_CfgDevPowerMode - Error (%d)\n", status);
        return HI_FAILURE;
    }
    do_gettimeofday(&stPwrMode );

    //Download firmware
    if (MXL541_DEVVERSION_INFO.firmwareDownloaded == MXL_FALSE)
    {
        status = mxl5xx_downloadFirmware(HYDRA_DEVICE_ID) ;
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("[HYDRA][%d] Download FW FAILED\n", HYDRA_DEVICE_ID);
            return HI_FAILURE;
        }
    }
    do_gettimeofday(&stFWDL );

    //Enable tuner
    status = MxLWare_HYDRA_API_CfgTunerEnable(HYDRA_DEVICE_ID, MXL_HYDRA_TUNER_ID_0, 1) ;
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Cfg enable tuner FAILED\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }

    do {
        MxLWare_HYDRA_OEM_SleepInMs(5);
        wait_time -= 5;

        status = MxLWare_HYDRA_API_ReqTunerEnableStatus(HYDRA_DEVICE_ID, MXL_HYDRA_TUNER_ID_0, &tuner_status);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("[HYDRA][%d] Req tuner status FAILED\n", HYDRA_DEVICE_ID);
            return HI_FAILURE;
        }
    }while ((wait_time > 0) && (tuner_status != MXL_ENABLE));
    do_gettimeofday(&stTunerEnable );

    if ((wait_time <= 0) || (tuner_status != MXL_ENABLE))
    {
        HI_ERR_TUNER("[HYDRA][%d] Enable tuner FAILED\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }

    //Demod search offset
    status = MxLWare_HYDRA_API_CfgDemodSearchFreqOffset(HYDRA_DEVICE_ID, MXL_HYDRA_DEMOD_ID_0, MXL_HYDRA_SEARCH_MAX_OFFSET);
    status |= MxLWare_HYDRA_API_CfgDemodSearchFreqOffset(HYDRA_DEVICE_ID, MXL_HYDRA_DEMOD_ID_1, MXL_HYDRA_SEARCH_MAX_OFFSET);
    status |= MxLWare_HYDRA_API_CfgDemodSearchFreqOffset(HYDRA_DEVICE_ID, MXL_HYDRA_DEMOD_ID_2, MXL_HYDRA_SEARCH_MAX_OFFSET);
    status |= MxLWare_HYDRA_API_CfgDemodSearchFreqOffset(HYDRA_DEVICE_ID, MXL_HYDRA_DEMOD_ID_3, MXL_HYDRA_SEARCH_MAX_OFFSET);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Cfg Demod search offset FAILED\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }
    do_gettimeofday(&stFreqOffset );

    status = MxLWare_HYDRA_API_CfgTSMuxMode(HYDRA_DEVICE_ID, MXL_HYDRA_TS_MUX_DISABLE);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Cfg TS mux mode type.\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }

    //Diseqc config
    status = MxLWare_HYDRA_API_CfgDevDiseqcFskOpMode(HYDRA_DEVICE_ID, MXL_HYDRA_AUX_CTRL_MODE_DISEQC);
    status |= MxLWare_HYDRA_API_CfgDiseqcOpMode(HYDRA_DEVICE_ID, MXL_HYDRA_DISEQC_ID_0, MXL_HYDRA_DISEQC_TONE_MODE, //MXL_HYDRA_DISEQC_ENVELOPE_MODE,
                                        MXL_HYDRA_DISEQC_2_X, MXL_HYDRA_DISEQC_CARRIER_FREQ_22KHZ);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Cfg Diseqc mode type.\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }
    do_gettimeofday(&stEndTime );
    u64Total = (stEndTime.tv_sec - stStartTime.tv_sec) * 1000 + (stEndTime.tv_usec - stStartTime.tv_usec) / 1000;
    u64DrvInit = (stDrvInit.tv_sec - stStartTime.tv_sec) * 1000 + (stDrvInit.tv_usec - stStartTime.tv_usec) / 1000;
    u64OverWriteDef = (stOverwriteDef.tv_sec - stDrvInit.tv_sec) * 1000 + (stOverwriteDef.tv_usec - stDrvInit.tv_usec) / 1000;
    u64Xtal = (stXtal.tv_sec - stOverwriteDef.tv_sec) * 1000 + (stXtal.tv_usec - stOverwriteDef.tv_usec) / 1000;
    u64VerInfo = (stVerInfo.tv_sec - stXtal.tv_sec) * 1000 + (stVerInfo.tv_usec - stXtal.tv_usec) / 1000;
    u64PwrMode = (stPwrMode.tv_sec - stVerInfo.tv_sec) * 1000 + (stPwrMode.tv_usec - stVerInfo.tv_usec) / 1000;
    u64FWDL = (stFWDL.tv_sec - stPwrMode.tv_sec) * 1000 + (stFWDL.tv_usec - stPwrMode.tv_usec) / 1000;
    u64TunerEnable = (stTunerEnable.tv_sec - stFWDL.tv_sec) * 1000 + (stTunerEnable.tv_usec - stFWDL.tv_usec) / 1000;
    u64FreqOffset = (stFreqOffset.tv_sec - stTunerEnable.tv_sec) * 1000 + (stFreqOffset.tv_usec - stTunerEnable.tv_usec) / 1000;
    HI_INFO_TUNER("\n##############\n");
    HI_INFO_TUNER("Total Time:%ldms.\n",u64Total);
    HI_INFO_TUNER("Drv init api time:%ldms.\n",u64DrvInit);
    HI_INFO_TUNER("Over write api time:%ldms.\n",u64OverWriteDef);
    HI_INFO_TUNER("Xtal api time:%ldms.\n",u64Xtal);
    HI_INFO_TUNER("Ver info api time:%ldms.\n",u64VerInfo);
    HI_INFO_TUNER("Power mode api time:%ldms.\n",u64PwrMode);
    HI_INFO_TUNER("Firmware download api time:%ldms.\n",u64FWDL);
    HI_INFO_TUNER("Tuner enable api time:%ldms.\n",u64TunerEnable);
    HI_INFO_TUNER("Freq offset api time:%ldms.\n",u64FreqOffset);
    HI_INFO_TUNER("##############\n");

    s_Mxl541InitFlag = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 mxl541_set_sat_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_SAT_ATTR_S *pstSatTunerAttr)
{
    return HI_SUCCESS;
}

HI_S32 mxl541_set_ts_type(HI_U32 u32TunerPort, HI_UNF_TUNER_OUPUT_MODE_E enTsType)
{
    MXL_STATUS_E status;
    MXL_HYDRA_MPEGOUT_PARAM_T mpeg_param;
    /*static int i = 0;

    if (i != 0)
        return HI_SUCCESS;
    i++;*/
    MxLWare_HYDRA_API_CfgTSOutDriveStrength(HYDRA_DEVICE_ID,MXL_HYDRA_TS_DRIVE_STRENGTH_2x );

    HI_INFO_TUNER("port %d, ts strength:%d.\n", u32TunerPort, MXL_HYDRA_TS_DRIVE_STRENGTH_2x);
    //串行输出。2路4线制时配置为 mpegClkType = MXL_HYDRA_MPEG_CLK_CONTINUOUS; mpegMode = MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE
    //          4路2线制时配置为 mpegClkType = MXL_HYDRA_MPEG_CLK_GAPPED;     mpegMode = MXL_HYDRA_MPEG_MODE_SERIAL_2_WIRE
    //maxMpegClkRate = 139; 最大时钟频率.    需要注意的是:mv420的所有时钟加起来不能超过450M。而mxl541的最大时钟频率104M之上还有就是139，而139*4 > 512，所以不能设置为139
    //由符号率得出TS速率的方法: 8psk 9/10  40MSym/s，速率是40 * 3 * 9/10 = 108.    8psk每个符号代表3个bit，QPSK每个符号代表2个bit，32APSK每个符号代表5个bit.
    //实际速率略小于算出来的速率，原因不知道。
    if (HI_UNF_TUNER_OUTPUT_MODE_SERIAL == enTsType)
    {
        mpeg_param.enable = MXL_ENABLE;
        mpeg_param.mpegClkType = MXL_HYDRA_MPEG_CLK_GAPPED;
        mpeg_param.mpegClkPol = MXL_HYDRA_MPEG_CLK_POSITIVE;//MXL_HYDRA_MPEG_CLK_NEGATIVE;
        mpeg_param.maxMpegClkRate = 139;
        mpeg_param.mpegClkPhase = MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_0_DEG;         // MPEG Clk phase
        mpeg_param.lsbOrMsbFirst = MXL_HYDRA_MPEG_SERIAL_MSB_1ST;               // LSB first or MSB first in TS transmission
        mpeg_param.mpegSyncPulseWidth = MXL_HYDRA_MPEG_SYNC_WIDTH_BIT;         // MPEG SYNC pulse width (1-bit or 1-byte)
        mpeg_param.mpegValidPol = MXL_HYDRA_MPEG_ACTIVE_HIGH;                   // MPEG VALID polarity
        //mpeg_param.mpegSyncPol = MXL_HYDRA_MPEG_ACTIVE_HIGH;                    // MPEG SYNC polarity
        mpeg_param.mpegMode = MXL_HYDRA_MPEG_MODE_SERIAL_2_WIRE;                // config 4/3/2-wire serial or parallel TS out
        mpeg_param.mpegErrorIndication = MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED;
    }
    else if (HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A == enTsType)  //并行输出模式
    {
        status = MxLWare_HYDRA_API_CfgTSMixMuxMode(HYDRA_DEVICE_ID, MXL_HYDRA_TS_GROUP_0_3, MXL_HYDRA_TS_MUX_4_TO_1);
        status |= MxLWare_HYDRA_API_CfgTSMixMuxMode(HYDRA_DEVICE_ID, MXL_HYDRA_TS_GROUP_4_7, MXL_HYDRA_TS_MUX_4_TO_1);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("[HYDRA][%d] Cfg TS Mix&Mux FAILED\n", HYDRA_DEVICE_ID);
            return HI_FAILURE;
        }

        //Ts out
        mpeg_param.enable = MXL_ENABLE;
        mpeg_param.lsbOrMsbFirst = MXL_HYDRA_MPEG_SERIAL_MSB_1ST;               // LSB first or MSB first in TS transmission
        mpeg_param.maxMpegClkRate = 104;
        mpeg_param.mpegClkType = MXL_HYDRA_MPEG_CLK_CONTINUOUS;
        mpeg_param.mpegClkPhase = MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_0_DEG;         // MPEG Clk phase
        mpeg_param.mpegClkPol = MXL_HYDRA_MPEG_CLK_POSITIVE;
        mpeg_param.mpegValidPol = MXL_HYDRA_MPEG_ACTIVE_HIGH;                   // MPEG VALID polarity
        mpeg_param.mpegSyncPol = MXL_HYDRA_MPEG_ACTIVE_HIGH;                    // MPEG SYNC polarity
        mpeg_param.mpegSyncPulseWidth = MXL_HYDRA_MPEG_SYNC_WIDTH_BYTE;         // MPEG SYNC pulse width (1-bit or 1-byte)
        mpeg_param.mpegMode = MXL_HYDRA_MPEG_MODE_PARALLEL;                     // config 4/3/2-wire serial or parallel TS out
        mpeg_param.mpegErrorIndication = MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED;
    }
    else
    {
        HI_ERR_TUNER("[HYDRA][%d] Unsupport TS output type.\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }
    HI_INFO_TUNER("TS CLOCK RATE %d.\n", mpeg_param.maxMpegClkRate);

    status = MxLWare_HYDRA_API_CfgMpegOutParams(HYDRA_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &mpeg_param) ;
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Cfg TS output type.\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }

    /*status = MxLWare_HYDRA_API_CfgTSErrorIndicationCtrl(HYDRA_DEVICE_ID, MXL_DISABLE);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Cfg Search offset FAILED\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }*/

    return HI_SUCCESS;
}

HI_S32 mxl541_set_ts_out(HI_U32 u32TunerPort, HI_UNF_TUNER_TSOUT_SET_S *pstTSOut)
{
    return HI_SUCCESS;
}

HI_S32 mxl541_set_lnb_out(HI_U32 u32TunerPort, TUNER_LNB_OUT_E enOut)
{
    return HI_SUCCESS;
}

HI_S32 mxl541_get_status(HI_U32 u32TunerPort, HI_UNF_TUNER_LOCK_STATUS_E *penTunerStatus)
{
    MXL_STATUS_E status;
    UINT8 allDemodLockPtr;


    status = MxLWare_HYDRA_API_ReqAllDemodLockStatus(HYDRA_DEVICE_ID, &allDemodLockPtr);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Req lock status FAILED\n", HYDRA_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }

    HI_INFO_TUNER("Demod lock status: 0x%x.\n", (HI_S32)allDemodLockPtr);

    if (allDemodLockPtr & ((UINT8)0x1 << u32TunerPort))
    {
        *penTunerStatus = HI_UNF_TUNER_SIGNAL_LOCKED;
    }
    else
    {
        *penTunerStatus = HI_UNF_TUNER_SIGNAL_DROPPED;
    }

    return HI_SUCCESS;
}

HI_S32 mxl541_connect(HI_U32 u32TunerPort, TUNER_ACC_QAM_PARAMS_S * pstChannel)
{
    MXL_STATUS_E status;
    MXL_HYDRA_TUNE_PARAMS_T channel_info;
    HI_S32 i = 0;
    HI_U32 u32ChkTim = 100;
    HI_UNF_TUNER_LOCK_STATUS_E enTunerStatus;
    HI_S32 s32Ret = HI_FAILURE;
    struct timeval stStartTime, stEndTime;
    long u64Total;

    do_gettimeofday(&stStartTime );
    HI_INFO_TUNER("freq %d, symbol %d.\n", pstChannel->u32Frequency, pstChannel->unSRBW.u32SymbolRate);
    //DVB-S2
    channel_info.standardMask  = MXL_HYDRA_DVBS2;
    channel_info.frequencyInHz = pstChannel->u32Frequency * 1000;
    channel_info.freqSearchRangeKHz = 10000;
    channel_info.symbolRateKSps  = pstChannel->unSRBW.u32SymbolRate / 1000;
    channel_info.spectrumInfo =  MXL_HYDRA_SPECTRUM_AUTO;
    if(channel_info.standardMask == MXL_HYDRA_DVBS2)
    {
        channel_info.params.paramsS2.fec = MXL_HYDRA_FEC_AUTO;
        channel_info.params.paramsS2.modulation = MXL_HYDRA_MOD_AUTO;
        channel_info.params.paramsS2.pilots = MXL_HYDRA_PILOTS_AUTO;
        channel_info.params.paramsS2.rollOff = MXL_HYDRA_ROLLOFF_AUTO;
    }
    else if(channel_info.standardMask == MXL_HYDRA_DVBS)
    {
        channel_info.params.paramsS.fec = MXL_HYDRA_FEC_AUTO;
        channel_info.params.paramsS.modulation = MXL_HYDRA_MOD_AUTO;
        channel_info.params.paramsS.rollOff = MXL_HYDRA_ROLLOFF_AUTO;
    }
    status = MxLWare_HYDRA_API_CfgDemodChanTune(HYDRA_DEVICE_ID, MXL_HYDRA_TUNER_ID_0, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &channel_info);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Chan Tune FAILED\n", u32TunerPort);
        return HI_FAILURE;
    }
    //Check lock status
    for(i = 0; i < u32ChkTim; i++)
    {
        s32Ret = mxl541_get_status(u32TunerPort, &enTunerStatus);
        if(s32Ret != HI_SUCCESS)
        {
            HI_ERR_TUNER("[HYDRA][%d] Get status failed: %d.\n", HYDRA_DEVICE_ID, i);
            return HI_FAILURE;
        }
        if (enTunerStatus == HI_UNF_TUNER_SIGNAL_LOCKED)
        {
            do_gettimeofday(&stEndTime );
            u64Total = (stEndTime.tv_sec - stStartTime.tv_sec) * 1000 + (stEndTime.tv_usec - stStartTime.tv_usec) / 1000;
            HI_INFO_TUNER("lock cost time:%ld.\n",u64Total);
            return HI_SUCCESS;
        }
        tuner_mdelay(20);
    }

    return HI_FAILURE;
}

HI_VOID mxl541_connect_timeout(HI_U32 u32ConnectTimeout)
{
    return;
}

HI_S32 mxl541_set_funcmode(HI_U32 u32TunerPort, TUNER_FUNC_MODE_E enFuncMode)
{
    return HI_SUCCESS;
}


HI_S32 mxl541_send_continuous_22K(HI_U32 u32TunerPort, HI_U32 u32Continuous22K)
{
    MXL_STATUS_E status;

    HI_INFO_TUNER("port %d, 22k %d.\n", u32TunerPort, u32Continuous22K);

    if (u32Continuous22K)
    {
        status = MxLWare_HYDRA_API_CfgDiseqcContinuousToneCtrl(HYDRA_DEVICE_ID, MXL_HYDRA_DISEQC_ID_0, MXL_TRUE);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("[HYDRA][%d] Cfg Continuous tone FAILED\n", u32TunerPort);
            return HI_FAILURE;
        }
    }
    else
    {
        status = MxLWare_HYDRA_API_CfgDiseqcContinuousToneCtrl(HYDRA_DEVICE_ID, MXL_HYDRA_DISEQC_ID_0, MXL_FALSE);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("[HYDRA][%d] Cfg Continuous tone FAILED\n", u32TunerPort);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 mxl541_send_tone(HI_U32 u32TunerPort, HI_U32 u32Tone)
{

    return HI_SUCCESS;
}

HI_S32 mxl541_DiSEqC_send_msg(HI_U32 u32TunerPort, HI_UNF_TUNER_DISEQC_SENDMSG_S *pstSendMsg)
{
    MXL_STATUS_E status;
    MXL_HYDRA_DISEQC_TX_MSG_T diseqcMsgPtr = {0};
    HI_U32 statusPtr = 0;
    HI_U32 u32TotalTime = 0;
    HI_U32 u32UsedTime = 0;

    HI_INFO_TUNER("port:%d.\n", u32TunerPort);

    diseqcMsgPtr.diseqcId = MXL_HYDRA_DISEQC_ID_0;
    diseqcMsgPtr.nbyte = pstSendMsg->u8Length;
    memcpy(diseqcMsgPtr.bufMsg, pstSendMsg->au8Msg, pstSendMsg->u8Length);
    diseqcMsgPtr.toneBurst = MXL_HYDRA_DISEQC_TONE_NONE;

    status = MxLWare_HYDRA_API_CfgDiseqcWrite(HYDRA_DEVICE_ID, &diseqcMsgPtr);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Cfg Diseqc write FAILED\n", u32TunerPort);
        return HI_FAILURE;
    }

    u32TotalTime = diseqcMsgPtr.nbyte * 14;
    u32UsedTime = 0;
    while(u32UsedTime < u32TotalTime)
    {
        status = MxLWare_HYDRA_API_ReqDiseqcStatus(HYDRA_DEVICE_ID, MXL_HYDRA_DISEQC_ID_0, &statusPtr);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("[HYDRA][%d] Req Diseqc status FAILED\n", u32TunerPort);
            return HI_FAILURE;
        }

        HI_INFO_TUNER("status %d, time %d.\n", statusPtr, u32UsedTime);
        if ((statusPtr & MXL_HYDRA_DISEQC_STATUS_TX_DONE) != 0)
        {
            HI_INFO_TUNER("Send OK.\n");
            return HI_SUCCESS;
        }

        MxLWare_HYDRA_OEM_SleepInMs(2);
        u32UsedTime += 2;
    }

    return HI_FAILURE;
}

HI_S32 mxl541_DiSEqC_recv_msg(HI_U32 u32TunerPort, HI_UNF_TUNER_DISEQC_RECVMSG_S *pstRecvMsg)
{
    MXL_STATUS_E status;
    MXL_HYDRA_DISEQC_RX_MSG_T diseqcMsgPtr = {0};
    //HI_U32 statusPtr = 0;
    //HI_U32 u32TotalTime = 60;
    //HI_U32 u32UsedTime = 0;
    //HI_S32 i = 0;

    //while(((statusPtr & MXL_HYDRA_DISEQC_STATUS_RX_DATA_AVAIL) == 0) && (u32UsedTime < u32TotalTime))
    //{
    //    status = MxLWare_HYDRA_API_ReqDiseqcStatus(HYDRA_DEVICE_ID, MXL_HYDRA_DISEQC_ID_0, &statusPtr);
    //    if (status != MXL_SUCCESS)
    //    {
    //        HI_ERR_TUNER("[HYDRA][%d] Req Diseqc status FAILED\n", u32TunerPort);
    //        return HI_FAILURE;
    //    }
    //
    //    printk("%s: status %d, time %d.\n", __func__, statusPtr, u32UsedTime);
    //
    //    MxLWare_HYDRA_OEM_SleepInMs(2);
    //    u32UsedTime += 2;
    //}

    status = MxLWare_HYDRA_API_ReqDiseqcRead(HYDRA_DEVICE_ID, MXL_HYDRA_DISEQC_ID_0, &diseqcMsgPtr);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Cfg Diseqc read FAILED\n", u32TunerPort);
        return HI_FAILURE;
    }

    HI_INFO_TUNER("DiseqcRead %d bytes.\n", diseqcMsgPtr.nbyte);
    //printk("0x%x\n", (HI_S32)(diseqcMsgPtr.bufMsg[0]));
    //printk("0x%x\n", (HI_S32)(diseqcMsgPtr.bufMsg[1]));
    //printk("0x%x\n", (HI_S32)(diseqcMsgPtr.bufMsg[2]));
    //printk("0x%x\n", (HI_S32)(diseqcMsgPtr.bufMsg[3]));
    //printk("0x%x\n", (HI_S32)(diseqcMsgPtr.bufMsg[4]));
    //printk("0x%x\n", (HI_S32)(diseqcMsgPtr.bufMsg[5]));
    //for (i = 0; i < MXL_HYDRA_DISEQC_MAX_PKT_SIZE; i++)
    //{
    //    printk("D0: %d: %d\n", i, diseqcMsgPtr.bufMsg[i]);
    //}

    //status = MxLWare_HYDRA_API_ReqDiseqcRead(HYDRA_DEVICE_ID, MXL_HYDRA_DISEQC_ID_1, &diseqcMsgPtr);
    //if (status != MXL_SUCCESS)
    //{
    //    HI_ERR_TUNER("[HYDRA][%d] Cfg Diseqc read FAILED\n", u32TunerPort);
    //    return HI_FAILURE;
    //}

    //printk("%s: %d bytes.\n", __func__, diseqcMsgPtr.nbyte);
    //for (i = 0; i < diseqcMsgPtr.nbyte; i++)
    //{
    //    printk("D1: %d: %d\n", i, diseqcMsgPtr.bufMsg[i]);
    //}

//    status = MxLWare_HYDRA_API_ReqDiseqcRead(HYDRA_DEVICE_ID, MXL_HYDRA_DISEQC_ID_2, &diseqcMsgPtr);
//    if (status != MXL_SUCCESS)
//    {
//        HI_ERR_TUNER("[HYDRA][%d] Cfg Diseqc read FAILED\n", u32TunerPort);
//        return HI_FAILURE;
//    }
//
//    printk("%s: %d bytes.\n", __func__, diseqcMsgPtr.nbyte);
//    for (i = 0; i < diseqcMsgPtr.nbyte; i++)
//    {
//        printk("D2: %d: %d\n", i, diseqcMsgPtr.bufMsg[i]);
//    }
//
//    status = MxLWare_HYDRA_API_ReqDiseqcRead(HYDRA_DEVICE_ID, MXL_HYDRA_DISEQC_ID_3, &diseqcMsgPtr);
//    if (status != MXL_SUCCESS)
//    {
//        HI_ERR_TUNER("[HYDRA][%d] Cfg Diseqc read FAILED\n", u32TunerPort);
//        return HI_FAILURE;
//    }

    //printk("%s: %d bytes.\n", __func__, diseqcMsgPtr.nbyte);
    //for (i = 0; i < diseqcMsgPtr.nbyte; i++)
    //{
    //    printk("D3: %d: %d\n", i, diseqcMsgPtr.bufMsg[i]);
    //}

    //diseqcMsgPtr.bufMsg[MXL_HYDRA_DISEQC_MAX_PKT_SIZE];

    return HI_SUCCESS;
}

HI_S32 mxl541_get_ber(HI_U32 u32TunerPort, HI_U32 * pu32BER)
{
    MXL_STATUS_E status;
    MXL_HYDRA_DEMOD_STATUS_T stDemodStatus;

    status = MxLWare_HYDRA_API_ReqDemodErrorCounters(HYDRA_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort,  &stDemodStatus);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Req Demod Error Count FAILED\n", HYDRA_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }

    if(MXL_HYDRA_DVBS2 == stDemodStatus.standardMask)
    {
        HI_INFO_TUNER("Signal:DVBS2.\n");
        pu32BER[0] = stDemodStatus.u.demodStatus_DVBS2.packetErrorCount;
        pu32BER[1] = stDemodStatus.u.demodStatus_DVBS2.totalPackets;
    }
    else if (MXL_HYDRA_DVBS == stDemodStatus.standardMask)
    {
        HI_INFO_TUNER("Signal:DVBS.\n");
        pu32BER[0] = stDemodStatus.u.demodStatus_DVBS.berCount_Iter1;
        pu32BER[1] = stDemodStatus.u.demodStatus_DVBS.berWindow_Iter1;
    }

    //ErrorConuters not clear immediately after call this function, it seems 100ms-200ms later!!
    status = MxLWare_HYDRA_API_CfgClearDemodErrorCounters(HYDRA_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Clear Demod Error Count FAILED\n", HYDRA_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 mxl541_get_snr(HI_U32 u32TunerPort, HI_U32 * pu32SNR)
{
    MXL_STATUS_E status;
    SINT16 snrPtr;

    status = MxLWare_HYDRA_API_ReqDemodSNR(HYDRA_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &snrPtr);

    *pu32SNR = (HI_U32)snrPtr;
    HI_INFO_TUNER("Snr %d.\n", snrPtr);

    return HI_SUCCESS;
}

HI_S32 mxl541_get_signal_strength(HI_U32 u32TunerPort, HI_U32 *pu32strength)
{
    MXL_STATUS_E status;
    SINT32 inputPwrLevelPtr;

    status = MxLWare_HYDRA_API_ReqDemodRxPowerLevel(HYDRA_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &inputPwrLevelPtr);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Req Demod Rx Power Level FAILED\n", HYDRA_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }

    HI_INFO_TUNER("inputPwrLevelPtr %d.\n", inputPwrLevelPtr);
    pu32strength[1] = (HI_U32)(107+inputPwrLevelPtr / 100) ;

    return HI_SUCCESS;
}

static HI_VOID mxl541_transvert_fec(MXL_HYDRA_FEC_E fec, HI_UNF_TUNER_FE_FECRATE_E *penFECRate)
{
    switch (fec)
    {
        default:
        case MXL_HYDRA_FEC_AUTO:
            *penFECRate = HI_UNF_TUNER_FE_FEC_AUTO;
            break;
        case MXL_HYDRA_FEC_1_2:
            *penFECRate = HI_UNF_TUNER_FE_FEC_1_2;
            break;
        case MXL_HYDRA_FEC_3_5:
            *penFECRate = HI_UNF_TUNER_FE_FEC_3_5;
            break;
        case MXL_HYDRA_FEC_2_3:
            *penFECRate = HI_UNF_TUNER_FE_FEC_2_3;
            break;
        case MXL_HYDRA_FEC_3_4:
            *penFECRate = HI_UNF_TUNER_FE_FEC_3_4;
            break;
        case MXL_HYDRA_FEC_4_5:
            *penFECRate = HI_UNF_TUNER_FE_FEC_4_5;
            break;
        case MXL_HYDRA_FEC_5_6:
            *penFECRate = HI_UNF_TUNER_FE_FEC_5_6;
            break;
        case MXL_HYDRA_FEC_6_7:
            *penFECRate = HI_UNF_TUNER_FE_FEC_6_7;
            break;
        case MXL_HYDRA_FEC_7_8:
            *penFECRate = HI_UNF_TUNER_FE_FEC_7_8;
            break;
        case MXL_HYDRA_FEC_8_9:
            *penFECRate = HI_UNF_TUNER_FE_FEC_8_9;
            break;
        case MXL_HYDRA_FEC_9_10:
            *penFECRate = HI_UNF_TUNER_FE_FEC_9_10;
            break;
    }

    return;
}

static HI_VOID mxl541_transvert_mod(MXL_HYDRA_MODULATION_E modulation, HI_UNF_MODULATION_TYPE_E *penModType)
{
    switch (modulation)
    {
        default:
        case MXL_HYDRA_MOD_AUTO:
            *penModType = HI_UNF_MOD_TYPE_DEFAULT;
            break;
        case MXL_HYDRA_MOD_QPSK:
            *penModType = HI_UNF_MOD_TYPE_QPSK;
            break;
        case MXL_HYDRA_MOD_8PSK:
            *penModType = HI_UNF_MOD_TYPE_8PSK;
            break;
    }

    return;
}

HI_S32 mxl541_get_signal_info(HI_U32 u32TunerPort, HI_UNF_TUNER_SIGNALINFO_S *pstInfo)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_UNF_TUNER_LOCK_STATUS_E enTunerStatus;
    MXL_HYDRA_TUNE_PARAMS_T demodTuneParamsPtr = {0};
    MXL_STATUS_E status;


    s32Ret = mxl541_get_status(u32TunerPort, &enTunerStatus);
    if(s32Ret != HI_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Get status failed.\n", HYDRA_DEVICE_ID);
        return HI_FAILURE;
    }
    if (enTunerStatus != HI_UNF_TUNER_SIGNAL_LOCKED)
    {
        HI_ERR_TUNER("Signal drop!\n");
        return HI_FAILURE;
    }

    pstInfo->enSigType = HI_UNF_TUNER_SIG_TYPE_SAT;

    pstInfo->unSignalInfo.stSat.enSATType = HI_UNF_TUNER_FE_BUTT;
    pstInfo->unSignalInfo.stSat.enModType = HI_UNF_MOD_TYPE_BUTT;
    pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FECRATE_BUTT;

    status = MxLWare_HYDRA_API_ReqDemodChanParams(HYDRA_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &demodTuneParamsPtr);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Req Demod Params FAILED\n", HYDRA_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }
    HI_INFO_TUNER("stand %d, freq %dHz, Search %d, Symb %dKSyps, Spec %d.\n",  demodTuneParamsPtr.standardMask, demodTuneParamsPtr.frequencyInHz,
        demodTuneParamsPtr.freqSearchRangeKHz, demodTuneParamsPtr.symbolRateKSps, demodTuneParamsPtr.spectrumInfo);

    pstInfo->unSignalInfo.stSat.u32Freq = demodTuneParamsPtr.frequencyInHz / 1000;
    pstInfo->unSignalInfo.stSat.u32SymbolRate = demodTuneParamsPtr.symbolRateKSps * 1000;

    if (demodTuneParamsPtr.standardMask == MXL_HYDRA_DVBS)
    {
        HI_INFO_TUNER("S: fec %d, modulation %d, rollOff %d.\n", demodTuneParamsPtr.params.paramsS.fec,
                demodTuneParamsPtr.params.paramsS.modulation, demodTuneParamsPtr.params.paramsS.rollOff);

        pstInfo->unSignalInfo.stSat.enSATType = HI_UNF_TUNER_FE_DVBS;

        mxl541_transvert_fec(demodTuneParamsPtr.params.paramsS.fec, &pstInfo->unSignalInfo.stSat.enFECRate);
        mxl541_transvert_mod(demodTuneParamsPtr.params.paramsS.modulation, &pstInfo->unSignalInfo.stSat.enModType);
    }
    else if (demodTuneParamsPtr.standardMask == MXL_HYDRA_DVBS2)
    {
        HI_INFO_TUNER("S2: fec %d, modulation %d, pilots %d, rollOff %d.\n", demodTuneParamsPtr.params.paramsS2.fec,
            demodTuneParamsPtr.params.paramsS2.modulation, demodTuneParamsPtr.params.paramsS2.pilots, demodTuneParamsPtr.params.paramsS2.rollOff);

        pstInfo->unSignalInfo.stSat.enSATType = HI_UNF_TUNER_FE_DVBS2;

        mxl541_transvert_fec(demodTuneParamsPtr.params.paramsS2.fec, &pstInfo->unSignalInfo.stSat.enFECRate);
        mxl541_transvert_mod(demodTuneParamsPtr.params.paramsS2.modulation, &pstInfo->unSignalInfo.stSat.enModType);
    }

    return HI_SUCCESS;
}

HI_S32 mxl541_get_powerspecdata(HI_U32 u32TunerPort, HI_U32 u32freqStartInHz,HI_U32 u32freqStepInHz,HI_U32 u32numOfFreqSteps,HI_S16 *ps16powerData)
{
    MXL_STATUS_E status;
    MXL_HYDRA_SPECTRUM_ERROR_CODE_E spectrumReadbackStatusPtr;

    status = MxLWare_HYDRA_API_ReqTunerPowerSpectrum(HYDRA_DEVICE_ID, MXL_HYDRA_TUNER_ID_0, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, u32freqStartInHz,
                                                      u32numOfFreqSteps, ps16powerData, &spectrumReadbackStatusPtr);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Req Tuner Power Spectrum FAILED\n", HYDRA_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 mxl541_get_freq_symb_offset(HI_U32 u32TunerPort, HI_U32 *pu32Freq, HI_U32 *pu32Symb)
{
    MXL_STATUS_E status;
    MXL_HYDRA_DEMOD_SIG_OFFSET_INFO_T demodSigOffsetInfoPtr = {0};


    status = MxLWare_HYDRA_API_ReqDemodSignalOffsetInfo(HYDRA_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &demodSigOffsetInfoPtr);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Req Demod Signal Offset FAILED\n", HYDRA_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }

    *pu32Freq = demodSigOffsetInfoPtr.carrierOffsetInHz / 1000;
    *pu32Symb = demodSigOffsetInfoPtr.symbolOffsetInSymbol;

    HI_INFO_TUNER("freq %d, symb %d.\n", demodSigOffsetInfoPtr.carrierOffsetInHz, demodSigOffsetInfoPtr.symbolOffsetInSymbol);
    return HI_SUCCESS;
}

HI_S32 mxl541_standby(HI_U32 u32TunerPort, HI_U32 u32Standby)
{
    MXL_STATUS_E status;
    MXL_HYDRA_PWR_MODE_E pwrMode = (MXL_HYDRA_PWR_MODE_E)u32Standby;


    status = MxLWare_HYDRA_API_CfgDevPowerMode(HYDRA_DEVICE_ID, pwrMode);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Cfg Dev Power Mode FAILED\n", HYDRA_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 mxl541_deinit(HI_VOID)
{
    s_Mxl541InitFlag = HI_FALSE;
    return HI_SUCCESS;
}

