/*******************************************************************************
 *
 * FILE NAME          : example254.c
 *
 * AUTHOR             : Mariusz Murawski
 *
 * DATE CREATED       : 07/15/2012
 *
 * DESCRIPTION        : Example code of MxL_HRCLS MxLWare API
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/


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
#include <linux/semaphore.h>

//hisilicon
#include "hi_type.h"

#include "hi_drv_i2c.h"
#include "hi_drv_gpio.h"
#include "hi_debug.h"
#include "hi_drv_proc.h"
#include "hi_drv_tuner.h"
#include "drv_demod.h"
#include "hi_kernel_adapt.h"

//mxl582
#include "MaxLinearDataTypes.h"
#include "MxLWare_HYDRA_OEM_Defines.h"
#include "MxLWare_HYDRA_CommonApi.h"
#include "MxLWare_HYDRA_DeviceApi.h"

#define     MXL_HYDRA_DEMOD_MAX     8
#define     MXL582_DEVICE_ID        0
#define     MXL582_TS_DRIVE_STRENGTH            MXL_HYDRA_TS_DRIVE_STRENGTH_2x

//struct semaphore mxl582_sem;
static oem_data_t stOemData;
static HI_BOOL  s_Mxl582InitFlag = HI_FALSE;

HI_S32 mxl582_init(HI_U32 u32TunerPort, HI_U8 enI2cChannel, HI_UNF_TUNER_DEV_TYPE_E enTunerDevType)
{
    MXL_STATUS_E status = MXL_SUCCESS;
    MXL_HYDRA_DEV_XTAL_T xtalCfg;
    MXL_HYDRA_VER_INFO_T versionInfo;
    MXL_HYDRA_INTR_CFG_T intrCfg;
    UINT32 intrMask = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        HI_ERR_TUNER("Bad u32TunerPort\n");
        return HI_FAILURE;
    }

    //HI_INIT_MUTEX(&mxl582_sem);
    //status = down_interruptible(&mxl582_sem);
    if(s_Mxl582InitFlag)
    {
        HI_INFO_TUNER("\n\nMxl582 already inited!!!\n");
        return HI_SUCCESS;
    }

    /* i2c config */
    stOemData.i2cAddress = g_stTunerOps[u32TunerPort].u32DemodAddress;
    stOemData.channel = enI2cChannel;
    
    // Init driver context
    status = MxLWare_HYDRA_API_CfgDrvInit(MXL582_DEVICE_ID, &stOemData, MXL_HYDRA_DEVICE_582C);
    if(MXL_SUCCESS != status)
    {
        HI_INFO_TUNER("MxLWare_HYDRA_API_CfgDrvInit fail,status:%d\n",status);
        if(MXL_ALREADY_INITIALIZED == status)
            return HI_SUCCESS;
        else
            return HI_FAILURE;
    }

    //overwrite default
    status = MxLWare_HYDRA_API_CfgDevOverwriteDefault(MXL582_DEVICE_ID);
    if(MXL_SUCCESS != status)
    {
        HI_ERR_TUNER("MxLWare_HYDRA_API_CfgDevOverwriteDefault fail,status:%d\n",status);
        return HI_FAILURE;
    }
    
    // Config XTAL
    xtalCfg.xtalFreq = MXL_HYDRA_XTAL_24_MHz;
    xtalCfg.xtalCap = 12;
    status = MxLWare_HYDRA_API_CfgDevXtal(MXL582_DEVICE_ID, &xtalCfg, MXL_DISABLE);
    if(MXL_SUCCESS != status)
    {
        HI_ERR_TUNER("MxLWare_HYDRA_API_CfgDevXtal fail,status:%d\n",status);
        return HI_FAILURE;
    }


    // Download firmware only if firmware is not active/running.
    status = mxl5xx_downloadFirmware(MXL582_DEVICE_ID);
    if(MXL_SUCCESS != status)
    {
        HI_ERR_TUNER("mxl582_downloadFirmware fail,status:%d\n",status);
        return HI_FAILURE;
    }

    // Get device version info
    status = MxLWare_HYDRA_API_ReqDevVersionInfo(MXL582_DEVICE_ID, &versionInfo);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_ReqDevVersionInfo - Error (%d)\n", status);
        return status;
    }
    else
    {
        HI_INFO_TUNER("Firmware Version  : %d.%d.%d.%d\n", versionInfo.firmwareVer[0],
                            versionInfo.firmwareVer[1],
                            versionInfo.firmwareVer[2],
                            versionInfo.firmwareVer[3]);

        HI_INFO_TUNER("MxLWare Version   : %d.%d.%d.%d\n", versionInfo.mxlWareVer[0],
                        versionInfo.mxlWareVer[1],
                        versionInfo.mxlWareVer[2],
                        versionInfo.mxlWareVer[3]);
    }

    // Configure device interrupts
    intrCfg.intrDurationInNanoSecs = 10000; //10 ms
    intrCfg.intrType = HYDRA_HOST_INTR_TYPE_LEVEL_POSITIVE; // Level trigger
    intrMask =  MXL_HYDRA_INTR_EN |
                MXL_HYDRA_INTR_DMD_FEC_LOCK_0 |
                MXL_HYDRA_INTR_DMD_FEC_LOCK_1 |
                MXL_HYDRA_INTR_DMD_FEC_LOCK_2 |
                MXL_HYDRA_INTR_DMD_FEC_LOCK_3 |
                MXL_HYDRA_INTR_DMD_FEC_LOCK_4 |
                MXL_HYDRA_INTR_DMD_FEC_LOCK_5 |
                MXL_HYDRA_INTR_DMD_FEC_LOCK_6 |
                MXL_HYDRA_INTR_DMD_FEC_LOCK_7;
    // Enable INT's for DiSEqC
    intrMask |= MXL_HYDRA_INTR_DISEQC_0;
    intrMask |= MXL_HYDRA_INTR_DISEQC_1;
    intrMask |= MXL_HYDRA_INTR_DISEQC_2;
    intrMask |= MXL_HYDRA_INTR_DISEQC_3;
    // Configure INT's
    status = MxLWare_HYDRA_API_CfgDevInterrupt(MXL582_DEVICE_ID, intrCfg, intrMask);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgDevInterrupt - Error (%d)\n", status);
        return status;
    }

    //Select either DiSEqC or FSK - only one interface will be avilable either FSK or DiSEqC
    status = MxLWare_HYDRA_API_CfgDevDiseqcFskOpMode(MXL582_DEVICE_ID, MXL_HYDRA_AUX_CTRL_MODE_DISEQC);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgDevDiseqcFskOpMode - Error (%d)\n", status);
        return status;
    }

    // Configure DISEQC operating mode - Only 22 KHz carrier frequency is supported.
    status = MxLWare_HYDRA_API_CfgDiseqcOpMode(MXL582_DEVICE_ID, 
                                                    MXL_HYDRA_DISEQC_ID_0,
                                                    MXL_HYDRA_DISEQC_ENVELOPE_MODE,
                                                    MXL_HYDRA_DISEQC_1_X,
                                                    MXL_HYDRA_DISEQC_CARRIER_FREQ_22KHZ);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgDevDiseqcFskOpMode - Error (%d)\n", status);
        return status;
    }
    status = MxLWare_HYDRA_API_CfgDiseqcOpMode(MXL582_DEVICE_ID, 
                                                    MXL_HYDRA_DISEQC_ID_1,
                                                    MXL_HYDRA_DISEQC_ENVELOPE_MODE,
                                                    MXL_HYDRA_DISEQC_1_X,
                                                    MXL_HYDRA_DISEQC_CARRIER_FREQ_22KHZ);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgDevDiseqcFskOpMode - Error (%d)\n", status);
        return status;
    }

    // Config TS MUX mode - Disable TS MUX feature
    status = MxLWare_HYDRA_API_CfgTSMuxMode(MXL582_DEVICE_ID, MXL_HYDRA_TS_MUX_DISABLE);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgTSMuxMode - Error (%d)\n", status);
        return status;
    }

    status = MxLWare_HYDRA_API_CfgTSOutDriveStrength(MXL582_DEVICE_ID, MXL582_TS_DRIVE_STRENGTH);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgTSOutDriveStrength - Error (%d)\n", status);
        return status;
    }

    //up(&mxl582_sem);
    s_Mxl582InitFlag = HI_TRUE;

    return status;
}

