/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     :drv_osal_lib.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_OSAL_LIB_H__
#define __DRV_OSAL_LIB_H__
#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/signal.h>
#include <linux/spinlock.h>
#include <linux/personality.h>
#include <linux/ptrace.h>
#include <linux/kallsyms.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/seq_file.h>
#include <linux/version.h>
#include <linux/sched.h>
#include <asm/atomic.h>
#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <asm/traps.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_common.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_dev.h"
#include "hi_drv_mem.h"
#include "hi_osal.h"
#include "hi_drv_mmz.h"
#include "hi_drv_module.h"
#include "hi_drv_proc.h"
#include "hi_type.h"
#include "drv_advca_ext.h"
#include "drv_osal_chip.h"
#include "drv_cipher_kapi.h"
#include "drv_cipher_ioctl.h"
#include "hi_error_mpi.h"

/*! \return uuid */
#define CHECK_OWNER(local) \
    do { \
        crypto_owner owner;\
        crypto_get_owner(&owner); \
        if (0 != memcmp(&owner, local, sizeof(owner))) { \
            HI_LOG_ERROR("return user uuid failed\n"); \
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_ILLEGAL_UUID);\
            return HI_ERR_CIPHER_ILLEGAL_UUID; \
        } \
    } while (0)

/*! \max length module name */
#define CRYPTO_MODULE_NAME_LEN            (16)

/*! \the max cipher hard channel count*/
#define CRYPTO_HARD_CHANNEL_MAX         (0x08)

/*! \serure mmz or not, not used */
#define SEC_MMZ                         (0x00)

/*! \struct channel
 * the context of hardware channel.
*/
typedef struct
{
    /*the state of instance, open or closed.*/
    u32 open;

    /*the context of channel, which is defined by specific module*/
    void *ctx;
}channel_context;

/*! \struct of crypto_mem*/
typedef struct
{
    compat_addr dma_addr;    /*!<  dam addr, may be mmz or smmu */
    compat_addr mmz_addr;    /*!<  mmz addr, sometimes the smmu must maped from mmz */
    void *dma_virt;         /*!<  cpu virtual addr maped from dam addr */
    u32 dma_size;           /*!<  dma memory size */
    void *user_buf;         /*!<  buffer of user */
}crypto_mem;

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/*! \****************************** API Declaration *****************************/
/*! \addtogroup    osal lib */
/** @{ */  /** <!--[osal]*/

/**
\brief  init dma memory.
*/
void crypto_mem_init(void);

/**
\brief  deinit dma memory.
*/
void crypto_mem_deinit(void);

/**
\brief  allocate and map a dma memory.
\param[in] mem  The struct of crypto_mem.
\param[in] size The size of mem.
\param[in] name The name of mem.
\return         HI_SUCCESS if successful, or HI_BASE_ERR_MALLOC_FAILED.
*/
s32 crypto_mem_create(crypto_mem *mem, u32 type, const s8 *name, u32 size);

/**
\brief  destory and unmap a dma memory.
\param[in] mem  The struct of crypto_mem.
\return         0 if successful, or HI_BASE_ERR_UNMAP_FAILED.
*/
s32 crypto_mem_destory(crypto_mem *mem);

/**
\brief  map a dma memory.
\param[in] mem  The struct of crypto_mem.
\param[in] dma_ddr The address of dma mem.
\param[in] dma_size The size of dma mem.
\return         HI_SUCCESS if successful, or HI_BASE_ERR_MAP_FAILED.
*/
s32 crypto_mem_open(crypto_mem *mem, compat_addr dma_ddr, u32 dma_size);

/**
\brief  unmap a dma memory.
\param[in] mem  The struct of crypto_mem.
\param[in] dma_ddr The address of dma mem.
\return         HI_SUCCESS if successful, or HI_BASE_ERR_UNMAP_FAILED.
*/
s32 crypto_mem_close(crypto_mem *mem);

/**
\brief  attach a cpu buffer with dma memory.
\param[in] mem  The struct of crypto_mem.
\param[in] buffer The user's buffer.
\return         HI_SUCCESS if successful, or HI_FAILURE.
*/
s32 crypto_mem_attach(crypto_mem *mem, void *buffer);

