
/******************************************************************************

  ��Ȩ���� (C), 2001-2011, ��˼�뵼�����޹�˾

******************************************************************************
    �� �� ��   : vfmw_osal.c
    �� �� ��   : ����
    ��    ��   :
    ��������   :
    ����޸�   :
    ��������   : Ϊvfmw���ƵĲ���ϵͳ����ģ��


    �޸���ʷ   :
    1.��    �� : 2009-05-12
    ��    ��   :
    �޸�����   :

******************************************************************************/

#include "hi_kernel_adapt.h"
#include "vfmw_osal.h"
#include "public.h"
#include "vfmw_osal_ext.h"

#include "vfmw_proc.h"

//#include "drv_vfmw_ext.h"

extern Vfmw_Osal_Func_Ptr vfmw_Osal_Func_Ptr_S;

#ifdef ENV_ARMLINUX_KERNEL
VOID  *g_fpLog = NULL;
SINT8  g_TmpMsg[1024]; /* ��ӡ�м������ݴ����� */
#endif

/* Wang Yun */
/* SpinLock */
OSAL_IRQ_SPIN_LOCK g_TaskLock;
OSAL_IRQ_SPIN_LOCK g_RecordLock;
OSAL_IRQ_SPIN_LOCK g_SpinLock;
OSAL_IRQ_SPIN_LOCK g_SpinLock_fsp;
OSAL_IRQ_SPIN_LOCK g_SpinLockIrq_Destroy;
OSAL_IRQ_SPIN_LOCK g_ActivateLock;
OSAL_IRQ_SPIN_LOCK g_SpinLockIsr_MsgQueue;
OSAL_IRQ_SPIN_LOCK g_SpinLockIsr_Image2D;
OSAL_IRQ_SPIN_LOCK g_FrameBuf_SpinLock;

/* Mutext */
OSAL_TASK_MUTEX g_IntEvent;

OSAL_SEMA g_stSem;

#ifdef ENV_ARMLINUX_KERNEL
SINT32 dprint_vfmw(UINT32 type, const SINT8 *format, ...)
{
    va_list args;
    SINT32  nTotalChar = 0;

    /* ��Ϣ���͹��� */
    if ((PRN_ALWS != type) && (0 == (g_PrintEnable & (1 << type)))) /* ������ӡû�д� */
    {
        return -1;
    }

    /* ����Ϣ��ӡ���ַ��� */
    va_start(args, format);
    nTotalChar = vsnprintf(g_TmpMsg, sizeof(g_TmpMsg), format, args);
    va_end(args);

    if ((nTotalChar <= 0) || (nTotalChar >= 1023))
    {
        return -1;
    }

    /* ���ַ���������豸 */
    if (DEV_SCREEN == g_PrintDevice)      /* �豸0: ��Ļ(����) */
    {
#ifdef ENV_ARMLINUX_KERNEL
#ifndef  HI_ADVCA_FUNCTION_RELEASE
        return (printk("%s", g_TmpMsg));
#else
        return 0;
#endif
#endif
    }
    else if (DEV_SYSLOG == g_PrintDevice) /* �豸1: ϵͳ��־ */
    {
#ifdef ENV_ARMLINUX_KERNEL
        // ��Ϣ(g_TmpMsg, nTotalChar)�����ϵͳ��־��ӡ......
#endif
    }
    else if (DEV_FILE == g_PrintDevice)   /* �豸2: �ļ� */
    {
        if (g_fpLog)
        {
#ifdef ENV_ARMLINUX_KERNEL
            //return ( klib_fwrite(g_TmpMsg, nTotalChar, g_fpLog) );
            return (vfmw_Osal_Func_Ptr_S.pfun_Osal_FileWrite(g_TmpMsg, nTotalChar, g_fpLog));
#endif
        }
    }
    else if (DEV_MEM == g_PrintDevice)    /* �豸3: �ڴ� */
    {
        // ��δ�ӡ���ڴ�......
    }

    return -1;
}
#endif