HI_S32 mxl582_set_sat_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_SAT_ATTR_S *pstSatTunerAttr)
{
    return HI_SUCCESS;
}

HI_S32 mxl582_connect(HI_U32 u32TunerPort, TUNER_ACC_QAM_PARAMS_S *pstChannel)
{
    MXL_STATUS_E mxlStatus = 0;
    MXL_HYDRA_TUNE_PARAMS_T chanTuneParams;
    MXL_HYDRA_DEMOD_SCRAMBLE_INFO_T demodScramblingCode;
    MXL_HYDRA_BCAST_STD_E std = MXL_HYDRA_DVBS2;
    MXL_HYDRA_TUNER_ID_E stTunerId;

    if(u32TunerPort >= TUNER_NUM)
    {
       HI_ERR_TUNER( "u32TunerPort(%d) goes over the top(%d) \n",u32TunerPort,TUNER_NUM);
       return HI_FAILURE;
    }
     
    //mxlStatus = down_interruptible(&mxl582_sem);

    // Channel tune
    // Common parameters for DVB-S2, DVB-S & DSS modes
    chanTuneParams.standardMask        = std;
    chanTuneParams.frequencyInHz       = pstChannel->u32Frequency*1000;
    chanTuneParams.freqSearchRangeKHz  = 5000;// 5MHz
    chanTuneParams.symbolRateKSps      = pstChannel->unSRBW.u32SymbolRate/1000;
    chanTuneParams.spectrumInfo        = MXL_HYDRA_SPECTRUM_AUTO;
    if(u32TunerPort < TUNER_NUM/2)
        stTunerId = MXL_HYDRA_TUNER_ID_0;
    else
        stTunerId = MXL_HYDRA_TUNER_ID_1;

    // parameters specific to standard
    switch(chanTuneParams.standardMask)
    {
        default:
        case MXL_HYDRA_DVBS2:
            // DVB-S2 specific parameters
            chanTuneParams.params.paramsS2.fec        = MXL_HYDRA_FEC_AUTO;
            chanTuneParams.params.paramsS2.modulation = MXL_HYDRA_MOD_AUTO;
            chanTuneParams.params.paramsS2.pilots     = MXL_HYDRA_PILOTS_AUTO;
            chanTuneParams.params.paramsS2.rollOff    = MXL_HYDRA_ROLLOFF_AUTO;

            // For DVB-S2 standard program default scrambling code
            demodScramblingCode.scrambleCode = 0x01;
            demodScramblingCode.scrambleSequence[0] = 0x00;
            demodScramblingCode.scrambleSequence[1] = 0x00;
            demodScramblingCode.scrambleSequence[2] = 0x00;
            demodScramblingCode.scrambleSequence[3] = 0x00;
            demodScramblingCode.scrambleSequence[4] = 0x00;
            demodScramblingCode.scrambleSequence[5] = 0x00;
            demodScramblingCode.scrambleSequence[6] = 0x00;
            demodScramblingCode.scrambleSequence[7] = 0x00;
            demodScramblingCode.scrambleSequence[8] = 0x00;
            demodScramblingCode.scrambleSequence[9] = 0x00;
            demodScramblingCode.scrambleSequence[10] = 0x00;
            demodScramblingCode.scrambleSequence[11] = 0x00;

            // program default scramble code
            mxlStatus = MxLWare_HYDRA_API_CfgDemodScrambleCode(MXL582_DEVICE_ID,
                                                                (MXL_HYDRA_DEMOD_ID_E)u32TunerPort,
                                                                &demodScramblingCode);

            break;

        case MXL_HYDRA_DVBS:
            // DVB-S specific parameters
            chanTuneParams.params.paramsS.fec        = MXL_HYDRA_FEC_AUTO;
            chanTuneParams.params.paramsS.modulation = MXL_HYDRA_MOD_AUTO;
            chanTuneParams.params.paramsS.rollOff    = MXL_HYDRA_ROLLOFF_AUTO;
            break;

        case MXL_HYDRA_DSS:
            // DSS specific parameters
            chanTuneParams.params.paramsDSS.fec        = MXL_HYDRA_FEC_1_2;
            break;
    }

    // channe tune
    mxlStatus = MxLWare_HYDRA_API_CfgDemodChanTune(MXL582_DEVICE_ID,
                                                    stTunerId,
                                                    (MXL_HYDRA_DEMOD_ID_E)u32TunerPort,
                                                    &chanTuneParams);
    if (mxlStatus != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgDemodChanTune for (%d) - Error (%d)\n", u32TunerPort, mxlStatus);
        return HI_FAILURE;
    }
    else
        HI_INFO_TUNER ("Done!, MxLWare_HYDRA_API_CfgDemodChanTune for (%d) \n", u32TunerPort);

    //up(&mxl582_sem);
    return HI_SUCCESS;
}

  
HI_S32 mxl582_get_status (HI_U32 u32TunerPort, HI_UNF_TUNER_LOCK_STATUS_E  *penTunerStatus)
{
    MXL_HYDRA_DEMOD_LOCK_T   demodLock;
    
    HI_TUNER_CHECKPOINTER( penTunerStatus);
    /* Check tuner port and init. */
    if (u32TunerPort >= TUNER_NUM)
    {
      HI_ERR_TUNER("Bad u32TunerPort\n");
      return HI_FAILURE;
    }

    // Check for Demod lock & status
    MxLWare_HYDRA_API_ReqDemodLockStatus(MXL582_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &demodLock);

    if (demodLock.fecLock == MXL_TRUE)
    {
        *penTunerStatus = HI_UNF_TUNER_SIGNAL_LOCKED;
    }
    else
    {
        *penTunerStatus = HI_UNF_TUNER_SIGNAL_DROPPED;
    }
    
    return HI_SUCCESS;
}

