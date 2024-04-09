#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <asm/uaccess.h>
#include <linux/seq_file.h>
#include <linux/namei.h>
#include <linux/stat.h>
#include <linux/version.h>

#include "hi_type.h"
#include "hi_osal.h"
#include "hi_drv_sys.h"
#include "hi_drv_log.h"
#include "hi_drv_file.h"
#include "drv_log.h"

#if (LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0))
#define PARENT_DIR_INODE_LOCK(d_inode) mutex_lock(&(d_inode)->i_mutex)
#define PARENT_DIR_INODE_UNLOCK(d_inode) mutex_unlock(&(d_inode)->i_mutex)
//#define PARENT_DIR_INODE_LOCK() mutex_lock(&path.dentry->d_parent->d_inode->i_mutex)
//#define PARENT_DIR_INODE_UNLOCK() mutex_lock(&path.dentry->d_parent->d_inode->i_mutex)
#else
#define PARENT_DIR_INODE_LOCK(d_inode) down_write_trylock(&(d_inode)->i_rwsem)
#define PARENT_DIR_INODE_UNLOCK(d_inode) up_write(&(d_inode)->i_rwsem)
#endif

struct file* HI_DRV_FILE_Open(const HI_S8* ps8FileName, HI_S32 s32Flags)
{
    struct file *pFile = NULL;

    if (NULL == ps8FileName)
    {
        return NULL;
    }

    if (s32Flags == 0)
    {
        s32Flags = O_RDONLY;
    }
    else
    {
        s32Flags = O_WRONLY | O_CREAT | O_APPEND;
    }