#define  OSAL_ASSERT_RET( cond, ret)                                    \
    do {                                                                \
        if( !(cond) )                                                   \
        {                                                               \
            dprint_vfmw(PRN_FATAL,"L:%d ASSERT RETURN\n", __LINE__);    \
            return ret;                                                 \
        }                                                               \
    }while(0)

/************************************************************************/
/* OSAL_GetTimeInMs():  ��ȡϵͳʱ��                                    */
/************************************************************************/
UINT32 OSAL_GetTimeInMs(VOID)
{
    UINT64   SysTime;

    SysTime = sched_clock();
    do_div(SysTime, 1000000);
    return (UINT32)SysTime;
}

UINT32 OSAL_GetTimeInUs(VOID)
{
    UINT64   SysTime;

    SysTime = sched_clock();
    do_div(SysTime, 1000);
    return (UINT32)SysTime;
}

/*  ��������                                                            */
/************************************************************************/
SINT32 OSAL_CreateTask( OSAL_TASK *pTask, SINT8 TaskName[], VOID *pTaskFunction )
{
    OSAL_ASSERT_RET(pTask != NULL, OSAL_ERR);
    OSAL_ASSERT_RET(pTaskFunction != NULL, OSAL_ERR);

    *pTask = kthread_create(pTaskFunction, (VOID *)NULL, TaskName);

    if (IS_ERR(*pTask))
    {
        dprint(PRN_FATAL, "can not create thread!\n");
        return ( VF_ERR_SYS );
    }

    wake_up_process(*pTask);
    return OSAL_OK;
}

/************************************************************************/
/* ��������                                                             */
/************************************************************************/
SINT32 OSAL_WakeupTask( OSAL_TASK *pTask )
{
    OSAL_ASSERT_RET(pTask != NULL, OSAL_ERR);

    return OSAL_OK;
}

/************************************************************************/
/* ��������                                                             */
/************************************************************************/
SINT32 OSAL_DeleteTask(OSAL_TASK *pTask)
{
    OSAL_ASSERT_RET(pTask != NULL, OSAL_ERR);

    return OSAL_OK;
}

/************************************************************************/
/* ��ʼ���¼�                                                           */
/************************************************************************/
SINT32 OSAL_InitEvent( OSAL_EVENT *pEvent, SINT32 InitVal )
{
    OSAL_ASSERT_RET(pEvent != NULL, OSAL_ERR);

    pEvent->flag = InitVal;
    init_waitqueue_head( &(pEvent->queue_head) );
    return OSAL_OK;
}

/************************************************************************/
/* �����¼�                                                             */
/************************************************************************/
SINT32 OSAL_GiveEvent( OSAL_EVENT *pEvent )
{
    OSAL_ASSERT_RET(pEvent != NULL, OSAL_ERR);

    pEvent->flag = 1;
    wake_up_interruptible ( &(pEvent->queue_head) );

    return OSAL_ERR;
}

/************************************************************************/
/* �ȴ��¼�                                                             */
/* �¼���������OSAL_OK����ʱ����OSAL_ERR ��condition������������ȴ�    */
/************************************************************************/
SINT32 OSAL_WaitEvent( OSAL_EVENT *pEvent, SINT32 msWaitTime )
{
    SINT32 l_ret;

    OSAL_ASSERT_RET(pEvent != NULL, OSAL_ERR);

    l_ret = (SINT32)wait_event_interruptible_timeout( pEvent->queue_head, (pEvent->flag != 0), msecs_to_jiffies(msWaitTime) );

    pEvent->flag = 0;//(pEvent->flag>0)? (pEvent->flag-1): 0;

    if (l_ret == 0)
    {
        return OSAL_OK;
    } else
    {
        return OSAL_ERR;
    }
}

UINT8 *KernelRegisterMap(UADDR  PhyAddr)
{
    return (UINT8 *)ioremap_nocache( PhyAddr, 0x10000 );
}

VOID KernelRegisterUnMap(UINT8 *VirAddr)
{
    iounmap(VirAddr);
    return;
}

struct file *klib_fopen(const char *filename, int flags, int mode)
{
    struct file *filp;

    OSAL_ASSERT_RET(filename != NULL, NULL);

