/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * Copyright (C) 2001  Erik Mouw (J.A.K.Mouw@its.tudelft.nl)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307	 USA
 *
 */

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <image.h>
#include <u-boot/zlib.h>
#include <asm/byteorder.h>
#include <asm/sizes.h>
#include <asm/cpu_info.h>
#include <ethcfg.h>
#include <params.h>
#include <asm/io.h>
#include <asc.h>
#include <atf.h>
#include <libfdt.h>
#include "mailbox.h"

DECLARE_GLOBAL_DATA_PTR;

extern int exec_smc(u32 arg0, u32 arg1, u32 arg2, u32 arg3);
extern u32 secure_entry_addr;
extern u32 _text_end;

#if defined(CONFIG_SETUP_MEMORY_TAGS) || \
defined(CONFIG_CMDLINE_TAG) || \
defined(CONFIG_INITRD_TAG) || \
defined(CONFIG_SERIAL_TAG) || \
defined(CONFIG_REVISION_TAG) || \
defined(CONFIG_ETHADDR_TAG) || \
defined(CONFIG_ETHMDIO_INF) || \
defined(CONFIG_NANDID_TAG) || \
defined(CONFIG_SPIID_TAG) || \
defined(CONFIG_SDKVERSION_TAG) || \
defined(CONFIG_BOOTREG_TAG) || \
defined(CONFIG_RSAKEY_TAG)

static void setup_start_tag (bd_t *bd);

# ifdef CONFIG_SETUP_MEMORY_TAGS
static void setup_memory_tags (bd_t *bd);
# endif
static void setup_commandline_tag (bd_t *bd, char *commandline);

# ifdef CONFIG_INITRD_TAG
static void setup_initrd_tag (bd_t *bd, ulong initrd_start,
			      ulong initrd_end);
# endif

static void setup_end_tag (bd_t *bd);

# if defined(CONFIG_ETHMDIO_INF)
static void setup_eth_mdiointf_tag(bd_t *bd, char *mdio_intf);
#endif

# if defined(CONFIG_ETHADDR_TAG)
static void setup_ethaddr_tag(bd_t *bd, char* ethaddr);
static void setup_phyaddr_tag(bd_t *bd,  int phy_addr_up, int phy_addr_down);
#endif

# if defined(CONFIG_PHYINTF_TAG_VAL)
static void setup_phyintf_tag(bd_t *bd);
#endif

# if defined(CONFIG_PHYGPIO_TAG_VAL)
static void setup_phygpio_tag(bd_t *bd);
#endif

# if defined(CONFIG_CHIPTRIM_TAG_VAL)
static void setup_chiptrim_tag(bd_t *bd);
#endif

# if defined(CONFIG_NANDID_TAG)
static void setup_nandid_tag(bd_t *bd);
#endif

# if defined(CONFIG_EMMC_PARAM_TAG)
static void set_emmc_param_tag(bd_t *bd);
#endif

#  if defined(CONFIG_NAND_PARAM_TAG)
static void set_nand_param_tag(bd_t *bd);
#endif

# if defined(CONFIG_SPIID_TAG)
static void setup_spiid_tag(bd_t *bd);
#endif

# if defined(CONFIG_SDKVERSION_TAG)
static void setup_sdkversion_tag(bd_t *bd);
#endif

# if defined(CONFIG_BOOTREG_TAG)
static void setup_bootreg_tag(bd_t *bd);
#endif

#if defined(CONFIG_RSAKEY_TAG)
static void setup_rsakey_param(void);
#endif

static void setup_eth_param(void);
static void setup_param_tag(bd_t *bd);

static struct tag *params;
#endif /* CONFIG_SETUP_MEMORY_TAGS || CONFIG_CMDLINE_TAG || CONFIG_INITRD_TAG */

#if defined(CONFIG_BOOTARGS_MERGE)
extern unsigned long long memparse(const char *ptr, char **retptr);