/**
\brief  flush dma memory,
*\param[in] mem The struct of crypto_mem.
*\param[in] dma2user 1-data from dma to user, 0-data from user to dma.
*\param[in] offset The offset of data to be flush.
*\param[in] data_size The size of data to be flush.
\return         HI_SUCCESS if successful, or HI_FAILURE.
*/
s32 crypto_mem_flush(crypto_mem *mem, u32 dma2user, u32 offset, u32 data_size);

/**
\brief  get dma memory physical address
*\param[in] mem The struct of crypto_mem.
\return         dma_addr if successful, or zero.
*/
s32 crypto_mem_phys(crypto_mem *mem, compat_addr *dma_addr);

/**
\brief  get dma memory virtual address
*\param[in] mem The struct of crypto_mem.
\return         dma_addr if successful, or zero.
*/
void * crypto_mem_virt(crypto_mem *mem);

/**
\brief  check whether cpu is secure or not.
\retval secure cpu, true is returned otherwise false is returned.
*/
u32 crypto_is_sec_cpu(void);

/**
\brief  load symc clean key from klad.
\retval NA.
*/
void crypto_load_symc_clean_key(u32 chn_num, u32 key[AES_IV_SIZE], u32 odd);

/**
\brief  map the physics addr to cpu within the base table, contains the base addr and crg addr.
\retval    on success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.*/
s32 module_addr_map(void);

/**
\brief  unmap the physics addr to cpu within the base table, contains the base addr and crg addr.
\retval    on success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.*/
s32 module_addr_unmap(void);

/**
\brief  get secure cpu type.
*/
u32 module_get_secure(void);

/**
\brief  enable a module, open clock  and remove reset signal.
\param[in]  id The module id.
\retval    NA */
void module_enable(module_id id);

/**
\brief  disable a module, close clock and set reset signal.
\param[in] id The module id.
\retval    NA */
void module_disable(module_id id);

/**
\brief  get attribute of module.
\param[in]  id The module id.
\param[out] int_valid enable interrupt or not.
\param[out] int_num interrupt number of module.
\param[out] name name of module.
\retval    on success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.*/
void module_get_attr(module_id id, u32 *int_valid, u32 *int_num, const char **name);

/**
\brief  read a register.
\param[in]  id The module id.
\param[in]  offset The module id.
\retval    the value of register*/
u32 module_reg_read(module_id id, u32 offset);

/**
\brief  hex to string.
\param[in]  buf The string buffer.
\param[in]  val The value of hex.
\retval    NA */
void HEX2STR(char buf[2], HI_U8 val);

/**
\brief  write a register.
\param[in]  id The module id.
\retval    NA */
void module_reg_write(module_id id, u32 offset, u32 val);

/* cipher module read and write a register */
#define SYMC_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_SYMC, offset)
#define SYMC_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_SYMC, offset, val)

/* hash module read and write a register */
#define HASH_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_HASH, offset)
#define HASH_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_HASH, offset, val)

/* rsa module read and write a register */
#define IFEP_RSA_READ(offset)       module_reg_read(CRYPTO_MODULE_ID_IFEP_RSA, offset)
#define IFEP_RSA_WRITE(offset, val) module_reg_write(CRYPTO_MODULE_ID_IFEP_RSA, offset, val)

/* trng module read and write a register */
#define TRNG_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_TRNG, offset)
#define TRNG_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_TRNG, offset, val)

/* sm2 module read and write a register */
#define SM2_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_SM2, offset)
#define SM2_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_SM2, offset, val)

/* smmu module read and write a register */
#define SMMU_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_SMMU, offset)
#define SMMU_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_SMMU, offset, val)

/**
\brief  Initialize the channel list.
\param[in]  ctx The context of channel.
\param[in]  num The channel numbers, max is 32.
\param[in]  ctx_size The size of context.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 crypto_channel_init(channel_context *ctx, u32 num, u32 ctx_size);

/**
\brief  Deinitialize the channel list.
\param[in]  ctx The context of channel.
\param[in]  num The channel numbers, max is 32.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 crypto_channel_deinit(channel_context *ctx, u32 num);

/**
\brief  allocate a channel.
\param[in]  ctx The context of channel.
\param[in]  num The channel numbers, max is 32.
\param[in]  mask Mask whick channel allowed be alloc, max is 32.
\param[out] id The id of channel.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 crypto_channel_alloc(channel_context *ctx, u32 num, u32 mask, u32 *id);

/**
\brief  free a channel.
\param[in]  ctx The context of channel.
\param[in]  num The channel numbers, max is 32.
\param[in] id The id of channel.
\retval    on success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
void crypto_channel_free(channel_context *ctx, u32 num, u32 id);

/**
\brief  get the private data of hard channel.
\param[in] ctx The context of channel.
\param[in] num The channel numbers, max is 32.
\param[in] id The id of channel.
\retval    on success, the address of context is returned.  On error, NULL is returned..
*/
void *crypto_channel_get_context(channel_context *ctx, u32 num, u32 id);

