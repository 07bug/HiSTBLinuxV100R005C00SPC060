#ifndef __VFMW_OSAL_EXT_HEADER__
#define __VFMW_OSAL_EXT_HEADER__

#include "mem_manage.h"


typedef SINT32(*vfmw_irq_handler_t)(SINT32, VOID *);

typedef enum FileOpenMode
{
    VFMW_O_RDONLY = 00000000,
    VFMW_O_WRONLY = 00000001,
    VFMW_O_RDWR   = 00000002,
    VFMW_O_CREATE = 00000100,
    VFMW_O_TRUNC  = 00001000,
    VFMW_O_APPEND = 00002000
} FileOpenMode;

typedef enum SpinLockType
{
    G_TASK_LOCK = 0,
    G_MEM_LOCK,
    G_VOQUE_LOCK,
    G_FSP_LOCK,
    G_DESTROY_LOCK,
} SpinLockType;

typedef enum SemType
{
    G_VFMW_SEM      = 0,
    G_RLSSTREAM_SEM = 1,
} SemType;

typedef enum FileType
{
    G_VFMW_SAVE_STR_FILE = 0,
    G_VFMW_SAEV_SEG_FILE = 1,
    G_VFMW_SAVE_YUV_FILE = 2
} FileType;

typedef enum MutexType
{
    G_INTEVENT = 0,
    G_INTWAITQUEUE = 1,
    G_VIR_PP_WQ = 2
} MutexType;

typedef enum RWLockType
{
    G_STATE_RWLOCK = 0
} RWLockType;


typedef  VOID  OSAL_FILE;
typedef  VOID  OSAL_ListHead;

