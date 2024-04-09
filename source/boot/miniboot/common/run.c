/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Czyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/
#include <asm/io.h>
#include <compile.h>
#include <stdio.h>
#include <string.h>
#include <run.h>
#include <env_set.h>
#include <module.h>
#include <mmu.h>
#include <cache.h>
#include <crc32.h>
#include <irq.h>
#include <board.h>
#include <bootimg.h>
#include <malloc.h>
#include <boot.h>
#include <libfdt.h>
#include <asc.h>
#include <atf.h>
#include "mailbox.h"
#include "image.h"


#ifdef CONFIG_ARM64_SUPPORT
extern int is_fip(char *buf);
extern int load_fip(char *buf);
#endif

extern u32 secure_entry_addr;

/******************************************************************************/

static int check_image(const char *addr, kernel_fn *kernel)
{
	uint32 tmp;
	const char *data;
	struct img_hdr_t hdr;

	memcpy(&hdr, addr, sizeof(struct img_hdr_t));

	if (SWAP32(hdr.magic) != UIMG_MAGIC) {
		printf("The image format invalid.\n");
		return -1;
	}

	hdr.hcrc = 0;
	tmp = crc32(0, &hdr, sizeof(struct img_hdr_t));
	if (SWAP32(((struct img_hdr_t *)addr)->hcrc) != tmp) {
		printf("The image head crc32 check fail.\n");
		return -1;
	}

	hdr.name[sizeof(hdr.name)-1] = '\0';
	hdr.entry = SWAP32(hdr.entry);
	hdr.size = SWAP32(hdr.size);
	hdr.load = SWAP32(hdr.load);
	hdr.dcrc = SWAP32(hdr.dcrc);

	printf("Kernel Name:   %s\n", hdr.name);
	printf("Kernel Size:   %d\n", hdr.size);
	printf("Load Address:  0x%08X\n", hdr.load);
	printf("Entry Address: 0x%08X\n", hdr.entry);

	data = addr + sizeof(struct img_hdr_t);

#ifdef CONFIG_VERIFY_KERNEL
	printf("Verifying CRC ... ");
	tmp = crc32(0, data, hdr.size);
	if (tmp != hdr.dcrc) {
		printf("Fail\n");
		return -1;
	}
	printf("OK\n");
#endif /* CONFIG_VERIFY_KERNEL */

	if ((uint32)data != hdr.load) {
		printf("Loading Kernel Image ... ");
		memcpy((char *)hdr.load, data, hdr.size);
		printf("OK\n");
	}

	if (kernel)
		*kernel = (kernel_fn)hdr.entry;

	return 0;
}
/******************************************************************************/
#if defined(CONFIG_TEE_SUPPORT) && defined(CONFIG_ASC_SUPPORT)
extern int exec_smc(unsigned int arg0, unsigned int arg1, unsigned int arg2, unsigned int arg3);

