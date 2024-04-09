/*************************************************************************************
                  Silicon Laboratories Broadcast Si2144 Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API commands definitions
   FILE: Si2144_L1_Commands.c
   Supported IC : Si2144
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.1
   Tag:  ROM62_2_1_build_5_V0.1
   Date: July 07 2017
  (C) Copyright 2017, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifdef    TER_TUNER_SILABS
    /* Before including the headers, define SiLevel and SiTAG */
    #define   SiLEVEL          1
    #define   SiTAG            api->i2c->tag
#endif /* TER_TUNER_SILABS */

#include "Si2144_L1_API.h"

/******   conversion functions, used to fill command response fields ***************************************************
  These functions provide compatibility with 8 bytes processing on some compilers
 ***********************************************************************************************************************/
unsigned char  Si2144_convert_to_byte (const unsigned char* buffer, unsigned char shift, unsigned char mask) {
  unsigned int rspBuffer = *buffer;
  return ((rspBuffer >> shift) & mask);
}
unsigned long  Si2144_convert_to_ulong(const unsigned char* buffer, unsigned char shift, unsigned long mask) {
  return ((( ( (unsigned long)buffer[0]) | ((unsigned long)buffer[1] << 8) | ((unsigned long)buffer[2]<<16) | ((unsigned long)buffer[3]<<24)) >> shift) & mask );
}
unsigned int   Si2144_convert_to_uint (const unsigned char* buffer, unsigned char shift, unsigned int  mask) {
  return ((( ( (unsigned int)buffer[0]) | (((unsigned int)buffer[1]) << 8)) >> shift) & mask);
}
signed   short Si2144_convert_to_int  (const unsigned char* buffer, unsigned char shift, unsigned int  mask) {
  return ((( ( (unsigned int)buffer[0]) | (((unsigned int)buffer[1]) << 8)) >> shift) & mask);
}
/***********************************************************************************************************************
  Si2144_CurrentResponseStatus function
  Use:        status checking function
              Used to fill the Si2144_COMMON_REPLY_struct members with the ptDataBuffer byte's bits
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
  Parameter: ptDataBuffer  a single byte received when reading a command's response (the first byte)
  Returns:   0 if the err bit (bit 6) is unset, 1 otherwise
 ***********************************************************************************************************************/
unsigned char Si2144_CurrentResponseStatus (L1_Si2144_Context *api, unsigned char ptDataBuffer)
{
    api->status->tunint =     Si2144_convert_to_byte(&ptDataBuffer, 0, 0x01);
    api->status->dtvint =     Si2144_convert_to_byte(&ptDataBuffer, 2, 0x01);
    api->status->err    =     Si2144_convert_to_byte(&ptDataBuffer, 6, 0x01);
    api->status->cts    =     Si2144_convert_to_byte(&ptDataBuffer, 7, 0x01);
  return (api->status->err ? ERROR_Si2144_ERR : NO_Si2144_ERROR);
}

 /***********************************************************************************************************************
  Si2144_pollForResetState function
  Use:        ResetState checking function
              Used to check the status byte for the reset code (0xFE).
  Comments:   Only required for the Si2144_L1_POWER_DOWN_HW Command

  Returns:   0 if the Status byte is = 0xFE, nonzero otherwise
 ***********************************************************************************************************************/
unsigned char Si2144_pollForResetState (L1_Si2144_Context *api)
{
  unsigned char rspByteBuffer[1];
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1) {
      SiTRACE("Si2144_pollForResetState ERROR reading byte 0!\n");
      return ERROR_Si2144_POLLING_CTS;
    }
    /* return OK if status=0xFE set */
    if (rspByteBuffer[0] == 0xFE) {
      return NO_Si2144_ERROR;
    }
  }

  SiTRACE("Si2144_pollForResetState ERROR status Timeout!\n");
  return ERROR_Si2144_CTS_TIMEOUT;
}
/***********************************************************************************************************************
  Si2144_GetStatus function
  Use:        POWER_UP checking function
              Used to check the status byte the reset code (0xFE) to drop.
  Comments:   Only required for the Si2144_L1_POWER_UP Command

  Returns:   0 if the Status byte is = 0xFE, nonzero otherwise
 ***********************************************************************************************************************/
unsigned char Si2144_GetStatus (L1_Si2144_Context *api)
{
    unsigned char rspByteBuffer[1];

    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1)
    {
      SiTRACE("Si2144_GetStatus ERROR reading byte 0!\n");
      return ERROR_Si2144_POLLING_CTS;
    }

    return (rspByteBuffer[0]);
}
/***********************************************************************************************************************
  Si2144_pollForCTS function
  Use:        CTS checking function
              Used to check the CTS bit until it is set before sending the next command
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Returns:   1 if the CTS bit is set, 0 otherwise
 ***********************************************************************************************************************/
unsigned char Si2144_pollForCTS (L1_Si2144_Context *api)
{
  unsigned char rspByteBuffer[1];
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1) {
      SiTRACE("Si2144_pollForCTS ERROR reading byte 0!\n");
      return ERROR_Si2144_POLLING_CTS;
    }
    /* return OK if CTS set */
    if (rspByteBuffer[0] & 0x80) {
      return NO_Si2144_ERROR;
    }
  }

  SiTRACE("Si2144_pollForCTS ERROR CTS Timeout!\n");
  return ERROR_Si2144_CTS_TIMEOUT;
}

/***********************************************************************************************************************
  Si2144_pollForResponse function
  Use:        command response retrieval function
              Used to retrieve the command response in the provided buffer
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Parameter:  nbBytes          the number of response bytes to read
  Parameter:  pByteBuffer      a buffer into which bytes will be stored
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2144_pollForResponse (L1_Si2144_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer)
{
  unsigned char debugBuffer[7];
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if ((unsigned int)L0_ReadCommandBytes(api->i2c, nbBytes, pByteBuffer) != nbBytes) {
      SiTRACE("Si2144_pollForResponse ERROR reading byte 0!\n");
      return ERROR_Si2144_POLLING_RESPONSE;
    }
    /* return response err flag if CTS set */
    if (pByteBuffer[0] & 0x80)  {
     if (pByteBuffer[0] & 0x40)  {
        L0_ReadCommandBytes(api->i2c, 7, &(debugBuffer[0]) );
        SiTRACE("Si2144 debug bytes 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", debugBuffer[0], debugBuffer[1], debugBuffer[2], debugBuffer[3], debugBuffer[4], debugBuffer[5], debugBuffer[6]);
      }
      return Si2144_CurrentResponseStatus(api, pByteBuffer[0]);
    }
  }

  SiTRACE("Si2144_pollForResponse ERROR CTS Timeout!\n");
  return ERROR_Si2144_CTS_TIMEOUT;
}

