#ifndef __ADSP_OSAL_EXT_H__
#define __ADSP_OSAL_EXT_H__

#ifdef __XTENSA__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define adsp_msleep                  msleep
#define adsp_memset                  memset
#define adsp_memcpy                  memcpy
#define adsp_memmove                 memmove
#define adsp_kmalloc(id, size)       malloc(size)
#define adsp_kfree(id, addr)         free(addr)
#define adsp_vmalloc(id, size)       malloc(size)
#define adsp_vfree(id, addr)         free(addr)

#define adsp_kneon_begin()
#define adsp_kneon_end()
#else

#include "hi_type.h"

typedef enum
{
    SPIN_LOCK_ID_0     = 0,
    SPIN_LOCK_ID_1     = 1,
    SPIN_LOCK_ID_2     = 2,
    SPIN_LOCK_ID_3     = 3,

    SPIN_LOCK_ID_BUTT,
} OSAL_SPIN_LOCK_ID_E;

typedef enum
{
    TIMER_ID_0     = 0,

    TIMER_ID_BUTT,
} OSAL_TIMER_ID_E;

typedef struct
{
    HI_VOID (*pfun_OSAL_adsp_fatal_print)(const char* fmt, ...);
    HI_VOID (*pfun_OSAL_adsp_err_print)(const char* fmt, ...);
    HI_VOID (*pfun_OSAL_adsp_warn_print)(const char* fmt, ...);
    HI_VOID (*pfun_OSAL_adsp_info_print)(const char* fmt, ...);

    HI_VOID  (*pfun_OSAL_adsp_msleep)(HI_U32);

#ifdef __aarch64__
    HI_VOID* (*pfun_OSAL_adsp_memset)(HI_VOID*, HI_S32, unsigned long);
    HI_VOID* (*pfun_OSAL_adsp_memcpy)(HI_VOID*, const HI_VOID*, unsigned long);
    HI_VOID* (*pfun_OSAL_adsp_memmove)(HI_VOID*, const HI_VOID*, unsigned long);
#else
    HI_VOID* (*pfun_OSAL_adsp_memset)(HI_VOID*, HI_S32, unsigned int);
    HI_VOID* (*pfun_OSAL_adsp_memcpy)(HI_VOID*, const HI_VOID*, unsigned int);
    HI_VOID* (*pfun_OSAL_adsp_memmove)(HI_VOID*, const HI_VOID*, unsigned int);
#endif

#ifndef __aarch64__
    HI_VOID  (*pfun_OSAL_adsp_kneon_begin)(HI_VOID);
    HI_VOID  (*pfun_OSAL_adsp_kneon_end)(HI_VOID);
#endif

    HI_VOID* (*pfun_OSAL_adsp_kmalloc)(HI_U32, HI_U32);
    HI_VOID  (*pfun_OSAL_adsp_kfree)(HI_U32, HI_VOID*);
    HI_VOID* (*pfun_OSAL_adsp_vmalloc)(HI_U32, HI_U32);
    HI_VOID  (*pfun_OSAL_adsp_vfree)(HI_U32, HI_VOID*);

    HI_VOID* (*pfun_OSAL_adsp_ioremap)(HI_U32, HI_U32);
    HI_VOID  (*pfun_OSAL_adsp_iounmap)(HI_VOID*);

    HI_U64  (*pfun_OSAL_adsp_get_time_us)(HI_VOID);

    HI_VOID  (*pfun_OSAL_adsp_schedule_task)(HI_U32);
    HI_VOID  (*pfun_OSAL_adsp_set_task_uninterrupt)(HI_VOID);
    HI_VOID  (*pfun_OSAL_adsp_set_task_running)(HI_VOID);

    HI_S32   (*pfun_OSAL_adsp_create_task)(HI_VOID**, const HI_PCHAR, HI_S32 (*threadfn)(HI_VOID *data));
    HI_VOID  (*pfun_OSAL_adsp_destory_task)(HI_VOID*);
    HI_BOOL  (*pfun_OSAL_adsp_task_should_stop)(HI_VOID);

    HI_VOID  (*pfun_OSAL_adsp_add_timer)(OSAL_TIMER_ID_E, HI_VOID*, HI_U32);
    HI_VOID  (*pfun_OSAL_adsp_mod_timer)(OSAL_TIMER_ID_E, HI_U32);
    HI_VOID  (*pfun_OSAL_adsp_del_timer)(OSAL_TIMER_ID_E);
    HI_VOID  (*pfun_OSAL_adsp_del_timer_sync)(OSAL_TIMER_ID_E);

    HI_VOID (*pfun_OSAL_adsp_spin_init)(OSAL_SPIN_LOCK_ID_E);
    HI_VOID (*pfun_OSAL_adsp_spin_lock)(OSAL_SPIN_LOCK_ID_E);
    HI_VOID (*pfun_OSAL_adsp_spin_unlock)(OSAL_SPIN_LOCK_ID_E);
} ADSP_OSAL_FUNC_S;

