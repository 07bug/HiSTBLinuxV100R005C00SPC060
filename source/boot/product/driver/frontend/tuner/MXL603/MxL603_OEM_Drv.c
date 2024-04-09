/*****************************************************************************************
 *
 * FILE NAME          : MxL603_OEM_Drv.c
 * 
 * AUTHOR             : Mahendra Kondur
 *
 * DATE CREATED       : 12/23/2011  
 *
 * DESCRIPTION        : This file contains I2C driver and Sleep functins that 
 *                      OEM should implement for MxL603 APIs
 *                             
 *****************************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ****************************************************************************************/
//#include <linux/delay.h>

#include "hi_type.h"
//#include "hi_i2c.h"
#include "hi_unf_frontend.h"
#include "hi_drv_tuner.h"
#include "drv_demod.h"

#include "MxL603_OEM_Drv.h"
#include "MxL603_TunerApi.h"

#define DMD_BANK_T2_	0x1c 

static HI_U32 g_MxlTunerPort;
static HI_U32 g_MxlI2cChnNum;
HI_UNF_TUNER_SIG_TYPE_E  enMxl603TunerSigType = HI_UNF_TUNER_SIG_TYPE_CAB;
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare603_OEM_WriteRegister
--| 
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C write operation.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxLWare603_OEM_WriteRegister_dvb_c(UINT8 devId, UINT8 RegAddr, UINT8 RegData)
{
  // OEM should implement I2C write protocol that complies with MxL603 I2C
  // format.

  // 8 bit Register Write Protocol:
  // +------+-+-----+-+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |RegAddr   | |RegData(L)| |P|
  // +------+-+-----+-+-+----------+-+----------+-+-+
  // |SLAVE |         |A|          |A|          |A| |
  // +------+---------+-+----------+-+----------+-+-+
  // Legends: SADDR (I2c slave address), S (Start condition), A (Ack), N(NACK), 
  // P(Stop condition)
	MXL_STATUS status = MXL_TRUE;//MXL_FALSE;
	UINT8 I2C_Addr = 0;
	UINT8 i;
	user_data_t * user_data = (user_data_t *) MxL603_OEM_DataPtr[devId];
	UINT8 pArray[2];
	TUNER_I2C_DATA_S stI2cData;
	if (user_data)
	{
		I2C_Addr = user_data->i2c_address; // get device i2c address
	}
	pArray[0] = RegAddr;
	pArray[1] = RegData;
	qam_config_i2c_out(g_MxlTunerPort,1);
	stI2cData.pu8ReceiveBuf = NULL;
	stI2cData.u32ReceiveLength = 0;
	stI2cData.pu8SendBuf = pArray;
	stI2cData.u32SendLength = 2;
	for(i=0;i<10;i++)
		{
			status = tuner_i2c_send_data(g_MxlI2cChnNum,I2C_Addr,&stI2cData);
			if(!status)
			break;
		}

  return status;
}