#ifdef    Si2144_AGC_OVERRIDE_CMD
/*---------------------------------------------------*/
/* Si2144_AGC_OVERRIDE COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2144_L1_AGC_OVERRIDE    (L1_Si2144_Context *api,
                                         unsigned char   force_max_gain,
                                         unsigned char   force_top_gain)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->agc_override.STATUS = api->status;

    SiTRACE("Si2144 AGC_OVERRIDE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((force_max_gain > Si2144_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_MAX_GAIN %d ", force_max_gain );
    if ((force_top_gain > Si2144_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_TOP_GAIN %d ", force_top_gain );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_AGC_OVERRIDE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( force_max_gain & Si2144_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MASK ) << Si2144_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_LSB|
                                         ( force_top_gain & Si2144_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MASK ) << Si2144_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing AGC_OVERRIDE bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling AGC_OVERRIDE response\n");
      return error_code;
    }


    return NO_Si2144_ERROR;
}
#endif /* Si2144_AGC_OVERRIDE_CMD */
#ifdef    Si2144_CONFIG_CLOCKS_CMD
/*---------------------------------------------------*/
/* Si2144_CONFIG_CLOCKS COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2144_L1_CONFIG_CLOCKS   (L1_Si2144_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->config_clocks.STATUS = api->status;

    SiTRACE("Si2144 CONFIG_CLOCKS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode    > Si2144_CONFIG_CLOCKS_CMD_SUBCODE_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "   , subcode    );
    if ((clock_mode > Si2144_CONFIG_CLOCKS_CMD_CLOCK_MODE_MAX)  || (clock_mode < Si2144_CONFIG_CLOCKS_CMD_CLOCK_MODE_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d ", clock_mode );
    if ((en_xout    > Si2144_CONFIG_CLOCKS_CMD_EN_XOUT_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "   , en_xout    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_CONFIG_CLOCKS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si2144_CONFIG_CLOCKS_CMD_SUBCODE_MASK    ) << Si2144_CONFIG_CLOCKS_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( clock_mode & Si2144_CONFIG_CLOCKS_CMD_CLOCK_MODE_MASK ) << Si2144_CONFIG_CLOCKS_CMD_CLOCK_MODE_LSB|
                                         ( en_xout    & Si2144_CONFIG_CLOCKS_CMD_EN_XOUT_MASK    ) << Si2144_CONFIG_CLOCKS_CMD_EN_XOUT_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing CONFIG_CLOCKS bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_CLOCKS response\n");
      return error_code;
    }


    return NO_Si2144_ERROR;
}
#endif /* Si2144_CONFIG_CLOCKS_CMD */
#ifdef    Si2144_CONFIG_I2C_CMD
/*---------------------------------------------------*/
/* Si2144_CONFIG_I2C COMMAND                             */
/*---------------------------------------------------*/
unsigned char Si2144_L1_CONFIG_I2C      (L1_Si2144_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   i2c_broadcast)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->config_i2c.STATUS = api->status;

    SiTRACE("Si2144 CONFIG_I2C ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode       > Si2144_CONFIG_I2C_CMD_SUBCODE_MAX      )  || (subcode       < Si2144_CONFIG_I2C_CMD_SUBCODE_MIN      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "      , subcode       );
    if ((i2c_broadcast > Si2144_CONFIG_I2C_CMD_I2C_BROADCAST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("I2C_BROADCAST %d ", i2c_broadcast );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_CONFIG_I2C_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode       & Si2144_CONFIG_I2C_CMD_SUBCODE_MASK       ) << Si2144_CONFIG_I2C_CMD_SUBCODE_LSB      );
    cmdByteBuffer[2] = (unsigned char) ( ( i2c_broadcast & Si2144_CONFIG_I2C_CMD_I2C_BROADCAST_MASK ) << Si2144_CONFIG_I2C_CMD_I2C_BROADCAST_LSB);

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing CONFIG_I2C bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_I2C response\n");
      return error_code;
    }
    return NO_Si2144_ERROR;
}
#endif /* Si2144_CONFIG_I2C_CMD */
#ifdef    Si2144_CONFIG_PINS_CMD
/*---------------------------------------------------*/
/* Si2144_CONFIG_PINS COMMAND                           */
/*---------------------------------------------------*/
unsigned char Si2144_L1_CONFIG_PINS     (L1_Si2144_Context *api,
                                         unsigned char   gpio1_mode,
                                         unsigned char   gpio1_read,
                                         unsigned char   gpio2_mode,
                                         unsigned char   gpio2_read,
                                         unsigned char   agc1_mode,
                                         unsigned char   agc1_read,
                                         unsigned char   agc2_mode,
                                         unsigned char   agc2_read,
                                         unsigned char   xout_mode)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[7];
    unsigned char rspByteBuffer[7];
    error_code = 0;
    api->rsp->config_pins.STATUS = api->status;

    SiTRACE("Si2144 CONFIG_PINS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((gpio1_mode > Si2144_CONFIG_PINS_CMD_GPIO1_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_MODE %d ", gpio1_mode );
    if ((gpio1_read > Si2144_CONFIG_PINS_CMD_GPIO1_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_READ %d ", gpio1_read );
    if ((gpio2_mode > Si2144_CONFIG_PINS_CMD_GPIO2_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_MODE %d ", gpio2_mode );
    if ((gpio2_read > Si2144_CONFIG_PINS_CMD_GPIO2_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_READ %d ", gpio2_read );
    if ((agc1_mode  > Si2144_CONFIG_PINS_CMD_AGC1_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC1_MODE %d " , agc1_mode  );
    if ((agc1_read  > Si2144_CONFIG_PINS_CMD_AGC1_READ_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC1_READ %d " , agc1_read  );
    if ((agc2_mode  > Si2144_CONFIG_PINS_CMD_AGC2_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC2_MODE %d " , agc2_mode  );
    if ((agc2_read  > Si2144_CONFIG_PINS_CMD_AGC2_READ_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC2_READ %d " , agc2_read  );
    if ((xout_mode  > Si2144_CONFIG_PINS_CMD_XOUT_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("XOUT_MODE %d " , xout_mode  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_CONFIG_PINS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( gpio1_mode & Si2144_CONFIG_PINS_CMD_GPIO1_MODE_MASK ) << Si2144_CONFIG_PINS_CMD_GPIO1_MODE_LSB|
                                         ( gpio1_read & Si2144_CONFIG_PINS_CMD_GPIO1_READ_MASK ) << Si2144_CONFIG_PINS_CMD_GPIO1_READ_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( gpio2_mode & Si2144_CONFIG_PINS_CMD_GPIO2_MODE_MASK ) << Si2144_CONFIG_PINS_CMD_GPIO2_MODE_LSB|
                                         ( gpio2_read & Si2144_CONFIG_PINS_CMD_GPIO2_READ_MASK ) << Si2144_CONFIG_PINS_CMD_GPIO2_READ_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( agc1_mode  & Si2144_CONFIG_PINS_CMD_AGC1_MODE_MASK  ) << Si2144_CONFIG_PINS_CMD_AGC1_MODE_LSB |
                                         ( agc1_read  & Si2144_CONFIG_PINS_CMD_AGC1_READ_MASK  ) << Si2144_CONFIG_PINS_CMD_AGC1_READ_LSB );
    cmdByteBuffer[4] = (unsigned char)0x00;
    cmdByteBuffer[5] = (unsigned char) ( ( agc2_mode  & Si2144_CONFIG_PINS_CMD_AGC2_MODE_MASK  ) << Si2144_CONFIG_PINS_CMD_AGC2_MODE_LSB |
                                         ( agc2_read  & Si2144_CONFIG_PINS_CMD_AGC2_READ_MASK  ) << Si2144_CONFIG_PINS_CMD_AGC2_READ_LSB );
    cmdByteBuffer[6] = (unsigned char) ( ( xout_mode  & Si2144_CONFIG_PINS_CMD_XOUT_MODE_MASK  ) << Si2144_CONFIG_PINS_CMD_XOUT_MODE_LSB );

    if (L0_WriteCommandBytes(api->i2c, 7, cmdByteBuffer) != 7) {
      SiTRACE("Error writing CONFIG_PINS bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 7, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_PINS response\n");
      return error_code;
    }

    api->rsp->config_pins.gpio1_mode  = Si2144_convert_to_byte  (&rspByteBuffer[ 1] , Si2144_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB   , Si2144_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK  );
    api->rsp->config_pins.gpio1_state = Si2144_convert_to_byte  (&rspByteBuffer[ 1] , Si2144_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB  , Si2144_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK );
    api->rsp->config_pins.gpio2_mode  = Si2144_convert_to_byte  (&rspByteBuffer[ 2] , Si2144_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB   , Si2144_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK  );
    api->rsp->config_pins.gpio2_state = Si2144_convert_to_byte  (&rspByteBuffer[ 2] , Si2144_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB  , Si2144_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK );
    api->rsp->config_pins.agc1_mode   = Si2144_convert_to_byte  (&rspByteBuffer[ 3] , Si2144_CONFIG_PINS_RESPONSE_AGC1_MODE_LSB    , Si2144_CONFIG_PINS_RESPONSE_AGC1_MODE_MASK   );
    api->rsp->config_pins.agc1_state  = Si2144_convert_to_byte  (&rspByteBuffer[ 3] , Si2144_CONFIG_PINS_RESPONSE_AGC1_STATE_LSB   , Si2144_CONFIG_PINS_RESPONSE_AGC1_STATE_MASK  );
    api->rsp->config_pins.agc2_mode   = Si2144_convert_to_byte  (&rspByteBuffer[ 5] , Si2144_CONFIG_PINS_RESPONSE_AGC2_MODE_LSB    , Si2144_CONFIG_PINS_RESPONSE_AGC2_MODE_MASK   );
    api->rsp->config_pins.agc2_state  = Si2144_convert_to_byte  (&rspByteBuffer[ 5] , Si2144_CONFIG_PINS_RESPONSE_AGC2_STATE_LSB   , Si2144_CONFIG_PINS_RESPONSE_AGC2_STATE_MASK  );
    api->rsp->config_pins.xout_mode   = Si2144_convert_to_byte  (&rspByteBuffer[ 6] , Si2144_CONFIG_PINS_RESPONSE_XOUT_MODE_LSB    , Si2144_CONFIG_PINS_RESPONSE_XOUT_MODE_MASK   );
    api->rsp->config_pins.xout_state  = Si2144_convert_to_byte  (&rspByteBuffer[ 6] , Si2144_CONFIG_PINS_RESPONSE_XOUT_STATE_LSB   , Si2144_CONFIG_PINS_RESPONSE_XOUT_STATE_MASK  );

    return NO_Si2144_ERROR;
}
#endif /* Si2144_CONFIG_PINS_CMD */
#ifdef    Si2144_EXIT_BOOTLOADER_CMD
/*---------------------------------------------------*/
/* Si2144_EXIT_BOOTLOADER COMMAND                   */
/*---------------------------------------------------*/
unsigned char Si2144_L1_EXIT_BOOTLOADER (L1_Si2144_Context *api,
                                         unsigned char   func,
                                         unsigned char   ctsien)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->exit_bootloader.STATUS = api->status;

    SiTRACE("Si2144 EXIT_BOOTLOADER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((func   > Si2144_EXIT_BOOTLOADER_CMD_FUNC_MAX  )  || (func   < Si2144_EXIT_BOOTLOADER_CMD_FUNC_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "  , func   );
    if ((ctsien > Si2144_EXIT_BOOTLOADER_CMD_CTSIEN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d ", ctsien );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_EXIT_BOOTLOADER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( func   & Si2144_EXIT_BOOTLOADER_CMD_FUNC_MASK   ) << Si2144_EXIT_BOOTLOADER_CMD_FUNC_LSB  |
                                         ( ctsien & Si2144_EXIT_BOOTLOADER_CMD_CTSIEN_MASK ) << Si2144_EXIT_BOOTLOADER_CMD_CTSIEN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing EXIT_BOOTLOADER bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling EXIT_BOOTLOADER response\n");
      return error_code;
    }


    return NO_Si2144_ERROR;
}
#endif /* Si2144_EXIT_BOOTLOADER_CMD */
#ifdef    Si2144_FINE_TUNE_CMD
/*---------------------------------------------------*/
/* Si2144_FINE_TUNE COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2144_L1_FINE_TUNE       (L1_Si2144_Context *api,
                                         unsigned char   persistence,
                                         signed   int    offset_500hz)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->fine_tune.STATUS = api->status;

    SiTRACE("Si2144 FINE_TUNE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((persistence  > Si2144_FINE_TUNE_CMD_PERSISTENCE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PERSISTENCE %d " , persistence  );
    if ((offset_500hz > Si2144_FINE_TUNE_CMD_OFFSET_500HZ_MAX)  || (offset_500hz < Si2144_FINE_TUNE_CMD_OFFSET_500HZ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OFFSET_500HZ %d ", offset_500hz );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_FINE_TUNE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( persistence  & Si2144_FINE_TUNE_CMD_PERSISTENCE_MASK  ) << Si2144_FINE_TUNE_CMD_PERSISTENCE_LSB );
    cmdByteBuffer[2] = (unsigned char) ( ( offset_500hz & Si2144_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2144_FINE_TUNE_CMD_OFFSET_500HZ_LSB);
    cmdByteBuffer[3] = (unsigned char) ((( offset_500hz & Si2144_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2144_FINE_TUNE_CMD_OFFSET_500HZ_LSB)>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing FINE_TUNE bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling FINE_TUNE response\n");
      return error_code;
    }


    return NO_Si2144_ERROR;
}
#endif /* Si2144_FINE_TUNE_CMD */
#ifdef    Si2144_GET_PROPERTY_CMD
/*---------------------------------------------------*/
/* Si2144_GET_PROPERTY COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2144_L1_GET_PROPERTY    (L1_Si2144_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[4];
    error_code = 0;
    api->rsp->get_property.STATUS = api->status;

    SiTRACE("Si2144 GET_PROPERTY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reserved > Si2144_GET_PROPERTY_CMD_RESERVED_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED %d ", reserved );
    SiTRACE("PROP %d "    , prop     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_GET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2144_GET_PROPERTY_CMD_RESERVED_MASK ) << Si2144_GET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2144_GET_PROPERTY_CMD_PROP_MASK     ) << Si2144_GET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2144_GET_PROPERTY_CMD_PROP_MASK     ) << Si2144_GET_PROPERTY_CMD_PROP_LSB    )>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing GET_PROPERTY bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_PROPERTY response\n");
      return error_code;
    }

    api->rsp->get_property.reserved = Si2144_convert_to_byte  (&rspByteBuffer[ 1] , Si2144_GET_PROPERTY_RESPONSE_RESERVED_LSB  , Si2144_GET_PROPERTY_RESPONSE_RESERVED_MASK );
    api->rsp->get_property.data     = Si2144_convert_to_uint  (&rspByteBuffer[ 2] , Si2144_GET_PROPERTY_RESPONSE_DATA_LSB      , Si2144_GET_PROPERTY_RESPONSE_DATA_MASK     );

    return NO_Si2144_ERROR;
}
#endif /* Si2144_GET_PROPERTY_CMD */
#ifdef    Si2144_GET_REV_CMD
/*---------------------------------------------------*/
/* Si2144_GET_REV COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2144_L1_GET_REV         (L1_Si2144_Context *api)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[13];
    error_code = 0;
    api->rsp->get_rev.STATUS = api->status;

    SiTRACE("Si2144 GET_REV ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_GET_REV_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing GET_REV bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_REV response\n");
      return error_code;
    }

    api->rsp->get_rev.pn       = Si2144_convert_to_byte  (&rspByteBuffer[ 1] , Si2144_GET_REV_RESPONSE_PN_LSB        , Si2144_GET_REV_RESPONSE_PN_MASK       );
    api->rsp->get_rev.fwmajor  = Si2144_convert_to_byte  (&rspByteBuffer[ 2] , Si2144_GET_REV_RESPONSE_FWMAJOR_LSB   , Si2144_GET_REV_RESPONSE_FWMAJOR_MASK  );
    api->rsp->get_rev.fwminor  = Si2144_convert_to_byte  (&rspByteBuffer[ 3] , Si2144_GET_REV_RESPONSE_FWMINOR_LSB   , Si2144_GET_REV_RESPONSE_FWMINOR_MASK  );
    api->rsp->get_rev.patch    = Si2144_convert_to_uint  (&rspByteBuffer[ 4] , Si2144_GET_REV_RESPONSE_PATCH_LSB     , Si2144_GET_REV_RESPONSE_PATCH_MASK    );
    api->rsp->get_rev.cmpmajor = Si2144_convert_to_byte  (&rspByteBuffer[ 6] , Si2144_GET_REV_RESPONSE_CMPMAJOR_LSB  , Si2144_GET_REV_RESPONSE_CMPMAJOR_MASK );
    api->rsp->get_rev.cmpminor = Si2144_convert_to_byte  (&rspByteBuffer[ 7] , Si2144_GET_REV_RESPONSE_CMPMINOR_LSB  , Si2144_GET_REV_RESPONSE_CMPMINOR_MASK );
    api->rsp->get_rev.cmpbuild = Si2144_convert_to_byte  (&rspByteBuffer[ 8] , Si2144_GET_REV_RESPONSE_CMPBUILD_LSB  , Si2144_GET_REV_RESPONSE_CMPBUILD_MASK );
    api->rsp->get_rev.chiprev  = Si2144_convert_to_byte  (&rspByteBuffer[ 9] , Si2144_GET_REV_RESPONSE_CHIPREV_LSB   , Si2144_GET_REV_RESPONSE_CHIPREV_MASK  );
    api->rsp->get_rev.pn2      = Si2144_convert_to_byte  (&rspByteBuffer[12] , Si2144_GET_REV_RESPONSE_PN2_LSB       , Si2144_GET_REV_RESPONSE_PN2_MASK      );

    return NO_Si2144_ERROR;
}
#endif /* Si2144_GET_REV_CMD */
#ifdef    Si2144_PART_INFO_CMD
/*---------------------------------------------------*/
/* Si2144_PART_INFO COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2144_L1_PART_INFO       (L1_Si2144_Context *api)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[14];
    error_code = 0;
    api->rsp->part_info.STATUS = api->status;

    SiTRACE("Si2144 PART_INFO ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_PART_INFO_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing PART_INFO bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 14, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling PART_INFO response\n");
      return error_code;
    }

    api->rsp->part_info.chiprev  = Si2144_convert_to_byte  (&rspByteBuffer[ 1] , Si2144_PART_INFO_RESPONSE_CHIPREV_LSB   , Si2144_PART_INFO_RESPONSE_CHIPREV_MASK  );
    api->rsp->part_info.part     = Si2144_convert_to_byte  (&rspByteBuffer[ 2] , Si2144_PART_INFO_RESPONSE_PART_LSB      , Si2144_PART_INFO_RESPONSE_PART_MASK     );
    api->rsp->part_info.pmajor   = Si2144_convert_to_byte  (&rspByteBuffer[ 3] , Si2144_PART_INFO_RESPONSE_PMAJOR_LSB    , Si2144_PART_INFO_RESPONSE_PMAJOR_MASK   );
    api->rsp->part_info.pminor   = Si2144_convert_to_byte  (&rspByteBuffer[ 4] , Si2144_PART_INFO_RESPONSE_PMINOR_LSB    , Si2144_PART_INFO_RESPONSE_PMINOR_MASK   );
    api->rsp->part_info.pbuild   = Si2144_convert_to_byte  (&rspByteBuffer[ 5] , Si2144_PART_INFO_RESPONSE_PBUILD_LSB    , Si2144_PART_INFO_RESPONSE_PBUILD_MASK   );
    api->rsp->part_info.reserved = Si2144_convert_to_uint  (&rspByteBuffer[ 6] , Si2144_PART_INFO_RESPONSE_RESERVED_LSB  , Si2144_PART_INFO_RESPONSE_RESERVED_MASK );
    api->rsp->part_info.serial   = Si2144_convert_to_ulong (&rspByteBuffer[ 8] , Si2144_PART_INFO_RESPONSE_SERIAL_LSB    , Si2144_PART_INFO_RESPONSE_SERIAL_MASK   );
    api->rsp->part_info.romid    = Si2144_convert_to_byte  (&rspByteBuffer[12] , Si2144_PART_INFO_RESPONSE_ROMID_LSB     , Si2144_PART_INFO_RESPONSE_ROMID_MASK    );
    api->rsp->part_info.part2    = Si2144_convert_to_byte  (&rspByteBuffer[13] , Si2144_PART_INFO_RESPONSE_PART2_LSB     , Si2144_PART_INFO_RESPONSE_PART2_MASK    );

    return NO_Si2144_ERROR;
}
#endif /* Si2144_PART_INFO_CMD */
#ifdef    Si2144_PART_INFO2_CMD
/*---------------------------------------------------*/
/* Si2144_PART_INFO2 COMMAND                             */
/*---------------------------------------------------*/
unsigned char Si2144_L1_PART_INFO2      (L1_Si2144_Context *api)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[8];
    error_code = 0;
    api->rsp->part_info2.STATUS = api->status;

    SiTRACE("Si2144 PART_INFO2 ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_PART_INFO2_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing PART_INFO2 bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 8, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling PART_INFO2 response\n");
      return error_code;
    }

    api->rsp->part_info2.romid    = Si2144_convert_to_byte  (&rspByteBuffer[ 1] , Si2144_PART_INFO2_RESPONSE_ROMID_LSB     , Si2144_PART_INFO2_RESPONSE_ROMID_MASK    );
    api->rsp->part_info2.part2    = Si2144_convert_to_byte  (&rspByteBuffer[ 2] , Si2144_PART_INFO2_RESPONSE_PART2_LSB     , Si2144_PART_INFO2_RESPONSE_PART2_MASK    );
    api->rsp->part_info2.reserved = Si2144_convert_to_byte  (&rspByteBuffer[ 3] , Si2144_PART_INFO2_RESPONSE_RESERVED_LSB  , Si2144_PART_INFO2_RESPONSE_RESERVED_MASK );
    api->rsp->part_info2.serial   = Si2144_convert_to_ulong (&rspByteBuffer[ 4] , Si2144_PART_INFO2_RESPONSE_SERIAL_LSB    , Si2144_PART_INFO2_RESPONSE_SERIAL_MASK   );

    return NO_Si2144_ERROR;
}
#endif /* Si2144_PART_INFO2_CMD */
#ifdef    Si2144_POLL_CTS_CMD
/*---------------------------------------------------*/
/* Si2144_POLL_CTS COMMAND                                 */
/*---------------------------------------------------*/
unsigned char Si2144_L1_POLL_CTS        (L1_Si2144_Context *api)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->poll_cts.STATUS = api->status;

    SiTRACE("Si2144 POLL_CTS ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_POLL_CTS_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing POLL_CTS bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POLL_CTS response\n");
      return error_code;
    }


    return NO_Si2144_ERROR;
}
#endif /* Si2144_POLL_CTS_CMD */
#ifdef    Si2144_POWER_DOWN_HW_CMD
/*---------------------------------------------------*/
/* Si2144_POWER_DOWN_HW COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2144_L1_POWER_DOWN_HW   (L1_Si2144_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   pdb_xo_osc,
                                         unsigned char   reserved1,
                                         unsigned char   en_xout,
                                         unsigned char   reserved2,
                                         unsigned char   reserved3,
                                         unsigned char   reserved4,
                                         unsigned char   reserved5,
                                         unsigned char   reserved6,
                                         unsigned char   reserved7,
                                         unsigned char   reserved8,
                                         unsigned char   reserved9)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[10];
    error_code = 0;
    api->rsp->power_down_hw.STATUS = api->status;

    SiTRACE("Si2144 POWER_DOWN_HW ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode    > Si2144_POWER_DOWN_HW_CMD_SUBCODE_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "   , subcode    );
    if ((pdb_xo_osc > Si2144_POWER_DOWN_HW_CMD_PDB_XO_OSC_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PDB_XO_OSC %d ", pdb_xo_osc );
    if ((reserved1  > Si2144_POWER_DOWN_HW_CMD_RESERVED1_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d " , reserved1  );
    if ((en_xout    > Si2144_POWER_DOWN_HW_CMD_EN_XOUT_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "   , en_xout    );
    if ((reserved2  > Si2144_POWER_DOWN_HW_CMD_RESERVED2_MAX )  || (reserved2  < Si2144_POWER_DOWN_HW_CMD_RESERVED2_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d " , reserved2  );
    if ((reserved3  > Si2144_POWER_DOWN_HW_CMD_RESERVED3_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d " , reserved3  );
    if ((reserved4  > Si2144_POWER_DOWN_HW_CMD_RESERVED4_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d " , reserved4  );
    if ((reserved5  > Si2144_POWER_DOWN_HW_CMD_RESERVED5_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d " , reserved5  );
    if ((reserved6  > Si2144_POWER_DOWN_HW_CMD_RESERVED6_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED6 %d " , reserved6  );
    if ((reserved7  > Si2144_POWER_DOWN_HW_CMD_RESERVED7_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED7 %d " , reserved7  );
    if ((reserved8  > Si2144_POWER_DOWN_HW_CMD_RESERVED8_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED8 %d " , reserved8  );
    if ((reserved9  > Si2144_POWER_DOWN_HW_CMD_RESERVED9_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED9 %d " , reserved9  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_POWER_DOWN_HW_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si2144_POWER_DOWN_HW_CMD_SUBCODE_MASK    ) << Si2144_POWER_DOWN_HW_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( pdb_xo_osc & Si2144_POWER_DOWN_HW_CMD_PDB_XO_OSC_MASK ) << Si2144_POWER_DOWN_HW_CMD_PDB_XO_OSC_LSB|
                                         ( reserved1  & Si2144_POWER_DOWN_HW_CMD_RESERVED1_MASK  ) << Si2144_POWER_DOWN_HW_CMD_RESERVED1_LSB |
                                         ( en_xout    & Si2144_POWER_DOWN_HW_CMD_EN_XOUT_MASK    ) << Si2144_POWER_DOWN_HW_CMD_EN_XOUT_LSB   |
                                         ( reserved2  & Si2144_POWER_DOWN_HW_CMD_RESERVED2_MASK  ) << Si2144_POWER_DOWN_HW_CMD_RESERVED2_LSB );
    cmdByteBuffer[3] = (unsigned char) ( ( reserved3  & Si2144_POWER_DOWN_HW_CMD_RESERVED3_MASK  ) << Si2144_POWER_DOWN_HW_CMD_RESERVED3_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved4  & Si2144_POWER_DOWN_HW_CMD_RESERVED4_MASK  ) << Si2144_POWER_DOWN_HW_CMD_RESERVED4_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved5  & Si2144_POWER_DOWN_HW_CMD_RESERVED5_MASK  ) << Si2144_POWER_DOWN_HW_CMD_RESERVED5_LSB );
    cmdByteBuffer[6] = (unsigned char) ( ( reserved6  & Si2144_POWER_DOWN_HW_CMD_RESERVED6_MASK  ) << Si2144_POWER_DOWN_HW_CMD_RESERVED6_LSB );
    cmdByteBuffer[7] = (unsigned char) ( ( reserved7  & Si2144_POWER_DOWN_HW_CMD_RESERVED7_MASK  ) << Si2144_POWER_DOWN_HW_CMD_RESERVED7_LSB );
    cmdByteBuffer[8] = (unsigned char) ( ( reserved8  & Si2144_POWER_DOWN_HW_CMD_RESERVED8_MASK  ) << Si2144_POWER_DOWN_HW_CMD_RESERVED8_LSB );
    cmdByteBuffer[9] = (unsigned char) ( ( reserved9  & Si2144_POWER_DOWN_HW_CMD_RESERVED9_MASK  ) << Si2144_POWER_DOWN_HW_CMD_RESERVED9_LSB );

    if (L0_WriteCommandBytes(api->i2c, 10, cmdByteBuffer) != 10) {
      SiTRACE("Error writing POWER_DOWN_HW bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResetState(api);
    if (error_code) {
      SiTRACE("Error polling POWER_DOWN_HW reset state\n");
      return error_code;
    }
    return NO_Si2144_ERROR;
}
#endif /* Si2144_POWER_DOWN_HW_CMD */
#ifdef    Si2144_POWER_UP_CMD
/*---------------------------------------------------*/
/* Si2144_POWER_UP COMMAND                                 */
/*---------------------------------------------------*/
unsigned char Si2144_L1_POWER_UP        (L1_Si2144_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout,
                                         unsigned char   config_1p8v,
                                         unsigned char   reserved3,
                                         unsigned char   reserved4,
                                         unsigned char   reserved5,
                                         unsigned char   reserved6,
                                         unsigned char   reserved7,
                                         unsigned char   reserved8)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[10];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->power_up.STATUS = api->status;

    SiTRACE("Si2144 POWER_UP ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode     > Si2144_POWER_UP_CMD_SUBCODE_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "    , subcode     );
    if ((clock_mode  > Si2144_POWER_UP_CMD_CLOCK_MODE_MAX )  || (clock_mode  < Si2144_POWER_UP_CMD_CLOCK_MODE_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d " , clock_mode  );
    if ((en_xout     > Si2144_POWER_UP_CMD_EN_XOUT_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "    , en_xout     );
    if ((config_1p8v > Si2144_POWER_UP_CMD_CONFIG_1P8V_MAX)  || (config_1p8v < Si2144_POWER_UP_CMD_CONFIG_1P8V_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CONFIG_1P8V %d ", config_1p8v );
    if ((reserved3   > Si2144_POWER_UP_CMD_RESERVED3_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d "  , reserved3   );
    if ((reserved4   > Si2144_POWER_UP_CMD_RESERVED4_MAX  )  || (reserved4   < Si2144_POWER_UP_CMD_RESERVED4_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d "  , reserved4   );
    if ((reserved5   > Si2144_POWER_UP_CMD_RESERVED5_MAX  )  || (reserved5   < Si2144_POWER_UP_CMD_RESERVED5_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d "  , reserved5   );
    if ((reserved6   > Si2144_POWER_UP_CMD_RESERVED6_MAX  )  || (reserved6   < Si2144_POWER_UP_CMD_RESERVED6_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED6 %d "  , reserved6   );
    if ((reserved7   > Si2144_POWER_UP_CMD_RESERVED7_MAX  )  || (reserved7   < Si2144_POWER_UP_CMD_RESERVED7_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED7 %d "  , reserved7   );
    if ((reserved8   > Si2144_POWER_UP_CMD_RESERVED8_MAX  )  || (reserved8   < Si2144_POWER_UP_CMD_RESERVED8_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED8 %d "  , reserved8   );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_POWER_UP_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode     & Si2144_POWER_UP_CMD_SUBCODE_MASK     ) << Si2144_POWER_UP_CMD_SUBCODE_LSB    );
    cmdByteBuffer[2] = (unsigned char) ( ( clock_mode  & Si2144_POWER_UP_CMD_CLOCK_MODE_MASK  ) << Si2144_POWER_UP_CMD_CLOCK_MODE_LSB |
                                         ( en_xout     & Si2144_POWER_UP_CMD_EN_XOUT_MASK     ) << Si2144_POWER_UP_CMD_EN_XOUT_LSB    );
    cmdByteBuffer[3] = (unsigned char) ( ( config_1p8v & Si2144_POWER_UP_CMD_CONFIG_1P8V_MASK ) << Si2144_POWER_UP_CMD_CONFIG_1P8V_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( reserved3   & Si2144_POWER_UP_CMD_RESERVED3_MASK   ) << Si2144_POWER_UP_CMD_RESERVED3_LSB  );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved4   & Si2144_POWER_UP_CMD_RESERVED4_MASK   ) << Si2144_POWER_UP_CMD_RESERVED4_LSB  );
    cmdByteBuffer[6] = (unsigned char) ( ( reserved5   & Si2144_POWER_UP_CMD_RESERVED5_MASK   ) << Si2144_POWER_UP_CMD_RESERVED5_LSB  );
    cmdByteBuffer[7] = (unsigned char) ( ( reserved6   & Si2144_POWER_UP_CMD_RESERVED6_MASK   ) << Si2144_POWER_UP_CMD_RESERVED6_LSB  );
    cmdByteBuffer[8] = (unsigned char) ( ( reserved7   & Si2144_POWER_UP_CMD_RESERVED7_MASK   ) << Si2144_POWER_UP_CMD_RESERVED7_LSB  );
    cmdByteBuffer[9] = (unsigned char) ( ( reserved8   & Si2144_POWER_UP_CMD_RESERVED8_MASK   ) << Si2144_POWER_UP_CMD_RESERVED8_LSB  );

    if (L0_WriteCommandBytes(api->i2c, 10, cmdByteBuffer) != 10) {
      SiTRACE("Error writing POWER_UP bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POWER_UP response\n");
      return error_code;
    }


    return NO_Si2144_ERROR;
}
#endif /* Si2144_POWER_UP_CMD */
#ifdef    Si2144_POWER_UP8_1_CMD
/*---------------------------------------------------*/
/* Si2144_POWER_UP8_1 COMMAND                           */
/*---------------------------------------------------*/
unsigned char Si2144_L1_POWER_UP8_1     (L1_Si2144_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout,
                                         unsigned char   config_1p8v,
                                         unsigned char   reserved3,
                                         unsigned char   reserved4,
                                         unsigned char   reserved5,
                                         unsigned char   reserved6)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->power_up8_1.STATUS = api->status;

    SiTRACE("Si2144 POWER_UP8_1 ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode     > Si2144_POWER_UP8_1_CMD_SUBCODE_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "    , subcode     );
    if ((clock_mode  > Si2144_POWER_UP8_1_CMD_CLOCK_MODE_MAX )  || (clock_mode  < Si2144_POWER_UP8_1_CMD_CLOCK_MODE_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d " , clock_mode  );
    if ((en_xout     > Si2144_POWER_UP8_1_CMD_EN_XOUT_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "    , en_xout     );
    if ((config_1p8v > Si2144_POWER_UP8_1_CMD_CONFIG_1P8V_MAX)  || (config_1p8v < Si2144_POWER_UP8_1_CMD_CONFIG_1P8V_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CONFIG_1P8V %d ", config_1p8v );
    if ((reserved3   > Si2144_POWER_UP8_1_CMD_RESERVED3_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d "  , reserved3   );
    if ((reserved4   > Si2144_POWER_UP8_1_CMD_RESERVED4_MAX  )  || (reserved4   < Si2144_POWER_UP8_1_CMD_RESERVED4_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d "  , reserved4   );
    if ((reserved5   > Si2144_POWER_UP8_1_CMD_RESERVED5_MAX  )  || (reserved5   < Si2144_POWER_UP8_1_CMD_RESERVED5_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d "  , reserved5   );
    if ((reserved6   > Si2144_POWER_UP8_1_CMD_RESERVED6_MAX  )  || (reserved6   < Si2144_POWER_UP8_1_CMD_RESERVED6_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED6 %d "  , reserved6   );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_POWER_UP8_1_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode     & Si2144_POWER_UP8_1_CMD_SUBCODE_MASK     ) << Si2144_POWER_UP8_1_CMD_SUBCODE_LSB    );
    cmdByteBuffer[2] = (unsigned char) ( ( clock_mode  & Si2144_POWER_UP8_1_CMD_CLOCK_MODE_MASK  ) << Si2144_POWER_UP8_1_CMD_CLOCK_MODE_LSB |
                                         ( en_xout     & Si2144_POWER_UP8_1_CMD_EN_XOUT_MASK     ) << Si2144_POWER_UP8_1_CMD_EN_XOUT_LSB    );
    cmdByteBuffer[3] = (unsigned char) ( ( config_1p8v & Si2144_POWER_UP8_1_CMD_CONFIG_1P8V_MASK ) << Si2144_POWER_UP8_1_CMD_CONFIG_1P8V_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( reserved3   & Si2144_POWER_UP8_1_CMD_RESERVED3_MASK   ) << Si2144_POWER_UP8_1_CMD_RESERVED3_LSB  );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved4   & Si2144_POWER_UP8_1_CMD_RESERVED4_MASK   ) << Si2144_POWER_UP8_1_CMD_RESERVED4_LSB  );
    cmdByteBuffer[6] = (unsigned char) ( ( reserved5   & Si2144_POWER_UP8_1_CMD_RESERVED5_MASK   ) << Si2144_POWER_UP8_1_CMD_RESERVED5_LSB  );
    cmdByteBuffer[7] = (unsigned char) ( ( reserved6   & Si2144_POWER_UP8_1_CMD_RESERVED6_MASK   ) << Si2144_POWER_UP8_1_CMD_RESERVED6_LSB  );

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing POWER_UP8_1 bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POWER_UP response\n");
      return error_code;
    }
    return NO_Si2144_ERROR;
}
#endif /* Si2144_POWER_UP8_1_CMD */
#ifdef    Si2144_POWER_UP8_2_CMD
/*---------------------------------------------------*/
/* Si2144_POWER_UP8_2 COMMAND                           */
/*---------------------------------------------------*/
unsigned char Si2144_L1_POWER_UP8_2     (L1_Si2144_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reserved7,
                                         unsigned char   reserved8)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->power_up8_2.STATUS = api->status;

    SiTRACE("Si2144 POWER_UP8_2 ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode   > Si2144_POWER_UP8_2_CMD_SUBCODE_MAX  )  || (subcode   < Si2144_POWER_UP8_2_CMD_SUBCODE_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "  , subcode   );
    if ((reserved7 > Si2144_POWER_UP8_2_CMD_RESERVED7_MAX)  || (reserved7 < Si2144_POWER_UP8_2_CMD_RESERVED7_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED7 %d ", reserved7 );
    if ((reserved8 > Si2144_POWER_UP8_2_CMD_RESERVED8_MAX)  || (reserved8 < Si2144_POWER_UP8_2_CMD_RESERVED8_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED8 %d ", reserved8 );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_POWER_UP8_2_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode   & Si2144_POWER_UP8_2_CMD_SUBCODE_MASK   ) << Si2144_POWER_UP8_2_CMD_SUBCODE_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( reserved7 & Si2144_POWER_UP8_2_CMD_RESERVED7_MASK ) << Si2144_POWER_UP8_2_CMD_RESERVED7_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( reserved8 & Si2144_POWER_UP8_2_CMD_RESERVED8_MASK ) << Si2144_POWER_UP8_2_CMD_RESERVED8_LSB);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing POWER_UP8_2 bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POWER_UP response\n");
      return error_code;
    }
    return NO_Si2144_ERROR;
}
#endif /* Si2144_POWER_UP8_2_CMD */
#ifdef    Si2144_REREAD_REPLY_CMD
/*---------------------------------------------------*/
/* Si2144_REREAD_REPLY COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2144_L1_REREAD_REPLY    (L1_Si2144_Context *api,
                                         unsigned char   offset)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[16];
    error_code = 0;
    api->rsp->reread_reply.STATUS = api->status;

    SiTRACE("Si2144 REREAD_REPLY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((offset > Si2144_REREAD_REPLY_CMD_OFFSET_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OFFSET %d ", offset );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_REREAD_REPLY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( offset & Si2144_REREAD_REPLY_CMD_OFFSET_MASK ) << Si2144_REREAD_REPLY_CMD_OFFSET_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing REREAD_REPLY bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 16, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling REREAD_REPLY response\n");
      return error_code;
    }

    api->rsp->reread_reply.reply1  = Si2144_convert_to_byte  (&rspByteBuffer[ 1] , Si2144_REREAD_REPLY_RESPONSE_REPLY1_LSB   , Si2144_REREAD_REPLY_RESPONSE_REPLY1_MASK  );
    api->rsp->reread_reply.reply2  = Si2144_convert_to_byte  (&rspByteBuffer[ 2] , Si2144_REREAD_REPLY_RESPONSE_REPLY2_LSB   , Si2144_REREAD_REPLY_RESPONSE_REPLY2_MASK  );
    api->rsp->reread_reply.reply3  = Si2144_convert_to_byte  (&rspByteBuffer[ 3] , Si2144_REREAD_REPLY_RESPONSE_REPLY3_LSB   , Si2144_REREAD_REPLY_RESPONSE_REPLY3_MASK  );
    api->rsp->reread_reply.reply4  = Si2144_convert_to_byte  (&rspByteBuffer[ 4] , Si2144_REREAD_REPLY_RESPONSE_REPLY4_LSB   , Si2144_REREAD_REPLY_RESPONSE_REPLY4_MASK  );
    api->rsp->reread_reply.reply5  = Si2144_convert_to_byte  (&rspByteBuffer[ 5] , Si2144_REREAD_REPLY_RESPONSE_REPLY5_LSB   , Si2144_REREAD_REPLY_RESPONSE_REPLY5_MASK  );
    api->rsp->reread_reply.reply6  = Si2144_convert_to_byte  (&rspByteBuffer[ 6] , Si2144_REREAD_REPLY_RESPONSE_REPLY6_LSB   , Si2144_REREAD_REPLY_RESPONSE_REPLY6_MASK  );
    api->rsp->reread_reply.reply7  = Si2144_convert_to_byte  (&rspByteBuffer[ 7] , Si2144_REREAD_REPLY_RESPONSE_REPLY7_LSB   , Si2144_REREAD_REPLY_RESPONSE_REPLY7_MASK  );
    api->rsp->reread_reply.reply8  = Si2144_convert_to_byte  (&rspByteBuffer[ 8] , Si2144_REREAD_REPLY_RESPONSE_REPLY8_LSB   , Si2144_REREAD_REPLY_RESPONSE_REPLY8_MASK  );
    api->rsp->reread_reply.reply9  = Si2144_convert_to_byte  (&rspByteBuffer[ 9] , Si2144_REREAD_REPLY_RESPONSE_REPLY9_LSB   , Si2144_REREAD_REPLY_RESPONSE_REPLY9_MASK  );
    api->rsp->reread_reply.reply10 = Si2144_convert_to_byte  (&rspByteBuffer[10] , Si2144_REREAD_REPLY_RESPONSE_REPLY10_LSB  , Si2144_REREAD_REPLY_RESPONSE_REPLY10_MASK );
    api->rsp->reread_reply.reply11 = Si2144_convert_to_byte  (&rspByteBuffer[11] , Si2144_REREAD_REPLY_RESPONSE_REPLY11_LSB  , Si2144_REREAD_REPLY_RESPONSE_REPLY11_MASK );
    api->rsp->reread_reply.reply12 = Si2144_convert_to_byte  (&rspByteBuffer[12] , Si2144_REREAD_REPLY_RESPONSE_REPLY12_LSB  , Si2144_REREAD_REPLY_RESPONSE_REPLY12_MASK );
    api->rsp->reread_reply.reply13 = Si2144_convert_to_byte  (&rspByteBuffer[13] , Si2144_REREAD_REPLY_RESPONSE_REPLY13_LSB  , Si2144_REREAD_REPLY_RESPONSE_REPLY13_MASK );
    api->rsp->reread_reply.reply14 = Si2144_convert_to_byte  (&rspByteBuffer[14] , Si2144_REREAD_REPLY_RESPONSE_REPLY14_LSB  , Si2144_REREAD_REPLY_RESPONSE_REPLY14_MASK );
    api->rsp->reread_reply.reply15 = Si2144_convert_to_byte  (&rspByteBuffer[15] , Si2144_REREAD_REPLY_RESPONSE_REPLY15_LSB  , Si2144_REREAD_REPLY_RESPONSE_REPLY15_MASK );

    return NO_Si2144_ERROR;
}
#endif /* Si2144_REREAD_REPLY_CMD */
#ifdef    Si2144_RESET_HW_CMD
/*---------------------------------------------------*/
/* Si2144_RESET_HW COMMAND                                 */
/*---------------------------------------------------*/
unsigned char Si2144_L1_RESET_HW        (L1_Si2144_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reserved1,
                                         unsigned char   reserved2)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[4];
    error_code = 0;
    api->rsp->reset_hw.STATUS = api->status;

    SiTRACE("Si2144 RESET_HW ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode   > Si2144_RESET_HW_CMD_SUBCODE_MAX  )  || (subcode   < Si2144_RESET_HW_CMD_SUBCODE_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "  , subcode   );
    if ((reserved1 > Si2144_RESET_HW_CMD_RESERVED1_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d ", reserved1 );
    if ((reserved2 > Si2144_RESET_HW_CMD_RESERVED2_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d ", reserved2 );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_RESET_HW_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode   & Si2144_RESET_HW_CMD_SUBCODE_MASK   ) << Si2144_RESET_HW_CMD_SUBCODE_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( reserved1 & Si2144_RESET_HW_CMD_RESERVED1_MASK ) << Si2144_RESET_HW_CMD_RESERVED1_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( reserved2 & Si2144_RESET_HW_CMD_RESERVED2_MASK ) << Si2144_RESET_HW_CMD_RESERVED2_LSB);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing RESET_HW bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }
    error_code = Si2144_pollForResetState(api);
    if (error_code) {
      SiTRACE("Error polling RESET_HW response\n");
      return error_code;
    }

    return NO_Si2144_ERROR;
}
#endif /* Si2144_RESET_HW_CMD */
#ifdef    Si2144_SET_PROPERTY_CMD
/*---------------------------------------------------*/
/* Si2144_SET_PROPERTY COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2144_L1_SET_PROPERTY    (L1_Si2144_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop,
                                         unsigned int    data)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[4];
    unsigned int shadowData;
    unsigned char res;
    error_code = 0;
    api->rsp->set_property.STATUS = api->status;

    res = Si2144_PackProperty(api->propShadow, prop, (signed   int *) &shadowData);

    if ((data != shadowData)  || (api->propertyWriteMode == DOWNLOAD_ALWAYS) || (res== ERROR_Si2144_UNKNOWN_PROPERTY) )
    {
        SiTRACE("Si2144 SET_PROPERTY prop 0x%04x data 0x%4x(%d)\n", prop, data, data);
        cmdByteBuffer[0] = Si2144_SET_PROPERTY_CMD;
        cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2144_SET_PROPERTY_CMD_RESERVED_MASK ) << Si2144_SET_PROPERTY_CMD_RESERVED_LSB);
        cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2144_SET_PROPERTY_CMD_PROP_MASK     ) << Si2144_SET_PROPERTY_CMD_PROP_LSB    );
        cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2144_SET_PROPERTY_CMD_PROP_MASK     ) << Si2144_SET_PROPERTY_CMD_PROP_LSB    )>>8);
        cmdByteBuffer[4] = (unsigned char) ( ( data     & Si2144_SET_PROPERTY_CMD_DATA_MASK     ) << Si2144_SET_PROPERTY_CMD_DATA_LSB    );
        cmdByteBuffer[5] = (unsigned char) ((( data     & Si2144_SET_PROPERTY_CMD_DATA_MASK     ) << Si2144_SET_PROPERTY_CMD_DATA_LSB    )>>8);

        if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
          SiTRACE("Error writing SET_PROPERTY bytes!\n");
          return ERROR_Si2144_SENDING_COMMAND;
        }

        error_code = Si2144_pollForResponse(api, 4, rspByteBuffer);
        if (error_code) {
          SiTRACE("Error polling SET_PROPERTY response\n");
          return error_code;
        }

        api->rsp->set_property.reserved = Si2144_convert_to_byte  (&rspByteBuffer[ 1] , Si2144_SET_PROPERTY_RESPONSE_RESERVED_LSB  , Si2144_SET_PROPERTY_RESPONSE_RESERVED_MASK );
        api->rsp->set_property.data     = Si2144_convert_to_uint  (&rspByteBuffer[ 2] , Si2144_SET_PROPERTY_RESPONSE_DATA_LSB      , Si2144_SET_PROPERTY_RESPONSE_DATA_MASK     );
       /* Update propShadow with latest data if correctly set */
        Si2144_UnpackProperty(api->propShadow, prop, data);
    }
    else
    {
        /* SiTRACE("Si2144_L1_SetProperty: Skipping Property Setting 0x%04x because value unchanged 0x%04x\n", prop,data); */

    }
    return NO_Si2144_ERROR;
}
#endif /* Si2144_SET_PROPERTY_CMD */
#ifdef    Si2144_STANDBY_CMD
/*---------------------------------------------------*/
/* Si2144_STANDBY COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2144_L1_STANDBY         (L1_Si2144_Context *api,
                                         unsigned char   type)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->standby.STATUS = api->status;

    SiTRACE("Si2144 STANDBY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((type > Si2144_STANDBY_CMD_TYPE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("TYPE %d ", type );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_STANDBY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( type & Si2144_STANDBY_CMD_TYPE_MASK ) << Si2144_STANDBY_CMD_TYPE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing STANDBY bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling STANDBY response\n");
      return error_code;
    }


    return NO_Si2144_ERROR;
}
#endif /* Si2144_STANDBY_CMD */
#ifdef    Si2144_TUNER_STATUS_CMD
/*---------------------------------------------------*/
/* Si2144_TUNER_STATUS COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2144_L1_TUNER_STATUS    (L1_Si2144_Context *api)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[12];
    error_code = 0;
    api->rsp->tuner_status.STATUS = api->status;

    SiTRACE("Si2144 TUNER_STATUS ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_TUNER_STATUS_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing TUNER_STATUS bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 12, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_STATUS response\n");
      return error_code;
    }

    api->rsp->tuner_status.rsvd1         = Si2144_convert_to_byte  (&rspByteBuffer[ 1] , Si2144_TUNER_STATUS_RESPONSE_RSVD1_LSB          , Si2144_TUNER_STATUS_RESPONSE_RSVD1_MASK         );
    api->rsp->tuner_status.rsvd2         = Si2144_convert_to_byte  (&rspByteBuffer[ 2] , Si2144_TUNER_STATUS_RESPONSE_RSVD2_LSB          , Si2144_TUNER_STATUS_RESPONSE_RSVD2_MASK         );
    api->rsp->tuner_status.rssi          = Si2144_convert_to_byte  (&rspByteBuffer[ 3] , Si2144_TUNER_STATUS_RESPONSE_RSSI_LSB           , Si2144_TUNER_STATUS_RESPONSE_RSSI_MASK          );
    api->rsp->tuner_status.freq          = Si2144_convert_to_ulong (&rspByteBuffer[ 4] , Si2144_TUNER_STATUS_RESPONSE_FREQ_LSB           , Si2144_TUNER_STATUS_RESPONSE_FREQ_MASK          );
    api->rsp->tuner_status.mode          = Si2144_convert_to_byte  (&rspByteBuffer[ 8] , Si2144_TUNER_STATUS_RESPONSE_MODE_LSB           , Si2144_TUNER_STATUS_RESPONSE_MODE_MASK          );
    api->rsp->tuner_status.wb_att_status = Si2144_convert_to_byte  (&rspByteBuffer[ 8] , Si2144_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_LSB  , Si2144_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_MASK );
    api->rsp->tuner_status.vco_code      = Si2144_convert_to_int   (&rspByteBuffer[10] , Si2144_TUNER_STATUS_RESPONSE_VCO_CODE_LSB       , Si2144_TUNER_STATUS_RESPONSE_VCO_CODE_MASK      );

    return NO_Si2144_ERROR;
}
#endif /* Si2144_TUNER_STATUS_CMD */
#ifdef    Si2144_TUNER_TUNE_FREQ_CMD
/*---------------------------------------------------*/
/* Si2144_TUNER_TUNE_FREQ COMMAND                   */
/*---------------------------------------------------*/
unsigned char Si2144_L1_TUNER_TUNE_FREQ (L1_Si2144_Context *api,
                                         unsigned char   mode,
                                         unsigned long   freq)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    error_code = 0;
    api->rsp->tuner_tune_freq.STATUS = api->status;

    SiTRACE("Si2144 TUNER_TUNE_FREQ mode %d, freq %d (Hz)\n", mode, freq);
  #ifdef   DEBUG_RANGE_CHECK
    if ((mode > Si2144_TUNER_TUNE_FREQ_CMD_MODE_MAX) ) {error_code++; SiTRACE("Out of range: mode\n");}
    if ((freq > Si2144_TUNER_TUNE_FREQ_CMD_FREQ_MAX)  || (freq < Si2144_TUNER_TUNE_FREQ_CMD_FREQ_MIN) ) {error_code++; SiTRACE("Out of range: freq\n");}
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    cmdByteBuffer[0] = Si2144_TUNER_TUNE_FREQ_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mode & Si2144_TUNER_TUNE_FREQ_CMD_MODE_MASK ) << Si2144_TUNER_TUNE_FREQ_CMD_MODE_LSB);
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( freq & Si2144_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2144_TUNER_TUNE_FREQ_CMD_FREQ_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( freq & Si2144_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2144_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ((( freq & Si2144_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2144_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>16);
    cmdByteBuffer[7] = (unsigned char) ((( freq & Si2144_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2144_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing TUNER_TUNE_FREQ bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    error_code = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_TUNE_FREQ response\n");
      return error_code;
    }


    return NO_Si2144_ERROR;
}
#endif /* Si2144_TUNER_TUNE_FREQ_CMD */
#ifdef    Si2144_WAKE_UP_CMD
/*---------------------------------------------------*/
/* Si2144_WAKE_UP COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2144_L1_WAKE_UP         (L1_Si2144_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reset,
                                         unsigned char   clock_freq,
                                         unsigned char   reserved9,
                                         unsigned char   func,
                                         unsigned char   wake_up)
{
    unsigned char error_code;
    unsigned char cmdByteBuffer[7];
    error_code = 0;
    api->rsp->wake_up.STATUS = api->status;

    SiTRACE("Si2144 WAKE_UP ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode     > Si2144_WAKE_UP_CMD_SUBCODE_MAX    )  || (subcode     < Si2144_WAKE_UP_CMD_SUBCODE_MIN    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "    , subcode     );
    if ((reset       > Si2144_WAKE_UP_CMD_RESET_MAX      )  || (reset       < Si2144_WAKE_UP_CMD_RESET_MIN      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESET %d "      , reset       );
    if ((clock_freq  > Si2144_WAKE_UP_CMD_CLOCK_FREQ_MAX )  || (clock_freq  < Si2144_WAKE_UP_CMD_CLOCK_FREQ_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_FREQ %d " , clock_freq  );
    if ((reserved9   > Si2144_WAKE_UP_CMD_RESERVED9_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED9 %d "  , reserved9   );
    if ((func        > Si2144_WAKE_UP_CMD_FUNC_MAX       ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "       , func        );
    if ((wake_up     > Si2144_WAKE_UP_CMD_WAKE_UP_MAX    )  || (wake_up     < Si2144_WAKE_UP_CMD_WAKE_UP_MIN    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("WAKE_UP %d "    , wake_up     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2144_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2144_WAKE_UP_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode     & Si2144_WAKE_UP_CMD_SUBCODE_MASK     ) << Si2144_WAKE_UP_CMD_SUBCODE_LSB    );
    cmdByteBuffer[2] = (unsigned char) ( ( reset       & Si2144_WAKE_UP_CMD_RESET_MASK       ) << Si2144_WAKE_UP_CMD_RESET_LSB      );
    cmdByteBuffer[3] = (unsigned char) ( ( clock_freq  & Si2144_WAKE_UP_CMD_CLOCK_FREQ_MASK  ) << Si2144_WAKE_UP_CMD_CLOCK_FREQ_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved9   & Si2144_WAKE_UP_CMD_RESERVED9_MASK   ) << Si2144_WAKE_UP_CMD_RESERVED9_LSB  );
    cmdByteBuffer[5] = (unsigned char) ( ( func        & Si2144_WAKE_UP_CMD_FUNC_MASK        ) << Si2144_WAKE_UP_CMD_FUNC_LSB       );
    cmdByteBuffer[6] = (unsigned char) ( ( wake_up     & Si2144_WAKE_UP_CMD_WAKE_UP_MASK     ) << Si2144_WAKE_UP_CMD_WAKE_UP_LSB    );

    if (L0_WriteCommandBytes(api->i2c, 7, cmdByteBuffer) != 7) {
      SiTRACE("Error writing WAKE_UP bytes!\n");
      return ERROR_Si2144_SENDING_COMMAND;
    }

    /* wait 5 ms to allow the firmware to start up */
    system_wait(5);

    /* check for CTS only */
    error_code = Si2144_pollForCTS(api);
    if (error_code) {
      SiTRACE("Error polling WAKE_UP response\n");
      return error_code;
    }
    return NO_Si2144_ERROR;
}
#endif /* Si2144_WAKE_UP_CMD */


  /* --------------------------------------------*/
  /* SEND_COMMAND2 FUNCTION                      */
  /* --------------------------------------------*/
unsigned char   Si2144_L1_SendCommand2(L1_Si2144_Context *api, unsigned int cmd_code) {
    switch (cmd_code) {
    #ifdef        Si2144_AGC_OVERRIDE_CMD
     case         Si2144_AGC_OVERRIDE_CMD_CODE:
       return Si2144_L1_AGC_OVERRIDE (api, api->cmd->agc_override.force_max_gain, api->cmd->agc_override.force_top_gain );
     break;
    #endif /*     Si2144_AGC_OVERRIDE_CMD */
    #ifdef        Si2144_CONFIG_CLOCKS_CMD
     case         Si2144_CONFIG_CLOCKS_CMD_CODE:
       return Si2144_L1_CONFIG_CLOCKS (api, api->cmd->config_clocks.subcode, api->cmd->config_clocks.clock_mode, api->cmd->config_clocks.en_xout );
     break;
    #endif /*     Si2144_CONFIG_CLOCKS_CMD */
    #ifdef        Si2144_CONFIG_I2C_CMD
     case         Si2144_CONFIG_I2C_CMD_CODE:
       return Si2144_L1_CONFIG_I2C (api, api->cmd->config_i2c.subcode, api->cmd->config_i2c.i2c_broadcast );
     break;
    #endif /*     Si2144_CONFIG_I2C_CMD */
    #ifdef        Si2144_CONFIG_PINS_CMD
     case         Si2144_CONFIG_PINS_CMD_CODE:
       return Si2144_L1_CONFIG_PINS (api, api->cmd->config_pins.gpio1_mode, api->cmd->config_pins.gpio1_read, api->cmd->config_pins.gpio2_mode, api->cmd->config_pins.gpio2_read, api->cmd->config_pins.agc1_mode, api->cmd->config_pins.agc1_read, api->cmd->config_pins.agc2_mode, api->cmd->config_pins.agc2_read, api->cmd->config_pins.xout_mode );
     break;
    #endif /*     Si2144_CONFIG_PINS_CMD */
    #ifdef        Si2144_EXIT_BOOTLOADER_CMD
     case         Si2144_EXIT_BOOTLOADER_CMD_CODE:
       return Si2144_L1_EXIT_BOOTLOADER (api, api->cmd->exit_bootloader.func, api->cmd->exit_bootloader.ctsien );
     break;
    #endif /*     Si2144_EXIT_BOOTLOADER_CMD */
    #ifdef        Si2144_FINE_TUNE_CMD
     case         Si2144_FINE_TUNE_CMD_CODE:
       return Si2144_L1_FINE_TUNE (api, api->cmd->fine_tune.persistence, api->cmd->fine_tune.offset_500hz );
     break;
    #endif /*     Si2144_FINE_TUNE_CMD */
    #ifdef        Si2144_GET_PROPERTY_CMD
     case         Si2144_GET_PROPERTY_CMD_CODE:
       return Si2144_L1_GET_PROPERTY (api, api->cmd->get_property.reserved, api->cmd->get_property.prop );
     break;
    #endif /*     Si2144_GET_PROPERTY_CMD */
    #ifdef        Si2144_GET_REV_CMD
     case         Si2144_GET_REV_CMD_CODE:
       return Si2144_L1_GET_REV (api );
     break;
    #endif /*     Si2144_GET_REV_CMD */
    #ifdef        Si2144_PART_INFO_CMD
     case         Si2144_PART_INFO_CMD_CODE:
       return Si2144_L1_PART_INFO (api );
     break;
    #endif /*     Si2144_PART_INFO_CMD */
    #ifdef        Si2144_PART_INFO2_CMD
     case         Si2144_PART_INFO2_CMD_CODE:
       return Si2144_L1_PART_INFO2 (api );
     break;
    #endif /*     Si2144_PART_INFO2_CMD */
    #ifdef        Si2144_POLL_CTS_CMD
     case         Si2144_POLL_CTS_CMD_CODE:
       return Si2144_L1_POLL_CTS (api );
     break;
    #endif /*     Si2144_POLL_CTS_CMD */
    #ifdef        Si2144_POWER_DOWN_HW_CMD
     case         Si2144_POWER_DOWN_HW_CMD_CODE:
       return Si2144_L1_POWER_DOWN_HW (api, api->cmd->power_down_hw.subcode, api->cmd->power_down_hw.pdb_xo_osc, api->cmd->power_down_hw.reserved1, api->cmd->power_down_hw.en_xout, api->cmd->power_down_hw.reserved2, api->cmd->power_down_hw.reserved3, api->cmd->power_down_hw.reserved4, api->cmd->power_down_hw.reserved5, api->cmd->power_down_hw.reserved6, api->cmd->power_down_hw.reserved7, api->cmd->power_down_hw.reserved8, api->cmd->power_down_hw.reserved9 );
     break;
    #endif /*     Si2144_POWER_DOWN_HW_CMD */
    #ifdef        Si2144_POWER_UP_CMD
     case         Si2144_POWER_UP_CMD_CODE:
       return Si2144_L1_POWER_UP (api, api->cmd->power_up.subcode, api->cmd->power_up.clock_mode, api->cmd->power_up.en_xout, api->cmd->power_up.config_1p8v, api->cmd->power_up.reserved3, api->cmd->power_up.reserved4, api->cmd->power_up.reserved5, api->cmd->power_up.reserved6, api->cmd->power_up.reserved7, api->cmd->power_up.reserved8 );
     break;
    #endif /*     Si2144_POWER_UP_CMD */
    #ifdef        Si2144_POWER_UP8_1_CMD
     case         Si2144_POWER_UP8_1_CMD_CODE:
       return Si2144_L1_POWER_UP8_1 (api, api->cmd->power_up8_1.subcode, api->cmd->power_up8_1.clock_mode, api->cmd->power_up8_1.en_xout, api->cmd->power_up8_1.config_1p8v, api->cmd->power_up8_1.reserved3, api->cmd->power_up8_1.reserved4, api->cmd->power_up8_1.reserved5, api->cmd->power_up8_1.reserved6 );
     break;
    #endif /*     Si2144_POWER_UP8_1_CMD */
    #ifdef        Si2144_POWER_UP8_2_CMD
     case         Si2144_POWER_UP8_2_CMD_CODE:
       return Si2144_L1_POWER_UP8_2 (api, api->cmd->power_up8_2.subcode, api->cmd->power_up8_2.reserved7, api->cmd->power_up8_2.reserved8 );
     break;
    #endif /*     Si2144_POWER_UP8_2_CMD */
    #ifdef        Si2144_REREAD_REPLY_CMD
     case         Si2144_REREAD_REPLY_CMD_CODE:
       return Si2144_L1_REREAD_REPLY (api, api->cmd->reread_reply.offset );
     break;
    #endif /*     Si2144_REREAD_REPLY_CMD */
    #ifdef        Si2144_RESET_HW_CMD
     case         Si2144_RESET_HW_CMD_CODE:
       return Si2144_L1_RESET_HW (api, api->cmd->reset_hw.subcode, api->cmd->reset_hw.reserved1, api->cmd->reset_hw.reserved2 );
     break;
    #endif /*     Si2144_RESET_HW_CMD */
    #ifdef        Si2144_SET_PROPERTY_CMD
     case         Si2144_SET_PROPERTY_CMD_CODE:
       return Si2144_L1_SET_PROPERTY (api, api->cmd->set_property.reserved, api->cmd->set_property.prop, api->cmd->set_property.data );
     break;
    #endif /*     Si2144_SET_PROPERTY_CMD */
    #ifdef        Si2144_STANDBY_CMD
     case         Si2144_STANDBY_CMD_CODE:
       return Si2144_L1_STANDBY (api, api->cmd->standby.type );
     break;
    #endif /*     Si2144_STANDBY_CMD */
    #ifdef        Si2144_TUNER_STATUS_CMD
     case         Si2144_TUNER_STATUS_CMD_CODE:
       return Si2144_L1_TUNER_STATUS (api );
     break;
    #endif /*     Si2144_TUNER_STATUS_CMD */
    #ifdef        Si2144_TUNER_TUNE_FREQ_CMD
     case         Si2144_TUNER_TUNE_FREQ_CMD_CODE:
       return Si2144_L1_TUNER_TUNE_FREQ (api, api->cmd->tuner_tune_freq.mode, api->cmd->tuner_tune_freq.freq );
     break;
    #endif /*     Si2144_TUNER_TUNE_FREQ_CMD */
    #ifdef        Si2144_WAKE_UP_CMD
     case         Si2144_WAKE_UP_CMD_CODE:
       return Si2144_L1_WAKE_UP (api, api->cmd->wake_up.subcode, api->cmd->wake_up.reset, api->cmd->wake_up.clock_freq, api->cmd->wake_up.reserved9, api->cmd->wake_up.func, api->cmd->wake_up.wake_up );
     break;
    #endif /*     Si2144_WAKE_UP_CMD */
   default : break;
    }
     return 0;
  }

#ifdef    Si2144_GET_COMMAND_STRINGS

  /* --------------------------------------------*/
  /* GET_COMMAND_RESPONSE_STRING FUNCTION        */
  /* --------------------------------------------*/
unsigned char   Si2144_L1_GetCommandResponseString(L1_Si2144_Context *api, unsigned int cmd_code, const char *separator, char *msg) {
    switch (cmd_code) {
    #ifdef        Si2144_AGC_OVERRIDE_CMD
     case         Si2144_AGC_OVERRIDE_CMD_CODE:
      snprintf(msg,1000,"AGC_OVERRIDE ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->agc_override.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->agc_override.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->agc_override.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->agc_override.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->agc_override.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->agc_override.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->agc_override.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->agc_override.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->agc_override.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->agc_override.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->agc_override.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->agc_override.STATUS->cts);
     break;
    #endif /*     Si2144_AGC_OVERRIDE_CMD */

    #ifdef        Si2144_CONFIG_CLOCKS_CMD
     case         Si2144_CONFIG_CLOCKS_CMD_CODE:
      snprintf(msg,1000,"CONFIG_CLOCKS ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->config_clocks.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_clocks.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clocks.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->config_clocks.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_clocks.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clocks.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->config_clocks.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->config_clocks.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clocks.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->config_clocks.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->config_clocks.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_clocks.STATUS->cts);
     break;
    #endif /*     Si2144_CONFIG_CLOCKS_CMD */

    #ifdef        Si2144_CONFIG_I2C_CMD
     case         Si2144_CONFIG_I2C_CMD_CODE:
      snprintf(msg,1000,"CONFIG_I2C ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->config_i2c.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_i2c.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_i2c.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->config_i2c.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_i2c.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_i2c.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->config_i2c.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->config_i2c.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_i2c.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->config_i2c.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->config_i2c.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                   STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_i2c.STATUS->cts);
     break;
    #endif /*     Si2144_CONFIG_I2C_CMD */

    #ifdef        Si2144_CONFIG_PINS_CMD
     case         Si2144_CONFIG_PINS_CMD_CODE:
      snprintf(msg,1000,"CONFIG_PINS ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT      ",1000);
           if  (api->rsp->config_pins.STATUS->tunint      ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_pins.STATUS->tunint      ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT      ",1000);
           if  (api->rsp->config_pins.STATUS->dtvint      ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->config_pins.STATUS->dtvint      ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR         ",1000);
           if  (api->rsp->config_pins.STATUS->err         ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->config_pins.STATUS->err         ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS         ",1000);
           if  (api->rsp->config_pins.STATUS->cts         ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->config_pins.STATUS->cts         ==     0) strncat(msg,"WAIT     ",1000);
      else                                                         STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.STATUS->cts);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GPIO1_MODE  ",1000);
           if  (api->rsp->config_pins.gpio1_mode  ==     1) strncat(msg,"DISABLE        ",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     2) strncat(msg,"DRIVE_0        ",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     3) strncat(msg,"DRIVE_1        ",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     7) strncat(msg,"DTV_FREEZE_HIGH",1000);
      else if  (api->rsp->config_pins.gpio1_mode  ==     8) strncat(msg,"DTV_FREEZE_LOW ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.gpio1_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GPIO1_STATE ",1000);
           if  (api->rsp->config_pins.gpio1_state ==     0) strncat(msg,"READ_0",1000);
      else if  (api->rsp->config_pins.gpio1_state ==     1) strncat(msg,"READ_1",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.gpio1_state);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GPIO2_MODE  ",1000);
           if  (api->rsp->config_pins.gpio2_mode  ==     1) strncat(msg,"DISABLE        ",1000);
      else if  (api->rsp->config_pins.gpio2_mode  ==     2) strncat(msg,"DRIVE_0        ",1000);
      else if  (api->rsp->config_pins.gpio2_mode  ==     3) strncat(msg,"DRIVE_1        ",1000);
      else if  (api->rsp->config_pins.gpio2_mode  ==     7) strncat(msg,"DTV_FREEZE_HIGH",1000);
      else if  (api->rsp->config_pins.gpio2_mode  ==     8) strncat(msg,"DTV_FREEZE_LOW ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.gpio2_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-GPIO2_STATE ",1000);
           if  (api->rsp->config_pins.gpio2_state ==     0) strncat(msg,"READ_0",1000);
      else if  (api->rsp->config_pins.gpio2_state ==     1) strncat(msg,"READ_1",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.gpio2_state);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AGC1_MODE   ",1000);
           if  (api->rsp->config_pins.agc1_mode   ==     1) strncat(msg,"DISABLE        ",1000);
      else if  (api->rsp->config_pins.agc1_mode   ==     2) strncat(msg,"DRIVE_0        ",1000);
      else if  (api->rsp->config_pins.agc1_mode   ==     3) strncat(msg,"DRIVE_1        ",1000);
      else if  (api->rsp->config_pins.agc1_mode   ==     5) strncat(msg,"DTV_AGC        ",1000);
      else if  (api->rsp->config_pins.agc1_mode   ==     7) strncat(msg,"DTV_FREEZE_HIGH",1000);
      else if  (api->rsp->config_pins.agc1_mode   ==     8) strncat(msg,"DTV_FREEZE_LOW ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.agc1_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AGC1_STATE  ",1000);
           if  (api->rsp->config_pins.agc1_state  ==     0) strncat(msg,"READ_0",1000);
      else if  (api->rsp->config_pins.agc1_state  ==     1) strncat(msg,"READ_1",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.agc1_state);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AGC2_MODE   ",1000);
           if  (api->rsp->config_pins.agc2_mode   ==     1) strncat(msg,"DISABLE        ",1000);
      else if  (api->rsp->config_pins.agc2_mode   ==     5) strncat(msg,"DTV_AGC        ",1000);
      else if  (api->rsp->config_pins.agc2_mode   ==     7) strncat(msg,"DTV_FREEZE_HIGH",1000);
      else if  (api->rsp->config_pins.agc2_mode   ==     8) strncat(msg,"DTV_FREEZE_LOW ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.agc2_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-AGC2_STATE  ",1000);
           if  (api->rsp->config_pins.agc2_state  ==     0) strncat(msg,"READ_0",1000);
      else if  (api->rsp->config_pins.agc2_state  ==     1) strncat(msg,"READ_1",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.agc2_state);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-XOUT_MODE   ",1000);
           if  (api->rsp->config_pins.xout_mode   ==     1) strncat(msg,"DISABLE      ",1000);
      else if  (api->rsp->config_pins.xout_mode   ==     2) strncat(msg,"DRIVE_0      ",1000);
      else if  (api->rsp->config_pins.xout_mode   ==     3) strncat(msg,"DRIVE_1      ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.xout_mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-XOUT_STATE  ",1000);
           if  (api->rsp->config_pins.xout_state  ==     0) strncat(msg,"READ_0",1000);
      else if  (api->rsp->config_pins.xout_state  ==     1) strncat(msg,"READ_1",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->config_pins.xout_state);
     break;
    #endif /*     Si2144_CONFIG_PINS_CMD */

    #ifdef        Si2144_EXIT_BOOTLOADER_CMD
     case         Si2144_EXIT_BOOTLOADER_CMD_CODE:
      snprintf(msg,1000,"EXIT_BOOTLOADER ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->exit_bootloader.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->exit_bootloader.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->exit_bootloader.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->exit_bootloader.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->exit_bootloader.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->exit_bootloader.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->exit_bootloader.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->exit_bootloader.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->exit_bootloader.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->exit_bootloader.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->exit_bootloader.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->exit_bootloader.STATUS->cts);
     break;
    #endif /*     Si2144_EXIT_BOOTLOADER_CMD */

    #ifdef        Si2144_FINE_TUNE_CMD
     case         Si2144_FINE_TUNE_CMD_CODE:
      snprintf(msg,1000,"FINE_TUNE ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->fine_tune.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->fine_tune.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->fine_tune.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->fine_tune.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->fine_tune.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->fine_tune.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->fine_tune.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->fine_tune.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->fine_tune.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->fine_tune.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->fine_tune.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->fine_tune.STATUS->cts);
     break;
    #endif /*     Si2144_FINE_TUNE_CMD */

    #ifdef        Si2144_GET_PROPERTY_CMD
     case         Si2144_GET_PROPERTY_CMD_CODE:
      snprintf(msg,1000,"GET_PROPERTY ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT   ",1000);
           if  (api->rsp->get_property.STATUS->tunint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->get_property.STATUS->tunint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT   ",1000);
           if  (api->rsp->get_property.STATUS->dtvint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->get_property.STATUS->dtvint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR      ",1000);
           if  (api->rsp->get_property.STATUS->err      ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->get_property.STATUS->err      ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS      ",1000);
           if  (api->rsp->get_property.STATUS->cts      ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->get_property.STATUS->cts      ==     0) strncat(msg,"WAIT     ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_property.STATUS->cts);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_property.reserved);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA     ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_property.data);
     break;
    #endif /*     Si2144_GET_PROPERTY_CMD */

    #ifdef        Si2144_GET_REV_CMD
     case         Si2144_GET_REV_CMD_CODE:
      snprintf(msg,1000,"GET_REV ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT   ",1000);
           if  (api->rsp->get_rev.STATUS->tunint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->get_rev.STATUS->tunint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT   ",1000);
           if  (api->rsp->get_rev.STATUS->dtvint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->get_rev.STATUS->dtvint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR      ",1000);
           if  (api->rsp->get_rev.STATUS->err      ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->get_rev.STATUS->err      ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS      ",1000);
           if  (api->rsp->get_rev.STATUS->cts      ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->get_rev.STATUS->cts      ==     0) strncat(msg,"WAIT     ",1000);
      else                                                  STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.STATUS->cts);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PN       ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_rev.pn);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FWMAJOR  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_rev.fwmajor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FWMINOR  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_rev.fwminor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PATCH    ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_rev.patch);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CMPMAJOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_rev.cmpmajor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CMPMINOR ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_rev.cmpminor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CMPBUILD ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_rev.cmpbuild);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CHIPREV  ",1000);
           if  (api->rsp->get_rev.chiprev  ==     1) strncat(msg,"A",1000);
      else if  (api->rsp->get_rev.chiprev  ==     2) strncat(msg,"B",1000);
      else                                          STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->get_rev.chiprev);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PN2      ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->get_rev.pn2);
     break;
    #endif /*     Si2144_GET_REV_CMD */

    #ifdef        Si2144_PART_INFO_CMD
     case         Si2144_PART_INFO_CMD_CODE:
      snprintf(msg,1000,"PART_INFO ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT   ",1000);
           if  (api->rsp->part_info.STATUS->tunint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->part_info.STATUS->tunint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT   ",1000);
           if  (api->rsp->part_info.STATUS->dtvint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->part_info.STATUS->dtvint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR      ",1000);
           if  (api->rsp->part_info.STATUS->err      ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->part_info.STATUS->err      ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS      ",1000);
           if  (api->rsp->part_info.STATUS->cts      ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->part_info.STATUS->cts      ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.STATUS->cts);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CHIPREV  ",1000);
           if  (api->rsp->part_info.chiprev  ==     1) strncat(msg,"A",1000);
      else if  (api->rsp->part_info.chiprev  ==     2) strncat(msg,"B",1000);
      else                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info.chiprev);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PART     ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info.part);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PMAJOR   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info.pmajor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PMINOR   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info.pminor);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PBUILD   ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info.pbuild);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info.reserved);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SERIAL   ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->part_info.serial);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ROMID    ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info.romid);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PART2    ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info.part2);
     break;
    #endif /*     Si2144_PART_INFO_CMD */

    #ifdef        Si2144_PART_INFO2_CMD
     case         Si2144_PART_INFO2_CMD_CODE:
      snprintf(msg,1000,"PART_INFO2 ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT   ",1000);
           if  (api->rsp->part_info2.STATUS->tunint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->part_info2.STATUS->tunint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info2.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT   ",1000);
           if  (api->rsp->part_info2.STATUS->dtvint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->part_info2.STATUS->dtvint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info2.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR      ",1000);
           if  (api->rsp->part_info2.STATUS->err      ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->part_info2.STATUS->err      ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info2.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS      ",1000);
           if  (api->rsp->part_info2.STATUS->cts      ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->part_info2.STATUS->cts      ==     0) strncat(msg,"WAIT     ",1000);
      else                                                     STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->part_info2.STATUS->cts);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ROMID    ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info2.romid);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-PART2    ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info2.part2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->part_info2.reserved);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-SERIAL   ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->part_info2.serial);
     break;
    #endif /*     Si2144_PART_INFO2_CMD */

    #ifdef        Si2144_POLL_CTS_CMD
     case         Si2144_POLL_CTS_CMD_CODE:
      snprintf(msg,1000,"POLL_CTS ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->poll_cts.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->poll_cts.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->poll_cts.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->poll_cts.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->poll_cts.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->poll_cts.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->poll_cts.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->poll_cts.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->poll_cts.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->poll_cts.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->poll_cts.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->poll_cts.STATUS->cts);
     break;
    #endif /*     Si2144_POLL_CTS_CMD */

    #ifdef        Si2144_POWER_DOWN_HW_CMD
     case         Si2144_POWER_DOWN_HW_CMD_CODE:
      snprintf(msg,1000,"POWER_DOWN_HW ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->power_down_hw.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_down_hw.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_down_hw.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->power_down_hw.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_down_hw.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_down_hw.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->power_down_hw.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->power_down_hw.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_down_hw.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->power_down_hw.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->power_down_hw.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_down_hw.STATUS->cts);
     break;
    #endif /*     Si2144_POWER_DOWN_HW_CMD */

    #ifdef        Si2144_POWER_UP_CMD
     case         Si2144_POWER_UP_CMD_CODE:
      snprintf(msg,1000,"POWER_UP ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->power_up.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_up.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->power_up.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_up.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->power_up.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->power_up.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->power_up.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->power_up.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up.STATUS->cts);
     break;
    #endif /*     Si2144_POWER_UP_CMD */

    #ifdef        Si2144_POWER_UP8_1_CMD
     case         Si2144_POWER_UP8_1_CMD_CODE:
      snprintf(msg,1000,"POWER_UP8_1 ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->power_up8_1.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_up8_1.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up8_1.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->power_up8_1.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_up8_1.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up8_1.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->power_up8_1.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->power_up8_1.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up8_1.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->power_up8_1.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->power_up8_1.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up8_1.STATUS->cts);
     break;
    #endif /*     Si2144_POWER_UP8_1_CMD */

    #ifdef        Si2144_POWER_UP8_2_CMD
     case         Si2144_POWER_UP8_2_CMD_CODE:
      snprintf(msg,1000,"POWER_UP8_2 ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->power_up8_2.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_up8_2.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up8_2.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->power_up8_2.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->power_up8_2.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up8_2.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->power_up8_2.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->power_up8_2.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up8_2.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->power_up8_2.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->power_up8_2.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->power_up8_2.STATUS->cts);
     break;
    #endif /*     Si2144_POWER_UP8_2_CMD */

    #ifdef        Si2144_REREAD_REPLY_CMD
     case         Si2144_REREAD_REPLY_CMD_CODE:
      snprintf(msg,1000,"REREAD_REPLY ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT  ",1000);
           if  (api->rsp->reread_reply.STATUS->tunint  ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->reread_reply.STATUS->tunint  ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->reread_reply.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT  ",1000);
           if  (api->rsp->reread_reply.STATUS->dtvint  ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->reread_reply.STATUS->dtvint  ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->reread_reply.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR     ",1000);
           if  (api->rsp->reread_reply.STATUS->err     ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->reread_reply.STATUS->err     ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->reread_reply.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS     ",1000);
           if  (api->rsp->reread_reply.STATUS->cts     ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->reread_reply.STATUS->cts     ==     0) strncat(msg,"WAIT     ",1000);
      else                                                      STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->reread_reply.STATUS->cts);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY1  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply1);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY2  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY3  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply3);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY4  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply4);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY5  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply5);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY6  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply6);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY7  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply7);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY8  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply8);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY9  ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply9);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY10 ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply10);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY11 ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply11);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY12 ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply12);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY13 ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply13);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY14 ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply14);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-REPLY15 ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->reread_reply.reply15);
     break;
    #endif /*     Si2144_REREAD_REPLY_CMD */

    #ifdef        Si2144_RESET_HW_CMD
     case         Si2144_RESET_HW_CMD_CODE:
      snprintf(msg,1000,"RESET_HW ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->reset_hw.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->reset_hw.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->reset_hw.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->reset_hw.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->reset_hw.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->reset_hw.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->reset_hw.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->reset_hw.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->reset_hw.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->reset_hw.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->reset_hw.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                 STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->reset_hw.STATUS->cts);
     break;
    #endif /*     Si2144_RESET_HW_CMD */

    #ifdef        Si2144_SET_PROPERTY_CMD
     case         Si2144_SET_PROPERTY_CMD_CODE:
      snprintf(msg,1000,"SET_PROPERTY ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT   ",1000);
           if  (api->rsp->set_property.STATUS->tunint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->set_property.STATUS->tunint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT   ",1000);
           if  (api->rsp->set_property.STATUS->dtvint   ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->set_property.STATUS->dtvint   ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR      ",1000);
           if  (api->rsp->set_property.STATUS->err      ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->set_property.STATUS->err      ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS      ",1000);
           if  (api->rsp->set_property.STATUS->cts      ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->set_property.STATUS->cts      ==     0) strncat(msg,"WAIT     ",1000);
      else                                                       STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->set_property.STATUS->cts);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RESERVED ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->set_property.reserved);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DATA     ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->set_property.data);
     break;
    #endif /*     Si2144_SET_PROPERTY_CMD */

    #ifdef        Si2144_STANDBY_CMD
     case         Si2144_STANDBY_CMD_CODE:
      snprintf(msg,1000,"STANDBY ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->standby.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->standby.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->standby.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->standby.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->standby.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->standby.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->standby.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->standby.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->standby.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->standby.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->standby.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->standby.STATUS->cts);
     break;
    #endif /*     Si2144_STANDBY_CMD */

    #ifdef        Si2144_TUNER_STATUS_CMD
     case         Si2144_TUNER_STATUS_CMD_CODE:
      snprintf(msg,1000,"TUNER_STATUS ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT        ",1000);
           if  (api->rsp->tuner_status.STATUS->tunint        ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->tuner_status.STATUS->tunint        ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_status.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT        ",1000);
           if  (api->rsp->tuner_status.STATUS->dtvint        ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->tuner_status.STATUS->dtvint        ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_status.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR           ",1000);
           if  (api->rsp->tuner_status.STATUS->err           ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->tuner_status.STATUS->err           ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_status.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS           ",1000);
           if  (api->rsp->tuner_status.STATUS->cts           ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->tuner_status.STATUS->cts           ==     0) strncat(msg,"WAIT     ",1000);
      else                                                            STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_status.STATUS->cts);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RSVD1         ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->tuner_status.rsvd1);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RSVD2         ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->tuner_status.rsvd2);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-RSSI          ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->tuner_status.rssi);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-FREQ          ",1000); STRING_APPEND_SAFE(msg,1000,"%ld", api->rsp->tuner_status.freq);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-MODE          ",1000);
           if  (api->rsp->tuner_status.mode          ==     0) strncat(msg,"DTV",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_status.mode);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-WB_ATT_STATUS ",1000);
           if  (api->rsp->tuner_status.wb_att_status ==     0) strncat(msg,"OFF",1000);
      else if  (api->rsp->tuner_status.wb_att_status ==     1) strncat(msg,"ON ",1000);
      else                                                    STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_status.wb_att_status);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-VCO_CODE      ",1000); STRING_APPEND_SAFE(msg,1000,"%d" , api->rsp->tuner_status.vco_code);
     break;
    #endif /*     Si2144_TUNER_STATUS_CMD */

    #ifdef        Si2144_TUNER_TUNE_FREQ_CMD
     case         Si2144_TUNER_TUNE_FREQ_CMD_CODE:
      snprintf(msg,1000,"TUNER_TUNE_FREQ ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->tuner_tune_freq.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->tuner_tune_freq.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_tune_freq.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->tuner_tune_freq.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->tuner_tune_freq.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_tune_freq.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->tuner_tune_freq.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->tuner_tune_freq.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_tune_freq.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->tuner_tune_freq.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->tuner_tune_freq.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                        STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->tuner_tune_freq.STATUS->cts);
     break;
    #endif /*     Si2144_TUNER_TUNE_FREQ_CMD */

    #ifdef        Si2144_WAKE_UP_CMD
     case         Si2144_WAKE_UP_CMD_CODE:
      snprintf(msg,1000,"WAKE_UP ");
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-TUNINT ",1000);
           if  (api->rsp->wake_up.STATUS->tunint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->wake_up.STATUS->tunint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->wake_up.STATUS->tunint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-DTVINT ",1000);
           if  (api->rsp->wake_up.STATUS->dtvint ==     0) strncat(msg,"NOT_TRIGGERED",1000);
      else if  (api->rsp->wake_up.STATUS->dtvint ==     1) strncat(msg,"TRIGGERED    ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->wake_up.STATUS->dtvint);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-ERR    ",1000);
           if  (api->rsp->wake_up.STATUS->err    ==     1) strncat(msg,"ERROR   ",1000);
      else if  (api->rsp->wake_up.STATUS->err    ==     0) strncat(msg,"NO_ERROR",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->wake_up.STATUS->err);
       STRING_APPEND_SAFE(msg,1000,"%s",separator); strncat(msg,"-CTS    ",1000);
           if  (api->rsp->wake_up.STATUS->cts    ==     1) strncat(msg,"COMPLETED",1000);
      else if  (api->rsp->wake_up.STATUS->cts    ==     0) strncat(msg,"WAIT     ",1000);
      else                                                STRING_APPEND_SAFE(msg,1000,"%d", api->rsp->wake_up.STATUS->cts);
     break;
    #endif /*     Si2144_WAKE_UP_CMD */

     default : break;
    }
    return 0;
  }
#endif /* Si2144_GET_COMMAND_STRINGS */








