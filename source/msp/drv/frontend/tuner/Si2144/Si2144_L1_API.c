/*************************************************************************************
                  Silicon Laboratories Broadcast Si2144 Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API functions definitions used by commands and properties
   FILE: Si2144_L1_API.c
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


/***********************************************************************************************************************
  Si2144_L1_API_Init function
  Use:        software initialization function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:  *api         a pointer to Si2144 Context
  Parameter:  add          the Si2144 I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si2144_L1_API_Init  (unsigned int u32TunerId,L1_Si2144_Context *api, int add,unsigned int u32I2cChannel) {
    api->i2c = &(api->i2cObj);

    L0_Init(u32TunerId,api->i2c,u32I2cChannel);
    L0_SetAddress(api->i2c, add, 0);

    api->cmd               = &(api->cmdObj);
    api->rsp               = &(api->rspObj);
    api->prop              = &(api->propObj);
    api->status            = &(api->statusObj);
    api->propShadow        = &(api->propShadowObj);
    /* Set the propertyWriteMode to Si2144_DOWNLOAD_ON_CHANGE to only download property settings on change (recommended) */
    /*      if propertyWriteMode is set to Si2144_DOWNLOAD_ALWAYS the properties will be downloaded regardless of change */
    api->propertyWriteMode = DOWNLOAD_ON_CHANGE;
    /* The load_control flag is used to control the interaction between Si2144_PowerUpWithPatch() and Si2144_PowerUpUsingBroadcastI2C().  */
    /* the default is SKIP_NONE */
    api->load_control = SKIP_NONE;
    api->rsp->get_rev.pn = 0;
    #ifdef    Si2144_TUNER_BLOCKED_VCO_PROP
        api->prop->tuner_blocked_vco.vco_code           = 0x8000; /* (default 0x8000) */
    #endif /* Si2144_TUNER_BLOCKED_VCO_PROP */
    #ifdef    Si2144_TUNER_BLOCKED_VCO2_PROP
        api->prop->tuner_blocked_vco2.vco_code          = 0x8000; /* (default 0x8000) */
    #endif /* Si2144_TUNER_BLOCKED_VCO2_PROP */
    #ifdef    Si2144_TUNER_BLOCKED_VCO3_PROP
        api->prop->tuner_blocked_vco3.vco_code          = 0x8000; /* (default 0x8000) */
    #endif /* Si2144_TUNER_BLOCKED_VCO3_PROP */
    return NO_Si2144_ERROR;
}
/***********************************************************************************************************************
  Si2144_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si2144. Useful to download the firmware.
  Returns:    0 if no error
 ***********************************************************************************************************************/
unsigned char    Si2144_L1_API_Patch     (L1_Si2144_Context *api, signed   int iNbBytes, unsigned char *pucDataBuffer) {
    signed   int res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si2144 Patch %d bytes\n",iNbBytes);

    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si2144_L1_API_Patch error writing bytes: %s\n", Si2144_L1_API_ERROR_TEXT(ERROR_Si2144_LOADING_FIRMWARE) );
      return ERROR_Si2144_LOADING_FIRMWARE;
    }

    res = Si2144_pollForResponse(api, 1, rspByteBuffer);
    if (res != NO_Si2144_ERROR) {
      SiTRACE("Si2144_L1_API_Patch error 0x%02x polling response: %s\n", res, Si2144_L1_API_ERROR_TEXT(res) );
      return ERROR_Si2144_POLLING_RESPONSE;
    }

    return NO_Si2144_ERROR;
}
/***********************************************************************************************************************
  Si2144_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
 ***********************************************************************************************************************/
unsigned char    Si2144_L1_CheckStatus   (L1_Si2144_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si2144_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si2144_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2144_L1_API_ERROR_TEXT(signed   int error_code) {
    switch (error_code) {
        case NO_Si2144_ERROR                     : return (char *)"No Si2144 error";
        case ERROR_Si2144_ALLOCATING_CONTEXT     : return (char *)"Error while allocating Si2144 context";
        case ERROR_Si2144_PARAMETER_OUT_OF_RANGE : return (char *)"Si2144 parameter(s) out of range";
        case ERROR_Si2144_SENDING_COMMAND        : return (char *)"Error while sending Si2144 command";
        case ERROR_Si2144_CTS_TIMEOUT            : return (char *)"Si2144 CTS timeout";
        case ERROR_Si2144_ERR                    : return (char *)"Si2144 Error (status 'err' bit 1)";
        case ERROR_Si2144_POLLING_CTS            : return (char *)"Si2144 Error while polling CTS";
        case ERROR_Si2144_POLLING_RESPONSE       : return (char *)"Si2144 Error while polling response";
        case ERROR_Si2144_LOADING_FIRMWARE       : return (char *)"Si2144 Error while loading firmware";
        case ERROR_Si2144_LOADING_BOOTBLOCK      : return (char *)"Si2144 Error while loading bootblock";
        case ERROR_Si2144_STARTING_FIRMWARE      : return (char *)"Si2144 Error while starting firmware";
        case ERROR_Si2144_SW_RESET               : return (char *)"Si2144 Error during software reset";
        case ERROR_Si2144_INCOMPATIBLE_PART      : return (char *)"Si2144 Error Incompatible part";
        case ERROR_Si2144_UNKNOWN_COMMAND        : return (char *)"Si2144 Error unknown command";
        case ERROR_Si2144_UNKNOWN_PROPERTY       : return (char *)"Si2144 Error unknown property";
        case ERROR_Si2144_TUNINT_TIMEOUT         : return (char *)"Si2144 Error TUNINT Timeout";
        case ERROR_Si2144_xTVINT_TIMEOUT         : return (char *)"Si2144 Error xTVINT Timeout";
        default                                  : return (char *)"Unknown Si2144 error code";
    }
}
/***********************************************************************************************************************
  Si2144_L1_API_TAG_TEXT function
  Use:        Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2144_L1_API_TAG_TEXT(void) { return (char *)"ROM62_2_1_build_5_V0.1";}
