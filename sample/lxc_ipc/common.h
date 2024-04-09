#ifndef _COMMON_H
#define _COMMON_H

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_common.h"

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

#endif