typedef UINT32(*FN_OSAL_GetTimeInMs)(VOID);
typedef UINT32(*FN_OSAL_GetTimeInUs)(VOID);
typedef VOID (*FN_OSAL_SpinLockInit)(SpinLockType);
typedef SINT32(*FN_OSAL_SpinLock)(SpinLockType);
typedef SINT32(*FN_OSAL_SpinUnlock)(SpinLockType);
typedef VOID (*FN_OSAL_SemaInit)(SemType semType, int chanID);
typedef SINT32(*FN_OSAL_SemaDown)(SemType semType, int chanID);
typedef VOID (*FN_OSAL_SemaUp)(SemType, int chanID);
typedef VOID  *(*FN_OSAL_FileOpen)(const char *fileName, int flags, int mod);
typedef VOID (*FN_OSAL_FileClose)(OSAL_FILE *);
typedef SINT32(*FN_OSAL_FileRead)(char *buffer, UINT32 length, OSAL_FILE *pFile);
typedef SINT32(*FN_OSAL_FileWrite)(char *buffer, UINT32 length, OSAL_FILE *pFile);
typedef VOID  *(*FN_OSAL_MemSet)(VOID *s, SINT32 c, unsigned long n);
typedef VOID  *(*FN_OSAL_MemCpy)(VOID *dest, const VOID *src, unsigned long n);
typedef VOID  *(*FN_OSAL_MemMov)(VOID *dest, const VOID *src, unsigned long n);
typedef SINT32(*FN_OSAL_MemCmp)(VOID *dest, const VOID *src, unsigned long n);
typedef SINT32(*FN_OSAL_printk)(const char *fmt, ...);
typedef SINT32(*FN_OSAL_snprintf)(char *str, unsigned long size, const char *format, ...);
typedef SINT32(*FN_OSAL_sscanf)(const char *str, const char *format, ...);
typedef SINT32(*FN_OSAL_strncmp)(const char *s1, const char *s2, UINT32 n);
typedef UINT32(*FN_OSAL_strlcpy)(char *dest, const char *src, UINT32 size);
typedef UINT32(*FN_OSAL_strlcpy_command_line)(char *dest, UINT32 size);
typedef SINT8 *(*FN_OSAL_strsep)(char **stringp, const char *delim);
typedef long (*FN_OSAL_simple_strtol)(const char *cp, char **endp, UINT32 base);
typedef SINT8 *(*FN_OSAL_strstr)(const char *haystack, const char *needle);
typedef UINT32(*FN_OSAL_strlen)(const char *string);
typedef VOID  *(*FN_OSAL_ioremap)(UADDR  phys_addr, unsigned long size);
typedef VOID (*FN_OSAL_iounmap)(void *addr);
typedef VOID (*FN_OSAL_mb)(VOID);
typedef VOID (*FN_OSAL_udelay)(unsigned long usecs);
typedef VOID (*FN_OSAL_msleep)(unsigned int msecs);
typedef SINT32(*FN_OSAL_InitEvent)(MutexType mutexType, SINT32 initVal);
typedef SINT32(*FN_OSAL_GiveEvent)(MutexType mutexType);
typedef SINT32(*FN_OSAL_WaitEvent)(MutexType mutexType, SINT32 condition, SINT32 waitTimeInMs);
typedef VOID (*FN_OSAL_FlushCache)(VOID *ptr, UADDR  phy_addr, UINT32 length);
typedef VOID (*FN_OSAL_KernelFlushCache)(VOID *ptr, UADDR  phy_addr, UINT32 length);
typedef SINT32(*FN_OSAL_KernelMemAlloc)(UINT8 *memName, UINT32 length, UINT32 align, UINT32 isCached, MEM_DESC_S *pMemDesc);
typedef SINT32(*FN_OSAL_KernelMemFree)(MEM_DESC_S *pMemDesc);
typedef UINT8 *(*FN_OSAL_KernelRegisterMap)(UADDR PhyAddr, SINT32 Length);
typedef VOID (*FN_OSAL_KernelRegisterUnMap)(UINT8 *VirAddr);
typedef UINT8 *(*FN_OSAL_KernelMmap)(MEM_RECORD_S *pMemRec);
typedef VOID (*FN_OSAL_KernelMunMap)(UINT8 *p);
typedef UINT8 *(*FN_OSAL_KernelMmapMMZ)(MEM_RECORD_S *pMemRec);
typedef VOID (*FN_OSAL_KernelMunMapMMZ)(UINT8 *p);
typedef UINT8 *(*FN_OSAL_KernelMmapCache)(MEM_RECORD_S *pMemRec);
typedef UINT8 *(*FN_OSAL_KernelNsMmap)(UADDR phy_addr, UINT32 size);
typedef VOID (*FN_OSAL_KernelNsMunMap)(UINT8 *p);
typedef VOID (*FN_OSAL_KernelGetPageTableAddr)(UADDR *pu32ptaddr, UADDR *pu32err_rdaddr, UADDR *pu32err_wraddr);
typedef SINT32(*FN_OSAL_CreateTask)(VOID *pParam, SINT8 *taskName, VOID *pTaskFunc);
typedef SINT32(*FN_OSAL_StopTask)(VOID *pParam);
typedef SINT32(*FN_OSAL_request_irq)(UINT32 irq, vfmw_irq_handler_t handler, unsigned long flags, const char *name, void *dev);
typedef VOID (*FN_OSAL_free_irq)(UINT32 irq, const char *name, void *dev);
typedef VOID  *(*FN_OSAL_phys_to_virt)(UADDR address);
typedef VOID  *(*FN_OSAL_AllocVirMem)(SINT32 size);
typedef VOID (*FN_OSAL_FreeVirMem)(VOID *virMem);
typedef VOID  *(*FN_OSAL_KmallocVirMem)(SINT32 size);
typedef VOID (*FN_OSAL_KfreeVirMem)(VOID *virMem);
typedef SINT32(*FN_OSAL_vfmw_proc_init)(VOID);
typedef VOID (*FN_OSAL_vfmw_proc_exit)(VOID);
typedef SINT32(*FN_OSAL_vfmw_proc_create)(UINT8 *proc_name, VOID *fp_read, VOID *fp_write);
typedef VOID (*FN_OSAL_vfmw_proc_destroy)(UINT8 *proc_name);
typedef SINT32(*FN_OSAL_Get_Vp9_Support)(UINT32 *pVp9Support);
typedef UINT64(*FN_OSAL_Do_Div)(UINT64 Dividend, UINT32 Divison);
typedef VOID (*FN_OSAL_ListAddTail)(OSAL_ListHead *pListNew, OSAL_ListHead *pListHead);
typedef VOID (*FN_OSAL_ListAdd)(OSAL_ListHead *pListNew, OSAL_ListHead *pListHead);
typedef VOID (*FN_OSAL_ListDel)(OSAL_ListHead *pList);
typedef SINT32(*FN_OSAL_ListIsEmpty)(OSAL_ListHead *pListHead);
typedef SINT32(*FN_OSAL_SeqPrintf)(VOID *pSeqFd, const char *Format, ...);

