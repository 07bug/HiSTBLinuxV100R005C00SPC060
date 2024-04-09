#ifndef __DRV_OSAL_CHIP_H__
#define __DRV_OSAL_CHIP_H__

#if defined(CHIP_TYPE_hi3798cv200)
#include "drv_osal_hi3798cv200.h"

#elif defined(CHIP_TYPE_hi3798mv200)
#include "drv_osal_hi3798mv200.h"

#elif defined(CHIP_TYPE_hi3798mv300)
#include "drv_osal_hi3798mv300.h"

#elif defined(CHIP_TYPE_hi3798mv310)
#include "drv_osal_hi3798mv310.h"

#elif defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
#include "drv_osal_hi3796mv200.h"

#elif defined(CHIP_TYPE_hi3798mv100)
#include "drv_osal_hi3798mv100.h"

#elif defined(CHIP_TYPE_hi3796mv100)
#include "drv_osal_hi3796mv100.h"

#elif defined(CHIP_TYPE_hi3716mv410)
#ifdef NOCS3_0_SUPPORT
#include "drv_osal_hi3716mv410_nocs30.h"
#else
#include "drv_osal_hi3716mv410.h"
#endif

#elif defined(CHIP_TYPE_hi3716mv420)
#ifdef NOCS3_0_SUPPORT
#include "drv_osal_hi3716mv420_nocs30.h"
#else
#include "drv_osal_hi3716mv420.h"
#endif

#else
#error You need to define a configuration file for chip !
#endif

#if defined(CHIP_HASH_VER_V100) || defined(CHIP_HASH_VER_V200)
#define CHIP_HASH_SUPPORT
#endif

#if defined(CHIP_SYMC_VER_V100) || defined(CHIP_SYMC_VER_V200)
#define CHIP_SYMC_SUPPORT
#endif

#if defined(CHIP_TRNG_VER_V100) || defined(CHIP_TRNG_VER_V200)
#define CHIP_TRNG_SUPPORT
#endif

#if defined(CHIP_IFEP_RSA_VER_V100) || defined(CHIP_SIC_RSA_VER_V100)
#define CHIP_RSA_SUPPORT
#endif

#if defined(CHIP_HDCP_VER_V100) || defined(CHIP_HDCP_VER_V200)
#define CHIP_HDCP_SUPPORT
#endif

#if defined(CHIP_SM2_VER_V100)
#define CHIP_SM2_SUPPORT
#endif

#if defined(CRYPTO_SWITCH_CPU) && defined(CRYPTO_SEC_CPU)
#error "CRYPTO_SEC_CPU and CPU_SWITCH_SUPPORT cannot be defined simultaneously"
#endif

#endif