/**
\brief  get the rang.
\retval    random number.
*/
u32 get_rand(void);

void crypto_memset(void *s, int sn, int val, int n);
void crypto_memcpy(void* s, int sn, const void* c, int n);

#define crypto_iomap

#define crypto_ioremap_nocache(addr, size)  ioremap_nocache(addr, size)
#define crypto_iounmap(addr, size)          iounmap(addr)

#define crypto_read(addr)         (*(volatile unsigned int *)(addr))
#define crypto_write(addr, val)   (*(volatile unsigned int *)(addr) = (val))

#define crypto_msleep(msec)         msleep(msec)
#define crypto_udelay(msec)         udelay(msec)

void *crypto_calloc(size_t n, size_t size);
#define crypto_malloc(x)          (0 < (x) ? HI_KMALLOC(HI_ID_CIPHER, (x), GFP_KERNEL) : HI_NULL)
#define crypto_free(x)            {if (HI_NULL != (x) ) HI_KFREE(HI_ID_CIPHER, (x));}

s32 crypto_copy_from_user(void *to, const void *from, unsigned long n);
s32 crypto_copy_to_user(void  *to, const void *from, unsigned long n);
u32 get_rand(void);

/* ARM Memory barrier */
#ifdef CONFIG_ARCH_LP64_MODE
#define ARM_MEMORY_BARRIER()  do { mb(); isb(); dsb(sy);} while(0)
#else
#define ARM_MEMORY_BARRIER()  do { mb(); isb(); dsb(); } while(0)
#endif

#define crypto_queue_head                          wait_queue_head_t
#define crypto_queue_init(x)                       init_waitqueue_head(x)
#define crypto_queue_wait_up(x)                    wake_up_interruptible(x)
#define crypto_queue_wait_timeout(head, con, time) wait_event_interruptible_timeout(head, con, time)

#define crypto_request_irq(irq, func, name) osal_request_irq((irq + 32), func, IRQF_SHARED, name, "crypto")
#define crypto_free_irq(irq, name)          osal_free_irq((irq + 32), name, "crypto")

typedef struct semaphore                     crypto_mutex;
#define crypto_mutex_init(x)                 sema_init(x, 1)
#define crypto_mutex_lock(x)                 down_interruptible(x)
#define crypto_mutex_unlock(x)               up(x)
#define crypto_mutex_destroy(x)

#ifdef CONFIG_ARCH_LP64_MODE
#define flush_cache()                        flush_cache_all(); mb(); isb(); dsb(sy)
#else
#define flush_cache()                        flush_cache_all(); mb(); isb(); dsb()
#endif

#define crypto_owner                         pid_t
#define crypto_get_owner(x)                  *x = task_tgid_nr(current)

void smmu_get_table_addr(u64 *rdaddr, u64 *wraddr, u64 *table);

/**< allow modules to modify, default value is HI_ID_STB, the general module id*/
#define LOG_D_MODULE_ID             HI_ID_CIPHER
#define LOG_D_FUNCTRACE             (0)
#define LOG_D_UNFTRACE              (0)

/**< allow modules to define internel error code, from 0x1000*/
#define LOG_ERRCODE_DEF(errid)      (HI_U32)(((LOG_D_MODULE_ID) << 16)  | (errid))