static void bootargs_adjust_mmz_offset(unsigned int ddrsize, char *name)
{
	int i;
	char *param[4];
	char *args;
	char *mmz_param, *mmz_pos;
	unsigned long long size, offset;
	char tmp_args[100];

	args = getenv(name);
	if (!args) {
		return;
	}

	mmz_pos = mmz_param = strstr(args, "mmz=");
	if (!mmz_param) {
		return;
	}

	memcpy(tmp_args, args, mmz_pos - args);
	mmz_pos = mmz_pos - args + tmp_args;

	/* eg: mmz=ddr,0,0,256M,  0-mmz=ddr, 1-0, 2-0, 3-256M */
	for (i = 0; (param[i] = strsep(&mmz_param, ",")) != NULL;) {
		if (++i == 4)
			break;
	}

	size = memparse(param[3], NULL);

	offset = ((ddrsize/3) * 2) - size;

#define CMA_ALIGN 0x400000 //the CMA pool should aligned to 4M
	if (offset > CMA_ALIGN)
		offset &= ~(CMA_ALIGN - 1);
	else
		offset = CMA_ALIGN;

	snprintf(mmz_pos, 50, "%s,%s,%s,%s", param[0], param[1],
			ultohstr((unsigned long long)offset), param[3]);

	setenv(name, tmp_args);
	return;
}

static char *bootargs_merge(void)
{
	char *args_merge;
	char args_merge_name[32];
	unsigned int ddrsize = get_ddr_size();

	snprintf(args_merge_name, sizeof(args_merge_name), "bootargs_%s",
		 ultohstr((unsigned long long)ddrsize));

	if((ddrsize == (SZ_512M + SZ_256M)) || (ddrsize == (SZ_1G + SZ_512M)))
		bootargs_adjust_mmz_offset(ddrsize, args_merge_name);

	args_merge = getenv(args_merge_name);

	return merge_args(getenv("bootargs"), args_merge, "booargs",
			  args_merge_name);
}
#endif /* CONFIG_BOOTARGS_MERGE */

void setup_boot_atags(ulong rd_start, ulong rd_end)
{
	bd_t	*bd = gd->bd;

#ifdef CONFIG_CMDLINE_TAG
		char *commandline = getenv ("bootargs");
#endif

#if defined (CONFIG_SETUP_MEMORY_TAGS) || \
		    defined (CONFIG_CMDLINE_TAG) || \
		    defined (CONFIG_INITRD_TAG) || \
		    defined (CONFIG_SERIAL_TAG) || \
		    defined (CONFIG_REVISION_TAG) || \
		    defined (CONFIG_BOOTREG_TAG)
			setup_start_tag (bd);
#ifdef CONFIG_SERIAL_TAG
			setup_serial_tag (&params);
#endif
#ifdef CONFIG_REVISION_TAG
			setup_revision_tag (&params);
#endif
#ifdef CONFIG_SETUP_MEMORY_TAGS
			setup_memory_tags (bd);
#endif
#ifdef CONFIG_CMDLINE_TAG
#  ifdef CONFIG_BOOTARGS_MERGE
			commandline = bootargs_merge();
			setup_commandline_tag (bd, commandline);
			if (commandline) {
				free(commandline);
				commandline = NULL;
			}
#  else
			setup_commandline_tag (bd, commandline);
#  endif /* CONFIG_BOOTARGS_MERGE */
#endif
#ifdef CONFIG_INITRD_TAG
			if (rd_start && rd_end)
				setup_initrd_tag (bd, rd_start, rd_end);
#endif
#if defined(CONFIG_ETHMDIO_INF)
			setup_eth_mdiointf_tag(bd, getenv("mdio_intf"));
#endif
#if defined(CONFIG_ETHADDR_TAG)
			setup_ethaddr_tag(bd, getenv("ethaddr"));
			setup_phyaddr_tag(bd, U_PHY_ADDR, D_PHY_ADDR);
#endif
#if defined(CONFIG_PHYINTF_TAG_VAL)
			setup_phyintf_tag(bd);
#endif
#if defined(CONFIG_PHYGPIO_TAG_VAL)
			setup_phygpio_tag(bd);
#endif
#if defined(CONFIG_CHIPTRIM_TAG_VAL)
			setup_chiptrim_tag(bd);
#endif
#if defined(CONFIG_NANDID_TAG)
			setup_nandid_tag(bd);
#endif
#if defined(CONFIG_NAND_PARAM_TAG)
			set_nand_param_tag(bd);
#endif
#if defined(CONFIG_EMMC_PARAM_TAG)
			set_emmc_param_tag(bd);
#endif
#if defined(CONFIG_SPIID_TAG)
			setup_spiid_tag(bd);
#endif
#if defined(CONFIG_SDKVERSION_TAG)
			setup_sdkversion_tag(bd);
#endif
#if defined(CONFIG_BOOTREG_TAG)
			setup_bootreg_tag(bd);
#endif
			setup_eth_param();
#if defined(CONFIG_RSAKEY_TAG)
			setup_rsakey_param();
#endif
			setup_param_tag(bd);
			setup_end_tag (bd);
#endif
}