typedef struct Vfmw_Osal_Func_Ptr
{
    FN_OSAL_GetTimeInMs            pfun_Osal_GetTimeInMs;
    FN_OSAL_GetTimeInUs            pfun_Osal_GetTimeInUs;
    FN_OSAL_SpinLockInit           pfun_Osal_SpinLockInit;
    FN_OSAL_SpinLock               pfun_Osal_SpinLock;
    FN_OSAL_SpinUnlock             pfun_Osal_SpinUnlock;
    FN_OSAL_SemaInit               pfun_Osal_SemaInit;
    FN_OSAL_SemaDown               pfun_Osal_SemaDown;
    FN_OSAL_SemaUp                 pfun_Osal_SemaUp;
    FN_OSAL_FileOpen               pfun_Osal_FileOpen;
    FN_OSAL_FileClose              pfun_Osal_FileClose;
    FN_OSAL_FileRead               pfun_Osal_FileRead;
    FN_OSAL_FileWrite              pfun_Osal_FileWrite;
    FN_OSAL_MemSet                 pfun_Osal_MemSet;
    FN_OSAL_MemCpy                 pfun_Osal_MemCpy;
    FN_OSAL_MemMov                 pfun_Osal_MemMov;
    FN_OSAL_MemCmp                 pfun_Osal_MemCmp;
    FN_OSAL_printk                 pfun_Osal_printk;
    FN_OSAL_snprintf               pfun_Osal_snprintf;
    FN_OSAL_sscanf                 pfun_Osal_sscanf;
    FN_OSAL_strncmp                pfun_Osal_strncmp;
    FN_OSAL_strlcpy_command_line   pfun_Osal_strlcpy_command_line;
    FN_OSAL_simple_strtol          pfun_Osal_simple_strtol;
    FN_OSAL_strlcpy                pfun_Osal_strlcpy;
    FN_OSAL_strsep                 pfun_Osal_strsep;
    FN_OSAL_strstr                 pfun_Osal_strstr;
    FN_OSAL_strlen                 pfun_Osal_strlen;
    FN_OSAL_ioremap                pfun_Osal_ioremap;
    FN_OSAL_iounmap                pfun_Osal_iounmap;
    FN_OSAL_mb                     pfun_Osal_mb;
    FN_OSAL_udelay                 pfun_Osal_udelay;
    FN_OSAL_msleep                 pfun_Osal_msleep;
    FN_OSAL_InitEvent              pfun_Osal_InitEvent;
    FN_OSAL_GiveEvent              pfun_Osal_GiveEvent;
    FN_OSAL_WaitEvent              pfun_Osal_WaitEvent;
    FN_OSAL_FlushCache             pfun_Osal_FlushCache;
    FN_OSAL_KernelFlushCache       pfun_Osal_KernelFlushCache;
    FN_OSAL_KernelMemAlloc         pfun_Osal_KernelMemAlloc;
    FN_OSAL_KernelMemFree          pfun_Osal_KernelMemFree;
    FN_OSAL_KernelRegisterMap      pfun_Osal_KernelRegisterMap;
    FN_OSAL_KernelRegisterUnMap    pfun_Osal_KernelRegisterUnMap;
    FN_OSAL_KernelMmap             pfun_Osal_KernelMmap;
    FN_OSAL_KernelMunMap           pfun_Osal_KernelMunMap;
    FN_OSAL_KernelMmapMMZ          pfun_Osal_KernelMmapMMZ;
    FN_OSAL_KernelMunMapMMZ        pfun_Osal_KernelMunMapMMZ;
    FN_OSAL_KernelMmapCache        pfun_Osal_KernelMmapCache;
    FN_OSAL_KernelNsMmap           pfun_Osal_KernelNsMmap;
    FN_OSAL_KernelNsMunMap         pfun_Osal_KernelNsMunMap;
    FN_OSAL_KernelGetPageTableAddr pfun_Osal_KernelGetPageTableAddr;
    FN_OSAL_CreateTask             pfun_Osal_CreateTask;
    FN_OSAL_StopTask               pfun_Osal_StopTask;
    FN_OSAL_request_irq            pfun_Osal_request_irq;
    FN_OSAL_free_irq               pfun_Osal_free_irq;
    FN_OSAL_phys_to_virt           pfun_Osal_phys_to_virt;
    FN_OSAL_AllocVirMem            pfun_Osal_AllocVirMem;
    FN_OSAL_FreeVirMem             pfun_Osal_FreeVirMem;
    FN_OSAL_AllocVirMem            pfun_Osal_KmallocVirMem;
    FN_OSAL_FreeVirMem             pfun_Osal_KfreeVirMem;
    FN_OSAL_vfmw_proc_init         pfun_Osal_vfmw_proc_init;
    FN_OSAL_vfmw_proc_exit         pfun_Osal_vfmw_proc_exit;
    FN_OSAL_vfmw_proc_create       pfun_Osal_vfmw_proc_create;
    FN_OSAL_vfmw_proc_destroy      pfun_Osal_vfmw_proc_destroy;
    FN_OSAL_Get_Vp9_Support        pfun_Osal_GetVp9Support;
    FN_OSAL_Do_Div                 pfun_Osal_DoDiv;
    FN_OSAL_ListAddTail            pfun_Osal_ListAddTail;
    FN_OSAL_ListAdd                pfun_Osal_ListAdd;
    FN_OSAL_ListDel                pfun_Osal_ListDel;
    FN_OSAL_ListIsEmpty            pfun_Osal_ListIsEmpty;
    FN_OSAL_SeqPrintf              pfun_Osal_seq_printf;
} Vfmw_Osal_Func_Ptr;