HI_S32 mxl582_get_signal_strength(HI_U32 u32TunerPort, HI_U32 *pu32SignalStrength)
{
    MXL_STATUS_E status;
    SINT32 inputPwrLevelPtr;

    HI_TUNER_CHECKPOINTER(pu32SignalStrength);

    status = MxLWare_HYDRA_API_ReqDemodRxPowerLevel(MXL582_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &inputPwrLevelPtr);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Req Demod Rx Power Level FAILED\n", MXL582_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }

    HI_INFO_TUNER("inputPwrLevelPtr %d.\n", inputPwrLevelPtr);
    pu32SignalStrength[1] = (HI_U32)(107+inputPwrLevelPtr / 100) ;

    return HI_SUCCESS;
}

HI_S32 mxl582_get_signal_info(HI_U32 u32TunerPort, HI_UNF_TUNER_SIGNALINFO_S *pstInfo)
{
    //HI_S32 s32Ret = HI_SUCCESS;
    MXL_STATUS_E enMXLStatus;
    MXL_HYDRA_TUNE_PARAMS_T stTuneParams;
    
    HI_TUNER_CHECKPOINTER( pstInfo);
    
    pstInfo->enSigType = HI_UNF_TUNER_SIG_TYPE_SAT;

    enMXLStatus = MxLWare_HYDRA_API_ReqDemodChanParams(MXL582_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &stTuneParams);
    if(MXL_SUCCESS != enMXLStatus)
    {
        HI_ERR_TUNER("MxLWare_HYDRA_API_ReqDemodChanParams fail,errcode:%d.\n",enMXLStatus);
        return HI_FAILURE;
    }

    switch(stTuneParams.standardMask)
    {
        case MXL_HYDRA_DVBS2:
            pstInfo->unSignalInfo.stSat.enSATType = HI_UNF_TUNER_FE_DVBS2;
            break;
        case MXL_HYDRA_DVBS:
            pstInfo->unSignalInfo.stSat.enSATType = HI_UNF_TUNER_FE_DVBS;
            break;
        case MXL_HYDRA_DSS:
            pstInfo->unSignalInfo.stSat.enSATType = HI_UNF_TUNER_FE_DIRECTV;
            break;
        default:
            break;
    }

    switch(stTuneParams.params.paramsS2.fec)
    {
        case MXL_HYDRA_FEC_1_2:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_1_2;
            break;
        case MXL_HYDRA_FEC_3_5:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_3_5;
            break;
        case MXL_HYDRA_FEC_2_3:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_2_3;
            break;
        case MXL_HYDRA_FEC_3_4:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_3_4;
            break;
        case MXL_HYDRA_FEC_4_5:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_4_5;
            break;
        case MXL_HYDRA_FEC_5_6:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_5_6;
            break;
        case MXL_HYDRA_FEC_6_7:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_6_7;
            break;
        case MXL_HYDRA_FEC_7_8:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_7_8;
            break;
        case MXL_HYDRA_FEC_8_9:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_8_9;
            break;
        case MXL_HYDRA_FEC_9_10:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_9_10;
            break;
        case MXL_HYDRA_FEC_AUTO:
            pstInfo->unSignalInfo.stSat.enFECRate = HI_UNF_TUNER_FE_FEC_AUTO;
            break;
    }

    switch(stTuneParams.params.paramsS2.modulation)
    {
        case MXL_HYDRA_MOD_QPSK:
            pstInfo->unSignalInfo.stSat.enModType = HI_UNF_MOD_TYPE_QPSK;
            break;
        case MXL_HYDRA_MOD_8PSK:
            pstInfo->unSignalInfo.stSat.enModType = HI_UNF_MOD_TYPE_8PSK;
            break;
        case MXL_HYDRA_MOD_AUTO:
            pstInfo->unSignalInfo.stSat.enModType = HI_UNF_MOD_TYPE_AUTO;
        default:
            break;
    }

    return HI_SUCCESS;
}