#if defined(CONFIG_TEE_SUPPORT) && defined(CONFIG_ASC_SUPPORT)
void start_tee(uint32_t arch, uint32_t entry, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{ 
#if defined(CONFIG_ADVANCED_CHIP)
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
#endif
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
#if defined(CONFIG_ADVANCED_CHIP)
	}
#endif
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
		char *fdt = (char *)image_get_image_end(hdr);
		ret = fdt_check_header(fdt);
		if (ret) {
			printf("Invalid FDT at 0x%p, hdr at 0x%p\n", fdt, hdr);
			goto error;
		}
		bl33_ep.pc = (uint64_t)image_get_data(hdr);
		bl33_ep.args.arg0 = (uint64_t)((uint32_t)fdt);
		bl33_ep.args.arg1 = (uint64_t)(image_get_ep(hdr));
		bl33_ep.args.arg2 = (uint64_t)(image_get_size(hdr));
		bl33_ep.args.arg3 = CFG_BOOT_PARAMS;
		bl33_ep.args.arg4 = CFG_BOOT_PARAMS + CONFIG_BOOT_PARAMS_MAX_SIZE;
		bl33_ep.args.arg5 = (uint64_t)(CONFIG_DTB_MAX_SIZE);
		bl33_ep.spsr = SPSR_64(MODE_EL1,MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
	} else if (arch == BL33_IMG_ARM32){
		bl33_ep.pc = (uint64_t)image_get_data(hdr);
		bl33_ep.args.arg1 = (uint64_t)(image_get_ep(hdr));
		bl33_ep.args.arg2 = (uint64_t)(image_get_size(hdr));
		bl33_ep.args.arg3 = CFG_BOOT_PARAMS;
		bl33_ep.args.arg4 = CFG_BOOT_PARAMS + CONFIG_BOOT_PARAMS_MAX_SIZE;
		bl33_ep.args.arg5 = (uint64_t)(CONFIG_DTB_MAX_SIZE);
		bl33_ep.args.arg6 = (uint64_t)(MACH_TYPE_GODBOX);
		bl33_ep.spsr = SPSR_MODE32(MODE32_svc, 0x0 , EP_EE_LITTLE, DISABLE_ALL_EXCEPTIONS);
	}

	printf("bl33_ep->spsr = 0x%X\n", bl33_ep.spsr);

	bl31_pc = CONFIG_BL31_BASE;

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

	cleanup_before_linux();

	/* warm reseting */
	__asm__ __volatile__("isb\n\r"
		"dsb\n\r"
		"mrc p15, 0, %0, c12, c0, 2\n\r"
		"orr %0, %0, #0x3\n\r"
		"mcr p15, 0, %0, c12, c0, 2\n\r"
		"isb\n\r"
		"wfi":"=r"(val)::"cc");
	printf("Fail to warm resetting...\n");
	hang();

error:
	return 0;
}
#endif