extern Vfmw_Osal_Func_Ptr vfmw_Osal_Func_Ptr_S;

#define OSAL_FP_strstr                     vfmw_Osal_Func_Ptr_S.pfun_Osal_strstr
#define OSAL_FP_ioremap                    vfmw_Osal_Func_Ptr_S.pfun_Osal_ioremap
#define OSAL_FP_iounmap                    vfmw_Osal_Func_Ptr_S.pfun_Osal_iounmap
#define OSAL_FP_mb                         vfmw_Osal_Func_Ptr_S.pfun_Osal_mb
#define OSAL_FP_udelay                     vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay
#define OSAL_FP_msleep                     vfmw_Osal_Func_Ptr_S.pfun_Osal_msleep
#define OSAL_FP_init_event                 vfmw_Osal_Func_Ptr_S.pfun_Osal_InitEvent
#define OSAL_FP_give_event                 vfmw_Osal_Func_Ptr_S.pfun_Osal_GiveEvent
#define OSAL_FP_wait_event                 vfmw_Osal_Func_Ptr_S.pfun_Osal_WaitEvent
#define OSAL_FP_flush_cache                vfmw_Osal_Func_Ptr_S.pfun_Osal_FlushCache
#define OSAL_FP_kernel_flush_cache         vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelFlushCache
#define OSAL_FP_kernel_mem_alloc           vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMemAlloc
#define OSAL_FP_kernel_mem_free            vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMemFree
#define OSAL_FP_kernel_register_map        vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelRegisterMap
#define OSAL_FP_kernel_register_unmap      vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelRegisterUnMap
#define OSAL_FP_kernel_mmap_mmz            vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmapMMZ
#define OSAL_FP_kernel_unmap_mmz           vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMunMapMMZ
#define OSAL_FP_kernel_mmap_cache          vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmapCache
#define OSAL_FP_kernel_ns_map              vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelNsMmap
#define OSAL_FP_kernel_ns_unmap            vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelNsMunMap
#define OSAL_FP_kernel_get_page_table_addr vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelGetPageTableAddr
#define OSAL_FP_create_task                vfmw_Osal_Func_Ptr_S.pfun_Osal_CreateTask
#define OSAL_FP_stop_task                  vfmw_Osal_Func_Ptr_S.pfun_Osal_StopTask
#define OSAL_FP_request_irq                vfmw_Osal_Func_Ptr_S.pfun_Osal_request_irq
#define OSAL_FP_alloc_virmem               vfmw_Osal_Func_Ptr_S.pfun_Osal_AllocVirMem
#define OSAL_FP_free_virmem                vfmw_Osal_Func_Ptr_S.pfun_Osal_FreeVirMem
#define OSAL_FP_kmalloc_virmem             vfmw_Osal_Func_Ptr_S.pfun_Osal_KmallocVirMem
#define OSAL_FP_kfree_virmem               vfmw_Osal_Func_Ptr_S.pfun_Osal_KfreeVirMem
#define OSAL_FP_free_irq                   vfmw_Osal_Func_Ptr_S.pfun_Osal_free_irq
#define OSAL_FP_phys_to_virt               vfmw_Osal_Func_Ptr_S.pfun_Osal_phys_to_virt
#define OSAL_FP_get_time_ms                vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInMs
#define OSAL_FP_get_time_us                vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInUs
#define OSAL_FP_spin_lock_init             vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit
#define OSAL_FP_spin_lock                  vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLock
#define OSAL_FP_spin_unlock                vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinUnlock
#define OSAL_FP_sema_init                  vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaInit
#define OSAL_FP_sema_down                  vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaDown
#define OSAL_FP_sema_up                    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaUp
#define OSAL_FP_memmov                     vfmw_Osal_Func_Ptr_S.pfun_Osal_MemMov
#define OSAL_FP_memcmp                     vfmw_Osal_Func_Ptr_S.pfun_Osal_MemCmp
#define OSAL_FP_strlcpy_command_line       vfmw_Osal_Func_Ptr_S.pfun_Osal_strlcpy_command_line
#define OSAL_FP_simple_strtol              vfmw_Osal_Func_Ptr_S.pfun_Osal_simple_strtol
#define OSAL_FP_strlcpy                    vfmw_Osal_Func_Ptr_S.pfun_Osal_strlcpy
#define OSAL_FP_strsep                     vfmw_Osal_Func_Ptr_S.pfun_Osal_strsep
#define OSAL_FP_print                      vfmw_Osal_Func_Ptr_S.pfun_Osal_printk
#define OSAL_FP_memcpy                     vfmw_Osal_Func_Ptr_S.pfun_Osal_MemCpy
#define OSAL_FP_memset                     vfmw_Osal_Func_Ptr_S.pfun_Osal_MemSet
#define OSAL_FP_strlen                     vfmw_Osal_Func_Ptr_S.pfun_Osal_strlen
#define OSAL_FP_strncmp                    vfmw_Osal_Func_Ptr_S.pfun_Osal_strncmp
#define OSAL_FP_snprintf                   vfmw_Osal_Func_Ptr_S.pfun_Osal_snprintf
#define OSAL_FP_fopen                      vfmw_Osal_Func_Ptr_S.pfun_Osal_FileOpen
#define OSAL_FP_fclose                     vfmw_Osal_Func_Ptr_S.pfun_Osal_FileClose
#define OSAL_FP_fread                      vfmw_Osal_Func_Ptr_S.pfun_Osal_FileRead
#define OSAL_FP_fwrite                     vfmw_Osal_Func_Ptr_S.pfun_Osal_FileWrite
#define OSAL_FP_proc_init                  vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_init
#define OSAL_FP_proc_exit                  vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_exit
#define OSAL_FP_proc_create                vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_create
#define OSAL_FP_proc_destroy               vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_destroy
#define OSAL_FP_ssanf                      vfmw_Osal_Func_Ptr_S.pfun_Osal_sscanf
#define OSAL_FP_mmap                       vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmap
#define OSAL_FP_unmap                      vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMunMap
#define OSAL_FP_do_div                     vfmw_Osal_Func_Ptr_S.pfun_Osal_DoDiv
#define OSAL_FP_list_add_tail              vfmw_Osal_Func_Ptr_S.pfun_Osal_ListAddTail
#define OSAL_FP_list_add                   vfmw_Osal_Func_Ptr_S.pfun_Osal_ListAdd
#define OSAL_FP_list_del                   vfmw_Osal_Func_Ptr_S.pfun_Osal_ListDel
#define OSAL_FP_list_is_empty              vfmw_Osal_Func_Ptr_S.pfun_Osal_ListIsEmpty
#define OSAL_FP_seq_printf                 vfmw_Osal_Func_Ptr_S.pfun_Osal_seq_printf


VOID OSAL_InitVfmwInterface(VOID);

#endif