/**< General Error Code, All modules can extend according to the rule */
#define HI_LOG_ERR_MEM              LOG_ERRCODE_DEF(0x0001)      /**< Memory Operation Error */
#define HI_LOG_ERR_SEM              LOG_ERRCODE_DEF(0x0002)      /**< Semaphore Operation Error */
#define HI_LOG_ERR_FILE             LOG_ERRCODE_DEF(0x0003)      /**< File Operation Error */
#define HI_LOG_ERR_LOCK             LOG_ERRCODE_DEF(0x0004)      /**< Lock Operation Error */
#define HI_LOG_ERR_PARAM            LOG_ERRCODE_DEF(0x0005)      /**< Invalid Parameter */
#define HI_LOG_ERR_TIMER            LOG_ERRCODE_DEF(0x0006)      /**< Timer error */
#define HI_LOG_ERR_THREAD           LOG_ERRCODE_DEF(0x0007)      /**< Thread Operation Error */
#define HI_LOG_ERR_TIMEOUT          LOG_ERRCODE_DEF(0x0008)      /**< Time Out Error */
#define HI_LOG_ERR_DEVICE           LOG_ERRCODE_DEF(0x0009)      /**< Device Operation Error */
#define HI_LOG_ERR_STATUS           LOG_ERRCODE_DEF(0x0010)      /**< Status Error */
#define HI_LOG_ERR_IOCTRL           LOG_ERRCODE_DEF(0x0011)      /**< IO Operation Error */
#define HI_LOG_ERR_INUSE            LOG_ERRCODE_DEF(0x0012)      /**< In use */
#define HI_LOG_ERR_EXIST            LOG_ERRCODE_DEF(0x0013)      /**< Have exist */
#define HI_LOG_ERR_NOEXIST          LOG_ERRCODE_DEF(0x0014)      /**< no exist */
#define HI_LOG_ERR_UNSUPPORTED      LOG_ERRCODE_DEF(0x0015)      /**< Unsupported */
#define HI_LOG_ERR_UNAVAILABLE      LOG_ERRCODE_DEF(0x0016)      /**< Unavailable */
#define HI_LOG_ERR_UNINITED         LOG_ERRCODE_DEF(0x0017)      /**< Uninited */
#define HI_LOG_ERR_DATABASE         LOG_ERRCODE_DEF(0x0018)      /**< Database Operation Error */
#define HI_LOG_ERR_OVERFLOW         LOG_ERRCODE_DEF(0x0019)      /**< Overflow */
#define HI_LOG_ERR_EXTERNAL         LOG_ERRCODE_DEF(0x0020)      /**< External Error */
#define HI_LOG_ERR_UNKNOWNED        LOG_ERRCODE_DEF(0x0021)      /**< Unknow Error */
#define HI_LOG_ERR_FLASH            LOG_ERRCODE_DEF(0x0022)      /**< Flash Operation Error*/
#define HI_LOG_ERR_ILLEGAL_IMAGE    LOG_ERRCODE_DEF(0x0023)      /**< Illegal Image */
#define HI_LOG_ERR_ILLEGAL_UUID     LOG_ERRCODE_DEF(0x0023)      /**< Illegal UUID */
#define HI_LOG_ERR_NOPERMISSION     LOG_ERRCODE_DEF(0x0023)      /**< No Permission */

#define HI_LOG_FATAL(fmt...)        HI_FATAL_PRINT(HI_ID_CIPHER, fmt)
#define HI_LOG_ERROR(fmt...)        HI_ERR_PRINT(HI_ID_CIPHER, fmt)
#define HI_LOG_WARN(fmt...)         HI_WARN_PRINT(HI_ID_CIPHER,  fmt)
#define HI_LOG_INFO(fmt...)         HI_INFO_PRINT(HI_ID_CIPHER,  fmt)
#define HI_LOG_DEBUG(fmt...)

/**< Function trace log, strictly prohibited to expand */
#define HI_LOG_PrintFuncWar(Func, ErrCode)  HI_LOG_WARN("Call %s return [0x%08X]\n", #Func, ErrCode)
#define HI_LOG_PrintFuncErr(Func, ErrCode)  HI_LOG_ERROR("Call %s return [0x%08X]\n", #Func, ErrCode)
#define HI_LOG_PrintErrCode(ErrCode)        HI_LOG_ERROR("Error Code: [0x%08X]\n", ErrCode)

