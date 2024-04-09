/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Lai Yingjun
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

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <malloc.h>
#include <cmd-words.h>
#include <memory.h>
#include <mmc_if.h>
#include "mmc_drv.h"

extern struct flash_info_t *get_mmcdev_info(void);
extern struct mmc_dev_t *get_mmcdev(int devnum);
extern int select_boot_part(struct mmc_dev_t *mmc_dev, int boot_part);
extern int confirm_yesno(void);

static int do_mmc_read(struct cmd_t *cmd)
{
	int index = param_first(cmd);
	uint32 devnum = param_int32(cmd, index++);
	uint32 addr = param_int32(cmd, index++);
	uint64 offset = param_int64(cmd, index++);
	uint32 size = param_int32(cmd, index++);
	uint32 cnt = size;
	uint64 ret = 0;
	uint32 blk = offset;
	uint32 blocksize = get_mmcdev_info()->blocksize;

	struct mmc_dev_t *mmc_dev = get_mmcdev(devnum);
	if (!mmc_dev) {
		printf("No mmc device %d\n", devnum);
		return 1;
	}

	printf("\nMMC read: dev # %d, block # %d, count %d ... ",
		devnum, blk, cnt);

	ret = mmcdev_read(blk * blocksize, (void *)addr, cnt * blocksize);

	printf("%llu blocks read: %s\n",
		ret / blocksize, (ret / blocksize == cnt) ? "OK" : "ERROR");
	return (ret / blocksize == cnt) ? 0 : 1;
}

CMD({&cw_mmc, NULL},
{&cw_read, NULL},
{&cw_devnum, NULL},
{&cw_addr, _T("memory address to save the data"), NULL},
{&cw_offset, _T("mmc offset"), NULL},
{&cw_size, _T("mmc read data length"), do_mmc_read});


static int do_mmc_write(struct cmd_t *cmd)
{
	int index = param_first(cmd);
	uint32 devnum = param_int32(cmd, index++);
	uint32 addr = param_int32(cmd, index++);
	uint64 offset = param_int64(cmd, index++);
	uint32 size = param_int32(cmd, index++);
	uint32 cnt = size;
	uint64 ret = 0;
	uint32 blk = offset;
	struct mmc_dev_t *mmc_dev = get_mmcdev(devnum);
	uint32 blocksize = get_mmcdev_info()->blocksize;

	if (!mmc_dev) {
		printf("No mmc device %d\n", devnum);
		return 1;
	}

	printf("\nMMC write: dev # %d, block # %d, count %d ... ",
		devnum, blk, cnt);

	ret = mmcdev_write(blk * blocksize, (void *)addr, cnt * blocksize);

	printf("%llu blocks written: %s\n",
		ret / blocksize, (ret / blocksize == cnt) ? "OK" : "ERROR");
	return (ret / blocksize == cnt) ? 0 : 1;
}

CMD({&cw_mmc, NULL},
{&cw_write, NULL},
{&cw_devnum, NULL},
{&cw_addr, _T("memory address that the data got from"), NULL},
{&cw_offset, _T("device offset"), NULL},
{&cw_size, _T("data length"), do_mmc_write});

static int confirm_key_prog(void)
{
	puts("Warning: Programming authentication key can be done only once !\n"
		 "         Use this command only if you are sure of what you are doing,\n"
		 "Really perform the key programming? <y/N> ");
	if (confirm_yesno())
		return 1;

	puts("Authentication key programming aborted\n");
	return 0;
}
static int do_mmcrpmb_key(struct cmd_t *cmd)
{
	int index = param_first(cmd);
	uint32 devnum = param_int32(cmd, index++);
	uint32 key_addr = param_int32(cmd, index++);
	struct mmc_dev_t *mmc = get_mmcdev(devnum);

	/* Switch to the RPMB partition */
	if (select_boot_part(mmc, MMC_PART_RPMB) != 0) {
		printf("failed to select rpmb partition.\n");
		return false;
	}

	if (!confirm_key_prog())
		return false;

	if (mmc_rpmb_set_key(mmc, (void *)key_addr)) {
		printf("ERROR - Key already programmed ?\n");
		return false;
	}

	/* Return to original partition */
	if (select_boot_part(mmc, 0x0) != 0) {
		printf("failed to restore partition.\n");
		return false;
	}

	return 0;
}

CMD({&cw_mmc, NULL},
{&cw_key_rpmb, NULL},
{&cw_devnum, NULL},
{&cw_addr, _T("memory address that h/mac key data(32 bytes)"), do_mmcrpmb_key});

