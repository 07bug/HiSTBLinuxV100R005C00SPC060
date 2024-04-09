#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/mman.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/slab.h>

#define HI_CRG_REG_BASE_ADDR    0xF8A22000
#define HI_REG_MAX_SIZE         0x10000

#define REG_DEV_NAME            "register"

static int register_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int register_close(struct inode *inode, struct file *file)
{
	return 0;
}

static int valid_reg_range(unsigned long start, unsigned long end)
{
	if (end < start)
		return 0;

	if ((start < HI_CRG_REG_BASE_ADDR) || (end >= (HI_CRG_REG_BASE_ADDR + HI_REG_MAX_SIZE)))
		return 0;

	return 1;
}

static int register_mmap(struct file *file, struct vm_area_struct *vma)
{
	size_t size = vma->vm_end - vma->vm_start;

	vma->vm_page_prot = phys_mem_access_prot(file, vma->vm_pgoff, size, vma->vm_page_prot);

	if (!valid_reg_range((vma->vm_pgoff) << PAGE_SHIFT, ((vma->vm_pgoff) << PAGE_SHIFT) + size)) {
		printk(KERN_INFO "Can not access 0x%lX-0x%lX\n", vma->vm_pgoff << PAGE_SHIFT, (vma->vm_pgoff << PAGE_SHIFT) + size);
		return -EINVAL;
	}

	if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, size, vma->vm_page_prot)) {
		printk(KERN_INFO "remap_pfn_range fail.\n");
		return -EAGAIN;
	}

	return 0;
}

static struct file_operations register_ops =
{
	.open    = register_open,
	.release = register_close,
	.mmap    = register_mmap
};

static struct miscdevice register_device =
{
	MISC_DYNAMIC_MINOR,
	REG_DEV_NAME,
	&register_ops
};

int register_access_init(void)
{
	int ret = 0;

	ret = misc_register(&register_device);
	if (ret) {
		printk(KERN_INFO "Fail to register register device\n");
		return ret;
	}

	return 0;
}

void register_access_exit(void)
{
	misc_deregister(&register_device);
}

module_init(register_access_init);
module_exit(register_access_exit);

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");