int do_bootm_linux(int flag, int argc, char *argv[], bootm_headers_t *images)
{
	bd_t	*bd = gd->bd;
	char	*s;
	int	machid = bd->bi_arch_number;
	void	(*theKernel)(int zero, int arch, uint params);
	unsigned long r2;
	int notee = 0;

	if ((flag != 0) && (flag != BOOTM_STATE_OS_GO))
		return 1;

	theKernel = (void (*)(int, int, uint))images->ep;

	s = getenv ("machid");
	if (s) {
		machid = simple_strtoul (s, NULL, 16);
		printf ("Using machid 0x%x from environment\n", machid);
	}

	show_boot_progress (15);

	debug ("## Transferring control to Linux (at address %08lx) ...\n",
	       (ulong) theKernel);

	setup_boot_atags(images->rd_start, images->rd_end);

	if (IMAGE_ENABLE_OF_LIBFDT && images->ft_len) {
#ifdef CONFIG_OF_LIBFDT
		r2 = (unsigned long)images->ft_addr;
#endif
	} else
		r2 = bd->bi_boot_params;

#ifndef CONFIG_ARM64_SUPPORT
	/* we assume that the kernel is in place */
	printf ("\nStarting kernel ...\n\n");
#endif

#ifdef CONFIG_USB_DEVICE
	{
		extern void udc_disconnect (void);
		udc_disconnect ();
	}
#endif

	cleanup_before_linux ();

#ifdef CONFIG_TEE_SUPPORT
	if (is_tee_type()) {
#ifdef CONFIG_ASC_SUPPORT
		s = getenv ("notee");
		if (s)
			notee = (*s == 'y') ? 1 : 0;

		if (!notee) {
			if (image_check_arch ((image_header_t *)(images->legacy_hdr_os), IH_ARCH_ARM64)) {
				image_header_t *hdr = (image_header_t *)(images->legacy_hdr_os);
				char *fdt = (char *)image_get_image_end(hdr);

				if (fdt_check_header(fdt)) {
					printf("Invalid FDT at 0x%p, hdr at 0x%p\n", fdt, hdr);
					return 1;
				}

				entry_point_info_t *bl33_ep_info = malloc(sizeof(entry_point_info_t));
				if (!bl33_ep_info) {
					printf("Fail to alloc bl31 params buffer!\n");
					return 1;
				}
				memset(bl33_ep_info, 0, sizeof(entry_point_info_t));
				bl33_ep_info->pc = (uint64_t)image_get_data(hdr);
				bl33_ep_info->args.arg0 = (uint64_t)((uint32_t)fdt);
				bl33_ep_info->args.arg1 = (uint64_t)(image_get_ep(hdr));
				bl33_ep_info->args.arg2 = (uint64_t)(image_get_size(hdr));
				bl33_ep_info->args.arg3 = CFG_BOOT_PARAMS;
				bl33_ep_info->args.arg4 = CFG_BOOT_PARAMS + CONFIG_BOOT_PARAMS_MAX_SIZE;
				bl33_ep_info->args.arg5 = (uint64_t)(CONFIG_DTB_MAX_SIZE);
				bl33_ep_info->spsr = SPSR_64(MODE_EL1, MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);
				start_tee(BL33_IMG_ARM64, (u32)bl33_ep_info, 0, 0, 0, 0);
			} else {
			#ifdef CONFIG_TEE_ATF_SUPPORT
				image_header_t *hdr = (image_header_t *)(images->legacy_hdr_os);
				entry_point_info_t *bl33_ep_info = malloc(sizeof(entry_point_info_t));
				if (!bl33_ep_info) {
					printf("Fail to alloc bl31 params buffer!\n");
					return 1;
				}
				memset(bl33_ep_info, 0, sizeof(entry_point_info_t));
				bl33_ep_info->pc = (uint64_t)images->ep;
				bl33_ep_info->args.arg0 = 0;
				bl33_ep_info->spsr = SPSR_MODE32(MODE32_svc, 0x0 , EP_EE_LITTLE, DISABLE_ALL_EXCEPTIONS);
				start_tee(BL33_IMG_ARM32, (u32)bl33_ep_info, 0, 0, 0, 0);
			#else
				start_tee(BL33_IMG_ARM32, (u32)theKernel, r2, 0, 0, 0);
			#endif

			}
		}
#else /*CONFIG_ASC_SUPPORT*/
#ifdef CONFIG_TEE_ATF_SUPPORT
		if (image_check_arch ((image_header_t *)(images->legacy_hdr_os), IH_ARCH_ARM)) {
			printf("Start TEE with aarch32 kernel...\n");
			start_tee_atf(BL33_IMG_ARM32, (char *)images->legacy_hdr_os, 0, 0, 0, 0);
		}
		else if (image_check_arch ((image_header_t *)(images->legacy_hdr_os), IH_ARCH_ARM64)) {
			printf("Start TEE with aarch64 kernel...\n");
			start_tee_atf(BL33_IMG_ARM64, (char *)images->legacy_hdr_os, 0, 0, 0, 0);
		}
		else
			printf("ARCH type not support!!!\n");
#else /*CONFIG_TEE_ATF_SUPPORT*/
		if (secure_entry_addr) {
			void (*secure_entry)(int, int, int, int, int, int) = (void(*)(int, int, int, int, int, int))(secure_entry_addr);
			unsigned int text_end = roundup(_text_end, 0x10); /* align for secure os clean boot */
			secure_entry(0, (int)machid, (int)r2, (int)theKernel, TEXT_BASE, text_end);
		}
#endif /*CONFIG_TEE_ATF_SUPPORT*/
#endif /*CONFIG_ASC_SUPPORT*/
	}
#endif /*CONFIG_TEE_SUPPORT*/

#ifdef CONFIG_SBL_VXX_UXX
	{
		smc_cmd_args_t cmd_args;
		uint32_t spsr;
		image_header_t *hdr = (image_header_t *)(images->legacy_hdr_os);
		if (image_check_arch (hdr, IH_ARCH_ARM64)) {
			char *fdt = (char *)image_get_image_end(hdr);
			if (fdt_check_header(fdt)) {
				printf("Invalid FDT at 0x%p, hdr at 0x%p\n", fdt, hdr);
				return 1;
			}
			theKernel = (void (*)(int, int, uint))image_get_data(hdr);
			cmd_args.arg1 = (uint64_t)((uint32_t)fdt);
			cmd_args.arg2 = (uint64_t)(image_get_ep(hdr));
			cmd_args.arg3 = (uint64_t)image_get_data_size(hdr) + CONFIG_DTB_MAX_SIZE;
			cmd_args.arg4 = CFG_BOOT_PARAMS + CONFIG_BOOT_PARAMS_MAX_SIZE;
			cmd_args.arg5 = (uint64_t)(CONFIG_DTB_MAX_SIZE);
			spsr = SPSR_64(MODE_EL1,
						MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);

			cmd_args.arg4 = (uint64_t)((uint32_t)fdt);

			return exec_smc(ARM_BOOT_SMC_CALL, (u32)theKernel, spsr, (u32)&cmd_args);
		} else
			theKernel (0, machid, r2);
	}
#else /*CONFIG_SBL_VXX_UXX*/
	theKernel (0, machid, r2);
#endif
	/* does not return */

	return 1;
}