MXL_STATUS MxLWare603_OEM_WriteRegister(UINT8 devId, UINT8 RegAddr, UINT8 RegData)
{
    if(enMxl603TunerSigType == HI_UNF_TUNER_SIG_TYPE_CAB)    
    {
        MXL_STATUS status = MXL_TRUE;
        status = MxLWare603_OEM_WriteRegister_dvb_c(devId, RegAddr, RegData);
        return status;
    }
    else
    {
        // OEM should implement I2C write protocol that complies with MxL603 I2C
        // format.

        // 8 bit Register Write Protocol:
        // +------+-+-----+-+-+----------+-+----------+-+-+
        // |MASTER|S|SADDR|W| |RegAddr   | |RegData(L)| |P|
        // +------+-+-----+-+-+----------+-+----------+-+-+
        // |SLAVE |         |A|          |A|          |A| |
        // +------+---------+-+----------+-+----------+-+-+
        // Legends: SADDR (I2c slave address), S (Start condition), A (Ack), N(NACK), 
        // P(Stop condition)

        MXL_STATUS status = MXL_FALSE;

#if 0
        /* If OEM data is implemented, customer needs to use OEM data structure related operation 
        Following code should be used as a reference. 
        For more information refer to sections 2.5 & 2.6 of MxL603_mxLWare_API_UserGuide document.

        UINT8 i2cSlaveAddr;
        UINT8 i2c_bus;
        user_data_t * user_data = (user_data_t *) MxL603_OEM_DataPtr[devId];

        if (user_data)
        {
        i2cSlaveAddr = user_data->i2c_address;           // get device i2c address
        i2c_bus = user_data->i2c_bus;                   // get device i2c bus  

        sem_up(user_data->sem);                         // up semaphore if needed

        // I2C Write operation 
        status = USER_I2C_WRITE_FUNCTION(i2cSlaveAddr, i2c_bus, RegAddr, RegData);

        sem_down(user_data->sem);                       // down semaphore
        user_data->i2c_cnt++;                           // user statistics
        }

        */

        /* If OEM data is not required, customer should treat devId as I2C slave Address */
        HI_U8 buf[4];
        TUNER_I2C_DATA_S stI2cDataStr = {0};

        buf[0] = 0xF7;
        buf[1] = g_stTunerOps[devId].u32TunerAddress;
        buf[2] = RegAddr;
        buf[3] = RegData;

        //printk("<0>devId=%d, g_stTunerOps[devId].enI2cChannel=%d, (g_stTunerOps[devId].u32DemodAddress=%d\n", devId, g_stTunerOps[devId].enI2cChannel, (g_stTunerOps[devId].u32DemodAddress));

        stI2cDataStr.pu8ReceiveBuf = 0;
        stI2cDataStr.u32ReceiveLength = 0;
        stI2cDataStr.pu8SendBuf = buf;
        stI2cDataStr.u32SendLength = 4;
        status = tuner_i2c_send_data(g_stTunerOps[devId].enI2cChannel, ((g_stTunerOps[devId].u32DemodAddress) + DMD_BANK_T2_)<<1 ,  &stI2cDataStr);
#endif
        return status;
    }
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare603_OEM_ReadRegister
--| 
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C read operation.
--|
--| RETURN VALUE  : True or False
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxLWare603_OEM_ReadRegister_dvb_c(UINT8 devId, UINT8 RegAddr, UINT8 *DataPtr)
{
  // OEM should implement I2C read protocol that complies with MxL603 I2C
  // format.

  // 8 bit Register Read Protocol:
  // +------+-+-----+-+-+----+-+----------+-+-+
  // |MASTER|S|SADDR|W| |0xFB| |RegAddr   | |P|
  // +------+-+-----+-+-+----+-+----------+-+-+
  // |SLAVE |         |A|    |A|          |A| |
  // +------+-+-----+-+-+----+-+----------+-+-+
  // +------+-+-----+-+-+-----+--+-+
  // |MASTER|S|SADDR|R| |     |MN|P|
  // +------+-+-----+-+-+-----+--+-+
  // |SLAVE |         |A|Data |  | |
  // +------+---------+-+-----+--+-+
  // Legends: SADDR(I2c slave address), S(Start condition), MA(Master Ack), MN(Master NACK), 
  // P(Stop condition)

	MXL_STATUS status = MXL_TRUE;

	  /* first step */
	TUNER_I2C_DATA_S stI2cData;
	HI_U32 u32RegAddr = 0;
	UINT8 Array[2];
	UINT8 I2C_Addr = 0;
	UINT8 i;
	user_data_t * user_data = (user_data_t *) MxL603_OEM_DataPtr[devId];

	if (user_data)
	{
		I2C_Addr = user_data->i2c_address; // get device i2c address
	}
    /*Array[0] = RegAddr;
    Array[1] = 0xFB;*/
    Array[0] = 0xFB;
    Array[1] = RegAddr;
    qam_config_i2c_out(g_MxlTunerPort,1);

    stI2cData.pu8ReceiveBuf = DataPtr;
    stI2cData.u32ReceiveLength = 1;
    stI2cData.pu8SendBuf = Array;
    stI2cData.u32SendLength = 2;
    /*for(i=0;i<10;i++)
  	{
	    status = tuner_i2c_receive_data(g_MxlI2cChnNum,I2C_Addr,&stI2cData);
		if(!status)
		{
		    break;
		}
  	}*/
    u32RegAddr = (Array[0] << 8) + Array[1];
    for(i=0; i<10; i++)
    {
       status = HI_DRV_I2C_Read(g_MxlI2cChnNum, (HI_U8)I2C_Addr, u32RegAddr, 2, DataPtr, 1);
       //status = I2C_Read(g_MxlI2cChnNum, (HI_U8)I2C_Addr, u32RegAddr, 2, DataPtr, 1);
        if(HI_SUCCESS == status)
        {
            break;
        }
    }
  return status;
}

MXL_STATUS MxLWare603_OEM_ReadRegister(UINT8 devId, UINT8 RegAddr, UINT8 *DataPtr)
{
    if(enMxl603TunerSigType == HI_UNF_TUNER_SIG_TYPE_CAB)
    {
        MXL_STATUS status = MXL_TRUE;
        status = MxLWare603_OEM_ReadRegister_dvb_c(devId, RegAddr, DataPtr);
        return status;
    }
    else
    {
        // OEM should implement I2C read protocol that complies with MxL603 I2C
        // format.

        // 8 bit Register Read Protocol:
        // +------+-+-----+-+-+----+-+----------+-+-+
        // |MASTER|S|SADDR|W| |0xFB| |RegAddr   | |P|
        // +------+-+-----+-+-+----+-+----------+-+-+
        // |SLAVE |         |A|    |A|          |A| |
        // +------+-+-----+-+-+----+-+----------+-+-+
        // +------+-+-----+-+-+-----+--+-+
        // |MASTER|S|SADDR|R| |     |MN|P|
        // +------+-+-----+-+-+-----+--+-+
        // |SLAVE |         |A|Data |  | |
        // +------+---------+-+-----+--+-+
        // Legends: SADDR(I2c slave address), S(Start condition), MA(Master Ack), MN(Master NACK), 
        // P(Stop condition)

        MXL_STATUS status = MXL_TRUE;
#if 0
        /* If OEM data is implemented, customer needs to use OEM data structure related operation 
        Following code should be used as a reference. 
        For more information refer to sections 2.5 & 2.6 of MxL603_mxLWare_API_UserGuide document.

        UINT8 i2cSlaveAddr;
        UINT8 i2c_bus;
        user_data_t * user_data = (user_data_t *) MxL603_OEM_DataPtr[devId];

        if (user_data)
        {
        i2cSlaveAddr = user_data->i2c_address;           // get device i2c address
        i2c_bus = user_data->i2c_bus;                   // get device i2c bus  

        sem_up(user_data->sem);                         // up semaphore if needed

        // I2C Write operation 
        status = USER_I2C_READ_FUNCTION(i2cSlaveAddr, i2c_bus, RegAddr, DataPtr);

        sem_down(user_data->sem);                       // down semaphore
        user_data->i2c_cnt++;                           // user statistics
        }

        */

        /* If OEM data is not required, customer should treat devId as I2C slave Address */
        HI_U8 buf[1];

        status = MxLWare603_OEM_WriteRegister(devId, 0xFB, RegAddr);

        buf[0] = g_stTunerOps[devId].u32TunerAddress | 0x1;
        if (HI_UNF_I2C_CHANNEL_QAM >= g_stTunerOps[devId].enI2cChannel)
        {
          status = HI_I2C_Write_NoSTOP(g_stTunerOps[devId].enI2cChannel, (g_stTunerOps[devId].u32DemodAddress + DMD_BANK_T2_)<<1, 0xF7, 1, buf, 1);

          status = HI_I2C_ReadDirectly(g_stTunerOps[devId].enI2cChannel, (g_stTunerOps[devId].u32DemodAddress + DMD_BANK_T2_)<<1, 0, 0, DataPtr, 1);
        }
        else
        {
          status = gpio_i2c_write_ext_NoSTOP(g_stTunerOps[devId].enI2cChannel, (g_stTunerOps[devId].u32DemodAddress + DMD_BANK_T2_)<<1, 0xF7, 1, buf, 1);

          status = gpio_i2c_read_ext_directly(g_stTunerOps[devId].enI2cChannel, (g_stTunerOps[devId].u32DemodAddress + DMD_BANK_T2_)<<1, 0, 0, DataPtr, 1);
        }
#endif
        return status;
 
    }
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare603_OEM_Sleep
--| 
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 01/10/2010
--|
--| DESCRIPTION   : This function complete sleep operation. WaitTime is in ms unit
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

void MxLWare603_OEM_Sleep(UINT16 DelayTimeInMs)
{
  // OEM should implement sleep operation 
  //msleep_interruptible(DelayTimeInMs);
  HI_TIMER_mdelay(DelayTimeInMs);
}

void MxL603_I2C_SetChn(UINT32 I2CChn)
{
    g_MxlI2cChnNum = I2CChn;
}

void MxL603_I2C_SetPort(UINT32 TunerPort)
{
    g_MxlTunerPort = TunerPort;
}
