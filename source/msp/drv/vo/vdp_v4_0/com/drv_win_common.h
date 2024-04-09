#ifndef __DRV_WIN_COM_H__
#define __DRV_WIN_COM_H__

#if  (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
#define WINDOW_MAX_NUMBER 36
#elif (defined(CHIP_TYPE_hi3798mv310))
#define WINDOW_MAX_NUMBER 5
#else
#define WINDOW_MAX_NUMBER 17
#endif

#define WINDOW_MAX_ALPHA 100
#endif

