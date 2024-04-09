/***************************************************************************************
                  Silicon Laboratories Broadcast Si2144 Layer 2 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   L2 API header for commands and properties
   FILE: Si2144_L2_API.h
   Supported IC : Si2144
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.1
   Date: July 07 2017
  (C) Copyright 2017, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si2144_L2_API_H
#define   Si2144_L2_API_H

#include "Si2144_L1_API.h"

#ifdef Si2144_COMMAND_LINE_APPLICATION
    #include "Si2144_Properties_Strings.h"
#endif /* Si2144_COMMAND_LINE_APPLICATION */

#ifdef    TUNER_ONLY
/* define some externals, required for VCO_BLOCKING */
/* only used for TUNER_ONLY mode */
extern signed   int fe;
extern L1_Si2144_Context  FrontEnd_Table[];
#endif /* TUNER_ONLY */

signed   int   Si2144_Init                       (L1_Si2144_Context *api);
signed   int   Si2144_Configure                  (L1_Si2144_Context *api);
signed   int   Si2144_PowerUpWithPatch           (L1_Si2144_Context *api);
signed   int   Si2144_PowerUpUsingBroadcastI2C   (L1_Si2144_Context *tuners[], signed   int tuner_count );
signed   int   Si2144_PowerUpOnly                (L1_Si2144_Context *api);
signed   int   Si2144_LoadFirmware               (L1_Si2144_Context *api, unsigned char *fw_table, signed   int lines);
signed   int   Si2144_StartFirmware              (L1_Si2144_Context *api);

signed   int   Si2144_LoadFirmware_16            (L1_Si2144_Context *api, firmware_struct fw_table[], signed   int nbLines);
signed   int   Si2144_GetRF                      (L1_Si2144_Context *api);
signed   int   Si2144_Tune                       (L1_Si2144_Context *api, unsigned char mode, unsigned long freq);
signed   int   Si2144_DTVTune                    (L1_Si2144_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
signed   int   Si2144_XoutOn                     (L1_Si2144_Context *api);
signed   int   Si2144_XoutOff                    (L1_Si2144_Context *api);
signed   int   Si2144_Standby                    (L1_Si2144_Context *api);
signed   int   Si2144_Powerdown                  (L1_Si2144_Context *api);
signed   int   Si2144_LoadVideofilter            (L1_Si2144_Context *api, vid_filt_struct vidFiltTable[], signed   int lines);
signed   int   Si2144_AGC_Override               (L1_Si2144_Context *api, unsigned char mode );
signed   int   Si2144_Tuner_Block_VCO            (L1_Si2144_Context *api, signed   int vco_code);
signed   int   Si2144_Tuner_Block_VCO2           (L1_Si2144_Context *api, signed   int vco_code);
signed   int   Si2144_Tuner_Block_VCO3           (L1_Si2144_Context *api, signed   int vco_code);
signed   int   Si2144_L2_VCO_Blocking_PostTune   (L1_Si2144_Context *tuners[], signed   int tuner_num, signed   int tuner_count);
signed   int   Si2144_L2_VCO_Blocking_PreTune    (L1_Si2144_Context *tuners[], signed   int tuner_num, signed   int tuner_count);
signed   int   Si2144_SetVcoProperties           (L1_Si2144_Context *api);

#define Si2144_FORCE_NORMAL_AGC       0
#define Si2144_FORCE_MAX_AGC          1
#define Si2144_FORCE_TOP_AGC          2

#endif /* Si2144_L2_API_H */







