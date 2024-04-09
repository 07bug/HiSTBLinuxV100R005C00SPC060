/*************************************************************************************
                  Silicon Laboratories Broadcast Si2144 Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties functions definitions
   FILE: Si2144_Properties_Functions.h
   Supported IC : Si2144
   Compiled for ROM 62 firmware 2_1_build_5
   Revision: 0.1
   Date: July 07 2017
  (C) Copyright 2017, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   _Si2144_PROPERTIES_FUNCTIONS_H_
#define   _Si2144_PROPERTIES_FUNCTIONS_H_

void          Si2144_storeUserProperties           (Si2144_PropObj   *prop);
unsigned char Si2144_PackProperty                  (Si2144_PropObj   *prop, unsigned int prop_code, signed   int *data);
unsigned char Si2144_UnpackProperty                (Si2144_PropObj   *prop, unsigned int prop_code, signed   int  data);
void          Si2144_storePropertiesDefaults       (Si2144_PropObj   *prop);

signed   int  Si2144_downloadCOMMONProperties(L1_Si2144_Context *api);
signed   int  Si2144_downloadDTVProperties   (L1_Si2144_Context *api);
signed   int  Si2144_downloadTUNERProperties (L1_Si2144_Context *api);
signed   int  Si2144_downloadAllProperties   (L1_Si2144_Context *api);

#endif /* _Si2144_PROPERTIES_FUNCTIONS_H_ */







