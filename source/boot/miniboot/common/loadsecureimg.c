/******************************************************************************
 *    Secure OS loading module
 *    Copyright (c) 2013-2023 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By LYJ.
 *
******************************************************************************/
#include <config.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <mmu.h>
#include <asm/io.h>

#define TRUSTEDCORE_HEADER_SIZE 0x800

extern void  execute_init_secure_kernel(uint32 addr, int run);

struct secure_img_header_t {
	u32 header_size;      //Header size
	u32 kernel_load_addr; //RTOSCK load address
	u32 kernel_size;      //RTOSCK size
	u32 task_num;         //TASK_NUM
	u32 task_total_size;
	u32 got_size;
};

struct img_symbol_header_t{
    u32 offset;         //symtab offset
    u32 symtab_size;    //symtab size
    u32 strtab_size;    //strtab size
    u32 bss_size;       //bss size
};

struct TASK_UUID{
    u32 time_Low;
    u16 time_Mid;
    u16 timeHiAndVersion;
    u8 clockSeqAndNode[8];
};

struct secure_img_task_header_t{
    u32 img_addr;         //task img addr
    u32 img_size;
    u32 task_size;        //task runtime allocate size
    char task_name[20];
    struct TASK_UUID task_uuid;
};



u32 secure_entry_addr = 0;
/*************************************************************
* Description:Start Secure OS
* param kloadaddr - Secure OS entry address
* return
**************************************************************/
void boot_secure_kernel(u32 kloadaddr)
{
	printf("Loading Secure OS ...\n");
	mmu_cache_disable();
	void (*secure_entry)(void) = (void(*)(void))(kloadaddr);
	secure_entry();
	printf("Back to boot\n");
}

void copy_secure_kernel_and_internal_task(struct secure_img_header_t* imgheader)
{
	char *dst_ptr = (char *)(imgheader->kernel_load_addr);
	char *src_ptr = (char *)((char *)imgheader + imgheader->header_size);

	struct img_symbol_header_t* k_symbolHeader = (struct img_symbol_header_t*)((char *)imgheader +
							sizeof(struct secure_img_header_t) +
							sizeof(struct secure_img_task_header_t)*imgheader->task_num +
							sizeof(struct img_symbol_header_t));

	mmu_cache_enable();

	/* Copy secure os image to executed address */
	printf("   Move SecureOS kernel from 0x%X to 0x%X, %uKB\n",
		(u32)src_ptr, (u32)dst_ptr, imgheader->kernel_size / 1024);
	memmove(dst_ptr, src_ptr, imgheader->kernel_size);

	/* Move systab and strtab behind internal tasks */
	dst_ptr = (char *)((char *)imgheader + imgheader->header_size + imgheader->kernel_size + imgheader->task_total_size);
	src_ptr = (char *)((char *)imgheader + imgheader->header_size + k_symbolHeader->offset);
	printf("   Move systab and strtab from 0x%X to 0x%X, %u KB\n",
		(u32)src_ptr, (u32)dst_ptr, (k_symbolHeader->symtab_size + k_symbolHeader->strtab_size) / 1024);
	memmove(dst_ptr, src_ptr, k_symbolHeader->symtab_size + k_symbolHeader->strtab_size);

	/* Move internal tasks to their loacation, remove kernel */
	dst_ptr = (char *)((char *)imgheader + imgheader->header_size);
	src_ptr = (char *)((char *)imgheader + imgheader->header_size + imgheader->kernel_size);

	printf("   Move TAs from 0x%X to 0x%X, %uKB\n",
		(u32)src_ptr, (u32)dst_ptr, imgheader->task_total_size / 1024);
	memmove(dst_ptr, src_ptr, imgheader->task_total_size);

        mmu_cache_disable();
}

/*************************************************************
* Description:execute secure os
* param addr -- Secure OS image address
* return
**************************************************************/
void  execute_init_secure_kernel(uint32 addr, int run)
{
	struct secure_img_header_t* imgheader;

	imgheader = (struct secure_img_header_t*)addr;

	printf("## Secure OS Image:\n");
	printf("   Header Size: 0x%X (%u KB)\n", imgheader->header_size, imgheader->header_size / 1024);
	printf("   Kernel Load Addresss: 0x%X\n", imgheader->kernel_load_addr);
	printf("   Kernel Size: 0x%x (%u KB)\n", imgheader->kernel_size, imgheader->kernel_size / 1024);
	printf("   Task Number: %d\n", imgheader->task_num);
	printf("   Task Total Size: 0x%X (%u KB)\n", imgheader->task_total_size, imgheader->task_total_size / 1024);

	copy_secure_kernel_and_internal_task(imgheader);
	if (run)
		boot_secure_kernel(imgheader->kernel_load_addr);
	else
		secure_entry_addr = imgheader->kernel_load_addr;

}
#ifndef CONFIG_ASC_SUPPORT
extern char _slave_cpu_startup[];
extern char _slave_cpu_end[];
#define TZMA_ROSIZE_REG                          0xf8a80000
void prepare_slave_cpu_bootcode(void)
{
	char *src = _slave_cpu_startup;
	char *dst = (char *)(0xFFFF0000);
	int length = 4096; /* reserve 4K for slave cpu bootup */

	if ((_slave_cpu_end - _slave_cpu_startup) > length) {
		printf("Error: Slave cpu bootcode over size 0x%x Byte.\n", length);
		return;
	}

	printf("Copy slave cpu bootcode from 0x%p to 0x%p, %d Bytes\n", src, dst, length);
	memcpy(dst, src, length);

	/* Lock 4K SRAM for TEE, 4K for canalplus */
	writel(2, TZMA_ROSIZE_REG);
}
#endif

int is_trustedcore_img(char *buf)
{
	struct secure_img_header_t *hdr = (struct secure_img_header_t *)buf;
	if (TRUSTEDCORE_HEADER_SIZE == hdr->header_size)
		return 1;

	return 0;
}
int is_atf_trustedcore_img(char *buf)
{
#ifdef CONFIG_ASC_SUPPORT
	struct secure_img_header_t *hdr = (struct secure_img_header_t *)(buf + CONFIG_BL31_SIZE);
	if (TRUSTEDCORE_HEADER_SIZE == hdr->header_size)
		return 1;
#endif
	return 0;
}
#ifdef CONFIG_ASC_SUPPORT
int do_load_secure_os(unsigned long addr, unsigned long org_offset, unsigned long img_dst, int run, uint32_t *rtos_load_addr)
{
	secure_entry_addr = addr;
	return 0;
}
#else
int do_load_secure_os(unsigned long addr, unsigned long org_offset, unsigned long img_dst, int run, uint32_t *rtos_load_addr)
{
	int      rc = 0;
	struct secure_img_header_t *hdr = (struct secure_img_header_t *)(addr + org_offset);
	u32 rtos_addr = hdr->kernel_load_addr;
	u32 img_start = 0;

	unsigned int img_size = hdr->header_size + hdr->kernel_size + hdr->task_total_size;
	if (img_dst) {
		img_start = img_dst;
	} else {
		img_start = addr;
	}

	prepare_slave_cpu_bootcode();
	printf ("## Starting Secure OS at 0x%08X ...\n", img_start);

	execute_init_secure_kernel(img_start, run);
	printf ("## Succeed to load SecureOS\n");
	if (rtos_load_addr)
		*rtos_load_addr = (uint32_t)rtos_addr;
	return rc;
}
#endif