    filp = filp_open(filename, flags, mode);

    return (IS_ERR(filp)) ? NULL : filp;
}

void klib_fclose(struct file *filp)
{
    mm_segment_t oldfs;
    if (filp)
    {
        oldfs = get_fs();
        set_fs(KERNEL_DS);
        vfs_fsync(filp, 0);
        set_fs(oldfs);
        filp_close(filp, NULL);
    }
}

int klib_fread(char *buf, unsigned int len, struct file *filp)
{
    int readlen;
    mm_segment_t oldfs;

    if (filp == NULL)
    {
        return -ENOENT;
    }

    if (buf == NULL)
    {
        return -ENOENT;
    }

    if (((filp->f_flags & O_ACCMODE) & (O_RDONLY | O_RDWR)) == 0)
    {
        return -EACCES;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    readlen = vfs_read(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return readlen;
}

int klib_fwrite(char *buf, int len, struct file *filp)
{
    int writelen;
    mm_segment_t oldfs;

    if (filp == NULL)
    {
        return -ENOENT;
    }

    if (buf == NULL)
    {
        return -ENOENT;
    }

    if (((filp->f_flags & O_ACCMODE) & (O_WRONLY | O_RDWR)) == 0)
    {
        return -EACCES;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);
    writelen = vfs_write(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);

    return writelen;
}

VOID OSAL_SEMA_INTIT(VOID)
{
    sema_init(&g_stSem, 1);
}

SINT32 OSAL_DOWN_INTERRUPTIBLE(VOID)
{
    HI_S32 s32Ret;
    s32Ret = down_interruptible(&g_stSem);
    return s32Ret;
}

VOID OSAL_UP(VOID)
{
    up(&g_stSem);
}

/************************************************************************/
/* ����ʼ��                                                             */
/************************************************************************/
inline VOID OSAL_SpinLockIRQInit(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    if (pIntrMutex == NULL)
    {
        return;
    }

    spin_lock_init(&pIntrMutex->irq_lock);
    pIntrMutex->isInit = 1;

    return;
}

/************************************************************************/
/* �жϻ������(���ж��Ҽ���)                                           */
/************************************************************************/
inline SINT32 OSAL_SpinLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    if (pIntrMutex == NULL)
    {
        return OSAL_ERR;
    }

    if (pIntrMutex->isInit == 0)
    {
        spin_lock_init(&pIntrMutex->irq_lock);
        pIntrMutex->isInit = 1;
    }

#ifndef Hi3716MV410
    spin_lock_irqsave(&pIntrMutex->irq_lock, pIntrMutex->irq_lockflags);
#else
    spin_lock(&pIntrMutex->irq_lock);
#endif

    return OSAL_OK;
}

/************************************************************************/
/* �жϻ������(���ж���ȥ��)                                           */
/************************************************************************/
inline SINT32 OSAL_SpinUnLockIRQ(OSAL_IRQ_SPIN_LOCK *pIntrMutex)
{
    if (pIntrMutex == NULL)
    {
        return OSAL_ERR;
    }

#ifndef Hi3716MV410
    spin_unlock_irqrestore(&pIntrMutex->irq_lock, pIntrMutex->irq_lockflags);
#else
    spin_unlock(&pIntrMutex->irq_lock);
#endif

    return OSAL_OK;
}

/******************************************************************************
                       ���￪ʼ�ǲ�Ʒ���컯����
******************************************************************************/

#ifdef VFMW_BVT_SUPPORT

extern MEM_DESC_S    (*mem_malloc)(UINT8 *MemName, UINT32 len, UINT32 align);
extern VOID          (*mem_free)( MEM_DESC_S mem);

/************************************************************************/
/* ���������ڴ棨���ܷ�����������                                       */
/************************************************************************/
VOID *OSAL_AllocVirMem(SINT32 Size)
{
    return vmalloc(Size);
}

/************************************************************************/
/* �ͷ������ڴ棨���ܷ�����������                                       */
/************************************************************************/
VOID OSAL_FreeVirMem(VOID *p)
{
    if (p)
    {
        vfree(p);
    }
}

SINT32 KernelMemMalloc(UINT8 *MemName, UINT32 len, UINT32 align, UINT32 IsCached, MEM_DESC_S *pMemDesc)
{
    MEM_DESC_S AllocMem;

    if (mem_malloc == NULL)
    {
        return -1;
    }

    OSAL_ASSERT_RET(pMemDesc != NULL, OSAL_ERR);
    OSAL_ASSERT_RET(len != 0, OSAL_ERR);

    AllocMem = mem_malloc( MemName, len, align);

    if ( NULL == AllocMem.VirAddr )
    {
        memset(pMemDesc, 0, sizeof(MEM_DESC_S));
        return -1;
    }
    else
    {
        pMemDesc->PhyAddr = AllocMem.PhyAddr;
        pMemDesc->VirAddr = AllocMem.VirAddr;
        pMemDesc->Length  = AllocMem.Length;
        return 0;
    }
}

SINT32 KernelMemFree(MEM_DESC_S *pMemDesc)
{
    MEM_DESC_S AllocMem;

    memset(&AllocMem, 0, sizeof(MEM_DESC_S));

    OSAL_ASSERT_RET(pMemDesc != NULL, OSAL_ERR);

    if (mem_free == NULL)
    {
        return -1;
    }

    AllocMem.Length = pMemDesc->Length;
    AllocMem.VirAddr = pMemDesc->VirAddr;
    AllocMem.PhyAddr = pMemDesc->PhyAddr;
    mem_free(AllocMem);

    return 0;
}

UINT8 *KernelMmap(UADDR phyaddr, UINT32 len)
{
    /*����BVT����ڴ�������ⲿ���У��Ҳ������������֧�����ֱ�ӷ���NULL����*/
    return NULL;
}

UINT8 *KernelMmapCache(UADDR phyaddr, UINT32 len)
{
    /*����BVT����ڴ�������ⲿ���У��Ҳ������������֧�����ֱ�ӷ���NULL����*/
    return NULL;
}

VOID KernelMunmap(UINT8 *p )
{
    /*����BVT����ڴ�������ⲿ���У��Ҳ������������֧�����ʲô����������*/
    return;
}

VOID KernelFlushCache(VOID *ptr, UADDR phy_addr, UINT32 len)
{
    /*����BVT����ڴ�������ⲿ���У��Ҳ������������֧�����ʲô����������*/
    return;
}

void klib_flush_cache(void *ptr, UADDR phy_addr, unsigned int len)
{
    /*����BVT����ڴ�������ⲿ���У��Ҳ������������֧�����ʲô����������*/
    return;
}

#else

/************************************************************************/
/* ���������ڴ棨���ܷ�����������                                       */
/************************************************************************/
VOID *OSAL_AllocVirMem(SINT32 Size)
{
    OSAL_ASSERT_RET(Size != 0, NULL);

    return HI_VMALLOC(HI_ID_VFMW, Size);
}

/************************************************************************/
/* �ͷ������ڴ棨���ܷ�����������                                       */
/************************************************************************/
VOID OSAL_FreeVirMem(VOID *p)
{
    if (p)
    {
        HI_VFREE(HI_ID_VFMW, p);
    }
}

SINT32 KernelMemMalloc(UINT8 *MemName, UINT32 len, UINT32 align, UINT32 IsCached, MEM_DESC_S *pMemDesc)
{
    MMZ_BUFFER_S stMmzBuffer;
    memset(&stMmzBuffer, 0, sizeof(MMZ_BUFFER_S));

    OSAL_ASSERT_RET(pMemDesc != NULL, OSAL_ERR);
    OSAL_ASSERT_RET(len != 0, OSAL_ERR);

    if (HI_SUCCESS != HI_DRV_MMZ_Alloc(MemName, NULL, len, align, &stMmzBuffer))
    {
        memset(pMemDesc, 0, sizeof(MEM_DESC_S));
        return -1;
    }

    if ( 0 != stMmzBuffer.u32StartPhyAddr )
    {
        if (IsCached == 1)
        {
            if (HI_SUCCESS != HI_DRV_MMZ_MapCache(&stMmzBuffer))
            {
                memset(pMemDesc, 0, sizeof(MEM_DESC_S));
                return -1;
            }
        }
        else
        {
            if (HI_SUCCESS != HI_DRV_MMZ_Map(&stMmzBuffer))
            {
                memset(pMemDesc, 0, sizeof(MEM_DESC_S));
                return -1;
            }
        }
    }
    else
    {
        memset(pMemDesc, 0, sizeof(MEM_DESC_S));
        return -1;
    }

    pMemDesc->PhyAddr = (SINT32)stMmzBuffer.u32StartPhyAddr;
    pMemDesc->VirAddr = stMmzBuffer.pu8StartVirAddr;
    pMemDesc->Length  = (SINT32)stMmzBuffer.u32Size;


    return 0;
}

SINT32 KernelMemFree(MEM_DESC_S *pMemDesc)
{
    MMZ_BUFFER_S stMBuf;
    memset(&stMBuf, 0, sizeof(MMZ_BUFFER_S));

    OSAL_ASSERT_RET(pMemDesc != NULL, OSAL_ERR);

    stMBuf.u32StartPhyAddr = (UINT32)pMemDesc->PhyAddr;
    stMBuf.pu8StartVirAddr = pMemDesc->VirAddr;
    stMBuf.u32Size         = (UINT32)pMemDesc->Length;

    HI_DRV_MMZ_Unmap(&stMBuf);
    HI_DRV_MMZ_Release(&stMBuf);

    return 0;
}

UINT8 *KernelMmap(UADDR phyaddr, UINT32 len)
{
    SINT32 s32Ret = 0;
    MMZ_BUFFER_S stMemBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));
    stMemBuf.u32StartPhyAddr = phyaddr;

    s32Ret = HI_DRV_MMZ_Map(&stMemBuf);

    if (s32Ret != HI_SUCCESS)
    {
        dprint(PRN_FATAL, "vfmw_osal.c, line %d: HI_DRV_MMZ_Map ERR\n", __LINE__);
    }

    return stMemBuf.pu8StartVirAddr;

}

