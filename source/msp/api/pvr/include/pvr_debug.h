
#ifndef __PVR_DEBUG_H__
#define __PVR_DEBUG_H__

#include "hi_debug.h"

#define HI_FATAL_PVR(fmt...)        HI_FATAL_PRINT  (HI_ID_PVR, fmt)
#define HI_ERR_PVR(fmt...)          HI_ERR_PRINT    (HI_ID_PVR, fmt)
#define HI_WARN_PVR(fmt...)         HI_WARN_PRINT   (HI_ID_PVR, fmt)
#define HI_INFO_PVR(fmt...)         HI_INFO_PRINT   (HI_ID_PVR, fmt)

#define HI_PVR_DEBUG_ENTER()\
    do {\
        HI_INFO_PVR("\tEnter the Func:%s(%s_%d)!\n", __FUNCTION__, __FILE__, __LINE__);\
    }while(0)

#define HI_PVR_DEBUG_EXIT()\
    do {\
        HI_INFO_PVR("\tExit the Func:%s(%s_%d)!\n", __FUNCTION__, __FILE__, __LINE__);\
    }while(0)
#define HI_PVR_DEBUG_POS()\
    do {\
        HI_INFO_PVR("\tpos:%s(%s_%d)!\n", __FUNCTION__, __FILE__, __LINE__);\
    }while(0)

#define HI_PVR_ERR_ENTER()\
        do {\
            HI_ERR_PVR("\tEnter the Func:%s(%s_%d)!\n", __FUNCTION__, __FILE__, __LINE__);\
        }while(0)

#define HI_PVR_ERR_EXIT()\
        do {\
            HI_ERR_PVR("\tExit the Func:%s(%s_%d)!\n", __FUNCTION__, __FILE__, __LINE__);\
        }while(0)
#define HI_PVR_ERR_POS()\
        do {\
            HI_ERR_PVR("\tpos:%s(%s_%d)!\n", __FUNCTION__, __FILE__, __LINE__);\
        }while(0)

#endif

