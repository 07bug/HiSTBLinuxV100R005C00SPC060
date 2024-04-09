#ifndef  __KFIFO2_H__
#define  __KFIFO2_H__

#ifdef __KERNEL__
#include <asm/setup.h>
#include <asm/io.h>
#include <linux/delay.h>

#include <linux/string.h>
#else
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if defined (__XTENSA__) && defined (DSP_DDR_CACHE_DMA_SUPPORT)
#include <xtensa/hal.h>
#define __arm_ptr
#endif

#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#ifndef min
#define min(a,b) (a)<=(b)?(a):(b)
#endif

#ifndef is_power_of_2
#define is_power_of_2(x)    ((x) != 0 && (((x) & ((x) - 1)) == 0))
#endif

typedef struct
{
    unsigned int*    in;     // 存放写指针偏移量地址
    unsigned int*    out;    // 存放读指针偏移量地址
    unsigned int    mask;    // kfifo长度掩码
    unsigned int    esize;   // kfifo成员的单位长度
    void*            data;   // buffer地址
} kfifo2_s;


/* DSP运行空间起始物理地址 */
#define DSP_MEM_ADDR_START 0x7000000
#define DSP_MEM_ADDR_END 0x8000000

/* 判断所给的buffer指针是否在DSP运行空间内部 */
#define is_dsp_mem(p) ((p - NULL) >= DSP_MEM_ADDR_START && (p - NULL) <= DSP_MEM_ADDR_END)

static inline void memset_safe(void* src, int val, unsigned int size)
{
    if (0 == size)
    {
        return;
    }

    memset(src, val, size);

#if defined (__XTENSA__) && defined (DSP_DDR_CACHE_DMA_SUPPORT)
    if (!is_dsp_mem(src))
    {
        xthal_dcache_region_writeback(__arm_ptr src, size);
    }
#endif
}

static inline void memcpy_safe(void* to, const void* from, unsigned int size)
{
    if (0 == size)
    {
        return;
    }

#if defined (__XTENSA__) && defined (DSP_DDR_CACHE_DMA_SUPPORT)
    if (!is_dsp_mem(from))
    {
        xthal_dcache_region_invalidate((void*) __arm_ptr from, size);
    }
#endif

    memcpy(to, from, size);

#if defined (__XTENSA__) && defined (DSP_DDR_CACHE_DMA_SUPPORT)
    if (!is_dsp_mem(to))
    {
        xthal_dcache_region_writeback(__arm_ptr to, size);
    }
#endif
}

static inline int kfifo2_init(kfifo2_s* fifo,
                              unsigned int* in,
                              unsigned int* out,
                              void* buffer,
                              unsigned int esize,
                              unsigned int size)
{
    size /= esize;

    if (size < 2)
    {
        return -1;
    }

    if (!is_power_of_2(size))
    {
        return -1;
    }

    if (NULL == fifo ||
        NULL == in   ||
        NULL == out  ||
        NULL == buffer)
    {
        return -1;
    }

    fifo->in = in;
    fifo->out = out;
    fifo->esize = esize;
    fifo->mask = size - 1;
    fifo->data = buffer;

    return 0;
}

static inline void kfifo2_deinit(kfifo2_s* fifo)
{
    if (NULL == fifo)
    {
        return;
    }

    memset(fifo, 0, sizeof(kfifo2_s));
}

static inline void kfifo2_reset(kfifo2_s* fifo)
{
    if (NULL == fifo)
    {
        return;
    }

    *fifo->in = 0;
    *fifo->out = 0;
}

/* 下面的接口，不判断kfifo_s结构体指针和内部成员指针的合法性 */
static inline unsigned int kfifo2_unused(kfifo2_s* fifo)
{
    return (fifo->mask + 1) - (*fifo->in - *fifo->out);
}

static inline unsigned int kfifo2_used(kfifo2_s* fifo)
{
    return (unsigned int)(*fifo->in - *fifo->out);
}

static inline unsigned int kfifo2_linear_avail(kfifo2_s* fifo)
{
    return (unsigned int)(*fifo->in >= *fifo->out) ? (fifo->mask + 1 - ((*fifo->in) & fifo->mask)) : (*fifo->out - *fifo->in);
}

static inline void kfifo2_get_wptr(kfifo2_s* fifo, void** buf)
{
    *buf = fifo->data + ((*fifo->in) & fifo->mask);
}

static inline void kfifo2_update_wptr(kfifo2_s* fifo, const unsigned int len)
{
    *fifo->in += len;
}

static inline void kfifo2_copy_in(kfifo2_s* fifo, const void* src,
                                  unsigned int len, unsigned int off)
{
    unsigned int size = fifo->mask + 1;
    unsigned int esize = fifo->esize;
    unsigned int l;

    off &= fifo->mask;
    if (esize != 1)
    {
        off *= esize;
        size *= esize;
        len *= esize;
    }

    l = min(len, size - off);

    if (NULL == src)
    {
        memset_safe(fifo->data + off, 0, l);
        memset_safe(fifo->data, 0, len - l);
    }
    else
    {
        memcpy_safe(fifo->data + off, src, l);
        memcpy_safe(fifo->data, src + l, len - l);
    }
}

static inline unsigned int kfifo2_in(kfifo2_s* fifo, const void* buf, unsigned int len)
{
    if (kfifo2_unused(fifo) < len) //允许写满
    {
        return 0;
    }

    kfifo2_copy_in(fifo, buf, len, *fifo->in);
    *fifo->in += len;

    return len;
}

static inline void kfifo2_copy_out(kfifo2_s* fifo, void* dst,
                                   unsigned int len, unsigned int off)
{
    unsigned int size = fifo->mask + 1;
    unsigned int esize = fifo->esize;
    unsigned int l;

    if (NULL == dst)
    {
        return;
    }

    off &= fifo->mask;
    if (esize != 1)
    {
        off *= esize;
        size *= esize;
        len *= esize;
    }
    l = min(len, size - off);

    memcpy_safe(dst, fifo->data + off, l);
    memcpy_safe(dst + l, fifo->data, len - l);
}

static inline unsigned int kfifo2_out(kfifo2_s* fifo,
                                      void* buf, unsigned int len)
{
    if (kfifo2_used(fifo) < len)
    {
        return 0;
    }

    kfifo2_copy_out(fifo, buf, len, *fifo->out);

    *fifo->out += len;
    return len;
}

static inline unsigned int kfifo2_in_prepare(kfifo2_s* fifo,
        const void* buf, const unsigned int len)
{
    if (kfifo2_unused(fifo) < len) //允许写满
    {
        return 0;
    }

    kfifo2_copy_in(fifo, buf, len, *fifo->in);

    return len;
}

static inline void kfifo2_in_finish(kfifo2_s* fifo, const unsigned int len)
{
    *fifo->in += len;
}

static inline unsigned int kfifo2_out_prepare(kfifo2_s* fifo,
        void* buf, const unsigned int len)
{
    if (kfifo2_used(fifo) < len)
    {
        return 0;
    }

    kfifo2_copy_out(fifo, buf, len, *fifo->out);

    return len;
}

static inline void kfifo2_out_finish(kfifo2_s* fifo, const unsigned int len)
{
    *fifo->out += len;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