UINT8 *KernelMmapCache(UADDR phyaddr, UINT32 len)
{
    MMZ_BUFFER_S stMemBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));
    stMemBuf.u32StartPhyAddr = phyaddr;

    (VOID)HI_DRV_MMZ_MapCache(&stMemBuf);

    return stMemBuf.pu8StartVirAddr;
}

VOID KernelMunmap(UINT8 *p )
{
    MMZ_BUFFER_S stMemBuf;
    memset(&stMemBuf, 0, sizeof(MMZ_BUFFER_S));

    if (p == HI_NULL)
    {
        return;
    }

    stMemBuf.pu8StartVirAddr = p;

    HI_DRV_MMZ_Unmap(&stMemBuf);
}

VOID KernelFlushCache(VOID *ptr, UADDR phy_addr, UINT32 len)
{
    unsigned long flags;
    DEFINE_SPINLOCK(cache_lock);

    if (ptr == HI_NULL)
    {
        return;
    }

    spin_lock_irqsave(&cache_lock, flags);
    __cpuc_flush_dcache_area((void *)ptr, (size_t)len); // flush l1cache
    outer_flush_range(phy_addr, phy_addr + len); // flush l2cache

    spin_unlock_irqrestore(&cache_lock, flags);
    return;
}

void klib_flush_cache(void *ptr, UADDR phy_addr, unsigned int len)
{
    unsigned long flags;
    DEFINE_SPINLOCK(cache_lock);

    if (ptr == HI_NULL)
    {
        return;
    }

    spin_lock_irqsave(&cache_lock, flags);

    __cpuc_flush_dcache_area((void *)ptr, (size_t)len); // flush l1cache
    outer_flush_range(phy_addr, phy_addr + len); // flush l2cache

    spin_unlock_irqrestore(&cache_lock, flags);
    return;
}