HI_S32 mxl582_get_snr(HI_U32 u32TunerPort, HI_U32* pu32SNR)
{
    MXL_STATUS_E enMXLStatus;
    HI_S16 s16SNR;  
    HI_TUNER_CHECKPOINTER( pu32SNR);

    enMXLStatus = MxLWare_HYDRA_API_ReqDemodSNR(MXL582_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &s16SNR);
    if(MXL_SUCCESS != enMXLStatus)
    {
        HI_ERR_TUNER("MxLWare_HYDRA_API_ReqDemodSNR fail,errcode:%d.\n",enMXLStatus);
        return HI_FAILURE;
    }

    //value in 100x dB.
    *pu32SNR = (HI_U32)s16SNR;

    return HI_SUCCESS;
}

HI_S32 mxl582_get_ber(HI_U32 u32TunerPort, HI_U32 *pu32ber)
{
    MXL_STATUS_E status;
    MXL_HYDRA_DEMOD_STATUS_T stDemodStatus;
    
    if (u32TunerPort >= TUNER_NUM)
    {
        HI_ERR_TUNER("Bad u32TunerPort\n");
        return HI_FAILURE;
    }

    status = MxLWare_HYDRA_API_ReqDemodErrorCounters(MXL582_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort,  &stDemodStatus);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Req Demod Error Count FAILED\n", MXL582_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }

    if(MXL_HYDRA_DVBS2 == stDemodStatus.standardMask)
    {
        HI_INFO_TUNER("Signal:DVBS2.\n");
        pu32ber[0] = stDemodStatus.u.demodStatus_DVBS2.packetErrorCount;
        pu32ber[1] = stDemodStatus.u.demodStatus_DVBS2.totalPackets;
    }
    else if (MXL_HYDRA_DVBS == stDemodStatus.standardMask)
    {
        HI_INFO_TUNER("Signal:DVBS.\n");
        pu32ber[0] = stDemodStatus.u.demodStatus_DVBS.berCount_Iter1;
        pu32ber[1] = stDemodStatus.u.demodStatus_DVBS.berWindow_Iter1;
    }

    //ErrorConuters not clear immediately after call this function, it seems 100ms-200ms later!!
    status = MxLWare_HYDRA_API_CfgClearDemodErrorCounters(MXL582_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d][%d] Clear Demod Error Count FAILED\n", MXL582_DEVICE_ID, u32TunerPort);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 mxl582_set_ts_type(HI_U32 u32TunerPort, HI_UNF_TUNER_OUPUT_MODE_E enTsType)
{
    MXL_STATUS_E status = MXL_SUCCESS;
    MXL_HYDRA_MPEGOUT_PARAM_T mpegInterfaceCfg;
    MXL_HYDRA_MPEG_MODE_E enMpegMode = MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE;
    MXL_HYDRA_MPEG_CLK_TYPE_E enClkMode = MXL_HYDRA_MPEG_CLK_GAPPED;
    /* TS clock can be configure to 418/n MHz (3 <= n <= 256)  */
    UINT8 u8ClkFreq = 139;  //Actually 139.33MHz (418/3)

    if(u32TunerPort >= MXL_HYDRA_DEMOD_MAX)
    {
        HI_ERR_TUNER("u32TunerPort invalid:%d\n", u32TunerPort);
        return HI_FALSE;
    }

    switch (enTsType)
    {
        case HI_UNF_TUNER_OUTPUT_MODE_SERIAL:
        case HI_UNF_TUNER_OUTPUT_MODE_FULLBAND_SERIAL_3WIRE:
            enClkMode = MXL_HYDRA_MPEG_CLK_GAPPED;
            enMpegMode = MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE;
            u8ClkFreq = 104;
            break;
        case HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A:
        case HI_UNF_TUNER_OUTPUT_MODE_FULLBAND_PARALLEL:
            enClkMode = MXL_HYDRA_MPEG_CLK_GAPPED;
            enMpegMode = MXL_HYDRA_MPEG_MODE_PARALLEL;
            u8ClkFreq = 38;
            break;
        case HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_B:
            enClkMode = MXL_HYDRA_MPEG_CLK_CONTINUOUS;
            enMpegMode = MXL_HYDRA_MPEG_MODE_PARALLEL;
            u8ClkFreq = 38;
            break;
        case HI_UNF_TUNER_OUTPUT_MODE_SERIAL_50:
            enClkMode = MXL_HYDRA_MPEG_CLK_GAPPED;
            enMpegMode = MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE;
            u8ClkFreq = 50;
            break;
        default:
            enMpegMode = MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE;
            enClkMode = MXL_HYDRA_MPEG_CLK_GAPPED;
            u8ClkFreq = 104;
            break;            
    }

    if(enTsType == HI_UNF_TUNER_OUTPUT_MODE_FULLBAND_SERIAL_3WIRE)
    {
        MXL_HYDRA_TS_MUX_PREFIX_HEADER_T stTagHeader = {0};
        stTagHeader.enable = MXL_TRUE;
        stTagHeader.numByte = 4;
        stTagHeader.header[0] = u32TunerPort+1;
        stTagHeader.header[1] = u32TunerPort+1;
        stTagHeader.header[2] = u32TunerPort+1;
        stTagHeader.header[3] = u32TunerPort+1;
        status = MxLWare_HYDRA_API_CfgTsMuxPrefixExtraTsHeader(MXL582_DEVICE_ID, u32TunerPort, &stTagHeader);           
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgTsMuxPrefixExtraTsHeader for (%d) - Error (%d)\n", u32TunerPort, status);
            return status;
        }
        
        status = MxLWare_HYDRA_API_CfgTSMuxMode(MXL582_DEVICE_ID, MXL_HYDRA_TS_MUX_2_TO_1);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgTSMuxMode for (%d) - Error (%d)\n", u32TunerPort, status);
            return status;
        }
    }

    if(enTsType == HI_UNF_TUNER_OUTPUT_MODE_FULLBAND_PARALLEL)
    {
        MXL_HYDRA_TS_MUX_PREFIX_HEADER_T stTagHeader = {0};
        stTagHeader.enable = MXL_TRUE;
        stTagHeader.numByte = 4;
        if (u32TunerPort < 7)
        {
            stTagHeader.header[0] = u32TunerPort+1;
            stTagHeader.header[1] = u32TunerPort+1;
            stTagHeader.header[2] = u32TunerPort+1;
            stTagHeader.header[3] = u32TunerPort+1;
        }
        else
        {
            stTagHeader.header[0] = 7;
            stTagHeader.header[1] = 7;
            stTagHeader.header[2] = 7;
            stTagHeader.header[3] = 7;
        }
        status = MxLWare_HYDRA_API_CfgTsMuxPrefixExtraTsHeader(MXL582_DEVICE_ID, u32TunerPort, &stTagHeader);           
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgTsMuxPrefixExtraTsHeader for (%d) - Error (%d)\n", u32TunerPort, status);
            return status;
        }
    }
    
    if (enTsType == HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A ||
        enTsType == HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_B ||
        enTsType == HI_UNF_TUNER_OUTPUT_MODE_FULLBAND_PARALLEL)
    {
        status = MxLWare_HYDRA_API_CfgTSMixMuxMode(MXL582_DEVICE_ID, MXL_HYDRA_TS_GROUP_0_3, MXL_HYDRA_TS_MUX_4_TO_1);
        status |= MxLWare_HYDRA_API_CfgTSMixMuxMode(MXL582_DEVICE_ID, MXL_HYDRA_TS_GROUP_4_7, MXL_HYDRA_TS_MUX_4_TO_1);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgTSMixMuxMode for (%d) - Error (%d)\n", u32TunerPort, status);
            return status;
        }
        else
            HI_INFO_TUNER ("Done! - MxLWare_HYDRA_API_CfgTSMixMuxMode (%d) \n", u32TunerPort);
    }
    
    // Config TS interface of the device
    mpegInterfaceCfg.enable = MXL_ENABLE;
    mpegInterfaceCfg.lsbOrMsbFirst = MXL_HYDRA_MPEG_SERIAL_MSB_1ST;
    mpegInterfaceCfg.maxMpegClkRate = u8ClkFreq; //  supports only 418/n MHz (3 <= n <= 256)
    mpegInterfaceCfg.mpegClkPhase = MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_0_DEG;
    mpegInterfaceCfg.mpegClkPol = MXL_HYDRA_MPEG_CLK_POSITIVE;
    mpegInterfaceCfg.mpegClkType = enClkMode;
    mpegInterfaceCfg.mpegErrorIndication = MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED;
    mpegInterfaceCfg.mpegMode = enMpegMode;
    mpegInterfaceCfg.mpegSyncPol  = MXL_HYDRA_MPEG_ACTIVE_HIGH;
    mpegInterfaceCfg.mpegSyncPulseWidth  = MXL_HYDRA_MPEG_SYNC_WIDTH_BYTE;
    mpegInterfaceCfg.mpegValidPol  = MXL_HYDRA_MPEG_ACTIVE_HIGH;

    // Configure TS interface
    status = MxLWare_HYDRA_API_CfgMpegOutParams(MXL582_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &mpegInterfaceCfg);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgMpegOutParams for (%d) - Error (%d)\n", u32TunerPort, status);
        return status;
    }
    else
        HI_INFO_TUNER ("Done! - MxLWare_HYDRA_API_CfgMpegOutParams (%d) \n", u32TunerPort);

    return HI_SUCCESS; 
}

