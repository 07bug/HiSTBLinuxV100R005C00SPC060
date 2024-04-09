#ifndef __LIB_H__
#define __LIB_H__

#include "types.h"

#undef reg_get
#define reg_get(addr) (*(volatile unsigned int *)(addr))

#undef reg_set
#define reg_set(addr, val) (*(volatile unsigned int *)(addr) = (val))

void memset(void *s, int c, size_t count);

void memcpy(void * dst, const void * src, size_t count);

#define udelay(count) \
{ \
    unsigned int offset = 0; \
    for (offset = 0; offset < count; offset++) \
    { \
        asm("nop"); \
        asm("nop"); \
        asm("nop"); \
        asm("nop"); \
        asm("nop"); \
        asm("nop"); \
        asm("nop"); \
        asm("nop"); \
        asm("nop"); \
        asm("nop"); \
    } \
}
#endif /*__LIB_H__*/