#endif

VOID Sema_Init_with_Option(OSAL_SEMA *stSem)
{
    if (stSem == HI_NULL)
    {
        return;
    }

    sema_init(stSem, 1);
}

SINT32 Down_Interruptible_with_Option(OSAL_SEMA *stSem)
{
    SINT32 s32Ret;

    if (stSem == HI_NULL)
    {
        return OSAL_ERR;
    }

    s32Ret = down_interruptible(stSem);
    return s32Ret;
}

VOID Up_Interruptible_with_Option(OSAL_SEMA *stSem)
{
    if (stSem == HI_NULL)
    {
        return;
    }

    up(stSem);
}

/* Wang Yun */
OSAL_IRQ_SPIN_LOCK *GetSpinLockByEnum(SpinLockType spinLockType)
{
    OSAL_IRQ_SPIN_LOCK *pOsalSpinLock = NULL;

    switch (spinLockType)
    {
        case G_TASKLOCK:
            pOsalSpinLock = &g_TaskLock;
            break;

        case G_RECORDLOCK:
            pOsalSpinLock = &g_RecordLock;
            break;

        case G_SPINLOCK:
            pOsalSpinLock = &g_SpinLock;
            break;

        case G_SPINLOCK_FSP:
            pOsalSpinLock = &g_SpinLock_fsp;
            break;

        case G_SPINLOCKIRQ_DESTROY:
            pOsalSpinLock = &g_SpinLockIrq_Destroy;
            break;

        case G_ACTIVATELOCK:
            pOsalSpinLock = &g_ActivateLock;
            break;

        case G_SPINLOCKISR_MSGQUE:
            pOsalSpinLock = &g_SpinLockIsr_MsgQueue;
            break;

        case G_SPINLOCKISR_IMAGE2D:
            pOsalSpinLock = &g_SpinLockIsr_Image2D;
            break;

        case G_FRAMEBUF:
            pOsalSpinLock = &g_FrameBuf_SpinLock;

        default:
            break;
    }

    return pOsalSpinLock;
}