extern ADSP_OSAL_FUNC_S g_AdspOsalFunc;

#define ADSP_OSAL_PREFIX g_AdspOsalFunc.pfun_OSAL

#define OSALCC1(x, y, z) OSALCC2(x, y, z)
#define OSALCC2(x, y, z) x ## y ## z

#ifdef ADSP_OSAL_PREFIX
#define OSAL_STATNAME(func) OSALCC1(ADSP_OSAL_PREFIX, _, func)
#else
#define OSAL_STATNAME(func) func
#endif

#define adsp_fatal_print             OSAL_STATNAME(adsp_fatal_print)
#define adsp_err_print               OSAL_STATNAME(adsp_err_print)
#define adsp_warn_print              OSAL_STATNAME(adsp_warn_print)
#define adsp_info_print              OSAL_STATNAME(adsp_info_print)

#define adsp_msleep                  OSAL_STATNAME(adsp_msleep)
#define adsp_memset                  OSAL_STATNAME(adsp_memset)
#define adsp_memcpy                  OSAL_STATNAME(adsp_memcpy)
#define adsp_memmove                 OSAL_STATNAME(adsp_memmove)
#ifndef __aarch64__
#define adsp_kneon_begin             OSAL_STATNAME(adsp_kneon_begin)
#define adsp_kneon_end               OSAL_STATNAME(adsp_kneon_end)
#endif
#define adsp_kmalloc                 OSAL_STATNAME(adsp_kmalloc)
#define adsp_kfree                   OSAL_STATNAME(adsp_kfree)
#define adsp_vmalloc                 OSAL_STATNAME(adsp_vmalloc)
#define adsp_vfree                   OSAL_STATNAME(adsp_vfree)
#define adsp_ioremap                 OSAL_STATNAME(adsp_ioremap)
#define adsp_iounmap                 OSAL_STATNAME(adsp_iounmap)

#define adsp_spin_init               OSAL_STATNAME(adsp_spin_init)
#define adsp_spin_lock               OSAL_STATNAME(adsp_spin_lock)
#define adsp_spin_unlock             OSAL_STATNAME(adsp_spin_unlock)
#define adsp_get_time_us             OSAL_STATNAME(adsp_get_time_us)

#define adsp_add_timer               OSAL_STATNAME(adsp_add_timer)
#define adsp_mod_timer               OSAL_STATNAME(adsp_mod_timer)
#define adsp_del_timer               OSAL_STATNAME(adsp_del_timer)
#define adsp_del_timer_sync          OSAL_STATNAME(adsp_del_timer_sync)

#define adsp_schedule_task           OSAL_STATNAME(adsp_schedule_task)
#define adsp_set_task_uninterrupt    OSAL_STATNAME(adsp_set_task_uninterrupt)
#define adsp_set_task_running        OSAL_STATNAME(adsp_set_task_running)
#define adsp_destory_task            OSAL_STATNAME(adsp_destory_task)
#define adsp_create_task             OSAL_STATNAME(adsp_create_task)
#define adsp_task_should_stop        OSAL_STATNAME(adsp_task_should_stop)

#endif // __XTENSA__
#endif // __ADSP_OSAL_EXT_H__
