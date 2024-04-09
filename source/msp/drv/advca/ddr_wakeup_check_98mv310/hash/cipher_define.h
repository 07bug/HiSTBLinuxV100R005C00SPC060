#ifndef __CIPHER_DEFINE__
#define __CIPHER_DEFINE__
#include <lib.h>

#define CIPHER_DBG(fmt...)  //printf(fmt)
#define CIPHER_ERR(fmt...)  //printf(fmt)
#define HI_PRINT_HEX(name, str, len) \
{\
    unsigned int _i = 0;\
    unsigned char *_str; \
    _str = (unsigned char*)str; \
    printf("[%s]:\n", name);\
    for ( _i = 0 ; _i < (len); _i++ )\
    {\
        if( (_i % 16 == 0) && (_i != 0)) printf("\n");\
        printf("\\x%02x", *((_str)+_i));\
    }\
    printf("\n");\
}

#define cipher_memcpy_s  memcpy
#define cipher_memset_s  memset
//#define cipher_memcmp_s  memcmp

#define HAL_SET_BIT(src, bit)        ((src) |= (1<<bit))
#define HAL_CLEAR_BIT(src,bit)       ((src) &= ~(1<<bit))
#define CPU_TO_BE32(v) (((v)>>24) | (((v)>>8)&0xff00) | (((v)<<8)&0xff0000)|((v)<<24))

#endif