HI_S32 mxl582_send_continuous_22K(HI_U32 u32TunerPort, HI_BOOL b22k_on)
{
    MXL_STATUS_E status;
    MXL_HYDRA_DISEQC_ID_E enDiseqcId;

    HI_INFO_TUNER("port %d, 22k %d.\n", u32TunerPort, b22k_on);
    
    if(u32TunerPort < TUNER_NUM/2)
        enDiseqcId = MXL_HYDRA_DISEQC_ID_0;
    else
        enDiseqcId = MXL_HYDRA_DISEQC_ID_1;

    if (b22k_on)
    {
        status = MxLWare_HYDRA_API_CfgDiseqcContinuousToneCtrl(MXL582_DEVICE_ID, enDiseqcId, MXL_TRUE);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("[HYDRA][%d] Cfg Continuous tone FAILED\n", u32TunerPort);
            return HI_FAILURE;
        }
    }
    else
    {
        status = MxLWare_HYDRA_API_CfgDiseqcContinuousToneCtrl(MXL582_DEVICE_ID, enDiseqcId, MXL_FALSE);
        if (status != MXL_SUCCESS)
        {
            HI_ERR_TUNER("[HYDRA][%d] Cfg Continuous tone FAILED\n", u32TunerPort);
            return HI_FAILURE;
        }
    }
    
    return HI_SUCCESS;
}

