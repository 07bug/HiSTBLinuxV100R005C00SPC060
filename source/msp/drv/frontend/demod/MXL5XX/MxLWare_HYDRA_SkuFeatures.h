/*
* Copyright (c) 2011-2013 MaxLinear, Inc. All rights reserved
*
* License type: GPLv2
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*
* This program may alternatively be licensed under a proprietary license from
* MaxLinear, Inc.
*
* See terms and conditions defined in file 'LICENSE.txt', which is part of this
* source code package.
*/

#ifndef __MXL_HDR_SKU_FEATURES_H__
#define __MXL_HDR_SKU_FEATURES_H__

/*****************************************************************************************
    Include Header Files
*****************************************************************************************/

#ifndef MXL_HYDRA_DEVICE_TYPE_EXTERNAL
#include "MxLWare_HYDRA_ProductId.h"
#endif // MXL_HYDRA_DEVICE_TYPE_EXTERNAL

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************************
    Macros
*****************************************************************************************/

// --------------------------------------------------------------------------------------
// Utility macro to extract product specific compiler switch setting based on MXL_HDR_PROD_ID
// --------------------------------------------------------------------------------------
#define _MXL_HYDRA_DISEQC_ENABLED_
#define _MXL_HYDRA_FSK_ENABLED_

#if defined(MXL_HYDRA_568_ENABLE)
#define _MXL_HYDRA_CHAN_BOND_
#endif

/*****************************************************************************************
    Extra options not SKU-dependent
 *****************************************************************************************/
#ifndef MXL_HYDRA_OPTIONS_EXTERNAL
  #define _MXL_HYDRA_DEBUG_ENABLED_
#endif

// Customer should undef or comment "MXL_ENABLE_SPECTRUM_RB" if spectrum readback feature
// is not required
#ifndef MXL_ENABLE_SPECTRUM_RB
#define MXL_ENABLE_SPECTRUM_RB
#endif


/*****************************************************************************************
    User-Defined Types (Typedefs)
*****************************************************************************************/

/*****************************************************************************************
    Global Variable Declarations
*****************************************************************************************/

/*****************************************************************************************
    Prototypes
*****************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // __MXL_HDR_FEATURES_H__