VOID Osal_SpinLockInit(SpinLockType spinLockType)
{
    OSAL_IRQ_SPIN_LOCK *pOsalSpinLock = NULL;

    pOsalSpinLock = GetSpinLockByEnum(spinLockType);

    OSAL_SpinLockIRQInit(pOsalSpinLock);
}

SINT32 Osal_SpinLock(SpinLockType spinLockType)
{
    OSAL_IRQ_SPIN_LOCK *pOsalSpinLock = NULL;

    pOsalSpinLock = GetSpinLockByEnum(spinLockType);

    return OSAL_SpinLockIRQ(pOsalSpinLock);
}


SINT32 Osal_SpinUnLock(SpinLockType spinLockType)
{
    OSAL_IRQ_SPIN_LOCK *pOsalSpinLock = NULL;

    pOsalSpinLock = GetSpinLockByEnum(spinLockType);

    return OSAL_SpinUnLockIRQ(pOsalSpinLock);
}

SINT32 Osal_InitWaitQue(MutexType mutextType, SINT32 initVal)
{
    SINT32 retVal = OSAL_ERR;

    switch (mutextType)
    {
        case G_INTEVENT:
            retVal = OSAL_InitEvent(&g_IntEvent, initVal);
            break;

        default:
            break;
    }

    return retVal;
}

SINT32 Osal_WakeupWaitQue(MutexType mutexType)
{
    SINT32 retVal = OSAL_ERR;

    switch (mutexType)
    {
        case G_INTEVENT:
            retVal = OSAL_GiveEvent(&g_IntEvent);
            break;

        default:
            break;
    }

    return retVal;
}

SINT32 Osal_WaitWaitQue(MutexType mutexType, SINT32 waitTimeInMs)
{
    SINT32 retVal = OSAL_ERR;

    switch (mutexType)
    {
        case G_INTEVENT:
            retVal = OSAL_WaitEvent(&g_IntEvent, waitTimeInMs);
            break;
        default:
            break;
    }

    return retVal;
}

UINT32 strlcpy_command_line(char *dest, UINT32 size)
{
    OSAL_ASSERT_RET(dest != NULL, OSAL_ERR);

    return strlcpy(dest, saved_command_line, size);
}

VOID Osal_isb(VOID)
{
    isb();
}