HI_S32 mxl582_DiSEqC_send_msg(HI_U32 u32TunerPort, HI_UNF_TUNER_DISEQC_SENDMSG_S *pstSendMsg)
{
    MXL_STATUS_E status;
    MXL_HYDRA_DISEQC_TX_MSG_T diseqcMsgPtr = {0};
    HI_U32 statusPtr = 0;
    HI_U32 u32TotalTime = 0;
    HI_U32 u32UsedTime = 0;
    MXL_HYDRA_DISEQC_ID_E enDiseqcId;

    HI_INFO_TUNER("port:%d.\n", u32TunerPort);

    if(u32TunerPort < TUNER_NUM/2)
        enDiseqcId = MXL_HYDRA_DISEQC_ID_0;
    else
        enDiseqcId = MXL_HYDRA_DISEQC_ID_1;

    diseqcMsgPtr.diseqcId = enDiseqcId;
    diseqcMsgPtr.nbyte = pstSendMsg->u8Length;
    memcpy(diseqcMsgPtr.bufMsg, pstSendMsg->au8Msg, pstSendMsg->u8Length);
    diseqcMsgPtr.toneBurst = MXL_HYDRA_DISEQC_TONE_NONE;

    status = MxLWare_HYDRA_API_CfgDiseqcWrite(MXL582_DEVICE_ID, &diseqcMsgPtr);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER("[HYDRA][%d] Cfg Diseqc write FAILED\n", u32TunerPort);
        return HI_FAILURE;
    }

    u32UsedTime = 0;

    u32TotalTime = diseqcMsgPtr.nbyte * 14;
    u32UsedTime = 0;
    while(u32UsedTime < u32TotalTime)
    {
        status = MxLWare_HYDRA_API_ReqDiseqcStatus(MXL582_DEVICE_ID, enDiseqcId, &statusPtr);
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
        
        tuner_mdelay(2);
        u32UsedTime += 2;
    }
    
    return HI_FAILURE;
}