void start_tee(uint32_t arch, uint32_t entry, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{

	if (SCPU_NOT_SUPPORT != (readl(REG_SCPU_SUPPORT) & SCPU_SUPPORT_MASK))  {
		u32 command = MBX_TYPE_SOS_PROCESS;

		writel((u32)entry, REG_BASE_SCTL + REG_SC_GEN1);

		printf("Send start TEE command to SCPU...");
		if (0 == mailbox_set(&command, NULL, 0, 0)) {
			while (1) {
				__asm__ __volatile__("wfi");
			}
		}
	} else {
		asc_params_t *asc_p = malloc(sizeof(asc_params_t));
		if (!asc_p) {
			printf("Failt to alloc asc params buffer!\n");
			goto error;
		}

		memset(asc_p, 0, sizeof(asc_params_t));
		if (BL33_IMG_ARM64 == arch) {
			asc_p->arg0 = BL33_IMG_ARM64;
			asc_p->arg1 = (uint32_t)entry;
			printf("Start TEE with aarch64 kernel...\n");
			exec_smc(CMD_LOAD_SOS, (u32)asc_p, 0, 0);
		} else {
			asc_p->arg0 = BL33_IMG_ARM32;
			asc_p->arg1 = (u32)entry;
			asc_p->arg2 = (u32)arg0;
			printf("Start TEE with aarch32 kernel...\n");
			exec_smc(CMD_LOAD_SOS, (u32)asc_p, 0, 0);
		}
	}
error:
	printf(" Failed, reset cpu......\n");
	reset_cpu(0);
	reset_cpu(0);
}
#endif

#if defined(CONFIG_TEE_SUPPORT) && defined(CONFIG_TEE_ATF_SUPPORT)
void start_tee_atf(uint32_t arch, char *buf, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
	int ret = 0;
	entry_point_info_t bl32_ep;
	entry_point_info_t bl33_ep;
	bl31_params_t bl31_p;
	uint32_t bl31_pc = 0;
	char *bl31_img_buf = NULL;
	u32 val = 0;
	image_header_t *hdr = (image_header_t *)buf;

	memset(&bl31_p, 0, sizeof(bl31_params_t));
	memset(&bl32_ep, 0, sizeof(entry_point_info_t));
	memset(&bl33_ep, 0, sizeof(entry_point_info_t));
	bl31_p.bl32_ep_info = (uint64_t)((uint32_t)&bl32_ep);
	bl31_p.bl33_ep_info = (uint64_t)((uint32_t)&bl33_ep);

	if(arch == BL33_IMG_ARM64) {
		char *fdt = (char *)get_image_end(hdr);
		ret = fdt_check_header(fdt);
		if (ret) {
			printf("Invalid FDT at 0x%p, hdr at 0x%p\n", fdt, hdr);
			goto error;
		}
		bl33_ep.pc = (uint64_t)get_image_data(hdr);
		bl33_ep.args.arg0 = (uint64_t)((uint32_t)fdt);
		bl33_ep.args.arg1 = (uint64_t)(get_image_ep(hdr));
		bl33_ep.args.arg2 = (uint64_t)(get_image_size(hdr));
		bl33_ep.args.arg3 = CONFIG_TAG_OFFSET;
		bl33_ep.args.arg4 = CONFIG_TAG_OFFSET + CONFIG_TAG_MAX_SIZE;
		bl33_ep.args.arg5 = (uint64_t)(CONFIG_DTB_MAX_SIZE);
		bl33_ep.spsr = SPSR_64(MODE_EL1,MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
	} else if (arch == BL33_IMG_ARM32){
		bl33_ep.pc = (uint64_t)get_image_data(hdr);
		bl33_ep.args.arg1 = (uint64_t)(get_image_ep(hdr));
		bl33_ep.args.arg2 = (uint64_t)(get_image_size(hdr));
		bl33_ep.args.arg3 = CONFIG_TAG_OFFSET;
		bl33_ep.args.arg4 = CONFIG_TAG_OFFSET + CONFIG_TAG_MAX_SIZE;
		bl33_ep.args.arg5 = (uint64_t)(CONFIG_DTB_MAX_SIZE);
		bl33_ep.spsr = SPSR_MODE32(MODE32_svc, 0x0 , EP_EE_LITTLE, DISABLE_ALL_EXCEPTIONS);
	}

	printf("bl33_ep->spsr = 0x%X\n", bl33_ep.spsr);

	bl31_pc = CONFIG_BL31_BASE;

#ifdef CONFIG_NET
	extern void setup_eth_param(void);
	setup_eth_param();
#endif

	if(is_tee_type()) {
		extern u32 secure_entry_addr;
		extern u32 _text_end;
		if (secure_entry_addr) {
			unsigned int text_end = roundup(_text_end, 0x10); /* align for secure os clean boot */
			bl32_ep.pc = (uint64_t)secure_entry_addr;
			SET_SECURITY_STATE(bl32_ep.h.attr,
					 SECURE);
			bl32_ep.spsr = 0;
			bl32_ep.args.arg0 = TEXT_BASE;
			bl32_ep.args.arg1 = text_end;
		}
	}

#if defined(CONFIG_HI3798MV2X_FPGA) || defined(CONFIG_HI3796MV2X_FPGA)
	writel(bl31_pc >> 2, REG_PERI_CPU_RVBARADDR);
#else
	writel(bl31_pc, REG_PERI_CPU_RVBARADDR);
#endif
	writel(readl(REG_PERI_CPU_AARCH_MODE) | 0xF,REG_PERI_CPU_AARCH_MODE);

	(*(volatile uint64_t *)0) = (uint64_t)((uint32_t)&bl31_p);
	(*(volatile uint64_t *)8) = (uint64_t)((uint32_t)NULL);

	printf("Start Warm Reseting\n");

	module_exit();
	cpu_disable_irq();

	mmu_cache_disable();
	cache_flush_all();

	/* warm reseting */
	__asm__ __volatile__("isb\n\r"
		"dsb\n\r"
		"mrc p15, 0, %0, c12, c0, 2\n\r"
		"orr %0, %0, #0x3\n\r"
		"mcr p15, 0, %0, c12, c0, 2\n\r"
		"isb\n\r"
		"wfi":"=r"(val)::"cc");
	printf("Fail to warm resetting...\n");
	while (1)
		;

error:
	return 0;
}
#endif

int kern_load(const char *addr)
{
	int ret;
	uint32 params;
	char *buf = (char *)addr;
	unsigned int kernel_buf = (unsigned int)buf;
	kernel_fn kernel = NULL;
#ifdef CONFIG_TEE_SUPPORT
#ifdef CONFIG_ASC_SUPPORT
    char	*s;
    int notee = 0;
#endif
#endif

#ifdef CONFIG_TEE_SUPPORT
	if(is_tee_type()) {
		/* Load Trustedcore OS */
		if (is_trustedcore_img(buf) || is_atf_trustedcore_img(buf)) {
#ifdef CONFIG_TEE_ATF_SUPPORT
			uint32_t bl31_pc = 0;
			char *bl31_img_buf = NULL;

			bl31_pc = CONFIG_BL31_BASE;
			bl31_img_buf = buf-HI_TEE_ATF_SIZE;
			printf("Move bl31 img from 0x%X to 0x%X, 0x%X Bytes\n", bl31_img_buf, bl31_pc,HI_TEE_ATF_SIZE);
			memmove((void *)bl31_pc, bl31_img_buf, HI_TEE_ATF_SIZE);
			memset(bl31_img_buf,0x0,HI_TEE_ATF_SIZE);
#endif
			return do_load_secure_os((u32)buf, 0, 0, 0, NULL);
		}
#ifdef CONFIG_SUPPORT_CA_RELEASE
		else if (!memcmp((char *)buf, HI_ADVCA_MAGIC, HI_ADVCA_MAGIC_SIZE) && is_trustedcore_img(buf + HI_ADVCA_HEADER_SIZE)) {
			printf("Boot Hisilicon ADVCA SecureOS Image ...\n");
			return do_load_secure_os((u32)buf, HI_ADVCA_HEADER_SIZE, 0, 0, NULL);
		}
#endif
	}
#endif

#ifdef CONFIG_SUPPORT_CA
	printf("Check Hisilicon_ADVCA ...\n");
	if (memcmp((char *)buf, HI_ADVCA_MAGIC, HI_ADVCA_MAGIC_SIZE)) {
		printf("Not hisilicon ADVCA image ...\n");
	} else {
		printf("Boot hisilicon ADVCA image ...\n");
		buf += HI_ADVCA_HEADER_SIZE;
	}
#endif

	if (!check_bootimg((char *)buf, MAX_BOOTIMG_LEN)) {
		char *bootargs;
		unsigned int initrd_start;
		unsigned int initrd_size;
		if (bootimg_get_kernel(buf, MAX_BOOTIMG_LEN, (unsigned int*)&kernel_buf)) {
			printf("Wrong Image Format. \n");
			return 1;
		}

		if (!bootimg_get_ramfs(buf, MAX_BOOTIMG_LEN, &initrd_start, &initrd_size)) {
			bootargs = env_get("bootargs");
			if (bootargs) {
				int sz_str = strlen(bootargs) + 0x40;
				char *str = malloc(sz_str);
				if (!str) {
					printf("malloc failed.\n");
					return 1;
				}
				memset(str, 0, sz_str);
				snprintf(str, sz_str - 1,
					 "%s initrd=0x%X,0x%X", bootargs,
					 initrd_start, initrd_size);

				env_set("bootargs", str);

				free(str);

				show_bootimg_header(buf);
			}
		}
	}

#ifdef CONFIG_ARM64_SUPPORT
	if (is_fip((char *)kernel_buf)) {
		return load_fip((char *)kernel_buf);
	}
#endif

	ret = check_image((char *)kernel_buf, &kernel);
	if (ret)
		return ret;

	module_exit();
	cpu_disable_irq();

	printf ("Starting kernel ...\n\n");

#ifdef CONFIG_NET
	setup_eth_param();
#endif

	params = get_kern_tags((uint32)kernel);

	mmu_cache_disable();
	cache_flush_all();

#ifdef CONFIG_TEE_SUPPORT
	if(is_tee_type()) {
#ifdef CONFIG_ASC_SUPPORT
		extern char *getenv (const char *key);
		s = getenv ("notee");
		if (s) {
			notee = (*s == 'y') ? 1 : 0;
		}

		if (!notee) {
			if (0 == check_image_arch ((image_header_t *)kernel_buf, IH_ARCH_ARM64)) {
				image_header_t *hdr = (image_header_t *)kernel_buf;
				char *fdt = (char *)get_image_end((image_header_t *)kernel_buf);

				if (fdt_check_header(fdt)) {
					printf("Invalid FDT at 0x%p, hdr at 0x%p  error=%d-->run.c\n", fdt, hdr,fdt_check_header(fdt));
					return 1;
				}

				entry_point_info_t *bl33_ep_info = malloc(sizeof(entry_point_info_t));
				if (!bl33_ep_info) {
					printf("Fail to alloc bl31 params buffer!\n");
					return 1;
				}
				memset(bl33_ep_info, 0, sizeof(entry_point_info_t));
				bl33_ep_info->pc = (uint64_t)get_image_data(hdr);
				bl33_ep_info->args.arg0 = (uint64_t)((uint32_t)fdt);
				bl33_ep_info->args.arg1 = (uint64_t)(get_image_ep(hdr));
				bl33_ep_info->args.arg2 = (uint64_t)(get_image_size(hdr));
				bl33_ep_info->args.arg3 = CONFIG_TAG_OFFSET;
				bl33_ep_info->args.arg4 = CONFIG_TAG_OFFSET + CONFIG_TAG_MAX_SIZE;
				bl33_ep_info->args.arg5 = (uint64_t)(CONFIG_DTB_MAX_SIZE);
				bl33_ep_info->spsr = SPSR_64(MODE_EL1, MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
				start_tee(BL33_IMG_ARM64, (u32)bl33_ep_info, 0, 0, 0, 0);
			} else {
				start_tee(BL33_IMG_ARM32, (u32)kernel, params, 0, 0, 0);
			}
		}
#else
#ifdef CONFIG_TEE_ATF_SUPPORT
		if (0 == check_image_arch ((image_header_t *)(kernel_buf), IH_ARCH_ARM)) {
			printf("Start TEE with aarch32 kernel...\n");
			start_tee_atf(BL33_IMG_ARM32, (char *)kernel_buf, 0, 0, 0, 0);
		}
		else if (0 == check_image_arch ((image_header_t *)(kernel_buf), IH_ARCH_ARM64)) {
			printf("Start TEE with aarch64 kernel...\n");
			start_tee_atf(BL33_IMG_ARM64, (char *)kernel_buf, 0, 0, 0, 0);
		}
		else
			printf("ARCH type not support!!!\n");
#else /*CONFIG_TEE_ATF_SUPPORT*/
		if (secure_entry_addr) {
			void (*secure_entry)(int, int, int, int, int, int) = (void(*)(int, int, int, int, int, int))(secure_entry_addr);
			unsigned int text_end = roundup(_text_end, 0x10); /* align for secure os clean boot */
			secure_entry(0, CONFIG_MACHINE_ID, (int)params, (int)kernel, TEXT_BASE, text_end);
		}
#endif /*CONFIG_TEE_ATF_SUPPORT*/
#endif /*CONFIG_ASC_SUPPORT*/
	}
#endif /*CONFIG_TEE_SUPPORT*/
	kernel(0, CONFIG_MACHINE_ID, params);

	return 0;
}

/******************************************************************************/

int image_load(const char *addr, const char *param)
{
	int (*entry)(const char *param) = (int(*)(const char *))addr;

	module_exit();

	cpu_disable_irq();
	mmu_cache_disable();
	cache_flush_all();

	invalidIcache();
	DSB();
	ISB();

	return entry(param);
}