VOID Osal_mb(VOID)
{
    mb();
}

VOID Osal_udelay(unsigned long usecs)
{
    udelay(usecs);
}

VOID InitVfmwInterface(VOID)
{
    vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInMs = OSAL_GetTimeInMs;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_GetTimeInUs = OSAL_GetTimeInUs;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLockInit = Osal_SpinLockInit;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinLock     = Osal_SpinLock;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SpinUnlock   = Osal_SpinUnLock;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaInit = OSAL_SEMA_INTIT;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaDown = OSAL_DOWN_INTERRUPTIBLE;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_SemaUp   = OSAL_UP;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_FileOpen  = (FN_OSAL_FileOpen)klib_fopen;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_FileClose = (FN_OSAL_FileClose)klib_fclose;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_FileRead  = (FN_OSAL_FileRead)klib_fread;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_FileWrite = (FN_OSAL_FileWrite)klib_fwrite;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemSet = (FN_OSAL_MemSet)memset;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemCpy = (FN_OSAL_MemCpy)memcpy;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemMov = (FN_OSAL_MemMov)memmove;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MemCmp = (FN_OSAL_MemCmp)memcmp;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_printk = printk;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_dprint = dprint_vfmw;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_snprintf = (FN_OSAL_snprintf)snprintf;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_sscanf   = sscanf;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_strncmp  = strncmp;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_strlcpy_command_line = strlcpy_command_line;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_strlcpy       = strlcpy;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_strsep        = (FN_OSAL_strsep)strsep;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_simple_strtol = simple_strtol;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_strstr        = (FN_OSAL_strstr)strstr;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_msleep = msleep;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_isb    = Osal_isb;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_mb     = Osal_mb;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_udelay = Osal_udelay;


    vfmw_Osal_Func_Ptr_S.pfun_Osal_InitEvent = Osal_InitWaitQue;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_GiveEvent = Osal_WakeupWaitQue;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_WaitEvent = Osal_WaitWaitQue;

#if 0
    vfmw_Osal_Func_Ptr_S.pfun_Osal_RWLockInit  = Osal_RWLockInit;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_ReadLock    = Osal_ReadLock;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_ReadUnLock  = Osal_ReadUnLock;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_WriteLock   = Osal_WriteLock;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_WriteUnLock = Osal_WriteUnLock;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_MsgQue_InitMsgQue    = MSGQUE_InitQueue;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MsgQue_GetMsg        = MSGQUE_GetMsg;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MsgQue_UpdateReadPtr = MSGQUE_UpdateRH;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MsgQue_GetNodeNum    = MSGQUE_GetNodeNum;
    vfmw_Osal_Func_Ptr_S.Pfun_Osal_MsgQue_Control       = MSGQUE_Control;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_MsgQue_DeinitMsgQue  = MSGQUE_DeinitQueue;
#endif

    vfmw_Osal_Func_Ptr_S.pfun_Osal_FlushCache       = klib_flush_cache;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelFlushCache = KernelFlushCache;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMemAlloc = KernelMemMalloc;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMemFree  = KernelMemFree;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelRegisterMap   = KernelRegisterMap;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelRegisterUnMap = KernelRegisterUnMap;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmap      = KernelMmap;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMunMap    = KernelMunmap;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_KernelMmapCache = KernelMmapCache;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_CreateTask = (FN_OSAL_CreateTask)OSAL_CreateTask;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_phys_to_virt = phys_to_virt;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_AllocVirMem = OSAL_AllocVirMem;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_FreeVirMem  = OSAL_FreeVirMem;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_request_irq = (FN_OSAL_request_irq)osal_request_irq;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_free_irq    = osal_free_irq;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_init = vfmw_proc_init;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_vfmw_proc_exit = (FN_OSAL_vfmw_proc_exit)vfmw_proc_exit;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_vdec_init      = VDEC_Init;
    vfmw_Osal_Func_Ptr_S.pfun_Osal_vdec_exit      = VDEC_Exit;

    vfmw_Osal_Func_Ptr_S.pfun_Osal_vdec_control   = VDEC_Control;
}