#if defined(CONFIG_SETUP_MEMORY_TAGS) || \
defined(CONFIG_CMDLINE_TAG) || \
defined(CONFIG_INITRD_TAG) || \
defined(CONFIG_SERIAL_TAG) || \
defined(CONFIG_REVISION_TAG) || \
defined(CONFIG_ETHADDR_TAG) || \
defined(CONFIG_SDKVERSION_TAG) || \
defined(CONFIG_BOOTREG_TAG)
static void setup_start_tag (bd_t *bd)
{
	params = (struct tag *) bd->bi_boot_params;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}

#ifdef CONFIG_SETUP_MEMORY_TAGS
static void setup_memory_tags (bd_t *bd)
{
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		params->hdr.tag = ATAG_MEM;
		params->hdr.size = tag_size (tag_mem64);

		params->u.mem.start = (u64)bd->bi_dram[i].start;
		params->u.mem.size = (u64)bd->bi_dram[i].size;

		params = tag_next (params);
	}
}
#endif /* CONFIG_SETUP_MEMORY_TAGS */

static void setup_commandline_tag (bd_t *bd, char *commandline)
{
	char *p;

	if (!commandline)
		return;

	/* eat leading white space */
	for (p = commandline; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;

	strncpy (params->u.cmdline.cmdline, p, strlen(p));
	params->u.cmdline.cmdline[strlen(p)] = '\0';

	params = tag_next (params);
}

#ifdef CONFIG_ETHMDIO_INF
static void setup_eth_mdiointf_tag(bd_t *bd, char *mdio_intf)
{
	unsigned char mac[6];
	if (!mdio_intf)
		return ;
	params->hdr.tag = CONFIG_ETH_MDIO_INF_TAG_VAL;
	params->hdr.size = 4;

	memcpy(&params->u, mdio_intf, (strlen(mdio_intf)+1));
	params = tag_next(params);
}
#endif
#ifdef CONFIG_ETHADDR_TAG
static void string_to_mac(unsigned char *mac, char* s)
{
	int i;
	char *e;

	for (i = 0; i < 6; ++i) {
		mac[i] = s ? simple_strtoul(s, &e, 16) : 0;
		if (s)
			s = (*e) ? e+1 : e;
	}
}

static void setup_ethaddr_tag(bd_t *bd, char *ethaddr)
{
	unsigned char mac[6];
	if (!ethaddr)
		return ;

	params->hdr.tag = CONFIG_ETHADDR_TAG_VAL;
	params->hdr.size = 4;

	string_to_mac(&mac[0], ethaddr);
	memcpy(&params->u, mac, 6);

	params = tag_next(params);
}

static void setup_phyaddr_tag(bd_t *bd, int phy_addr_up, int phy_addr_down)
{
	params->hdr.tag = CONFIG_PHYADDR_TAG_VAL;
	params->hdr.size = 4;

	*(int*)(&params->u) = phy_addr_up;
	*((int*)(&params->u) + 1) = phy_addr_down;

	params = tag_next(params);
}
#endif

#ifdef CONFIG_PHYINTF_TAG_VAL
static void setup_phyintf_tag(bd_t *bd)
{
	char *env;

	params->hdr.tag = CONFIG_PHYINTF_TAG_VAL;

	env = get_eth_phyintf_str();
	if (!env)
		return;

	memset(&params->u, '\0', strlen(env) + 1);
	memcpy(&params->u, env, strlen(env));
	params->hdr.size = (sizeof(struct tag_header)
			+ strlen(env) + 1 + 4) >> 2;
	params = tag_next(params);
}
#endif

#ifdef CONFIG_PHYGPIO_TAG_VAL
static void setup_phygpio_tag(bd_t *bd)
{
	int i;

	params->hdr.tag = CONFIG_PHYGPIO_TAG_VAL;
	params->hdr.size = 6;
	for (i = 0; i < 2; i++) {
		u32 gpio_base, gpio_bit;

		get_eth_phygpio(i, &gpio_base, &gpio_bit);
		*((u32*)(&params->u) + (i * 2)) = gpio_base;
		*((u32*)(&params->u) + (i * 2) + 1) = gpio_bit;
	}

	params = tag_next(params);
}
#endif

#ifdef CONFIG_CHIPTRIM_TAG_VAL
extern char *chiptrim_value;
extern int chiptrim_size;
static void setup_chiptrim_tag(bd_t *bd)
{
	params->hdr.tag = CONFIG_CHIPTRIM_TAG_VAL;
	params->hdr.size = (sizeof(struct tag_header) + chiptrim_size) >> 2;

	memcpy(&params->u, chiptrim_value, chiptrim_size);

	params = tag_next(params);
}
#endif

#ifdef CONFIG_NANDID_TAG
extern struct nand_tag nandtag[1];

static void setup_nandid_tag(bd_t *bd)
{
	if (nandtag->length == 0)
		return;

	params->hdr.tag = ATAG_NDNDID;
	params->hdr.size = (sizeof(struct tag_header)
			+ sizeof(struct nand_tag)) >> 2;

	memcpy(&params->u, nandtag, sizeof(struct nand_tag));

	params = tag_next(params);
}
#endif

#ifdef CONFIG_NAND_PARAM_TAG
extern int nand_get_rr_param(char *param);

static void set_nand_param_tag(bd_t *bd)
{
	int size;

	params->hdr.tag = ATAG_NAND_PARAM;
	size = nand_get_rr_param((char *)&params->u);
	params->hdr.size = (sizeof(struct tag_header) + size) >> 2;
	params = tag_next(params);
}
#endif /* CONFIG_NAND_PARAM_TAG */

#ifdef CONFIG_EMMC_PARAM_TAG
u32 emmc_offline = 1;
u32 emmc_samplephase = 3;
u32 emmc_caps2 = 0;
static void set_emmc_param_tag(bd_t *bd)
{
	params->hdr.tag = ATAG_EMMC_PARAM;
	params->hdr.size = 4;
	*((u32*)&params->u) = emmc_offline;
	*(((u32*)&params->u) + 1) = emmc_samplephase | (emmc_caps2 << 8);

	params = tag_next(params);
}
#endif /* CONFIG_NAND_PARAM_TAG */

#ifdef CONFIG_SPIID_TAG
extern struct spi_tag spitag[1];

static void setup_spiid_tag(bd_t *bd)
{
	if (spitag->id_len == 0)
		return;

	params->hdr.tag = ATAG_SPIID;
	params->hdr.size = (sizeof(struct tag_header) +
			sizeof(struct spi_tag)) >> 2;

	memcpy(&params->u, &spitag, sizeof(struct spi_tag));

	params = tag_next(params);
}
#endif

#ifdef CONFIG_SDKVERSION_TAG
#define SDKVERSION_LENGTH                 64
static void setup_sdkversion_tag(bd_t *bd)
{
	char *version = CONFIG_SDKVERSION;

	params->hdr.tag = CONFIG_SDKVERSION_TAG_VAL;
	params->hdr.size = (sizeof(struct tag_header) + SDKVERSION_LENGTH) >> 2;
	memcpy(&params->u, version, SDKVERSION_LENGTH);

	params = tag_next(params);
}
#endif

#ifdef CONFIG_BOOTREG_TAG
static void setup_bootreg_tag(bd_t *bd)
{
	extern unsigned int _blank_zone_start;
	extern unsigned int _blank_zone_end;
	int length = _blank_zone_end - _blank_zone_start;

	params->hdr.tag = CONFIG_BOOTREG_TAG_VAL;
	params->hdr.size = (sizeof(struct tag_header)
		+ sizeof(int) + length) >> 2;
	*(int *)&params->u = length;
	memcpy(((char *)&params->u + sizeof(int)),
		(char *)_blank_zone_start, length);

	params = tag_next(params);
}
#endif

#ifdef CONFIG_INITRD_TAG
static void setup_initrd_tag (bd_t *bd, ulong initrd_start, ulong initrd_end)
{
	/* an ATAG_INITRD node tells the kernel where the compressed
	 * ramdisk can be found. ATAG_RDIMG is a better name, actually.
	 */
	params->hdr.tag = ATAG_INITRD2;
	params->hdr.size = tag_size (tag_initrd);

	params->u.initrd.start = initrd_start;
	params->u.initrd.size = initrd_end - initrd_start;

	params = tag_next (params);
}
#endif /* CONFIG_INITRD_TAG */

#ifdef CONFIG_SERIAL_TAG
void setup_serial_tag (struct tag **tmp)
{
	struct tag *params = *tmp;
	struct tag_serialnr serialnr;
	void get_board_serial(struct tag_serialnr *serialnr);

	get_board_serial(&serialnr);
	params->hdr.tag = ATAG_SERIAL;
	params->hdr.size = tag_size (tag_serialnr);
	params->u.serialnr.low = serialnr.low;
	params->u.serialnr.high= serialnr.high;
	params = tag_next (params);
	*tmp = params;
}
#endif

#ifdef CONFIG_REVISION_TAG
void setup_revision_tag(struct tag **in_params)
{
	u32 rev = 0;
	u32 get_board_rev(void);

	rev = get_board_rev();
	params->hdr.tag = ATAG_REVISION;
	params->hdr.size = tag_size (tag_revision);
	params->u.revision.rev = rev;
	params = tag_next (params);
}
#endif  /* CONFIG_REVISION_TAG */

extern int get_param_tag_data(char *tagbuf);

static void setup_eth_param(void)
{
	int i;
	char *env;
#define MAX_MAC_NUMS    (2)

	env = get_eth_phymdio_str();
	if (env)
		set_param_data("phymdio", env, strlen(env));

	env = get_eth_phyaddr_str();
	if (env)
		set_param_data("phyaddr", env, strlen(env));

	env = get_eth_phyintf_str();
	if (env)
		set_param_data("phyintf", env, strlen(env));

	env = getenv("ethaddr");
	if (env)
		set_param_data("ethaddr", env, strlen(env));

	for (i = 0; i < MAX_MAC_NUMS; i++) {
		char name[16];
		u32 gpio_base, gpio_bit, data[2];

		get_eth_phygpio(i, &gpio_base, &gpio_bit);
		if (!gpio_base)
			continue;
		snprintf(name, sizeof(name), "phyio%d", i);
		data[0] = gpio_base;
		data[1] = gpio_bit;
		set_param_data(name, (const char *)&data, sizeof(data));
	}
}

static void setup_param_tag(bd_t *bd)
{
	int length;

	length = get_param_tag_data((char *)&params->u);
	if (!length)
		return;

	params->hdr.tag  = 0x70000001;
	params->hdr.size = ((sizeof(struct tag_header) + length) >> 2);

	params = tag_next(params);
}

#ifdef CONFIG_RSAKEY_TAG
/* rsa public key is defined and assigned value in product code. */
extern unsigned char g_customer_rsa_public_key_N[256];
extern unsigned int g_customer_rsa_public_key_E;
extern unsigned char g_partition_hash[96];

/* transfer rsakey to linux */
static void setup_rsakey_param(void)
{
	unsigned char key_e[4];
	unsigned int rsakey_e = g_customer_rsa_public_key_E;

	key_e[0] = 0xff & (rsakey_e >> 24);
	key_e[1] = 0xff & (rsakey_e >> 16);
	key_e[2] = 0xff & (rsakey_e >> 8);
	key_e[3] = 0xff & (rsakey_e);

	set_param_data("rsa_e", key_e, sizeof(key_e));
	set_param_data("rsa_n", g_customer_rsa_public_key_N, sizeof(g_customer_rsa_public_key_N));
	set_param_data("rsa_ha", g_partition_hash, sizeof(g_partition_hash));
}
#endif

static void setup_end_tag (bd_t *bd)
{

	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;

	if (((ulong)params - bd->bi_boot_params) >= CONFIG_BOOT_PARAMS_MAX_SIZE) {
		printf("ERROR: NOT enough TAG area!\n");
		hang();
	}

	printf("ATAGS [0x%08lX - 0x%08lX], %luBytes\n", bd->bi_boot_params, (ulong)params, ((ulong)params - bd->bi_boot_params));
}

#endif /* CONFIG_SETUP_MEMORY_TAGS || CONFIG_CMDLINE_TAG || CONFIG_INITRD_TAG */