static int do_mmcrpmb_read(struct cmd_t *cmd)
{
	int n=0;
	int index = param_first(cmd);
	uint32 devnum = param_int32(cmd, index++);
	uint32 addr = param_int32(cmd, index++);
	uint64 offset = param_int64(cmd, index++);
	uint32 size = param_int32(cmd, index++);
	uint32 key_addr = param_int32(cmd, index++);
	uint32 cnt = size;
	uint32 blk = offset;
	struct mmc_dev_t *mmc = get_mmcdev(devnum);

	/* Switch to the RPMB partition */
	if (select_boot_part(mmc, MMC_PART_RPMB) != 0) {
		printf("failed to select rpmb partition.\n");
		return false;
	}

	printf("\nMMC RPMB read: dev # %d, block # %d, count %d ... ",
		   devnum, blk, cnt);
	n =  mmc_rpmb_read(mmc, (void *)addr, blk, cnt, (void *)key_addr);

	printf("%d RPMB blocks read: %s\n", n, (n == cnt) ? "OK" : "ERROR");
	if (n != cnt)
		return false;

	/* Return to original partition */
	if (select_boot_part(mmc, 0x0) != 0) {
		printf("failed to restore partition.\n");
		return false;
	}

	return 0;
}

CMD({&cw_mmc, NULL},
{&cw_read_rpmb, NULL},
{&cw_devnum, NULL},
{&cw_addr, _T("memory address to save the data"), NULL},
{&cw_offset, _T("mmc offset(block numer)"), NULL},
{&cw_size, _T("mmc read data length(block number)"), NULL},
{&cw_addr, _T("memory address that key data got from"), do_mmcrpmb_read});

static int do_mmcrpmb_write(struct cmd_t *cmd)
{
	int n=0;
	int index = param_first(cmd);
	uint32 devnum = param_int32(cmd, index++);
	uint32 addr = param_int32(cmd, index++);
	uint64 offset = param_int64(cmd, index++);
	uint32 size = param_int32(cmd, index++);
	uint32 key_addr = param_int32(cmd, index++);
	uint32 cnt = size;
	uint32 blk = offset;
	struct mmc_dev_t *mmc = get_mmcdev(devnum);

	/* Switch to the RPMB partition */
	if (select_boot_part(mmc, MMC_PART_RPMB) != 0) {
		printf("failed to select rpmb partition.\n");
		return false;
	}

	printf("\nMMC RPMB write: dev # %d, block # %d, count %d ... ",
		   devnum, blk, cnt);
	n =  mmc_rpmb_write(mmc, (void *)addr, blk, cnt, (void *)key_addr);

	printf("%d RPMB blocks written: %s\n", n, (n == cnt) ? "OK" : "ERROR");
	if (n != cnt)
		return false;

	/* Return to original partition */
	if (select_boot_part(mmc, 0x0) != 0) {
		printf("failed to restore partition.\n");
		return false;
	}

	return 0;
}

CMD({&cw_mmc, NULL},
{&cw_write_rpmb, NULL},
{&cw_devnum, NULL},
{&cw_addr, _T("memory address that the data got from"), NULL},
{&cw_offset, _T("device offset(block numer)"), NULL},
{&cw_size, _T("data length(block numer)"), NULL},
{&cw_addr, _T("memory address that key data got from"), do_mmcrpmb_write});

static int do_mmcrpmb_counter(struct cmd_t *cmd)
{
	unsigned long counter;
	int index = param_first(cmd);
	uint32 devnum = param_int32(cmd, index++);
	struct mmc_dev_t *mmc = get_mmcdev(devnum);

	/* Switch to the RPMB partition */
	if (select_boot_part(mmc, MMC_PART_RPMB) != 0) {
		printf("failed to select rpmb partition.\n");
		return false;
	}

	if (mmc_rpmb_get_counter(mmc, &counter)) {
		printf("Err: faied to get RPMB write counter.\n");
		return false;
	}

	/* Return to original partition */
	if (select_boot_part(mmc, 0x0) != 0) {
		printf("failed to restore partition.\n");
		return false;
	}

	printf("RPMB Write counter= 0x%lx\n", counter);

	return 0;
}

CMD({&cw_mmc, NULL},
{&cw_counter_rpmb, NULL},
{&cw_devnum, _T("mmc device number, 0,1"), do_mmcrpmb_counter});