/**< Used for displaying more detailed error information */
#define HI_LOG_PrintS32(val)                HI_LOG_WARN("%s = %d\n",        #val, val)
#define HI_LOG_PrintU32(val)
#define HI_LOG_PrintS64(val)                HI_LOG_WARN("%s = %lld\n",      #val, val)
#define HI_LOG_PrintU64(val)                HI_LOG_WARN("%s = %llu\n",      #val, val)
#define HI_LOG_PrintH32(val)                HI_LOG_WARN("%s = 0x%08X\n",    #val, val)
#define HI_LOG_PrintH64(val)                HI_LOG_WARN("%s = 0x%016llX\n", #val, val)
#define HI_LOG_PrintStr(val)                HI_LOG_WARN("%s = %s\n",        #val, val)
#define HI_LOG_PrintVoid(val)               HI_LOG_WARN("%s = %p\n",        #val, val)
#define HI_LOG_PrintFloat(val)              HI_LOG_WARN("%s = %f\n",        #val, val)
#define HI_LOG_PrintInfo(val)               HI_LOG_WARN("<%s>\n", val)

/**< Only used for self debug, Can be expanded as needed */
#define HI_DBG_PrintS32(val)                HI_LOG_DEBUG("%s = %d\n",       #val, val)
#define HI_DBG_PrintU32(val)                HI_LOG_DEBUG("%s = %u\n",       #val, val)
#define HI_DBG_PrintS64(val)                HI_LOG_DEBUG("%s = %lld\n",     #val, val)
#define HI_DBG_PrintU64(val)                HI_LOG_DEBUG("%s = %llu\n",     #val, val)
#define HI_DBG_PrintH32(val)                HI_LOG_DEBUG("%s = 0x%08X\n",   #val, val)
#define HI_DBG_PrintH64(val)                HI_LOG_DEBUG("%s = 0x%016llX\n",#val, val)
#define HI_DBG_PrintStr(val)                HI_LOG_DEBUG("%s = %s\n",       #val, val)
#define HI_DBG_PrintVoid(val)               HI_LOG_DEBUG("%s = %p\n",       #val, val)
#define HI_DBG_PrintFloat(val)              HI_LOG_DEBUG("%s = %f\n",       #val, val)
#define HI_DBG_PrintInfo(val)               HI_LOG_DEBUG("<%s>\n", val)

#if (LOG_D_FUNCTRACE == 1) || (LOG_D_UNFTRACE == 1)
#define HI_UNF_FuncEnter()                  HI_LOG_DEBUG(" >>>>>>[Enter]\n")    /**< Only used for unf interface */
#define HI_UNF_FuncExit()                   HI_LOG_DEBUG(" <<<<<<[Exit]\n")     /**< Only used for unf interface */
#else
#define HI_UNF_FuncEnter()
#define HI_UNF_FuncExit()
#endif

#if LOG_D_FUNCTRACE
#define HI_LOG_FuncEnter()                  HI_LOG_DEBUG(" =====>[Enter]\n")    /**< Used for all interface except unf */
#define HI_LOG_FuncExit()                   HI_LOG_DEBUG(" =====>[Exit]\n")     /**< Used for all interface except unf */
#else
#define HI_LOG_FuncEnter()
#define HI_LOG_FuncExit()
#endif

#define HI_LOG_CHECK(fnFunc)                            \
do                                                      \
{                                                       \
    HI_S32 s32iErrCode = fnFunc;                        \
    if (HI_SUCCESS != s32iErrCode)                      \
    {                                                   \
        HI_LOG_PrintFuncErr(#fnFunc, s32iErrCode);      \
    }                                                   \
} while (0)


#define HI_LOG_CHECK_PARAM(bVal)                        \
do                                                      \
{                                                       \
    if (bVal)                                           \
    {                                                   \
        HI_LOG_PrintErrCode(HI_LOG_ERR_PARAM);          \
        return HI_LOG_ERR_PARAM;                        \
    }                                                   \
} while (0)


#define HI_LOG_CHECK_INITED(u32InitCount)               \
do                                                      \
{                                                       \
    if (0 == u32InitCount)                              \
    {                                                   \
        HI_LOG_PrintErrCode(HI_LOG_ERR_UNINITED);       \
        return HI_LOG_ERR_UNINITED;                     \
    }                                                   \
} while (0)

#define HI_LOG_PrintBlock(data, length)

#endif  /* End of #ifndef __HI_DRV_CIPHER_H__*/
