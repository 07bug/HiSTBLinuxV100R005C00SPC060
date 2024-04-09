/*****************************************************************************/
/**
* @file si_lib_log_api.h
*
* @brief
*
*****************************************************************************/

#ifndef __SI_LIB_LOG_API_H__
#define __SI_LIB_LOG_API_H__

/***** #include statements ***************************************************/

#include "si_datatypes.h"
#ifndef HDMI_BUILD_IN_BOOT
#include "drv_hdmi_platform.h"
#else
#include "boot_hdmi_intf.h"
#endif
/***** public macro definitions **********************************************/

#ifdef SII_DEBUG
#define SII_LIB_LOG_DEBUG1(obj, str...)      { SiiLibLogTimeStamp(sSiiLibObjClassStr, obj); SiiLibLogPrintf(str); }
#define SII_LIB_LOG_DEBUG2(str...)           { SiiLibLogPrintf(str);}
#define SII_LIB_LOG_ERR(obj, str...)      { SiiLibLogTimeStamp(sSiiLibObjClassStr, obj); SiiLibLogPrintf(str); }
#define SII_LIB_LOG_WARN(obj, str...)     { SiiLibLogTimeStamp(sSiiLibObjClassStr, obj); SiiLibLogPrintf(str); }
#else
#define SII_LIB_LOG_DEBUG1(obj, str...) HDMI_INFO(str);
#define SII_LIB_LOG_DEBUG2(str...)      HDMI_INFO(str);
#define SII_LIB_LOG_ERR(obj, str...)    HDMI_ERR(str);
#define SII_LIB_LOG_WARN(obj, str...)   HDMI_WARN(str);
#endif

//#define CEC_DEBUG

#ifdef CEC_DEBUG
#define CEC_LOG                         SII_LIB_LOG_ERR
#else
#define CEC_LOG                         SII_LIB_LOG_DEBUG1
#endif

#define SII_LIB_LOG_PRINT1(obj, str)      { SiiLibLogTimeStamp(sSiiLibObjClassStr, obj); SiiLibLogPrintf str; }
#define SII_LIB_LOG_PRINT2(str)           { SiiLibLogPrintf str; }


/***** public type definitions ***********************************************/

/***** public functions ******************************************************/

void SiiLibLogTimeStamp(const char* pClassStr, void* pObj);
void SiiLibLogPrintf( char* pFrm, ...);

#endif /* __SI_LIB_LOG_API_H__ */

/***** end of file ***********************************************************/