    pFile = filp_open(ps8FileName, s32Flags | O_LARGEFILE, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    return (IS_ERR(pFile)) ? NULL : pFile;
}

HI_VOID HI_DRV_FILE_Close(struct file * pFile)
{
    if ( NULL != pFile )
    {
        filp_close(pFile, NULL);
    }

    return;
}

HI_S32 HI_DRV_FILE_Read(struct file * pFile,  HI_U8* ps8Buf, HI_U32 u32Len)
{
    HI_S32 s32ReadLen = 0;
    mm_segment_t stOld_FS = {0};

    if (pFile == NULL || NULL == ps8Buf)
    {
        return -ENOENT; /* No such file or directory */
    }

    if (((pFile->f_flags & O_ACCMODE) & (O_RDONLY | O_RDWR)) != 0)
    {
        return -EACCES; /* Permission denied */
    }

    /* saved the original file space */
    stOld_FS = get_fs();

    /* extend to the kernel data space */
    set_fs(KERNEL_DS);

    s32ReadLen = vfs_read(pFile, ps8Buf, u32Len, &pFile->f_pos);

    /* Restore the original file space */
    set_fs(stOld_FS);

    return s32ReadLen;
}
HI_S32 HI_DRV_FILE_Write(struct file* pFile, HI_S8* ps8Buf, HI_U32 u32Len)
{
    HI_S32 s32WriteLen = 0;
    mm_segment_t stOld_FS = {0};

    if (pFile == NULL || ps8Buf == NULL)
    {
        return -ENOENT; /* No such file or directory */
    }

    if (((pFile->f_flags & O_ACCMODE) & (O_WRONLY | O_RDWR)) == 0)
    {
        return -EACCES; /* Permission denied */
    }

    stOld_FS = get_fs();
    set_fs(KERNEL_DS);

    s32WriteLen = vfs_write(pFile, ps8Buf, u32Len, &pFile->f_pos);

    set_fs(stOld_FS);

    return s32WriteLen;
}

HI_S32 HI_DRV_FILE_Stat(const HI_S8* ps8FileName, struct kfilestat *pstStat)
{
    HI_S32 s32Ret = HI_FAILURE;
    struct kstat stKstat;
    mm_segment_t stOld_FS = {0};

    if (HI_NULL == ps8FileName || HI_NULL == pstStat) {
        return -ENOENT; /* No such file or directory */
    }

    stOld_FS = get_fs();
    set_fs(KERNEL_DS);
    s32Ret = vfs_stat(ps8FileName, &stKstat);
    set_fs(stOld_FS);

    if (HI_SUCCESS != s32Ret) {
        HI_ERR_SYS("vfs_stat failed, s32Ret[0x%x\n]\n", s32Ret);
        return s32Ret;
    }

    pstStat->size    = stKstat.size;
    pstStat->blksize = stKstat.blksize;
    pstStat->blocks  = stKstat.blocks;

    return s32Ret;
}

#if 1 /* general solution */
HI_S32 HI_DRV_FILE_Remove(const HI_S8 *ps8FileName)
{
    int error = 0;

    struct dentry *dentry = HI_NULL;
    struct inode *pinode = HI_NULL;
    struct path path = {0};
    struct inode *delegated_inode = HI_NULL;

    if (HI_NULL == ps8FileName) {
        return -ENOENT; /* No such file or directory */
    }

    /* find the parent dentry of the file */
    /* if the file path is "/mnt/stb.log00000000" linux3.18 kernel LOOKUP_PARENT will get path.dentry->d_name.name as "mnt", but linux4.4&4.9 as "stb.log00000000" , so here use LOOKUP_FOLLOW in general */
    error = kern_path(ps8FileName, LOOKUP_FOLLOW, &path);
    if (error || (HI_NULL == path.dentry)) {
        HI_ERR_SYS("kern_path error = %d, path.dentry is 0x%x\n", error, path.dentry);
        return error;
    }

    pinode = path.dentry->d_parent->d_inode;
    if (!pinode) {
        HI_ERR_SYS("parent dir inode is NULL\n");
        path_put(&path);
        return -EINVAL;
    }

    /* find the file dentry in parent dentry */
    PARENT_DIR_INODE_LOCK(pinode);
    dentry = lookup_one_len(path.dentry->d_name.name, path.dentry->d_parent, strlen(path.dentry->d_name.name));
    if (!dentry) {
        PARENT_DIR_INODE_UNLOCK(pinode);
        HI_ERR_SYS("lookup_one_len error = %d\n", -EINVAL);
        path_put(&path);
        return -EINVAL;
    }

    /* delete the file dentry from the parent dentry */
    error = vfs_unlink(pinode, dentry, &delegated_inode);
    if (error) {
        PARENT_DIR_INODE_UNLOCK(pinode);
        HI_ERR_SYS("vfs_unlink error = %d\n", error);
        path_put(&path);
        return error;
    }

    dput(dentry);
    PARENT_DIR_INODE_UNLOCK(pinode);
    path_put(&path);

    return HI_SUCCESS;
}
#else /* special solution for linux, android selinux forbid kernel exec shell to operate file */
HI_S32 HI_DRV_FILE_Remove(const HI_S8 *ps8FileName)
{
    HI_S8 szCurFileName[256] = {0};

#ifdef HI_COMMON_ANDROID_SUPPORT
    char *argv[4] = {"system/bin/sh", "-c", szCurFileName, NULL};
    char *envp[4] = {"HOME=/",
                    "TERM=linux",
                    "PATH=/sbin:system/bin:", NULL};
#else
    char *argv[4] = {"bin/sh", "-c", szCurFileName, NULL};
    char *envp[4] = {"HOME=/",
                    "TERM=linux",
                    "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL};
#endif
    if (HI_NULL == ps8FileName) {
        return -ENOENT; /* No such file or directory */
    }

    HI_OSAL_Snprintf(szCurFileName, sizeof(szCurFileName)-1, "%s %s", "rm -rf", ps8FileName);

    return call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
}
#endif

HI_S32 HI_DRV_FILE_Lseek(struct file *pFile, HI_S32 s32Offset, HI_S32 s32Whence)
{
    HI_S32 s32Ret;

    loff_t res = vfs_llseek(pFile, s32Offset, s32Whence);
    s32Ret = res;
    if (res != (loff_t)s32Ret)
        s32Ret = -EOVERFLOW;

    return s32Ret;
}

HI_S32 HI_DRV_FILE_GetStorePath(HI_S8* ps8Buf, HI_U32 u32Len)
{
    if (ps8Buf == NULL || u32Len == 0)
    {
        return HI_FAILURE;
    }

    memset(ps8Buf, 0, u32Len);

    return HI_DRV_LOG_GetStorePath(ps8Buf, u32Len);
}

EXPORT_SYMBOL(HI_DRV_FILE_Open);
EXPORT_SYMBOL(HI_DRV_FILE_Close);
EXPORT_SYMBOL(HI_DRV_FILE_Read);
EXPORT_SYMBOL(HI_DRV_FILE_Write);
EXPORT_SYMBOL(HI_DRV_FILE_Stat);
EXPORT_SYMBOL(HI_DRV_FILE_Remove);
EXPORT_SYMBOL(HI_DRV_FILE_Lseek);
EXPORT_SYMBOL(HI_DRV_FILE_GetStorePath);