HI_VOID mxl582_connect_timeout(HI_U32 u32ConnectTimeout)
{
    return;
}

HI_S32 mxl582_deinit(HI_VOID)
{
    MXL_STATUS_E enMXLStatus;

    if(s_Mxl582InitFlag)
    {
        enMXLStatus = MxLWare_HYDRA_API_CfgDrvUnInit(MXL582_DEVICE_ID);
        if(MXL_SUCCESS != enMXLStatus)
        {
            HI_ERR_TUNER("MxLWare_HYDRA_API_CfgDrvUnInit fail,errcode:%d.\n",enMXLStatus);
            //return HI_FAILURE;
        }
        s_Mxl582InitFlag = HI_FALSE;
    }
    return HI_SUCCESS;
}

HI_S32 mxl582_config_ts_port_output(HI_U32 u32TunerPort,  HI_U32 u32Enable)
{
    MXL_STATUS_E status = MXL_SUCCESS;
    MXL_HYDRA_MPEGOUT_PARAM_T mpegInterfaceCfg;

    // Config TS interface of the device
    if(!u32Enable)
        mpegInterfaceCfg.enable = MXL_DISABLE;
    else
        mpegInterfaceCfg.enable = MXL_ENABLE;
    
    mpegInterfaceCfg.lsbOrMsbFirst = MXL_HYDRA_MPEG_SERIAL_MSB_1ST;
    mpegInterfaceCfg.maxMpegClkRate = 139; //  supports only (0 - 104 & 139)MHz
    mpegInterfaceCfg.mpegClkPhase = MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_0_DEG;
    mpegInterfaceCfg.mpegClkPol = MXL_HYDRA_MPEG_CLK_POSITIVE;
    mpegInterfaceCfg.mpegClkType = MXL_HYDRA_MPEG_CLK_GAPPED;
    mpegInterfaceCfg.mpegErrorIndication = MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED;
    mpegInterfaceCfg.mpegMode = MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE;
    mpegInterfaceCfg.mpegSyncPol  = MXL_HYDRA_MPEG_ACTIVE_HIGH;
    mpegInterfaceCfg.mpegSyncPulseWidth  = MXL_HYDRA_MPEG_SYNC_WIDTH_BYTE;
    mpegInterfaceCfg.mpegValidPol  = MXL_HYDRA_MPEG_ACTIVE_HIGH;
    // Configure TS interface
    status = MxLWare_HYDRA_API_CfgMpegOutParams(MXL582_DEVICE_ID, (MXL_HYDRA_DEMOD_ID_E)u32TunerPort, &mpegInterfaceCfg);
    if (status != MXL_SUCCESS)
    {
        HI_ERR_TUNER ("MxLWare_HYDRA_API_CfgMpegOutParams for (%d) - Error (%d)\n", u32TunerPort, status);
        return status;
    }
    else
        HI_INFO_TUNER ("Done! - MxLWare_HYDRA_API_CfgMpegOutParams (%d) \n", u32TunerPort);


    return HI_SUCCESS; 
}




