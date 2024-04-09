#ifndef __VFMW_OSAL_PROC_HEADER__
#define __VFMW_OSAL_PROC_HEADER__

#if defined(ENV_ARMLINUX_KERNEL)
#include "vfmw_linux_kernel_proc.h"
#elif defined(ENV_SOS_KERNEL)
#include "vfmw_sos_kernel_proc.h"
#endif

#endif

